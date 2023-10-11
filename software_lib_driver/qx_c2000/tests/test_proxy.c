#include "common.h"

#ifdef QX_C2000_CORE0
void test_func0(void)
{
    int x0 = 0;
    int y0 = 1;
    int z0 = x0 + y0;
    z0++;

    while (1)
    {
        z0 = z0 + x0;
        z0 = z0 - y0;
        z0 = z0 + 1;
    }
}
#endif

#ifdef QX_C2000_CORE1
void test_func0(void)
{
    int x1 = 0;
    int y1 = 1;
    int z1 = x1 + y1;
    z1++;

    while (1)
    {
        z1 = z1 + x1;
        z1 = z1 - y1;
        z1 = z1 + 1;
    }
}
#endif

void test_proxy(void)
{
    test_func0();
}
