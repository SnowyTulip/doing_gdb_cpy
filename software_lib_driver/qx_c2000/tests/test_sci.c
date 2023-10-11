#include "common.h"
#include <string.h>

#define DATA_NUM 8

int sci0_cnt = 0;
int sci1_cnt = 0;

char sci0_data[DATA_NUM] = { 0 };
char sci1_data[DATA_NUM] = { 0 };

__interrupt void scia_isr(void)
{
    if (SCI_getInterruptStatus(SciaRegs) == 0x04)
        sci0_data[sci0_cnt++] = SCI_readCharNonBlocking(SciaRegs);
    else
        printf("sci0 int flag error(%x)\n", SCI_getInterruptStatus(SciaRegs));
}

__interrupt void scib_isr(void)
{
    if (sci1_cnt < DATA_NUM)
        SCI_writeCharNonBlocking(ScibRegs, sci1_data[sci1_cnt++]);
    else
        SCI_enableInterrupt(ScibRegs, 0);
}

void SCI_Basic_Init(
    u32 div, u32 baud_int, u8 baud_fra, SCI_DataWidthType data_bit, SCI_StopBitType stop_bit, SCI_ParityType parity)
{
    SCI_setConfig(SciaRegs, baud_int, baud_fra, data_bit, stop_bit, parity);
    SCI_setConfig(ScibRegs, baud_int, baud_fra, data_bit, stop_bit, parity);
}

void test_sci_config()
{
    int i = 0, j = 0, c = 0;
    puts("test_sci_config");
    StdOutInit(SciaRegs);

    int sci_cfg_table[][6] = {
        /* basic 50MHz sys_clk caculate baudrate */
        { 1, 3, 6, SCI_DATA_8BITS, SCI_STOP_BIT_1, SCI_PARITY_NONE }, // 921600
        { 1, 3, 6, SCI_DATA_7BITS, SCI_STOP_BIT_1, SCI_PARITY_NONE },
        { 1, 3, 6, SCI_DATA_6BITS, SCI_STOP_BIT_1, SCI_PARITY_NONE },
        { 1, 3, 6, SCI_DATA_5BITS, SCI_STOP_BIT_1, SCI_PARITY_NONE },
        { 1, 3, 6, SCI_DATA_8BITS, SCI_STOP_BIT_2, SCI_PARITY_NONE },
        { 1, 3, 6, SCI_DATA_8BITS, SCI_STOP_BIT_1, SCI_PARITY_ODD },
        { 1, 3, 6, SCI_DATA_8BITS, SCI_STOP_BIT_1, SCI_PARITY_EVEN },
        { 25, 2, 0, SCI_DATA_8BITS, SCI_STOP_BIT_1, SCI_PARITY_NONE },
        { 50, 2, 0, SCI_DATA_8BITS, SCI_STOP_BIT_1, SCI_PARITY_NONE },
    };
    for (i = 0; i < sizeof(sci_cfg_table) / sizeof(sci_cfg_table[0]); i++)
    {
        SCI_Basic_Init(sci_cfg_table[i][0], sci_cfg_table[i][1], sci_cfg_table[i][2], sci_cfg_table[i][3],
            sci_cfg_table[i][4], sci_cfg_table[i][5]);
        for (j = 0; j < DATA_NUM; j++)
        {
            SCI_writeCharBlocking(ScibRegs, j);
            c = SCI_readCharBlocking(SciaRegs);
            if (c != j)
            {
                StdOutInit(SciaRegs);
                puts("error: sci tests failed!");
                EndSimulation();
            }
        }
        simple_delay(20);
    }
}

void test_sci_send_int()
{
    int i = 0, j = 0, c = 0;
    StdOutInit(SciaRegs);
    puts("SCI send interrupt test...");
    sci1_cnt = 0;
    for (i = 0; i < DATA_NUM; i++)
        sci1_data[i] = i;
    SCI_Basic_Init(1, 13, 9, SCI_DATA_8BITS, SCI_STOP_BIT_1, SCI_PARITY_NONE);
    Interrupt_enable(INT_SCIB);
    SCI_enableInterrupt(ScibRegs, SCI_INT_SET_TXRDY);
    for (j = 0; j < DATA_NUM; j++)
    {
        c = SCI_readCharBlocking(SciaRegs);
        if (c != j)
        {
            StdOutInit(SciaRegs);
            puts("error: sci tests failed!");
            EndSimulation();
        }
    }
}

void test_sci_recv_int()
{
    int i;
    StdOutInit(SciaRegs);
    puts("SCI recv interrupt test...");
    sci0_cnt = 0;
    memset(sci0_data, 0, sizeof(sci0_data));
    SCI_Basic_Init(1, 13, 9, SCI_DATA_8BITS, SCI_STOP_BIT_1, SCI_PARITY_NONE);
    Interrupt_enable(INT_SCIA);
    SCI_enableInterrupt(SciaRegs, SCI_INT_SET_RXRDY);
    for (i = 0; i < DATA_NUM; i++)
        SCI_writeCharBlocking(ScibRegs, i);
    while (sci0_cnt < DATA_NUM)
        ;
    for (i = 0; i < DATA_NUM; i++)
    {
        if (sci0_data[i] != i)
        {
            StdOutInit(SciaRegs);
            puts("error: sci tests failed!");
            EndSimulation();
        }
    }
    SCI_enableInterrupt(SciaRegs, 0);
}

void test_sci_send_and_recv_int()
{
    int i;
    StdOutInit(SciaRegs);
    puts("SCI send & recv interrupt test...");
    sci0_cnt = 0;
    sci1_cnt = 0;
    for (i = 0; i < DATA_NUM; i++)
        sci1_data[i] = i;
    memset(sci0_data, 0, sizeof(sci0_data));
    SCI_Basic_Init(1, 13, 9, SCI_DATA_8BITS, SCI_STOP_BIT_1, SCI_PARITY_NONE);
    Interrupt_enable(INT_SCIA);
    SCI_enableInterrupt(SciaRegs, SCI_INT_SET_RXRDY);
    Interrupt_enable(INT_SCIB);
    SCI_enableInterrupt(ScibRegs, SCI_INT_SET_TXRDY);
    while (sci0_cnt < DATA_NUM)
        ;
    for (i = 0; i < DATA_NUM; i++)
    {
        if (sci0_data[i] != sci1_data[i])
        {
            printf("%x %x %x\n", i, sci0_data[i], sci1_data[i]);
            {
                StdOutInit(SciaRegs);
                puts("error: sci tests failed!");
                EndSimulation();
            }
        }
    }
    SCI_enableInterrupt(SciaRegs, 0);
}

void test_sci(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIB);
    GPIO_Config(10, GPIO_10_SCIB_TX, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_Config(8, GPIO_8_SCIA_TX, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    // GPIO_Config(11, GPIO_11_SCIB_RX_2, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_Config(9, GPIO_9_SCIA_RX, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);

    // test_sci_config();
    // test_sci_send_int();
    // test_sci_recv_int();
    test_sci_send_and_recv_int();

    StdOutInit(SciaRegs);
    puts("succeed: sci tests passed");
    EndSimulation();
}
