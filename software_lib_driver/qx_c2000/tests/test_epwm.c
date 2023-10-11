#include "common.h"

#define EPWM_NUM 8

char int_flag[8] = { 0 };

// ======================================中断处理函数===================================================

static void epwm_tz_isr_common(char ch)
{
    printf("epwm%x_tz_isr\n", ch); // 充当时延，方便看波形
    struct EPWM_REGS *EPwmRegs = (struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);

    EPwmRegs->TZCLR.bit.INT = 1; // 清楚INT信号
    EPwmRegs->TZCLR.bit.OST = 1; // 清除OST信号
    EPwmRegs->TZCLR.bit.CBC = 1; // 清除CBC信号
    // EPWM_clearTripZoneFlag((int)EPwmRegs, EPWM_TZ_FLAG_DCBEVT1); // 只能清flg，清tz状态还得靠上面两个
    int_flag[ch] = 1;
}

// tz中断处理函数
__interrupt void epwm1_tz_isr(void)
{
    epwm_tz_isr_common(0);
}

__interrupt void epwm2_tz_isr(void)
{
    epwm_tz_isr_common(1);
}

__interrupt void epwm3_tz_isr(void)
{
    epwm_tz_isr_common(2);
}

__interrupt void epwm4_tz_isr(void)
{
    epwm_tz_isr_common(3);
}

__interrupt void epwm5_tz_isr(void)
{
    epwm_tz_isr_common(4);
}

__interrupt void epwm6_tz_isr(void)
{
    epwm_tz_isr_common(5);
}

__interrupt void epwm7_tz_isr(void)
{
    epwm_tz_isr_common(6);
}

__interrupt void epwm8_tz_isr(void)
{
    epwm_tz_isr_common(7);
}

// et中断处理函数
static void epwm1_isr_common(char ch)
{
    printf("epwm%x_isr\n", ch);
    struct EPWM_REGS *EPwmRegs = (struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);

    EPwmRegs->ETCLR.bit.INT = 1; // 清除ET的INT信号
    int_flag[ch]            = 1;
}

__interrupt void epwm1_isr(void)
{
    epwm1_isr_common(0);
}

__interrupt void epwm2_isr(void)
{
    epwm1_isr_common(1);
}

__interrupt void epwm3_isr(void)
{
    epwm1_isr_common(2);
}

__interrupt void epwm4_isr(void)
{
    epwm1_isr_common(3);
}

__interrupt void epwm5_isr(void)
{
    epwm1_isr_common(4);
}

__interrupt void epwm6_isr(void)
{
    epwm1_isr_common(5);
}

__interrupt void epwm7_isr(void)
{
    epwm1_isr_common(6);
}

__interrupt void epwm8_isr(void)
{
    epwm1_isr_common(7);
}

// ==============================================================================================

void pwm_normal_gen(u8 ch, u8 count_mode, u16 tbprd, u16 cmp, u16 tbphs, u8 int_type, u32 p_flag)
{
    // volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch *0x200);
    // TB
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    EPWM_setTimeBaseCounterMode(epwm_base, count_mode); // 计数模式
    // EPWM_enablePhaseShiftLoad(uint32_t base)   // 不从TBPHS加载TBCTR
    EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_SHADOW_LOAD); // 启用影子模式读写TBPRD
    // EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_DIRECT_LOAD);     // 启用直接模式读写TBPRD
    // epwm->TBCTL.bit.SYNCOSEL = 0;        // 禁用EPWMxSYNCO信号，该信号拉高后会使CTR跳转为TBPHS
    EPWM_setSyncOutPulseMode(epwm_base, EPWM_SYNC_OUT_PULSE_ON_EPWMxSYNCIN);
    // SWFSYNC，软件强制同步脉冲，应该是动态的，先不管
    // epwm->TBCTL.bit.HSPCLKDIV = 1;       /* TBCLK = SYSTEM_OUT_CLK/(2 * HSPCLKDIV *
    // 2^CLKDIV)高速基准时钟，为0时只由CLKDIV决定 */ epwm->TBCTL.bit.CLKDIV    = 2; // TBCLK = SYSTEM_OUT_CLK/(2^CLKDIV)
    EPWM_setClockPrescaler(epwm_base, 2, 1);
    // PHSDIR，相位方向位，仅在递增计数时使用
    // FREE_SOFT，仿真模式自由运行

    // epwm->TBPHS.bit.TBPHS     = tbphs;
    EPWM_setPhaseShift(epwm_base, tbphs); // 相位偏移
    // epwm->TBPRD               = tbprd;
    EPWM_setTimeBasePeriod(epwm_base, tbprd); // 时基周期设置
    // epwm->TBCTR               = 0;
    EPWM_setTimeBaseCounter(epwm_base, 0); // 清零时基计数寄存器

    // CC
    // epwm->CMPCTL.bit.SHDWAMODE = 0;
    // epwm->CMPCTL.bit.SHDWBMODE = 0;
    // epwm->CMPCTL.bit.LOADAMODE = 0;
    // epwm->CMPCTL.bit.LOADBMODE = 0;
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_C, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_D, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    // epwm->CMPA.bit.CMPA        = cmp;
    // epwm->CMPB.bit.CMPB        = cmp / 2;
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_A, cmp);
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_B, cmp / 2);
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_C, 1);
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_D, 2);

    // AQ
    // 对应赋值1则触发输出0，对应赋值1则触发输出1
    // epwm->AQCTLA.bit.CAU = 2; // 当CTR=CMPA且Up增计数时，EPWM1A输出高电平
    // epwm->AQCTLA.bit.CAD = 1; // 当CTR=CMPA且Down减计数时，EPWM1A输出低电平
    // epwm->AQCTLB.bit.CAU = 2; // 当CTR=CMPA且Up增计数时，EPWM1B输出高电平
    // epwm->AQCTLB.bit.CAD = 1; // 当CTR=CMPA且Down减计数时，EPWM1B输出低电平
    EPWM_setActionQualifierAction(epwm_base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(epwm_base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    // DB
    // epwm->DBCTL.bit.OUT_MODE = 0; // 死区完全旁路
    // 死区没有enable函数，只要不配置就没有

    // PC
    // EPWM_enableChopper(epwm_base); // 斩波器完全旁路

    // 是否打开中断触发
    if (int_type)
        Interrupt_enable(INT_EPWM1_TZ + ch);
    else
        Interrupt_disable(INT_EPWM1_TZ + ch);

    if (p_flag)
    {
        printf("epwm test -> ch:%d, count_mode:%d, tbprd:%d, cmp:%d, tbphs:%d, int_type:%d\n", ch, count_mode, tbprd,
            cmp, tbphs, int_type);
    }
}

void pwm_denormal_gen(u8 ch, u8 count_mode, u16 tbprd, u16 cmp, u16 tbphs, u8 int_type, u32 p_flag)
{
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);
    // TB
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    EPWM_setTimeBaseCounterMode(epwm_base, count_mode); // 计数模式
    // EPWM_enablePhaseShiftLoad(epwm_base);   // 不从TBPHS加载TBCTR
    // EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_SHADOW_LOAD);  // 启用影子模式读写TBPRD
    EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_DIRECT_LOAD); // 启用直接模式读写TBPRD
    // EPWM_setSyncOutPulseMode(epwm_base, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);//cnt eq zero 输出同步
    EPWM_setClockPrescaler(epwm_base, 2, 1);
    // PHSDIR，相位方向位，仅在递增计数时使用
    // FREE_SOFT，仿真模式自由运行

    EPWM_setPhaseShift(epwm_base, tbphs);     // 相位偏移
    EPWM_setTimeBasePeriod(epwm_base, tbprd); // 时基周期设置
    EPWM_setTimeBaseCounter(epwm_base, 0);    // 清零时基计数寄存器

    // CC
    // epwm->CMPCTL.bit.SHDWAMODE = 0;
    // epwm->CMPCTL.bit.SHDWBMODE = 0;
    epwm->CMPCTL.bit.SHDWAMODE = 1; // 不启用影子模式
    epwm->CMPCTL.bit.SHDWBMODE = 1; // 不启用影子模式
    epwm->CMPCTL.bit.LOADAMODE = 0;
    epwm->CMPCTL.bit.LOADBMODE = 0;
    epwm->CMPA.bit.CMPA        = cmp;
    epwm->CMPB.bit.CMPB        = cmp / 2;

    // AQ
    // 对应赋值1则触发输出0，对应赋值1则触发输出1
    epwm->AQCTLA.bit.CAU = 2; // 当CTR=CMPA且Up增计数时，EPWM1A输出高电平
    epwm->AQCTLA.bit.CAD = 1; // 当CTR=CMPA且Down减计数时，EPWM1A输出低电平
    epwm->AQCTLB.bit.CBU = 2; // 当CTR=CMPA且Up增计数时，EPWM1B输出高电平
    epwm->AQCTLB.bit.CBD = 1; // 当CTR=CMPA且Down减计数时，EPWM1B输出低电平

    // DB
    epwm->DBCTL.bit.OUT_MODE = 0; // 死区完全旁路

    // PC
    // EPWM_enableChopper(epwm_base); // 斩波器完全旁路

    // 是否打开中断触发
    if (int_type)
        Interrupt_enable(INT_EPWM1 + ch);
    else
        Interrupt_disable(INT_EPWM1 + ch);

    if (p_flag)
        printf("epwm test -> ch:%d, count_mode:%d, tbprd:%d, cmp:%d, tbphs:%d, int_type:%d\n", ch, count_mode, tbprd,
            cmp, tbphs, int_type);
}

void pwm_aq(u8 ch)
{
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    EPWM_setActionQualifierSWAction(epwm_base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW); // 触发SW事件时的响应
    EPWM_setActionQualifierSWAction(epwm_base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_TOGGLE);
    // AQCSFRC的影子模式，在eqprd时写入
    EPWM_setActionQualifierContSWForceShadowMode(epwm_base, EPWM_AQ_SW_SH_LOAD_ON_CNTR_PERIOD);
}

void pwm_dead_band_gen(u8 ch, u16 dead_time)
{
    uint32_t epwm_base              = EPWM1_BASE + ch * 0x200;
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);
    // DB
    // epwm->DBCTL.bit.OUT_MODE = 0b11;         // 使能上升沿和下降沿信号
    EPWM_setDeadBandDelayMode(epwm_base, EPWM_DB_RED, 1);
    EPWM_setDeadBandDelayMode(epwm_base, EPWM_DB_FED, 1);
    // epwm->DBCTL.bit.IN_MODE  = 0b10; // 上升沿和下降沿死区以哪一路作为参考，10-》EPWM1A上升沿，EPWM1B下降沿作为参考
    EPWM_setRisingEdgeDeadBandDelayInput(epwm_base, EPWM_DB_INPUT_EPWMA);
    EPWM_setFallingEdgeDeadBandDelayInput(epwm_base, EPWM_DB_INPUT_EPWMB);
    // epwm->DBCTL.bit.POLSEL   = 0b10;         // EPWM1B极性反转
    EPWM_setDeadBandDelayPolarity(epwm_base, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW); // 不太懂逻辑，但结果没问题
    // epwm->DBRED.all          = dead_time; // 死区延时配置
    // epwm->DBFED.all          = dead_time; // 死区延时配置
    EPWM_setFallingEdgeDelayCountShadowLoadMode(epwm_base, EPWM_FED_LOAD_ON_CNTR_PERIOD); // 启用影子模式，eq_prd装载
    EPWM_setRisingEdgeDelayCountShadowLoadMode(epwm_base, EPWM_RED_LOAD_ON_CNTR_PERIOD);
    EPWM_setRisingEdgeDelayCount(epwm_base, dead_time);
    EPWM_setFallingEdgeDelayCount(epwm_base, dead_time);
    EPWM_setDeadBandControlShadowLoadMode(epwm_base, EPWM_DB_LOAD_ON_CNTR_PERIOD);
    printf("epwm test -> ch:%d, dead_time:%d\n", ch, dead_time);
}

void pwm_chopper_gen(u8 ch, u16 oshtw, u16 pcfreq, u16 pcduty)
{
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    // volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch *0x200);
    // PC
    // epwm->PCCTL.bit.CHPEN = 1;        // 启用斩波功能
    // epwm->PCCTL.bit.OSHTWTH = oshtw;  // 设置第一个波的宽度，8/oshtw个epwm周期
    // epwm->PCCTL.bit.CHPFREQ = pcfreq; // 设置频率，每个tbclk周期被分为freq*8个周期
    // epwm->PCCTL.bit.CHPDUTY = pcduty; // 设置psclk的占空比

    EPWM_enableChopper(epwm_base);
    EPWM_setChopperFirstPulseWidth(epwm_base, oshtw);
    EPWM_setChopperFreq(epwm_base, pcfreq);
    EPWM_setChopperDutyCycle(epwm_base, pcduty);

    printf("epwm test -> ch:%d, oshtw:%d, pcfreq:%d, pcduty:%d\n", ch, oshtw, pcfreq, pcduty);
}

void pwm_trip_osht(u8 ch, u8 int_type)
{
    uint32_t epwm_base              = EPWM1_BASE + ch * 0x200;
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);
    // epwm->TZCTL.bit.TZA = 0;  //触发错误事件时强制EPWMA高阻
    // epwm->TZCTL.bit.TZB = 1;  //触发错误事件时强制EPWMB拉高
    EPWM_setTripZoneAction(epwm_base, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_HIGH_Z);
    EPWM_setTripZoneAction(epwm_base, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_HIGH);
    // epwm->TZSEL.bit.OSHT1 = 1;  //使能TZ1 OSHT错误联防，frc无论是否使能，都会触发
    EPWM_enableTripZoneSignals(epwm_base, EPWM_TZSEL_OSHT1);
    if (int_type)
        // epwm->TZEINT.bit.OST = int_type;//使能or禁止OSHT中断
        EPWM_enableTripZoneInterrupt(epwm_base, EPWM_TZEINT_OST);
}

void pwm_trip_cbc(u8 ch, u8 int_type)
{
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    // volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch *0x200);

    // epwm->TZCTL.bit.TZA = 0; // 触发错误事件时强制EPWMA高阻
    // epwm->TZCTL.bit.TZB = 1; // 触发错误事件时强制EPWMB拉高
    EPWM_setTripZoneAction(epwm_base, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_HIGH_Z);
    EPWM_setTripZoneAction(epwm_base, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_HIGH);
    // epwm->TZSEL.bit.CBC1 = 1; // 使能TZ1 CBC错误联防，frc无论是否使能，都会触发
    EPWM_enableTripZoneSignals(epwm_base, EPWM_TZSEL_CBC1);
    if (int_type)
        // epwm->TZEINT.bit.OST = int_type; // 使能or禁止OSHT中断
        EPWM_enableTripZoneInterrupt(epwm_base, EPWM_TZEINT_CBC);
}

void pwm_trip_in(u8 ch)
{
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    XBAR_setInputPin(XBAR_INPUT2, XBAR_INPUT_GPIO2); // 需配合硬件激励
    EPWM_setTripZoneAction(epwm_base, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_HIGH_Z);
    EPWM_setTripZoneAction(epwm_base, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_HIGH);
    EPWM_enableTripZoneSignals(epwm_base, EPWM_TZSEL_OSHT2); // 使能OST2错误联防
    // EPWM_enableTripZoneSignals(epwm_base, EPWM_TZSEL_CBC2);//使能CBC2错误联防

    EPWM_enableTripZoneAdvAction(epwm_base);                                                       // 使能拓展TZCTL2
    EPWM_setTripZoneAdvAction(epwm_base, EPWM_TZ_ADV_ACTION_EVENT_TZA_D, EPWM_TZ_ADV_ACTION_HIGH); // 任意输入直接拉高
}

void pwm_et(u8 ch)
{
    uint32_t epwm_base              = EPWM1_BASE + ch * 0x200;
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);

    // epwm->ETSEL.bit.INTSEL = 1;  // 使能eq_zero事件
    // epwm->ETSEL.bit.SOCASEL = 2; // 使能eq_zero事件
    // epwm->ETSEL.bit.SOCBSEL = 1; // 使能eq_zero事件
    EPWM_setInterruptSource(epwm_base, EPWM_INT_TBCTR_ZERO);
    EPWM_setADCTriggerSource(epwm_base, EPWM_SOC_A, EPWM_SOC_TBCTR_PERIOD);
    EPWM_setADCTriggerSource(epwm_base, EPWM_SOC_B, EPWM_SOC_TBCTR_D_CMPD);

    // epwm->ETSEL.bit.SOCAEN = 1; // 使能SOCA输出
    // epwm->ETSEL.bit.SOCBEN = 1; // 使能SOCA输出
    // epwm->ETSEL.bit.INTEN = 1;  // 使能中断
    EPWM_enableInterrupt(epwm_base);
    EPWM_enableADCTrigger(epwm_base, EPWM_SOC_A);
    EPWM_enableADCTrigger(epwm_base, EPWM_SOC_B);

    // epwm->ETPS.bit.INTPRD = 3;  //每发生3次事件都产生产生一次中断
    // epwm->ETPS.bit.SOCAPRD = 3; //没发生3次事件产生一个SOCA脉冲
    // epwm->ETPS.bit.SOCBPRD = 3;
    EPWM_setInterruptEventCount(epwm_base, 3); // 这个函数好像只会设置intprd2，不过不影响
    EPWM_setADCTriggerEventPrescale(epwm_base, EPWM_SOC_A, 15); // 同上
    EPWM_setADCTriggerEventPrescale(epwm_base, EPWM_SOC_B, 15); // 同上

    EPWM_enableADCTriggerEventCountInit(epwm_base, EPWM_SOC_A);
    epwm->ETCNTINIT.bit.SOCAINIT = 8; // 同步信号触发时，soca的计数初始化为8
}

void pwm_dc(u8 ch, u16 offset, u16 window, EPWM_DigitalCompareEdgeFilterMode edgemode, u16 count)
{
    // 需配合硬件激励
    XBAR_setInputPin(XBAR_INPUT6, XBAR_INPUT_GPIO6);
    uint32_t epwm_base              = EPWM1_BASE + ch * 0x200;
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);

    // epwm->DCTRIPSEL.bit.DCALCOMPSEL = 0; // TRIPIN0
    // epwm->DCTRIPSEL.bit.DCAHCOMPSEL = 1; // TRIPIN1
    // epwm->DCTRIPSEL.bit.DCBLCOMPSEL = 4; // TRIPIN5
    // epwm->DCTRIPSEL.bit.DCBHCOMPSEL = 5; // TRIPIN6
    EPWM_selectDigitalCompareTripInput(epwm_base, EPWM_DC_TRIP_TRIPIN1, EPWM_DC_TYPE_DCAL);
    EPWM_selectDigitalCompareTripInput(epwm_base, EPWM_DC_TRIP_TRIPIN2, EPWM_DC_TYPE_DCAH);
    EPWM_selectDigitalCompareTripInput(epwm_base, EPWM_DC_TRIP_TRIPIN5, EPWM_DC_TYPE_DCBL);
    EPWM_selectDigitalCompareTripInput(epwm_base, EPWM_DC_TRIP_TRIPIN6, EPWM_DC_TYPE_DCBH);

    // epwm->TZDCSEL.bit.DCAEVT1 = 2;  //DCAH = high时触发DCAEVT1
    // epwm->TZDCSEL.bit.DCBEVT1 = 2; //DCBH = high时触发DCBEVT1
    EPWM_setTripZoneDigitalCompareEventCondition(epwm_base, EPWM_TZ_DC_OUTPUT_B1, EPWM_TZ_EVENT_DCXH_HIGH);
    EPWM_setTripZoneDigitalCompareEventCondition(epwm_base, EPWM_TZ_DC_OUTPUT_A1, EPWM_TZ_EVENT_DCXH_HIGH);

    // 配置空窗
    // epwm->DCFCTL.bit.PULSESEL = 0; //offset对齐到ctr_eq_zero；ctr_eq_prd清掉ctr
    EPWM_setDigitalCompareBlankingEvent(epwm_base, EPWM_DC_WINDOW_START_TBCTR_ZERO);

    // epwm->DCFCTL.bit.BLANKE = 1; //使能blank
    EPWM_enableDigitalCompareBlankingWindow(epwm_base);

    // epwm->DCFOFFSET = offset;  //空窗偏移
    // epwm->DCFWINDOW = window;  //空窗期长度
    EPWM_setDigitalCompareWindowOffset(epwm_base, offset);
    EPWM_setDigitalCompareWindowLength(epwm_base, window);

    // 配置边沿过滤器
    // epwm->DCFCTL.bit.EDGEMODE = edgemode;
    // epwm->DCFCTL.bit.EDGECOUNT = count;  //每六个下降的dcf blank sel out信号产生一次脉冲
    // epwm->DCFCTL.bit.EDGEFILTSEL = 1; //启用边沿过滤器？
    EPWM_setDigitalCompareEdgeFilterMode(epwm_base, edgemode);
    EPWM_setDigitalCompareEdgeFilterEdgeCount(epwm_base, count);
    EPWM_enableDigitalCompareEdgeFilter(epwm_base);

    // epwm->DCFCTL.bit.SRCSEL = 0b10; //过滤器针对dcbevt1
    EPWM_setDigitalCompareFilterInput(epwm_base, EPWM_DC_WINDOW_SOURCE_DCBEVT1);

    // epwm->VCAPCTL.bit.TRIGSEL = 1;
    // epwm->VCAPCTL.bit.VCAPE = 1; //每个prd都会复位边沿过滤，看图
    EPWM_setValleyTriggerSource(epwm_base, EPWM_VALLEY_TRIGGER_EVENT_CNTR_ZERO);
    EPWM_enableValleyCapture(epwm_base);

    EPWM_setValleyTriggerEdgeCounts(epwm_base, 2, 5); // 配置边沿过滤的延迟
    EPWM_setValleySWDelayValue(epwm_base, 32);        // 设置软件延迟
    EPWM_setValleyDelayDivider(
        epwm_base, EPWM_VALLEY_DELAY_MODE_VCNT_DELAY_SHIFT_2_SW_DELAY); // HWVDELVAL = VCNTVAL>>2+SWVDELVAL
    EPWM_enableValleyHWDelay(epwm_base);                                // 使能延迟

    // 配置捕获器
    epwm->DCCAPCTL.bit.CAPMODE = 1; // 手动清除，没有对应函数
    // epwm->DCCAPCTL.bit.SHDWMODE = 0; //启用影子模式
    // epwm->DCCAPCTL.bit.CAPE = 1;  //使能捕获器

    EPWM_setDigitalCompareCounterShadowMode(epwm_base, 1);
    EPWM_enableDigitalCompareCounterCapture(epwm_base);

    // epwm->DCACTL.bit.EVT1SRCSEL = 0;//DEAVET1信号源为DCAEVT1，旁路filter
    // epwm->DCBCTL.bit.EVT1SRCSEL = 1;//DCBEVT1信号源为DCEVTFTLT
    EPWM_setDigitalCompareEventSource(epwm_base, EPWM_DC_MODULE_A, EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);
    EPWM_setDigitalCompareEventSource(epwm_base, EPWM_DC_MODULE_B, EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_FILT_SIGNAL);

    // epwm->DCBCTL.bit.EVT1SOCE = 1; //同时给出DCBEVT1.soc信号
    EPWM_enableDigitalCompareADCTrigger(epwm_base, EPWM_DC_MODULE_B);

    EPWM_enableDigitalCompareSyncEvent(epwm_base, EPWM_DC_MODULE_B); // 使能sync输出
}

void pwm_sync(u8 ch)
{
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    EPWM_enablePhaseShiftLoad(epwm_base); // 使能同步信号调整相位

    // EPWM_enableOneShotSync(epwm_base);  //使能osht同步信号
    // EPWM_startOneShotSync(epwm_base);  //允许传播，不明白具体功能，效果来说，这俩置为后oshtsyncout会等于swfsync

    EPWM_setSyncOutPulseMode(epwm_base, EPWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_C); // 设置同步信号输出模式

    EPWM_selectPeriodLoadEvent(epwm_base, EPWM_SHADOW_LOAD_MODE_SYNC); // 触发同步信号时从影子加载PRD
    EPWM_setCounterCompareShadowLoadMode(
        epwm_base, EPWM_COUNTER_COMPARE_C, EPWM_COMP_LOAD_ON_SYNC_ONLY); // 触发同步信号时从影子加载CMPC

    SysCtl_enableExtADCSOCSource(SYSCTL_ADCSOCOUTSELECT_PWM2SOCAEN); // 使能设置ADC src为 epwm_ch1
    SysCtl_enableExtADCSOCSource(SYSCTL_ADCSOCOUTSELECT_PWM3SOCBEN); // 使能设置ADC src为 epwm_ch1
}

void pwm_lock(u8 ch)
{
    // //epwmlock寄存器取消
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + 0 * 0x200);
    uint32_t epwm_base              = EPWM1_BASE + ch * 0x200;
    SysCtl_enableExtADCSOCSource(SYSCTL_ADCSOCOUTSELECT_PWM1SOCAEN);
    int delay = 1000;
    while (delay--)
        ;
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_EPWM7, SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT);
    delay = 1000;
    while (delay--)
        ;
    SysCtl_lockSyncSelect(); // 上锁，阻挡一次写操作
    delay = 1000;
    while (delay--)
        ;
    SysCtl_lockExtADCSOCSelect(); // 上锁，阻挡一次写操作
    delay = 1000;
    while (delay--)
        ;
    SysCtl_enableExtADCSOCSource(SYSCTL_ADCSOCOUTSELECT_PWM2SOCAEN);
    delay = 1000;
    while (delay--)
        ;
    SysCtl_enableExtADCSOCSource(SYSCTL_ADCSOCOUTSELECT_PWM2SOCAEN);
    delay = 1000;
    while (delay--)
        ;
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP1, SYSCTL_SYNC_IN_SRC_EPWM7SYNCOUT); // 预期被阻止
    delay = 1000;
    while (delay--)
        ;
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP1, SYSCTL_SYNC_IN_SRC_EPWM7SYNCOUT); // 预期成功写入
}

void pwm_tz_aq(u8 ch)
{
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    EPWM_setTimeBaseCounterMode(epwm_base, 2);                  // 计数模式
    EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_SHADOW_LOAD); // 启用影子模式读写TBPRD
    EPWM_setSyncOutPulseMode(epwm_base, EPWM_SYNC_OUT_PULSE_ON_EPWMxSYNCIN);
    EPWM_setClockPrescaler(epwm_base, 2, 1);
    EPWM_setTimeBasePeriod(epwm_base, SYS_CLK / 100000 / 2);                            // 时基周期设置
    EPWM_setTimeBaseCounter(epwm_base, 0);                                              // 清零时基计数寄存器
    EPWM_setActionQualifierT1TriggerSource(epwm_base, EPWM_AQ_TRIGGER_EVENT_TRIG_TZ_2); // 输入源选择tz2
    EPWM_setActionQualifierAction(epwm_base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_T1_COUNT_UP);
    EPWM_setActionQualifierAction(epwm_base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_T1_COUNT_DOWN);
    EPWM_setActionQualifierAction(epwm_base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_T1_COUNT_UP);
    EPWM_setActionQualifierAction(epwm_base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_T1_COUNT_DOWN);
    XBAR_setInputPin(XBAR_INPUT2, XBAR_INPUT_GPIO2); // 接上GPIO2输入，需培养硬件激励使用
}

void pwm_gld(u8 ch)
{
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;

    EPWM_enableGlobalLoad(epwm_base); // 使能全局装载

    EPWM_setGlobalLoadTrigger(epwm_base, EPWM_GL_LOAD_PULSE_CNTR_PERIOD); // 配置事件位eq_prd
    // EPWM_setGlobalLoadTrigger(epwm_base, EPWM_GL_LOAD_PULSE_GLOBAL_FORCE);//配置事件为，gldctl2中CFRCLD位置1
    EPWM_setGlobalLoadEventPrescale(epwm_base, 6); // 6次事件触发一次全局装载

    EPWM_enableGlobalLoadOneShotMode(epwm_base); // 激活osht模式，只有在gldctl2中oshtld位中写入1方可装载

    EPWM_enableGlobalLoadRegisters(epwm_base, EPWM_GLDCFG_CMPA_CMPAHR); // 使能cmpa全局装载
}

void test_normal()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // 增减计数, 10KHz, 占空比50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        SysCtl_TbClkSyncToggle(1);
        while (1)
            ;
    }
}

void test_denormal()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // 增减计数, 10KHz, 占空比50%
        pwm_denormal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        SysCtl_TbClkSyncToggle(1);
        // 影子寄存器
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;
        int delay          = 100;
        while (delay--)
            ;
        volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i * 0x200);
        epwm->CMPA.bit.CMPA             = SYS_CLK / 100000 / 8;
        epwm->CMPB.bit.CMPB             = SYS_CLK / 100000 / 16;
        delay                           = 100;
        while (delay--)
            ;
        epwm->TBPRD = SYS_CLK / 100000 / 4;
        while (1)
            ;
    }
}

void test_aq()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // 增减计数, 10KHz, 占空比50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        pwm_aq(i);
        SysCtl_TbClkSyncToggle(1);
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;
        int delay          = 100;
        while (delay--)
            ;
        EPWM_forceActionQualifierSWAction(epwm_base, EPWM_AQ_OUTPUT_A); // 触发SW事件时的响应(单次)
        //  EPWM_setActionQualifierContSWForceAction(epwm_base, EPWM_AQ_OUTPUT_A, EPWM_AQ_SW_OUTPUT_LOW);
        ////触发SW事件时的响应(持续)
        delay = 100;
        while (delay--)
            ;
        EPWM_forceActionQualifierSWAction(epwm_base, EPWM_AQ_OUTPUT_B);
        //  EPWM_setActionQualifierContSWForceAction(epwm_base, EPWM_AQ_OUTPUT_B, EPWM_AQ_SW_OUTPUT_HIGH);
        while (1)
            ;
    }
}

void test_db()
{
    SysCtl_TbClkSyncToggle(0);
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // 增减计数, 10KHz, 占空比50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        pwm_dead_band_gen(i, 16);
        SysCtl_TbClkSyncToggle(1);
        volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i * 0x200);
        uint32_t epwm_base              = EPWM1_BASE + i * 0x200;
        int delay                       = 1000;
        while (delay--)
            ;
        EPWM_setRisingEdgeDelayCount(epwm_base, 20);
        EPWM_setFallingEdgeDelayCount(epwm_base, 20);
        delay = 1000;
        while (delay--)
            ;
        EPWM_setDeadBandOutputSwapMode(epwm_base, EPWM_DB_OUTPUT_A, 1); // 验证输出交换
        delay = 1000;
        while (delay--)
            ;
        EPWM_setDeadBandOutputSwapMode(epwm_base, EPWM_DB_OUTPUT_B, 1);
        delay = 1000;
        while (delay--)
            ;
        epwm->DBCTL.bit.HALFCYCLE = 1; // 验证半周期
        delay                     = 1000;
        while (delay--)
            ;
        epwm->DBCTL.bit.POLSEL = 0b11; // 验证影子模式
        while (1)
            ;
    }
}

void test_pc()
{
    SysCtl_TbClkSyncToggle(0);
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // 增减计数, 10KHz, 占空比50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        pwm_chopper_gen(i, 3, 1, 3);
        SysCtl_TbClkSyncToggle(1);
    }
}

void test_db_pc()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // 增减计数, 10KHz, 占空比50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        pwm_dead_band_gen(i, 24);
        pwm_chopper_gen(i, 3, 1, 3);
        SysCtl_TbClkSyncToggle(1);
    }
}

void test_tz_osht()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // 增减计数, 10KHz, 占空比50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        pwm_trip_osht(i, 0);
        SysCtl_TbClkSyncToggle(1);
        int delay = 1000;
        while (delay--)
            ;
        //  volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i *0x200);
        //  epwm->TZFRC.bit.OST = 1;//强制触发OST事件
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;
        //  EPWM_forceTripZoneEvent(epwm_base, EPWM_TZFRC_OST);
        while (1)
            ;
    }
}

void test_tz_cbc()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // 增减计数, 10KHz, 占空比50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        pwm_trip_cbc(i, 0);
        SysCtl_TbClkSyncToggle(1);
        int delay = 100;
        while (delay--)
            ;
        volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i * 0x200);
        //  epwm->TZFRC.bit.CBC = 1;//强制触发CBC事件
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;
        EPWM_forceTripZoneEvent(epwm_base, EPWM_TZFRC_CBC);
        while (1)
            ;
    }
}

void test_tz_osht_int()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // 增减计数, 10KHz, 占空比50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 1, 1);
        pwm_trip_osht(i, 1);
        SysCtl_TbClkSyncToggle(1);
        int delay = 100;
        while (delay--)
            ;
        // volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i *0x200);
        // epwm->TZFRC.bit.OST = 1;//强制触发OST事件
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;
        EPWM_forceTripZoneEvent(epwm_base, EPWM_TZFRC_OST);
        while (int_flag[i] == 0)
            ;
    }
}

void test_tz_cbc_int()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // 增减计数, 10KHz, 占空比50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 1, 1);
        pwm_trip_cbc(i, 1);
        SysCtl_TbClkSyncToggle(1);
        int delay = 100;
        while (delay--)
            ;
        volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i * 0x200);
        //  epwm->TZFRC.bit.CBC = 1;//强制触发OST事件
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;
        EPWM_forceTripZoneEvent(epwm_base, EPWM_TZFRC_CBC);
        while (1)
            ;
    }
}

void test_et_int()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        Interrupt_enable(INT_EPWM1 + i);
        // 增减计数, 10KHz, 占空比50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 0);
        pwm_et(i);
        SysCtl_TbClkSyncToggle(1);
        int delay = 100;
        while (delay--)
            ;
        // volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i *0x200);
        // epwm->TZFRC.bit.OST = 1;//强制触发OST事件
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;
        EPWM_forceEventTriggerInterrupt(epwm_base);
        while (int_flag[i] == 0)
            ;
    }
}

void test_tz_in()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // 增减计数, 10KHz, 占空比50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 1, 1);
        pwm_trip_in(i);
        SysCtl_TbClkSyncToggle(1);

        uint32_t epwm_base              = EPWM1_BASE + i * 0x200;
        volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i * 0x200);
        int delay                       = 1000;
        while (delay--)
            ;
        u16 flg = EPWM_getOneShotTripZoneFlagStatus(epwm_base);
        //  u16 flg = EPWM_getCycleByCycleTripZoneFlagStatus(epwm_base);
        printf("flg = %d\n", flg);
        EPWM_clearOneShotTripZoneFlag(epwm_base, flg);
        //  EPWM_clearCycleByCycleTripZoneFlag(epwm_base, flg);
        epwm->TZCLR.bit.OST = 1; // 清除OST信号
        while (1)
            ;
    }
}

void test_et()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // 增减计数, 10KHz, 占空比50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        //      pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 1, 1);
        pwm_et(i);
        SysCtl_TbClkSyncToggle(1);
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;
        //      volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i *0x200);
        int delay = 100;
        while (delay--)
            ;
        EPWM_forceADCTrigger(epwm_base, EPWM_SOC_A); // 强制触发SOCA脉冲
        delay = 100;
        while (delay--)
            ;
        EPWM_clearADCTriggerFlag(epwm_base, EPWM_SOC_A);
        EPWM_forceADCTrigger(epwm_base, EPWM_SOC_B); // 强制触发SOCB脉冲
        delay = 100;
        while (delay--)
            ;
        EPWM_clearADCTriggerFlag(epwm_base, EPWM_SOC_B);
        delay = 100;
        while (delay--)
            ;
        EPWM_forceADCTriggerEventCountInit(epwm_base, EPWM_SOC_A); // 强制soca初始化counter
        while (1)
            ;
    }
}

void test_dc()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // 增减计数, 10KHz, 占空比50%
        //  pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 10000 / 2, SYS_CLK / 10000 / 4, 0, 1, 1);
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 10000 / 2, SYS_CLK / 10000 / 4, 0, 0, 1);
        // 频率得低一点，不然复位信号太频繁

        uint32_t epwm_base = EPWM1_BASE + i * 0x200;

        EPWM_setTripZoneAction(epwm_base, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_HIGH_Z);
        EPWM_setTripZoneAction(epwm_base, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_HIGH_Z);
        EPWM_enableTripZoneSignals(epwm_base, EPWM_TZSEL_DCBEVT1);
        //  EPWM_enableTripZoneInterrupt(epwm_base, EPWM_TZEINT_DCBEVT1);

        pwm_dc(i, 80, 640, EPWM_DC_EDGEFILT_MODE_FALLING, 4);
        SysCtl_TbClkSyncToggle(1);
        int delay = 1000;
        while (delay--)
            ;
        volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i * 0x200);
        epwm->DCCAPCTL.bit.CAPCLR       = 1;
        delay                           = 1000;
        while (delay--)
            ;
        //  EPWM_enableDigitalCompareWindowInverseMode(epwm_base); //空窗翻转
        while (1)
            ;
    }
}

void test_sync()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // 增减计数, 10KHz, 占空比50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 8, 0, 1);
        pwm_sync(i);
        SysCtl_TbClkSyncToggle(1);
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;

        int delay = 100;
        while (delay--)
            ;
        EPWM_setTimeBasePeriod(epwm_base, SYS_CLK / 100000 / 2 - 1); // 验证同步加载模式
        EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_C, 3);
        EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_A, SYS_CLK / 100000 / 4 - 1); // 验证shdwafull
        delay = 100;
        while (delay--)
            ;
        EPWM_forceSyncPulse(epwm_base);
        while (1)
            ;
    }
}

void test_lock()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        pwm_lock(i);
    }
}

void test_tz_aq()
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (0 << 8));
    SysCtl_TbClkSyncToggle(0);
    pwm_tz_aq(0);
    SysCtl_TbClkSyncToggle(1);
    while (1)
        ;
}

void test_to_ecap()
{
    int i = 3;
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
    SysCtl_TbClkSyncToggle(0);
    uint32_t epwm_base = EPWM1_BASE + i * 0x200;
    // 增减计数, 10KHz, 占空比50%
    pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 8, 0, 1);
    EPWM_setSyncOutPulseMode(epwm_base, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP1, SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT); // 设置ECAP1的输入为EPWM4SYNCOUT
    SysCtl_TbClkSyncToggle(1);
    int delay = 10000;
    while (delay--)
        ;
}

void test_dc_tz()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // 增减计数, 10KHz, 占空比50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);

        // 配置dc
        XBAR_setInputPin(XBAR_INPUT6, XBAR_INPUT_GPIO6);
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;

        EPWM_selectDigitalCompareTripInput(epwm_base, EPWM_DC_TRIP_TRIPIN6, EPWM_DC_TYPE_DCBH);

        EPWM_setTripZoneDigitalCompareEventCondition(epwm_base, EPWM_TZ_DC_OUTPUT_B1, EPWM_TZ_EVENT_DCXH_HIGH);
        EPWM_setDigitalCompareEventSource(
            epwm_base, EPWM_DC_MODULE_B, EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);

        // 配置TZ关于DC事件的响应
        EPWM_enableTripZoneAdvAction(epwm_base);
        // EPWM_enableTripZoneSignals(epwm_base, EPWM_TZSEL_DCBEVT1);
        EPWM_setTripZoneAdvDigitalCompareActionB(
            epwm_base, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_U, EPWM_TZ_ADV_ACTION_HIGH);

        SysCtl_TbClkSyncToggle(1);
        int delay = 5000;
        while (delay--)
            ;
    }
}

void test_gld()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // 增减计数, 10KHz, 占空比50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        // 配置GLD
        pwm_gld(i);
        SysCtl_TbClkSyncToggle(1);

        int delay = 1000;
        while (delay--)
            ;

        // 修改cmpa测试
        volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i * 0x200);
        uint32_t epwm_base              = EPWM1_BASE + i * 0x200;
        epwm->CMPA.bit.CMPA             = SYS_CLK / 100000 / 8 - 1;

        delay = 100;
        while (delay--)
            ;
        for (int j = 0; j < 6; j++)
        {
            EPWM_forceGlobalLoadOneShotEvent(epwm_base); // 强制产生一次事件
        }
        delay = 1000;
        while (delay--)
            ;

        EPWM_setGlobalLoadOneShotLatch(epwm_base);

        delay = 5000;
        while (delay--)
            ;
    }
}

void test_link()
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (0 << 8));
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (1 << 8));
    volatile struct EPWM_REGS *epwm1 = (volatile struct EPWM_REGS *)(EPWM1_BASE + 0 * 0x200);
    volatile struct EPWM_REGS *epwm2 = (volatile struct EPWM_REGS *)(EPWM1_BASE + 1 * 0x200);

    SysCtl_TbClkSyncToggle(0);
    // 增减计数, 10KHz, 占空比50%
    pwm_normal_gen(0, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
    pwm_normal_gen(1, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);

    // 配置链接
    epwm1->EPWMXLINK.bit.CMPALINK = 1; // 将epwm1的cmpa与epwm2的cmpa链接

    SysCtl_TbClkSyncToggle(1);

    int delay = 1000;
    while (delay--)
        ;
    // 修改cmpa测试
    epwm2->CMPA.bit.CMPA = SYS_CLK / 100000 / 8 - 1;

    delay = 5000;
    while (delay--)
        ;
}

void test_epwm(void)
{
    // test_normal();
    // test_denormal();
    // test_aq();
    // test_db();
    // test_pc();
    // test_db_pc();
    // test_tz_osht();
    // test_tz_cbc();
   // test_tz_osht_int();
    // test_tz_cbc_int();
	test_et_int();
    // test_tz_in();
    // test_et();
    // test_dc();
    // test_sync();
    // test_lock();
    // test_tz_aq();
    // test_to_ecap();
    // test_dc_tz();
    // test_gld();
    // test_link();
}
