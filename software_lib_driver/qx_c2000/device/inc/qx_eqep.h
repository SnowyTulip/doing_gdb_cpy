/**
 **************************************************************************
 * @file     qx_eqep.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_EQEP_H
#define QX_EQEP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"
#include "hw_eqep.h"

struct QDECCTL_BITS
{                   // bits description
    vu16 rsvd1 : 5; // 4:0 Reserved
    vu16 QSP   : 1; // 5 QEPS input polarity
    vu16 QIP   : 1; // 6 QEPI input polarity
    vu16 QBP   : 1; // 7 QEPB input polarity
    vu16 QAP   : 1; // 8 QEPA input polarity
    vu16 IGATE : 1; // 9 Index pulse gating option
    vu16 SWAP  : 1; // 10 CLK/DIR Signal Source for Position Counter
    vu16 XCR   : 1; // 11 External Clock Rate
    vu16 SPSEL : 1; // 12 Sync output pin selection
    vu16 SOEN  : 1; // 13 Sync output-enable
    vu16 QSRC  : 2; // 15:14 Position-counter source selection
};

union QDECCTL_REG
{
    vu16 all;
    struct QDECCTL_BITS bit;
};

struct QEPCTL_BITS
{                       // bits description
    vu16 WDE       : 1; // 0 QEP watchdog enable
    vu16 UTE       : 1; // 1 QEP unit timer enable
    vu16 QCLM      : 1; // 2 QEP capture latch mode
    vu16 QPEN      : 1; // 3 Quadrature postotion counter enable
    vu16 IEL       : 2; // 5:4 Index event latch
    vu16 SEL       : 1; // 6 Strobe event latch
    vu16 SWI       : 1; // 7 Software init position counter
    vu16 IEI       : 2; // 9:8 Index event init of position count
    vu16 SEI       : 2; // 11:10 Strobe event init
    vu16 PCRM      : 2; // 13:12 Postion counter reset
    vu16 FREE_SOFT : 2; // 15:14 Emulation mode
};

union QEPCTL_REG
{
    vu16 all;
    struct QEPCTL_BITS bit;
};

struct QCAPCTL_BITS
{                   // bits description
    vu16 UPPS  : 4; // 3:0 Unit position event prescaler
    vu16 CCPS  : 3; // 6:4 eQEP capture timer clock prescaler
    vu16 rsvd1 : 8; // 14:7 Reserved
    vu16 CEN   : 1; // 15 Enable eQEP capture
};

union QCAPCTL_REG
{
    vu16 all;
    struct QCAPCTL_BITS bit;
};

struct QPOSCTL_BITS
{                     // bits description
    vu16 PCSPW  : 12; // 11:0 Position compare sync pulse width
    vu16 PCE    : 1;  // 12 Position compare enable/disable
    vu16 PCPOL  : 1;  // 13 Polarity of sync output
    vu16 PCLOAD : 1;  // 14 Position compare of shadow load
    vu16 PCSHDW : 1;  // 15 Position compare of shadow enable
};

union QPOSCTL_REG
{
    vu16 all;
    struct QPOSCTL_BITS bit;
};

struct QEINT_BITS
{                   // bits description
    vu16 rsvd1 : 1; // 0 Reserved
    vu16 PCE   : 1; // 1 Position counter error interrupt enable
    vu16 QPE   : 1; // 2 Quadrature phase error interrupt enable
    vu16 QDC   : 1; // 3 Quadrature direction change interrupt enable
    vu16 WTO   : 1; // 4 Watchdog time out interrupt enable
    vu16 PCU   : 1; // 5 Position counter underflow interrupt enable
    vu16 PCO   : 1; // 6 Position counter overflow interrupt enable
    vu16 PCR   : 1; // 7 Position-compare ready interrupt enable
    vu16 PCM   : 1; // 8 Position-compare match interrupt enable
    vu16 SEL   : 1; // 9 Strobe event latch interrupt enable
    vu16 IEL   : 1; // 10 Index event latch interrupt enable
    vu16 UTO   : 1; // 11 Unit time out interrupt enable
    vu16 QMAE  : 1; // 12 QMA error interrupt enable
    vu16 rsvd2 : 3; // 15:13 Reserved
};

union QEINT_REG
{
    vu16 all;
    struct QEINT_BITS bit;
};

struct QFLG_BITS
{                   // bits description
    vu16 INT   : 1; // 0 Global interrupt status flag
    vu16 PCE   : 1; // 1 Position counter error interrupt flag
    vu16 PHE   : 1; // 2 Quadrature phase error interrupt flag
    vu16 QDC   : 1; // 3 Quadrature direction change interrupt flag
    vu16 WTO   : 1; // 4 Watchdog timeout interrupt flag
    vu16 PCU   : 1; // 5 Position counter underflow interrupt flag
    vu16 PCO   : 1; // 6 Position counter overflow interrupt flag
    vu16 PCR   : 1; // 7 Position-compare ready interrupt flag
    vu16 PCM   : 1; // 8 eQEP compare match event interrupt flag
    vu16 SEL   : 1; // 9 Strobe event latch interrupt flag
    vu16 IEL   : 1; // 10 Index event latch interrupt flag
    vu16 UTO   : 1; // 11 Unit time out interrupt flag
    vu16 QMAE  : 1; // 12 QMA error interrupt flag
    vu16 rsvd1 : 3; // 15:13 Reserved
};

union QFLG_REG
{
    vu16 all;
    struct QFLG_BITS bit;
};

struct QCLR_BITS
{                   // bits description
    vu16 INT   : 1; // 0 Global interrupt clear flag
    vu16 PCE   : 1; // 1 Clear position counter error interrupt flag
    vu16 PHE   : 1; // 2 Clear quadrature phase error interrupt flag
    vu16 QDC   : 1; // 3 Clear quadrature direction change interrupt flag
    vu16 WTO   : 1; // 4 Clear watchdog timeout interrupt flag
    vu16 PCU   : 1; // 5 Clear position counter underflow interrupt flag
    vu16 PCO   : 1; // 6 Clear position counter overflow interrupt flag
    vu16 PCR   : 1; // 7 Clear position-compare ready interrupt flag
    vu16 PCM   : 1; // 8 Clear eQEP compare match event interrupt flag
    vu16 SEL   : 1; // 9 Clear strobe event latch interrupt flag
    vu16 IEL   : 1; // 10 Clear index event latch interrupt flag
    vu16 UTO   : 1; // 11 Clear unit time out interrupt flag
    vu16 QMAE  : 1; // 12 Clear QMA error interrupt flag
    vu16 rsvd1 : 3; // 15:13 Reserved
};

union QCLR_REG
{
    vu16 all;
    struct QCLR_BITS bit;
};

struct QFRC_BITS
{                   // bits description
    vu16 rsvd1 : 1; // 0 Reserved
    vu16 PCE   : 1; // 1 Force position counter error interrupt
    vu16 PHE   : 1; // 2 Force quadrature phase error interrupt
    vu16 QDC   : 1; // 3 Force quadrature direction change interrupt
    vu16 WTO   : 1; // 4 Force watchdog time out interrupt
    vu16 PCU   : 1; // 5 Force position counter underflow interrupt
    vu16 PCO   : 1; // 6 Force position counter overflow interrupt
    vu16 PCR   : 1; // 7 Force position-compare ready interrupt
    vu16 PCM   : 1; // 8 Force position-compare match interrupt
    vu16 SEL   : 1; // 9 Force strobe event latch interrupt
    vu16 IEL   : 1; // 10 Force index event latch interrupt
    vu16 UTO   : 1; // 11 Force unit time out interrupt
    vu16 QMAE  : 1; // 12 Force QMA error interrupt
    vu16 rsvd2 : 3; // 15:13 Reserved
};

union QFRC_REG
{
    vu16 all;
    struct QFRC_BITS bit;
};

struct QEPSTS_BITS
{                    // bits description
    vu16 PCEF   : 1; // 0 Position counter error flag.
    vu16 FIMF   : 1; // 1 First index marker flag
    vu16 CDEF   : 1; // 2 Capture direction error flag
    vu16 COEF   : 1; // 3 Capture overflow error flag
    vu16 QDLF   : 1; // 4 eQEP direction latch flag
    vu16 QDF    : 1; // 5 Quadrature direction flag
    vu16 FIDF   : 1; // 6 The first index marker
    vu16 UPEVNT : 1; // 7 Unit position event flag
    vu16 rsvd1  : 8; // 15:8 Reserved
};

union QEPSTS_REG
{
    vu16 all;
    struct QEPSTS_BITS bit;
};

struct REV_BITS
{                    // bits description
    vu16 MAJOR : 3;  // 2:0 Major Revision Number
    vu16 MINOR : 3;  // 5:3 Minor Revision Number
    vu16 rsvd1 : 10; // 15:6 Reserved
    vu16 rsvd2 : 16; // 31:16 Reserved
};

union REV_REG
{
    vu32 all;
    struct REV_BITS bit;
};

struct QEPSTROBESEL_BITS
{                        // bits description
    vu16 STROBESEL : 2;  // 1:0 QMA Mode Select
    vu16 rsvd1     : 14; // 15:2 Reserved
    vu16 rsvd2     : 16; // 31:16 Reserved
};

union QEPSTROBESEL_REG
{
    vu32 all;
    struct QEPSTROBESEL_BITS bit;
};

struct QMACTRL_BITS
{                    // bits description
    vu16 MODE  : 3;  // 2:0 QMA Mode Select
    vu16 rsvd1 : 13; // 15:3 Reserved
    vu16 rsvd2 : 16; // 31:16 Reserved
};

union QMACTRL_REG
{
    vu32 all;
    struct QMACTRL_BITS bit;
};

struct EQEP_REGS
{
    vu32 QPOSCNT;                        // Position Counter
    vu32 QPOSINIT;                       // Position Counter Init
    vu32 QPOSMAX;                        // Maximum Position Count
    vu32 QPOSCMP;                        // Position Compare
    vu32 QPOSILAT;                       // Index Position Latch
    vu32 QPOSSLAT;                       // Strobe Position Latch
    vu32 QPOSLAT;                        // Position Latch
    vu32 QUTMR;                          // QEP Unit Timer
    vu32 QUPRD;                          // QEP Unit Period
    vu16 QWDTMR;                         // QEP Watchdog Timer
    vu16 QWDPRD;                         // QEP Watchdog Period
    union QDECCTL_REG QDECCTL;           // Quadrature Decoder Control
    union QEPCTL_REG QEPCTL;             // QEP Control
    union QCAPCTL_REG QCAPCTL;           // Qaudrature Capture Control
    union QPOSCTL_REG QPOSCTL;           // Position Compare Control
    union QEINT_REG QEINT;               // QEP Interrupt Control
    union QFLG_REG QFLG;                 // QEP Interrupt Flag
    union QCLR_REG QCLR;                 // QEP Interrupt Clear
    union QFRC_REG QFRC;                 // QEP Interrupt Force
    union QEPSTS_REG QEPSTS;             // QEP Status
    vu16 QCTMR;                          // QEP Capture Timer
    vu16 QCPRD;                          // QEP Capture Period
    vu16 QCTMRLAT;                       // QEP Capture Latch
    vu16 QCPRDLAT;                       // QEP Capture Period Latch
    vu16 rsvd1[15];                      // Reserved
    union REV_REG REV;                   // QEP Revision Number
    union QEPSTROBESEL_REG QEPSTROBESEL; // QEP Strobe select register
    union QMACTRL_REG QMACTRL;           // QMA Control register
};

#define EQep1Regs ((struct EQEP_REGS *)EQEP1_BASE)
#define EQep2Regs ((struct EQEP_REGS *)EQEP2_BASE)

//
// Operation Mode
//
#define EQEP_CONFIG_QUADRATURE 0x0000U //!< Quadrature-clock mode
#define EQEP_CONFIG_CLOCK_DIR  0x4000U //!< Direction-count mode
#define EQEP_CONFIG_UP_COUNT   0x8000U //!< Up-count mode, QDIR = 1
#define EQEP_CONFIG_DOWN_COUNT 0xC000U //!< Down-count mode, QDIR = 0

//
// Resolution
//
#define EQEP_CONFIG_2X_RESOLUTION 0x0000U //!< Count rising and falling edge
#define EQEP_CONFIG_1X_RESOLUTION 0x0800U //!< Count rising edge only

//
// Swap QEPA and QEPB
//
#define EQEP_CONFIG_NO_SWAP 0x0000U //!< Do not swap QEPA and QEPB
#define EQEP_CONFIG_SWAP    0x0400U //!< Swap QEPA and QEPB

//
// Index pulse gating option
//
#define EQEP_CONFIG_IGATE_DISABLE 0x0000U //!< Disable gating of Index pulse
#define EQEP_CONFIG_IGATE_ENABLE  0x0200U //!< Gate the index pin with strobe

//*****************************************************************************

//
// Values that can be passed to EQEP_setCompareConfig() as the config
// parameter.
//
//*****************************************************************************

//
// Sync pulse pin
//
#define EQEP_COMPARE_NO_SYNC_OUT     0x0000U //!< Disable sync output
#define EQEP_COMPARE_IDX_SYNC_OUT    0x2000U //!< Sync output on index pin
#define EQEP_COMPARE_STROBE_SYNC_OUT 0x3000U //!< Sync output on strobe pin

//
// Shadow register use
//
#define EQEP_COMPARE_NO_SHADOW     0x0000U //!< Disable shadow of QPOSCMP
#define EQEP_COMPARE_LOAD_ON_ZERO  0x8000U //!< Load on QPOSCNT = 0
#define EQEP_COMPARE_LOAD_ON_MATCH 0xC000U //!< Load on QPOSCNT = QPOSCMP

//*****************************************************************************
//
// Values that can be passed to EQEP_enableInterrupt(),
// EQEP_disableInterrupt(), and EQEP_clearInterruptStatus() as the
// intFlags parameter and returned by EQEP_clearInterruptStatus().
//
//*****************************************************************************
#define EQEP_INT_GLOBAL            0x0001U //!< Global interrupt flag
#define EQEP_INT_POS_CNT_ERROR     0x0002U //!< Position counter error
#define EQEP_INT_PHASE_ERROR       0x0004U //!< Quadrature phase error
#define EQEP_INT_DIR_CHANGE        0x0008U //!< Quadrature direction change
#define EQEP_INT_WATCHDOG          0x0010U //!< Watchdog time-out
#define EQEP_INT_UNDERFLOW         0x0020U //!< Position counter underflow
#define EQEP_INT_OVERFLOW          0x0040U //!< Position counter overflow
#define EQEP_INT_POS_COMP_READY    0x0080U //!< Position-compare ready
#define EQEP_INT_POS_COMP_MATCH    0x0100U //!< Position-compare match
#define EQEP_INT_STROBE_EVNT_LATCH 0x0200U //!< Strobe event latch
#define EQEP_INT_INDEX_EVNT_LATCH  0x0400U //!< Index event latch
#define EQEP_INT_UNIT_TIME_OUT     0x0800U //!< Unit time-out
#define EQEP_INT_QMA_ERROR         0x1000U //!< QMA error

//*****************************************************************************
//
// Values that can be returned by EQEP_getStatus().
//
//*****************************************************************************
//! Unit position event detected
#define EQEP_STS_UNIT_POS_EVNT 0x0080U
//! Direction was clockwise on first index event
#define EQEP_STS_DIR_ON_1ST_IDX 0x0040U
//! Direction is CW (forward)
#define EQEP_STS_DIR_FLAG 0x0020U
//! Direction was CW on index
#define EQEP_STS_DIR_LATCH 0x0010U
//! Capture timer overflow
#define EQEP_STS_CAP_OVRFLW_ERROR 0x0008U
//! Direction changed between position capture events
#define EQEP_STS_CAP_DIR_ERROR 0x0004U
//! First index pulse occurred
#define EQEP_STS_1ST_IDX_FLAG 0x0002U
//! Position counter error
#define EQEP_STS_POS_CNT_ERROR 0x0001U

//*****************************************************************************
//
// Values that can be passed to EQEP_setLatchMode() as the latchMode parameter.
//
//*****************************************************************************

//
// Position counter latch event
//
#define EQEP_LATCH_CNT_READ_BY_CPU 0x0000U //!< On position counter read
#define EQEP_LATCH_UNIT_TIME_OUT   0x0004U //!< On unit time-out event

//
// Strobe position counter latch event
//
//! On rising edge of strobe
#define EQEP_LATCH_RISING_STROBE 0x0000U
//! On rising edge when clockwise, on falling when counter clockwise
#define EQEP_LATCH_EDGE_DIR_STROBE 0x0040U

//
// Index position counter latch event
//
#define EQEP_LATCH_RISING_INDEX  0x0010U //!< On rising edge of index
#define EQEP_LATCH_FALLING_INDEX 0x0020U //!< On falling edge of index

#define EQEP_LATCH_SW_INDEX_MARKER 0x0030U //!< On software index marker

//*****************************************************************************
//
// Values that can be passed to EQEP_setPositionInitMode() as the initMode
// parameter.
//
//*****************************************************************************
#define EQEP_INIT_DO_NOTHING 0x0000U //!< Action is disabled

//
// Strobe events
//
//! On rising edge of strobe
#define EQEP_INIT_RISING_STROBE 0x0800U
//! On rising edge when clockwise, on falling when counter clockwise
#define EQEP_INIT_EDGE_DIR_STROBE 0x0C00U

//
// Index events
//
#define EQEP_INIT_RISING_INDEX  0x0200U //!< On rising edge of index
#define EQEP_INIT_FALLING_INDEX 0x0300U //!< On falling edge of index

//*****************************************************************************
//
//! Values that can be passed to EQEP_setPositionCounterConfig() as the \e mode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! Reset position on index pulse
    EQEP_POSITION_RESET_IDX = 0x0000,
    //! Reset position on maximum position
    EQEP_POSITION_RESET_MAX_POS = 0x1000,
    //! Reset position on the first index pulse
    EQEP_POSITION_RESET_1ST_IDX = 0x2000,
    //! Reset position on a unit time event
    EQEP_POSITION_RESET_UNIT_TIME_OUT = 0x3000
} EQEP_PositionResetMode;

//*****************************************************************************
//
//! Values that can be passed to EQEP_setCaptureConfig() as the \e capPrescale
//! parameter. CAPCLK is the capture timer clock frequency.
//
//*****************************************************************************
typedef enum
{
    EQEP_CAPTURE_CLK_DIV_1   = 0x00, //!< CAPCLK = SYSCLKOUT/1
    EQEP_CAPTURE_CLK_DIV_2   = 0x10, //!< CAPCLK = SYSCLKOUT/2
    EQEP_CAPTURE_CLK_DIV_4   = 0x20, //!< CAPCLK = SYSCLKOUT/4
    EQEP_CAPTURE_CLK_DIV_8   = 0x30, //!< CAPCLK = SYSCLKOUT/8
    EQEP_CAPTURE_CLK_DIV_16  = 0x40, //!< CAPCLK = SYSCLKOUT/16
    EQEP_CAPTURE_CLK_DIV_32  = 0x50, //!< CAPCLK = SYSCLKOUT/32
    EQEP_CAPTURE_CLK_DIV_64  = 0x60, //!< CAPCLK = SYSCLKOUT/64
    EQEP_CAPTURE_CLK_DIV_128 = 0x70  //!< CAPCLK = SYSCLKOUT/128
} EQEP_CAPCLKPrescale;

//*****************************************************************************
//
//! Values that can be passed to EQEP_setCaptureConfig() as the \e evntPrescale
//! parameter. UPEVNT is the unit position event frequency.
//
//*****************************************************************************
typedef enum
{
    EQEP_UNIT_POS_EVNT_DIV_1,    //!< UPEVNT = QCLK/1
    EQEP_UNIT_POS_EVNT_DIV_2,    //!< UPEVNT = QCLK/2
    EQEP_UNIT_POS_EVNT_DIV_4,    //!< UPEVNT = QCLK/4
    EQEP_UNIT_POS_EVNT_DIV_8,    //!< UPEVNT = QCLK/8
    EQEP_UNIT_POS_EVNT_DIV_16,   //!< UPEVNT = QCLK/16
    EQEP_UNIT_POS_EVNT_DIV_32,   //!< UPEVNT = QCLK/32
    EQEP_UNIT_POS_EVNT_DIV_64,   //!< UPEVNT = QCLK/64
    EQEP_UNIT_POS_EVNT_DIV_128,  //!< UPEVNT = QCLK/128
    EQEP_UNIT_POS_EVNT_DIV_256,  //!< UPEVNT = QCLK/256
    EQEP_UNIT_POS_EVNT_DIV_512,  //!< UPEVNT = QCLK/512
    EQEP_UNIT_POS_EVNT_DIV_1024, //!< UPEVNT = QCLK/1024
    EQEP_UNIT_POS_EVNT_DIV_2048  //!< UPEVNT = QCLK/2048
} EQEP_UPEVNTPrescale;

//*****************************************************************************
//
//! Values that can be passed to EQEP_setStrobeSource() as the \e strobeSrc
//! parameter.
//
//*****************************************************************************
typedef enum
{
    EQEP_STROBE_FROM_GPIO  = 0, //!< Strobe signal comes from GPIO
    EQEP_STROBE_OR_ADCSOCA = 2, //!< Strobe signal is OR'd with ADCSOCA
    EQEP_STROBE_OR_ADCSOCB = 3  //!< Strobe signal is OR'd with ADCSOCB
} EQEP_StrobeSource;

//*****************************************************************************
//
//! Values that can be passed to EQEP_setQMAModuleMode() as the \e qmaMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    EQEP_QMA_MODE_BYPASS, //!< QMA module is bypassed
    EQEP_QMA_MODE_1,      //!< QMA mode-1 operation is selected
    EQEP_QMA_MODE_2       //!< QMA mode-2 operation is selected
} EQEP_QMAMode;

//*****************************************************************************
//
//! Values that can be passed to EQEP_setEmulationMode() as the \e emuMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    EQEP_EMULATIONMODE_STOPIMMEDIATELY, //!< Counters stop immediately
    EQEP_EMULATIONMODE_STOPATROLLOVER,  //!< Counters stop at period rollover
    EQEP_EMULATIONMODE_RUNFREE          //!< Counter unaffected by suspend
} EQEP_EmulationMode;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks an eQEP base address.
//!
//! \param base specifies the eQEP module base address.
//!
//! This function determines if a eQEP module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool EQEP_isBaseValid(uint32_t base)
{
    return ((base == EQEP1_BASE) || (base == EQEP2_BASE));
}
#endif

//*****************************************************************************
//
//! Enables the eQEP module.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function enables operation of the enhanced quadrature encoder pulse
//! (eQEP) module.  The module must be configured before it is enabled.
//!
//! \sa EQEP_setConfig()
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Enable the eQEP module.
    //
    HWREGH(base + EQEP_O_QEPCTL) |= EQEP_QEPCTL_QPEN;
}

//*****************************************************************************
//
//! Disables the eQEP module.
//!
//! \param base is the base address of the enhanced quadrature encoder pulse
//! (eQEP) module
//!
//! This function disables operation of the eQEP module.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Disable the eQEP module.
    //
    HWREGH(base + EQEP_O_QEPCTL) &= ~(EQEP_QEPCTL_QPEN);
}

//*****************************************************************************
//
//! Configures eQEP module's quadrature decoder unit.
//!
//! \param base is the base address of the eQEP module.
//! \param config is the configuration for the eQEP module decoder unit.
//!
//! This function configures the operation of the eQEP module's quadrature
//! decoder unit.  The \e config parameter provides the configuration
//! of the decoder and is the logical OR of several values:
//!
//! - \b EQEP_CONFIG_2X_RESOLUTION or \b EQEP_CONFIG_1X_RESOLUTION specify
//!   if both rising and falling edges should be counted or just rising edges.
//! - \b EQEP_CONFIG_QUADRATURE, \b EQEP_CONFIG_CLOCK_DIR,
//!   \b EQEP_CONFIG_UP_COUNT, or \b EQEP_CONFIG_DOWN_COUNT specify if
//!   quadrature signals are being provided on QEPA and QEPB, if a direction
//!   signal and a clock are being provided, or if the direction should be
//!   hard-wired for a single direction with QEPA used for input.
//! - \b EQEP_CONFIG_NO_SWAP or \b EQEP_CONFIG_SWAP to specify if the
//!   signals provided on QEPA and QEPB should be swapped before being
//!   processed.
//! - \b EQEP_CONFIG_IGATE_DISABLE or \b EQEP_CONFIG_IGATE_ENABLE to specify
//!   if the gating of the index pulse should be enabled or disabled
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_setDecoderConfig(uint32_t base, uint16_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Write the new decoder configuration to the hardware.
    //
    HWREGH(base + EQEP_O_QDECCTL)
        = (HWREGH(base + EQEP_O_QDECCTL)
              & ~(EQEP_QDECCTL_SWAP | EQEP_QDECCTL_XCR | EQEP_QDECCTL_QSRC_M | EQEP_QDECCTL_IGATE))
          | config;
}

//*****************************************************************************
//
//! Configures eQEP module position counter unit.
//!
//! \param base is the base address of the eQEP module.
//! \param mode is the configuration for the eQEP module position counter.
//! \param maxPosition specifies the maximum position value.
//!
//! This function configures the operation of the eQEP module position
//! counter.  The \e mode parameter determines the event on which the position
//! counter gets reset. It should be passed one of the following values:
//! \b EQEP_POSITION_RESET_IDX, \b EQEP_POSITION_RESET_MAX_POS,
//! \b EQEP_POSITION_RESET_1ST_IDX, or \b EQEP_POSITION_RESET_UNIT_TIME_OUT.
//!
//! \e maxPosition is the maximum value of the position counter and is
//! the value used to reset the position capture when moving in the reverse
//! (negative) direction.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_setPositionCounterConfig(uint32_t base, EQEP_PositionResetMode mode, uint32_t maxPosition)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Write the position counter reset configuration to the hardware.
    //
    HWREGH(base + EQEP_O_QEPCTL) = (HWREGH(base + EQEP_O_QEPCTL) & ~EQEP_QEPCTL_PCRM_M) | (uint16_t)mode;

    //
    // Set the maximum position.
    //
    HWREG(base + EQEP_O_QPOSMAX) = maxPosition;
}

//*****************************************************************************
//
//! Gets the current encoder position.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function returns the current position of the encoder.  Depending upon
//! the configuration of the encoder, and the incident of an index pulse, this
//! value may or may not contain the expected data (that is, if in reset on
//! index mode, if an index pulse has not been encountered, the position
//! counter is not yet aligned with the index pulse).
//!
//! \return The current position of the encoder.
//
//*****************************************************************************
static inline uint32_t EQEP_getPosition(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Return the current position counter.
    //
    return (HWREG(base + EQEP_O_QPOSCNT));
}

//*****************************************************************************
//
//! Sets the current encoder position.
//!
//! \param base is the base address of the eQEP module.
//! \param position is the new position for the encoder.
//!
//! This function sets the current position of the encoder; the encoder
//! position is then measured relative to this value.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_setPosition(uint32_t base, uint32_t position)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Set the position counter.
    //
    HWREG(base + EQEP_O_QPOSCNT) = position;
}

//*****************************************************************************
//
//! Gets the current direction of rotation.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function returns the current direction of rotation.  In this case,
//! current means the most recently detected direction of the encoder; it may
//! not be presently moving but this is the direction it last moved before it
//! stopped.
//!
//! \return Returns 1 if moving in the forward direction or -1 if moving in the
//! reverse direction.
//
//*****************************************************************************
static inline int16_t EQEP_getDirection(uint32_t base)
{
    int16_t direction;

    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Return the direction of rotation.
    //
    if ((HWREGH(base + EQEP_O_QEPSTS) & EQEP_QEPSTS_QDF) != 0U)
    {
        direction = 1;
    }
    else
    {
        direction = -1;
    }

    return (direction);
}

//*****************************************************************************
//
//! Enables individual eQEP module interrupt sources.
//!
//! \param base is the base address of the eQEP module.
//! \param intFlags is a bit mask of the interrupt sources to be enabled.
//!
//! This function enables eQEP module interrupt sources. The \e intFlags
//! parameter can be any of the following values OR'd together:
//! - \b EQEP_INT_POS_CNT_ERROR - Position counter error
//! - \b EQEP_INT_PHASE_ERROR - Quadrature phase error
//! - \b EQEP_INT_DIR_CHANGE - Quadrature direction change
//! - \b EQEP_INT_WATCHDOG - Watchdog time-out
//! - \b EQEP_INT_UNDERFLOW - Position counter underflow
//! - \b EQEP_INT_OVERFLOW - Position counter overflow
//! - \b EQEP_INT_POS_COMP_READY - Position-compare ready
//! - \b EQEP_INT_POS_COMP_MATCH - Position-compare match
//! - \b EQEP_INT_STROBE_EVNT_LATCH - Strobe event latch
//! - \b EQEP_INT_INDEX_EVNT_LATCH - Index event latch
//! - \b EQEP_INT_UNIT_TIME_OUT - Unit time-out
//! - \b EQEP_INT_QMA_ERROR - QMA error
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_enableInterrupt(uint32_t base, uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Enable the specified interrupts.
    //
    HWREGH(base + EQEP_O_QEINT) |= intFlags;
}

//*****************************************************************************
//
//! Disables individual eQEP module interrupt sources.
//!
//! \param base is the base address of the eQEP module.
//! \param intFlags is a bit mask of the interrupt sources to be disabled.
//!
//! This function disables eQEP module interrupt sources. The \e intFlags
//! parameter can be any of the following values OR'd together:
//! - \b EQEP_INT_POS_CNT_ERROR - Position counter error
//! - \b EQEP_INT_PHASE_ERROR - Quadrature phase error
//! - \b EQEP_INT_DIR_CHANGE - Quadrature direction change
//! - \b EQEP_INT_WATCHDOG - Watchdog time-out
//! - \b EQEP_INT_UNDERFLOW - Position counter underflow
//! - \b EQEP_INT_OVERFLOW - Position counter overflow
//! - \b EQEP_INT_POS_COMP_READY - Position-compare ready
//! - \b EQEP_INT_POS_COMP_MATCH - Position-compare match
//! - \b EQEP_INT_STROBE_EVNT_LATCH - Strobe event latch
//! - \b EQEP_INT_INDEX_EVNT_LATCH - Index event latch
//! - \b EQEP_INT_UNIT_TIME_OUT - Unit time-out
//! - \b EQEP_INT_QMA_ERROR - QMA error
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_disableInterrupt(uint32_t base, uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Disable the specified interrupts.
    //
    HWREGH(base + EQEP_O_QEINT) &= ~(intFlags);
}

//*****************************************************************************
//
//! Gets the current interrupt status.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function returns the interrupt status for the eQEP module
//! module.
//!
//! \return Returns the current interrupt status, enumerated as a bit field of
//! the following values:
//! - \b EQEP_INT_GLOBAL - Global interrupt flag
//! - \b EQEP_INT_POS_CNT_ERROR - Position counter error
//! - \b EQEP_INT_PHASE_ERROR - Quadrature phase error
//! - \b EQEP_INT_DIR_CHANGE - Quadrature direction change
//! - \b EQEP_INT_WATCHDOG - Watchdog time-out
//! - \b EQEP_INT_UNDERFLOW - Position counter underflow
//! - \b EQEP_INT_OVERFLOW - Position counter overflow
//! - \b EQEP_INT_POS_COMP_READY - Position-compare ready
//! - \b EQEP_INT_POS_COMP_MATCH - Position-compare match
//! - \b EQEP_INT_STROBE_EVNT_LATCH - Strobe event latch
//! - \b EQEP_INT_INDEX_EVNT_LATCH - Index event latch
//! - \b EQEP_INT_UNIT_TIME_OUT - Unit time-out
//! - \b EQEP_INT_QMA_ERROR - QMA error
//
//*****************************************************************************
static inline uint16_t EQEP_getInterruptStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    return (HWREGH(base + EQEP_O_QFLG));
}

//*****************************************************************************
//
//! Clears eQEP module interrupt sources.
//!
//! \param base is the base address of the eQEP module.
//! \param intFlags is a bit mask of the interrupt sources to be cleared.
//!
//! This function clears eQEP module interrupt flags. The \e intFlags
//! parameter can be any of the following values OR'd together:
//! - \b EQEP_INT_GLOBAL - Global interrupt flag
//! - \b EQEP_INT_POS_CNT_ERROR - Position counter error
//! - \b EQEP_INT_PHASE_ERROR - Quadrature phase error
//! - \b EQEP_INT_DIR_CHANGE - Quadrature direction change
//! - \b EQEP_INT_WATCHDOG - Watchdog time-out
//! - \b EQEP_INT_UNDERFLOW - Position counter underflow
//! - \b EQEP_INT_OVERFLOW - Position counter overflow
//! - \b EQEP_INT_POS_COMP_READY - Position-compare ready
//! - \b EQEP_INT_POS_COMP_MATCH - Position-compare match
//! - \b EQEP_INT_STROBE_EVNT_LATCH - Strobe event latch
//! - \b EQEP_INT_INDEX_EVNT_LATCH - Index event latch
//! - \b EQEP_INT_UNIT_TIME_OUT - Unit time-out
//! - \b EQEP_INT_QMA_ERROR - QMA error
//!
//! Note that the \b EQEP_INT_GLOBAL value is the global interrupt flag. In
//! order to get any further eQEP interrupts, this flag must be cleared.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_clearInterruptStatus(uint32_t base, uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Clear the requested interrupt sources.
    //
    HWREGH(base + EQEP_O_QCLR) = intFlags;
}

//*****************************************************************************
//
//! Forces individual eQEP module interrupts.
//!
//! \param base is the base address of the eQEP module.
//! \param intFlags is a bit mask of the interrupt sources to be forced.
//!
//! This function forces eQEP module interrupt flags. The \e intFlags
//! parameter can be any of the following values OR'd together:
//! - \b EQEP_INT_POS_CNT_ERROR
//! - \b EQEP_INT_PHASE_ERROR
//! - \b EQEP_INT_DIR_CHANGE
//! - \b EQEP_INT_WATCHDOG
//! - \b EQEP_INT_UNDERFLOW
//! - \b EQEP_INT_OVERFLOW
//! - \b EQEP_INT_POS_COMP_READY
//! - \b EQEP_INT_POS_COMP_MATCH
//! - \b EQEP_INT_STROBE_EVNT_LATCH
//! - \b EQEP_INT_INDEX_EVNT_LATCH
//! - \b EQEP_INT_UNIT_TIME_OUT
//! - \b EQEP_INT_QMA_ERROR
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_forceInterrupt(uint32_t base, uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Force the specified interrupts.
    //
    HWREGH(base + EQEP_O_QFRC) |= intFlags;
}

//*****************************************************************************
//
//! Gets the encoder error indicator.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function returns the error indicator for the eQEP module.  It is an
//! error for both of the signals of the quadrature input to change at the same
//! time.
//!
//! \return Returns \b true if an error has occurred and \b false otherwise.
//
//*****************************************************************************
static inline bool EQEP_getError(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Return the error indicator.
    //
    return ((HWREGH(base + EQEP_O_QFLG) & EQEP_QFLG_PHE) != 0U);
}

//*****************************************************************************
//
//! Returns content of the eQEP module status register
//!
//! \param base is the base address of the eQEP module.
//!
//! This function returns the contents of the status register.  The value it
//! returns is an OR of the following values:
//!
//! - \b EQEP_STS_UNIT_POS_EVNT - Unit position event detected
//! - \b EQEP_STS_DIR_ON_1ST_IDX - If set, clockwise rotation (forward
//!   movement) occurred on the first index event
//! - \b EQEP_STS_DIR_FLAG - If set, movement is clockwise rotation
//! - \b EQEP_STS_DIR_LATCH - If set, clockwise rotation occurred on last
//!   index event marker
//! - \b EQEP_STS_CAP_OVRFLW_ERROR - Overflow occurred in eQEP capture timer
//! - \b EQEP_STS_CAP_DIR_ERROR - Direction change occurred between position
//!   capture events
//! - \b EQEP_STS_1ST_IDX_FLAG - Set by the occurrence of the first index
//!   pulse
//! - \b EQEP_STS_POS_CNT_ERROR - Position counter error occurred
//!
//! \return Returns the value of the QEP status register.
//
//*****************************************************************************
static inline uint16_t EQEP_getStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Return the status register.
    //
    return (HWREGH(base + EQEP_O_QEPSTS) & 0x00FFU);
}

//*****************************************************************************
//
//! Clears selected fields of the eQEP module status register
//!
//! \param base is the base address of the eQEP module.
//! \param statusFlags is the bit mask of the status flags to be cleared.
//!
//! This function clears the status register fields indicated by
//! \e statusFlags. The \e statusFlags parameter is the logical OR of any of
//! the following:
//!
//! - \b EQEP_STS_UNIT_POS_EVNT - Unit position event detected
//! - \b EQEP_STS_CAP_OVRFLW_ERROR - Overflow occurred in eQEP capture timer
//! - \b EQEP_STS_CAP_DIR_ERROR - Direction change occurred between position
//!   capture events
//! - \b EQEP_STS_1ST_IDX_FLAG - Set by the occurrence of the first index
//!   pulse
//!
//! \note Only the above status fields can be cleared. All others are
//! read-only, non-sticky fields.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_clearStatus(uint32_t base, uint16_t statusFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Clear the requested interrupt sources.
    //
    HWREGH(base + EQEP_O_QEPSTS) = statusFlags;
}

//*****************************************************************************
//
//! Configures eQEP module edge-capture unit.
//!
//! \param base is the base address of the eQEP module.
//! \param capPrescale is the prescaler setting of the eQEP capture timer clk.
//! \param evntPrescale is the prescaler setting of the unit position event
//! frequency.
//!
//! This function configures the operation of the eQEP module edge-capture
//! unit.  The \e capPrescale parameter provides the configuration of the eQEP
//! capture timer clock rate. It determines by which power of 2 between 1 and
//! 128 inclusive SYSCLKOUT is divided. The macros for this parameter are in
//! the format of EQEP_CAPTURE_CLK_DIV_X, where X is the divide value. For
//! example, \b EQEP_CAPTURE_CLK_DIV_32 will give a capture timer clock
//! frequency that is SYSCLKOUT/32.
//!
//! The \e evntPrescale parameter determines how frequently a unit position
//! event occurs. The macro that can be passed this parameter is in the format
//! EQEP_UNIT_POS_EVNT_DIV_X, where X is the number of quadrature clock
//! periods between unit position events. For example,
//! \b EQEP_UNIT_POS_EVNT_DIV_16 will result in a unit position event
//! frequency of QCLK/16.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_setCaptureConfig(
    uint32_t base, EQEP_CAPCLKPrescale capPrescale, EQEP_UPEVNTPrescale evntPrescale)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Write new prescaler configurations to the appropriate registers.
    //
    HWREGH(base + EQEP_O_QCAPCTL) = (HWREGH(base + EQEP_O_QCAPCTL) & ~(EQEP_QCAPCTL_UPPS_M | EQEP_QCAPCTL_CCPS_M))
                                    | ((uint16_t)evntPrescale | (uint16_t)capPrescale);
}

//*****************************************************************************
//
//! Enables the eQEP module edge-capture unit.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function enables operation of the eQEP module's edge-capture unit.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_enableCapture(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Enable edge capture.
    //
    HWREGH(base + EQEP_O_QCAPCTL) |= EQEP_QCAPCTL_CEN;
}

//*****************************************************************************
//
//! Disables the eQEP module edge-capture unit.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function disables operation of the eQEP module's edge-capture unit.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_disableCapture(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Disable edge capture.
    //
    HWREGH(base + EQEP_O_QCAPCTL) &= ~(EQEP_QCAPCTL_CEN);
}

//*****************************************************************************
//
//! Gets the encoder capture period.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function returns the period count value between the last successive
//! eQEP position events.
//!
//! \return The period count value between the last successive position events.
//
//*****************************************************************************
static inline uint16_t EQEP_getCapturePeriod(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Return the capture period.
    //
    return (HWREGH(base + EQEP_O_QCPRD));
}

//*****************************************************************************
//
//! Gets the encoder capture timer value.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function returns the time base for the edge capture unit.
//!
//! \return The capture timer value.
//
//*****************************************************************************
static inline uint16_t EQEP_getCaptureTimer(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Return the capture timer value.
    //
    return (HWREGH(base + EQEP_O_QCTMR));
}

//*****************************************************************************
//
//! Enables the eQEP module position-compare unit.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function enables operation of the eQEP module's position-compare unit.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_enableCompare(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Enable position compare.
    //
    HWREGH(base + EQEP_O_QPOSCTL) |= EQEP_QPOSCTL_PCE;
}

//*****************************************************************************
//
//! Disables the eQEP module position-compare unit.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function disables operation of the eQEP module's position-compare
//! unit.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_disableCompare(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Disable position compare.
    //
    HWREGH(base + EQEP_O_QPOSCTL) &= ~(EQEP_QPOSCTL_PCE);
}

//*****************************************************************************
//
//! Configures the position-compare unit's sync output pulse width.
//!
//! \param base is the base address of the eQEP module.
//! \param cycles is the width of the pulse that can be generated on a
//! position-compare event.  It is in units of 4 SYSCLKOUT cycles.
//!
//! This function configures the width of the sync output pulse.  The width of
//! the pulse will be \e cycles * 4 * the width of a SYSCLKOUT cycle.  The
//! maximum width is 4096 * 4 * SYSCLKOUT cycles.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_setComparePulseWidth(uint32_t base, uint16_t cycles)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));
    ASSERT(cycles <= (EQEP_QPOSCTL_PCSPW_M + 1U));

    //
    // Set the pulse width.
    //
    HWREGH(base + EQEP_O_QPOSCTL) = (HWREGH(base + EQEP_O_QPOSCTL) & ~(uint16_t)EQEP_QPOSCTL_PCSPW_M) | (cycles - 1U);
}

//*****************************************************************************
//
//! Loads the eQEP module unit timer period as number of SYSCLK cycles.
//!
//! \param base is the base address of the eQEP module.
//! \param period is period value at which a unit time-out interrupt is set.
//!
//! This function sets the unit time-out interrupt when it matches the value
//! specified by \e period
//! The unit timer is clocked by SYSCLKOUT
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_loadUnitTimer(uint32_t base, uint32_t period)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Set the period of the unit timer.
    //
    HWREG(base + EQEP_O_QUPRD) = period;
}

//*****************************************************************************
//
//! Enables the eQEP module unit timer.
//!
//! \param base is the base address of the eQEP module.
//! \param period is period value at which a unit time-out interrupt is set.
//!
//! This function enables operation of the eQEP module's peripheral unit timer.
//! The unit timer is clocked by SYSCLKOUT and will set the unit time-out
//! interrupt when it matches the value specified by \e period.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_enableUnitTimer(uint32_t base, uint32_t period)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Set the period of the unit timer.
    //
    HWREG(base + EQEP_O_QUPRD) = period;

    //
    // Enable peripheral unit timer.
    //
    HWREGH(base + EQEP_O_QEPCTL) |= EQEP_QEPCTL_UTE;
}

//*****************************************************************************
//
//! Disables the eQEP module unit timer.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function disables operation of the eQEP module's peripheral
//! unit timer.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_disableUnitTimer(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Disable peripheral unit timer.
    //
    HWREGH(base + EQEP_O_QEPCTL) &= ~(EQEP_QEPCTL_UTE);
}

//*****************************************************************************
//
//! Enables the eQEP module watchdog timer.
//!
//! \param base is the base address of the eQEP module.
//! \param period is watchdog period value at which a time-out will occur if
//! no quadrature-clock event is detected.
//!
//! This function enables operation of the eQEP module's peripheral watchdog
//! timer.
//!
//! \note When selecting \e period, note that the watchdog timer is clocked
//! from SYSCLKOUT/64.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_enableWatchdog(uint32_t base, uint16_t period)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Set the timeout count for the eQEP peripheral watchdog timer.
    //
    HWREGH(base + EQEP_O_QWDPRD) = period;

    //
    // Enable peripheral watchdog.
    //
    HWREGH(base + EQEP_O_QEPCTL) |= EQEP_QEPCTL_WDE;
}

//*****************************************************************************
//
//! Disables the eQEP module watchdog timer.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function disables operation of the eQEP module's peripheral watchdog
//! timer.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_disableWatchdog(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Disable peripheral watchdog.
    //
    HWREGH(base + EQEP_O_QEPCTL) &= ~(EQEP_QEPCTL_WDE);
}

//*****************************************************************************
//
//! Sets the eQEP module watchdog timer value.
//!
//! \param base is the base address of the eQEP module.
//! \param value is the value to be written to the watchdog timer.
//!
//! This function sets the eQEP module's watchdog timer value.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_setWatchdogTimerValue(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Write the value to the watchdog timer register.
    //
    HWREGH(base + EQEP_O_QWDTMR) = value;
}

//*****************************************************************************
//
//! Gets the eQEP module watchdog timer value.
//!
//! \param base is the base address of the eQEP module.
//!
//! \return Returns the current watchdog timer value.
//
//*****************************************************************************
static inline uint16_t EQEP_getWatchdogTimerValue(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Read the value from the watchdog timer register.
    //
    return (HWREGH(base + EQEP_O_QWDTMR));
}

//*****************************************************************************
//
//! Configures the mode in which the position counter is initialized.
//!
//! \param base is the base address of the eQEP module.
//! \param initMode is the configuration for initializing the position count.
//! See below for a description of this parameter.
//!
//! This function configures the events on which the position count can be
//! initialized.  The \e initMode parameter provides the mode as either
//! \b EQEP_INIT_DO_NOTHING (no action configured) or one of the following
//! strobe events, index events, or a logical OR of both a strobe event and an
//! index event.
//!
//! - \b EQEP_INIT_RISING_STROBE or \b EQEP_INIT_EDGE_DIR_STROBE specify
//!   which strobe event will initialize the position counter.
//! - \b EQEP_INIT_RISING_INDEX or \b EQEP_INIT_FALLING_INDEX specify
//!   which index event will initialize the position counter.
//!
//! Use EQEP_setSWPositionInit() to cause a software initialization and
//! EQEP_setInitialPosition() to set the value that gets loaded into the
//! position counter upon initialization.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_setPositionInitMode(uint32_t base, uint16_t initMode)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Set the init mode in the QEP Control register.
    //
    HWREGH(base + EQEP_O_QEPCTL) = (HWREGH(base + EQEP_O_QEPCTL) & ~(EQEP_QEPCTL_IEI_M | EQEP_QEPCTL_SEI_M)) | initMode;
}

//*****************************************************************************
//
//! Sets the software initialization of the encoder position counter.
//!
//! \param base is the base address of the eQEP module.
//! \param initialize is a flag to specify if software initialization of the
//! position counter is enabled.
//!
//! This function does a software initialization of the position counter when
//! the \e initialize parameter is \b true. When \b false, the QEPCTL[SWI] bit
//! is cleared and no action is taken.
//!
//! The init value to be loaded into the position counter can be set with
//! EQEP_setInitialPosition().  Additional initialization causes can be
//! configured with EQEP_setPositionInitMode().
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_setSWPositionInit(uint32_t base, bool initialize)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Set or clear the software initialization bit.
    //
    if (initialize)
    {
        HWREGH(base + EQEP_O_QEPCTL) |= EQEP_QEPCTL_SWI;
    }
    else
    {
        HWREGH(base + EQEP_O_QEPCTL) &= ~EQEP_QEPCTL_SWI;
    }
}

//*****************************************************************************
//
//! Sets the init value for the encoder position counter.
//!
//! \param base is the base address of the eQEP module.
//! \param position is the value to be written to the position counter upon.
//! initialization.
//!
//! This function sets the init value for position of the encoder. See
//! EQEP_setPositionInitMode() to set the initialization cause or
//! EQEP_setSWPositionInit() to cause a software initialization.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_setInitialPosition(uint32_t base, uint32_t position)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Write position to position counter init register
    //
    HWREG(base + EQEP_O_QPOSINIT) = position;
}

//*****************************************************************************
//
//! Configures the quadrature modes in which the position count can be latched.
//!
//! \param base is the base address of the eQEP module.
//! \param latchMode is the configuration for latching of the position count
//! and several other registers.  See below for a description of this
//! parameter.
//!
//! This function configures the events on which the position count and several
//! other registers can be latched.  The \e latchMode parameter provides the
//! mode as the logical OR of several values.
//!
//! - \b EQEP_LATCH_CNT_READ_BY_CPU or \b EQEP_LATCH_UNIT_TIME_OUT specify
//!   the event that latches the position counter.  This latch register can be
//!   read using EQEP_getPositionLatch(). The capture timer and capture
//!   period are also latched based on this setting, and can be read using
//!   EQEP_getCaptureTimerLatch() and EQEP_getCapturePeriodLatch().
//! - \b EQEP_LATCH_RISING_STROBE or \b EQEP_LATCH_EDGE_DIR_STROBE
//!   specify which strobe event will latch the position counter into the
//!   strobe position latch register.  This register can be read with
//!    EQEP_getStrobePositionLatch().
//! - \b EQEP_LATCH_RISING_INDEX, \b EQEP_LATCH_FALLING_INDEX, or
//!   \b EQEP_LATCH_SW_INDEX_MARKER specify which index event will latch the
//!   position counter into the index position latch register.  This register
//!   can be read with EQEP_getIndexPositionLatch().
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_setLatchMode(uint32_t base, uint32_t latchMode)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Set the latch mode in the QEP Control register.
    //
    HWREGH(base + EQEP_O_QEPCTL)
        = (HWREGH(base + EQEP_O_QEPCTL) & ~(EQEP_QEPCTL_QCLM | EQEP_QEPCTL_IEL_M | EQEP_QEPCTL_SEL)) | latchMode;
}

//*****************************************************************************
//
//! Gets the encoder position that was latched on an index event.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function returns the value in the index position latch register. The
//! position counter is latched into this register on either a rising index
//! edge, a falling index edge, or a software index marker. This is configured
//! using EQEP_setLatchMode().
//!
//! \return The position count latched on an index event.
//
//*****************************************************************************
static inline uint32_t EQEP_getIndexPositionLatch(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Return the current position counter.
    //
    return (HWREG(base + EQEP_O_QPOSILAT));
}

//*****************************************************************************
//
//! Gets the encoder position that was latched on a strobe event.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function returns the value in the strobe position latch register. The
//! position counter can be configured to be latched into this register on
//! rising strobe edges only or on rising strobe edges while moving clockwise
//! and falling strobe edges while moving counter-clockwise. This is configured
//! using EQEP_setLatchMode().
//!
//! \return The position count latched on a strobe event.
//
//*****************************************************************************
static inline uint32_t EQEP_getStrobePositionLatch(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Return the current position counter.
    //
    return (HWREG(base + EQEP_O_QPOSSLAT));
}

//*****************************************************************************
//
//! Gets the encoder position that was latched on a unit time-out event.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function returns the value in the position latch register. The
//! position counter is latched into this register either on a unit time-out
//! event.
//!
//! \return The position count latch register value.
//
//*****************************************************************************
static inline uint32_t EQEP_getPositionLatch(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Return the current position counter.
    //
    return (HWREG(base + EQEP_O_QPOSLAT));
}

//*****************************************************************************
//
//! Gets the encoder capture timer latch.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function returns the value in the capture timer latch register.  The
//! capture timer value is latched into this register either on a unit time-out
//! event or upon the CPU reading the eQEP position counter. This is configured
//! using EQEP_setLatchMode().
//!
//! \return The edge-capture timer latch value.
//
//*****************************************************************************
static inline uint16_t EQEP_getCaptureTimerLatch(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Return the current position counter.
    //
    return (HWREGH(base + EQEP_O_QCTMRLAT));
}

//*****************************************************************************
//
//! Gets the encoder capture period latch.
//!
//! \param base is the base address of the eQEP module.
//!
//! This function returns the value in the capture period latch register.  The
//! capture period value is latched into this register either on a unit
//! time-out event or upon the CPU reading the eQEP position counter. This is
//! configured using EQEP_setLatchMode().
//!
//! \return The edge-capture period latch value.
//
//*****************************************************************************
static inline uint16_t EQEP_getCapturePeriodLatch(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Return the current position counter.
    //
    return (HWREGH(base + EQEP_O_QCPRDLAT));
}

//*****************************************************************************
//
//! Set the quadrature mode adapter (QMA) module mode
//!
//! \param base is the base address of the eQEP module.
//! \param qmaMode is the mode in which the QMA module will operate.
//!
//! This function sets the quadrature mode adapter module mode. The possible
//! modes are passed to the function through the \e qmaMode parameter which
//! can take the values EQEP_QMA_MODE_BYPASS, EQEP_QMA_MODE_1, or
//! EQEP_QMA_MODE_2.
//!
//! To use the QMA module, you must first put the eQEP module into
//! direction-count mode (\b EQEP_CONFIG_CLOCK_DIR) using EQEP_setConfig().
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_setQMAModuleMode(uint32_t base, EQEP_QMAMode qmaMode)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Write the QMA module mode into the appropriate register.
    //
    HWREGH(base + EQEP_O_QMACTRL) = (HWREGH(base + EQEP_O_QMACTRL) & ~EQEP_QMACTRL_MODE_M) | (uint16_t)qmaMode;
}

//*****************************************************************************
//
//! Set the strobe input source of the eQEP module.
//!
//! \param base is the base address of the eQEP module.
//! \param strobeSrc is the source of the strobe signal.
//!
//! This function sets the source of the eQEP module's strobe signal. The
//! possible values of the \e strobeSrc parameter are
//! - \b EQEP_STROBE_FROM_GPIO - The strobe is used as-is after passing through
//!   the polarity select logic.
//! - \b EQEP_STROBE_OR_ADCSOCA - The strobe is OR'd with the ADCSOCA signal
//!   after passing through the polarity select logic.
//! - \b EQEP_STROBE_OR_ADCSOCB - The strobe is OR'd with the ADCSOCB signal
//!   after passing through the polarity select logic.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_setStrobeSource(uint32_t base, EQEP_StrobeSource strobeSrc)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Write the strobe source selection into the appropriate register.
    //
    HWREGH(base + EQEP_O_QEPSTROBESEL)
        = (HWREGH(base + EQEP_O_QEPSTROBESEL) & ~EQEP_QEPSTROBESEL_STROBESEL_M) | (uint16_t)strobeSrc;
}

//*****************************************************************************
//
//! Set the emulation mode of the eQEP module.
//!
//! \param base is the base address of the eQEP module.
//! \param emuMode is the mode operation upon an emulation suspend.
//!
//! This function sets the eQEP module's emulation mode. This mode determines
//! how the timers are affected by an emulation suspend. Valid values for the
//! \e emuMode parameter are the following:
//!
//! - \b EQEP_EMULATIONMODE_STOPIMMEDIATELY - The position counter, watchdog
//!   counter, unit timer, and capture timer all stop immediately.
//! - \b EQEP_EMULATIONMODE_STOPATROLLOVER - The position counter, watchdog
//!   counter, unit timer all count until period rollover. The capture timer
//!   counts until the next unit period event.
//! - \b EQEP_EMULATIONMODE_RUNFREE - The position counter, watchdog counter,
//!   unit timer, and capture timer are all unaffected by an emulation suspend.
//!
//! \return None.
//
//*****************************************************************************
static inline void EQEP_setEmulationMode(uint32_t base, EQEP_EmulationMode emuMode)
{
    //
    // Check the arguments.
    //
    ASSERT(EQEP_isBaseValid(base));

    //
    // Write the emulation mode to the FREE_SOFT bits.
    //
    HWREGH(base + EQEP_O_QEPCTL)
        = (HWREGH(base + EQEP_O_QEPCTL) & ~EQEP_QEPCTL_FREE_SOFT_M) | ((uint16_t)emuMode << EQEP_QEPCTL_FREE_SOFT_S);
}

//*****************************************************************************
//
//! Configures eQEP module position-compare unit.
//!
//! \param base is the base address of the eQEP module.
//! \param config is the configuration for the eQEP module
//! position-compare unit.  See below for a description of this parameter.
//! \param compareValue is the value to which the position count value is
//! compared for a position-compare event.
//! \param cycles is the width of the pulse that can be generated on a
//! position-compare event.  It is in units of 4 SYSCLKOUT cycles.
//!
//! This function configures the operation of the eQEP module position-compare
//! unit.  The \e config parameter provides the configuration of the
//! position-compare unit and is the logical OR of several values:
//!
//! - \b EQEP_COMPARE_NO_SYNC_OUT, \b EQEP_COMPARE_IDX_SYNC_OUT, or
//!   \b EQEP_COMPARE_STROBE_SYNC_OUT specify if there is a sync output pulse
//!   and which pin should be used.
//! - \b EQEP_COMPARE_NO_SHADOW, \b EQEP_COMPARE_LOAD_ON_ZERO, or
//!   \b EQEP_COMPARE_LOAD_ON_MATCH specify if a shadow is enabled and when
//!   should the load should occur--QPOSCNT = 0 or QPOSCNT = QPOSCOMP.
//!
//! The \e cycles is used to select the width of the sync output pulse. The
//! width of the resulting pulse will be \e cycles * 4 * the width of a
//! SYSCLKOUT cycle. The maximum width is 4096 * 4 * SYSCLKOUT cycles.
//!
//! \note You can set the sync pulse width independently using the
//! EQEP_setComparePulseWidth() function.
//!
//! \return None.
//
//*****************************************************************************
extern void EQEP_setCompareConfig(uint32_t base, uint16_t config, uint32_t compareValue, uint16_t cycles);

//*****************************************************************************
//
//! Sets the polarity of the eQEP module's input signals.
//!
//! \param base is the base address of the eQEP module.
//! \param invertQEPA is the flag to negate the QEPA input.
//! \param invertQEPB is the flag to negate the QEPA input.
//! \param invertIndex is the flag to negate the index input.
//! \param invertStrobe is the flag to negate the strobe input.
//!
//! This function configures the polarity of the inputs to the eQEP module. To
//! negate the polarity of any of the input signals, pass \b true into its
//! corresponding parameter in this function. Pass \b false to leave it as-is.
//!
//! \return None.
//
//*****************************************************************************
extern void EQEP_setInputPolarity(uint32_t base, bool invertQEPA, bool invertQEPB, bool invertIndex, bool invertStrobe);

#ifdef __cplusplus
}
#endif

#endif
