#include "common.h"

#define EPWM_NUM 8

char int_flag[8] = { 0 };

// ======================================�жϴ�����===================================================

static void epwm_tz_isr_common(char ch)
{
    printf("epwm%x_tz_isr\n", ch); // �䵱ʱ�ӣ����㿴����
    struct EPWM_REGS *EPwmRegs = (struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);

    EPwmRegs->TZCLR.bit.INT = 1; // ���INT�ź�
    EPwmRegs->TZCLR.bit.OST = 1; // ���OST�ź�
    EPwmRegs->TZCLR.bit.CBC = 1; // ���CBC�ź�
    // EPWM_clearTripZoneFlag((int)EPwmRegs, EPWM_TZ_FLAG_DCBEVT1); // ֻ����flg����tz״̬���ÿ���������
    int_flag[ch] = 1;
}

// tz�жϴ�����
__interrupt void epwm1_tz_isr(void)
{
    epwm_tz_isr_common(0);
}

__interrupt void epwm2_tz_isr(void)
{
    epwm_tz_isr_common(1);
}

__interrupt void epwm3_tz_isr(void)
{
    epwm_tz_isr_common(2);
}

__interrupt void epwm4_tz_isr(void)
{
    epwm_tz_isr_common(3);
}

__interrupt void epwm5_tz_isr(void)
{
    epwm_tz_isr_common(4);
}

__interrupt void epwm6_tz_isr(void)
{
    epwm_tz_isr_common(5);
}

__interrupt void epwm7_tz_isr(void)
{
    epwm_tz_isr_common(6);
}

__interrupt void epwm8_tz_isr(void)
{
    epwm_tz_isr_common(7);
}

// et�жϴ�����
static void epwm1_isr_common(char ch)
{
    printf("epwm%x_isr\n", ch);
    struct EPWM_REGS *EPwmRegs = (struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);

    EPwmRegs->ETCLR.bit.INT = 1; // ���ET��INT�ź�
    int_flag[ch]            = 1;
}

__interrupt void epwm1_isr(void)
{
    epwm1_isr_common(0);
}

__interrupt void epwm2_isr(void)
{
    epwm1_isr_common(1);
}

__interrupt void epwm3_isr(void)
{
    epwm1_isr_common(2);
}

__interrupt void epwm4_isr(void)
{
    epwm1_isr_common(3);
}

__interrupt void epwm5_isr(void)
{
    epwm1_isr_common(4);
}

__interrupt void epwm6_isr(void)
{
    epwm1_isr_common(5);
}

__interrupt void epwm7_isr(void)
{
    epwm1_isr_common(6);
}

__interrupt void epwm8_isr(void)
{
    epwm1_isr_common(7);
}

// ==============================================================================================

void pwm_normal_gen(u8 ch, u8 count_mode, u16 tbprd, u16 cmp, u16 tbphs, u8 int_type, u32 p_flag)
{
    // volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch *0x200);
    // TB
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    EPWM_setTimeBaseCounterMode(epwm_base, count_mode); // ����ģʽ
    // EPWM_enablePhaseShiftLoad(uint32_t base)   // ����TBPHS����TBCTR
    EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_SHADOW_LOAD); // ����Ӱ��ģʽ��дTBPRD
    // EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_DIRECT_LOAD);     // ����ֱ��ģʽ��дTBPRD
    // epwm->TBCTL.bit.SYNCOSEL = 0;        // ����EPWMxSYNCO�źţ����ź����ߺ��ʹCTR��תΪTBPHS
    EPWM_setSyncOutPulseMode(epwm_base, EPWM_SYNC_OUT_PULSE_ON_EPWMxSYNCIN);
    // SWFSYNC�����ǿ��ͬ�����壬Ӧ���Ƕ�̬�ģ��Ȳ���
    // epwm->TBCTL.bit.HSPCLKDIV = 1;       /* TBCLK = SYSTEM_OUT_CLK/(2 * HSPCLKDIV *
    // 2^CLKDIV)���ٻ�׼ʱ�ӣ�Ϊ0ʱֻ��CLKDIV���� */ epwm->TBCTL.bit.CLKDIV    = 2; // TBCLK = SYSTEM_OUT_CLK/(2^CLKDIV)
    EPWM_setClockPrescaler(epwm_base, 2, 1);
    // PHSDIR����λ����λ�����ڵ�������ʱʹ��
    // FREE_SOFT������ģʽ��������

    // epwm->TBPHS.bit.TBPHS     = tbphs;
    EPWM_setPhaseShift(epwm_base, tbphs); // ��λƫ��
    // epwm->TBPRD               = tbprd;
    EPWM_setTimeBasePeriod(epwm_base, tbprd); // ʱ����������
    // epwm->TBCTR               = 0;
    EPWM_setTimeBaseCounter(epwm_base, 0); // ����ʱ�������Ĵ���

    // CC
    // epwm->CMPCTL.bit.SHDWAMODE = 0;
    // epwm->CMPCTL.bit.SHDWBMODE = 0;
    // epwm->CMPCTL.bit.LOADAMODE = 0;
    // epwm->CMPCTL.bit.LOADBMODE = 0;
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_C, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_D, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    // epwm->CMPA.bit.CMPA        = cmp;
    // epwm->CMPB.bit.CMPB        = cmp / 2;
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_A, cmp);
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_B, cmp / 2);
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_C, 1);
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_D, 2);

    // AQ
    // ��Ӧ��ֵ1�򴥷����0����Ӧ��ֵ1�򴥷����1
    // epwm->AQCTLA.bit.CAU = 2; // ��CTR=CMPA��Up������ʱ��EPWM1A����ߵ�ƽ
    // epwm->AQCTLA.bit.CAD = 1; // ��CTR=CMPA��Down������ʱ��EPWM1A����͵�ƽ
    // epwm->AQCTLB.bit.CAU = 2; // ��CTR=CMPA��Up������ʱ��EPWM1B����ߵ�ƽ
    // epwm->AQCTLB.bit.CAD = 1; // ��CTR=CMPA��Down������ʱ��EPWM1B����͵�ƽ
    EPWM_setActionQualifierAction(epwm_base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(epwm_base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    // DB
    // epwm->DBCTL.bit.OUT_MODE = 0; // ������ȫ��·
    // ����û��enable������ֻҪ�����þ�û��

    // PC
    // EPWM_enableChopper(epwm_base); // ն������ȫ��·

    // �Ƿ���жϴ���
    if (int_type)
        Interrupt_enable(INT_EPWM1_TZ + ch);
    else
        Interrupt_disable(INT_EPWM1_TZ + ch);

    if (p_flag)
    {
        printf("epwm test -> ch:%d, count_mode:%d, tbprd:%d, cmp:%d, tbphs:%d, int_type:%d\n", ch, count_mode, tbprd,
            cmp, tbphs, int_type);
    }
}

void pwm_denormal_gen(u8 ch, u8 count_mode, u16 tbprd, u16 cmp, u16 tbphs, u8 int_type, u32 p_flag)
{
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);
    // TB
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    EPWM_setTimeBaseCounterMode(epwm_base, count_mode); // ����ģʽ
    // EPWM_enablePhaseShiftLoad(epwm_base);   // ����TBPHS����TBCTR
    // EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_SHADOW_LOAD);  // ����Ӱ��ģʽ��дTBPRD
    EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_DIRECT_LOAD); // ����ֱ��ģʽ��дTBPRD
    // EPWM_setSyncOutPulseMode(epwm_base, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);//cnt eq zero ���ͬ��
    EPWM_setClockPrescaler(epwm_base, 2, 1);
    // PHSDIR����λ����λ�����ڵ�������ʱʹ��
    // FREE_SOFT������ģʽ��������

    EPWM_setPhaseShift(epwm_base, tbphs);     // ��λƫ��
    EPWM_setTimeBasePeriod(epwm_base, tbprd); // ʱ����������
    EPWM_setTimeBaseCounter(epwm_base, 0);    // ����ʱ�������Ĵ���

    // CC
    // epwm->CMPCTL.bit.SHDWAMODE = 0;
    // epwm->CMPCTL.bit.SHDWBMODE = 0;
    epwm->CMPCTL.bit.SHDWAMODE = 1; // ������Ӱ��ģʽ
    epwm->CMPCTL.bit.SHDWBMODE = 1; // ������Ӱ��ģʽ
    epwm->CMPCTL.bit.LOADAMODE = 0;
    epwm->CMPCTL.bit.LOADBMODE = 0;
    epwm->CMPA.bit.CMPA        = cmp;
    epwm->CMPB.bit.CMPB        = cmp / 2;

    // AQ
    // ��Ӧ��ֵ1�򴥷����0����Ӧ��ֵ1�򴥷����1
    epwm->AQCTLA.bit.CAU = 2; // ��CTR=CMPA��Up������ʱ��EPWM1A����ߵ�ƽ
    epwm->AQCTLA.bit.CAD = 1; // ��CTR=CMPA��Down������ʱ��EPWM1A����͵�ƽ
    epwm->AQCTLB.bit.CBU = 2; // ��CTR=CMPA��Up������ʱ��EPWM1B����ߵ�ƽ
    epwm->AQCTLB.bit.CBD = 1; // ��CTR=CMPA��Down������ʱ��EPWM1B����͵�ƽ

    // DB
    epwm->DBCTL.bit.OUT_MODE = 0; // ������ȫ��·

    // PC
    // EPWM_enableChopper(epwm_base); // ն������ȫ��·

    // �Ƿ���жϴ���
    if (int_type)
        Interrupt_enable(INT_EPWM1 + ch);
    else
        Interrupt_disable(INT_EPWM1 + ch);

    if (p_flag)
        printf("epwm test -> ch:%d, count_mode:%d, tbprd:%d, cmp:%d, tbphs:%d, int_type:%d\n", ch, count_mode, tbprd,
            cmp, tbphs, int_type);
}

void pwm_aq(u8 ch)
{
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    EPWM_setActionQualifierSWAction(epwm_base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW); // ����SW�¼�ʱ����Ӧ
    EPWM_setActionQualifierSWAction(epwm_base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_TOGGLE);
    // AQCSFRC��Ӱ��ģʽ����eqprdʱд��
    EPWM_setActionQualifierContSWForceShadowMode(epwm_base, EPWM_AQ_SW_SH_LOAD_ON_CNTR_PERIOD);
}

void pwm_dead_band_gen(u8 ch, u16 dead_time)
{
    uint32_t epwm_base              = EPWM1_BASE + ch * 0x200;
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);
    // DB
    // epwm->DBCTL.bit.OUT_MODE = 0b11;         // ʹ�������غ��½����ź�
    EPWM_setDeadBandDelayMode(epwm_base, EPWM_DB_RED, 1);
    EPWM_setDeadBandDelayMode(epwm_base, EPWM_DB_FED, 1);
    // epwm->DBCTL.bit.IN_MODE  = 0b10; // �����غ��½�����������һ·��Ϊ�ο���10-��EPWM1A�����أ�EPWM1B�½�����Ϊ�ο�
    EPWM_setRisingEdgeDeadBandDelayInput(epwm_base, EPWM_DB_INPUT_EPWMA);
    EPWM_setFallingEdgeDeadBandDelayInput(epwm_base, EPWM_DB_INPUT_EPWMB);
    // epwm->DBCTL.bit.POLSEL   = 0b10;         // EPWM1B���Է�ת
    EPWM_setDeadBandDelayPolarity(epwm_base, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW); // ��̫���߼��������û����
    // epwm->DBRED.all          = dead_time; // ������ʱ����
    // epwm->DBFED.all          = dead_time; // ������ʱ����
    EPWM_setFallingEdgeDelayCountShadowLoadMode(epwm_base, EPWM_FED_LOAD_ON_CNTR_PERIOD); // ����Ӱ��ģʽ��eq_prdװ��
    EPWM_setRisingEdgeDelayCountShadowLoadMode(epwm_base, EPWM_RED_LOAD_ON_CNTR_PERIOD);
    EPWM_setRisingEdgeDelayCount(epwm_base, dead_time);
    EPWM_setFallingEdgeDelayCount(epwm_base, dead_time);
    EPWM_setDeadBandControlShadowLoadMode(epwm_base, EPWM_DB_LOAD_ON_CNTR_PERIOD);
    printf("epwm test -> ch:%d, dead_time:%d\n", ch, dead_time);
}

void pwm_chopper_gen(u8 ch, u16 oshtw, u16 pcfreq, u16 pcduty)
{
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    // volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch *0x200);
    // PC
    // epwm->PCCTL.bit.CHPEN = 1;        // ����ն������
    // epwm->PCCTL.bit.OSHTWTH = oshtw;  // ���õ�һ�����Ŀ�ȣ�8/oshtw��epwm����
    // epwm->PCCTL.bit.CHPFREQ = pcfreq; // ����Ƶ�ʣ�ÿ��tbclk���ڱ���Ϊfreq*8������
    // epwm->PCCTL.bit.CHPDUTY = pcduty; // ����psclk��ռ�ձ�

    EPWM_enableChopper(epwm_base);
    EPWM_setChopperFirstPulseWidth(epwm_base, oshtw);
    EPWM_setChopperFreq(epwm_base, pcfreq);
    EPWM_setChopperDutyCycle(epwm_base, pcduty);

    printf("epwm test -> ch:%d, oshtw:%d, pcfreq:%d, pcduty:%d\n", ch, oshtw, pcfreq, pcduty);
}

void pwm_trip_osht(u8 ch, u8 int_type)
{
    uint32_t epwm_base              = EPWM1_BASE + ch * 0x200;
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);
    // epwm->TZCTL.bit.TZA = 0;  //���������¼�ʱǿ��EPWMA����
    // epwm->TZCTL.bit.TZB = 1;  //���������¼�ʱǿ��EPWMB����
    EPWM_setTripZoneAction(epwm_base, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_HIGH_Z);
    EPWM_setTripZoneAction(epwm_base, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_HIGH);
    // epwm->TZSEL.bit.OSHT1 = 1;  //ʹ��TZ1 OSHT����������frc�����Ƿ�ʹ�ܣ����ᴥ��
    EPWM_enableTripZoneSignals(epwm_base, EPWM_TZSEL_OSHT1);
    if (int_type)
        // epwm->TZEINT.bit.OST = int_type;//ʹ��or��ֹOSHT�ж�
        EPWM_enableTripZoneInterrupt(epwm_base, EPWM_TZEINT_OST);
}

void pwm_trip_cbc(u8 ch, u8 int_type)
{
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    // volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch *0x200);

    // epwm->TZCTL.bit.TZA = 0; // ���������¼�ʱǿ��EPWMA����
    // epwm->TZCTL.bit.TZB = 1; // ���������¼�ʱǿ��EPWMB����
    EPWM_setTripZoneAction(epwm_base, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_HIGH_Z);
    EPWM_setTripZoneAction(epwm_base, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_HIGH);
    // epwm->TZSEL.bit.CBC1 = 1; // ʹ��TZ1 CBC����������frc�����Ƿ�ʹ�ܣ����ᴥ��
    EPWM_enableTripZoneSignals(epwm_base, EPWM_TZSEL_CBC1);
    if (int_type)
        // epwm->TZEINT.bit.OST = int_type; // ʹ��or��ֹOSHT�ж�
        EPWM_enableTripZoneInterrupt(epwm_base, EPWM_TZEINT_CBC);
}

void pwm_trip_in(u8 ch)
{
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    XBAR_setInputPin(XBAR_INPUT2, XBAR_INPUT_GPIO2); // �����Ӳ������
    EPWM_setTripZoneAction(epwm_base, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_HIGH_Z);
    EPWM_setTripZoneAction(epwm_base, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_HIGH);
    EPWM_enableTripZoneSignals(epwm_base, EPWM_TZSEL_OSHT2); // ʹ��OST2��������
    // EPWM_enableTripZoneSignals(epwm_base, EPWM_TZSEL_CBC2);//ʹ��CBC2��������

    EPWM_enableTripZoneAdvAction(epwm_base);                                                       // ʹ����չTZCTL2
    EPWM_setTripZoneAdvAction(epwm_base, EPWM_TZ_ADV_ACTION_EVENT_TZA_D, EPWM_TZ_ADV_ACTION_HIGH); // ��������ֱ������
}

void pwm_et(u8 ch)
{
    uint32_t epwm_base              = EPWM1_BASE + ch * 0x200;
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);

    // epwm->ETSEL.bit.INTSEL = 1;  // ʹ��eq_zero�¼�
    // epwm->ETSEL.bit.SOCASEL = 2; // ʹ��eq_zero�¼�
    // epwm->ETSEL.bit.SOCBSEL = 1; // ʹ��eq_zero�¼�
    EPWM_setInterruptSource(epwm_base, EPWM_INT_TBCTR_ZERO);
    EPWM_setADCTriggerSource(epwm_base, EPWM_SOC_A, EPWM_SOC_TBCTR_PERIOD);
    EPWM_setADCTriggerSource(epwm_base, EPWM_SOC_B, EPWM_SOC_TBCTR_D_CMPD);

    // epwm->ETSEL.bit.SOCAEN = 1; // ʹ��SOCA���
    // epwm->ETSEL.bit.SOCBEN = 1; // ʹ��SOCA���
    // epwm->ETSEL.bit.INTEN = 1;  // ʹ���ж�
    EPWM_enableInterrupt(epwm_base);
    EPWM_enableADCTrigger(epwm_base, EPWM_SOC_A);
    EPWM_enableADCTrigger(epwm_base, EPWM_SOC_B);

    // epwm->ETPS.bit.INTPRD = 3;  //ÿ����3���¼�����������һ���ж�
    // epwm->ETPS.bit.SOCAPRD = 3; //û����3���¼�����һ��SOCA����
    // epwm->ETPS.bit.SOCBPRD = 3;
    EPWM_setInterruptEventCount(epwm_base, 3); // �����������ֻ������intprd2��������Ӱ��
    EPWM_setADCTriggerEventPrescale(epwm_base, EPWM_SOC_A, 15); // ͬ��
    EPWM_setADCTriggerEventPrescale(epwm_base, EPWM_SOC_B, 15); // ͬ��

    EPWM_enableADCTriggerEventCountInit(epwm_base, EPWM_SOC_A);
    epwm->ETCNTINIT.bit.SOCAINIT = 8; // ͬ���źŴ���ʱ��soca�ļ�����ʼ��Ϊ8
}

void pwm_dc(u8 ch, u16 offset, u16 window, EPWM_DigitalCompareEdgeFilterMode edgemode, u16 count)
{
    // �����Ӳ������
    XBAR_setInputPin(XBAR_INPUT6, XBAR_INPUT_GPIO6);
    uint32_t epwm_base              = EPWM1_BASE + ch * 0x200;
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);

    // epwm->DCTRIPSEL.bit.DCALCOMPSEL = 0; // TRIPIN0
    // epwm->DCTRIPSEL.bit.DCAHCOMPSEL = 1; // TRIPIN1
    // epwm->DCTRIPSEL.bit.DCBLCOMPSEL = 4; // TRIPIN5
    // epwm->DCTRIPSEL.bit.DCBHCOMPSEL = 5; // TRIPIN6
    EPWM_selectDigitalCompareTripInput(epwm_base, EPWM_DC_TRIP_TRIPIN1, EPWM_DC_TYPE_DCAL);
    EPWM_selectDigitalCompareTripInput(epwm_base, EPWM_DC_TRIP_TRIPIN2, EPWM_DC_TYPE_DCAH);
    EPWM_selectDigitalCompareTripInput(epwm_base, EPWM_DC_TRIP_TRIPIN5, EPWM_DC_TYPE_DCBL);
    EPWM_selectDigitalCompareTripInput(epwm_base, EPWM_DC_TRIP_TRIPIN6, EPWM_DC_TYPE_DCBH);

    // epwm->TZDCSEL.bit.DCAEVT1 = 2;  //DCAH = highʱ����DCAEVT1
    // epwm->TZDCSEL.bit.DCBEVT1 = 2; //DCBH = highʱ����DCBEVT1
    EPWM_setTripZoneDigitalCompareEventCondition(epwm_base, EPWM_TZ_DC_OUTPUT_B1, EPWM_TZ_EVENT_DCXH_HIGH);
    EPWM_setTripZoneDigitalCompareEventCondition(epwm_base, EPWM_TZ_DC_OUTPUT_A1, EPWM_TZ_EVENT_DCXH_HIGH);

    // ���ÿմ�
    // epwm->DCFCTL.bit.PULSESEL = 0; //offset���뵽ctr_eq_zero��ctr_eq_prd���ctr
    EPWM_setDigitalCompareBlankingEvent(epwm_base, EPWM_DC_WINDOW_START_TBCTR_ZERO);

    // epwm->DCFCTL.bit.BLANKE = 1; //ʹ��blank
    EPWM_enableDigitalCompareBlankingWindow(epwm_base);

    // epwm->DCFOFFSET = offset;  //�մ�ƫ��
    // epwm->DCFWINDOW = window;  //�մ��ڳ���
    EPWM_setDigitalCompareWindowOffset(epwm_base, offset);
    EPWM_setDigitalCompareWindowLength(epwm_base, window);

    // ���ñ��ع�����
    // epwm->DCFCTL.bit.EDGEMODE = edgemode;
    // epwm->DCFCTL.bit.EDGECOUNT = count;  //ÿ�����½���dcf blank sel out�źŲ���һ������
    // epwm->DCFCTL.bit.EDGEFILTSEL = 1; //���ñ��ع�������
    EPWM_setDigitalCompareEdgeFilterMode(epwm_base, edgemode);
    EPWM_setDigitalCompareEdgeFilterEdgeCount(epwm_base, count);
    EPWM_enableDigitalCompareEdgeFilter(epwm_base);

    // epwm->DCFCTL.bit.SRCSEL = 0b10; //���������dcbevt1
    EPWM_setDigitalCompareFilterInput(epwm_base, EPWM_DC_WINDOW_SOURCE_DCBEVT1);

    // epwm->VCAPCTL.bit.TRIGSEL = 1;
    // epwm->VCAPCTL.bit.VCAPE = 1; //ÿ��prd���Ḵλ���ع��ˣ���ͼ
    EPWM_setValleyTriggerSource(epwm_base, EPWM_VALLEY_TRIGGER_EVENT_CNTR_ZERO);
    EPWM_enableValleyCapture(epwm_base);

    EPWM_setValleyTriggerEdgeCounts(epwm_base, 2, 5); // ���ñ��ع��˵��ӳ�
    EPWM_setValleySWDelayValue(epwm_base, 32);        // ��������ӳ�
    EPWM_setValleyDelayDivider(
        epwm_base, EPWM_VALLEY_DELAY_MODE_VCNT_DELAY_SHIFT_2_SW_DELAY); // HWVDELVAL = VCNTVAL>>2+SWVDELVAL
    EPWM_enableValleyHWDelay(epwm_base);                                // ʹ���ӳ�

    // ���ò�����
    epwm->DCCAPCTL.bit.CAPMODE = 1; // �ֶ������û�ж�Ӧ����
    // epwm->DCCAPCTL.bit.SHDWMODE = 0; //����Ӱ��ģʽ
    // epwm->DCCAPCTL.bit.CAPE = 1;  //ʹ�ܲ�����

    EPWM_setDigitalCompareCounterShadowMode(epwm_base, 1);
    EPWM_enableDigitalCompareCounterCapture(epwm_base);

    // epwm->DCACTL.bit.EVT1SRCSEL = 0;//DEAVET1�ź�ԴΪDCAEVT1����·filter
    // epwm->DCBCTL.bit.EVT1SRCSEL = 1;//DCBEVT1�ź�ԴΪDCEVTFTLT
    EPWM_setDigitalCompareEventSource(epwm_base, EPWM_DC_MODULE_A, EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);
    EPWM_setDigitalCompareEventSource(epwm_base, EPWM_DC_MODULE_B, EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_FILT_SIGNAL);

    // epwm->DCBCTL.bit.EVT1SOCE = 1; //ͬʱ����DCBEVT1.soc�ź�
    EPWM_enableDigitalCompareADCTrigger(epwm_base, EPWM_DC_MODULE_B);

    EPWM_enableDigitalCompareSyncEvent(epwm_base, EPWM_DC_MODULE_B); // ʹ��sync���
}

void pwm_sync(u8 ch)
{
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    EPWM_enablePhaseShiftLoad(epwm_base); // ʹ��ͬ���źŵ�����λ

    // EPWM_enableOneShotSync(epwm_base);  //ʹ��oshtͬ���ź�
    // EPWM_startOneShotSync(epwm_base);  //�������������׾��幦�ܣ�Ч����˵��������Ϊ��oshtsyncout�����swfsync

    EPWM_setSyncOutPulseMode(epwm_base, EPWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_C); // ����ͬ���ź����ģʽ

    EPWM_selectPeriodLoadEvent(epwm_base, EPWM_SHADOW_LOAD_MODE_SYNC); // ����ͬ���ź�ʱ��Ӱ�Ӽ���PRD
    EPWM_setCounterCompareShadowLoadMode(
        epwm_base, EPWM_COUNTER_COMPARE_C, EPWM_COMP_LOAD_ON_SYNC_ONLY); // ����ͬ���ź�ʱ��Ӱ�Ӽ���CMPC

    SysCtl_enableExtADCSOCSource(SYSCTL_ADCSOCOUTSELECT_PWM2SOCAEN); // ʹ������ADC srcΪ epwm_ch1
    SysCtl_enableExtADCSOCSource(SYSCTL_ADCSOCOUTSELECT_PWM3SOCBEN); // ʹ������ADC srcΪ epwm_ch1
}

void pwm_lock(u8 ch)
{
    // //epwmlock�Ĵ���ȡ��
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + 0 * 0x200);
    uint32_t epwm_base              = EPWM1_BASE + ch * 0x200;
    SysCtl_enableExtADCSOCSource(SYSCTL_ADCSOCOUTSELECT_PWM1SOCAEN);
    int delay = 1000;
    while (delay--)
        ;
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_EPWM7, SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT);
    delay = 1000;
    while (delay--)
        ;
    SysCtl_lockSyncSelect(); // �������赲һ��д����
    delay = 1000;
    while (delay--)
        ;
    SysCtl_lockExtADCSOCSelect(); // �������赲һ��д����
    delay = 1000;
    while (delay--)
        ;
    SysCtl_enableExtADCSOCSource(SYSCTL_ADCSOCOUTSELECT_PWM2SOCAEN);
    delay = 1000;
    while (delay--)
        ;
    SysCtl_enableExtADCSOCSource(SYSCTL_ADCSOCOUTSELECT_PWM2SOCAEN);
    delay = 1000;
    while (delay--)
        ;
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP1, SYSCTL_SYNC_IN_SRC_EPWM7SYNCOUT); // Ԥ�ڱ���ֹ
    delay = 1000;
    while (delay--)
        ;
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP1, SYSCTL_SYNC_IN_SRC_EPWM7SYNCOUT); // Ԥ�ڳɹ�д��
}

void pwm_tz_aq(u8 ch)
{
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    EPWM_setTimeBaseCounterMode(epwm_base, 2);                  // ����ģʽ
    EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_SHADOW_LOAD); // ����Ӱ��ģʽ��дTBPRD
    EPWM_setSyncOutPulseMode(epwm_base, EPWM_SYNC_OUT_PULSE_ON_EPWMxSYNCIN);
    EPWM_setClockPrescaler(epwm_base, 2, 1);
    EPWM_setTimeBasePeriod(epwm_base, SYS_CLK / 100000 / 2);                            // ʱ����������
    EPWM_setTimeBaseCounter(epwm_base, 0);                                              // ����ʱ�������Ĵ���
    EPWM_setActionQualifierT1TriggerSource(epwm_base, EPWM_AQ_TRIGGER_EVENT_TRIG_TZ_2); // ����Դѡ��tz2
    EPWM_setActionQualifierAction(epwm_base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_T1_COUNT_UP);
    EPWM_setActionQualifierAction(epwm_base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_T1_COUNT_DOWN);
    EPWM_setActionQualifierAction(epwm_base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_T1_COUNT_UP);
    EPWM_setActionQualifierAction(epwm_base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_T1_COUNT_DOWN);
    XBAR_setInputPin(XBAR_INPUT2, XBAR_INPUT_GPIO2); // ����GPIO2���룬������Ӳ������ʹ��
}

void pwm_gld(u8 ch)
{
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;

    EPWM_enableGlobalLoad(epwm_base); // ʹ��ȫ��װ��

    EPWM_setGlobalLoadTrigger(epwm_base, EPWM_GL_LOAD_PULSE_CNTR_PERIOD); // �����¼�λeq_prd
    // EPWM_setGlobalLoadTrigger(epwm_base, EPWM_GL_LOAD_PULSE_GLOBAL_FORCE);//�����¼�Ϊ��gldctl2��CFRCLDλ��1
    EPWM_setGlobalLoadEventPrescale(epwm_base, 6); // 6���¼�����һ��ȫ��װ��

    EPWM_enableGlobalLoadOneShotMode(epwm_base); // ����oshtģʽ��ֻ����gldctl2��oshtldλ��д��1����װ��

    EPWM_enableGlobalLoadRegisters(epwm_base, EPWM_GLDCFG_CMPA_CMPAHR); // ʹ��cmpaȫ��װ��
}

void test_normal()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // ��������, 10KHz, ռ�ձ�50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        SysCtl_TbClkSyncToggle(1);
        while (1)
            ;
    }
}

void test_denormal()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // ��������, 10KHz, ռ�ձ�50%
        pwm_denormal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        SysCtl_TbClkSyncToggle(1);
        // Ӱ�ӼĴ���
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;
        int delay          = 100;
        while (delay--)
            ;
        volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i * 0x200);
        epwm->CMPA.bit.CMPA             = SYS_CLK / 100000 / 8;
        epwm->CMPB.bit.CMPB             = SYS_CLK / 100000 / 16;
        delay                           = 100;
        while (delay--)
            ;
        epwm->TBPRD = SYS_CLK / 100000 / 4;
        while (1)
            ;
    }
}

void test_aq()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // ��������, 10KHz, ռ�ձ�50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        pwm_aq(i);
        SysCtl_TbClkSyncToggle(1);
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;
        int delay          = 100;
        while (delay--)
            ;
        EPWM_forceActionQualifierSWAction(epwm_base, EPWM_AQ_OUTPUT_A); // ����SW�¼�ʱ����Ӧ(����)
        //  EPWM_setActionQualifierContSWForceAction(epwm_base, EPWM_AQ_OUTPUT_A, EPWM_AQ_SW_OUTPUT_LOW);
        ////����SW�¼�ʱ����Ӧ(����)
        delay = 100;
        while (delay--)
            ;
        EPWM_forceActionQualifierSWAction(epwm_base, EPWM_AQ_OUTPUT_B);
        //  EPWM_setActionQualifierContSWForceAction(epwm_base, EPWM_AQ_OUTPUT_B, EPWM_AQ_SW_OUTPUT_HIGH);
        while (1)
            ;
    }
}

void test_db()
{
    SysCtl_TbClkSyncToggle(0);
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // ��������, 10KHz, ռ�ձ�50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        pwm_dead_band_gen(i, 16);
        SysCtl_TbClkSyncToggle(1);
        volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i * 0x200);
        uint32_t epwm_base              = EPWM1_BASE + i * 0x200;
        int delay                       = 1000;
        while (delay--)
            ;
        EPWM_setRisingEdgeDelayCount(epwm_base, 20);
        EPWM_setFallingEdgeDelayCount(epwm_base, 20);
        delay = 1000;
        while (delay--)
            ;
        EPWM_setDeadBandOutputSwapMode(epwm_base, EPWM_DB_OUTPUT_A, 1); // ��֤�������
        delay = 1000;
        while (delay--)
            ;
        EPWM_setDeadBandOutputSwapMode(epwm_base, EPWM_DB_OUTPUT_B, 1);
        delay = 1000;
        while (delay--)
            ;
        epwm->DBCTL.bit.HALFCYCLE = 1; // ��֤������
        delay                     = 1000;
        while (delay--)
            ;
        epwm->DBCTL.bit.POLSEL = 0b11; // ��֤Ӱ��ģʽ
        while (1)
            ;
    }
}

void test_pc()
{
    SysCtl_TbClkSyncToggle(0);
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // ��������, 10KHz, ռ�ձ�50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        pwm_chopper_gen(i, 3, 1, 3);
        SysCtl_TbClkSyncToggle(1);
    }
}

void test_db_pc()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // ��������, 10KHz, ռ�ձ�50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        pwm_dead_band_gen(i, 24);
        pwm_chopper_gen(i, 3, 1, 3);
        SysCtl_TbClkSyncToggle(1);
    }
}

void test_tz_osht()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // ��������, 10KHz, ռ�ձ�50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        pwm_trip_osht(i, 0);
        SysCtl_TbClkSyncToggle(1);
        int delay = 1000;
        while (delay--)
            ;
        //  volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i *0x200);
        //  epwm->TZFRC.bit.OST = 1;//ǿ�ƴ���OST�¼�
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;
        //  EPWM_forceTripZoneEvent(epwm_base, EPWM_TZFRC_OST);
        while (1)
            ;
    }
}

void test_tz_cbc()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // ��������, 10KHz, ռ�ձ�50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        pwm_trip_cbc(i, 0);
        SysCtl_TbClkSyncToggle(1);
        int delay = 100;
        while (delay--)
            ;
        volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i * 0x200);
        //  epwm->TZFRC.bit.CBC = 1;//ǿ�ƴ���CBC�¼�
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;
        EPWM_forceTripZoneEvent(epwm_base, EPWM_TZFRC_CBC);
        while (1)
            ;
    }
}

void test_tz_osht_int()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // ��������, 10KHz, ռ�ձ�50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 1, 1);
        pwm_trip_osht(i, 1);
        SysCtl_TbClkSyncToggle(1);
        int delay = 100;
        while (delay--)
            ;
        // volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i *0x200);
        // epwm->TZFRC.bit.OST = 1;//ǿ�ƴ���OST�¼�
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;
        EPWM_forceTripZoneEvent(epwm_base, EPWM_TZFRC_OST);
        while (int_flag[i] == 0)
            ;
    }
}

void test_tz_cbc_int()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // ��������, 10KHz, ռ�ձ�50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 1, 1);
        pwm_trip_cbc(i, 1);
        SysCtl_TbClkSyncToggle(1);
        int delay = 100;
        while (delay--)
            ;
        volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i * 0x200);
        //  epwm->TZFRC.bit.CBC = 1;//ǿ�ƴ���OST�¼�
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;
        EPWM_forceTripZoneEvent(epwm_base, EPWM_TZFRC_CBC);
        while (1)
            ;
    }
}

void test_et_int()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        Interrupt_enable(INT_EPWM1 + i);
        // ��������, 10KHz, ռ�ձ�50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 0);
        pwm_et(i);
        SysCtl_TbClkSyncToggle(1);
        int delay = 100;
        while (delay--)
            ;
        // volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i *0x200);
        // epwm->TZFRC.bit.OST = 1;//ǿ�ƴ���OST�¼�
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;
        EPWM_forceEventTriggerInterrupt(epwm_base);
        while (int_flag[i] == 0)
            ;
    }
}

void test_tz_in()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // ��������, 10KHz, ռ�ձ�50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 1, 1);
        pwm_trip_in(i);
        SysCtl_TbClkSyncToggle(1);

        uint32_t epwm_base              = EPWM1_BASE + i * 0x200;
        volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i * 0x200);
        int delay                       = 1000;
        while (delay--)
            ;
        u16 flg = EPWM_getOneShotTripZoneFlagStatus(epwm_base);
        //  u16 flg = EPWM_getCycleByCycleTripZoneFlagStatus(epwm_base);
        printf("flg = %d\n", flg);
        EPWM_clearOneShotTripZoneFlag(epwm_base, flg);
        //  EPWM_clearCycleByCycleTripZoneFlag(epwm_base, flg);
        epwm->TZCLR.bit.OST = 1; // ���OST�ź�
        while (1)
            ;
    }
}

void test_et()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // ��������, 10KHz, ռ�ձ�50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        //      pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 1, 1);
        pwm_et(i);
        SysCtl_TbClkSyncToggle(1);
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;
        //      volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i *0x200);
        int delay = 100;
        while (delay--)
            ;
        EPWM_forceADCTrigger(epwm_base, EPWM_SOC_A); // ǿ�ƴ���SOCA����
        delay = 100;
        while (delay--)
            ;
        EPWM_clearADCTriggerFlag(epwm_base, EPWM_SOC_A);
        EPWM_forceADCTrigger(epwm_base, EPWM_SOC_B); // ǿ�ƴ���SOCB����
        delay = 100;
        while (delay--)
            ;
        EPWM_clearADCTriggerFlag(epwm_base, EPWM_SOC_B);
        delay = 100;
        while (delay--)
            ;
        EPWM_forceADCTriggerEventCountInit(epwm_base, EPWM_SOC_A); // ǿ��soca��ʼ��counter
        while (1)
            ;
    }
}

void test_dc()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // ��������, 10KHz, ռ�ձ�50%
        //  pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 10000 / 2, SYS_CLK / 10000 / 4, 0, 1, 1);
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 10000 / 2, SYS_CLK / 10000 / 4, 0, 0, 1);
        // Ƶ�ʵõ�һ�㣬��Ȼ��λ�ź�̫Ƶ��

        uint32_t epwm_base = EPWM1_BASE + i * 0x200;

        EPWM_setTripZoneAction(epwm_base, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_HIGH_Z);
        EPWM_setTripZoneAction(epwm_base, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_HIGH_Z);
        EPWM_enableTripZoneSignals(epwm_base, EPWM_TZSEL_DCBEVT1);
        //  EPWM_enableTripZoneInterrupt(epwm_base, EPWM_TZEINT_DCBEVT1);

        pwm_dc(i, 80, 640, EPWM_DC_EDGEFILT_MODE_FALLING, 4);
        SysCtl_TbClkSyncToggle(1);
        int delay = 1000;
        while (delay--)
            ;
        volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i * 0x200);
        epwm->DCCAPCTL.bit.CAPCLR       = 1;
        delay                           = 1000;
        while (delay--)
            ;
        //  EPWM_enableDigitalCompareWindowInverseMode(epwm_base); //�մ���ת
        while (1)
            ;
    }
}

void test_sync()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // ��������, 10KHz, ռ�ձ�50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 8, 0, 1);
        pwm_sync(i);
        SysCtl_TbClkSyncToggle(1);
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;

        int delay = 100;
        while (delay--)
            ;
        EPWM_setTimeBasePeriod(epwm_base, SYS_CLK / 100000 / 2 - 1); // ��֤ͬ������ģʽ
        EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_C, 3);
        EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_A, SYS_CLK / 100000 / 4 - 1); // ��֤shdwafull
        delay = 100;
        while (delay--)
            ;
        EPWM_forceSyncPulse(epwm_base);
        while (1)
            ;
    }
}

void test_lock()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        pwm_lock(i);
    }
}

void test_tz_aq()
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (0 << 8));
    SysCtl_TbClkSyncToggle(0);
    pwm_tz_aq(0);
    SysCtl_TbClkSyncToggle(1);
    while (1)
        ;
}

void test_to_ecap()
{
    int i = 3;
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
    SysCtl_TbClkSyncToggle(0);
    uint32_t epwm_base = EPWM1_BASE + i * 0x200;
    // ��������, 10KHz, ռ�ձ�50%
    pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 8, 0, 1);
    EPWM_setSyncOutPulseMode(epwm_base, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP1, SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT); // ����ECAP1������ΪEPWM4SYNCOUT
    SysCtl_TbClkSyncToggle(1);
    int delay = 10000;
    while (delay--)
        ;
}

void test_dc_tz()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // ��������, 10KHz, ռ�ձ�50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);

        // ����dc
        XBAR_setInputPin(XBAR_INPUT6, XBAR_INPUT_GPIO6);
        uint32_t epwm_base = EPWM1_BASE + i * 0x200;

        EPWM_selectDigitalCompareTripInput(epwm_base, EPWM_DC_TRIP_TRIPIN6, EPWM_DC_TYPE_DCBH);

        EPWM_setTripZoneDigitalCompareEventCondition(epwm_base, EPWM_TZ_DC_OUTPUT_B1, EPWM_TZ_EVENT_DCXH_HIGH);
        EPWM_setDigitalCompareEventSource(
            epwm_base, EPWM_DC_MODULE_B, EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);

        // ����TZ����DC�¼�����Ӧ
        EPWM_enableTripZoneAdvAction(epwm_base);
        // EPWM_enableTripZoneSignals(epwm_base, EPWM_TZSEL_DCBEVT1);
        EPWM_setTripZoneAdvDigitalCompareActionB(
            epwm_base, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_U, EPWM_TZ_ADV_ACTION_HIGH);

        SysCtl_TbClkSyncToggle(1);
        int delay = 5000;
        while (delay--)
            ;
    }
}

void test_gld()
{
    for (int i = 0; i < EPWM_NUM; i++)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        SysCtl_TbClkSyncToggle(0);
        // ��������, 10KHz, ռ�ձ�50%
        pwm_normal_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        // ����GLD
        pwm_gld(i);
        SysCtl_TbClkSyncToggle(1);

        int delay = 1000;
        while (delay--)
            ;

        // �޸�cmpa����
        volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + i * 0x200);
        uint32_t epwm_base              = EPWM1_BASE + i * 0x200;
        epwm->CMPA.bit.CMPA             = SYS_CLK / 100000 / 8 - 1;

        delay = 100;
        while (delay--)
            ;
        for (int j = 0; j < 6; j++)
        {
            EPWM_forceGlobalLoadOneShotEvent(epwm_base); // ǿ�Ʋ���һ���¼�
        }
        delay = 1000;
        while (delay--)
            ;

        EPWM_setGlobalLoadOneShotLatch(epwm_base);

        delay = 5000;
        while (delay--)
            ;
    }
}

void test_link()
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (0 << 8));
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (1 << 8));
    volatile struct EPWM_REGS *epwm1 = (volatile struct EPWM_REGS *)(EPWM1_BASE + 0 * 0x200);
    volatile struct EPWM_REGS *epwm2 = (volatile struct EPWM_REGS *)(EPWM1_BASE + 1 * 0x200);

    SysCtl_TbClkSyncToggle(0);
    // ��������, 10KHz, ռ�ձ�50%
    pwm_normal_gen(0, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
    pwm_normal_gen(1, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);

    // ��������
    epwm1->EPWMXLINK.bit.CMPALINK = 1; // ��epwm1��cmpa��epwm2��cmpa����

    SysCtl_TbClkSyncToggle(1);

    int delay = 1000;
    while (delay--)
        ;
    // �޸�cmpa����
    epwm2->CMPA.bit.CMPA = SYS_CLK / 100000 / 8 - 1;

    delay = 5000;
    while (delay--)
        ;
}

void test_epwm(void)
{
    // test_normal();
    // test_denormal();
    // test_aq();
    // test_db();
    // test_pc();
    // test_db_pc();
    // test_tz_osht();
    // test_tz_cbc();
   // test_tz_osht_int();
    // test_tz_cbc_int();
	test_et_int();
    // test_tz_in();
    // test_et();
    // test_dc();
    // test_sync();
    // test_lock();
    // test_tz_aq();
    // test_to_ecap();
    // test_dc_tz();
    // test_gld();
    // test_link();
}
