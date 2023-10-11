/*****************************************************************************
 *
*****************************************************************************/
#define DMA_CH0_BASE	(0x01009000UL)
#define FLASH_CTL_BASE	(0x01040000)
#define DMA_CH0			((int *)DMA_CH0_BASE)
#define CPUSYS_BASE      0x01001000
/*****************************************************************************
 *
*****************************************************************************/
#define RAM_BASE			(0x60000)
#define FLASH_BASE			(0x30002400)
#define FLASH_INFO_BASE		(0x30002000)
#define DMA_LENGTH			(256)
#define CORE0_TXT_START		(0x200000)
#define CORE0_DATA_START	(0x000000)
#define CORE1_TXT_START		(0x240000)
#define CORE1_DATA_START	(0x040000)
#define RAM_TEST_BASE		(0x044000)
#define SYSCTL_PERIPH_CLK_DMA	(0x0200)
/*****************************************************************************
 *
*****************************************************************************/
int  __attribute__((section(".qxboot"))) boot_dma_read_256bytes(int srcAddr, int dstAddr)
{
	unsigned int *dma_ch = (unsigned int*)(DMA_CH0);
	*(dma_ch + 0x4) = 0x03;//DMA enable
	*(dma_ch + 0x44) = 0x3f;//DMA	block 256B
	*(dma_ch + 0x49) = 0x0;//DMA mermory to memory
	*(dma_ch + 0x40) = srcAddr;
	*(dma_ch + 0x42) = dstAddr;
	*(dma_ch + 0x46) = 0x001200;//src:32bit dst:32bit
	*(dma_ch + 0x60) = 0x02;//DMA	�ж����� ����block��������ж�
	*(dma_ch + 0x64) = 0x02;//DMA	�ж����� ����block��������ж�
	*(dma_ch + 0x6) = 0x00101;//DMA	CH1 start
	int x = *(dma_ch + 0x62);
	int y = x & 0x01;
	while(!y){
		x = *(dma_ch + 0x62);
		y = x & 0x02;
	}
	*(dma_ch + 0x66) = 0x02;//clear interrupt flag
	return 0;
}

/*****************************************************************************
 *
*****************************************************************************/
int  __attribute__((section(".qxboot")))boot_dma_read(int srcAddr, int dstAddr, int len)
{
	int tempSrc = srcAddr;
	int tempDst = dstAddr;
	int check = 0;
	do{
		int nc = boot_dma_read_256bytes(tempSrc, tempDst);
		check = check + nc;
		tempSrc = tempSrc + DMA_LENGTH ;
		tempDst = tempDst + DMA_LENGTH ;
		len = len - DMA_LENGTH;

	}while(len > 0);
	return check;
}

/*****************************************************************************
 *
*****************************************************************************/
void  __attribute__((section(".qxboot")))boot_SysCtl_enableDMA(void)
{
    short regIndex;
    short bitIndex;

    // Decode the peripheral variable.
    regIndex = 4 * (SYSCTL_PERIPH_CLK_DMA & 0x001FU);
    bitIndex = (SYSCTL_PERIPH_CLK_DMA & 0x1F00U) >> 0x0008U;

    // Turn on the module clock.
    int* ptrDmaClk = (int*)(CPUSYS_BASE + regIndex);
    int dmaClk = *ptrDmaClk;
    *ptrDmaClk = dmaClk | (1 << bitIndex);

}
/*****************************************************************************
 *
*****************************************************************************/
int  __attribute__((section(".qxboot")))bootmain(void)
{
#if 0
	boot_SysCtl_enableDMA();
#endif
	int *p = (int*)(FLASH_INFO_BASE);
	int core0_txt_len	= *(p);
	int core0_data_len	= *(p + 1);
	int core1_txt_len	= *(p + 2);
	int core1_data_len	= *(p + 3);

	int flashCore0Txt	= FLASH_BASE;
	int flashCore0Data	= FLASH_BASE + core0_txt_len;
	int flashCore1Txt	= FLASH_BASE + core0_txt_len + core0_data_len;
	int flashCore1Data	= FLASH_BASE + core0_txt_len + core0_data_len + core1_txt_len;

#if 0
	boot_dma_read(flashCore0Txt,	CORE0_TXT_START, core0_txt_len);
	boot_dma_read(flashCore0Data, CORE0_DATA_START, core0_data_len);
	boot_dma_read(flashCore1Txt, CORE1_TXT_START, core1_txt_len);
	boot_dma_read(flashCore1Data, CORE1_DATA_START, core1_data_len);
#endif
	return 0;
}
/*****************************************************************************
 *
*****************************************************************************/

