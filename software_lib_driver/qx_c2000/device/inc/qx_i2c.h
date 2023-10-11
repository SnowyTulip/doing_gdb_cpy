/**
 **************************************************************************
 * @file     qx_i2c.h
 * @version  v1.0.0
 * @date     2022-08-30
 * @brief    dw_apb_i2c header file
 **************************************************************************
 */

#ifndef QX_I2C_H
#define QX_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"

struct CON_BITS {
    vu32 MASTER_MODE: 1; /* [0] */
    vu32 SPEED                      : 2;    /* [2:1] */
    vu32 IC_10BITADDR_SLAVE         : 1;    /* [3] */
    vu32 IC_10BITADDR_MASTER        : 1;    /* [4] */
    vu32 IC_RESTART_EN              : 1;    /* [5] */
    vu32 IC_SLAVE_DISABLE           : 1;    /* [6] */
    vu32 STOP_DET_IFADDRESSED       : 1;    /* [7] */
    vu32 TX_EMPTY_CTRL              : 1;    /* [8] */
    vu32 RX_FIFO_FULL_HLD_CTRL      : 1;    /* [9] */
    vu32 STOP_DET_IF_MASTER_ACTIVE  : 1;    /* [10] */
    vu32 BUS_CLEAR_FEATURE_CTRL     : 1;    /* [11] */
    vu32 reserved                   : 20;   /* [31:12] */
};

union IC_CON_REG {
    vu32 all;
    struct CON_BITS bit;
};

struct TAR_BITS {
    vu32 TAR                    : 10;   /* [9:0] */
    vu32 GC_OR_START            : 1;    /* [10] */
    vu32 SPECIAL                : 1;    /* [11] */
    vu32 IC_10BITADDR_MASTER    : 1;    /* [12] */
    vu32 Device_ID              : 1;    /* [13] */
    vu32 Reserved               : 18;   /* [31:14] */
};

union IC_TAR_REG {
    vu32 all;
    struct TAR_BITS bit;
};

struct SAR_BITS {
    vu32 SAR     : 10;   /* [9:0] */
    vu32 Reserved   : 12;   /* [31:10] */
};

union IC_SAR_REG {
    vu32 all;
    struct SAR_BITS bit;
};

struct IC_DATA_CMD_BIT{
    vu32 DATA               : 8;  /* [7:0] */
    vu32 CMD                : 1;  /* [8] */
    vu32 STOP               : 1;  /* [9] */
    vu32 RESTART            : 1;  /* [10] */
    vu32 FIRST_DATA_BYTE    : 1;  /* [11] */
    vu32 Reserved           : 20; /* [31:12] */
};

union IC_DATA_CMD_REG {
    vu32 all;
    struct IC_DATA_CMD_BIT bit;
};


struct SS_SCL_HCNT_BITS {
    vu32 SS_SCL_HCNT    : 16; /* [15:0] */
    vu32 Reserved       : 16; /* [31:16] */
};

union IC_SS_SCL_HCNT_REG {
    vu32 all;
    struct SS_SCL_HCNT_BITS bit;
};

struct SS_SCL_LCNT_BITS {
    vu32 SS_SCL_LCNT    : 16; /* [15:0] */
    vu32 Reserved       : 16; /* [31:16] */
};

union IC_SS_SCL_LCNT_REG {
    vu32 all;
    struct SS_SCL_LCNT_BITS bit;
};

struct FS_SCL_HCNT_BITS {
    vu32 FS_SCL_HCNT : 16; /* [15:0] */
    vu32 Reserved    : 16; /* [31:16] */
};

union IC_FS_SCL_HCNT_REG {
    vu32 all;
    struct FS_SCL_HCNT_BITS bit;
};

struct FS_SCL_LCNT_BITS {
    vu32 FS_SCL_LCNT    : 16; /* [15:0] */
    vu32 Reserved       : 16; /* [31:16] */
};

union IC_FS_SCL_LCNT_REG {
    vu32 all;
    struct FS_SCL_LCNT_BITS bit;
};

struct INTR_STAT_BITS {
    vu32 RX_UNDE            : 1;  /* [0] */
    vu32 RX_OVER            : 1;  /* [1] */
    vu32 RX_FULL            : 1;  /* [2] */
    vu32 TX_OVER            : 1;  /* [3] */
    vu32 TX_EMPTY           : 1;  /* [4] */
    vu32 RD_REQ             : 1;  /* [5] */
    vu32 TX_ABRT            : 1;  /* [6] */
    vu32 RX_DONE            : 1;  /* [7] */
    vu32 ACTIVITY           : 1;  /* [8] */
    vu32 STOP_DET           : 1;  /* [9] */
    vu32 START_DET          : 1;  /* [10] */
    vu32 GEN_CALL           : 1;  /* [11] */
    vu32 RESTART_DET        : 1;  /* [12] */
    vu32 MST_ON_HOLD        : 1;  /* [13] */
    vu32 SCL_STUCK_AT_LOW   : 1;  /* [14] */
    vu32 Reserved           : 17; /* [31:15] */
};

union IC_INTR_STAT_REG {
    vu32 all;
    struct INTR_STAT_BITS bit;
};

struct INTR_MASK_BITS {
    vu32 M_RX_UNDER         : 1;  /* [0] */
    vu32 M_RX_OVER          : 1;  /* [1] */
    vu32 M_RX_FULL          : 1;  /* [2] */
    vu32 M_TX_OVER          : 1;  /* [3] */
    vu32 M_TX_EMPTY         : 1;  /* [4] */
    vu32 M_RD_REQ           : 1;  /* [5] */
    vu32 M_TX_ABRT          : 1;  /* [6] */
    vu32 M_RX_DONE          : 1;  /* [7] */
    vu32 M_ACTIVITY         : 1;  /* [8] */
    vu32 M_STOP_DET         : 1;  /* [9] */
    vu32 M_START_DET        : 1;  /* [10] */
    vu32 M_GEN_CALL         : 1;  /* [11] */
    vu32 M_RESTART_DET      : 1;  /* [12] */
    vu32 M_MST_ON_HOLD      : 1;  /* [13] */
    vu32 M_SCL_STUCK_AT_LOW : 1;  /* [14] */
    vu32 Reserved           : 17; /* [31:15] */
};

union IC_INTR_MASK_REG {
    vu32 all;
    struct INTR_MASK_BITS bit;
};

struct RAW_INTR_STAT_BITS {
    vu32 RX_UNDE            : 1;  /* [0] */
    vu32 RX_OVER            : 1;  /* [1] */
    vu32 RX_FULL            : 1;  /* [2] */
    vu32 TX_OVER            : 1;  /* [3] */
    vu32 TX_EMPTY           : 1;  /* [4] */
    vu32 RD_REQ             : 1;  /* [5] */
    vu32 TX_ABRT            : 1;  /* [6] */
    vu32 RX_DONE            : 1;  /* [7] */
    vu32 ACTIVITY           : 1;  /* [8] */
    vu32 STOP_DET           : 1;  /* [9] */
    vu32 START_DET          : 1;  /* [10] */
    vu32 GEN_CALL           : 1;  /* [11] */
    vu32 RESTART_DET        : 1;  /* [12] */
    vu32 MST_ON_HOLD        : 1;  /* [13] */
    vu32 SCL_STUCK_AT_LOW   : 1;  /* [14] */
    vu32 Reserved           : 17; /* [31:15] */
};

union IC_RAW_INTR_STAT_REG {
    vu32 all;
    struct RAW_INTR_STAT_BITS bit;
};

struct ENABLE_BITS {
    vu32 ENABLE                     : 1;  /* [0] */
    vu32 ABORT                      : 1;  /* [1] */
    vu32 TX_CMD_BLOCK               : 1;  /* [2] */
    vu32 SDA_STUCK_RECOVERY_ENABLE  : 1;  /* [3] */
    vu32 Reserved1                  : 12; /* [15:4] */
    vu32 Reserved2                  : 16; /* [31:16] */
};

union IC_ENABLE_REG {
    vu32 all;
    struct ENABLE_BITS bit;
};

struct IC_STATUS_BITS {
    vu32 ACTIVITY                   : 1;  /* [0] */
    vu32 TFNF                       : 1;  /* [1] */
    vu32 TFE                        : 1;  /* [2] */
    vu32 RFNE                       : 1;  /* [3] */
    vu32 RFF                        : 1;  /* [4] */
    vu32 MST_ACTIVITY               : 1;  /* [5] */
    vu32 SLV_ACTIVITY               : 1;  /* [6] */
    vu32 MST_HOLD_TX_FIFO_EMPTY     : 1;  /* [7] */
    vu32 MST_HOLD_RX_FIFO_FULL      : 1;  /* [8] */
    vu32 SLV_HOLD_TX_FIFO_EMPTY     : 1;  /* [9] */
    vu32 SLV_HOLD_RX_FIFO_FULL      : 1;  /* [10] */
    vu32 SDA_STUCK_NOT_RECOVERED    : 1;  /* [11] */
    vu32 Reserved1                  : 4;  /* [15:12] */
    vu32 Reserved2                  : 16; /* [31:16] */
};

union IC_STATUS_REG {
    vu32 all;
    struct IC_STATUS_BITS bit;
};

struct SDA_HOLD_BITS {
    vu32 IC_SDA_TX_HOLD : 16; /* [15:0] */
    vu32 IC_SDA_RX_HOLD : 8;  /* [23:16] */
    vu32 Reserved       : 8;  /* [31:24] */
};

union IC_SDA_HOLD_REG {
    vu32 all;
    struct SDA_HOLD_BITS bit;
};

struct DMA_CR_BITS {
      vu32 RDMAE    : 1;  /* [0] */
      vu32 TDMAE    : 1;  /* [1] */
      vu32 Reserved : 30; /* [31:2] */
};

union IC_DMA_CR_REG {
    vu32 all;
    struct DMA_CR_BITS bit;
};

struct SDA_SETUP_BITS {
    vu32 SDA_SETUP  : 8;  /* [7:0] */
    vu32 Reserved   : 24; /* [31:8] */
};

union IC_SDA_SETUP_REG {
    vu32 all;
    struct SDA_SETUP_BITS bit;
};

struct ENABLE_STATUS_BITS {
    vu32 IC_EN                   : 1; /* [0] */
    vu32 SLV_DISABLED_WHILE_BUSY : 1; /* [1] */
    vu32 SLV_RX_DATA_LOST        : 1; /* [2] */
};

union IC_ENABLE_STATUS_REG {
    vu32 all;
    struct ENABLE_STATUS_BITS bit;
};

typedef struct
{
    union IC_CON_REG IC_CON;                     /* offset:0x00 */
    union IC_TAR_REG IC_TAR;                     /* offset:0x04 */
    union IC_SAR_REG IC_SAR;                     /* offset:0x08 */
    vu32 IC_HS_MAR;                              /* offset:0x0C */
    union IC_DATA_CMD_REG IC_DATA_CMD;           /* offset:0x10 */
    union IC_SS_SCL_HCNT_REG IC_SS_SCL_HCNT;     /* offset:0x14 */
    union IC_SS_SCL_LCNT_REG IC_SS_SCL_LCNT;     /* offset:0x18 */
    union IC_FS_SCL_HCNT_REG IC_FS_SCL_HCNT;     /* offset:0x1C */
    union IC_FS_SCL_LCNT_REG IC_FS_SCL_LCNT;     /* offset:0x20 */
    vu32 Reserved1;                              /* offset:0x24 */
    vu32 Reserved2;                              /* offset:0x28 */
    union IC_INTR_STAT_REG IC_INTR_STAT;         /* offset:0x2C */
    union IC_INTR_MASK_REG IC_INTR_MASK;         /* offset:0x30 */
    union IC_RAW_INTR_STAT_REG IC_RAW_INTR_STAT; /* offset:0x34 */
    vu32 IC_RX_TL;                               /* offset:0x38 */
    vu32 IC_TX_TL;                               /* offset:0x3C */
    vu32 IC_CLR_INTR;                            /* offset:0x40 */
    vu32 IC_CLR_RX_UNDER;                        /* offset:0x44 */
    vu32 IC_CLR_RX_OVER;                         /* offset:0x48 */
    vu32 IC_CLR_TX_OVER;                         /* offset:0x4C */
    vu32 IC_CLR_RD_REQ;                          /* offset:0x50 */
    vu32 IC_CLR_TX_ABRT;                         /* offset:0x54 */
    vu32 IC_CLR_RX_DONE;                         /* offset:0x58 */
    vu32 IC_CLR_ACTIVITY;                        /* offset:0x5C */
    vu32 IC_CLR_STOP_DET;                        /* offset:0x60 */
    vu32 IC_CLR_START_DET;                       /* offset:0x64 */
    vu32 IC_CLR_GEN_CALL;                        /* offset:0x68 */
    union IC_ENABLE_REG IC_ENABLE;               /* offset:0x6C */
    union IC_STATUS_REG IC_STATUS;               /* offset:0x70 */
    vu32 IC_TXFLR;                               /* offset:0x74 */
    vu32 IC_RXFLR;                               /* offset:0x78 */
    union IC_SDA_HOLD_REG IC_SDA_HOLD;           /* offset:0x7C */
    vu32 reserved5;                              /* offset:0x80 */
    vu32 IC_SLV_DATA_NACK_ONLY;                  /* offset:0x84 */
    union IC_DMA_CR_REG IC_DMA_CR;               /* offset:0x88 */
    vu32 IC_DMA_TDLR;                            /* offset:0x8C */
    vu32 IC_DMA_RDLR;                            /* offset:0x90 */
    union IC_SDA_SETUP_REG IC_SDA_SETUP;         /* offset:0x94 */
    vu32 IC_ACK_GENERAL_CALL;                    /* offset:0x98 */
    union IC_ENABLE_STATUS_REG IC_ENABLE_STATUS; /* offset:0x9C */
    vu32 IC_FS_SPKLEN;                           /* offset:0xA0 */
    vu32 Reserved9;                              /* offset:0xA4 */
    vu32 IC_CLR_RESTART_DET;                     /* offset:0xA8 */
} I2C_TypeDef;

typedef enum {
  I2C_STANDARD_MODE  = 0x1U,
  I2C_FAST_MODE      = 0x2U,
  I2C_HIGHSPEED_MODE = 0x3U
} I2C_SpeedMode;

typedef enum {
  I2C_CONTROLLER_MASTER_ONLY  = 1,
  I2C_CONTROLLER_SLAVE_ONLY   = 2,
  I2C_CONTROLLER_MASTER_SLAVE = 3
} I2C_ControllerType;

typedef enum {
    I2C_INT_NONE         = 0x0U,
    I2C_INT_RX_UNDERFLOW = 0x1U,
    I2C_INT_RX_OVERFLOW  = 0x2U,
    I2C_INT_RX_FULL      = 0x4U,
    I2C_INT_TX_OVERFLOW  = 0x8U,
    I2C_INT_TX_EMPTY     = 0x10U,
    I2C_INT_RD_REQUEST   = 0x20U,
    I2C_INT_TX_ABORT     = 0x40U,
    I2C_INT_RX_DONE      = 0x80U,
    I2C_INT_ACTIVITY     = 0x100U,
    I2C_INT_STOP_DET     = 0x200U,
    I2C_INT_START_DET    = 0x400U,
    I2C_INT_GEN_CALL     = 0x800U,
    I2C_INT_RESTART_DET  = 0x1000U,
    I2C_INT_ALL          = 0x1FFFU
} I2C_InterruptFlag;

typedef enum {
  I2C_ACTIVITY     = 0x1U,
  I2C_TXFIFO_NF    = 0x2U,
  I2C_TXFIFO_EMPTY = 0x4U,
  I2C_RXFIFO_NE    = 0x8U,
  I2C_RXFIFO_FULL  = 0x10U,
  I2C_MST_ACTIVITY = 0x20U,
  I2C_SLV_ACTIVITY = 0x40U,
} I2C_Status;

typedef enum {
  I2C_ADDR_MODE_7BITS  = 0,
  I2C_ADDR_MODE_10BITS = 1
} I2C_AddressMode;

typedef enum
{
    I2C_FIFO_TXE_0        = 0x0U,
    I2C_FIFO_TXE_1        = 0x1U,
    I2C_FIFO_TXE_2        = 0x2U,
    I2C_FIFO_TXE_3        = 0x3U,
    I2C_FIFO_TXE_4        = 0x4U,
    I2C_FIFO_TXE_5        = 0x5U,
    I2C_FIFO_TXE_6        = 0x6U,
    I2C_FIFO_TXE_7        = 0x7U
} I2C_TxFIFOLevel;

typedef enum
{
    I2C_FIFO_RXF_1        = 0x0U,
    I2C_FIFO_RXF_2        = 0x1U,
    I2C_FIFO_RXF_3        = 0x2U,
    I2C_FIFO_RXF_4        = 0x3U,
    I2C_FIFO_RXF_5        = 0x4U,
    I2C_FIFO_RXF_6        = 0x5U,
    I2C_FIFO_RXF_7        = 0x6U,
    I2C_FIFO_RXF_8        = 0x7U,
} I2C_RxFIFOLevel;

typedef enum
{
    I2C_FIFO_TX0        = 0x0U,
    I2C_FIFO_TX1        = 0x1U,
    I2C_FIFO_TX2        = 0x2U,
    I2C_FIFO_TX3        = 0x3U,
    I2C_FIFO_TX4        = 0x4U,
    I2C_FIFO_TX5        = 0x5U,
    I2C_FIFO_TX6        = 0x6U,
    I2C_FIFO_TX7        = 0x7U
} I2C_TxDMATriggerLevel;

typedef enum
{
    I2C_FIFO_RX1        = 0x0U,
    I2C_FIFO_RX2        = 0x1U,
    I2C_FIFO_RX3        = 0x2U,
    I2C_FIFO_RX4        = 0x3U,
    I2C_FIFO_RX5        = 0x4U,
    I2C_FIFO_RX6        = 0x5U,
    I2C_FIFO_RX7        = 0x6U,
    I2C_FIFO_RX8        = 0x7U
} I2C_RxDMATriggerLevel;

#define I2C1 ((I2C_TypeDef *)I2CA_BASE)
#define I2C2 ((I2C_TypeDef *)PMBUS_BASE)

STATIC_INLINE void I2C_enableModule(I2C_TypeDef *i2c)
{
    i2c->IC_ENABLE.bit.ENABLE = 1;
    while(i2c->IC_ENABLE_STATUS.bit.IC_EN != 1)
      ;
}

STATIC_INLINE void I2C_disableModule(I2C_TypeDef *i2c)
{
    i2c->IC_ENABLE.bit.ENABLE = 0;
    while(i2c->IC_ENABLE_STATUS.bit.IC_EN != 0)
      ;
}

STATIC_INLINE void I2C_enableMasterMode(I2C_TypeDef *i2c)
{
    i2c->IC_CON.bit.MASTER_MODE = 1;
}

STATIC_INLINE void I2C_disableMasterMode(I2C_TypeDef *i2c)
{
    i2c->IC_CON.bit.MASTER_MODE = 0;
}

STATIC_INLINE void I2C_enableSlaveMode(I2C_TypeDef *i2c)
{
    i2c->IC_CON.bit.IC_SLAVE_DISABLE = 0;
}

STATIC_INLINE void I2C_disableSlaveMode(I2C_TypeDef *i2c)
{
    i2c->IC_CON.bit.IC_SLAVE_DISABLE = 1;
}

STATIC_INLINE void I2C_setSpeedMode(I2C_TypeDef *i2c, I2C_SpeedMode mode)
{
    i2c->IC_CON.bit.SPEED = mode;
}

STATIC_INLINE void I2C_setAddressMode(I2C_TypeDef *i2c, I2C_AddressMode mode)
{
    i2c->IC_CON.bit.IC_10BITADDR_SLAVE = mode;
//    i2c->IC_CON.bit.IC_10BITADDR_MASTER = mode;
}

STATIC_INLINE void I2C_enableRestart(I2C_TypeDef *i2c)
{
    i2c->IC_CON.bit.IC_RESTART_EN = 1;
}

STATIC_INLINE void I2C_disableRestart(I2C_TypeDef *i2c)
{
    i2c->IC_CON.bit.IC_RESTART_EN = 0;
}

STATIC_INLINE void I2C_enableStopDetIfAddress(I2C_TypeDef *i2c)
{
    i2c->IC_CON.bit.STOP_DET_IFADDRESSED = 1;
}

STATIC_INLINE void I2C_disableStopDetIfAddress(I2C_TypeDef *i2c)
{
    i2c->IC_CON.bit.STOP_DET_IFADDRESSED = 0;
}

STATIC_INLINE void I2C_setFIFOInterruptLevel(I2C_TypeDef *i2c, I2C_TxFIFOLevel txLevel,
     I2C_RxFIFOLevel rxLevel)
{
    i2c->IC_TX_TL = txLevel;
    i2c->IC_RX_TL = rxLevel;
}

STATIC_INLINE void I2C_getFIFOInterruptLevel(I2C_TypeDef *i2c, I2C_TxFIFOLevel *txLevel,
     I2C_RxFIFOLevel *rxLevel)
{
    *txLevel = (I2C_TxFIFOLevel) i2c->IC_TX_TL;
    *rxLevel = (I2C_RxFIFOLevel) i2c->IC_RX_TL;
}

STATIC_INLINE u8 I2C_getTxFIFOStatus(I2C_TypeDef *i2c)
{
    return (u8) i2c->IC_TXFLR;
}

STATIC_INLINE u8 I2C_getRxFIFOStatus(I2C_TypeDef *i2c)
{
    return (u8) i2c->IC_RXFLR;
}

STATIC_INLINE void I2C_setTargetAddress(I2C_TypeDef *i2c, u16 targetAddr)
{
    //I2C_disableModule(i2c);

    i2c->IC_TAR.bit.TAR = targetAddr;

    //I2C_enableModule(i2c);
}

STATIC_INLINE void I2C_setOwnAddress(I2C_TypeDef *i2c, u16 ownAddr)
{
    //I2C_disableModule(i2c);

    i2c->IC_SAR.bit.SAR = ownAddr;

    //I2C_enableModule(i2c);
}

STATIC_INLINE void I2C_setSCLLowCount(I2C_TypeDef *i2c, u16 count)
{
    //I2C_disableModule(i2c);

    if (i2c->IC_CON.bit.SPEED == 1)
        i2c->IC_SS_SCL_LCNT.bit.SS_SCL_LCNT = count;
    else if (i2c->IC_CON.bit.SPEED == 2)
        i2c->IC_FS_SCL_LCNT.bit.FS_SCL_LCNT = count;

    //I2C_enableModule(i2c);
}

STATIC_INLINE void I2C_setSCLHighCount(I2C_TypeDef *i2c, u16 count)
{
    //I2C_disableModule(i2c);

    if (i2c->IC_CON.bit.SPEED == 1)
        i2c->IC_SS_SCL_HCNT.bit.SS_SCL_HCNT = count;
    else if (i2c->IC_CON.bit.SPEED == 2)
        i2c->IC_FS_SCL_HCNT.bit.FS_SCL_HCNT = count;

    //I2C_enableModule(i2c);
}

STATIC_INLINE void I2C_setSDAHold(I2C_TypeDef *i2c, u16 rxHold, u16 txHold)
{
    //I2C_disableModule(i2c);

    i2c->IC_SDA_HOLD.bit.IC_SDA_RX_HOLD = rxHold;
    i2c->IC_SDA_HOLD.bit.IC_SDA_TX_HOLD = txHold;

    //I2C_enableModule(i2c);
}

STATIC_INLINE void I2C_setSpikeSuppression(I2C_TypeDef *i2c, u8 count)
{
    //I2C_disableModule(i2c);

    i2c->IC_FS_SPKLEN = count;

    //I2C_enableModule(i2c);
}

STATIC_INLINE bool I2C_isBusy(I2C_TypeDef *i2c)
{
    return i2c->IC_STATUS.bit.ACTIVITY;
}

STATIC_INLINE u32 I2C_getStatus(I2C_TypeDef *i2c)
{
    return i2c->IC_STATUS.all;
}

STATIC_INLINE u32 I2C_getInterruptStatus(I2C_TypeDef *i2c)
{
    return i2c->IC_INTR_STAT.all;
}

STATIC_INLINE u32 I2C_getPendingInterrupt(I2C_TypeDef *i2c)
{
    return (i2c->IC_INTR_STAT.all ^ i2c->IC_RAW_INTR_STAT.all);
}

STATIC_INLINE void I2C_enableDMA(I2C_TypeDef *i2c)
{
    i2c->IC_DMA_CR.bit.TDMAE = 1;
    i2c->IC_DMA_CR.bit.RDMAE = 1;
}

STATIC_INLINE void I2C_disableDMA(I2C_TypeDef *i2c)
{
    i2c->IC_DMA_CR.bit.TDMAE = 0;
    i2c->IC_DMA_CR.bit.RDMAE = 0;
}

STATIC_INLINE void I2C_sendStopCondition(I2C_TypeDef *i2c)
{
    i2c->IC_DATA_CMD.bit.STOP = 1;
}

STATIC_INLINE void I2C_sendNACK(I2C_TypeDef *i2c)
{
    //I2C_disableModule(i2c);

    i2c->IC_SLV_DATA_NACK_ONLY = 1U;

    //I2C_enableModule(i2c);
}

STATIC_INLINE void I2C_sendStartWrite(I2C_TypeDef *i2c)
{
    i2c->IC_DATA_CMD.bit.CMD = 0;
}

STATIC_INLINE void I2C_sendStartRead(I2C_TypeDef *i2c)
{
    i2c->IC_DATA_CMD.bit.CMD = 1;
}

STATIC_INLINE u8 I2C_getData(I2C_TypeDef *i2c)
{
    return (u8) i2c->IC_DATA_CMD.bit.DATA;
}

STATIC_INLINE void I2C_putData(I2C_TypeDef *i2c, u8 data)
{
    i2c->IC_DATA_CMD.bit.DATA = data;
}

STATIC_INLINE void I2C_setDMATriggerLevel(I2C_TypeDef *i2c, I2C_RxDMATriggerLevel rxLevel,
     I2C_TxDMATriggerLevel txLevel)
{
    i2c->IC_DMA_RDLR = rxLevel;
    i2c->IC_DMA_TDLR = txLevel;
}

void I2C_initController(I2C_TypeDef *i2c, u32 sysclkHz, u32 bitRate);
void I2C_enableInterrupt(I2C_TypeDef *i2c, I2C_InterruptFlag flag);
void I2C_disableInterrupt(I2C_TypeDef *i2c, I2C_InterruptFlag flag);
void I2C_clearInterruptStatus(I2C_TypeDef *i2c, I2C_InterruptFlag flag);
void I2C_configModuleFrequency(I2C_TypeDef *i2c, u32 sysclkHz);

#if 0
#endif

#ifdef __cplusplus
}
#endif

#endif
