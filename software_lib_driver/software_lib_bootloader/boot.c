/**
 **************************************************************************
 * @file     boot.c
 * @version  v1.0.0
 * @date     2023-12-30
 **************************************************************************
 */

#define CPUSYS_BASE     (0x01001000U)
#define DMA_CH0_BASE    (0x01009000U)
#define RAM_BASE        (0x00060000U)
#define FLASH_BASE      (0x30002400U)
#define FLASH_INFO_BASE (0x30002000U)
#define RAM_TEST_BASE   (0x00044000U)

#define CORE0_TXT_START  (0x200000)
#define CORE0_DATA_START (0x000000)
#define CORE1_TXT_START  (0x240000)
#define CORE1_DATA_START (0x040000)

#define DMA_LENGTH       (256)

#define HWREG(x) (*((volatile unsigned int *)(x)))

int dma_read_256bytes(int srcAddr, int dstAddr)
{
    unsigned int *dma_ch = (unsigned int *)(DMA_CH0_BASE);

    *(dma_ch + 0x4)  = 0x03; // DMA enable
    *(dma_ch + 0x44) = 0x3f; // DMA	block 256B
    *(dma_ch + 0x49) = 0x0;  // DMA mermory to memory
    *(dma_ch + 0x40) = srcAddr;
    *(dma_ch + 0x42) = dstAddr;
    *(dma_ch + 0x46) = 0x001200; // src:32bit dst:32bit
    *(dma_ch + 0x60) = 0x02;     // DMA	中断屏蔽 保留block传输结束中断
    *(dma_ch + 0x64) = 0x02;     // DMA	中断屏蔽 保留block传输结束中断
    *(dma_ch + 0x6)  = 0x00101;  // DMA	CH1 start
    int x            = *(dma_ch + 0x62);
    int y            = x & 0x01;

    while (!y)
    {
        x = *(dma_ch + 0x62);
        y = x & 0x02;
    }
    *(dma_ch + 0x66) = 0x02; // clear interrupt flag

    return 0;
}

int dma_read(int srcAddr, int dstAddr, int len)
{
    int tempSrc = srcAddr;
    int tempDst = dstAddr;
    int check   = 0;

    do
    {
        int nc  = dma_read_256bytes(tempSrc, tempDst);
        check   = check + nc;
        tempSrc = tempSrc + DMA_LENGTH;
        tempDst = tempDst + DMA_LENGTH;
        len     = len - DMA_LENGTH;

    } while (len > 0);

    return check;
}

void SysCtl_enableDMA(void)
{
    HWREG(CPUSYS_BASE) |= (1 << 2);
}

void SysCtl_resetAndDisableDMA(void)
{
    HWREG(DMA_CH0_BASE + 0x58) = 1;
    for (int i = 0; i < 10; i++) // wait for reset
        ;
    HWREG(CPUSYS_BASE) &= ~(1 << 2);
}

int main(void)
{
    SysCtl_enableDMA();

    int *p             = (int *)(FLASH_INFO_BASE);
    int core0_txt_len  = *(p);
    int core0_data_len = *(p + 1);
    int core1_txt_len  = *(p + 2);
    int core1_data_len = *(p + 3);

    int flashCore0Txt  = FLASH_BASE;
    int flashCore0Data = FLASH_BASE + core0_txt_len;
    int flashCore1Txt  = FLASH_BASE + core0_txt_len + core0_data_len;
    int flashCore1Data = FLASH_BASE + core0_txt_len + core0_data_len + core1_txt_len;

    if (core0_txt_len != 0)
        dma_read(flashCore0Txt, CORE0_TXT_START, core0_txt_len);

    if (core0_data_len != 0)
        dma_read(flashCore0Data, CORE0_DATA_START, core0_data_len);

    if (core1_txt_len != 0)
        dma_read(flashCore1Txt, CORE1_TXT_START, core1_txt_len);

    if (core1_data_len != 0)
        dma_read(flashCore1Data, CORE1_DATA_START, core1_data_len);

    SysCtl_resetAndDisableDMA();

    return 0;
}
