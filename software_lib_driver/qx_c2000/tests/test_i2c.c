#include "common.h"

//#ifdef TEST_I2C

// int send_cnt = 0;
// int recv_cnt = 0;
// char send_data[16] = { 0 };
// char recv_data[16] = { 0 };

u8 buf[32]    = { 0 };
char recv_len = 0;

// 中断服务函数
int reg = 0, flag0 = 0, flag1 = 0, read_val = 0;

# if 1 //test_i2c_fpga_read_reg() 中断
__interrupt void i2ca_isr(void)
{

	printf("I2C1=%x\n", I2C1->IC_INTR_STAT.all); //
    if (I2C1->IC_INTR_STAT.all == 0x4)

    {
        reg = I2C1->IC_DATA_CMD.bit.DATA;
        //printf("reg = %d\n", reg);
        int a = I2C1->IC_CLR_STOP_DET;
    }
    else
    {
        I2C1->IC_DATA_CMD.bit.DATA = HWREGH(I2CA_BASE + reg * 4);
        int a = I2C1->IC_CLR_RD_REQ;
    }
}

__interrupt void pmbus_isr(void)
{

    printf("i2c2 %x\n", I2C2->IC_INTR_STAT.all);
    if(I2C2->IC_INTR_STAT.all == 0x200)
    {
    	int a   = I2C2->IC_CLR_STOP_DET;
    	flag0 =1;
    }
    else{

    	I2C2->IC_DATA_CMD.bit.DATA = 0xaf;
    	I2C2->IC_DATA_CMD.bit.DATA = 0xaa;
    	I2C2->IC_DATA_CMD.bit.DATA = 0xaf;
    	I2C2->IC_DATA_CMD.bit.DATA = 0xaa;
    	int a  = I2C2->IC_CLR_RD_REQ;
    }

}
#endif

# if 0  //test_i2c_fpga_read_reg() 中断
__interrupt void i2ca_isr(void)
{
	printf("%x\n", I2C1->IC_INTR_STAT.all); //
    if (I2C1->IC_INTR_STAT.all == 0x4)
    {
        reg = I2C1->IC_DATA_CMD.bit.DATA;
        printf("reg = %x\n", reg);
        int a = I2C1->CLR_STOP_DET_BIT;
    }
}
__interrupt void pmbus_isr(void)
{
    printf("i2c2 %x\n", I2C1->IC_INTR_STAT);
    read_val = I2C2->IC_DATA_CMD.bit.DATA;
    flag1++;
    int a = I2C2->CLR_STOP_DET;
}
#endif


# if 0  //test_i2c_fpga_master_send()   FPGA 作为主发送
__interrupt void i2ca_isr(void)
{
	printf("I2C1=%x\n", I2C1->IC_INTR_STAT); //
    if (I2C1->IC_INTR_STAT == 0x4)
    {
        reg = I2C1->IC_DATA_CMD.bit.DATA;
        printf("reg = %x\n", reg);
        int a = I2C1->CLR_STOP_DET_BIT.CLR_STOP_DET;
    }
}
__interrupt void pmbus_isr(void)
{
    printf("i2c2=%x\n", I2C1->IC_INTR_STAT);
    read_val = I2C2->IC_DATA_CMD.bit.DATA;
    flag1++;
    int a = I2C2->CLR_STOP_DET_BIT.CLR_STOP_DET;
}
#endif


# if 0  //test_MasterTX_SlaveRX_7bitAdress_SS()   FPGA 作为主发送
__interrupt void i2ca_isr(void)
{
	printf("I2C1=%x\n", I2C1->IC_INTR_STAT.all);
    if (I2C1->IC_INTR_STAT.all == 0x10)
    {

        I2C1->IC_DATA_CMD.bit.DATA =0xf0;
        I2C1->IC_DATA_CMD.bit.DATA =0xf0;
        I2C1->IC_DATA_CMD.bit.DATA =0xf0;
        I2C1->IC_DATA_CMD.bit.DATA =0xf0;
        I2C1->IC_DATA_CMD.bit.DATA =0xf0;
        I2C1->IC_DATA_CMD.bit.DATA =0xf0;
        I2C1->IC_DATA_CMD.bit.DATA =0xf0;
        I2C1->IC_DATA_CMD.bit.DATA =0xf0;
        int a = I2C1->IC_CLR_STOP_DET;

    }
}
__interrupt void pmbus_isr(void)
{
    printf("i2c2=%x\n", I2C1->IC_INTR_STAT.all);
    read_val = I2C2->IC_DATA_CMD.bit.DATA;
    flag1++;
    int a = I2C2->IC_CLR_STOP_DET;
}
#endif





void test_MasterTX_SlaveRX_7bitAdress_SS() // test 1 ：主发从收  7bit  标准速率
{
    // test 1 ： 7bit 标准速率  主发从收  10KHZ
	puts("start...");
    I2C1->IC_ENABLE.bit.ENABLE = 0;
    I2C1->IC_CON.all            = 0x63; //   0x75 表示打开10bit 传输；  0x65 快速       0x63标准
    I2C1->IC_TAR.all            = 0x05;
//    I2C1->IC_TX_TL = 0x7;
//    I2C1->IC_SS_SCL_HCNT.all    = 0xa4;
//    I2C1->IC_SS_SCL_LCNT.all    = 0xa5;
    I2C1->IC_INTR_MASK.all      = 0x000;
    I2C1->IC_ENABLE.bit.ENABLE = 1;
//    I2C1->IC_DATA_CMD.bit.CMD  = 0;

    I2C2->IC_ENABLE.bit.ENABLE = 0;
    I2C2->IC_CON.all            = 0x02;
    I2C2->IC_SAR.all            = 0x05;
    //      I2C2->IC_RX_TL = 0x7;
    I2C2->IC_INTR_MASK.all      = 0x00;
    I2C2->IC_ENABLE.bit.ENABLE = 1;
    I2C2->IC_DATA_CMD.bit.CMD  = 1;


    I2C1->IC_DATA_CMD.bit.DATA = 0xaa;
    I2C1->IC_DATA_CMD.bit.DATA = 0x55;
    // I2C1->IC_DATA_CMD.DATA = 0xee;
    // I2C1->IC_DATA_CMD.DATA = 0xee;
    //
    //

    //      printf("%x\n", I2C2->IC_DATA_CMD.bit.DATA);
    //      printf("%x\n", I2C2->IC_DATA_CMD.bit.DATA);
    printf("I2C1=%x\n", I2C1->IC_INTR_STAT.all);

    puts("I2C test over");
}

void test_MasterTX_SlaveRX_7bitAdress_FS() // test 2 ：主发从收  7bit  快速速率
{
    // test 2 ：主发从收  7bit 快速速率
    I2C1->IC_ENABLE.bit.ENABLE = 0;
    I2C1->IC_CON.all            = 0x65; //   0x75 表示打开10bit 传输；  0x65 快速 0x63标准
    I2C1->IC_TAR.all            = 0x05;
    I2C1->IC_FS_SCL_HCNT.all    = 0x10;
    I2C1->IC_FS_SCL_LCNT.all    = 0x10;
    I2C1->IC_INTR_MASK.all     = 0x000;
    I2C1->IC_ENABLE.bit.ENABLE = 1;
    //      I2C1->IC_DATA_CMD.CMD = 0;

    I2C2->IC_ENABLE.bit.ENABLE = 0;
    I2C2->IC_CON.all            = 0x04;
    I2C2->IC_SAR.all            = 0x05;
    I2C2->IC_INTR_MASK.all      = 0x000;
    I2C2->IC_ENABLE.bit.ENABLE = 1;


    I2C1->IC_DATA_CMD.bit.DATA = 0xff;
    I2C1->IC_DATA_CMD.bit.DATA = 0xaa;
    I2C1->IC_DATA_CMD.bit.DATA = 0xff;
    I2C2->IC_DATA_CMD.bit.CMD  = 1;
    puts("I2C test over");
}

void test_MasterTX_SlaveRX_10bitAdress_SS() // test 3 ：主发从收  10bit 标准速率  24KHZ
{
    // test 3 ：主发从收  10bit 标准速率  24KHZ
    I2C1->IC_ENABLE.bit.ENABLE = 0;
    I2C1->IC_CON.all           = 0x73; //   0x75 表示打开10bit 传输；  0x65 快速 0x63标准
    I2C1->IC_TAR.all            = 0x05;

    I2C1->IC_FS_SCL_HCNT.bit.FS_SCL_HCNT = 200;
    I2C1->IC_FS_SCL_LCNT.bit.FS_SCL_LCNT = 200;

    I2C1->IC_INTR_MASK.all      = 0x000;
    I2C1->IC_ENABLE.bit.ENABLE = 1;
    I2C1->IC_DATA_CMD.bit.CMD  = 0;

    I2C1->IC_DATA_CMD.bit.DATA = 0xff;
    I2C1->IC_DATA_CMD.bit.DATA = 0xaa;
    I2C1->IC_DATA_CMD.bit.DATA = 0xff;

    I2C2->IC_ENABLE.bit.ENABLE = 0;
    I2C2->IC_CON.all            = 0x0a; // 0x0a 表示 10 bit 标准模式；
    I2C2->IC_SAR.all           = 0x05;
    I2C2->IC_INTR_MASK.all      = 0x000;
    I2C2->IC_ENABLE.bit.ENABLE = 1;
    I2C1->IC_DATA_CMD.bit.CMD  = 1;
    puts("over");
}

void test_MasterTX_SlaveRX_10bitAdress_FS() // test 4 ：主发从收  10bit 快速速率  24KHZ
{
    // test 4 ：主发从收  10bit 快速速率  24KHZ
    I2C1->IC_ENABLE.bit.ENABLE          = 0;
    I2C1->IC_CON.all                    = 0x75; //   0x75 表示打开10bit 传输；  0x65 快速 0x63标准
    I2C1->IC_TAR.all                    = 0x05;
    I2C1->IC_FS_SCL_HCNT.all    = 0x10;
    I2C1->IC_FS_SCL_LCNT.all    = 0x10;
    I2C1->IC_INTR_MASK.all             = 0x000;
    I2C1->IC_ENABLE.bit.ENABLE         = 1;

    I2C2->IC_ENABLE.bit.ENABLE = 0;
    I2C2->IC_CON.all            = 0x0a; // 0x0a 表示 10 bit 标准模式；
    I2C2->IC_SAR.all            = 0x05;
    I2C2->IC_INTR_MASK.all      = 0x000;
    I2C2->IC_ENABLE.bit.ENABLE = 1;
    I2C2->IC_DATA_CMD.bit.CMD  = 1;

    I2C1->IC_DATA_CMD.bit.DATA = 0xff;
    I2C1->IC_DATA_CMD.bit.DATA = 0xaa;
    I2C1->IC_DATA_CMD.bit.DATA = 0xff;
    puts("over");
}

void test_SlaveTX_MasterRX_7bitAdress_SS()  // test 5 ：从发主收  7bit  标准速率  10KHZ   ==> 打开中断
{
    I2C2->IC_ENABLE.bit.ENABLE = 0;
    /// I2C2->CON = 0x24;            // 0x0a 表示 10 bit 标准模式；
    I2C2->IC_CON.all                    = 0x22; // 0x0a 表示 10 bit 标准模式；
    I2C2->IC_SAR.all                    = 0x05;
    I2C2->IC_INTR_MASK.all              = 0x060;
    I2C2->IC_TX_TL                    = 0x3;
    I2C2->IC_ENABLE.bit.ENABLE = 1;

    I2C1->IC_ENABLE.bit.ENABLE = 0;
    I2C1->IC_CON.all       = 0x63; //   0x75 表示打开10bit 传输；  0x65 快速 0x63标准
    I2C1->IC_TAR.all       = 0x05;

    I2C1->IC_INTR_MASK.all              = 0x000;
    I2C1->IC_ENABLE.bit.ENABLE = 1;

    I2C1->IC_DATA_CMD.bit.CMD = 1;
    I2C1->IC_DATA_CMD.bit.CMD = 1;
    I2C1->IC_DATA_CMD.bit.CMD = 1;
    I2C1->IC_DATA_CMD.bit.CMD = 1;

    printf("c=%x\n", I2C1->IC_DATA_CMD.bit.DATA);
    printf("c=%x\n", I2C1->IC_DATA_CMD.bit.DATA);
    printf("c=%x\n", I2C1->IC_DATA_CMD.bit.DATA);
    printf("c=%x\n", I2C1->IC_DATA_CMD.bit.DATA);

    puts("I2C test over111");
}

void test_SlaveTX_MasterRX_7bitAdress_FS()  // test 6 ：从发主收  7bit  快速速率  300KHZ
{
    I2C2->IC_ENABLE.bit.ENABLE = 0;
    I2C2->IC_CON.all        = 0x24; // 0x0a 表示 10 bit 标准模式；
    I2C2->IC_SAR.all        = 0x05;
    I2C2->IC_INTR_MASK.all  = 0x020;
    I2C2->IC_TX_TL          = 0x3;
    I2C2->IC_ENABLE.bit.ENABLE = 1;

    I2C1->IC_ENABLE.bit.ENABLE = 0;
    I2C1->IC_CON.all        = 0x65; //   0x75 表示打开10bit 传输；  0x65 快速 0x63标准
    I2C1->IC_TAR.all        = 0x05;

    I2C1->IC_FS_SCL_HCNT.all = 20;
    I2C1->IC_FS_SCL_LCNT.all = 20;
    //  I2C1->IC_SDA_HOLD.bit.IC_SDA_TX_HOLD=0x47;
    //  I2C1->IC_SDA_HOLD.bit.IC_SDA_RX_HOLD=0x47;
    I2C1->IC_INTR_MASK.all = 0x040;

    I2C1->IC_ENABLE.bit.ENABLE = 1;

    I2C1->IC_DATA_CMD.bit.CMD = 1;
    I2C1->IC_DATA_CMD.bit.CMD = 1;
    I2C1->IC_DATA_CMD.bit.CMD = 1;
    I2C1->IC_DATA_CMD.bit.CMD = 1;

    while (!I2C1->IC_RAW_INTR_STAT.bit.STOP_DET)
    {
        puts("3");
    };

    printf("c=%x\n", I2C1->IC_DATA_CMD.bit.DATA);
    printf("c=%x\n", I2C1->IC_DATA_CMD.bit.DATA);
    printf("c=%x\n", I2C1->IC_DATA_CMD.bit.DATA);
    printf("c=%x\n", I2C1->IC_DATA_CMD.bit.DATA);

    puts("I2C test over");
}

void test_SlaveTX_MasterRX_10bitAdress_SS()
{ // test 7 ：从发主收  10bit 标准速率  10KHZ
    I2C2->IC_ENABLE.bit.ENABLE = 0;
    // I2C2->CON = 0x24;            // 0x0a 表示 10 bit 标准模式；
    I2C2->IC_CON.all        = 0x0a; // 0x0a 表示 10 bit 标准模式；
    I2C2->IC_SAR.all         = 0x05;

    I2C2->IC_INTR_MASK.all  = 0x020;
    I2C2->IC_TX_TL       = 0x3;
    // I2C2->IC_SDA_HOLD.bit.IC_SDA_TX_HOLD=0x47;
    // I2C2->IC_SDA_HOLD.bit.IC_SDA_RX_HOLD=0x47;

    I2C2->IC_ENABLE.bit.ENABLE = 1;

    I2C1->IC_ENABLE.bit.ENABLE = 0;
    I2C1->IC_CON.all           = 0x75; //   0x75 表示打开10bit 传输；  0x65 快速 0x63标准
    I2C1->IC_TAR.all           = 0x05;

//    I2C1->IC_SS_SCL_HCNT.all = 100;
//    I2C1->IC_SS_SCL_LCNT.all = 100;
    I2C1->IC_INTR_MASK.all= 0x000;

    I2C1->IC_ENABLE.bit.ENABLE = 1;

    I2C1->IC_DATA_CMD.bit.CMD = 1;
    I2C1->IC_DATA_CMD.bit.CMD = 1;
    I2C1->IC_DATA_CMD.bit.CMD = 1;
    I2C1->IC_DATA_CMD.bit.CMD = 1;

    while (!I2C1->IC_RAW_INTR_STAT.bit.STOP_DET)
    {
        puts("3");
    };

    printf("c=%x\n", I2C1->IC_DATA_CMD.bit.DATA);
    printf("c=%x\n", I2C1->IC_DATA_CMD.bit.DATA);
    printf("c=%x\n", I2C1->IC_DATA_CMD.bit.DATA);
    printf("c=%x\n", I2C1->IC_DATA_CMD.bit.DATA);

    puts("I2C test over");
}

void test_SlaveTX_MasterRX_10bitAdress_FS()
{ // test 8 ：从发主收  10bit 快速速率  300KHZ
    I2C2->IC_ENABLE.bit.ENABLE = 0;
    /// I2C2->CON = 0x24;            // 0x0a 表示 10 bit 标准模式；
    I2C2->IC_CON.all         = 0x0a; // 0x0a 表示 10 bit 标准模式；
    I2C2->IC_SAR.all         = 0x05;

    I2C2->IC_INTR_MASK.all  = 0x020;
    I2C2->IC_TX_TL       = 0x3;
    // I2C2->IC_SDA_HOLD.bit.IC_SDA_TX_HOLD=0x47;
    // I2C2->IC_SDA_HOLD.bit.IC_SDA_RX_HOLD=0x47;

    I2C2->IC_ENABLE.bit.ENABLE = 1;

    I2C1->IC_ENABLE.bit.ENABLE = 0;
    I2C1->IC_CON.all          = 0x75; //   0x75 表示打开10bit 传输；  0x65 快速 0x63标准
    I2C1->IC_TAR.all            = 0x05;

    I2C1->IC_FS_SCL_HCNT.all = 20;
    I2C1->IC_FS_SCL_LCNT.all = 20;
    // I2C1->IC_SDA_HOLD.bit.IC_SDA_TX_HOLD=0x47;
    // I2C1->IC_SDA_HOLD.bit.IC_SDA_RX_HOLD=0x47;
    I2C1->IC_INTR_MASK.all = 0x000;

    I2C1->IC_ENABLE.bit.ENABLE = 1;

    I2C1->IC_DATA_CMD.bit.CMD = 1;
    I2C1->IC_DATA_CMD.bit.CMD = 1;
    I2C1->IC_DATA_CMD.bit.CMD = 1;
    I2C1->IC_DATA_CMD.bit.CMD = 1;


    while (!I2C1->IC_RAW_INTR_STAT.bit.STOP_DET)
    {
        puts("3");
    };

    printf("c=%x\n", I2C1->IC_DATA_CMD.bit.DATA);
    printf("c=%x\n", I2C1->IC_DATA_CMD.bit.DATA);
    printf("c=%x\n", I2C1->IC_DATA_CMD.bit.DATA);
    printf("c=%x\n", I2C1->IC_DATA_CMD.bit.DATA);

    puts("I2C test over");
}

void test_SlaveTX_MasterRX_7bitAdress_SS_FPGA()
{
    I2C1->IC_ENABLE.bit.ENABLE = 0;
    I2C1->IC_CON.all          = 0x22;
    I2C1->IC_SAR.all          = 0x05;
    I2C1->IC_INTR_MASK.all    = 0x220;
    I2C1->IC_ENABLE.bit.ENABLE = 1;

    while (1)
    {
        simple_delay(500000);
        puts("wait read...");
    };
}

void test_i2c_read_reg()
{
    I2C1->IC_ENABLE.bit.ENABLE = 0;
    I2C1->IC_CON.all           = 0x63; // 0x75 表示打开10bit 传输；  0x65 快速 0x63标准
    I2C1->IC_TAR.all            = 0x05;
    I2C1->IC_SS_SCL_HCNT.all    = 160;
    I2C1->IC_SS_SCL_LCNT.all   = 160;
    I2C1->IC_INTR_MASK.all      = 0x200;

    I2C1->IC_RX_TL = 0x7;
    I2C1->IC_TX_TL = 0x7;

    I2C1->IC_ENABLE.bit.ENABLE = 1;

    I2C2->IC_ENABLE.bit.ENABLE = 0;
    I2C2->IC_CON.all         = 0x22; // 0x0a 表示 10 bit 标准模式；
    I2C2->IC_SAR.all           = 0x05;
    I2C2->IC_INTR_MASK.all     = 0x220;
    I2C2->IC_ENABLE.bit.ENABLE = 1;

    // I2C2->IC_DATA_CMD.DATA= 0xaa;
    // I2C2->IC_DATA_CMD.DATA= 0xcc;
    // I2C2->IC_DATA_CMD.DATA= 0xbb;

    I2C1->IC_DATA_CMD.bit.DATA = 0x02;

    while (flag0 != 1)
        ;

    I2C1->IC_DATA_CMD.bit.CMD = 1;

    while (flag1 < 2)
    {
        puts(".");
    };

    if (read_val == 0x55)
    	puts("pass");
    else
    	puts("failed!");
}

void test_i2c_fpga_read_reg()
{
    I2C1->IC_ENABLE.bit.ENABLE = 0;
    I2C1->IC_CON.all          = 0x24; // 0x0a 表示 10 bit 标准模式；
    I2C1->IC_SAR.all          = 0x02;
    // I2C1->IC_RX_TL          = 0x1;
    // I2C1->IC_TX_TL          = 0x1;
    I2C1->IC_INTR_MASK.all      = 0x24;
    I2C1->IC_ENABLE.bit.ENABLE = 1;
    while (1)
    {
    	simple_delay(400000);
    	puts("...");
    }
}

void test_i2c_fpga_write() // 串口向FPGA 中写值，
{
    I2C1->IC_ENABLE.bit.ENABLE = 0;
    I2C1->IC_CON.all            = 0x22; // 0x0a 表示 10 bit 标准模式；
    I2C1->IC_SAR.all            = 0x02;
    // I2C1->IC_RX_TL          = 0x1;
    // I2C1->IC_TX_TL          = 0x1;
    I2C1->IC_INTR_MASK.all      = 0x24;
    I2C1->IC_ENABLE.bit.ENABLE = 1;
    while (1)
    {
    	simple_delay(400000);
    	puts("...");
//    	printf("reg=%d\n",reg);
    }
}


void test_i2c_fpga_master_send() // 串口向FPGA 中写值，
{

	while(1){

	I2C1->IC_ENABLE.bit.ENABLE = 0;
    I2C1->IC_CON.all            = 0x63; //   0x75 表示打开10bit 传输；  0x65 快速       0x63标准
    I2C1->IC_TAR.all          = 0x05;
    //      I2C1->IC_TX_TL = 0x7;
    I2C1->IC_SS_SCL_HCNT.all    = 0xa4;
    I2C1->IC_SS_SCL_LCNT.all    = 0xa5;
    I2C1->IC_INTR_MASK.all      = 0x000;
    I2C1->IC_ENABLE.bit.ENABLE = 1;
 //   I2C1->IC_DATA_CMD.bit.CMD  = 0;



    I2C1->IC_DATA_CMD.bit.DATA = 0xaa;
    I2C1->IC_DATA_CMD.bit.DATA = 0x55;

    simple_delay(400000);
    printf("nihao\n");

	}
//    while (1)
//    {
//    	simple_delay(400000);
//    	puts("...");
////    	printf("reg=%d\n",reg);
//    }
}





void test_i2c()    // 使用系统默认的 10MHZ
{
    puts("I2C test start...");
    GPIO_Config(0, GPIO_0_I2CA_SDA, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_OD|GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
    GPIO_Config(1, GPIO_1_I2CA_SCL, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_OD|GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
    GPIO_Config(2, GPIO_2_PMBUSA_SDA, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_OD, GPIO_QUAL_ASYNC);
    GPIO_Config(3, GPIO_3_PMBUSA_SCL, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_OD, GPIO_QUAL_ASYNC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CB);
    Interrupt_enable(INT_I2CA);
    Interrupt_enable(INT_PMBUSA);

//    test_MasterTX_SlaveRX_7bitAdress_SS();
//    test_MasterTX_SlaveRX_7bitAdress_FS();
//    test_MasterTX_SlaveRX_10bitAdress_SS();
//    test_MasterTX_SlaveRX_10bitAdress_FS();

//    test_SlaveTX_MasterRX_7bitAdress_SS();
//    test_SlaveTX_MasterRX_7bitAdress_FS();
//    test_SlaveTX_MasterRX_10bitAdress_SS();
    test_SlaveTX_MasterRX_10bitAdress_FS();

   // test_SlaveTX_MasterRX_7bitAdress_SS_FPGA();

   // test_i2c_read_reg();
   // test_i2c_fpga_read_reg();

//    test_i2c_fpga_master_send();
      simple_delay(1500);
}



