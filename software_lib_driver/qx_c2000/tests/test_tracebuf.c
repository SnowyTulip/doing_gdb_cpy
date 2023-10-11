#include "common.h"
#include <string.h>

#define TRACEBUF_BASE   0x007f0c04
#define PC_START        0x007f0c10
#define PC_END          0x007f0cf0
#define WATCHPOINT_BASE 0x007F0D00
#define WATCHPOINT_CTRL 0x007F0D04

typedef enum
{
    A_RAMLOAD_EN,       // 控制是否检测A区域上的数据RAM读（load）地址
    B_RAMLOAD_EN1,      // 控制是否检测B区域上的数据RAM读（load）地址
    A_RAMSTORE_EN1,     // 控制是否检测A区域上的数据RAM写（store）地址
    B_RAMSTORE_EN,      // 控制是否检测B区域上的数据RAM写（store）地址
    A_PC_EN,            // 控制是否检测A区域上的PC值
    B_PC_EN,            // 控制是否检测B区域上的PC值
    TRACEBUF_OUTPUT_EN, // 控制检测到非法地址访问时，是否向trace buffer输出
    TRACEBUF_EXP_EN,    // 控制检测到非法地址访问时，是否是否发出异常
} watchpoint_ctrlbit;

typedef struct WATCHPOINT
{
    vu32 rsvd;       // 意义不明
    vu32 WP_CTRL;    // 控制模块使能
    vu32 WP_ILLADDR; // 检测到的非法地址输出，可读
    vu32 WP_DATAA1;  // 控制数据RAM检测A区域起始地址
    vu32 WP_DATAA2;  // 控制数据RAM检测A区域结束地址
    vu32 WP_DATAB1;  // 控制数据RAM检测B区域起始地址
    vu32 WP_DATAB2;  // 控制数据RAM检测B区域结束地址
    vu32 WP_INSNA1;  // 控制指令RAM检测A区域起始地址
    vu32 WP_INSNA2;  // 控制指令RAM检测A区域结束地址
    vu32 WP_INSNB1;  // 控制指令RAM检测B区域起始地址
    vu32 WP_INSNB2;  // 控制指令RAM检测B区域结束地址
} WATCHPOINT;

void watchpoint_enable(watchpoint_ctrlbit bit)
{
    HWREG(WATCHPOINT_CTRL) = HWREG(WATCHPOINT_CTRL) | (0x1U << bit);
}

void clearbuf()
{
    unsigned char *start = (unsigned char *)PC_START;
    unsigned char *end   = (unsigned char *)PC_END;
    int size             = end - start + 1;
    memset(start, 0, size);
}

void setmode(int mode)
{
    clearbuf();
    int off   = mode - 1;
    u32 *addr = (u32 *)(TRACEBUF_BASE) + off;
    u32 value = mode;
    *addr     = value;
}

void disable_trace_buffer()
{
    int off   = 2;
    u32 *addr = (u32 *)(TRACEBUF_BASE) + off;
    u32 value = 0xffff;
    *addr     = value;
}

// 新增两个中断处理函数，需调整.s文件配合使用
void watchpoint_exp()
{
    unsigned int *start = (unsigned int *)PC_START;
    unsigned int *end   = (unsigned int *)PC_END;
    while (start < end)
    {
        unsigned int pc = *start;
        printf("pc is %x\n", pc);
        start++;
    }
}

void trace_buffer_exp()
{
    unsigned int *start = (unsigned int *)PC_START;
    unsigned int *end   = (unsigned int *)PC_END;
    while (start < end)
    {
        unsigned int pc = *start;
        start++;
    }
    disable_trace_buffer();
}

// 通过函数名找到PC地址进行测试
void func()
{
    int count  = 0;
    int result = 0;

    while (count < 100)
    {
        int a    = count + 1;
        int temp = a * count;
        result   = result + temp;
        count++;
    }
}

#define WATCHPOINT_PC

void test_tracebuf(void)
{
#ifdef MODE1
    setmode(1);
#endif

#ifdef MODE2
    WATCHPOINT *watchpoint_reg = (WATCHPOINT *)(WATCHPOINT_BASE);
    watchpoint_reg->WP_DATAA1  = 0x00060000; // 数据区域A的起始地址
    watchpoint_reg->WP_DATAA2  = 0x00060010; // 数据区域A的结束地址
    watchpoint_enable(A_RAMLOAD_EN);         // 开启对数据区域A的监视
    watchpoint_enable(TRACEBUF_EXP_EN);      // 非法地址将会引发异常
    setmode(2);

    int count  = 0;
    int result = 0;

    while (count < 100)
    {
        int a    = count + 1;
        int temp = a * count;
        result   = result + temp;
        count++;
    }

    int a = *(int *)(0x60004);
#endif

#ifdef MODE3
    WATCHPOINT *watchpoint_reg = (WATCHPOINT *)(WATCHPOINT_BASE);
    watchpoint_reg->WP_DATAA1  = 0x00060000; // 数据区域A的起始地址
    watchpoint_reg->WP_DATAA2  = 0x00060010; // 数据区域A的结束地址
    watchpoint_enable(A_RAMLOAD_EN);         // 开启对数据区域A的监视
    watchpoint_enable(TRACEBUF_OUTPUT_EN) // TRACEBUF_OUTPUT_EN置位则开启mode3，触发异常则输入到tracebuffer

        int count
        = 0;
    int result = 0;

    while (count < 100)
    {
        int a    = count + 1;
        int temp = a * count;
        result   = result + temp;
        count++;
    }

    int a = *(int *)(0x60004);
#endif

#ifdef WATCHPOINT_PC

    WATCHPOINT *watchpoint_reg = (WATCHPOINT *)(WATCHPOINT_BASE);
    watchpoint_reg->WP_INSNA1  = 0x8730; // 指令区域A的起始地址
    watchpoint_reg->WP_INSNA2  = 0x8740; // 指令区域A的结束地址
    watchpoint_enable(A_PC_EN);          // 开启对指令区域A的监视
    watchpoint_enable(TRACEBUF_EXP_EN);  // 非法地址将会引发异常

    func();

#endif

    int delay = 1000;
    while (delay--)
        ;
}
