#include "common.h"

#define PRESCALER_VAL 0x49
uint16_t *txBufAddr = 0, *rxBufAddr = 0;
FSI_ExtFrameTriggerSrc ePWMTrigSel = FSI_EXT_TRIGSRC_EPWM1_SOCA;

uint16_t nWords        = 6;
uint16_t txBufData[17] = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
uint16_t rxBufData[16] = { 0 };

volatile uint32_t fsiTxInt1Received = 0, fsiTxInt2Received = 0;
volatile uint32_t fsiRxInt1Received = 0, fsiRxInt2Received = 0;
uint32_t txTimeOutCntr = 0x2900, rxTimeOutCntr = 0x2900;
uint32_t dataFrameCntr = 0;

uint32_t error = 0;

// User data to be sent with Data frame
uint16_t txUserData = 0x47;

// Transfer can be happen over single or double lane
FSI_DataWidth nLanes = FSI_DATA_WIDTH_1_LANE; // FSI_DATA_WIDTH_1_LANE  FSI_DATA_WIDTH_2_LANE

uint32_t rxFrameWdRefCntr = 0x1000000; //  0x1000000

uint32_t txPingTimeRefCntr = 0x100000; // 0x100000     改为 0x2900

uint32_t rxWdTimeoutRefCntr = 0x140000; // 0x140000

bool isRxFrameWdEnable = true;

__interrupt void fsitx_int1_isr(void)
{
    puts("int_fsitx");
    FSI_clearTxEvents(FSITX_BASE, FSI_TX_EVT_CLR_FRAME_DONE);
    // FSI_clearTxEvents(FSITX_BASE,FSI_TX_EVT_CLR_PING_TRIGGERED);
    FSI_clearTxEvents(FSITX_BASE, FSI_TX_EVT_CLR_BUF_UNDERRUN);
    FSI_clearTxEvents(FSITX_BASE, FSI_TX_EVT_CLR_BUF_OVERRUN);
    // FSI_clearTxEvents(FSITX_BASE,FSI_TX_EVT_CLR_FRAME_DONE);
}

__interrupt void fsirx_int1_isr(void)
{

    puts("int_fsirx");
    rxBufData[0] = HWREGH(FSIRX_BASE + FSI_O_RX_BUF_BASE(0) + 4 * 0);
    rxBufData[1] = HWREGH(FSIRX_BASE + FSI_O_RX_BUF_BASE(0) + 4 * 1);
    rxBufData[2] = HWREGH(FSIRX_BASE + FSI_O_RX_BUF_BASE(0) + 4 * 2);
    rxBufData[3] = HWREGH(FSIRX_BASE + FSI_O_RX_BUF_BASE(0) + 4 * 3);
    rxBufData[4] = HWREGH(FSIRX_BASE + FSI_O_RX_BUF_BASE(0) + 4 * 4);
    rxBufData[5] = HWREGH(FSIRX_BASE + FSI_O_RX_BUF_BASE(0) + 4 * 5);

    printf("BUFF=%d\n", rxBufData[0]);
    printf("BUFF=%d\n", rxBufData[1]);
    printf("BUFF=%d\n", rxBufData[2]);
    printf("BUFF=%d\n", rxBufData[3]);
    printf("BUFF=%d\n", rxBufData[4]);
    printf("BUFF=%d\n", rxBufData[5]);

    // FSI_clearRxEvents(FSIRX_BASE,FSI_RX_EVT_STS_PING_WD_TO);
    // FSI_clearRxEvents(FSIRX_BASE,FSI_RX_EVT_PING_WD_TIMEOUT | FSI_RX_EVT_FRAME_WD_TIMEOUT |
    // 	            		FSI_RX_EVT_CRC_ERR |FSI_RX_EVT_TYPE_ERR|FSI_RX_EVT_EOF_ERR |
    // 						FSI_RX_EVT_OVERRUN |FSI_RX_EVT_FRAME_DONE |FSI_RX_EVT_ERR_FRAME|
    // 	            		FSI_RX_EVT_PING_FRAME|FSI_RX_EVT_FRAME_OVERRUN|FSI_RX_EVT_DATA_FRAME);//|FSI_RX_EVT_UNDERRUN
    // FSI_clearRxEvents(FSIRX_BASE,FSI_RX_EVT_UNDERRUN);
}

__interrupt void fsitx_int2_isr(void)
{
    puts("fsitx_int2=========>");
    FSI_clearTxEvents(FSITX_BASE, FSI_TX_EVT_CLR_PING_TRIGGERED);
    FSI_clearTxEvents(FSITX_BASE, FSI_TX_EVT_CLR_FRAME_DONE);
    FSI_clearTxEvents(FSITX_BASE, FSI_TX_EVT_CLR_BUF_UNDERRUN);
    FSI_clearTxEvents(FSITX_BASE, FSI_TX_EVT_CLR_BUF_OVERRUN);
}

__interrupt void fsirx_int2_isr(void)
{
    puts("fsirx_int2");
    // FSI_clearRxEvents(FSIRX_BASE,FSI_RX_EVT_STS_PING_WD_TO);
    // FSI_clearRxEvents(FSIRX_BASE,FSI_RX_EVT_PING_WD_TIMEOUT | FSI_RX_EVT_FRAME_WD_TIMEOUT |
    // 	            		FSI_RX_EVT_CRC_ERR |FSI_RX_EVT_TYPE_ERR|FSI_RX_EVT_EOF_ERR |
    // 						FSI_RX_EVT_OVERRUN |FSI_RX_EVT_FRAME_DONE |FSI_RX_EVT_ERR_FRAME|
    // 	            		FSI_RX_EVT_PING_FRAME|FSI_RX_EVT_FRAME_OVERRUN|FSI_RX_EVT_DATA_FRAME);//|FSI_RX_EVT_UNDERRUN
    // FSI_clearRxEvents(FSIRX_BASE,FSI_RX_EVT_UNDERRUN);
}

void prepareTxBufData(void)
{
    uint16_t i;

    for (i = 0; i < nWords; i++)
    {
        txBufData[i] = txBufData[i] + 1;
    }
}

void pwm_gen(u8 ch, u8 count_mode, u16 tbprd, u16 cmp, u16 tbphs, u8 int_type, u32 p_flag)
{
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);
    /* TB */
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    EPWM_setTimeBaseCounterMode(epwm_base, count_mode); /* 计数模式  */
    //    EPWM_enablePhaseShiftLoad(uint32_t base)			/* 不从TBPHS加载TBCTR */
    EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_SHADOW_LOAD); /* 启用影子模式读写TBPRD */
    //    EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_DIRECT_LOAD);     /* 启用直接模式读写TBPRD*/
    epwm->TBCTL.bit.SYNCOSEL = 0;      		/* 禁用EPWMxSYNCO信号，该信号拉高后会使CTR跳转为TBPHS 注:该操作会导致通道2开启时通道1的gpio输出高阻, 需要确定是否正确 */ //00应该是启用？
    /* SWFSYNC，软件强制同步脉冲，应该是动态的，先不管 */
    epwm->TBCTL.bit.HSPCLKDIV
        = 1; /* TBCLK = SYSTEM_OUT_CLK/(2 * HSPCLKDIV * CLKDIV^2)高速基准时钟，为0时只由CLKDIV决定 */
    epwm->TBCTL.bit.CLKDIV = 1; /* TBCLK = SYSTEM_OUT_CLK/(2^CLKDIV)，基准时钟, 最终TBCLK = SYSTEM_OUT_CLK/2 */
                                /* PHSDIR，相位方向位，仅在递增计数时使用*/
                                /* FREE_SOFT，仿真模式自由运行*/

    epwm->TBPHS.bit.TBPHS = tbphs; /* 相位偏移 */
    epwm->TBPRD           = tbprd; /* 时基周期设置 */
    epwm->TBCTR           = 0;     /* 清零时基计数寄存器 */

    /* CC */
    epwm->CMPCTL.bit.SHDWAMODE = 0;
    epwm->CMPCTL.bit.SHDWBMODE = 0;
    //    epwm->CMPCTL.bit.SHDWAMODE = 1;
    //    epwm->CMPCTL.bit.SHDWBMODE = 1;
    epwm->CMPCTL.bit.LOADAMODE = 0;
    epwm->CMPCTL.bit.LOADBMODE = 0;
    epwm->CMPA.bit.CMPA        = cmp;

    /* AQ */
    // 对应赋值1则触发输出0，对应赋值1则触发输出1
    epwm->AQCTLA.bit.CAU = 2; /* 当CTR=CMPA且Up增计数时，EPWM1A输出高电平 */
    epwm->AQCTLA.bit.CAD = 1; /* 当CTR=CMPA且Down减计数时，EPWM1A输出低电平 */
    epwm->AQCTLB.bit.CAU = 2; /* 当CTR=CMPA且Up增计数时，EPWM1B输出高电平 */
    epwm->AQCTLB.bit.CAD = 1; /* 当CTR=CMPA且Down减计数时，EPWM1B输出低电平 */

    /* DB */
    epwm->DBCTL.bit.OUT_MODE = 0; /* 死区完全旁路 */
    /* PC */
    //    EPWM_enableChopper(epwm_base);	/* 斩波器完全旁路 */

    /* 是否打开中断触发 */
    if (int_type)
    {
        Interrupt_enable(INT_EPWM1);
    }
    else
    {
        Interrupt_disable(INT_EPWM1);
    }
    if (p_flag)
        printf("epwm test -> ch:%d, count_mode:%d, tbprd:%d, cmp:%d, tbphs:%d, int_type:%d\n", ch, count_mode, tbprd,
            cmp, tbphs, int_type);
}
void gen_et(u8 ch, u16 cmp)
{
    uint32_t epwm_base              = EPWM1_BASE + ch * 0x200;
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch * 0x200);

    epwm->CMPB.bit.CMPB = cmp; // 设置cmpb

    epwm->ETSEL.bit.SOCASEL = 0b111; // 使能ctr下降时等于cmpb or cmpd事件，试了下cmpd为0时好像不影响
    epwm->ETSEL.bit.SOCBSEL = 0b111; // 使能ctr下降时等于cmpb or cmpd事件

    epwm->ETSEL.bit.SOCAEN = 1; // 使能SOCA输出
    epwm->ETSEL.bit.SOCBEN = 1; // 使能SOCA输出

    epwm->ETPS.bit.SOCAPRD = 1; // 每发生3次事件产生一个SOCA脉冲
    epwm->ETPS.bit.SOCBPRD = 1;

    SysCtl_enableExtADCSOCSource(SYSCTL_ADCSOCOUTSELECT_PWM1SOCAEN); // 使能设置ADC src为 epwm_ch1
    SysCtl_enableExtADCSOCSource(SYSCTL_ADCSOCOUTSELECT_PWM1SOCBEN); // 使能设置ADC src为 epwm_ch1
}

void test_software_trigger()
{ // 测试软件触发传输 以及中断测试
    // Initialize Tx/Rx, reset sequence, clear events
    //-->begin FSI_init
    //  TODO- Add logic to calculate PRESCALER_VAL based on user input FSI CLK

    // Loopback open
    FSI_enableRxInternalLoopback(FSIRX_BASE);

    FSI_performTxInitialization(FSITX_BASE, PRESCALER_VAL);
    FSI_performRxInitialization(FSIRX_BASE);

    // Flush Sequence before and after releasing Rx core reset, ensures flushing of Rx data/clock lines and prepares it
    // for reception
    FSI_resetRxModule(FSIRX_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_executeTxFlushSequence(FSITX_BASE, PRESCALER_VAL);
    delay_us(1);
    FSI_clearRxModuleReset(FSIRX_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_executeTxFlushSequence(FSITX_BASE, PRESCALER_VAL);

    // Assigning base addresses of Tx/Rx data buffer to globals
    txBufAddr = (uint16_t *)FSI_getTxBufferAddress(FSITX_BASE);
    rxBufAddr = (uint16_t *)FSI_getRxBufferAddress(FSIRX_BASE);

    // Enable FSI Tx/Rx interrupts

    FsiRxaRegs->RX_MASTER_CTRL.bit.INT_LOOPBACK = 1;

    // Performing a reset on PING WD counter before its usage is recommended
    // Done on both FSI Tx/Rx sides
    FSI_resetTxModule(FSITX_BASE, FSI_TX_PING_TIMEOUT_CNT_RESET);
    delay_us(1);
    FSI_clearTxModuleReset(FSITX_BASE, FSI_TX_PING_TIMEOUT_CNT_RESET);

    FSI_resetRxModule(FSIRX_BASE, FSI_RX_PING_WD_CNT_RESET);
    delay_us(1);
    FSI_clearRxModuleReset(FSIRX_BASE, FSI_RX_PING_WD_CNT_RESET);

    // Enable Rx Ping Watchdog timeout event on INT2 line

    // Now enable PING WD timer in both FSI Tx/Rx sides
    // Keeping reference counter for Rx little wide to ensure its not too sharp
    // to generate a WD timeout

    FSI_enableTxPingTimer(FSITX_BASE, txPingTimeRefCntr);
    FSI_enableRxPingWatchdog(FSIRX_BASE, rxWdTimeoutRefCntr);

    // Setting for requested nWords and nLanes with transfers

    // Sets frame type for transmission
    FSI_setTxSoftwareFrameSize(FSITX_BASE, nWords);
    FSI_setRxSoftwareFrameSize(FSIRX_BASE, nWords);

    FSI_setTxDataWidth(FSITX_BASE, nLanes);
    FSI_setRxDataWidth(FSIRX_BASE, nLanes);

    // Enable normal data transfer events to be sent over INT1 line

    // FSI_enableTxInterrupt(FSITX_BASE, FSI_INT1, FSI_TX_EVT_FRAME_DONE);  //FSI_TX_EVT_FRAME_DONE =  0x0001U
    // FSI_enableTxInterrupt(FSITX_BASE, FSI_INT2, FSI_TX_EVT_PING_TIMEOUT);
    // FSI_enableTxInterrupt(FSITX_BASE, FSI_INT2, FSI_TX_EVT_BUF_UNDERRUN);
    // FSI_enableTxInterrupt(FSITX_BASE, FSI_INT2, FSI_TX_EVT_BUF_OVERRUN);
    // FSI_enableTxInterrupt(FSITX_BASE, FSI_INT2, FSI_TX_EVT_FRAME_DONE);

    // FsiRxaRegs ->RX_INT1_CTRL.bit.INT1_EN_PING_WD_TO=1;
    // FsiRxaRegs ->RX_INT1_CTRL.bit.INT1_EN_FRAME_WD_TO=1;

    // FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_PING_WD_TIMEOUT);
    //
    // FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_PING_WD_TIMEOUT);
    // FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_CRC_ERR  |
    //		  	  	  	  	  	  	  	  	  	  FSI_RX_EVT_TYPE_ERR |
    //												  FSI_RX_EVT_EOF_ERR);
    //
    // FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_FRAME_WD_TIMEOUT);
    //
    // FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_OVERRUN);
    // FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_FRAME_DONE);
    // FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_UNDERRUN);
    // FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_ERR_FRAME);
    // FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_PING_FRAME);
    // FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_FRAME_OVERRUN);
    // FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_DATA_FRAME);

    FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_DATA_FRAME);
    FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_PING_WD_TIMEOUT);
    FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_CRC_ERR | FSI_RX_EVT_TYPE_ERR | FSI_RX_EVT_EOF_ERR);

    FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_FRAME_WD_TIMEOUT);

    FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_OVERRUN);
    FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_FRAME_DONE);
    FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_UNDERRUN);
    FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_ERR_FRAME);
    FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_PING_FRAME);
    FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_FRAME_OVERRUN);

    FSI_configRxDelayLine(FSIRX_BASE, FSI_RX_DELAY_D0, 15);
    FSI_configRxDelayLine(FSIRX_BASE, FSI_RX_DELAY_CLK, 31);
    //	    FSI_configRxDelayLine(FSIRX_BASE,FSI_RX_DELAY_D0,31);

    FSI_setTxUserDefinedData(FSITX_BASE, txUserData);

    FSI_setTxFrameTag(FSITX_BASE, FSI_FRAME_TAG7);

    // Sets frame type for transmission
    FSI_setTxFrameType(FSITX_BASE, FSI_FRAME_TYPE_NWORD_DATA);

    if (isRxFrameWdEnable)
    {
        // Performing a reset on frame WD before its usage is recommended
        FSI_resetRxModule(FSIRX_BASE, FSI_RX_FRAME_WD_CNT_RESET);
        delay_us(1);
        FSI_clearRxModuleReset(FSIRX_BASE, FSI_RX_FRAME_WD_CNT_RESET);
        FSI_enableRxFrameWatchdog(FSIRX_BASE, rxFrameWdRefCntr);

        // FSI_clearRxEvents(FSIRX_BASE,FSI_RX_EVT_DATA_FRAME);
    }

    // Now, start transmitting data frames
    //
    while (1)
    {

        // Write data into Tx buffer and set other Frame specific fields
        // prepareTxBufData();
        FSI_writeTxBuffer(FSITX_BASE, txBufData, 0x06, 0U);

        // Start Transfer
        FSI_startTxTransmit(FSITX_BASE);
        //	            FSI_clearRxEvents(FSIRX_BASE,FSI_RX_EVT_PING_WD_TIMEOUT | FSI_RX_EVT_FRAME_WD_TIMEOUT |
        //	            		FSI_RX_EVT_CRC_ERR |FSI_RX_EVT_TYPE_ERR|FSI_RX_EVT_EOF_ERR |
        //						FSI_RX_EVT_OVERRUN |FSI_RX_EVT_FRAME_DONE |FSI_RX_EVT_ERR_FRAME|
        //	            		FSI_RX_EVT_PING_FRAME|FSI_RX_EVT_FRAME_OVERRUN|FSI_RX_EVT_DATA_FRAME);//|FSI_RX_EVT_UNDERRUN
        //

        // array[j] = HWREGH(base + FSI_O_RX_BUF_BASE(tempBufOffset) + 4*i);
        //				rxBufData[0]=HWREGH(FSIRX_BASE + FSI_O_RX_BUF_BASE(0) + 4*0);
        //				rxBufData[1]=HWREGH(FSIRX_BASE + FSI_O_RX_BUF_BASE(0) + 4*1);
        //				rxBufData[2]=HWREGH(FSIRX_BASE + FSI_O_RX_BUF_BASE(0) + 4*2);
        //				rxBufData[3]=HWREGH(FSIRX_BASE + FSI_O_RX_BUF_BASE(0) + 4*3);
        //				rxBufData[4]=HWREGH(FSIRX_BASE + FSI_O_RX_BUF_BASE(0) + 4*4);
        //				rxBufData[5]=HWREGH(FSIRX_BASE + FSI_O_RX_BUF_BASE(0) + 4*5);
        //
        //
        //				printf("BUFF=%d\n",rxBufData[0]);
        //				printf("BUFF=%d\n",rxBufData[1]);
        //				printf("BUFF=%d\n",rxBufData[2]);
        //				printf("BUFF=%d\n",rxBufData[3]);
        //				printf("BUFF=%d\n",rxBufData[4]);
        //				printf("BUFF=%d\n",rxBufData[5]);

        // Wait till frame done event is received by both Tx/Rx modules
        while ((fsiTxInt1Received != 1U) && (txTimeOutCntr != 0U))
        {
            txTimeOutCntr--;
        }

        while ((fsiRxInt1Received != 1U) && (rxTimeOutCntr != 0U))
        {
            rxTimeOutCntr--;
        }

        if ((txTimeOutCntr == 0) || (rxTimeOutCntr == 0))
        {
            //
            // Timeout for one of expected Tx/Rx evetns, so break execution here
            //
            break;
        }

        else
        {
            // Re-initialize flags and buffer pointer before next transmission
            fsiTxInt1Received = 0U;
            fsiRxInt1Received = 0U;
            txTimeOutCntr     = 0x100000U;
            rxTimeOutCntr     = 0x100000U;
            FSI_setTxBufferPtr(FSITX_BASE, 0U);
            FSI_setRxBufferPtr(FSIRX_BASE, 0U);
        }
    }
}

void test_epwm_trigger()
{ // 测试 epwm 触发传输
    // Loopback
    FSI_enableRxInternalLoopback(FSIRX_BASE);

    FSI_performTxInitialization(FSITX_BASE, PRESCALER_VAL);
    FSI_performRxInitialization(FSIRX_BASE);

    // FSI_setTxSoftwareFrameSize(FSITX_BASE, nWords);
    // Flush Sequence before and after releasing Rx core reset, ensures flushing of Rx data/clock lines and prepares it
    // for reception
    FSI_resetRxModule(FSIRX_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_executeTxFlushSequence(FSITX_BASE, PRESCALER_VAL);
    delay_us(1);
    FSI_clearRxModuleReset(FSIRX_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_executeTxFlushSequence(FSITX_BASE, PRESCALER_VAL);

    // Assigning base addresses of Tx/Rx data buffer to globals
    txBufAddr = (uint16_t *)FSI_getTxBufferAddress(FSITX_BASE);
    rxBufAddr = (uint16_t *)FSI_getRxBufferAddress(FSIRX_BASE);

    // reset Ping Timer
    FSI_resetTxModule(FSITX_BASE, FSI_TX_PING_TIMEOUT_CNT_RESET);
    delay_us(1);
    FSI_clearTxModuleReset(FSITX_BASE, FSI_TX_PING_TIMEOUT_CNT_RESET);

    // Frame Watchdog Counter Reset
    FSI_resetRxModule(FSIRX_BASE, FSI_RX_PING_WD_CNT_RESET);
    delay_us(1);
    FSI_clearRxModuleReset(FSIRX_BASE, FSI_RX_PING_WD_CNT_RESET);

    // Now enable PING WD timer in both FSI Tx/Rx sides

    // Enable Rx Ping Watchdog timeout event on INT1 line
    //		FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_PING_WD_TIMEOUT);
    FSI_enableTxPingTimer(FSITX_BASE, txPingTimeRefCntr);
    FSI_enableRxPingWatchdog(FSIRX_BASE, rxWdTimeoutRefCntr);

    // Setting for requested nWords and nLanes with transfers
    FSI_setTxSoftwareFrameSize(FSITX_BASE, nWords);
    FSI_setRxSoftwareFrameSize(FSIRX_BASE, nWords);
    FSI_setTxFrameType(FSITX_BASE, FSI_FRAME_TYPE_NWORD_DATA);

    FSI_setTxDataWidth(FSITX_BASE, nLanes);
    FSI_setRxDataWidth(FSIRX_BASE, nLanes);

    FSI_enableTxInterrupt(FSITX_BASE, FSI_INT1, FSI_TX_EVT_FRAME_DONE);
    FSI_enableTxInterrupt(FSITX_BASE, FSI_INT1, FSI_TX_EVT_CLR_BUF_UNDERRUN);
    //  FSI_enableTxInterrupt(FSITX_BASE, FSI_INT1, FSI_TX_EVT_CLR_PING_TRIGGERED);
    //  FSI_enableTxInterrupt(FSITX_BASE, FSI_INT1, FSI_TX_EVT_CLR_BUF_OVERRUN);
    FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_DATA_FRAME);
    FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR | FSI_RX_EVT_EOF_ERR | FSI_RX_EVT_TYPE_ERR);

    if (isRxFrameWdEnable)
    {
        // Performing a reset on frame WD before its usage is recommended
        FSI_resetRxModule(FSIRX_BASE, FSI_RX_FRAME_WD_CNT_RESET);
        delay_us(1);
        FSI_clearRxModuleReset(FSIRX_BASE, FSI_RX_FRAME_WD_CNT_RESET);
        FSI_enableRxFrameWatchdog(FSIRX_BASE, rxFrameWdRefCntr);

        // FSI_clearRxEvents(FSIRX_BASE,FSI_RX_EVT_DATA_FRAME);
    }

    FSI_setTxFrameTag(FSITX_BASE, FSI_FRAME_TAG15);
    FSI_setTxStartMode(FSITX_BASE, FSI_TX_START_EXT_TRIG);
    FSI_setTxExtFrameTrigger(FSITX_BASE, ePWMTrigSel);

    while (1)
    {
        // prepareTxBufData();
        FSI_writeTxBuffer(FSITX_BASE, txBufData, nWords, 0U);

        FSI_setTxUserDefinedData(FSITX_BASE, (txUserData & 0xFF));

        //
        // Start ePWM to trigger FSI data frames transfer upon SOC event
        //
        int i = 0; // epwm1
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
        CpuSysRegs->PCLKCR0.bit.TBCLKSYNC = 0;
        pwm_gen(i, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
        gen_et(i, 1);
        CpuSysRegs->PCLKCR0.bit.TBCLKSYNC = 1;

        //
        // Wait till frame done event is received by both Tx/Rx modules
        //
        while (fsiTxInt1Received != 1U)
            ;
        fsiTxInt1Received = 0;
        while (fsiRxInt1Received != 1U)
            ;
        fsiRxInt1Received = 0;

        //
        // Disable peripheral clk for ePWM and Sync
        //
        SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
        SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
    }
}

void test_delay_trigger()
{ // 测试延时delay模块
    // 打开 ECAP 中断

    // Initialize Tx/Rx, reset sequence, clear events
    //  TODO- Add logic to calculate PRESCALER_VAL based on user input FSI CLK

    FSI_performTxInitialization(FSITX_BASE, PRESCALER_VAL);
    FSI_performRxInitialization(FSIRX_BASE);

    //	 FSI_setTxSoftwareFrameSize(FSITX_BASE, nWords);
    // Flush Sequence before and after releasing Rx core reset, ensures flushing of Rx data/clock lines and prepares it
    // for reception

    FSI_resetRxModule(FSIRX_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_executeTxFlushSequence(FSITX_BASE, PRESCALER_VAL);
    delay_us(1);
    FSI_clearRxModuleReset(FSIRX_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_executeTxFlushSequence(FSITX_BASE, PRESCALER_VAL);

    // Assigning base addresses of Tx/Rx data buffer to globals
    txBufAddr = (uint16_t *)FSI_getTxBufferAddress(FSITX_BASE);
    rxBufAddr = (uint16_t *)FSI_getRxBufferAddress(FSIRX_BASE);
    //<--end FSI_init

    // Performing a reset on PING WD counter before its usage is recommended
    // Done on both FSI Tx/Rx sides
    FSI_resetTxModule(FSITX_BASE, FSI_TX_PING_TIMEOUT_CNT_RESET);
    delay_us(1);
    FSI_clearTxModuleReset(FSITX_BASE, FSI_TX_PING_TIMEOUT_CNT_RESET);

    FSI_resetRxModule(FSIRX_BASE, FSI_RX_PING_WD_CNT_RESET);
    delay_us(1);
    FSI_clearRxModuleReset(FSIRX_BASE, FSI_RX_PING_WD_CNT_RESET);

    // Enable Rx Ping Watchdog timeout event on INT2 line

    // Now enable PING WD timer in both FSI Tx/Rx sides
    // Keeping reference counter for Rx little wide to ensure its not too sharp
    // to generate a WD timeout
    FSI_enableTxPingTimer(FSITX_BASE, txPingTimeRefCntr);

    FSI_enableRxPingWatchdog(FSIRX_BASE, rxWdTimeoutRefCntr);

    // Setting for requested nWords and nLanes with transfers

    // Sets frame type for transmission
    FSI_setTxSoftwareFrameSize(FSITX_BASE, nWords);
    FSI_setRxSoftwareFrameSize(FSIRX_BASE, nWords);

    FSI_setTxDataWidth(FSITX_BASE, nLanes);
    FSI_setRxDataWidth(FSIRX_BASE, nLanes);

    // Enable normal data transfer events to be sent over INT1 line

    FSI_enableTxInterrupt(FSITX_BASE, FSI_INT1, FSI_TX_EVT_FRAME_DONE);
    //    FSI_enableTxInterrupt(FSITX_BASE, FSI_INT1, FSI_TX_EVT_CLR_BUF_UNDERRUN);

    // FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_PING_WD_TIMEOUT);
    // FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, 0x02);
    //	    FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_INT1_CTRL_INT1_EN_CRC_ERR);
    //	    FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_INT1_CTRL_INT1_EN_EOF_ERR);

    //        FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_DATA_FRAME);  //FSI_RX_EVT_DATA_FRAME = (0x0800U)

    // FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_UNDERRUN);

    //        FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_OVERRUN);
    //
    //        FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_ERR_FRAME);
    //        FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_FRAME_DONE);

    //        FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_PING_WD_TIMEOUT);
    //       FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_FRAME_WD_TIMEOUT);

    //        FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_ERR_FRAME);
    //	    FSI_enableRxInterrupt(FSIRX_BASE, FSI_INT1, FSI_RX_EVT_CRC_ERR  |
    //	                                                 FSI_RX_EVT_EOF_ERR  |
    //	                                                 FSI_RX_EVT_TYPE_ERR );

    FSI_setTxUserDefinedData(FSITX_BASE, txUserData);
    FSI_setTxFrameTag(FSITX_BASE, FSI_FRAME_TAG7);

    // Sets frame type for transmission
    FSI_setTxFrameType(FSITX_BASE, FSI_FRAME_TYPE_NWORD_DATA);

    if (isRxFrameWdEnable)
    {
        //
        // Performing a reset on frame WD before its usage is recommended
        //
        FSI_resetRxModule(FSIRX_BASE, FSI_RX_FRAME_WD_CNT_RESET);
        delay_us(1);
        FSI_clearRxModuleReset(FSIRX_BASE, FSI_RX_FRAME_WD_CNT_RESET);
        FSI_enableRxFrameWatchdog(FSIRX_BASE, rxFrameWdRefCntr);
    }

    // Now, start transmitting data frames
    while (1)
    {

        //
        // Write data into Tx buffer and set other Frame specific fields
        //
        // prepareTxBufData();
        puts("1 ");
        FSI_writeTxBuffer(FSITX_BASE, txBufData, nWords, 0U);
        puts("2 ");
        // Start Transfer

        FSI_startTxTransmit(FSITX_BASE);

        FSI_clearRxEvents(FSIRX_BASE, FSI_RX_EVT_PING_WD_TIMEOUT | FSI_RX_EVT_FRAME_WD_TIMEOUT | FSI_RX_EVT_CRC_ERR
                                          | FSI_RX_EVT_TYPE_ERR | FSI_RX_EVT_EOF_ERR | FSI_RX_EVT_OVERRUN
                                          | FSI_RX_EVT_FRAME_DONE | FSI_RX_EVT_ERR_FRAME | FSI_RX_EVT_PING_FRAME
                                          | FSI_RX_EVT_FRAME_OVERRUN | FSI_RX_EVT_DATA_FRAME); //|FSI_RX_EVT_UNDERRUN

        // Wait till frame done event is received by both Tx/Rx modules
        //
        while ((fsiTxInt1Received != 1U) && (txTimeOutCntr != 0U))
        {
            txTimeOutCntr--;
        }

        while ((fsiRxInt1Received != 1U) && (rxTimeOutCntr != 0U))
        {
            rxTimeOutCntr--;
        }

        if ((txTimeOutCntr == 0) || (rxTimeOutCntr == 0))
        {
            //
            // Timeout for one of expected Tx/Rx evetns, so break execution here
            //
            break;
        }

        else
        {
            //
            // Re-initialize flags and buffer pointer before next transmission
            //
            fsiTxInt1Received = 0U;
            fsiRxInt1Received = 0U;
            txTimeOutCntr     = 0x100000U;
            rxTimeOutCntr     = 0x100000U;
            FSI_setTxBufferPtr(FSITX_BASE, 0U);
            FSI_setRxBufferPtr(FSIRX_BASE, 0U);
        }
    }
}

void test_fsi()
{
    puts("FSI test start-->2");
    FSI_FrameTag txDataFrameTag, txPingFrameTag;
    // Tx Ping timer and Rx Watchdog reference counter values

    // GPIO 复用     FSITXA_D1   FSITXA_D0    FSITXA_CLK
    GPIO_Config(5, GPIO_5_FSITXA_D1, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);  // FSITXA_D1
    GPIO_Config(6, GPIO_6_FSITXA_D0, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);  // FSITXA_D0
    GPIO_Config(7, GPIO_7_FSITXA_CLK, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC); // FSITXA_CLK

    // GPIO 复用     FSIRXA_D1   FSIRXA_D0    FSIRXA_CLK
    GPIO_Config(11, GPIO_11_FSIRXA_D1, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);  // FSIRXA_D1
    GPIO_Config(12, GPIO_12_FSIRXA_D0, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);  // FSIRXA_D0
    GPIO_Config(13, GPIO_13_FSIRXA_CLK, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC); // FSIRXA_CLK

    // 使能系统中断
    Interrupt_enable(INT_FSITX_INT1);
    Interrupt_enable(INT_FSIRX_INT1);
    Interrupt_enable(INT_FSITX_INT2);
    Interrupt_enable(INT_FSIRX_INT2);
    // test model
    test_software_trigger();
    //	test_epwm_trigger();
    //	test_delay_trigger();

    puts("over!!!");
}
