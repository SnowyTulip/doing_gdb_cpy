/**
 **************************************************************************
 * @file     qx_eqep.c
 * @version  v1.0.0
 * @date     2023-12-30
 **************************************************************************
 */

#include "devicelib.h"

//*****************************************************************************
// GPIO_writePin
//*****************************************************************************
void GPIO_writePin(uint32_t pin, uint32_t outVal)
{
    ASSERT(GPIO_isPinValid(pin));

    vu32 *gpioBaseAddr = (vu32 *)(GPIODATA_BASE + ((pin / 32U) * 0x10));

    if (outVal) // GPxSET
        gpioBaseAddr[1] = (uint32_t)1U << (pin % 32U);
    else // GPxCLEAR
        gpioBaseAddr[2] = (uint32_t)1U << (pin % 32U);
}

//*****************************************************************************
// GPIO_setDirectionMode
//*****************************************************************************
void GPIO_setDirectionMode(uint32_t pin, GPIO_Direction pinDir)
{
    ASSERT(GPIO_isPinValid(pin));

    vu32 *gpioBaseAddr = (vu32 *)(GPIOCTRL_BASE + ((pin / 32U) * 0x50));

    EALLOW;
    if (pinDir == GPIO_DIR_MODE_OUT) // GPxDIR
        gpioBaseAddr[5] |= (uint32_t)1U << (pin % 32U);
    else
        gpioBaseAddr[5] &= ~((uint32_t)1U << (pin % 32U));
    EDIS;
}

//*****************************************************************************
// GPIO_setInterruptPin
//*****************************************************************************
void GPIO_setInterruptPin(uint32_t pin, GPIO_ExternalIntNum extIntNum)
{
    ASSERT(GPIO_isPinValid(pin));

    XBAR_InputNum input;
    // Pick the X-BAR input that corresponds to the requested XINT.
    switch (extIntNum)
    {
        case GPIO_INT_XINT1:
            input = XBAR_INPUT4;
            break;
        case GPIO_INT_XINT2:
            input = XBAR_INPUT5;
            break;
        case GPIO_INT_XINT3:
            input = XBAR_INPUT6;
            break;
        case GPIO_INT_XINT4:
            input = XBAR_INPUT13;
            break;
        case GPIO_INT_XINT5:
            input = XBAR_INPUT14;
            break;
        default:
            // Invalid interrupt. Shouldn't happen if enum value is used.
            // XBAR_INPUT1 isn't tied to an XINT, so we'll use it to check for
            // a bad value.
            input = XBAR_INPUT1;
            break;
    }

    if (input != XBAR_INPUT1)
        XBAR_setInputPin(input, (uint16_t)pin);
}

//*****************************************************************************
// GPIO_setPadConfig
//*****************************************************************************
void GPIO_setPadConfig(uint32_t pin, GPIO_PinType pinType)
{
    volatile uint32_t *gpioBaseAddr;
    uint32_t pinMask;

    ASSERT(GPIO_isPinValid(pin));

    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE + ((pin / 32U) * 0x50);
    pinMask      = (uint32_t)1U << (pin % 32U);

    EALLOW;
    // Enable pull-up if necessary (GPxPUD)
    if (pinType & GPIO_PIN_TYPE_PULLUP)
        gpioBaseAddr[6] &= ~pinMask;
    else
        gpioBaseAddr[6] |= pinMask;

    // Invert polarity if necessary (GPxINV)
    if (pinType & GPIO_PIN_TYPE_INVERT)
        gpioBaseAddr[8] |= pinMask;
    else
        gpioBaseAddr[8] &= ~pinMask;

    // Enable open drain if necessary (GPxODR)
    if (pinType & GPIO_PIN_TYPE_OD)
        gpioBaseAddr[9] |= pinMask;
    else
        gpioBaseAddr[9] &= ~pinMask;
    EDIS;
}

//*****************************************************************************
// GPIO_getPadConfig
//*****************************************************************************
uint32_t GPIO_getPadConfig(uint32_t pin)
{
    volatile uint32_t *gpioBaseAddr;
    uint32_t pinMask;
    uint32_t pinTypeRes;

    ASSERT(GPIO_isPinValid(pin));

    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE + ((pin / 32U) * 0x50);
    pinMask      = (uint32_t)1U << (pin % 32U);

    pinTypeRes = GPIO_PIN_TYPE_STD;

    // Get pull-up disable value
    if ((gpioBaseAddr[6] & pinMask) != 0U)
        pinTypeRes |= GPIO_PIN_TYPE_PULLUP;

    // Get polarity value
    if ((gpioBaseAddr[8] & pinMask) != 0U)
        pinTypeRes |= GPIO_PIN_TYPE_INVERT;

    // Get open drain value
    if ((gpioBaseAddr[9] & pinMask) != 0U)
        pinTypeRes |= GPIO_PIN_TYPE_OD;

    return (pinTypeRes);
}

//*****************************************************************************
// GPIO_setQualificationMode
//*****************************************************************************
void GPIO_setQualificationMode(uint32_t pin, GPIO_QualificationMode qualification)
{
    volatile uint32_t *gpioBaseAddr;
    uint32_t qSelIndex;
    uint32_t shiftAmt;

    ASSERT(GPIO_isPinValid(pin));

    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE + ((pin / 32U) * 0x50);
    shiftAmt     = 2 * (pin % 16U);
    qSelIndex    = 1 + ((pin % 32U) / 16U); /* GPxSEL1 or GPxSEL2 */

    EALLOW;
    // Write the input qualification mode to the register.
    gpioBaseAddr[qSelIndex] &= ~(0x3 << shiftAmt);
    gpioBaseAddr[qSelIndex] |= (uint32_t)qualification << shiftAmt;
    EDIS;
}

//*****************************************************************************
// GPIO_getQualificationMode
//*****************************************************************************
GPIO_QualificationMode GPIO_getQualificationMode(uint32_t pin)
{
    volatile uint32_t *gpioBaseAddr;
    uint32_t qSelIndex;
    uint32_t qualRes;
    uint32_t shiftAmt;

    ASSERT(GPIO_isPinValid(pin));

    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE + ((pin / 32U) * 0x50);
    shiftAmt     = (uint32_t)2 * (pin % 16U);
    qSelIndex    = 1 + ((pin % 32U) / 16U); /* GPxSEL1 or GPxSEL2 */

    //
    // Read the qualification mode register and shift and mask to get the
    // value for the specified pin.
    //
    qualRes = (gpioBaseAddr[qSelIndex] >> shiftAmt) & (uint32_t)0x3;
    return ((GPIO_QualificationMode)qualRes);
}

//*****************************************************************************
// GPIO_setQualificationPeriod
//*****************************************************************************
void GPIO_setQualificationPeriod(uint32_t pin, uint32_t divider)
{
    volatile uint32_t *gpioBaseAddr;
    uint32_t pinMask, regVal, shiftAmt;

    ASSERT(GPIO_isPinValid(pin));

    shiftAmt = (pin % 32U) & ~((uint32_t)0x7U);
    pinMask  = (uint32_t)0xFFU << shiftAmt;

    //
    // Divide divider by two to get the value that needs to go into the field.
    // Then shift it into the right place.
    //
    regVal = (divider / 2U) << shiftAmt;

    //
    // Write the divider parameter into the register.
    //
    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE + ((pin / 32U) * 0x50);

    EALLOW;
    gpioBaseAddr[0] &= ~pinMask; // GPxCTRL
    gpioBaseAddr[0] |= regVal;
    EDIS;
}

//*****************************************************************************
// GPIO_setControllerCore
//*****************************************************************************
void GPIO_setControllerCore(uint32_t pin, GPIO_CoreSelect core)
{
    //    volatile uint32_t *gpioBaseAddr;
    //    uint32_t cSelIndex;
    //    uint32_t shiftAmt;
    //
    //    ASSERT(GPIO_isPinValid(pin));
    //
    //    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE + ((pin / 32U) * 0x50);
    //    shiftAmt     = (uint32_t)1 * (pin % 8U);
    //    cSelIndex    = 1 + ((pin % 32U) / 8U);
    //
    //    //
    //    // Write the core parameter into the register.
    //    //
    //    EALLOW;
    //    gpioBaseAddr[cSelIndex] &= ~((uint32_t)1 << shiftAmt);
    //    gpioBaseAddr[cSelIndex] |= (uint32_t)core << shiftAmt;
    //    EDIS;
}

//*****************************************************************************
// GPIO_setAnalogMode
//*****************************************************************************
void GPIO_setAnalogMode(uint32_t pin, GPIO_AnalogMode mode)
{
    volatile uint32_t *gpioBaseAddr;
    uint32_t pinMask;

    /* ASSERT(((pin >= 224U) && (pin <= 247U)) || (pin == 22U) || (pin == 23U)); */

    pinMask      = (uint32_t)1U << (pin % 32U);
    gpioBaseAddr = (uint32_t *)GPIOCTRL_BASE + ((pin / 32U) * 0x50);

    EALLOW;
    if (mode == GPIO_ANALOG_ENABLED)
        gpioBaseAddr[8] |= pinMask;
    else
        gpioBaseAddr[8] &= ~pinMask;
    EDIS;
}

//*****************************************************************************
// GPIO_setPinConfig
//*****************************************************************************
void GPIO_setPinConfig(GPIO_PinMux pinMux)
{
    uint32_t muxRegAddr;
    uint32_t pinMask, shiftAmt;

    ASSERT(GPIO_isPinValid(pin));

    muxRegAddr = (uint32_t)GPIOCTRL_BASE + (pinMux >> 16);
    shiftAmt   = ((pinMux >> 8) & (uint32_t)0xFFU);
    pinMask    = (uint32_t)0x3U << shiftAmt;

    EALLOW;
    // Clear fields in MUX register first to avoid glitches
    HWREG(muxRegAddr) &= ~pinMask;

    // Write value into GMUX register(GPxGMUX1 - GPxMUX1 = 0x1c)
    HWREG(muxRegAddr + 0x1C) = (HWREG(muxRegAddr + 0x1C) & ~pinMask) | (((pinMux >> 2) & (uint32_t)0x3U) << shiftAmt);

    // Write value into MUX register
    HWREG(muxRegAddr) |= ((pinMux & (uint32_t)0x3U) << shiftAmt);
    EDIS;
}

//*****************************************************************************
// Configures the all essential function of a GPIO pin.
//*****************************************************************************
void GPIO_Config(uint32_t pin, GPIO_PinMux mux, GPIO_Direction dir, GPIO_PinType type, GPIO_QualificationMode qual)
{
    GPIO_setPinConfig(mux);
    GPIO_setDirectionMode(pin, dir);
    GPIO_setPadConfig(pin, type);
    /* output mode no need config qualification */
    if (dir == GPIO_DIR_MODE_IN)
        GPIO_setQualificationMode(pin, qual);
}
