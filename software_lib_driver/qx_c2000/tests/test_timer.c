#include "common.h"

static int num_intr = 0;

__interrupt void timer0_isr(void)
{
    num_intr++;
    CPUTimer_clearInterrupt(CPUTimer0Regs);
}

__interrupt void timer1_isr(void)
{
    num_intr++;
    CPUTimer_clearInterrupt(CPUTimer1Regs);
}

__interrupt void timer2_isr(void)
{
    num_intr++;
    CPUTimer_clearInterrupt(CPUTimer2Regs);
}

void timer_setAndStart(CPUTimerReg_types *timer, timer_mode_type timer_mode, u32 time_value, u8 int_flag)
{
    CPUTimer_initTimer(timer, timer_mode, time_value);

    if (int_flag)
        CPUTimer_enableInterrupt(timer);
    else
        CPUTimer_disableInterrupt(timer);

    CPUTimer_enableTimer(timer);

    if (int_flag)
    {
        while (num_intr < 5)
            ;
        num_intr = 0;
        CPUTimer_disableTimer(timer);
        CPUTimer_disableInterrupt(timer);
    }
    else
    {
        simple_delay(100);
        CPUTimer_disableTimer(timer);
    }
}

void timer_test(CPUTimerReg_types *timer, TimerNLoadCount2_types *timerPwmReg)
{
    /* timer with no interrupt */
    /* 目前中断效率比较低(中断现场保存由纯软件实现, 大概需要50-100时钟个周期),
     * timer中断最低触发周 期需要在250以上才能保证正常的处理时序 */
#if 0
    puts("timer without interrupt test...");
    timer_setAndStart(timer, FREE_RUNNING, 300, 0);
    if (num_intr > 0)
    {
        puts("eror: interrupt enter when interrupt disable");
        return;
    }
    timer_setAndStart(timer, USER_DEFINED, 300, 0);
    if (num_intr > 0)
    {
        puts("eror: interrupt enter when interrupt disable");
        return;
    }
#endif

#if 0
    puts("timer with interrupt test...");

    if (timer == CPUTimer0Regs)
        Interrupt_enable(INT_TIMER0);
    else if (timer == CPUTimer1Regs)
        Interrupt_enable(INT_TIMER1);
    else
        Interrupt_enable(INT_TIMER2);

    timer_setAndStart(timer, USER_DEFINED, 250, 1);
    if (num_intr != 5)
    {
        puts("eror: interrupt enter when interrupt enable");
        return;
    }
#endif

#if 0
    puts("timer pwm test in mode USER_DEFINED...");
    CPUTimer_disableInterrupt(timer);
    CPUTimer_initPwm(timer, timerPwmReg, USER_DEFINED, 50, 50);
    CPUTimer_enableTimer(timer);
    simple_delay(50);
    if (num_intr > 0)
    {
        puts("eror: interrupt enter when interrupt disable");
        return;
    }

    puts("timer pwm test with alwalys high...");
    CPUTimer_initPwm(timer, timerPwmReg, USER_DEFINED, 100, 0);
    CPUTimer_enableTimer(timer);
    simple_delay(50);

    puts("timer pwm test with alwalys low...");
    CPUTimer_initPwm(timer, timerPwmReg, USER_DEFINED, 0, 10);
    CPUTimer_enableTimer(timer);
    simple_delay(50);

    puts("timer pwm test with 100:20...");
    CPUTimer_initPwm(timer, timerPwmReg, USER_DEFINED, 100, 20);
    CPUTimer_enableTimer(timer);
    simple_delay(50);

    puts("timer pwm test with 5:1...");
    CPUTimer_initPwm(timer, timerPwmReg, USER_DEFINED, 5, 1);
    CPUTimer_enableTimer(timer);
    simple_delay(50);
#endif
}

void test_timer()
{
#if 0 // for cpu0 timer test
    puts("timer0 test start...");
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    timer_test(CPUTimer0Regs, CPUTimer0PwmRegs);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);

    puts("timer1 test start...");
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER1);
    timer_test(CPUTimer1Regs, CPUTimer1PwmRegs);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER1);

    puts("timer2 test start...");
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER2);
    timer_test(CPUTimer2Regs, CPUTimer2PwmRegs);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER2);
#endif

#if 0 // for cpu1 timer test
    puts("timer0 test start...");
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER0);
    timer_test(CPUTimer0Regs, CPUTimer0PwmRegs);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER0);

    puts("timer1 test start...");
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER1);
    timer_test(CPUTimer1Regs, CPUTimer1PwmRegs);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER1);

    puts("timer2 test start...");
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER2);
    timer_test(CPUTimer2Regs, CPUTimer2PwmRegs);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER2);
#endif

#if 1
    puts("all timer run with interrupt test...");
    Interrupt_enable(INT_TIMER0);
    Interrupt_enable(INT_TIMER1);
    Interrupt_enable(INT_TIMER2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER2);
    /* SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER0); */
    /* SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER1); */
    /* SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER2); */
    CPUTimer_initTimer(CPUTimer0Regs, USER_DEFINED, 400);
    CPUTimer_initTimer(CPUTimer1Regs, USER_DEFINED, 800);
    CPUTimer_initTimer(CPUTimer2Regs, USER_DEFINED, 1200);
    CPUTimer_enableInterrupt(CPUTimer0Regs);
    CPUTimer_enableInterrupt(CPUTimer1Regs);
    CPUTimer_enableInterrupt(CPUTimer2Regs);
    CPUTimer_enableTimer(CPUTimer0Regs);
    CPUTimer_enableTimer(CPUTimer1Regs);
    CPUTimer_enableTimer(CPUTimer2Regs);
    while (num_intr < 15)
        ;
    num_intr = 0;
    CPUTimer_disableTimer(CPUTimer0Regs);
    CPUTimer_disableTimer(CPUTimer1Regs);
    CPUTimer_disableTimer(CPUTimer2Regs);
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_disableInterrupt(CPUTimer1Regs);
    CPUTimer_disableInterrupt(CPUTimer2Regs);
#endif
}
