#include "common.h"

#include <stdlib.h>

// ʹ���ⲿX1ʱ��(10Mhz) ��Ƶ�� 26.66Mhz(Minimum)
#define XTAL_WITH_PLL_CLK_26M \
    (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(40) | SYSCTL_FMULT(1) | SYSCTL_ODIV(15) | SYSCTL_SYSDIV(0) | SYSCTL_PLL_ENABLE)
// ʹ���ⲿX1ʱ��(10Mhz) ��Ƶ�� 50Mhz
#define XTAL_WITH_PLL_CLK_50M \
    (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(50) | SYSCTL_FMULT(1) | SYSCTL_ODIV(10) | SYSCTL_SYSDIV(0) | SYSCTL_PLL_ENABLE)
// ʹ���ⲿX1ʱ��(10Mhz) ��Ƶ�� 200Mhz
#define XTAL_WITH_PLL_CLK_200M \
    (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(40) | SYSCTL_FMULT(1) | SYSCTL_ODIV(2) | SYSCTL_SYSDIV(0) | SYSCTL_PLL_ENABLE)
// ʹ���ⲿX1ʱ��(10Mhz) ��Ƶ�� 400Mhz
#define XTAL_WITH_PLL_CLK_400M \
    (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(40) | SYSCTL_FMULT(1) | SYSCTL_ODIV(1) | SYSCTL_SYSDIV(0) | SYSCTL_PLL_ENABLE)
// ʹ���ڲ�OSC1ʱ��(10Mhz) ��Ƶ�� 100Mhz
#define OSC1_WITH_PLL_CLK_100M \
    (SYSCTL_OSCSRC_xOSC2 | SYSCTL_IMULT(40) | SYSCTL_FMULT(1) | SYSCTL_ODIV(4) | SYSCTL_SYSDIV(0) | SYSCTL_PLL_ENABLE)

// ��Ҫʹ�ó���Ĭ��OSC1��10Mhzʱ������ʱ, �⿪ע��
// #define USE_PLL

// �豸��ʼ�������ӿ�
void Device_init(void)
{
#ifdef USE_PLL // ʹ��PLL��Ƶ�����ʱ��Ƶ��
    // ע��:flash���֧��ʱ��133Mhz, Ĭ��ʹ��sysclk�Ҳ���Ƶ, ���PLL����ʱ�Ӵ���133Mhz, ��Ҫ������flash��Ƶ
    // Flash_setClkDiv(4);
    SysCtl_setClock(XTAL_WITH_PLL_CLK_26M);            // ע��: FPGA����ʱSysCtl_setClock��Ȼ��Ч
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_1); // ����ʱ�ӷ�ƵΪ1 (Ĭ��4)
#else                                                  // ʹ��ϵͳ�ڲ�OSC1Ĭ��ʱ��, ������PLL
    SysCtl_setPLLSysClk(0); // Ĭ��CPU��AXIʱ��Ϊ2.5Mhz(4��Ƶ), ��������Ϊ1����ߵ�10MHz
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_1); // ����ʱ�ӷ�ƵΪ1 (Ĭ��4)
#endif
}

int Device_verifyXTAL(float freq)
{
    // Use DCC to verify the XTAL frequency using INTOSC2 as reference clock
    // Turn on XTAL and wait for it to power up using X1CNT
    // SysCtl_turnOnOsc(SYSCTL_OSCSRC_XTAL);
    // SysCtl_clearExternalOscCounterValue();
    // while (SysCtl_getExternalOscCounterValue() != SYSCTL_X1CNT_X1CNT_M)
    //     ;

    // Enable DCC0 clock
    // SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCC0);

    // Insert atleast 5 cycles delay after enabling the peripheral clock
    // asm(" RPT #5 || NOP");

    // Configures XTAL as CLKSRC0 and INTOSC2 as CLKSRC1
    // Fclk0 = XTAL frequency (input parameter)
    // Fclk1 = INTOSC2 frequency = 10MHz
    // Configuring DCC error tolerance of +/-1%
    // INTOSC2 can have a variance in frequency of +/-10%
    // Assuming PLL is not already configured, SysClk freq = 10MHz
    // Note : Update the tolerance and INTOSC2 frequency variance as necessary.
    // return (DCC_verifyClockFrequency(
    //     DCC0_BASE, DCC_COUNT1SRC_INTOSC2, 10.0F, DCC_COUNT0SRC_XTAL, freq, 1.0F, 10.0F, 10.0F));
    return 0;
}

void SysCtl_enablePeripheralAll(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_HRPWM);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM8);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EQEP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EQEP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SD1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PGA7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_LINA);
}

void SysCtl_disablePeripheralAll(void)
{
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_DMA);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER1);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER2);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER0);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER1);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CPU1_TIMER2);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_HRPWM);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM2);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM3);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM4);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM5);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM6);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM7);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM8);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_ECAP1);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_ECAP2);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_ECAP3);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_ECAP4);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_ECAP5);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_ECAP6);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_ECAP7);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EQEP1);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EQEP2);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_SD1);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_SCIA);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_SCIB);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_SPIB);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_I2CA);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CANA);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CANB);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_ADCB);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_ADCC);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CMPSS1);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CMPSS2);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CMPSS3);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CMPSS4);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CMPSS5);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CMPSS6);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_CMPSS7);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_PGA1);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_PGA2);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_PGA3);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_PGA4);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_PGA5);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_PGA6);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_PGA7);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_DACA);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_DACB);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_LINA);
}

void __error__(const char *filename, uint32_t line)
{
    printf("assert error at %s:%d\n", filename, line);
    ESTOP0;
}
