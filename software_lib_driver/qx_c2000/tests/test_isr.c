#include "common.h"

static int num_intr       = 0;
static int test_case_flag = 0;

__interrupt void timer0_isr(void)
{
    int lr  = ExpRegs->EPCR;
    int ier = PieCtrlRegs->IER.all;

    PieCtrlRegs->IER.all = PIC_TIMER1 | PIC_TIMER2;
    EINT;

    puts("0");
    CPUTimer_clearInterrupt(CPUTimer0Regs);
    num_intr++;

    DINT;
    ExpRegs->EPCR        = lr;
    PieCtrlRegs->IER.all = ier;
}

__interrupt void timer1_isr(void)
{
    int lr  = ExpRegs->EPCR;
    int ier = PieCtrlRegs->IER.all;

    PieCtrlRegs->IER.all = PIC_TIMER1;
    EINT;

    puts("1");
    CPUTimer_clearInterrupt(CPUTimer1Regs);
    num_intr++;

    DINT;
    ExpRegs->EPCR        = lr;
    PieCtrlRegs->IER.all = ier;
}

__interrupt void timer2_isr(void)
{
    puts("2");
    CPUTimer_clearInterrupt(CPUTimer2Regs);
    num_intr++;
}

void test_nest_between_group(void)
{
    puts("test_nest_between_group...");
    Interrupt_initModule();
    num_intr = 0;

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    CPUTimer_initTimer(CPUTimer0Regs, USER_DEFINED, 6000);
    CPUTimer_enableInterrupt(CPUTimer0Regs);
    Interrupt_enable(INT_TIMER0);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER1);
    CPUTimer_initTimer(CPUTimer1Regs, USER_DEFINED, 6000);
    CPUTimer_enableInterrupt(CPUTimer1Regs);
    Interrupt_enable(INT_TIMER1);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER2);
    CPUTimer_initTimer(CPUTimer2Regs, USER_DEFINED, 6000);
    CPUTimer_enableInterrupt(CPUTimer2Regs);
    Interrupt_enable(INT_TIMER2);
    CPUTimer_enableTimer(CPUTimer0Regs);
    CPUTimer_enableTimer(CPUTimer1Regs);
    CPUTimer_enableTimer(CPUTimer2Regs);

    while (num_intr < 9)
        ;
}

__interrupt void xint1_isr(void)
{
    puts("1");
    num_intr++;
}

__interrupt void xint2_isr(void)
{
    puts("2");
    num_intr++;
}

__interrupt void xint3_isr(void)
{
    puts("3");
    num_intr++;
}

__interrupt void xint4_isr(void)
{
    puts("4");
    num_intr++;
}

__interrupt void xint5_isr(void)
{
    puts("5");
    num_intr++;
}

void test_isr_default_priority()
{
    puts("test_isr_default_priority");
    Interrupt_initModule();

    num_intr = 0;

    GPIO_Config(7, GPIO_7_GPIO7, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_3SAMPLE);
    GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_RISING_EDGE);
    GPIO_setInterruptPin(7, GPIO_INT_XINT1);
    GPIO_enableInterrupt(GPIO_INT_XINT1);

    GPIO_Config(8, GPIO_8_GPIO8, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_6SAMPLE);
    GPIO_setInterruptType(GPIO_INT_XINT2, GPIO_INT_TYPE_RISING_EDGE);
    GPIO_setInterruptPin(8, GPIO_INT_XINT2);
    GPIO_enableInterrupt(GPIO_INT_XINT2);

    GPIO_Config(9, GPIO_9_GPIO9, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
    GPIO_setInterruptType(GPIO_INT_XINT3, GPIO_INT_TYPE_RISING_EDGE);
    GPIO_setInterruptPin(9, GPIO_INT_XINT3);
    GPIO_enableInterrupt(GPIO_INT_XINT3);

    GPIO_Config(10, GPIO_10_GPIO10, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
    GPIO_setInterruptType(GPIO_INT_XINT4, GPIO_INT_TYPE_RISING_EDGE);
    GPIO_setInterruptPin(10, GPIO_INT_XINT4);
    GPIO_enableInterrupt(GPIO_INT_XINT4);

    GPIO_Config(11, GPIO_11_GPIO11, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
    GPIO_setInterruptType(GPIO_INT_XINT5, GPIO_INT_TYPE_RISING_EDGE);
    GPIO_setInterruptPin(11, GPIO_INT_XINT5);
    GPIO_enableInterrupt(GPIO_INT_XINT5);

    Interrupt_enable(INT_XINT1);
    Interrupt_enable(INT_XINT2);
    Interrupt_enable(INT_XINT3);
    Interrupt_enable(INT_XINT4);
    Interrupt_enable(INT_XINT5);

    while (num_intr < 15)
        ;
}

void test_isr(void)
{
    // test_nest_between_group();
    test_isr_default_priority();
}
