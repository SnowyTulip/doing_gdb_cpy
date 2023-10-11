/**
 **************************************************************************
 * @file     qx_dcc.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_DCC_H
#define QX_DCC_H

#include "qx_define.h"

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// DCC Individual Register Bit Definitions:

struct DCCGCTRL_BITS
{                         // bits description
    vu32 DCCENA     : 4;  // 3:0 DCC Enable
    vu32 ERRENA     : 4;  // 7:4 Error Enable
    vu32 SINGLESHOT : 4;  // 11:8 Single-Shot Enable
    vu32 DONEENA    : 4;  // 15:12 DONE Enable
    vu32 rsvd1      : 16; // 31:16 Reserved
};

union DCCGCTRL_REG
{
    vu32 all;
    struct DCCGCTRL_BITS bit;
};

struct DCCREV_BITS
{                    // bits description
    vu32 MINOR : 6;  // 5:0 Minor Revision Number
    vu32 rsvd1 : 2;  // 7:6 Reserved
    vu32 MAJOR : 3;  // 10:8 Major Revision Number
    vu32 rsvd2 : 5;  // 15:11 Reserved
    vu32 rsvd3 : 12; // 27:16 Reserved
    vu32 rsvd4 : 2;  // 29:28 Reserved
    vu32 rsvd5 : 2;  // 31:30 Reserved
};

union DCCREV_REG
{
    vu32 all;
    struct DCCREV_BITS bit;
};

struct DCCCNTSEED0_BITS
{                         // bits description
    vu32 COUNTSEED0 : 20; // 19:0 Seed Value for Counter 0
    vu32 rsvd1      : 12; // 31:20 Reserved
};

union DCCCNTSEED0_REG
{
    vu32 all;
    struct DCCCNTSEED0_BITS bit;
};

struct DCCVALIDSEED0_BITS
{                        // bits description
    vu32 VALIDSEED : 16; // 15:0 Seed Value for Valid Duration Counter 0
    vu32 rsvd1     : 16; // 31:16 Reserved
};

union DCCVALIDSEED0_REG
{
    vu32 all;
    struct DCCVALIDSEED0_BITS bit;
};

struct DCCCNTSEED1_BITS
{                         // bits description
    vu32 COUNTSEED1 : 20; // 19:0 Seed Value for Counter 1
    vu32 rsvd1      : 12; // 31:20 Reserved
};

union DCCCNTSEED1_REG
{
    vu32 all;
    struct DCCCNTSEED1_BITS bit;
};

struct DCCSTATUS_BITS
{                    // bits description
    vu32 ERR   : 1;  // 0 Error Flag
    vu32 DONE  : 1;  // 1 Single-Shot Done Flag
    vu32 rsvd1 : 14; // 15:2 Reserved
    vu32 rsvd2 : 16; // 31:16 Reserved
};

union DCCSTATUS_REG
{
    vu32 all;
    struct DCCSTATUS_BITS bit;
};

struct DCCCNT0_BITS
{                     // bits description
    vu32 COUNT0 : 20; // 19:0 Current Value of Counter 0
    vu32 rsvd1  : 12; // 31:20 Reserved
};

union DCCCNT0_REG
{
    vu32 all;
    struct DCCCNT0_BITS bit;
};

struct DCCVALID0_BITS
{                     // bits description
    vu32 VALID0 : 16; // 15:0 Current Value of Valid 0
    vu32 rsvd1  : 16; // 31:16 Reserved
};

union DCCVALID0_REG
{
    vu32 all;
    struct DCCVALID0_BITS bit;
};

struct DCCCNT1_BITS
{                     // bits description
    vu32 COUNT1 : 20; // 19:0 Current Value of Counter 1
    vu32 rsvd1  : 12; // 31:20 Reserved
};

union DCCCNT1_REG
{
    vu32 all;
    struct DCCCNT1_BITS bit;
};

struct DCCCLKSRC1_BITS
{                      // bits description
    vu32 CLKSRC1 : 4;  // 3:0 Clock Source Select for Counter 1
    vu32 rsvd1   : 8;  // 11:4 Reserved
    vu32 KEY     : 4;  // 15:12 Enables or Disables Clock Source Selection for COUNT1
    vu32 rsvd2   : 16; // 31:16 Reserved
};

union DCCCLKSRC1_REG
{
    vu32 all;
    struct DCCCLKSRC1_BITS bit;
};

struct DCCCLKSRC0_BITS
{                      // bits description
    vu32 CLKSRC0 : 4;  // 3:0 Clock Source Select for Counter 0
    vu32 rsvd1   : 12; // 15:4 Reserved
    vu32 rsvd2   : 16; // 31:16 Reserved
};

union DCCCLKSRC0_REG
{
    vu32 all;
    struct DCCCLKSRC0_BITS bit;
};

struct DCC_REGS
{
    union DCCGCTRL_REG DCCGCTRL;           // Global Control Register
    union DCCREV_REG DCCREV;               // DCC Revision Register
    union DCCCNTSEED0_REG DCCCNTSEED0;     // Counter 0 Seed Value
    union DCCVALIDSEED0_REG DCCVALIDSEED0; // Valid 0 Seed Value
    union DCCCNTSEED1_REG DCCCNTSEED1;     // Counter 1 Seed Value
    union DCCSTATUS_REG DCCSTATUS;         // DCC Status
    union DCCCNT0_REG DCCCNT0;             // Counter 0 Value
    union DCCVALID0_REG DCCVALID0;         // Valid Value 0
    union DCCCNT1_REG DCCCNT1;             // Counter 1 Value
    union DCCCLKSRC1_REG DCCCLKSRC1;       // Clock Source 1
    union DCCCLKSRC0_REG DCCCLKSRC0;       // Clock Source 0
};

#define Dcc0Regs ((struct DCC_REGS *)DCC0_BASE)

//*************************************************************************************************
// The following are defines for the DCC register offsets
//*************************************************************************************************
#define DCC_O_GCTRL      0x0U  // Global Control Register
#define DCC_O_REV        0x4U  // DCC Revision Register
#define DCC_O_CNTSEED0   0x8U  // Counter 0 Seed Value
#define DCC_O_VALIDSEED0 0xCU  // Valid 0 Seed Value
#define DCC_O_CNTSEED1   0x10U // Counter 1 Seed Value
#define DCC_O_STATUS     0x14U // DCC Status
#define DCC_O_CNT0       0x18U // Counter 0 Value
#define DCC_O_VALID0     0x1CU // Valid Value 0
#define DCC_O_CNT1       0x20U // Counter 1 Value
#define DCC_O_CLKSRC1    0x24U // Clock Source 1
#define DCC_O_CLKSRC0    0x28U // Clock Source 0

//*************************************************************************************************
// The following are defines for the bit fields in the DCCGCTRL register
//*************************************************************************************************
#define DCC_GCTRL_DCCENA_S     0U
#define DCC_GCTRL_DCCENA_M     0xFU // DCC Enable
#define DCC_GCTRL_ERRENA_S     4U
#define DCC_GCTRL_ERRENA_M     0xF0U // Error Enable
#define DCC_GCTRL_SINGLESHOT_S 8U
#define DCC_GCTRL_SINGLESHOT_M 0xF00U // Single-Shot Enable
#define DCC_GCTRL_DONEENA_S    12U
#define DCC_GCTRL_DONEENA_M    0xF000U // DONE Enable

//*************************************************************************************************
// The following are defines for the bit fields in the DCCREV register
//*************************************************************************************************
#define DCC_REV_MINOR_S 0U
#define DCC_REV_MINOR_M 0x3FU // Minor Revision Number
#define DCC_REV_MAJOR_S 8U
#define DCC_REV_MAJOR_M 0x700U // Major Revision Number

//*************************************************************************************************
// The following are defines for the bit fields in the DCCCNTSEED0 register
//*************************************************************************************************
#define DCC_CNTSEED0_COUNTSEED0_S 0U
#define DCC_CNTSEED0_COUNTSEED0_M 0xFFFFFU // Seed Value for Counter 0

//*************************************************************************************************
// The following are defines for the bit fields in the DCCVALIDSEED0 register
//*************************************************************************************************
#define DCC_VALIDSEED0_VALIDSEED_S 0U
#define DCC_VALIDSEED0_VALIDSEED_M 0xFFFFU // Seed Value for Valid Duration Counter 0

//*************************************************************************************************
// The following are defines for the bit fields in the DCCCNTSEED1 register
//*************************************************************************************************
#define DCC_CNTSEED1_COUNTSEED1_S 0U
#define DCC_CNTSEED1_COUNTSEED1_M 0xFFFFFU // Seed Value for Counter 1

//*************************************************************************************************
// The following are defines for the bit fields in the DCCSTATUS register
//*************************************************************************************************
#define DCC_STATUS_ERR  0x1U // Error Flag
#define DCC_STATUS_DONE 0x2U // Single-Shot Done Flag

//*************************************************************************************************
// The following are defines for the bit fields in the DCCCNT0 register
//*************************************************************************************************
#define DCC_CNT0_COUNT0_S 0U
#define DCC_CNT0_COUNT0_M 0xFFFFFU // Current Value of Counter 0

//*************************************************************************************************
// The following are defines for the bit fields in the DCCVALID0 register
//*************************************************************************************************
#define DCC_VALID0_VALID0_S 0U
#define DCC_VALID0_VALID0_M 0xFFFFU // Current Value of Valid 0

//*************************************************************************************************
// The following are defines for the bit fields in the DCCCNT1 register
//*************************************************************************************************
#define DCC_CNT1_COUNT1_S 0U
#define DCC_CNT1_COUNT1_M 0xFFFFFU // Current Value of Counter 1

//*************************************************************************************************
// The following are defines for the bit fields in the DCCCLKSRC1 register
//*************************************************************************************************
#define DCC_CLKSRC1_CLKSRC1_S 0U
#define DCC_CLKSRC1_CLKSRC1_M 0xFU // Clock Source Select for Counter 1
#define DCC_CLKSRC1_KEY_S     12U
#define DCC_CLKSRC1_KEY_M     0xF000U // Enables or Disables Clock Source Selection for COUNT1

//*************************************************************************************************
// The following are defines for the bit fields in the DCCCLKSRC0 register
//*************************************************************************************************
#define DCC_CLKSRC0_CLKSRC0_S 0U
#define DCC_CLKSRC0_CLKSRC0_M 0xFU // Clock Source Select for Counter 0

// Minimum and maximum values of valid seed value
#define DCC_VALIDSEED_MIN 4U
#define DCC_VALIDSEED_MAX 0xFFFFU

// Minimum and maximum values of counter0/1 seed value
#define DCC_COUNTSEED_MIN 1U
#define DCC_COUNTSEED_MAX 0xFFFFFU

// The reset value required to start or enable specific DCC operations
#define DCC_ENABLE_VALUE (0xAU)

// The reset value required to stop or disable specific DCC operations
#define DCC_DISABLE_VALUE (0x5U)

// A 16-bit register mask
#define DCC_REG_WORD_MASK (0xFFFFU)

// A 8-bit register mask
#define DCC_REG_BYTE_MASK (0xFFU)

// A mask for the DCC counter seed registers
#define DCC_SEED_REG_MASK (0xFFF0U)

// A mask for the DCC counter seed value
#define DCC_SEED_CNT_MASK (0xF0000U)

//*****************************************************************************
//
//! The following are defines for the mode parameter of the
//! DCC_enableSingleShotMode() function.
//
//*****************************************************************************
typedef enum
{
    //! Use to stop counting when counter0 and valid0 both reach zero
    DCC_MODE_COUNTER_ZERO = 0xA00U,
    //! Use to stop counting when counter1 reaches zero
    DCC_MODE_COUNTER_ONE = 0xB00U
} DCC_SingleShotMode;

//*****************************************************************************
//
//! The following are defines for the identifier parameter of the
//! DCC_getRevisionNumber() function.
//
//*****************************************************************************
typedef enum
{
    DCC_REVISION_MINOR = 0x0U, //!< The module minor revision number
    DCC_REVISION_MAJOR = 0x2U, //!< The module major revision number
} DCC_RevisionNumber;

//*****************************************************************************
//
//! The following are defines for the source parameter of the
//! DCC_setCounter1ClkSource() function.
//
//*****************************************************************************
typedef enum
{
    DCC_COUNT0SRC_XTAL    = 0x0U, //!< PLLRAWCLK Clock Out Source
    DCC_COUNT0SRC_INTOSC1 = 0x2U, //!< Internal Oscillator1 Clock Source
    DCC_COUNT0SRC_INTOSC2 = 0x3U, //!< Internal Oscillator2 Clock Source
} DCC_Count0ClockSource;

//*****************************************************************************
//
//! The following are defines for the source parameter of the
//! DCC_setCounter0ClkSource() function.
//
//*****************************************************************************
typedef enum
{
    DCC_COUNT1SRC_PLL     = 0x0U, //!< XTAL Clock Source
    DCC_COUNT1SRC_INTOSC1 = 0x1U, //!< Internal Oscillator1 Clock Source
    DCC_COUNT1SRC_INTOSC2 = 0x2U, //!< Internal Oscillator2 Clock Source
} DCC_Count1ClockSource;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks DCC base address.
//!
//! \param base specifies the DCC module base address.
//!
//! This function determines if an DCC module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool DCC_isBaseValid(uint32_t base)
{
    return ((base == DCC0_BASE));
}
#endif

//*****************************************************************************
//! Enables the DCC module.
//*****************************************************************************
static inline void DCC_enableModule()
{
    Dcc0Regs->DCCGCTRL.bit.DCCENA = 0xAU;
}

//*****************************************************************************
//! Disable the DCC module.
//*****************************************************************************
static inline void DCC_disableModule()
{
    Dcc0Regs->DCCGCTRL.bit.DCCENA = 0x5U;
}

//*****************************************************************************
//! Enable DCC Error Signal
//*****************************************************************************
static inline void DCC_enableErrorSignal()
{

    EALLOW;
    Dcc0Regs->DCCGCTRL.bit.ERRENA = 0xAU;
    EDIS;
}

//*****************************************************************************
//! Enable DCC Done Signal
//*****************************************************************************
static inline void DCC_enableDoneSignal()
{
    EALLOW;
    Dcc0Regs->DCCGCTRL.bit.DONEENA = 0xAU;
    EDIS;
}

//*****************************************************************************
// Disable DCC Error Signal
//*****************************************************************************
static inline void DCC_disableErrorSignal()
{
    EALLOW;
    Dcc0Regs->DCCGCTRL.bit.ERRENA = 0x5U;
    EDIS;
}

//*****************************************************************************
// Disable DCC Done Signal
//*****************************************************************************
static inline void DCC_disableDoneSignal()
{
    EALLOW;
    Dcc0Regs->DCCGCTRL.bit.DONEENA = 0x5U;
    EDIS;
}

//*****************************************************************************
// Set Single-Shot Mode
//*****************************************************************************
static inline void DCC_SetSingle_Shot()
{
    EALLOW;
    Dcc0Regs->DCCGCTRL.all = 0xaaaa;
    EDIS;
}
//*****************************************************************************
// Set Not Single-Shot Mode
//*****************************************************************************
static inline void DCC_DisSetSingle_Shot()
{
    EALLOW;
    Dcc0Regs->DCCGCTRL.all = 0xa5aa;
    EDIS;
}

//*****************************************************************************
//
//! Enable DCC Single-Shot Mode
//!
//! \param base is the DCC module base address
//! \param mode is the selected Single-Shot operation mode
//!
//! This function enables the single-shot mode and sets the operation mode.
//!
//! The \e mode parameter can have one of two values:
//! - \b DCC_MODE_COUNTER_ZERO - Stops counting when counter0 and valid0 both
//!   reach zero
//! - \b DCC_MODE_COUNTER_ONE  - Stops counting when counter1 reaches zero
//!
//! \return None.
//
//*****************************************************************************
static inline void DCC_enableSingleShotMode(DCC_SingleShotMode mode)
{
    // Set Single-Shot mode value to the appropriate register
    if (mode == DCC_MODE_COUNTER_ZERO)
    {
        EALLOW;
        Dcc0Regs->DCCGCTRL.bit.DCCENA     = 0x0U;
        Dcc0Regs->DCCGCTRL.bit.ERRENA     = 0x0U;
        Dcc0Regs->DCCGCTRL.bit.SINGLESHOT = 0xAU;
        EDIS;
    }
    else
    {
        EALLOW;
        Dcc0Regs->DCCGCTRL.bit.DCCENA     = 0x0U;
        Dcc0Regs->DCCGCTRL.bit.ERRENA     = 0x0U;
        Dcc0Regs->DCCGCTRL.bit.SINGLESHOT = 0xBU;
        EDIS;
    }
}

//*****************************************************************************
//
//! Disable DCC Single-Shot Mode
//!
//! \param base is the DCC module base address
//!
//! This function disables the DCC Single-Shot operation mode
//!
//! \return None.
//
//*****************************************************************************
static inline void DCC_disableSingleShotMode()
{
    EALLOW;
    Dcc0Regs->DCCGCTRL.bit.SINGLESHOT = 0x5U;
    EDIS;
}

//*****************************************************************************
// Get Error Flag Status
//*****************************************************************************
static inline bool DCC_getErrorStatus(uint32_t base)
{
    // Check the arguments.
    ASSERT(DCC_isBaseValid(base));
    // Get the error flag
    return ((bool)((HWREGH(base + DCC_O_STATUS) & DCC_STATUS_ERR) == DCC_STATUS_ERR));
}

//*****************************************************************************
// Get Single-Shot Done Flag Status
//*****************************************************************************
static inline bool DCC_getSingleShotStatus(uint32_t base)
{
    // Check the arguments.
    ASSERT(DCC_isBaseValid(base));
    // Read the done flag
    return ((bool)((HWREGH(base + DCC_O_STATUS) & DCC_STATUS_DONE) == DCC_STATUS_DONE));
}

//*****************************************************************************
//! Clear Error Status Flag
//*****************************************************************************
static inline void DCC_clearErrorInterupt()
{
    EALLOW;
    Dcc0Regs->DCCSTATUS.bit.ERR = 1;
    EDIS;
}

//*****************************************************************************
// Clear Single-Shot Done Status Flag
//*****************************************************************************
static inline void DCC_clearDoneInterupt()
{
    EALLOW;
    Dcc0Regs->DCCSTATUS.bit.DONE = 1;
    EDIS;
}

//*****************************************************************************
// Get Current Value of Counter 0
//*****************************************************************************
static inline uint32_t DCC_getCounter0Value()
{
    // Get the current counter 0 value
    return (HWREG(Dcc0Regs + DCC_O_CNT0));
}

//*****************************************************************************
//! Get Current Value of the Valid Duration Counter for Counter 0
//*****************************************************************************
static inline uint16_t DCC_getValidCounter0Value()
{
    // Get the current valid duration counter value
    return (HWREGH(Dcc0Regs + DCC_O_VALID0));
}

//*****************************************************************************
//! Get Current Value of Counter 1
//*****************************************************************************
static inline uint32_t DCC_getCounter1Value()
{
    // Get the current counter 1 value
    return (HWREG(Dcc0Regs + DCC_O_CNT1));
}

//*****************************************************************************
//! Set Counter 1 Clock Source
//*****************************************************************************
static inline void DCC_setCounter1ClkSource(uint32_t base, DCC_Count1ClockSource source)
{
    EALLOW;
    HWREGH(base + DCC_O_CLKSRC1)
        = (HWREGH(base + DCC_O_CLKSRC1) & (DCC_REG_BYTE_MASK << 4U)) | ((DCC_ENABLE_VALUE << 12U) | (uint16_t)source);
    EDIS;
}

//*****************************************************************************
//! Set Counter 0 Clock Source
//*****************************************************************************
static inline void DCC_setCounter0ClkSource(uint32_t base, DCC_Count0ClockSource source)
{
    EALLOW;
    HWREGH(base + DCC_O_CLKSRC0) = (HWREGH(base + DCC_O_CLKSRC0) & ~(DCC_CLKSRC0_CLKSRC0_M)) | (uint16_t)source;
    EDIS;
}

//*****************************************************************************
//! Get Counter 1 Clock Source
//*****************************************************************************
static inline uint16_t DCC_getCounter1ClkSource(uint32_t base)
{
    return (HWREGH(base + DCC_O_CLKSRC1) & DCC_CLKSRC1_CLKSRC1_M);
}

//*****************************************************************************
//! Get Counter 0 Clock Source
//*****************************************************************************
static inline uint16_t DCC_getCounter0ClkSource(uint32_t base)
{
    return (HWREGH(base + DCC_O_CLKSRC0) & DCC_CLKSRC0_CLKSRC0_M);
}

//*****************************************************************************
//
//! Set the seed values
//!
//! \param base is the DCC module base address
//! \param counter0 sets the seed value that gets loaded into Counter 0
//! \param validCounter0 sets the seed value that gets loaded into the valid
//!  duration counter for Counter 0
//! \param counter1 sets the seed value that gets loaded into Counter 1
//!
//! This function sets the seed values for Counter 0, Valid Duration Counter 0,
//! and Counter 1.
//!
//! \note
//! -# Operating DCC with '0' set as the seed value for Counter 0, Valid
//! Duration Counter 0, and/or Counter 1 will result in undefined operation.
//! -# The Valid Duration Counter 0 is designed to be at least four cycles
//! wide and shouldn't be programmed with a value less than '4'.
//!
//! \return None.
//
//*****************************************************************************

static inline void DCC_setCounterSeeds(uint32_t base, uint32_t counter0, uint32_t validCounter0, uint32_t counter1)
{
    // Check the arguments.
    ASSERT(DCC_isBaseValid(base));
    ASSERT(validCounter0 >= DCC_VALIDSEED_MIN);
    ASSERT(counter0 >= DCC_COUNTSEED_MIN);
    ASSERT(counter1 >= DCC_COUNTSEED_MIN);
    ASSERT(validCounter0 <= DCC_VALIDSEED_MAX);
    ASSERT(counter0 <= DCC_COUNTSEED_MAX);
    ASSERT(counter1 <= DCC_COUNTSEED_MAX);

    EALLOW;
    // Set Counter 0 Seed
    HWREGH(base + DCC_O_CNTSEED0) = counter0 & DCC_REG_WORD_MASK;
    HWREGH(base + DCC_O_CNTSEED0 + 2U)
        = (HWREGH(base + DCC_O_CNTSEED0 + 2U) & DCC_SEED_REG_MASK) | ((uint32_t)(counter0 & DCC_SEED_CNT_MASK) >> 16U);

    // Set Valid Duration Counter 0 Seed
    HWREGH(base + DCC_O_VALIDSEED0) = validCounter0;

    // Set Counter 1 Seed
    HWREGH(base + DCC_O_CNTSEED1) = counter1 & DCC_REG_WORD_MASK;
    HWREGH(base + DCC_O_CNTSEED1 + 2U)
        = (HWREGH(base + DCC_O_CNTSEED1 + 2U) & DCC_SEED_REG_MASK) | ((uint32_t)(counter1 & DCC_SEED_CNT_MASK) >> 16U);
    EDIS;
}

//*****************************************************************************
//
//! Get DCC Version Number
//!
//! \param base is the DCC module base address
//! \param identifier is the selected revision number identifier
//!
//! This function gets the specific version number.
//!
//! The \e identifier parameter can have one of these values:
//! - \b DCC_REVISION_MINOR      - The minor revision number
//! - \b DCC_REVISION_MAJOR      - The major revision number
//!
//! \return Specified revision number
//
//*****************************************************************************
extern uint16_t DCC_getRevisionNumber(uint32_t base, DCC_RevisionNumber identifier);

//*****************************************************************************
//
//! Verify the frequency of a clock source using a reference clock
//!
//! \param base is the DCC module base address
//! \param clock1 is the clock source to be verified
//! \param freq1 is the frequency of the clock source to be verified
//! \param clock0 is the reference clock
//! \param freq0 is the frequency of the reference clock
//! \param tolerance is the DCC error tolerance in percentage
//! \param freqerr is the allowable Frequency Tolerance in percentage
//! \param freq_sysclk is the frequency of the system clock
//!
//! This function verifies the frequency of the specified clock using a
//! reference clock.
//!
//! \note Make sure that the frequency of all the clocks are in the same unit
//!
//! \return Returns \b true if the actual frequency of clock1 is matching
//! freq1, \b false otherwise
//
//*****************************************************************************
extern bool DCC_verifyClockFrequency(uint32_t base, DCC_Count1ClockSource clock1, float32_t freq1,
    DCC_Count0ClockSource clock0, float32_t freq0, float32_t tolerance, float32_t freqerr);

//*****************************************************************************
//
//! Measure the frequency of a clock source using a reference clock
//!
//! \param base is the DCC module base address
//! \param clock1 is the clock source to be measured
//! \param clock0 is the reference clock
//! \param freq0 is the frequency of the reference clock
//! \param tolerance is the DCC error tolerance in percentage
//! \param freqerr is the allowable Frequency Tolerance in percentage
//! \param freq_sysclk is the frequency of the system clock
//!
//! This function measures the frequency of the specified clock using a
//! reference clock.
//!
//! \note Make sure that the frequency of all the clocks are in the same unit
//!
//! \return Measured clock frequency
//
//*****************************************************************************
extern float32_t DCC_measureClockFrequency(uint32_t base, DCC_Count1ClockSource clock1, DCC_Count0ClockSource clock0,
    float32_t freq0, float32_t tolerance, float32_t freqerr, float32_t freq_sysclk);

//*****************************************************************************
//
//! Continuously monitor the frequency of a clock source using a reference clock
//!
//! \param base is the DCC module base address
//! \param clock1 is the clock source to be verified
//! \param freq1 is the frequency of the clock source to be verified
//! \param clock0 is the reference clock
//! \param freq0 is the frequency of the reference clock
//! \param tolerance is the DCC error tolerance in percentage
//! \param freqerr is the allowable Frequency Tolerance in percentage
//! \param freq_sysclk is the frequency of the system clock
//!
//! This function continuously monitors the frequency of the specified clock
//! using a reference clock. An error signal is generated if the frequency
//! ratio is altered.
//!
//! \note Make sure that the frequency of all the clocks are in the same unit
//!
//! \note This function does not enable the DCC interrupt. The user application
//! must enable it to trigger an intetrupt when an error is detected.
//!
//! \return Returns None
//
//*****************************************************************************
extern void DCC_continuousMonitor(uint32_t base, DCC_Count1ClockSource clock1, float32_t freq1,
    DCC_Count0ClockSource clock0, float32_t freq0, float32_t tolerance, float32_t freqerr, float32_t freq_sysclk);
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

#ifdef __cplusplus
}
#endif

#endif
