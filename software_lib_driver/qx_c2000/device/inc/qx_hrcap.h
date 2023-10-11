/**
 **************************************************************************
 * @file	 qx_hrcap.h
 * @version	 v1.0.0
 * @date	 2023-06-06
 * @brief	 qx_hrcap header
 **************************************************************************
 */

#ifndef QX_HRCAP_H
#define QX_HRCAP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "qx_define.h"

struct HRCTL_BITS
{                         // bits description
    vu16 HRE        : 1;  // 0 High Resolution Enable
    vu16 HRCLKE     : 1;  // 1 High Resolution Clock Enable
    vu16 PRDSEL     : 1;  // 2 Calibration Period Match
    vu16 CALIBSTART : 1;  // 3 Calibration start
    vu16 CALIBSTS   : 1;  // 4 Calibration status
    vu16 CALIBCONT  : 1;  // 5 Continuous mode Calibration Select
    vu16 rsvd1      : 10; // 15:6 Reserved
    vu16 rsvd2      : 16; // 31:16 Reserved
};

union HRCTL_REG
{
    vu32 all;
    struct HRCTL_BITS bit;
};

struct HRINTEN_BITS
{                           // bits description
    vu16 rsvd1        : 1;  // 0 Reserved
    vu16 CALIBDONE    : 1;  // 1 Calibration doe interrupt enable
    vu16 CALPRDCHKSTS : 1;  // 2 Calibration period check status enable
    vu16 rsvd2        : 13; // 15:3 Reserved
    vu16 rsvd3        : 16; // 31:16 Reserved
};

union HRINTEN_REG
{
    vu32 all;
    struct HRINTEN_BITS bit;
};

struct HRFLG_BITS
{                           // bits description
    vu16 CALIBINT     : 1;  // 0 Global calibration Interrupt Status Flag
    vu16 CALIBDONE    : 1;  // 1 Calibration Done Interrupt Flag Bit
    vu16 CALPRDCHKSTS : 1;  // 2 Calibration period check status Flag Bi
    vu16 rsvd1        : 13; // 15:3 Reserved
    vu16 rsvd2        : 16; // 31:16 Reserved
};

union HRFLG_REG
{
    vu32 all;
    struct HRFLG_BITS bit;
};

struct HRCLR_BITS
{                           // bits description
    vu16 CALIBINT     : 1;  // 0 Clear Global calibration Interrupt Flag
    vu16 CALIBDONE    : 1;  // 1 Clear Calibration Done Interrupt Flag Bit
    vu16 CALPRDCHKSTS : 1;  // 2 Clear Calibration period check status Flag Bit
    vu16 rsvd1        : 13; // 15:3 Reserved
    vu16 rsvd2        : 16; // 31:16 Reserved
};

union HRCLR_REG
{
    vu32 all;
    struct HRCLR_BITS bit;
};

struct HRFRC_BITS
{                           // bits description
    vu16 rsvd1        : 1;  // 0 Reserved
    vu16 CALIBDONE    : 1;  // 1 Force Calibration Done Interrupt Flag Bit
    vu16 CALPRDCHKSTS : 1;  // 2 Force Calibration period check status Flag Bit
    vu16 rsvd2        : 13; // 15:3 Reserved
    vu16 rsvd3        : 16; // 31:16 Reserved
};

union HRFRC_REG
{
    vu32 all;
    struct HRFRC_BITS bit;
};

typedef struct
{
    union HRCTL_REG HRCTL;     // High-Res Control Register
    vu16 rsvd1[2];             // Reserved
    union HRINTEN_REG HRINTEN; // High-Res Calibration Interrupt Enable Register
    union HRFLG_REG HRFLG;     // High-Res Calibration Interrupt Flag Register
    union HRCLR_REG HRCLR;     // High-Res Calibration Interrupt Clear Register
    union HRFRC_REG HRFRC;     // High-Res Calibration Interrupt Force Register
    vu32 HRCALPRD;             // High-Res Calibration Period Register
    vu32 HRSYSCLKCTR;          // High-Res Calibration SYSCLK Counter Register
    vu32 HRSYSCLKCAP;          // High-Res Calibration SYSCLK Capture Register
    vu32 HRCLKCTR;             // High-Res Calibration HRCLK Counter Register
    vu32 HRCLKCAP;             // High-Res Calibration HRCLK Capture Register
} HRCAP_REGS;

#define HRCap6Regs ((HRCAP_REGS *)HRCAP6_BASE)
#define HRCap7Regs ((HRCAP_REGS *)HRCAP7_BASE)

#define HRCAP_O_TSCTR    0x0U  // Time-Stamp Counter
#define HRCAP_O_CTRPHS   0x4U  // Counter Phase Offset Value Register
#define HRCAP_O_CAP1     0x8U  // Capture 1 Register
#define HRCAP_O_CAP2     0xCU  // Capture 2 Register
#define HRCAP_O_CAP3     0x10U // Capture 3 Register
#define HRCAP_O_CAP4     0x14U // Capture 4 Register
#define HRCAP_O_ECCTL0   0x24U // Capture Control Register 0
#define HRCAP_O_ECCTL1   0x28U // Capture Control Register 1
#define HRCAP_O_ECCTL2   0x2AU // Capture Control Register 2
#define HRCAP_O_ECEINT   0x2CU // Capture Interrupt Enable Register
#define HRCAP_O_ECFLG    0x2EU // Capture Interrupt Flag Register
#define HRCAP_O_ECCLR    0x30U // Capture Interrupt Clear Register
#define HRCAP_O_ECFRC    0x32U // Capture Interrupt Force Register

#define HRCAP_O_HRCTL         0x0U    // High-Res Control Register
#define HRCAP_O_HRINTEN       0x8U    // High-Res Calibration Interrupt Enable Register
#define HRCAP_O_HRFLG         0xCU    // High-Res Calibration Interrupt Flag Register
#define HRCAP_O_HRCLR         0x10U   // High-Res Calibration Interrupt Clear Register
#define HRCAP_O_HRFRC         0x14U   // High-Res Calibration Interrupt Force Register
#define HRCAP_O_HRCALPRD      0x18U   // High-Res Calibration Period Register
#define HRCAP_O_HRSYSCLKCTR   0x1CU   // High-Res Calibration SYSCLK Counter Register
#define HRCAP_O_HRSYSCLKCAP   0x20U   // High-Res Calibration SYSCLK Capture Register
#define HRCAP_O_HRCLKCTR      0x24U   // High-Res Calibration HRCLK Counter Register
#define HRCAP_O_HRCLKCAP      0x28U   // High-Res Calibration HRCLK Capture Register

// The following are defines for the bit fields in the ECCTL0 register
#define HRCAP_ECCTL0_INPUTSEL_S   0U
#define HRCAP_ECCTL0_INPUTSEL_M   0x7FU   // INPUT source select

// The following are defines for the bit fields in the ECCTL1 register
#define HRCAP_ECCTL1_CAP1POL       0x1U      // Capture Event 1 Polarity select
#define HRCAP_ECCTL1_CTRRST1       0x2U      // Counter Reset on Capture Event 1
#define HRCAP_ECCTL1_CAP2POL       0x4U      // Capture Event 2 Polarity select
#define HRCAP_ECCTL1_CTRRST2       0x8U      // Counter Reset on Capture Event 2
#define HRCAP_ECCTL1_CAP3POL       0x10U     // Capture Event 3 Polarity select
#define HRCAP_ECCTL1_CTRRST3       0x20U     // Counter Reset on Capture Event 3
#define HRCAP_ECCTL1_CAP4POL       0x40U     // Capture Event 4 Polarity select
#define HRCAP_ECCTL1_CTRRST4       0x80U     // Counter Reset on Capture Event 4
#define HRCAP_ECCTL1_CAPLDEN       0x100U    // Enable Loading CAP1-4 regs on a Cap Event
#define HRCAP_ECCTL1_PRESCALE_S    9U
#define HRCAP_ECCTL1_PRESCALE_M    0x3E00U   // Event Filter prescale select
#define HRCAP_ECCTL1_FREE_SOFT_S   14U
#define HRCAP_ECCTL1_FREE_SOFT_M   0xC000U   // Emulation mode

// The following are defines for the bit fields in the ECCTL2 register
#define HRCAP_ECCTL2_CONT_ONESHT    0x1U      // Continuous or one-shot
#define HRCAP_ECCTL2_STOP_WRAP_S    1U
#define HRCAP_ECCTL2_STOP_WRAP_M    0x6U      // Stop value for one-shot, Wrap for continuous
#define HRCAP_ECCTL2_REARM          0x8U      // One-shot re-arm
#define HRCAP_ECCTL2_TSCTRSTOP      0x10U     // TSCNT counter stop
#define HRCAP_ECCTL2_SYNCI_EN       0x20U     // Counter sync-in select
#define HRCAP_ECCTL2_SYNCO_SEL_S    6U
#define HRCAP_ECCTL2_SYNCO_SEL_M    0xC0U     // Sync-out mode
#define HRCAP_ECCTL2_SWSYNC         0x100U    // SW forced counter sync
#define HRCAP_ECCTL2_CAP_APWM       0x200U    // CAP/APWM operating mode select
#define HRCAP_ECCTL2_APWMPOL        0x400U    //  APWM output polarity select
#define HRCAP_ECCTL2_CTRFILTRESET   0x800U    // Reset event filter, modulus counter, and interrupt
                                              // flags.
#define HRCAP_ECCTL2_DMAEVTSEL_S    12U
#define HRCAP_ECCTL2_DMAEVTSEL_M    0x3000U   // DMA event select
#define HRCAP_ECCTL2_MODCNTRSTS_S   14U
#define HRCAP_ECCTL2_MODCNTRSTS_M   0xC000U   // modulo counter status

// The following are defines for the bit fields in the ECEINT register
#define HRCAP_ECEINT_CEVT1        0x2U    // Capture Event 1 Interrupt Enable
#define HRCAP_ECEINT_CEVT2        0x4U    // Capture Event 2 Interrupt Enable
#define HRCAP_ECEINT_CEVT3        0x8U    // Capture Event 3 Interrupt Enable
#define HRCAP_ECEINT_CEVT4        0x10U   // Capture Event 4 Interrupt Enable
#define HRCAP_ECEINT_CTROVF       0x20U   // Counter Overflow Interrupt Enable
#define HRCAP_ECEINT_CTR_EQ_PRD   0x40U   // Period Equal Interrupt Enable
#define HRCAP_ECEINT_CTR_EQ_CMP   0x80U   // Compare Equal Interrupt Enable

// The following are defines for the bit fields in the ECFLG register
#define HRCAP_ECFLG_INT       0x1U    // Global Flag
#define HRCAP_ECFLG_CEVT1     0x2U    // Capture Event 1 Interrupt Flag
#define HRCAP_ECFLG_CEVT2     0x4U    // Capture Event 2 Interrupt Flag
#define HRCAP_ECFLG_CEVT3     0x8U    // Capture Event 3 Interrupt Flag
#define HRCAP_ECFLG_CEVT4     0x10U   // Capture Event 4 Interrupt Flag
#define HRCAP_ECFLG_CTROVF    0x20U   // Counter Overflow Interrupt Flag
#define HRCAP_ECFLG_CTR_PRD   0x40U   // Period Equal Interrupt Flag
#define HRCAP_ECFLG_CTR_CMP   0x80U   // Compare Equal Interrupt Flag


// The following are defines for the bit fields in the ECCLR register
#define HRCAP_ECCLR_INT       0x1U    // ECAP Global Interrupt Status Clear
#define HRCAP_ECCLR_CEVT1     0x2U    // Capture Event 1 Status Clear
#define HRCAP_ECCLR_CEVT2     0x4U    // Capture Event 2 Status Clear
#define HRCAP_ECCLR_CEVT3     0x8U    // Capture Event 3 Status Clear
#define HRCAP_ECCLR_CEVT4     0x10U   // Capture Event 4 Status Clear
#define HRCAP_ECCLR_CTROVF    0x20U   // Counter Overflow Status Clear
#define HRCAP_ECCLR_CTR_PRD   0x40U   // Period Equal Status Clear
#define HRCAP_ECCLR_CTR_CMP   0x80U   // Compare Equal Status Clear

// The following are defines for the bit fields in the ECFRC register
#define HRCAP_ECFRC_CEVT1     0x2U    // Capture Event 1 Force Interrupt
#define HRCAP_ECFRC_CEVT2     0x4U    // Capture Event 2 Force Interrupt
#define HRCAP_ECFRC_CEVT3     0x8U    // Capture Event 3 Force Interrupt
#define HRCAP_ECFRC_CEVT4     0x10U   // Capture Event 4 Force Interrupt
#define HRCAP_ECFRC_CTROVF    0x20U   // Counter Overflow Force Interrupt
#define HRCAP_ECFRC_CTR_PRD   0x40U   // Period Equal Force Interrupt
#define HRCAP_ECFRC_CTR_CMP   0x80U   // Compare Equal Force Interrupt



// The following are defines for the bit fields in the HRCTL register
#define HRCAP_HRCTL_HRE          0x1U    // High Resolution Enable
#define HRCAP_HRCTL_HRCLKE       0x2U    // High Resolution Clock Enable
#define HRCAP_HRCTL_PRDSEL       0x4U    // Calibration Period Match
#define HRCAP_HRCTL_CALIBSTART   0x8U    // Calibration start
#define HRCAP_HRCTL_CALIBSTS     0x10U   // Calibration status
#define HRCAP_HRCTL_CALIBCONT    0x20U   // Continuous mode Calibration Select

// The following are defines for the bit fields in the HRINTEN register
#define HRCAP_HRINTEN_CALIBDONE      0x2U   // Calibration doe interrupt enable
#define HRCAP_HRINTEN_CALPRDCHKSTS   0x4U   // Calibration period check status enable

// The following are defines for the bit fields in the HRFLG register
#define HRCAP_HRFLG_CALIBINT       0x1U   // Global calibration Interrupt Status Flag
#define HRCAP_HRFLG_CALIBDONE      0x2U   // Calibration Done Interrupt Flag Bit
#define HRCAP_HRFLG_CALPRDCHKSTS   0x4U   // Calibration period check status Flag Bi

// The following are defines for the bit fields in the HRCLR register
#define HRCAP_HRCLR_CALIBINT       0x1U   // Clear Global calibration Interrupt Flag
#define HRCAP_HRCLR_CALIBDONE      0x2U   // Clear Calibration Done Interrupt Flag Bit
#define HRCAP_HRCLR_CALPRDCHKSTS   0x4U   // Clear Calibration period check status Flag Bit

// The following are defines for the bit fields in the HRFRC register
#define HRCAP_HRFRC_CALIBDONE      0x2U   // Force Calibration Done Interrupt Flag Bit
#define HRCAP_HRFRC_CALPRDCHKSTS   0x4U   // Force Calibration period check status Flag Bit

#define HRCAP_GLOBAL_CALIBRATION_INTERRUPT 0x1U
//! Calibration done flag
//!
#define HRCAP_CALIBRATION_DONE  0x2U
//! Calibration period overflow flag
//!
#define HRCAP_CALIBRATION_PERIOD_OVERFLOW  0x4U

typedef enum
{
    HRCAP_CALIBRATION_CLOCK_SYSCLK = 0x0, //!< Use SYSCLK for period match.
    HRCAP_CALIBRATION_CLOCK_HRCLK  = 0x8  //!< Use HRCLK for period match.
}HRCAP_CalibrationClockSource;

typedef enum
{
    //! Continuous calibration disabled.
    HRCAP_CONTINUOUS_CALIBRATION_DISABLED = 0x00,
    //! Continuous calibration enabled.
    HRCAP_CONTINUOUS_CALIBRATION_ENABLED =  0x20
}HRCAP_ContinuousCalibrationMode;

#ifdef DEBUG
static inline bool HRCAP_isBaseValid(uint32_t base)
{
    return(
           (base == HRCAP6_BASE) ||
           (base == HRCAP7_BASE)
          );
}
#endif

static inline void
HRCAP_enableHighResolution(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));

    EALLOW

    // Set HRE bit.
    HWREGH(base + HRCAP_O_HRCTL) |= HRCAP_HRCTL_HRE;
    EDIS;
}

static inline void
HRCAP_enableHighResolutionClock(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));

    EALLOW;

    // Set HRCLKE bit.
    HWREGH(base + HRCAP_O_HRCTL) |= HRCAP_HRCTL_HRCLKE;
    EDIS;
}

static inline void
HRCAP_disbleHighResolutionClock(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));

    EALLOW;

    // Clear HRCLKE bit.
    HWREGH(base + HRCAP_O_HRCTL) &= ~HRCAP_HRCTL_HRCLKE;
    EDIS;
}

static inline void
HRCAP_startCalibration(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));

    EALLOW;

    // Set CALIBSTART bit.
    HWREGH(base + HRCAP_O_HRCTL) |= HRCAP_HRCTL_CALIBSTART;
    EDIS;
}

static inline void
HRCAP_setCalibrationMode(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));

    EALLOW;

    // Write to CALIBSTS and CALIBCONT bits.
    HWREGH(base + HRCAP_O_HRCTL) |= HRCAP_HRCTL_CALIBCONT;
    EDIS;
}

static inline void
HRCAP_enableCalibrationInterrupt(uint32_t base, uint16_t intFlags)
{
    ASSERT(HRCAP_isBaseValid(base));
    ASSERT((intFlags & ~(HRCAP_CALIBRATION_DONE |
                       HRCAP_CALIBRATION_PERIOD_OVERFLOW)) == 0);

    EALLOW;

    // Set CALIBDONE or CALPRDCHKSTS.
    HWREGH(base + HRCAP_O_HRINTEN) |= intFlags;
    EDIS;
}

static inline void
HRCAP_disableCalibrationInterrupt(uint32_t base, uint16_t intFlags)
{
    ASSERT(HRCAP_isBaseValid(base));
    ASSERT((intFlags & ~(HRCAP_CALIBRATION_DONE |
                       HRCAP_CALIBRATION_PERIOD_OVERFLOW)) == 0);

    EALLOW;

    // Clear CALIBDONE or CALPRDCHKSTS.
    HWREGH(base + HRCAP_O_HRINTEN) &= ~intFlags;
    EDIS;
}

static inline uint16_t
HRCAP_getCalibrationFlags(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));

    // Return contents of HRFLG register.
    return((uint16_t)(HWREGH(base + HRCAP_O_HRFLG) & 0x7U));
}

static inline void
HRCAP_clearCalibrationFlags(uint32_t base, uint16_t flags)
{
    ASSERT(HRCAP_isBaseValid(base));
    ASSERT((flags == (HRCAP_CALIBRATION_DONE |
                      HRCAP_GLOBAL_CALIBRATION_INTERRUPT)) ||
           (flags == (HRCAP_CALIBRATION_PERIOD_OVERFLOW |
                      HRCAP_GLOBAL_CALIBRATION_INTERRUPT)) ||
           (flags == (HRCAP_CALIBRATION_DONE |
                      HRCAP_GLOBAL_CALIBRATION_INTERRUPT |
                      HRCAP_CALIBRATION_PERIOD_OVERFLOW)));

    // Write to HRCLR register.
    HWREGH(base + HRCAP_O_HRCLR) |= flags;
}

static inline bool
HRCAP_isCalibrationBusy(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));

    // Read CALIBSTS bit.
    return((HWREGH(base + HRCAP_O_HRCTL) & HRCAP_HRCTL_CALIBSTS) ==
             HRCAP_HRCTL_CALIBSTS);
}

static inline void
HRCAP_forceCalibrationFlags(uint32_t base, uint16_t flag)
{
    ASSERT(HRCAP_isBaseValid(base));
    ASSERT((flag & ~(HRCAP_CALIBRATION_DONE |
                    HRCAP_CALIBRATION_PERIOD_OVERFLOW)) == 0);

    EALLOW;

    // Write to CALIBDONE or CALPRDCHKSTS bit.
    HWREGH(base + HRCAP_O_HRFRC) |= flag;
    EDIS;
}

static inline void
HRCAP_setCalibrationPeriod(uint32_t base, uint32_t sysclkHz)
{
    ASSERT(HRCAP_isBaseValid(base));

    EALLOW;
    HWREG(base + HRCAP_O_HRCALPRD) = (sysclkHz * 16U) / 10000U;
    EDIS;
}

static inline void
HRCAP_configCalibrationPeriod(uint32_t base, uint32_t sysclkHz,
                                                     float periodInMs)
{
    ASSERT(HRCAP_isBaseValid(base));

    EALLOW;
    HWREG(base + HRCAP_O_HRCALPRD) =
                    (uint32_t)((float32_t)sysclkHz * periodInMs / 1000.0F);
    EDIS;
}

static inline uint32_t
HRCAP_getCalibrationClockPeriod(uint32_t base,
                                HRCAP_CalibrationClockSource clockSource)
{
    ASSERT(HRCAP_isBaseValid(base));

    // Return HRCAP_O_HRSYSCLKCAP or HRCAP_O_HRCLKCAP.
    return(HWREG(base + HRCAP_O_HRSYSCLKCAP + (uint32_t)clockSource));
}

static inline float32_t
HRCAP_getScaleFactor(uint32_t base)
{
    ASSERT(HRCAP_isBaseValid(base));

    // Calculate and return the scale factor.
    return((float32_t)HRCAP_getCalibrationClockPeriod(base,
                                            HRCAP_CALIBRATION_CLOCK_SYSCLK) /
           (float32_t)HRCAP_getCalibrationClockPeriod(base,
                                            HRCAP_CALIBRATION_CLOCK_HRCLK));
}

static inline float32_t
HRCAP_convertEventTimeStampNanoseconds(uint32_t timeStamp,
                                       float32_t scaleFactor)
{
    // Convert the raw count value to nanoseconds using the given scale factor.
    return((float32_t)timeStamp * scaleFactor * ((float32_t)10.0 /
                                                 (float32_t)128.0));
}

#ifdef __cplusplus
}
#endif

#endif
