/**
 **************************************************************************
 * @file     qx_memmap.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_MEMMAP_H
#define QX_MEMMAP_H

/* memery map for peripheral */
#define SRAM_DATA_BASE    0x00000000U
#define PIC_CPU0_BASE     0x00100000U
#define PIC_CPU1_BASE     0x00101000U
#define SRAM_INST_BASE    0x00200000U
#define SRAM_BOOT_BASE    0x00280000U
#define PIECTRL_BASE      0x007F0100U
#define DU_BASE           0x007F0200U
#define CPUTIMER_BASE     0x007f0300U
#define CR_BASE           0x007F0400U
#define GR_BASE           0x007F0500U
#define MOB_BASE          0x007F0600U
#define EXP_BASE          0x007F0700U
#define WD_BASE           0x007F0800U
#define IPC_REG_BASE      0x007F0900U
#define IPC_CMD_BASE      0x007F0A00U
#define VCU_BASE          0x007F0B00U
#define TRACE_BUFFER_BASE 0x007F0C00U
#define WP_BASE           0x007F0D00U
#define ECC_BASE          0x007F0E00U
#define CLKCFG_BASE       0x01000000U
#define CPUSYS_BASE       0x01001000U
#define NMI_BASE          0x01001200U
#define DCC0_BASE         0x01002000U
#define GPIOCTRL_BASE     0x01003000U
#define GPIODATA_BASE     0x01004000U
#define INPUTXBAR_BASE    0x01005000U
#define EPWMXBAR_BASE     0x01006000U
#define OUTPUTXBAR_BASE   0x01007000U
#define XBAR_FLAG_BASE    0x01008000U
#define DMA_BASE          0x01009000U
#define ANALOGSUBSYS_BASE 0x0100A000U
#define ADCA_REGS_BASE    0x0100B000U
#define ADCB_REGS_BASE    0x0100B200U
#define ADCC_REGS_BASE    0x0100B400U
#define PGA1_BASE         0x0100C000U
#define PGA2_BASE         0x0100C100U
#define PGA3_BASE         0x0100C200U
#define PGA4_BASE         0x0100C300U
#define PGA5_BASE         0x0100C400U
#define PGA6_BASE         0x0100C500U
#define PGA7_BASE         0x0100C600U
#define DAC_BASE          0x0100D000U
#define CMPSS_BASE        0x0100E000U
#define SDFM_BASE         0x0100F000U
#define ECAP1_BASE        0x01010000U
#define ECAP2_BASE        0x01010080U
#define ECAP3_BASE        0x01010100U
#define ECAP4_BASE        0x01010180U
#define ECAP5_BASE        0x01010200U
#define HRCAP1_BASE       0x01010280U
#define HRCAP2_BASE       0x01010300U
#define SYNCSOC_BASE      0x01010380U
#define SFO_BASE          0x01010400U
#define EPWM1_BASE        0x01011000U
#define EPWM2_BASE        0x01011200U
#define EPWM3_BASE        0x01011400U
#define EPWM4_BASE        0x01011600U
#define EPWM5_BASE        0x01011800U
#define EPWM6_BASE        0x01011A00U
#define EPWM7_BASE        0x01011C00U
#define EPWM8_BASE        0x01011E00U
#define EQEP1_BASE        0x01012000U
#define EQEP2_BASE        0x01012800U
#define SPI1_MASTER_BASE  0x01013000U
#define SPI1_SLAVE_BASE   0x01013400U
#define SPI1_SEL_BASE     0x01013800U
#define SPI2_MASTER_BASE  0x01014000U
#define SPI2_SLAVE_BASE   0x01014400U
#define SPI2_SEL_BASE     0x01014800U
#define SCIA_BASE         0x01015000U
#define SCIB_BASE         0x01016000U
#define I2CA_BASE         0x01017000U
#define PMBUS_BASE        0x01018000U
#define DLIN_BASE         0x01019000U
#define FSITX_BASE        0x0101A000U
#define FSIRX_BASE        0x0101B000U
#define REGFILE_BASE      0x0101C000U
#define CANA_BASE         0x01020000U
#define CANB_BASE         0x01030000U
#define FLASH_CTRL_BASE   0x01040000U
#define EFUSE_BASE        0x20000000U
#define FLASH_DATA_BASE   0x30000000U

#endif
