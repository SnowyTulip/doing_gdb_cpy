/**
 **************************************************************************
 * @file     qx_pga.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_PGA_H
#define QX_PGA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"

//---------------------------------------------------------------------------
// PGA Individual Register Bit Definitions:

struct PGACTL_BITS
{                         // bits description
    vu32 PGAEN      : 1;  // 0 PGA Enable
    vu32 FILTRESSEL : 4;  // 4:1 Filter Resistor Select
    vu32 GAIN       : 3;  // 7:5 PGA gain setting
    vu32 rsvd1      : 8;  // 15:8 Reserved
    vu32 rsvd2      : 16; // 31:16 Reserved
};

union PGACTL_REG
{
    vu32 all;
    struct PGACTL_BITS bit;
};

struct PGALOCK_BITS
{                           // bits description
    vu32 PGACTL        : 1; // 0 Lock bit for PGACTL.
    vu32 rsvd1         : 1; // 1 Reserved
    vu32 PGAGAIN3TRIM  : 1; // 2 Lock bit for PGAGAIN3TRIM.
    vu32 PGAGAIN6TRIM  : 1; // 3 Lock bit for PGAGAIN6TRIM.
    vu32 PGAGAIN12TRIM : 1; // 4 Lock bit for PGAGAIN12TRIM.
    vu32 PGAGAIN24TRIM : 1; // 5 Lock bit for PGAGAIN24TRIM.
    vu32 rsvd2         : 1; // 6 Reserved
    vu32 rsvd3         : 1; // 7 Reserved
    vu32 rsvd4         : 8; // 15:8 Reserved
};

union PGALOCK_REG
{
    vu32 all;
    struct PGALOCK_BITS bit;
};

struct PGAGAIN3TRIM_BITS
{                        // bits description
    vu32 GAINTRIM   : 8; // 7:0 Gain TRIM value, when gain setting is 3
    vu32 OFFSETTRIM : 8; // 15:8 OFFSET TRIM value, when Gain setting is 3
};

union PGAGAIN3TRIM_REG
{
    vu32 all;
    struct PGAGAIN3TRIM_BITS bit;
};

struct PGAGAIN6TRIM_BITS
{                        // bits description
    vu32 GAINTRIM   : 8; // 7:0 Gain TRIM value, when gain setting is 6
    vu32 OFFSETTRIM : 8; // 15:8 OFFSET TRIM value, when Gain setting is 6
};

union PGAGAIN6TRIM_REG
{
    vu32 all;
    struct PGAGAIN6TRIM_BITS bit;
};

struct PGAGAIN12TRIM_BITS
{                        // bits description
    vu32 GAINTRIM   : 8; // 7:0 Gain TRIM value, when gain setting is 12
    vu32 OFFSETTRIM : 8; // 15:8 OFFSET TRIM value, when Gain setting is 12
};

union PGAGAIN12TRIM_REG
{
    vu32 all;
    struct PGAGAIN12TRIM_BITS bit;
};

struct PGAGAIN24TRIM_BITS
{                        // bits description
    vu32 GAINTRIM   : 8; // 7:0 Gain TRIM value, when gain setting is 24
    vu32 OFFSETTRIM : 8; // 15:8 OFFSET TRIM value, when Gain setting is 24
};

union PGAGAIN24TRIM_REG
{
    vu32 all;
    struct PGAGAIN24TRIM_BITS bit;
};

struct PGATYPE_BITS
{                  // bits description
    vu32 REV  : 8; // 7:0 PGA Revision Field
    vu32 TYPE : 8; // 15:8 PGA Type Field
};

union PGATYPE_REG
{
    vu32 all;
    struct PGATYPE_BITS bit;
};

struct PGA_REGS
{
    union PGACTL_REG PGACTL;               // PGA Control Register
    union PGALOCK_REG PGALOCK;             // PGA Lock Register
    vu32 rsvd1;                            // Reserved
    union PGAGAIN3TRIM_REG PGAGAIN3TRIM;   // PGA Gain Trim Register for a gain setting of 3
    union PGAGAIN6TRIM_REG PGAGAIN6TRIM;   // PGA Gain Trim Register for a gain setting of 6
    union PGAGAIN12TRIM_REG PGAGAIN12TRIM; // PGA Gain Trim Register for a gain setting of 12
    union PGAGAIN24TRIM_REG PGAGAIN24TRIM; // PGA Gain Trim Register for a gain setting of 24
    union PGATYPE_REG PGATYPE;             // PGA Type Register
};

//---------------------------------------------------------------------------
// PGA External References & Function Declarations:
//
#define PGA1Regs ((struct PGA_REGS *)PGA1_BASE)
#define PGA2Regs ((struct PGA_REGS *)PGA2_BASE)
#define PGA3Regs ((struct PGA_REGS *)PGA3_BASE)
#define PGA4Regs ((struct PGA_REGS *)PGA4_BASE)
#define PGA5Regs ((struct PGA_REGS *)PGA5_BASE)
#define PGA6Regs ((struct PGA_REGS *)PGA6_BASE)
#define PGA7Regs ((struct PGA_REGS *)PGA7_BASE)

//*****************************************************************************
//
//! Values that can be passed to PGA_setGain() as the \e gainValue parameter.
//
//*****************************************************************************
typedef enum
{
    PGA_GAIN_3  = 0x0, //!< PGA gain value of 3
    PGA_GAIN_6  = 0x1, //!< PGA gain value of 6
    PGA_GAIN_12 = 0x2, //!< PGA gain value of 12
    PGA_GAIN_24 = 0x3  //!< PGA gain value of 24
} PGA_GainValue;

//*****************************************************************************
//
//! Values that can be passed to PGA_setFilterResistor() as the \e
//! resistorValue parameter.
//
//*****************************************************************************
typedef enum
{
    //! Low pass filter disabled (open circuit)
    PGA_LOW_PASS_FILTER_DISABLED         = 0, //! Resistor value of 200 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_200_OHM = 1, //! Resistor value of 160 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_160_OHM = 2, //! Resistor value of 130 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_130_OHM = 3, //! Resistor value of 100 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_100_OHM = 4, //! Resistor value of 80 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_80_OHM  = 5, //! Resistor value of 50 Ohm
    PGA_LOW_PASS_FILTER_RESISTOR_50_OHM  = 6
} PGA_LowPassResistorValue;

//*****************************************************************************
//
//! \internal
//! Checks PGA wrapper base address.
//!
//! \param base specifies the PGA wrapper base address.
//!
//! This function determines if a PGA wrapper base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool PGA_isBaseValid(uint32_t base)
{
    return ((base == PGA1_BASE) || (base == PGA2_BASE) || (base == PGA3_BASE) || (base == PGA4_BASE)
            || (base == PGA5_BASE) || (base == PGA6_BASE) || (base == PGA7_BASE));
}
#endif

//*****************************************************************************
//
//! Enables PGA.
//!
//! \param base is the base address of the PGA module.
//!
//! This function enables the PGA module.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_enable(uint32_t base)
{
    ASSERT(PGA_isBaseValid(base));
    ((struct PGA_REGS *)base)->PGACTL.bit.PGAEN = 1;
}

//*****************************************************************************
//
//! Disables PGA.
//!
//! \param base is the base address of the PGA module.
//!
//! This function disables the PGA module.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_disable(uint32_t base)
{
    ASSERT(PGA_isBaseValid(base));

    ((struct PGA_REGS *)base)->PGACTL.bit.PGAEN = 0;
}

//*****************************************************************************
//
//! Sets PGA gain value
//!
//! \param base is the base address of the PGA module.
//! \param gainValue is the PGA gain value.
//!
//! This function sets the PGA gain value.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_setGain(uint32_t base, PGA_GainValue gainValue)
{
    ASSERT(PGA_isBaseValid(base));

    ((struct PGA_REGS *)base)->PGACTL.bit.GAIN = gainValue;
}

//*****************************************************************************
//
//! Sets PGA output filter resistor value
//!
//! \param base is the base address of the PGA module.
//! \param resistorValue is the PGA output resistor value.
//!
//! This function sets the resistor value for the PGA output low pass RC
//! filter. The resistance for the RC low pass filter is provided within the
//! microprocessor and is determined by the value of resistorValue. The
//! capacitor, however, has to be connected outside the microprocessor.
//!
//! \b Note: Setting a value of PGA_LOW_PASS_FILTER_RESISTOR_0_OHM will
//!          disable the internal resistance value.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_setFilterResistor(uint32_t base, PGA_LowPassResistorValue resistorValue)
{
    ASSERT(PGA_isBaseValid(base));

    ((struct PGA_REGS *)base)->PGACTL.bit.FILTRESSEL = resistorValue;
}

//*****************************************************************************
//
//! Returns the PGA revision number.
//!
//! \param base is the base address of the PGA module.
//!
//! This function returns the PGA revision number.
//!
//! \return Returns PGA revision.
//
//*****************************************************************************
static inline uint16_t PGA_getPGARevision(uint32_t base)
{
    ASSERT(PGA_isBaseValid(base));

    return ((struct PGA_REGS *)base)->PGATYPE.bit.REV;
}

//*****************************************************************************
//
//! Returns the PGA Type.
//!
//! \param base is the base address of the PGA module.
//!
//! This function returns the PGA Type number.
//!
//! \return Returns PGA type.
//
//*****************************************************************************
static inline uint16_t PGA_getPGAType(uint32_t base)
{

    ASSERT(PGA_isBaseValid(base));

    return ((struct PGA_REGS *)base)->PGATYPE.bit.TYPE;
}

//*****************************************************************************
//
//! Locks PGA registers.
//!
//! \param base is the base address of the PGA module.
//! \param registerType is the PGA register to be locked.
//!
//! This function locks the PGA registers specified by registerType. Valid
//! values for registerType are:
//! PGA_REGISTER_PGACTL, PGA_REGISTER_GAINxTRIM, where x is
//! 3,6,12 or 24.
//!
//! \return None.
//
//*****************************************************************************
static inline void PGA_lockRegisters(uint32_t base, uint16_t registerType)
{

    ASSERT(PGA_isBaseValid(base));
    ASSERT((registerType < 0x3DU) && ((registerType & 0x2U) == 0U));

    ((struct PGA_REGS *)base)->PGALOCK.all = registerType;
}

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
