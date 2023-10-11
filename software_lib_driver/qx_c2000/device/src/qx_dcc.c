/**
 **************************************************************************
 * @file     qx_dcc.c
 * @version  v1.0.0
 * @date     2023-05-18
 **************************************************************************
 */

#include "devicelib.h"

//*****************************************************************************
// DCC_getRevisionNumber
//*****************************************************************************
uint16_t DCC_getRevisionNumber(uint32_t base, DCC_RevisionNumber identifier)
{
    uint16_t number;

    // Check the arguments.
    ASSERT(DCC_isBaseValid(base));

    //  Get specified revision number or scheme
    if (identifier == DCC_REVISION_MINOR)
    {
        number = (HWREGH(base + DCC_O_REV) & DCC_REV_MINOR_M);
    }
    else if (identifier == DCC_REVISION_MAJOR)
    {
        number = (HWREGH(base + DCC_O_REV) & DCC_REV_MAJOR_M) >> DCC_REV_MAJOR_S;
    }

    return (number);
}

//*****************************************************************************
//
// DCC_verifyClockFrequency
//
//*****************************************************************************
bool DCC_verifyClockFrequency(uint32_t base, DCC_Count1ClockSource clock1, float32_t freq1,
    DCC_Count0ClockSource clock0, float32_t freq0, float32_t tolerance, float32_t freqerr)
{
    float32_t total_error;
    float32_t window;
    uint32_t count0;
    uint32_t valid;
    uint32_t count1;
    bool status;

    if (freq1 > freq0)
    {
        // total_error = (2.0F + (2.0F * (freq_sysclk / freq0)));
        total_error = 2.0F;
    }
    else
    {
        total_error = 2.0F * (freq0 / freq1);
    }

    // Digitization error = 3 Clock0 cycles
    total_error += 3.0F;
    // Window (in Cycles) = (Total Error) / (0.01 * Tolerance)
    window = total_error / (0.01F * tolerance);

    // Error due to variance in clock frequency =
    // window * (Allowable Frequency Tolerance (in %) / 100)
    total_error += window * (freqerr / 100.0F);

    // DCC counter configuration :
    // Counter0 = Window - Total Error
    // Valid0 = 2 * Total Error
    // Counter1 = Window * (Fclk1 / Fclk0)
    count0 = window - total_error;
    valid  = 2U * (uint32_t)total_error;
    count1 = window * freq1 / freq0;

    // Clear Error & Done Flag
    // DCC_BASE->DCCGCTRL.bit.DCCENA =0x4;

    // DCC_BASE->DCCSTATUS.bit.ERR = 1;
    // DCC_BASE->DCCSTATUS.bit.DONE =1;
    // DCC_clearErrorFlag(base);
    // DCC_clearDoneFlag(base);

    // Disable DCC and the error and done signals
    DCC_disableModule();
    DCC_disableErrorSignal();
    DCC_disableDoneSignal();

    // Configure Clock Source0 and clock source1
    DCC_setCounter0ClkSource(base, clock0); // clock0����� PLLclk
    DCC_setCounter1ClkSource(base, clock1); // clock1 ���������ʱ��ѡ�� ��
    // Configure COUNTER-0, COUNTER-1 & Valid Window
    DCC_setCounterSeeds(base, count0, valid, count1);

    DCC_SetSingle_Shot(); //  0xa5aaΪ��SingleShotMode
    // Enable Single Shot mode
    DCC_enableSingleShotMode(DCC_MODE_COUNTER_ZERO);

    // Enable Error Signal and Done signal
    DCC_enableErrorSignal();
    DCC_enableDoneSignal();

    // Enable DCC to start counting
    DCC_enableModule();

    // Wait until Error or Done Flag is generated
    while (!(DCC_getSingleShotStatus(base) || DCC_getErrorStatus(base)))
    { }

    // Returns true if DCC completes without error
    if (DCC_getSingleShotStatus(base))
        status = true;
    else
        status = false;

    return (status);
}

//*****************************************************************************
// DCC_measureClockFrequency
//*****************************************************************************
float32_t DCC_measureClockFrequency(uint32_t base, DCC_Count1ClockSource clock1, DCC_Count0ClockSource clock0,
    float32_t freq0, float32_t tolerance, float32_t freqerr, float32_t freq_sysclk)
{
    float32_t total_error;
    float32_t window;
    uint32_t count0;
    uint32_t valid;
    uint32_t count1;
    uint32_t actual_cnt1;
    float32_t freq1;

    // Check the arguments.
    ASSERT(DCC_isBaseValid(base));

    // Async. Error = 2 + 2*(Fsysclk/Fclk0)
    // Digitization error = 8 Clock0 cycles
    // Total DCC error = Async Error + Digitization error
    total_error = (2.0F + (2.0F * (freq_sysclk / freq0)));
    total_error += 8.0F;

    // Window (in Cycles) = (Total Error) / (0.01 * Tolerance)
    window = total_error / (0.01F * tolerance);

    // Error due to variance in clock frequency =
    // window * (Allowable Frequency Tolerance (in %) / 100)
    total_error += window * (freqerr / 100.0F);

    // DCC counter configuration :
    // Counter0 = Window - Total Error
    // Valid0 = 2 * Total Error
    // Counter1 = Maximum counter value (0xFFFFF)
    count0 = window - total_error;
    valid  = 2U * (uint32_t)total_error;
    count1 = 0xFFFFFU;

    // Clear Error & Done Flag
    DCC_clearErrorInterupt();
    DCC_clearDoneInterupt();

    // Disable DCC and the error and done signals
    DCC_disableModule();
    DCC_disableErrorSignal();
    DCC_disableDoneSignal();

    // Configure Clock Source0 and clock source1
    DCC_setCounter0ClkSource(base, clock0);
    DCC_setCounter1ClkSource(base, clock1);

    // Configure COUNTER-0, COUNTER-1 & Valid Window
    DCC_setCounterSeeds(base, count0, valid, count1);

    // Enable Single Shot mode
    DCC_enableSingleShotMode(DCC_MODE_COUNTER_ZERO);

    // Enable Error Signal and Done signal
    DCC_enableErrorSignal();
    DCC_enableDoneSignal();

    // Enable DCC to start counting
    DCC_enableModule();

    // Wait until Error or Done Flag is generated
    while (!(DCC_getSingleShotStatus(base) || DCC_getErrorStatus(base)))
    { }

    // Calculate the difference of the current counter
    // values with the initial fed counter values. This
    // will give the counts corresponding to the frequency
    // of each clock source
    actual_cnt1 = count1 - DCC_getCounter1Value();

    // Compute the frequency using relation F1 = (F0 * Actual C1)/Window.
    freq1 = (freq0 * (float32_t)actual_cnt1) / ((float32_t)count0 + (float32_t)valid);

    return (freq1);
}

//*****************************************************************************
// DCC_continuousMonitor
//*****************************************************************************
void DCC_continuousMonitor(uint32_t base, DCC_Count1ClockSource clock1, float32_t freq1, DCC_Count0ClockSource clock0,
    float32_t freq0, float32_t tolerance, float32_t freqerr, float32_t freq_sysclk)
{
    float32_t total_error;
    float32_t window;
    uint32_t count0;
    uint32_t valid;
    uint32_t count1;

    // Check the arguments.
    ASSERT(DCC_isBaseValid(base));

    // If Fclk1 > Fclk0,
    //     Async. Error (In Clock0 cycles) = 2 + 2*(Fsysclk/Fclk0)
    // If Fclk1 < Fclk0,
    //     Async. Error (In Clock0 cycles) = 2*(Fclk0/Fclk1) + 2*(Fsysclk/Fclk0)
    if (freq1 > freq0)
    {
        total_error = (2.0F + (2.0F * (freq_sysclk / freq0)));
    }
    else
    {
        total_error = ((2.0F * (freq0 / freq1)) + (2.0F * (freq_sysclk / freq0)));
    }

    // Digitization error = 8 Clock0 cycles
    total_error += 8.0F;

    // Window (in Cycles) = (Total Error) / (0.01 * Tolerance)
    window = total_error / (0.01F * tolerance);

    // Error due to variance in clock frequency =
    // window * (Allowable Frequency Tolerance (in %) / 100)
    total_error += window * (freqerr / 100.0F);

    // DCC counter configuration :
    // Counter0 = Window - Total     Error
    // Valid0 = 2 * Total Error
    // Counter1 = Window * (Fclk1 / Fclk0)
    count0 = window - total_error;
    valid  = 2U * (uint32_t)total_error;
    count1 = window * freq1 / freq0;

    // Clear Error & Done Flag
    DCC_clearErrorInterupt();
    DCC_clearDoneInterupt();

    // Disable DCC and the error and done signals
    DCC_disableModule();
    DCC_disableErrorSignal();
    DCC_disableDoneSignal();

    // Configure Clock Source0 and clock source1
    DCC_setCounter0ClkSource(base, clock0);
    DCC_setCounter1ClkSource(base, clock1);

    // Configure COUNTER-0, COUNTER-1 & Valid Window
    DCC_setCounterSeeds(base, count0, valid, count1);
    // Enable Continuous mode
    DCC_disableSingleShotMode();
    // Enable Error Signal
    DCC_enableErrorSignal();
    // Enable DCC to start counting
    DCC_enableModule();
}
