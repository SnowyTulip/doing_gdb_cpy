#include "common.h"

#ifdef TEST_ECAP

u32 cap_result[100] = { 0 };
static u32 num_intr = 0;
__interrupt void ecap1_isr(void)
{
	puts("ecap1 isr start");
    cap_result[num_intr]     = ECap1Regs->CAP1;
    cap_result[num_intr + 1] = ECap1Regs->CAP2;
    cap_result[num_intr + 2] = ECap1Regs->CAP3;
    cap_result[num_intr + 3] = ECap1Regs->CAP4;
    num_intr += 4;
    ECap1Regs->ECCLR.all = 0xFFFF;
}

__interrupt void ecap2_isr(void)
{
	puts("ecap2 isr start");
    cap_result[num_intr]     = ECap2Regs->CAP1;
    cap_result[num_intr + 1] = ECap2Regs->CAP2;
    cap_result[num_intr + 2] = ECap2Regs->CAP3;
    cap_result[num_intr + 3] = ECap2Regs->CAP4;
    num_intr += 4;
    ECap2Regs->ECCLR.all = 0xFFFF;
}

__interrupt void ecap3_isr(void)
{
	puts("ecap3 isr start");
    cap_result[num_intr]     = ECap3Regs->CAP1;
    cap_result[num_intr + 1] = ECap3Regs->CAP2;
    cap_result[num_intr + 2] = ECap3Regs->CAP3;
    cap_result[num_intr + 3] = ECap3Regs->CAP4;
    num_intr += 4;
    ECap3Regs->ECCLR.all = 0xFFFF;
}

__interrupt void ecap4_isr(void)
{
	puts("ecap3 isr start");
    cap_result[num_intr]     = ECap4Regs->CAP1;
    cap_result[num_intr + 1] = ECap4Regs->CAP2;
    cap_result[num_intr + 2] = ECap4Regs->CAP3;
    cap_result[num_intr + 3] = ECap4Regs->CAP4;
    num_intr += 4;
    ECap4Regs->ECCLR.all = 0xFFFF;
}

__interrupt void ecap5_isr(void)
{
	puts("ecap3 isr start");
    cap_result[num_intr]     = ECap5Regs->CAP1;
    cap_result[num_intr + 1] = ECap5Regs->CAP2;
    cap_result[num_intr + 2] = ECap5Regs->CAP3;
    cap_result[num_intr + 3] = ECap5Regs->CAP4;
    num_intr += 4;
    ECap5Regs->ECCLR.all = 0xFFFF;
}

__interrupt void ecap6_isr(void)
{
	puts("ecap3 isr start");
    cap_result[num_intr]     = ECap6Regs->CAP1;
    cap_result[num_intr + 1] = ECap6Regs->CAP2;
    cap_result[num_intr + 2] = ECap6Regs->CAP3;
    cap_result[num_intr + 3] = ECap6Regs->CAP4;
    num_intr += 4;
    ECap6Regs->ECCLR.all = 0xFFFF;
}

__interrupt void ecap7_isr(void)
{
	puts("ecap3 isr start");
    cap_result[num_intr]     = ECap7Regs->CAP1;
    cap_result[num_intr + 1] = ECap7Regs->CAP2;
    cap_result[num_intr + 2] = ECap7Regs->CAP3;
    cap_result[num_intr + 3] = ECap7Regs->CAP4;
    num_intr += 4;
    ECap7Regs->ECCLR.all = 0xFFFF;
}

#if 1
void pwm_normal_gen_for_ecap(u8 ch, u8 count_mode, u16 tbprd, u16 cmp, u16 tbphs, u8 int_type, u32 p_flag)
{
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    EPWM_setTimeBaseCounterMode(epwm_base, count_mode);         /* 计数模式  */
    EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_SHADOW_LOAD); /* 启用影子模式读写TBPRD */
    EPWM_setSyncOutPulseMode(epwm_base, EPWM_SYNC_OUT_PULSE_ON_EPWMxSYNCIN);
    EPWM_setClockPrescaler(epwm_base, 2, 1);
    EPWM_setPhaseShift(epwm_base, tbphs);     /* 相位偏移 */
    EPWM_setTimeBasePeriod(epwm_base, tbprd); /* 时基周期设置 */
    EPWM_setTimeBaseCounter(epwm_base, 0);    /* 清零时基计数寄存器 */

    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_C, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_D, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_A, cmp);
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_B, cmp / 2);
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_C, 1);
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_D, 2);

    EPWM_setActionQualifierAction(epwm_base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(epwm_base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    if (int_type)
    {
        Interrupt_enable(INT_ECAP1 + ch);
    }
    else
    {
        Interrupt_disable(INT_ECAP1 + ch);
    }
    if (p_flag)
    {
        printf("epwm test -> ch:%d, count_mode:%d, tbprd:%d, cmp:%d, tbphs:%d, int_type:%d\n", ch, count_mode, tbprd,
            cmp, tbphs, int_type);
    }
}

void get_sync_for_ecap()
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM4);
    CpuSysRegs->PCLKCR0.bit.TBCLKSYNC = 0;
    /* 增减计数, 10KHz, 占空比50%  */
    pwm_normal_gen_for_ecap(3, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 8, 0, 1);
    EPWM_setSyncOutPulseMode(EPWM4_BASE, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP1, SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT); // 设置ECAP1的输入为EPWM4SYNCOUT
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP4, SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT); // 设置ECAP4的输入为EPWM4SYNCOUT
    CpuSysRegs->PCLKCR0.bit.TBCLKSYNC = 1;
    int delay                         = 10000;
    while (delay--)
        ;
}
#endif

#if 1
void ECAP_APWMConfig(uint32_t base, u32 period, u32 comp, u32 shift, ECAP_APWMPolarity pol, u32 syncin_en,
    ECAP_SyncOutMode sync_out_mode)
{
    ECAP_stopCounter(base);   // stop counter first
    ECAP_resetCounters(base); // need reset counter
    ECAP_enableAPWMMode(base);
    ECAP_setPhaseShiftCount(base, shift);
    ECAP_setAPWMPolarity(base, pol);
    ECAP_setSyncOutMode(base, sync_out_mode);
    // bug here
    ECAP_setAPWMPeriod(base, period);
    ECAP_setAPWMCompare(base, comp);
    ((struct ECAP_REGS *)base)->ECCTL2.bit.SYNCI_EN = syncin_en;
}
#endif

#if 1
void ECAP_CaptureConfig(u32 base, ECAP_CaptureMode cap_mode, ECAP_Events stop_warp, u8 prescale, u8 cap_load,
    u32 count_mode, ECAP_EventPolarity p1, ECAP_EventPolarity p2, ECAP_EventPolarity p3, ECAP_EventPolarity p4)
{
    ECAP_stopCounter(base);
    ECAP_resetCounters(base);
    ECAP_enableCaptureMode(base);
    ECAP_setCaptureMode(base, cap_mode, stop_warp);
    ECAP_setEventPrescaler(base, prescale);
    struct ECAP_REGS *ecap   = (struct ECAP_REGS *)base;
    ecap->ECCTL1.bit.CAPLDEN = cap_load;
    ecap->ECCTL1.bit.CTRRST1 = count_mode;
    ecap->ECCTL1.bit.CTRRST2 = count_mode;
    ecap->ECCTL1.bit.CTRRST3 = count_mode;
    ecap->ECCTL1.bit.CTRRST4 = count_mode;
    ecap->ECCTL1.bit.CAP1POL = p1;
    ecap->ECCTL1.bit.CAP2POL = p2;
    ecap->ECCTL1.bit.CAP3POL = p3;
    ecap->ECCTL1.bit.CAP4POL = p4;
}
#endif

void ecap_testcase_apwm(void)
{
	puts("ecap apwm to (active high) 100:30 (fastest) test...");
	ECAP_APWMConfig(ECAP1_BASE, 100, 30, 0, ECAP_APWM_ACTIVE_HIGH, 0, ECAP_SYNC_OUT_DISABLED);
	ECAP_startCounter(ECAP1_BASE);
	ECAP_setAPWMShadowCompare(ECAP1_BASE, 1000);
	ECAP_setAPWMShadowPeriod(ECAP1_BASE, 1000);
	ECAP_setAPWMShadowCompare(ECAP1_BASE, 1);
	ECAP_setAPWMShadowPeriod(ECAP1_BASE, 1001);
	ECAP_setAPWMShadowCompare(ECAP1_BASE, 0);
	ECAP_stopCounter(ECAP1_BASE);
	ECAP_resetCounters(ECAP1_BASE); // need reset counter
	ECAP_setAPWMPeriod(ECAP1_BASE, 1);
	ECAP_setAPWMCompare(ECAP1_BASE, 1);
	ECAP_startCounter(ECAP1_BASE);
}

void ecap_testcase_interrupt(void)
{
	puts("ecap interrupt test");

	//struct ECAP_REGS *ecap_c = (struct ECAP_REGS *) (ECAP1_BASE + (ecap_n + 1) % 5 * 0x100);
	//struct ECAP_REGS *ecap_a = (struct ECAP_REGS *) (ECAP1_BASE + ecap_n * 0x100);

    // 测试中断产生,以及测试准确度
    XBAR_setOutputMuxConfig(XBAR_OUTPUT1, XBAR_OUT_MUX00_ECAP1_OUT);
    XBAR_enableOutputMux(XBAR_OUTPUT1, XBAR_MUX00);
    ECAP_APWMConfig(ECAP1_BASE, 2000, 600, 0, ECAP_APWM_ACTIVE_HIGH, 0, ECAP_SYNC_OUT_DISABLED);
    ECAP_startCounter(ECAP1_BASE);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP2);
    ECAP_setSyncOutMode(ECAP2_BASE, ECAP_SYNC_OUT_DISABLED);
    ECAP_disableLoadCounter(ECAP2_BASE);
    ECAP_selectECAPInput(ECAP2_BASE, ECAP_INPUT_OUTPUTXBAR1);
    ECAP_CaptureConfig(ECAP2_BASE, ECAP_CONTINUOUS_CAPTURE_MODE, ECAP_EVENT_4, 0, 1, 0, ECAP_EVNT_RISING_EDGE,
        ECAP_EVNT_FALLING_EDGE, ECAP_EVNT_RISING_EDGE, ECAP_EVNT_FALLING_EDGE);
    Interrupt_enable(INT_ECAP2);
    ECAP_enableInterrupt(ECAP2_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_4);
    ECAP_startCounter(ECAP2_BASE);
    simple_delay(400);
    printf("interrupt happens %d times\n", num_intr / 4);
    printf("high period is %d\n", cap_result[num_intr - 3] - cap_result[num_intr - 4]);
    printf("low period is %d\n", cap_result[num_intr - 2] - cap_result[num_intr - 3]);
    while (1)
        ;
}

void ecap_testcase_reset(void)
{
	// 测试ECAP软复位
	ECAP_APWMConfig(ECAP1_BASE, 100, 30, 0, ECAP_APWM_ACTIVE_HIGH, 0, ECAP_SYNC_OUT_DISABLED);
	ECAP_startCounter(ECAP1_BASE);
	simple_delay(100);
	SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ECAP1);

	// 测试ECAP软复位
	ECAP_APWMConfig(ECAP1_BASE, 100, 30, 0, ECAP_APWM_ACTIVE_HIGH, 0, ECAP_SYNC_OUT_DISABLED);
	ECAP_startCounter(ECAP1_BASE);
	simple_delay(100);
	SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ECAP1);

	// 测试ECAP随着核1一起复位
	SysCtl_selectCPUForPeripheralInstance(SYSCTL_CPUSEL_ECAP1, SYSCTL_CPUSEL_CPU1);
	ECAP_APWMConfig(ECAP1_BASE, 100, 30, 0, ECAP_APWM_ACTIVE_HIGH, 0, ECAP_SYNC_OUT_DISABLED);
	ECAP_startCounter(ECAP1_BASE);
	simple_delay(100);
	SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_CPU1);
}

void test_ecap(void)
{
    int i = 0;
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP1);

    puts("ecap test start");
#if 0
    ecap_testcase_apwm();
#endif

#if 0
    puts("ecap apwm (active low) to 10:3 test...");
    ECAP_APWMConfig(ECAP1_BASE, 10, 3, 0, ECAP_APWM_ACTIVE_LOW, 0, ECAP_SYNC_OUT_DISABLED);
    ECAP_startCounter(ECAP1_BASE);
    puts("change pwm period wave to 1000:1 in running test...");
    ECAP_setAPWMShadowCompare(ECAP1_BASE, 1000);
    ECAP_setAPWMShadowPeriod(ECAP1_BASE, 1000);
    puts("change pwm period wave to always low in running test...");
    ECAP_setAPWMShadowPeriod(ECAP1_BASE, 1002);
    puts("change pwm period wave to alway high running test...");
    ECAP_setAPWMShadowCompare(ECAP1_BASE, 0);
    puts("change pwm period wave to 1:1000 running test...");
    ECAP_setAPWMShadowCompare(ECAP1_BASE, 1);
#endif

#if 0
    // 先配置采集再产生pwm波会导致最开始抖动，当然影响不大，仅仅是前几次cap的值
    // 故采取先产生apwm波后配置采集
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP2);
    puts("ecap1 apwm -> ecap2 capture test...");
    ECAP_setSyncOutMode(ECAP2_BASE, ECAP_SYNC_OUT_DISABLED);
    ECAP_disableLoadCounter(ECAP2_BASE);
    ECAP_selectECAPInput(ECAP2_BASE, ECAP_INPUT_OUTPUTXBAR1);// INPUT_1 -> ECAP2_IN (ECAP_INPUT_OUTPUTXBAR1)
    /* interrupt enable */
//    Interrupt_enable(PIC_GROUP4);
    ECAP_disableInterrupt(ECAP2_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_1);
    XBAR_setOutputMuxConfig(XBAR_OUTPUT1, XBAR_OUT_MUX00_ECAP1_OUT);  // ECAP1_OUT(PWM) -> OUTPUT_1
    XBAR_enableOutputMux(XBAR_OUTPUT1, XBAR_MUX00);
    ECAP_APWMConfig(ECAP1_BASE, 5000, 2000, 0, ECAP_APWM_ACTIVE_HIGH, 0, ECAP_SYNC_OUT_DISABLED);
    ECAP_startCounter(ECAP1_BASE);
    // 测试连续采集或者单次采集
	ECAP_CaptureConfig(ECAP2_BASE, ECAP_CONTINUOUS_CAPTURE_MODE, ECAP_EVENT_4, 5, 1, 0, ECAP_EVNT_RISING_EDGE,
		ECAP_EVNT_FALLING_EDGE, ECAP_EVNT_RISING_EDGE, ECAP_EVNT_FALLING_EDGE);
//	ECAP_CaptureConfig(ECAP2_BASE, ECAP_ONE_SHOT_CAPTURE_MODE, ECAP_EVENT_4, 0, 1, 0, ECAP_EVNT_RISING_EDGE,
//			ECAP_EVNT_FALLING_EDGE, ECAP_EVNT_RISING_EDGE, ECAP_EVNT_FALLING_EDGE);
	ECAP_startCounter(ECAP2_BASE);
	puts("now change pwm period wave to 5:2 in running test...");
	ECAP_setAPWMShadowCompare(ECAP1_BASE, 2);
	ECAP_setAPWMShadowPeriod(ECAP1_BASE, 5);
    while (1)
        ;
#endif

#if 0
    // ecclr寄存器的值清除之后不操作的话应该要自动拉下来，修改后测试通过。
    // 此外顺便测试是否每个event都可以作为采集循环的结束
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP2);
    ECAP_setSyncOutMode(ECAP2_BASE, ECAP_SYNC_OUT_DISABLED);
    ECAP_disableLoadCounter(ECAP2_BASE);
    ECAP_selectECAPInput(ECAP2_BASE, ECAP_INPUT_OUTPUTXBAR1);
    XBAR_setOutputMuxConfig(XBAR_OUTPUT1, XBAR_OUT_MUX00_ECAP1_OUT);
    XBAR_enableOutputMux(XBAR_OUTPUT1, XBAR_MUX00);
    ECAP_APWMConfig(ECAP1_BASE, 5000, 2000, 0, ECAP_APWM_ACTIVE_HIGH, 0, ECAP_SYNC_OUT_DISABLED);
    ECAP_startCounter(ECAP1_BASE);
	ECAP_CaptureConfig(ECAP2_BASE, ECAP_CONTINUOUS_CAPTURE_MODE, ECAP_EVENT_3, 0, 1, 0, ECAP_EVNT_RISING_EDGE,
		ECAP_EVNT_FALLING_EDGE, ECAP_EVNT_RISING_EDGE, ECAP_EVNT_FALLING_EDGE);
	ECAP_startCounter(ECAP2_BASE);
	simple_delay(500);
	ECap2Regs->ECCLR.bit.CEVT2 = 1;
    while (1)
        ;
#endif

#if 1
    ecap_testcase_interrupt();
#endif

#if 0
    // 测试单次采集模式的rearm
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP2);
    ECAP_setSyncOutMode(ECAP2_BASE, ECAP_SYNC_OUT_DISABLED);
    ECAP_disableLoadCounter(ECAP2_BASE);
    ECAP_selectECAPInput(ECAP2_BASE, ECAP_INPUT_OUTPUTXBAR1);
    XBAR_setOutputMuxConfig(XBAR_OUTPUT1, XBAR_OUT_MUX00_ECAP1_OUT);
    XBAR_enableOutputMux(XBAR_OUTPUT1, XBAR_MUX00);
    ECAP_APWMConfig(ECAP1_BASE, 3000, 1000, 0, ECAP_APWM_ACTIVE_HIGH, 0, ECAP_SYNC_OUT_DISABLED);
    ECAP_startCounter(ECAP1_BASE);
	ECAP_CaptureConfig(ECAP2_BASE, ECAP_ONE_SHOT_CAPTURE_MODE, ECAP_EVENT_4, 0, 1, 0, ECAP_EVNT_RISING_EDGE,
		ECAP_EVNT_FALLING_EDGE, ECAP_EVNT_RISING_EDGE, ECAP_EVNT_FALLING_EDGE);
	ECAP_startCounter(ECAP2_BASE);
	while(1)
	{
		simple_delay(400);
		ECAP_reArm(ECAP2_BASE);
	}
		;
#endif

#if 0
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP2);
    puts("ecap apwm phase shift test...");
    ECAP_APWMConfig(ECAP1_BASE, 1000, 300, 0, ECAP_APWM_ACTIVE_LOW, 0, ECAP_SYNC_OUT_COUNTER_PRD);
    ECAP_disableLoadCounter(ECAP1_BASE);
    ECAP_APWMConfig(ECAP2_BASE, 800, 300, 300, ECAP_APWM_ACTIVE_LOW, 1, ECAP_SYNC_OUT_DISABLED);
    ECAP_enableLoadCounter(ECAP2_BASE);
    ECAP_startCounter(ECAP2_BASE);
    ECAP_startCounter(ECAP1_BASE);
    while (1)
        ;
#endif

#if 0
    // 测试ecap1控制ecap2同步
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP2);
    ECAP_APWMConfig(ECAP1_BASE, 1000, 300, 0x50, ECAP_APWM_ACTIVE_LOW, 1, ECAP_SYNC_OUT_COUNTER_PRD);
    ECAP_APWMConfig(ECAP2_BASE, 1000, 300, 0x50, ECAP_APWM_ACTIVE_LOW, 1, ECAP_SYNC_OUT_SYNCI);
    ECAP_startCounter(ECAP1_BASE);
    ECAP_startCounter(ECAP2_BASE);
    simple_delay(1000);
    ECAP_stopCounter(ECAP1_BASE);
    ECAP_stopCounter(ECAP2_BASE);
    ECAP_setPhaseShiftCount(ECAP2_BASE, 0x20);
    ECAP_startCounter(ECAP1_BASE);
	ECAP_startCounter(ECAP2_BASE);
    while (1)
        ;
#endif

#if 0
    // 测试ecap的同步，利用epwm4和ecap1与ecap2进行同步
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP2);
    CpuSysRegs->PCLKCR0.bit.TBCLKSYNC = 0;
    /* 增减计数, 10KHz, 占空比50%  */
    pwm_normal_gen_for_ecap(3, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 8, 0, 1);
    EPWM_setSyncOutPulseMode(EPWM4_BASE, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP1, SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT);//设置ECAP1的输入为EPWM4SYNCOUT
//    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP4, SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT);//设置ECAP4的输入为EPWM4SYNCOUT
    CpuSysRegs->PCLKCR0.bit.TBCLKSYNC = 1;
    simple_delay(200);
    ECAP_APWMConfig(ECAP1_BASE, 1000, 300, 0, ECAP_APWM_ACTIVE_LOW, 0, ECAP_SYNC_OUT_SYNCI);
    ECAP_APWMConfig(ECAP2_BASE, 1000, 300, 0, ECAP_APWM_ACTIVE_LOW, 0, ECAP_SYNC_OUT_SYNCI);
    ECAP_enableLoadCounter(ECAP1_BASE);
	ECAP_enableLoadCounter(ECAP2_BASE);
    ECAP_startCounter(ECAP1_BASE);
    ECAP_startCounter(ECAP2_BASE);
    while (1)
        ;
#endif

#if 0
    // ADC事件目前还有问题，事件数量有重复，可以让ecap采集，在ADC修改完成后再进行测试
#endif

    return;

error:
    puts("error: ecap test error!");
}

#endif
