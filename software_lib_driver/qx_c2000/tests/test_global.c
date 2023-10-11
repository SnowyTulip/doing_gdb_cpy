#include "common.h"

void test_global(void)
{
#if 0
    puts("printf test 1...");
    printf(0, 123);
    printf("%\n");
    printf("%%x\n", 0x123);
    printf("hex(0x0)=%x\n", 0x0);
    printf("hex(0x100)=%x\n", 0x100);
    printf("hex(0x1234)=%x\n", 0x1234);
    printf("hex(0x7fffffff)=0x%x\n", 0x7fffffff);
    printf("hex(0xffffffff)=0x%x\n", 0xffffffff);
    printf("str=%s\n", "hello");
    printf("%s(str)\n", "hello");
    printf("ch =%c\n", 'a');
    printf("%c(ch)\n", 'a');
#endif

#if 0
    puts("printf test 2...");
    printf("%d(int0)\n", 0);
    printf("%d(int100)\n", 100);
    printf("int(-123) =%d\n", -123);
    printf("%d(int 123)\n", 123);
    printf("%d(int 0x1234=4660)\n", 0x1234);
    printf("oct %o(int 0x1234=011064)\n", 0x1234);
    printf("oct %o(int 0x12345678=02215053170)\n", 0x12345678);
    printf("bin(0xff)=%b\n", 0xff);
    printf("%b(bin 0xff)\n", 0xff);
#endif

#if 0
  float v = 3.1415926;
  printf("%f\n", v);
#endif
}
