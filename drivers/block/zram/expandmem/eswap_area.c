/*
 * Expanded RAM block device
 * Description: expanded memory implement
 *
 * Released under the terms of GNU General Public License Version 2.0
 *
 */

#define KMSG_COMPONENT "expandmem"
#define pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#include <linux/kernel.h>
#include <linux/memcontrol.h>

#include "eswap.h"
#include "expandmem.h"
#include "eswap_common.h"
#include "eswap_area.h"
#include "eswap_list.h"

struct mem_cgroup *get_mem_cgroup(unsigned short mcg_id)
{
	struct mem_cgroup *mcg = NULL;

	rcu_read_lock();
	mcg = mem_cgroup_from_id(mcg_id);
	rcu_read_unlock();

	return mcg;
}

int obj_idx(struct eswap_area *area, int idx)
{
	if (!area) {
		eswap_print(LEVEL_WARN, "area is null\n");
		return -EINVAL;
	}
	if (idx < 0 || idx >= area->nr_objs) {
		eswap_print(LEVEL_WARN, "idx = %d invalid\n", idx);
		return -EINVAL;
	}

	return idx;
}

int ext_idx(struct eswap_area *area, int idx)
{
	if (!area) {
		eswap_print(LEVEL_WARN, "area is null\n");
		return -EINVAL;
	}
	if (idx < 0 || idx >= area->nr_exts) {
		eswap_print(LEVEL_WARN, "idx = %d invalid\n", idx);
		return -EINVAL;
	}

	return idx + area->nr_objs;
}

int mcg_idx(struct eswap_area *area, int idx)
{
	if (!area) {
		eswap_print(LEVEL_WARN, "area is null\n");
		return -EINVAL;
	}
	if (idx <= 0 || idx >= area->nr_mcgs) {
		eswap_print(LEVEL_DEBUG, "idx = %d invalid\n", idx);
		return -EINVAL;
	}

	return idx + area->nr_objs + area->nr_exts;
}

static int extent_id2bit(struct eswap_area *area, int id)
{
	if (id < 0 || id >= area->nr_exts) {
		eswap_print(LEVEL_WARN, "id = %d invalid\n", id);
		return -EINVAL;
	}

	return area->nr_exts - id - 1;
}

static int extent_bit2id(struct eswap_area *area, int bit)
{
	if (bit < 0 || bit >= area->nr_exts) {
		eswap_print(LEVEL_WARN, "bit = %d invalid\n", bit);
		return -EINVAL;
	}

	return area->nr_exts - bit - 1;
}

static bool fragment_dec(bool prev_flag, bool next_flag,
			 struct eswap_stat *stat)
{
	if (prev_flag && next_flag) {
		atomic64_inc(&stat->frag_cnt);
		return false;
	}

	if (prev_flag || next_flag)
		return false;

	return true;
}

static bool fragment_inc(bool prev_flag, bool next_flag,
			 struct eswap_stat *stat)
{
	if (prev_flag && next_flag) {
		atomic64_dec(&stat->frag_cnt);
		return false;
	}

	if (prev_flag || next_flag)
		return false;

	return true;
}

static bool prev_is_cont(struct eswap_area *area, int ext_id, int mcg_id)
{
	int prev;

	if (is_first_idx(ext_idx(area, ext_id), mcg_idx(area, mcg_id),
			 area->ext_table))
		return false;
	prev = prev_idx(ext_idx(area, ext_id), area->ext_table);

	return (prev >= 0) && (ext_idx(area, ext_id) == prev + 1);
}

static bool next_is_cont(struct eswap_area *area, int ext_id, int mcg_id)
{
	int next;

	if (is_last_idx(ext_idx(area, ext_id), mcg_idx(area, mcg_id),
			area->ext_table))
		return false;
	next = next_idx(ext_idx(area, ext_id), area->ext_table);

	return (next >= 0) && (ext_idx(area, ext_id) + 1 == next);
}

static void ext_fragment_sub(struct eswap_area *area, int ext_id)
{
	bool prev_flag = false;
	bool next_flag = false;
	int mcg_id;
	struct eswap_stat *stat = eswap_get_stat_obj();

	if (!stat) {
		eswap_print(LEVEL_WARN, "stat is null\n");
		return;
	}

	if (!area->ext_table) {
		eswap_print(LEVEL_WARN, "table is null\n");
		return;
	}
	if (ext_id < 0 || ext_id >= area->nr_exts) {
		eswap_print(LEVEL_WARN, "ext = %d invalid\n", ext_id);
		return;
	}

	mcg_id = eswap_list_get_mcgid(ext_idx(area, ext_id), area->ext_table);
	if (mcg_id <= 0 || mcg_id >= area->nr_mcgs) {
		eswap_print(LEVEL_WARN, "mcg_id = %d invalid\n", mcg_id);
		return;
	}

	atomic64_dec(&stat->ext_cnt);
	area->mcg_id_cnt[mcg_id]--;
	if (area->mcg_id_cnt[mcg_id] == 0) {
		atomic64_dec(&stat->mcg_cnt);
		atomic64_dec(&stat->frag_cnt);
		return;
	}

	prev_flag = prev_is_cont(area, ext_id, mcg_id);
	next_flag = next_is_cont(area, ext_id, mcg_id);

	if (fragment_dec(prev_flag, next_flag, stat))
		atomic64_dec(&stat->frag_cnt);
}

static void ext_fragment_add(struct eswap_area *area, int ext_id)
{
	bool prev_flag = false;
	bool next_flag = false;
	int mcg_id;
	struct eswap_stat *stat = eswap_get_stat_obj();

	if (!stat) {
		eswap_print(LEVEL_WARN, "stat is null\n");
		return;
	}

	if (!area->ext_table) {
		eswap_print(LEVEL_WARN, "table is null\n");
		return;
	}
	if (ext_id < 0 || ext_id >= area->nr_exts) {
		eswap_print(LEVEL_WARN, "ext = %d invalid\n", ext_id);
		return;
	}

	mcg_id = eswap_list_get_mcgid(ext_idx(area, ext_id), area->ext_table);
	if (mcg_id <= 0 || mcg_id >= area->nr_mcgs) {
		eswap_print(LEVEL_WARN, "mcg_id = %d invalid\n", mcg_id);
		return;
	}

	atomic64_inc(&stat->ext_cnt);
	if (area->mcg_id_cnt[mcg_id] == 0) {
		area->mcg_id_cnt[mcg_id]++;
		atomic64_inc(&stat->frag_cnt);
		atomic64_inc(&stat->mcg_cnt);
		return;
	}
	area->mcg_id_cnt[mcg_id]++;

	prev_flag = prev_is_cont(area, ext_id, mcg_id);
	next_flag = next_is_cont(area, ext_id, mcg_id);

	if (fragment_inc(prev_flag, next_flag, stat))
		atomic64_inc(&stat->frag_cnt);
}

void eswap_free_extent(struct eswap_area *area, int ext_id)
{
	if (!area) {
		eswap_print(LEVEL_WARN, "area is null\n");
		return;
	}
	if (ext_id < 0 || ext_id >= area->nr_exts) {
		eswap_print(LEVEL_WARN, "INVALID ext %d\n", ext_id);
		return;
	}
	eswap_print(LEVEL_DEBUG, "free ext id = %d\n", ext_id);

	eswap_list_set_mcgid(ext_idx(area, ext_id), area->ext_table, 0);

	if (!test_and_clear_bit(extent_id2bit(area, ext_id), area->bitmap)) {
		eswap_print(LEVEL_ERR, "bit not set, ext = %d\n", ext_id);
		WARN_ON_ONCE(1);
	}

	atomic_dec(&area->stored_exts);
}

static int alloc_bitmap(unsigned long *bitmap, int max, int last_bit)
{
	int bit;

	if (!bitmap) {
		eswap_print(LEVEL_ERR, "bitmap is null\n");
		return -EINVAL;
	}
retry:
	bit = find_next_zero_bit(bitmap, max, last_bit);
	if (bit == max) {
		if (last_bit == 0) {
			eswap_print(LEVEL_ERR, "alloc bitmap failed\n");
			return -ENOSPC;
		}
		last_bit = 0;
		goto retry;
	}
	if (test_and_set_bit(bit, bitmap))
		goto retry;

	return bit;
}

int eswap_alloc_extent(struct eswap_area *area, struct mem_cgroup *mcg)
{
	int last_bit;
	int bit;
	int ext_id;
	int mcg_id;

	if (!area) {
		eswap_print(LEVEL_WARN, "area is null\n");
		return -EINVAL;
	}
	if (!mcg) {
		eswap_print(LEVEL_WARN, "mcg is null\n");
		return -EINVAL;
	}

	last_bit = atomic_read(&area->last_alloc_bit);
	eswap_print(LEVEL_DEBUG, "last_bit = %d\n", last_bit);
	bit = alloc_bitmap(area->bitmap, area->nr_exts, last_bit);
	if (bit < 0) {
		eswap_print(LEVEL_WARN, "alloc bitmap failed\n");
		return bit;
	}
	ext_id = extent_bit2id(area, bit);
	mcg_id = eswap_list_get_mcgid(ext_idx(area, ext_id), area->ext_table);

	if (mcg_id) {
		eswap_print(LEVEL_WARN, "already has mcg %d, ext %d\n",
				mcg_id, ext_id);
		goto err_out;
	}

	eswap_list_set_mcgid(ext_idx(area, ext_id), area->ext_table, mcg->id.id);

	atomic_set(&area->last_alloc_bit, bit);
	atomic_inc(&area->stored_exts);
	eswap_print(LEVEL_DEBUG, "extent init OK, mcg_id = %d, ext id = %d\n", mcg->id.id, ext_id);

	return ext_id;
err_out:
	clear_bit(bit, area->bitmap);
	WARN_ON_ONCE(1);
	return -EBUSY;

}

int get_extent(struct eswap_area *area, int ext_id)
{
	int mcg_id;
	int idx;
	struct eswap_list_head *node;

	if (!area) {
		eswap_print(LEVEL_WARN, "area is null\n");
		return -EINVAL;
	}
	if (ext_id < 0 || ext_id >= area->nr_exts) {
		eswap_print(LEVEL_WARN, "ext = %d invalid\n", ext_id);
		return -EINVAL;
	}

	idx = ext_idx(area, ext_id);
	node = idx_node(idx, area->ext_table);
	if (!node) {
		eswap_print(LEVEL_WARN, "idx = %d, table = %pK invalid\n", idx, area->ext_table);
		return -EINVAL;
	}

	if (!eswap_list_clear_priv(idx, area->ext_table))
		return -EBUSY;

	mcg_id = eswap_list_get_mcgid(idx, area->ext_table);
	if (mcg_id) {
		ext_fragment_sub(area, ext_id);
		eswap_list_del(idx, mcg_idx(area, mcg_id),
			    area->ext_table);
	}
	eswap_print(LEVEL_DEBUG, "ext id = %d\n", ext_id);

	return ext_id;
}

void put_extent(struct eswap_area *area, int ext_id)
{
	int mcg_id;

	if (!area) {
		eswap_print(LEVEL_WARN, "area is null\n");
		return;
	}
	if (ext_id < 0 || ext_id >= area->nr_exts) {
		eswap_print(LEVEL_WARN, "ext = %d invalid\n", ext_id);
		return;
	}

	mcg_id = eswap_list_get_mcgid(ext_idx(area, ext_id), area->ext_table);
	if (mcg_id) {
		eswap_lock_list(mcg_idx(area, mcg_id), area->ext_table);
		eswap_list_add_nolock(ext_idx(area, ext_id), mcg_idx(area, mcg_id),
			area->ext_table);
		ext_fragment_add(area, ext_id);
		eswap_unlock_list(mcg_idx(area, mcg_id), area->ext_table);
	}
	if (!eswap_list_set_priv(ext_idx(area, ext_id), area->ext_table)) {
		eswap_print(LEVEL_WARN, "private not set, ext = %d\n", ext_id);
		WARN_ON_ONCE(1);
		return;
	}
	eswap_print(LEVEL_DEBUG, "put extent %d\n", ext_id);
}

int get_memcg_extent(struct eswap_area *area, struct mem_cgroup *mcg)
{
	int mcg_id;
	int ext_id = -ENOENT;
	int idx;

	if (!area) {
		eswap_print(LEVEL_WARN, "area is null\n");
		return -EINVAL;
	}
	if (!area->ext_table) {
		eswap_print(LEVEL_WARN, "table is null\n");
		return -EINVAL;
	}
	if (!mcg) {
		eswap_print(LEVEL_WARN, "mcg is null\n");
		return -EINVAL;
	}

	mcg_id = mcg->id.id;
	eswap_lock_list(mcg_idx(area, mcg_id), area->ext_table);
	eswap_list_for_each_entry(idx, mcg_idx(area, mcg_id), area->ext_table)
		if (eswap_list_clear_priv(idx, area->ext_table)) {
			ext_id = idx - area->nr_objs;
			break;
		}
	if (ext_id >= 0 && ext_id < area->nr_exts) {
		ext_fragment_sub(area, ext_id);
		eswap_list_del_nolock(idx, mcg_idx(area, mcg_id), area->ext_table);
		eswap_print(LEVEL_DEBUG, "ext id = %d\n", ext_id);
	}
	eswap_unlock_list(mcg_idx(area, mcg_id), area->ext_table);

	return ext_id;
}

int get_memcg_zram_entry(struct eswap_area *area, struct mem_cgroup *mcg)
{
	int mcg_id, idx;
	int index = -ENOENT;

	if (!area) {
		eswap_print(LEVEL_WARN, "area is null\n");
		return -EINVAL;
	}
	if (!area->obj_table) {
		eswap_print(LEVEL_WARN, "table is null\n");
		return -EINVAL;
	}
	if (!mcg) {
		eswap_print(LEVEL_WARN, "mcg is null\n");
		return -EINVAL;
	}

	mcg_id = mcg->id.id;
	eswap_lock_list(mcg_idx(area, mcg_id), area->obj_table);
	eswap_list_for_each_entry(idx, mcg_idx(area, mcg_id), area->obj_table) {
		index = idx;
		break;
	}
	eswap_unlock_list(mcg_idx(area, mcg_id), area->obj_table);

	return index;
}

static void free_obj_list_table(struct eswap_area *area)
{
	if (!area) {
		eswap_print(LEVEL_WARN, "area is null\n");
		return;
	}

	if (area->lru) {
		vfree(area->lru);
		area->lru = NULL;
	}
	if (area->rmap) {
		vfree(area->rmap);
		area->rmap = NULL;
	}

	kfree(area->obj_table);
	area->obj_table = NULL;
}

static struct eswap_list_head *get_obj_table_node(int idx, void *private)
{
	struct eswap_area *area = private;

	if (!area) {
		eswap_print(LEVEL_WARN, "area is null\n");
		return NULL;
	}
	if (idx < 0) {
		eswap_print(LEVEL_DEBUG, "idx = %d invalid\n", idx);
		return NULL;
	}
	if (idx < area->nr_objs)
		return &area->lru[idx];
	idx -= area->nr_objs;
	if (idx < area->nr_exts)
		return &area->rmap[idx];
	idx -= area->nr_exts;
	if (idx > 0 && idx < area->nr_mcgs) {
		struct mem_cgroup *mcg = get_mem_cgroup(idx);
		struct oem_mem_cgroup *oem_memcg;

		if (!mcg) {
			eswap_print(LEVEL_WARN, "mcg invalid idx = %d\n", idx);
			return NULL;
		}

		oem_memcg = get_oem_mem_cgroup(mcg);
		if (unlikely(!oem_memcg)) {
			eswap_print(LEVEL_ERR, "mcg data invalid idx = %d\n", idx);
			return NULL;
		}

		return (struct eswap_list_head *)(&oem_memcg->zram_lru);
	}

	eswap_print(LEVEL_DEBUG, "node invalid idx = %d\n", idx);
	return NULL;
}

static int init_obj_list_table(struct eswap_area *area)
{
	int i;

	if (!area) {
		eswap_print(LEVEL_ERR, "area is null\n");
		return -EINVAL;
	}

	area->lru = vzalloc(sizeof(struct eswap_list_head) * area->nr_objs);
	if (!area->lru) {
		eswap_print(LEVEL_ERR, "area->lru alloc failed\n");
		goto err_out;
	}
	area->rmap = vzalloc(sizeof(struct eswap_list_head) * area->nr_exts);
	if (!area->rmap) {
		eswap_print(LEVEL_ERR, "area->rmap alloc failed\n");
		goto err_out;
	}
	area->obj_table = alloc_table(get_obj_table_node, area, GFP_KERNEL);
	if (!area->obj_table) {
		eswap_print(LEVEL_ERR, "area->obj_table alloc failed\n");
		goto err_out;
	}
	for (i = 0; i < area->nr_objs; i++)
		eswap_list_init(obj_idx(area, i), area->obj_table);
	for (i = 0; i < area->nr_exts; i++)
		eswap_list_init(ext_idx(area, i), area->obj_table);

	eswap_print(LEVEL_DEBUG, "eswap obj list table init OK\n");
	return 0;
err_out:
	free_obj_list_table(area);
	eswap_print(LEVEL_WARN, "eswap obj list table init failed\n");

	return -ENOMEM;
}

static void free_ext_list_table(struct eswap_area *area)
{
	if (!area) {
		eswap_print(LEVEL_WARN, "area is null\n");
		return;
	}

	if (area->ext)
		vfree(area->ext);

	kfree(area->ext_table);
}

static struct eswap_list_head *get_ext_table_node(int idx, void *private)
{
	struct eswap_area *area = private;

	if (!area) {
		eswap_print(LEVEL_WARN, "area is null\n");
		return NULL;
	}

	if (idx < area->nr_objs) {
		eswap_print(LEVEL_DEBUG, "idx = %d invalid\n", idx);
		return NULL;
	}
	idx -= area->nr_objs;
	if (idx < area->nr_exts)
		return &area->ext[idx];
	idx -= area->nr_exts;
	if (idx > 0 && idx < area->nr_mcgs) {
		struct mem_cgroup *mcg = get_mem_cgroup(idx);
		struct oem_mem_cgroup *oem_memcg;

		if (!mcg) {
			eswap_print(LEVEL_WARN, "mcd invalid idx = %d\n", idx);
			return NULL;
		}
		oem_memcg = get_oem_mem_cgroup(mcg);
		if (unlikely(!oem_memcg)) {
			eswap_print(LEVEL_ERR, "mcg data invalid idx = %d\n", idx);
			return NULL;
		}
		return (struct eswap_list_head *)(&oem_memcg->ext_lru);
	}

	eswap_print(LEVEL_DEBUG, "node invalid idx = %d nr_objs = %d nr_exts = %d\n", idx, area->nr_objs, area->nr_exts);
	return NULL;
}

static int init_ext_list_table(struct eswap_area *area)
{
	int i;

	if (!area) {
		eswap_print(LEVEL_ERR, "area is null\n");
		return -EINVAL;
	}
	area->ext = vzalloc(sizeof(struct eswap_list_head) * area->nr_exts);
	if (!area->ext)
		goto err_out;
	area->ext_table = alloc_table(get_ext_table_node, area, GFP_KERNEL);
	if (!area->ext_table)
		goto err_out;
	for (i = 0; i < area->nr_exts; i++)
		eswap_list_init(ext_idx(area, i), area->ext_table);
	eswap_print(LEVEL_DEBUG, "eswap ext list table init OK\n");
	return 0;
err_out:
	free_ext_list_table(area);
	eswap_print(LEVEL_WARN, "eswap ext list table init failed\n");

	return -ENOMEM;
}

void free_eswap_area(struct eswap_area *area)
{
	if (!area) {
		eswap_print(LEVEL_WARN, "area is null\n");
		return;
	}

	vfree(area->bitmap);
	vfree(area->ext_stored_pages);
	free_obj_list_table(area);
	free_ext_list_table(area);
	vfree(area);
}

struct eswap_area *alloc_eswap_area(unsigned long ori_size,
					    unsigned long comp_size)
{
	struct eswap_area *area = vzalloc(sizeof(struct eswap_area));

	if (!area) {
		eswap_print(LEVEL_ERR, "area alloc failed\n");
		goto err_out;
	}
	if (comp_size & (EXTENT_SIZE - 1)) {
		eswap_print(LEVEL_ERR, "disksize = %ld align invalid (32K align needed)\n",
			 comp_size);
		goto err_out;
	}
	area->size = comp_size;
	area->nr_exts = comp_size >> EXTENT_SHIFT;
	area->nr_mcgs = MEM_CGROUP_ID_MAX;
	area->nr_objs = ori_size >> PAGE_SHIFT;
	area->bitmap = vzalloc(BITS_TO_LONGS(area->nr_exts) * sizeof(long));
	if (!area->bitmap) {
		eswap_print(LEVEL_ERR, "area->bitmap alloc failed\n");
		goto err_out;
	}
	area->ext_stored_pages = vzalloc(sizeof(atomic_t) * area->nr_exts);
	if (!area->ext_stored_pages) {
		eswap_print(LEVEL_ERR, "area->ext_stored_pages alloc failed\n");
		goto err_out;
	}
	if (init_obj_list_table(area)) {
		eswap_print(LEVEL_ERR, "init obj list table failed\n");
		goto err_out;
	}
	if (init_ext_list_table(area)) {
		eswap_print(LEVEL_ERR, "init ext list table failed\n");
		goto err_out;
	}
	eswap_print(LEVEL_DEBUG, "eswap_area init OK\n");
	return area;
err_out:
	free_eswap_area(area);
	eswap_print(LEVEL_ERR, "eswap_area init failed\n");

	return NULL;
}