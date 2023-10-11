/**
 **************************************************************************
 * @file	 qx_dma.h
 * @version	 v1.0.0
 * @date	 2023-05-23
 * @brief	 dw_axi_dmac header
 **************************************************************************
 */

#ifndef QX_DMA_H
#define QX_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"

/* IP defines */
#define DMAX_NUM_CHANNELS  6
#define DMAX_NUM_HS_IF     64
#define DMAX_HAS_LLI_PARAM 0
#define DMAX_M_DATA_WIDTH  32
#define DMAX_MAX_MSIZE     8
#define DMAX_MAX_BLOCK_TS  31

#define COMMON_REG_LEN 0x100
#define CHAN_REG_LEN   0x100
#define DMAX_CHAN_BASE (DMA_BASE + COMMON_REG_LEN)
#define DMAX_COMM_BASE DMA_BASE

/* Common registers offset */
#define DMAC_ID                   0x000 /* R DMAC ID */
#define DMAC_COMPVER              0x008 /* R DMAC Component Version */
#define DMAC_CFG                  0x010 /* R/W DMAC Configuration */
#define DMAC_CHEN                 0x018 /* R/W DMAC Channel Enable */
#define DMAC_CHEN_L               0x018 /* R/W DMAC Channel Enable 00-31 */
#define DMAC_CHEN_H               0x01C /* R/W DMAC Channel Enable 32-63 */
#define DMAC_CHSUSPREG            0x020 /* R/W DMAC Channel Suspend */
#define DMAC_CHABORTREG           0x028 /* R/W DMAC Channel Abort */
#define DMAC_INTSTATUS            0x030 /* R DMAC Interrupt Status */
#define DMAC_COMMON_INTCLEAR      0x038 /* W DMAC Interrupt Clear */
#define DMAC_COMMON_INTSTATUS_ENA 0x040 /* R DMAC Interrupt Status Enable */
#define DMAC_COMMON_INTSIGNAL_ENA 0x048 /* R/W DMAC Interrupt Signal Enable */
#define DMAC_COMMON_INTSTATUS     0x050 /* R DMAC Interrupt Status */
#define DMAC_RESET                0x058 /* R DMAC Reset Register1 */

/* DMA channel registers offset */
#define CH_SAR_L             0x000 /* R/W Chan Source Low Address */
#define CH_SAR_H             0x004 /* R/W Chan Source High Address */
#define CH_DAR_L             0x008 /* R/W Chan Destination Low Address */
#define CH_DAR_H             0x00C /* R/W Chan Destination High Address */
#define CH_BLOCK_TS          0x010 /* R/W Chan Block Transfer Size */
#define CH_CTL               0x018 /* R/W Chan Control */
#define CH_CTL_L             0x018 /* R/W Chan Control 00-31 */
#define CH_CTL_H             0x01C /* R/W Chan Control 32-63 */
#define CH_CFG               0x020 /* R/W Chan Configuration */
#define CH_CFG_L             0x020 /* R/W Chan Configuration 00-31 */
#define CH_CFG_H             0x024 /* R/W Chan Configuration 32-63 */
#define CH_LLP               0x028 /* R/W Chan Linked List Pointer */
#define CH_STATUS            0x030 /* R Chan Status */
#define CH_SWHSSRC           0x038 /* R/W Chan SW Handshake Source */
#define CH_SWHSDST           0x040 /* R/W Chan SW Handshake Destination */
#define CH_BLK_TFR_RESUMEREQ 0x048 /* W Chan Block Transfer Resume Req */
#define CH_AXI_ID            0x050 /* R/W Chan AXI ID */
#define CH_AXI_QOS           0x058 /* R/W Chan AXI QOS */
#define CH_SSTAT             0x060 /* R Chan Source Status */
#define CH_DSTAT             0x068 /* R Chan Destination Status */
#define CH_SSTATAR           0x070 /* R/W Chan Source Status Fetch Addr */
#define CH_DSTATAR           0x078 /* R/W Chan Destination Status Fetch Addr */
#define CH_INTSTATUS_ENA     0x080 /* R/W Chan Interrupt Status Enable */
#define CH_INTSTATUS         0x088 /* R/W Chan Interrupt Status */
#define CH_INTSIGNAL_ENA     0x090 /* R/W Chan Interrupt Signal Enable */
#define CH_INTCLEAR          0x098 /* W Chan Interrupt Clear */

#define UNUSED_CHANNEL          0x3F   /* Set unused DMA channel to 0x3F */
#define DMA_APB_HS_SEL_BIT_SIZE 0x08   /* HW handshake bits per channel */
#define DMA_APB_HS_SEL_MASK     0xFF   /* HW handshake select masks */
#define MAX_BLOCK_SIZE          0x1000 /* 1024 blocks * 4 bytes data width */
#define DMA_REG_MAP_CH_REF      0x08   /* Channel count to choose register map */

#define BIT(nr) ((1UL) << (nr))

/* DMAC_CFG */
#define DMAC_EN_POS  0
#define DMAC_EN_MASK BIT(DMAC_EN_POS)

#define INT_EN_POS  1
#define INT_EN_MASK BIT(INT_EN_POS)

/* DMAC_CHEN */
#define DMAC_CHAN_EN_SHIFT    0
#define DMAC_CHAN_EN_WE_SHIFT 8

#define DMAC_CHAN_SUSP_SHIFT    16
#define DMAC_CHAN_SUSP_WE_SHIFT 24

/* DMAC_CHEN2 */
#define DMAC_CHAN_EN2_WE_SHIFT 16

/* DMAC_CHSUSP */
#define DMAC_CHAN_SUSP2_SHIFT    0
#define DMAC_CHAN_SUSP2_WE_SHIFT 16

/* CH_CTL_H */

#define CH_CTL_H_ARLEN_EN      BIT(6)
#define CH_CTL_H_ARLEN_POS     7
#define CH_CTL_H_AWLEN_EN      BIT(15)
#define CH_CTL_H_AWLEN_POS     16
#define CH_CTL_L_DST_WIDTH_POS 11
#define CH_CTL_L_SRC_WIDTH_POS 8

#define CH_CTL_L_DST_INC_POS   6
#define CH_CTL_L_SRC_INC_POS   4
#define CH_CTL_L_LAST_WRITE_EN BIT(30)

#define CH_CTL_L_DST_MSIZE_POS 18
#define CH_CTL_L_SRC_MSIZE_POS 14
#define CH_CTL_H_LLI_LAST      BIT(30)
#define CH_CTL_H_LLI_VALID     BIT(31)

/* CH_CFG_L */
#define CH_CTL_L_DST_MAST             BIT(2)
#define CH_CTL_L_SRC_MAST             BIT(0)
#define CH_CFG_L_DST_MULTBLK_TYPE_POS 2
#define CH_CFG_L_SRC_MULTBLK_TYPE_POS 0

/* CH_CFG_H */
#define CH_CFG_H_TT_FC_POS      0
#define CH_CFG_H_PRIORITY_POS   17
#define CH_CFG_H_DST_PER_POS    12
#define CH_CFG_H_SRC_PER_POS    7
#define CH_CFG_H_HS_SEL_DST_POS 4
#define CH_CFG_H_HS_SEL_SRC_POS 3

/* CH_CFG2 */
#define CH_CFG2_L_SRC_PER_POS 4
#define CH_CFG2_L_DST_PER_POS 11

#define CH_CFG2_H_TT_FC_POS      0
#define CH_CFG2_H_HS_SEL_SRC_POS 3
#define CH_CFG2_H_HS_SEL_DST_POS 4
#define CH_CFG2_H_PRIORITY_POS   20

typedef enum
{
    DMAX_M2M_DMA = 0x0,
    DMAX_M2P_DMA = 0x1,
    DMAX_P2M_DMA = 0x2,
    DMAX_P2P_DMA = 0x3,
    DMAX_M2P_SRC = 0x4,
    DMAX_P2P_SRC = 0x5,
    DMAX_P2M_DST = 0x6,
    DMAX_P2P_DST = 0x7,
} DMAX_TT_FC;

typedef enum
{
    DMAX_MSIZE_1    = 0x0,
    DMAX_MSIZE_4    = 0x1,
    DMAX_MSIZE_8    = 0x2,
    DMAX_MSIZE_16   = 0x3,
    DMAX_MSIZE_32   = 0x4,
    DMAX_MSIZE_64   = 0x5,
    DMAX_MSIZE_128  = 0x6,
    DMAX_MSIZE_256  = 0x7,
    DMAX_MSIZE_512  = 0x8,
    DMAX_MSIZE_1024 = 0x9,
} DMAXBurstLength;

typedef enum
{
    DMAX_MBLK_TYPE_CONTIGUOUS = 0,
    DMAX_MBLK_TYPE_RELOAD,
    DMAX_MBLK_TYPE_SHADOW_REG,
    DMAX_MBLK_TYPE_LL
} DMAXMultBlockType;

typedef enum
{
    DMAX_IRQ_CH1_ACTIVE    = BIT(0),
    DMAX_IRQ_CH2_ACTIVE    = BIT(1),
    DMAX_IRQ_CH3_ACTIVE    = BIT(2),
    DMAX_IRQ_CH4_ACTIVE    = BIT(3),
    DMAX_IRQ_CH5_ACTIVE    = BIT(4),
    DMAX_IRQ_CH6_ACTIVE    = BIT(5),
    DMAX_IRQ_COMMON_ACTIVE = BIT(16),
} DMAX_IRQ_STATUS;

typedef enum
{
    DMAX_COMM_IRQ_NONE      = 0,
    DMAX_SLVIF_DEC_ERR      = BIT(0),
    DMAX_SLVIF_WR2RO_ERR    = BIT(1),
    DMAX_SLVIF_RD2WO_ERR    = BIT(2),
    DMAX_SLVIF_DRONHOLD_ERR = BIT(3),
    DMAX_SLVIF_WRPARITY_ERR = BIT(7),
    DMAX_SLVIF_OF_DEC_ERR   = BIT(8),
} DMAX_COMM_IRQ;

typedef enum
{
    DMAX_IRQ_NONE             = 0,
    DMAX_IRQ_BLOCK_TRF        = BIT(0),
    DMAX_IRQ_DMA_TRF          = BIT(1),
    DMAX_IRQ_SRC_TRAN         = BIT(3),
    DMAX_IRQ_DST_TRAN         = BIT(4),
    DMAX_IRQ_SRC_DEC_ERR      = BIT(5),
    DMAX_IRQ_DST_DEC_ERR      = BIT(6),
    DMAX_IRQ_SRC_SLV_ERR      = BIT(7),
    DMAX_IRQ_DST_SLV_ERR      = BIT(8),
    DMAX_IRQ_LLI_RD_DEC_ERR   = BIT(9),
    DMAX_IRQ_LLI_WR_DEC_ERR   = BIT(10),
    DMAX_IRQ_LLI_RD_SLV_ERR   = BIT(11),
    DMAX_IRQ_LLI_WR_SLV_ERR   = BIT(12),
    DMAX_IRQ_INVALID_ERR      = BIT(13),
    DMAX_IRQ_MULTIBLKTYPE_ERR = BIT(14),
    DMAX_IRQ_DEC_ERR          = BIT(16),
    DMAX_IRQ_WR2RO_ERR        = BIT(17),
    DMAX_IRQ_RD2RWO_ERR       = BIT(18),
    DMAX_IRQ_WRONCHEN_ERR     = BIT(19),
    DMAX_IRQ_SHADOWREG_ERR    = BIT(20),
    DMAX_IRQ_WRONHOLD_ERR     = BIT(21),
    DMAX_IRQ_LOCK_CLEARED     = BIT(27),
    DMAX_IRQ_SRC_SUSPENDED    = BIT(28),
    DMAX_IRQ_SUSPENDED        = BIT(29),
    DMAX_IRQ_DISABLED         = BIT(30),
    DMAX_IRQ_ABORTED          = BIT(31),
    DMAX_IRQ_ALL_ERR          = ((unsigned long)(0x2F << 15 | 0x2FF << 4)),
    DMAX_IRQ_ALL              = 0xFFFFFFFFUL
} DMAX_CHAN_IRQ;

typedef enum
{
    DAMCX_HS_HARDWARE = 0,
    DMAX_HS_SOFTWARE  = 1
} DMAXHandShakeType;

typedef enum
{
    DMAX_TRANS_WIDTH_8   = 0x0,
    DMAX_TRANS_WIDTH_16  = 0x1,
    DMAX_TRANS_WIDTH_32  = 0x2,
    DMAX_TRANS_WIDTH_64  = 0x3,
    DMAX_TRANS_WIDTH_128 = 0x4,
    DMAX_TRANS_WIDTH_256 = 0x5,
    DMAX_TRANS_WIDTH_512 = 0x6,
    DMAX_TRANS_WIDTH_MAX = DMAX_TRANS_WIDTH_512
} DMAXTransferWidth;

typedef enum
{
    DMAX_HS_NONE      = 0,
    DMAX_HS_MEM       = 0,
    DMAX_HS_ADC1_REQ1 = 0,
    DMAX_HS_ADC1_REQ2 = 1,
    DMAX_HS_ADC1_REQ3 = 2,
    DMAX_HS_ADC1_REQ4 = 3,
    DMAX_HS_ADC1_EVT  = 4,
    DMAX_HS_ADC2_REQ1 = 5,
    DMAX_HS_ADC2_REQ2 = 6,
    DMAX_HS_ADC2_REQ3 = 7,
    DMAX_HS_ADC2_REQ4 = 8,
    DMAX_HS_ADC2_EVT  = 9,
    DMAX_HS_ADC3_REQ1 = 10,
    DMAX_HS_ADC3_REQ2 = 11,
    DMAX_HS_ADC3_REQ3 = 12,
    DMAX_HS_ADC3_REQ4 = 13,
    DMAX_HS_ADC3_EVT  = 14,
    DMAX_HS_XINT1     = 15,
    DMAX_HS_XINT2     = 16,
    DMAX_HS_XINT3     = 17,
    DMAX_HS_XINT4     = 18,
    DMAX_HS_XINT5     = 19,
    DMAX_HS_EPWM1_A   = 20,
    DMAX_HS_EPWM1_B   = 21,
    DMAX_HS_EPWM2_A   = 22,
    DMAX_HS_EPWM2_B   = 23,
    DMAX_HS_EPWM3_A   = 24,
    DMAX_HS_EPWM3_B   = 25,
    DMAX_HS_EPWM4_A   = 26,
    DMAX_HS_EPWM4_B   = 27,
    DMAX_HS_EPWM5_A   = 28,
    DMAX_HS_EPWM5_B   = 29,
    DMAX_HS_EPWM6_A   = 30,
    DMAX_HS_EPWM6_B   = 31,
    DMAX_HS_EPWM7_A   = 32,
    DMAX_HS_EPWM7_B   = 33,
    DMAX_HS_EPWM8_A   = 34,
    DMAX_HS_EPWM8_B   = 35,
    DMAX_HS_TINT1     = 36,
    DMAX_HS_TINT2     = 37,
    DMAX_HS_TINT3     = 38,
    DMAX_HS_ECAP1     = 39,
    DMAX_HS_ECAP2     = 40,
    DMAX_HS_ECAP3     = 41,
    DMAX_HS_ECAP4     = 42,
    DMAX_HS_ECAP5     = 43,
    DMAX_HS_ECAP6     = 44,
    DMAX_HS_ECAP7     = 45,
    DMAX_HS_SDFLT1    = 46,
    DMAX_HS_SDFLT2    = 47,
    DMAX_HS_SDFLT3    = 48,
    DMAX_HS_SDFLT4    = 49,
    DMAX_HS_SPI0M_TX  = 50,
    DMAX_HS_SPI0M_RX  = 51,
    DMAX_HS_SPI0S_TX  = 52,
    DMAX_HS_SPI0S_RX  = 53,
    DMAX_HS_SPI1M_TX  = 54,
    DMAX_HS_SPI1M_RX  = 55,
    DMAX_HS_SPI1S_TX  = 56,
    DMAX_HS_SPI1S_RX  = 57,
    DMAX_HS_UART0_TX  = 58,
    DMAX_HS_UART0_RX  = 59,
    DMAX_HS_UART1_TX  = 60,
    DMAX_HS_UART1_RX  = 61,
    DMAX_HS_FSI_TX    = 62,
    DMAX_HS_FSI_RX    = 63
} DMAXHSInterface;

typedef enum
{
    DMAX_MASTER_0 = 0,
    DMAX_MASTER_1 = 1
} DMAXMasterIF;

typedef enum
{
    DMAX_SWHS_REQ    = 0,
    DMAX_SWHS_SINGLE = 1,
    DMAX_SWHS_LST    = 2
} DMAXSWHSReqType;

typedef struct
{
    u32 src_addr;
    u32 dst_addr;
    u32 block_size;
    DMAXTransferWidth src_width;
    DMAXTransferWidth dst_width;
    DMAXBurstLength src_msize;
    DMAXBurstLength dst_msize;
    u8 channel;
    u8 prior;
    DMAX_TT_FC tt_fc;
    DMAXHSInterface src_hs_i;
    DMAXHSInterface dst_hs_i;
    DMAXHandShakeType src_hs_t;
    DMAXHandShakeType dst_hs_t;
    DMAXMultBlockType src_mblk_t;
    DMAXMultBlockType dst_mblk_t;
} DMAXChanConfig;

typedef struct
{
    vu32 SAR_LO;
    vu32 SAR_HI;
    vu32 DAR_LO;
    vu32 DAR_HI;
    vu32 BLOCK_TS;
    vu32 RESERVED0;
    union
    {
        vu32 CTL_LO;
        struct
        {
            vu32 SMS       : 1; // [0]
            vu32 RESERVED0 : 1; // [1]
            vu32 DMS       : 1; // [2]
            vu32 RESERVED1 : 1; // [3]
            vu32 SINC      : 1; // [4]
            vu32 RESERVED2 : 1; // [5]
            vu32 DINC      : 1; // [6]
            vu32 RESERVED3 : 1; // [7]
            vu32 SRC_WIDTH : 3; // [10:8]
            vu32 DST_WIDTH : 3; // [13:11]
            vu32 SRC_MSIZE : 4; // [17:14]
            vu32 DST_MSIZE : 4; // [21:18]
            vu32 AR_CACHE  : 4; // [25:22]
            vu32 AW_CACHE  : 4; // [29:26]
            vu32 RESERVED4 : 2; // [31:30]
        } CTL_LO_BITS;
    };
    union
    {
        vu32 CTL_HI;
        struct
        {
            vu32 AR_PROT     : 3; // [2:0]
            vu32 AW_PROT     : 3; // [5:3}
            vu32 ARLEN_EN    : 1; // [6]
            vu32 ARLEN       : 8; // [14:7]
            vu32 AWLEN_EN    : 1; // [15]
            vu32 AW_LEN      : 8; // [23:16]
            vu32 SRC_STAT_EN : 1; // [24]
            vu32 DST_STAT_EN : 1; // [25]
            vu32 IOC_BLKTFR  : 1; // [26]
            vu32 RESERVED    : 5; // [31:27]
        } CTL_HI_BITS;
    };
    union
    {
        vu32 CFG_LO;
        struct
        {
            vu32 SRC_MULTBLK_TYPE : 2;  // [1:0]
            vu32 DST_MULTBLK_TYPE : 2;  // [3:2]
            vu32 RESERVED         : 28; // [31:4]
        } CFG_LO_BITS;
        vu32 cfg2_lo;
        struct
        {
            vu32 SRC_MULTBLK_TYPE : 2; // [1:0]
            vu32 DST_MULTBLK_TYPE : 2; // [3:2]
            vu32 SRC_PER          : 6; // [9:4]
            vu32 RESERVED0        : 1; // [10]
            vu32 DST_PER          : 6; // [16:11]
            vu32 RESERVED1        : 1; // [17]
            vu32 RD_UID           : 4; // [21:18]
            vu32 RESERVED2        : 3; // [24:22]
            vu32 WR_UID           : 4; // [21:18]
        } CFG2_LO_BITS;
    };
    union
    {
        vu32 CFG_HI;
        struct
        {
            vu32 TT_FC        : 3; // [2:0]
            vu32 HS_SEL_SRC   : 1; // [3]
            vu32 HS_SEL_DST   : 1; // [4]
            vu32 SRC_HWHS_POL : 1; // [5]
            vu32 DST_HWHS_POL : 1; // [6]
            vu32 SRC_PER      : 4; // [10:7]
            vu32 RESERVED0    : 1; // [11]
            vu32 DST_PER      : 4; // [15:12]
            vu32 RESERVED1    : 1; // [16]
            vu32 PRIOR        : 3; // [19:17]
            vu32 LOCK_CH      : 1; // [20]
            vu32 LOCK_CH_L    : 2; // [22:21]
            vu32 SRC_OSR_LMT  : 4; // [26:23]
            vu32 DST_OSR_LMT  : 4; // [30:27]
        } CFG_HI_BITS;
        vu32 CFG2_HI;
        struct
        {
            vu32 TT_FC        : 3; // [2:0]
            vu32 HS_SEL_SRC   : 1; // [3]
            vu32 HS_SEL_DST   : 1; // [4]
            vu32 SRC_HWHS_POL : 1; // [5]
            vu32 DST_HWHS_POL : 1; // [6]
            vu32 RESERVED0    : 8; // [13:7]
            vu32 PRIOR        : 5; // [19:14]
            vu32 LOCK_CH      : 1; // [20]
            vu32 LOCK_CH_L    : 2; // [22:21]
            vu32 SRC_OSR_LMT  : 4; // [26:23]
            vu32 DST_OSR_LMT  : 4; // [30:27]
        } CFG2_HI_BITS;
    };
    vu32 LLP_LO;
    vu32 LLP_HI;
    vu32 STATUS_LO;
    vu32 STATUS_HI;
    union
    {
        vu32 SWHSSRC_LO;
        struct
        {
            vu32 SWHS_REQ_SRC       : 1; // [0]
            vu32 SWHS_REQ_SRC_EN    : 1; // [1]
            vu32 SWHS_SGLREQ_SRC    : 1; // [2]
            vu32 SWHS_SGLREQ_SRC_WE : 1; // [3]
            vu32 SWHS_LST_SRC       : 1; // [4]
            vu32 SWHS_LST_SRC_WE    : 1; // [5]
        } SWHSSRC_LO_BITS;
    };
    vu32 SWHSSRC_HI;
    union
    {
        vu32 SWHSDST_LO;
        struct
        {
            vu32 SWHS_REQ_DST       : 1; // [0]
            vu32 SWHS_REQ_DST_EN    : 1; // [1]
            vu32 SWHS_SGLREQ_DST    : 1; // [2]
            vu32 SWHS_SGLREQ_DST_WE : 1; // [3]
            vu32 SWHS_LST_DST       : 1; // [4]
            vu32 SWHS_LST_DST_WE    : 1; // [5]
        } SWHSDST_LO_BITS;
    };
    vu32 SWHSDST_HI;
    vu32 BLK_TFR_RESUME_LO;
    vu32 BLK_TFR_RESUME_HI;
    vu32 AIX_ID_LO;
    vu32 AIX_ID_HI;
    vu32 AIX_QOS_LO;
    vu32 AIX_QOS_HI;
    vu32 SSTAT_LO;
    vu32 SSTAT_HI;
    vu32 DSTAT_LO;
    vu32 DSTAT_HI;
    vu32 SSTATA_LO;
    vu32 SSTATA_HI;
    vu32 DSTATA_LO;
    vu32 DSTATA_HI;
    vu32 INTSTATUS_EN_LO;
    vu32 INTSTATUS_EN_HI;
    vu32 INTSTATUS_LO;
    vu32 INTSTATUS_HI;
    vu32 INTSIGNAL_EN_LO;
    vu32 INTSIGNAL_EN_HI;
    vu32 INTSIGNAL_LO;
    vu32 INTSIGNAL_HI;
    vu32 INTCLEAR_LO;
    vu32 INTCLEAR_HI;
} DMAX_CHAN_REG;

typedef struct
{
    vu32 ID_LO;
    vu32 ID_HI;
    vu32 COMPVER_LO;
    vu32 COMPVER_HI;
    vu32 CFG_LO;
    vu32 CFG_HI;
    union
    {
        vu32 CHEN_LO;
        vu32 CHEN2_LO;
    };
    union
    {
        vu32 CHEN_HI;
        vu32 CHEN2_HI;
    };
    vu32 CHSUSP_LO;
    vu32 CHSUSP_HI;
    vu32 CHABORT_LO;
    vu32 CHABORT_HI;
    union
    {
        vu32 INTSTATUS_LO;
        vu32 INTSTATUS2_LO;
    };
    union
    {
        vu32 INTSTATUS_HI;
        vu32 INTSTATUS2_HI;
    };
    vu32 COMMON_INTCLEAR_LO;
    vu32 COMMON_INTCLEAR_HI;
    vu32 COMMON_INTSTATUS_EN_LO;
    vu32 COMMON_INTSTATUS_EN_HI;
    vu32 COMMON_INTSIGNAL_EN_LO;
    vu32 COMMON_INTSIGNAL_EN_HI;
    vu32 COMMON_INTSTATUS_LO;
    vu32 COMMON_INTSTATUS_HI;
    vu32 RESET_LO;
    vu32 RESET_HI;
    vu32 LOWPOWER_LO;
    vu32 LOWPOWER_HI;
    vu32 COMMON_PARCTL_LO;
    vu32 COMMON_PARCTL_HI;
    vu32 COMMON_ECCCTLSTATUS_LO;
    vu32 COMMON_ECCCTLSTATUS_HI;
} DMAX_COMMON_REG;

#define DW_DMAX      ((DMAX_COMMON_REG *)DMA_BASE)
#define DMAX_CHAN(x) ((DMAX_CHAN_REG *)(DMA_BASE + 0x100 * x));

static inline void DMAX_DMACEnable(void)
{
    DW_DMAX->CFG_LO |= 1U;
}

static inline void DMAX_DMACDisable(void)
{
    DW_DMAX->CFG_LO &= 2U;
}

static inline void DMAX_IRQEnable(void)
{
#if 0
	u32 value = 0;

	value = DW_DMAX->CFG_LO;
	value |= 2U;
	DW_DMAX->CFG_LO = value;
#endif
    DW_DMAX->CFG_LO |= 2U;
}

static inline void DMAX_IRQDisable(void)
{
    DW_DMAX->CFG_LO &= 1U;
}

static inline void DMAX_chanEnable(u8 channel)
{
    u32 value = 0;

    value = DW_DMAX->CHEN_LO;
    value |= (0x101 << (channel - 1));
    DW_DMAX->CHEN_LO = value;
}

static inline bool DMAX_isChanEnable(u8 channel)
{
    return (DW_DMAX->CHEN_LO & (1 << (channel - 1)));
}

static inline void DMAX_chanSuspend(u8 channel)
{
    u32 value = 0;

    value = DW_DMAX->CHSUSP_LO;
    value |= (0x101 << (channel - 1));
    DW_DMAX->CHSUSP_LO = value;
}

static inline void DMAX_chanAbort(u8 channel)
{
    u32 value = 0;

    value = DW_DMAX->CHABORT_LO;
    value |= (0x101 << (channel - 1));
    DW_DMAX->CHABORT_LO = value;
}

static inline u32 DMAX_getIRQStatus(void)
{
    return DW_DMAX->INTSTATUS_LO;
}

static inline u32 DMAX_getCommIRQStatus(void)
{
    return DW_DMAX->COMMON_INTSTATUS_LO;
}

static inline void DMAX_enableCommIRQStatus(u32 flag)
{
    DW_DMAX->COMMON_INTSTATUS_EN_LO |= flag;
}

static inline void DMAX_enableCommIRQSignal(u32 flag)
{
    DW_DMAX->COMMON_INTSIGNAL_EN_LO |= flag;
}

static inline void DMAX_clearCommIRQ(u32 flag)
{
    DW_DMAX->COMMON_INTCLEAR_LO |= flag;
}

static inline void DMAX_DMACReset(void)
{
    DW_DMAX->RESET_LO = 0x1;
}

static inline void DMAX_setChanAddr(u8 channel, u32 src_addr, u32 dst_addr)
{
    DMAX_CHAN_REG *chan_reg = DMAX_CHAN(channel);

    chan_reg->SAR_LO = src_addr;
    chan_reg->SAR_HI = 0U;
    chan_reg->DAR_LO = dst_addr;
    chan_reg->DAR_HI = 0U;
}

static inline void DMAX_setChanBlockTS(u8 channel, u32 block_ts)
{
    DMAX_CHAN_REG *chan_reg = DMAX_CHAN(channel);

    if (block_ts > DMAX_MAX_BLOCK_TS)
        block_ts = DMAX_MAX_BLOCK_TS;

    chan_reg->BLOCK_TS = block_ts;
}

static inline void DMAX_setChanMaster(u8 channel, DMAXMasterIF src, DMAXMasterIF dst)
{
    DMAX_CHAN_REG *chan_reg = DMAX_CHAN(channel);

    chan_reg->CTL_LO_BITS.SMS = src;
    chan_reg->CTL_LO_BITS.DMS = dst;
}

static inline void DMAX_setChanWidth(u8 channel, DMAXTransferWidth src, DMAXTransferWidth dst)
{
    DMAX_CHAN_REG *chan_reg = DMAX_CHAN(channel);

    chan_reg->CTL_LO_BITS.SRC_WIDTH = src;
    chan_reg->CTL_LO_BITS.DST_WIDTH = dst;
}

static inline void DMAX_setBurstLength(u8 channel, DMAXBurstLength src, DMAXBurstLength dst)
{
    DMAX_CHAN_REG *chan_reg = DMAX_CHAN(channel);

    chan_reg->CTL_LO_BITS.SRC_MSIZE = src;
    chan_reg->CTL_LO_BITS.DST_MSIZE = dst;
}

static inline void DMAX_setTT_FC(u8 channel, DMAX_TT_FC tt_fc)
{
    DMAX_CHAN_REG *chan_reg = DMAX_CHAN(channel);

    switch (tt_fc)
    {
        case DMAX_M2M_DMA:
            // chan_reg->CFG_HI_BITS.TT_FC = DMAX_M2M_DMA;
            chan_reg->CFG2_HI_BITS.TT_FC = DMAX_M2M_DMA;
            chan_reg->CTL_LO_BITS.SINC   = 0;
            chan_reg->CTL_LO_BITS.DINC   = 0;
            break;
        case DMAX_M2P_DMA:
            // chan_reg->CFG_HI_BITS.TT_FC = DMAX_M2P_DMA;
            chan_reg->CFG2_HI_BITS.TT_FC = DMAX_M2P_DMA;
            chan_reg->CTL_LO_BITS.SINC   = 0;
            chan_reg->CTL_LO_BITS.DINC   = 1;
            break;
        case DMAX_P2M_DMA:
            // chan_reg->CFG_HI_BITS.TT_FC = DMAX_P2M_DMA;
            chan_reg->CFG2_HI_BITS.TT_FC = DMAX_P2M_DMA;
            chan_reg->CTL_LO_BITS.SINC   = 1;
            chan_reg->CTL_LO_BITS.DINC   = 0;
            break;
        case DMAX_P2P_DMA:
            // chan_reg->CFG_HI_BITS.TT_FC = DMAX_P2P_DMA;
            chan_reg->CFG2_HI_BITS.TT_FC = DMAX_P2P_DMA;
            chan_reg->CTL_LO_BITS.SINC   = 1;
            chan_reg->CTL_LO_BITS.DINC   = 1;
            break;
        case DMAX_M2P_SRC:
            // chan_reg->CFG_HI_BITS.TT_FC = DMAX_M2P_SRC;
            chan_reg->CFG2_HI_BITS.TT_FC = DMAX_M2P_SRC;
            chan_reg->CTL_LO_BITS.SINC   = 0;
            chan_reg->CTL_LO_BITS.DINC   = 1;
            break;
        case DMAX_P2P_SRC:
            // chan_reg->CFG_HI_BITS.TT_FC = DMAX_P2P_SRC;
            chan_reg->CFG2_HI_BITS.TT_FC = DMAX_P2P_SRC;
            chan_reg->CTL_LO_BITS.SINC   = 1;
            chan_reg->CTL_LO_BITS.DINC   = 1;
            break;
        case DMAX_P2M_DST:
            // chan_reg->CFG_HI_BITS.TT_FC = DMAX_P2M_DST;
            chan_reg->CFG2_HI_BITS.TT_FC = DMAX_P2M_DST;
            chan_reg->CTL_LO_BITS.SINC   = 1;
            chan_reg->CTL_LO_BITS.DINC   = 0;
            break;
        case DMAX_P2P_DST:
            // chan_reg->CFG_HI_BITS.TT_FC = DMAX_P2P_DST;
            chan_reg->CFG2_HI_BITS.TT_FC = DMAX_P2P_DST;
            chan_reg->CTL_LO_BITS.SINC   = 1;
            chan_reg->CTL_LO_BITS.DINC   = 1;
            break;
    }
}

static inline void DMAX_setHSInterface(u8 channel, DMAXHSInterface src, DMAXHSInterface dst)
{
    DMAX_CHAN_REG *chan_reg = DMAX_CHAN(channel);

#if 1
    if (src != 0)
    {
        chan_reg->CFG2_HI_BITS.HS_SEL_SRC = 0;
        chan_reg->CFG2_LO_BITS.SRC_PER    = src;
    }
    else
        chan_reg->CFG2_LO_BITS.SRC_PER = 0;

    if (dst != 0)
    {
        chan_reg->CFG2_HI_BITS.HS_SEL_DST = 0;
        chan_reg->CFG2_LO_BITS.DST_PER    = dst;
    }
    else
        chan_reg->CFG2_LO_BITS.DST_PER = 0;
#endif
#if 0
    if (src != 0 ) {
    	chan_reg->CFG_HI_BITS.HS_SEL_SRC = 0;
    	chan_reg->CFG_HI_BITS.SRC_PER = src;
    } else
    	chan_reg->CFG_HI_BITS.SRC_PER = 0;

    if (dst != 0) {
    	chan_reg->CFG_HI_BITS.HS_SEL_DST = 0;
    	chan_reg->CFG_HI_BITS.DST_PER = dst;
    } else
    	chan_reg->CFG_HI_BITS.DST_PER = 0;
#endif
}

static inline void DMAX_setMultBlocktype(u8 channel, DMAXMultBlockType src, DMAXMultBlockType dst)
{
    DMAX_CHAN_REG *chan_reg = DMAX_CHAN(channel);

    chan_reg->CFG_LO_BITS.SRC_MULTBLK_TYPE = src;
    chan_reg->CFG_LO_BITS.DST_MULTBLK_TYPE = dst;
}

static inline void DMAX_setChanPrior(u8 channel, u8 prior)
{
    DMAX_CHAN_REG *chan_reg = DMAX_CHAN(channel);

    prior                        = prior % DMAX_NUM_CHANNELS;
    chan_reg->CFG2_HI_BITS.PRIOR = prior;

    chan_reg->CFG2_HI_BITS.SRC_OSR_LMT = 5;
    chan_reg->CFG2_HI_BITS.DST_OSR_LMT = 5;
}

static inline u32 DMAX_getCompletedSize(u8 channel)
{
    DMAX_CHAN_REG *chan_reg = DMAX_CHAN(channel);

    return chan_reg->STATUS_LO;
}

static inline void DMAX_setSourceReq(u8 channel, DMAXSWHSReqType type)
{
    DMAX_CHAN_REG *chan_reg = DMAX_CHAN(channel);

    if (type == DMAX_SWHS_REQ)
    {
        chan_reg->SWHSSRC_LO_BITS.SWHS_REQ_SRC_EN = 1;
        chan_reg->SWHSSRC_LO_BITS.SWHS_REQ_SRC    = 1;
    }
    else if (type == DMAX_SWHS_SINGLE)
    {
        chan_reg->SWHSSRC_LO_BITS.SWHS_SGLREQ_SRC_WE = 1;
        chan_reg->SWHSSRC_LO_BITS.SWHS_SGLREQ_SRC    = 1;
    }
    else if (type == DMAX_SWHS_LST)
    {
        chan_reg->SWHSSRC_LO_BITS.SWHS_LST_SRC_WE = 1;
        chan_reg->SWHSSRC_LO_BITS.SWHS_LST_SRC    = 1;
    }
}

static inline void DMAX_setDestReq(u8 channel, DMAXSWHSReqType type)
{
    DMAX_CHAN_REG *chan_reg = DMAX_CHAN(channel);

    if (type == DMAX_SWHS_REQ)
    {
        chan_reg->SWHSDST_LO_BITS.SWHS_REQ_DST_EN = 1;
        chan_reg->SWHSDST_LO_BITS.SWHS_REQ_DST    = 1;
    }
    else if (type == DMAX_SWHS_SINGLE)
    {
        chan_reg->SWHSDST_LO_BITS.SWHS_SGLREQ_DST_WE = 1;
        chan_reg->SWHSDST_LO_BITS.SWHS_SGLREQ_DST    = 1;
    }
    else if (type == DMAX_SWHS_LST)
    {
        chan_reg->SWHSDST_LO_BITS.SWHS_LST_DST_WE = 1;
        chan_reg->SWHSDST_LO_BITS.SWHS_LST_DST    = 1;
    }
}

static inline u32 DMAX_getChanIntStatus(u8 channel)
{
    DMAX_CHAN_REG *chan_reg = DMAX_CHAN(channel);

    return chan_reg->INTSTATUS_LO;
}

static inline void DMAX_enableChanIRQStatus(u8 channel, u32 flag)
{
    u32 status;
    DMAX_CHAN_REG *chan_reg = DMAX_CHAN(channel);

    status                    = chan_reg->INTSTATUS_EN_LO;
    status                    = status | flag;
    chan_reg->INTSTATUS_EN_LO = status;
}

static inline void DMAX_setChanIRQSignal(u8 channel, u32 flag)
{
    u32 status;
    DMAX_CHAN_REG *chan_reg = DMAX_CHAN(channel);

    status                    = chan_reg->INTSIGNAL_EN_LO;
    status                    = status | flag;
    chan_reg->INTSIGNAL_EN_LO = status;
}

static inline void DMAX_clearChanIntStatus(u8 channel, u32 flag)
{
    DMAX_CHAN_REG *chan_reg = DMAX_CHAN(channel);

    chan_reg->INTCLEAR_LO = flag;
}

void DMAX_chanSetup(DMAXChanConfig *config);
void DMAX_interrupt(void);
void DMAX_commonInit(void);

#ifdef __cplusplus
}
#endif

#endif
