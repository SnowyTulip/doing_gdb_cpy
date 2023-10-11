#include "common.h"

static int num_xint1, num_xint2, num_xint3, num_xint4, num_xint5;

__interrupt void xint1_isr(void)
{
    num_xint1++;
}

__interrupt void xint2_isr(void)
{
    num_xint2++;
}

__interrupt void xint3_isr(void)
{
    num_xint3++;
}

__interrupt void xint4_isr(void)
{
    num_xint4++;
}

__interrupt void xint5_isr(void)
{
    num_xint5++;
}

void test_gpio_external_int()
{
    puts("XINT1 test...");
    GPIO_Config(7, GPIO_7_GPIO7, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_3SAMPLE);
    Interrupt_enable(INT_XINT1);
    GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_RISING_EDGE);
    GPIO_setInterruptPin(7, GPIO_INT_XINT1);
    GPIO_enableInterrupt(GPIO_INT_XINT1);
    while (num_xint1 < 5)
        ;
    GPIO_disableInterrupt(GPIO_INT_XINT1);

    puts("XINT2 test...");
    GPIO_Config(8, GPIO_8_GPIO8, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_6SAMPLE);
    Interrupt_enable(INT_XINT2);
    GPIO_setInterruptType(GPIO_INT_XINT2, GPIO_INT_TYPE_FALLING_EDGE);
    GPIO_setInterruptPin(8, GPIO_INT_XINT2);
    GPIO_enableInterrupt(GPIO_INT_XINT2);
    while (num_xint2 < 5)
        ;
    GPIO_disableInterrupt(GPIO_INT_XINT2);

    puts("XINT3 test...");
    GPIO_Config(9, GPIO_9_GPIO9, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
    Interrupt_enable(INT_XINT3);
    GPIO_setInterruptType(GPIO_INT_XINT3, GPIO_INT_TYPE_BOTH_EDGES);
    GPIO_setInterruptPin(9, GPIO_INT_XINT3);
    GPIO_enableInterrupt(GPIO_INT_XINT3);
    while (num_xint3 < 5)
        ;
    GPIO_disableInterrupt(GPIO_INT_XINT3);

    puts("XINT4 test...");
    GPIO_Config(10, GPIO_10_GPIO10, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
    Interrupt_enable(INT_XINT4);
    GPIO_setInterruptType(GPIO_INT_XINT4, GPIO_INT_TYPE_BOTH_EDGES);
    GPIO_setInterruptPin(10, GPIO_INT_XINT4);
    GPIO_enableInterrupt(GPIO_INT_XINT4);
    while (num_xint4 < 5)
        ;
    GPIO_disableInterrupt(GPIO_INT_XINT4);

    puts("XINT5 test...");
    GPIO_Config(11, GPIO_11_GPIO11, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
    Interrupt_enable(INT_XINT5);
    GPIO_setInterruptType(GPIO_INT_XINT5, GPIO_INT_TYPE_BOTH_EDGES);
    GPIO_setInterruptPin(11, GPIO_INT_XINT5);
    GPIO_enableInterrupt(GPIO_INT_XINT5);
    while (num_xint5 < 5)
        ;
    GPIO_disableInterrupt(GPIO_INT_XINT5);

    puts("XINT test passed");
}

void test_gpio(void)
{
    test_gpio_external_int();
}
