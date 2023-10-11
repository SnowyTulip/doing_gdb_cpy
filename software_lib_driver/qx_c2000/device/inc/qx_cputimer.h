/**
 **************************************************************************
 * @file     qx_cputimer.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_CPUTIMER_H
#define QX_CPUTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"

// INFO: LoadCount2 register is no used, No define by default

typedef enum
{
    FREE_RUNNING = 0U,
    USER_DEFINED = 1U,
} timer_mode_type;

typedef struct
{
    vu32 LoadCount;    /* offset: 0x00 */
    vu32 CurrentValue; /* offset: 0x04 */

    union /* offset: 0x08 */
    {
        vu32 ControlReg;
        struct
        {
            vu32 enable   : 1;  /* [0] */
            vu32 mode     : 1;  /* [1] */
            vu32 int_mask : 1;  /* [2] */
            vu32 pwm      : 1;  /* [3] */
            vu32 rsvd     : 28; /* [31:4]*/
        } ControlReg_bit;
    };

    union /* offset: 0x0C */
    {
        vu32 EOI;
        struct
        {
            vu32 EOI  : 1;  /* [0] */
            vu32 rsvd : 31; /* [31:1] */
        } EOI_bit;
    };

    union /* offset: 0x10 */
    {
        vu32 IntStatus;
        struct
        {
            vu32 int_status : 1;  /* [0] */
            vu32 rsvd       : 31; /* [31:1] */
        } IntStatus_bit;
    };
} CPUTimerReg_types;

typedef struct
{
    union /* offset: 0x00 */
    {
        vu32 IntStatus;
        struct
        {
            vu32 IntStatus : 3;  /* [2:0] */
            vu32 rsvd      : 29; /* [31:3] */
        } IntStatus_bit;
    };

    union /* offset: 0x04 */
    {
        vu32 EOI;
        struct
        {
            vu32 EOI  : 3;  /* [2:0] */
            vu32 rsvd : 29; /* [31:3] */
        } EOI_bit;
    };

    union /* offset: 0x08 */
    {
        vu32 RawIntStatus;
        struct
        {
            vu32 RawIntStatus : 3;  /* [2:0] */
            vu32 rsvd         : 29; /* [31:3] */
        } RawIntStatus_bit;
    };
    vu32 CompVersion; /* offset: 0x0C */
} CPUTimerSys_types;

typedef struct
{
    vu32 LoadCount2;
} TimerNLoadCount2_types;

#define CPUTimer0Regs    ((CPUTimerReg_types *)(CPUTIMER_BASE + 0x00U))
#define CPUTimer1Regs    ((CPUTimerReg_types *)(CPUTIMER_BASE + 0x14U))
#define CPUTimer2Regs    ((CPUTimerReg_types *)(CPUTIMER_BASE + 0x28U))
#define CPUTimer0PwmRegs ((TimerNLoadCount2_types *)(CPUTIMER_BASE + 0xb0U))
#define CPUTimer1PwmRegs ((TimerNLoadCount2_types *)(CPUTIMER_BASE + 0xb4U))
#define CPUTimer2PwmRegs ((TimerNLoadCount2_types *)(CPUTIMER_BASE + 0xb8U))
#define CPUTimerSysRegs  ((CPUTimerSys_types *)(CPUTIMER_BASE + 0xa0U))

STATIC_INLINE void CPUTimer_enableTimer(CPUTimerReg_types *timer)
{
    timer->ControlReg_bit.enable = 1;
}

STATIC_INLINE void CPUTimer_disableTimer(CPUTimerReg_types *timer)
{
    timer->ControlReg_bit.enable = 0;
}

STATIC_INLINE void CPUTimer_setMode(CPUTimerReg_types *timer, timer_mode_type mode)
{
    timer->ControlReg_bit.mode = mode;
}

STATIC_INLINE void CPUTimer_enableInterrupt(CPUTimerReg_types *timer)
{
    timer->ControlReg_bit.int_mask = 0;
}

STATIC_INLINE void CPUTimer_disableInterrupt(CPUTimerReg_types *timer)
{
    timer->ControlReg_bit.int_mask = 1;
}

STATIC_INLINE void CPUTimer_clearInterrupt(CPUTimerReg_types *timer)
{
    u32 TimerEOI = timer->EOI_bit.EOI;
}

STATIC_INLINE void CPUTimer_clearALLInterrupt(void)
{
    u32 TimerALLEOI = CPUTimerSysRegs->EOI_bit.EOI;
}

STATIC_INLINE void CPUTimer_reload(CPUTimerReg_types *timer, u32 time_value)
{
    timer->LoadCount = time_value;
}

STATIC_INLINE void CPUTimer_enablePwm(CPUTimerReg_types *timer)
{
    timer->ControlReg_bit.pwm = 1;
}

STATIC_INLINE void CPUTimer_disablePwm(CPUTimerReg_types *timer)
{
    timer->ControlReg_bit.pwm = 0;
}

STATIC_INLINE void CPUTimer_setPwmHighPeriod(TimerNLoadCount2_types *timerPwmReg, u32 time_value)
{
    timerPwmReg->LoadCount2 = time_value;
}

void CPUTimer_initTimer(CPUTimerReg_types *timer, timer_mode_type mode, u32 value);
void CPUTimer_initPwm(CPUTimerReg_types *timer, TimerNLoadCount2_types *timerPwmReg, timer_mode_type mode,
    u32 high_period, u32 low_period);

#endif
