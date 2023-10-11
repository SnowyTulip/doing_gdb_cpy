#include "common.h"

static int num_adc_intr = 0, num_adc_evt_intr = 0;
static int event_flag     = 0;
static int adc_result     = 0;
static u8 adc_event_state = 0;
static int x              = 0;

__interrupt void adca2_isr()
{
    puts("intr happends in a");
    num_adc_intr++;
}

__interrupt void adcb2_isr()
{
    puts("intr happends in b");
    num_adc_intr++;
}

__interrupt void adcc2_isr()
{
    puts("intr happends in c");
    num_adc_intr++;
}

__interrupt void adca_evt_isr()
{
    //    puts("event intr happends");
    //    num_adc_evt_intr++;
    //    event_flag = ADC_getPPBEventStatus(ADCA_REGS_BASE);
    //    printf("%d\n", event_flag);
    //    ADC_disablePPBEventInterrupt(ADCA_REGS_BASE, event_flag);
}

// ����ADC�õ�PWM soc�ź�,����epwm�����ﻹ����,�����ɾ��
void pwm_gen_for_adc(u8 ch, u8 count_mode, u16 tbprd, u16 cmp, u16 tbphs, u8 int_type, u32 p_flag)
{
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);
    /* TB */
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    EPWM_setTimeBaseCounterMode(epwm_base, count_mode); /* ����ģʽ  */
    //    EPWM_enablePhaseShiftLoad(uint32_t base)			/* ����TBPHS����TBCTR */
    EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_SHADOW_LOAD); /* ����Ӱ��ģʽ��дTBPRD */
    //    EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_DIRECT_LOAD);     /* ����ֱ��ģʽ��дTBPRD*/
    epwm->TBCTL.bit.SYNCOSEL = 0;      		/* ����EPWMxSYNCO�źţ����ź����ߺ��ʹCTR��תΪTBPHS ע:�ò����ᵼ��ͨ��2����ʱͨ��1��gpio�������, ��Ҫȷ���Ƿ���ȷ */ //00Ӧ�������ã�
    /* SWFSYNC�����ǿ��ͬ�����壬Ӧ���Ƕ�̬�ģ��Ȳ��� */
    epwm->TBCTL.bit.HSPCLKDIV
        = 0; /* TBCLK = SYSTEM_OUT_CLK/(2 * HSPCLKDIV * CLKDIV^2)���ٻ�׼ʱ�ӣ�Ϊ0ʱֻ��CLKDIV���� */
    epwm->TBCTL.bit.CLKDIV = 0; /* TBCLK = SYSTEM_OUT_CLK/(2^CLKDIV)����׼ʱ��, ����TBCLK = SYSTEM_OUT_CLK/2 */
                                /* PHSDIR����λ����λ�����ڵ�������ʱʹ��*/
                                /* FREE_SOFT������ģʽ��������*/

    epwm->TBPHS.bit.TBPHS = tbphs; /* ��λƫ�� */
    epwm->TBPRD           = tbprd; /* ʱ���������� */
    epwm->TBCTR           = 0;     /* ����ʱ�������Ĵ��� */

    /* CC */
    epwm->CMPCTL.bit.SHDWAMODE = 0;
    epwm->CMPCTL.bit.SHDWBMODE = 0;
    //    epwm->CMPCTL.bit.SHDWAMODE = 1;
    //    epwm->CMPCTL.bit.SHDWBMODE = 1;
    epwm->CMPCTL.bit.LOADAMODE = 0;
    epwm->CMPCTL.bit.LOADBMODE = 0;
    epwm->CMPA.bit.CMPA        = cmp;

    /* AQ */
    // ��Ӧ��ֵ1�򴥷����0����Ӧ��ֵ1�򴥷����1
    epwm->AQCTLA.bit.CAU = 2; /* ��CTR=CMPA��Up������ʱ��EPWM1A����ߵ�ƽ */
    epwm->AQCTLA.bit.CAD = 1; /* ��CTR=CMPA��Down������ʱ��EPWM1A����͵�ƽ */
    epwm->AQCTLB.bit.CAU = 2; /* ��CTR=CMPA��Up������ʱ��EPWM1B����ߵ�ƽ */
    epwm->AQCTLB.bit.CAD = 1; /* ��CTR=CMPA��Down������ʱ��EPWM1B����͵�ƽ */

    /* DB */
    epwm->DBCTL.bit.OUT_MODE = 0; /* ������ȫ��· */
    /* PC */
    //    EPWM_enableChopper(epwm_base);	/* ն������ȫ��· */

    /* �Ƿ���жϴ��� */
    if (int_type)
        Interrupt_enable(INT_EPWM1 + ch);
    else
        Interrupt_disable(INT_EPWM1 + ch);

    if (p_flag)
        printf("epwm test -> ch:%d, count_mode:%d, tbprd:%d, cmp:%d, tbphs:%d, int_type:%d\n", ch, count_mode, tbprd,
            cmp, tbphs, int_type);
}

void gen_et_for_adc(u8 ch)
{
    uint32_t epwm_base              = EPWM1_BASE + ch * 0x200;
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);

    epwm->ETSEL.bit.INTSEL  = 1; // ʹ��eq_zero�¼�
    epwm->ETSEL.bit.SOCASEL = 1; // ʹ��eq_zero�¼�
    epwm->ETSEL.bit.SOCBSEL = 1; // ʹ��eq_zero�¼�

    epwm->ETSEL.bit.SOCAEN = 1; // ʹ��SOCA���
    epwm->ETSEL.bit.SOCBEN = 1; // ʹ��SOCA���

    epwm->ETPS.bit.SOCAPRD = 3; // ÿ����3���¼�����һ��SOCA����
    epwm->ETPS.bit.SOCBPRD = 3;
}

extern void timer_setAndStart(CPUTimerReg_types *timer, timer_mode_type timer_mode, u32 time_value, u8 int_flag);

void test_adc(void)
{
    // ����ADCʱ��Ӳ��tbģ���CH�����˼���,����ADC�ɼ�ģ���źſ��Ի�ò�ͬ��ֵ
    puts("adc test start...");
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
    puts("now start adc...");
    ADC_enableConverter(ADCA_REGS_BASE);
    simple_delay(200);

#if 0
    // ���Է�Ƶ
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_8_0);
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    simple_delay(10);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7);
    simple_delay(10);
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_2_0);
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER9, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    simple_delay(10);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER9);
    simple_delay(10);
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_18_0);
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_3);
    simple_delay(10);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2);
    simple_delay(10);
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_4_0);
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER17, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_2);
    simple_delay(10);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER17);
    simple_delay(10);
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_16_0);
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_1);
    simple_delay(10);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4);
    simple_delay(10);
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_14_0);
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    simple_delay(10);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4);
    simple_delay(10);
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_2_0);
#endif

#if 0
    // �����������SOC�Ƿ������ȷ�ɼ�,�������ж�
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7);
    puts("now read adc in result7...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER7);
    printf("7 is 0x%x\n", adc_result);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER10);
    puts("now read adc in result10...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER10);
    printf("10 is 0x%x\n", adc_result);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1);
    puts("now read adc in result1...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER1);
    printf("0x%x\n", adc_result);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2);
    puts("now read adc in result2...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER2);
    printf("0x%x\n", adc_result);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3);
    puts("now read adc in result3...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER3);
    printf("0x%x\n", adc_result);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4);
    puts("now read adc in result4...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN8, ADC_SAMPLE_WINDOW_1);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4);
    puts("now read adc again in result4...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER4);
    printf("0x%x\n", adc_result);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER19, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER19);
    puts("now read adc in result19...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER19);
    printf("0x%x\n", adc_result);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0);
    puts("now read in result0...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER0);
    printf("0x%x\n", adc_result);
#endif

#if 0
    // �����������
    //     ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_18_0);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_5);
    while (1)
    {
        simple_delay(200);
        ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x7);
    }
#endif

#if 0
    // ����ADC�Ĺص�����ʹ�ܸ�λ,���ܲ����ټ���������SOC��ʼ�ɼ�
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN5, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER10);
    puts("now read adc in result10...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER10);
    printf("10 is 0x%x\n", adc_result);
    ADC_disableConverter(ADCA_REGS_BASE);
    simple_delay(100);
    ADC_enableConverter(ADCA_REGS_BASE);
    simple_delay(100);	// ��Ҫ��ADC�������ȶ�
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6);
    puts("now read adc again in result6...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER6);
    printf("0x%x\n", adc_result);

#endif

#if 0
    // ���� SOC�Ƿ������ȷ�����ɼ�,�������ж�,�����ڵ�һ�βɼ�δ���ʱ��������һ��SOC
    puts("tests continuous acquisition");
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0xff);
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_1);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x8f);
    simple_delay(100);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_20);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_20);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x28);
    puts("now start read adc...");
    puts("now read adc in result7...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER7);
    printf("0x%x\n", adc_result);
    puts("now read adc in result0...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER0);
    printf("0x%x\n", adc_result);
    puts("now read adc in result1...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER1);
    printf("0x%x\n", adc_result);
    puts("now read adc in result2...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER2);
    printf("0x%x\n", adc_result);
    puts("now read adc in result3...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER3);
    printf("0x%x\n", adc_result);
    puts("now read adc in result4...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER4);
    printf("0x%x\n", adc_result);
    puts("now read adc in result5...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER5);
    printf("0x%x\n", adc_result);
    puts("now read adc in result6...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER6);
    printf("0x%x\n", adc_result);
#endif

#if 0
    // ��Ӳ���������
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER16, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x100bf);
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER16, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_1);
    simple_delay(50);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 1, 300);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(400);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN14, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER11, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER12, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER13, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_1);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x3c80);
#endif

#if 0
    // ���Լ�ʱ��Ӳ������SOC�Ƿ������ȷ�ɼ�.����Դ�ǳ��죬ʹ��Ҫ�������ֳ���������
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_16_0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_10);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_1);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 1, 300);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    CPUTimer_disableTimer(CPUTimer0Regs);
    CPUTimer_enableTimer(CPUTimer0Regs);
    int temp = AdcaRegs->ADCSOCFLG.all;
    printf("0x%x\n", temp);
    simple_delay(100);
    CPUTimer_enableInterrupt(CPUTimer0Regs);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER0);
    printf("0x%x\n", adc_result);
#endif

#if 0
    // ������Ծ����������SOC���вɼ�.����Դ��������
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_8);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_5);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 500, 2000);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_20_0);
    simple_delay(300);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER6);
    printf("0x%x\n", adc_result);
#endif

#if 0
    // ���������Ϊ����Դʱ�����Ҳ���Դ���SOC�ɼ�
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_8);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_5);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 1, 2000);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x43);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER6);
    printf("0x%x\n", adc_result);
    while (1)
    {
        simple_delay(300);
        ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x43);
    }
#endif

#if 0
    // ���Լ�ʱ����ʹ����PWm����Ҳ�ᴥ��ADC����
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_8);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_8);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_8);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_8);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_8);
    puts("now start timer without PWM...");
    CPUTimer_disablePwm(CPUTimer0Regs);
    timer_setAndStart(CPUTimer0Regs, USER_DEFINED, 400, 0);
    simple_delay(300);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER1);
    printf("0x%x\n", adc_result);
#endif

#if 0
    // ������timer����ʱ�����SOC�Ƿ������ȷ�ɼ����
    // һ������Դ�Ὣ���õ�����SOC������ɼ�һ�飬������һ�βɼ�����ǰ���вɼ������ͬ������
    // �ڲɼ�ǰ�����úô���Դ�����ܻᵼ�������úò���SOC�󴥷�Դ���ǰ���βɼ���ֻ�в���SOC������������SOC�ɼ���˳����ܻ��Ԥ�ڲ���ȫ��ͬ������˳���������
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 2, 500);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_6);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_7);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_8);
    simple_delay(500);
    CPUTimer_disableTimer(CPUTimer0Regs);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_10);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_20);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_30);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_40);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_60);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_70);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_80);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(50);
    CPUTimer_disableTimer(CPUTimer0Regs);
    simple_delay(200);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER7);
    printf("result 7 is 0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER0);
    printf("result 0 is 0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER1);
    printf("result 1 is 0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER2);
    printf("result 2 is 0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER3);
    printf("result 3 is 0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER4);
    printf("result 4 is 0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER5);
    printf("result 5 is 0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER6);
    printf("result 6 is 0x%x\n", adc_result);
#endif

#if 0
    // ��������Ƿ�����ȷ����EOC���ж�,
    // �������û����ADCINT��־����ADCINTFLG�Ĵ����У�֮ǰ������������ADCIINT����
    Interrupt_enable(PIC_GROUP9);
    ADC_setInterruptPulseMode(ADCA_REGS_BASE, ADC_PULSE_END_OF_CONV);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0);
    simple_delay(50);
    printf("intr num is %d\n", num_adc_intr);
#endif

#if 0
    // ���������δ����ж�,�ĸ��ж϶�����һ��
    ADC_setInterruptPulseMode(ADCA_REGS_BASE, ADC_PULSE_END_OF_CONV);
    Interrupt_enable(PIC_GROUP9);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER1);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER3);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER4);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER2);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER3);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER4, ADC_SOC_NUMBER4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN5, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN6, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN7, ADC_SAMPLE_WINDOW_5);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x1f);
    simple_delay(200);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x1f);
    printf("intr num is %d\n", num_adc_intr);
#endif

#if 0
    // ����INTCONTΪ1ʱ,�Ƿ�ÿ��EOC��������ж����壬�����ж����ж��������
    ADC_setInterruptPulseMode(ADCA_REGS_BASE, ADC_PULSE_END_OF_CONV);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER2);
//    ADC_enableContinuousMode(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_disableContinuousMode(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER7);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE,ADC_SOC_NUMBER7);
    puts("now read adc in result7...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER7);
    printf("7 is 0x%x\n", adc_result);
    simple_delay(50);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER0);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE,ADC_SOC_NUMBER0);
    puts("now read adc in result0...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER0);
    printf("0 is 0x%x\n", adc_result);
    ADC_clearInterruptOverflowStatus(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_clearInterruptStatus(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE,ADC_SOC_NUMBER1);
    puts("now read adc again in result1...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER1);
    printf("1 is 0x%x\n", adc_result);
    //	ADC_clearInterruptStatus(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER4, ADC_SOC_NUMBER2);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_5);
    ADC_forceSOC(ADCA_REGS_BASE,ADC_SOC_NUMBER2);
    simple_delay(50);
    printf("intr num is %d\n", num_adc_intr);
#endif

#if 0
    // ����Ӳ��timer�����ж�,��һ��ʱ����ж�����ģʽ
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    ADC_setInterruptPulseMode(ADCA_REGS_BASE, ADC_PULSE_END_OF_CONV);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_4);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 2, 50);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    ADC_enableContinuousMode(ADCA_REGS_BASE, ADC_INT_NUMBER4);
#endif

#if 0
    // ����timer�����ж����ж����
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_setInterruptPulseMode(ADCA_REGS_BASE, ADC_PULSE_END_OF_CONV);
    ADC_enableContinuousMode(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    //	ADC_disableContinuousMode(ADCA_REGS_BASE);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_4);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 2, 50);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    x = ADC_getInterruptOverflowStatus(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    printf("intr num is %d and overflow status is %d\n", num_adc_intr, x);
    ADC_clearInterruptOverflowStatus(ADCA_REGS_BASE, ADC_INT_NUMBER2);
#endif

#if 0
    // ������timer����ʱ�����SOC�Ƿ������ȷ�ɼ���ͨ����Դ���ź�
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 2, 50);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    simple_delay(500);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER14, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN0, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER15, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER16, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER17, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER18, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER19, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN5, ADC_SAMPLE_WINDOW_5);
//    simple_delay(200);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER8, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN6, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER9, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN7, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_5);
    simple_delay(300);
#endif

#if 0
    // ���Ժ���ģ��,��ȡ�Ӻ�SOC�ɼ���ʱ���
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER2, ADC_SOC_NUMBER6);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER4, ADC_SOC_NUMBER16);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_6);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_8);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_7);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_10);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER16, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_50);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x100fd);
    simple_delay(50);
    x = ADC_getPPBDelayTimeStamp(ADCA_REGS_BASE, ADC_PPB_NUMBER1);
    printf("delay TimeStamp is %d\n", x);
    x = ADC_getPPBDelayTimeStamp(ADCA_REGS_BASE, ADC_PPB_NUMBER2);
	printf("delay TimeStamp is %d\n", x);
	x = ADC_getPPBDelayTimeStamp(ADCA_REGS_BASE, ADC_PPB_NUMBER4);
	printf("delay TimeStamp is %d\n", x);
#endif

#if 0
    // ���Ժ���ģ��,ƫ����OFFREF�Ƿ���ȷ����
    ADC_disablePPBTwosComplement(ADCA_REGS_BASE, ADC_PPB_NUMBER1);
//	ADC_enablePPBTwosComplement(ADCA_REGS_BASE, ADC_PPB_NUMBER1);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER1);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER1, 0x1);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0x1);
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN7, ADC_SAMPLE_WINDOW_8);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x403);
    simple_delay(100);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER1, 0xf);
    simple_delay(10);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER2);
    simple_delay(50);
#endif

#if 0
    // ���Ժ���ģ��,ƫ����OFFCAL�Ƿ���ȷ����
//    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_16_0);
    ADC_disablePPBTwosComplement(ADCA_REGS_BASE, ADC_PPB_NUMBER1);
    //	ADC_enablePPBTwosComplement(ADCA_REGS_BASE);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER1);
    ADC_setPPBCalibrationOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER1, 0x3fa);
    simple_delay(300);
//    ADC_disableInterrupt(ADCA_REGS_BASE);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN18, ADC_SAMPLE_WINDOW_3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN18, ADC_SAMPLE_WINDOW_3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER13, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER16, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN7, ADC_SAMPLE_WINDOW_3);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x12007);
    simple_delay(100);
    ADC_setPPBCalibrationOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER1, 0xf);
    simple_delay(10);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER16);
    simple_delay(10);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x12006);
#endif

#if 0
    // ���Ժ���ģ��,OFFREF��OFFCALͬʱʹ���Ƿ����ȷ����
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER1);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER1, 0x5);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0x8);
    ADC_setPPBCalibrationOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER1, 0x3ff);
    ADC_setPPBCalibrationOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0x3fe);
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN7, ADC_SAMPLE_WINDOW_8);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x403);
//    simple_delay(100);
//    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER1, 0xf);
    simple_delay(10);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER0);
    simple_delay(50);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x403);
#endif

#if 0
    // ���������¼��Ƿ���Է���,�������Ƿ���ȷ��ȡ,�ܷ���ȷ���,�������¼��ж�
    // ����CBCEN�����Ƿ���ȷ
//	ADC_enablePPBEventCBCClear(ADCA_REGS_BASE, ADC_PPB_NUMBER1);
    ADC_disablePPBEventCBCClear(ADCA_REGS_BASE, ADC_PPB_NUMBER3);
    ADC_disablePPBTwosComplement(ADCA_REGS_BASE, ADC_PPB_NUMBER3);
    ADC_setPPBTripLimits(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x10, -0x08);
    ADC_enablePPBEvent(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x7);
    ADC_disablePPBEventInterrupt(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x7);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER3, ADC_SOC_NUMBER1);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x1);
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN18, ADC_SAMPLE_WINDOW_2);
    ADC_forceSOC(ADCA_REGS_BASE,ADC_SOC_NUMBER1);
    simple_delay(100);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x10);
    simple_delay(100);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x30);
    ADC_clearPPBEventStatus(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x7);
    simple_delay(50);
    ADC_setPPBTripLimits(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x10, -0x20);
    simple_delay(50);
    adc_event_state = ADC_getPPBEventStatus(ADCA_REGS_BASE, ADC_PPB_NUMBER3);
    printf("adc event state is %x\n", adc_event_state);
    ADC_clearPPBEventStatus(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x7);
    adc_event_state = ADC_getPPBEventStatus(ADCA_REGS_BASE, ADC_PPB_NUMBER3);
    printf("adc event state is %x\n", adc_event_state);
#endif

#if 0
//    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_4_0);
    //��֤���PPBģ�齻��
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER3, ADC_SOC_NUMBER1);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0x5);		//-5
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x8);		//-8
    ADC_setPPBCalibrationOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0x3ff);	//+1
    ADC_setPPBCalibrationOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x3fe);	//+2
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_5);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN7, ADC_SAMPLE_WINDOW_8);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x403);
    simple_delay(50);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x403);
#endif

#if 0
    // �����¼��ж��Ƿ������ȷ����
    Interrupt_enable(PIC_GROUP3);
    ADC_setInterruptPulseMode(ADCA_REGS_BASE, ADC_PULSE_END_OF_CONV);
    ADC_disablePPBTwosComplement(ADCA_REGS_BASE, ADC_PPB_NUMBER2);
    ADC_setPPBTripLimits(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0x10, -0x08);
    ADC_enablePPBEvent(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0x7);
    ADC_enablePPBEventInterrupt(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0x7);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER2, 0xa);
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN7, ADC_SAMPLE_WINDOW_2);
    simple_delay(300);
#endif

#if 0
    // ���Զ��ADCͬʱ�ɼ���timer����
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER1);
    puts("now start adcB...");
    ADC_enableConverter(ADCB_REGS_BASE);
    simple_delay(200);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT1, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT1, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT1, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT1, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCB_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT1, ADC_CH_ADCIN6, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCB_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT1, ADC_CH_ADCIN6, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCB_REGS_BASE, ADC_SOC_NUMBER8, ADC_TRIGGER_CPU0_TINT1, ADC_CH_ADCIN6, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCB_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT1, ADC_CH_ADCIN6, ADC_SAMPLE_WINDOW_2);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer1Regs);
    CPUTimer_initPwm(CPUTimer1Regs, CPUTimer1PwmRegs, USER_DEFINED, 5, 1500);
    CPUTimer_enableTimer(CPUTimer1Regs);
    simple_delay(300);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER1);
    printf("0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCB_RESULT_BASE, ADC_SOC_NUMBER6);
    printf("0x%x\n", adc_result);
#endif

#if 0
    // ���Զ��ADCͬʱ�����жϣ���������ݲ�����,���ж��޸����ٴ���
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    Interrupt_enable(PIC_GROUP3);
    puts("now start adcB...");
    ADC_enableConverter(ADCB_REGS_BASE);
    simple_delay(300);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER3);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER1);
    ADC_enableInterrupt(ADCB_REGS_BASE, ADC_INT_NUMBER3);
    ADC_setInterruptSource(ADCB_REGS_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_3);
    ADC_setupSOC(ADCB_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_3);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, FREE_RUNNING, 2, 50);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER1);
    printf("A is 0x%x\n", adc_result);
    adc_result = ADC_readResult(ADCB_RESULT_BASE, ADC_SOC_NUMBER1);
    printf("B is 0x%x\n", adc_result);
    printf("adc intr num is %d\n", num_adc_intr);
#endif

#if 0
    // ���������ɼ�ģʽ���Լ������ɼ�ģʽ�ϵ��ĸ�λ
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    AdcaRegs->ADCCTL.bit.MODE = 1;
    simple_delay(50);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN1);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 1, 500);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(3000);
    puts("end timer or mode...");
    CPUTimer_disableTimer(CPUTimer0Regs);
    simple_delay(300);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(100);
    AdcaRegs->ADCCTL.bit.MODE = 0;
    simple_delay(100);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN2);
    ADC_disableConverter(ADCA_REGS_BASE);
#endif

#if 0
    // ����EPWM���봥��ADC
    u8 epwm_num = 2; // epwm3
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (epwm_num << 8));
    CpuSysRegs->PCLKCR0.bit.TBCLKSYNC = 0;
    pwm_gen_for_adc(epwm_num, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 10000 / 2, SYS_CLK / 10000 / 4, 0, 0, 1);
    gen_et_for_adc(epwm_num);
    CpuSysRegs->PCLKCR0.bit.TBCLKSYNC = 1;
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_EPWM3_SOCA, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_EPWM3_SOCA, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM3_SOCA, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM3_SOCA, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_EPWM3_SOCA, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_EPWM3_SOCA, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_EPWM3_SOCA, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_EPWM3_SOCA, ADC_CH_ADCIN5, ADC_SAMPLE_WINDOW_2);
    simple_delay(300);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER7);
    printf("0x%x\n", adc_result);
#endif

#if 0
    // ����GPIO���봥��ADC
    simple_delay(200);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_GPIO, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_GPIO, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_GPIO, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    simple_delay(200);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER5);
    printf("0x%x\n", adc_result);
    XBAR_setInputPin(XBAR_INPUT5, XBAR_INPUT_GPIO5);
    simple_delay(1000);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER16, ADC_TRIGGER_GPIO, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER17, ADC_TRIGGER_GPIO, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER18, ADC_TRIGGER_GPIO, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER11, ADC_TRIGGER_GPIO, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER12, ADC_TRIGGER_GPIO, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_2);
    simple_delay(300);
    puts("now read adc...");
    adc_result = ADC_readResult(ADCA_RESULT_BASE, ADC_SOC_NUMBER7);
    printf("0x%x\n", adc_result);
#endif

#if 0
    // Ӳ�������ɼ�SOC��������SOC��������ɼ�
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU0_TIMER0);
    puts("now start timer...");
    CPUTimer_disableInterrupt(CPUTimer0Regs);
    CPUTimer_initPwm(CPUTimer0Regs, CPUTimer0PwmRegs, USER_DEFINED, 3000, 3000);
    CPUTimer_enableTimer(CPUTimer0Regs);
    simple_delay(300);
    ADC_disableInterrupt(ADCA_REGS_BASE);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN3);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER13, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN19);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER16, ADC_TRIGGER_CPU0_TINT0, ADC_CH_ADCIN319);
    simple_delay(500);
#endif

#if 0
//���Ը�λ
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_1);
	simple_delay(200);
	ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x7);
	simple_delay(100);
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ADCA);
#endif

#if 0
    //������busy�źŴ��ڣ�������ʱ��������ͨ��������ʱע�͵���Ϊ�˲���ʱ��Υ��
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_60_0);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_40);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, ADC_SAMPLE_WINDOW_40);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x3);
    simple_delay(1);
    AdcaRegs->ADCSOC0CTL.bit.CHSEL = ADC_CH_ADCIN5;
    AdcaRegs->ADCSOC1CTL.bit.CHSEL = ADC_CH_ADCIN5;
#endif

#if 0
    // ��֤ADC��λ���ٴ��������Ƿ�����
    ADC_disablePPBEventCBCClear(ADCA_REGS_BASE, ADC_PPB_NUMBER3);
    ADC_disablePPBTwosComplement(ADCA_REGS_BASE, ADC_PPB_NUMBER3);
    ADC_setPPBTripLimits(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x10, -0x08);
    ADC_enablePPBEvent(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x7);
    ADC_disablePPBEventInterrupt(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x7);
    ADC_setupPPB(ADCA_REGS_BASE, ADC_PPB_NUMBER3, ADC_SOC_NUMBER1);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x1);
    simple_delay(300);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN18, ADC_SAMPLE_WINDOW_2);
    ADC_forceSOC(ADCA_REGS_BASE,ADC_SOC_NUMBER1);
    simple_delay(100);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x10);
    simple_delay(100);
    ADC_setPPBReferenceOffset(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x30);
    ADC_clearPPBEventStatus(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x7);
    simple_delay(50);
    ADC_setPPBTripLimits(ADCA_REGS_BASE, ADC_PPB_NUMBER3, 0x10, -0x20);
    simple_delay(50);
    adc_event_state = ADC_getPPBEventStatus(ADCA_REGS_BASE, ADC_PPB_NUMBER3);
    printf("adc event state is %x\n", adc_event_state);
    simple_delay(100);
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ADCA);
    simple_delay(500);
    ADC_enableConverter(ADCA_REGS_BASE);
    simple_delay(200);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN19, ADC_SAMPLE_WINDOW_3);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x6);
#endif

#if 0
    // ��֤ADC�����ж�ģʽ
    ADC_setPrescaler(ADCA_REGS_BASE, ADC_CLK_DIV_8_0);
    ADC_setInterruptPulseMode(ADCA_REGS_BASE, ADC_PULSE_END_OF_ACQ_WIN);
//    ADC_setInterruptPulseMode(ADCA_REGS_BASE, ADC_PULSE_END_OF_CONV);
    ADC_enableContinuousMode(ADCA_REGS_BASE, ADC_INT_NUMBER2);
//    ADC_setInterruptCycleOffset(ADCA_REGS_BASE, 0x100);
//    ADC_setInterruptCycleOffset(ADCA_REGS_BASE, 0x1);
    ADC_setInterruptCycleOffset(ADCA_REGS_BASE, 0x0);
    Interrupt_enable(PIC_GROUP9);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER1);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER2);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER3);
    ADC_enableInterrupt(ADCA_REGS_BASE, ADC_INT_NUMBER4);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER3);
    ADC_setInterruptSource(ADCA_REGS_BASE, ADC_INT_NUMBER4, ADC_SOC_NUMBER4);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, ADC_SAMPLE_WINDOW_2);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, ADC_SAMPLE_WINDOW_7);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN5, ADC_SAMPLE_WINDOW_30);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN6, ADC_SAMPLE_WINDOW_40);
    ADC_setupSOC(ADCA_REGS_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN7, ADC_SAMPLE_WINDOW_50);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x1f);
    simple_delay(200);
    ADC_forceMultipleSOC(ADCA_REGS_BASE, 0x1f);
    printf("intr num is %d\n", num_adc_intr);
#endif
    while (1)
        ;
}
