#include "common.h"

static uint32_t count = 0;

// 复位值寄存器读取
void test_reg_def_val_cgu()
{
    puts("test_reg_def_val_cgu");
    if (ClkCfgRegs->CLKSRCCTL1.all != 0)
        puts("Error: CLKSRCCTL1 def value error");
    if (ClkCfgRegs->CLKSRCCTL2.all != 0)
        puts("Error: CLKSRCCTL2 def value error");
    if (ClkCfgRegs->CLKSRCCTL3.all != 0)
        puts("Error: CLKSRCCTL3 def value error");
    if (ClkCfgRegs->SYSPLLCTL1.all != 0)
        puts("Error: SYSPLLCTL1 def value error");
    if (ClkCfgRegs->SYSPLLMULT.all != 0x1200)
        puts("Error: SYSPLLMULT def value error");
    if (ClkCfgRegs->SYSPLLSTS.all != 0)
        puts("Error: SYSPLLSTS def value error");
    // SYSCLKDIVSEL可能会在Device_init中被设置为0, 这里对0值不做检错
    if (ClkCfgRegs->SYSCLKDIVSEL.all != 0x2 && ClkCfgRegs->SYSCLKDIVSEL.all != 0)
        puts("Error: SYSCLKDIVSEL def value error");
    if (ClkCfgRegs->XCLKOUTDIVSEL.all != 0x3)
        puts("Error: XCLKOUTDIVSEL def value error");
    // LOSPCP可能会在Device_init中被设置为0, 这里对0值不做检错
    if (ClkCfgRegs->LOSPCP.all != 0x2 && ClkCfgRegs->LOSPCP.all != 0)
        puts("Error: LOSPCP def value error");
    if (ClkCfgRegs->MCDCR.all != 0)
        puts("Error: MCDCR def value error");
    if (ClkCfgRegs->X1CNT.all != 0)
        puts("Error: X1CNT def value error");
    if (ClkCfgRegs->XTALCR.all != 0x1)
        puts("Error: XTALCR def value error");
    if (ClkCfgRegs->CLKSTATUS.all != 0x3)
        puts("Error: CLKSTATUS def value error");
}

// 振荡器时钟源选择
void test_osc_clk_src_sel()
{
    puts("switch to X1 test");
    ClkCfgRegs->XTALCR.bit.OSCOFF = 0; // Turn on XTAL
    ClkCfgRegs->XTALCR.bit.SE     = 0; // select crystal mode
    while (1)                          // Wait for the X1 clock readly
    {
        if (ClkCfgRegs->CLKSTATUS.bit.X1READLY)
            break;
    }
    ClkCfgRegs->SYSPLLCTL1.bit.PLLCLKEN = 0; // bypass PLL
    // Select XTAL as the oscillator source
    ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 1;
    simple_delay(10);

    puts("switch to osc1 test");
    ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 2; // OSC1
    simple_delay(10);

    puts("switch to osc2 test");
    ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 0; // OSC2
    simple_delay(10);

    puts("switch to osc1 test");
    ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 3; // 3是Reserved指,行为OSC1一致
    simple_delay(10);

    puts("switch to osc2 test");
    ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 0; // 还原到默认值
    simple_delay(10);
}

void test_can_clk_switch(void)
{
    puts("test_can_clk_switch");

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANB);

    ClkCfgRegs->CLKSRCCTL2.bit.CANACLKSEL = 1; // SYSCLK
    simple_delay(10);
    ClkCfgRegs->CLKSRCCTL2.bit.CANACLKSEL = 2; // 无效, 效果=0
    simple_delay(10);
    ClkCfgRegs->CLKSRCCTL2.bit.CANACLKSEL = 3; // 无效, 效果=1
    simple_delay(10);
    ClkCfgRegs->CLKSRCCTL2.bit.CANACLKSEL = 0; // X1 默认关闭
    simple_delay(10);
    ClkCfgRegs->CLKSRCCTL2.bit.CANBCLKSEL = 1; // SYSCLK
    simple_delay(10);
    ClkCfgRegs->CLKSRCCTL2.bit.CANBCLKSEL = 2; // 无效, 效果=0
    simple_delay(10);
    ClkCfgRegs->CLKSRCCTL2.bit.CANBCLKSEL = 3; // 无效, 效果=1
    simple_delay(10);
    ClkCfgRegs->CLKSRCCTL2.bit.CANBCLKSEL = 0; // X1 默认关闭
    simple_delay(10);
}

void test_clk_out_sel()
{
    puts("test clkout select");
    // XCLKOUT 时钟分频
    GPIO_Config(16, GPIO_16_XCLKOUT, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    SysCtl_setXClk(SYSCTL_XCLKOUT_DIV_2);
    simple_delay(50);
    SysCtl_setXClk(SYSCTL_XCLKOUT_DIV_4);
    simple_delay(50);
    SysCtl_setXClk(SYSCTL_XCLKOUT_DIV_8);
    simple_delay(50);
    SysCtl_setXClk(SYSCTL_XCLKOUT_DIV_1);
    simple_delay(50);

    // XCLKOUTSEL 时钟源头选择
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_PLLSYS);
    simple_delay(50);
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_PLLRAW);
    simple_delay(50);
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_SYSCLK);
    simple_delay(50);
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_INTOSC1);
    simple_delay(50);
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_INTOSC2);
    simple_delay(50);
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_XTALOSC);
    simple_delay(50);
}

// 使用外部X1时钟(10Mhz), IMULT最小值, ODIV最大值, 26.66MHz是PLL可以配置出来的最小频率
#define XTAL_WITH_PLL_CLK_26M \
    (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(40) | SYSCTL_FMULT(1) | SYSCTL_ODIV(15) | SYSCTL_SYSDIV(0) | SYSCTL_PLL_ENABLE)

// 使用外部X1时钟(10Mhz), IMULT中间值, ODIV中间值
#define XTAL_WITH_PLL_CLK_60M \
    (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(60) | SYSCTL_FMULT(1) | SYSCTL_ODIV(10) | SYSCTL_SYSDIV(0) | SYSCTL_PLL_ENABLE)

// 使用外部X1时钟(10Mhz), 200M是实际运行的典型配置
#define XTAL_WITH_PLL_CLK_200M \
    (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(40) | SYSCTL_FMULT(1) | SYSCTL_ODIV(2) | SYSCTL_SYSDIV(0) | SYSCTL_PLL_ENABLE)

// 使用外部X1时钟(10Mhz), 300M是实际运行的典型配置
#define XTAL_WITH_PLL_CLK_300M \
    (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(60) | SYSCTL_FMULT(1) | SYSCTL_ODIV(2) | SYSCTL_SYSDIV(0) | SYSCTL_PLL_ENABLE)

// 使用外部X1时钟(10Mhz), 400M是实际运行可能的最大速率
#define XTAL_WITH_PLL_CLK_400M \
    (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(40) | SYSCTL_FMULT(1) | SYSCTL_ODIV(0) | SYSCTL_SYSDIV(0) | SYSCTL_PLL_ENABLE)

// 使用外部X1时钟(10Mhz), IMULT最大值, ODIV最小值, 0和1都为1分频, 63Mhz是PLL模块可以配置出来的最大频率
#define XTAL_WITH_PLL_CLK_630M \
    (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(63) | SYSCTL_FMULT(1) | SYSCTL_ODIV(0) | SYSCTL_SYSDIV(0) | SYSCTL_PLL_ENABLE)

// 使用外部X1时钟(10Mhz), SYSDIV中间值, 32分频
#define XTAL_WITH_PLL_CLK_100M \
    (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(40) | SYSCTL_FMULT(1) | SYSCTL_ODIV(4) | SYSCTL_SYSDIV(32) | SYSCTL_PLL_ENABLE)

// 使用外部X1时钟(10Mhz), SYSDIV最小值, 126分频
#define XTAL_WITH_PLL_CLK_50M \
    (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(40) | SYSCTL_FMULT(1) | SYSCTL_ODIV(8) | SYSCTL_SYSDIV(126) | SYSCTL_PLL_ENABLE)

// 使用内部OSC1时钟(10Mhz), OSC1源, SYS_DIV为中间典型值
#define OSC1_WITH_PLL_CLK_40M \
    (SYSCTL_OSCSRC_OSC1 | SYSCTL_IMULT(40) | SYSCTL_FMULT(1) | SYSCTL_ODIV(10) | SYSCTL_SYSDIV(10) | SYSCTL_PLL_ENABLE)

// 使用内部OSC1时钟(10Mhz), OSC2源, SYS_DIV为直接典型值
#define OSC2_WITH_PLL_CLK_60M \
    (SYSCTL_OSCSRC_OSC2 | SYSCTL_IMULT(60) | SYSCTL_FMULT(1) | SYSCTL_ODIV(10) | SYSCTL_SYSDIV(20) | SYSCTL_PLL_ENABLE)

// 使用内部OSC1时钟(10Mhz), OSC2源, 50M典型时钟, SYS_DIV为1分频
#define OSC2_WITH_PLL_CLK_50M \
    (SYSCTL_OSCSRC_OSC2 | SYSCTL_IMULT(50) | SYSCTL_FMULT(1) | SYSCTL_ODIV(10) | SYSCTL_SYSDIV(0) | SYSCTL_PLL_ENABLE)

// 配置和使用PLL, PLLSYSCLK时钟分频
void test_sysctl_set()
{
    puts("test_sysctl_set");
    // puts("XTAL_WITH_PLL_CLK_26M");
    // SysCtl_setClock(XTAL_WITH_PLL_CLK_26M);
    // simple_delay(10);
    // puts("XTAL_WITH_PLL_CLK_60M");
    // SysCtl_setClock(XTAL_WITH_PLL_CLK_60M);
    // simple_delay(10);
    puts("XTAL_WITH_PLL_CLK_200M");
    SysCtl_setClock(XTAL_WITH_PLL_CLK_200M);
    simple_delay(10);
    puts("XTAL_WITH_PLL_CLK_300M");
    SysCtl_setClock(XTAL_WITH_PLL_CLK_300M);
    simple_delay(10);
    puts("XTAL_WITH_PLL_CLK_400M");
    SysCtl_setClock(XTAL_WITH_PLL_CLK_400M);
    simple_delay(10);
    // puts("XTAL_WITH_PLL_CLK_630M");
    // SysCtl_setClock(XTAL_WITH_PLL_CLK_630M);
    // simple_delay(10);
    // puts("XTAL_WITH_PLL_CLK_100M");
    // SysCtl_setClock(XTAL_WITH_PLL_CLK_100M);
    // simple_delay(10);
    // puts("XTAL_WITH_PLL_CLK_50M");
    // SysCtl_setClock(XTAL_WITH_PLL_CLK_50M);
    // simple_delay(10);
    // puts("OSC1_WITH_PLL_CLK_40M");
    // SysCtl_setClock(OSC1_WITH_PLL_CLK_40M);
    // simple_delay(10);
    // puts("OSC2_WITH_PLL_CLK_60M");
    // SysCtl_setClock(OSC2_WITH_PLL_CLK_60M);
    // simple_delay(10);
    puts("OSC2_WITH_PLL_CLK_50M");
    // 最后切换到对其他用例仿真比较合适的50Mhz典型时钟配置
    SysCtl_setClock(OSC2_WITH_PLL_CLK_50M);
    simple_delay(10);
}

// LSPCLK时钟分频
void test_lsp_div()
{
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_2);
    simple_delay(10);
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_4);
    simple_delay(10);
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_6);
    simple_delay(10);
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_8);
    simple_delay(10);
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_10);
    simple_delay(10);
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_12);
    simple_delay(10);
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_14);
    simple_delay(10);
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_1);
    simple_delay(10);
}

// X1CNT外部时钟计数
// 外部时钟状态检测
void test_x1cnt()
{
    puts("test_x1cnt");

    if (ClkCfgRegs->CLKSTATUS.bit.OSC1READLY != 1)
        puts("ERROR:OSC1READLY error");

    if (ClkCfgRegs->CLKSTATUS.bit.OSC2READLY != 1)
        puts("ERROR:OSC2READLY error");

    ClkCfgRegs->XTALCR.bit.OSCOFF = 0; // Turn on XTAL

    while (1) // Wait for the X1 clock readly
    {
        if (ClkCfgRegs->CLKSTATUS.bit.X1READLY) // X1READLY在x1cnt计数到0x7f就拉高
            break;
    }

    while (1) // Wait for the X1 cnt count to 0x3ff
    {
        if (ClkCfgRegs->X1CNT.all == 0x3ff)
            break;
    }

    ClkCfgRegs->X1CNT.bit.CLR = 1;
    simple_delay(10);
    if (ClkCfgRegs->X1CNT.all == 0x3ff)
        puts("ERROR: X1cnt clear error");

    while (1) // Wait for the X1 clock readly
    {
        if (ClkCfgRegs->CLKSTATUS.bit.X1READLY) // X1READLY在x1cnt计数到0x7f就拉高
            break;
    }

    while (1) // Wait for the X1 cnt count to 0x3ff
    {
        if (ClkCfgRegs->X1CNT.all == 0x3ff)
            break;
    }

    ClkCfgRegs->X1CNT.bit.CLR = 1;
    simple_delay(10);
    if (ClkCfgRegs->X1CNT.all == 0x3ff)
        puts("X1CNT not reset to 0 after X1 clear");

    ClkCfgRegs->XTALCR.bit.OSCOFF = 1; // Turn off XTAL

    if (ClkCfgRegs->CLKSTATUS.bit.X1READLY != 0)
        puts("X1READLY not reset to 0 after X1 tran off");
}

// INTOSC2关闭/打开 | 外部晶振开关 | MCD测试一：触发MCD | MCD测试二：触发MCD | 清除MCD | 关闭MCD
void test_osc_toaggle_and_mcd_detected()
{
#if 1
    puts("MCD detected x1 lost test...");
    count = 0;

    ClkCfgRegs->XTALCR.bit.OSCOFF = 0; // Turn on XTAL
    while (1)
    {
        if (ClkCfgRegs->CLKSTATUS.bit.X1READLY)
            break;
    }
    // 注意:由于PLL仿真模型问题, 不bypass PLL会导致时钟源断开后PLL依然有时钟输出问题
    ClkCfgRegs->SYSPLLCTL1.bit.PLLCLKEN     = 0; // bypass PLL
    ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 1; // 切换到x1时钟源
    ClkCfgRegs->XTALCR.bit.OSCOFF           = 1; // X1关闭
    while (SysCtl_isMCDClockFailureDetected())
    {
        puts("detect x1 clock lost");
        if (count++ < 2)
        {
            if (!SysCtl_isMCDClockFailureDetected())
                puts("ERROR:MCLKSTS error");
            SysCtl_resetMCD();
            ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 1; // 切换到x1时钟源
        }
        else
        {
            if (!SysCtl_isMCDClockFailureDetected())
                puts("ERROR:MCLKSTS error");
            SysCtl_resetMCD();
            ClkCfgRegs->XTALCR.bit.OSCOFF           = 0;
            ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 1; // 切换到x1时钟源
            puts("MCD detect x1 test passed");
        }
    }
#endif

#if 1
    puts("MCD detected osc2 lost test...");
    count = 0;
    // 注意:由于PLL仿真模型问题, 不bypass PLL会导致时钟源断开后PLL依然有时钟输出问题
    ClkCfgRegs->SYSPLLCTL1.bit.PLLCLKEN     = 0; // bypass PLL
    ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 0; // 切换到osc2
    ClkCfgRegs->CLKSRCCTL1.bit.INTOSC2OFF   = 1; // OSC2关闭测试
    while (SysCtl_isMCDClockFailureDetected())
    {
        puts("detect osc2 clock lost");
        if (count++ < 2)
        {
            if (!SysCtl_isMCDClockFailureDetected())
                puts("ERROR:MCLKSTS error");
            SysCtl_resetMCD();
            ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 0; // 切换到osc2
        }
        else
        {
            if (!SysCtl_isMCDClockFailureDetected())
                puts("ERROR:MCLKSTS error");
            SysCtl_resetMCD();
            ClkCfgRegs->CLKSRCCTL1.bit.INTOSC2OFF   = 0;
            ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 0; // 切换到osc2
            puts("MCD detect osc2 test passed");
        }
    }
#endif

#if 1
    puts("MCD detected mcd clk lost test...");
    count = 0;
    // 注意:由于PLL仿真模型问题, 不bypass PLL会导致时钟源断开后PLL依然有时钟输出问题
    ClkCfgRegs->SYSPLLCTL1.bit.PLLCLKEN     = 0; // bypass PLL
    ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 0; // 切换到osc2
    ClkCfgRegs->MCDCR.bit.OSCOFF            = 1; // MCD 时钟源关闭

    while (count < 3)
    {
        while (!SysCtl_isMCDClockFailureDetected())
            ;
        puts("detect mcd clock lost");
        if (count < 2)
        {
            if (!SysCtl_isMCDClockFailureDetected())
                puts("ERROR:MCLKSTS error");
            SysCtl_resetMCD();
            ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 0; // 切换到OSC2时钟
            ClkCfgRegs->MCDCR.bit.OSCOFF            = 0; // MCD 时钟源打开
            ClkCfgRegs->MCDCR.bit.OSCOFF            = 1; // MCD 时钟源关闭
        }
        else
        {
            if (!SysCtl_isMCDClockFailureDetected())
                puts("ERROR:MCLKSTS error");
            SysCtl_resetMCD();
            ClkCfgRegs->MCDCR.bit.OSCOFF            = 0; // MCD 时钟源打开
            ClkCfgRegs->CLKSRCCTL1.bit.OSCCLKSRCSEL = 0; // 切换到OSC2时钟
            puts("MCD detect mcd clk test passed");
        }
        count++;
    }
#endif

#if 0
    puts("MCD detected toggler test...");
    SysCtl_disableMCD();
    ClkCfgRegs->CLKSRCCTL1.bit.INTOSC2OFF = 1; // OSC2关闭测试
    puts("this message should not output");
#endif
}

__interrupt void timer0_isr(void)
{
    puts("timer0_isr");
    CPUTimer_clearInterrupt(CPUTimer0Regs);
}

__interrupt void xint1_isr(void)
{
    puts("xint1_isr");
}

// 进入IDLE低功耗模式指令进入/中断事件退出
void idle_mode_test()
{
#if 1
    puts("idle_mode_test_with_gpio_loop");
    puts("enable xint1 interrupt...");
    Interrupt_enable(INT_XINT1);
    GPIO_Config(8, GPIO_8_GPIO8, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_3SAMPLE);
    GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_RISING_EDGE);
    GPIO_setInterruptPin(8, GPIO_INT_XINT1);
    GPIO_enableInterrupt(GPIO_INT_XINT1);
    for (int i = 0; i < 3; i++)
    {
        SysCtl_enterIdleMode();
        puts("IDLE mode wakeup by xint1 interrupt");
    }
    GPIO_disableInterrupt(GPIO_INT_XINT1);
#endif

#if 1
    puts("idle_mode_test_with_timer0_loop");
    puts("enable timer0 interrupt...");
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    Interrupt_enable(INT_TIMER0);
    CPUTimer_initTimer(CPUTimer0Regs, USER_DEFINED, 4000);
    CPUTimer_enableInterrupt(CPUTimer0Regs);
    CPUTimer_enableTimer(CPUTimer0Regs);
    for (int i = 0; i < 3; i++)
    {
        SysCtl_enterIdleMode();
        puts("IDLE mode wakeup by timer interrupt");
    }
    CPUTimer_disableTimer(CPUTimer0Regs);
#endif
}

__interrupt void wake_wdog_isr(void)
{
    puts("wake_wdog_isr");
    WdRegs->WD_EOI.bit.WD_EOI = 1;
}

// 进入STANDBY低功耗模式/看门狗退出
void standby_mode_test_with_wdg()
{
    puts("standby_mode_test_with_wdg");
    SysCtl_enablePeripheralAll();

    Interrupt_enable(INT_WAKE_WDOG);
    CpuSysRegs->LPMCR.bit.WDINTE = 1;
    SysCtl_setWatchdogMode(SYSCTL_WD_MODE_INTERRUPT);
    SysCtl_enableWatchdog();
    SysCtl_serviceWatchdog();

    for (int i = 0; i < 3; i++)
    {
        SysCtl_enterStandbyMode();
        puts("STANDBY mode wakeup by wdg");
    }
    SysCtl_disableWatchdog();
}

// 进入STANDBY低功耗模式/GPIO退出
void standby_mode_test_with_gpio()
{
    puts("standby_mode_test_with_gpio");
    Interrupt_enable(INT_WAKE_WDOG);
    GPIO_Config(8, GPIO_8_GPIO8, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
    SysCtl_enableLPMWakeupPin(8);
    CpuSysRegs->LPMCR.bit.GPIOLPSEL = 1;

    for (int i = 0; i < 3; i++)
    {
        SysCtl_enablePeripheralAll();
        SysCtl_enterStandbyMode();
        SysCtl_disablePeripheralAll();
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIA);
        puts("STANDBY mode wakeup by GPIO");
    }
    SysCtl_disableLPMWakeupPin(8);
}

// 进入HALT低功耗模式/GPIO退出
void halt_mode_test_with_gpio()
{
    puts("halt_mode_test_with_gpio");
    SysCtl_enablePeripheralAll();

    Interrupt_enable(INT_WAKE_WDOG);
    GPIO_Config(8, GPIO_8_GPIO8, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
    SysCtl_disableWatchdogInHalt();
    SysCtl_enableLPMWakeupPin(8);
    CpuSysRegs->LPMCR.bit.GPIOLPSEL = 1;
    for (int i = 0; i < 3; i++)
    {
        SysCtl_enterHaltMode();
        puts("HALT mode wakeup by GPIO");
    }
    SysCtl_disableLPMWakeupPin(8);
}

// HALT模式下看门狗是否工作
void halt_mode_test_with_enable_wdg_in_halt()
{
    puts("halt_mode_test_with_enable_wdg_in_halt");
    SysCtl_enablePeripheralAll();

    GPIO_Config(8, GPIO_8_GPIO8, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
    SysCtl_enableLPMWakeupPin(8);
    CpuSysRegs->LPMCR.bit.GPIOLPSEL = 1;

    // 目前看门狗在halt模式使能时, halt模式进入时osc1和osc2的时钟不关闭, 其它的情况和禁用时一致
    SysCtl_enableWatchdogInHalt();
    CpuSysRegs->LPMCR.bit.WDINTE = 1;

    for (int i = 0; i < 3; i++)
    {
        SysCtl_enterHaltMode();
        puts("HALT mode wakeup by GPIO");
    }

    SysCtl_disableLPMWakeupPin(8);
}

// HALT模式进入前如果使用X1时钟, 如果需要最低功耗, 需要先切换到OSC1/OSC2, 然后再手动停止X1, 然后再进入HALT模式
void halt_mode_test_with_x1_clock()
{
    puts("HALT mode test with X1 clock...");
    Interrupt_enable(INT_WAKE_WDOG);
    GPIO_Config(8, GPIO_8_GPIO8, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
    SysCtl_enableLPMWakeupPin(8);
    CpuSysRegs->LPMCR.bit.GPIOLPSEL = 1;

    puts("Switch Clock to X1...");
    SysCtl_setClock(XTAL_WITH_PLL_CLK_50M);

    puts("Switch Clock to OSC2 before enter HALT mode...");
    ClkCfgRegs->SYSPLLCTL1.bit.PLLCLKEN = 0;
    SysCtl_selectOscSource(SYSCTL_OSCSRC_OSC2);
    puts("Close X1 before enter HALT mode...");
    ClkCfgRegs->XTALCR.bit.OSCOFF = 1;

    SysCtl_enterHaltMode();
    SysCtl_disableLPMWakeupPin(8);
    puts("Switch Clock to X1 after wackup form HALT mode...");
    SysCtl_setClock(XTAL_WITH_PLL_CLK_50M);
}

void test_core1_reset()
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU1);
    qx_ipc_wait_block(IPC_EVENT5);
    puts("CPU1 Start OK...");
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_CPU1);
    qx_ipc_wait_block(IPC_EVENT5);
    puts("CPU1 Reset OK...");
}

__interrupt void nmi_isr(void)
{
    printf("%x\n", NmiIntruptRegs->NMIFLG.all);
    switch (NmiIntruptRegs->NMIFLG.all)
    {
        case 0x03:
            NmiIntruptRegs->NMIFLGCLR.bit.CLOCKFAIL = 1;
            break;
        case 0x05:
            NmiIntruptRegs->NMIFLGCLR.bit.RAMUNCERR = 1;
            break;
        case 0x09:
            NmiIntruptRegs->NMIFLGCLR.bit.FLUNCERR = 1;
            break;
        case 0x41:
            NmiIntruptRegs->NMIFLGCLR.bit.PIEVECTERR = 1;
            break;
        case 0x81:
            NmiIntruptRegs->NMIFLGCLR.bit.DMEMERR = 1;
            break;
        case 0x101:
            NmiIntruptRegs->NMIFLGCLR.bit.IMEMERR1 = 1;
            break;
        case 0x201:
            NmiIntruptRegs->NMIFLGCLR.bit.IMEMERR2 = 1;
            break;
        case 0x2001:
            NmiIntruptRegs->NMIFLGCLR.bit.SWERR = 1;
            break;
        default:
            break;
    }

    if (NmiIntruptRegs->NMIFLG.all != 0)
        printf("ERROR:NMIINT flag no auto clear!");
    count++;
}

static void test_xsr_por_pvd_reset()
{
    puts("test_xsr_por_pvd_reset");
    printf("RESC = %x\n", CpuSysRegs->RESC.all);
    CpuSysRegs->RESCCLR.all = 0xFFFFFFFF; // clear all flags
    printf("RESC after clear = %x\n", CpuSysRegs->RESC.all);
    while (1)
        ;
}

static void test_reg_def_val_sysclk()
{
    puts("test_reg_def_val_of_sysclk");
    if (CpuSysRegs->PCLKCR0.all != 0)
        puts("Error: CLKSRCCTL0 def value error");
    if (CpuSysRegs->PCLKCR1.all != 0)
        puts("Error: CLKSRCCTL1 def value error");
    if (CpuSysRegs->PCLKCR2.all != 0)
        puts("Error: CLKSRCCTL2 def value error");
    if (CpuSysRegs->PCLKCR3.all != 0)
        puts("Error: CLKSRCCTL3 def value error");
    if (CpuSysRegs->PCLKCR4.all != 0)
        puts("Error: CLKSRCCTL4 def value error");
    if (CpuSysRegs->PCLKCR5.all != 0)
        puts("Error: CLKSRCCTL5 def value error");
    if (CpuSysRegs->PCLKCR6.all != 0)
        puts("Error: CLKSRCCTL6 def value error");
    if (CpuSysRegs->PCLKCR7.all != 0)
        puts("Error: CLKSRCCTL7 def value error");
    if (CpuSysRegs->PCLKCR8.all != 0)
        puts("Error: CLKSRCCTL8 def value error");
    if (CpuSysRegs->PCLKCR9.all != 0)
        puts("Error: CLKSRCCTL9 def value error");
    if (CpuSysRegs->PCLKCR10.all != 0)
        puts("Error: CLKSRCCTL10 def value error");
    if (CpuSysRegs->PCLKCR11.all != 0)
        puts("Error: CLKSRCCTL11 def value error");
    if (CpuSysRegs->PCLKCR12.all != 0)
        puts("Error: CLKSRCCTL12 def value error");
    if (CpuSysRegs->PCLKCR13.all != 0)
        puts("Error: CLKSRCCTL13 def value error");
    if (CpuSysRegs->LPMCR.all != 0)
        puts("Error: LPMCR def value error");
    if (CpuSysRegs->TMR2CLKCTL.all != 0)
        puts("Error: TMR2CLKCTL def value error");
    if (CpuSysRegs->GPIOLPMSEL0.all != 0)
        puts("Error: GPIOLPMSEL0 def value error");
    if (CpuSysRegs->GPIOLPMSEL1.all != 0)
        puts("Error: GPIOLPMSEL1 def value error");
    if (CpuSysRegs->RESCCLR.all != 0)
        puts("Error: RESCCLR def value error");
    // 注意：快速前仿时jtags会开启，期望值为E0000033，带bootlader时为20000033
    printf("WARNING: RESC Reg = %x\n", CpuSysRegs->RESC.all);
}

void test_nmi(void)
{
    puts("test_nmi");
    NmiIntruptRegs->NMIWDPRD        = 0x1000;
    NmiIntruptRegs->NMICFG.bit.NMIE = 1;
    NmiIntruptRegs->NMICFG.bit.NMIE = 0; // 验证NMI只能被使能不能被禁用
    // 软件强制方式目前存在问题
    // NmiIntruptRegs->NMIFLGFRC.bit.SWERR = 1;
    while (count <= 6)
        ;
}

void test_cgu(void)
{
    test_reg_def_val_cgu();
    test_osc_clk_src_sel();
    test_can_clk_switch();
    test_clk_out_sel();
    test_sysctl_set();
    test_lsp_div();
    test_x1cnt();
    test_osc_toaggle_and_mcd_detected();
}

void test_lp_mode(void)
{
    idle_mode_test();
    standby_mode_test_with_wdg();
    standby_mode_test_with_gpio();
    halt_mode_test_with_gpio();
    halt_mode_test_with_enable_wdg_in_halt();
    halt_mode_test_with_x1_clock();
}

void test_sysclk(void)
{
    test_xsr_por_pvd_reset();
    // test_reg_def_val_sysclk();
    // SysCtl_enablePeripheralAll();
    // simple_delay(100);
    // SysCtl_disablePeripheralAll();
}

void test_reset(void)
{
    // test_core1_reset();
}

void test_sysctl(void)
{
    // test_cgu();
    // test_lp_mode();
    test_sysclk();
    // test_reset();
    // test_nmi();
}
