#ifndef QX_COMMON_H
#define QX_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "devicelib.h"
#include "device.h"

#define TEST_WDG

// ��Ҫʹ��FPGA��֤ʱ�����ú�, �����޷�ʹ�ô��ڴ�ӡ
// #define FGPA_TEST

#define USE_SELF_PRINTF

#ifndef USE_SELF_PRINTF
#include <stdio.h>
#else
// ��ʵ��putchar puts��printf����
void putchar(char c);
void puts(const char *str);
int printf(const char *str, ...);
#endif

// ���ڴ�ӡ��ʼ�������ͷ����Զ���������
void StdOutInitA();
void StdOutInitB();
void EndSimulation(void);

// һЩ��֤���õ�ͨ�ú������װ
void simple_delay(u32 count);
void verify_data_byte(u8 *buf1, u8 *buf2, u32 len);
void verify_data_short(u16 *buf1, u16 *buf2, u32 len);
void verify_data_word(u32 *buf1, u32 *buf2, u32 len);
void buf_dump_byte(const char *head, const char *buf, int len);
void buf_dump_short(const char *head, const short *buf, int len);
void buf_dump_word(const char *head, const int *buf, int len);

// ����ģ����֤�������
void test_flash(void);
void test_sysctl(void);
void test_global(void);
void test_sci(void);
void test_can(void);
void test_dma(void);
void test_ecap(void);
void test_epwm(void);
void test_eqep(void);
void test_spi(void);
void test_ipc(void);
void test_wdg(void);
void test_timer(void);
void test_adc(void);
void test_dac(void);
void test_gpio(void);
void test_xbar(void);
void test_sdfm(void);
void test_hrcap(void);
void test_mem(void);
void test_fsi(void);
void test_i2c(void);
void test_pll(void);
void test_isr(void);
void test_dcc(void);
void test_asys(void);
void test_pmbus(void);
void test_cmpss(void);

#ifdef __cplusplus
}
#endif

#endif
