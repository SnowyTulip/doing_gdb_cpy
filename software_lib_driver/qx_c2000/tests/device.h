#ifndef QX_DEVICE_H
#define QX_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

void Device_init(void);

int Device_verifyXTAL(float freq);
void SysCtl_enablePeripheralAll(void);
void SysCtl_disablePeripheralAll(void);
void __error__(const char *filename, uint32_t line);

#ifdef __cplusplus
}
#endif

#endif
