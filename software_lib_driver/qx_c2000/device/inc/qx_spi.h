/**
 **************************************************************************
 * @file     qx32m_spi.h
 * @version  v1.0.0
 * @date     2022-12-30
 * @brief    qx32m spi header file
 **************************************************************************
 */

#ifndef __QX32M_SPI_H
#define __QX32M_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"
#include "hw_spi.h"
#include "qx_debug.h"

#define SSI_RX_FIFO_DEPTH 8
#define SSI_TX_FIFO_DEPTH 8
#define SSI_HAS_DMA       1
#define SRC_CLK_FREQ      10000000

#define SPI_PRI_STEINV 0x2U // SPISTE inversion bit
#define SPI_PRI_PTEINV SPI_PRI_STEINV

typedef enum
{
    SPI1_SLAVE_MODE  = 1,
    SPI1_MASTER_MODE = 2,
    SPI2_SLAVE_MODE  = 3,
    SPI2_MASTER_MODE = 4
} SPI_HostMode;

typedef enum
{
    SPI_STANDARD_FORMAT = 0,
    SPI_DUAL_FORMAT     = 1,
    SPI_QUAD_FORMAT     = 2
} SPI_WireFormat;

typedef enum
{
    SPI_INT_MASK_TXE = 0x01,
    SPI_INT_MASK_TXO = 0x02,
    SPI_INT_MASK_RXU = 0x04,
    SPI_INT_MASK_RXO = 0x08,
    SPI_INT_MASK_RXF = 0x10,
    SPI_INT_MASK_MST = 0x20,
    SPI_INT_MASK_ALL = 0x3F
} SPI_InterruptMask;

typedef enum
{
    SPI_INT_STATUS_TXEI = 0x01,
    SPI_INT_STATUS_TXOI = 0x02,
    SPI_INT_STATUS_RXUI = 0x04,
    SPI_INT_STATUS_RXOI = 0x08,
    SPI_INT_STATUS_RXFI = 0x10,
    SPI_INT_STATUS_MSTI = 0x20
} SPI_InterruptStatus;

typedef enum
{
    SPI_CTRL_BITS_1  = 0x0,
    SPI_CTRL_BITS_2  = 0x1,
    SPI_CTRL_BITS_3  = 0x2,
    SPI_CTRL_BITS_4  = 0x3,
    SPI_CTRL_BITS_5  = 0x4,
    SPI_CTRL_BITS_6  = 0x5,
    SPI_CTRL_BITS_7  = 0x6,
    SPI_CTRL_BITS_8  = 0x7,
    SPI_CTRL_BITS_9  = 0x8,
    SPI_CTRL_BITS_10 = 0x9,
    SPI_CTRL_BITS_11 = 0xA,
    SPI_CTRL_BITS_12 = 0xB,
    SPI_CTRL_BITS_13 = 0xC,
    SPI_CTRL_BITS_14 = 0xD,
    SPI_CTRL_BITS_15 = 0xE,
    SPI_CTRL_BITS_16 = 0xF
} SPI_CtrlFrameWidth;

typedef enum
{
    SPI_DATA_BITS_4  = 0x03,
    SPI_DATA_BITS_5  = 0x04,
    SPI_DATA_BITS_6  = 0x05,
    SPI_DATA_BITS_7  = 0x06,
    SPI_DATA_BITS_8  = 0x07,
    SPI_DATA_BITS_9  = 0x08,
    SPI_DATA_BITS_10 = 0x09,
    SPI_DATA_BITS_11 = 0x0A,
    SPI_DATA_BITS_12 = 0x0B,
    SPI_DATA_BITS_13 = 0x0C,
    SPI_DATA_BITS_14 = 0x0D,
    SPI_DATA_BITS_15 = 0x0E,
    SPI_DATA_BITS_16 = 0x0F,
    SPI_DATA_BITS_17 = 0x10,
    SPI_DATA_BITS_18 = 0x11,
    SPI_DATA_BITS_19 = 0x12,
    SPI_DATA_BITS_20 = 0x13,
    SPI_DATA_BITS_21 = 0x14,
    SPI_DATA_BITS_22 = 0x15,
    SPI_DATA_BITS_23 = 0x16,
    SPI_DATA_BITS_24 = 0x17,
    SPI_DATA_BITS_25 = 0x18,
    SPI_DATA_BITS_26 = 0x19,
    SPI_DATA_BITS_27 = 0x1A,
    SPI_DATA_BITS_28 = 0x1B,
    SPI_DATA_BITS_29 = 0x1C,
    SPI_DATA_BITS_30 = 0x1D,
    SPI_DATA_BITS_31 = 0x1E,
    SPI_DATA_BITS_32 = 0x1F
} SPI_DataFrameWidth;

typedef enum
{
    SPI_TRANS_MODE_TR     = 0x0,
    SPI_TRANS_MODE_TO     = 0x1,
    SPI_TRANS_MODE_RO     = 0x2,
    SPI_TRANS_EEPROM_READ = 0x3
} SPI_TransferMode;

typedef enum
{
    SPI_SAMPLE_POS_0 = 0x0U,
    SPI_SAMPLE_POS_1 = 0x1U,
    SPI_SAMPLE_NEG_0 = 0x2U,
    SPI_SAMPLE_NEG_1 = 0x3U
} SPI_SampleMode;

typedef enum
{
    SPI_TRANS_STATUS_NULL = 0x00,
    SPI_TRANS_STAT_BUSY   = 0x01,
    SPI_TRANS_STAT_TFNF   = 0x02,
    SPI_TRANS_STAT_TFE    = 0x04,
    SPI_TRANS_STAT_RFNE   = 0x08,
    SPI_TRANS_STAT_RFF    = 0x10,
    SPI_TRANS_STAT_TXE    = 0x20,
    SPI_TRANS_STAT_DCOL   = 0x40
} SPI_TransferStatus;

typedef enum
{
    SPI_FRF_MOTOROLA  = 0x0,
    SPI_FRF_TEXAS     = 0x1,
    SPI_FRF_MICROWIRE = 0x2
} SPI_FrameFormat;

typedef struct
{
    SPI_DataFrameWidth data_width;
    SPI_SampleMode sample_mode;
    SPI_TransferMode trans_mode;
    u32 baudrate;
    u8 rx_ftl;
    u8 tx_ftl;
} SPI_Config;

struct CTRL0_BITS
{
    vu32 rsvd0   : 4; /* [3:0] */
    vu32 FRF     : 2; /* [5:4] */
    vu32 SCPH    : 1; /* [6] */
    vu32 SCPOL   : 1; /* [7] */
    vu32 TMOD    : 2; /* [9:8] */
    vu32 SLV_OE  : 1; /* [10] */
    vu32 SRL     : 1; /* [11] */
    vu32 CFS     : 4; /* [15:12] */
    vu32 DFS_32  : 5; /* [20:16] */
    vu32 SPI_FRF : 2; /* [22:21] */
    vu32 rsvd1   : 1; /* [23] */
    vu32 SSTE    : 1; /* [24] */
    vu32 SECONV  : 1; /* [25] */
};

union CTRL0_REG
{
    vu32 all;
    struct CTRL0_BITS bit;
};

struct CTRL1_BITS
{
    vu32 NDF : 16; /* [15:0] */
};

union CTRL1_REG
{
    vu32 all;
    struct CTRL1_BITS bit;
};

struct MWC_BITS
{
    vu32 MWMOD : 1; /* [0] */
    vu32 MDD   : 1; /* [1] */
    vu32 MHS   : 1; /* [2] */
};

union MWC_REG
{
    vu32 all;
    struct MWC_BITS bit;
};

struct STAT_BITS
{
    vu32 BUSY : 1; /* [0] */
    vu32 TFNF : 1; /* [1] */
    vu32 TFE  : 1; /* [2] */
    vu32 RFNE : 1; /* [3] */
    vu32 RFF  : 1; /* [4] */
    vu32 TXE  : 1; /* [5] */
    vu32 DCOL : 1; /* [6] */
};

union STAT_REG
{
    vu32 all;
    struct STAT_BITS bit;
};

struct IM_BITS
{
    vu32 TXEIM : 1; /* [0] */
    vu32 TXOIM : 1; /* [1] */
    vu32 RXUIM : 1; /* [2] */
    vu32 RXOIM : 1; /* [3] */
    vu32 RXFIM : 1; /* [4] */
    vu32 MSTIM : 1; /* [5] */
};

union IM_REG
{
    vu32 all;
    struct IM_BITS bit;
};

struct IS_BITS
{
    vu32 TXEIS : 1; /* [0] */
    vu32 TXOIS : 1; /* [1] */
    vu32 RXUIS : 1; /* [2] */
    vu32 RXOIS : 1; /* [3] */
    vu32 RXFIS : 1; /* [4] */
    vu32 MSTIS : 1; /* [5] */
};

union IS_REG
{
    vu32 all;
    struct IS_BITS bit;
};

struct RIS_BITS
{
    vu32 TXEIR : 1; /* [0] */
    vu32 TXOIR : 1; /* [1] */
    vu32 RXUIR : 1; /* [2] */
    vu32 RXOIR : 1; /* [3] */
    vu32 RXFIR : 1; /* [4] */
    vu32 MSTIR : 1; /* [5] */
};

union IRS_REG
{
    vu32 all;
    struct RIS_BITS bit;
};

struct DMAC_BITS
{
    vu32 RDMAE : 1; /* [0] */
    vu32 TDMAE : 1; /* [1] */
};

union DMAC_REG
{
    vu32 dmac;
    struct DMAC_BITS bit;
};

struct SPI_CTRL0_BITS
{
    vu32 TRANS_TYPE  : 2; /* [1:0] */
    vu32 ADDR_L      : 4; /* [5:2] */
    vu32 reserved0   : 2; /* [7:6] */
    vu32 INST_L      : 2; /* [9:8] */
    vu32 reserved1   : 1; /* [10] */
    vu32 WAIT_CYCLES : 4; /* [14:11] */
};

union SPI_CTRL0_REG
{
    vu32 SPI_ctrl0;
    struct SPI_CTRL0_BITS bit;
};

typedef struct
{
    union CTRL0_REG CTRL0;         /* offset:0x00 */
    union CTRL1_REG CTRL1;         /* offset:0x04 */
    vu32 SSIEN;                    /* offset:0x08 */
    union MWC_REG MWC;             /* offset:0x0c */
    vu32 SE;                       /* offset:0x10 */
    vu32 BAUD;                     /* offset:0x14 */
    vu32 TXFTL;                    /* offset:0x18 */
    vu32 RXFTL;                    /* offset:0x1c */
    vu32 TXFL;                     /* offset:0x20 */
    vu32 RXFL;                     /* offset:0x24 */
    union STAT_REG STAT;           /* offset:0x28 */
    union IM_REG IM;               /* offset:0x2c */
    union IS_REG IS;               /* offset:0x30 */
    union IRS_REG RIS;             /* offset:0x34 */
    vu32 TXOIC;                    /* offset:0x38 */
    vu32 RXOIS;                    /* offset:0x3c */
    vu32 RXUIC;                    /* offset:0x40 */
    vu32 MSTIC;                    /* offset:0x44 */
    vu32 IC;                       /* offset:0x48 */
    union DMAC_REG DMAC;           /* offset:0x4c */
    vu32 DMATDL;                   /* offset:0x50 */
    vu32 DMARDL;                   /* offset:0x54 */
    vu32 ID;                       /* offset:0x58 */
    vu32 SSI_VERSION_ID;           /* offset:0x5c */
    vu32 DATA[0x90];               /* offset:0x60 */
    vu32 RX_SAMPLE_DLY;            /* offset:0xf0 */
    union SPI_CTRL0_REG SPI_CTRL0; /* offset:0xf4 */
    vu32 rsvd_1;                   /* offset:0xf8 */
    vu32 rsvd_2;                   /* offset:0xfc */
} SPI_Type;

typedef struct
{
    u32 length;
    char *buf;
} buf_desc;

static SPI_Type *SPI1;
static SPI_Type *SPI2;

buf_desc spi_send, spi_recv;

//*****************************************************************************
//
//! This macro definition is used to transmit a byte of data
//!
//! \param base specifies the SPI module base address.
//! \param txData is the data to be transmitted over SPI
//!
//! This macro definition is to transmit a byte of data.
//! This macro uses SPI_pollingNonFIFOTransaction function
//! SPI character length is hardcoded to 8 (1 byte = 8 bits)of character length
//!
//! \return None.
//
//*****************************************************************************
#define SPI_transmitByte(base, txData) SPI_pollingNonFIFOTransaction(base, 8U, txData)

//*****************************************************************************
//
//! This macro definition is used to transmit a 16-bit word of data
//!
//! \param base specifies the SPI module base address.
//! \param txData is the data to be transmitted over SPI
//!
//! This macro definition is to transmit a 16-bit word of data.
//! This macro uses SPI_pollingNonFIFOTransaction function
//! SPI character length is hardcoded to 16 (16bit word) of character length
//!
//! \return None.
//
//*****************************************************************************
#define SPI_transmit16Bits(base, txData) SPI_pollingNonFIFOTransaction(base, 16U, txData)

//*****************************************************************************
//
//! This macro definition can be used to transmit 'N' bytes of data
//!
//! \param base specifies the SPI module base address.
//! \param txBuffer is the transmit buffer to be transmitted over SPI
//! \param numOfWords is the number of bytes to be transmitted
//! \param txDelay specifies the number of serial clock cycles delay time after
//!        completion of perious word
//!
//! This macro definition can be used to transmit 'N' bytes of data.
//! This macro definition uses SPI_pollingFIFOTransaction function.
//!
//! SPI character length is hardcoded to 8 (8bits) of character length
//!
//! \return None.
//
//*****************************************************************************
#define SPI_transmitNBytes(base, txBuffer, numOfWords, txDelay) \
    SPI_pollingFIFOTransaction(base, 8U, txBuffer, NULL, numOfWords, txDelay)

//*****************************************************************************
//
//! This macro definition can be used to transmit 'N' 16-bit words of data
//!
//! \param base specifies the SPI module base address.
//! \param txBuffer is the transmit buffer to be transmitted over SPI
//! \param numOfWords is the number of 16-bit word to be transmitted
//! \param txDelay specifies the number of serial clock cycles delay time after
//!        completion of perious word
//!
//! This function can be used to transmit 'N' 16-bit words of data.
//! This function uses SPI_pollingFIFOTransaction function.
//! SPI character length is hardcoded to 16 (16-bit word)
//!
//! \return None.
//
//*****************************************************************************
#define SPI_transmitN16BitWord(base, txBuffer, numOfWords, txDelay) \
    SPI_pollingFIFOTransaction(base, 16U, txBuffer, NULL, numOfWords, txDelay)

//*****************************************************************************
//
//! This macro definition can be used to transmit 'N' with configurable
//! SPI character length
//!
//! \param base specifies the SPI module base address
//! \param charLength specifies the SPI character length
//! \param txBuffer is the transmit buffer to be transmitted over SPI
//! \param numOfWords is the number of 16-bit word to be transmitted
//! \param txDelay specifies the number of serial clock cycles delay time after
//!        completion of perious word
//!
//! This macro definition can be used to transmit 'N' with configurable
//! SPI character length.
//!
//! This macro uses SPIpolling_FIFO_Transaction function.
//! SPI character length is configurable using charLength variable.
//!
//! \return None.
//
//*****************************************************************************
#define SPI_transmitNWordsWithCharLength(base, charLength, txBuffer, numOfWords, txDelay) \
    SPI_pollingFIFOTransaction(base, charLength, txBuffer, NULL, numOfWords, txDelay)

//*****************************************************************************
//
//! This macro definition is used to receive a byte of data
//!
//! \param base specifies the SPI module base address.
//! \param dummyData is the data which is transmitted to initiate
//!        SPI transaction to receive SPI data
//!
//! This macro definition is to receive a byte of data.
//! This macro uses SPI_pollingNonFIFOTransaction function
//! SPI character length is hardcoded to 8 (1byte = 8bits) of character length
//!
//! \return the received byte.
//
//*****************************************************************************
#define SPI_receiveByte(base, dummyData) SPI_pollingNonFIFOTransaction(base, 8U, dummyData)

//*****************************************************************************
//
//! This macro is used to receive 'N' bytes of data
//!
//! \param base specifies the SPI module base address.
//! \param rxBuffer specifies receive buffer which will store the received bytes
//! \param numOfWords specifies the number of bytes to be received
//! \param txDelay specifies the number of serial clock cycles delay time after
//!        completion of perious word
//!
//! This function is used to receive 'N' bytes of data
//! This function uses SPIpolling_FIFO_Transaction function.
//! SPI character length is hardcoded to 8 (1 byte = 8 bits)
//!
//! \return None.
//
//*****************************************************************************
#define SPI_receiveNBytes(base, rxBuffer, numOfWords, txDelay) \
    SPI_pollingFIFOTransaction(base, 8U, NULL, rxBuffer, numOfWords, txDelay)

//*****************************************************************************
//
//! This macro is used to receive 'N' 16-bits words of data
//!
//! \param base specifies the SPI module base address.
//! \param rxBuffer specifies receive buffer which will store the received bytes
//! \param numOfWords specifies the number of 16-bit words to be received
//! \param txDelay specifies the number of serial clock cycles delay time after
//!        completion of perious word
//!
//! This function is used to receive 'N' 16-bit words of data
//! This function uses SPIpolling_FIFO_Transaction function.
//! SPI character length is hardcoded to 16bits
//!
//! \return None.
//
//*****************************************************************************
#define SPI_receiveN16BitWord(base, rxBuffer, numOfWords, txDelay) \
    SPI_pollingFIFOTransaction(base, 16U, NULL, rxBuffer, numOfWords, txDelay)

//*****************************************************************************
//
//! This macro is used to receive 'N' words with specified character length
//!
//! \param base specifies the SPI module base address.
//! \param charLength specifies the SPI character length of SPI transaction
//! \param rxBuffer specifies receive buffer which will store the received bytes
//! \param numOfWords specifies the number of words with specified character
//!        length
//! \param txDelay specifies the number of serial clock cycles delay time after
//!        completion of perious word
//!
//! This function is used to receive 'N' words with specified character length
//! This function uses SPIpolling_FIFO_Transaction function.
//! SPI character length is configurable using charLength variable
//!
//! \return None.
//
//*****************************************************************************
#define SPI_receiveNWordsWithcharLength(base, charLength, rxBuffer, numOfWords, txDelay) \
    SPI_pollingFIFOTransaction(base, charLength, NULL, rxBuffer, numOfWords, txDelay)

//*****************************************************************************
//
//! Values that can be passed to SPI_setConfig() as the \e protocol parameter.
//
//*****************************************************************************
typedef enum
{
    //! Mode 0. Polarity 0, phase 0. Rising edge without delay.
    SPI_PROT_POL0PHA0 = 0x0000U,
    //! Mode 1. Polarity 0, phase 1. Rising edge with delay.
    SPI_PROT_POL0PHA1 = 0x0002U,
    //! Mode 2. Polarity 1, phase 0. Falling edge without delay.
    SPI_PROT_POL1PHA0 = 0x0001U,
    //! Mode 3. Polarity 1, phase 1. Falling edge with delay.
    SPI_PROT_POL1PHA1 = 0x0003U
} SPI_TransferProtocol;

//*****************************************************************************
//
//! Values that can be passed to SPI_setConfig() as the \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    SPI_MODE_PERIPHERAL    = 0x0002U, //!< SPI peripheral
    SPI_MODE_CONTROLLER    = 0x0006U, //!< SPI controller
    SPI_MODE_PERIPHERAL_OD = 0x0000U, //!< SPI peripheral w/ output disabled
    SPI_MODE_CONTROLLER_OD = 0x0004U  //!< SPI controller w/ output disabled
} SPI_Mode;

//*****************************************************************************
//
//! Values that can be passed to SPI_setFIFOInterruptLevel() as the \e txLevel
//! parameter, returned by SPI_getFIFOInterruptLevel() in the \e txLevel
//! parameter, and returned by SPI_getTxFIFOStatus().
//
//*****************************************************************************
typedef enum
{
    SPI_FIFO_TXEMPTY = 0x0000U, //!< Transmit FIFO empty
    SPI_FIFO_TX0     = 0x0000U, //!< Transmit FIFO empty
    SPI_FIFO_TX1     = 0x0001U, //!< Transmit FIFO 1/8 full
    SPI_FIFO_TX2     = 0x0002U, //!< Transmit FIFO 2/8 full
    SPI_FIFO_TX3     = 0x0003U, //!< Transmit FIFO 3/8 full
    SPI_FIFO_TX4     = 0x0004U, //!< Transmit FIFO 4/8 full
    SPI_FIFO_TX5     = 0x0005U, //!< Transmit FIFO 5/8 full
    SPI_FIFO_TX6     = 0x0006U, //!< Transmit FIFO 6/8 full
    SPI_FIFO_TX7     = 0x0007U, //!< Transmit FIFO 7/8 full
    SPI_FIFO_TX8     = 0x0008U, //!< Transmit FIFO full
    SPI_FIFO_TXFULL  = 0x0008U  //!< Transmit FIFO full
} SPI_TxFIFOLevel;

//*****************************************************************************
//
//! Values that can be passed to SPI_setFIFOInterruptLevel() as the \e rxLevel
//! parameter, returned by SPI_getFIFOInterruptLevel() in the \e rxLevel
//! parameter, and returned by SPI_getRxFIFOStatus().
//
//*****************************************************************************
typedef enum
{
    SPI_FIFO_RXEMPTY   = 0x0000U, //!< Receive FIFO empty
    SPI_FIFO_RX0       = 0x0000U, //!< Receive FIFO empty
    SPI_FIFO_RX1       = 0x0001U, //!< Receive FIFO 1/16 full
    SPI_FIFO_RX2       = 0x0002U, //!< Receive FIFO 2/16 full
    SPI_FIFO_RX3       = 0x0003U, //!< Receive FIFO 3/16 full
    SPI_FIFO_RX4       = 0x0004U, //!< Receive FIFO 4/16 full
    SPI_FIFO_RX5       = 0x0005U, //!< Receive FIFO 5/16 full
    SPI_FIFO_RX6       = 0x0006U, //!< Receive FIFO 6/16 full
    SPI_FIFO_RX7       = 0x0007U, //!< Receive FIFO 7/16 full
    SPI_FIFO_RX8       = 0x0008U, //!< Receive FIFO 8/16 full
    SPI_FIFO_RX16      = 0x0008U, //!< Receive FIFO full
    SPI_FIFO_RXFULL    = 0x0008U, //!< Receive FIFO full
    SPI_FIFO_RXDEFAULT = 0x0000U  //!< To prevent interrupt at reset
} SPI_RxFIFOLevel;

//*****************************************************************************
//
//! Values that can be passed to SPI_setEmulationMode() as the \e mode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! Transmission stops after midway in the bit stream
    SPI_EMULATION_STOP_MIDWAY = 0x0000U,
    //! Continue SPI operation regardless
    SPI_EMULATION_FREE_RUN = 0x0010U,
    //! Transmission will stop after a started transmission completes
    SPI_EMULATION_STOP_AFTER_TRANSMIT = 0x0020U
} SPI_EmulationMode;

//*****************************************************************************
//
//! Values that can be passed to SPI_setPTESignalPolarity() as the \e polarity
//! parameter.
//
//*****************************************************************************
typedef enum
{
    SPI_PTE_ACTIVE_LOW  = 0x0000U,       //!< SPIPTE is active low (normal)
    SPI_PTE_ACTIVE_HIGH = SPI_PRI_PTEINV //!< SPIPTE is active high (inverted)
} SPI_PTEPolarity;

//*****************************************************************************
//
//! Values that can be passed to SPI_receive16Bits(), SPI_receive24Bits(),
//! SPI_receive32Bits()
//
//*****************************************************************************
typedef enum
{
    SPI_DATA_LITTLE_ENDIAN = 0U, //!< LITTLE ENDIAN
    SPI_DATA_BIG_ENDIAN    = 1U, //!< BIG ENDIAN
} SPI_endianess;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks an SPI base address.
//!
//! \param base specifies the SPI module base address.
//!
//! This function determines if a SPI module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool SPI_isBaseValid(uint32_t base)
{
    return ((base == SPI_MASTER_BASE) || (base == SPI_SLAVE_BASE));
}
#endif

//*****************************************************************************
//
//! Enables the serial peripheral interface.
//!
//! \param base specifies the SPI module base address.
//!
//! This function enables operation of the serial peripheral interface.  The
//! serial peripheral interface must be configured before it is enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void SPI_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    HWREG(base + DW_SPI_SSIENR) = 1U;
}

//*****************************************************************************
//
//! Disables the serial peripheral interface.
//!
//! \param base specifies the SPI module base address.
//!
//! This function disables operation of the serial peripheral interface. Call
//! this function before doing any configuration.
//!
//! \return None.
//
//*****************************************************************************
static inline void SPI_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    HWREG(base + DW_SPI_SSIENR) = 0U;
}

//*****************************************************************************
//
//! Sets the character length of SPI transaction
//!
//! \param base specifies the SPI module base address.
//! \param charLength specifies the character length of SPI transaction
//!
//! This function configures the character length of SPI transaction.
//! SPI character length can be from anywhere between 1-bit word to 16 bit word
//! of character length
//!
//! \return None.
//
//*****************************************************************************
static inline void SPI_setcharLength(uint32_t base, uint16_t charLength)
{
    uint32_t regValue;
    ASSERT((charLength >= 4U) && (charLength <= 16U));
    SPI_disableModule(base);
    regValue &= ~DW_PSSI_CTRLR0_DFS32_MASK;
    regValue |= (charLength - 1) << 16;
    HWREG(base + DW_SPI_CTRLR0) |= regValue;
    SPI_enableModule(base);
}

//*****************************************************************************
//
//! Sets the FIFO level at which interrupts are generated.
//!
//! \param base is the base address of the SPI port.
//! \param txLevel is the transmit FIFO interrupt level, specified as
//! \b SPI_FIFO_TX0, \b SPI_FIFO_TX1, \b SPI_FIFO_TX2, . . . or
//! \b SPI_FIFO_TX16.
//! \param rxLevel is the receive FIFO interrupt level, specified as
//! \b SPI_FIFO_RX0, \b SPI_FIFO_RX1, \b SPI_FIFO_RX2, . . . or
//! \b SPI_FIFO_RX16.
//!
//! This function sets the FIFO level at which transmit and receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
static inline void SPI_setFIFOInterruptLevel(uint32_t base, SPI_TxFIFOLevel txLevel, SPI_RxFIFOLevel rxLevel)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Set the FIFO interrupt levels.
    //
    SPI_disableModule(base);
    HWREG(base + DW_SPI_TXFTLR) = txLevel;
    if (rxLevel > 0)
        HWREG(base + DW_SPI_RXFTLR) = rxLevel - 1;
    SPI_enableModule(base);
}

//*****************************************************************************
//
//! Gets the FIFO level at which interrupts are generated.
//!
//! \param base is the base address of the SPI port.
//! \param txLevel is a pointer to storage for the transmit FIFO level,
//! returned as one of \b SPI_FIFO_TX0, \b SPI_FIFO_TX1,
//! \b SPI_FIFO_TX2, . . . or \b SPI_FIFO_TX16.
//! \param rxLevel is a pointer to storage for the receive FIFO level,
//! returned as one of \b SPI_FIFO_RX0, \b SPI_FIFO_RX1,
//! \b SPI_FIFO_RX2, . . . or \b SPI_FIFO_RX16.
//!
//! This function gets the FIFO level at which transmit and receive interrupts
//! are generated.
//!
//! \return None.
//
//*****************************************************************************
static inline void SPI_getFIFOInterruptLevel(uint32_t base, SPI_TxFIFOLevel *txLevel, SPI_RxFIFOLevel *rxLevel)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Extract the transmit and receive FIFO levels.
    //
    *txLevel = HWREG(base + DW_SPI_TXFTLR);
    *rxLevel = HWREG(base + DW_SPI_RXFTLR) + 1;
}

//*****************************************************************************
//
//! Get the transmit FIFO status
//!
//! \param base is the base address of the SPI port.
//!
//! This function gets the current number of words in the transmit FIFO.
//!
//! \return Returns the current number of words in the transmit FIFO specified
//! as one of the following:
//! \b SPI_FIFO_TX0, \b SPI_FIFO_TX1, \b SPI_FIFO_TX2, \b SPI_FIFO_TX3,
//! ..., or \b SPI_FIFO_TX16
//
//*****************************************************************************
static inline SPI_TxFIFOLevel SPI_getTxFIFOStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Get the current FIFO status
    //
    return ((SPI_TxFIFOLevel)(HWREG(base + DW_SPI_TXFLR)));
}

//*****************************************************************************
//
//! Get the receive FIFO status
//!
//! \param base is the base address of the SPI port.
//!
//! This function gets the current number of words in the receive FIFO.
//!
//! \return Returns the current number of words in the receive FIFO specified
//! as one of the following:
//! \b SPI_FIFO_RX0, \b SPI_FIFO_RX1, \b SPI_FIFO_RX2, \b SPI_FIFO_RX3,
//! ..., or \b SPI_FIFO_RX16
//
//*****************************************************************************
static inline SPI_RxFIFOLevel SPI_getRxFIFOStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Get the current FIFO status
    //
    return ((SPI_RxFIFOLevel)(HWREG(base + DW_SPI_RXFLR)));
}

//*****************************************************************************
//
//! Determines whether the SPI transmitter is busy or not.
//!
//! \param base is the base address of the SPI port.
//!
//! This function allows the caller to determine whether all transmitted bytes
//! have cleared the transmitter hardware.  If \b false is returned, then the
//! transmit FIFO is empty and all bits of the last transmitted word have left
//! the hardware shift register. This function is only valid when operating in
//! FIFO mode.
//!
//! \return Returns \b true if the SPI is transmitting or \b false if all
//! transmissions are complete.
//
//*****************************************************************************
static inline bool SPI_isBusy(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Determine if the SPI is busy.
    //
    return (HWREG(base + DW_SPI_SR) & DW_SPI_SR_BUSY);
}

//*****************************************************************************
//
//! Puts a data element into the SPI transmit buffer.
//!
//! \param base specifies the SPI module base address.
//! \param data is the left-justified data to be transmitted over SPI.
//!
//! This function places the supplied data into the transmit buffer of the
//! specified SPI module.
//!
//! \note The data being sent must be left-justified in \e data. The lower
//! 16 - N bits will be discarded where N is the data width selected in
//! SPI_setConfig(). For example, if configured for a 6-bit data width, the
//! lower 10 bits of data will be discarded.
//!
//! \return None.
//
//*****************************************************************************
static inline void SPI_writeDataNonBlocking(uint32_t base, uint16_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Write data to the transmit buffer.
    //
    HWREGH(base + DW_SPI_DR) = data;
}

//*****************************************************************************
//
//! Gets a data element from the SPI receive buffer.
//!
//! \param base specifies the SPI module base address.
//!
//! This function gets received data from the receive buffer of the specified
//! SPI module and returns it.
//!
//! \note Only the lower N bits of the value written to \e data contain valid
//! data, where N is the data width as configured by SPI_setConfig(). For
//! example, if the interface is configured for 8-bit data width, only the
//! lower 8 bits of the value written to \e data contain valid data.
//!
//! \return Returns the word of data read from the SPI receive buffer.
//
//*****************************************************************************
static inline uint16_t SPI_readDataNonBlocking(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Check for data to read.
    //
    return (HWREGH(base + DW_SPI_DR));
}

//*****************************************************************************
//
//! Waits for space in the FIFO and then puts data into the transmit buffer.
//!
//! \param base specifies the SPI module base address.
//! \param data is the left-justified data to be transmitted over SPI.
//!
//! This function places the supplied data into the transmit buffer of the
//! specified SPI module once space is available in the transmit FIFO. This
//! function should only be used when the FIFO is enabled.
//!
//! \note The data being sent must be left-justified in \e data. The lower
//! 16 - N bits will be discarded where N is the data width selected in
//! SPI_setConfig(). For example, if configured for a 6-bit data width, the
//! lower 10 bits of data will be discarded.
//!
//! \return None.
//
//*****************************************************************************
static inline void SPI_writeDataBlockingFIFO(uint32_t base, uint16_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Wait until space is available in the receive FIFO.
    //
    while (SPI_getTxFIFOStatus(base) == SPI_FIFO_TXFULL)
    { }

    //
    // Write data to the transmit buffer.
    //
    HWREGH(base + DW_SPI_DR) = data;
}

//*****************************************************************************
//
//! Waits for data in the FIFO and then reads it from the receive buffer.
//!
//! \param base specifies the SPI module base address.
//!
//! This function waits until there is data in the receive FIFO and then reads
//! received data from the receive buffer.  This function should only be used
//! when FIFO mode is enabled.
//!
//! \note Only the lower N bits of the value written to \e data contain valid
//! data, where N is the data width as configured by SPI_setConfig(). For
//! example, if the interface is configured for 8-bit data width, only the
//! lower 8 bits of the value written to \e data contain valid data.
//!
//! \return Returns the word of data read from the SPI receive buffer.
//
//*****************************************************************************
static inline uint16_t SPI_readDataBlockingFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Wait until data is available in the receive FIFO.
    //
    while (SPI_getRxFIFOStatus(base) == SPI_FIFO_RXEMPTY)
    { }

    //
    // Check for data to read.
    //
    return (HWREGH(base + DW_SPI_DR));
}

//*****************************************************************************
//
//! Waits for the transmit buffer to empty and then writes data to it.
//!
//! \param base specifies the SPI module base address.
//! \param data is the left-justified data to be transmitted over SPI.
//!
//! This function places the supplied data into the transmit buffer of the
//! specified SPI module once it is empty. This function should not be used
//! when FIFO mode is enabled.
//!
//! \note The data being sent must be left-justified in \e data. The lower
//! 16 - N bits will be discarded where N is the data width selected in
//! SPI_setConfig(). For example, if configured for a 6-bit data width, the
//! lower 10 bits of data will be discarded.
//!
//! \return None.
//
//*****************************************************************************
static inline void SPI_writeDataBlockingNonFIFO(uint32_t base, uint16_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Wait until the transmit buffer is not full.
    //
    while ((HWREG(base + DW_SPI_SR) & DW_SPI_SR_TF_NOT_FULL) != 0U)
    { }

    //
    // Write data to the transmit buffer.
    //
    HWREGH(base + DW_SPI_DR) = data;
}

//*****************************************************************************
//
//! Waits for data to be received and then reads it from the buffer.
//!
//! \param base specifies the SPI module base address.
//!
//! This function waits for data to be received and then reads it from the
//! receive buffer of the specified SPI module. This function should not be
//! used when FIFO mode is enabled.
//!
//! \note Only the lower N bits of the value written to \e data contain valid
//! data, where N is the data width as configured by SPI_setConfig(). For
//! example, if the interface is configured for 8-bit data width, only the
//! lower 8 bits of the value written to \e data contain valid data.
//!
//! \return Returns the word of data read from the SPI receive buffer.
//
//*****************************************************************************
static inline uint16_t SPI_readDataBlockingNonFIFO(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Wait until data has been received.
    //
    while ((HWREG(base + DW_SPI_SR) & DW_SPI_SR_RF_NOT_EMPT) == 0U)
    { }

    //
    // Check for data to read.
    //
    return (HWREGH(base + DW_SPI_DR));
}

//*****************************************************************************
//
//! Enables SPI 3-wire mode.
//!
//! \param base is the base address of the SPI port.
//!
//! This function enables 3-wire mode. When in controller mode, this allows
//! SPIPICO to become SPICOCI and SPIPOCI to become free for non-SPI use.
//! When in peripheral mode, SPIPOCI because the SPIPIPO pin and SPIPICO is
//! free for non-SPI use.
//!
//! \return None.
//
//*****************************************************************************
static inline void SPI_enableTriWire(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    SPI_disableModule(base);
    HWREG(base + DW_SPI_CTRLR0) |= DW_SPI_CTRLR0_FRF_NS_MICROWIRE << 4;
    SPI_enableModule(base);
}

//*****************************************************************************
//
//! Disables SPI 3-wire mode.
//!
//! \param base is the base address of the SPI port.
//!
//! This function disables 3-wire mode. SPI will operate in normal 4-wire mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void SPI_disableTriWire(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    SPI_disableModule(base);
    HWREG(base + DW_SPI_CTRLR0) &= ~DW_PSSI_CTRLR0_FRF_MASK;
    SPI_enableModule(base);
}

//*****************************************************************************
//
//! Enables SPI loopback mode.
//!
//! \param base is the base address of the SPI port.
//!
//! This function enables loopback mode. This mode is only valid during
//! controller mode and is helpful during device testing as it internally
//! connects PICO and POCI.
//!
//! \return None.
//
//*****************************************************************************
static inline void SPI_enableLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    SPI_disableModule(base);
    HWREG(base + DW_SPI_CTRLR0) |= DW_PSSI_CTRLR0_SRL;
    SPI_enableModule(base);
}

//*****************************************************************************
//
//! Disables SPI loopback mode.
//!
//! \param base is the base address of the SPI port.
//!
//! This function disables loopback mode. Loopback mode is disabled by default
//! after reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void SPI_disableLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    SPI_disableModule(base);
    HWREG(base + DW_SPI_CTRLR0) &= ~DW_PSSI_CTRLR0_SRL;
    SPI_enableModule(base);
}

//*****************************************************************************
//
//! Set the peripheral select (SPIPTE) signal polarity.
//!
//! \param base is the base address of the SPI port.
//! \param polarity is the SPIPTE signal polarity.
//!
//! This function sets the polarity of the peripheral select (SPIPTE) signal.
//! The two modes to choose from for the \e polarity parameter are
//! \b SPI_PTE_ACTIVE_LOW for active-low polarity (typical) and
//! \b SPI_PTE_ACTIVE_HIGH for active-high polarity (considered inverted).
//!
//! \note This has no effect on the PTE signal when in controller mode. It is
//! only applicable to peripheral mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void SPI_setPTESignalPolarity(uint32_t base, SPI_PTEPolarity polarity)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    //
    // Write the polarity of the SPIPTE signal to the register.
    //
    SPI_disableModule(base);
    if (polarity == SPI_PTE_ACTIVE_HIGH)
        HWREG(base + DW_SPI_CTRLR0) |= DW_PSSI_CTRLR0_SLV_OE;
    else
        HWREG(base + DW_SPI_CTRLR0) &= ~DW_PSSI_CTRLR0_SLV_OE;
    SPI_disableModule(base);
}

//*****************************************************************************
//
//! Enables SPI high speed mode.
//!
//! \param base is the base address of the SPI port.
//!
//! This function enables high speed mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void SPI_enableHighSpeedMode(uint32_t base)
{ }

//*****************************************************************************
//
//! Disables SPI high speed mode.
//!
//! \param base is the base address of the SPI port.
//!
//! This function disables high speed mode. High speed mode is disabled by
//! default after reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void SPI_disableHighSpeedMode(uint32_t base)
{ }

//*****************************************************************************
//
//! Configures the FIFO Transmit Delay
//!
//! \param base is the base address of the SPI port.
//! \param delay Tx FIFO delay to be configured in cycles (0..0xFF)
//!
//! This function sets the delay between every transfer from FIFO
//! transmit buffer to transmit shift register. The delay is defined in
//! number SPI serial clock cycles.
//!
//! \return None
//
//*****************************************************************************
static inline void SPI_setTxFifoTransmitDelay(uint32_t base, uint16_t delay)
{ }

//*****************************************************************************
//
//! Sets SPI emulation mode.
//!
//! \param base is the base address of the SPI port.
//! \param mode is the emulation mode.
//!
//! This function sets the behavior of the SPI operation when an emulation
//! suspend occurs. The \e mode parameter can be one of the following:
//!
//! - \b SPI_EMULATION_STOP_MIDWAY - Transmission stops midway through the bit
//!   stream. The rest of the bits will be transmitting after the suspend is
//!   deasserted.
//! - \b SPI_EMULATION_STOP_AFTER_TRANSMIT - If the suspend occurs before the
//!   first SPICLK pulse, the transmission will not start. If it occurs later,
//!   the transmission will be completed.
//! - \b SPI_EMULATION_FREE_RUN - SPI operation continues regardless of a
//!   the suspend.
//!
//! \return None.
//
//*****************************************************************************
static inline void SPI_setEmulationMode(uint32_t base, SPI_EmulationMode mode)
{ }

//*****************************************************************************
//
//! Enable Trasnmit
//!
//! \param base is the base address of the SPI port.
//!
//! This function sets the TALK bit enabling the data trasnmission.
//! This bit is enabled by SPI_setConfig if the parameter \r mode is selected as
//! SPI_MODE_PERIPHERAL or SPI_MODE_CONTROLLER.
//!
//! \return None
//
//*****************************************************************************
static inline void SPI_enableTalk(uint32_t base)
{ }

//*****************************************************************************
//
//! Disable Trasnmit
//!
//! \param base is the base address of the SPI port.
//!
//! This function clears the TALK bit disabling the data trasnmission. The
//! output pin will be put in high-impedance state.
//! This bit is enabled by SPI_setConfig if the parameter \r mode is selected as
//! SPI_MODE_PERIPHERAL or SPI_MODE_CONTROLLER.
//!
//! \return None
//
//*****************************************************************************
static inline void SPI_disableTalk(uint32_t base)
{ }

//*****************************************************************************
//
//! Reset SPI transmit and receive channels
//!
//! \param base is the base address of the SPI port.
//!
//! This function resets the SPI transmit and receive channels.
//!
//! \return None
//
//*****************************************************************************
static inline void SPI_reset(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(SPI_isBaseValid(base));

    SPI_disableModule(base);
    // SPI_resetTxFIFO(base);
    HWREG(base + DW_SPI_SER) = 0;
    SPI_enableModule(base);
}

//*****************************************************************************
//
//! Configures the serial peripheral interface.
//!
//! \param base specifies the SPI module base address.
//! \param lspclkHz is the rate of the clock supplied to the SPI module
//! (LSPCLK) in Hz.
//! \param protocol specifies the data transfer protocol.
//! \param mode specifies the mode of operation.
//! \param bitRate specifies the clock rate in Hz.
//! \param dataWidth specifies number of bits transferred per frame.
//!
//! This function configures the serial peripheral interface.  It sets the SPI
//! protocol, mode of operation, bit rate, and data width.
//!
//! The \e protocol parameter defines the data frame format.  The \e protocol
//! parameter can be one of the following values: \b SPI_PROT_POL0PHA0,
//! \b SPI_PROT_POL0PHA1, \b SPI_PROT_POL1PHA0, or
//! \b SPI_PROT_POL1PHA1. These frame formats encode the following polarity
//! and phase configurations:
//!
//! <pre>
//! Polarity Phase       Mode
//!   0       0   SPI_PROT_POL0PHA0
//!   0       1   SPI_PROT_POL0PHA1
//!   1       0   SPI_PROT_POL1PHA0
//!   1       1   SPI_PROT_POL1PHA1
//! </pre>
//!
//! The \e mode parameter defines the operating mode of the SPI module.  The
//! SPI module can operate as a controller or peripheral; the SPI can also be be
//! configured to disable output on its serial output line.  The \e mode
//! parameter can be one of the following values: \b SPI_MODE_CONTROLLER,
//! \b SPI_MODE_PERIPHERAL, \b SPI_MODE_CONTROLLER_OD or
//! \b SPI_MODE_PERIPHERAL_OD ("OD" indicates "output disabled").
//!
//! The \e bitRate parameter defines the bit rate for the SPI.  This bit rate
//! must satisfy the following clock ratio criteria:
//!
//! - \e bitRate can be no greater than lspclkHz divided by 4.
//! - \e lspclkHz / \e bitRate cannot be greater than 128.
//!
//! The \e dataWidth parameter defines the width of the data transfers and
//! can be a value between 1 and 16, inclusive.
//!
//! The peripheral clock is the low speed peripheral clock.  This value is
//! returned by SysCtl_getLowSpeedClock(), or it can be explicitly hard coded
//! if it is constant and known (to save the code/execution overhead of a call
//! to SysCtl_getLowSpeedClock()).
//!
//! \note SPI operation should be disabled via SPI_disableModule() before any
//! changes to its configuration.
//!
//! \return None.
//
//*****************************************************************************
extern void SPI_setConfig(uint32_t base, uint32_t lspclkHz, SPI_TransferProtocol protocol, SPI_Mode mode,
    uint32_t bitRate, uint16_t dataWidth);

//*****************************************************************************
//
//! Configures the baud rate of the serial peripheral interface.
//!
//! \param base specifies the SPI module base address.
//! \param lspclkHz is the rate of the clock supplied to the SPI module
//! (LSPCLK) in Hz.
//! \param bitRate specifies the clock rate in Hz.
//!
//! This function configures the SPI baud rate. The \e bitRate parameter
//! defines the bit rate for the SPI.  This bit rate must satisfy the following
//! clock ratio criteria:
//!
//! - \e bitRate can be no greater than \e lspclkHz divided by 4.
//! - \e lspclkHz / \e bitRate cannot be greater than 128.
//!
//! The peripheral clock is the low speed peripheral clock.  This value is
//! returned by SysCtl_getLowSpeedClock(), or it can be explicitly hard coded
//! if it is constant and known (to save the code/execution overhead of a call
//! to SysCtl_getLowSpeedClock()).
//!
//! \note SPI_setConfig() also sets the baud rate. Use SPI_setBaudRate()
//! if you wish to configure it separately from protocol and mode.
//!
//! \return None.
//
//*****************************************************************************
extern void SPI_setBaudRate(SPI_Type *spi, uint32_t lspclkHz, uint32_t bitRate);

//*****************************************************************************
//
//! Gets the current interrupt status.
//!
//! \param base specifies the SPI module base address.
//!
//! This function returns the interrupt status for the SPI module.
//!
//! \return The current interrupt status, enumerated as a bit field of the
//! following values:
//! - \b SPI_INT_RX_OVERRUN - Receive overrun interrupt
//! - \b SPI_INT_RX_DATA_TX_EMPTY - Data received, transmit empty
//! - \b SPI_INT_RXFF - RX FIFO level interrupt
//! - \b SPI_INT_RXFF_OVERFLOW - RX FIFO overflow
//! - \b SPI_INT_TXFF - TX FIFO level interrupt
//
//*****************************************************************************
extern uint32_t SPI_getInterruptStatus(uint32_t base);

//*****************************************************************************
//
//! Clears SPI interrupt sources.
//!
//! \param base specifies the SPI module base address.
//! \param intFlags is a bit mask of the interrupt sources to be cleared.
//!
//! This function clears the specified SPI interrupt sources so that they no
//! longer assert.  This function must be called in the interrupt handler to
//! keep the interrupts from being triggered again immediately upon exit.  The
//! \e intFlags parameter can consist of a bit field of the following values:
//! - \b SPI_INT_RX_OVERRUN
//! - \b SPI_INT_RX_DATA_TX_EMPTY
//! - \b SPI_INT_RXFF
//! - \b SPI_INT_RXFF_OVERFLOW
//! - \b SPI_INT_TXFF
//!
//! \note \b SPI_INT_RX_DATA_TX_EMPTY is cleared by a read of the receive
//! receive buffer, so it usually doesn't need to be cleared using this
//! function.
//!
//! \note Also note that \b SPI_INT_RX_OVERRUN, \b SPI_INT_RX_DATA_TX_EMPTY,
//! \b SPI_INT_RXFF_OVERFLOW, and \b SPI_INT_RXFF are associated with
//! \b SPIRXINT; \b SPI_INT_TXFF is associated with \b SPITXINT.
//!
//! \return None.
//
//*****************************************************************************
extern void SPI_clearInterruptStatus(uint32_t base, uint32_t intFlags);

//*****************************************************************************
//
//! This function can be used to transmit a 24-bit word of data
//!
//! \param base specifies the SPI module base address.
//! \param txData is the data to be transmitted over SPI
//! \param txDelay specifies the number of serial clock cycles delay time after
//!        completion of perious word
//!
//! This function can be used to transmit a 24-bit word of data.
//! 24-bit word data is divided into three bytes of data.
//!
//! This function uses SPI_pollingFIFOTransaction function.
//! SPI character length is hardcoded to 8 (8bits) of character length
//!
//! \return None.
//
//*****************************************************************************
extern void SPI_transmit24Bits(uint32_t base, uint32_t data, uint16_t txDelay);

//*****************************************************************************
//
//! This function can be used to transmit a 32-bit word of data
//!
//! \param base specifies the SPI module base address.
//! \param txData is the data to be transmitted over SPI
//! \param txDelay specifies the number of serial clock cycles delay time after
//!        completion of perious word
//!
//! This function can be used to transmit a 32-bit word of data.
//! 32-bit word data is divided into four bytes of data.
//!
//! This function uses SPI_pollingFIFOTransaction function.
//! SPI character length is hardcoded to 8 (8bits) of character length
//!
//! \return None.
//
//*****************************************************************************
extern void SPI_transmit32Bits(uint32_t base, uint32_t data, uint16_t txDelay);

//*****************************************************************************
//
//! This function is used to receive a 16-bit word of data
//!
//! \param base specifies the SPI module base address.
//! \param endianness specifies the endianess of received data
//! \param dummyData is the data which is transmitted to initiate
//!        SPI transaction to receive SPI data
//! \param txDelay specifies the number of serial clock cycles delay time after
//!        completion of perious word
//!
//! This function is used to receive a 16-bit word of data.
//! This function uses SPIpolling_FIFO_Transaction function.
//! SPI character length is hardcoded to 8 (1 byte = 8 bits)of character length
//!
//! \return the received 16-bit word.
//
//*****************************************************************************
extern uint16_t SPI_receive16Bits(uint32_t base, SPI_endianess endianness, uint16_t dummyData, uint16_t txDelay);

//*****************************************************************************
//
//! This function is used to receive a 24-bit word of data
//!
//! \param base specifies the SPI module base address.
//! \param endianness specifies the endianess of received data
//! \param dummyData is the data which is transmitted to initiate
//!        SPI transaction to receive SPI data
//! \param txDelay specifies the number of serial clock cycles delay time after
//!        completion of perious word
//!
//! This function is used to receive a 24-bit word of data.
//! This function uses SPIpolling_FIFO_Transaction function.
//! SPI character length is hardcoded to 8 (1 byte = 8 bits)of character length
//!
//! \return the received 24-bit word.
//
//*****************************************************************************
extern uint32_t SPI_receive24Bits(uint32_t base, SPI_endianess endianness, uint16_t dummyData, uint16_t txDelay);

//*****************************************************************************
//
//! This function is used to receive a 32-bit word of data
//!
//! \param base specifies the SPI module base address.
//! \param endianness specifies the endianess of received data
//! \param dummyData is the data which is transmitted to initiate
//!        SPI transaction to receive SPI data
//! \param txDelay specifies the number of serial clock cycles delay time after
//!        completion of perious word
//!
//! This function is used to receive a 32-bit word of data.
//! This function uses SPIpolling_FIFO_Transaction function.
//! SPI character length is hardcoded to 8 (1 byte = 8 bits)of character length
//!
//! \return the received 32-bit word.
//
//*****************************************************************************
extern uint32_t SPI_receive32Bits(uint32_t base, SPI_endianess endianness, uint16_t dummyData, uint16_t txDelay);

//*****************************************************************************
//
//! This function is used to initiate SPI transaction of specified character
//! length
//!
//! \param base specifies the SPI module base address.
//! \param charLength specifies the SPI character length of SPI transaction
//! \param data specified the data to be transmitted
//!
//! This function is used to initiate SPI transaction of specified character.
//! SPI character length is configurable using charLength variable
//!
//! \return .
//
//*****************************************************************************
extern uint16_t SPI_pollingNonFIFOTransaction(uint32_t base, uint16_t charLength, uint16_t data);

//*****************************************************************************
//
//! This function is used to initiate SPI transaction of specified character
//! length and 'N' words of transaction
//!
//! \param base specifies the SPI module base address.
//! \param charLength specifies the SPI character length of SPI transaction
//! \param pTxBuffer specifies the pointer to transmit buffer
//! \param pRxBuffer specifies the pointer to receive buffer
//! \param numOfWords specified the number of data to be transmitted / received
//!
//! SPI character length is configurable using charLength variable
//!
//! \return none
//
//*****************************************************************************
extern void SPI_pollingFIFOTransaction(uint32_t base, uint16_t charLength, uint16_t *pTxBuffer, uint16_t *pRxBuffer,
    uint16_t numOfWords, uint16_t txDelay);

STATIC_INLINE void SPI_setHostMode(SPI_HostMode mode)
{
    if (mode == SPI1_MASTER_MODE)
    {
        HWREGB(SPI1_SEL_BASE) = 1;
        SPI1                  = (SPI_Type *)SPI1_MASTER_BASE;
    }
    else if (mode == SPI1_SLAVE_MODE)
    {
        HWREGB(SPI1_SEL_BASE) = 0;
        SPI1                  = (SPI_Type *)SPI1_SLAVE_BASE;
    }
    else if (mode == SPI2_MASTER_MODE)
    {
        HWREGB(SPI2_SEL_BASE) = 1;
        SPI2                  = (SPI_Type *)SPI2_MASTER_BASE;
    }
    else if (mode == SPI2_SLAVE_MODE)
    {
        HWREGB(SPI2_SEL_BASE) = 0;
        SPI2                  = (SPI_Type *)SPI2_SLAVE_BASE;
    }
}

STATIC_INLINE void SPI_moduleEnable(SPI_Type *spi)
{
    if (!spi)
        return;

    spi->SSIEN = 1;
}

STATIC_INLINE void SPI_moduleDisable(SPI_Type *spi)
{
    if (!spi)
        return;

    spi->SSIEN = 0;
}

STATIC_INLINE void SPI_setFrameFormat(SPI_Type *spi, SPI_FrameFormat mode)
{
    if (!spi)
        return;

    SPI_moduleDisable(spi);

    spi->CTRL0.bit.FRF = mode;

    SPI_moduleEnable(spi);
}

STATIC_INLINE void SPI_slaveEnable(SPI_Type *spi)
{
    if (!spi)
        return;

    SPI_moduleDisable(spi);

    spi->SE = 1;

    SPI_moduleEnable(spi);
}

STATIC_INLINE void SPI_setTransferWidth(SPI_Type *spi, SPI_DataFrameWidth width)
{
    if (!spi)
        return;

    SPI_moduleDisable(spi);

    spi->CTRL0.bit.DFS_32 = width;

    SPI_moduleEnable(spi);
}

STATIC_INLINE u32 SPI_getFIFOLevel(SPI_Type *spi, bool is_rx)
{
    if (!spi)
        return -1;

    if (is_rx)
        return spi->RXFL;
    else
        return spi->TXFL;
}

STATIC_INLINE u8 SPI_getFIFOThresholdLevel(SPI_Type *spi, bool is_rx)
{
    if (!spi)
        return -1;

    if (is_rx)
        return spi->RXFTL;
    else
        return spi->TXFTL;
}

STATIC_INLINE void SPI_setFIFOThresholdLevel(SPI_Type *spi, u8 tx_ftl, u8 rx_ftl)
{
    if (!spi)
        return;

    SPI_moduleDisable(spi);

    if (tx_ftl >= 0 && tx_ftl <= SSI_TX_FIFO_DEPTH)
        spi->TXFTL = tx_ftl;

    if (rx_ftl > 0 && rx_ftl <= SSI_RX_FIFO_DEPTH)
        spi->RXFTL = rx_ftl - 1;

    SPI_moduleEnable(spi);
}

STATIC_INLINE u32 SPI_getTransferStatus(SPI_Type *spi)
{
    if (!spi)
        return -1;

    return spi->STAT.all;
}

STATIC_INLINE u32 SPI_getPendingInterrupt(SPI_Type *spi)
{
    u32 status;

    if (!spi)
        return -1;

    status = spi->RIS.all;
    status |= spi->IS.all;

    return status;
}

#if SSI_HAS_DMA == 1
STATIC_INLINE void SPI_enableDMA(SPI_Type *spi, bool tx, bool rx)
{
    if (!spi)
        return;

    if (tx)
        spi->DMAC.bit.TDMAE = 1;

    if (rx)
        spi->DMAC.bit.RDMAE = 1;
}

STATIC_INLINE void SPI_disableDMA(SPI_Type *spi, bool tx, bool rx)
{
    if (!spi)
        return;

    if (tx)
        spi->DMAC.bit.TDMAE = 0;

    if (rx)
        spi->DMAC.bit.RDMAE = 0;
}

STATIC_INLINE void SPI_setDMATriggerLevel(SPI_Type *spi, u8 tdl, u8 rdl)
{
    if (!spi)
        return;

    if (spi->DMAC.bit.TDMAE == 1)
        spi->DMATDL = tdl;

    if (spi->DMAC.bit.RDMAE == 1)
        spi->DMARDL = rdl;
}
#endif

#if SSI_HAS_RX_SAMPLE_DELAY == 1
STATIC_INLINE void SPI_setRXSampleDelay(SPI_Type *spi)
{
    if (!spi)
        return;

#ifdef SPI_RX_DLY_SR_DEPTH
    spi->RX_SAMPLE_DLY = SPI_RX_DLY_SR_DEPTH;
#else
    spi->RX_SAMPLE_DLY = 4;
#endif
}
#endif

void SPI_setTransferMode(SPI_Type *spi, SPI_TransferMode type);
void SPI_setSampleMode(SPI_Type *spi, SPI_SampleMode mode);
void SPI_setBaudrate(SPI_Type *spi, u32 clk_freq);
void SPI_setCLKDivider(SPI_Type *spi, u32 clkdiv);
void SPI_enableInterrupt(SPI_Type *spi, SPI_InterruptMask type);
void SPI_disableInterrupt(SPI_Type *spi, SPI_InterruptMask type);
void SPI_sendData(SPI_Type *spi, char *buf);
void SPI_receiveData(SPI_Type *spi, char *buf);
void SPI_sendDataWithPolling(SPI_Type *spi, char *buf, u32 length);
u32 SPI_recvDataWithPolling(SPI_Type *spi, char *buf);
void SPI_recvDataWithInterrupt(SPI_Type *spi);
void SPI_sendDataWithInterrupt(SPI_Type *spi);
void SPI_masterInit(SPI_Type *spi, SPI_Config *config);
void SPI_slaveInit(SPI_Type *spi, SPI_Config *config);

#if SSI_HAS_DMA == 1
void SPI_enableDMA(SPI_Type *spi, bool tx, bool rx);
void SPI_disableDMA(SPI_Type *spi, bool tx, bool rx);
void SPI_setDMATriggerLevel(SPI_Type *spi, u8 tdl, u8 rdl);
#endif

#ifdef __cplusplus
}
#endif

#endif
