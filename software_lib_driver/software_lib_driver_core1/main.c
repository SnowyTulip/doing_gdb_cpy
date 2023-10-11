#include "common.h"

int i = 0;

int main(void)
{
#ifdef FGPA_TEST // FPGA调试时, 开启串口打印支持, 核1固定使用SCIB
    StdOutInitB();
    // 指定一个GPIO口作为调试串口打印输出
    GPIO_Config(40, GPIO_40_SCIB_TX, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
#endif

    puts("CPU1 test begain...");

    test_wdg();

#if 0
    while (1)
        printf("CPU1: %d\n", i++);
#else
    EndSimulation();
#endif
    return 0;
}
