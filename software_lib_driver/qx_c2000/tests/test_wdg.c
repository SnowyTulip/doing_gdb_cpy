#include "common.h"

static char int_clear_flag = 0;

__interrupt void wake_wdog_isr(void)
{
    puts("wake_wdog_isr");
    if (!SysCtl_isWatchdogInterruptActive())
        puts("WD_STAT no set to 1 in interrupt");
    if (int_clear_flag)
        WdRegs->WD_EOI.bit.WD_EOI = 1;
}

void test_wdg_feed_dog(vu32 cpu_id)
{
    printf("CPU%d:test_wdg_feed_dog\n", cpu_id);
    SysCtl_enableWatchdog();
    // 注意：使能后立刻喂狗才能让SysCtl_setWatchdogResetPeriod配置生效
    SysCtl_serviceWatchdog();
    while (1)
    {
        simple_delay(100);
        SysCtl_serviceWatchdog();
        printf("WD_CCVR=%x\n", SysCtl_getWatchdogCounterValue());
    }
}

void test_wdg_reset_direct(vu32 cpu_id)
{
    SysCtl_disableWatchdog();
    if (SysCtl_getWatchdogResetStatus(cpu_id))
    {
        puts("wdg reset OK...");
        SysCtl_clearWatchdogResetStatus(cpu_id);
        if (!SysCtl_getWatchdogResetStatus(cpu_id))
            puts("wdg reset flag clear OK...");
        while (1) // 等待看是否正确关闭了看门狗
            printf("WD_CCVR=%x\n", SysCtl_getWatchdogCounterValue());
    }
    else
    {
        printf("CPU%d:test_wdg_reset_direct\n", cpu_id);
        SysCtl_setWatchdogResetPeriod(SYSCTL_WD_PERIOD_2_17);
        SysCtl_enableWatchdog();
        // 注意：使能后立刻喂狗才能让SysCtl_setWatchdogResetPeriod配置生效
        SysCtl_serviceWatchdog();

        while (1)
            printf("WD_CCVR=%x\n", SysCtl_getWatchdogCounterValue());
    }
}

void test_wdg_int_and_start(vu32 cpu_id)
{
    SysCtl_disableWatchdog();
    if (SysCtl_getWatchdogResetStatus(cpu_id))
    {
        puts("wdg reset OK...");
        SysCtl_clearWatchdogResetStatus(cpu_id);
        if (!SysCtl_getWatchdogResetStatus(cpu_id))
            puts("wdg reset flag clear OK...");
        while (1) // 等待看是否正确关闭了看门狗
            printf("WD_CCVR=%x\n", SysCtl_getWatchdogCounterValue());
    }
    else
    {
        printf("CPU%d:test_wdg_int_and_start\n", cpu_id);
        int_clear_flag = 0;
        Interrupt_enable(INT_WAKE_WDOG);

        SysCtl_setWatchdogMode(SYSCTL_WD_MODE_INTERRUPT);
        SysCtl_enableWatchdog();
        SysCtl_serviceWatchdog(); // 注意：使能后立刻喂狗才能让TOP配置生效
        while (1)
            printf("WD_CCVR=%x\n", SysCtl_getWatchdogCounterValue());
    }
}

void test_wdg_int_and_no_start(vu32 cpu_id)
{
    SysCtl_disableWatchdog();
    printf("CPU%d:test_wdg_int_and_no_start\n", cpu_id);
    int_clear_flag = 1;
    Interrupt_enable(INT_WAKE_WDOG);

    SysCtl_setWatchdogMode(SYSCTL_WD_MODE_INTERRUPT);
    if (SysCtl_isWatchdogInterruptActive())
        puts("WD_STAT error");
    SysCtl_enableWatchdog();
    SysCtl_serviceWatchdog(); // 注意：使能后立刻喂狗才能让TOP配置生效
    while (1)
        printf("WD_CCVR=%x\n", SysCtl_getWatchdogCounterValue());
}

void test_wdg_def_val()
{
    puts("test_wdg_def_val");
    if (WdRegs->WD_CR.all != 0)
        puts("ERROR:WD_CR def value error");
    if (WdRegs->WD_TORR != 0)
        puts("ERROR:WD_TORR def value error");
    if (WdRegs->WD_CCVR != 0xFFFF)
        puts("ERROR:WD_CCVR def value error");
    if (WdRegs->WD_CRR.all != 0)
        puts("ERROR:WD_CRR def value error");
    if (WdRegs->WD_STAT.all != 0)
        puts("ERROR:WD_STAT def value error");
    if (WdRegs->WD_EOI.all != 0)
        puts("ERROR:WD_EOI def value error");

    if (WdRegs->rsvd1[1] != 0)
        puts("ERROR:WDT_PORT_LEVEL def value error");
    if (WdRegs->rsvd2[0] != 0)
        puts("ERROR:WDT_COMP_PARAM5 def value error");
    if (WdRegs->rsvd2[1] != 0)
        puts("ERROR:WDT_COMP_PARAM4 def value error");
    if (WdRegs->rsvd2[2] != 0)
        puts("ERROR:WDT_COMP_PARAM3 def value error");
    if (WdRegs->rsvd2[3] != 0xFFFF)
        puts("ERROR:WDT_COMP_PARAM2 def value error");
    if (WdRegs->rsvd2[4] != 0x100002D0)
        puts("ERROR:WDT_COMP_PARAM1 def value error");
    if (WdRegs->rsvd2[5] != 0x3131322A)
        puts("ERROR:WDT_COMP_VERSION def value error");
    if (WdRegs->rsvd2[6] != 0x44570120)
        puts("ERROR:WDT_COMP_TYPE def value error");
}

void test_wdg(void)
{
    // test_wdg_def_val();
#ifdef QX_C2000_CORE0
    test_wdg_feed_dog(0);
    // test_wdg_reset_direct(0);
    // test_wdg_int_and_start(0);
    // test_wdg_int_and_no_start(0);
#else
    // test_wdg_reset_direct(1);
    // test_wdg_int_and_start(1);
    test_wdg_int_and_no_start(1);
#endif
}
