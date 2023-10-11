#include "common.h"

#include <stdlib.h>
#include <string.h>

// 注意:由于SCI IP的bclk产生机制问题, 前仿时DLL参数<2时将导致无法打印
// 为避免所有测试用例对qx_sci.c库产生依赖, 这里不建议调用sci库函数
void StdOutInitA()
{
    CpuSysRegs->PCLKCR5.bit.SCIA = 1;
    while (SciaRegs->USR.bit.BUSY)
        ;
    SciaRegs->LCR.bit.DLAB = 1; // 波特率配置解锁
    SciaRegs->DLH          = 0; // 波特率整数部分高16位

    // set bandrate to 921600 at 50Mhz
    // bandrate = SYSTEM_CLOCK / DLL.(DLF/16*10) * 16)
    SciaRegs->DLL = 3; // 波特率整数部分低16位
    SciaRegs->DLF = 6; // 波特率小数部分

    SciaRegs->LCR.bit.DLAB = 0;              // 波特率配置上锁
    SciaRegs->LCR.bit.PEN  = 0;              // 检验位 = NONE
    SciaRegs->LCR.bit.DLS  = SCI_DATA_8BITS; // 数据位宽 = 8
    SciaRegs->LCR.bit.STOP = SCI_STOP_BIT_1; // 停止位 = 1
}

void StdOutInitB()
{
    CpuSysRegs->PCLKCR5.bit.SCIB = 1;
    while (ScibRegs->USR.bit.BUSY)
        ;
    ScibRegs->LCR.bit.DLAB = 1; // 波特率配置解锁
    ScibRegs->DLH          = 0; // 波特率整数部分高16位

    // set bandrate to 921600 at 50Mhz
    // bandrate = SYSTEM_CLOCK / DLL.(DLF/16*10) * 16)
    ScibRegs->DLL = 3; // 波特率整数部分低16位
    ScibRegs->DLF = 6; // 波特率小数部分

    ScibRegs->LCR.bit.DLAB = 0;              // 波特率配置上锁
    ScibRegs->LCR.bit.PEN  = 0;              // 检验位 = NONE
    ScibRegs->LCR.bit.DLS  = SCI_DATA_8BITS; // 数据位宽 = 8
    ScibRegs->LCR.bit.STOP = SCI_STOP_BIT_1; // 停止位 = 1
}

// 主动结束 VCS or FPGA 仿真
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
{ // 以wireshack相似的格式打印数据, 主要为了方便包信息分析和调试
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
{ // 以wireshack相似的格式打印数据, 主要为了方便包信息分析和调试
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
{ // 以wireshack相似的格式打印数据, 主要为了方便包信息分析和调试
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

// 使用ibc库实现puts + printf重定向
#include <sys/stat.h>
__attribute__((used)) int _write(int fd, char *ptr, int len)
{
    for (int i = 0; i < len; i++)
    {
#ifdef FGPA_TEST // FPGA验证时需使用 SCIA 作为调试串口打印
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
#else // 使用特殊寄存器实现打印, 仿真时使用, 可以极大加速打印速度
        HWREGB(0x007f0000) = c;
#endif
    }
    return len;
}

#else

// 自实现puts+printf函数(不依赖libc库)
#include <stdarg.h>

inline void putchar(char c)
{
#ifdef FGPA_TEST // FPGA验证时需使用 SCIA 作为调试串口打印
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
#else // 使用特殊寄存器实现打印, 仿真时使用, 可以极大加速打印速度
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

// 计算m^n
unsigned long m_pow_n(unsigned long m, unsigned long n)
{
    unsigned long i = 0, ret = 1;
    if (n < 0)
        return 0;
    for (i = 0; i < n; i++)
        ret *= m;
    return ret;
}

// 返回值为打印字符的个数
// 支持%d，%o, %x，%s，%c，%f（只打印6位数字）
int printf(const char *str, ...)
{
    if (str == NULL)
        return -1;

    unsigned int ret_num    = 0;           // 返回打印字符的个数
    char *pStr              = (char *)str; // 指向str
    int ArgIntVal           = 0;           // 接收整型
    unsigned long ArgHexVal = 0;           // 接十六进制
    char *ArgStrVal         = NULL;        // 接收字符型
    double ArgFloVal        = 0.0;         // 接受浮点型
    unsigned long val_seg   = 0;           // 数据切分
    unsigned long val_temp  = 0;           // 临时保存数据
    int cnt                 = 0;           // 数据长度计数
    int i                   = 0;

    va_list pArgs;        // 定义va_list类型指针，用于存储参数的地址
    va_start(pArgs, str); // 初始化pArgs
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
                // % 格式解析
                switch (*pStr)
                {
                    case '%':
                        putchar('%'); // %%，输出%
                        ret_num++;
                        pStr++;
                        continue;
#if 1
                    case 'c':
                        ArgIntVal = va_arg(pArgs, int); // %c，输出char
                        putchar((char)ArgIntVal);
                        ret_num++;
                        pStr++;
                        continue;
                    case 's':
                        // 接收字符
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
                        // 接收16进制
                        ArgHexVal = va_arg(pArgs, unsigned long);
                        val_seg   = ArgHexVal;
                        // 计算ArgIntVal长度
                        if (ArgHexVal)
                        {
                            while (val_seg)
                            {
                                cnt++;
                                val_seg /= 16;
                            }
                        }
                        else
                            cnt = 1; // 数字0的长度为1

                        ret_num += cnt; // 字符个数加上整数的长度
                        // 将整数转为单个字符打印
                        while (cnt)
                        {
                            val_seg = ArgHexVal / m_pow_n(16, cnt - 1);
                            ArgHexVal %= m_pow_n(16, cnt - 1);
                            if (val_seg <= 9)
                                putchar((char)val_seg + '0');
                            else
                            {
                                // putchar((char)val_seg - 10 + 'a'); //小写字母
                                putchar((char)val_seg - 10 + 'A');
                            }
                            cnt--;
                        }
                        pStr++;
                        continue;
#endif
#if 1
                    case 'd':
                        // 接收整型
                        ArgIntVal = va_arg(pArgs, int);
                        if (ArgIntVal < 0) // 如果为负数打印，负号
                        {
                            ArgIntVal = -ArgIntVal; // 取相反数

                            putchar('-');
                            ret_num++;
                        }
                        val_seg = ArgIntVal; // 赋值给 val_seg处理数据
                        // 计算ArgIntVal长度
                        if (ArgIntVal)
                        {
                            while (val_seg)
                            {
                                cnt++;
                                val_seg /= 10;
                            }
                        }
                        else
                            cnt = 1; // 数字0的长度为1

                        ret_num += cnt; // 字符个数加上整数的长度

                        // 将整数转为单个字符打印
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
#if 0 // %o 打印支持
                    case 'o':
                        // 接收整型
                        ArgIntVal = va_arg(pArgs, int);
                        if (ArgIntVal < 0) // 如果为负数打印，负号
                        {
                            ArgIntVal = -ArgIntVal; // 取相反数

                            putchar('-');
                            ret_num++;
                        }
                        val_seg = ArgIntVal; // 赋值给 val_seg处理数据
                        // 计算ArgIntVal长度
                        if (ArgIntVal)
                        {
                            while (val_seg)
                            {
                                cnt++;
                                val_seg /= 8;
                            }
                        }
                        else
                            cnt = 1; // 数字0的长度为1

                        ret_num += cnt; // 字符个数加上整数的长度

                        // 将整数转为单个字符打印
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
#if 0 // %b 打印支持
                    case 'b':
                        // 接收整型
                        ArgIntVal = va_arg(pArgs, int);
                        val_seg   = ArgIntVal;
                        // 计算ArgIntVal长度
                        if (ArgIntVal)
                        {
                            while (val_seg)
                            {
                                cnt++;
                                val_seg /= 2;
                            }
                        }
                        else
                            cnt = 1; // 数字0的长度为1

                        ret_num += cnt; // 字符个数加上整数的长度
                        // 将整数转为单个字符打印
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
#if 0 // %f 打印支持, 会导致编译后代码增大32K
                    case 'f':
                        // 接收浮点型 保留6为小数，不采取四舍五入
                        ArgFloVal = va_arg(pArgs, double);
                        val_seg   = (unsigned long)ArgFloVal; // 取整数部分
                        val_temp  = val_seg;                  // 临时保存整数部分数据
                        ArgFloVal = ArgFloVal - val_seg;      // 得出余下的小数部分
                        // 计算整数部分长度
                        if (val_seg)
                        {
                            while (val_seg)
                            {
                                cnt++;
                                val_seg /= 10;
                            }
                        }
                        else
                            cnt = 1;    // 数字0的长度为1
                        ret_num += cnt; // 字符个数加上整数的长度
                        // 将整数转为单个字符打印
                        while (cnt)
                        {
                            val_seg = val_temp / m_pow_n(10, cnt - 1);
                            val_temp %= m_pow_n(10, cnt - 1);
                            putchar((char)val_seg + '0');
                            cnt--;
                        }
                        // 打印小数点
                        putchar('.');
                        ret_num++;
                        // 开始输出小数部分
                        ArgFloVal *= 1000000;
                        // printf("\r\n %f\r\n", ArgFloVal);
                        cnt      = 6;
                        val_temp = (int)ArgFloVal; // 取整数部分
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
                    default: // % 匹配错误，暂输出空格
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
    va_end(pArgs); // 结束取参数

    return ret_num;
}

#endif
