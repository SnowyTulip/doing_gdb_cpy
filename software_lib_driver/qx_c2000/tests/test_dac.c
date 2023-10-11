#include "common.h"

static u16 value = 0;

extern void pwm_gen_for_adc(u8 ch, u8 count_mode, u16 tbprd, u16 cmp, u16 tbphs, u8 int_type, u32 p_flag);
extern void gen_et_for_adc(u8 ch);

void init_dac(uint32_t base, DAC_ReferenceVoltage source, DAC_GainMode mode, DAC_LoadMode loadmode, DAC_SyncSel sync)
{
    DAC_setReferenceVoltage(base, source);
    DAC_setGainMode(base, mode);
    DAC_setLoadMode(base, loadmode);
    if (loadmode)
        DAC_setPWMSyncSignal(base, sync);
    DAC_enableOutput(base);
}

void test_dac(void)
{
    puts("DAC tests start...");
    DacaRegs->DACCTL.bit.PRESCALE = 60; // ����DAC��Ҫ������5MHz��ʱ�ӣ������ڿ���DACʱ��ǰ��Ҫ�ȷ�ƵDAC��ʱ�ӵ�5M����
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACA);

#if 0
    // ����DAC�����ܷ���ȷ�ͳ�
    init_dac(DACA_BASE, DAC_REF_VDAC, DAC_GAIN_ONE, DAC_LOAD_SYSCLK, 0);
    simple_delay(150);
    DAC_setShadowValue(DACA_BASE, 0xaa);
#endif

#if 0
    // �����������ܲ���д,���������Զ��Ѿ������Ĳ��֣����Ǹ�λ�ⲻ�ܽ���
    init_dac(DACA_BASE, DAC_REF_VDAC, DAC_GAIN_ONE, DAC_LOAD_SYSCLK, 0);
    simple_delay(150);
    DAC_setShadowValue(DACA_BASE, 0x55);
    simple_delay(200);
    DAC_disableOutput(DACA_BASE);
    DAC_lockRegister(DACA_BASE, 0x4);
    simple_delay(100);
    DAC_lockRegister(DACA_BASE, 0x3);
    simple_delay(100);
    int islock = DAC_isRegisterLocked(DACA_BASE, 0x7);
    printf("the lock state is %d ...\n", islock);
    DAC_enableOutput(DACA_BASE);
    DAC_setShadowValue(DACA_BASE, 0x77);
    simple_delay(200);
    value = DAC_getActiveValue(DACA_BASE);
    printf("the active value is 0x%x ...\n", value);
#endif

#if 0
    // ����key���Կ��������Ƿ񻹻�ɹ�
    // ���ڵ�ѹû���趨ΪDAC_REF_ADC_VREFHI����������ģʽ�趨Ϊ2��Ч������Ϊ1
    init_dac(DACA_BASE, DAC_REF_VDAC, DAC_GAIN_TWO, DAC_LOAD_SYSCLK, 0);
    simple_delay(150);
    DAC_setShadowValue(DACA_BASE, 0xaa);
    simple_delay(200);
    DAC_disableOutput(DACA_BASE);
    DacaRegs->DACLOCK.all = 0xb007;
    simple_delay(100);
    int islock = DAC_isRegisterLocked(DACA_BASE, 0x7);
    printf("the lock state is %d ...\n", islock);
    DAC_enableOutput(DACA_BASE);
    DAC_setShadowValue(DACA_BASE, 0x77);
    simple_delay(200);
    value = DAC_getActiveValue(DACA_BASE);
    printf("the active value is 0x%x ...\n", value);
#endif

#if 0
    // ��������ģʽ�Ƿ�ᷢ��
    init_dac(DACA_BASE, DAC_REF_ADC_VREFHI, DAC_GAIN_TWO, DAC_LOAD_SYSCLK, 0);
    simple_delay(150);
    DAC_setShadowValue(DACA_BASE, 0xaa);
#endif

#if 0
    // ���Կ�д����д
    //    init_dac(DACA_BASE, DAC_REF_ADC_VREFHI, DAC_GAIN_TWO, DAC_LOAD_SYSCLK, 0);
    init_dac(DACA_BASE, DAC_REF_ADC_VREFHI, DAC_BYPASS, DAC_LOAD_SYSCLK, 0);
    simple_delay(150);
    DAC_setShadowValue(DACA_BASE, 0xaa);
    DAC_setShadowValue(DACA_BASE, 0xbb); // busyд����ȥ
    simple_delay(200);
    value = DAC_getActiveValue(DACA_BASE);
    printf("the active value is 0x%x ...\n", value);
    DAC_setShadowValue(DACA_BASE, 0x55);
    DAC_setShadowValue(DACA_BASE, 0x66);
    DAC_setShadowValue(DACA_BASE, 0x77); // busyд����ȥ
    simple_delay(200);
    value = DAC_getActiveValue(DACA_BASE);
    printf("the active value is 0x%x ...\n", value);
    DAC_setShadowValue(DACA_BASE, 0xbb);
    DAC_setShadowValue(DACA_BASE, 0xcc);
    DAC_setShadowValue(DACA_BASE, 0xdd);
    DAC_setShadowValue(DACA_BASE, 0xee);
    DAC_setShadowValue(DACA_BASE, 0xff);
    simple_delay(100);
    DacaRegs->DACVALS.bit.DACVALS = 0x12;
    DacaRegs->DACVALS.bit.DACVALS = 0x23;
    DacaRegs->DACVALS.bit.DACVALS = 0x34;
    DacaRegs->DACVALS.bit.DACVALS = 0x45;
    value                         = DAC_getActiveValue(DACA_BASE);
    printf("the active value is 0x%x ...\n", value);
#endif

#if 0
    // �޸�DACƫ��΢��
    // ���ǿ����������ļ���ȷָ�������򲻵��޸Ĵ˼Ĵ������޸Ĵ˼Ĵ��������ݿ��ܵ��´�ģ�������ݱ�淶֮�����У���ֻ�����ܷ��޸ĳɹ�
    init_dac(DACA_BASE, DAC_REF_VDAC, DAC_GAIN_ONE, DAC_LOAD_SYSCLK, 0);
    simple_delay(150);
    DacaRegs->DACTRIM.bit.OFFSET_TRIM = 0x22;
    DAC_setShadowValue(DACA_BASE, 0x44);
    simple_delay(200);
    DAC_tuneOffsetTrim(DACA_BASE, 5.0);
#endif

#if 0
    // epwmͬ���ź�
    u8 epwm_num = 2; // epwm3
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (epwm_num << 8));
    CpuSysRegs->PCLKCR0.bit.TBCLKSYNC = 1;
    pwm_gen_for_adc(epwm_num, EPWM_COUNTER_MODE_UP_DOWN, 200, 100, 0, 0, 1);
    gen_et_for_adc(epwm_num);
    init_dac(DACA_BASE, DAC_REF_VDAC, DAC_GAIN_ONE, DAC_LOAD_PWMSYNC, EPWM3SYNCPER);
    simple_delay(150);
    DAC_setShadowValue(DACA_BASE, 0xaa);
    simple_delay(50);
    value = DAC_getActiveValue(DACA_BASE);
    printf("the active value is 0x%x ...\n", value);
    DAC_setShadowValue(DACA_BASE, 0x55);
    DAC_setShadowValue(DACA_BASE, 0x66);
    DAC_setShadowValue(DACA_BASE, 0x77);
    DAC_setShadowValue(DACA_BASE, 0x88);
    DAC_setShadowValue(DACA_BASE, 0x99);
    DAC_setShadowValue(DACA_BASE, 0x11);
    DAC_setShadowValue(DACA_BASE, 0x22);
#endif

#if 0
    // ����DAC��Ƶ
    simple_delay(120);
    DacaRegs->DACCTL.bit.PRESCALE = 2;
    simple_delay(50);
    DacaRegs->DACCTL.bit.PRESCALE = 7;
    simple_delay(50);
    DacaRegs->DACCTL.bit.PRESCALE = 1;
    simple_delay(50);
    DacaRegs->DACCTL.bit.PRESCALE = 39;
    simple_delay(50);
    DacaRegs->DACCTL.bit.PRESCALE = 18;
    simple_delay(50);
#endif

#if 0
    // ����DAC Trim
    // DAC_setOffsetTrim(DACA_BASE, 0x10);	//+0x10
    DAC_setOffsetTrim(DACA_BASE, 0x90); //-0x10
    init_dac(DACA_BASE, DAC_REF_VDAC, DAC_GAIN_TWO, DAC_LOAD_SYSCLK, 0);
    simple_delay(200);
    DAC_setShadowValue(DACA_BASE, 0xaa);
    DAC_setShadowValue(DACA_BASE, 0xbb);
    DAC_setShadowValue(DACA_BASE, 0xcc);
    DAC_setShadowValue(DACA_BASE, 0xdd);
#endif

#if 0
    // ����DAC��λ
    DacaRegs->DACCTL.bit.PRESCALE = 7;
    init_dac(DACA_BASE, DAC_REF_VDAC, DAC_GAIN_ONE, DAC_LOAD_SYSCLK, 0);
    simple_delay(150);
    DAC_setShadowValue(DACA_BASE, 0xaa);
    simple_delay(200);
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_DACA);
#endif

#if 0
    // ����DAC�����1һ��λ
    SysCtl_selectCPUForPeripheralInstance(SYSCTL_CPUSEL_DACA, SYSCTL_CPUSEL_CPU1);
    DacaRegs->DACCTL.bit.PRESCALE = 7;
    init_dac(DACA_BASE, DAC_REF_VDAC, DAC_GAIN_ONE, DAC_LOAD_SYSCLK, 0);
    simple_delay(150);
    DAC_setShadowValue(DACA_BASE, 0xaa);
    simple_delay(300);
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_CPU1);
#endif

    while (1)
        ;
}
