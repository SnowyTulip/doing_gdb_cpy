/**
 **************************************************************************
 * @file     qx_pmbus.h
 * @version  v1.0.0
 * @date     2023-12-30
 **************************************************************************
 */

#ifndef QX_PMBUS_H
#define QX_PMBUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"

typedef struct
{
    vu32 MASTER_MODE                   : 1; /* [0] */
    vu32 SPEED                         : 2; /* [2:1] */
    vu32 IC_10BITADDR_SLAVE            : 1; /* [3] */
    vu32 IC_10BITADDR_MASTER           : 1; /* [4] */
    vu32 IC_RESTART_EN                 : 1; /* [5] */
    vu32 IC_SLAVE_DISABLE              : 1; /* [6] */
    vu32 STOP_DET_IFADDRESSED          : 1; /* [7] */
    vu32 TX_EMPTY_CTRL                 : 1; /* [8] */
    vu32 RX_FIFO_FULL_HLD_CTRL         : 1; /* [9] */
    vu32 STOP_DET_IF_MASTER_ACTIVE     : 1; /* [10] */
    vu32 BUS_CLEAR_FEATURE_CTRL        : 1; /* [11] */
    vu32 RSVD_IC_CON_1                 : 4; /* [15:12] */
    vu32 OPTIONAL_SAR_CTRL             : 1; /* [16] */
    vu32 SMBUS_SLAVE_QUICK_EN          : 1; /* [17] */
    vu32 SMBUS_ARP_EN                  : 1; /* [18] */
    vu32 SMBUS_PERSISTENT_SLV_ADDR_EN  : 1; /* [19] */
    vu32 SMBUS_PERSISTENT_SLV_ADDR2_EN : 1; /* [20] */
    vu32 SMBUS_PERSISTENT_SLV_ADDR3_EN : 1; /* [21] */
    vu32 SMBUS_PERSISTENT_SLV_ADDR4_EN : 1; /* [22] */
    vu32 IC_SAR2_SMBUS_ARP_EN          : 1; /* [23] */
    vu32 IC_SAR3_SMBUS_ARP_EN          : 1; /* [24] */
    vu32 IC_SAR4_SMBUS_ARP_EN          : 1; /* [25] */
    vu32 RSVD_IC_CON_2                 : 1; /* [31:26] */
} PMB_CON_BIT;

union PMB_CON_REG
{
    vu32 all;
    PMB_CON_BIT bit;
};

typedef struct
{
    vu32 TAR                 : 10; /* [9:0] */
    vu32 GC_OR_START         : 1;  /* [10] */
    vu32 SPECIAL             : 1;  /* [11] */
    vu32 IC_10BITADDR_MASTER : 1;  /* [12] */
    vu32 Device_ID           : 1;  /* [13] */
    vu32 RSVD_IC_TAR_1       : 2;  /* [15:14] */
    vu32 SMBUS_QUICK_CMD     : 1;  /* [16] */
    vu32 RSVD_IC_TAR_2       : 15; /* [31:17] */
} PMB_TAR_BIT;

union PMB_TAR_REG
{
    vu32 all;
    PMB_TAR_BIT bit;
};

typedef struct
{
    vu32 IC_SAR   : 10; /* [9:0] */
    vu32 Reserved : 22; /* [31:10] */
} PMB_SAR_BIT;

union PMB_SAR_REG
{
    vu32 all;
    PMB_SAR_BIT bit;
};

typedef struct
{
    vu32 DATA            : 8;  /* [7:0] */
    vu32 CMD             : 1;  /* [8] */
    vu32 STOP            : 1;  /* [9] */
    vu32 RESTART         : 1;  /* [10] */
    vu32 FIRST_DATA_BYTE : 1;  /* [11] */
    vu32 Reserved        : 20; /* [31:12] */
} PMB_DATA_CMD_BIT;

union PMB_DATA_CMD_REG
{
    vu32 all;
    PMB_DATA_CMD_BIT bit;
};

typedef struct
{
    vu32 SS_SCL_HCNT : 16; /* [15:0] */
    vu32 Reserved    : 16; /* [31:16] */
} SS_SCL_HCNT_BIT;

union SS_SCL_HCNT_REG
{
    vu32 all;
    SS_SCL_HCNT_BIT bit;
};

typedef struct
{
    vu32 SS_SCL_LCNT : 16; /* [15:0] */
    vu32 Reserved    : 16; /* [31:16] */
} SS_SCL_LCNT_BIT;

union SS_SCL_LCNT_REG
{
    vu32 all;
    SS_SCL_LCNT_BIT bit;
};

typedef struct
{
    vu32 FS_SCL_HCNT : 16; /* [15:0] */
    vu32 Reserved    : 16; /* [31:16] */
} FS_SCL_HCNT_BIT;

union FS_SCL_HCNT_REG
{
    vu32 all;
    FS_SCL_HCNT_BIT bit;
};

typedef struct
{
    vu32 FS_SCL_LCNT : 16; /* [15:0] */
    vu32 Reserved    : 16; /* [31:16] */
} FS_SCL_LCNT_BIT;

union FS_SCL_LCNT_REG
{
    vu32 all;
    FS_SCL_LCNT_BIT bit;
};

typedef struct
{
    vu32 R_RX_UNDER         : 1;  /* [0] */
    vu32 R_RX_OVER          : 1;  /* [1] */
    vu32 R_RX_FULL          : 1;  /* [2] */
    vu32 R_TX_OVER          : 1;  /* [3] */
    vu32 R_TX_EMPTY         : 1;  /* [4] */
    vu32 R_RD_REQ           : 1;  /* [5] */
    vu32 R_TX_ABRT          : 1;  /* [6] */
    vu32 R_RX_DONE          : 1;  /* [7] */
    vu32 R_ACTIVITY         : 1;  /* [8] */
    vu32 R_STOP_DET         : 1;  /* [9] */
    vu32 R_START_DET        : 1;  /* [10] */
    vu32 R_GEN_CALL         : 1;  /* [11] */
    vu32 R_RESTART_DET      : 1;  /* [12] */
    vu32 R_MST_ON_HOLD      : 1;  /* [13] */
    vu32 R_SCL_STUCK_AT_LOW : 1;  /* [14] */
    vu32 R_WR_REQ           : 1;  /* [15] */
    vu32 R_SLV_ADDR1_TAG    : 1;  /* [16] */
    vu32 R_SLV_ADDR2_TAG    : 1;  /* [17] */
    vu32 R_SLV_ADDR3_TAG    : 1;  /* [18] */
    vu32 R_SLV_ADDR4_TAG    : 1;  /* [19] */
    vu32 Reserved           : 12; /* [31:20 */
} PMB_INTR_STAT_BIT;

union PMB_INTR_STAT_REG
{
    vu32 all;
    PMB_INTR_STAT_BIT bit;
};

typedef struct
{
    vu32 R_RX_UNDER         : 1;  /* [0] */
    vu32 R_RX_OVER          : 1;  /* [1] */
    vu32 R_RX_FULL          : 1;  /* [2] */
    vu32 R_TX_OVER          : 1;  /* [3] */
    vu32 R_TX_EMPTY         : 1;  /* [4] */
    vu32 R_RD_REQ           : 1;  /* [5] */
    vu32 R_TX_ABRT          : 1;  /* [6] */
    vu32 R_RX_DONE          : 1;  /* [7] */
    vu32 R_ACTIVITY         : 1;  /* [8] */
    vu32 R_STOP_DET         : 1;  /* [9] */
    vu32 R_START_DET        : 1;  /* [10] */
    vu32 R_GEN_CALL         : 1;  /* [11] */
    vu32 R_RESTART_DET      : 1;  /* [12] */
    vu32 R_MST_ON_HOLD      : 1;  /* [13] */
    vu32 R_SCL_STUCK_AT_LOW : 1;  /* [14] */
    vu32 R_WR_REQ           : 1;  /* [15] */
    vu32 R_SLV_ADDR1_TAG    : 1;  /* [16] */
    vu32 R_SLV_ADDR2_TAG    : 1;  /* [17] */
    vu32 R_SLV_ADDR3_TAG    : 1;  /* [18] */
    vu32 R_SLV_ADDR4_TAG    : 1;  /* [19] */
    vu32 Reserved           : 12; /* [31:20 */
} PMB_INTR_MASK_BIT;

union PMB_INTR_MASK_REG
{
    vu32 all;
    PMB_INTR_MASK_BIT bit;
};

typedef struct
{
    vu32 R_RX_UNDER         : 1;  /* [0] */
    vu32 R_RX_OVER          : 1;  /* [1] */
    vu32 R_RX_FULL          : 1;  /* [2] */
    vu32 R_TX_OVER          : 1;  /* [3] */
    vu32 R_TX_EMPTY         : 1;  /* [4] */
    vu32 R_RD_REQ           : 1;  /* [5] */
    vu32 R_TX_ABRT          : 1;  /* [6] */
    vu32 R_RX_DONE          : 1;  /* [7] */
    vu32 R_ACTIVITY         : 1;  /* [8] */
    vu32 R_STOP_DET         : 1;  /* [9] */
    vu32 R_START_DET        : 1;  /* [10] */
    vu32 R_GEN_CALL         : 1;  /* [11] */
    vu32 R_RESTART_DET      : 1;  /* [12] */
    vu32 R_MST_ON_HOLD      : 1;  /* [13] */
    vu32 R_SCL_STUCK_AT_LOW : 1;  /* [14] */
    vu32 R_WR_REQ           : 1;  /* [15] */
    vu32 R_SLV_ADDR1_TAG    : 1;  /* [16] */
    vu32 R_SLV_ADDR2_TAG    : 1;  /* [17] */
    vu32 R_SLV_ADDR3_TAG    : 1;  /* [18] */
    vu32 R_SLV_ADDR4_TAG    : 1;  /* [19] */
    vu32 Reserved           : 12; /* [31:20 */
} PMB_RAW_INTR_STAT_BIT;

union PMB_RAW_INTR_STAT_REG
{
    vu32 all;
    PMB_RAW_INTR_STAT_BIT bit;
};

typedef struct
{
    vu32 RX_TL    : 8;  /* [7:0] */
    vu32 Reserved : 24; /* [31:8] */
} PMB_RX_TL_BIT;

union PMB_RX_TL_REG
{
    vu32 all;
    PMB_RX_TL_BIT bit;
};

typedef struct
{
    vu32 TX_TL    : 8;  /* [7:0] */
    vu32 Reserved : 24; /* [31:8] */
} PMB_TX_TL_BIT;

union PMB_TX_TL_REG
{
    vu32 all;
    PMB_TX_TL_BIT bit;
};

typedef struct
{
    vu32 ENABLE                    : 1;  /* [0] */
    vu32 ABORT                     : 1;  /* [1] */
    vu32 TX_CMD_BLOCK              : 1;  /* [2] */
    vu32 SDA_STUCK_RECOVERY_ENABLE : 1;  /* [3] */
    vu32 Reserved1                 : 12; /* [15:4] */
    vu32 SMBUS_CLK_RESET           : 1;  /* [16] */
    vu32 SMBUS_SUSPEND_EN          : 1;  /* [17] */
    vu32 SMBUS_ALERT_EN            : 1;  /* [18] */
    vu32 IC_SAR_EN                 : 1;  /* [19] */
    vu32 IC_SAR2_EN                : 1;  /* [20] */
    vu32 IC_SAR3_EN                : 1;  /* [21] */
    vu32 IC_SAR4_EN                : 1;  /* [22] */
    vu32 Reserved2                 : 9;  /* [31:23] */
} PMB_ENABLE_BIT;

union PMB_ENABLE_REG
{
    vu32 all;
    PMB_ENABLE_BIT bit;
};

typedef struct
{
    vu32 ACTIVITY                     : 1; /* [0] */
    vu32 TFNF                         : 1; /* [1] */
    vu32 TFE                          : 1; /* [2] */
    vu32 RFNE                         : 1; /* [3] */
    vu32 RFF                          : 1; /* [4] */
    vu32 MST_ACTIVITY                 : 1; /* [5] */
    vu32 SLV_ACTIVITY                 : 1; /* [6] */
    vu32 MST_HOLD_TX_FIFO_EMPTY       : 1; /* [7] */
    vu32 MST_HOLD_RX_FIFO_FULL        : 1; /* [8] */
    vu32 SLV_HOLD_TX_FIFO_EMPTY       : 1; /* [9] */
    vu32 SLV_HOLD_RX_FIFO_FULL        : 1; /* [10] */
    vu32 SDA_STUCK_NOT_RECOVERED      : 1; /* [11] */
    vu32 SLV_ISO_SAR_DATA_CLK_STRETCH : 1; /* [12] */
    vu32 Reserved1                    : 3; /* [15:13] */
    vu32 SMBUS_QUICK_CMD_BIT          : 1; /* [16] */
    vu32 SMBUS_SLAVE_ADDR_VALID       : 1; /* [17] */
    vu32 SMBUS_SLAVE_ADDR_RESOLVED    : 1; /* [18] */
    vu32 SMBUS_SUSPEND_STATUS         : 1; /* [19] */
    vu32 SMBUS_ALERT_STATUS           : 1; /* [20] */
    vu32 SMBUS_SLAVE_ADDR2_VALID      : 1; /* [21] */
    vu32 SMBUS_SLAVE_ADDR2_RESOLVED   : 1; /* [22] */
    vu32 SMBUS_SLAVE_ADDR3_VALID      : 1; /* [23] */
    vu32 SMBUS_SLAVE_ADDR3_RESOLVED   : 1; /* [24] */
    vu32 SMBUS_SLAVE_ADDR4_VALID      : 1; /* [25] */
    vu32 SMBUS_SLAVE_ADDR4_RESOLVED   : 1; /* [26] */
    vu32 Reserved2                    : 5; /* [31:27] */
} PMB_STATUS_BIT;

union PMB_STATUS_REG
{
    vu32 all;
    PMB_STATUS_BIT bit;
};

typedef struct
{
    vu32 IC_SDA_TX_HOLD : 16; /* [15:0] */
    vu32 IC_SDA_RX_HOLD : 8;  /* [23:16] */
    vu32 Reserved       : 8;  /* [31:24] */
} PMB_SDA_HOLD_BIT;

union PMB_SDA_HOLD_REG
{
    vu32 all;
    PMB_SDA_HOLD_BIT bit;
};

typedef struct
{
    vu32 ABRT_7B_ADDR_NOACK        : 1; /* [0] */
    vu32 ABRT_10ADDR1_NOACK        : 1; /* [1] */
    vu32 ABRT_10ADDR2_NOACK        : 1; /* [2] */
    vu32 ABRT_TXDATA_NOACK         : 1; /* [3] */
    vu32 ABRT_GCALL_NOACK          : 1; /* [4] */
    vu32 ABRT_GCALL_READ           : 1; /* [5] */
    vu32 ABRT_HS_ACKDET            : 1; /* [6] */
    vu32 ABRT_SBYTE_ACKDET         : 1; /* [7] */
    vu32 ABRT_HS_NORSTRT           : 1; /* [8] */
    vu32 ABRT_SBYTE_NORSTRT        : 1; /* [9] */
    vu32 ABRT_10B_RD_NORSTRT       : 1; /* [10] */
    vu32 ABRT_MASTER_DIS           : 1; /* [11] */
    vu32 ARB_LOST                  : 1; /* [12] */
    vu32 ABRT_SLVFLUSH_TXFIFO      : 1; /* [13] */
    vu32 ABRT_SLV_ARBLOST          : 1; /* [14] */
    vu32 ABRT_SLVRD_INTX           : 1; /* [15] */
    vu32 ABRT_USER_ABRT            : 1; /* [16] */
    vu32 ABRT_SDA_STUCK_AT_LOW     : 1; /* [17] */
    vu32 ABRT_DEVICE_NOACK         : 1; /* [18] */
    vu32 ABRT_DEVICE_SLVADDR_NOACK : 1; /* [19] */
    vu32 ABRT_DEVICE_WRITE         : 1; /* [20] */
    vu32 RSVD_IC_TX_ABRT_SOURCE    : 2; /* [22:21] */
    vu32 TX_FLUSH_CNT              : 2; /* [24:23] */
} PMB_TX_ABRT_SOURCE_BIT;

union PMB_TX_ABRT_SOURCE_REG
{
    vu32 all;
    PMB_TX_ABRT_SOURCE_BIT bit;
};

typedef struct
{
    vu32 RDMAE    : 1;  /* [0] */
    vu32 TDMAE    : 1;  /* [1] */
    vu32 Reserved : 30; /* [31:2] */
} PMB_DMA_CR_BIT;

union PMB_DMA_CR_REG
{
    vu32 all;
    PMB_DMA_CR_BIT bit;
};

typedef struct
{
    vu32 SDA_SETUP : 8;  /* [7:0] */
    vu32 Reserved  : 24; /* [31:8] */
} PMB_SDA_SETUP_BIT;

union PMB_SDA_SETUP_REG
{
    vu32 all;
    PMB_SDA_SETUP_BIT bit;
};

typedef struct
{
    vu32 UFM_SPKLEN : 8;  /* [7:0] */
    vu32 Reserved  : 24;  /* [31:8] */
} PMB_UFM_SPKLEN_BIT;

union PMB_UFM_SPKLEN_REG
{
    vu32 all;
    PMB_UFM_SPKLEN_BIT bit;
};

typedef struct
{
    vu32 HS_SPKLEN : 8;  /* [7:0] */
    vu32 Reserved  : 24; /* [31:8] */
} PMB_HS_SPKLEN_BIT;

union PMB_HS_SPKLEN_REG
{
    vu32 all;
    PMB_HS_SPKLEN_BIT bit;
};

typedef struct
{
    vu32 CLR_RESTART_DET : 1;   /* [0] */
    vu32 Reserved        : 31;  /* [31:1] */
} PMB_CLR_RESTART_DET_BIT;

union PMB_CLR_RESTART_DET_REG
{
    vu32 all;
    PMB_CLR_RESTART_DET_BIT bit;
};


typedef struct
{
    vu32 SCL_STUCK_LOW_TIMEOUT        : 32;  /* [31:0] */
} PMB_SCL_STUCK_AT_LOW_TIMEOUT_BIT;

union PMB_SCL_STUCK_AT_LOW_TIMEOUT_REG
{
    vu32 all;
    PMB_SCL_STUCK_AT_LOW_TIMEOUT_BIT bit;
};

typedef struct
{
    vu32 SDA_STUCK_LOW_TIMEOUT        : 32;  /* [31:0] */
} PMB_SDA_STUCK_AT_LOW_TIMEOUT_BIT;

union PMB_SDA_STUCK_AT_LOW_TIMEOUT_REG
{
    vu32 all;
    PMB_SDA_STUCK_AT_LOW_TIMEOUT_BIT bit;
};

typedef struct
{
    vu32 CLR_SCL_STUCK_DET : 1;   /* [0] */
    vu32 Reserved        : 31;  /* [31:1] */
} PMB_CLR_SCL_STUCK_DET_BIT;

union PMB_CLR_SCL_STUCK_DET_REG
{
    vu32 all;
    PMB_CLR_SCL_STUCK_DET_BIT bit;
};

typedef struct
{
    vu32 DEVICE_ID : 24; /* [23:0] */
    vu32 Reserved  : 8;  /* [31:24] */
} PMB_DEVICE_ID_BIT;

union PMB_DEVICE_ID_REG
{
    vu32 all;
    PMB_DEVICE_ID_BIT bit;
};


typedef struct
{
    vu32  SMBUS_CLK_LOW_SEXT_TIMEOUT        : 32;  /* [31:0] */
} PMB_SMBUS_CLK_LOW_SEXT_BIT;

union PMB_SMBUS_CLK_LOW_SEXT_REG
{
    vu32 all;
    PMB_SMBUS_CLK_LOW_SEXT_BIT bit;
};

typedef struct
{
    vu32 SMBUS_CLK_LOW_MEXT_TIMEOUT        : 32;  /* [31:0] */
} PMB_SMBUS_CLK_LOW_MEXT_BIT;

union PMB_SMBUS_CLK_LOW_MEXT_REG
{
    vu32 all;
    PMB_SMBUS_CLK_LOW_MEXT_BIT bit;
};


typedef struct
{
    vu32 SMBUS_THIGH_MAX_BUS_IDLE_CNT : 16; /* [15:0] */
    vu32 Reserved                     : 16; /* [31:16] */
} SMBUS_THIGH_MAX_BUS_IDLE_CNT_BIT;

union SMBUS_THIGH_MAX_BUS_IDLE_CNT_REG
{
    vu32 all;
    SMBUS_THIGH_MAX_BUS_IDLE_CNT_BIT bit;
};

typedef struct
{
    vu32 SLV_CLOCK_EXTND_TIMEOUT : 1;  /* [0] */
    vu32 MST_CLOCK_EXTND_TIMEOUT : 1;  /* [1] */
    vu32 QUICK_CMD_DET           : 1;  /* [2] */
    vu32 HOST_NOTIFY_MST_DET     : 1;  /* [3] */
    vu32 ARP_PREPARE_CMD_DET     : 1;  /* [4] */
    vu32 ARP_RST_CMD_DET         : 1;  /* [5] */
    vu32 ARP_GET_UDID_CMD_DET    : 1;  /* [6] */
    vu32 ARP_ASSGN_ADDR_CMD_DET  : 1;  /* [7] */
    vu32 SLV_RX_PEC_NACK         : 1;  /* [8] */
    vu32 SMBUS_SUSPEND_DET       : 1;  /* [9] */
    vu32 SMBUS_ALERT_DET         : 1;  /* [10] */
    vu32 Reserved                : 21; /* [31:11] */
} SMBUS_INTR_STAT_BIT;

union SMBUS_INTR_STAT_REG
{
    vu32 all;
    SMBUS_INTR_STAT_BIT bit;
};

typedef struct
{
    vu32 SLV_CLOCK_EXTND_TIMEOUT : 1;  /* [0] */
    vu32 MST_CLOCK_EXTND_TIMEOUT : 1;  /* [1] */
    vu32 QUICK_CMD_DET           : 1;  /* [2] */
    vu32 HOST_NOTIFY_MST_DET     : 1;  /* [3] */
    vu32 ARP_PREPARE_CMD_DET     : 1;  /* [4] */
    vu32 ARP_RST_CMD_DET         : 1;  /* [5] */
    vu32 ARP_GET_UDID_CMD_DET    : 1;  /* [6] */
    vu32 ARP_ASSGN_ADDR_CMD_DET  : 1;  /* [7] */
    vu32 SLV_RX_PEC_NACK         : 1;  /* [8] */
    vu32 SMBUS_SUSPEND_DET       : 1;  /* [9] */
    vu32 SMBUS_ALERT_DET         : 1;  /* [10] */
    vu32 Reserved                : 21; /* [31:11] */
} SMBUS_INTR_MASK_BIT;

union SMBUS_INTR_MASK_REG
{
    vu32 all;
    SMBUS_INTR_MASK_BIT bit;
};

typedef struct
{
    vu32 SLV_CLOCK_EXTND_TIMEOUT : 1;  /* [0] */
    vu32 MST_CLOCK_EXTND_TIMEOUT : 1;  /* [1] */
    vu32 QUICK_CMD_DET           : 1;  /* [2] */
    vu32 HOST_NOTIFY_MST_DET     : 1;  /* [3] */
    vu32 ARP_PREPARE_CMD_DET     : 1;  /* [4] */
    vu32 ARP_RST_CMD_DET         : 1;  /* [5] */
    vu32 ARP_GET_UDID_CMD_DET    : 1;  /* [6] */
    vu32 ARP_ASSGN_ADDR_CMD_DET  : 1;  /* [7] */
    vu32 SLV_RX_PEC_NACK         : 1;  /* [8] */
    vu32 SMBUS_SUSPEND_DET       : 1;  /* [9] */
    vu32 SMBUS_ALERT_DET         : 1;  /* [10] */
    vu32 Reserved                : 21; /* [31:11] */
} SMBUS_RAW_INTR_STAT_BIT;

union SMBUS_RAW_INTR_STAT_REG
{
    vu32 all;
    SMBUS_RAW_INTR_STAT_BIT bit;
};

typedef struct
{
    vu32 CLR_SLV_CLOCK_EXTND_TIMEOUT : 1;  /* [0] */
    vu32 CLR_MST_CLOCK_EXTND_TIMEOUT : 1;  /* [1] */
    vu32 CLR_QUICK_CMD_DET           : 1;  /* [2] */
    vu32 CLR_HOST_NOTIFY_MST_DET     : 1;  /* [3] */
    vu32 CLR_ARP_PREPARE_CMD_DET     : 1;  /* [4] */
    vu32 CLR_ARP_RST_CMD_DET         : 1;  /* [5] */
    vu32 CLR_ARP_GET_UDID_CMD_DET    : 1;  /* [6] */
    vu32 CLR_ARP_ASSGN_ADDR_CMD_DET  : 1;  /* [7] */
    vu32 CLR_SLV_RX_PEC_NACK         : 1;  /* [8] */
    vu32 CLR_SMBUS_SUSPEND_DET       : 1;  /* [9] */
    vu32 CLR_SMBUS_ALERT_DET         : 1;  /* [10] */
    vu32 Reserved                    : 21; /* [31:11] */
} CLR_SMBUS_INTR_BIT;

union CLR_SMBUS_INTR_REG
{
    vu32 all;
    CLR_SMBUS_INTR_BIT bit;
};

typedef struct
{
    vu32 REG_TIMEOUT_RST_rw : 10; /* [9:0] */
    vu32 REG_TIMEOUT_RST_ro : 10; /* [19:10] */
    vu32 Reserved           : 12; /* [31:20] */
} PMB_REG_TIMEOUT_RST_BIT;

union PMB_REG_TIMEOUT_RST_REG
{
    vu32 all;
    PMB_REG_TIMEOUT_RST_BIT bit;
};

typedef struct
{
    vu32 APB_DATA_WIDTH     : 2; /* [1:0] */
    vu32 MAX_SPEED_MODE     : 2; /* [3:2] */
    vu32 HC_COUNT_VALUES    : 1; /* [4] */
    vu32 INTR_IO            : 1; /* [5] */
    vu32 HAS_DMA            : 1; /* [6] */
    vu32 ADD_ENCODED_PARAMS : 1; /* [7] */
    vu32 RX_BUFFER_DEPTH    : 8; /* [15:8] */
    vu32 TX_BUFFER_DEPTH    : 8; /* [23:16] */
    vu32 Reserved           : 8; /* [31:24] */
} PMB_COMP_PARAM1_BIT;

union PMB_COMP_PARAM1_REG
{
    vu32 all;
    PMB_COMP_PARAM1_BIT bit;
};

struct PMBUS_REGS
{
    union PMB_CON_REG IC_CON;                                             /* offset:0x00 */
    union PMB_TAR_REG IC_TAR;                                             /* offset:0x04 */
    union PMB_SAR_REG IC_SAR;                                             /* offset:0x08 */
    vu32 Reserved1;                                                       /* offset:0x0C */
    union PMB_DATA_CMD_REG IC_DATA_CMD;                                   /* offset:0x10 */
    union SS_SCL_HCNT_REG IC_SS_SCL_HCNT;                                 /* offset:0x14 */
    union SS_SCL_LCNT_REG IC_SS_SCL_LCNT;                                 /* offset:0x18 */
    union FS_SCL_HCNT_REG IC_FS_SCL_HCNT;                                 /* offset:0x1C */
    union FS_SCL_LCNT_REG IC_FS_SCL_LCNT;                                 /* offset:0x20 */
    vu32 Reserved2;                                                       /* offset:0x24 */
    vu32 Reserved3;                                                       /* offset:0x28 */
    union PMB_INTR_STAT_REG IC_INTR_STAT;                                 /* offset:0x2C */
    union PMB_INTR_MASK_REG IC_INTR_MASK;                                 /* offset:0x30 */
    union PMB_RAW_INTR_STAT_REG IC_RAW_INTR_STAT;                         /* offset:0x34 */
    union PMB_RX_TL_REG IC_RX_TL;                                         /* offset:0x38 */
    union PMB_TX_TL_REG IC_TX_TL;                                         /* offset:0x3C */
    vu32 CLR_INTR;                                                        /* offset:0x40 */
    vu32 CLR_RX_UNDER;                                                    /* offset:0x44 */
    vu32 CLR_RX_OVER;                                                     /* offset:0x48 */
    vu32 CLR_TX_OVER;                                                     /* offset:0x4C */
    vu32 CLR_RD_REQ;                                                      /* offset:0x50 */
    vu32 CLR_TX_ABRT;                                                     /* offset:0x54 */
    vu32 CLR_RX_DONE;                                                     /* offset:0x58 */
    vu32 CLR_ACTIVITY;                                                    /* offset:0x5C */
    vu32 CLR_STOP_DET;                                                    /* offset:0x60 */
    vu32 CLR_START_DET;                                                   /* offset:0x64 */
    vu32 CLR_GEN_CALL;                                                    /* offset:0x68 */
    union PMB_ENABLE_REG IC_ENABLE;                                       /* offset:0x6C */
    union PMB_STATUS_REG IC_STATUS;                                       /* offset:0x70 */
    vu32 IC_TXFLR;                                                        /* offset:0x74 */
    vu32 IC_RXFLR;                                                        /* offset:0x78 */
    union PMB_SDA_HOLD_REG IC_SDA_HOLD;                                   /* offset:0x7C */
    union PMB_TX_ABRT_SOURCE_REG IC_TX_ABRT_SOURCE;                       /* offset:0x80 */
    vu32 IC_SLV_DATA_NACK_ONLY;                                           /* offset:0x84 */
    union PMB_DMA_CR_REG IC_DMA_CR;                                       /* offset:0x88 */
    vu32 IC_DMA_TDLR;                                                     /* offset:0x8C */
    vu32 IC_DMA_RDLR;                                                     /* offset:0x90 */
    union PMB_SDA_SETUP_REG IC_SDA_SETUP;                                 /* offset:0x94 */
    vu32 IC_ACK_GENERAL_CALL;                                             /* offset:0x98 */
    vu32 IC_ENABLE_STATUS;                                                /* offset:0x9C */
    union PMB_UFM_SPKLEN_REG IC_UFM_SPKLEN;                               /* offset:0xA0 */
    union PMB_HS_SPKLEN_REG IC_HS_SPKLEN;                                 /* offset:0xA4 */
    union PMB_CLR_RESTART_DET_REG CLR_RESTART_DET;                        /* offset:0xA8 */
    union PMB_SCL_STUCK_AT_LOW_TIMEOUT_REG IC_SCL_STUCK_AT_LOW_TIMEOUT;   /* offset:0xAC */
    union PMB_SDA_STUCK_AT_LOW_TIMEOUT_REG IC_SDA_STUCK_AT_LOW_TIMEOUT;   /* offset:0xB0 */
    union PMB_CLR_SCL_STUCK_DET_REG  IC_CLR_SCL_STUCK_DET;                /* offset:0xB4 */
    union PMB_DEVICE_ID_REG IC_DEVICE_ID;                                 /* offset:0xB8 */
    union PMB_SMBUS_CLK_LOW_SEXT_REG IC_SMBUS_CLK_LOW_SEXT;               /* offset:0xBC */
    union PMB_SMBUS_CLK_LOW_MEXT_REG IC_SMBUS_CLK_LOW_MEXT;               /* offset:0xC0 */
    union SMBUS_THIGH_MAX_BUS_IDLE_CNT_REG IC_SMBUS_THIGH_MAX_IDLE_COUNT; /* offset:0xC4 */
    union SMBUS_INTR_STAT_REG IC_SMBUS_INTR_STAT;                         /* offset:0xC8 */
    union SMBUS_INTR_MASK_REG IC_SMBUS_INTR_MASK;                         /* offset:0xCC */
    union SMBUS_RAW_INTR_STAT_REG IC_SMBUS_RAW_INTR_STAT;                 /* offset:0xd0 */
    union CLR_SMBUS_INTR_REG IC_CLR_SMBUS_INTR;                           /* offset:0xd4 */
    vu32 IC_OPTIONAL_SAR;                                                 /* offset:0xd8 */
    vu32 IC_SMBUS_UDID_LSB;                                               /* offset:0xdc */
    vu32 IC_SMBUS_UDID_WORD1;                                             /* offset:0xe0 */
    vu32 IC_SMBUS_UDID_WORD2;                                             /* offset:0xe4 */
    vu32 IC_SMBUS_UDID_WORD3;                                             /* offset:0xe8 */
    union PMB_REG_TIMEOUT_RST_REG REG_TIMEOUT_RST;                        /* offset:0xf0 */
    union PMB_COMP_PARAM1_REG IC_COMP_PARAM1;                             /* offset:0xf4 */
    vu32 IC_COMP_VERSION;                                                 /* offset:0xf8 */
    vu32 IC_COMP_TYPE;                                                    /* offset:0xfC */
    vu32 IC_SAR2;                                                         /* offset:0x100 */
    vu32 IC_SAR3;                                                         /* offset:0x104 */
    vu32 IC_SAR4;                                                         /* offset:0x108 */
    vu32 Reserved_0x10c;                                                  /* offset:0x10c */
    vu32 Reserved_0x110;                                                  /* offset:0x110 */
    vu32 Reserved_0x114;                                                  /* offset:0x114 */
    vu32 Reserved_0x118;                                                  /* offset:0x118 */
    vu32 CLR_WR_REQ;                                                      /* offset:0x11c */
    vu32 CLR_SLV_ADDR_TAG;                                                /* offset:0x120 */
    vu32 IC_SAR2_SMBUS_UDID_WORD0;                                        /* offset:0x124 */
    vu32 IC_SAR2_SMBUS_UDID_WORD1;                                        /* offset:0x128 */
    vu32 IC_SAR2_SMBUS_UDID_WORD2;                                        /* offset:0x12C */
    vu32 IC_SAR2_SMBUS_UDID_WORD3;                                        /* offset:0x130 */
    vu32 IC_SAR3_SMBUS_UDID_WORD0;                                        /* offset:0x134 */
    vu32 IC_SAR3_SMBUS_UDID_WORD1;                                        /* offset:0x138 */
    vu32 IC_SAR3_SMBUS_UDID_WORD2;                                        /* offset:0x13C */
    vu32 IC_SAR3_SMBUS_UDID_WORD3;                                        /* offset:0x140 */
    vu32 IC_SAR4_SMBUS_UDID_WORD0;                                        /* offset:0x144 */
    vu32 IC_SAR4_SMBUS_UDID_WORD1;                                        /* offset:0x148 */
    vu32 IC_SAR4_SMBUS_UDID_WORD2;                                        /* offset:0x14C */
    vu32 IC_SAR4_SMBUS_UDID_WORD3;                                        /* offset:0x150 */
};

#define PmbusaRegs1 ((struct PMBUS_REGS *)I2CA_BASE)
#define PmbusaRegs2 ((struct PMBUS_REGS *)PMBUS_BASE)

#define PMBUS_INT_ALL 0x000007FFUL

#define PMBUS_O_PMBINTM   0xCC
#define PMBUS_O_PMBSTS    0x70
#define PMBUS_O_PMBENABLE 0x6C
#define PMBUS_O_PMBSAR    0x08
#define PMBUS_O_PMBTAR    0x04

#define PMBUS_PMBSTS_BUS_FREE 0x0001U // PMBus Free Indicator

#define PMBUS_PMBENABLE_ALERT_EN 0x40000U

//*****************************************************************************
//
//! Clock Mode Descriptor
//!
//! Used in PMBus_configBusClock() to set up the bus speed. There are two
//! possible modes of operation:
//! -# Standard Mode 100 kHz
//! -# Fast Mode 400 kHz
//
//*****************************************************************************
typedef enum
{
    PMBUS_CLOCKMODE_STANDARD = 0U, //!< Standard mode 100 kHz
    PMBUS_CLOCKMODE_FAST     = 1U  //!< Fast Mode 400 kHz
} PMBus_ClockMode;

//*****************************************************************************
//
// PCBCCR Commands -> used in PMBus_configControlleer()
//
//*****************************************************************************

//*****************************************************************************
//
//! Disables the PMBus module.
//!
//! \param base is the base address of the PMBus instance used.
//!
//! This function resets the internal state machine of the PMBus module and
//! holds it in that state
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    EALLOW;
    PmbusaRegs2->IC_ENABLE.bit.ENABLE = 0;
    HWREG(base + PMBUS_O_PMBENABLE) &= ~(0x1U);
    EDIS;
}

//*****************************************************************************
//
//! Enables the PMBus module.
//!
//! \param base is the base address of the PMBus instance used.
//!
//! This function enables operation of the PMBus module by removing it from the
//! reset state
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    EALLOW;
    PmbusaRegs2->IC_ENABLE.bit.ENABLE |= 0x01;
    EDIS;
}

//*****************************************************************************
//
//! Enables PMBus interrupt sources.
//!
//! \param base is the base address of the PMBus instance used.
//! \param intFlags is the bit mask of the interrupt sources to be enabled.
//!
//! This function enables the indicated PMBus interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.
//!
//! The \e intFlags parameter is the logical OR of any of the following:
//!
//! - \b PMBUS_INT_BUS_FREE          - Bus Free Interrupt
//! - \b PMBUS_INT_CLK_LOW_TIMEOUT   - Clock Low Time-out Interrupt
//! - \b PMBUS_INT_DATA_READY        - Data Ready Interrupt
//! - \b PMBUS_INT_DATA_REQUEST      - Data Request Interrupt
//! - \b PMBUS_INT_TARGET_ADDR_READY  - Target Address Ready Interrupt
//! - \b PMBUS_INT_EOM               - End of Message Interrupt
//! - \b PMBUS_INT_ALERT             - Alert Detection Interrupt
//! - \b PMBUS_INT_CONTROL           - Control Detection Interrupt
//! - \b PMBUS_INT_LOST_ARB          - Lost Arbitration Interrupt
//! - \b PMBUS_INT_CLK_HIGH_DETECT   - Clock High Detection Interrupt
//! - \b PMBUS_INT_ALL               - all PMBus interrupts
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_enableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    EALLOW;

    //
    // Enable the desired basic interrupts, that is, clear their mask bits
    // in PMBINTM
    //
    HWREG(base + PMBUS_O_PMBINTM) &= ~(intFlags & 0x07FFU);
    EDIS;
}

//*****************************************************************************
//
//! Disables PMBus interrupt sources.
//!
//! \param base is the base address of the PMBus instance used.
//! \param intFlags is the bit mask of the interrupt sources to be disabled.
//!
//! This function disables the indicated PMBus interrupt sources.  Only
//! the sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.
//!
//! The \e intFlags parameter has the same definition as the \e intFlags
//! parameter to PMBus_enableInterrupt().
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_disableInterrupt(uint32_t base, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    EALLOW;

    //
    // Disable the desired interrupts
    //
    HWREG(base + PMBUS_O_PMBINTM) |= (intFlags & 0x07FFU);
    EDIS;
}

//*****************************************************************************
//
//! Indicates whether or not the PMBus bus is busy.
//!
//! \param status  the value of the status register (PMBUS_O_PMBSTS)
//!
//! This function returns an indication of whether or not the PMBus bus is busy
//!
//! \note The status register is cleared each time it is read, therefore, it
//! should be read once at the beginning of an interrupt service routine using
//! PMBus_getInterruptStatus() and saved to a temporary variable for further
//! processing.
//!
//! \return Returns \b true if the PMBus bus is busy; otherwise, returns
//! \b false.
//
//*****************************************************************************
static inline bool PMBus_isBusBusy(uint32_t status)
{
    return (((status & PMBUS_PMBSTS_BUS_FREE) == 0U) ? true : false);
}

//*****************************************************************************
//
//! Enable I2C mode
//!
//! \param base is the base address of the PMBus instance used.
//!
//! Set the PMBus module to work in I2C mode
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_enableI2CMode(uint32_t base)
{
    //
    // Locals
    //
    uint32_t interruptState;

    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    EALLOW;

    //
    // Save off the interrupt state and disable them
    //
    interruptState                = HWREG(base + PMBUS_O_PMBINTM);
    HWREG(base + PMBUS_O_PMBINTM) = PMBUS_INT_ALL;

    EDIS;
}

//*****************************************************************************
//
//! Disable I2C mode
//!
//! \param base is the base address of the PMBus instance used.
//!
//! Set the PMBus module to work in PMBus mode
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_disableI2CMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    EALLOW;

    EDIS;
}

//*****************************************************************************
//
//! Read the status register
//!
//! \param base is the base address of the PMBus instance used.
//!
//! \return Contents of the status register.
//
//*****************************************************************************
static inline uint32_t PMBus_getStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    return (HWREG(base + PMBUS_O_PMBSTS));
}

//*****************************************************************************
//
//! Acknowledge the transaction by writing to the PMBACK register
//!
//! \param base is the base address of the PMBus instance used.
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_ackTransaction(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    //
    // Acknowledge
    //
    //    HWREG(base + PMBUS_O_PMBACK) |= PMBUS_PMBACK_ACK;
}

//*****************************************************************************
//
//! Nack the transaction by writing to the PMBACK register
//!
//! \param base is the base address of the PMBus instance used.
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_nackTransaction(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    //
    // NACK
    //
    //    HWREG(base + PMBUS_O_PMBACK) &= ~(uint32_t)PMBUS_PMBACK_ACK;
}

//*****************************************************************************
//
//! Alert the controller by asserting the ALERT line
//!
//! \param base is the base address of the PMBus instance used.
//!
//! A target PMBus can alert the controller by pulling the alert line low.
//! This triggers an Alert Response from the controller`, where the ,controller issues
//! the \b Alert \b Response \b Address on the bus with a read bit and the
//! alerting target is required to reply with its address.
//!
//! \note The alerting device should be in target mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_assertAlertLine(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    EALLOW;

    //
    // Pull the alert line low
    //
    HWREG(base + PMBUS_O_PMBENABLE) |= PMBUS_PMBENABLE_ALERT_EN;

    EDIS;
}

//*****************************************************************************
//
//! De-assert the alert line
//!
//! \param base is the base address of the PMBus instance used.
//!
//! \return None.
//
//*****************************************************************************
static inline void PMBus_deassertAlertLine(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    EALLOW;

    //
    // Pull the alert line low

    //
    HWREG(base + PMBUS_O_PMBENABLE) &= ~(uint32_t)PMBUS_PMBENABLE_ALERT_EN;

    EDIS;
}

//*****************************************************************************
//
//! Get the address that the PMBus module will respond to (in target mode)
//!
//! \param base is the base address of the PMBus instance used.
//!
//! This function will query the PMBUS_O_PMBHTA register, this
//! will be the address of the module when used in Target Mode.
//! \return Address of the PMBus device (in slave mode).
//
//*****************************************************************************
static inline uint16_t PMBus_getOwnAddress(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));

    return (HWREG(base + PMBUS_O_PMBSAR) & 0x3FFU);
}

//*****************************************************************************
//
//! Set the current device address
//!
//! \param base is the base address of the PMBus instance used.
//! \param address : Address to be configured.
//!
//! This function configures the current device address, this
//! will be the own address of the module.
//! \return None.
//
//*****************************************************************************
static inline void PMBus_setOwnAddress(uint32_t base, uint16_t Ownaddress)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    ASSERT(Ownaddress <= 0x3FFU);

    EALLOW;

    //
    // Write the address to the PMBSC register (bits 6:0)
    //
    HWREG(base + PMBUS_O_PMBSAR) = (Ownaddress & 0x3FF);

    EDIS;
}

//*****************************************************************************
//
//! Set the target address
//!
//! \param base is the base address of the PMBus instance used.
//! \param address : Target Address to be configured.
//!
//! This function configures the current device address, this
//! will be the target address.
//! \return None.
//
//*****************************************************************************
static inline void PMBus_setTargetAddress(uint32_t base, uint16_t targetAddress)
{
    //
    // Check the arguments.
    //
    ASSERT(PMBus_isBaseValid(base));
    ASSERT(targetAddress <= 0x3FFU);

    EALLOW;

    //
    // Write the target address to PMBMC register
    //
    HWREG(base + PMBUS_O_PMBTAR) |= ((uint32_t)targetAddress & 0x3ff);
    EDIS;
}

#ifdef __cplusplus
}
#endif
#endif
