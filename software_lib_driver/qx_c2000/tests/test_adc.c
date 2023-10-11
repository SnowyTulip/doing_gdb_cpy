#include "common.h"

static int num_adc_intr = 0, num_adc_evt_intr = 0;
static int event_flag     = 0;
static int adc_result     = 0;
static u8 adc_event_state = 0;
static int x              = 0;

__interrupt void adca2_isr()
{
    puts("intr happends in a");
    num_adc_intr++;
}

__interrupt void adcb2_isr()
{
    puts("intr happends in b");
    num_adc_intr++;
}

__interrupt void adcc2_isr()
{
    puts("intr happends in c");
    num_adc_intr++;
}

__interrupt void adca_evt_isr()
{
    //    puts("event intr happends");
    //    num_adc_evt_intr++;
    //    event_flag = ADC_getPPBEventStatus(ADCA_REGS_BASE);
    //    printf("%d\n", event_flag);
    //    ADC_disablePPBEventInterrupt(ADCA_REGS_BASE, event_flag);
}

// 生成ADC用的PWM soc信号,现在epwm函数里还定义,定义后删除
void pwm_gen_for_adc(u8 ch, u8 count_mode, u16 tbprd, u16 cmp, u16 tbphs, u8 int_type, u32 p_flag)
{
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);
    /* TB */
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    EPWM_setTimeBaseCounterMode(epwm_base, count_mode); /* 计数模式  */
    //    EPWM_enablePhaseShiftLoad(uint32_t base)			/* 不从TBPHS加载TBCTR */
    EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_SHADOW_LOAD); /* 启用影子模式读写TBPRD */
    //    EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_DIRECT_LOAD);     /* 启用直接模式读写TBPRD*/
    epwm->TBCTL.bit.SYNCOSEL = 0;      		/* 禁用EPWMxSYNCO信号，该信号拉高后会使CTR跳转为TBPHS 注:该操作会导致通道2开启时通道1的gpio输出高阻, 需要确定是否正确 */ //00应该是启用？
    /* SWFSYNC，软件强制同步脉冲，应该是动态的，先不管 */
    epwm->TBCTL.bit.HSPCLKDIV
        = 0; /* TBCLK = SYSTEM_OUT_CLK/(2 * HSPCLKDIV * CLKDIV^2)高速基准时钟，为0时只由CLKDIV决定 */
    epwm->TBCTL.bit.CLKDIV = 0; /* TBCLK = SYSTEM_OUT_CLK/(2^CLKDIV)，基准时钟, 最终TBCLK = SYSTEM_OUT_CLK/2 */
                                /* PHSDIR，相位方向位，仅在递增计数时使用*/
                                /* FREE_SOFT，仿真模式自由运行*/

    epwm->TBPHS.bit.TBPHS = tbphs; /* 相位偏移 */
    epwm->TBPRD           = tbprd; /* 时基周期设置 */
    epwm->TBCTR           = 0;     /* 清零时基计数寄存器 */

    /* CC */
    epwm->CMPCTL.bit.SHDWAMODE = 0;
    epwm->CMPCTL.bit.SHDWBMODE = 0;
    //    epwm->CMPCTL.bit.SHDWAMODE = 1;
    //    epwm->CMPCTL.bit.SHDWBMODE = 1;
    epwm->CMPCTL.bit.LOADAMODE = 0;
    epwm->CMPCTL.bit.LOADBMODE = 0;
    epwm->CMPA.bit.CMPA        = cmp;

    /* AQ */
    // 对应赋值1则触发输出0，对应赋值1则触发输出1
    epwm->AQCTLA.bit.CAU = 2; /* 当CTR=CMPA且Up增计数时，EPWM1A输出高电平 */
    epwm->AQCTLA.bit.CAD = 1; /* 当CTR=CMPA且Down减计数时，EPWM1A输出低电平 */
    epwm->AQCTLB.bit.CAU = 2; /* 当CTR=CMPA且Up增计数时，EPWM1B输出高电平 */
    epwm->AQCTLB.bit.CAD = 1; /* 当CTR=CMPA且Down减计数时，EPWM1B输出低电平 */

    /* DB */
    epwm->DBCTL.bit.OUT_MODE = 0; /* 死区完全旁路 */
    /* PC */
    //    EPWM_enableChopper(epwm_base);	/* 斩波器完全旁路 */

    /* 是否打开中断触发 */
    if (int_type)
        Interrupt_enable(INT_EPWM1 + ch);
    else
        Interrupt_disable(INT_EPWM1 + ch);

    if (p_flag)
        printf("epwm test -> ch:%d, count_mode:%d, tbprd:%d, cmp:%d, tbphs:%d, int_type:%d\n", ch, count_mode, tbprd,
            cmp, tbphs, int_type);
}

void gen_et_for_adc(u8 ch)
{
    uint32_t epwm_base              = EPWM1_BASE + ch * 0x200;
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);

    epwm->ETSEL.bit.INTSEL  = 1; // 使能eq_zero事件
    epwm->ETSEL.bit.SOCASEL = 1; // 使能eq_zero事件
    epwm->ETSEL.bit.SOCBSEL = 1; // 使能eq_zero事件

    epwm->ETSEL.bit.SOCAEN = 1; // 使能SOCA输出
    epwm->ETSEL.bit.SOCBEN = 1; // 使能SOCA输出

    epwm->ETPS.bit.SOCAPRD = 3; // 每发生3次事件产生一个SOCA脉冲
    epwm->ETPS.bit.SOCBPRD = 3;
}

extern void timer_setAndStart(CPUTimerReg_types *timer, timer_mode_type timer_mode, u32 time_value, u8 int_flag);

void test_adc(void)
{
    // 测试ADC时在硬件tb模块给CH产生了激励,以让ADC采集模拟信号可以获得不同的值
    puts("adc test start...");
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
    puts("now start adc...");
    ADC_enableConverter(ADCA_REGS_BASE);
    simple_delay(200);

#if 0
    // 测试分频
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_8_0);
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    simple_delay(10);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7);
    simple_delay(10);
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_2_0);
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER9, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    simple_delay(10);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER9);
    simple_delay(10);
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_18_0);
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_3);
    simple_delay(10);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2);
    simple_delay(10);
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_4_0);
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER17, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_2);
    simple_delay(10);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER17);
    simple_delay(10);
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_16_0);
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_1);
    simple_delay(10);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4);
    simple_delay(10);
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_14_0);
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    simple_delay(10);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4);
    simple_delay(10);
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_2_0);
#endif

#if 0
    // 测试软件触发SOC是否可以正确采集,不考虑中断
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7);
    puts("now read adc in result7...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER7);
    printf("7 is 0x%x\n", adc_result);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER10);
    puts("now read adc in result10...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER10);
    printf("10 is 0x%x\n", adc_result);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1);
    puts("now read adc in result1...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER1);
    printf("0x%x\n", adc_result);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2);
    puts("now read adc in result2...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER2);
    printf("0x%x\n", adc_result);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3);
    puts("now read adc in result3...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER3);
    printf("0x%x\n", adc_result);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4);
    puts("now read adc in result4...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN8, ADC_SAMPLE_WINDOW_1);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4);
    puts("now read adc again in result4...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER4);
    printf("0x%x\n", adc_result);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER19, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER19);
    puts("now read adc in result19...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER19);
    printf("0x%x\n", adc_result);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0);
    puts("now read in result0...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER0);
    printf("0x%x\n", adc_result);
#endif

#if 0
    // 软件连续触发
    //     ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_18_0);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_5);
    while (1)
    {
        simple_delay(200);
        ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x7);
    }
#endif

#if 0
    // 测试ADC的关掉后再使能复位,还能不能再继续从任意SOC开始采集
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN5, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER10);
    puts("now read adc in result10...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER10);
    printf("10 is 0x%x\n", adc_result);
    ADC_disableConverter(ADCA_REGS_BASE);
    simple_delay(100);
    ADC_enableConverter(ADCA_REGS_BASE);
    simple_delay(100);	// 需要等ADC启动并稳定
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6);
    puts("now read adc again in result6...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER6);
    printf("0x%x\n", adc_result);

#endif

#if 0
    // 测试 SOC是否可以正确连续采集,不考虑中断,而且在第一次采集未完成时就配置下一个SOC
    puts("tests continuous acquisition");
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0xff);
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_1);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x8f);
    simple_delay(100);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_20);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_20);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x28);
    puts("now start read adc...");
    puts("now read adc in result7...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER7);
    printf("0x%x\n", adc_result);
    puts("now read adc in result0...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER0);
    printf("0x%x\n", adc_result);
    puts("now read adc in result1...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER1);
    printf("0x%x\n", adc_result);
    puts("now read adc in result2...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER2);
    printf("0x%x\n", adc_result);
    puts("now read adc in result3...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER3);
    printf("0x%x\n", adc_result);
    puts("now read adc in result4...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER4);
    printf("0x%x\n", adc_result);
    puts("now read adc in result5...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER5);
    printf("0x%x\n", adc_result);
    puts("now read adc in result6...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER6);
    printf("0x%x\n", adc_result);
#endif

#if 0
    // 软硬件交替测试
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER16, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x100bf);
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER16, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_1);
    simple_delay(50);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 1, 300);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(400);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN14, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER11, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER12, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER13, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_1);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x3c80);
#endif

#if 0
    // 测试计时器硬件触发SOC是否可以正确采集.触发源非常快，使用要避免这种场景产生。
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_16_0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_10);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_1);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 1, 300);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    CPUTimer_disableTimer(CPUTimer0Regs);
    CPUTimer_enableTimer(CPUTimer0Regs);
    int temp = AdcaRegs->ADCSOCFLG.all;
    printf("0x%x\n", temp);
    simple_delay(100);
    CPUTimer_enableInterrupt(CPUTimer0Regs);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER0);
    printf("0x%x\n", adc_result);
#endif

#if 0
    // 可以跳跃，任意数量SOC进行采集.触发源是上升沿
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_8);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_5);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 500, 2000);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_20_0);
    simple_delay(300);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER6);
    printf("0x%x\n", adc_result);
#endif

#if 0
    // 当软件不作为触发源时，软件也可以触发SOC采集
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_8);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_5);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 1, 2000);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x43);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER6);
    printf("0x%x\n", adc_result);
    while (1)
    {
        simple_delay(300);
        ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x43);
    }
#endif

#if 0
    // 测试计时器即使不用PWm功能也会触发ADC启动
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_8);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_8);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_8);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_8);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_8);
    puts("now start timer without PWM...");
    CPUTimer_disablePwm(CPUTimer0Regs);
    timer_setAndStart(CPUTimer0Regs, USER_DEFINED, 400, 0);
    simple_delay(300);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER1);
    printf("0x%x\n", adc_result);
#endif

#if 0
    // 测试用timer触发时，多个SOC是否可以正确采集多次
    // 一个触发源会将配置的所有SOC按次序采集一遍，所以在一次采集结束前进行采集会产生同步问题
    // 在采集前就配置好触发源，可能会导致在配置好部分SOC后触发源到达，前几次采集会只有部分SOC触发，后续的SOC采集的顺序可能会和预期不完全相同，但是顺序符合条件
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 2, 500);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_6);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_7);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_8);
    simple_delay(500);
    CPUTimer_disableTimer(CPUTimer0Regs);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_10);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_20);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_30);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_40);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_60);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_70);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_80);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(50);
    CPUTimer_disableTimer(CPUTimer0Regs);
    simple_delay(200);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER7);
    printf("result 7 is 0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER0);
    printf("result 0 is 0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER1);
    printf("result 1 is 0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER2);
    printf("result 2 is 0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER3);
    printf("result 3 is 0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER4);
    printf("result 4 is 0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER5);
    printf("result 5 is 0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER6);
    printf("result 6 is 0x%x\n", adc_result);
#endif

#if 0
    // 测试软件是否能正确产生EOC的中断,
    // 并且在用户清除ADCINT标志（在ADCINTFLG寄存器中）之前，不会再生成ADCIINT脉冲
    Interrupt_enable(PIC_GROUP9);
    ADC_setInterruptPulseMode(ADCA_REGS_BASE, ADC_PULSE_END_OF_CONV);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0);
    simple_delay(50);
    printf("intr num is %d\n", num_adc_intr);
#endif

#if 0
    // 测试软件多次触发中断,四个中断都触发一次
    ADC_setInterruptPulseMode(ADCA_REGS_BASE, ADC_PULSE_END_OF_CONV);
    Interrupt_enable(PIC_GROUP9);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER1);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER3);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER4);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER2);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER3);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER4, ADC_SOC_NUMBER4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN5, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN6, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN7, ADC_SAMPLE_WINDOW_5);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x1f);
    simple_delay(200);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x1f);
    printf("intr num is %d\n", num_adc_intr);
#endif

#if 0
    // 测试INTCONT为1时,是否每次EOC都会产生中断脉冲，连续中断与中断溢出测试
    ADC_setInterruptPulseMode(ADCA_REGS_BASE, ADC_PULSE_END_OF_CONV);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER2);
//    ADC_enableContinuousMode(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_disableContinuousMode(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER7);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE,ADC_SOC_NUMBER7);
    puts("now read adc in result7...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER7);
    printf("7 is 0x%x\n", adc_result);
    simple_delay(50);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER0);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE,ADC_SOC_NUMBER0);
    puts("now read adc in result0...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER0);
    printf("0 is 0x%x\n", adc_result);
    ADC_clearInterruptOverflowStatus(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_clearInterruptStatus(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE,ADC_SOC_NUMBER1);
    puts("now read adc again in result1...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER1);
    printf("1 is 0x%x\n", adc_result);
    //	ADC_clearInterruptStatus(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER4, ADC_SOC_NUMBER2);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE,ADC_SOC_NUMBER2);
    simple_delay(50);
    printf("intr num is %d\n", num_adc_intr);
#endif

#if 0
    // 测试硬件timer触发中断,隔一段时间打开中断连续模式
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    ADC_setInterruptPulseMode(ADCA_REGS_BASE, ADC_PULSE_END_OF_CONV);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_4);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 2, 50);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    ADC_enableContinuousMode(ADCA_REGS_BASE, ADC_INT_NUMBER4);
#endif

#if 0
    // 测试timer连续中断与中断溢出
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_setInterruptPulseMode(ADCA_REGS_BASE, ADC_PULSE_END_OF_CONV);
    ADC_enableContinuousMode(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    //	ADC_disableContinuousMode(ADCA_REGS_BASE);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_4);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 2, 50);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    x = ADC_getInterruptOverflowStatus(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    printf("intr num is %d and overflow status is %d\n", num_adc_intr, x);
    ADC_clearInterruptOverflowStatus(ADCA_REGS_BASE, ADC_INT_NUMBER2);
#endif

#if 0
    // 测试用timer触发时，多个SOC是否可以正确采集多通道来源的信号
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 2, 50);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    simple_delay(500);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER14, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN0, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER15, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER16, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER17, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER18, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER19, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN5, ADC_SAMPLE_WINDOW_5);
//    simple_delay(200);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER8, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN6, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER9, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN7, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    simple_delay(300);
#endif

#if 0
    // 测试后处理模块,读取延后SOC采集的时间戳
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER2, ADC_SOC_NUMBER6);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER4, ADC_SOC_NUMBER16);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_6);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_8);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_7);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_10);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER16, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_50);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x100fd);
    simple_delay(50);
    x = ADC_getPPBDelayTimeStamp(ADCA_REGS_BASE, ADC_PPB_NUMBER1);
    printf("delay TimeStamp is %d\n", x);
    x = ADC_getPPBDelayTimeStamp(ADCA_REGS_BASE, ADC_PPB_NUMBER2);
	printf("delay TimeStamp is %d\n", x);
	x = ADC_getPPBDelayTimeStamp(ADCA_REGS_BASE, ADC_PPB_NUMBER4);
	printf("delay TimeStamp is %d\n", x);
#endif

#if 0
    // 测试后处理模块,偏移量OFFREF是否正确工作
    ADC_disablePPBTwosComplement(ADCA_REGS_BASE, ADC_PPB_NUMBER1);
//	ADC_enablePPBTwosComplement(ADCA_REGS_BASE, ADC_PPB_NUMBER1);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER1);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER1, 0x1);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0x1);
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN7, ADC_SAMPLE_WINDOW_8);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x403);
    simple_delay(100);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER1, 0xf);
    simple_delay(10);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER2);
    simple_delay(50);
#endif

#if 0
    // 测试后处理模块,偏移量OFFCAL是否正确工作
//    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_16_0);
    ADC_disablePPBTwosComplement(ADCA_REGS_BASE, ADC_PPB_NUMBER1);
    //	ADC_enablePPBTwosComplement(ADCA_REGS_BASE);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER1);
    ADC_setPPBCalibrationOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER1, 0x3fa);
    simple_delay(300);
//    ADC_disableInterrupt(ADCA_REGS_BASE);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN18, ADC_SAMPLE_WINDOW_3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN18, ADC_SAMPLE_WINDOW_3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER13, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER16, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN7, ADC_SAMPLE_WINDOW_3);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x12007);
    simple_delay(100);
    ADC_setPPBCalibrationOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER1, 0xf);
    simple_delay(10);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER16);
    simple_delay(10);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x12006);
#endif

#if 0
    // 测试后处理模块,OFFREF和OFFCAL同时使用是否会正确交互
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER1);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER1, 0x5);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0x8);
    ADC_setPPBCalibrationOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER1, 0x3ff);
    ADC_setPPBCalibrationOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0x3fe);
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN7, ADC_SAMPLE_WINDOW_8);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x403);
//    simple_delay(100);
//    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER1, 0xf);
    simple_delay(10);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER0);
    simple_delay(50);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x403);
#endif

#if 0
    // 测试三个事件是否可以发生,发生后是否正确读取,能否正确清除,不考虑事件中断
    // 测试CBCEN功能是否正确
//	ADC_enablePPBEventCBCClear(ADCA_REGS_BASE, ADC_PPB_NUMBER1);
    ADC_disablePPBEventCBCClear(ADCA_REGS_BASE, ADC_PPB_NUMBER3);
    ADC_disablePPBTwosComplement(ADCA_REGS_BASE, ADC_PPB_NUMBER3);
    ADC_setPPBTripLimits(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x10, -0x08);
    ADC_enablePPBEvent(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x7);
    ADC_disablePPBEventInterrupt(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x7);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER3, ADC_SOC_NUMBER1);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x1);
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN18, ADC_SAMPLE_WINDOW_2);
    ADC_forceSOC(ADCA_REGS_BASE,ADC_SOC_NUMBER1);
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
#endif

#if 0
//    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_4_0);
    //验证多个PPB模块交互
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER3, ADC_SOC_NUMBER1);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0x5);		//-5
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x8);		//-8
    ADC_setPPBCalibrationOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0x3ff);	//+1
    ADC_setPPBCalibrationOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x3fe);	//+2
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN7, ADC_SAMPLE_WINDOW_8);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x403);
    simple_delay(50);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x403);
#endif

#if 0
    // 测试事件中断是否可以正确发生
    Interrupt_enable(PIC_GROUP3);
    ADC_setInterruptPulseMode(ADCA_REGS_BASE, ADC_PULSE_END_OF_CONV);
    ADC_disablePPBTwosComplement(ADCA_REGS_BASE, ADC_PPB_NUMBER2);
    ADC_setPPBTripLimits(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0x10, -0x08);
    ADC_enablePPBEvent(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0x7);
    ADC_enablePPBEventInterrupt(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0x7);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0xa);
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN7, ADC_SAMPLE_WINDOW_2);
    simple_delay(300);
#endif

#if 0
    // 测试多个ADC同时采集，timer触发
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER1);
    puts("now start adcB...");
    ADC_enableConverter(ADCB_REGS_BASE);
    simple_delay(200);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT1, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT1, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT1, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT1, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCB_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT1, ADC_CH_ADCIN6, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCB_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT1, ADC_CH_ADCIN6, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCB_REGS_BASE, ADC_SOC_NUMBER8, ADC_TRIGGER_CPU0_TINT1, ADC_CH_ADCIN6, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCB_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT1, ADC_CH_ADCIN6, ADC_SAMPLE_WINDOW_2);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer1Regs);
    CPUTimer_initPwm(CPUTimer1Regs, CPUTimer1PwmRegs, USER_DEFINED, 5, 1500);
    CPUTimer_enableTimer(CPUTimer1Regs);
    simple_delay(300);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER1);
    printf("0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCB_RESULT_BASE, ADC_SOC_NUMBER6);
    printf("0x%x\n", adc_result);
#endif

#if 0
    // 测试多个ADC同时触发中断，这个问题暂不处理,等中断修改完再处理
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    Interrupt_enable(PIC_GROUP3);
    puts("now start adcB...");
    ADC_enableConverter(ADCB_REGS_BASE);
    simple_delay(300);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER3);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER1);
    ADC_enableInterrupt(ADCB_REGS_BASE, ADC_INT_NUMBER3);
    ADC_setInterruptSource(ADCB_REGS_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_3);
    ADC_setupSOC(ADCB_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_3);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, FREE_RUNNING, 2, 50);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER1);
    printf("A is 0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCB_RESULT_BASE, ADC_SOC_NUMBER1);
    printf("B is 0x%x\n", adc_result);
    printf("adc intr num is %d\n", num_adc_intr);
#endif

#if 0
    // 测试连续采集模式，以及连续采集模式断电后的复位
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    AdcaRegs->ADCCTL.bit.MODE = 1;
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 1, 500);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(3000);
    puts("end timer or mode...");
    CPUTimer_disableTimer(CPUTimer0Regs);
    simple_delay(300);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(100);
    AdcaRegs->ADCCTL.bit.MODE = 0;
    simple_delay(100);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2);
    ADC_disableConverter(ADCA_REGS_BASE);
#endif

#if 0
    // 测试EPWM输入触发ADC
    u8 epwm_num = 2; // epwm3
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (epwm_num << 8));
    CpuSysRegs->PCLKCR0.bit.TBCLKSYNC = 0;
    pwm_gen_for_adc(epwm_num, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 10000 / 2, SYS_CLK / 10000 / 4, 0, 0, 1);
    gen_et_for_adc(epwm_num);
    CpuSysRegs->PCLKCR0.bit.TBCLKSYNC = 1;
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_EPWM3_SOCA, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_EPWM3_SOCA, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM3_SOCA, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM3_SOCA, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_EPWM3_SOCA, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_EPWM3_SOCA, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_EPWM3_SOCA, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_EPWM3_SOCA, ADC_CH_ADCIN5, ADC_SAMPLE_WINDOW_2);
    simple_delay(300);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER7);
    printf("0x%x\n", adc_result);
#endif

#if 0
    // 测试GPIO输入触发ADC
    simple_delay(200);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_GPIO, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_GPIO, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_GPIO, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    simple_delay(200);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER5);
    printf("0x%x\n", adc_result);
    XBAR_setInputPin(XBAR_INPUT5, XBAR_INPUT_GPIO5);
    simple_delay(1000);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER16, ADC_TRIGGER_GPIO, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER17, ADC_TRIGGER_GPIO, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER18, ADC_TRIGGER_GPIO, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER11, ADC_TRIGGER_GPIO, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER12, ADC_TRIGGER_GPIO, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_2);
    simple_delay(300);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER7);
    printf("0x%x\n", adc_result);
#endif

#if 0
    // 硬件触发采集SOC，连续的SOC与非连续采集
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 3000, 3000);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    ADC_disableInterrupt(ADCA_REGS_BASE);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER13, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER16, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN319);
    simple_delay(500);
#endif

#if 0
//测试复位
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
	simple_delay(200);
	ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x7);
	simple_delay(100);
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ADCA);
#endif

#if 0
    //由于有busy信号存在，不能随时更改输入通道，测试时注释掉，为了测试时序违例
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_60_0);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_40);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_40);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x3);
    simple_delay(1);
    AdcaRegs->ADCSOC0CTL.bit.CHSEL = ADC_CH_ADCIN5;
    AdcaRegs->ADCSOC1CTL.bit.CHSEL = ADC_CH_ADCIN5;
#endif

#if 0
    // 验证ADC复位后再次启动，是否正常
    ADC_disablePPBEventCBCClear(ADCA_REGS_BASE, ADC_PPB_NUMBER3);
    ADC_disablePPBTwosComplement(ADCA_REGS_BASE, ADC_PPB_NUMBER3);
    ADC_setPPBTripLimits(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x10, -0x08);
    ADC_enablePPBEvent(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x7);
    ADC_disablePPBEventInterrupt(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x7);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER3, ADC_SOC_NUMBER1);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x1);
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN18, ADC_SAMPLE_WINDOW_2);
    ADC_forceSOC(ADCA_REGS_BASE,ADC_SOC_NUMBER1);
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
    simple_delay(100);
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ADCA);
    simple_delay(500);
    ADC_enableConverter(ADCA_REGS_BASE);
    simple_delay(200);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_3);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x6);
#endif

#if 0
    // 验证ADC早期中断模式
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_8_0);
    ADC_setInterruptPulseMode(ADCA_REGS_BASE, ADC_PULSE_END_OF_ACQ_WIN);
//    ADC_setInterruptPulseMode(ADCA_REGS_BASE, ADC_PULSE_END_OF_CONV);
    ADC_enableContinuousMode(ADCA_REGS_BASE, ADC_INT_NUMBER2);
//    ADC_setInterruptCycleOffset(ADCA_REGS_BASE, 0x100);
//    ADC_setInterruptCycleOffset(ADCA_REGS_BASE, 0x1);
    ADC_setInterruptCycleOffset(ADCA_REGS_BASE, 0x0);
    Interrupt_enable(PIC_GROUP9);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER1);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER3);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER4);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER3);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER4, ADC_SOC_NUMBER4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_7);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN5, ADC_SAMPLE_WINDOW_30);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN6, ADC_SAMPLE_WINDOW_40);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN7, ADC_SAMPLE_WINDOW_50);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x1f);
    simple_delay(200);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x1f);
    printf("intr num is %d\n", num_adc_intr);
#endif
    while (1)
        ;
}
