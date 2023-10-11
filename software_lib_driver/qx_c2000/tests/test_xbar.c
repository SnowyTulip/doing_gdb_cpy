#include "common.h"

static u8 adc_event_state = 0;

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
        Interrupt_enable(INT_EPWM1 + ch);
    else
        Interrupt_disable(INT_EPWM1 + ch);

    if (p_flag)
    {
        printf("epwm test -> ch:%d, count_mode:%d, tbprd:%d, cmp:%d, tbphs:%d, int_type:%d\n", ch, count_mode, tbprd,
            cmp, tbphs, int_type);
    }
}

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

void test_inputBar_reg()
{
    puts("test_inputBar_reg");
    int i, j;
    for (i = 0; i < 16; i++)
    {
        j = 0xFFFE; // default value test
        if (HWREGH(INPUTXBAR_BASE + i * 4) != j)
            printf("XBAR_setInputPin error(i=%d, j=%d, val=%d)\n", i, j, HWREGH(INPUTXBAR_BASE + i * 4));

        for (j = 0; j < 16; j++) // all valid value set test
        {
            XBAR_setInputPin(i, j);
            if (HWREGH(INPUTXBAR_BASE + i * 4) != j)
                printf("XBAR_setInputPin error(i=%d, j=%d, val=%d)\n", i, j, HWREGH(INPUTXBAR_BASE + i * 4));
        }

        j = 0x10; // invalid value test
        XBAR_setInputPin(i, j);
        if (HWREGH(INPUTXBAR_BASE + i * 4) != j)
            printf("XBAR_setInputPin error(i=%d, j=%d, val=%d)\n", i, j, HWREGH(INPUTXBAR_BASE + i * 4));

        j = 0xFFFE;
        XBAR_setInputPin(i, j);
        if (HWREGH(INPUTXBAR_BASE + i * 4) != j)
            printf("XBAR_setInputPin error(i=%d, j=%d, val=%d)\n", i, j, HWREGH(INPUTXBAR_BASE + i * 4));

        j = 0xFFFF; // max invalid value test
        XBAR_setInputPin(i, j);
        if (HWREGH(INPUTXBAR_BASE + i * 4) != j)
            printf("XBAR_setInputPin error(i=%d, j=%d, val=%d)\n", i, j, HWREGH(INPUTXBAR_BASE + i * 4));

        // lock test
        XBAR_setInputPin(i, 1);
        if (HWREGH(INPUTXBAR_BASE + i * 4) != 1)
            printf("XBAR_setInputPin error(i=%d, j=%d, val=%d)\n", i, 1, HWREGH(INPUTXBAR_BASE + i * 4));

        XBAR_lockInput(i);

        XBAR_setInputPin(i, 2);
        if (HWREGH(INPUTXBAR_BASE + i * 4) != 1)
            printf("XBAR_setInputPin error(i=%d, j=%d, val=%d)\n", i, 1, HWREGH(INPUTXBAR_BASE + i * 4));
    }
}

void test_outputBar()
{
    puts("output xbar test...");
    for (int i = 0; i < 16 * 4; i += 4)
    {
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX00_ADCAEVT1);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX00_ECAP1_OUT);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX01_INPUTXBAR1);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX01_ADCCEVT1);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX02_ADCAEVT2);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX02_ECAP2_OUT);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX03_INPUTXBAR2);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX03_ADCCEVT2);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX04_ADCAEVT3);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX04_ECAP3_OUT);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX05_INPUTXBAR3);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX05_ADCCEVT3);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX06_ADCAEVT4);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX06_ECAP4_OUT);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX07_INPUTXBAR4);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX07_ADCCEVT4);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX08_ADCBEVT1);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX08_ECAP5_OUT);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX09_INPUTXBAR5);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX10_ADCBEVT2);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX10_ECAP6_OUT);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX11_INPUTXBAR6);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX12_ADCBEVT3);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX12_ECAP7_OUT);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX13_ADCSOCA);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX14_ADCBEVT4);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX14_EXTSYNCOUT);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX15_ADCSOCB);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX16_SD1FLT1_COMPH);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX16_SD1FLT1_COMPH_OR_COMPL);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX17_SD1FLT1_COMPL);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX18_SD1FLT2_COMPH);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX18_SD1FLT2_COMPH_OR_COMPL);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX19_SD1FLT2_COMPL);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX20_SD1FLT3_COMPH);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX20_SD1FLT3_COMPH_OR_COMPL);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX21_SD1FLT3_COMPL);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX22_SD1FLT4_COMPH);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX22_SD1FLT4_COMPH_OR_COMPL);
        XBAR_setOutputMuxConfig(i, XBAR_OUT_MUX23_SD1FLT4_COMPL);
    }
}

void test_InputBarToOutputBar()
{ // test from Input to Output  (GPIO2 ---->Input1 -----> Output1)   // XBar_Flag

    puts("test_InputBarToOutputBar...");

    // Config GPIO
    GPIO_Config(2, GPIO_2_SCIA_TX, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);

    // Config InputBar
    XBAR_setInputPin(XBAR_INPUT1, XBAR_INPUT_GPIO2); // 参数1：选择Input  参数2： 选择 GPIO Pin （从GPIO1输入，从Input1输出）

    // Config OutputBar
    XBAR_enableOutputMux(XBAR_OUTPUT1, 1); // 参数1： 选择Output  参数2： 选择 复用口

    XBAR_setOutputLatchMode(XBAR_OUTPUT1, 1);

    XBAR_clearOutputLatch(XBAR_OUTPUT1);

    XBAR_setOutputMuxConfig(XBAR_OUTPUT1, XBAR_OUT_MUX01_INPUTXBAR1);

    // Config Xbar_Flag
    printf("Flag_Status:%d\n", XBAR_getInputFlagStatus(XBAR_INPUT_FLG_INPUT1));

    // printf test over
    puts("test_InputBarToOutputBar  over!");
}

void test_ADCEvent_epwmXbar()
{ // test from ADCEvent to Output  (ADCEvent input ----> epwmbar)   // XBar_Flag

    puts("test_epwmXbar start ...");

    // XBAR_enableEPWMMux(XBAR_TRIP5,4);
    EPwmXbarRegs->TRIP5MUXENABLE.all = 4; //  XBAR_TRIP5  mux4

    XBAR_setEPWMMuxConfig(XBAR_TRIP5, XBAR_EPWM_MUX04_ADCAEVT3);

    // triggger adc_event3_a
    puts("adc test start...");
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
    puts("now start adc...");
    ADC_enableConverter(ADCA_REGS_BASE);
    simple_delay(200);

    ADC_disablePPBEventCBCClear(ADCA_REGS_BASE, ADC_PPB_NUMBER3);
    ADC_disablePPBTwosComplement(ADCA_REGS_BASE, ADC_PPB_NUMBER3);
    ADC_setPPBTripLimits(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x10, -0x08);
    ADC_enablePPBEvent(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x7);
    ADC_disablePPBEventInterrupt(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x7);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER3, ADC_SOC_NUMBER1);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x1);
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN18, ADC_SAMPLE_WINDOW_2);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1);
    simple_delay(100);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x10);
    simple_delay(100);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x30);
    ADC_clearPPBEventStatus(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x7);
    simple_delay(50);
    ADC_setPPBTripLimits(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x10, -0x20);
    simple_delay(50);
    adc_event_state = ADC_getPPBEventStatus(ADCA_REGS_BASE, ADC_PPB_NUMBER3);
    printf("adc event state is %x\n", adc_event_state);
    ADC_clearPPBEventStatus(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x7);
    adc_event_state = ADC_getPPBEventStatus(ADCA_REGS_BASE, ADC_PPB_NUMBER3);
    printf("adc event state is %x\n", adc_event_state);

    puts("test_epwmXbar  over!");
}

void test_ecap_epwmXbar()
{
    puts("test_epwmXbar start ...");

    // XBAR_enableEPWMMux(XBAR_TRIP5,4);
    EPwmXbarRegs->TRIP5MUXENABLE.all = 1; //  XBAR_TRIP5  mux4

    XBAR_setEPWMMuxConfig(XBAR_TRIP5, XBAR_EPWM_MUX00_ECAP1_OUT);

    EPwmXbarRegs->TRIP4MUXENABLE.bit.MUX2 = 1;
    XBAR_setEPWMMuxConfig(XBAR_TRIP4, XBAR_EPWM_MUX02_ECAP2_OUT);

    // 测试ecap的同步，利用epwm4和ecap1与ecap2进行同步
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP2);
    CpuSysRegs->PCLKCR0.bit.TBCLKSYNC = 0;
    // 增减计数, 10KHz, 占空比50%
    pwm_normal_gen_for_ecap(3, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 8, 0, 1);
    EPWM_setSyncOutPulseMode(EPWM4_BASE, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP1, SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT); // 设置ECAP1的输入为EPWM4SYNCOUT
    //    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP4,
    //    SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT);//设置ECAP4的输入为EPWM4SYNCOUT
    CpuSysRegs->PCLKCR0.bit.TBCLKSYNC = 1;
    simple_delay(200);
    ECAP_APWMConfig(ECAP1_BASE, 1000, 300, 0, ECAP_APWM_ACTIVE_LOW, 0, ECAP_SYNC_OUT_SYNCI);
    ECAP_APWMConfig(ECAP2_BASE, 1000, 300, 0, ECAP_APWM_ACTIVE_LOW, 0, ECAP_SYNC_OUT_SYNCI);
    ECAP_enableLoadCounter(ECAP1_BASE);
    ECAP_enableLoadCounter(ECAP2_BASE);
    ECAP_startCounter(ECAP1_BASE);
    ECAP_startCounter(ECAP2_BASE);

    puts("ecap....");

    while (1)
        ;
}

void test_xbar(void)
{
    puts("XBar test...");

//	test_inputBar_reg();   /** InputBar_test  **/
//	test_outputBar();      /** OutputBar_test **/
//	test_InputBarToOutputBar();
//	test_ADCEvent_epwmXbar();
	test_ecap_epwmXbar();

}
