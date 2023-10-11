#include "common.h"
uint32_t result = FAIL, pass_base = 0, isr_enter = 0;
uint32_t cnt0 = 0, cnt1 = 0, valid = 0;
bool status = 0;

__interrupt void dcc_isr(void)
{
    puts("dcc_int1");
    Dcc0Regs->DCCSTATUS.bit.DONE = 1;
    Dcc0Regs->DCCSTATUS.bit.ERR  = 1;
}

void test_SingleShotMode()
{ // ����SingleShotMode ģʽ

    float32_t total_error;
    float32_t window;
    uint32_t count0;
    uint32_t valid;
    uint32_t count1;
    float32_t freq0     = 10.0F;    // PLL_clk  Ƶ��  40M-400M
    float32_t freq1     = 50.0F;     // sel_clk  ���ֿ���ѡ�� Xtal��clk1��clk2
    float32_t tolerance = 0.1F;
    float32_t freqerr   = 0.0F;

    if (freq1 > freq0)
    {
        total_error = 2.0F;
    }
    else
    {
        total_error = 2.0F * (freq0 / freq1);
    }

    total_error += 3.0F;

    window = total_error / (0.01F * tolerance);

    total_error += window * (freqerr / 100.0F);

    count0 = window - total_error;
    valid  = 2U * (uint32_t)total_error;
    count1 = window * freq1 / freq0;

    bool status;

    // Disable DCC and the error and done signals
    DCC_disableModule();
    DCC_disableErrorSignal();
    DCC_disableDoneSignal();

    // Configure Clock Source0 and clock source1
    DCC_setCounter0ClkSource(DCC0_BASE, DCC_COUNT0SRC_XTAL); //  clock0 ����� PLLclk
    DCC_setCounter1ClkSource(DCC0_BASE, DCC_COUNT1SRC_PLL); //  clock1 ���������ʱ��ѡ�� ��   DCC_COUNT1SRC_XTAL

    // choose err or right
    DCC_setCounterSeeds(DCC0_BASE, count0, valid, count1);

    // enableSingleShotMode
    DCC_SetSingle_Shot();
    DCC_enableErrorSignal();
    DCC_enableDoneSignal();

    if (!DCC_getErrorStatus(DCC0_BASE))
        puts("pass");
    else
        puts("no pass");
    puts("test_SingleShotMode over");
}

void test_NoSingleShotMode()
{ // ���Է�SingleShotMode ģʽ

    float32_t total_error;
    float32_t window;
    uint32_t count0;
    uint32_t valid;
    uint32_t count1;
    //   bool status;

    float32_t freq0     = 10.0F;     // sel_clk  ���ֿ���ѡ�� Xtal��clk1��clk2
    float32_t freq1     = 50.0F;     // PLL_clk  Ƶ��  40M-400M
    float32_t tolerance = 1.0F;
    float32_t freqerr   = 0.0F;

    if (freq1 > freq0)
    {
        total_error = 2.0F;
    }
    else
    {
        total_error = 2.0F * (freq0 / freq1);
    }

    total_error += 3.0F;

    window = total_error / (0.01F * tolerance);

    total_error += window * (freqerr / 100.0F);

    count0 = window - total_error;
    valid  = 2U * (uint32_t)total_error;
    count1 = window * freq1 / freq0;

    // Disable DCC and the error and done signals
    DCC_disableModule();
    DCC_disableErrorSignal();
    DCC_disableDoneSignal();

    // Configure Clock Source0 and clock source1�� ��
    DCC_setCounter0ClkSource(DCC0_BASE, DCC_COUNT0SRC_XTAL);
    DCC_setCounter1ClkSource(DCC0_BASE, DCC_COUNT1SRC_PLL);

    DCC_setCounterSeeds(DCC0_BASE, count0, valid, count1);

    DCC_DisSetSingle_Shot();  // ���÷ǵ���ģʽ
    Dcc0Regs->DCCGCTRL.bit.DONEENA = 0x1;

    // Enable DCC to start counting
    DCC_enableModule();

    // Wait until Error or Done Flag is generated
    if (!DCC_getErrorStatus(DCC0_BASE))
        puts("pass");
    else
        puts("no pass");

    puts("over");
}

void test_interupt()
{ // �жϲ���
    // Verify the frequency of PLL clock using the XTAL as reference clock

    float32_t total_error;
    float32_t window;
    uint32_t count0;
    uint32_t valid;
    uint32_t count1;
    // bool status;

    float32_t freq0     = 10.0F; // PLL_clk  Ƶ��  40M-400M
    float32_t freq1     = 50.0F;  // sel_clk  ���ֿ���ѡ�� Xtal��clk1��clk2
    float32_t tolerance = 1.0F;
    float32_t freqerr   = 0.0F;

    if (freq1 > freq0)
    {
        total_error = 2.0F;
    }
    else
    {
        total_error = 2.0F * (freq0 / freq1);
    }

    total_error += 3.0F;
    window = total_error / (0.01F * tolerance);
    total_error += window * (freqerr / 100.0F);

    count0 = window - total_error;
    valid  = 2U * (uint32_t)total_error;
    count1 = window * freq1 / freq0;

    // Disable DCC and the error and done signals
    DCC_disableModule();
    DCC_disableErrorSignal();
    DCC_disableDoneSignal();

    // Configure Clock Source0 and clock source1
    // DCC_setCounter1ClkSource ��  ѡ��ʱ��
    // DCC_setCounter0ClkSource ��  �ο�ʱ�� ��
    DCC_setCounter0ClkSource(DCC0_BASE, DCC_COUNT0SRC_INTOSC2); //  clock0 ����� PLLclk
    DCC_setCounter1ClkSource(DCC0_BASE, DCC_COUNT1SRC_PLL); //  clock1 ���������ʱ��ѡ�� ��   DCC_COUNT1SRC_XTAL

    DCC_setCounterSeeds(DCC0_BASE, count0, valid, count1);

    DCC_SetSingle_Shot(); //  0xa5aaΪ��SingleShotMode
     // Enable Single Shot mode
    DCC_enableSingleShotMode(DCC_MODE_COUNTER_ZERO);

     // Enable Error Signal and Done signal
    DCC_enableErrorSignal();
    DCC_enableDoneSignal();

     // Enable DCC to start counting
     DCC_enableModule();
    // Wait until Error or Done Flag is generated
    // Returns true if DCC completes without error

    puts("interupt_test over");
}

void DCC_verify()
{   //  DCC_COUNT1SRC_PLL Ϊ 50 HZ     DCC_COUNT0SRC_INTOSC2Ϊ 10 HZ        0.1 Ϊ���̶�
    status = DCC_verifyClockFrequency(DCC0_BASE, DCC_COUNT1SRC_PLL, 50, DCC_COUNT0SRC_INTOSC2, 10, 0.1, 0);
}

void test_dcc()
{
    puts("begin dcc_test...");
    Interrupt_enable(INT_DCC);
// ��ÿ�����Ժ����У���������ʱ��Ƶ��(������ 50HZ �� ϵͳʱ�� 10HZ)
//  DCC_verify();
//  test_SingleShotMode();
//  test_NoSingleShotMode();
  test_interupt();
    puts("DCC_test over ");
    simple_delay(1500);
}
