/**
 **************************************************************************
 * @file     qx_sci.h
 * @version  v1.0.0
 * @date     2023-12-30
 **************************************************************************
 */

#ifndef QX_SCI_H
#define QX_SCI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"

struct IER_BITS
{
    vu32 ERBFI : 1;  /* [0] */
    vu32 ETBEI : 1;  /* [1] */
    vu32 ELSI  : 1;  /* [2] */
    vu32 EDSSI : 1;  /* [3] */
    vu32 rsvd0 : 3;  /* [6:4] */
    vu32 PTIME : 1;  /* [7] */
    vu32 rsvd1 : 24; /* [31:8] */
};

union IER_REG
{
    vu32 all;
    struct IER_BITS bit;
};

struct IIR_BITS
{
    vu32 INTID   : 4;  /* [3:0] */
    vu32 RESERVE : 2;  /* [5:4] */
    vu32 FIFO_EN : 2;  /* [7:6] */
    vu32 RSVD    : 24; /* [31:8] */
};

union IIR_REG
{
    vu32 all;
    struct IIR_BITS bit;
};

struct FCR_BITS
{
    vu32 FIFOE  : 1;  /* [0] */
    vu32 RFIFOR : 1;  /* [1] */
    vu32 XFIFOR : 1;  /* [2] */
    vu32 DMAM   : 1;  /* [3] */
    vu32 TET    : 2;  /* [5:4] */
    vu32 RT     : 2;  /* [7:6] */
    vu32 rsvd   : 24; /* [31:8] */
};

union FCR_REG
{
    vu32 all;
    struct FCR_BITS bit;
};

struct LCR_BITS
{
    vu32 DLS          : 2;  /* [1:0] */
    vu32 STOP         : 1;  /* [2] */
    vu32 PEN          : 1;  /* [3] */
    vu32 EPS          : 1;  /* [4] */
    vu32 STICK_PARITY : 1;  /* [5] */
    vu32 BC           : 1;  /* [6] */
    vu32 DLAB         : 1;  /* [7] */
    vu32 rsvd         : 24; /* [31:8] */
} LCR_BIT;

union LCR_REG
{
    vu32 all;
    struct LCR_BITS bit;
};

struct MCR_BITS
{
    vu32 DTR      : 1;  /* [0] */
    vu32 RTS      : 1;  /* [1] */
    vu32 OUT1     : 1;  /* [2] */
    vu32 OUT2     : 1;  /* [3] */
    vu32 LOOPBACK : 1;  /* [4] */
    vu32 AFCE     : 1;  /* [5] */
    vu32 SIRE     : 1;  /* [6] */
    vu32 rsvd     : 25; /* [31:7] */
} MCR_BIT;

union MCR_REG
{
    vu32 all;
    struct MCR_BITS bit;
};

struct LSR_BITS
{
    vu32 DR        : 1;  /* [0] */
    vu32 OE        : 1;  /* [1] */
    vu32 PE        : 1;  /* [2] */
    vu32 FE        : 1;  /* [3] */
    vu32 BI        : 1;  /* [4] */
    vu32 THRE      : 1;  /* [5] */
    vu32 TEMT      : 1;  /* [6] */
    vu32 RFE       : 1;  /* [7] */
    vu32 ADDR_RCVD : 1;  /* [8] */
    vu32 rsvd      : 23; /* [31:9] */
};

union LSR_REG
{
    vu32 all;
    struct LSR_BITS bit;
};

struct MSR_BITS
{
    vu32 DCTS : 1;  /* [0] */
    vu32 DDSR : 1;  /* [1] */
    vu32 TERI : 1;  /* [2] */
    vu32 DDCD : 1;  /* [3] */
    vu32 CTS  : 1;  /* [4] */
    vu32 DSR  : 1;  /* [5] */
    vu32 RI   : 1;  /* [6] */
    vu32 DCD  : 1;  /* [7] */
    vu32 rsvd : 24; /* [31:8] */
};

union MSR_REG
{
    vu32 all;
    struct MSR_BITS bit;
};

struct FAR_BITS
{
    vu32 FAR  : 1;  /* [0] */
    vu32 rsvd : 31; /* [31:1] */
};

union FAR_REG
{
    vu32 all;
    struct FAR_BITS bit;
};

struct RFW_BITS
{
    vu32 RFWD : 8;  /* [7:0] */
    vu32 RFPE : 1;  /* [8] */
    vu32 RFFE : 1;  /* [9] */
    vu32 rsvd : 22; /* [31:10] */
};

union RFW_REG
{
    vu32 all;
    struct RFW_BITS bit;
};

struct USR_BITS
{
    vu32 BUSY : 1;  /* [0] */
    vu32 TFNF : 1;  /* [1] */
    vu32 TFE  : 1;  /* [2] */
    vu32 RFNE : 1;  /* [3] */
    vu32 RFF  : 1;  /* [4] */
    vu32 rsvd : 27; /* [31:5] */
};

union USR_REG
{
    vu32 all;
    struct USR_BITS bit;
};

struct SRR_BITS
{
    vu32 UR   : 1;  /* [0] */
    vu32 RFR  : 1;  /* [1] */
    vu32 XFR  : 1;  /* [2] */
    vu32 rsvd : 29; /* [31:3] */
};

union SRR_REG
{
    vu32 all;
    struct SRR_BITS bit;
};

struct TCR_BITS
{
    vu32 RS485_EN  : 1;  /* [0] */
    vu32 RE_POL    : 1;  /* [1] */
    vu32 DE_POL    : 1;  /* [2] */
    vu32 XFER_MODE : 2;  /* [4:3] */
    vu32 rsvd      : 27; /* [31:5] */
};

union TCR_REG
{
    vu32 all;
    struct TCR_BITS bit;
};

struct DET_BITS
{
    vu32 DEAT    : 8; /* [7:0] */
    vu32 RESERVE : 8; /* [15:8] */
    vu32 DEDEAT  : 8; /* [23:16] */
    vu32 rsvd    : 8; /* [31:24] */
};

union DET_REG
{
    vu32 all;
    struct DET_BITS bit;
};

struct TAT_BITS
{
    vu32 DE_TO_RE : 16; /* [15:0] */
    vu32 RE_TO_DE : 16; /* [31:16] */
};

union TAT_REG
{
    vu32 all;
    struct TAT_BITS bit;
};

struct LCR_EXT_BITS
{
    vu32 DLS_E      : 1;  /* [0] */
    vu32 ADDR_MATCH : 1;  /* [1] */
    vu32 SEND_ADDR  : 1;  /* [2] */
    vu32 TRANS_MODE : 1;  /* [3] */
    vu32 rsvd       : 28; /* [31:4] */
};

union LCR_EXT_REG
{
    vu32 all;
    struct LCR_EXT_BITS bit;
};

struct CPR_BITS
{
    vu32 APB_DATA_WIDTH         : 2; /* [1:0] */
    vu32 RESERVE0               : 2; /* [3:2] */
    vu32 AFCE_MODE              : 1; /* [4] */
    vu32 THER_MODE              : 1; /* [5] */
    vu32 SIR_MODE               : 1; /* [6] */
    vu32 SIR_LP_MODE            : 1; /* [7] */
    vu32 NEW_FEAT               : 1; /* [8] */
    vu32 FIFO_ACCESS            : 1; /* [9] */
    vu32 FIFO_STAT              : 1; /* [10] */
    vu32 SHADOW                 : 1; /* [11] */
    vu32 SCI_ADD_ENCODED_PARAMS : 1; /* [12] */
    vu32 DMA_EXTRA              : 1; /* [13] */
    vu32 RESERVE1               : 2; /* [15:14] */
    vu32 FIFO_MODE              : 8; /* [23:16] */
    vu32 rsvd                   : 8; /* [31:24] */
};

union CPR_REG
{
    vu32 all;
    struct CPR_BITS bit;
};

typedef struct
{
    union /* offset:0x00 */
    {
        vu32 RBR;
        vu32 THR;
        vu32 DLL;
    };
    union /* offset:0x04 */
    {
        vu32 DLH;
        union IER_REG IER;
    };
    union /* offset:0x08 */
    {
        union IIR_REG IIR;
        union FCR_REG FCR;
    };
    union LCR_REG LCR; /* offset:0x0C */
    union MCR_REG MCR; /* offset:0x10 */
    union LSR_REG LSR; /* offset:0x14 */
    union MSR_REG MSR; /* offset:0x18 */
    vu32 SCR;          /* offset:0x1C */
    vu32 LPDLL;        /* offset:0x20 */
    vu32 LPDLH;        /* offset:0x24 */
    vu32 rsvd0;        /* offset:0x28 */
    vu32 rsvd1;        /* offset:0x2C */
    union              /* offset:0x30-0x6C */
    {
        vu32 SRBR[16];
        vu32 STHR[16];
    };
    union FAR_REG FAR;         /* offset:0x70 */
    vu32 TFR;                  /* offset:0x74 */
    union RFW_REG RFW;         /* offset:0x78 */
    union USR_REG USR;         /* offset:0x7C */
    vu32 TFL;                  /* offset:0x80 */
    vu32 RFL;                  /* offset:0x84 */
    union SRR_REG SRR;         /* offset:0x88 */
    vu32 SRTS;                 /* offset:0x8C */
    vu32 SBCR;                 /* offset:0x90 */
    vu32 SDMAM;                /* offset:0x94 */
    vu32 SFE;                  /* offset:0x98 */
    vu32 SRT;                  /* offset:0x9C */
    vu32 STET;                 /* offset:0xA0 */
    vu32 HTX;                  /* offset:0xA4 */
    vu32 DMASA;                /* offset:0xA8 */
    union TCR_REG TCR;         /* offset:0xAC */
    vu32 DE_EN;                /* offset:0xB0 */
    vu32 RE_EN;                /* offset:0xB4 */
    union DET_REG DET;         /* offset:0xB8 */
    union TAT_REG TAT;         /* offset:0xBC */
    vu32 DLF;                  /* offset:0xC0 */
    vu32 RAR;                  /* offset:0xC4 */
    vu32 tAR;                  /* offset:0xC8 */
    union LCR_EXT_REG LCR_EXT; /* offset:0xCC */
    vu32 RESERVE[9];           /* offset:0xD0-0xF0 */
    union CPR_REG CPR;         /* offset:0xF4 */
    vu32 UCV;                  /* offset:0xF8 */
    vu32 CTR;                  /* offset:0xFC */
} sci_type;

#define SciaRegs ((sci_type *)SCIA_BASE)
#define ScibRegs ((sci_type *)SCIB_BASE)

typedef enum
{
    SCI_DATA_5BITS = 0x00U,
    SCI_DATA_6BITS = 0x01U,
    SCI_DATA_7BITS = 0x02U,
    SCI_DATA_8BITS = 0x03U,
} SCI_DataWidthType;

typedef enum
{
    SCI_STOP_BIT_1 = 0x00U,
    SCI_STOP_BIT_2 = 0x01U,
} SCI_StopBitType;

typedef enum
{
    SCI_PARITY_NONE = 0x00U,
    SCI_PARITY_EVEN = 0x01U,
    SCI_PARITY_ODD  = 0x02U,
} SCI_ParityType;

typedef enum
{
    SCI_INT_SET_NONE  = 0x00U, /* no interrupt */
    SCI_INT_SET_RXRDY = 0x01U, /* Recv Data Available interrupt */
    SCI_INT_SET_TXRDY = 0x02U, /* Transmit Empty interrupt */
    SCI_INT_SET_RLS   = 0x04U, /* Recv Line Status interrupt */
    SCI_INT_SET_MSI   = 0x08U, /* Modem Status interrupt */
    SCI_INT_SET_THER  = 0x10U, /* RX FIFO level interrupt */
    SCI_INT_SET_ALL   = 0x1FU
} SCI_IntSetType;

typedef enum
{
    SCI_INT_SATUS_MODEM_STATUS = 0x00U, /* modem status interrupt */
    SCI_INT_SATUS_NONE         = 0x01U, /* no interrupt pending */
    SCI_INT_SATUS_TXRDY        = 0x02U, /* tx ready interrupt */
    SCI_INT_SATUS_RXRDY        = 0x04U, /* rx ready interrupt */
    SCI_INT_SATUS_LINE_STATUS  = 0x06U, /* recieiver line interrupt */
    SCI_INT_SATUS_BUSY         = 0x07U, /* busy dectect interrupt */
    SCI_INT_SATUS_RXTIMEROUT   = 0x0CU, /* character timerout interrupt */
} SCI_IntStatusType;

typedef enum
{
    SCI_RX_FIFO_TRIGGER_1_CHAR      = 0x00, /* trgger when 1 char in rx FIFO */
    SCI_RX_FIFO_TRIGGER_1_4_FULL    = 0x01, /* trgger when 1/2 full in rx FIFO */
    SCI_RX_FIFO_TRIGGER_1_2_FULL    = 0x02, /* trgger when 1/4 full in rx FIFO */
    SCI_RX_FIFO_TRIGGER_2_LESS_FULL = 0x03, /* trgger when 2 less than full in rx FIFO */
} SCI_RxFIFOLevel;

typedef enum
{
    SCI_TX_FIFO_TRIGGER_EMPTY    = 0x00, /* trgger when tx FIFO empty */
    SCI_TX_FIFO_TRIGGER_2_CHAR   = 0x01, /* trgger when tx FIFO has 2 char */
    SCI_TX_FIFO_TRIGGER_1_4_FULL = 0x02, /* trgger when tx FIFO 1/4 full */
    SCI_TX_FIFO_TRIGGER_1_2_FULL = 0x03, /* trgger when tx FIFO 1/2 full */
} SCI_TxFIFOLevel;

typedef enum
{
    SCI_DMA_MODE_SINGLE = 0,
    SCI_DMA_MODE_MULTI  = 1
} SCIDMAMode;

typedef enum
{
    SCI_RX_STATUS_NONE = 0x00,
    SCI_RX_STATUS_DR   = 0x01,
    SCI_RX_STATUS_OE   = 0x02,
    SCI_RX_STATUS_PE   = 0x04,
    SCI_RX_STATUS_FE   = 0x08,
    SCI_RX_STATUS_BI   = 0x10,
    SCI_RX_STATUS_THRE = 0x20,
    SCI_RX_STATUS_TEMT = 0x40,
    SCI_RX_STATUS_RFE  = 0x80,
    SCI_RX_STATUS_ADDR = 0x100
} SCIRxStatus;

STATIC_INLINE void SCI_enableFIFO(sci_type *sci)
{
    sci->FCR.bit.FIFOE = 1;
}

STATIC_INLINE void SCI_disableFIFO(sci_type *sci)
{
    sci->FCR.bit.FIFOE = 0;
}

STATIC_INLINE bool SCI_isFIFOEnabled(sci_type *sci)
{
    return sci->IIR.bit.FIFO_EN;
}

STATIC_INLINE void SCI_resetRxFIFO(sci_type *sci)
{
    sci->FCR.bit.RFIFOR = 1;
}

STATIC_INLINE void SCI_resetTxFIFO(sci_type *sci)
{
    sci->FCR.bit.XFIFOR = 1;
}

STATIC_INLINE void SCI_setFIFOInterruptLevel(sci_type *sci, SCI_TxFIFOLevel txlevel, SCI_RxFIFOLevel rxlevel)
{
    sci->FCR.bit.TET = txlevel;
    sci->FCR.bit.RT  = rxlevel;
}

STATIC_INLINE bool SCI_isTxFIFOFull(sci_type *sci)
{
    return !sci->USR.bit.TFNF;
}

STATIC_INLINE bool SCI_isRxFIFOEmpty(sci_type *sci)
{
    return !sci->USR.bit.RFNE;
}

STATIC_INLINE u32 SCI_getTxFIFOStatus(sci_type *sci)
{
    return sci->TFL;
}

STATIC_INLINE u32 SCI_getRxFIFOStatus(sci_type *sci)
{
    return sci->RFL;
}

STATIC_INLINE u32 SCI_getRxStatus(sci_type *sci)
{
    return sci->LSR.all;
}

STATIC_INLINE bool SCI_isTransmitterBusy(sci_type *sci)
{
    return !sci->LSR.bit.TEMT;
}

STATIC_INLINE bool SCI_hasErrorInFIFO(sci_type *sci)
{
    return sci->LSR.bit.RFE;
}

STATIC_INLINE void SCI_setDmaMode(sci_type *sci, SCIDMAMode mode)
{
    if (mode == SCI_DMA_MODE_SINGLE)
        sci->FCR.bit.DMAM = 0;
    else if (mode == SCI_DMA_MODE_MULTI)
        sci->FCR.bit.DMAM = 1;
}

STATIC_INLINE void SCI_writeCharBlocking(sci_type *sci, char data)
{
    while (!sci->LSR.bit.THRE)
        ;
    sci->THR = data;
    /* wait send finish */
    while (!sci->LSR.bit.TEMT)
        ;
}

STATIC_INLINE void SCI_writeCharNonBlocking(sci_type *sci, char data)
{
    sci->THR = data;
}

STATIC_INLINE char SCI_readCharBlocking(sci_type *sci)
{
    while (!sci->LSR.bit.DR)
        ;
    return (char)(sci->RBR);
}

STATIC_INLINE char SCI_readCharNonBlocking(sci_type *sci)
{
    return (char)(sci->RBR);
}

STATIC_INLINE void SCI_performSoftwareReset(sci_type *sci)
{
    sci->SRR.bit.UR = 1;
}

STATIC_INLINE void SCI_enableLoopback(sci_type *sci)
{
    sci->LCR.bit.BC = 1;
}

STATIC_INLINE void SCI_disableLoopback(sci_type *sci)
{
    sci->LCR.bit.BC = 0;
}

STATIC_INLINE void SCI_enableInterrupt(sci_type *sci, SCI_IntSetType interrupts)
{
    sci->IER.all = interrupts;
}

STATIC_INLINE void SCI_disableInterrupt(sci_type *sci, SCI_IntSetType interrupts)
{
    sci->IER.all |= ~interrupts;
}

STATIC_INLINE SCI_IntStatusType SCI_getInterruptStatus(sci_type *sci)
{
    return (SCI_IntStatusType)sci->IIR.bit.INTID;
}

STATIC_INLINE SCI_ParityType SCI_getParityMode(sci_type *sci)
{
    return (SCI_ParityType)sci->LCR.bit.EPS;
}

void SCI_setConfig(sci_type *sci, u32 baud_int, u8 baud_fra, SCI_DataWidthType data_bit, SCI_StopBitType stop_bit,
    SCI_ParityType parity);
void SCI_setParityMode(sci_type *sci, SCI_ParityType parity);
void SCI_setBaud(sci_type *sci, u32 baud_int, u8 baud_fra);
void SCI_writeCharArray(sci_type *sci, void *array, u32 len);
void SCI_readCharArray(sci_type *sci, void *array, u32 len);

#ifdef __cplusplus
}
#endif

#endif
