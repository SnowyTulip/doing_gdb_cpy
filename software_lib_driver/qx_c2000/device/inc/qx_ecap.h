/**
 **************************************************************************
 * @file     qx_ecap.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_ECAP_H
#define QX_ECAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"
#include "hw_ecap.h"

//---------------------------------------------------------------------------
// ECAP Individual Register Bit Definitions:

struct ECCTL0_BITS
{                       // bits description
    vu32 INPUTSEL : 7;  // 6:0 INPUT source select
    vu32 rsvd1    : 9;  // 15:7 Reserved
    vu32 rsvd2    : 16; // 31:16 Reserved
};

union ECCTL0_REG
{
    vu32 all;
    struct ECCTL0_BITS bit;
};

struct ECCTL1_BITS
{                       // bits description
    vu16 CAP1POL   : 1; // 0 Capture Event 1 Polarity select
    vu16 CTRRST1   : 1; // 1 Counter Reset on Capture Event 1
    vu16 CAP2POL   : 1; // 2 Capture Event 2 Polarity select
    vu16 CTRRST2   : 1; // 3 Counter Reset on Capture Event 2
    vu16 CAP3POL   : 1; // 4 Capture Event 3 Polarity select
    vu16 CTRRST3   : 1; // 5 Counter Reset on Capture Event 3
    vu16 CAP4POL   : 1; // 6 Capture Event 4 Polarity select
    vu16 CTRRST4   : 1; // 7 Counter Reset on Capture Event 4
    vu16 CAPLDEN   : 1; // 8 Enable Loading CAP1-4 regs on a Cap Event
    vu16 PRESCALE  : 5; // 13:9 Event Filter prescale select
    vu16 FREE_SOFT : 2; // 15:14 Emulation mode
};

union ECCTL1_REG
{
    vu16 all;
    struct ECCTL1_BITS bit;
};

struct ECCTL2_BITS
{                          // bits description
    vu16 CONT_ONESHT  : 1; // 0 Continuous or one-shot
    vu16 STOP_WRAP    : 2; // 2:1 Stop value for one-shot, Wrap for continuous
    vu16 REARM        : 1; // 3 One-shot re-arm
    vu16 TSCTRSTOP    : 1; // 4 TSCNT counter stop
    vu16 SYNCI_EN     : 1; // 5 Counter sync-in select
    vu16 SYNCO_SEL    : 2; // 7:6 Sync-out mode
    vu16 SWSYNC       : 1; // 8 SW forced counter sync
    vu16 CAP_APWM     : 1; // 9 CAP/APWM operating mode select
    vu16 APWMPOL      : 1; // 10  APWM output polarity select
    vu16 CTRFILTRESET : 1; // 11 Reset event filter, modulus counter, and interrupt flags.
    vu16 DMAEVTSEL    : 2; // 13:12 DMA event select
    vu16 MODCNTRSTS   : 2; // 15:14 modulo counter status
};

union ECCTL2_REG
{
    vu16 all;
    struct ECCTL2_BITS bit;
};

struct ECEINT_BITS
{                        // bits description
    vu16 rsvd1      : 1; // 0 Reserved
    vu16 CEVT1      : 1; // 1 Capture Event 1 Interrupt Enable
    vu16 CEVT2      : 1; // 2 Capture Event 2 Interrupt Enable
    vu16 CEVT3      : 1; // 3 Capture Event 3 Interrupt Enable
    vu16 CEVT4      : 1; // 4 Capture Event 4 Interrupt Enable
    vu16 CTROVF     : 1; // 5 Counter Overflow Interrupt Enable
    vu16 CTR_EQ_PRD : 1; // 6 Period Equal Interrupt Enable
    vu16 CTR_EQ_CMP : 1; // 7 Compare Equal Interrupt Enable
    vu16 rsvd2      : 1; // 8 Reserved
    vu16 rsvd3      : 7; // 15:9 Reserved
};

union ECEINT_REG
{
    vu16 all;
    struct ECEINT_BITS bit;
};

struct ECFLG_BITS
{                     // bits description
    vu16 INT     : 1; // 0 Global Flag
    vu16 CEVT1   : 1; // 1 Capture Event 1 Interrupt Flag
    vu16 CEVT2   : 1; // 2 Capture Event 2 Interrupt Flag
    vu16 CEVT3   : 1; // 3 Capture Event 3 Interrupt Flag
    vu16 CEVT4   : 1; // 4 Capture Event 4 Interrupt Flag
    vu16 CTROVF  : 1; // 5 Counter Overflow Interrupt Flag
    vu16 CTR_PRD : 1; // 6 Period Equal Interrupt Flag
    vu16 CTR_CMP : 1; // 7 Compare Equal Interrupt Flag
    vu16 rsvd1   : 1; // 8 Reserved
    vu16 rsvd2   : 7; // 15:9 Reserved
};

union ECFLG_REG
{
    vu16 all;
    struct ECFLG_BITS bit;
};

struct ECCLR_BITS
{                     // bits description
    vu16 INT     : 1; // 0 ECAP Global Interrupt Status Clear
    vu16 CEVT1   : 1; // 1 Capture Event 1 Status Clear
    vu16 CEVT2   : 1; // 2 Capture Event 2 Status Clear
    vu16 CEVT3   : 1; // 3 Capture Event 3 Status Clear
    vu16 CEVT4   : 1; // 4 Capture Event 4 Status Clear
    vu16 CTROVF  : 1; // 5 Counter Overflow Status Clear
    vu16 CTR_PRD : 1; // 6 Period Equal Status Clear
    vu16 CTR_CMP : 1; // 7 Compare Equal Status Clear
    vu16 rsvd1   : 1; // 8 Reserved
    vu16 rsvd2   : 7; // 15:9 Reserved
};

union ECCLR_REG
{
    vu16 all;
    struct ECCLR_BITS bit;
};

struct ECFRC_BITS
{                     // bits description
    vu16 rsvd1   : 1; // 0 Reserved
    vu16 CEVT1   : 1; // 1 Capture Event 1 Force Interrupt
    vu16 CEVT2   : 1; // 2 Capture Event 2 Force Interrupt
    vu16 CEVT3   : 1; // 3 Capture Event 3 Force Interrupt
    vu16 CEVT4   : 1; // 4 Capture Event 4 Force Interrupt
    vu16 CTROVF  : 1; // 5 Counter Overflow Force Interrupt
    vu16 CTR_PRD : 1; // 6 Period Equal Force Interrupt
    vu16 CTR_CMP : 1; // 7 Compare Equal Force Interrupt
    vu16 rsvd2   : 1; // 8 Reserved
    vu16 rsvd3   : 7; // 15:9 Reserved
};

union ECFRC_REG
{
    vu16 all;
    struct ECFRC_BITS bit;
};

struct ECAP_REGS
{
    vu32 TSCTR;              // Time-Stamp Counter offset:0x00
    vu32 CTRPHS;             // Counter Phase Offset Value Register offset:0x04
    vu32 CAP1;               // Capture 1 Register offset:0x08
    vu32 CAP2;               // Capture 2 Register offset:0x0C
    vu32 CAP3;               // Capture 3 Register offset:0x10
    vu32 CAP4;               // Capture 4 Register offset:0x14
    vu32 rsvd1[3];           // Reserved offset:0x18~0x20
    union ECCTL0_REG ECCTL0; // Capture Control Register 0 offset:0x24
    union ECCTL1_REG ECCTL1; // Capture Control Register 1 offset:0x28
    union ECCTL2_REG ECCTL2; // Capture Control Register 2 offset:0x2A
    union ECEINT_REG ECEINT; // Capture Interrupt Enable Register offset:0x2C
    union ECFLG_REG ECFLG;   // Capture Interrupt Flag Register offset:0x2E
    union ECCLR_REG ECCLR;   // Capture Interrupt Clear Register offset:0x30
    union ECFRC_REG ECFRC;   // Capture Interrupt Force Register offset:0x32
};

#define ECap1Regs ((struct ECAP_REGS *)ECAP1_BASE)
#define ECap2Regs ((struct ECAP_REGS *)ECAP2_BASE)
#define ECap3Regs ((struct ECAP_REGS *)ECAP3_BASE)
#define ECap4Regs ((struct ECAP_REGS *)ECAP4_BASE)
#define ECap5Regs ((struct ECAP_REGS *)ECAP5_BASE)
#define ECap6Regs ((struct ECAP_REGS *)HRCAP1_BASE)
#define ECap7Regs ((struct ECAP_REGS *)HRCAP2_BASE)

//*************************************************************************************************
//
// The following are defines for the ECAP register offsets
//
//*************************************************************************************************
#define ECAP_O_TSCTR  0x0U  // Time-Stamp Counter
#define ECAP_O_CTRPHS 0x4U  // Counter Phase Offset Value Register
#define ECAP_O_CAP1   0x8U  // Capture 1 Register
#define ECAP_O_CAP2   0xCU  // Capture 2 Register
#define ECAP_O_CAP3   0x10U // Capture 3 Register
#define ECAP_O_CAP4   0x14U // Capture 4 Register
#define ECAP_O_ECCTL0 0x24U // Capture Control Register 0
#define ECAP_O_ECCTL1 0x28U // Capture Control Register 1
#define ECAP_O_ECCTL2 0x2AU // Capture Control Register 2
#define ECAP_O_ECEINT 0x2CU // Capture Interrupt Enable Register
#define ECAP_O_ECFLG  0x2EU // Capture Interrupt Flag Register
#define ECAP_O_ECCLR  0x30U // Capture Interrupt Clear Register
#define ECAP_O_ECFRC  0x32U // Capture Interrupt Force Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECCTL0 register
//
//*************************************************************************************************
#define ECAP_ECCTL0_INPUTSEL_S 0U
#define ECAP_ECCTL0_INPUTSEL_M 0x7FU // INPUT source select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECCTL1 register
//
//*************************************************************************************************
#define ECAP_ECCTL1_CAP1POL     0x1U   // Capture Event 1 Polarity select
#define ECAP_ECCTL1_CTRRST1     0x2U   // Counter Reset on Capture Event 1
#define ECAP_ECCTL1_CAP2POL     0x4U   // Capture Event 2 Polarity select
#define ECAP_ECCTL1_CTRRST2     0x8U   // Counter Reset on Capture Event 2
#define ECAP_ECCTL1_CAP3POL     0x10U  // Capture Event 3 Polarity select
#define ECAP_ECCTL1_CTRRST3     0x20U  // Counter Reset on Capture Event 3
#define ECAP_ECCTL1_CAP4POL     0x40U  // Capture Event 4 Polarity select
#define ECAP_ECCTL1_CTRRST4     0x80U  // Counter Reset on Capture Event 4
#define ECAP_ECCTL1_CAPLDEN     0x100U // Enable Loading CAP1-4 regs on a Cap Event
#define ECAP_ECCTL1_PRESCALE_S  9U
#define ECAP_ECCTL1_PRESCALE_M  0x3E00U // Event Filter prescale select
#define ECAP_ECCTL1_FREE_SOFT_S 14U
#define ECAP_ECCTL1_FREE_SOFT_M 0xC000U // Emulation mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECCTL2 register
//
//*************************************************************************************************
#define ECAP_ECCTL2_CONT_ONESHT  0x1U // Continuous or one-shot
#define ECAP_ECCTL2_STOP_WRAP_S  1U
#define ECAP_ECCTL2_STOP_WRAP_M  0x6U  // Stop value for one-shot, Wrap for continuous
#define ECAP_ECCTL2_REARM        0x8U  // One-shot re-arm
#define ECAP_ECCTL2_TSCTRSTOP    0x10U // TSCNT counter stop
#define ECAP_ECCTL2_SYNCI_EN     0x20U // Counter sync-in select
#define ECAP_ECCTL2_SYNCO_SEL_S  6U
#define ECAP_ECCTL2_SYNCO_SEL_M  0xC0U  // Sync-out mode
#define ECAP_ECCTL2_SWSYNC       0x100U // SW forced counter sync
#define ECAP_ECCTL2_CAP_APWM     0x200U // CAP/APWM operating mode select
#define ECAP_ECCTL2_APWMPOL      0x400U //  APWM output polarity select
#define ECAP_ECCTL2_CTRFILTRESET 0x800U // Reset event filter, modulus counter, and interrupt flags
#define ECAP_ECCTL2_DMAEVTSEL_S  12U
#define ECAP_ECCTL2_DMAEVTSEL_M  0x3000U // DMA event select
#define ECAP_ECCTL2_MODCNTRSTS_S 14U
#define ECAP_ECCTL2_MODCNTRSTS_M 0xC000U // modulo counter status

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECEINT register
//
//*************************************************************************************************
#define ECAP_ECEINT_CEVT1      0x2U  // Capture Event 1 Interrupt Enable
#define ECAP_ECEINT_CEVT2      0x4U  // Capture Event 2 Interrupt Enable
#define ECAP_ECEINT_CEVT3      0x8U  // Capture Event 3 Interrupt Enable
#define ECAP_ECEINT_CEVT4      0x10U // Capture Event 4 Interrupt Enable
#define ECAP_ECEINT_CTROVF     0x20U // Counter Overflow Interrupt Enable
#define ECAP_ECEINT_CTR_EQ_PRD 0x40U // Period Equal Interrupt Enable
#define ECAP_ECEINT_CTR_EQ_CMP 0x80U // Compare Equal Interrupt Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECFLG register
//
//*************************************************************************************************
#define ECAP_ECFLG_INT     0x1U  // Global Flag
#define ECAP_ECFLG_CEVT1   0x2U  // Capture Event 1 Interrupt Flag
#define ECAP_ECFLG_CEVT2   0x4U  // Capture Event 2 Interrupt Flag
#define ECAP_ECFLG_CEVT3   0x8U  // Capture Event 3 Interrupt Flag
#define ECAP_ECFLG_CEVT4   0x10U // Capture Event 4 Interrupt Flag
#define ECAP_ECFLG_CTROVF  0x20U // Counter Overflow Interrupt Flag
#define ECAP_ECFLG_CTR_PRD 0x40U // Period Equal Interrupt Flag
#define ECAP_ECFLG_CTR_CMP 0x80U // Compare Equal Interrupt Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECCLR register
//
//*************************************************************************************************
#define ECAP_ECCLR_INT     0x1U  // ECAP Global Interrupt Status Clear
#define ECAP_ECCLR_CEVT1   0x2U  // Capture Event 1 Status Clear
#define ECAP_ECCLR_CEVT2   0x4U  // Capture Event 2 Status Clear
#define ECAP_ECCLR_CEVT3   0x8U  // Capture Event 3 Status Clear
#define ECAP_ECCLR_CEVT4   0x10U // Capture Event 4 Status Clear
#define ECAP_ECCLR_CTROVF  0x20U // Counter Overflow Status Clear
#define ECAP_ECCLR_CTR_PRD 0x40U // Period Equal Status Clear
#define ECAP_ECCLR_CTR_CMP 0x80U // Compare Equal Status Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECFRC register
//
//*************************************************************************************************
#define ECAP_ECFRC_CEVT1   0x2U  // Capture Event 1 Force Interrupt
#define ECAP_ECFRC_CEVT2   0x4U  // Capture Event 2 Force Interrupt
#define ECAP_ECFRC_CEVT3   0x8U  // Capture Event 3 Force Interrupt
#define ECAP_ECFRC_CEVT4   0x10U // Capture Event 4 Force Interrupt
#define ECAP_ECFRC_CTROVF  0x20U // Counter Overflow Force Interrupt
#define ECAP_ECFRC_CTR_PRD 0x40U // Period Equal Force Interrupt
#define ECAP_ECFRC_CTR_CMP 0x80U // Compare Equal Force Interrupt
//*****************************************************************************
//
// eCAP minimum and maximum values
//
//*****************************************************************************
#define ECAP_MAX_PRESCALER_VALUE 32U // Maximum Pre-scaler value

//*****************************************************************************
//
// Values that can be passed to ECAP_enableInterrupt(),
// ECAP_disableInterrupt(), ECAP_clearInterrupt() and ECAP_forceInterrupt() as
// the intFlags parameter and returned by ECAP_getInterruptSource().
//
//*****************************************************************************
//! Event 1 ISR source
//!
#define ECAP_ISR_SOURCE_CAPTURE_EVENT_1 0x2U
//! Event 2 ISR source
//!
#define ECAP_ISR_SOURCE_CAPTURE_EVENT_2 0x4U
//! Event 3 ISR source
//!
#define ECAP_ISR_SOURCE_CAPTURE_EVENT_3 0x8U
//! Event 4 ISR source
//!
#define ECAP_ISR_SOURCE_CAPTURE_EVENT_4 0x10U
//! Counter overflow ISR source
//!
#define ECAP_ISR_SOURCE_COUNTER_OVERFLOW 0x20U
//! Counter equals period ISR source
//!
#define ECAP_ISR_SOURCE_COUNTER_PERIOD 0x40U
//! Counter equals compare ISR source
//!
#define ECAP_ISR_SOURCE_COUNTER_COMPARE 0x80U

//*****************************************************************************
//
//! Values that can be passed to ECAP_setEmulationMode() as the
//! \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    //! TSCTR is stopped on emulation suspension
    ECAP_EMULATION_STOP = 0x0U,
    //! TSCTR runs until 0 before stopping on emulation suspension
    ECAP_EMULATION_RUN_TO_ZERO = 0x1U,
    //! TSCTR is not affected by emulation suspension
    ECAP_EMULATION_FREE_RUN = 0x2U
} ECAP_EmulationMode;

//*****************************************************************************
//
//! Values that can be passed to ECAP_setCaptureMode() as the
//! \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    //! eCAP operates in continuous capture mode
    ECAP_CONTINUOUS_CAPTURE_MODE = 0U,
    //! eCAP operates in one shot capture mode
    ECAP_ONE_SHOT_CAPTURE_MODE = 1U
} ECAP_CaptureMode;

//*****************************************************************************
//
//! Values that can be passed to ECAP_setEventPolarity(),ECAP_setCaptureMode(),
//! ECAP_enableCounterResetOnEvent(),ECAP_disableCounterResetOnEvent(),
//! ECAP_getEventTimeStamp(),ECAP_setDMASource() as the \e event parameter.
//
//*****************************************************************************
typedef enum
{
    ECAP_EVENT_1 = 0U, //!< eCAP event 1
    ECAP_EVENT_2 = 1U, //!< eCAP event 2
    ECAP_EVENT_3 = 2U, //!< eCAP event 3
    ECAP_EVENT_4 = 3U  //!< eCAP event 4
} ECAP_Events;

//*****************************************************************************
//
//! Values that can be passed to ECAP_setSyncOutMode() as the \e mode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! sync out on the sync in signal and software force
    ECAP_SYNC_OUT_SYNCI = 0x00U,
    //! sync out on counter equals period
    ECAP_SYNC_OUT_COUNTER_PRD = 0x40U,
    //! Disable sync out signal
    ECAP_SYNC_OUT_DISABLED = 0x80U
} ECAP_SyncOutMode;

//*****************************************************************************
//
//! Values that can be passed to ECAP_setAPWMPolarity() as the \e polarity
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ECAP_APWM_ACTIVE_HIGH = 0x000, //!< APWM is active high
    ECAP_APWM_ACTIVE_LOW  = 0x400  //!< APWM is active low
} ECAP_APWMPolarity;

//*****************************************************************************
//
//! Values that can be passed to ECAP_setEventPolarity() as the \e polarity
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ECAP_EVNT_RISING_EDGE  = 0U, //!< Rising edge polarity
    ECAP_EVNT_FALLING_EDGE = 1U  //!< Falling edge polarity
} ECAP_EventPolarity;

//*****************************************************************************
//
//! Values that can be passed to ECAP_selectECAPInput() as the \e input
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! GPIO Input Crossbar output signal-1
    ECAP_INPUT_INPUTXBAR1 = 0,
    //! GPIO Input Crossbar output signal-2
    ECAP_INPUT_INPUTXBAR2 = 1,
    //! GPIO Input Crossbar output signal-3
    ECAP_INPUT_INPUTXBAR3 = 2,
    //! GPIO Input Crossbar output signal-4
    ECAP_INPUT_INPUTXBAR4 = 3,
    //! GPIO Input Crossbar output signal-5
    ECAP_INPUT_INPUTXBAR5 = 4,
    //! GPIO Input Crossbar output signal-6
    ECAP_INPUT_INPUTXBAR6 = 5,
    //! GPIO Input Crossbar output signal-7
    ECAP_INPUT_INPUTXBAR7 = 6,
    //! GPIO Input Crossbar output signal-8
    ECAP_INPUT_INPUTXBAR8 = 7,
    //! GPIO Input Crossbar output signal-9
    ECAP_INPUT_INPUTXBAR9 = 8,
    //! GPIO Input Crossbar output signal-10
    ECAP_INPUT_INPUTXBAR10 = 9,
    //! GPIO Input Crossbar output signal-11
    ECAP_INPUT_INPUTXBAR11 = 10,
    //! GPIO Input Crossbar output signal-12
    ECAP_INPUT_INPUTXBAR12 = 11,
    //! GPIO Input Crossbar output signal-13
    ECAP_INPUT_INPUTXBAR13 = 12,
    //! GPIO Input Crossbar output signal-14
    ECAP_INPUT_INPUTXBAR14 = 13,
    //! GPIO Input Crossbar output signal-15
    ECAP_INPUT_INPUTXBAR15 = 14,
    //! GPIO Input Crossbar output signal-16
    ECAP_INPUT_INPUTXBAR16 = 15,
    //! CANA INT0 Input
    ECAP_INPUT_CANA_INT0 = 20,
    //! CANB INT0 Input
    ECAP_INPUT_CANB_INT0 = 21,
    //! Delay clock for measurement
    ECAP_INPUT_ECAP_DELAY_CLOCK = 23,
    //! Output Xbar Output-1
    ECAP_INPUT_OUTPUTXBAR1 = 24,
    //! Output Xbar Output-2
    ECAP_INPUT_OUTPUTXBAR2 = 25,
    //! Output Xbar Output-3
    ECAP_INPUT_OUTPUTXBAR3 = 26,
    //! Output Xbar Output-4
    ECAP_INPUT_OUTPUTXBAR4 = 27,
    //! Output Xbar Output-5
    ECAP_INPUT_OUTPUTXBAR5 = 28,
    //! Output Xbar Output-6
    ECAP_INPUT_OUTPUTXBAR6 = 29,
    //! Output Xbar Output-7
    ECAP_INPUT_OUTPUTXBAR7 = 30,
    //! Output Xbar Output-8
    ECAP_INPUT_OUTPUTXBAR8 = 31,
    //! ADCC Event4
    ECAP_INPUT_ADC_C_EVENT4 = 36,
    //! ADCC Event3
    ECAP_INPUT_ADC_C_EVENT3 = 37,
    //! ADCC Event2
    ECAP_INPUT_ADC_C_EVENT2 = 38,
    //! ADCC Event1
    ECAP_INPUT_ADC_C_EVENT1 = 39,
    //! ADCB Event4
    ECAP_INPUT_ADC_B_EVENT4 = 40,
    //! ADCB Event3
    ECAP_INPUT_ADC_B_EVENT3 = 41,
    //! ADCB Event2
    ECAP_INPUT_ADC_B_EVENT2 = 42,
    //! ADCB Event1
    ECAP_INPUT_ADC_B_EVENT1 = 43,
    //! ADCA Event4
    ECAP_INPUT_ADC_A_EVENT4 = 44,
    //! ADCA Event3
    ECAP_INPUT_ADC_A_EVENT3 = 45,
    //! ADCA Event2
    ECAP_INPUT_ADC_A_EVENT2 = 46,
    //! ADCA Event1
    ECAP_INPUT_ADC_A_EVENT1 = 47,
    //! SDFM-1 Filter-1 Compare Low Trip
    ECAP_INPUT_SDFM1_FLT1_COMPARE_LOW = 64,
    //! SDFM-1 Filter-2 Compare Low Trip
    ECAP_INPUT_SDFM1_FLT2_COMPARE_LOW = 65,
    //! SDFM-1 Filter-3 Compare Low Trip
    ECAP_INPUT_SDFM1_FLT3_COMPARE_LOW = 66,
    //! SDFM-1 Filter-4 Compare Low Trip
    ECAP_INPUT_SDFM1_FLT4_COMPARE_LOW = 67,
    //! SDFM-1 Filter-1 Compare High Trip
    ECAP_INPUT_SDFM1_FLT1_COMPARE_HIGH = 80,
    //! SDFM-1 Filter-2 Compare High Trip
    ECAP_INPUT_SDFM1_FLT2_COMPARE_HIGH = 81,
    //! SDFM-1 Filter-3 Compare High Trip
    ECAP_INPUT_SDFM1_FLT3_COMPARE_HIGH = 82,
    //! SDFM-1 Filter-4 Compare High Trip
    ECAP_INPUT_SDFM1_FLT4_COMPARE_HIGH = 83,
    //! SDFM-1 Filter-1 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM1_FLT1_COMPARE_HIGH_OR_LOW = 88,
    //! SDFM-1 Filter-2 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM1_FLT2_COMPARE_HIGH_OR_LOW = 89,
    //! SDFM-1 Filter-3 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM1_FLT3_COMPARE_HIGH_OR_LOW = 90,
    //! SDFM-1 Filter-4 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM1_FLT4_COMPARE_HIGH_OR_LOW = 91,
    //! Compare Subsystem-1 Low Trip
    ECAP_INPUT_CMPSS1_CTRIP_LOW = 96,
    //! Compare Subsystem-2 Low Trip
    ECAP_INPUT_CMPSS2_CTRIP_LOW = 97,
    //! Compare Subsystem-3 Low Trip
    ECAP_INPUT_CMPSS3_CTRIP_LOW = 98,
    //! Compare Subsystem-4 Low Trip
    ECAP_INPUT_CMPSS4_CTRIP_LOW = 99,
    //! Compare Subsystem-5 Low Trip
    ECAP_INPUT_CMPSS5_CTRIP_LOW = 100,
    //! Compare Subsystem-6 Low Trip
    ECAP_INPUT_CMPSS6_CTRIP_LOW = 101,
    //! Compare Subsystem-7 Low Trip
    ECAP_INPUT_CMPSS7_CTRIP_LOW = 102,
    //! Compare Subsystem-1 High Trip
    ECAP_INPUT_CMPSS1_CTRIP_HIGH = 108,
    //! Compare Subsystem-2 High Trip
    ECAP_INPUT_CMPSS2_CTRIP_HIGH = 109,
    //! Compare Subsystem-3 High Trip
    ECAP_INPUT_CMPSS3_CTRIP_HIGH = 110,
    //! Compare Subsystem-4 High Trip
    ECAP_INPUT_CMPSS4_CTRIP_HIGH = 111,
    //! Compare Subsystem-5 High Trip
    ECAP_INPUT_CMPSS5_CTRIP_HIGH = 112,
    //! Compare Subsystem-6 High Trip
    ECAP_INPUT_CMPSS6_CTRIP_HIGH = 113,
    //! Compare Subsystem-7 High Trip
    ECAP_INPUT_CMPSS7_CTRIP_HIGH = 114,
    //! Compare Subsystem-1 High Trip or Low Trip
    ECAP_INPUT_CMPSS1_CTRIP_HIGH_OR_LOW = 120,
    //! Compare Subsystem-2 High Trip or Low Trip
    ECAP_INPUT_CMPSS2_CTRIP_HIGH_OR_LOW = 121,
    //! Compare Subsystem-3 High Trip or Low Trip
    ECAP_INPUT_CMPSS3_CTRIP_HIGH_OR_LOW = 122,
    //! Compare Subsystem-4 High Trip or Low Trip
    ECAP_INPUT_CMPSS4_CTRIP_HIGH_OR_LOW = 123,
    //! Compare Subsystem-5 High Trip or Low Trip
    ECAP_INPUT_CMPSS5_CTRIP_HIGH_OR_LOW = 124,
    //! Compare Subsystem-6 High Trip or Low Trip
    ECAP_INPUT_CMPSS6_CTRIP_HIGH_OR_LOW = 125,
    //! Compare Subsystem-7 High Trip or Low Trip
    ECAP_INPUT_CMPSS7_CTRIP_HIGH_OR_LOW = 126,
    //! Default Reserved Input
    ECAP_INPUT_RESERVED = 127,
} ECAP_InputCaptureSignals;

//*****************************************************************************
//
//! \internal
//! Checks eCAP base address.
//!
//! \param base specifies the eCAP module base address.
//!
//! This function determines if an eCAP module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool ECAP_isBaseValid(uint32_t base)
{
    return ((base == ECAP1_BASE) || (base == ECAP2_BASE) || (base == ECAP3_BASE) || (base == ECAP4_BASE)
            || (base == ECAP5_BASE) || (base == ECAP6_BASE) || (base == ECAP7_BASE));
}
#endif

//*****************************************************************************
//
//! Sets the input prescaler.
//!
//! \param base is the base address of the ECAP module.
//! \param preScalerValue is the pre scaler value for ECAP input
//!
//! This function divides the ECAP input scaler. The pre scale value is
//! doubled inside the module. For example a preScalerValue of 5 will divide
//! the scaler by 10. Use a value of 1 to divide the pre scaler by 1.
//! The \e preScalerValue should be less than \b ECAP_MAX_PRESCALER_VALUE.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setEventPrescaler(uint32_t base, uint16_t preScalerValue)
{
    ASSERT(ECAP_isBaseValid(base));

    ASSERT(preScalerValue < ECAP_MAX_PRESCALER_VALUE);

    EALLOW;

    //
    // Write to PRESCALE bit
    //
    HWREGH(base + ECAP_O_ECCTL1)
        = ((HWREGH(base + ECAP_O_ECCTL1) & (~ECAP_ECCTL1_PRESCALE_M)) | (preScalerValue << ECAP_ECCTL1_PRESCALE_S));
    EDIS;
}

//*****************************************************************************
//
//! Sets the Capture event polarity.
//!
//! \param base is the base address of the ECAP module.
//! \param event is the event number.
//! \param polarity is the polarity of the event.
//!
//! This function sets the polarity of a given event. The value of event
//! is between \b ECAP_EVENT_1 and \b ECAP_EVENT_4 inclusive corresponding to
//! the four available events.For each event the polarity value determines the
//! edge on which the capture is activated. For a rising edge use a polarity
//! value of \b ECAP_EVNT_RISING_EDGE and for a falling edge use a polarity of
//! \b ECAP_EVNT_FALLING_EDGE.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setEventPolarity(uint32_t base, ECAP_Events event, ECAP_EventPolarity polarity)
{

    uint16_t shift;

    ASSERT(ECAP_isBaseValid(base));

    shift = ((uint16_t)event) << 1U;

    EALLOW;

    //
    // Write to CAP1POL, CAP2POL, CAP3POL or CAP4POL
    //
    HWREGH(base + ECAP_O_ECCTL1) = (HWREGH(base + ECAP_O_ECCTL1) & ~(1U << shift)) | ((uint16_t)polarity << shift);
    EDIS;
}

//*****************************************************************************
//
//! Sets the capture mode.
//!
//! \param base is the base address of the ECAP module.
//! \param mode is the capture mode.
//! \param event is the event number at which the counter stops or wraps.
//!
//! This function sets the eCAP module to a continuous or one-shot mode.
//! The value of mode should be either \b ECAP_CONTINUOUS_CAPTURE_MODE or
//! \b ECAP_ONE_SHOT_CAPTURE_MODE corresponding to continuous or one-shot mode
//! respectively.
//!
//! The value of event determines the event number at which the counter stops
//! (in one-shot mode) or the counter wraps (in continuous mode). The value of
//! event should be between \b ECAP_EVENT_1 and \b ECAP_EVENT_4 corresponding
//! to the valid event numbers.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setCaptureMode(uint32_t base, ECAP_CaptureMode mode, ECAP_Events event)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to CONT/ONESHT
    //
    HWREGH(base + ECAP_O_ECCTL2) = ((HWREGH(base + ECAP_O_ECCTL2) & (~ECAP_ECCTL2_CONT_ONESHT)) | (uint16_t)mode);

    //
    // Write to STOP_WRAP
    //
    HWREGH(base + ECAP_O_ECCTL2) = ((HWREGH(base + ECAP_O_ECCTL2) & (~ECAP_ECCTL2_STOP_WRAP_M))
                                    | (((uint16_t)event) << ECAP_ECCTL2_STOP_WRAP_S));
    EDIS;
}

//*****************************************************************************
//
//! Re-arms the eCAP module.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function re-arms the eCAP module.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_reArm(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to RE-ARM bit
    //
    HWREGH(base + ECAP_O_ECCTL2) |= ECAP_ECCTL2_REARM;
    EDIS;
}

//*****************************************************************************
//
//! Enables interrupt source.
//!
//! \param base is the base address of the ECAP module.
//! \param intFlags is the interrupt source to be enabled.
//!
//! This function sets and enables eCAP interrupt source. The following are
//! valid interrupt sources.
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_1 - Event 1 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_2 - Event 2 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_3 - Event 3 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_4 - Event 4 generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_OVERFLOW - Counter overflow generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_PERIOD   - Counter equal period generates
//!                                       interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_COMPARE  - Counter equal compare generates
//!                                       interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableInterrupt(uint32_t base, uint16_t intFlags)
{
    ASSERT(ECAP_isBaseValid(base));
    ASSERT((intFlags
               & ~(ECAP_ISR_SOURCE_CAPTURE_EVENT_1 | ECAP_ISR_SOURCE_CAPTURE_EVENT_2 | ECAP_ISR_SOURCE_CAPTURE_EVENT_3
                   | ECAP_ISR_SOURCE_CAPTURE_EVENT_4 | ECAP_ISR_SOURCE_COUNTER_OVERFLOW | ECAP_ISR_SOURCE_COUNTER_PERIOD
                   | ECAP_ISR_SOURCE_COUNTER_COMPARE))
           == 0U);

    EALLOW;

    //
    // Set bits in ECEINT register
    //
    HWREGH(base + ECAP_O_ECEINT) |= intFlags;
    EDIS;
}

//*****************************************************************************
//
//! Disables interrupt source.
//!
//! \param base is the base address of the ECAP module.
//! \param intFlags is the interrupt source to be disabled.
//!
//! This function clears and disables eCAP interrupt source. The following are
//! valid interrupt sources.
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_1   - Event 1 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_2   - Event 2 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_3   - Event 3 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_4   - Event 4 generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_OVERFLOW  - Counter overflow generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_PERIOD    - Counter equal period generates
//!                                        interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_COMPARE   - Counter equal compare generates
//!                                        interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_disableInterrupt(uint32_t base, uint16_t intFlags)
{

    ASSERT(ECAP_isBaseValid(base));
    ASSERT((intFlags
               & ~(ECAP_ISR_SOURCE_CAPTURE_EVENT_1 | ECAP_ISR_SOURCE_CAPTURE_EVENT_2 | ECAP_ISR_SOURCE_CAPTURE_EVENT_3
                   | ECAP_ISR_SOURCE_CAPTURE_EVENT_4 | ECAP_ISR_SOURCE_COUNTER_OVERFLOW | ECAP_ISR_SOURCE_COUNTER_PERIOD
                   | ECAP_ISR_SOURCE_COUNTER_COMPARE))
           == 0U);

    EALLOW;

    //
    // Clear bits in ECEINT register
    //
    HWREGH(base + ECAP_O_ECEINT) &= ~intFlags;
    EDIS;
}

//*****************************************************************************
//
//! Returns the interrupt flag.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function returns the eCAP interrupt flag. The following are valid
//! interrupt sources corresponding to the eCAP interrupt flag.
//!
//! \return Returns the eCAP interrupt that has occurred. The following are
//!  valid return values.
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_1   - Event 1 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_2   - Event 2 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_3   - Event 3 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_4   - Event 4 generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_OVERFLOW  - Counter overflow generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_PERIOD    - Counter equal period generates
//!                                        interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_COMPARE   - Counter equal compare generates
//!                                        interrupt
//!
//! \note - User can check if a combination of various interrupts have occurred
//!         by ORing the above return values.
//
//*****************************************************************************
static inline uint16_t ECAP_getInterruptSource(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Return contents of ECFLG register
    //
    return (HWREGH(base + ECAP_O_ECFLG) & 0xFEU);
}

//*****************************************************************************
//
//! Returns the Global interrupt flag.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function returns the eCAP Global interrupt flag.
//!
//! \return Returns true if there is a global eCAP interrupt, false otherwise.
//
//*****************************************************************************
static inline bool ECAP_getGlobalInterruptStatus(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Return contents of Global interrupt bit
    //
    return ((HWREGH(base + ECAP_O_ECFLG) & 0x1U) == 0x1U);
}

//*****************************************************************************
//
//! Clears interrupt flag.
//!
//! \param base is the base address of the ECAP module.
//! \param intFlags is the interrupt source.
//!
//! This function clears eCAP interrupt flags. The following are valid
//! interrupt sources.
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_1 - Event 1 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_2 - Event 2 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_3 - Event 3 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_4 - Event 4 generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_OVERFLOW - Counter overflow generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_PERIOD   - Counter equal period generates
//!                                       interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_COMPARE  - Counter equal compare generates
//!                                       interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_clearInterrupt(uint32_t base, uint16_t intFlags)
{
    ASSERT(ECAP_isBaseValid(base));
    ASSERT((intFlags
               & ~(ECAP_ISR_SOURCE_CAPTURE_EVENT_1 | ECAP_ISR_SOURCE_CAPTURE_EVENT_2 | ECAP_ISR_SOURCE_CAPTURE_EVENT_3
                   | ECAP_ISR_SOURCE_CAPTURE_EVENT_4 | ECAP_ISR_SOURCE_COUNTER_OVERFLOW | ECAP_ISR_SOURCE_COUNTER_PERIOD
                   | ECAP_ISR_SOURCE_COUNTER_COMPARE))
           == 0U);

    //
    // Write to ECCLR register
    //
    HWREGH(base + ECAP_O_ECCLR) = intFlags;
}

//*****************************************************************************
//
//! Clears global interrupt flag
//!
//! \param base is the base address of the ECAP module.
//!
//! This function clears the global interrupt bit.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_clearGlobalInterrupt(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Write to INT bit
    //
    HWREGH(base + ECAP_O_ECCLR) = ECAP_ECCLR_INT;
}

//*****************************************************************************
//
//! Forces interrupt source.
//!
//! \param base is the base address of the ECAP module.
//! \param intFlags is the interrupt source.
//!
//! This function forces and enables eCAP interrupt source. The following are
//! valid interrupt sources.
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_1 - Event 1 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_2 - Event 2 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_3 - Event 3 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_4 - Event 4 generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_OVERFLOW - Counter overflow generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_PERIOD   - Counter equal period generates
//!                                       interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_COMPARE  - Counter equal compare generates
//!                                       interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_forceInterrupt(uint32_t base, uint16_t intFlags)
{
    ASSERT(ECAP_isBaseValid(base));
    ASSERT((intFlags
               & ~(ECAP_ISR_SOURCE_CAPTURE_EVENT_1 | ECAP_ISR_SOURCE_CAPTURE_EVENT_2 | ECAP_ISR_SOURCE_CAPTURE_EVENT_3
                   | ECAP_ISR_SOURCE_CAPTURE_EVENT_4 | ECAP_ISR_SOURCE_COUNTER_OVERFLOW | ECAP_ISR_SOURCE_COUNTER_PERIOD
                   | ECAP_ISR_SOURCE_COUNTER_COMPARE))
           == 0U);

    EALLOW;

    //
    // Write to ECFRC register
    //
    HWREGH(base + ECAP_O_ECFRC) = intFlags;
    EDIS;
}

//*****************************************************************************
//
//! Sets eCAP in Capture mode.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function sets the eCAP module to operate in Capture mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableCaptureMode(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Clear CAP/APWM bit
    //
    HWREGH(base + ECAP_O_ECCTL2) &= ~ECAP_ECCTL2_CAP_APWM;
    EDIS;
}

//*****************************************************************************
//
//! Sets eCAP in APWM mode.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function sets the eCAP module to operate in APWM mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableAPWMMode(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Set CAP/APWM bit
    //
    HWREGH(base + ECAP_O_ECCTL2) |= ECAP_ECCTL2_CAP_APWM;
    EDIS;
}

//*****************************************************************************
//
//! Enables counter reset on an event.
//!
//! \param base is the base address of the ECAP module.
//! \param event is the event number the time base gets reset.
//!
//! This function enables the base timer, TSCTR, to be reset on capture
//! event provided by the variable event. Valid inputs for event are
//! \b ECAP_EVENT_1 to \b ECAP_EVENT_4.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableCounterResetOnEvent(uint32_t base, ECAP_Events event)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Set CTRRST1,CTRRST2,CTRRST3 or CTRRST4 bits
    //
    HWREGH(base + ECAP_O_ECCTL1) |= 1U << ((2U * (uint16_t)event) + 1U);
    EDIS;
}

//*****************************************************************************
//
//! Disables counter reset on events.
//!
//! \param base is the base address of the ECAP module.
//! \param event is the event number the time base gets reset.
//!
//! This function disables the base timer, TSCTR, from being reset on capture
//! event provided by the variable event. Valid inputs for event are
//! \b ECAP_EVENT_1 to \b ECAP_EVENT_4.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_disableCounterResetOnEvent(uint32_t base, ECAP_Events event)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Clear CTRRST1,CTRRST2,CTRRST3 or CTRRST4 bits
    //
    HWREGH(base + ECAP_O_ECCTL1) &= ~(1U << ((2U * (uint16_t)event) + 1U));
    EDIS;
}

//*****************************************************************************
//
//! Enables time stamp capture.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function enables time stamp count to be captured
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableTimeStampCapture(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Set CAPLDEN bit
    //
    HWREGH(base + ECAP_O_ECCTL1) |= ECAP_ECCTL1_CAPLDEN;
    EDIS;
}

//*****************************************************************************
//
//! Disables time stamp capture.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function disables time stamp count to be captured
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_disableTimeStampCapture(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Clear CAPLDEN bit
    //
    HWREGH(base + ECAP_O_ECCTL1) &= ~ECAP_ECCTL1_CAPLDEN;
    EDIS;
}

//*****************************************************************************
//
//! Sets a phase shift value count.
//!
//! \param base is the base address of the ECAP module.
//! \param shiftCount is the phase shift value.
//!
//! This function writes a phase shift value to be loaded into the main time
//! stamp counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setPhaseShiftCount(uint32_t base, uint32_t shiftCount)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Write to CTRPHS
    //
    HWREG(base + ECAP_O_CTRPHS) = shiftCount;
}

//*****************************************************************************
//
//! Enable counter loading with phase shift value.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function enables loading of the counter with the value present in the
//! phase shift counter as defined by the ECAP_setPhaseShiftCount() function.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableLoadCounter(uint32_t base)
{

    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to SYNCI_EN
    //
    HWREGH(base + ECAP_O_ECCTL2) |= ECAP_ECCTL2_SYNCI_EN;
    EDIS;
}

//*****************************************************************************
//
//! Disable counter loading with phase shift value.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function disables loading of the counter with the value present in the
//! phase shift counter as defined by the ECAP_setPhaseShiftCount() function.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_disableLoadCounter(uint32_t base)
{

    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to SYNCI_EN
    //
    HWREGH(base + ECAP_O_ECCTL2) &= ~ECAP_ECCTL2_SYNCI_EN;
    EDIS;
}

//*****************************************************************************
//
//! Load time stamp counter
//!
//! \param base is the base address of the ECAP module.
//!
//! This function forces the value in the phase shift counter register to be
//! loaded into Time stamp counter register.
//! Make sure to enable loading of Time stamp counter by calling
//! ECAP_enableLoadCounter() function before calling this function.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_loadCounter(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to SWSYNC
    //
    HWREGH(base + ECAP_O_ECCTL2) |= ECAP_ECCTL2_SWSYNC;
    EDIS;
}

//*****************************************************************************
//
//! Configures Sync out signal mode.
//!
//! \param base is the base address of the ECAP module.
//! \param mode is the sync out mode.
//!
//! This function sets the sync out mode. Valid parameters for mode are:
//! - ECAP_SYNC_OUT_SYNCI - Trigger sync out on sync-in event.
//! - ECAP_SYNC_OUT_COUNTER_PRD - Trigger sync out when counter equals period.
//! - ECAP_SYNC_OUT_DISABLED - Disable sync out.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setSyncOutMode(uint32_t base, ECAP_SyncOutMode mode)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to SYNCO_SEL
    //
    HWREGH(base + ECAP_O_ECCTL2) = ((HWREGH(base + ECAP_O_ECCTL2) & (~ECAP_ECCTL2_SYNCO_SEL_M)) | (uint16_t)mode);
    EDIS;
}

//*****************************************************************************
//
//! Stops Time stamp counter.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function stops the time stamp counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_stopCounter(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Clear TSCTR
    //
    HWREGH(base + ECAP_O_ECCTL2) &= ~ECAP_ECCTL2_TSCTRSTOP;
    EDIS;
}

//*****************************************************************************
//
//! Starts Time stamp counter.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function starts the time stamp counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_startCounter(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Set TSCTR
    //
    HWREGH(base + ECAP_O_ECCTL2) |= ECAP_ECCTL2_TSCTRSTOP;
    EDIS;
}

//*****************************************************************************
//
//! Set eCAP APWM polarity.
//!
//! \param base is the base address of the ECAP module.
//! \param polarity is the polarity of APWM
//!
//! This function sets the polarity of the eCAP in APWM mode. Valid inputs for
//! polarity are:
//!  - ECAP_APWM_ACTIVE_HIGH - For active high.
//!  - ECAP_APWM_ACTIVE_LOW - For active low.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setAPWMPolarity(uint32_t base, ECAP_APWMPolarity polarity)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;
    HWREGH(base + ECAP_O_ECCTL2) = ((HWREGH(base + ECAP_O_ECCTL2) & ~ECAP_ECCTL2_APWMPOL) | (uint16_t)polarity);
    EDIS;
}

//*****************************************************************************
//
//! Set eCAP APWM period.
//!
//! \param base is the base address of the ECAP module.
//! \param periodCount is the period count for APWM.
//!
//! This function sets the period count of the APWM waveform.
//! periodCount takes the actual count which is written to the register. The
//! user is responsible for converting the desired frequency or time into
//! the period count.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setAPWMPeriod(uint32_t base, uint32_t periodCount)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Write to CAP1
    //
    HWREG(base + ECAP_O_CAP1) = periodCount;
}

//*****************************************************************************
//
//! Set eCAP APWM on or off time count.
//!
//! \param base is the base address of the ECAP module.
//! \param compareCount is the on or off count for APWM.
//!
//! This function sets the on or off time count of the APWM waveform depending
//! on the polarity of the output. If the output , as set by
//! ECAP_setAPWMPolarity(), is active high then compareCount determines the on
//! time. If the output is active low then compareCount determines the off
//! time. compareCount takes the actual count which is written to the register.
//! The user is responsible for converting the desired frequency or time into
//! the appropriate count value.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setAPWMCompare(uint32_t base, uint32_t compareCount)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Write to CAP2
    //
    HWREG(base + ECAP_O_CAP2) = compareCount;
}

//*****************************************************************************
//
//! Load eCAP APWM shadow period.
//!
//! \param base is the base address of the ECAP module.
//! \param periodCount is the shadow period count for APWM.
//!
//! This function sets the shadow period count of the APWM waveform.
//! periodCount takes the actual count which is written to the register. The
//! user is responsible for converting the desired frequency or time into
//! the period count.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setAPWMShadowPeriod(uint32_t base, uint32_t periodCount)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Write to CAP3
    //
    HWREG(base + ECAP_O_CAP3) = periodCount;
}

//*****************************************************************************
//
//! Set eCAP APWM shadow on or off time count.
//!
//! \param base is the base address of the ECAP module.
//! \param compareCount is the on or off count for APWM.
//!
//! This function sets the shadow on or off time count of the APWM waveform
//! depending on the polarity of the output. If the output , as set by
//! ECAP_setAPWMPolarity() , is active high then compareCount determines the
//! on time. If the output is active low then compareCount determines the off
//! time. compareCount takes the actual count which is written to the register.
//! The user is responsible for converting the desired frequency or time into
//! the appropriate count value.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setAPWMShadowCompare(uint32_t base, uint32_t compareCount)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Write to CAP4
    //
    HWREG(base + ECAP_O_CAP4) = compareCount;
}

//*****************************************************************************
//
//! Returns the time base counter value.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function returns the time base counter value.
//!
//! \return Returns the time base counter value.
//
//*****************************************************************************
static inline uint32_t ECAP_getTimeBaseCounter(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Read the Time base counter value
    //
    return (HWREG(base + ECAP_O_TSCTR));
}

//*****************************************************************************
//
//! Returns event time stamp.
//!
//! \param base is the base address of the ECAP module.
//! \param event is the event number.
//!
//! This function returns the current time stamp count of the given event.
//! Valid values for event are \b ECAP_EVENT_1 to \b ECAP_EVENT_4.
//!
//! \return Event time stamp value or 0 if \e event is invalid.
//
//*****************************************************************************
static inline uint32_t ECAP_getEventTimeStamp(uint32_t base, ECAP_Events event)
{
    uint32_t count;

    ASSERT(ECAP_isBaseValid(base));

    switch (event)
    {
        case ECAP_EVENT_1:

            //
            // Read CAP1 register
            //
            count = HWREG(base + ECAP_O_CAP1);
            break;

        case ECAP_EVENT_2:
            //
            // Read CAP2 register
            //
            count = HWREG(base + ECAP_O_CAP2);
            break;

        case ECAP_EVENT_3:

            //
            // Read CAP3 register
            //
            count = HWREG(base + ECAP_O_CAP3);
            break;

        case ECAP_EVENT_4:

            //
            // Read CAP4 register
            //
            count = HWREG(base + ECAP_O_CAP4);
            break;

        default:

            //
            // Invalid event parameter
            //
            count = 0U;
            break;
    }

    return (count);
}

//*****************************************************************************
//
//! Select eCAP input.
//!
//! \param base is the base address of the ECAP module.
//! \param input is the eCAP input signal.
//!
//! This function selects the eCAP input signal.
//!
//! Please refer to the ::ECAP_InputCaptureSignals Enum for the valid values
//! to be passed to \e input parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_selectECAPInput(uint32_t base, ECAP_InputCaptureSignals input)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to ECCTL0
    //
    HWREGH(base + ECAP_O_ECCTL0) = ((HWREGH(base + ECAP_O_ECCTL0) & ~ECAP_ECCTL0_INPUTSEL_M) | (uint16_t)input);
    EDIS;
}

//*****************************************************************************
//
//! Resets eCAP counters and flags.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function resets the main counter (TSCTR register), event filter,
//! modulo counter, capture events and counter overflow flags
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_resetCounters(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to ECCTL2
    //
    HWREGH(base + ECAP_O_ECCTL2) |= ECAP_ECCTL2_CTRFILTRESET;
    EDIS;
}

//*****************************************************************************
//
//! Sets the eCAP DMA source.
//!
//! \param base is the base address of the ECAP module.
//! \param event is the eCAP event for the DMA
//!
//! This function sets the eCAP event source for the DMA trigger.
//! Valid values for \e event are \b ECAP_EVENT_1 to \b ECAP_EVENT_4.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setDMASource(uint32_t base, ECAP_Events event)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to ECCTL2
    //
    HWREGH(base + ECAP_O_ECCTL2)
        = ((HWREGH(base + ECAP_O_ECCTL2) & ~ECAP_ECCTL2_DMAEVTSEL_M) | ((uint16_t)event << ECAP_ECCTL2_DMAEVTSEL_S));
    EDIS;
}

//*****************************************************************************
//
//! Return the Modulo counter status.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function returns the modulo counter status, indicating which register
//! gets loaded on the next capture event.
//!
//! \return Returns an \b ECAP_EVENT_n value indicating that CAPn is the
//! register to be loaded on the next event.
//
//*****************************************************************************
static inline ECAP_Events ECAP_getModuloCounterStatus(uint32_t base)
{
    uint16_t counterStatusValue;

    ASSERT(ECAP_isBaseValid(base));

    counterStatusValue = (((HWREGH(base + ECAP_O_ECCTL2) & ECAP_ECCTL2_MODCNTRSTS_M) >> ECAP_ECCTL2_MODCNTRSTS_S));

    //
    // Read MODCNTRSTS bit
    //
    return ((ECAP_Events)(counterStatusValue));
}

//*****************************************************************************
//
//! Configures emulation mode.
//!
//! \param base is the base address of the ECAP module.
//! \param mode is the emulation mode.
//!
//! This function configures the eCAP counter, TSCTR,  to the desired emulation
//! mode when emulation suspension occurs. Valid inputs for mode are:
//! - ECAP_EMULATION_STOP  - Counter is stopped immediately.
//! - ECAP_EMULATION_RUN_TO_ZERO - Counter runs till it reaches 0.
//! - ECAP_EMULATION_FREE_RUN - Counter is not affected.
//!
//! \return None.
//
//*****************************************************************************
extern void ECAP_setEmulationMode(uint32_t base, ECAP_EmulationMode mode);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************

#if 0

typedef enum
{
    ECAP_CAP_MODE  = 0x0U,
    ECAP_APWM_MODE = 0x1U,
} ECAP_Mode;

typedef enum
{
    ECAP_EVENT_1 = 0x0U,
    ECAP_EVENT_2 = 0x1U,
    ECAP_EVENT_3 = 0x2U,
    ECAP_EVENT_4 = 0x3U,
} ECAP_Events;

typedef enum
{
    ECAP_EMULATION_STOP        = 0x0U,
    ECAP_EMULATION_RUN_TO_ZERO = 0x1U,
    ECAP_EMULATION_FREE_RUN    = 0x2U,
} ECAP_EmulationMode;

typedef enum
{
    ECAP_CAP_MODE_CONTINUE = 0x0U,
    ECAP_CAP_MODE_ONE_SHOT = 0x1U,
} ECAP_CaptureMode;

typedef enum
{
    ECAP_CAP_COUNT_MODE_CONTINUE = 0x0U,
    ECAP_CAP_COUNT_MODE_RESET    = 0x1U,
} ECAP_CapCountMode;

typedef enum
{
    ECAP_APWM_ACTIVE_HIGH = 0x0,
    ECAP_APWM_ACTIVE_LOW  = 0x1,
} ECAP_APWMPolarity;

typedef enum
{
    ECAP_EVENT_RISE_EDGE = 0U,
    ECAP_EVENT_FALL_EDGE = 1U,
} ECAP_EventPolarity;

typedef enum
{
    ECAP_SYNCIN_DISABLE = 0x0U,
    ECAP_SYNCIN_ENABLE  = 0x1U,
} ECAP_SyncInEnType;

typedef enum
{
    ECAP_SYNC_OUT_SYNCI       = 0x0U,
    ECAP_SYNC_OUT_COUNTER_PRD = 0x1U,
    ECAP_SYNC_OUT_DISABLED    = 0x2U,
} ECAP_SyncOutMode;

typedef enum
{
    ECAP_INPUT_INPUTXBAR1                     = 0,
    ECAP_INPUT_INPUTXBAR2                     = 1,
    ECAP_INPUT_INPUTXBAR3                     = 2,
    ECAP_INPUT_INPUTXBAR4                     = 3,
    ECAP_INPUT_INPUTXBAR5                     = 4,
    ECAP_INPUT_INPUTXBAR6                     = 5,
    ECAP_INPUT_INPUTXBAR7                     = 6,
    ECAP_INPUT_INPUTXBAR8                     = 7,
    ECAP_INPUT_INPUTXBAR9                     = 8,
    ECAP_INPUT_INPUTXBAR10                    = 9,
    ECAP_INPUT_INPUTXBAR11                    = 10,
    ECAP_INPUT_INPUTXBAR12                    = 11,
    ECAP_INPUT_INPUTXBAR13                    = 12,
    ECAP_INPUT_INPUTXBAR14                    = 13,
    ECAP_INPUT_INPUTXBAR15                    = 14,
    ECAP_INPUT_INPUTXBAR16                    = 15,
    ECAP_INPUT_CANA_INT0                      = 20,
    ECAP_INPUT_CANB_INT0                      = 21,
    ECAP_INPUT_ECAP_DELAY_CLOCK               = 23,
    ECAP_INPUT_OUTPUTXBAR1                    = 24,
    ECAP_INPUT_OUTPUTXBAR2                    = 25,
    ECAP_INPUT_OUTPUTXBAR3                    = 26,
    ECAP_INPUT_OUTPUTXBAR4                    = 27,
    ECAP_INPUT_OUTPUTXBAR5                    = 28,
    ECAP_INPUT_OUTPUTXBAR6                    = 29,
    ECAP_INPUT_OUTPUTXBAR7                    = 30,
    ECAP_INPUT_OUTPUTXBAR8                    = 31,
    ECAP_INPUT_ADC_C_EVENT4                   = 36,
    ECAP_INPUT_ADC_C_EVENT3                   = 37,
    ECAP_INPUT_ADC_C_EVENT2                   = 38,
    ECAP_INPUT_ADC_C_EVENT1                   = 39,
    ECAP_INPUT_ADC_B_EVENT4                   = 40,
    ECAP_INPUT_ADC_B_EVENT3                   = 41,
    ECAP_INPUT_ADC_B_EVENT2                   = 42,
    ECAP_INPUT_ADC_B_EVENT1                   = 43,
    ECAP_INPUT_ADC_A_EVENT4                   = 44,
    ECAP_INPUT_ADC_A_EVENT3                   = 45,
    ECAP_INPUT_ADC_A_EVENT2                   = 46,
    ECAP_INPUT_ADC_A_EVENT1                   = 47,
    ECAP_INPUT_SDFM1_FLT1_COMPARE_LOW         = 64,
    ECAP_INPUT_SDFM1_FLT2_COMPARE_LOW         = 65,
    ECAP_INPUT_SDFM1_FLT3_COMPARE_LOW         = 66,
    ECAP_INPUT_SDFM1_FLT4_COMPARE_LOW         = 67,
    ECAP_INPUT_SDFM1_FLT1_COMPARE_HIGH        = 80,
    ECAP_INPUT_SDFM1_FLT2_COMPARE_HIGH        = 81,
    ECAP_INPUT_SDFM1_FLT3_COMPARE_HIGH        = 82,
    ECAP_INPUT_SDFM1_FLT4_COMPARE_HIGH        = 83,
    ECAP_INPUT_SDFM1_FLT1_COMPARE_HIGH_OR_LOW = 88,
    ECAP_INPUT_SDFM1_FLT2_COMPARE_HIGH_OR_LOW = 89,
    ECAP_INPUT_SDFM1_FLT3_COMPARE_HIGH_OR_LOW = 90,
    ECAP_INPUT_SDFM1_FLT4_COMPARE_HIGH_OR_LOW = 91,
    ECAP_INPUT_CMPSS1_CTRIP_LOW               = 96,
    ECAP_INPUT_CMPSS2_CTRIP_LOW               = 97,
    ECAP_INPUT_CMPSS3_CTRIP_LOW               = 98,
    ECAP_INPUT_CMPSS4_CTRIP_LOW               = 99,
    ECAP_INPUT_CMPSS5_CTRIP_LOW               = 100,
    ECAP_INPUT_CMPSS6_CTRIP_LOW               = 101,
    ECAP_INPUT_CMPSS7_CTRIP_LOW               = 102,
    ECAP_INPUT_CMPSS1_CTRIP_HIGH              = 108,
    ECAP_INPUT_CMPSS2_CTRIP_HIGH              = 109,
    ECAP_INPUT_CMPSS3_CTRIP_HIGH              = 110,
    ECAP_INPUT_CMPSS4_CTRIP_HIGH              = 111,
    ECAP_INPUT_CMPSS5_CTRIP_HIGH              = 112,
    ECAP_INPUT_CMPSS6_CTRIP_HIGH              = 113,
    ECAP_INPUT_CMPSS7_CTRIP_HIGH              = 114,
    ECAP_INPUT_CMPSS1_CTRIP_HIGH_OR_LOW       = 120,
    ECAP_INPUT_CMPSS2_CTRIP_HIGH_OR_LOW       = 121,
    ECAP_INPUT_CMPSS3_CTRIP_HIGH_OR_LOW       = 122,
    ECAP_INPUT_CMPSS4_CTRIP_HIGH_OR_LOW       = 123,
    ECAP_INPUT_CMPSS5_CTRIP_HIGH_OR_LOW       = 124,
    ECAP_INPUT_CMPSS6_CTRIP_HIGH_OR_LOW       = 125,
    ECAP_INPUT_CMPSS7_CTRIP_HIGH_OR_LOW       = 126,
    ECAP_INPUT_RESERVED                       = 127,
} ECAP_InputCaptureSignals;

typedef struct
{
    vu32 tsctr;       /* offset:0x00 time-stamp counter */
    vu32 ctrphs;      /* offset:0x04 counter phase offset value register */
    vu32 cap1;        /* offset:0x08 capture 1 register */
    vu32 cap2;        /* offset:0x0C capture 2 register */
    vu32 cap3;        /* offset:0x10 capture 3 register */
    vu32 cap4;        /* offset:0x14 capture 4 register */
    vu32 reserve0[3]; /* offset:0x18~0x20 */

    union /* offset: 0x24 */
    {
        vu32 ecctl0;
        struct
        {                      /* bits description */
            vu32 inputsel : 7; /* 6:0 input source select */
        } ecctl0_bits;
    };

    union /* offset: 0x28 */
    {
        vu16 ecctl1;
        struct
        {                       /* bits description */
            vu16 cap1pol   : 1; /* 0 capture event 1 polarity select */
            vu16 ctrrst1   : 1; /* 1 counter reset on capture event 1 */
            vu16 cap2pol   : 1; /* 2 capture event 2 polarity select */
            vu16 ctrrst2   : 1; /* 3 counter reset on capture event 2 */
            vu16 cap3pol   : 1; /* 4 capture event 3 polarity select */
            vu16 ctrrst3   : 1; /* 5 counter reset on capture event 3 */
            vu16 cap4pol   : 1; /* 6 capture event 4 polarity select */
            vu16 ctrrst4   : 1; /* 7 counter reset on capture event 4 */
            vu16 caplden   : 1; /* 8 enable loading cap1-4 regs on a cap event */
            vu16 prescale  : 5; /* 13:9 event filter prescale select */
            vu16 free_soft : 2; /* 15:14 emulation mode */
        } ecctl1_bits;
    };

    union /* offset: 0x2A */
    {
        vu16 ecctl2;
        struct
        {                         /* bits description */
            vu16 cont_onesht : 1; /* 0 continuous or one-shot */
            vu16 stop_wrap   : 2; /* 2:1 stop value for one-shot, wrap for continuous */
            vu16 rearm       : 1; /* 3 one-shot re-arm */
            vu16 tsctrstop   : 1; /* 4 tscnt counter stop */
            vu16 synci_en    : 1; /* 5 counter sync-in select */
            vu16 synco_sel   : 2; /* 7:6 sync-out mode */
            vu16 swsync      : 1; /* 8 sw forced counter sync */
            vu16 cap_apwm    : 1; /* 9 cap/apwm operating mode select */
            vu16 apwmpol     : 1; /* 10  apwm output polarity select */
            vu16
                ctrfiltreset : 1; /* 11 reset event filter, modulus counter, and interrupt flags. */
            vu16 dmaevtsel   : 2; /* 13:12 dma event select */
            vu16 modcntrsts  : 2; /* 15:14 modulo counter status */
        } ecctl2_bits;
    };

    union /* offset: 0x2C */
    {
        vu16 eceint;
        struct
        {                        /* bits description */
            vu16 reserved0  : 1; /* 0 reserved */
            vu16 cevt1      : 1; /* 1 capture event 1 interrupt enable */
            vu16 cevt2      : 1; /* 2 capture event 2 interrupt enable */
            vu16 cevt3      : 1; /* 3 capture event 3 interrupt enable */
            vu16 cevt4      : 1; /* 4 capture event 4 interrupt enable */
            vu16 ctrovf     : 1; /* 5 counter overflow interrupt enable */
            vu16 ctr_eq_prd : 1; /* 6 period equal interrupt enable */
            vu16 ctr_eq_cmp : 1; /* 7 compare equal interrupt enable */
        } eceint_bits;
    };

    union /* offset: 0x2E */
    {
        vu16 ecflg;
        struct
        {                     /* bits description */
            vu16 intflag : 1; /* 0 global flag */
            vu16 cevt1   : 1; /* 1 capture event 1 interrupt flag */
            vu16 cevt2   : 1; /* 2 capture event 2 interrupt flag */
            vu16 cevt3   : 1; /* 3 capture event 3 interrupt flag */
            vu16 cevt4   : 1; /* 4 capture event 4 interrupt flag */
            vu16 ctrovf  : 1; /* 5 counter overflow interrupt flag */
            vu16 ctr_prd : 1; /* 6 period equal interrupt flag */
            vu16 ctr_cmp : 1; /* 7 compare equal interrupt flag */
        } ecflg_bits;
    };

    union /* offset: 0x30 */
    {
        vu16 ecclr;
        struct
        {                     /* bits description */
            vu16 intflag : 1; /* 0 ecap global interrupt status clear */
            vu16 cevt1   : 1; /* 1 capture event 1 status clear */
            vu16 cevt2   : 1; /* 2 capture event 2 status clear */
            vu16 cevt3   : 1; /* 3 capture event 3 status clear */
            vu16 cevt4   : 1; /* 4 capture event 4 status clear */
            vu16 ctrovf  : 1; /* 5 counter overflow status clear */
            vu16 ctr_prd : 1; /* 6 period equal status clear */
            vu16 ctr_cmp : 1; /* 7 compare equal status clear */
        } ecclr_bits;
    };

    union /* offset: 0x32 */
    {
        vu16 ecfrc;
        struct
        {                       /* bits description */
            vu16 reserved0 : 1; /* 0 reserved */
            vu16 cevt1     : 1; /* 1 capture event 1 force interrupt */
            vu16 cevt2     : 1; /* 2 capture event 2 force interrupt */
            vu16 cevt3     : 1; /* 3 capture event 3 force interrupt */
            vu16 cevt4     : 1; /* 4 capture event 4 force interrupt */
            vu16 ctrovf    : 1; /* 5 counter overflow force interrupt */
            vu16 ctr_prd   : 1; /* 6 period equal force interrupt */
            vu16 ctr_cmp   : 1; /* 7 compare equal force interrupt */
        } ecfrc_bits;
    };
} ecap_type;

#define ECAP1 ((ecap_type *)ECAP1_BASE)
#define ECAP2 ((ecap_type *)ECAP2_BASE)
#define ECAP3 ((ecap_type *)ECAP3_BASE)
#define ECAP4 ((ecap_type *)ECAP4_BASE)
#define ECAP5 ((ecap_type *)ECAP5_BASE)

STATIC_INLINE void ECAP_setEventPrescaler(ecap_type *ecap, uint16_t preScalerValue)
{
    ecap->ecctl1_bits.prescale = preScalerValue;
}

STATIC_INLINE void ECAP_enableCaptureMode(ecap_type *ecap)
{
    ecap->ecctl2_bits.cap_apwm = 0;
}

STATIC_INLINE void ECAP_enableAPWMMode(ecap_type *ecap)
{
    ecap->ecctl2_bits.cap_apwm = 1;
}

STATIC_INLINE void ECAP_setMode(ecap_type *ecap, ECAP_Mode mode)
{
    ecap->ecctl2_bits.cap_apwm = mode;
}

STATIC_INLINE void ECAP_setEventPolarity(
    ecap_type *ecap, ECAP_Events event, ECAP_EventPolarity polarity)
{
    ecap->ecctl1 = (ecap->ecctl1 & ~(1U << (event << 1))) | ((u16)polarity << (event << 1));
}

STATIC_INLINE void ECAP_setCaptureMode(ecap_type *ecap, ECAP_CaptureMode mode)
{
    ecap->ecctl2_bits.cont_onesht = mode;
}

STATIC_INLINE void ECAP_setStopWarp(ecap_type *ecap, u8 stop_warp)
{
    ecap->ecctl2_bits.stop_wrap = stop_warp;
}

STATIC_INLINE void ECAP_reArm(ecap_type *ecap)
{
    ecap->ecctl2_bits.rearm = 1;
}

STATIC_INLINE void ECAP_enableInterrupt(ecap_type *ecap, uint16_t intFlags)
{
    ecap->eceint |= intFlags;
}

STATIC_INLINE void ECAP_disableInterrupt(ecap_type *ecap, uint16_t intFlags)
{
    ecap->eceint &= ~intFlags;
}

STATIC_INLINE uint16_t ECAP_getInterruptSource(ecap_type *ecap)
{
    return ecap->ecflg;
}

STATIC_INLINE bool ECAP_getGlobalInterruptStatus(ecap_type *ecap)
{
    return ecap->ecflg_bits.intflag;
}

STATIC_INLINE void ECAP_clearInterrupt(ecap_type *ecap, uint16_t intFlags)
{
    ecap->ecclr = intFlags;
}

STATIC_INLINE void ECAP_clearGlobalInterrupt(ecap_type *ecap)
{
    ecap->ecclr_bits.intflag = 1;
}

STATIC_INLINE void ECAP_forceInterrupt(ecap_type *ecap, uint16_t intFlags)
{
    ecap->ecfrc = intFlags;
}

STATIC_INLINE void ECAP_enableCounterResetOnEvent(ecap_type *ecap, ECAP_Events event)
{
    ecap->ecctl1 |= 1U << (2U * event + 1U);
}

STATIC_INLINE void ECAP_disableCounterResetOnEvent(ecap_type *ecap, ECAP_Events event)
{
    ecap->ecctl1 &= ~(1U << (2U * event + 1U));
}

STATIC_INLINE void ECAP_enableTimeStampCapture(ecap_type *ecap)
{
    ecap->ecctl1_bits.caplden = 1;
}

STATIC_INLINE void ECAP_disableTimeStampCapture(ecap_type *ecap)
{
    ecap->ecctl1_bits.caplden = 0;
}

STATIC_INLINE void ECAP_setPhaseShiftCount(ecap_type *ecap, u32 shift)
{
    ecap->ctrphs = shift;
}

STATIC_INLINE void ECAP_enableLoadCounter(ecap_type *ecap)
{
    ecap->ecctl2_bits.synci_en = 1;
}

STATIC_INLINE void ECAP_disableLoadCounter(ecap_type *ecap)
{
    ecap->ecctl2_bits.synci_en = 0;
}

STATIC_INLINE void ECAP_loadCounter(ecap_type *ecap)
{
    ecap->ecctl2_bits.swsync = 1;
}

STATIC_INLINE void ECAP_setSyncOutMode(ecap_type *ecap, ECAP_SyncOutMode mode)
{
    ecap->ecctl2_bits.synco_sel = mode;
}

STATIC_INLINE void ECAP_stopCounter(ecap_type *ecap)
{
    ecap->ecctl2_bits.tsctrstop = 0;
}

STATIC_INLINE void ECAP_startCounter(ecap_type *ecap)
{
    ecap->ecctl2_bits.tsctrstop = 1;
}

STATIC_INLINE void ECAP_setAPWMPolarity(ecap_type *ecap, ECAP_APWMPolarity polarity)
{
    ecap->ecctl2_bits.apwmpol = polarity;
}

STATIC_INLINE void ECAP_setAPWMPeriod(ecap_type *ecap, u32 period)
{
    ecap->cap1 = period;
}

STATIC_INLINE void ECAP_setAPWMCompare(ecap_type *ecap, u32 compareCount)
{
    ecap->cap2 = compareCount;
}

STATIC_INLINE void ECAP_setAPWMShadowPeriod(ecap_type *ecap, u32 periodCount)
{
    ecap->cap3 = periodCount;
}

STATIC_INLINE void ECAP_setAPWMShadowCompare(ecap_type *ecap, u32 compareCount)
{
    ecap->cap4 = compareCount;
}

STATIC_INLINE void ECAP_setTimeBaseCounter(ecap_type *ecap, u32 count)
{
    ecap->tsctr = count;
}

STATIC_INLINE u32 ECAP_getTimeBaseCounter(ecap_type *ecap)
{
    return ecap->tsctr;
}

STATIC_INLINE u32 ECAP_getEventTimeStamp(ecap_type *ecap, ECAP_Events event)
{
    return REG32(&ecap->cap1 + event * 4);
}

STATIC_INLINE void ECAP_selectECAPInput(ecap_type *ecap, ECAP_InputCaptureSignals input)
{
    ecap->ecctl0 = input;
}

STATIC_INLINE void ECAP_resetCounters(ecap_type *ecap)
{
    ecap->ecctl2_bits.ctrfiltreset = 1;
}

STATIC_INLINE void ECAP_setDMASource(ecap_type *ecap, ECAP_Events event)
{
    ecap->ecctl2_bits.dmaevtsel = event;
}

STATIC_INLINE ECAP_Events ECAP_getModuloCounterStatus(ecap_type *ecap)
{
    return ecap->ecctl2_bits.modcntrsts;
}

STATIC_INLINE void ECAP_setEmulationMode(ecap_type *ecap, ECAP_EmulationMode mode)
{
    ecap->ecctl2_bits.modcntrsts = mode;
}

#endif

#ifdef __cplusplus
}
#endif

#endif
