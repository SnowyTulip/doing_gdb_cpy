/**
 **************************************************************************
 * @file     qx_dac.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_DAC_H
#define QX_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"

//---------------------------------------------------------------------------
// DAC Individual Register Bit Definitions:

struct DACREV_BITS
{                    // bits description
    vu32 REV   : 8;  // 7:0 DAC Revision Register
    vu32 rsvd1 : 24; // 31:8 Reserved
};

union DACREV_REG
{
    vu32 all;
    struct DACREV_BITS bit;
};

struct DACCTL_BITS
{                       // bits description
    vu32 DACREFSEL : 2; // 1:0 DAC Reference Select
    vu32 rsvd1     : 1; // 2 Reserved
    vu32 LOADMODE  : 1; // 3 DACVALA Load Mode
    vu32 rsvd2     : 1; // 4 Reserved
    vu32 SYNCSEL   : 4; // 8:5 DAC EPWMSYNCPER Select
    vu32 MODE      : 2; // 10:9 DAC Mode Select
    vu32 rsvd3     : 6; // 16:11 Reserved
    vu32 PRESCALE  : 8; // 24:17 DAC frequency division
    vu32 rsvd4     : 7; // 31:25 Reserved
};

union DACCTL_REG
{
    vu32 all;
    struct DACCTL_BITS bit;
};

struct DACVALA_BITS
{                      // bits description
    vu32 DACVALA : 12; // 11:0 DAC Active Output Code
    vu32 rsvd1   : 20; // 31:12 Reserved
};

union DACVALA_REG
{
    vu32 all;
    struct DACVALA_BITS bit;
};

struct DACVALS_BITS
{                      // bits description
    vu32 DACVALS : 12; // 11:0 DAC Shadow Output Code
    vu32 rsvd1   : 20; // 31:12 Reserved
};

union DACVALS_REG
{
    vu32 all;
    struct DACVALS_BITS bit;
};

struct DACOUTEN_BITS
{                       // bits description
    vu32 DACOUTEN : 1;  // 0 DAC Output Code
    vu32 rsvd1    : 31; // 31:1 Reserved
};

union DACOUTEN_REG
{
    vu32 all;
    struct DACOUTEN_BITS bit;
};

struct DACLOCK_BITS
{                       // bits description
    vu32 DACCTL   : 1;  // 0 DAC Control Register Lock
    vu32 DACVAL   : 1;  // 1 DAC Value Register Lock
    vu32 DACOUTEN : 1;  // 2 DAC Output Enable Register Lock
    vu32 rsvd1    : 9;  // 11:3 Reserved
    vu32 KEY      : 4;  // 15:12 DAC Register Lock Key
    vu32 rsvd2    : 16; // 31:16 Reserved
};

union DACLOCK_REG
{
    vu32 all;
    struct DACLOCK_BITS bit;
};

struct DACTRIM_BITS
{                          // bits description
    vu32 OFFSET_TRIM : 8;  // 7:0 DAC Offset Trim
    vu32 rsvd1       : 4;  // 11:8 Reserved
    vu32 rsvd2       : 20; // 31:12 Reserved
};

union DACTRIM_REG
{
    vu32 all;
    struct DACTRIM_BITS bit;
};

typedef struct
{
    union DACREV_REG DACREV;     // DAC Revision Register
    union DACCTL_REG DACCTL;     // DAC Control Register
    union DACVALA_REG DACVALA;   // DAC Value Register - Active
    union DACVALS_REG DACVALS;   // DAC Value Register - Shadow
    union DACOUTEN_REG DACOUTEN; // DAC Output Enable Register
    union DACLOCK_REG DACLOCK;   // DAC Lock Register
    union DACTRIM_REG DACTRIM;   // DAC Trim Register
} DAC_REGS;

#define DACA_BASE (DAC_BASE)
#define DACB_BASE (DAC_BASE + 0x40U)
#define DacaRegs  ((DAC_REGS *)(DACA_BASE))
#define DacbRegs  ((DAC_REGS *)(DACB_BASE))

//*****************************************************************************
//
//! Values that can be passed to DAC_setReferenceVoltage() as the \e source
//! parameter.
//
//*****************************************************************************
typedef enum
{
    DAC_REF_VDAC       = 0, //!< VDAC reference voltage
    DAC_REF_ADC_VREFHI = 1  //!< ADC VREFHI reference voltage
} DAC_ReferenceVoltage;

//*****************************************************************************
//
//! Values that can be passed to DAC_setGainMode() as the \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    DAC_GAIN_ONE = 0, //!< Gain set to 1
    DAC_GAIN_TWO = 1, //!< Gain set to 2
    DAC_BYPASS   = 2  //!< Bypass
} DAC_GainMode;

//*****************************************************************************
//
//! Values that can be passed to DAC_setLoadMode() as the \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    DAC_LOAD_SYSCLK  = 0, //!< Load on next SYSCLK
    DAC_LOAD_PWMSYNC = 1  //!< Load on next PWMSYNC specified by SYNCSEL
} DAC_LoadMode;

typedef enum
{
    EPWM1SYNCPER = 0,
    EPWM2SYNCPER = 1,
    EPWM3SYNCPER = 2,
    EPWM4SYNCPER = 3,
    EPWM5SYNCPER = 4,
    EPWM6SYNCPER = 5,
    EPWM7SYNCPER = 6,
    EPWM8SYNCPER = 7
} DAC_SyncSel;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks DAC base address.
//!
//! \param base specifies the DAC module base address.
//!
//! This function determines if an DAC module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool DAC_isBaseValid(uint32_t base)
{
    return ((base == DACA_BASE) || (base == DACB_BASE));
}
#endif

//*****************************************************************************
//
//! Get the DAC Revision value
//!
//! \param base is the DAC module base address
//!
//! This function gets the DAC revision value.
//!
//! \return Returns the DAC revision value.
//
//*****************************************************************************
static inline uint16_t DAC_getRevision(uint32_t base)
{
    //
    // Get the revision value.
    //
    return (((DAC_REGS *)base)->DACREV.all);
}

//*****************************************************************************
//
//! Sets the DAC Reference Voltage
//!
//! \param base is the DAC module base address
//! \param source is the selected reference voltage
//!
//! This function sets the DAC reference voltage.
//!
//! The \e source parameter can have one of two values:
//! - \b DAC_REF_VDAC       - The VDAC reference voltage
//! - \b DAC_REF_ADC_VREFHI - The ADC VREFHI reference voltage
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_setReferenceVoltage(uint32_t base, DAC_ReferenceVoltage source)
{
    //
    // Set the reference  voltage
    //
    EALLOW;

    ((DAC_REGS *)base)->DACCTL.bit.DACREFSEL = source;

    EDIS;
}

//*****************************************************************************
//
//! Sets the DAC Gain Mode
//!
//! \param base is the DAC module base address
//! \param mode is the selected gain mode
//!
//! This function sets the DAC gain mode for the buffered output.
//!
//! The \e mode parameter can have one of two values:
//! - \b DAC_GAIN_ONE  - Gain is set to 1
//! - \b DAC_GAIN_TWO  - Gain is set to 2
//!
//! \note This value is only used when \e DAC_REF_ADC_VREFHI is set using
//! DAC_setReferenceVoltage() and internal ADC reference mode is selected.
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_setGainMode(uint32_t base, DAC_GainMode mode)
{
    //
    // Set the gain mode
    //
    EALLOW;

    ((DAC_REGS *)base)->DACCTL.bit.MODE = mode;

    EDIS;
}

//*****************************************************************************
//
//! Sets the DAC Load Mode
//!
//! \param base is the DAC module base address
//! \param mode is the selected load mode
//!
//! This function sets the DAC load mode.
//!
//! The \e mode parameter can have one of two values:
//! - \b DAC_LOAD_SYSCLK   - Load on next SYSCLK
//! - \b DAC_LOAD_PWMSYNC  - Load on next PWMSYNC specified by SYNCSEL
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_setLoadMode(uint32_t base, DAC_LoadMode mode)
{
    //
    // Set the load mode
    //
    EALLOW;

    ((DAC_REGS *)base)->DACCTL.bit.LOADMODE = mode;

    EDIS;
}

//*****************************************************************************
//
//! Sets the DAC PWMSYNC Signal
//!
//! \param base is the DAC module base address
//! \param signal is the selected PWM signal
//!
//! This function sets the DAC PWMSYNC signal.
//!
//! The \e signal parameter must be set to a number that represents the PWM
//! signal that will be set. For instance, passing 2 into \e signal will
//! select PWM sync signal 2.
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_setPWMSyncSignal(uint32_t base, DAC_SyncSel signal)
{
    //
    // Set the PWM sync signal
    //
    EALLOW;
    ((DAC_REGS *)base)->DACCTL.bit.SYNCSEL = signal;

    EDIS;
}

//*****************************************************************************
//
//! Get the DAC Active Output Value
//!
//! \param base is the DAC module base address
//!
//! This function gets the DAC active output value.
//!
//! \return Returns the DAC active output value.
//
//*****************************************************************************
static inline uint16_t DAC_getActiveValue(uint32_t base)
{
    //
    // Get the active value
    //
    return (((DAC_REGS *)base)->DACVALA.bit.DACVALA);
}

//*****************************************************************************
//
//! Set the DAC Shadow Output Value
//!
//! \param base is the DAC module base address
//! \param value is the 12-bit code to be loaded into the active value register
//!
//! This function sets the DAC shadow output value.
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_setShadowValue(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(value <= 0xFFFU);

    //
    // Set the shadow value
    //
    ((DAC_REGS *)base)->DACVALS.bit.DACVALS = value;
}

//*****************************************************************************
//
//! Get the DAC Shadow Output Value
//!
//! \param base is the DAC module base address
//!
//! This function gets the DAC shadow output value.
//!
//! \return Returns the DAC shadow output value.
//
//*****************************************************************************
static inline uint16_t DAC_getShadowValue(uint32_t base)
{
    //
    // Get the shadow value
    //
    return (((DAC_REGS *)base)->DACVALS.bit.DACVALS);
}

//*****************************************************************************
//
//! Enable the DAC Output
//!
//! \param base is the DAC module base address
//!
//! This function enables the DAC output.
//!
//! \note A delay is required after enabling the DAC. Further details
//! regarding the exact delay time length can be found in the device datasheet.
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_enableOutput(uint32_t base)
{
    //
    // Enable the output
    //
    EALLOW;

    ((DAC_REGS *)base)->DACOUTEN.bit.DACOUTEN = 1;

    EDIS;
}
//*****************************************************************************
//
//! Disable the DAC Output
//!
//! \param base is the DAC module base address
//!
//! This function disables the DAC output.
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_disableOutput(uint32_t base)
{
    //
    // Enable the output
    //
    EALLOW;

    ((DAC_REGS *)base)->DACOUTEN.bit.DACOUTEN = 0;

    EDIS;
}

//*****************************************************************************
//
//! Set DAC Offset Trim
//!
//! \param base is the DAC module base address
//! \param offset is the specified value for the offset trim
//!
//! This function sets the DAC offset trim. The \e offset value should be a
//! signed number in the range of -128 to 127.
//!
//! \note The offset should not be modified unless specifically indicated by
//! TI Errata or other documentation. Modifying the offset value could cause
//! this module to operate outside of the datasheet specifications.
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_setOffsetTrim(uint32_t base, int16_t offset)
{
    //
    // Check the arguments.
    //
    ASSERT((offset > -129) && (offset < 128));

    //
    // Set the offset trim value
    //
    EALLOW;

    ((DAC_REGS *)base)->DACTRIM.bit.OFFSET_TRIM = offset;

    EDIS;
}

//*****************************************************************************
//
//! Get DAC Offset Trim
//!
//! \param base is the DAC module base address
//!
//! This function gets the DAC offset trim value.
//!
//! \return None.
//
//*****************************************************************************
static inline int16_t DAC_getOffsetTrim(uint32_t base)
{
    uint16_t value;

    //
    // Get the sign-extended offset trim value
    //
    value = ((DAC_REGS *)base)->DACTRIM.bit.OFFSET_TRIM;
    value = (value ^ (uint16_t)0x80) - (uint16_t)0x80;

    return ((int16_t)value);
}

//*****************************************************************************
//
//! Lock write-access to DAC Register
//!
//! \param base is the DAC module base address
//! \param reg is the selected DAC registers
//!
//! This function locks the write-access to the specified DAC register. Only a
//! system reset can unlock the register once locked.
//!
//! The \e reg parameter can be an ORed combination of any of the following
//!
//! \return None.
//
//*****************************************************************************
static inline void DAC_lockRegister(uint32_t base, uint16_t reg)
{
    //
    // Check the arguments.
    //
    ASSERT((reg & ~(0x7U)) == 0U);

    //
    // Lock the specified registers
    //
    EALLOW;

    ((DAC_REGS *)base)->DACLOCK.all = (0xA000U | reg)

        EDIS;
}

//*****************************************************************************
//
//! Check if DAC Register is locked
//!
//! \param base is the DAC module base address
//! \param reg is the selected DAC register locks to check
//!
//! This function checks if write-access has been locked on the specified DAC
//! register.
//!
//! The \e reg parameter can be an ORed combination of any of the following
//!
//! \return Returns \b true if any of the registers specified are locked, and
//! \b false if all specified registers aren't locked.
//
//*****************************************************************************
static inline bool DAC_isRegisterLocked(uint32_t base, uint16_t reg)
{
    //
    // Check the arguments.
    //
    ASSERT((reg & ~(0x7U)) == 0U);

    //
    // Return the lock status on the specified registers
    //
    return ((bool)(((((DAC_REGS *)base)->DACLOCK.all) & reg) != 0U));
}

//*****************************************************************************
//
//! Tune DAC Offset Trim
//!
//! \param base is the DAC module base address
//! \param referenceVoltage is the reference voltage the DAC
//! module is operating at.
//!
//! This function adjusts/tunes the DAC offset trim. The \e referenceVoltage
//! value should be a floating point number in the range specified in the
//! device data manual.
//!
//! \note Use this function to adjust the DAC offset trim if operating
//! at a reference voltage other than 2.5v. Since this function modifies
//! the DAC offset trim register, it should only be called once after
//! Device_cal. If it is called multiple times after Device_cal, the offset
//! value scaled would be the wrong value.
//!
//! \return None.
//
//*****************************************************************************
extern void DAC_tuneOffsetTrim(uint32_t base, float32_t referenceVoltage);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // DAC_H
