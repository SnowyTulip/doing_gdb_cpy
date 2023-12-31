/**
 **************************************************************************
 * @file     qx_cmpss.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_CMPSS_H
#define QX_CMPSS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"
#include "hw_cmpss.h"

//---------------------------------------------------------------------------
// CMPSS Individual Register Bit Definitions:

struct COMPCTL_BITS
{                          // bits description
    vu32 COMPHSOURCE  : 1; // 0 High Comparator Source Select
    vu32 COMPHINV     : 1; // 1 High Comparator Invert Select
    vu32 CTRIPHSEL    : 2; // 3:2 High Comparator Trip Select
    vu32 CTRIPOUTHSEL : 2; // 5:4 High Comparator Trip Output Select
    vu32 ASYNCHEN     : 1; // 6 High Comparator Asynchronous Path Enable
    vu32 rsvd1        : 1; // 7 Reserved
    vu32 COMPLSOURCE  : 1; // 8 Low Comparator Source Select
    vu32 COMPLINV     : 1; // 9 Low Comparator Invert Select
    vu32 CTRIPLSEL    : 2; // 11:10 Low Comparator Trip Select
    vu32 CTRIPOUTLSEL : 2; // 13:12 Low Comparator Trip Output Select
    vu32 ASYNCLEN     : 1; // 14 Low Comparator Asynchronous Path Enable
    vu32 COMPDACE     : 1; // 15 Comparator/DAC Enable
};

union COMPCTL_REG
{
    vu32 all;
    struct COMPCTL_BITS bit;
};

struct COMPSTS_BITS
{                        // bits description
    vu32 COMPHSTS   : 1; // 0 High Comparator Status
    vu32 COMPHLATCH : 1; // 1 High Comparator Latched Status
    vu32 rsvd1      : 6; // 7:2 Reserved
    vu32 COMPLSTS   : 1; // 8 Low Comparator Status
    vu32 COMPLLATCH : 1; // 9 Low Comparator Latched Status
};

union COMPSTS_REG
{
    vu32 all;
    struct COMPSTS_BITS bit;
};

struct COMPSTSCLR_BITS
{                        // bits description
    vu32 rsvd1      : 1; // 0 Reserved
    vu32 HLATCHCLR  : 1; // 1 High Comparator Latched Status Clear
    vu32 HSYNCCLREN : 1; // 2 High Comparator EPWMSYNCPER Clear Enable
    vu32 rsvd2      : 6; // 8:3 Reserved
    vu32 LLATCHCLR  : 1; // 9 Low Comparator Latched Status Clear
    vu32 LSYNCCLREN : 1; // 10 Low Comparator EPWMSYNCPER Clear Enable
};

union COMPSTSCLR_REG
{
    vu32 all;
    struct COMPSTSCLR_BITS bit;
};

struct COMPDACCTL_BITS
{                         // bits description
    vu32 DACSOURCE   : 1; // 0 DAC Source Control
    vu32 RAMPSOURCE  : 4; // 4:1 Ramp Generator Source Control
    vu32 SELREF      : 1; // 5 DAC Reference Select
    vu32 RAMPLOADSEL : 1; // 6 Ramp Load Select
    vu32 SWLOADSEL   : 1; // 7 Software Load Select
    vu32 BLANKSOURCE : 4; // 11:8 EPWMBLANK Source Select
    vu32 BLANKEN     : 1; // 12 EPWMBLANK Enable
    vu32 rsvd1       : 1; // 13 Reserved
    vu32 FREESOFT    : 2; // 15:14 Free/Soft Emulation Bits
};

union COMPDACCTL_REG
{
    vu32 all;
    struct COMPDACCTL_BITS bit;
};

struct DACHVALS_BITS
{                     // bits description
    vu32 DACVAL : 12; // 11:0 DAC Value Control
};

union DACHVALS_REG
{
    vu32 all;
    struct DACHVALS_BITS bit;
};

struct DACHVALA_BITS
{                     // bits description
    vu32 DACVAL : 12; // 11:0 DAC Value Control
};

union DACHVALA_REG
{
    vu32 all;
    struct DACHVALA_BITS bit;
};

struct DACLVALS_BITS
{                     // bits description
    vu32 DACVAL : 12; // 11:0 DAC Value Control
};

union DACLVALS_REG
{
    vu32 all;
    struct DACLVALS_BITS bit;
};

struct DACLVALA_BITS
{                     // bits description
    vu32 DACVAL : 12; // 11:0 DAC Value Control
};

union DACLVALA_REG
{
    vu32 all;
    struct DACLVALA_BITS bit;
};

struct RAMPDLYA_BITS
{                    // bits description
    vu32 DELAY : 13; // 12:0 Ramp Delay Value
};

union RAMPDLYA_REG
{
    vu32 all;
    struct RAMPDLYA_BITS bit;
};

struct RAMPDLYS_BITS
{                    // bits description
    vu32 DELAY : 13; // 12:0 Ramp Delay Value
};

union RAMPDLYS_REG
{
    vu32 all;
    struct RAMPDLYS_BITS bit;
};

struct CTRIPLFILCTL_BITS
{                     // bits description
    vu32 rsvd1   : 4; // 3:0 Reserved
    vu32 SAMPWIN : 5; // 8:4 Sample Window
    vu32 THRESH  : 5; // 13:9 Majority Voting Threshold
    vu32 rsvd2   : 1; // 14 Reserved
    vu32 FILINIT : 1; // 15 Filter Initialization Bit
};

union CTRIPLFILCTL_REG
{
    vu32 all;
    struct CTRIPLFILCTL_BITS bit;
};

struct CTRIPLFILCLKCTL_BITS
{                          // bits description
    vu32 CLKPRESCALE : 10; // 9:0 Sample Clock Prescale
};

union CTRIPLFILCLKCTL_REG
{
    vu32 all;
    struct CTRIPLFILCLKCTL_BITS bit;
};

struct CTRIPHFILCTL_BITS
{                     // bits description
    vu32 rsvd1   : 4; // 3:0 Reserved
    vu32 SAMPWIN : 5; // 8:4 Sample Window
    vu32 THRESH  : 5; // 13:9 Majority Voting Threshold
    vu32 rsvd2   : 1; // 14 Reserved
    vu32 FILINIT : 1; // 15 Filter Initialization Bit
};

union CTRIPHFILCTL_REG
{
    vu32 all;
    struct CTRIPHFILCTL_BITS bit;
};

struct CTRIPHFILCLKCTL_BITS
{                          // bits description
    vu32 CLKPRESCALE : 10; // 9:0 Sample Clock Prescale
};

union CTRIPHFILCLKCTL_REG
{
    vu32 all;
    struct CTRIPHFILCLKCTL_BITS bit;
};

struct COMPLOCK_BITS
{                        // bits description
    vu32 COMPCTL    : 1; // 0 COMPCTL Lock
    vu32 COMPHYSCTL : 1; // 1 COMPHYSCTL Lock
    vu32 DACCTL     : 1; // 2 DACCTL Lock
    vu32 CTRIP      : 1; // 3 CTRIP Lock
};

union COMPLOCK_REG
{
    vu32 all;
    struct COMPLOCK_BITS bit;
};

struct COMPDACHCTL_BITS
{                           // bits description
    vu32 COMPH_HYS     : 3; // 2:0
    vu32 DACH_MD       : 2; // 4:3
    vu32 DACH_PRESCALE : 8; // 12:5
};

union COMPDACHCTL_REG
{
    vu32 all;
    struct COMPDACHCTL_BITS bit;
};

struct COMPDACLCTL_BITS
{                           // bits description
    vu32 COMPH_HYS     : 3; // 2:0
    vu32 DACH_MD       : 2; // 4:3
    vu32 DACH_PRESCALE : 8; // 12:5
};

union COMPDACLCTL_REG
{
    vu32 all;
    struct COMPDACLCTL_BITS bit;
};

struct CMPSS_REGS
{
    union COMPCTL_REG COMPCTL;                 // CMPSS Comparator Control Register
    vu32  rsvd;                                // CMPSS  rsvd
    union COMPSTS_REG COMPSTS;                 // CMPSS Comparator Status Register
    union COMPSTSCLR_REG COMPSTSCLR;           // CMPSS Comparator Status Clear Register
    union COMPDACCTL_REG COMPDACCTL;           // CMPSS DAC Control Register
    union DACHVALS_REG DACHVALS;               // CMPSS High DAC Value Shadow Register
    union DACHVALA_REG DACHVALA;               // CMPSS High DAC Value Active Register
    vu32 RAMPMAXREFA;                          // CMPSS Ramp Max Reference Active Register
    vu32 RAMPMAXREFS;                          // CMPSS Ramp Max Reference Shadow Register
    vu32 RAMPDECVALA;                          // CMPSS Ramp Decrement Value Active Register
    vu32 RAMPDECVALS;                          // CMPSS Ramp Decrement Value Shadow Register
    vu32 RAMPSTS;                              // CMPSS Ramp Status Register
    union DACLVALS_REG DACLVALS;               // CMPSS Low DAC Value Shadow Register
    union DACLVALA_REG DACLVALA;               // CMPSS Low DAC Value Active Register
    union RAMPDLYA_REG RAMPDLYA;               // CMPSS Ramp Delay Active Register
    union RAMPDLYS_REG RAMPDLYS;               // CMPSS Ramp Delay Shadow Register
    union CTRIPLFILCTL_REG CTRIPLFILCTL;       // CTRIPL Filter Control Register
    union CTRIPLFILCLKCTL_REG CTRIPLFILCLKCTL; // CTRIPL Filter Clock Control Register
    union CTRIPHFILCTL_REG CTRIPHFILCTL;       // CTRIPH Filter Control Register
    union CTRIPHFILCLKCTL_REG CTRIPHFILCLKCTL; // CTRIPH Filter Clock Control Register
    union COMPLOCK_REG COMPLOCK;               // CMPSS Lock Register
    union COMPDACHCTL_REG COMPDACHCTL;
    union COMPDACLCTL_REG COMPDACLCTL;
};

#define Cmpss1Regs ((CMPSS_REGS *)(CMPSS_BASE + 0x000))
#define Cmpss2Regs ((CMPSS_REGS *)(CMPSS_BASE + 0x100))
#define Cmpss3Regs ((CMPSS_REGS *)(CMPSS_BASE + 0x200))
#define Cmpss4Regs ((CMPSS_REGS *)(CMPSS_BASE + 0x300))
#define Cmpss5Regs ((CMPSS_REGS *)(CMPSS_BASE + 0x400))
#define Cmpss6Regs ((CMPSS_REGS *)(CMPSS_BASE + 0x500))
#define Cmpss7Regs ((CMPSS_REGS *)(CMPSS_BASE + 0x600))

//*****************************************************************************
//
//! \addtogroup cmpss_api CMPSS
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Useful defines used within the driver functions. Not intended for use by
// application code.
//
//*****************************************************************************
#define CMPSS_HICMP_CTL_M (CMPSS_COMPCTL_COMPHSOURCE | CMPSS_COMPCTL_COMPHINV | CMPSS_COMPCTL_ASYNCHEN)

#define CMPSS_LOCMP_CTL_M (CMPSS_COMPCTL_COMPLSOURCE | CMPSS_COMPCTL_COMPLINV | CMPSS_COMPCTL_ASYNCLEN)

#ifndef DOXYGEN_PDF_IGNORE
//*****************************************************************************
//
// Values that can be passed to CMPSS_configLowComparator() and
// CMPSS_configHighComparator() as the config parameter.
//
//*****************************************************************************
//
// Comparator negative input source
//
//! Input driven by internal DAC
#define CMPSS_INSRC_DAC 0x0000U
//! Input driven by external pin
#define CMPSS_INSRC_PIN 0x0001U

//
// Extra options
//
//! Comparator output is inverted
#define CMPSS_INV_INVERTED 0x0002U
//! Asynch comparator output feeds into OR with latched digital filter output
#define CMPSS_OR_ASYNC_OUT_W_FILT 0x0040U

//*****************************************************************************
//
// Values that can be passed to CMPSS_configOutputsLow() and
// CMPSS_configOutputsHigh() as the config parameter.
//
//*****************************************************************************
//
// Signal driving CTRIPOUT
//
//! Asynchronous comparator output drives CTRIPOUT
#define CMPSS_TRIPOUT_ASYNC_COMP 0x0000U
//! Synchronous comparator output drives CTRIPOUT
#define CMPSS_TRIPOUT_SYNC_COMP 0x0010U
//! Filter output drives CTRIPOUT
#define CMPSS_TRIPOUT_FILTER 0x0020U
//! Latched filter output drives CTRIPOUT
#define CMPSS_TRIPOUT_LATCH 0x0030U

//
// Signal driving CTRIP
//
//! Asynchronous comparator output drives CTRIP
#define CMPSS_TRIP_ASYNC_COMP 0x0000U
//! Synchronous comparator output drives CTRIP
#define CMPSS_TRIP_SYNC_COMP 0x0004U
//! Filter output drives CTRIP
#define CMPSS_TRIP_FILTER 0x0008U
//! Latched filter output drives CTRIP
#define CMPSS_TRIP_LATCH 0x000CU

//*****************************************************************************
//
// Values that can be returned by CMPSS_getStatus().
//
//*****************************************************************************
//! High digital filter output
#define CMPSS_STS_HI_FILTOUT 0x0001U
//! Latched value of high digital filter output
#define CMPSS_STS_HI_LATCHFILTOUT 0x0002U
//! Low digital filter output
#define CMPSS_STS_LO_FILTOUT 0x0100U
//! Latched value of low digital filter output
#define CMPSS_STS_LO_LATCHFILTOUT 0x0200U

//*****************************************************************************
//
// Values that can be passed to CMPSS_configDAC() the config parameter.
//
//*****************************************************************************
//
// When is DAC value loaded from shadow register
//
//! DAC value updated from SYSCLK
#define CMPSS_DACVAL_SYSCLK 0x0000U
//! DAC value updated from PWMSYNC
#define CMPSS_DACVAL_PWMSYNC 0x0080U

//
// DAC reference voltage
//
//! VDDA is the voltage reference
#define CMPSS_DACREF_VDDA 0x0000U
//! VDAC is the voltage reference
#define CMPSS_DACREF_VDAC 0x0020U

//
// DAC value source
//
//! DAC value updated from shadow register
#define CMPSS_DACSRC_SHDW 0x0000U
//! DAC value is updated from the ramp register
#define CMPSS_DACSRC_RAMP 0x0001U
#endif

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks the CMPSS base address.
//!
//! \param base is the base address of the CMPSS module.
//!
//! This function determines if a CMPSS base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool CMPSS_isBaseValid(uint32_t base)
{
    return ((base == CMPSS1_BASE) || (base == CMPSS2_BASE) || (base == CMPSS3_BASE) || (base == CMPSS4_BASE)
            || (base == CMPSS5_BASE) || (base == CMPSS6_BASE) || (base == CMPSS7_BASE));
}
#endif

//*****************************************************************************
//
//! Enables the CMPSS module.
//!
//! \param base is the base address of the CMPSS module.
//!
//! This function enables the CMPSS module passed into the \e base parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_enableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Set the bit that enables the CMPSS module.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPCTL) |= CMPSS_COMPCTL_COMPDACE;

    EDIS;
}

//*****************************************************************************
//
//! Disables the CMPSS module.
//!
//! \param base is the base address of the CMPSS module.
//!
//! This function disables the CMPSS module passed into the \e base parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_disableModule(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Clear the bit that enables the CMPSS module.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPCTL) &= ~CMPSS_COMPCTL_COMPDACE;

    EDIS;
}

//*****************************************************************************
//
//! Sets the configuration for the high comparator.
//!
//! \param base is the base address of the CMPSS module.
//! \param config is the configuration of the high comparator.
//!
//! This function configures a comparator.  The \e config parameter is the
//! result of a logical OR operation between a \b CMPSS_INSRC_xxx value and if
//! desired, \b CMPSS_INV_INVERTED and \b CMPSS_OR_ASYNC_OUT_W_FILT values.
//!
//! The \b CMPSS_INSRC_xxx term can take on the following values to specify
//! the high comparator negative input source:
//! - \b CMPSS_INSRC_DAC - The internal DAC.
//! - \b CMPSS_INSRC_PIN - An external pin.
//!
//! \b CMPSS_INV_INVERTED may be ORed into \e config if the comparator output
//! should be inverted.
//!
//! \b CMPSS_OR_ASYNC_OUT_W_FILT may be ORed into \e config if the
//! asynchronous comparator output should be fed into an OR gate with the
//! latched digital filter output before it is made available for CTRIPH or
//! CTRIPOUTH.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_configHighComparator(uint32_t base, uint16_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the high comparator configuration to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPCTL) = (HWREGH(base + CMPSS_O_COMPCTL) & ~CMPSS_HICMP_CTL_M) | config;

    EDIS;
}

//*****************************************************************************
//
//! Sets the configuration for the low comparator.
//!
//! \param base is the base address of the CMPSS module.
//! \param config is the configuration of the low comparator.
//!
//! This function configures a comparator.  The \e config parameter is the
//! result of a logical OR operation between a \b CMPSS_INSRC_xxx value and if
//! desired, \b CMPSS_INV_INVERTED and \b CMPSS_OR_ASYNC_OUT_W_FILT values.
//!
//! The \b CMPSS_INSRC_xxx term can take on the following values to specify
//! the low comparator negative input source:
//! - \b CMPSS_INSRC_DAC - The internal DAC.
//! - \b CMPSS_INSRC_PIN - An external pin.
//!
//! \b CMPSS_INV_INVERTED may be ORed into \e config if the comparator output
//! should be inverted.
//!
//! \b CMPSS_OR_ASYNC_OUT_W_FILT may be ORed into \e config if the
//! asynchronous comparator output should be fed into an OR gate with the
//! latched digital filter output before it is made available for CTRIPL or
//! CTRIPOUTL.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_configLowComparator(uint32_t base, uint16_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the low comparator configuration to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPCTL) = (HWREGH(base + CMPSS_O_COMPCTL) & ~CMPSS_LOCMP_CTL_M) | (config << 8U);

    EDIS;
}

//*****************************************************************************
//
//! Sets the output signal configuration for the high comparator.
//!
//! \param base is the base address of the CMPSS module.
//! \param config is the configuration of the high comparator output signals.
//!
//! This function configures a comparator's output signals CTRIP and CTRIPOUT.
//! The \e config parameter is the result of a logical OR operation between the
//! \b CMPSS_TRIPOUT_xxx and \b CMPSS_TRIP_xxx values.
//!
//! The \b CMPSS_TRIPOUT_xxx term can take on the following values to specify
//! which signal drives CTRIPOUTH:
//! - \b CMPSS_TRIPOUT_ASYNC_COMP - The asynchronous comparator output.
//! - \b CMPSS_TRIPOUT_SYNC_COMP - The synchronous comparator output.
//! - \b CMPSS_TRIPOUT_FILTER - The output of the digital filter.
//! - \b CMPSS_TRIPOUT_LATCH - The latched output of the digital filter.
//!
//! The \b CMPSS_TRIP_xxx term can take on the following values to specify
//! which signal drives CTRIPH:
//! - \b CMPSS_TRIP_ASYNC_COMP - The asynchronous comparator output.
//! - \b CMPSS_TRIP_SYNC_COMP - The synchronous comparator output.
//! - \b CMPSS_TRIP_FILTER - The output of the digital filter.
//! - \b CMPSS_TRIP_LATCH - The latched output of the digital filter.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_configOutputsHigh(uint32_t base, uint16_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the high comparator output settings to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPCTL)
        = (HWREGH(base + CMPSS_O_COMPCTL) & ~(CMPSS_COMPCTL_CTRIPOUTHSEL_M | CMPSS_COMPCTL_CTRIPHSEL_M)) | config;

    EDIS;
}

//*****************************************************************************
//
//! Sets the output signal configuration for the low comparator.
//!
//! \param base is the base address of the CMPSS module.
//! \param config is the configuration of the low comparator output signals.
//!
//! This function configures a comparator's output signals CTRIP and CTRIPOUT.
//! The \e config parameter is the result of a logical OR operation between the
//! \b CMPSS_TRIPOUT_xxx and \b CMPSS_TRIP_xxx values.
//!
//! The \b CMPSS_TRIPOUT_xxx term can take on the following values to specify
//! which signal drives CTRIPOUTL:
//! - \b CMPSS_TRIPOUT_ASYNC_COMP - The asynchronous comparator output.
//! - \b CMPSS_TRIPOUT_SYNC_COMP - The synchronous comparator output.
//! - \b CMPSS_TRIPOUT_FILTER - The output of the digital filter.
//! - \b CMPSS_TRIPOUT_LATCH - The latched output of the digital filter.
//!
//! The \b CMPSS_TRIP_xxx term can take on the following values to specify
//! which signal drives CTRIPL:
//! - \b CMPSS_TRIP_ASYNC_COMP - The asynchronous comparator output.
//! - \b CMPSS_TRIP_SYNC_COMP - The synchronous comparator output.
//! - \b CMPSS_TRIP_FILTER - The output of the digital filter.
//! - \b CMPSS_TRIP_LATCH - The latched output of the digital filter.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_configOutputsLow(uint32_t base, uint16_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the low comparator output settings to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPCTL)
        = (HWREGH(base + CMPSS_O_COMPCTL) & ~(CMPSS_COMPCTL_CTRIPOUTLSEL_M | CMPSS_COMPCTL_CTRIPLSEL_M))
          | (config << 8U);

    EDIS;
}

//*****************************************************************************
//
//! Gets the current comparator status.
//!
//! \param base is the base address of the comparator module.
//!
//! This function returns the current status for the comparator, specifically
//! the digital filter output and latched digital filter output.
//!
//! \return Returns the current interrupt status, enumerated as a bit field of
//! the following values:
//! - \b CMPSS_STS_HI_FILTOUT - High digital filter output
//! - \b CMPSS_STS_HI_LATCHFILTOUT - Latched value of high digital filter
//!   output
//! - \b CMPSS_STS_LO_FILTOUT - Low digital filter output
//! - \b CMPSS_STS_LO_LATCHFILTOUT - Latched value of low digital filter output
//
//*****************************************************************************
static inline uint16_t CMPSS_getStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Return contents of the status register.
    //
    return (HWREGH(base + CMPSS_O_COMPSTS));
}

//*****************************************************************************
//
//! Sets the configuration for the internal comparator DACs.
//!
//! \param base is the base address of the CMPSS module.
//! \param config is the configuration of the internal DAC.
//!
//! This function configures the comparator's internal DAC.  The \e config
//! parameter is the result of a logical OR operation between the
//! \b CMPSS_DACVAL_xxx, \b CMPSS_DACREF_xxx, and \b CMPSS_DACSRC_xxx.
//!
//! The \b CMPSS_DACVAL_xxx term can take on the following values to specify
//! when the DAC value is loaded from its shadow register:
//! - \b CMPSS_DACVAL_SYSCLK - Value register updated on system clock.
//! - \b CMPSS_DACVAL_PWMSYNC - Value register updated on PWM sync.
//!
//! The \b CMPSS_DACREF_xxx term can take on the following values to specify
//! which voltage supply is used as reference for the DACs:
//! - \b CMPSS_DACREF_VDDA - VDDA is the voltage reference for the DAC.
//! - \b CMPSS_DACREF_VDAC - VDAC is the voltage reference for the DAC.
//!
//! The \b CMPSS_DACSRC_xxx term can take on the following values to specify
//! the DAC value source for the high comparator's internal DAC:
//! - \b CMPSS_DACSRC_SHDW - The user-programmed DACVALS register.
//! - \b CMPSS_DACSRC_RAMP - The ramp generator RAMPSTS register
//!
//! \note The \b CMPSS_DACVAL_xxx and \b CMPSS_DACREF_xxx terms apply to
//! both the high and low comparators. \b CMPSS_DACSRC_xxx will only affect
//! the high comparator's internal DAC.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_configDAC(uint32_t base, uint16_t config)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the DAC configuration to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPDACCTL)
        = (HWREGH(base + CMPSS_O_COMPDACCTL)
              & ~(CMPSS_COMPDACCTL_SWLOADSEL | CMPSS_COMPDACCTL_SELREF | CMPSS_COMPDACCTL_DACSOURCE))
          | config;

    EDIS;
}

//*****************************************************************************
//
//! Sets the value of the internal DAC of the high comparator.
//!
//! \param base is the base address of the comparator module.
//! \param value is the value actively driven by the DAC.
//!
//! This function sets the 12-bit value driven by the internal DAC of the high
//! comparator. This function will load the value into the shadow register from
//! which the actual DAC value register will be loaded. To configure which
//! event causes this shadow load to take place, use CMPSS_configDAC().
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_setDACValueHigh(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(value < 4096U);

    //
    // Write the DAC value to the DAC value shadow register.
    //
    HWREGH(base + CMPSS_O_DACHVALS) = value;
}

//*****************************************************************************
//
//! Sets the value of the internal DAC of the low comparator.
//!
//! \param base is the base address of the comparator module.
//! \param value is the value actively driven by the DAC.
//!
//! This function sets the 12-bit value driven by the internal DAC of the low
//! comparator. This function will load the value into the shadow register from
//! which the actual DAC value register will be loaded. To configure which
//! event causes this shadow load to take place, use CMPSS_configDAC().
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_setDACValueLow(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(value < 4096U);

    //
    // Write the DAC value to the DAC value shadow register.
    //
    HWREGH(base + CMPSS_O_DACLVALS) = value;
}

//*****************************************************************************
//
//! Initializes the digital filter of the high comparator.
//!
//! \param base is the base address of the comparator module.
//!
//! This function initializes all the samples in the high comparator digital
//! filter to the filter input value.
//!
//! \note See CMPSS_configFilterHigh() for the proper initialization sequence
//! to avoid glitches.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_initFilterHigh(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Set the high comparator filter initialization bit.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_CTRIPHFILCTL) |= CMPSS_CTRIPHFILCTL_FILINIT;

    EDIS;
}

//*****************************************************************************
//
//! Initializes the digital filter of the low comparator.
//!
//! \param base is the base address of the comparator module.
//!
//! This function initializes all the samples in the low comparator digital
//! filter to the filter input value.
//!
//! \note See CMPSS_configFilterLow() for the proper initialization sequence
//! to avoid glitches.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_initFilterLow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Set the low comparator filter initialization bit.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_CTRIPLFILCTL) |= CMPSS_CTRIPLFILCTL_FILINIT;

    EDIS;
}

//*****************************************************************************
//
//! Gets the value of the internal DAC of the high comparator.
//!
//! \param base is the base address of the comparator module.
//!
//! This function gets the value of the internal DAC of the high comparator.
//! The value is read from the \e active register--not the shadow register to
//! which CMPSS_setDACValueHigh() writes.
//!
//! \return Returns the value driven by the internal DAC of the high comparator.
//
//*****************************************************************************
static inline uint16_t CMPSS_getDACValueHigh(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the DAC value to the DAC value shadow register.
    //
    return (HWREGH(base + CMPSS_O_DACHVALA));
}

//*****************************************************************************
//
//! Gets the value of the internal DAC of the low comparator.
//!
//! \param base is the base address of the comparator module.
//!
//! This function gets the value of the internal DAC of the low comparator.
//! The value is read from the \e active register--not the shadow register to
//! which CMPSS_setDACValueLow() writes.
//!
//! \return Returns the value driven by the internal DAC of the low comparator.
//
//*****************************************************************************
static inline uint16_t CMPSS_getDACValueLow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the DAC value to the DAC value shadow register.
    //
    return (HWREGH(base + CMPSS_O_DACLVALA));
}

//*****************************************************************************
//
//! Causes a software reset of the high comparator digital filter output latch.
//!
//! \param base is the base address of the comparator module.
//!
//! This function causes a software reset of the high comparator digital filter
//! output latch. It will generate a single pulse of the latch reset signal.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_clearFilterLatchHigh(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Set the bit that generates a reset pulse to the digital filter latch.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPSTSCLR) |= CMPSS_COMPSTSCLR_HLATCHCLR;

    EDIS;
}

//*****************************************************************************
//
//! Causes a software reset of the low comparator digital filter output latch.
//!
//! \param base is the base address of the comparator module.
//!
//! This function causes a software reset of the low comparator digital filter
//! output latch. It will generate a single pulse of the latch reset signal.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_clearFilterLatchLow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Set the bit that generates a reset pulse to the digital filter latch.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPSTSCLR) |= CMPSS_COMPSTSCLR_LLATCHCLR;

    EDIS;
}

//*****************************************************************************
//
//! Sets the ramp generator maximum reference value.
//!
//! \param base is the base address of the comparator module.
//! \param value the ramp maximum reference value.
//!
//! This function sets the ramp maximum reference value that will be loaded
//! into the ramp generator.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_setMaxRampValue(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the maximum ramp value to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPMAXREFS) = value;
}

//*****************************************************************************
//
//! Gets the ramp generator maximum reference value.
//!
//! \param base is the base address of the comparator module.
//!
//! \return Returns the latched ramp maximum reference value that will be
//! loaded into the ramp generator.
//
//*****************************************************************************
static inline uint16_t CMPSS_getMaxRampValue(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Read the maximum ramp value from the register.
    //
    return (HWREGH(base + CMPSS_O_RAMPMAXREFA));
}

//*****************************************************************************
//
//! Sets the ramp generator decrement value.
//!
//! \param base is the base address of the comparator module.
//! \param value is the ramp decrement value.
//!
//! This function sets the value that is subtracted from the ramp value on
//! every system clock cycle.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_setRampDecValue(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Write the ramp decrement value to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPDECVALS) = value;
}

//*****************************************************************************
//
//! Gets the ramp generator decrement value.
//!
//! \param base is the base address of the comparator module.
//!
//! \return Returns the latched ramp decrement value that is subtracted from
//! the ramp value on every system clock cycle.
//
//*****************************************************************************
static inline uint16_t CMPSS_getRampDecValue(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Read the ramp decrement value from the register.
    //
    return (HWREGH(base + CMPSS_O_RAMPDECVALA));
}

//*****************************************************************************
//
//! Sets the ramp generator delay value.
//!
//! \param base is the base address of the comparator module.
//! \param value is the 13-bit ramp delay value.
//!
//! This function sets the value that configures the number of system clock
//! cycles to delay the start of the ramp generator decrementer after a PWMSYNC
//! event is received. Delay value can be no greater than 8191.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_setRampDelayValue(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(value < 8192U);

    //
    // Write the ramp delay value to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPDLYS) = value;
}

//*****************************************************************************
//
//! Gets the ramp generator delay value.
//!
//! \param base is the base address of the comparator module.
//!
//! \return Returns the latched ramp delay value that is subtracted from
//! the ramp value on every system clock cycle.
//
//*****************************************************************************
static inline uint16_t CMPSS_getRampDelayValue(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Read the ramp delay value from the register.
    //
    return (HWREGH(base + CMPSS_O_RAMPDLYA));
}

//*****************************************************************************
//
//! Sets the comparator hysteresis settings.
//!
//! \param base is the base address of the comparator module.
//! \param value is the amount of hysteresis on the comparator inputs.
//!
//! This function sets the amount of hysteresis on the comparator inputs. The
//! \e value parameter indicates the amount of hysteresis desired. Passing in 0
//! results in none, passing in 1 results in typical hysteresis, passing in 2
//! results in 2x of typical hysteresis, and so on where \e value x of typical
//! hysteresis is the amount configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_setHysteresis(uint32_t base, uint16_t value)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(value <= 4U);

    //
    // Read the ramp delay value from the register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPHYSCTL) = value;

    EDIS;
}

//*****************************************************************************
//
//! Enables reset of HIGH comparator digital filter output latch on PWMSYNC
//!
//! \param base is the base address of the comparator module.
//!
//! This function enables EPWMSYNCPER reset of High comparator digital filter
//! output latch
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_enableLatchResetOnPWMSYNCHigh(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    EALLOW;

    HWREGH(base + CMPSS_O_COMPSTSCLR) |= CMPSS_COMPSTSCLR_HSYNCCLREN;

    EDIS;
}

//*****************************************************************************
//
//! Disables reset of HIGH comparator digital filter output latch on PWMSYNC
//!
//! \param base is the base address of the comparator module.
//!
//! This function disables EPWMSYNCPER reset of High comparator digital filter
//! output latch
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_disableLatchResetOnPWMSYNCHigh(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    EALLOW;

    HWREGH(base + CMPSS_O_COMPSTSCLR) &= ~CMPSS_COMPSTSCLR_HSYNCCLREN;

    EDIS;
}

//*****************************************************************************
//
//! Enables reset of LOW comparator digital filter output latch on PWMSYNC
//!
//! \param base is the base address of the comparator module.
//!
//! This function enables EPWMSYNCPER reset of Low comparator digital filter
//! output latch
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_enableLatchResetOnPWMSYNCLow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    EALLOW;

    HWREGH(base + CMPSS_O_COMPSTSCLR) |= CMPSS_COMPSTSCLR_LSYNCCLREN;

    EDIS;
}

//*****************************************************************************
//
//! Disables reset of LOW comparator digital filter output latch on PWMSYNC
//!
//! \param base is the base address of the comparator module.
//!
//! This function disables EPWMSYNCPER reset of Low comparator digital filter
//! output latch
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_disableLatchResetOnPWMSYNCLow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    EALLOW;

    HWREGH(base + CMPSS_O_COMPSTSCLR) &= ~CMPSS_COMPSTSCLR_LSYNCCLREN;

    EDIS;
}

//*****************************************************************************
//
//! Sets the ePWM module blanking signal that holds trip in reset.
//!
//! \param base is the base address of the comparator module.
//! \param pwmBlankSrc is the number of the PWMBLANK source.
//!
//! This function configures which PWMBLANK signal from the ePWM module will
//! hold trip in reset when blanking is enabled.
//!
//! The number of the PWMBLANK signal to be used to reset the ramp generator
//! should be specified by passing it into the \e pwmBlankSrc parameter. For
//! instance, passing a 2 into \e pwmBlankSrc will select PWMBLANK2.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_configBlanking(uint32_t base, uint16_t pwmBlankSrc)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT((pwmBlankSrc >= 1U) && (pwmBlankSrc <= 16U));

    //
    // Write the blank source number to the appropriate register.
    //
    EALLOW;

    HWREGH(base + CMPSS_O_COMPDACCTL) = (HWREGH(base + CMPSS_O_COMPDACCTL) & ~CMPSS_COMPDACCTL_BLANKSOURCE_M)
                                        | ((pwmBlankSrc - 1U) << CMPSS_COMPDACCTL_BLANKSOURCE_S);

    EDIS;
}

//*****************************************************************************
//
//! Enables an ePWM blanking signal to hold trip in reset.
//!
//! \param base is the base address of the comparator module.
//!
//! This function enables a selected ePWM blanking signal to hold trip in
//! reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_enableBlanking(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Set the bit that enables the PWMBLANK signal.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACCTL) |= CMPSS_COMPDACCTL_BLANKEN;
    EDIS;
}

//*****************************************************************************
//
//! Disables an ePWM blanking signal from holding trip in reset.
//!
//! \param base is the base address of the comparator module.
//!
//! This function disables a selected ePWM blanking signal from holding trip in
//! reset.
//!
//! \return None.
//
//*****************************************************************************
static inline void CMPSS_disableBlanking(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // Clear the bit that enables the PWMBLANK signal.
    //
    EALLOW;
    HWREGH(base + CMPSS_O_COMPDACCTL) &= ~CMPSS_COMPDACCTL_BLANKEN;
    EDIS;
}

//*****************************************************************************
//
//! Configures the digital filter of the high comparator.
//!
//! \param base is the base address of the comparator module.
//! \param samplePrescale is the number of system clock cycles between samples.
//! \param sampleWindow is the number of FIFO samples to monitor.
//! \param threshold is the majority threshold of samples to change state.
//!
//! This function configures the operation of the digital filter of the high
//! comparator.
//!
//! The \e samplePrescale parameter specifies the number of system clock cycles
//! between samples. It is a 10-bit value so a number higher than 1023 should
//! not be passed as this parameter. The prescaler used by digital filter is 1
//! more than \e samplePrescale value. So, the input provided should be 1 less
//! than the expected prescaler.
//!
//! The \e sampleWindow parameter configures the size of the window of FIFO
//! samples taken from the input that will be monitored to determine when to
//! change the filter output. This sample window may be no larger than 32
//! samples.
//!
//! The \e threshold parameter configures the threshold value to be used by
//! the digital filter.
//!
//! The filter output resolves to the majority value of the sample window where
//! majority is defined by the value passed into the \e threshold parameter.
//! For proper operation, the value of \e threshold must be greater than
//! sampleWindow / 2.
//!
//! To ensure proper operation of the filter, the following is the recommended
//! function call sequence for initialization:
//!
//! -# Configure and enable the comparator using CMPSS_configHighComparator()
//!    and CMPSS_enableModule()
//! -# Configure the digital filter using CMPSS_configFilterHigh()
//! -# Initialize the sample values using CMPSS_initFilterHigh()
//! -# Configure the module output signals CTRIP and CTRIPOUT using
//!    CMPSS_configOutputsHigh()
//!
//! \return None.
//
//*****************************************************************************
extern void CMPSS_configFilterHigh(uint32_t base, uint16_t samplePrescale, uint16_t sampleWindow, uint16_t threshold);

//*****************************************************************************
//
//! Configures the digital filter of the low comparator.
//!
//! \param base is the base address of the comparator module.
//! \param samplePrescale is the number of system clock cycles between samples.
//! \param sampleWindow is the number of FIFO samples to monitor.
//! \param threshold is the majority threshold of samples to change state.
//!
//! This function configures the operation of the digital filter of the low
//! comparator.
//!
//! The \e samplePrescale parameter specifies the number of system clock cycles
//! between samples. It is a 10-bit value so a number higher than 1023 should
//! not be passed as this parameter. The prescaler used by digital filter is 1
//! more than \e samplePrescale value. So, the input provided should be 1 less
//! than the expected prescaler.
//!
//! The \e sampleWindow parameter configures the size of the window of FIFO
//! samples taken from the input that will be monitored to determine when to
//! change the filter output. This sample window may be no larger than 32
//! samples.
//!
//! The \e threshold parameter configures the threshold value to be used by
//! the digital filter.
//!
//! The filter output resolves to the majority value of the sample window where
//! majority is defined by the value passed into the \e threshold parameter.
//! For proper operation, the value of \e threshold must be greater than
//! sampleWindow / 2.
//!
//! To ensure proper operation of the filter, the following is the recommended
//! function call sequence for initialization:
//!
//! -# Configure and enable the comparator using CMPSS_configLowComparator()
//!    and CMPSS_enableModule()
//! -# Configure the digital filter using CMPSS_configFilterLow()
//! -# Initialize the sample values using CMPSS_initFilterLow()
//! -# Configure the module output signals CTRIP and CTRIPOUT using
//!    CMPSS_configOutputsLow()
//!
//! \return None.
//
//*****************************************************************************
extern void CMPSS_configFilterLow(uint32_t base, uint16_t samplePrescale, uint16_t sampleWindow, uint16_t threshold);

//*****************************************************************************
//
//! Configures whether or not the digital filter latches are reset by PWMSYNC
//!
//! \param base is the base address of the comparator module.
//! \param highEnable indicates filter latch settings in the high comparator.
//! \param lowEnable indicates filter latch settings in the low comparator.
//!
//! This function configures whether or not the digital filter latches in both
//! the high and low comparators should be reset by PWMSYNC. If the
//! \e highEnable parameter is \b true, the PWMSYNC will be allowed to reset
//! the high comparator's digital filter latch. If it is false, the ability of
//! the PWMSYNC to reset the latch will be disabled. The \e lowEnable parameter
//! has the same effect on the low comparator's digital filter latch.
//!
//! \return None.
//
//*****************************************************************************
extern void CMPSS_configLatchOnPWMSYNC(uint32_t base, bool highEnable, bool lowEnable);

//*****************************************************************************
//
//! Configures the comparator subsystem's ramp generator.
//!
//! \param base is the base address of the comparator module.
//! \param maxRampVal is the ramp maximum reference value.
//! \param decrementVal value is the ramp decrement value.
//! \param delayVal is the ramp delay value.
//! \param pwmSyncSrc is the number of the PWMSYNC source.
//! \param useRampValShdw indicates if the max ramp shadow should be used.
//!
//! This function configures many of the main settings of the comparator
//! subsystem's ramp generator. The \e maxRampVal parameter should be passed
//! the ramp maximum reference value that will be loaded into the ramp
//! generator. The \e decrementVal parameter should be passed the decrement
//! value that will be subtracted from the ramp generator on each system clock
//! cycle. The \e delayVal parameter should be passed the 13-bit number of
//! system clock cycles the ramp generator should delay before beginning to
//! decrement the ramp generator after a PWMSYNC signal is received.
//!
//! These three values may be be set individually using the
//! CMPSS_setMaxRampValue(), CMPSS_setRampDecValue(), and
//! CMPSS_setRampDelayValue() APIs.
//!
//! The number of the PWMSYNC signal to be used to reset the ramp generator
//! should be specified by passing it into the \e pwmSyncSrc parameter. For
//! instance, passing a 2 into \e pwmSyncSrc will select PWMSYNC2.
//!
//! To indicate whether the ramp generator should reset with the value from the
//! ramp max reference value shadow register or with the latched ramp max
//! reference value, use the \e useRampValShdw parameter. Passing it \b true
//! will result in the latched value being bypassed. The ramp generator will be
//! loaded right from the shadow register. A value of \b false will load the
//! ramp generator from the latched value.
//!
//! \return None.
//
//*****************************************************************************
extern void CMPSS_configRamp(uint32_t base, uint16_t maxRampVal, uint16_t decrementVal, uint16_t delayVal,
    uint16_t pwmSyncSrc, bool useRampValShdw);

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
