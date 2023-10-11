#include "common.h"

int send_cnt = 0;
int recv_cnt = 0;

u8 recv_buf[64] = { 0 };
u8 send_buf[64] = { 0 };

__interrupt void cana_isr(void)
{
    u32 ints = CAN_getAndAutoClearInterrupt(CanARegs);
    printf("A=%x\n", ints);

    if (ints & CAN_INT_TRANS)
    {
        send_cnt++;
    }

    if (ints & CAN_INT_ERROR_WARNNING)
    { }

    if (ints & CAN_INT_OVERRUN)
    { }

    if (ints & CAN_INT_WAKEUP)
    { }

    if (ints & CAN_INT_ERROR_PASSIVE)
    { }
}

__interrupt void canb_isr(void)
{
    int lr = ExpRegs->EPCR; // save link return register

    PieCtrlRegs->IER.bit.GROUP9 = 1; // enable canb group
    PieCtrlRegs->PIEIER9.bit.INTx6 = 0; // disable self interrupt
    EINT;

    u32 ints = CAN_getAndAutoClearInterrupt(CanBRegs);
    printf("B=%x\n", ints);

    if (ints & CAN_INT_RECV)
    {
        CAN_recvFrameBlocking(CanBRegs, recv_buf);
        recv_cnt++;
    }

    if (ints & CAN_INT_ERROR_WARNNING)
    { }

    if (ints & CAN_INT_OVERRUN)
    { }

    if (ints & CAN_INT_WAKEUP)
    { }

    if (ints & CAN_INT_ERROR_PASSIVE)
    { }

    DINT;
    ExpRegs->EPCR = lr; // recover link return register
    PieCtrlRegs->PIEIER9.bit.INTx6 = 1; // enable self interrupt
}

static void CAN_Config(
    CAN_REGS *can, u32 clk_div, CAN_ModeType modes, CAN_OutputModeType out_mode, u32 acr, u32 amr, u32 ints)
{
    CAN_setClkDiv(can, clk_div);
    CAN_setMode(can, CAN_MODE_RESET);
    CAN_setAcceptFilter(can, acr, amr);
    CAN_setInterrupt(can, ints);
    // 500K bundrate when can pclk = 16Mhz, sample rate = 81.25%
    CAN_setBusTiming(can, 0, 0, 11, 2, 0);
    CAN_setOutputMode(can, out_mode);
    CAN_setRecvBuffStartOffset(can, 0);
    CAN_setClockOutDivider(can, CAN_CLKOUT_DIV_1);
    // CAN_disableClockOutput(can);
    CAN_setMode(can, modes);
}

void test_can_standard_frame_send_loop(void)
{
    puts("test_can_standard_frame_send_loop");
    CAN_Config(CanARegs, 4, CAN_MODE_SINGLE_FILTER, CAN_OUTPUT_MODE_NORMAL, STA_FRAME_SINGLE_FITER(0x111U, 0, 0, 0),
        0x001fffffU, CAN_INT_NONE);
    // CAN_Config(CanBRegs, 10, CAN_MODE_SINGLE_FILTER, CAN_OUTPUT_MODE_NORMAL, STA_FRAME_SINGLE_FITER(0x222U, 0, 0, 0),
    // 0x001fffffU, CAN_INT_NONE);
    simple_delay(200); // wait for CanB init ready
    while (1)
    {
        puts("can1 send...");
        CAN_sendStandardFrame(CanARegs, 0x444, CAN_FRAME_DATA, send_buf, 8);
        simple_delay(300000);
    }
}

void test_can_standard_frame_with_single_filter(void)
{
    puts("test_can_standard_frame_with_single_filter");
    // 0x001fffffU filter_mask mean only filter frame id, donot care frame type, and care all sta frame id
    CAN_Config(CanARegs, 1, CAN_MODE_SINGLE_FILTER, CAN_OUTPUT_MODE_NORMAL, STA_FRAME_SINGLE_FITER(0x111U, 0, 0, 0),
        0x001fffffU, CAN_INT_NONE);
    CAN_Config(CanBRegs, 1, CAN_MODE_SINGLE_FILTER, CAN_OUTPUT_MODE_NORMAL, STA_FRAME_SINGLE_FITER(0x222U, 0, 0, 0),
        0x001fffffU, CAN_INT_NONE);
    simple_delay(200); // wait for CanB init ready
    // CAN_setCmd(CanBRegs, CAN_CMD_CLEAR_DATA_OVERRUN | CAN_CMD_RELEASE_RECV_BUFF);

    //  send + recv frame1, frame id match
    CAN_sendStandardFrame(CanARegs, 0x222U, CAN_FRAME_DATA, send_buf, 8);
    while ((CAN_getStatus(CanBRegs) & CAN_STATUS_RECV_BUFFER) == 0)
        ;
    CAN_recvFrameBlocking(CanBRegs, recv_buf);
    verify_data_byte(&recv_buf[3], &send_buf[0], 8);

    //  send + recv frame2, frame id no matched
    /* CAN_sendStandardFrame(CanARegs, 0x333U, CAN_FRAME_DATA, send_buf, 8);
    simple_delay(1000); [> wait for frame send over <]
    if ((CAN_getStatus(CanBRegs) & CAN_STATUS_RECV_BUFFER) == 0)
        puts("single filter test passed");
    else
        puts("single filter test failed!!!"); */
}

void test_can_standard_frame_with_double_filter(void)
{
    puts("test_can_standard_frame_with_double_filter");
    CAN_Config(CanARegs, 10, CAN_MODE_DOUBLE_FILTER, CAN_OUTPUT_MODE_NORMAL, 0, 0xffffffffU, CAN_INT_NONE);
    // 0x001f001fU filter_mask mean only filter frame id1 + id2, donot care frame type + data1/data2
    CAN_Config(CanBRegs, 10, CAN_MODE_DOUBLE_FILTER, CAN_OUTPUT_MODE_NORMAL,
        STA_FRAME_DOUBLE_FITER(0x222U, 0, 0x333U, 0, 0, 0), 0x001f001fU, CAN_INT_NONE);
    simple_delay(200); // wait for CanB init ready

    //  send + recv frame1, frame id match filter ID1
    CAN_sendStandardFrame(CanARegs, 0x222U, CAN_FRAME_DATA, send_buf, 8);
    while ((CAN_getStatus(CanBRegs) & CAN_STATUS_RECV_BUFFER) == 0)
        ;
    CAN_recvFrameBlocking(CanBRegs, recv_buf);
    verify_data_byte(&recv_buf[3], &send_buf[0], 8);

    //  send + recv frame2, frame id match filter ID2
    CAN_sendStandardFrame(CanARegs, 0x333U, CAN_FRAME_REMOTE, &send_buf[8], 8);
    while ((CAN_getStatus(CanBRegs) & CAN_STATUS_RECV_BUFFER) == 0)
        ;
    CAN_recvFrameBlocking(CanBRegs, recv_buf);
    verify_data_byte(&recv_buf[3], &send_buf[8], 8);

    //  send + recv frame3, frame id no match filter ID1 or ID2
    CAN_sendStandardFrame(CanARegs, 0x444U, CAN_FRAME_DATA, &send_buf[16], 8);
    simple_delay(1000); // wait for frame send over
    if ((CAN_getStatus(CanBRegs) & CAN_STATUS_RECV_BUFFER) == 0)
        puts("single filter test passed");
    else
        puts("single filter test failed!!!");
}

void test_can_extend_frame_with_single_filter(void)
{
    puts("test_can_extend_frame_with_single_filter");
    CAN_Config(CanARegs, 25, CAN_MODE_SINGLE_FILTER, CAN_OUTPUT_MODE_NORMAL, 0, 0xffffffffU, CAN_INT_NONE);
    // 0x0000007U filter_mask mean only filter frame id
    CAN_Config(CanBRegs, 25, CAN_MODE_SINGLE_FILTER, CAN_OUTPUT_MODE_NORMAL, EXT_FRAME_SINGLE_FITER(0x12234412, 0),
        0x0000007U, CAN_INT_NONE);
    CAN_setCmd(CanBRegs, CAN_CMD_CLEAR_DATA_OVERRUN | CAN_CMD_RELEASE_RECV_BUFF);
    simple_delay(200); // wait for CanB init ready

    //  send + recv frame1, frame id match filter ID
    CAN_sendExtendFrame(CanARegs, 0x12234412, CAN_FRAME_DATA, send_buf, 8);
    while ((CAN_getStatus(CanBRegs) & CAN_STATUS_RECV_BUFFER) == 0)
        ;
    CAN_recvFrameBlocking(CanBRegs, recv_buf);
    verify_data_byte(&recv_buf[3], &send_buf[0], 8);

    //  send + recv frame2, frame id no match filter ID
    CAN_sendExtendFrame(CanARegs, 0x12234413, CAN_FRAME_DATA, &send_buf[8], 8);
    simple_delay(1000); // wait for frame send over
    if ((CAN_getStatus(CanBRegs) & CAN_STATUS_RECV_BUFFER) == 0)
        puts("single filter test passed");
    else
        puts("single filter test failed!!!");
}

void test_can_extend_frame_with_double_filter(void)
{
    puts("test_can_extend_frame_with_double_filter");
    CAN_Config(CanARegs, 25, CAN_MODE_SINGLE_FILTER, CAN_OUTPUT_MODE_NORMAL, 0, 0xffffffffU, CAN_INT_NONE);
    // 0x00070007U filter_mask mean only filter frame id1 or id2
    CAN_Config(CanBRegs, 25, CAN_MODE_SINGLE_FILTER, CAN_OUTPUT_MODE_NORMAL,
        EXT_FRAME_DOUBLE_FITER(0x11220000, 0x11330000), 0x00070007U, CAN_INT_NONE);
    CAN_setCmd(CanBRegs, CAN_CMD_CLEAR_DATA_OVERRUN | CAN_CMD_RELEASE_RECV_BUFF);
    simple_delay(100); // wait for CanB init ready

    //  send + recv frame1, frame id match filter ID1
    CAN_sendExtendFrame(CanARegs, 0x11223344, CAN_FRAME_DATA, send_buf, 8);
    while ((CAN_getStatus(CanBRegs) & CAN_STATUS_RECV_BUFFER) == 0)
        ;
    CAN_recvFrameBlocking(CanBRegs, recv_buf);
    verify_data_byte(&recv_buf[3], &send_buf[0], 8);

    //  send + recv frame1, frame id match filter ID2
    CAN_sendExtendFrame(CanARegs, 0x11331111, CAN_FRAME_REMOTE, &send_buf[8], 8);
    while ((CAN_getStatus(CanBRegs) & CAN_STATUS_RECV_BUFFER) == 0)
        ;
    CAN_recvFrameBlocking(CanBRegs, recv_buf);
    verify_data_byte(&recv_buf[3], &send_buf[8], 8);

    //  send + recv frame2, frame id no match filter ID1 or ID2
    CAN_sendExtendFrame(CanARegs, 0x11442233, CAN_FRAME_DATA, &send_buf[16], 8);
    simple_delay(1000); // wait for frame send over
    if ((CAN_getStatus(CanBRegs) & CAN_STATUS_RECV_BUFFER) == 0)
        puts("single filter test passed");
    else
        puts("single filter test failed!!!");
}

void test_can_with_recv_and_trans_interrupt(void)
{
    puts("test_can_with_recv_and_trans_interrupt");
    Interrupt_enable(INT_CANA);
    Interrupt_enable(INT_CANB);
    // 0x001fffffU filter_mask mean only filter frame id, donot care frame type, and care all frame id
    CAN_Config(CanBRegs, 2, CAN_MODE_SINGLE_FILTER, CAN_OUTPUT_MODE_NORMAL, STA_FRAME_SINGLE_FITER(0x888U, 0, 0, 0),
        0x001fffffU, CAN_INT_RECV);
    CAN_setCmd(CanBRegs, CAN_CMD_CLEAR_DATA_OVERRUN | CAN_CMD_RELEASE_RECV_BUFF);
    simple_delay(200); // wait for frame send over
    CAN_Config(CanARegs, 2, CAN_MODE_SINGLE_FILTER, CAN_OUTPUT_MODE_NORMAL, 0, 0xffffffffU, CAN_INT_TRANS);
    CAN_sendStandardFrame(CanARegs, 0x888U, CAN_FRAME_DATA, send_buf, 8);
    while (send_cnt == 0 || recv_cnt == 0)
        ;
    verify_data_byte(&recv_buf[3], &send_buf[0], 8);
}

void test_can_with_clockout(void)
{
    puts("test_can_with_clockout");
    // 0x001fffffU filter_mask mean only filter frame id, donot care frame type, and care all frame id
    CAN_Config(CanBRegs, 10, CAN_MODE_SINGLE_FILTER, CAN_OUTPUT_MODE_CLOCKOUT, STA_FRAME_SINGLE_FITER(0x888U, 0, 0, 0),
        0x001fffffU, CAN_INT_NONE);

    CAN_Config(CanARegs, 10, CAN_MODE_SINGLE_FILTER, CAN_OUTPUT_MODE_CLOCKOUT, 0, 0xFFFFFFFFU, CAN_INT_NONE);
    CAN_sendStandardFrame(CanARegs, 0x888U, CAN_FRAME_DATA, send_buf, 8);

    while ((CAN_getStatus(CanBRegs) & CAN_STATUS_RECV_BUFFER) == 0)
        ;
    CAN_recvFrameBlocking(CanBRegs, recv_buf);
    verify_data_byte(&recv_buf[3], &send_buf[0], 8);
}

void test_can(void)
{
    for (int i = 0; i < sizeof(send_buf); i++)
        send_buf[i] = i + 1;
    // enable module clock
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANB);

    // config IO mux
    GPIO_Config(4, GPIO_4_CANA_TX, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_Config(6, GPIO_6_CANB_TX, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);

    GPIO_Config(5, GPIO_5_CANA_RX, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_Config(7, GPIO_7_CANB_RX, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);

    // test_can_standard_frame_send_loop();
    // test_can_standard_frame_with_single_filter();
    // test_can_standard_frame_with_double_filter();
    // test_can_extend_frame_with_single_filter();
    // test_can_extend_frame_with_double_filter();
    test_can_with_recv_and_trans_interrupt();
    // test_can_with_clockout();

    puts("can test end");
};
