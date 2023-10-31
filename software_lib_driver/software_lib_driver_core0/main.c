#include "common.h"
int m = 0;
int arr_stack [100];
float s = 1;
float s1 = 0.2;

static void delay(int cnt) {
	cnt = cnt > 0 ? cnt : 0;
	while(cnt--);
}

int main() {
	int a = 0;
	int b = 0;

	while (1) {
		a += 1;
		a %= 10;

		m += 1;
		m %= 100;

		s ++ ;
		s1 ++;
		s += s1/s;

		arr_stack[m] = m+1;
		//delay(10000);
	}

	return 0;
}

#if 0
int main(void)
{
    Device_init(); // ϵͳʱ��������Device_init��ʵ��

#ifdef FGPA_TEST // FPGA����ʱ, �������ڴ�ӡ֧��, ��0�̶�ʹ��SCIA
    StdOutInitA();
    // ָ��һ��GPIO����Ϊ���Դ��ڴ�ӡ���
    GPIO_Config(29, GPIO_29_SCIA_TX, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
#endif

    puts("Test begain (good luck) ...");

#if 0 // ��Ҫ��֤����һ����ʱ��Ҫʹ��CORE0����CORE1ʱ��
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU1);
    while (1) ;
#endif

#ifdef TEST_SYSCTL
    test_sysctl();
#endif

#ifdef TEST_GPIO
    test_gpio();
#endif

#ifdef TEST_SCI
    test_sci();
#endif

#ifdef TEST_FLASH
    test_flash();
#endif

#ifdef TEST_CAN
    test_can();
#endif

#ifdef TEST_ECAP
    test_ecap();
#endif

#ifdef TEST_HRCAP
    test_hrcap();
#endif

#ifdef TEST_EPWM
    test_epwm();
#endif

#ifdef TEST_EQEP
    test_eqep();
#endif

#ifdef TEST_SPI
    test_spi();
#endif

#ifdef TEST_I2C
    test_i2c();
#endif

#ifdef TEST_DMA
    test_dma();
#endif

#ifdef TEST_WDG
    test_wdg();
#endif

#ifdef TEST_TIMER
    test_timer();
#endif

#ifdef TEST_ADC
    test_adc();
#endif

#ifdef TEST_DAC
    test_dac();
#endif

#ifdef TEST_MEM
    test_mem();
#endif

#ifdef TEST_FSI
    test_fsi();
#endif

#ifdef TEST_PLL
    test_pll();
#endif

#ifdef TEST_XBAR
    test_xbar();
#endif

#ifdef TEST_ISR
    test_isr();
#endif

#ifdef TEST_ASYS
    test_asys();
#endif

#ifdef TEST_DCC
    test_dcc();
    simple_delay(2500);
#endif

#ifdef TEST_PMBUS
    test_pmbus();
#endif

#ifdef TEST_CMPSS
    test_cmpss();
#endif

    EndSimulation();
    return 0;
}
#endif
