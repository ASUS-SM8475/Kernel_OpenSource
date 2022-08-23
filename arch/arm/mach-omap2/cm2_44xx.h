/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * OMAP44xx CM2 instance offset macros
 *
 * Copyright (C) 2009-2011 Texas Instruments, Inc.
 * Copyright (C) 2009-2010 Nokia Corporation
 *
 * Paul Walmsley (paul@pwsan.com)
 * Rajendra Nayak (rnayak@ti.com)
 * Benoit Cousson (b-cousson@ti.com)
 *
 * This file is automatically generated from the OMAP hardware databases.
 * We respectfully ask that any modifications to this file be coordinated
 * with the public linux-omap@vger.kernel.org mailing list and the
 * authors above to ensure that the autogeneration scripts are kept
 * up-to-date with the file contents.
 *
 * XXX This file needs to be updated to align on one of "OMAP4", "OMAP44XX",
 *     or "OMAP4430".
 */

#ifndef __ARCH_ARM_MACH_OMAP2_CM2_44XX_H
#define __ARCH_ARM_MACH_OMAP2_CM2_44XX_H

/* CM2 base address */
#define OMAP4430_CM2_BASE		0x4a008000

#define OMAP44XX_CM2_REGADDR(inst, reg)				\
	OMAP2_L4_IO_ADDRESS(OMAP4430_CM2_BASE + (inst) + (reg))

/* CM2 instances */
#define OMAP4430_CM2_OCP_SOCKET_INST	0x0000
#define OMAP4430_CM2_CKGEN_INST		0x0100
#define OMAP4430_CM2_ALWAYS_ON_INST	0x0600
#define OMAP4430_CM2_CORE_INST		0x0700
#define OMAP4430_CM2_IVAHD_INST		0x0f00
#define OMAP4430_CM2_CAM_INST		0x1000
#define OMAP4430_CM2_DSS_INST		0x1100
#define OMAP4430_CM2_GFX_INST		0x1200
#define OMAP4430_CM2_L3INIT_INST	0x1300
#define OMAP4430_CM2_L4PER_INST		0x1400
#define OMAP4430_CM2_CEFUSE_INST	0x1600
#define OMAP4430_CM2_RESTORE_INST	0x1e00
#define OMAP4430_CM2_INSTR_INST		0x1f00

/* CM2 clockdomain register offsets (from instance start) */
#define OMAP4430_CM2_ALWAYS_ON_ALWON_CDOFFS	0x0000
#define OMAP4430_CM2_CORE_L3_1_CDOFFS		0x0000
#define OMAP4430_CM2_CORE_L3_2_CDOFFS		0x0100
#define OMAP4430_CM2_CORE_DUCATI_CDOFFS		0x0200
#define OMAP4430_CM2_CORE_SDMA_CDOFFS		0x0300
#define OMAP4430_CM2_CORE_MEMIF_CDOFFS		0x0400
#define OMAP4430_CM2_CORE_D2D_CDOFFS		0x0500
#define OMAP4430_CM2_CORE_L4CFG_CDOFFS		0x0600
#define OMAP4430_CM2_CORE_L3INSTR_CDOFFS	0x0700
#define OMAP4430_CM2_IVAHD_IVAHD_CDOFFS		0x0000
#define OMAP4430_CM2_CAM_CAM_CDOFFS		0x0000
#define OMAP4430_CM2_DSS_DSS_CDOFFS		0x0000
#define OMAP4430_CM2_GFX_GFX_CDOFFS		0x0000
#define OMAP4430_CM2_L3INIT_L3INIT_CDOFFS	0x0000
#define OMAP4430_CM2_L4PER_L4PER_CDOFFS		0x0000
#define OMAP4430_CM2_L4PER_L4SEC_CDOFFS		0x0180
#define OMAP4430_CM2_CEFUSE_CEFUSE_CDOFFS	0x0000

/* CM2 */

/* CM2.OCP_SOCKET_CM2 register offsets */
#define OMAP4_REVISION_CM2_OFFSET			0x0000
#define OMAP4430_REVISION_CM2				OMAP44XX_CM2_REGADDR(OMAP4430_CM2_OCP_SOCKET_INST, 0x0000)
#define OMAP4_CM_CM2_PROFILING_CLKCTRL_OFFSET		0x0040
#define OMAP4430_CM_CM2_PROFILING_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_OCP_SOCKET_INST, 0x0040)

/* CM2.CKGEN_CM2 register offsets */
#define OMAP4_CM_CLKSEL_DUCATI_ISS_ROOT_OFFSET		0x0000
#define OMAP4430_CM_CLKSEL_DUCATI_ISS_ROOT		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0000)
#define OMAP4_CM_CLKSEL_USB_60MHZ_OFFSET		0x0004
#define OMAP4430_CM_CLKSEL_USB_60MHZ			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0004)
#define OMAP4_CM_SCALE_FCLK_OFFSET			0x0008
#define OMAP4430_CM_SCALE_FCLK				OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0008)
#define OMAP4_CM_CORE_DVFS_PERF1_OFFSET			0x0010
#define OMAP4430_CM_CORE_DVFS_PERF1			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0010)
#define OMAP4_CM_CORE_DVFS_PERF2_OFFSET			0x0014
#define OMAP4430_CM_CORE_DVFS_PERF2			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0014)
#define OMAP4_CM_CORE_DVFS_PERF3_OFFSET			0x0018
#define OMAP4430_CM_CORE_DVFS_PERF3			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0018)
#define OMAP4_CM_CORE_DVFS_PERF4_OFFSET			0x001c
#define OMAP4430_CM_CORE_DVFS_PERF4			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x001c)
#define OMAP4_CM_CORE_DVFS_CURRENT_OFFSET		0x0024
#define OMAP4430_CM_CORE_DVFS_CURRENT			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0024)
#define OMAP4_CM_IVA_DVFS_PERF_TESLA_OFFSET		0x0028
#define OMAP4430_CM_IVA_DVFS_PERF_TESLA			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0028)
#define OMAP4_CM_IVA_DVFS_PERF_IVAHD_OFFSET		0x002c
#define OMAP4430_CM_IVA_DVFS_PERF_IVAHD			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x002c)
#define OMAP4_CM_IVA_DVFS_PERF_ABE_OFFSET		0x0030
#define OMAP4430_CM_IVA_DVFS_PERF_ABE			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0030)
#define OMAP4_CM_IVA_DVFS_CURRENT_OFFSET		0x0038
#define OMAP4430_CM_IVA_DVFS_CURRENT			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0038)
#define OMAP4_CM_CLKMODE_DPLL_PER_OFFSET		0x0040
#define OMAP4430_CM_CLKMODE_DPLL_PER			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0040)
#define OMAP4_CM_IDLEST_DPLL_PER_OFFSET			0x0044
#define OMAP4430_CM_IDLEST_DPLL_PER			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0044)
#define OMAP4_CM_AUTOIDLE_DPLL_PER_OFFSET		0x0048
#define OMAP4430_CM_AUTOIDLE_DPLL_PER			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0048)
#define OMAP4_CM_CLKSEL_DPLL_PER_OFFSET			0x004c
#define OMAP4430_CM_CLKSEL_DPLL_PER			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x004c)
#define OMAP4_CM_DIV_M2_DPLL_PER_OFFSET			0x0050
#define OMAP4430_CM_DIV_M2_DPLL_PER			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0050)
#define OMAP4_CM_DIV_M3_DPLL_PER_OFFSET			0x0054
#define OMAP4430_CM_DIV_M3_DPLL_PER			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0054)
#define OMAP4_CM_DIV_M4_DPLL_PER_OFFSET			0x0058
#define OMAP4430_CM_DIV_M4_DPLL_PER			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0058)
#define OMAP4_CM_DIV_M5_DPLL_PER_OFFSET			0x005c
#define OMAP4430_CM_DIV_M5_DPLL_PER			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x005c)
#define OMAP4_CM_DIV_M6_DPLL_PER_OFFSET			0x0060
#define OMAP4430_CM_DIV_M6_DPLL_PER			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0060)
#define OMAP4_CM_DIV_M7_DPLL_PER_OFFSET			0x0064
#define OMAP4430_CM_DIV_M7_DPLL_PER			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0064)
#define OMAP4_CM_SSC_DELTAMSTEP_DPLL_PER_OFFSET		0x0068
#define OMAP4430_CM_SSC_DELTAMSTEP_DPLL_PER		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0068)
#define OMAP4_CM_SSC_MODFREQDIV_DPLL_PER_OFFSET		0x006c
#define OMAP4430_CM_SSC_MODFREQDIV_DPLL_PER		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x006c)
#define OMAP4_CM_CLKMODE_DPLL_USB_OFFSET		0x0080
#define OMAP4430_CM_CLKMODE_DPLL_USB			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0080)
#define OMAP4_CM_IDLEST_DPLL_USB_OFFSET			0x0084
#define OMAP4430_CM_IDLEST_DPLL_USB			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0084)
#define OMAP4_CM_AUTOIDLE_DPLL_USB_OFFSET		0x0088
#define OMAP4430_CM_AUTOIDLE_DPLL_USB			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0088)
#define OMAP4_CM_CLKSEL_DPLL_USB_OFFSET			0x008c
#define OMAP4430_CM_CLKSEL_DPLL_USB			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x008c)
#define OMAP4_CM_DIV_M2_DPLL_USB_OFFSET			0x0090
#define OMAP4430_CM_DIV_M2_DPLL_USB			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x0090)
#define OMAP4_CM_SSC_DELTAMSTEP_DPLL_USB_OFFSET		0x00a8
#define OMAP4430_CM_SSC_DELTAMSTEP_DPLL_USB		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x00a8)
#define OMAP4_CM_SSC_MODFREQDIV_DPLL_USB_OFFSET		0x00ac
#define OMAP4430_CM_SSC_MODFREQDIV_DPLL_USB		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x00ac)
#define OMAP4_CM_CLKDCOLDO_DPLL_USB_OFFSET		0x00b4
#define OMAP4430_CM_CLKDCOLDO_DPLL_USB			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x00b4)
#define OMAP4_CM_CLKMODE_DPLL_UNIPRO_OFFSET		0x00c0
#define OMAP4430_CM_CLKMODE_DPLL_UNIPRO			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x00c0)
#define OMAP4_CM_IDLEST_DPLL_UNIPRO_OFFSET		0x00c4
#define OMAP4430_CM_IDLEST_DPLL_UNIPRO			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x00c4)
#define OMAP4_CM_AUTOIDLE_DPLL_UNIPRO_OFFSET		0x00c8
#define OMAP4430_CM_AUTOIDLE_DPLL_UNIPRO		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x00c8)
#define OMAP4_CM_CLKSEL_DPLL_UNIPRO_OFFSET		0x00cc
#define OMAP4430_CM_CLKSEL_DPLL_UNIPRO			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x00cc)
#define OMAP4_CM_DIV_M2_DPLL_UNIPRO_OFFSET		0x00d0
#define OMAP4430_CM_DIV_M2_DPLL_UNIPRO			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x00d0)
#define OMAP4_CM_SSC_DELTAMSTEP_DPLL_UNIPRO_OFFSET	0x00e8
#define OMAP4430_CM_SSC_DELTAMSTEP_DPLL_UNIPRO		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x00e8)
#define OMAP4_CM_SSC_MODFREQDIV_DPLL_UNIPRO_OFFSET	0x00ec
#define OMAP4430_CM_SSC_MODFREQDIV_DPLL_UNIPRO		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CKGEN_INST, 0x00ec)

/* CM2.ALWAYS_ON_CM2 register offsets */
#define OMAP4_CM_ALWON_CLKSTCTRL_OFFSET			0x0000
#define OMAP4430_CM_ALWON_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_ALWAYS_ON_INST, 0x0000)
#define OMAP4_CM_ALWON_MDMINTC_CLKCTRL_OFFSET		0x0020
#define OMAP4430_CM_ALWON_MDMINTC_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_ALWAYS_ON_INST, 0x0020)
#define OMAP4_CM_ALWON_SR_MPU_CLKCTRL_OFFSET		0x0028
#define OMAP4430_CM_ALWON_SR_MPU_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_ALWAYS_ON_INST, 0x0028)
#define OMAP4_CM_ALWON_SR_IVA_CLKCTRL_OFFSET		0x0030
#define OMAP4430_CM_ALWON_SR_IVA_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_ALWAYS_ON_INST, 0x0030)
#define OMAP4_CM_ALWON_SR_CORE_CLKCTRL_OFFSET		0x0038
#define OMAP4430_CM_ALWON_SR_CORE_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_ALWAYS_ON_INST, 0x0038)
#define OMAP4_CM_ALWON_USBPHY_CLKCTRL_OFFSET		0x0040
#define OMAP4430_CM_ALWON_USBPHY_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_ALWAYS_ON_INST, 0x0040)

/* CM2.CORE_CM2 register offsets */
#define OMAP4_CM_L3_1_CLKSTCTRL_OFFSET			0x0000
#define OMAP4430_CM_L3_1_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0000)
#define OMAP4_CM_L3_1_DYNAMICDEP_OFFSET			0x0008
#define OMAP4430_CM_L3_1_DYNAMICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0008)
#define OMAP4_CM_L3_1_L3_1_CLKCTRL_OFFSET		0x0020
#define OMAP4430_CM_L3_1_L3_1_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0020)
#define OMAP4_CM_L3_2_CLKSTCTRL_OFFSET			0x0100
#define OMAP4430_CM_L3_2_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0100)
#define OMAP4_CM_L3_2_DYNAMICDEP_OFFSET			0x0108
#define OMAP4430_CM_L3_2_DYNAMICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0108)
#define OMAP4_CM_L3_2_L3_2_CLKCTRL_OFFSET		0x0120
#define OMAP4430_CM_L3_2_L3_2_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0120)
#define OMAP4_CM_L3_2_GPMC_CLKCTRL_OFFSET		0x0128
#define OMAP4430_CM_L3_2_GPMC_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0128)
#define OMAP4_CM_L3_2_OCMC_RAM_CLKCTRL_OFFSET		0x0130
#define OMAP4430_CM_L3_2_OCMC_RAM_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0130)
#define OMAP4_CM_DUCATI_CLKSTCTRL_OFFSET		0x0200
#define OMAP4430_CM_DUCATI_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0200)
#define OMAP4_CM_DUCATI_STATICDEP_OFFSET		0x0204
#define OMAP4430_CM_DUCATI_STATICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0204)
#define OMAP4_CM_DUCATI_DYNAMICDEP_OFFSET		0x0208
#define OMAP4430_CM_DUCATI_DYNAMICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0208)
#define OMAP4_CM_DUCATI_DUCATI_CLKCTRL_OFFSET		0x0220
#define OMAP4430_CM_DUCATI_DUCATI_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0220)
#define OMAP4_CM_SDMA_CLKSTCTRL_OFFSET			0x0300
#define OMAP4430_CM_SDMA_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0300)
#define OMAP4_CM_SDMA_STATICDEP_OFFSET			0x0304
#define OMAP4430_CM_SDMA_STATICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0304)
#define OMAP4_CM_SDMA_DYNAMICDEP_OFFSET			0x0308
#define OMAP4430_CM_SDMA_DYNAMICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0308)
#define OMAP4_CM_SDMA_SDMA_CLKCTRL_OFFSET		0x0320
#define OMAP4430_CM_SDMA_SDMA_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0320)
#define OMAP4_CM_MEMIF_CLKSTCTRL_OFFSET			0x0400
#define OMAP4430_CM_MEMIF_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0400)
#define OMAP4_CM_MEMIF_DMM_CLKCTRL_OFFSET		0x0420
#define OMAP4430_CM_MEMIF_DMM_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0420)
#define OMAP4_CM_MEMIF_EMIF_FW_CLKCTRL_OFFSET		0x0428
#define OMAP4430_CM_MEMIF_EMIF_FW_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0428)
#define OMAP4_CM_MEMIF_EMIF_1_CLKCTRL_OFFSET		0x0430
#define OMAP4430_CM_MEMIF_EMIF_1_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0430)
#define OMAP4_CM_MEMIF_EMIF_2_CLKCTRL_OFFSET		0x0438
#define OMAP4430_CM_MEMIF_EMIF_2_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0438)
#define OMAP4_CM_MEMIF_DLL_CLKCTRL_OFFSET		0x0440
#define OMAP4430_CM_MEMIF_DLL_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0440)
#define OMAP4_CM_MEMIF_EMIF_H1_CLKCTRL_OFFSET		0x0450
#define OMAP4430_CM_MEMIF_EMIF_H1_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0450)
#define OMAP4_CM_MEMIF_EMIF_H2_CLKCTRL_OFFSET		0x0458
#define OMAP4430_CM_MEMIF_EMIF_H2_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0458)
#define OMAP4_CM_MEMIF_DLL_H_CLKCTRL_OFFSET		0x0460
#define OMAP4430_CM_MEMIF_DLL_H_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0460)
#define OMAP4_CM_D2D_CLKSTCTRL_OFFSET			0x0500
#define OMAP4430_CM_D2D_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0500)
#define OMAP4_CM_D2D_STATICDEP_OFFSET			0x0504
#define OMAP4430_CM_D2D_STATICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0504)
#define OMAP4_CM_D2D_DYNAMICDEP_OFFSET			0x0508
#define OMAP4430_CM_D2D_DYNAMICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0508)
#define OMAP4_CM_D2D_SAD2D_CLKCTRL_OFFSET		0x0520
#define OMAP4430_CM_D2D_SAD2D_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0520)
#define OMAP4_CM_D2D_MODEM_ICR_CLKCTRL_OFFSET		0x0528
#define OMAP4430_CM_D2D_MODEM_ICR_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0528)
#define OMAP4_CM_D2D_SAD2D_FW_CLKCTRL_OFFSET		0x0530
#define OMAP4430_CM_D2D_SAD2D_FW_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0530)
#define OMAP4_CM_L4CFG_CLKSTCTRL_OFFSET			0x0600
#define OMAP4430_CM_L4CFG_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0600)
#define OMAP4_CM_L4CFG_DYNAMICDEP_OFFSET		0x0608
#define OMAP4430_CM_L4CFG_DYNAMICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0608)
#define OMAP4_CM_L4CFG_L4_CFG_CLKCTRL_OFFSET		0x0620
#define OMAP4430_CM_L4CFG_L4_CFG_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0620)
#define OMAP4_CM_L4CFG_HW_SEM_CLKCTRL_OFFSET		0x0628
#define OMAP4430_CM_L4CFG_HW_SEM_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0628)
#define OMAP4_CM_L4CFG_MAILBOX_CLKCTRL_OFFSET		0x0630
#define OMAP4430_CM_L4CFG_MAILBOX_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0630)
#define OMAP4_CM_L4CFG_SAR_ROM_CLKCTRL_OFFSET		0x0638
#define OMAP4430_CM_L4CFG_SAR_ROM_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0638)
#define OMAP4_CM_L3INSTR_CLKSTCTRL_OFFSET		0x0700
#define OMAP4430_CM_L3INSTR_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0700)
#define OMAP4_CM_L3INSTR_L3_3_CLKCTRL_OFFSET		0x0720
#define OMAP4430_CM_L3INSTR_L3_3_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0720)
#define OMAP4_CM_L3INSTR_L3_INSTR_CLKCTRL_OFFSET	0x0728
#define OMAP4430_CM_L3INSTR_L3_INSTR_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0728)
#define OMAP4_CM_L3INSTR_OCP_WP1_CLKCTRL_OFFSET		0x0740
#define OMAP4430_CM_L3INSTR_OCP_WP1_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CORE_INST, 0x0740)

/* CM2.IVAHD_CM2 register offsets */
#define OMAP4_CM_IVAHD_CLKSTCTRL_OFFSET			0x0000
#define OMAP4430_CM_IVAHD_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_IVAHD_INST, 0x0000)
#define OMAP4_CM_IVAHD_STATICDEP_OFFSET			0x0004
#define OMAP4430_CM_IVAHD_STATICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_IVAHD_INST, 0x0004)
#define OMAP4_CM_IVAHD_DYNAMICDEP_OFFSET		0x0008
#define OMAP4430_CM_IVAHD_DYNAMICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_IVAHD_INST, 0x0008)
#define OMAP4_CM_IVAHD_IVAHD_CLKCTRL_OFFSET		0x0020
#define OMAP4430_CM_IVAHD_IVAHD_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_IVAHD_INST, 0x0020)
#define OMAP4_CM_IVAHD_SL2_CLKCTRL_OFFSET		0x0028
#define OMAP4430_CM_IVAHD_SL2_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_IVAHD_INST, 0x0028)

/* CM2.CAM_CM2 register offsets */
#define OMAP4_CM_CAM_CLKSTCTRL_OFFSET			0x0000
#define OMAP4430_CM_CAM_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CAM_INST, 0x0000)
#define OMAP4_CM_CAM_STATICDEP_OFFSET			0x0004
#define OMAP4430_CM_CAM_STATICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CAM_INST, 0x0004)
#define OMAP4_CM_CAM_DYNAMICDEP_OFFSET			0x0008
#define OMAP4430_CM_CAM_DYNAMICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CAM_INST, 0x0008)
#define OMAP4_CM_CAM_ISS_CLKCTRL_OFFSET			0x0020
#define OMAP4430_CM_CAM_ISS_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CAM_INST, 0x0020)
#define OMAP4_CM_CAM_FDIF_CLKCTRL_OFFSET		0x0028
#define OMAP4430_CM_CAM_FDIF_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CAM_INST, 0x0028)

/* CM2.DSS_CM2 register offsets */
#define OMAP4_CM_DSS_CLKSTCTRL_OFFSET			0x0000
#define OMAP4430_CM_DSS_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_DSS_INST, 0x0000)
#define OMAP4_CM_DSS_STATICDEP_OFFSET			0x0004
#define OMAP4430_CM_DSS_STATICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_DSS_INST, 0x0004)
#define OMAP4_CM_DSS_DYNAMICDEP_OFFSET			0x0008
#define OMAP4430_CM_DSS_DYNAMICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_DSS_INST, 0x0008)
#define OMAP4_CM_DSS_DSS_CLKCTRL_OFFSET			0x0020
#define OMAP4430_CM_DSS_DSS_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_DSS_INST, 0x0020)
#define OMAP4_CM_DSS_DEISS_CLKCTRL_OFFSET		0x0028
#define OMAP4430_CM_DSS_DEISS_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_DSS_INST, 0x0028)

/* CM2.GFX_CM2 register offsets */
#define OMAP4_CM_GFX_CLKSTCTRL_OFFSET			0x0000
#define OMAP4430_CM_GFX_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_GFX_INST, 0x0000)
#define OMAP4_CM_GFX_STATICDEP_OFFSET			0x0004
#define OMAP4430_CM_GFX_STATICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_GFX_INST, 0x0004)
#define OMAP4_CM_GFX_DYNAMICDEP_OFFSET			0x0008
#define OMAP4430_CM_GFX_DYNAMICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_GFX_INST, 0x0008)
#define OMAP4_CM_GFX_GFX_CLKCTRL_OFFSET			0x0020
#define OMAP4430_CM_GFX_GFX_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_GFX_INST, 0x0020)

/* CM2.L3INIT_CM2 register offsets */
#define OMAP4_CM_L3INIT_CLKSTCTRL_OFFSET		0x0000
#define OMAP4430_CM_L3INIT_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x0000)
#define OMAP4_CM_L3INIT_STATICDEP_OFFSET		0x0004
#define OMAP4430_CM_L3INIT_STATICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x0004)
#define OMAP4_CM_L3INIT_DYNAMICDEP_OFFSET		0x0008
#define OMAP4430_CM_L3INIT_DYNAMICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x0008)
#define OMAP4_CM_L3INIT_MMC1_CLKCTRL_OFFSET		0x0028
#define OMAP4430_CM_L3INIT_MMC1_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x0028)
#define OMAP4_CM_L3INIT_MMC2_CLKCTRL_OFFSET		0x0030
#define OMAP4430_CM_L3INIT_MMC2_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x0030)
#define OMAP4_CM_L3INIT_HSI_CLKCTRL_OFFSET		0x0038
#define OMAP4430_CM_L3INIT_HSI_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x0038)
#define OMAP4_CM_L3INIT_UNIPRO1_CLKCTRL_OFFSET		0x0040
#define OMAP4430_CM_L3INIT_UNIPRO1_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x0040)
#define OMAP4_CM_L3INIT_USB_HOST_CLKCTRL_OFFSET		0x0058
#define OMAP4430_CM_L3INIT_USB_HOST_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x0058)
#define OMAP4_CM_L3INIT_USB_OTG_CLKCTRL_OFFSET		0x0060
#define OMAP4430_CM_L3INIT_USB_OTG_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x0060)
#define OMAP4_CM_L3INIT_USB_TLL_CLKCTRL_OFFSET		0x0068
#define OMAP4430_CM_L3INIT_USB_TLL_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x0068)
#define OMAP4_CM_L3INIT_P1500_CLKCTRL_OFFSET		0x0078
#define OMAP4430_CM_L3INIT_P1500_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x0078)
#define OMAP4_CM_L3INIT_EMAC_CLKCTRL_OFFSET		0x0080
#define OMAP4430_CM_L3INIT_EMAC_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x0080)
#define OMAP4_CM_L3INIT_SATA_CLKCTRL_OFFSET		0x0088
#define OMAP4430_CM_L3INIT_SATA_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x0088)
#define OMAP4_CM_L3INIT_TPPSS_CLKCTRL_OFFSET		0x0090
#define OMAP4430_CM_L3INIT_TPPSS_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x0090)
#define OMAP4_CM_L3INIT_PCIESS_CLKCTRL_OFFSET		0x0098
#define OMAP4430_CM_L3INIT_PCIESS_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x0098)
#define OMAP4_CM_L3INIT_CCPTX_CLKCTRL_OFFSET		0x00a8
#define OMAP4430_CM_L3INIT_CCPTX_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x00a8)
#define OMAP4_CM_L3INIT_XHPI_CLKCTRL_OFFSET		0x00c0
#define OMAP4430_CM_L3INIT_XHPI_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x00c0)
#define OMAP4_CM_L3INIT_MMC6_CLKCTRL_OFFSET		0x00c8
#define OMAP4430_CM_L3INIT_MMC6_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x00c8)
#define OMAP4_CM_L3INIT_USB_HOST_FS_CLKCTRL_OFFSET	0x00d0
#define OMAP4430_CM_L3INIT_USB_HOST_FS_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x00d0)
#define OMAP4_CM_L3INIT_USBPHYOCP2SCP_CLKCTRL_OFFSET	0x00e0
#define OMAP4430_CM_L3INIT_USBPHYOCP2SCP_CLKCTRL	OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L3INIT_INST, 0x00e0)

/* CM2.L4PER_CM2 register offsets */
#define OMAP4_CM_L4PER_CLKSTCTRL_OFFSET			0x0000
#define OMAP4430_CM_L4PER_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0000)
#define OMAP4_CM_L4PER_DYNAMICDEP_OFFSET		0x0008
#define OMAP4430_CM_L4PER_DYNAMICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0008)
#define OMAP4_CM_L4PER_ADC_CLKCTRL_OFFSET		0x0020
#define OMAP4430_CM_L4PER_ADC_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0020)
#define OMAP4_CM_L4PER_DMTIMER10_CLKCTRL_OFFSET		0x0028
#define OMAP4430_CM_L4PER_DMTIMER10_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0028)
#define OMAP4_CM_L4PER_DMTIMER11_CLKCTRL_OFFSET		0x0030
#define OMAP4430_CM_L4PER_DMTIMER11_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0030)
#define OMAP4_CM_L4PER_DMTIMER2_CLKCTRL_OFFSET		0x0038
#define OMAP4430_CM_L4PER_DMTIMER2_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0038)
#define OMAP4_CM_L4PER_DMTIMER3_CLKCTRL_OFFSET		0x0040
#define OMAP4430_CM_L4PER_DMTIMER3_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0040)
#define OMAP4_CM_L4PER_DMTIMER4_CLKCTRL_OFFSET		0x0048
#define OMAP4430_CM_L4PER_DMTIMER4_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0048)
#define OMAP4_CM_L4PER_DMTIMER9_CLKCTRL_OFFSET		0x0050
#define OMAP4430_CM_L4PER_DMTIMER9_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0050)
#define OMAP4_CM_L4PER_ELM_CLKCTRL_OFFSET		0x0058
#define OMAP4430_CM_L4PER_ELM_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0058)
#define OMAP4_CM_L4PER_GPIO2_CLKCTRL_OFFSET		0x0060
#define OMAP4430_CM_L4PER_GPIO2_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0060)
#define OMAP4_CM_L4PER_GPIO3_CLKCTRL_OFFSET		0x0068
#define OMAP4430_CM_L4PER_GPIO3_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0068)
#define OMAP4_CM_L4PER_GPIO4_CLKCTRL_OFFSET		0x0070
#define OMAP4430_CM_L4PER_GPIO4_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0070)
#define OMAP4_CM_L4PER_GPIO5_CLKCTRL_OFFSET		0x0078
#define OMAP4430_CM_L4PER_GPIO5_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0078)
#define OMAP4_CM_L4PER_GPIO6_CLKCTRL_OFFSET		0x0080
#define OMAP4430_CM_L4PER_GPIO6_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0080)
#define OMAP4_CM_L4PER_HDQ1W_CLKCTRL_OFFSET		0x0088
#define OMAP4430_CM_L4PER_HDQ1W_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0088)
#define OMAP4_CM_L4PER_HECC1_CLKCTRL_OFFSET		0x0090
#define OMAP4430_CM_L4PER_HECC1_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0090)
#define OMAP4_CM_L4PER_HECC2_CLKCTRL_OFFSET		0x0098
#define OMAP4430_CM_L4PER_HECC2_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0098)
#define OMAP4_CM_L4PER_I2C1_CLKCTRL_OFFSET		0x00a0
#define OMAP4430_CM_L4PER_I2C1_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x00a0)
#define OMAP4_CM_L4PER_I2C2_CLKCTRL_OFFSET		0x00a8
#define OMAP4430_CM_L4PER_I2C2_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x00a8)
#define OMAP4_CM_L4PER_I2C3_CLKCTRL_OFFSET		0x00b0
#define OMAP4430_CM_L4PER_I2C3_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x00b0)
#define OMAP4_CM_L4PER_I2C4_CLKCTRL_OFFSET		0x00b8
#define OMAP4430_CM_L4PER_I2C4_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x00b8)
#define OMAP4_CM_L4PER_L4PER_CLKCTRL_OFFSET		0x00c0
#define OMAP4430_CM_L4PER_L4PER_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x00c0)
#define OMAP4_CM_L4PER_MCASP2_CLKCTRL_OFFSET		0x00d0
#define OMAP4430_CM_L4PER_MCASP2_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x00d0)
#define OMAP4_CM_L4PER_MCASP3_CLKCTRL_OFFSET		0x00d8
#define OMAP4430_CM_L4PER_MCASP3_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x00d8)
#define OMAP4_CM_L4PER_MCBSP4_CLKCTRL_OFFSET		0x00e0
#define OMAP4430_CM_L4PER_MCBSP4_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x00e0)
#define OMAP4_CM_L4PER_MGATE_CLKCTRL_OFFSET		0x00e8
#define OMAP4430_CM_L4PER_MGATE_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x00e8)
#define OMAP4_CM_L4PER_MCSPI1_CLKCTRL_OFFSET		0x00f0
#define OMAP4430_CM_L4PER_MCSPI1_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x00f0)
#define OMAP4_CM_L4PER_MCSPI2_CLKCTRL_OFFSET		0x00f8
#define OMAP4430_CM_L4PER_MCSPI2_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x00f8)
#define OMAP4_CM_L4PER_MCSPI3_CLKCTRL_OFFSET		0x0100
#define OMAP4430_CM_L4PER_MCSPI3_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0100)
#define OMAP4_CM_L4PER_MCSPI4_CLKCTRL_OFFSET		0x0108
#define OMAP4430_CM_L4PER_MCSPI4_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0108)
#define OMAP4_CM_L4PER_MMCSD3_CLKCTRL_OFFSET		0x0120
#define OMAP4430_CM_L4PER_MMCSD3_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0120)
#define OMAP4_CM_L4PER_MMCSD4_CLKCTRL_OFFSET		0x0128
#define OMAP4430_CM_L4PER_MMCSD4_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0128)
#define OMAP4_CM_L4PER_MSPROHG_CLKCTRL_OFFSET		0x0130
#define OMAP4430_CM_L4PER_MSPROHG_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0130)
#define OMAP4_CM_L4PER_SLIMBUS2_CLKCTRL_OFFSET		0x0138
#define OMAP4430_CM_L4PER_SLIMBUS2_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0138)
#define OMAP4_CM_L4PER_UART1_CLKCTRL_OFFSET		0x0140
#define OMAP4430_CM_L4PER_UART1_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0140)
#define OMAP4_CM_L4PER_UART2_CLKCTRL_OFFSET		0x0148
#define OMAP4430_CM_L4PER_UART2_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0148)
#define OMAP4_CM_L4PER_UART3_CLKCTRL_OFFSET		0x0150
#define OMAP4430_CM_L4PER_UART3_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0150)
#define OMAP4_CM_L4PER_UART4_CLKCTRL_OFFSET		0x0158
#define OMAP4430_CM_L4PER_UART4_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0158)
#define OMAP4_CM_L4PER_MMCSD5_CLKCTRL_OFFSET		0x0160
#define OMAP4430_CM_L4PER_MMCSD5_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0160)
#define OMAP4_CM_L4PER_I2C5_CLKCTRL_OFFSET		0x0168
#define OMAP4430_CM_L4PER_I2C5_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0168)
#define OMAP4_CM_L4SEC_CLKSTCTRL_OFFSET			0x0180
#define OMAP4430_CM_L4SEC_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0180)
#define OMAP4_CM_L4SEC_STATICDEP_OFFSET			0x0184
#define OMAP4430_CM_L4SEC_STATICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0184)
#define OMAP4_CM_L4SEC_DYNAMICDEP_OFFSET		0x0188
#define OMAP4430_CM_L4SEC_DYNAMICDEP			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x0188)
#define OMAP4_CM_L4SEC_AES1_CLKCTRL_OFFSET		0x01a0
#define OMAP4430_CM_L4SEC_AES1_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x01a0)
#define OMAP4_CM_L4SEC_AES2_CLKCTRL_OFFSET		0x01a8
#define OMAP4430_CM_L4SEC_AES2_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x01a8)
#define OMAP4_CM_L4SEC_DES3DES_CLKCTRL_OFFSET		0x01b0
#define OMAP4430_CM_L4SEC_DES3DES_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x01b0)
#define OMAP4_CM_L4SEC_PKAEIP29_CLKCTRL_OFFSET		0x01b8
#define OMAP4430_CM_L4SEC_PKAEIP29_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x01b8)
#define OMAP4_CM_L4SEC_RNG_CLKCTRL_OFFSET		0x01c0
#define OMAP4430_CM_L4SEC_RNG_CLKCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x01c0)
#define OMAP4_CM_L4SEC_SHA2MD51_CLKCTRL_OFFSET		0x01c8
#define OMAP4430_CM_L4SEC_SHA2MD51_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x01c8)
#define OMAP4_CM_L4SEC_CRYPTODMA_CLKCTRL_OFFSET		0x01d8
#define OMAP4430_CM_L4SEC_CRYPTODMA_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_L4PER_INST, 0x01d8)

/* CM2.CEFUSE_CM2 register offsets */
#define OMAP4_CM_CEFUSE_CLKSTCTRL_OFFSET		0x0000
#define OMAP4430_CM_CEFUSE_CLKSTCTRL			OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CEFUSE_INST, 0x0000)
#define OMAP4_CM_CEFUSE_CEFUSE_CLKCTRL_OFFSET		0x0020
#define OMAP4430_CM_CEFUSE_CEFUSE_CLKCTRL		OMAP44XX_CM2_REGADDR(OMAP4430_CM2_CEFUSE_INST, 0x0020)

#endif