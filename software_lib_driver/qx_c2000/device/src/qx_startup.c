/**
 **************************************************************************
 * @file     qx_startup.c
 * @version  v1.0.0
 * @date     2023-12-30
 **************************************************************************
 */

#include "devicelib.h"

extern int main(void);

void __init_bss()
{
    extern char __bss_start;
    extern char __data_end__;
    // init BSS section
    char *i = &__bss_start;
    while (i != &__data_end__)
    {
        *i = 0;
        i++;
    }
}

void system_init(void)
{
    __init_bss();
    main();
}
