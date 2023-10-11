#include "devicelib.h"

//*****************************************************************************
//
// ADC_setVREF
//
//*****************************************************************************
void ADC_setVREF(uint32_t base, ADC_ReferenceMode refMode, ADC_ReferenceVoltage refVoltage)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    uint16_t moduleShiftVal;

    //
    // Assign a shift amount corresponding to which ADC module is being
    // configured.
    //
    switch (base)
    {
        case ADCA_REGS_BASE:
            moduleShiftVal = 1U;
            break;
        case ADCB_REGS_BASE:
            moduleShiftVal = 0U;
            break;
        case ADCC_REGS_BASE:
            moduleShiftVal = 0U;
            break;
        default:
            //
            // Invalid base address!!
            //
            moduleShiftVal = 0U;
            break;
    }

    EALLOW;
    //
    // Configure the reference mode (internal or external).
    //

    if (refMode == ADC_REFERENCE_INTERNAL)
    {
        if (base == ADCA_REGS_BASE)
        {
            AnalogSubsysRegs->ANAREFCTL.bit.EN_HIZ_A    = 0;
            AnalogSubsysRegs->ANAREFCTL.bit.EN_VREFBI_A = 1;
        }
        else
        {
            AnalogSubsysRegs->ANAREFCTL.bit.EN_HIZ_BC    = 0;
            AnalogSubsysRegs->ANAREFCTL.bit.EN_VREFBI_BC = 1;
        }
    }
    else
    {
        if (base == ADCA_REGS_BASE)
        {
            AnalogSubsysRegs->ANAREFCTL.bit.EN_HIZ_A    = 1;
            AnalogSubsysRegs->ANAREFCTL.bit.EN_VREFBI_A = 0;
        }
        else
        {
            AnalogSubsysRegs->ANAREFCTL.bit.EN_HIZ_BC    = 1;
            AnalogSubsysRegs->ANAREFCTL.bit.EN_VREFBI_BC = 0;
        }
    }

    //
    // Configure the reference voltage
    //
    if (moduleShiftVal)
        AnalogSubsysRegs->ANAREFCTL.bit.SEL_VREFBIBI_A = refVoltage;
    else
        AnalogSubsysRegs->ANAREFCTL.bit.SEL_VREFBIBI_BC = refVoltage;
    EDIS;
}

//*****************************************************************************
//
// ADC_setPPBTripLimits
//
//*****************************************************************************
void ADC_setPPBTripLimits(uint32_t base, ADC_PPBNumber ppbNumber, int32_t tripHiLimit, int32_t tripLoLimit)
{
    uint32_t ppbHiOffset;
    uint32_t ppbLoOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT((tripHiLimit <= 65535) && (tripHiLimit >= -65536));
    ASSERT((tripLoLimit <= 65535) && (tripLoLimit >= -65536));

    //
    // Get the offset to the appropriate trip limit registers.
    //
    ppbHiOffset = 0x8cU + (int16_t)ppbNumber * 0x18U;
    ppbLoOffset = 0x90U + (int16_t)ppbNumber * 0x18U;

    EALLOW;

    //
    // Set the trip high limit.
    //
    ((union ADCPPB1TRIPHI_REG *)(base + ppbHiOffset))->all = tripHiLimit;

    //
    // Set the trip low limit.
    //
    ((union ADCPPB1TRIPLO_REG *)(base + ppbLoOffset))->all = tripLoLimit;

    EDIS;
}
