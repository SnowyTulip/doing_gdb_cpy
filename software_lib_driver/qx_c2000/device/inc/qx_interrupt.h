/**
 **************************************************************************
 * @file     qx_interrupt.h
 * @version  v1.0.0
 * @date     2023-12-30
 **************************************************************************
 */

#ifndef QX_INTERRUPT_H
#define QX_INTERRUPT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_types.h"

//---------------------------------------------------------------------------
// Except Register Bit Definitions:
//---------------------------------------------------------------------------

struct EXP_REGS
{
    vu32 rsvd;  // Reserved,      offset:0x00
    vu32 RD;    // RD Register,   offset:0x04
    vu32 RS;    // RS Register,   offset:0x08
    vu32 RT;    // RT Register,   offset:0x0C
    vu32 RX;    // RX Register,   offset:0x10
    vu32 IMM;   // IMM Register,  offset:0x14
    vu32 EPCR;  // EPCR Register, offset:0x18
    vu32 rsvd1; // Reserved,      offset:0x1C
    vu32 INTM;  // INTM Register, offset:0x20
};

#define ExpRegs ((struct EXP_REGS *)EXP_BASE)

//---------------------------------------------------------------------------
// PIC_CTRL Register Bit Definitions:
//---------------------------------------------------------------------------

struct PIC_BITS
{ // bits description
    vu32 GROUP1  : 1;
    vu32 GROUP2  : 1;
    vu32 GROUP3  : 1;
    vu32 GROUP4  : 1;
    vu32 GROUP5  : 1;
    vu32 GROUP6  : 1;
    vu32 GROUP7  : 1;
    vu32 GROUP8  : 1;
    vu32 GROUP9  : 1;
    vu32 GROUP10 : 1;
    vu32 GROUP11 : 1;
    vu32 GROUP12 : 1;
    vu32 TIMER1  : 1;
    vu32 TIMER2  : 1;
    vu32 NMI     : 1;
};

union PIC_REG
{
    vu32 all;
    struct PIC_BITS bit;
};

struct PIE_BITS
{                    // bits description
    vu32 INTx1  : 1; // 0 Enable for Interrupt 1.1
    vu32 INTx2  : 1; // 1 Enable for Interrupt 1.2
    vu32 INTx3  : 1; // 2 Enable for Interrupt 1.3
    vu32 INTx4  : 1; // 3 Enable for Interrupt 1.4
    vu32 INTx5  : 1; // 4 Enable for Interrupt 1.5
    vu32 INTx6  : 1; // 5 Enable for Interrupt 1.6
    vu32 INTx7  : 1; // 6 Enable for Interrupt 1.7
    vu32 INTx8  : 1; // 7 Enable for Interrupt 1.8
    vu32 INTx9  : 1; // 8 Enable for Interrupt 1.9
    vu32 INTx10 : 1; // 9 Enable for Interrupt 1.10
    vu32 INTx11 : 1; // 10 Enable for Interrupt 1.11
    vu32 INTx12 : 1; // 11 Enable for Interrupt 1.12
    vu32 INTx13 : 1; // 12 Enable for Interrupt 1.13
    vu32 INTx14 : 1; // 13 Enable for Interrupt 1.14
    vu32 INTx15 : 1; // 14 Enable for Interrupt 1.15
    vu32 INTx16 : 1; // 15 Enable for Interrupt 1.16
};

union PIE_REG
{
    vu32 all;
    struct PIE_BITS bit;
};

struct PIE_CTRL_REGS
{
    vu32 rsvd0;             // offset:0x00
    union PIC_REG IER;      // Interrupt Enable Register, offset:0x04
    vu32 rsvd1;             // offset: 0x08
    union PIE_REG PIEIER1;  // Interrupt Group 1 Enable Register, offset:0x0C
    union PIE_REG PIEIER2;  // Interrupt Group 2 Enable Register, offset:0x10
    union PIE_REG PIEIER3;  // Interrupt Group 3 Enable Register, offset:0x14
    union PIE_REG PIEIER4;  // Interrupt Group 4 Enable Register, offset:0x18
    union PIE_REG PIEIER5;  // Interrupt Group 5 Enable Register offset:0x1C
    union PIE_REG PIEIER6;  // Interrupt Group 6 Enable Register, offset:0x20
    union PIE_REG PIEIER7;  // Interrupt Group 7 Enable Register, offset:0x24
    union PIE_REG PIEIER8;  // Interrupt Group 8 Enable Register, offset:0x28
    union PIE_REG PIEIER9;  // Interrupt Group 9 Enable Register, offset:0x2C
    union PIE_REG PIEIER10; // Interrupt Group 10 Enable Register, offset:0x30
    union PIE_REG PIEIER11; // Interrupt Group 11 Enable Register, offset:0x34
    union PIE_REG PIEIER12; // Interrupt Group 12 Enable Register, offset:0x38
    union PIC_REG IER_RET;  // Interrupt Enable Return Register, offset:0x3C
};

#define PieCtrlRegs ((struct PIE_CTRL_REGS *)PIECTRL_BASE)

//*****************************************************************************
// IER  BIT Numbers define
//*****************************************************************************

#define PIC_GROUP1  0x0001
#define PIC_GROUP2  0x0002
#define PIC_GROUP3  0x0004
#define PIC_GROUP4  0x0008
#define PIC_GROUP5  0x0010
#define PIC_GROUP6  0x0020
#define PIC_GROUP7  0x0040
#define PIC_GROUP8  0x0080
#define PIC_GROUP9  0x0100
#define PIC_GROUP10 0x0200
#define PIC_GROUP11 0x0400
#define PIC_GROUP12 0x0800
#define PIC_TIMER1  0x1000
#define PIC_TIMER2  0x2000

//*****************************************************************************
// PIEIER  BIT Numbers define
//*****************************************************************************

// Lower PIE Group 1
#define PIE_BIT_TRACE     0x0001 // 1.1 - Debug Trace Interrupt
#define PIE_BIT_WP_EXP    0x0002 // 1.2 - Debug WatchPoint Interrupt
#define PIE_BIT_ADCA1     0x0004 // 1.3 - ADCA Interrupt 1
#define PIE_BIT_ADCB1     0x0008 // 1.4 - ADCB Interrupt 1
#define PIE_BIT_ADCC1     0x0010 // 1.5 - ADCC Interrupt 1
#define PIE_BIT_XINT1     0x0020 // 1.6 - XINT1 Interrupt
#define PIE_BIT_XINT2     0x0040 // 1.7 - XINT2 Interrupt
#define PIE_BIT_TIMER0    0x0080 // 1.9 - Timer 0 Interrupt
#define PIE_BIT_WAKE_WDOG 0x0100 // 1.10 - Halt Wakeup/Watchdog Interrupt

// Lower PIE Group 2
#define PIE_BIT_EPWM1_TZ 0x0001 // 2.1 - ePWM1 Trip Zone Interrupt
#define PIE_BIT_EPWM2_TZ 0x0002 // 2.2 - ePWM2 Trip Zone Interrupt
#define PIE_BIT_EPWM3_TZ 0x0004 // 2.3 - ePWM3 Trip Zone Interrupt
#define PIE_BIT_EPWM4_TZ 0x0008 // 2.4 - ePWM4 Trip Zone Interrupt
#define PIE_BIT_EPWM5_TZ 0x0010 // 2.5 - ePWM5 Trip Zone Interrupt
#define PIE_BIT_EPWM6_TZ 0x0020 // 2.6 - ePWM6 Trip Zone Interrupt
#define PIE_BIT_EPWM7_TZ 0x0040 // 2.7 - ePWM7 Trip Zone Interrupt
#define PIE_BIT_EPWM8_TZ 0x0080 // 2.8 - ePWM8 Trip Zone Interrupt

// Lower PIE Group 3
#define PIE_BIT_EPWM1 0x0001 // 3.1 - ePWM1 Interrupt
#define PIE_BIT_EPWM2 0x0002 // 3.2 - ePWM2 Interrupt
#define PIE_BIT_EPWM3 0x0004 // 3.3 - ePWM3 Interrupt
#define PIE_BIT_EPWM4 0x0008 // 3.4 - ePWM4 Interrupt
#define PIE_BIT_EPWM5 0x0010 // 3.5 - ePWM5 Interrupt
#define PIE_BIT_EPWM6 0x0020 // 3.6 - ePWM6 Interrupt
#define PIE_BIT_EPWM7 0x0040 // 3.7 - ePWM7 Interrupt
#define PIE_BIT_EPWM8 0x0080 // 3.8 - ePWM8 Interrupt

// Lower PIE Group 4
#define PIE_BIT_ECAP1       0x0001 // 4.1 - eCAP1 Interrupt
#define PIE_BIT_ECAP2       0x0002 // 4.2 - eCAP2 Interrupt
#define PIE_BIT_ECAP3       0x0004 // 4.3 - eCAP3 Interrupt
#define PIE_BIT_ECAP4       0x0008 // 4.4 - eCAP4 Interrupt
#define PIE_BIT_ECAP5       0x0010 // 4.5 - eCAP5 Interrupt
#define PIE_BIT_ECAP6       0x0020 // 4.6 - eCAP6 Interrupt
#define PIE_BIT_ECAP7       0x0040 // 4.7 - eCAP7 Interrupt
#define PIE_BIT_ECAP6_HRCAL 0x2000 // 4.14 - eCAP6_HRCAL Interrupt
#define PIE_BIT_ECAP7_HRCAL 0x4000 // 4.15 - eCAP7_HRCAL Interrupt

// Lower PIE Group 5
#define PIE_BIT_EQEP1    0x0001 // 5.1 - eQEP1 Interrupt
#define PIE_BIT_EQEP2    0x0002 // 5.2 - eQEP2 Interrupt
#define PIE_BIT_SDFM1    0x0100 // 5.9 - SDFM1 Interrupt
#define PIE_BIT_SDFM1DR1 0x1000 // 5.13 - SDFM1DR1 Interrupt
#define PIE_BIT_SDFM1DR2 0x2000 // 5.14 - SDFM1DR2 Interrupt
#define PIE_BIT_SDFM1DR3 0x4000 // 5.15 - SDFM1DR3 Interrupt
#define PIE_BIT_SDFM1DR4 0x8000 // 5.16 - SDFM1DR4 Interrupt

// Lower PIE Group 6
#define PIE_BIT_SPIA_RX 0x0001 // 6.1 - SPIA Receive Interrupt
#define PIE_BIT_SPIA_TX 0x0002 // 6.2 - SPIA Transmit Interrupt
#define PIE_BIT_SPIB_RX 0x0004 // 6.3 - SPIB Receive Interrupt
#define PIE_BIT_SPIB_TX 0x0008 // 6.4 - SPIB Transmit Interrupt

// Lower PIE Group 7
#define PIE_BIT_DMA_CH1    0x0001 // 7.1 - DMA Channel 1 Interrupt
#define PIE_BIT_DMA_CH2    0x0002 // 7.2 - DMA Channel 2 Interrupt
#define PIE_BIT_DMA_CH3    0x0004 // 7.3 - DMA Channel 3 Interrupt
#define PIE_BIT_DMA_CH4    0x0008 // 7.4 - DMA Channel 4 Interrupt
#define PIE_BIT_DMA_CH5    0x0010 // 7.5 - DMA Channel 5 Interrupt
#define PIE_BIT_DMA_CH6    0x0020 // 7.6 - DMA Channel 6 Interrupt
#define PIE_BIT_FSITX_INT1 0x0400 // 7.11 - FSITXA_INT1 Interrupt
#define PIE_BIT_FSITX_INT2 0x0800 // 7.12 - FSITXA_INT2 Interrupt
#define PIE_BIT_FSIRX_INT1 0x1000 // 7.13 - FSIRXA_INT1 Interrupt
#define PIE_BIT_FSIRX_INT2 0x2000 // 7.14 - FSIRXA_INT2 Interrupt
#define PIE_BIT_DCC        0x8000 // 7.16 - DCC Interrupt

// Lower PIE Group 8
#define PIE_BIT_I2CA   0x0001 // 8.1 - I2CA Interrupt 1
#define PIE_BIT_LINA   0x0100 // 8.9 - LINA Interrupt0
#define PIE_BIT_PMBUSA 0x1000 // 8.13 - PMBUSA Interrupt

// Lower PIE Group 9
#define PIE_BIT_SCIA 0x0001 // 9.1 - SCIA Interrupt
#define PIE_BIT_SCIB 0x0002 // 9.2 - SCIB Interrupt
#define PIE_BIT_CANA 0x0010 // 9.5 - CANA Interrupt
#define PIE_BIT_CANB 0x0020 // 9.6 - CANB Interrupt

// Lower PIE Group 10
#define PIE_BIT_ADCA_EVT 0x0001 // 10.1 - ADCA Event Interrupt
#define PIE_BIT_ADCA2    0x0002 // 10.2 - ADCA Interrupt 2
#define PIE_BIT_ADCA3    0x0004 // 10.3 - ADCA Interrupt 3
#define PIE_BIT_ADCA4    0x0008 // 10.4 - ADCA Interrupt 4
#define PIE_BIT_ADCB_EVT 0x0010 // 10.5 - ADCB Event Interrupt
#define PIE_BIT_ADCB2    0x0020 // 10.6 - ADCB Interrupt 2
#define PIE_BIT_ADCB3    0x0040 // 10.7 - ADCB Interrupt 3
#define PIE_BIT_ADCB4    0x0080 // 10.8 - ADCB Interrupt 4
#define PIE_BIT_ADCC_EVT 0x0100 // 10.9 - ADCC Event Interrupt
#define PIE_BIT_ADCC2    0x0200 // 10.10 - ADCC Interrupt 2
#define PIE_BIT_ADCC3    0x0400 // 10.11 - ADCC Interrupt 3
#define PIE_BIT_ADCC4    0x0800 // 10.12 - ADCC Interrupt 4

// Lower PIE Group 11
#define PIE_BIT_IPC_0 0x0001 // 11.1 - IPC interrupts
#define PIE_BIT_IPC_1 0x0002 // 11.2 - IPC interrupts
#define PIE_BIT_IPC_2 0x0004 // 11.3 - IPC interrupts
#define PIE_BIT_IPC_3 0x0008 // 11.4 - IPC interrupts

// Lower PIE Group 12
#define PIE_BIT_XINT3 0x0001 // 12.1 - XINT3 Interrupt
#define PIE_BIT_XINT4 0x0002 // 12.2 - XINT4 Interrupt
#define PIE_BIT_XINT5 0x0004 // 12.3 - XINT5 Interrupt

typedef enum
{
    //*****************************************************************************
    // PIE Interrupt Numbers
    // 0x00FF = PIE Table Row
    // 0xFF00 = PIE Table Column
    //*****************************************************************************

    // Lower PIE Group 1
    INT_TRACE     = 0x0C01, // 1.1 - Debug Trace Interrupt
    INT_WP_EXP    = 0x0C02, // 1.2 - Debug WatchPoint Interrupt
    INT_ADCA1     = 0x0103, // 1.3 - ADCA Interrupt 1
    INT_ADCB1     = 0x0104, // 1.4 - ADCB Interrupt 1
    INT_ADCC1     = 0x0105, // 1.5 - ADCC Interrupt 1
    INT_XINT1     = 0x0106, // 1.6 - XINT1 Interrupt
    INT_XINT2     = 0x0107, // 1.7 - XINT2 Interrupt
    INT_TIMER0    = 0x0109, // 1.9 - Timer 0 Interrupt
    INT_WAKE_WDOG = 0x010A, // 1.10 - Halt Wakeup/Watchdog Interrupt

    // Lower PIE Group 2
    INT_EPWM1_TZ = 0x0201, // 2.1 - ePWM1 Trip Zone Interrupt
    INT_EPWM2_TZ = 0x0202, // 2.2 - ePWM2 Trip Zone Interrupt
    INT_EPWM3_TZ = 0x0203, // 2.3 - ePWM3 Trip Zone Interrupt
    INT_EPWM4_TZ = 0x0204, // 2.4 - ePWM4 Trip Zone Interrupt
    INT_EPWM5_TZ = 0x0205, // 2.5 - ePWM5 Trip Zone Interrupt
    INT_EPWM6_TZ = 0x0206, // 2.6 - ePWM6 Trip Zone Interrupt
    INT_EPWM7_TZ = 0x0207, // 2.7 - ePWM7 Trip Zone Interrupt
    INT_EPWM8_TZ = 0x0208, // 2.8 - ePWM8 Trip Zone Interrupt

    // Lower PIE Group 3
    INT_EPWM1 = 0x0301, // 3.1 - ePWM1 Interrupt
    INT_EPWM2 = 0x0302, // 3.2 - ePWM2 Interrupt
    INT_EPWM3 = 0x0303, // 3.3 - ePWM3 Interrupt
    INT_EPWM4 = 0x0304, // 3.4 - ePWM4 Interrupt
    INT_EPWM5 = 0x0305, // 3.5 - ePWM5 Interrupt
    INT_EPWM6 = 0x0306, // 3.6 - ePWM6 Interrupt
    INT_EPWM7 = 0x0307, // 3.7 - ePWM7 Interrupt
    INT_EPWM8 = 0x0308, // 3.8 - ePWM8 Interrupt

    // Lower PIE Group 4
    INT_ECAP1       = 0x0401, // 4.1 - eCAP1 Interrupt
    INT_ECAP2       = 0x0402, // 4.2 - eCAP2 Interrupt
    INT_ECAP3       = 0x0403, // 4.3 - eCAP3 Interrupt
    INT_ECAP4       = 0x0404, // 4.4 - eCAP4 Interrupt
    INT_ECAP5       = 0x0405, // 4.5 - eCAP5 Interrupt
    INT_ECAP6       = 0x0406, // 4.6 - eCAP6 Interrupt
    INT_ECAP7       = 0x0407, // 4.7 - eCAP7 Interrupt
    INT_ECAP6_HRCAL = 0x040E, // 4.14 - eCAP6_HRCAL Interrupt
    INT_ECAP7_HRCAL = 0x040F, // 4.15 - eCAP7_HRCAL Interrupt

    // Lower PIE Group 5
    INT_EQEP1    = 0x0501, // 5.1 - eQEP1 Interrupt
    INT_EQEP2    = 0x0502, // 5.2 - eQEP2 Interrupt
    INT_SDFM1    = 0x0509, // 5.9 - SDFM1 Interrupt
    INT_SDFM1DR1 = 0x050D, // 5.13 - SDFM1DR1 Interrupt
    INT_SDFM1DR2 = 0x050E, // 5.14 - SDFM1DR2 Interrupt
    INT_SDFM1DR3 = 0x050F, // 5.15 - SDFM1DR3 Interrupt
    INT_SDFM1DR4 = 0x0510, // 5.16 - SDFM1DR4 Interrupt

    // Lower PIE Group 6
    INT_SPIA_M = 0x0601, // 6.1 - SPIA Receive Interrupt
    INT_SPIA_S = 0x0602, // 6.2 - SPIA Transmit Interrupt
    INT_SPIB_M = 0x0603, // 6.3 - SPIB Receive Interrupt
    INT_SPIB_S = 0x0604, // 6.4 - SPIB Transmit Interrupt

    // Lower PIE Group 7
    INT_DMA_CH1    = 0x0701, // 7.1 - DMA Channel 1 Interrupt
    INT_DMA_CH2    = 0x0702, // 7.2 - DMA Channel 2 Interrupt
    INT_DMA_CH3    = 0x0703, // 7.3 - DMA Channel 3 Interrupt
    INT_DMA_CH4    = 0x0704, // 7.4 - DMA Channel 4 Interrupt
    INT_DMA_CH5    = 0x0705, // 7.5 - DMA Channel 5 Interrupt
    INT_DMA_CH6    = 0x0706, // 7.6 - DMA Channel 6 Interrupt
    INT_FSITX_INT1 = 0x070B, // 7.11 - FSITXA_INT1 Interrupt
    INT_FSITX_INT2 = 0x070C, // 7.12 - FSITXA_INT2 Interrupt
    INT_FSIRX_INT1 = 0x070D, // 7.13 - FSIRXA_INT1 Interrupt
    INT_FSIRX_INT2 = 0x070E, // 7.14 - FSIRXA_INT2 Interrupt
    INT_DCC        = 0x0710, // 7.16 - DCC Interrupt

    // Lower PIE Group 8
    INT_I2CA   = 0x0801, // 8.1 - I2CA Interrupt 1
    INT_LINA   = 0x0809, // 8.9 - LINA Interrupt0
    INT_PMBUSA = 0x080D, // 8.13 - PMBUSA Interrupt

    // Lower PIE Group 9
    INT_SCIA = 0x0901, // 9.1 - SCIA Interrupt
    INT_SCIB = 0x0902, // 9.2 - SCIB Interrupt
    INT_CANA = 0x0905, // 9.5 - CANA Interrupt
    INT_CANB = 0x0906, // 9.6 - CANB Interrupt

    // Lower PIE Group 10
    INT_ADCA_EVT = 0x0A01, // 10.1 - ADCA Event Interrupt
    INT_ADCA2    = 0x0A02, // 10.2 - ADCA Interrupt 2
    INT_ADCA3    = 0x0A03, // 10.3 - ADCA Interrupt 3
    INT_ADCA4    = 0x0A04, // 10.4 - ADCA Interrupt 4
    INT_ADCB_EVT = 0x0A05, // 10.5 - ADCB Event Interrupt
    INT_ADCB2    = 0x0A06, // 10.6 - ADCB Interrupt 2
    INT_ADCB3    = 0x0A07, // 10.7 - ADCB Interrupt 3
    INT_ADCB4    = 0x0A08, // 10.8 - ADCB Interrupt 4
    INT_ADCC_EVT = 0x0A09, // 10.9 - ADCC Event Interrupt
    INT_ADCC2    = 0x0A0A, // 10.10 - ADCC Interrupt 2
    INT_ADCC3    = 0x0A0B, // 10.11 - ADCC Interrupt 3
    INT_ADCC4    = 0x0A0C, // 10.12 - ADCC Interrupt 4

    // Lower PIE Group 11
    INT_IPC_0 = 0x0B01, // 11.1 - IPC interrupts
    INT_IPC_1 = 0x0B02, // 11.2 - IPC interrupts
    INT_IPC_2 = 0x0B03, // 11.3 - IPC interrupts
    INT_IPC_3 = 0x0B04, // 11.4 - IPC interrupts

    // Lower PIE Group 12
    INT_XINT3 = 0x0C01, // 12.1 - XINT3 Interrupt
    INT_XINT4 = 0x0C02, // 12.2 - XINT4 Interrupt
    INT_XINT5 = 0x0C03, // 12.3 - XINT5 Interrupt

    // Other interrupts
    INT_TIMER1 = 0x0D01, // CPU Timer 1 Interrupt
    INT_TIMER2 = 0x0E01, // CPU Timer 2 Interrupt
    INT_NMI    = 0x0F01, // Non-Maskable Interrupt
} INTERRUPT_Type;

void Interrupt_initModule(void);
void Interrupt_enable(INTERRUPT_Type interruptNumber);
void Interrupt_disable(INTERRUPT_Type interruptNumber);
#ifdef __cplusplus
}
#endif

#endif
