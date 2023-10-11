/**
 **************************************************************************
 * @file     qx_interrupt.c
 * @version  v1.0.0
 * @date     2023-12-30
 * @brief    contains all the functions for the inttrupt entery
 **************************************************************************
 */

#include "qx_define.h"
#include "qx_interrupt.h"

void __attribute__((weak)) exception_nc(void)
{
    while (1)
        ;
}

void __attribute__((weak)) pic_group_nc(void)
{
    while (1)
        ;
}

void __attribute__((weak)) adca1_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) adcb1_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) adcc1_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) xint1_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) xint2_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) timer0_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) wake_wdog_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) epwm1_tz_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) epwm2_tz_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) epwm3_tz_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) epwm4_tz_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) epwm5_tz_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) epwm6_tz_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) epwm7_tz_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) epwm8_tz_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) epwm1_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) epwm2_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) epwm3_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) epwm4_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) epwm5_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) epwm6_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) epwm7_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) epwm8_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) ecap1_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) ecap2_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) ecap3_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) ecap4_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) ecap5_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) ecap6_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) ecap7_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) ecap6_hrcal_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) ecap7_hrcal_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) eqep1_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) eqep2_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) sdfm1_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) sdfm1dr1_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) sdfm1dr2_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) sdfm1dr3_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) sdfm1dr4_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) spia_m_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) spia_s_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) spib_m_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) spib_s_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) dma_ch1_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) dma_ch2_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) dma_ch3_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) dma_ch4_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) dma_ch5_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) dma_ch6_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) fsitx_int1_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) fsitx_int2_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) fsirx_int1_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) fsirx_int2_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) dcc_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) i2ca_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) lina_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) pmbus_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) scia_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) scib_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) cana_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) canb_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) adca_evt_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) adca2_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) adca3_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) adca4_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) adcb_evt_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) adcb2_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) adcb3_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) adcb4_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) adcc_evt_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) adcc2_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) adcc3_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) adcc4_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) ipc_0_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) ipc_1_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) ipc_2_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) ipc_3_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) xint3_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) xint4_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) xint5_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) trace_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) wp_exp_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) timer1_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) timer2_isr(void)
{
    while (1)
        ;
}

void __attribute__((weak)) nmi_isr(void)
{
    while (1)
        ;
}

//*****************************************************************************
// Interrupt_initModule
//*****************************************************************************
void Interrupt_initModule(void)
{
    DINT;

    PieCtrlRegs->PIEIER1.all  = 0;
    PieCtrlRegs->PIEIER2.all  = 0;
    PieCtrlRegs->PIEIER3.all  = 0;
    PieCtrlRegs->PIEIER4.all  = 0;
    PieCtrlRegs->PIEIER5.all  = 0;
    PieCtrlRegs->PIEIER6.all  = 0;
    PieCtrlRegs->PIEIER7.all  = 0;
    PieCtrlRegs->PIEIER8.all  = 0;
    PieCtrlRegs->PIEIER9.all  = 0;
    PieCtrlRegs->PIEIER10.all = 0;
    PieCtrlRegs->PIEIER11.all = 0;
    PieCtrlRegs->PIEIER12.all = 0;

    PieCtrlRegs->IER.all = 0;

    EINT;
}

//*****************************************************************************
// Interrupt_enable
//*****************************************************************************
void Interrupt_enable(INTERRUPT_Type interruptNumber)
{
    int intGroup;
    int groupMask;

    intGroup  = ((interruptNumber & 0xFF00) >> 8) - 1;
    groupMask = 1 << intGroup;

    if (intGroup <= 12)
        HWREGH(((int)&PieCtrlRegs->PIEIER1 + (intGroup * 4))) |= (1 << ((interruptNumber & 0xFF) - 1));

    PieCtrlRegs->IER.all |= (1 << intGroup);
}

//*****************************************************************************
// Interrupt_disable
//*****************************************************************************
void Interrupt_disable(INTERRUPT_Type interruptNumber)
{
    int intGroup;
    int groupMask;

    intGroup  = ((interruptNumber & 0xFF00) >> 8) - 1;
    groupMask = 1 << intGroup;

    if (intGroup <= 12)
        HWREGH(((int)&PieCtrlRegs->PIEIER1 + (intGroup * 4))) |= 1 << ((interruptNumber & 0xFF) - 1);
    else
        PieCtrlRegs->IER.all &= ~(1 << intGroup);
}
