#include "common.h"

#define DATA_NUM 8

static u8 send_data0[DATA_NUM] = { 0 };
static u8 send_data1[DATA_NUM] = { 0 };
static u8 recv_data0[DATA_NUM] = { 0 };
static u8 recv_data1[DATA_NUM] = { 0 };

__interrupt void spia_m_isr(void)
{
    u32 status;

    puts("spia isr");

    status = SPI_getInterruptStatus((u32)SPI1);

    if (status & SPI_INT_STATUS_TXEI)
    {
    	puts("TX fifo empty");
        SPI_disableInterrupt(SPI1, SPI_INT_MASK_TXE);
        SPI_sendDataWithInterrupt(SPI1);
    }

    if (status & SPI_INT_STATUS_TXOI)

    	puts("TX fifo overflow");

    if (status & SPI_INT_STATUS_RXUI)
    	puts("RX fifo underflow");

    if (status & SPI_INT_STATUS_RXOI)
    	puts("RX fifo overflow");

    if (status & SPI_INT_STATUS_RXFI)
    {
    	puts("RX fifo full");
        SPI_disableInterrupt(SPI1, SPI_INT_MASK_RXF);
        SPI_recvDataWithInterrupt(SPI1);
        SPI_enableInterrupt(SPI1, SPI_INT_MASK_RXF);
    }

    if (status & SPI_INT_STATUS_MSTI)
    	puts("Master error");
}

__interrupt void spib_s_isr(void)
{
	u32 status;

	puts("spib isr");

	status = SPI_getInterruptStatus((u32)SPI2);

	if (status & SPI_INT_STATUS_TXEI)
	{
		puts("TX fifo empty");
	    SPI_disableInterrupt(SPI2, SPI_INT_MASK_TXE);
	    SPI_sendDataWithInterrupt(SPI2);
	}

	if (status & SPI_INT_STATUS_TXOI)
	    puts("TX fifo overflow");

	if (status & SPI_INT_STATUS_RXUI)
	    puts("RX fifo underflow");

	if (status & SPI_INT_STATUS_RXOI)
	    puts("RX fifo overflow");

	if (status & SPI_INT_STATUS_RXFI)
	{
	    puts("RX fifo full");
	    SPI_disableInterrupt(SPI2, SPI_INT_MASK_RXF);
	    SPI_recvDataWithInterrupt(SPI2);
	    SPI_enableInterrupt(SPI2, SPI_INT_MASK_RXF);
	}

	if (status & SPI_INT_STATUS_MSTI)
	    puts("Master error");
}

int spi_testcase_TR_no_interrupt(void)
{
    SPI_Config sconfig;

    SPI_setHostMode(SPI1_MASTER_MODE);
    SPI_setHostMode(SPI2_SLAVE_MODE);
    SPI_moduleDisable(SPI1);
    SPI_moduleDisable(SPI2);

    sconfig.data_width  = SPI_DATA_BITS_8;
    sconfig.sample_mode = SPI_SAMPLE_POS_0;
    sconfig.trans_mode  = SPI_TRANS_MODE_TR;
    sconfig.baudrate = 1000000;
    sconfig.rx_ftl  = 0;
    sconfig.tx_ftl  = 0;

    SPI_masterInit(SPI1, &sconfig);
    SPI_moduleEnable(SPI1);

    SPI_slaveInit(SPI2, &sconfig);
    SPI_moduleEnable(SPI2);

    for (int i = 0; i < DATA_NUM; i++) {
    	send_data0[i] = 0x5A + i;
        send_data1[i] = 0x6A + i;
    }

    SPI_sendDataWithPolling(SPI2, (char *)send_data1, DATA_NUM);
    SPI_sendDataWithPolling(SPI1, (char *)send_data0, DATA_NUM);

    SPI_recvDataWithPolling(SPI2, (char *)recv_data0);
    SPI_recvDataWithPolling(SPI1, (char *)recv_data1);

    for (int i = 0; i < DATA_NUM; i++) {
        if (recv_data0[i] != send_data0[i]) {
            printf("recv error(send_data0[%d] = 0x%x, recv_data0[%d] = 0x%x\n", i, recv_data0[i], i, send_data0[i]);
            return -1;
        }

        if (recv_data1[i] != send_data1[i]) {
            printf("recv error(send_data1[%d] = 0x%x, recv_data1[%d] = 0x%x\n", i, recv_data1[i], i, send_data1[i]);
            return -1;
        }
    }

    return 0;
}

int spi_testcase_TR_with_interrupt(void)
{
    SPI_Config sconfig;

    for (int i = 0; i < DATA_NUM; i++) {
        send_data0[i] = 0x5A + i;
    }

    spi_send.length = DATA_NUM;
    spi_send.buf = (char *) send_data0;
    spi_recv.length = 0;
    spi_recv.buf = (char *) recv_data0;

    sconfig.data_width  = SPI_DATA_BITS_8;
    sconfig.sample_mode = SPI_SAMPLE_POS_0;
    sconfig.trans_mode  = SPI_TRANS_MODE_TR;
    sconfig.baudrate = 1000000;
    sconfig.rx_ftl  = 0;
    sconfig.tx_ftl  = 0;

    SPI_setHostMode(SPI1_MASTER_MODE);
    SPI_setHostMode(SPI2_SLAVE_MODE);
    SPI_moduleDisable(SPI1);
    SPI_moduleDisable(SPI2);

    SPI_masterInit(SPI1, &sconfig);
    SPI_moduleEnable(SPI1);

    SPI_slaveInit(SPI2, &sconfig);
    SPI_moduleEnable(SPI2);

    SPI_disableInterrupt(SPI1, SPI_INT_MASK_ALL);
    SPI_disableInterrupt(SPI2, SPI_INT_MASK_ALL);
    SPI_enableInterrupt(SPI2, SPI_INT_MASK_RXF);
    SPI_enableInterrupt(SPI1, SPI_INT_MASK_TXE);

    Interrupt_enable(INT_SPIA_M);
    Interrupt_enable(INT_SPIB_S);

    while(spi_recv.length < 8)
    	;

    for (int i = 0; i < DATA_NUM; i++) {
        if (recv_data0[i] != send_data0[i]) {
            printf("recv error(send_data0[%d] = 0x%x, recv_data0[%d] = 0x%x\n", i, send_data0[i], i, recv_data0[i]);
            return -1;
        }
    }

    return 0;
}

int spi_testcase_TR_with_DMA(void)
{
	int i;
	SPI_Config sconfig;
	DMAXChanConfig dconfig;

	sconfig.data_width = SPI_DATA_BITS_8;
	sconfig.sample_mode = SPI_SAMPLE_POS_0;
	sconfig.trans_mode  = SPI_TRANS_MODE_TR;
	sconfig.baudrate = 1000000;
	sconfig.rx_ftl  = 0;
	sconfig.tx_ftl  = 0;

	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIB);
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);

	SPI_setHostMode(SPI1_MASTER_MODE);
	SPI_setHostMode(SPI2_SLAVE_MODE);

	SPI_moduleDisable(SPI1);
	SPI_masterInit(SPI1, &sconfig);
	SPI_moduleEnable(SPI1);

	SPI_moduleDisable(SPI2);
	SPI_slaveInit(SPI2, &sconfig);
	SPI_moduleEnable(SPI2);

	SPI_disableInterrupt(SPI1, SPI_INT_MASK_ALL);
	SPI_disableInterrupt(SPI2, SPI_INT_MASK_ALL);

	for(i = 0; i < sizeof(send_data0); i++) {
		send_data0[i] = 0x5A + i;
		recv_data0[i] = 0;
	}

	SPI_enableDMA(SPI1, 1, 0);
	SPI_enableDMA(SPI2, 0, 1);

	dconfig.src_addr = (u32)send_data0;
	dconfig.dst_addr = (u32)&SPI1->DATA;
	dconfig.src_width = DMAX_TRANS_WIDTH_8;
	dconfig.dst_width = DMAX_TRANS_WIDTH_8;
	dconfig.src_msize = DMAX_MSIZE_1;
	dconfig.dst_msize = DMAX_MSIZE_1;
	dconfig.channel = 1;
	dconfig.prior = 1;
	dconfig.block_size = 7;
	dconfig.src_hs_i = DMAX_HS_MEM;
	dconfig.dst_hs_i = DMAX_HS_SPI0M_TX;
	dconfig.src_hs_t = DAMCX_HS_HARDWARE;
	dconfig.dst_hs_t = DAMCX_HS_HARDWARE;
	dconfig.tt_fc = DMAX_M2P_DMA;
	dconfig.src_mblk_t = 0;
	dconfig.dst_mblk_t = 0;

	puts("DMAX init!");
	DMAX_commonInit();
	DMAX_chanSetup(&dconfig);
	DMAX_chanEnable(dconfig.channel);

	puts("delay!");
	dconfig.src_addr = (u32)&SPI2->DATA;
	dconfig.dst_addr = (u32)recv_data0;
	dconfig.src_width = DMAX_TRANS_WIDTH_8;
	dconfig.dst_width = DMAX_TRANS_WIDTH_8;
	dconfig.src_msize = DMAX_MSIZE_1;
	dconfig.dst_msize = DMAX_MSIZE_1;
	dconfig.channel = 2;
	dconfig.prior = 2;
	dconfig.block_size = 7;
	dconfig.src_hs_i = DMAX_HS_SPI1S_RX;
	dconfig.dst_hs_i = DMAX_HS_MEM;
	dconfig.src_hs_t = DAMCX_HS_HARDWARE;
	dconfig.dst_hs_t = DAMCX_HS_HARDWARE;
	dconfig.tt_fc = DMAX_P2M_DMA;
	dconfig.src_mblk_t = 0;
	dconfig.dst_mblk_t = 0;

	DMAX_chanSetup(&dconfig);
	DMAX_chanEnable(dconfig.channel);

	puts("delay!");
	for (i = 0; i < (dconfig.block_size + 1); i++) {
		if (send_data0[i] != recv_data0[i]) {
			printf("the number = %d, src value = %x, dst value = %x\n",
					i, send_data0[i], recv_data0[i]);
			return -1;
		}
	}

	return 0;
}

void spi_init_gpio(void)
{
	GPIO_Config(GPIO_PIN_9, GPIO_9_SPIA_CLK, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
	GPIO_Config(GPIO_PIN_5, GPIO_5_SPIA_STE, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
	GPIO_Config(GPIO_PIN_8, GPIO_8_SPIA_SIMO, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
	//GPIO_Config(GPIO_PIN_10, GPIO_10_GPIO10, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_INVERT, GPIO_QUAL_ASYNC);

	GPIO_Config(GPIO_PIN_6, GPIO_6_SPIB_SOMI, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
	GPIO_Config(GPIO_PIN_7, GPIO_7_SPIB_SIMO, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
	GPIO_Config(GPIO_PIN_14, GPIO_14_SPIB_CLK, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
	GPIO_Config(GPIO_PIN_15, GPIO_15_SPIB_STE, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
	GPIO_Config(GPIO_PIN_10, GPIO_10_SPIA_SOMI, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
}

void test_spi()
{
    puts("spi test start!");

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIB);

    puts("spi gpio init start!");
    spi_init_gpio();
    puts("spi gpio init done!");

#if 0
    if (spi_testcase_TR_no_interrupt())
        goto error;
#endif

#if 0
    if (spi_testcase_TR_with_interrupt())
        goto error;
#endif

#if 1
    if (spi_testcase_TR_with_DMA())
    	goto error;
#endif

    puts("succeed: spi tests passed!");
    return;

error:
    puts("error: spi tests failed!");
}
