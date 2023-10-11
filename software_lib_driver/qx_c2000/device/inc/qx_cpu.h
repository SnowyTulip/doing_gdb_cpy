/**
 **************************************************************************
 * @file     qx_cpu.h
 * @version  v1.0.0
 * @date     2023-12-30
 **************************************************************************
 */

#ifndef QX_CPU_H
#define QX_CPU_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __interrupt
#define __interrupt __attribute__((interrupt))
#endif

#define INTM_ADDR 0x007f0720U

// Define to enable interrupts
#ifndef EINT
#define EINT ((*((short *)(INTM_ADDR))) = 0)
#endif

// Define to disable interrupts
#ifndef DINT
#define DINT ((*((short *)(INTM_ADDR))) = 1)
#endif

// Define to enable debug events
#ifndef ERTM
#define ERTM // __asm(" clrc DBGM")
#endif

// Define to disable debug events
#ifndef DRTM
#define DRTM // __asm(" setc DBGM")
#endif

// Define to allow writes to protected registers
#ifndef EALLOW
#define EALLOW // __eallow()
#endif

// Define to disable writes to protected registers
#ifndef EDIS
#define EDIS // __edis()
#endif

// Define for emulation stop
#ifndef ESTOP0
#define ESTOP0 // __asm(" ESTOP0")
#endif

// Define for emulation stop
#ifndef ESTOP1
#define ESTOP1 // __asm(" ESTOP1")
#endif

// Define for no operation
#ifndef NOP
#define NOP __builtin_dsp_nop()
#endif

// Define for putting processor into a low-power mode
#ifndef IDLE
#define IDLE __builtin_dsp_idle()
#endif

extern void __eallow(void);
extern void __edis(void);

#ifdef __cplusplus
}
#endif

#endif // CPU_H
