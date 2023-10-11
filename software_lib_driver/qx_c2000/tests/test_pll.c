#include "common.h"

static uint32_t count = 0;

void test_osc_power_up_down(void)
{
    /* osc1 can not shut down */
    SysCtl_selectOscSource(SYSCTL_OSCSRC_OSC1);

    SysCtl_turnOffOsc(SYSCTL_OSCSRC_OSC2);
    simple_delay(100);
    SysCtl_turnOnOsc(SYSCTL_OSCSRC_OSC2);

    SysCtl_turnOffOsc(SYSCTL_OSCSRC_XTAL);
    simple_delay(100);
    SysCtl_turnOnOsc(SYSCTL_OSCSRC_XTAL);
}

void test_system_clock_set()
{
    /* clang-format off */
    puts("system_clock_set_test");
    // minimum clock = 26.6Mhz
    if (!SysCtl_setClock(SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(40) | SYSCTL_FMULT(1) | SYSCTL_ODIV(15) | SYSCTL_SYSDIV(1) | SYSCTL_PLL_ENABLE))
        puts("Error: SysCtl_setClock failed!!!");
    if (SysCtl_getClock(10000000) != 26666666)
        puts("Error: SysCtl_getClock failed!!!");
    // maximum clock = 630Mhz
    if (!SysCtl_setClock(SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(63) | SYSCTL_FMULT(1) | SYSCTL_ODIV(1) | SYSCTL_SYSDIV(1) | SYSCTL_PLL_ENABLE))
        puts("Error: SysCtl_setClock failed!!!");
    if (SysCtl_getClock(10000000) != 630000000)
        puts("Error: SysCtl_setClock failed!!!");

    if (!SysCtl_setClock(SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(32) | SYSCTL_FMULT(1) | SYSCTL_ODIV(1) | SYSCTL_SYSDIV(1) | SYSCTL_PLL_ENABLE))
        puts("Error: SysCtl_setClock failed!!!");
    if (SysCtl_getClock(10000000) != 320000000)
        puts("Error: SysCtl_setClock failed!!!");
    /* clang-format on */
}

void test_pll(void)
{
    test_osc_power_up_down();
    // test_system_clock_set();
}
