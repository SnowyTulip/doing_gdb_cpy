/**
 **************************************************************************
 * @file     qx_can.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_CAN_H
#define QX_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"

//---------------------------------------------------------------------------
// CAN Register Bit Definitions:

struct CAN_MODE_BIT
{
    vu32 RM  : 1; /* [0] */
    vu32 LOM : 1; /* [1] */
    vu32 STM : 1; /* [2] */
    vu32 AFM : 1; /* [3] */
    vu32 SM  : 1; /* [4] */
};

union CAN_MODE_REG
{
    vu32 all;
    struct CAN_MODE_BIT bit;
};

struct CAN_CMD_BIT
{
    vu32 TR  : 1; /* [0] */
    vu32 AT  : 1; /* [1] */
    vu32 RRB : 1; /* [2] */
    vu32 CDO : 1; /* [3] */
    vu32 SRR : 1; /* [4] */
};

union CAN_CMD_REG
{
    vu32 all;
    struct CAN_CMD_BIT bit;
};

struct CAN_SR_BIT
{
    vu32 RBS : 1; /* [0] */
    vu32 DOS : 1; /* [1] */
    vu32 TBS : 1; /* [2] */
    vu32 TCS : 1; /* [3] */
    vu32 RS  : 1; /* [4] */
    vu32 TS  : 1; /* [5] */
    vu32 ES  : 1; /* [6] */
    vu32 BS  : 1; /* [7] */
};

union CAN_SR_REG
{
    vu32 all;
    struct CAN_SR_BIT bit;
};

struct CAN_IR_BIT
{
    vu32 RI  : 1; /* [0] */
    vu32 TI  : 1; /* [1] */
    vu32 EI  : 1; /* [2] */
    vu32 DOI : 1; /* [3] */
    vu32 WUI : 1; /* [4] */
    vu32 EPI : 1; /* [5] */
    vu32 ALI : 1; /* [6] */
    vu32 BEI : 1; /* [7] */
};

union CAN_IR_REG
{
    vu32 all;
    struct CAN_IR_BIT bit;
};

struct CAN_IER_BIT
{
    vu32 RIE  : 1; /* [0] */
    vu32 TIE  : 1; /* [1] */
    vu32 EIE  : 1; /* [2] */
    vu32 DOIE : 1; /* [3] */
    vu32 WUIE : 1; /* [4] */
    vu32 EPIE : 1; /* [5] */
    vu32 ALIE : 1; /* [6] */
    vu32 BEIE : 1; /* [7] */
};

union CAN_IER_REG
{
    vu32 all;
    struct CAN_IER_BIT bit;
};

struct CAN_BTR0_BIT
{
    vu32 BRP : 6; /* [5:0] */
    vu32 SJW : 2; /* [7:6] */
};

union CAN_BTR0_REG
{
    vu32 all;
    struct CAN_BTR0_BIT bit;
};

struct CAN_BTR1_BIT
{
    vu32 TSEG1 : 4; /* [3:0] */
    vu32 TSEG2 : 3; /* [6:4] */
    vu32 SAM   : 1; /* [7] */
};

union CAN_BTR1_REG
{
    vu32 all;
    struct CAN_BTR1_BIT bit;
};

struct CAN_ALC_BIT
{
    vu32 ALC : 5; /* [4:0] */
};

union CAN_ALC_REG
{
    vu32 all;
    struct CAN_ALC_BIT bit;
};

struct CAN_ECC_BIT
{
    vu32 SEGMENT_CODE : 5; /* [4:0] */
    vu32 DIRECTION    : 1; /* [5] */
    vu32 ERROR_CODE   : 2; /* [7:6] */
};

union CAN_ECC_REG
{
    vu32 all;
    struct CAN_ECC_BIT bit;
};

struct CAN_BUFF_BIT
{
    vu32 ACR0;
    vu32 ACR1;
    vu32 ACR2;
    vu32 ACR3;
    vu32 AMR0;
    vu32 AMR1;
    vu32 AMR2;
    vu32 AMR3;
};

union CAN_BUFF_REG
{
    vu32 BUFF[13];
    struct CAN_BUFF_BIT bit;
};

struct CAN_RMC_BIT
{
    vu32 RMC : 5; /* [4:0] */
};

union CAN_RMC_REG
{
    vu32 all;
    struct CAN_RMC_BIT bit;
};

struct CAN_RBSA_BIT
{
    vu32 RBSA  : 6; /* [5:0] */
    vu32 RSVD4 : 2; /* [7:6] */
};

union CAN_RBSA_REG
{
    vu32 all;
    struct CAN_RBSA_BIT bit;
};

struct CAN_CDR_BIT
{
    vu32 CDR       : 3; /* [2:0] */
    vu32 CLOCK_OFF : 1; /* [3] */
};

union CAN_CDR_REG
{
    vu32 all;
    struct CAN_CDR_BIT bit;
};

typedef struct
{

    union CAN_MODE_REG MODE; /* offset: 0x00 */
    union CAN_CMD_REG CMD;   /* offset: 0x04 */
    union CAN_SR_REG SR;     /* offset: 0x08 */
    union CAN_IR_REG IR;     /* offset: 0x0C */
    union CAN_IER_REG IER;   /* offset: 0x10 */
    vu32 rcvd;               /* offset: 0x14 */
    union CAN_BTR0_REG BTR0; /* offset: 0x18 */
    union CAN_BTR1_REG BTR1; /* offset: 0x1C */
    vu32 OCR;                /* offset: 0x20 */
    vu32 rsvd1;              /* offset: 0x24 */
    vu32 rsvd2;              /* offset: 0x28 */
    union CAN_ALC_REG ALC;   /* offset: 0x2C */
    union CAN_ECC_REG ECC;   /* offset: 0x2C */
    vu32 EWLR;               /* offset: 0x34 */
    vu32 RXERR;              /* offset: 0x38 */
    vu32 TXERR;              /* offset: 0x3C */
    union CAN_BUFF_REG BUFF; /* offset: offset: 0x40-0x70 */
    union CAN_RMC_REG RMC;   /* offset: 0x74 */
    union CAN_RBSA_REG RBSA; /* offset: 0x78 */
    union CAN_CDR_REG CDR;   /* offset: 0x7C */
    vu32 RECV_FIFO[63];      /* offset: 0x80-0x17C */
    vu32 TRANS_BUFF[13];     /* offset: 0x180-0x1B0 */
} CAN_REGS;

#define CanARegs ((CAN_REGS *)CANA_BASE)
#define CanBRegs ((CAN_REGS *)CANB_BASE)

typedef enum
{
    CAN_MODE_RESET         = 0x01U,
    CAN_MODE_LISSTEN_ONLY  = 0x02U,
    CAN_MODE_SELF_TEST     = 0x04U,
    CAN_MODE_SINGLE_FILTER = 0x08U,
    CAN_MODE_DOUBLE_FILTER = 0x00U,
    CAN_MODE_SLEEP         = 0x10U,
} CAN_ModeType;

typedef enum
{
    CAN_FRAME_STANDARD = 0x00U,
    CAN_FRAME_EXTEND   = 0x01U,
} CAN_FrameType;

typedef enum
{
    CAN_FRAME_DATA   = 0x00U,
    CAN_FRAME_REMOTE = 0x01U,
} CAN_FrameDataType;

typedef enum
{
    CAN_CMD_TRANS_REQUEST       = 0x01U,
    CAN_CMD_ABOART_TARNS        = 0x02U,
    CAN_CMD_RELEASE_RECV_BUFF   = 0x04U,
    CAN_CMD_CLEAR_DATA_OVERRUN  = 0x08U,
    CAN_CMD_SELF_RECEPT_REQUEST = 0x10U,
} CAN_CmdType;

typedef enum
{
    CAN_STATUS_RECV_BUFFER    = 0x01U,
    CAN_STATUS_DATA_OVERRUN   = 0x02U,
    CAN_STATUS_TRANS_BUFFER   = 0x04U,
    CAN_STATUS_TRANS_COMPIETE = 0x08U,
    CAN_STATUS_RECV_PROCESS   = 0x10U,
    CAN_STATUS_TRANS_PROCESS  = 0x20U,
    CAN_STATUS_ERROR          = 0x40U,
    CAN_STATUS_BUS_OFF        = 0x80U,
} CAN_StatusType;

typedef enum
{
    CAN_INT_NONE             = 0x00U,
    CAN_INT_RECV             = 0x01U,
    CAN_INT_TRANS            = 0x02U,
    CAN_INT_ERROR_WARNNING   = 0x04U,
    CAN_INT_OVERRUN          = 0x08U,
    CAN_INT_WAKEUP           = 0x10U,
    CAN_INT_ERROR_PASSIVE    = 0x20U,
    CAN_INT_ARBITRATION_LOST = 0x40U, // normal no need enable
    CAN_INT_BUS_ERROR        = 0x80U, // normal no need enable
    CAN_INT_ALL              = 0xFFU,
} CAN_IntType;

typedef enum
{
    CAN_OUTPUT_MODE_NORMAL   = 0x02U,
    CAN_OUTPUT_MODE_CLOCKOUT = 0x03U,
} CAN_OutputModeType;

typedef enum
{
    CAN_LOST_ID28_BIT = 0x00U,
    CAN_LOST_ID27_BIT = 0x01U,
    CAN_LOST_ID26_BIT = 0x02U,
    CAN_LOST_ID25_BIT = 0x03U,
    CAN_LOST_ID24_BIT = 0x04U,
    CAN_LOST_ID23_BIT = 0x05U,
    CAN_LOST_ID22_BIT = 0x06U,
    CAN_LOST_ID21_BIT = 0x07U,
    CAN_LOST_ID20_BIT = 0x08U,
    CAN_LOST_ID19_BIT = 0x09U,
    CAN_LOST_ID18_BIT = 0x0AU,
    CAN_LOST_SRTR_BIT = 0x0BU,
    CAN_LOST_IDE_BIT  = 0x0CU,
    CAN_LOST_ID17_BIT = 0x0DU,
    CAN_LOST_ID16_BIT = 0x0EU,
    CAN_LOST_ID15_BIT = 0x0FU,
    CAN_LOST_ID14_BIT = 0x10U,
    CAN_LOST_ID13_BIT = 0x11U,
    CAN_LOST_ID12_BIT = 0x12U,
    CAN_LOST_ID11_BIT = 0x13U,
    CAN_LOST_ID10_BIT = 0x14U,
    CAN_LOST_ID9_BIT  = 0x15U,
    CAN_LOST_ID8_BIT  = 0x16U,
    CAN_LOST_ID7_BIT  = 0x17U,
    CAN_LOST_ID6_BIT  = 0x18U,
    CAN_LOST_ID5_BIT  = 0x19U,
    CAN_LOST_ID4_BIT  = 0x1AU,
    CAN_LOST_ID3_BIT  = 0x1BU,
    CAN_LOST_ID2_BIT  = 0x1CU,
    CAN_LOST_ID1_BIT  = 0x1DU,
    CAN_LOST_ID0_BIT  = 0x1EU,
    CAN_LOST_RTR_BIT  = 0x1FU,
} CAN_ArbitrationLostType;

typedef enum
{
    CAN_BIT_ERROR   = 0x00U,
    CAN_FORM_ERROR  = 0x01U,
    CAN_STUFF_ERROR = 0x02U,
    CAN_OTHER_ERROR = 0x03U,
} CAN_ErrorType;

typedef enum
{
    CAN_SEG_START_OF_FRAME        = 0x03U,
    CAN_SEG_ID28_TO_ID21          = 0x02U,
    CAN_SEG_ID20_TO_ID18          = 0x06U,
    CAN_SEG_SRTR_BIT              = 0x04U,
    CAN_SEG_IDE_BIT               = 0x05U,
    CAN_SEG_ID17_TO_ID13          = 0x07U,
    CAN_SEG_ID12_TO_ID5           = 0x0FU,
    CAN_SEG_ID4_TO_ID0            = 0x0EU,
    CAN_SEG_RTR_BIT               = 0x0CU,
    CAN_SEG_RESERVE_BIT_1         = 0x0DU,
    CAN_SEG_RESERVE_BIT_0         = 0x09U,
    CAN_SEG_DATA_LEN_CODE         = 0x0BU,
    CAN_SEG_DATA_FIELD            = 0x0AU,
    CAN_SEG_CRC_SEQUENCE          = 0x08U,
    CAN_SEG_CRC_DELIMITER         = 0x24U,
    CAN_SEG_ACKNOWLEDGE           = 0x19U,
    CAN_SEG_ACKNOWLEDGE_DELIMITER = 0x1BU,
    CAN_SEG_END_OF_FRAME          = 0x1AU,
    CAN_SEG_INTERMISSION          = 0x18U,
    CAN_SEG_ACTIVE_ERROR_FLAG     = 0x17U,
    CAN_SEG_PASSIVE_ERROR_FLAG    = 0x20U,
    CAN_SEG_TOLERATE_DOMAIN_BIT   = 0x19U,
    CAN_SEG_ERROR_DELIMITER       = 0x23U,
    CAN_SEG_OVERLOAD_FLAG         = 0x28U,
} CAN_SegmentCodeType;

typedef enum
{
    CAN_CLKOUT_DIV_2  = 0x00U,
    CAN_CLKOUT_DIV_4  = 0x01U,
    CAN_CLKOUT_DIV_6  = 0x02U,
    CAN_CLKOUT_DIV_8  = 0x03U,
    CAN_CLKOUT_DIV_10 = 0x04U,
    CAN_CLKOUT_DIV_12 = 0x05U,
    CAN_CLKOUT_DIV_14 = 0x06U,
    CAN_CLKOUT_DIV_1  = 0x07U,
} CAN_ClkOutDivType;

/* clang-format off */
#define STA_FRAME_SINGLE_FITER(ID, FRMAE_DATA_TYPE, DATA1, DATA2) \
(((ID) << 21) | ((FRMAE_DATA_TYPE) << 20) | ((DATA1) << 8) | (DATA2))

#define STA_FRAME_DOUBLE_FITER(ID1, FRAME_DATA_TYPE1, ID2, FRAME_DATA_TYPE2, DATA1, DATA2) \
(((ID1) << 21) | ((FRAME_DATA_TYPE1) << 20) | (((DATA1) >> 4) << 19)| \
((ID2) <<   5) | ((FRAME_DATA_TYPE2) <<  4) | ((DATA2)  >> 4))

#define EXT_FRAME_SINGLE_FITER(ID, FRMAE_DATA_TYPE) \
(((ID) << 3) | ((FRMAE_DATA_TYPE) << 2))

#define EXT_FRAME_DOUBLE_FITER(ID1, ID2) \
((((ID1) >> 13) << 16) | ((ID2) >> 13))
/* clang-format on */

STATIC_INLINE void CAN_setMode(CAN_REGS *can, CAN_ModeType modes)
{
    can->MODE.all = modes;
}

STATIC_INLINE void CAN_setClkDiv(CAN_REGS *can, vu32 div)
{
    if (can == CanARegs)
        DevCfgRegs->CANACLKDIV.bit.CLK_CANA_DIV_NUM = div;
    else if (can == CanBRegs)
        DevCfgRegs->CANBCLKDIV.bit.CLK_CANB_DIV_NUM = div;
}

STATIC_INLINE void CAN_setCmd(CAN_REGS *can, CAN_CmdType cmds)
{
    can->CMD.all = cmds;
}

STATIC_INLINE u32 CAN_getStatus(CAN_REGS *can)
{
    return can->SR.all;
}

STATIC_INLINE void CAN_setInterrupt(CAN_REGS *can, CAN_IntType ints)
{
    can->IER.all = ints;
}

STATIC_INLINE u32 CAN_getAndAutoClearInterrupt(CAN_REGS *can)
{
    return can->IR.all;
}

/* can baudrate = pclk/(2 * (bpr+1) * (1 + (tseg1+1) + (tseg2+1)) */
/* sample  rate = (1 + (tseg1 + 1))/((1 + (tseg1+1) + (tseg2+1)), suggest at 75% ~ 85% */
STATIC_INLINE void CAN_setBusTiming(CAN_REGS *can, u32 brp, u32 sjw, u32 tseg1, u32 tseg2, u32 sam)
{
    can->BTR0.bit.BRP   = brp;
    can->BTR0.bit.SJW   = sjw;
    can->BTR1.bit.TSEG1 = tseg1;
    can->BTR1.bit.TSEG2 = tseg2;
    can->BTR1.bit.SAM   = sam;
}

STATIC_INLINE void CAN_setOutputMode(CAN_REGS *can, CAN_OutputModeType modes)
{
    can->OCR = modes;
}

STATIC_INLINE CAN_ArbitrationLostType CAN_getArbirationLost(CAN_REGS *can)
{
    return can->ALC.all;
}

STATIC_INLINE CAN_ErrorType CAN_getErrorCode(CAN_REGS *can)
{
    return can->ECC.bit.ERROR_CODE;
}

STATIC_INLINE CAN_SegmentCodeType CAN_getSegmentCode(CAN_REGS *can)
{
    return can->ECC.bit.SEGMENT_CODE;
}

STATIC_INLINE void CAN_setErrorWaningLimit(CAN_REGS *can, u8 error_num)
{
    can->EWLR = error_num;
}

STATIC_INLINE u8 CAN_getRecvErrorCount(CAN_REGS *can)
{
    return can->RXERR;
}

STATIC_INLINE u8 CAN_getTransErrorCount(CAN_REGS *can)
{
    return can->TXERR;
}

STATIC_INLINE void CAN_setAcceptFilter(CAN_REGS *can, vu32 acr, vu32 amr)
{
    can->BUFF.bit.ACR0 = (acr >> 24) & 0xFFU;
    can->BUFF.bit.ACR1 = (acr >> 16) & 0xFFU;
    can->BUFF.bit.ACR2 = (acr >> 8) & 0xFFU;
    can->BUFF.bit.ACR3 = (acr & 0xFFU);

    can->BUFF.bit.AMR0 = (amr >> 24) & 0xFFU;
    can->BUFF.bit.AMR1 = (amr >> 16) & 0xFFU;
    can->BUFF.bit.AMR2 = (amr >> 8) & 0xFFU;
    can->BUFF.bit.AMR3 = (amr & 0xFFU);
}

STATIC_INLINE void CAN_setClockOutDivider(CAN_REGS *can, CAN_ClkOutDivType clkout_div)
{
    can->CDR.bit.CDR = clkout_div;
}

STATIC_INLINE void CAN_enableClockOutput(CAN_REGS *can)
{
    can->CDR.bit.CLOCK_OFF = 0;
}

STATIC_INLINE void CAN_disableClockOutput(CAN_REGS *can)
{
    can->CDR.bit.CLOCK_OFF = 1;
}

STATIC_INLINE void CAN_setRecvBuffStartOffset(CAN_REGS *can, int offset)
{
    can->RBSA.all = offset;
}

STATIC_INLINE void CAN_enableDMA(CAN_REGS *can)
{ }

STATIC_INLINE void CAN_disableDMA(CAN_REGS *can)
{ }

STATIC_INLINE u32 CAN_isTransmitterBusy(CAN_REGS *can)
{
    return !can->SR.bit.TBS;
}

void CAN_sendStandardFrame(CAN_REGS *can, u32 frame_id, CAN_FrameDataType rtr, const void *msg, u8 msglen);
void CAN_sendExtendFrame(CAN_REGS *can, u32 frame_id, CAN_FrameDataType rtr, const void *msg, u8 msglen);
void CAN_recvFrameBlocking(CAN_REGS *can, void *msg);
void CAN_recvFrameNonBlocking(CAN_REGS *can, void *msg);

#ifdef __cplusplus
}
#endif

#endif // __QX_DSP_CAN_H
