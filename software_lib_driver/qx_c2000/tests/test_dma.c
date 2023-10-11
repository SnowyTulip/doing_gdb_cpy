#include "common.h"

#ifdef TEST_DMA

char src_buf[128] = { 0 };
char dst_buf[128] = { 0 };

__interrupt void dma_ch1_isr(void)
{
	puts("dma ch1 isr start");
	u32 status;

	status = DMAX_getChanIntStatus(1);
	if (status & DMAX_IRQ_ALL_ERR) {
		puts("DMA error");
		//DMAX_clearChanIntStatus(1, DMAX_IRQ_ALL_ERR);
	}
	if (status & DMAX_IRQ_DMA_TRF) {
		puts("DMA done");
		//DMAX_clearChanIntStatus(1, 0x2U);
	}
}

__interrupt void dma_ch2_isr(void)
{
	puts("dma ch2 isr start");
	u32 status;

	status = DMAX_getChanIntStatus(2);
	if (status & DMAX_IRQ_ALL_ERR) {
		puts("DMA error");
		DMAX_clearChanIntStatus(2, DMAX_IRQ_ALL_ERR);
	}
	if (status & DMAX_IRQ_DMA_TRF) {
		puts("DMA done");
		DMAX_clearChanIntStatus(2, 0x2U);
	}
}

__interrupt void dma_ch3_isr(void)
{
	puts("dma ch3 isr start");
	u32 status;

	status = DMAX_getChanIntStatus(3);
	if (status & DMAX_IRQ_ALL_ERR) {
		puts("DMA error");
		DMAX_clearChanIntStatus(3, DMAX_IRQ_ALL_ERR);
	}
	if (status & DMAX_IRQ_DMA_TRF) {
		puts("DMA done");
		DMAX_clearChanIntStatus(3, 0x2U);
	}
}

__interrupt void dma_ch4_isr(void)
{
	puts("dma ch4 isr start");
	u32 status;

	status = DMAX_getChanIntStatus(4);
	if (status & DMAX_IRQ_ALL_ERR) {
		puts("DMA error");
		DMAX_clearChanIntStatus(4, DMAX_IRQ_ALL_ERR);
	}
	if (status & DMAX_IRQ_DMA_TRF) {
		puts("DMA done");
		DMAX_clearChanIntStatus(4, 0x2U);
	}
}

__interrupt void dma_ch5_isr(void)
{
	puts("dma ch5 isr start");
	u32 status;

	status = DMAX_getChanIntStatus(5);
	if (status & DMAX_IRQ_ALL_ERR) {
		puts("DMA error");
		DMAX_clearChanIntStatus(5, DMAX_IRQ_ALL_ERR);
	}
	if (status & DMAX_IRQ_DMA_TRF) {
		puts("DMA done");
		DMAX_clearChanIntStatus(5, 0x2U);
	}
}

__interrupt void dma_ch6_isr(void)
{
	puts("dma ch6 isr start");
	u32 status;

	status = DMAX_getChanIntStatus(6);
	if (status & DMAX_IRQ_ALL_ERR) {
		puts("DMA error");
		DMAX_clearChanIntStatus(6, DMAX_IRQ_ALL_ERR);
	}
	if (status & DMAX_IRQ_DMA_TRF) {
		puts("DMA done");
		DMAX_clearChanIntStatus(6, 0x2U);
	}
}

int dma_testcase_m2m_8b(u8 channel)
{
	int i;
	DMAXChanConfig dconfig;

	dconfig.src_addr = (u32)src_buf;
	dconfig.dst_addr = (u32)dst_buf;
	dconfig.src_width = DMAX_TRANS_WIDTH_8;
	dconfig.dst_width = DMAX_TRANS_WIDTH_8;
	dconfig.src_msize = DMAX_MSIZE_1;
	dconfig.dst_msize = DMAX_MSIZE_1;
	dconfig.channel = channel;
	dconfig.prior = channel;
	dconfig.block_size = 7;
	dconfig.src_hs_i = DMAX_HS_MEM;
	dconfig.dst_hs_i = DMAX_HS_MEM;
	dconfig.src_hs_t = 0;
	dconfig.dst_hs_t = 0;
	dconfig.tt_fc = DMAX_M2M_DMA;

	printf("src addr = %x, dst addr =%x\n", dconfig.src_addr, dconfig.dst_addr);

	for(i = 0; i < sizeof(src_buf); i++)
		src_buf[i] = 0x5A + i;

	DMAX_commonInit();
	DMAX_chanSetup(&dconfig);
	DMAX_chanEnable(dconfig.channel);

	puts("delay");

	for (i = 0; i < (dconfig.block_size + 1); i++) {
		if (src_buf[i] != dst_buf[i]) {
			printf("the number = %d, src value = %x, dst value = %x\n",
					i, src_buf[i], dst_buf[i]);
			return -1;
		}
	}

	return 0;
}

int dma_testcase_m2m_16b(u8 channel)
{
	int i;
	DMAXChanConfig dconfig;

	dconfig.src_addr = (u32)src_buf;
	dconfig.dst_addr = (u32)dst_buf;
	dconfig.src_width = DMAX_TRANS_WIDTH_32;
	dconfig.dst_width = DMAX_TRANS_WIDTH_32;
	dconfig.src_msize = DMAX_MSIZE_1;
	dconfig.dst_msize = DMAX_MSIZE_1;
	dconfig.channel = channel;
	dconfig.prior = channel;
	dconfig.block_size = 7;
	dconfig.src_hs_i = DMAX_HS_MEM;
	dconfig.dst_hs_i = DMAX_HS_MEM;
	dconfig.src_hs_t = 0;
	dconfig.dst_hs_t = 0;
	dconfig.tt_fc = DMAX_M2M_DMA;

	printf("src addr = %x, dst addr =%x\n", dconfig.src_addr, dconfig.dst_addr);

	for(i = 0; i < sizeof(src_buf); i++)
		src_buf[i] = 0x5A + i;

	DMAX_commonInit();
	DMAX_chanSetup(&dconfig);
	DMAX_chanEnable(dconfig.channel);

	puts("delay");

	for (i = 0; i < 2 * (dconfig.block_size + 1); i++) {
		if (src_buf[i] != dst_buf[i]) {
			printf("the number = %d, src value = %x, dst value = %x\n",
					i, src_buf[i], dst_buf[i]);
			return -1;
		}
	}

	return 0;
}

int dma_testcase_m2m_32b(u8 channel)
{
	int i;
	DMAXChanConfig dconfig;

	dconfig.src_addr = (u32)src_buf;
	dconfig.dst_addr = (u32)dst_buf;
	dconfig.src_width = DMAX_TRANS_WIDTH_32;
	dconfig.dst_width = DMAX_TRANS_WIDTH_32;
	dconfig.src_msize = DMAX_MSIZE_1;
	dconfig.dst_msize = DMAX_MSIZE_1;
	dconfig.channel = channel;
	dconfig.prior = channel;
	dconfig.block_size = 7;
	dconfig.src_hs_i = DMAX_HS_MEM;
	dconfig.dst_hs_i = DMAX_HS_MEM;
	dconfig.src_hs_t = 0;
	dconfig.dst_hs_t = 0;
	dconfig.tt_fc = DMAX_M2M_DMA;

	printf("src addr = %x, dst addr =%x\n", dconfig.src_addr, dconfig.dst_addr);

	for(i = 0; i < sizeof(src_buf); i++)
		src_buf[i] = 0x5A + i;

	DMAX_commonInit();
	DMAX_chanSetup(&dconfig);
	DMAX_chanEnable(dconfig.channel);

	puts("delay");

	for (i = 0; i < 4 * (dconfig.block_size + 1); i++) {
		if (src_buf[i] != dst_buf[i]) {
			printf("the number = %d, src value = %x, dst value = %x\n",
					i, src_buf[i], dst_buf[i]);
			return -1;
		}
	}

	return 0;
}

int dma_testcase_m2m_unalign(u8 channel)
{
	int i;
	DMAXChanConfig dconfig;

	dconfig.src_addr = (u32)src_buf + 1;
	dconfig.dst_addr = (u32)dst_buf + 1;
	dconfig.src_width = DMAX_TRANS_WIDTH_32;
	dconfig.dst_width = DMAX_TRANS_WIDTH_32;
	dconfig.src_msize = DMAX_MSIZE_1;
	dconfig.dst_msize = DMAX_MSIZE_1;
	dconfig.channel = channel;
	dconfig.prior = channel;
	dconfig.block_size = 7;
	dconfig.src_hs_i = DMAX_HS_MEM;


	dconfig.dst_hs_i = DMAX_HS_MEM;
	dconfig.src_hs_t = 0;
	dconfig.dst_hs_t = 0;
	dconfig.tt_fc = DMAX_M2M_DMA;

	printf("src addr = %x, dst addr =%x\n", dconfig.src_addr, dconfig.dst_addr);

	for(i = 0; i < sizeof(src_buf); i++)
		src_buf[i] = 0x5A + i;

	DMAX_commonInit();
	DMAX_chanSetup(&dconfig);
	DMAX_chanEnable(dconfig.channel);

	puts("delay");

	for (i = 1; i < 4 * (dconfig.block_size + 1); i++) {
		if (src_buf[i] != dst_buf[i]) {
			printf("the number = %d, src value = %x, dst value = %x\n",
					i, src_buf[i], dst_buf[i]);
			return -1;
		}
	}

	return 0;
}

int dma_testcase_prior(void)
{
	int i;
	DMAXChanConfig dconfig;

	for(i = 0; i < sizeof(src_buf); i++)
			src_buf[i] = 0x5A + i;

	for ( i = 1; i <= DMAX_NUM_CHANNELS; i++) {
		dconfig.src_addr = (u32)src_buf;
		dconfig.dst_addr = (u32)dst_buf;
		dconfig.src_width = DMAX_TRANS_WIDTH_32;
		dconfig.dst_width = DMAX_TRANS_WIDTH_32;
		dconfig.src_msize = DMAX_MSIZE_1;
		dconfig.dst_msize = DMAX_MSIZE_1;
		dconfig.channel = i;
		dconfig.prior = i - 1;
		dconfig.block_size = 31;
		dconfig.src_hs_i = DMAX_HS_MEM;
		dconfig.dst_hs_i = DMAX_HS_MEM;
		dconfig.src_hs_t = 0;
		dconfig.dst_hs_t = 0;
		dconfig.tt_fc = DMAX_M2M_DMA;

		printf("src addr = %x, dst addr =%x\n", dconfig.src_addr, dconfig.dst_addr);

		DMAX_commonInit();
		DMAX_chanSetup(&dconfig);
	}


	for ( i = 1; i <= DMAX_NUM_CHANNELS; i++)
		DMAX_chanEnable((u8) i);

	for ( i = 0; i < 5; i++)
		puts("delay");

	for (i = 0; i < 4 * (dconfig.block_size + 1); i++) {
		if (src_buf[i] != dst_buf[i]) {
			printf("the number = %d, src value = %x, dst value = %x\n",
					i, src_buf[i], dst_buf[i]);
			return -1;
		}
	}

	return 0;
}

int dma_testcase_interrupt(u8 channel)
{
	int i;
	DMAXChanConfig dconfig;

	dconfig.src_addr = (u32)src_buf;
	dconfig.dst_addr = (u32)dst_buf;
	dconfig.src_width = DMAX_TRANS_WIDTH_32;
	dconfig.dst_width = DMAX_TRANS_WIDTH_32;
	dconfig.src_msize = DMAX_MSIZE_1;
	dconfig.dst_msize = DMAX_MSIZE_1;
	dconfig.channel = channel;
	dconfig.prior = channel;
	dconfig.block_size = 7;
	dconfig.src_hs_i = DMAX_HS_MEM;
	dconfig.dst_hs_i = DMAX_HS_MEM;
	dconfig.src_hs_t = 0;
	dconfig.dst_hs_t = 0;
	dconfig.tt_fc = DMAX_M2M_DMA;

	printf("src addr = %x, dst addr =%x\n", dconfig.src_addr, dconfig.dst_addr);

	Interrupt_enable(INT_DMA_CH1);
	Interrupt_enable(INT_DMA_CH2);
	Interrupt_enable(INT_DMA_CH3);
	Interrupt_enable(INT_DMA_CH4);
	Interrupt_enable(INT_DMA_CH5);
	Interrupt_enable(INT_DMA_CH6);
	for(i = 0; i < sizeof(src_buf); i++)
		src_buf[i] = 0x5A + i;

	DMAX_commonInit();
	DMAX_chanSetup(&dconfig);
	DMAX_chanEnable(dconfig.channel);

	puts("delay");

	for (i = 0; i < 4 * (dconfig.block_size + 1); i++) {
		if (src_buf[i] != dst_buf[i]) {
			printf("the number = %d, src value = %x, dst value = %x\n",
					i, src_buf[i], dst_buf[i]);
			return -1;
		}
	}

	return 0;
}

int dma_testcase_p2m_m2p(u8 channel)
{
	int i;
	SPI_Config sconfig;
	DMAXChanConfig dconfig;

	sconfig.data_width = SPI_DATA_BITS_32;
	sconfig.sample_mode = SPI_SAMPLE_POS_0;
	sconfig.trans_mode  = SPI_TRANS_MODE_TR;
	sconfig.baudrate = 1000000;
	sconfig.rx_ftl  = 0;
	sconfig.tx_ftl  = 0;

	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIB);

	GPIO_Config(GPIO_PIN_9, GPIO_9_SPIA_CLK, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
	GPIO_Config(GPIO_PIN_5, GPIO_5_SPIA_STE, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
	GPIO_Config(GPIO_PIN_8, GPIO_8_SPIA_SIMO, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
		//GPIO_Config(GPIO_PIN_10, GPIO_10_GPIO10, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_INVERT, GPIO_QUAL_ASYNC);

	GPIO_Config(GPIO_PIN_6, GPIO_6_SPIB_SOMI, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
	GPIO_Config(GPIO_PIN_7, GPIO_7_SPIB_SIMO, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
	GPIO_Config(GPIO_PIN_14, GPIO_14_SPIB_CLK, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
	GPIO_Config(GPIO_PIN_15, GPIO_15_SPIB_STE, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
	GPIO_Config(GPIO_PIN_10, GPIO_10_SPIA_SOMI, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);

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

	for(i = 0; i < sizeof(src_buf); i++) {
		src_buf[i] = 0x5A + i;
		dst_buf[i] = 0;
	}

	SPI_enableDMA(SPI1, 1, 0);
	SPI_enableDMA(SPI2, 0, 1);

	dconfig.src_addr = (u32)src_buf;
	dconfig.dst_addr = (u32)&SPI1->DATA;
	dconfig.src_width = DMAX_TRANS_WIDTH_32;
	dconfig.dst_width = DMAX_TRANS_WIDTH_32;
	dconfig.src_msize = DMAX_MSIZE_1;
	dconfig.dst_msize = DMAX_MSIZE_1;
	dconfig.channel = channel;
	dconfig.prior = channel;
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
	dconfig.dst_addr = (u32)dst_buf;
	dconfig.src_width = DMAX_TRANS_WIDTH_32;
	dconfig.dst_width = DMAX_TRANS_WIDTH_32;
	dconfig.src_msize = DMAX_MSIZE_1;
	dconfig.dst_msize = DMAX_MSIZE_1;
	dconfig.channel = (channel + 1) % 6;
	dconfig.prior = (channel + 1) % 6;
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
	for (i = 0; i < 4 * (dconfig.block_size + 1); i++) {
		if (src_buf[i] != dst_buf[i]) {
			printf("the number = %d, src value = %x, dst value = %x\n",
					i, src_buf[i], dst_buf[i]);
			return -1;
		}
	}

	return 0;
}

void test_dma(void)
{
	puts("dma test start!");
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);

#if 0
	for (int i = 1; i <= DMAX_NUM_CHANNELS; i++) {
		if (dma_testcase_m2m_32b(i)) {
			printf("chan %d DMA_M2M test failed\n", i);
			goto error;
		}
	}
#endif

#if 0
	for (int i = 1; i <= DMAX_NUM_CHANNELS; i++) {
		if (dma_testcase_m2m_16b(i)) {
			printf("chan %d DMA_M2M test failed\n", i);
			goto error;
		}
	}
#endif

#if 0
	for (int i = 1; i <= DMAX_NUM_CHANNELS; i++) {
		if (dma_testcase_m2m_8b(i)) {
			printf("chan %d DMA_M2M test failed\n", i);
			goto error;
		}
	}
#endif

#if 0
	for (int i = 1; i <= DMAX_NUM_CHANNELS; i++) {
		if (dma_testcase_m2m_unalign(i)) {
			printf("chan %d DMA_M2M test failed\n", i);
			goto error;
		}
	}
#endif

#if 0
	if (dma_testcase_prior()) {
		printf("DMA prior test failed\n");
		goto error;
	}
#endif

#if 0
	for (int i = 1; i <= DMAX_NUM_CHANNELS; i++) {
		if (dma_testcase_p2m_m2p(i)) {
			printf("chan %d DMA_M2P_P2M test failed\n", i);
			goto error;
		}
	}
#endif

#if 0
	for (int i = 1; i <= DMAX_NUM_CHANNELS; i++) {
		dma_testcase_interrupt(i);
	}
#endif

	puts("succeed: dma tests passed!");
	return;

error:
	puts("error: dma tests failed!");
}

#endif
