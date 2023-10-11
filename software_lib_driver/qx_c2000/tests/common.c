#include "common.h"

#include <stdlib.h>
#include <string.h>

// ע��:����SCI IP��bclk������������, ǰ��ʱDLL����<2ʱ�������޷���ӡ
// Ϊ�������в���������qx_sci.c���������, ���ﲻ�������sci�⺯��
void StdOutInitA()
{
    CpuSysRegs->PCLKCR5.bit.SCIA = 1;
    while (SciaRegs->USR.bit.BUSY)
        ;
    SciaRegs->LCR.bit.DLAB = 1; // ���������ý���
    SciaRegs->DLH          = 0; // �������������ָ�16λ

    // set bandrate to 921600 at 50Mhz
    // bandrate = SYSTEM_CLOCK / DLL.(DLF/16*10) * 16)
    SciaRegs->DLL = 3; // �������������ֵ�16λ
    SciaRegs->DLF = 6; // ������С������

    SciaRegs->LCR.bit.DLAB = 0;              // ��������������
    SciaRegs->LCR.bit.PEN  = 0;              // ����λ = NONE
    SciaRegs->LCR.bit.DLS  = SCI_DATA_8BITS; // ����λ�� = 8
    SciaRegs->LCR.bit.STOP = SCI_STOP_BIT_1; // ֹͣλ = 1
}

void StdOutInitB()
{
    CpuSysRegs->PCLKCR5.bit.SCIB = 1;
    while (ScibRegs->USR.bit.BUSY)
        ;
    ScibRegs->LCR.bit.DLAB = 1; // ���������ý���
    ScibRegs->DLH          = 0; // �������������ָ�16λ

    // set bandrate to 921600 at 50Mhz
    // bandrate = SYSTEM_CLOCK / DLL.(DLF/16*10) * 16)
    ScibRegs->DLL = 3; // �������������ֵ�16λ
    ScibRegs->DLF = 6; // ������С������

    ScibRegs->LCR.bit.DLAB = 0;              // ��������������
    ScibRegs->LCR.bit.PEN  = 0;              // ����λ = NONE
    ScibRegs->LCR.bit.DLS  = SCI_DATA_8BITS; // ����λ�� = 8
    ScibRegs->LCR.bit.STOP = SCI_STOP_BIT_1; // ֹͣλ = 1
}

// �������� VCS or FPGA ����
void EndSimulation(void)
{
    // for VCS simulation end
    putchar(0x4);
#ifdef FGPA_TEST
    // for FPGA simulation end
    puts("FPGA End");
    exit(0);
#endif
}

// 1s ~= 500000 at 25Mhz cpu_clk
void simple_delay(u32 count)
{
    volatile int i = 0;
    for (i = 0; i < count; i++)
        ;
}

void common_reg_read_write(vu32 addr)
{
    u32 val = 0;

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
}

void verify_data_byte(u8 *buf1, u8 *buf2, u32 len)
{
    for (int i = 0; i < len; i++)
    {
        if (buf1[i] != buf2[i])
        {
            printf("verify_data error: buf1[%x]= %d, buf2[%d] = %d)\n", i, buf1[i], i, buf2[i]);
            break;
        }
    }
}

void verify_data_short(u16 *buf1, u16 *buf2, u32 len)
{
    for (int i = 0; i < len; i++)
    {
        if (buf1[i] != buf2[i])
        {
            printf("verify_data error: buf1[%x]= %d, buf2[%d] = %d)\n", i, buf1[i], i, buf2[i]);
            break;
        }
    }
}

void verify_data_word(u32 *buf1, u32 *buf2, u32 len)
{
    for (int i = 0; i < len; i++)
    {
        if (buf1[i] != buf2[i])
        {
            printf("verify_data error: buf1[%x]= %d, buf2[%d] = %d)\n", i, buf1[i], i, buf2[i]);
            break;
        }
    }
}

void buf_dump_byte(const char *head, const char *buf, int len)
{ // ��wireshack���Ƶĸ�ʽ��ӡ����, ��ҪΪ�˷������Ϣ�����͵���
    if (head)
        printf("%s\n", head);
    int i;
    printf("---------------------------------------------------------------------\n");
    printf("%08X ---| %02X ", 0, buf[0]);
    for (i = 1; i < len; ++i)
    {
        if (!(i % 16))
            printf("|\n%08X ---| ", i / 16 * 16);
        else if (!(i % 4))
            printf("| ");
        printf("%02X ", buf[i]);
    }
    if (!(i % 16))
        printf("|");
    printf("\n---------------------------------------------------------------------\n\n");
}

void buf_dump_short(const char *head, const short *buf, int len)
{ // ��wireshack���Ƶĸ�ʽ��ӡ����, ��ҪΪ�˷������Ϣ�����͵���
    if (head)
        printf("%s\n", head);
    int i;
    printf("%08X ---| %04X ", 0, buf[0]);
    for (i = 1; i < len; ++i)
    {
        if (!(i % 16))
            printf("|\n%08X ---| ", i / 16 * 16);
        else if (!(i % 4))
            printf("| ");
        printf("%04X ", buf[i]);
    }
    if (!(i % 16))
        printf("|");
    printf("\n");
}

void buf_dump_word(const char *head, const int *buf, int len)
{ // ��wireshack���Ƶĸ�ʽ��ӡ����, ��ҪΪ�˷������Ϣ�����͵���
    if (head)
        printf("%s\n", head);
    int i;
    printf("%08X ---| %08X ", 0, buf[0]);
    for (i = 1; i < len; ++i)
    {
        if (!(i % 16))
            printf("|\n%08X ---| ", i / 16 * 16);
        else if (!(i % 4))
            printf("| ");
        printf("%08X ", buf[i]);
    }
    if (!(i % 16))
        printf("|");
    printf("\n");
}

// =======================================================================================

#ifndef USE_SELF_PRINTF

// ʹ��ibc��ʵ��puts + printf�ض���
#include <sys/stat.h>
__attribute__((used)) int _write(int fd, char *ptr, int len)
{
    for (int i = 0; i < len; i++)
    {
#ifdef FGPA_TEST // FPGA��֤ʱ��ʹ�� SCIA ��Ϊ���Դ��ڴ�ӡ
#ifdef QX_C2000_CORE0
        while (!SciaRegs->LSR.bit.THRE) // wait send empty
            ;
        SciaRegs->THR = ptr[i];
        while (!SciaRegs->LSR.bit.TEMT) // wait send finish
            ;
#else
        while (!ScibRegs->LSR.bit.THRE) // wait send empty
            ;
        ScibRegs->THR = ptr[i];
        while (!ScibRegs->LSR.bit.TEMT) // wait send finish
            ;
#endif
#else // ʹ������Ĵ���ʵ�ִ�ӡ, ����ʱʹ��, ���Լ�����ٴ�ӡ�ٶ�
        HWREGB(0x007f0000) = c;
#endif
    }
    return len;
}

#else

// ��ʵ��puts+printf����(������libc��)
#include <stdarg.h>

inline void putchar(char c)
{
#ifdef FGPA_TEST // FPGA��֤ʱ��ʹ�� SCIA ��Ϊ���Դ��ڴ�ӡ
#ifdef QX_C2000_CORE0
    while (!SciaRegs->LSR.bit.THRE) // wait send empty
        ;
    SciaRegs->THR = c;
    while (!SciaRegs->LSR.bit.TEMT) // wait send finish
        ;
#else
    while (!ScibRegs->LSR.bit.THRE) // wait send empty
        ;
    ScibRegs->THR = c;
    while (!ScibRegs->LSR.bit.TEMT) // wait send finish
        ;
#endif
#else // ʹ������Ĵ���ʵ�ִ�ӡ, ����ʱʹ��, ���Լ�����ٴ�ӡ�ٶ�
    HWREGB(0x007f0000) = c;
#endif
}

void puts(const char *str)
{
    while (*str)
    {
        putchar(*str);
        str++;
    }
    putchar('\n');
}

// ����m^n
unsigned long m_pow_n(unsigned long m, unsigned long n)
{
    unsigned long i = 0, ret = 1;
    if (n < 0)
        return 0;
    for (i = 0; i < n; i++)
        ret *= m;
    return ret;
}

// ����ֵΪ��ӡ�ַ��ĸ���
// ֧��%d��%o, %x��%s��%c��%f��ֻ��ӡ6λ���֣�
int printf(const char *str, ...)
{
    if (str == NULL)
        return -1;

    unsigned int ret_num    = 0;           // ���ش�ӡ�ַ��ĸ���
    char *pStr              = (char *)str; // ָ��str
    int ArgIntVal           = 0;           // ��������
    unsigned long ArgHexVal = 0;           // ��ʮ������
    char *ArgStrVal         = NULL;        // �����ַ���
    double ArgFloVal        = 0.0;         // ���ܸ�����
    unsigned long val_seg   = 0;           // �����з�
    unsigned long val_temp  = 0;           // ��ʱ��������
    int cnt                 = 0;           // ���ݳ��ȼ���
    int i                   = 0;

    va_list pArgs;        // ����va_list����ָ�룬���ڴ洢�����ĵ�ַ
    va_start(pArgs, str); // ��ʼ��pArgs
    while (*pStr != '\0')
    {
        switch (*pStr)
        {
            case ' ':
            case '\r':
            case '\n':
                putchar(*pStr);
                ret_num++;
                break;
            case '\t':
                putchar(*pStr);
                ret_num += 4;
                break;
            case '%':
                pStr++;
                // % ��ʽ����
                switch (*pStr)
                {
                    case '%':
                        putchar('%'); // %%�����%
                        ret_num++;
                        pStr++;
                        continue;
#if 1
                    case 'c':
                        ArgIntVal = va_arg(pArgs, int); // %c�����char
                        putchar((char)ArgIntVal);
                        ret_num++;
                        pStr++;
                        continue;
                    case 's':
                        // �����ַ�
                        ArgStrVal = va_arg(pArgs, char *);
                        ret_num += (unsigned int)strlen(ArgStrVal);
                        while (*ArgStrVal)
                        {
                            putchar(*ArgStrVal);
                            ArgStrVal++;
                        }
                        pStr++;
                        continue;
#endif
#if 1
                    case 'x':
                        // ����16����
                        ArgHexVal = va_arg(pArgs, unsigned long);
                        val_seg   = ArgHexVal;
                        // ����ArgIntVal����
                        if (ArgHexVal)
                        {
                            while (val_seg)
                            {
                                cnt++;
                                val_seg /= 16;
                            }
                        }
                        else
                            cnt = 1; // ����0�ĳ���Ϊ1

                        ret_num += cnt; // �ַ��������������ĳ���
                        // ������תΪ�����ַ���ӡ
                        while (cnt)
                        {
                            val_seg = ArgHexVal / m_pow_n(16, cnt - 1);
                            ArgHexVal %= m_pow_n(16, cnt - 1);
                            if (val_seg <= 9)
                                putchar((char)val_seg + '0');
                            else
                            {
                                // putchar((char)val_seg - 10 + 'a'); //Сд��ĸ
                                putchar((char)val_seg - 10 + 'A');
                            }
                            cnt--;
                        }
                        pStr++;
                        continue;
#endif
#if 1
                    case 'd':
                        // ��������
                        ArgIntVal = va_arg(pArgs, int);
                        if (ArgIntVal < 0) // ���Ϊ������ӡ������
                        {
                            ArgIntVal = -ArgIntVal; // ȡ�෴��

                            putchar('-');
                            ret_num++;
                        }
                        val_seg = ArgIntVal; // ��ֵ�� val_seg��������
                        // ����ArgIntVal����
                        if (ArgIntVal)
                        {
                            while (val_seg)
                            {
                                cnt++;
                                val_seg /= 10;
                            }
                        }
                        else
                            cnt = 1; // ����0�ĳ���Ϊ1

                        ret_num += cnt; // �ַ��������������ĳ���

                        // ������תΪ�����ַ���ӡ
                        while (cnt)
                        {
                            val_seg = ArgIntVal / m_pow_n(10, cnt - 1);
                            ArgIntVal %= m_pow_n(10, cnt - 1);
                            putchar((char)val_seg + '0');
                            cnt--;
                        }
                        pStr++;
                        continue;
#endif
#if 0 // %o ��ӡ֧��
                    case 'o':
                        // ��������
                        ArgIntVal = va_arg(pArgs, int);
                        if (ArgIntVal < 0) // ���Ϊ������ӡ������
                        {
                            ArgIntVal = -ArgIntVal; // ȡ�෴��

                            putchar('-');
                            ret_num++;
                        }
                        val_seg = ArgIntVal; // ��ֵ�� val_seg��������
                        // ����ArgIntVal����
                        if (ArgIntVal)
                        {
                            while (val_seg)
                            {
                                cnt++;
                                val_seg /= 8;
                            }
                        }
                        else
                            cnt = 1; // ����0�ĳ���Ϊ1

                        ret_num += cnt; // �ַ��������������ĳ���

                        // ������תΪ�����ַ���ӡ
                        while (cnt)
                        {
                            val_seg = ArgIntVal / m_pow_n(8, cnt - 1);
                            ArgIntVal %= m_pow_n(8, cnt - 1);
                            putchar((char)val_seg + '0');
                            cnt--;
                        }
                        pStr++;
                        continue;
#endif
#if 0 // %b ��ӡ֧��
                    case 'b':
                        // ��������
                        ArgIntVal = va_arg(pArgs, int);
                        val_seg   = ArgIntVal;
                        // ����ArgIntVal����
                        if (ArgIntVal)
                        {
                            while (val_seg)
                            {
                                cnt++;
                                val_seg /= 2;
                            }
                        }
                        else
                            cnt = 1; // ����0�ĳ���Ϊ1

                        ret_num += cnt; // �ַ��������������ĳ���
                        // ������תΪ�����ַ���ӡ
                        while (cnt)
                        {
                            val_seg = ArgIntVal / m_pow_n(2, cnt - 1);
                            ArgIntVal %= m_pow_n(2, cnt - 1);
                            putchar((char)val_seg + '0');
                            cnt--;
                        }
                        pStr++;
                        continue;
#endif
#if 0 // %f ��ӡ֧��, �ᵼ�±�����������32K
                    case 'f':
                        // ���ո����� ����6ΪС��������ȡ��������
                        ArgFloVal = va_arg(pArgs, double);
                        val_seg   = (unsigned long)ArgFloVal; // ȡ��������
                        val_temp  = val_seg;                  // ��ʱ����������������
                        ArgFloVal = ArgFloVal - val_seg;      // �ó����µ�С������
                        // �����������ֳ���
                        if (val_seg)
                        {
                            while (val_seg)
                            {
                                cnt++;
                                val_seg /= 10;
                            }
                        }
                        else
                            cnt = 1;    // ����0�ĳ���Ϊ1
                        ret_num += cnt; // �ַ��������������ĳ���
                        // ������תΪ�����ַ���ӡ
                        while (cnt)
                        {
                            val_seg = val_temp / m_pow_n(10, cnt - 1);
                            val_temp %= m_pow_n(10, cnt - 1);
                            putchar((char)val_seg + '0');
                            cnt--;
                        }
                        // ��ӡС����
                        putchar('.');
                        ret_num++;
                        // ��ʼ���С������
                        ArgFloVal *= 1000000;
                        // printf("\r\n %f\r\n", ArgFloVal);
                        cnt      = 6;
                        val_temp = (int)ArgFloVal; // ȡ��������
                        while (cnt)
                        {
                            val_seg = val_temp / m_pow_n(10, cnt - 1);
                            val_temp %= m_pow_n(10, cnt - 1);
                            putchar((char)val_seg + '0');
                            cnt--;
                        }
                        ret_num += 6;
                        pStr++;
                        continue;
                    default: // % ƥ�����������ո�
                        putchar(' ');
                        ret_num++;
                        continue;
#endif
                }
            default:
                putchar(*pStr);
                ret_num++;
                break;
        }
        pStr++;
    }
    va_end(pArgs); // ����ȡ����

    return ret_num;
}

#endif
