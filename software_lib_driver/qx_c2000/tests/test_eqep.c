#include "common.h"

#define EQEP_DATA_NUM 32

void eqep_GpioConfig(void)
{
    EALLOW;

    GpioCtrlRegs->GPAPU.bit.GPIO6 = 0;
    GpioCtrlRegs->GPAPU.bit.GPIO7 = 0;
    GpioCtrlRegs->GPAPU.bit.GPIO8 = 0;
    GpioCtrlRegs->GPAPU.bit.GPIO9 = 0;

    GpioCtrlRegs->GPAQSEL1.bit.GPIO6 = 0;
    GpioCtrlRegs->GPAQSEL1.bit.GPIO7 = 0;
    GpioCtrlRegs->GPAQSEL1.bit.GPIO8 = 0;
    GpioCtrlRegs->GPAQSEL1.bit.GPIO9 = 0;

    GpioCtrlRegs->GPAMUX1.bit.GPIO6 = 1;
    GpioCtrlRegs->GPAMUX1.bit.GPIO7 = 1;
    GpioCtrlRegs->GPAMUX1.bit.GPIO8 = 1;
    GpioCtrlRegs->GPAMUX1.bit.GPIO9 = 1;

    GpioCtrlRegs->GPAGMUX1.bit.GPIO6 = 1;
    GpioCtrlRegs->GPAGMUX1.bit.GPIO7 = 1;
    GpioCtrlRegs->GPAGMUX1.bit.GPIO8 = 1;
    GpioCtrlRegs->GPAGMUX1.bit.GPIO9 = 1;

    EDIS;
}

void eqep_InitAsQuadratureCount(struct EQEP_REGS *reg)
{
    reg->QUPRD = 1000000;

    reg->QDECCTL.bit.QSRC     = 0; // 正交计数模式
    reg->QDECCTL.bit.XCR      = 0; // 2x分辨率  上升和下降沿计数
    reg->QEPCTL.bit.FREE_SOFT = 2;
    reg->QEPCTL.bit.PCRM      = 00; // QPOSCNT在index信号到来时复位
    reg->QEPCTL.bit.UTE       = 1;  // unit timer使能
    reg->QEPCTL.bit.QCLM      = 1;  // latch on unit time out
    reg->QPOSMAX              = 0xFFFFFFFF;
    reg->QEPCTL.bit.QPEN      = 1; // QEP使能

    reg->QCAPCTL.bit.UPPS = 3; // 1/8 for unit position at 100MHz sysclkout

    reg->QCAPCTL.bit.CCPS = 7; // 1/128 for CAP clock
    reg->QCAPCTL.bit.CEN  = 1; // QEP捕获使能
}

void eqep_InitAsDirectionCount(struct EQEP_REGS *reg)
{
    reg->QUPRD = 1000000;

    reg->QDECCTL.bit.QSRC     = 1; // 方向计数模式
    reg->QDECCTL.bit.XCR      = 0; // 2x分辨率  上升和下降沿计数
    reg->QEPCTL.bit.FREE_SOFT = 2;
    reg->QEPCTL.bit.PCRM      = 00; // QPOSCNT在index信号到来时复位
    reg->QEPCTL.bit.UTE       = 1;  // unit timer使能
    reg->QEPCTL.bit.QCLM      = 1;  // latch on unit time out
    reg->QPOSMAX              = 0xFFFFFFFF;
    reg->QEPCTL.bit.QPEN      = 1; // QEP使能

    reg->QCAPCTL.bit.UPPS = 3; // 1/8 for unit position at 100MHz sysclkout

    reg->QCAPCTL.bit.CCPS = 7; // 1/128 for CAP clock
    reg->QCAPCTL.bit.CEN  = 1; // QEP捕获使能
}

void eqep_InitAsUPCount(struct EQEP_REGS *reg)
{
    reg->QUPRD = 1000000;

    reg->QDECCTL.bit.QSRC     = 2; // 递增计数模式
    reg->QDECCTL.bit.XCR      = 0; // 2x分辨率  上升和下降沿计数
    reg->QEPCTL.bit.FREE_SOFT = 2;
    reg->QEPCTL.bit.PCRM      = 00; // QPOSCNT在index信号到来时复位
    reg->QEPCTL.bit.UTE       = 1;  // unit timer使能
    reg->QEPCTL.bit.QCLM      = 1;  // latch on unit time out
    reg->QPOSMAX              = 0xFFFFFFFF;
    reg->QEPCTL.bit.QPEN      = 1; // QEP使能

    reg->QCAPCTL.bit.UPPS = 3; // 1/8 for unit position at 100MHz sysclkout

    reg->QCAPCTL.bit.CCPS = 7; // 1/128 for CAP clock
    reg->QCAPCTL.bit.CEN  = 1; // QEP捕获使能
}

void eqep_InitAsDownCount(struct EQEP_REGS *reg)
{
    reg->QUPRD = 1000000;

    reg->QDECCTL.bit.QSRC     = 2; // 递减计数模式
    reg->QDECCTL.bit.XCR      = 0; // 2x分辨率  上升和下降沿计数
    reg->QEPCTL.bit.FREE_SOFT = 2;
    reg->QEPCTL.bit.PCRM      = 00; // QPOSCNT在index信号到来时复位
    reg->QEPCTL.bit.UTE       = 1;  // unit timer使能
    reg->QEPCTL.bit.QCLM      = 1;  // latch on unit time out
    reg->QPOSMAX              = 0xFFFFFFFF;
    reg->QEPCTL.bit.QPEN      = 1; // QEP使能

    reg->QCAPCTL.bit.UPPS = 3; // 1/8 for unit position at 100MHz sysclkout

    reg->QCAPCTL.bit.CCPS = 7; // 1/128 for CAP clock
    reg->QCAPCTL.bit.CEN  = 1; // QEP捕获使能
}

void test_eqep(void)
{
    eqep_GpioConfig();
#if 1
    eqep_InitAsQuadratureCount(EQep1Regs);
#endif

    return;

error:
    puts("error: eqep test error!");
}
