#include "common.h"

int i = 0;

int main(void)
{
#ifdef FGPA_TEST // FPGA����ʱ, �������ڴ�ӡ֧��, ��1�̶�ʹ��SCIB
    StdOutInitB();
    // ָ��һ��GPIO����Ϊ���Դ��ڴ�ӡ���
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
