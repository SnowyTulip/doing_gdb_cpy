#include "common.h"
#include <string.h>

#define TRACEBUF_BASE   0x007f0c04
#define PC_START        0x007f0c10
#define PC_END          0x007f0cf0
#define WATCHPOINT_BASE 0x007F0D00
#define WATCHPOINT_CTRL 0x007F0D04

typedef enum
{
    A_RAMLOAD_EN,       // �����Ƿ���A�����ϵ�����RAM����load����ַ
    B_RAMLOAD_EN1,      // �����Ƿ���B�����ϵ�����RAM����load����ַ
    A_RAMSTORE_EN1,     // �����Ƿ���A�����ϵ�����RAMд��store����ַ
    B_RAMSTORE_EN,      // �����Ƿ���B�����ϵ�����RAMд��store����ַ
    A_PC_EN,            // �����Ƿ���A�����ϵ�PCֵ
    B_PC_EN,            // �����Ƿ���B�����ϵ�PCֵ
    TRACEBUF_OUTPUT_EN, // ���Ƽ�⵽�Ƿ���ַ����ʱ���Ƿ���trace buffer���
    TRACEBUF_EXP_EN,    // ���Ƽ�⵽�Ƿ���ַ����ʱ���Ƿ��Ƿ񷢳��쳣
} watchpoint_ctrlbit;

typedef struct WATCHPOINT
{
    vu32 rsvd;       // ���岻��
    vu32 WP_CTRL;    // ����ģ��ʹ��
    vu32 WP_ILLADDR; // ��⵽�ķǷ���ַ������ɶ�
    vu32 WP_DATAA1;  // ��������RAM���A������ʼ��ַ
    vu32 WP_DATAA2;  // ��������RAM���A���������ַ
    vu32 WP_DATAB1;  // ��������RAM���B������ʼ��ַ
    vu32 WP_DATAB2;  // ��������RAM���B���������ַ
    vu32 WP_INSNA1;  // ����ָ��RAM���A������ʼ��ַ
    vu32 WP_INSNA2;  // ����ָ��RAM���A���������ַ
    vu32 WP_INSNB1;  // ����ָ��RAM���B������ʼ��ַ
    vu32 WP_INSNB2;  // ����ָ��RAM���B���������ַ
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

// ���������жϴ������������.s�ļ����ʹ��
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

// ͨ���������ҵ�PC��ַ���в���
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
    watchpoint_reg->WP_DATAA1  = 0x00060000; // ��������A����ʼ��ַ
    watchpoint_reg->WP_DATAA2  = 0x00060010; // ��������A�Ľ�����ַ
    watchpoint_enable(A_RAMLOAD_EN);         // ��������������A�ļ���
    watchpoint_enable(TRACEBUF_EXP_EN);      // �Ƿ���ַ���������쳣
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
    watchpoint_reg->WP_DATAA1  = 0x00060000; // ��������A����ʼ��ַ
    watchpoint_reg->WP_DATAA2  = 0x00060010; // ��������A�Ľ�����ַ
    watchpoint_enable(A_RAMLOAD_EN);         // ��������������A�ļ���
    watchpoint_enable(TRACEBUF_OUTPUT_EN) // TRACEBUF_OUTPUT_EN��λ����mode3�������쳣�����뵽tracebuffer

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
    watchpoint_reg->WP_INSNA1  = 0x8730; // ָ������A����ʼ��ַ
    watchpoint_reg->WP_INSNA2  = 0x8740; // ָ������A�Ľ�����ַ
    watchpoint_enable(A_PC_EN);          // ������ָ������A�ļ���
    watchpoint_enable(TRACEBUF_EXP_EN);  // �Ƿ���ַ���������쳣

    func();

#endif

    int delay = 1000;
    while (delay--)
        ;
}
