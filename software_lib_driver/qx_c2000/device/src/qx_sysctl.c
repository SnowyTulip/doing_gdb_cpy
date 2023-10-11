/**
 **************************************************************************
 * @file     qx_sysctl.c
 * @version  v1.0.0
 * @date     2023-05-18
 * @brief    contains all the functions for the sysctrl firmware library
 **************************************************************************
 */

#include "devicelib.h"

//
// Define to isolate inline assembly
//
// #define SYSCTL_DELAY                                   \
//     __asm(" .if __TI_EABI__\n"                         \
//           " .asg    SysCtl_delay    , _SysCtl_delay\n" \
//           " .endif\n"                                  \
//           " .def _SysCtl_delay\n"                      \
//           " .sect \".TI.ramfunc\"\n"                   \
//           " .global  _SysCtl_delay\n"                  \
//           "_SysCtl_delay:\n"                           \
//           " SUB    ACC,#1\n"                           \
//           " BF     _SysCtl_delay, GEQ\n"               \
//           " LRETR\n")

//
// Macro used for adding delay between 2 consecutive writes to CLKSRCCTL1
// register.
// Delay = 300 NOPs
//
#define SYSCTL_CLKSRCCTL1_DELAY SysCtl_delay(250);

//*****************************************************************************
// SysCtl_getClock()
//*****************************************************************************
uint32_t SysCtl_getClock(uint32_t clockInHz)
{
    uint32_t temp;
    uint32_t oscSource;
    uint32_t clockOut;

    if (SysCtl_isMCDClockFailureDetected())
        clockOut = SYSCTL_DEFAULT_OSC_FREQ;
    else
    {
        oscSource = ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL;
        if (oscSource == 0 || oscSource == 2)
            clockOut = SYSCTL_DEFAULT_OSC_FREQ;
        else
            clockOut = clockInHz;
        if (ClkCfgRegs->SYSPLLCTL1.bit.PLLCLKEN == 1 && ClkCfgRegs->SYSPLLCTL1.bit.PLLEN == 1)
        {
            temp = ClkCfgRegs->SYSPLLMULT.bit.FMULT;
            clockOut *= ClkCfgRegs->SYSPLLMULT.bit.IMULT;
            if (temp != 0U)
                clockOut /= temp;
            temp = ClkCfgRegs->SYSPLLMULT.bit.ODDIV;
            clockOut /= temp;
        }
        temp = ClkCfgRegs->SYSCLKDIVSEL.bit.PLLSYSCLKDIV;
        if (temp != 0U)
            clockOut /= (2U * ClkCfgRegs->SYSCLKDIVSEL.bit.PLLSYSCLKDIV);
    }

    return (clockOut);
}

//*****************************************************************************
// SysCtl_setClock()
//*****************************************************************************
uint32_t SysCtl_setClock(uint32_t config)
{
    uint16_t divSel, pllLockStatus;
    uint32_t retries, oscSource, timeout;
    uint32_t status = false;

    // Don't proceed to the PLL initialization if an MCD failure is detected.
    // OSCCLKSRC2 failure detected. Returning false. You'll need to clear the MCD error.
    if (SysCtl_isMCDClockFailureDetected())
        status = false;
    else
    {
        // Configure oscillator source Bypass PLL
        ClkCfgRegs->SYSPLLCTL1.bit.PLLCLKEN = 0;

        oscSource = config & SYSCTL_OSCSRC_M;
        SysCtl_selectOscSource(oscSource);

        // Configure PLL if enabled
        if ((config & SYSCTL_PLL_ENABLE) == SYSCTL_PLL_ENABLE)
        {
            ClkCfgRegs->SYSPLLCTL1.bit.PLLEN = 1; // Turn off PLL

            for (retries = 0U; (retries < SYSCTL_PLL_RETRIES); retries++)
            {
                ClkCfgRegs->SYSPLLMULT.bit.RST = 0; // enter reset mode
                ClkCfgRegs->SYSPLLMULT.all     = config & 0xFFFFFU;
                ClkCfgRegs->SYSPLLMULT.bit.RST = 1; // enter normal mode
                // Wait for the SYSPLL lock counter or a timeout
                timeout       = SYSCTL_PLLLOCK_TIMEOUT;
                pllLockStatus = ClkCfgRegs->SYSPLLSTS.bit.LOCKS;
                while ((pllLockStatus != 1U) && (timeout != 0U))
                {
                    pllLockStatus = ClkCfgRegs->SYSPLLSTS.bit.LOCKS;
                    timeout--;
                }

                // Check PLL Frequency using DCC
                /* status = SysCtl_isPLLValid(oscSource, (config & (SYSCTL_IMULT_M | SYSCTL_FMULT_M | SYSCTL_ODIV_M)));
                 */
                status = true;
                // Check DCC Status, if no error break the loop
                if (status)
                    break;
            }
        }
        else
            status = true;

        // If PLL locked successfully, configure the dividers
        if (status)
        {
            ClkCfgRegs->SYSPLLCTL1.bit.PLLCLKEN       = 1; // Enable PLLSYSCLK is fed from system PLL clock
            ClkCfgRegs->SYSCLKDIVSEL.bit.PLLSYSCLKDIV = (config & SYSCTL_SYSDIV_M) >> SYSCTL_SYSDIV_S;
        }
    }

    return (status);
}

//*****************************************************************************
// SysCtl_selectXTAL()
//*****************************************************************************
void SysCtl_selectXTAL(void)
{
    EALLOW;
    // Turn on XTAL and select crystal mode
    ClkCfgRegs->XTALCR.bit.OSCOFF = 0;
    ClkCfgRegs->XTALCR.bit.SE     = 0;
    EDIS;

    // Wait for the X1 clock readly
    while (1)
    {
        if (ClkCfgRegs->CLKSTATUS.bit.X1READLY)
            break;
    }

    while (1) // Wait for the X1 stable
    {
        if (ClkCfgRegs->X1CNT.all == 0x3ff)
            break;
    }

    // Select XTAL as the oscillator source
    EALLOW;
    ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 1;
    EDIS;

    // If a missing clock failure was detected, try waiting for the X1 counter
    // to saturate again. Consider modifying this code to add a 10ms timeout.
    while (SysCtl_isMCDClockFailureDetected())
    {
        SysCtl_resetMCD(); // Clear the MCD failure
        // Select XTAL as the oscillator source
        EALLOW;
        ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 1;
        EDIS;
    }
}

//*****************************************************************************
// SysCtl_selectXTALSingleEnded()
//*****************************************************************************
void SysCtl_selectXTALSingleEnded(void)
{
    EALLOW;
    // Turn on XTAL and select single-ended mode.
    ClkCfgRegs->XTALCR.bit.OSCOFF = 0;
    ClkCfgRegs->XTALCR.bit.SE     = 1;
    EDIS;

    // Wait for the X1 clock readly
    while (1)
    {
        if (ClkCfgRegs->CLKSTATUS.bit.X1READLY)
            break;
    }

    // Select XTAL as the oscillator source
    EALLOW;
    ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 1;
    EDIS;

    // Something is wrong with the oscillator module. Replace the ESTOP0 with
    // an appropriate error-handling routine.
    while (SysCtl_isMCDClockFailureDetected())
    {
        // ESTOP0;
    }
}

//*****************************************************************************
// SysCtl_selectOscSource()
//*****************************************************************************
void SysCtl_selectOscSource(uint32_t oscSource)
{
    EALLOW;
    switch (oscSource)
    {
        case SYSCTL_OSCSRC_OSC2:
            ClkCfgRegs->CLKSRCCTL1.bit.INTOSC2OFF   = 0; // Turn on INTOSC2
            ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 0; // Clk Src = INTOSC2
            break;
        case SYSCTL_OSCSRC_XTAL:
            SysCtl_selectXTAL(); // Select XTAL in crystal mode and wait for it to power up
            break;
        case SYSCTL_OSCSRC_XTAL_SE:
            SysCtl_selectXTALSingleEnded(); // Select XTAL in single-ended mode and wait for it to power up
            break;
        case SYSCTL_OSCSRC_OSC1:
            ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 2; // Clk Src = INTOSC1
            break;
        default:
            // Do nothing. Not a valid oscSource value.
            break;
    }
    EDIS;
}

//*****************************************************************************
// SysCtl_getLowSpeedClock()
//*****************************************************************************
uint32_t SysCtl_getLowSpeedClock(uint32_t clockInHz)
{
    uint32_t clockOut;
    clockOut = SysCtl_getClock(clockInHz); // Get the main system clock
    if (ClkCfgRegs->LOSPCP.bit.LSPCLKDIV != 0U)
        clockOut /= (2U * ClkCfgRegs->LOSPCP.bit.LSPCLKDIV);
    return (clockOut);
}

//*****************************************************************************
// SysCtl_isPLLValid()
//*****************************************************************************
uint32_t SysCtl_isPLLValid(uint32_t oscSource, uint32_t pllMultDiv)
{
    uint32_t imult, fmult, odiv, base;

    DCC_Count0ClockSource dccClkSrc0;
    DCC_Count1ClockSource dccClkSrc1;
    uint32_t dccCounterSeed0, dccCounterSeed1, dccValidSeed0;

    switch (oscSource)
    {
        case SYSCTL_OSCSRC_OSC2:
            // Select DCC Clk Src0 as INTOSC2
            dccClkSrc0 = DCC_COUNT0SRC_INTOSC2;
            break;
        case SYSCTL_OSCSRC_XTAL:
        case SYSCTL_OSCSRC_XTAL_SE:
            // Select DCC Clk Src0 as XTAL
            dccClkSrc0 = DCC_COUNT0SRC_XTAL;
            break;
        case SYSCTL_OSCSRC_OSC1:
            // Select DCC Clk Src0 as INTOSC1
            dccClkSrc0 = DCC_COUNT0SRC_INTOSC1;
            break;
        default:
            // Select DCC Clk Src0 as INTOSC1
            dccClkSrc0 = DCC_COUNT0SRC_INTOSC1;
            break;
    }

    // Setting Counter0 & Valid Seed Value with +/-12% tolerance
    dccCounterSeed0 = (uint32_t)SYSCTL_DCC_COUNTER0_WINDOW - 12U;
    dccValidSeed0   = 24U;

    // Select DCC0 for PLL validation
    base = DCC0_BASE;

    // Select DCC Clk Src1 as SYSPLL
    dccClkSrc1 = DCC_COUNT1SRC_PLL;

    imult = pllMultDiv & SYSCTL_IMULT_M;
    fmult = pllMultDiv & SYSCTL_FMULT_M;
    odiv  = (pllMultDiv & SYSCTL_ODIV_M) >> SYSCTL_ODIV_S;

    // Multiplying Counter-0 window with PLL Integer Multiplier
    dccCounterSeed1 = SYSCTL_DCC_COUNTER0_WINDOW * imult / (odiv + 1U);

    // Multiplying Counter-0 window with PLL Fractional Multiplier
    switch (fmult)
    {
        /* case SYSCTL_FMULT_1_4:
            // FMULT * CNTR0 Window = 0.25 * 100 = 25, gets added to cntr0
            // seed value
            dccCounterSeed1 = dccCounterSeed1 + 25U;
            break;
        case SYSCTL_FMULT_1_2:
            // FMULT * CNTR0 Window = 0.5 * 100 = 50, gets added to cntr0
            // seed value
            dccCounterSeed1 = dccCounterSeed1 + 50U;
            break;
        case SYSCTL_FMULT_3_4:
            // FMULT * CNTR0 Window = 0.75 * 100 = 75, gets added to cntr0
            // seed value
            dccCounterSeed1 = dccCounterSeed1 + 75U;
            break;
        default:
            // No fractional multiplier
            dccCounterSeed1 = dccCounterSeed1;
            break; */
    }

    // Enable peripheral clock to DCC
    // SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCC0);

    // Clear Error & Done Flag
    DCC_clearErrorInterupt();
    DCC_clearDoneInterupt();
    DCC_disableModule();      // Disable DCC
    DCC_disableErrorSignal(); // Disable Error Signal
    DCC_disableDoneSignal();  // Disable Done Signal
    // Configure Clock Source0 to whatever set as a clock source for PLL   DCC_setCounter0ClkSource(base, dccClkSrc0);
    // Configure Clock Source1 to PLL
    DCC_setCounter1ClkSource(base, dccClkSrc1);
    // Configure COUNTER-0, COUNTER-1 & Valid Window
    DCC_setCounterSeeds(base, dccCounterSeed0, dccValidSeed0, dccCounterSeed1);
    // Enable Single Shot mode
    DCC_enableSingleShotMode(DCC_MODE_COUNTER_ZERO);
    DCC_enableErrorSignal(); // Enable Error Signal
    DCC_enableDoneSignal();  // Enable Done Signal
    DCC_enableModule();      // Enable DCC to start counting
    // Timeout for the loop
    uint32_t timeout = dccCounterSeed1;
    // Wait until Error or Done Flag is generated
    while (((HWREGH(base + DCC_O_STATUS) & (DCC_STATUS_ERR | DCC_STATUS_DONE)) == 0U) && (timeout != 0U))
        timeout--;
    // Returns true if DCC completes without error
    return (((HWREGH(base + DCC_O_STATUS) & (DCC_STATUS_ERR | DCC_STATUS_DONE)) == DCC_STATUS_DONE)
            && (HWREGH(base + DCC_O_CNT0) == 0U) && (HWREGH(base + DCC_O_VALID0) == 0U)
            && (HWREGH(base + DCC_O_CNT1) == 0U));
}
