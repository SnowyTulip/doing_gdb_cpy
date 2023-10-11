#include "common.h"

#define SYSCTL_PERIPH_CLK_DMA (0x0200)

int dma_read_256bytes(int srcAddr, int dstAddr)
{
    unsigned int *dma_ch = (unsigned int *)(DMA_BASE);
    *(dma_ch + 0x4)      = 0x03; // DMA enable
    *(dma_ch + 0x44)     = 0x3f; // DMA	block 256B
    *(dma_ch + 0x49)     = 0x0;  // DMA mermory to memory
    *(dma_ch + 0x40)     = srcAddr;
    *(dma_ch + 0x42)     = dstAddr;
    *(dma_ch + 0x46)     = 0x001200; // src:32bit dst:32bit
    *(dma_ch + 0x60)     = 0x02;     // DMA	中断屏蔽 保留block传输结束中断
    *(dma_ch + 0x64)     = 0x02;     // DMA	中断屏蔽 保留block传输结束中断
    *(dma_ch + 0x6)      = 0x00101;  // DMA	CH1 start
    int x                = *(dma_ch + 0x62);
    int y                = x & 0x01;
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
        tempSrc = tempSrc + 256;
        tempDst = tempDst + 256;
        len     = len - 256;

    } while (len > 0);
    return check;
}

void SysCtl_enableDMA(void)
{
    short regIndex;
    short bitIndex;

    // Decode the peripheral variable.
    regIndex = 4 * (SYSCTL_PERIPH_CLK_DMA & 0x001FU);
    bitIndex = (SYSCTL_PERIPH_CLK_DMA & 0x1F00U) >> 0x0008U;

    // Turn on the module clock.
    int *ptrDmaClk = (int *)(CPUSYS_BASE + regIndex);
    int dmaClk     = *ptrDmaClk;
    *ptrDmaClk     = dmaClk | (1 << bitIndex);
}

int sector_read_all_speed_test_with_dma(void)
{
    SysCtl_enableDMA();
    dma_read(FLASH_DATA_BASE, 0x40000, 256 * 1024);
    return 0;
}

void sector_erase_and_write_test(u32 sectors_count)
{
    int i, sector, base, val;

    for (sector = 0; sector < sectors_count; sector++)
    {
        base = FLASH_DATA_BASE + 4096 * sector;
        /* buf_dump_word("before erase:", (int *)base, 1024); */

        printf("sector %d test...\n", sector);
        Flash_eraseSector(sector);
        /* buf_dump_word("after erase:", (int *)base, 1024); */
        for (i = 0; i < 1024; i++)
        {
            val = Flash_readWord(base + i * 4);
            if (val != 0xFFFFFFFF)
                printf("erase check error:sector=%d, idx=%x, val=%x\n", sector, i, val);
        }

        for (i = 0; i < 1024; i++)
            Flash_writeWord(base + i * 4, sector * i);
        /* buf_dump_word("after write:", (int *)base, 1024); */

        for (i = 0; i < 1024; i++)
        {
            val = Flash_readWord(base + i * 4);
            if (val != sector * i)
                printf("flash write check error:sector=%d, idx=%x, val=%x\n", sector, i, val);
        }
    }
}

void block_erase_test()
{
    int i, block, val, base;
    for (block = 0; block < 16; block++)
    {
        puts("flash block erase test...");
        Flash_eraseBlock(block);
        base = FLASH_DATA_BASE + 1024 * 64 * block;

        for (int i = 0; i < 1024 * 64 / 4; i++)
        {
            val = Flash_readWord(base + i * 4);
            if (val != 0xFFFFFFFF)
            {
                printf("flash block erase check error:block = %d, idx=%x, val=%x\n", block, i, val);
                break;
            }
            Flash_writeWord(base + i * 4, base + i * 4);
            val = Flash_readWord(base + i * 4);
            if (val != base + i * 4)
            {
                printf("flash read after write check error:idx=%x, val=%x, \n", i, val);
                break;
            }
        }
    }
}

void chip_erase_test()
{
    int i, val;

    puts("flash chip erase test...");
    Flash_eraseChip();
    for (i = 0; i < 1024 * 1024 / 4; i++)
    {
        Flash_writeWord(FLASH_DATA_BASE + i * 4, 0x5A);
        val = Flash_readWord(FLASH_DATA_BASE + i * 4);
        if (val != 0x5A)
        {
            printf("flash chip erase check error:idx=%x, val=%x, \n", i, val);
            break;
        }
    }
    puts("flash chip erase test passed");
}

void sector_read_all_speed_test()
{
    int i, val;
    for (i = 0; i < 1024 * 256 / 4; i++)
        val = *((volatile uint32_t *)(FLASH_DATA_BASE + i * 4));
}

static void Flash_eraseOTP(vu32 otp_num)
{
    while (Flash0CtrlRegs->STATUS.bit.WIP)
        ;
    while (Flash0CtrlRegs->ERASE & 0x20000000) // wait NO BUSY
        ;

    Flash0CtrlRegs->ERASE = 0x90000000 | 3 << 25 | otp_num << 12;

    while (Flash0CtrlRegs->ERASE & 0x80000000) // wait ERASE Finish
        ;
}

void flash_otp_area_test(void)
{
    int i, j, addr, val;

    for (j = 0; j < 2; j++)
    {
        printf("OTP%d test...\n", j);
        Flash_eraseOTP(j);
        for (i = 0; i < 256; i++)
        {
            addr = 0x30100000 + j * 0x1000 + i * 4;
            val  = Flash_readWord(addr);
            if (val != 0xFFFFFFFF)
                printf("OTP%d erase check error: idx=%x, val=%x\n", j, i, val);
            Flash_writeWord(addr, i);
            val = Flash_readWord(addr);
            if (val != i)
                printf("OTP%d flash write check error:idx=%x, val=%x\n", j, i, val);
        }

        Flash_eraseOTP(j);
        for (i = 0; i < 256; i++)
        {
            addr = 0x30100000 + j * 0x1000 + i * 4;
            val  = Flash_readWord(addr);
            if (val != 0xFFFFFFFF)
                printf("OTP%d erase check error: idx=%x, val=%x\n", j, i, val);
            Flash_writeWord(addr, i);
            val = Flash_readWord(addr);
            if (val != i)
                printf("OTP%d flash write check error:idx=%x, val=%x\n", j, i, val);
        }
    }
}

void test_flash(void)
{
#if 0
    puts("flash init module with qspi mode...");
    Flash_initModule(1, 1);
    sector_erase_and_write_test(256);
    block_erase_test();
#endif

#if 0
    puts("flash init module with spi mode...");
    Flash_initModule(1, 0);
    sector_erase_and_write_test(256);
    chip_erase_test();
#endif

#if 0
    puts("flash init module with 512 div clock...");
    Flash_initModule(512, 1);
    sector_erase_and_write_test(10);
#endif

#if 0
    Flash_initModule(1, 1);
    puts("flash read speed test...");
    /* 0.14s read 256k byte at 50MHz flash clock with qspi mode */
    sector_read_all_speed_test();
    puts("end");
#endif

#if 0
    Flash_initModule(1, 1);
    puts("flash read speed test with dma...");
    /* 0.04s read 256K Byte at 50MHz flash clock with qspi mode */
    sector_read_all_speed_test_with_dma();
#endif

#if 0
    Flash_initModule(1, 1);
    puts("flash_otp_area_test");
    flash_otp_area_test();
#endif
}
