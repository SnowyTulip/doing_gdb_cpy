#include "common.h"

#ifdef TEST_HRCAP

#define HRCALCAL_STATUS_DONE_ISR    (HRCAP_CALIBRATION_DONE |                  \
                                     HRCAP_GLOBAL_CALIBRATION_INTERRUPT )

#define HRCALCAL_STATUS_DONE_PERIOD_OVERFLOW_ISR                               \
                                    (HRCAP_CALIBRATION_DONE |                  \
                                     HRCAP_GLOBAL_CALIBRATION_INTERRUPT |      \
                                     HRCAP_CALIBRATION_PERIOD_OVERFLOW)

#define HRCALCAL_CALIBRATION_FLAGS  (HRCAP_CALIBRATION_DONE |                  \
                                     HRCAP_CALIBRATION_PERIOD_OVERFLOW)

#define HRCAPCAL_OVERFLOW           4294967295.0f
#define HRCAPCAL_INV_OVERFLOW       (float32_t)(1.0f / HRCAPCAL_OVERFLOW)

// Typedefs
typedef struct
{
    uint32_t hrclkCount;    // High resolution clock count
    uint32_t sysclkcount;   // System clock count
    float32_t scaleFactor;  // Scale factor
    bool calDone;           // Calibration done flag
} HRCAPCAL_CalResultObj;

volatile uint32_t cap1Count;
volatile uint32_t cap2Count;
volatile uint32_t cap3Count;
volatile uint32_t cap4Count;

uint32_t absCountOn1, absCountOn2;
uint32_t absCountOff1, absCountOff2;
uint32_t absCountPeriod1, absCountPeriod2;

float32_t onTime1 = 0, onTime2 = 0;
float32_t offTime1 = 0, offTime2 = 0;
float32_t period1 = 0, period2 = 0;

uint32_t ecapIntCount;
uint16_t hrcapIntCount = 0;
uint16_t ecapIntCalCount = 0;
uint16_t calStatus = 0;

HRCAPCAL_CalResultObj hrcapCalResult;

uint32_t totalCount = 0;
float32_t inputFreqMHz = 0;

// eCAP ISR
__interrupt void ecap6_isr(void)
{
	puts("ECAP6 ISR");
#if 0
    ecapIntCalCount++;
    if(ecapIntCount++ > 10)
    {
        ecapIntCount = 0;

        // Get the raw time stamps
        cap1Count = ECAP_getEventTimeStamp(HRCAP1_BASE, ECAP_EVENT_1);
        cap2Count = ECAP_getEventTimeStamp(HRCAP1_BASE, ECAP_EVENT_2);
        cap3Count = ECAP_getEventTimeStamp(HRCAP1_BASE, ECAP_EVENT_3);
        cap4Count = ECAP_getEventTimeStamp(HRCAP1_BASE, ECAP_EVENT_4);

        absCountOn1 = cap2Count - cap1Count;
        absCountOff1 = cap3Count - cap2Count;
        absCountPeriod1 = cap3Count - cap1Count;

        absCountOn2 = cap4Count - cap3Count;
        absCountOff2 = cap3Count - cap2Count;
        absCountPeriod2 = cap4Count - cap2Count;

        // Convert counts to nanoseconds using the scale factor
        onTime1 = HRCAP_convertEventTimeStampNanoseconds(absCountOn1,
        		 hrcapCalResult.scaleFactor);
        offTime1 = HRCAP_convertEventTimeStampNanoseconds(absCountOff1,
        		 hrcapCalResult.scaleFactor);
        period1 = HRCAP_convertEventTimeStampNanoseconds(absCountPeriod1,
        		 hrcapCalResult.scaleFactor);

        onTime2 = HRCAP_convertEventTimeStampNanoseconds(absCountOn2,
        		 hrcapCalResult.scaleFactor);
        offTime2 = HRCAP_convertEventTimeStampNanoseconds(absCountOff2,
        		 hrcapCalResult.scaleFactor);
        period2 = HRCAP_convertEventTimeStampNanoseconds(absCountPeriod2,
        		 hrcapCalResult.scaleFactor);

        totalCount++;
    }

    ECAP_clearInterrupt(HRCAP1_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_4);
    ECAP_clearGlobalInterrupt(HRCAP1_BASE);
    ECAP_reArm(HRCAP1_BASE);
    ECAP_resetCounters(HRCAP1_BASE);
#endif
    ECAP_clearInterrupt(HRCAP1_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_4);
    ECAP_clearGlobalInterrupt(HRCAP1_BASE);
    // Acknowledge the PIE interrupt group
    //Interrupt_clearACKGroup(INT_myECAP0_INTERRUPT_ACK_GROUP);
}

// HRCAP Calibration ISR
__interrupt void ecap6_hrcal_isr(void)
{
	puts("HRCAP ISR");
    hrcapIntCount++;

    // Get calibration interrupt sources
    calStatus = HRCAP_getCalibrationFlags(HRCAP1_BASE + 0x40);

    // Get calibration clock counts
    hrcapCalResult.hrclkCount = HRCAP_getCalibrationClockPeriod(HRCAP1_BASE + 0x40,
    		 HRCAP_CALIBRATION_CLOCK_HRCLK);
    hrcapCalResult.sysclkcount = HRCAP_getCalibrationClockPeriod(HRCAP1_BASE + 0x40,
    		 HRCAP_CALIBRATION_CLOCK_SYSCLK);

    // The following options are possible
    //   - HRCALCAL_STATUS_DONE_ISR
    //   - HRCALCAL_STATUS_DONE_PERIOD_OVERFLOW_ISR
    //   - Software forced generated interrupt
    if(HRCALCAL_STATUS_DONE_ISR == calStatus)
    {
        // Calculate scale factor
        hrcapCalResult.scaleFactor = HRCAP_getScaleFactor(HRCAP1_BASE + 0x40);
    }
    else if (HRCALCAL_STATUS_DONE_PERIOD_OVERFLOW_ISR == calStatus)
    {
        // Calibration done with an overflow. Determine which counter has
        // overflowed
        if(hrcapCalResult.hrclkCount > hrcapCalResult.sysclkcount)
        {
            // HRCLK has overflowed
            hrcapCalResult.scaleFactor = hrcapCalResult.sysclkcount *
            		 HRCAPCAL_INV_OVERFLOW;
        }
        else if(hrcapCalResult.hrclkCount < hrcapCalResult.sysclkcount)
        {
            // SYSCLK has overflowed
            hrcapCalResult.scaleFactor = HRCAPCAL_OVERFLOW /
            		 hrcapCalResult.hrclkCount;
        }
        else
        {
            // Both SYSCLK and HRCLK have overflowed
            hrcapCalResult.scaleFactor = 1.0f;
        }
    }

    // Clear the interrupts
    HRCAP_clearCalibrationFlags(HRCAP1_BASE + 0x40, calStatus);

    // Acknowledge the PIE interrupt group
    //Interrupt_clearACKGroup(INT_myECAP0_HR_INTERRUPT_ACK_GROUP);
}

void config_ECAP(uint32_t base)
{
	puts("config ECAP");
	// Disable ,clear all capture flags and interrupts
	ECAP_disableInterrupt(base,
			 (ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
			 ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
			 ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
			 ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
			 ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
			 ECAP_ISR_SOURCE_COUNTER_PERIOD   |
			 ECAP_ISR_SOURCE_COUNTER_COMPARE));
	ECAP_clearInterrupt(base,
			 (ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
			 ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
			 ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
			 ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
			 ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
			 ECAP_ISR_SOURCE_COUNTER_PERIOD   |
			 ECAP_ISR_SOURCE_COUNTER_COMPARE));

	// Disable CAP1-CAP4 register loads
	ECAP_disableTimeStampCapture(base);

	/* Configure eCAP
	 * Enable capture mode.
	 * One shot mode, stop capture at event 4.
	 * Set polarity of the events to rising, falling, rising, falling edge.
	 * Set capture in time difference mode.
	 * Select input from XBAR7.
	 * Enable eCAP module.
	 * Enable interrupt.
	 */
	ECAP_stopCounter(base);
	ECAP_enableCaptureMode(base);

	ECAP_setCaptureMode(base, ECAP_CONTINUOUS_CAPTURE_MODE, ECAP_EVENT_4);

	ECAP_setEventPolarity(base, ECAP_EVENT_1, ECAP_EVNT_FALLING_EDGE);
	ECAP_setEventPolarity(base, ECAP_EVENT_2, ECAP_EVNT_RISING_EDGE);
	ECAP_setEventPolarity(base, ECAP_EVENT_3, ECAP_EVNT_FALLING_EDGE);
	ECAP_setEventPolarity(base, ECAP_EVENT_4, ECAP_EVNT_RISING_EDGE);

	ECAP_disableCounterResetOnEvent(base, ECAP_EVENT_1);
	ECAP_disableCounterResetOnEvent(base, ECAP_EVENT_2);
	ECAP_disableCounterResetOnEvent(base, ECAP_EVENT_3);
	ECAP_disableCounterResetOnEvent(base, ECAP_EVENT_4);

	ECAP_selectECAPInput(base, ECAP_INPUT_OUTPUTXBAR1);
	ECAP_enableLoadCounter(base);
	ECAP_setSyncOutMode(base, ECAP_SYNC_OUT_DISABLED);
	ECAP_enableTimeStampCapture(base);
	ECAP_startCounter(base);
	ECAP_resetCounters(base);
	ECAP_enableTimeStampCapture(base);
	ECAP_reArm(base);

	ECAP_enableInterrupt(base, ECAP_ISR_SOURCE_CAPTURE_EVENT_4);
}

void config_HRCAP(uint32_t base)
{
	//enable continous calibration
	HRCAP_setCalibrationMode(base);

	//set calibration period
	HRCAP_setCalibrationPeriod(base, 1000000);

	//enable HRCLK
	puts("enable hrclk");
	HRCAP_enableHighResolutionClock(base);
	puts("enable hrclk done");

	//enable HR mode
	HRCAP_enableHighResolution(base);

	//enable interrupt
	HRCAP_enableCalibrationInterrupt(base, HRCAP_CALIBRATION_DONE);
	HRCAP_enableCalibrationInterrupt(base, HRCAP_CALIBRATION_PERIOD_OVERFLOW);

	//start calibration
	HRCAP_startCalibration(base);
}

void init_HRCAP()
{
	puts("init HRCAP");
	//configure ECAP
	config_ECAP(HRCAP1_BASE);

	//configure HRCAP
	config_HRCAP(HRCAP1_BASE + 0x40);
}

void hrcap_testcase_reset(void)
{
	init_HRCAP();
    simple_delay(100);
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ECAP1);
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ECAP6);

    // 测试ECAP随着核1一起复位
    SysCtl_selectCPUForPeripheralInstance(SYSCTL_CPUSEL_ECAP6, SYSCTL_CPUSEL_CPU1);
    init_HRCAP();
    simple_delay(100);
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_CPU1);
}

void hrcap_testcase_cal_delay_clock(void)
{
	// Initialize counters
	ecapIntCount = 0;
	cap2Count = 0U;
	cap3Count = 0U;
	cap4Count = 0U;

	Interrupt_enable(INT_ECAP6_HRCAL);
	Interrupt_enable(INT_ECAP6);

	init_HRCAP();
	puts("init HRCAP done");

#if 1
	XBAR_setOutputMuxConfig(XBAR_OUTPUT1, XBAR_OUT_MUX00_ECAP1_OUT);  // ECAP1_OUT(PWM) -> OUTPUT_1
	XBAR_enableOutputMux(XBAR_OUTPUT1, XBAR_MUX00);

	ECAP_stopCounter(ECAP1_BASE);   // stop counter first
	ECAP_resetCounters(ECAP1_BASE); // need reset counter
	ECAP_enableAPWMMode(ECAP1_BASE);
	ECAP_setPhaseShiftCount(ECAP1_BASE, 10000000);
	ECAP_setAPWMPolarity(ECAP1_BASE, ECAP_APWM_ACTIVE_HIGH);
	ECAP_setSyncOutMode(ECAP1_BASE, ECAP_SYNC_OUT_DISABLED);
	// bug here
	ECAP_setAPWMPeriod(ECAP1_BASE, 2000);
	ECAP_setAPWMCompare(ECAP1_BASE, 500);
	((struct ECAP_REGS *)ECAP1_BASE)->ECCTL2.bit.SYNCI_EN = 0;
	ECAP_startCounter(ECAP1_BASE);

	//ECAP_setAPWMShadowCompare(ECAP1_BASE, 2);
	//ECAP_setAPWMShadowPeriod(ECAP1_BASE, 5);
#endif

	// Loop indefinitely
	while(1) {
	    if (period1 != 0) {
	        // Convert from nS to MHz
	        inputFreqMHz = 1 / (period1 / 1000);
	    }
	}
}

void test_hrcap(void)
{
	puts("hrcap test start");
	//enable pclk

	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP6);
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP1);

    //hrcap_testcase_reset();

    hrcap_testcase_cal_delay_clock();
}

#endif
