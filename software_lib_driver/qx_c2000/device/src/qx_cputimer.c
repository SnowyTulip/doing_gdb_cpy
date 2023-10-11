#include "qx_cputimer.h"

void CPUTimer_initTimer(CPUTimerReg_types *timer, timer_mode_type mode, u32 value)
{
    CPUTimer_disableTimer(timer);
    CPUTimer_setMode(timer, mode);
    CPUTimer_reload(timer, value);
}

void CPUTimer_initPwm(CPUTimerReg_types *timer, TimerNLoadCount2_types *timerPwmReg, timer_mode_type mode,
    u32 high_period, u32 low_period)
{
    CPUTimer_disableTimer(timer);
    CPUTimer_setMode(timer, mode);
    CPUTimer_enablePwm(timer);
    CPUTimer_setPwmHighPeriod(timerPwmReg, high_period);
    CPUTimer_reload(timer, low_period);
}
