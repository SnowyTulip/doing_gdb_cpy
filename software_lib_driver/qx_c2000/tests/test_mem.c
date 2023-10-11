#include "common.h"

void addr_read_write_test(vu32 addr)
{
    u32 val = 0;
#if 1
    val         = 0x11111111;
    HWREG(addr) = val;
    if (HWREG(addr) != val)
        printf("read error:(%x %x)\n", HWREG(addr), val);

    val          = 0x2222;
    HWREGH(addr) = val;
    if (HWREGH(addr) != val)
        printf("read error:(%x %x)\n", HWREGH(addr), val);
    val = 0x11112222;
    if (HWREG(addr) != val)
        printf("read error:(%x %x)\n", HWREG(addr), val);

    val              = 0x3333;
    HWREGH(addr + 2) = val;
    if (HWREGH(addr + 2) != val)
        printf("read error:(%x %x)\n", HWREGH(addr + 2), val);
    val = 0x33332222;
    if (HWREG(addr) != val)
        printf("read error:(%x %x)\n", HWREG(addr), val);

    val          = 0x44;
    HWREGB(addr) = val;
    if (HWREGB(addr) != val)
        printf("read error:(%x %x)\n", HWREGB(addr), val);
    val = 0x33332244;
    if (HWREG(addr) != val)
        printf("read error:(%x %x)\n", HWREG(addr), val);

    val              = 0x55;
    HWREGB(addr + 1) = val;
    if (HWREGB(addr + 1) != val)
        printf("read error:(%x %x)\n", HWREGB(addr + 1), val);
    val = 0x33335544;
    if (HWREG(addr) != val)
        printf("read error:(%x %x)\n", HWREG(addr), val);

    val              = 0x66;
    HWREGB(addr + 2) = val;
    if (HWREGB(addr + 2) != val)
        printf("read error:(%x %x)\n", HWREGB(addr + 2), val);
    val = 0x33665544;
    if (HWREG(addr) != val)
        printf("read error:(%x %x)\n", HWREG(addr), val);

    val              = 0x77;
    HWREGB(addr + 3) = val;
    if (HWREGB(addr + 3) != val)
        printf("read error:(%x %x)\n", HWREGB(addr + 3), val);
    val = 0x77665544;
    if (HWREG(addr) != val)
        printf("read error:(%x %x)\n", HWREG(addr), val);
#else
    HWREG(addr) = 0x1;
    val         = HWREG(addr);
#endif
}

void mem_full_range_test()
{
#if 1
    puts("mem_full_range_test");
    int loop_size = 0x10000; // one bank 64K size

    /* bank0 test, 0 ~ 10k byte is save outer_data_mem_core0.dat, can not break */
    for (int j = 0x2800; j < loop_size; j += 4)
        addr_read_write_test(j);

    /* bank 1 test */
    for (int j = 0; j < loop_size; j += 4)
        addr_read_write_test(0x10000 + j);

    /* bank 2 test */
    for (int j = 0; j < loop_size; j += 4)
        addr_read_write_test(0x20000 + j);

    /* bank 3 test, last 2K byte is stack region, can not break */
    for (int j = 0; j < loop_size - 2048; j += 4)
        addr_read_write_test(0x30000 + j);

    /* bank 4 ~ 7 test */
    for (int i = 4; i < 8; i++)
    {
        for (int j = 0; j < loop_size; j += 4)
            addr_read_write_test(0x10000 * i + j);
    }
#endif

#if 0
    puts("load & store stack region for break execution test...");
    for (int j = 0x10000 - 2048; j < 0x10000; j += 4)
        addr_read_write_test(0x30000 + j);
    puts("function break...");
#endif
}

void test_mem(void)
{
#if 1
    puts("load & store peripheral regs test...");
    addr_read_write_test(OUTPUTXBAR_BASE);
#endif

#if 1
    puts("phl_reg_read_write_out_band_est");
    addr_read_write_test(CANA_BASE + 0x1000);
#endif

    mem_full_range_test();
}
