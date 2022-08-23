// SPDX-License-Identifier: GPL-2.0-only

/*
 * Copyright (c) 2021, The Linux Foundation. All rights reserved.
 */

#define pr_fmt(fmt) "logbuf vendorhook: " fmt

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/atomic.h>
#include <linux/slab.h>
#include <soc/qcom/minidump.h>
#include <linux/proc_fs.h>
#include <linux/time.h>
#include <linux/ktime.h>

#include <linux/rtc.h>
#include <linux/timekeeping.h>

#include <trace/hooks/logbuf.h>
#include "../../../kernel/printk/printk_ringbuffer.h"

#define BOOT_LOG_SIZE    SZ_512K
#define LOG_NEWLINE          2

static char *boot_log_buf;
static unsigned int boot_log_buf_size;
static bool copy_early_boot_log = true;
static unsigned int off;

static size_t print_time(u64 ts, char *buf, size_t buf_sz)
{
	unsigned long rem_nsec = do_div(ts, 1000000000);

	return scnprintf(buf, buf_sz, "[%5lu.%06lu]",
				(unsigned long)ts, rem_nsec / 1000);
}

struct timezone sys_tz;
extern int nSuspendInProgress;
//static struct workqueue_struct *ASUSEvtlog_workQueue;
//static int g_hfileEvtlog = -MAX_ERRNO;
static int g_bEventlogEnable = 0;
#define ASUS_EVTLOG_STR_MAXLEN (256)
#define ASUS_EVTLOG_MAX_ITEM (32)
static struct mutex mA;

static char *g_Asus_Eventlog;
static int  g_Asus_Eventlog_size;

static int g_Asus_Eventlog_read = 0;
static int g_Asus_Eventlog_write = 0;

char evtlog_bootup_reason[100];
EXPORT_SYMBOL(evtlog_bootup_reason);
char evtlog_poweroff_reason[100];
EXPORT_SYMBOL(evtlog_poweroff_reason);

void ASUSEvtlog(const char *fmt, ...)
{
        va_list args;
        char *buffer;

        if (!in_interrupt() && !in_atomic() && !irqs_disabled()){
                mutex_lock(&mA);
		}
		
        buffer = &g_Asus_Eventlog[(g_Asus_Eventlog_write*ASUS_EVTLOG_STR_MAXLEN)];
        g_Asus_Eventlog_write++;
        g_Asus_Eventlog_write %= ASUS_EVTLOG_MAX_ITEM;

		if (g_bEventlogEnable == 0){
			snprintf(buffer, ASUS_EVTLOG_STR_MAXLEN,
					"\n\n---------------System Boot----%s---------\n"
					"[Shutdown] Reset Trigger: %s ###### \n"
					"###### Reset Type: %s ######\n",
					ASUS_SW_VER,
					evtlog_poweroff_reason,
					evtlog_bootup_reason
			);
			g_bEventlogEnable = 1;
			buffer = &g_Asus_Eventlog[(g_Asus_Eventlog_write*ASUS_EVTLOG_STR_MAXLEN)];
        	g_Asus_Eventlog_write++;
        	g_Asus_Eventlog_write %= ASUS_EVTLOG_MAX_ITEM;
		}

        if (!in_interrupt() && !in_atomic() && !irqs_disabled()){
                mutex_unlock(&mA);
        }

        memset(buffer, 0, ASUS_EVTLOG_STR_MAXLEN);

        if (buffer) {
			struct rtc_time tm;
			struct timespec64 ts;
			ktime_get_real_ts64(&ts);
			ts.tv_sec -= sys_tz.tz_minuteswest * 60;
			rtc_time64_to_tm(ts.tv_sec, &tm);
			ktime_get_raw_ts64(&ts);
			sprintf(buffer, "(%ld)%04d-%02d-%02d %02d:%02d:%02d :", ts.tv_sec, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			va_start(args, fmt);
			vscnprintf(buffer + strlen(buffer), ASUS_EVTLOG_STR_MAXLEN - strlen(buffer), fmt, args);
			va_end(args);
			printk("%s", buffer);
        } else {
                printk("ASUSEvtlog buffer cannot be allocated\n");
        }
}
EXPORT_SYMBOL(ASUSEvtlog);
static DECLARE_WAIT_QUEUE_HEAD(log_wait);


static ssize_t asusevtlog_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
		char messages[256];
        if (count > 256)
                count = 256;

        memset(messages, 0, sizeof(messages));
        if (copy_from_user(messages, buf, count))
                return -EFAULT;

        ASUSEvtlog("%s", messages);
		wake_up_interruptible(&log_wait);
        return count;
}


static ssize_t asusevtlog_read(struct file *file, char __user *buf,
                              size_t count, loff_t *ppos)
{
	int str_len = 0;
	char *pchar;
	int error = 0;
	error = wait_event_interruptible(log_wait,
						 g_Asus_Eventlog_read != g_Asus_Eventlog_write);

	if(!(g_Asus_Eventlog_read != g_Asus_Eventlog_write)) return 0;
	mutex_lock(&mA);
	str_len = strlen(&g_Asus_Eventlog[(g_Asus_Eventlog_read*ASUS_EVTLOG_STR_MAXLEN)]);
	pchar = &g_Asus_Eventlog[(g_Asus_Eventlog_read*ASUS_EVTLOG_STR_MAXLEN)];
	g_Asus_Eventlog_read++;
	g_Asus_Eventlog_read %= ASUS_EVTLOG_MAX_ITEM;
	mutex_unlock(&mA);

	if (pchar[str_len - 1] != '\n') {
		if (str_len + 1 >= ASUS_EVTLOG_STR_MAXLEN){
				str_len = ASUS_EVTLOG_STR_MAXLEN - 2;
		}
		pchar[str_len] = '\n';
		pchar[str_len + 1] = '\0';
	}
	if (copy_to_user(buf, pchar, str_len)) {
		if (!str_len)
			str_len = -EFAULT;
	}

        return str_len;
}


static const struct proc_ops proc_asusevtlog_operations = {
        .proc_write  = asusevtlog_write,
		.proc_read   = asusevtlog_read,
};



void asusevtlog_init(void){
	void *start; 
	int ret = 0;
	struct md_region md_entry;
	
	start = kzalloc((ASUS_EVTLOG_MAX_ITEM * ASUS_EVTLOG_STR_MAXLEN), GFP_KERNEL);
	if (!start) {
		ret = -ENOMEM;
		return ;
	}

	strlcpy(md_entry.name, "KEVENT_LOG", sizeof(md_entry.name));
	md_entry.virt_addr = (uintptr_t)start;
	md_entry.phys_addr = virt_to_phys(start);
	md_entry.size = (ASUS_EVTLOG_MAX_ITEM * ASUS_EVTLOG_STR_MAXLEN);
	ret = msm_minidump_add_region(&md_entry);
	if (ret < 0) {
		pr_err("Failed to add KEVENT_LOG entry in minidump table\n");
		kfree(start);
		return ;
	}

	mutex_init(&mA);

	g_Asus_Eventlog_size = (ASUS_EVTLOG_MAX_ITEM * ASUS_EVTLOG_STR_MAXLEN);
	g_Asus_Eventlog = (char *)start;


	proc_create("asusevtlog", S_IRWXUGO, NULL, &proc_asusevtlog_operations);  

}


#ifdef CONFIG_PRINTK_CALLER
#define PREFIX_MAX              48
static size_t print_caller(u32 id, char *buf, size_t buf_sz)
{
	char caller[12];

	snprintf(caller, sizeof(caller), "%c%u",
		id & 0x80000000 ? 'C' : 'T', id & ~0x80000000);
	return scnprintf(buf, buf_sz, "[%6s]", caller);
}
#else
#define PREFIX_MAX            32
#define print_caller(id, buf) 0
#endif

static size_t info_print_prefix(const struct printk_info *info, char *buf,
				size_t buf_sz)
{
	size_t len = 0;

	len = print_time(info->ts_nsec, buf + len, buf_sz);
	len += print_caller(info->caller_id, buf + len, buf_sz - len);
	buf[len++] = ' ';
	buf[len] = '\0';
	return len;
}

static size_t record_print_text(struct printk_info *pinfo, char *r_text, size_t buf_size)
{
	size_t text_len = pinfo->text_len;
	char prefix[PREFIX_MAX];
	size_t prefix_len;
	char *text = r_text;
	size_t line_len;
	size_t len = 0;
	char *next;

	prefix_len = info_print_prefix(pinfo, prefix, PREFIX_MAX);

	/*
	 * @text_len: bytes of unprocessed text
	 * @line_len: bytes of current line _without_ newline
	 * @text:     pointer to beginning of current line
	 * @len:      number of bytes prepared in r->text_buf
	 */
	for (;;) {
		next = memchr(text, '\n', text_len);
		if (next)
			line_len = next - text;
		else
			line_len = text_len;

		/*
		 * Truncate the text if there is not enough space to add the
		 * prefix and a trailing newline and a terminator.
		 */
		if ((len + prefix_len + text_len + 1 + 1) > buf_size)
			break;

		memmove(text + prefix_len, text, text_len);
		memcpy(text, prefix, prefix_len);

		/*
		 * Increment the prepared length to include the text and
		 * prefix that were just moved+copied. Also increment for the
		 * newline at the end of this line. If this is the last line,
		 * there is no newline, but it will be added immediately below.
		 */
		len += prefix_len + line_len + 1;
		if (text_len == line_len) {
			 /*
			  * This is the last line. Add the trailing newline
			  * removed in vprintk_store().
			  */
			text[prefix_len + line_len] = '\n';
			break;
		}

		/*
		 * Advance beyond the added prefix and the related line with
		 * its newline.
		 */

		text += prefix_len + line_len + 1;

		/*
		 * The remaining text has only decreased by the line with its
		 * newline.
		 *
		 * Note that @text_len can become zero. It happens when @text
		 * ended with a newline (either due to truncation or the
		 * original string ending with "\n\n"). The loop is correctly
		 * repeated and (if not truncated) an empty line with a prefix
		 * will be prepared.
		 */

		text_len -= line_len + 1;
	}

	/*
	 * If a buffer was provided, it will be terminated. Space for the
	 * string terminator is guaranteed to be available. The terminator is
	 * not counted in the return value.
	 */

	if (buf_size > 0)
		r_text[len] = 0;

	return len;
}

static void register_log_minidump(struct printk_ringbuffer *prb)
{
	struct prb_desc_ring descring = prb->desc_ring;
	struct prb_data_ring textdata_ring = prb->text_data_ring;
	struct prb_desc *descaddr = descring.descs;
	struct printk_info *p_infos = descring.infos;
	struct md_region md_entry;
	int ret;

	strlcpy(md_entry.name, "KLOGBUF", sizeof(md_entry.name));
	md_entry.virt_addr = (uintptr_t)textdata_ring.data;
	md_entry.phys_addr = virt_to_phys(textdata_ring.data);
	md_entry.size = _DATA_SIZE(textdata_ring.size_bits);
	ret = msm_minidump_add_region(&md_entry);
	if (ret < 0)
		pr_err("Failed to add log_text entry in minidump table\n");

	strlcpy(md_entry.name, "LOG_DESC", sizeof(md_entry.name));
	md_entry.virt_addr = (uintptr_t)descaddr;
	md_entry.phys_addr = virt_to_phys(descaddr);
	md_entry.size = sizeof(struct prb_desc) * _DESCS_COUNT(descring.count_bits);
	ret = msm_minidump_add_region(&md_entry);
	if (ret < 0)
		pr_err("Failed to add log_desc entry in minidump table\n");

	strlcpy(md_entry.name, "LOG_INFO", sizeof(md_entry.name));
	md_entry.virt_addr = (uintptr_t)p_infos;
	md_entry.phys_addr = virt_to_phys(p_infos);
	md_entry.size = sizeof(struct printk_info) * _DESCS_COUNT(descring.count_bits);
	ret = msm_minidump_add_region(&md_entry);
	if (ret < 0)
		pr_err("Failed to add log_info entry in minidump table\n");
}

static void copy_boot_log_pr_cont(void *unused, struct printk_record *r, size_t text_len)
{
	if (copy_early_boot_log)
		return;

	if (!r->info->text_len || !off ||
		((off + r->info->text_len + 1 + 1) > boot_log_buf_size))
		return;

	if (boot_log_buf[off - 1] == '\n')
		off = off - 1;

	memcpy(&boot_log_buf[off], &r->text_buf[r->info->text_len - text_len], text_len);
	off += text_len;
	if (r->info->flags & LOG_NEWLINE) {
		boot_log_buf[off] = '\n';
		boot_log_buf[off + 1] = 0;
		off += 1;
	}
}

static void copy_boot_log(void *unused, struct printk_ringbuffer *prb,
					struct printk_record *r)
{
	struct prb_desc_ring descring = prb->desc_ring;
	struct prb_data_ring textdata_ring = prb->text_data_ring;
	struct prb_desc *descaddr = descring.descs;
	struct printk_info *p_infos = descring.infos;
	atomic_long_t headid, tailid;
	unsigned long did, ind, sv;
	unsigned int textdata_size = _DATA_SIZE(textdata_ring.size_bits);
	unsigned long begin, end;
	enum desc_state state;
	size_t rem_buf_sz;

	tailid = descring.tail_id;
	headid = descring.head_id;

	if (!copy_early_boot_log) {
		if (!r->info->text_len)
			return;

		/*
		 * Check whether remaining buffer has enough space
		 * for record meta data size + newline + terminator
		 * if not, let's reject the record.
		 */
		if ((off + r->info->text_len + PREFIX_MAX + 1 + 1) > boot_log_buf_size)
			return;

		rem_buf_sz = boot_log_buf_size - off;
		if (!rem_buf_sz)
			return;

		memcpy(&boot_log_buf[off], &r->text_buf[0], r->info->text_len);
		off += record_print_text(r->info, &boot_log_buf[off], rem_buf_sz);
		return;
	}

	copy_early_boot_log = false;
	register_log_minidump(prb);
	did = atomic_long_read(&tailid);
	while (true) {
		ind = did % _DESCS_COUNT(descring.count_bits);
		sv = atomic_long_read(&descaddr[ind].state_var);
		state = DESC_STATE(sv);
		/* skip non-committed record */
		if ((state != desc_committed) && (state != desc_finalized)) {
			if (did == atomic_long_read(&headid))
				break;

			did = DESC_ID(did + 1);
			continue;
		}

		begin = (descaddr[ind].text_blk_lpos.begin) % textdata_size;
		end = (descaddr[ind].text_blk_lpos.next) % textdata_size;
		if ((begin & 1) != 1) {
			unsigned long text_start;
			u16 textlen;

			if (begin > end)
				begin = 0;

			text_start = begin + sizeof(unsigned long);
			textlen = p_infos[ind].text_len;
			if (end - text_start < textlen)
				textlen = end - text_start;

			/*
			 * Check whether remaining buffer has enough space
			 * for record meta data size + newline + terminator
			 * if not, let's reject the record.
			 */
			if ((off + textlen + PREFIX_MAX + 1 + 1) > boot_log_buf_size)
				break;

			rem_buf_sz = boot_log_buf_size - off;

			memcpy(&boot_log_buf[off], &textdata_ring.data[text_start],
					textlen);
			off += record_print_text(&p_infos[ind],
					&boot_log_buf[off], rem_buf_sz);
		}

		if (did == atomic_long_read(&headid))
			break;

		did = DESC_ID(did + 1);
	}
}

static int boot_log_init(void)
{
	void *start;
	int ret = 0;
	unsigned int size = BOOT_LOG_SIZE;
	struct md_region md_entry;

	start = kzalloc(size, GFP_KERNEL);
	if (!start) {
		ret = -ENOMEM;
		goto out;
	}

	strlcpy(md_entry.name, "KBOOT_LOG", sizeof(md_entry.name));
	md_entry.virt_addr = (uintptr_t)start;
	md_entry.phys_addr = virt_to_phys(start);
	md_entry.size = size;
	ret = msm_minidump_add_region(&md_entry);
	if (ret < 0) {
		pr_err("Failed to add boot_log entry in minidump table\n");
		kfree(start);
		goto out;
	}

	boot_log_buf_size = size;
	boot_log_buf = (char *)start;

	/* Ensure boot_log_buf and boot_log_buf initialization
	 * is visible to other CPU's
	 */
	smp_mb();

out:
	return ret;
}

static void release_boot_log_buf(void)
{
	if (!boot_log_buf)
		return;

	kfree(boot_log_buf);
}
static int logbuf_vendor_hooks_driver_probe(struct platform_device *pdev)
{
	int ret;

	ret = boot_log_init();

	if (ret < 0)
		return ret;
	

	ret = register_trace_android_vh_logbuf(copy_boot_log, NULL);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register android_vh_logbuf hook\n");
		kfree(boot_log_buf);
		return ret;
	}


	ret = register_trace_android_vh_logbuf_pr_cont(copy_boot_log_pr_cont, NULL);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register android_vh_logbuf_pr_cont hook\n");
		unregister_trace_android_vh_logbuf(copy_boot_log, NULL);
		kfree(boot_log_buf);
	}

	asusevtlog_init();

	


	return ret;
}

static int logbuf_vendor_hooks_driver_remove(struct platform_device *pdev)
{
	unregister_trace_android_vh_logbuf_pr_cont(copy_boot_log_pr_cont, NULL);
	unregister_trace_android_vh_logbuf(copy_boot_log, NULL);
	release_boot_log_buf();
	return 0;
}

static const struct of_device_id logbuf_vendor_hooks_of_match[] = {
	{ .compatible = "qcom,logbuf-vendor-hooks" },
	{ }
};
MODULE_DEVICE_TABLE(of, logbuf_vendor_hooks_of_match);

static struct platform_driver logbuf_vendor_hooks_driver = {
	.driver = {
		.name = "qcom-logbuf-vendor-hooks",
		.of_match_table = logbuf_vendor_hooks_of_match,
	},
	.probe = logbuf_vendor_hooks_driver_probe,
	.remove = logbuf_vendor_hooks_driver_remove,
};

static int __init qcom_logbuf_vendor_hook_driver_init(void)
{
	return platform_driver_register(&logbuf_vendor_hooks_driver);
}
#if IS_MODULE(CONFIG_QCOM_LOGBUF_VENDOR_HOOKS)
module_init(qcom_logbuf_vendor_hook_driver_init);
#else
pure_initcall(qcom_logbuf_vendor_hook_driver_init);
#endif


static void __exit qcom_logbuf_vendor_hook_driver_exit(void)
{
	return platform_driver_unregister(&logbuf_vendor_hooks_driver);
}
module_exit(qcom_logbuf_vendor_hook_driver_exit);

MODULE_DESCRIPTION("QCOM Logbuf Vendor Hooks Driver");
MODULE_LICENSE("GPL v2");
