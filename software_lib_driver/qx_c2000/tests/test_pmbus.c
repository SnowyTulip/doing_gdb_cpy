#include "common.h"

#if 0
// 用于检测一般的中断函数
__interrupt void i2ca_isr(void)
{
	printf("PmbusaRegs1=%x\n", PmbusaRegs1->IC_SMBUS_RAW_INTR_STAT.all);
}

__interrupt void pmbus_isr(void)
{
    printf("PmbusaRegs21=%x\n", PmbusaRegs2->IC_INTR_STAT.all);        // 0x00
    printf("PmbusaRegs22=%x\n", PmbusaRegs2->IC_SMBUS_INTR_STAT.all);  // 0x200
}
#endif

#if 1
// 用于检测 alert 警报线的检测
__interrupt void i2ca_isr(void)
{
	printf("PmbusaRegs1=%x\n", PmbusaRegs1->IC_SMBUS_RAW_INTR_STAT.all);
	if(PmbusaRegs1->IC_SMBUS_RAW_INTR_STAT.bit.SMBUS_ALERT_DET == 1){

		PmbusaRegs1->IC_CLR_SMBUS_INTR.bit.CLR_SMBUS_ALERT_DET = 1;
		// 主机发送自己的地址到总线上(在中断中给出主机地址，从机将自己的地址发给主机)
	    PmbusaRegs1->IC_ENABLE.bit.ENABLE       = 0;
	    PmbusaRegs1->IC_TAR.bit.TAR             = 0xC;   // 0xC 定义为主机地址
	    PmbusaRegs1->IC_ENABLE.bit.ENABLE       = 1;
	    // 从机发送地址给主机
	    PmbusaRegs1->IC_DATA_CMD.bit.CMD=1;
	}
}

__interrupt void pmbus_isr(void)
{
    printf("PmbusaRegs21=%x\n", PmbusaRegs2->IC_INTR_STAT.all);        // 0x00
    printf("PmbusaRegs22=%x\n", PmbusaRegs2->IC_SMBUS_INTR_STAT.all);  // 0x200
}
#endif




void test_SMBusTimeOut()
{

    PmbusaRegs1->IC_ENABLE.bit.ENABLE                                  = 0;
    PmbusaRegs1->IC_SCL_STUCK_AT_LOW_TIMEOUT.bit.SCL_STUCK_LOW_TIMEOUT = 0xff;
    PmbusaRegs1->IC_SDA_STUCK_AT_LOW_TIMEOUT.bit.SDA_STUCK_LOW_TIMEOUT = 0xff;
    PmbusaRegs1->IC_SMBUS_CLK_LOW_SEXT.bit.SMBUS_CLK_LOW_SEXT_TIMEOUT  = 0xff;
    PmbusaRegs1->IC_SMBUS_CLK_LOW_MEXT.bit.SMBUS_CLK_LOW_MEXT_TIMEOUT  = 0xff;
    //	PmbusaRegs1->IC_ENABLE.bit.ENABLE = 1;

    PmbusaRegs1->IC_CON.all     = 0x63;
    PmbusaRegs1->IC_TAR.bit.TAR = 0x05;
    //	PmbusaRegs1->IC_TAR.bit.SMBUS_QUICK_CMD =1;    // IC_TAR[11]
    //	PmbusaRegs1->IC_TAR.bit.SPECIAL =1;    		  // IC_TAR[16]

    PmbusaRegs1->IC_ENABLE.bit.ENABLE = 1;
    //	PmbusaRegs1->IC_DATA_CMD.bit.CMD = 0;
    PmbusaRegs1->IC_DATA_CMD.bit.DATA = 0xaa;
    //	PmbusaRegs1->IC_DATA_CMD.bit.STOP = 1 ;

    //
    //	PmbusaRegs2->IC_SCL_STUCK_AT_LOW_TIMEOUT.bit.IC_SCL_STUCK_LOW_TIMEOUT = 0x11;
    //	PmbusaRegs2->IC_CON.bit.BUS_CLEAR_FEATURE_CTRL = 1;
    //	PmbusaRegs2->IC_ENABLE.bit.ENABLE = 1;

    PmbusaRegs2->IC_ENABLE.bit.ENABLE = 0;
    PmbusaRegs2->IC_CON.all           = 0x02;
    PmbusaRegs2->IC_SAR.bit.IC_SAR    = 0x05;

    //	PmbusaRegs2->IC_CON.bit.SMBUS_SLAVE_QUICK_EN = 1;
    PmbusaRegs2->IC_ENABLE.bit.ENABLE = 1;

    PmbusaRegs2->IC_DATA_CMD.bit.CMD = 1;
}

void test_quickCommond()
{

    PmbusaRegs1->IC_ENABLE.bit.ENABLE       = 0;
    PmbusaRegs1->IC_CON.all                 = 0x63;
    PmbusaRegs1->IC_TAR.bit.TAR             = 0x05;
    PmbusaRegs1->IC_TAR.bit.SMBUS_QUICK_CMD = 1; // IC_TAR[11]
    PmbusaRegs1->IC_TAR.bit.SPECIAL         = 1; // IC_TAR[16]
    PmbusaRegs1->IC_ENABLE.bit.ENABLE       = 1;
    PmbusaRegs1->IC_DATA_CMD.all            = 0x200;

    PmbusaRegs2->IC_ENABLE.bit.ENABLE            = 0;
    PmbusaRegs2->IC_CON.all                      = 0x02;
    PmbusaRegs2->IC_CON.bit.SMBUS_SLAVE_QUICK_EN = 1;

    PmbusaRegs2->IC_SAR.bit.IC_SAR    = 0x05;
    PmbusaRegs2->IC_ENABLE.bit.ENABLE = 1;

    PmbusaRegs2->IC_DATA_CMD.bit.CMD = 1;
}

void test_Suspend()
{


	PmbusaRegs1->IC_ENABLE.bit.ENABLE = 0;
    PmbusaRegs1->IC_CON.all = 0x63;
	PmbusaRegs1->IC_TAR.bit.TAR = 0x05;
	PmbusaRegs1->IC_SMBUS_INTR_MASK.all =0x000;
	PmbusaRegs1->IC_INTR_MASK.all = 0x000;
	PmbusaRegs1->IC_ENABLE.bit.ENABLE =1;

	PmbusaRegs2->IC_ENABLE.bit.ENABLE =0;
	PmbusaRegs2->IC_CON.all = 0x02;
	PmbusaRegs2->IC_SAR.bit.IC_SAR = 0x05;
	PmbusaRegs2->IC_INTR_MASK.all = 0x000;
	PmbusaRegs2->IC_SMBUS_INTR_MASK.all =0x200;
	PmbusaRegs2->IC_ENABLE.bit.ENABLE = 1;

    PmbusaRegs1->IC_DATA_CMD.all = 0xfa;

    PmbusaRegs2->IC_DATA_CMD.bit.CMD = 1;

	PmbusaRegs1->IC_DATA_CMD.all = 0xfa;

	PmbusaRegs2->IC_DATA_CMD.bit.CMD = 1;


	PmbusaRegs1->IC_DATA_CMD.bit.STOP = 1;

	simple_delay(2500);
	PmbusaRegs1->IC_ENABLE.bit.SMBUS_SUSPEND_EN = 1;
	simple_delay(1000);
}

void test_ALERT()
{
	PmbusaRegs1->IC_ENABLE.bit.ENABLE = 0;
    PmbusaRegs1->IC_CON.all = 0x63;
	PmbusaRegs1->IC_TAR.bit.TAR = 0x05;
	PmbusaRegs1->IC_SMBUS_INTR_MASK.all =0x400;
	PmbusaRegs1->IC_INTR_MASK.all = 0x00;
	PmbusaRegs1->IC_ENABLE.bit.ENABLE =1;

	PmbusaRegs2->IC_ENABLE.bit.ENABLE =0;
	PmbusaRegs2->IC_CON.all = 0x02;
	PmbusaRegs2->IC_SAR.bit.IC_SAR = 0x05;
	PmbusaRegs2->IC_INTR_MASK.all = 0x000;
	PmbusaRegs2->IC_SMBUS_INTR_MASK.all =0x200;
	PmbusaRegs2->IC_ENABLE.bit.ENABLE = 1;

	PmbusaRegs1->IC_DATA_CMD.all = 0xfa;
	PmbusaRegs2->IC_DATA_CMD.bit.CMD = 1;
	PmbusaRegs1->IC_DATA_CMD.bit.STOP = 1;
	simple_delay(3500);

	// 从机发出警报 并发送地址
	PmbusaRegs2->IC_ENABLE.bit.SMBUS_ALERT_EN = 1;
	PmbusaRegs2->IC_DATA_CMD.bit.DATA = PmbusaRegs2->IC_TAR.bit.TAR ;
	simple_delay(3500);

}






void test_pmbus()
{

    GPIO_Config(8, GPIO_8_SPIA_SIMO, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);   // pmbus_ctl
    GPIO_Config(9, GPIO_9_SPIA_CLK, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_OD, GPIO_QUAL_ASYNC);     // pmbus_alert
    GPIO_Config(10, GPIO_10_SPIA_SOMI, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_OD, GPIO_QUAL_ASYNC);  // SDA
    GPIO_Config(11, GPIO_11_SPIA_STE, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_OD, GPIO_QUAL_ASYNC);   // SCL

    GPIO_Config(12, GPIO_12_PMBUSA_CTL, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);   // pmbus_ctl
    GPIO_Config(13, GPIO_13_PMBUSA_ALERT, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_OD, GPIO_QUAL_ASYNC); // pmbus_alert
    GPIO_Config(14, GPIO_14_PMBUSA_SDA, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_OD, GPIO_QUAL_ASYNC);
    GPIO_Config(15, GPIO_15_PMBUSA_SCL, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_OD, GPIO_QUAL_ASYNC);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CB);

    Interrupt_enable(INT_I2CA);
    Interrupt_enable(INT_PMBUSA);

//   test_SMBusTimeOut();
// 	 test_quickCommond();
//   test_Suspend();
	 test_ALERT();

    puts("test_pmbus over");
}
