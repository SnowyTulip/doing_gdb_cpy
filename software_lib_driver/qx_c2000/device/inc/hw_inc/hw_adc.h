#ifndef HW_ADC_H
#define HW_ADC_H

// ####
//*************************************************************************************************
//
//  The following are defines for the ADC register offsets
//
//*************************************************************************************************
#define ADC_O_CTL        0x00U // ADC Control Register
#define ADC_O_INTFLG     0x04U // ADC Interrupt Flag Register
#define ADC_O_INTSEL     0x08U // ADC Interrupt Selection Register
#define ADC_O_INTFLGCLR  0x0cU // ADC Interrupt Flag Clear Register
#define ADC_O_INTOVF     0x10U // ADC Interrupt Overflow Register
#define ADC_O_INTOVFCLR  0x14U // ADC Interrupt Overflow Clear Register
#define ADC_O_SOC0CTL    0x18U // ADC SOC0 Control Register
#define ADC_O_SOC1CTL    0x1cU // ADC SOC1 Control Register
#define ADC_O_SOC2CTL    0x20U // ADC SOC2 Control Register
#define ADC_O_SOC3CTL    0x24U // ADC SOC3 Control Register
#define ADC_O_SOC4CTL    0x28U // ADC SOC4 Control Register
#define ADC_O_SOC5CTL    0x2cU // ADC SOC5 Control Register
#define ADC_O_SOC6CTL    0x30U // ADC SOC6 Control Register
#define ADC_O_SOC7CTL    0x34U // ADC SOC7 Control Register
#define ADC_O_SOC8CTL    0x38U // ADC SOC8 Control Register
#define ADC_O_SOC9CTL    0x3cU // ADC SOC9 Control Register
#define ADC_O_SOC10CTL   0x40U // ADC SOC10 Control Register
#define ADC_O_SOC11CTL   0x44U // ADC SOC11 Control Register
#define ADC_O_SOC12CTL   0x48U // ADC SOC12 Control Register
#define ADC_O_SOC13CTL   0x4cU // ADC SOC13 Control Register
#define ADC_O_SOC14CTL   0x50U // ADC SOC14 Control Register
#define ADC_O_SOC15CTL   0x54U // ADC SOC15 Control Register
#define ADC_O_SOC16CTL   0x58U // ADC SOC16 Control Register
#define ADC_O_SOC17CTL   0x5cU // ADC SOC17 Control Register
#define ADC_O_SOC18CTL   0x60U // ADC SOC18 Control Register
#define ADC_O_SOC19CTL   0x64U // ADC SOC19 Control Register
#define ADC_O_EVTSTAT    0x68U // ADC Event Status Register
#define ADC_O_EVTCLR     0x6cU // ADC Event Clear Register
#define ADC_O_EVTSEL     0x70U // ADC Event Selection Register
#define ADC_O_EVTINTSEL  0x74U // ADC Event Interrupt Selection Register
#define ADC_O_COUNTER    0x78U // ADC Counter Register
#define ADC_O_REV        0x7cU // ADC Revision Register
#define ADC_O_PPB1CONFIG 0x80U // ADC PPB1 Configuration Register
#define ADC_O_PPB1STAMP  0x84U // ADC PPB1 Sample Delay Time Stamp Register
#define ADC_O_PPB1OFFREF 0x88U // ADC PPB1 Offset Reference Register
#define ADC_O_PPB1TRIPHI 0x8cU // ADC PPB1 Trip High Register
#define ADC_O_PPB1TRIPLO 0x90U // ADC PPB1 Trip Low Register
#define ADC_O_PPB1OFFCAL 0x94U // ADC PPB1 Offset Calibration Register
#define ADC_O_PPB2CONFIG 0x98U // ADC PPB2 Configuration Register
#define ADC_O_PPB2STAMP  0x9cU // ADC PPB2 Sample Delay Time Stamp Register
#define ADC_O_PPB2OFFREF 0xa0U // ADC PPB2 Offset Reference Register
#define ADC_O_PPB2TRIPHI 0xa4U // ADC PPB2 Trip High Register
#define ADC_O_PPB2TRIPLO 0xa8U // ADC PPB2 Trip Low Register
#define ADC_O_PPB2OFFCAL 0xacU // ADC PPB2 Offset Calibration Register
#define ADC_O_PPB3CONFIG 0xb0U // ADC PPB3 Configuration Register
#define ADC_O_PPB3STAMP  0xb4U // ADC PPB3 Sample Delay Time Stamp Register
#define ADC_O_PPB3OFFREF 0xb8U // ADC PPB3 Offset Reference Register
#define ADC_O_PPB3TRIPHI 0xbcU // ADC PPB3 Trip High Register
#define ADC_O_PPB3TRIPLO 0xc0U // ADC PPB3 Trip Low Register
#define ADC_O_PPB3OFFCAL 0xc4U // ADC PPB3 Offset Calibration Register
#define ADC_O_PPB4CONFIG 0xc8U // ADC PPB4 Configuration Register
#define ADC_O_PPB4STAMP  0xccU // ADC PPB4 Sample Delay Time Stamp Register
#define ADC_O_PPB4OFFREF 0xd0U // ADC PPB4 Offset Reference Register
#define ADC_O_PPB4TRIPHI 0xd4U // ADC PPB4 Trip High Register
#define ADC_O_PPB4TRIPLO 0xd8U // ADC PPB4 Trip Low Register
#define ADC_O_PPB4OFFCAL 0xdcU // ADC PPB4 Offset Calibration Register
#define ADC_O_SOCFRC     0xe0U // ADC SOC Force Register
#define ADC_O_SOCFLG     0xe4U // ADC SOC Flag Register
#define ADC_O_SOCOVF     0xe8U // ADC SOC Overflow Register
#define ADC_O_SOCOVFCL1  0xecU // ADC SOC Overflow Clear Register

#define ADC_RESULT0    0x00U   // ADC Result 0 Register
#define ADC_RESULT1    0x04U   // ADC Result 1 Register
#define ADC_RESULT2    0x08U   // ADC Result 2 Register
#define ADC_RESULT3    0x0cU   // ADC Result 3 Register
#define ADC_RESULT4    0x10U   // ADC Result 4 Register
#define ADC_RESULT5    0x14U   // ADC Result 5 Register
#define ADC_RESULT6    0x18U   // ADC Result 6 Register
#define ADC_RESULT7    0x1cU   // ADC Result 7 Register
#define ADC_RESULT8    0x20U   // ADC Result 8 Register
#define ADC_RESULT9    0x24U   // ADC Result 9 Register
#define ADC_RESULT10   0x28U   // ADC Result 10 Register
#define ADC_RESULT11   0x2cU   // ADC Result 11 Register
#define ADC_RESULT12   0x30U   // ADC Result 12 Register
#define ADC_RESULT13   0x34U   // ADC Result 13 Register
#define ADC_RESULT14   0x38U   // ADC Result 14 Register
#define ADC_RESULT15   0x3cU   // ADC Result 15 Register
#define ADC_RESULT16   0x40U   // ADC Result 16 Register
#define ADC_RESULT17   0x44U   // ADC Result 17 Register
#define ADC_RESULT18   0x48U   // ADC Result 18 Register
#define ADC_RESULT19   0x4cU   // ADC Result 19 Register
#define ADC_PPB1RESULT 0x50U   // ADC PPB1 Result Register
#define ADC_PPB2RESULT 0x54U   // ADC PPB2 Result Register
#define ADC_PPB3RESULT 0x58U   // ADC PPB3 Result Register
#define ADC_PPB4RESULT 0x5cU   // ADC PPB4 Result Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCCTL register
//
//*************************************************************************************************
#define ADC_CTL_SWLDO_HS_LU    0x1U
#define ADC_CTL_SELVI_HD_LS    0x2U
#define ADC_CTL_MODE           0x4U
#define ADC_CTL_BIAS_C_S       4U
#define ADC_CTL_BIAS_C_M       0x70U
#define ADC_CTL_ADCPWDNZ       0x7U
#define ADC_CTL_CLK_DLY_SEL_S  8U
#define ADC_CTL_CLK_DLY_SEL_M  0x300U
#define ADC_CTL_MD_ADC_S       10U
#define ADC_CTL_MD_ADC_M       0xc00U
#define ADC_CTL_ADC_BUSYCHAN_S 12U
#define ADC_CTL_ADC_BUSYCHAN_M 0xf000U
#define ADC_CTL_ADC_BUSY       0x10000U
#define ADC_CTL_PRESCALE_S     17U
#define ADC_CTL_PRESCALE_M     0x3e000U

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTFLG register
//
//*************************************************************************************************
#define ADC_INTFLG_ADCINT1 0x1U // ADC Interrupt 1 Flag
#define ADC_INTFLG_ADCINT2 0x2U // ADC Interrupt 2 Flag
#define ADC_INTFLG_ADCINT3 0x4U // ADC Interrupt 3 Flag
#define ADC_INTFLG_ADCINT4 0x8U // ADC Interrupt 4 Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTFLGCLR register
//
//*************************************************************************************************
#define ADC_INTFLGCLR_ADCINT1 0x1U // ADC Interrupt 1 Flag Clear
#define ADC_INTFLGCLR_ADCINT2 0x2U // ADC Interrupt 2 Flag Clear
#define ADC_INTFLGCLR_ADCINT3 0x4U // ADC Interrupt 3 Flag Clear
#define ADC_INTFLGCLR_ADCINT4 0x8U // ADC Interrupt 4 Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTOVF register
//
//*************************************************************************************************
#define ADC_INTOVF_ADCINT1 0x1U // ADC Interrupt 1 Overflow Flags
#define ADC_INTOVF_ADCINT2 0x2U // ADC Interrupt 2 Overflow Flags
#define ADC_INTOVF_ADCINT3 0x4U // ADC Interrupt 3 Overflow Flags
#define ADC_INTOVF_ADCINT4 0x8U // ADC Interrupt 4 Overflow Flags

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTOVFCLR register
//
//*************************************************************************************************
#define ADC_INTOVFCLR_ADCINT1 0x1U // ADC Interrupt 1 Overflow Clear Bits
#define ADC_INTOVFCLR_ADCINT2 0x2U // ADC Interrupt 2 Overflow Clear Bits
#define ADC_INTOVFCLR_ADCINT3 0x4U // ADC Interrupt 3 Overflow Clear Bits
#define ADC_INTOVFCLR_ADCINT4 0x8U // ADC Interrupt 4 Overflow Clear Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCINTSEL register
//
//*************************************************************************************************
#define ADC_INT1SEL_INTSEL_S 0U
#define ADC_INT1SEL_INTSEL_M 0x1fU       // ADCINT1 EOC Source Select
#define ADC_INT1SEL_INTE     0x20U       // ADCINT1 Interrupt Enable
#define ADC_INT1SEL_INTCONT  0x40U       // ADCINT1 Continue to Interrupt Mode
#define ADC_INT2SEL_INTSEL_S 8U
#define ADC_INT2SEL_INTSEL_M 0x1f00U     // ADCINT2 EOC Source Select
#define ADC_INT2SEL_INTE     0x2000U     // ADCINT2 Interrupt Enable
#define ADC_INT2SEL_INTCONT  0x4000U     // ADCINT2 Continue to Interrupt Mode
#define ADC_INT3SEL_INTSEL_S 16U
#define ADC_INT3SEL_INTSEL_M 0x1f0000U   // ADCINT1 EOC Source Select
#define ADC_INT3SEL_INTE     0x200000U   // ADCINT1 Interrupt Enable
#define ADC_INT3SEL_INTCONT  0x400000U   // ADCINT1 Continue to Interrupt Mode
#define ADC_INT4SEL_INTSEL_S 24U
#define ADC_INT4SEL_INTSEL_M 0x1f000000U // ADCINT2 EOC Source Select
#define ADC_INT4SEL_INTE     0x20000000U // ADCINT2 Interrupt Enable
#define ADC_INT4SEL_INTCONT  0x40000000U // ADCINT2 Continue to Interrupt Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC0CTL register
//
//*************************************************************************************************
#define ADC_SOC0CTL_CHSEL_S   12U
#define ADC_SOC0CTL_CHSEL_M   0x1f000U // SOC0 Channel Select
#define ADC_SOC0CTL_TRIGSEL_S 3U
#define ADC_SOC0CTL_TRIGSEL_M 0xF8U    // SOC0 Trigger Source Select
#define ADC_SOC0CTL_ACQPS_S   8U
#define ADC_SOC0CTL_ACQPS_M   0xF00U   // SOC0 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC1CTL register
//
//*************************************************************************************************
#define ADC_SOC1CTL_CHSEL_S   12U
#define ADC_SOC1CTL_CHSEL_M   0x1f000U // SOC1 Channel Select
#define ADC_SOC1CTL_TRIGSEL_S 3U
#define ADC_SOC1CTL_TRIGSEL_M 0xF8U    // SOC1 Trigger Source Select
#define ADC_SOC1CTL_ACQPS_S   8U
#define ADC_SOC1CTL_ACQPS_M   0xF00U   // SOC1 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC2CTL register
//
//*************************************************************************************************
#define ADC_SOC2CTL_CHSEL_S   12U
#define ADC_SOC2CTL_CHSEL_M   0x1f000U // SOC2 Channel Select
#define ADC_SOC2CTL_TRIGSEL_S 3U
#define ADC_SOC2CTL_TRIGSEL_M 0xF8U    // SOC2 Trigger Source Select
#define ADC_SOC2CTL_ACQPS_S   8U
#define ADC_SOC2CTL_ACQPS_M   0xF00U   // SOC2 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC3CTL register
//
//*************************************************************************************************
#define ADC_SOC3CTL_CHSEL_S   12U
#define ADC_SOC3CTL_CHSEL_M   0x1f000U // SOC3 Channel Select
#define ADC_SOC3CTL_TRIGSEL_S 3U
#define ADC_SOC3CTL_TRIGSEL_M 0xF8U    // SOC3 Trigger Source Select
#define ADC_SOC3CTL_ACQPS_S   8U
#define ADC_SOC3CTL_ACQPS_M   0xF00U   // SOC3 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC4CTL register
//
//*************************************************************************************************
#define ADC_SOC4CTL_CHSEL_S   12U
#define ADC_SOC4CTL_CHSEL_M   0x1f000U // SOC4 Channel Select
#define ADC_SOC4CTL_TRIGSEL_S 3U
#define ADC_SOC4CTL_TRIGSEL_M 0xF8U    // SOC4 Trigger Source Select
#define ADC_SOC4CTL_ACQPS_S   8U
#define ADC_SOC4CTL_ACQPS_M   0xF00U   // SOC4 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC5CTL register
//
//*************************************************************************************************
#define ADC_SOC5CTL_CHSEL_S   12U
#define ADC_SOC5CTL_CHSEL_M   0x1f000U // SOC5 Channel Select
#define ADC_SOC5CTL_TRIGSEL_S 3U
#define ADC_SOC5CTL_TRIGSEL_M 0xF8U    // SOC5 Trigger Source Select
#define ADC_SOC5CTL_ACQPS_S   8U
#define ADC_SOC5CTL_ACQPS_M   0xF00U   // SOC5 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC6CTL register
//
//*************************************************************************************************
#define ADC_SOC6CTL_CHSEL_S   12U
#define ADC_SOC6CTL_CHSEL_M   0x1f000U // SOC6 Channel Select
#define ADC_SOC6CTL_TRIGSEL_S 3U
#define ADC_SOC6CTL_TRIGSEL_M 0xF8U    // SOC6 Trigger Source Select
#define ADC_SOC6CTL_ACQPS_S   8U
#define ADC_SOC6CTL_ACQPS_M   0xF00U   // SOC6 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC7CTL register
//
//*************************************************************************************************
#define ADC_SOC7CTL_CHSEL_S   12U
#define ADC_SOC7CTL_CHSEL_M   0x1f000U // SOC7 Channel Select
#define ADC_SOC7CTL_TRIGSEL_S 3U
#define ADC_SOC7CTL_TRIGSEL_M 0xF8U    // SOC7 Trigger Source Select
#define ADC_SOC7CTL_ACQPS_S   8U
#define ADC_SOC7CTL_ACQPS_M   0xF00U   // SOC7 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC8CTL register
//
//*************************************************************************************************
#define ADC_SOC8CTL_CHSEL_S   12U
#define ADC_SOC8CTL_CHSEL_M   0x1f000U // SOC8 Channel Select
#define ADC_SOC8CTL_TRIGSEL_S 3U
#define ADC_SOC8CTL_TRIGSEL_M 0xF8U    // SOC8 Trigger Source Select
#define ADC_SOC8CTL_ACQPS_S   8U
#define ADC_SOC8CTL_ACQPS_M   0xF00U   // SOC8 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC9CTL register
//
//*************************************************************************************************
#define ADC_SOC9CTL_CHSEL_S   12U
#define ADC_SOC9CTL_CHSEL_M   0x1f000U // SOC9 Channel Select
#define ADC_SOC9CTL_TRIGSEL_S 3U
#define ADC_SOC9CTL_TRIGSEL_M 0xF8U    // SOC9 Trigger Source Select
#define ADC_SOC9CTL_ACQPS_S   8U
#define ADC_SOC9CTL_ACQPS_M   0xF00U   // SOC9 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC10CTL register
//
//*************************************************************************************************
#define ADC_SOC10CTL_CHSEL_S   12U
#define ADC_SOC10CTL_CHSEL_M   0x1f000U // SOC10 Channel Select
#define ADC_SOC10CTL_TRIGSEL_S 3U
#define ADC_SOC10CTL_TRIGSEL_M 0xF8U    // SOC10 Trigger Source Select
#define ADC_SOC10CTL_ACQPS_S   8U
#define ADC_SOC10CTL_ACQPS_M   0xF00U   // SOC10 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC11CTL register
//
//*************************************************************************************************
#define ADC_SOC11CTL_CHSEL_S   12U
#define ADC_SOC11CTL_CHSEL_M   0x1f000U // SOC11 Channel Select
#define ADC_SOC11CTL_TRIGSEL_S 3U
#define ADC_SOC11CTL_TRIGSEL_M 0xF8U    // SOC11 Trigger Source Select
#define ADC_SOC11CTL_ACQPS_S   8U
#define ADC_SOC11CTL_ACQPS_M   0xF00U   // SOC11 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC12CTL register
//
//*************************************************************************************************
#define ADC_SOC12CTL_CHSEL_S   12U
#define ADC_SOC12CTL_CHSEL_M   0x1f000U // SOC12 Channel Select
#define ADC_SOC12CTL_TRIGSEL_S 3U
#define ADC_SOC12CTL_TRIGSEL_M 0xF8U    // SOC12 Trigger Source Select
#define ADC_SOC12CTL_ACQPS_S   8U
#define ADC_SOC12CTL_ACQPS_M   0xF00U   // SOC12 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC13CTL register
//
//*************************************************************************************************
#define ADC_SOC13CTL_CHSEL_S   12U
#define ADC_SOC13CTL_CHSEL_M   0x1f000U // SOC13 Channel Select
#define ADC_SOC13CTL_TRIGSEL_S 3U
#define ADC_SOC13CTL_TRIGSEL_M 0xF8U    // SOC13 Trigger Source Select
#define ADC_SOC13CTL_ACQPS_S   8U
#define ADC_SOC13CTL_ACQPS_M   0xF00U   // SOC13 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC14CTL register
//
//*************************************************************************************************
#define ADC_SOC14CTL_CHSEL_S   12U
#define ADC_SOC14CTL_CHSEL_M   0x1f000U // SOC14 Channel Select
#define ADC_SOC14CTL_TRIGSEL_S 3U
#define ADC_SOC14CTL_TRIGSEL_M 0xF8U    // SOC14 Trigger Source Select
#define ADC_SOC14CTL_ACQPS_S   8U
#define ADC_SOC14CTL_ACQPS_M   0xF00U   // SOC14 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC15CTL register
//
//*************************************************************************************************
#define ADC_SOC15CTL_CHSEL_S   12U
#define ADC_SOC15CTL_CHSEL_M   0x1f000U // SOC15 Channel Select
#define ADC_SOC15CTL_TRIGSEL_S 3U
#define ADC_SOC15CTL_TRIGSEL_M 0xF8U    // SOC15 Trigger Source Select
#define ADC_SOC15CTL_ACQPS_S   8U
#define ADC_SOC15CTL_ACQPS_M   0xF00U   // SOC15 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC16CTL register
//
//*************************************************************************************************
#define ADC_SOC16CTL_CHSEL_S   12U
#define ADC_SOC16CTL_CHSEL_M   0x1f000U // SOC16 Channel Select
#define ADC_SOC16CTL_TRIGSEL_S 3U
#define ADC_SOC16CTL_TRIGSEL_M 0xF8U    // SOC16 Trigger Source Select
#define ADC_SOC16CTL_ACQPS_S   8U
#define ADC_SOC16CTL_ACQPS_M   0xF00U   // SOC16 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC17CTL register
//
//*************************************************************************************************
#define ADC_SOC17CTL_CHSEL_S   12U
#define ADC_SOC17CTL_CHSEL_M   0x1f000U // SOC17 Channel Select
#define ADC_SOC17CTL_TRIGSEL_S 3U
#define ADC_SOC17CTL_TRIGSEL_M 0xF8U    // SOC17 Trigger Source Select
#define ADC_SOC17CTL_ACQPS_S   8U
#define ADC_SOC17CTL_ACQPS_M   0xF00U   // SOC17 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC18CTL register
//
//*************************************************************************************************
#define ADC_SOC18CTL_CHSEL_S   12U
#define ADC_SOC18CTL_CHSEL_M   0x1f000U // SOC18 Channel Select
#define ADC_SOC18CTL_TRIGSEL_S 3U
#define ADC_SOC18CTL_TRIGSEL_M 0xF8U    // SOC18 Trigger Source Select
#define ADC_SOC18CTL_ACQPS_S   8U
#define ADC_SOC18CTL_ACQPS_M   0xF00U   // SOC18 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOC19CTL register
//
//*************************************************************************************************
#define ADC_SOC19CTL_CHSEL_S   12U
#define ADC_SOC19CTL_CHSEL_M   0x1f000U // SOC19 Channel Select
#define ADC_SOC19CTL_TRIGSEL_S 3U
#define ADC_SOC19CTL_TRIGSEL_M 0xF8U    // SOC19 Trigger Source Select
#define ADC_SOC19CTL_ACQPS_S   8U
#define ADC_SOC19CTL_ACQPS_M   0xF00U   // SOC19 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCEVTSTAT register
//
//*************************************************************************************************
#define ADC_EVTSTAT_PPB1TRIPHI 0x1U   // Post Processing Block 1 Trip High Flag
#define ADC_EVTSTAT_PPB1TRIPLO 0x2U   // Post Processing Block 1 Trip Low Flag
#define ADC_EVTSTAT_PPB1ZERO   0x4U   // Post Processing Block 1 Zero Crossing Flag
#define ADC_EVTSTAT_PPB2TRIPHI 0x8U   // Post Processing Block 2 Trip High Flag
#define ADC_EVTSTAT_PPB2TRIPLO 0x10U  // Post Processing Block 2 Trip Low Flag
#define ADC_EVTSTAT_PPB2ZERO   0x20U  // Post Processing Block 2 Zero Crossing Flag
#define ADC_EVTSTAT_PPB3TRIPHI 0x40U  // Post Processing Block 3 Trip High Flag
#define ADC_EVTSTAT_PPB3TRIPLO 0x80U  // Post Processing Block 3 Trip Low Flag
#define ADC_EVTSTAT_PPB3ZERO   0x100U // Post Processing Block 3 Zero Crossing Flag
#define ADC_EVTSTAT_PPB4TRIPHI 0x200U // Post Processing Block 4 Trip High Flag
#define ADC_EVTSTAT_PPB4TRIPLO 0x400U // Post Processing Block 4 Trip Low Flag
#define ADC_EVTSTAT_PPB4ZERO   0x800U // Post Processing Block 4 Zero Crossing Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCEVTCLR register
//
//*************************************************************************************************
#define ADC_EVTCLR_PPB1TRIPHI 0x1U   // Post Processing Block 1 Trip High Flag Clear
#define ADC_EVTCLR_PPB1TRIPLO 0x2U   // Post Processing Block 1 Trip Low Flag Clear
#define ADC_EVTCLR_PPB1ZERO   0x4U   // Post Processing Block 1 Zero Crossing Flag Clear
#define ADC_EVTCLR_PPB2TRIPHI 0x8U   // Post Processing Block 2 Trip High Flag Clear
#define ADC_EVTCLR_PPB2TRIPLO 0x10U  // Post Processing Block 2 Trip Low Flag Clear
#define ADC_EVTCLR_PPB2ZERO   0x20U  // Post Processing Block 2 Zero Crossing Flag Clear
#define ADC_EVTCLR_PPB3TRIPHI 0x40U  // Post Processing Block 3 Trip High Flag Clear
#define ADC_EVTCLR_PPB3TRIPLO 0x80U  // Post Processing Block 3 Trip Low Flag Clear
#define ADC_EVTCLR_PPB3ZERO   0x100U // Post Processing Block 3 Zero Crossing Flag Clear
#define ADC_EVTCLR_PPB4TRIPHI 0x200U // Post Processing Block 4 Trip High Flag Clear
#define ADC_EVTCLR_PPB4TRIPLO 0x400U // Post Processing Block 4 Trip Low Flag Clear
#define ADC_EVTCLR_PPB4ZERO   0x800U // Post Processing Block 4 Zero Crossing Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCEVTSEL register
//
//*************************************************************************************************
#define ADC_EVTSEL_PPB1TRIPHI 0x1U   // Post Processing Block 1 Trip High Flag Select
#define ADC_EVTSEL_PPB1TRIPLO 0x2U   // Post Processing Block 1 Trip Low Flag Select
#define ADC_EVTSEL_PPB1ZERO   0x4U   // Post Processing Block 1 Zero Crossing Flag Select
#define ADC_EVTSEL_PPB2TRIPHI 0x8U   // Post Processing Block 2 Trip High Flag Select
#define ADC_EVTSEL_PPB2TRIPLO 0x10U  // Post Processing Block 2 Trip Low Flag Select
#define ADC_EVTSEL_PPB2ZERO   0x20U  // Post Processing Block 2 Zero Crossing Flag Select
#define ADC_EVTSEL_PPB3TRIPHI 0x40U  // Post Processing Block 3 Trip High Flag Select
#define ADC_EVTSEL_PPB3TRIPLO 0x80U  // Post Processing Block 3 Trip Low Flag Select
#define ADC_EVTSEL_PPB3ZERO   0x100U // Post Processing Block 3 Zero Crossing Flag Select
#define ADC_EVTSEL_PPB4TRIPHI 0x200U // Post Processing Block 4 Trip High Flag Select
#define ADC_EVTSEL_PPB4TRIPLO 0x400U // Post Processing Block 4 Trip Low Flag Select
#define ADC_EVTSEL_PPB4ZERO   0x800U // Post Processing Block 4 Zero Crossing Flag Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCEVTINTSEL register
//
//*************************************************************************************************
#define ADC_EVTINTSEL_PPB1TRIPHI 0x1U   // Post Processing Block 1 Trip High Flag Interrupt Select
#define ADC_EVTINTSEL_PPB1TRIPLO 0x2U   // Post Processing Block 1 Trip Low Flag Interrupt Select
#define ADC_EVTINTSEL_PPB1ZERO   0x4U   // Post Processing Block 1 Zero Crossing Flag Interrupt Select
#define ADC_EVTINTSEL_PPB2TRIPHI 0x8U   // Post Processing Block 2 Trip High Flag Interrupt Select
#define ADC_EVTINTSEL_PPB2TRIPLO 0x10U  // Post Processing Block 2 Trip Low Flag Interrupt Select
#define ADC_EVTINTSEL_PPB2ZERO   0x20U  // Post Processing Block 2 Zero Crossing Flag Interrupt Select
#define ADC_EVTINTSEL_PPB3TRIPHI 0x40U  // Post Processing Block 3 Trip High Flag Interrupt Select
#define ADC_EVTINTSEL_PPB3TRIPLO 0x80U  // Post Processing Block 3 Trip Low Flag Interrupt Select
#define ADC_EVTINTSEL_PPB3ZERO   0x100U // Post Processing Block 3 Zero Crossing Flag Interrupt Select
#define ADC_EVTINTSEL_PPB4TRIPHI 0x200U // Post Processing Block 4 Trip High Flag Interrupt Select
#define ADC_EVTINTSEL_PPB4TRIPLO 0x400U // Post Processing Block 4 Trip Low Flag Interrupt Select
#define ADC_EVTINTSEL_PPB4ZERO   0x800U // Post Processing Block 4 Zero Crossing Flag Interrupt Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCCOUNTER register
//
//*************************************************************************************************
#define ADC_COUNTER_FREECOUNT_S 0U
#define ADC_COUNTER_FREECOUNT_M 0xFFFU // ADC Free Running Counter Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCREV register
//
//*************************************************************************************************
#define ADC_REV_TYPE_S 0U
#define ADC_REV_TYPE_M 0xFFU   // ADC Type
#define ADC_REV_REV_S  8U
#define ADC_REV_REV_M  0xFF00U // ADC Revision

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBCONFIG register
//
//*************************************************************************************************
#define ADC_PPB1CONFIG_CONFIG_S   0U
#define ADC_PPB1CONFIG_CONFIG_M   0x1fU // ADC Post Processing Block 1 Configuration
#define ADC_PPB1CONFIG_TWOSCOMPEN 0x20U // ADC Post Processing Block 1 Two's Complement Enable
#define ADC_PPB1CONFIG_CBCEN      0x40U // ADC Post Processing Block 1 Cycle By Cycle Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBSTAMP register
//
//*************************************************************************************************
#define ADC_PPB1STAMP_DLYSTAMP_S 0U
#define ADC_PPB1STAMP_DLYSTAMP_M 0xFFFU // ADC Post Processing Block 1 Delay Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBOFFREF register
//
//*************************************************************************************************
#define ADC_PPB1OFFREF_OFFREF_S 0U
#define ADC_PPB1OFFREF_OFFREF_M 0xFFFFU // ADC Post Processing Block 1 Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBTRIPHI register
//
//*************************************************************************************************
#define ADC_PPB1TRIPHI_LIMITHI_S 0U
#define ADC_PPB1TRIPHI_LIMITHI_M 0xFFFU  // ADC Post Processing Block 1 Trip High Limit
#define ADC_PPB1TRIPHI_HSIGN     0x1000U // ADC Post Processing Block 1 High Limit Sign Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBTRIPLO register
//
//*************************************************************************************************
#define ADC_PPB1TRIPLO_LIMITLO_S  0U
#define ADC_PPB1TRIPLO_LIMITLO_M  0xFFFU      // ADC Post Processing Block 1 Trip Low Limit
#define ADC_PPB1TRIPLO_LSIGN      0x1000U     // ADC Post Processing Block 1 Low Limit Sign Bit
#define ADC_PPB1TRIPLO_REQSTAMP_S 20U
#define ADC_PPB1TRIPLO_REQSTAMP_M 0xFFF00000U // ADC Post Processing Block 1 Request Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBOFFCAL register
//
//*************************************************************************************************
#define ADC_PPB1OFFCAL_OFFCAL_S 0U
#define ADC_PPB1OFFCAL_OFFCAL_M 0x3FFU // ADC Post Processing Block 1 Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBCONFIG register
//
//*************************************************************************************************
#define ADC_PPB2CONFIG_CONFIG_S   0U
#define ADC_PPB2CONFIG_CONFIG_M   0x1fU // ADC Post Processing Block 2 Configuration
#define ADC_PPB2CONFIG_TWOSCOMPEN 0x20U // ADC Post Processing Block 2 Two's Complement Enable
#define ADC_PPB2CONFIG_CBCEN      0x40U // ADC Post Processing Block 2 Cycle By Cycle Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBSTAMP register
//
//*************************************************************************************************
#define ADC_PPB2STAMP_DLYSTAMP_S 0U
#define ADC_PPB2STAMP_DLYSTAMP_M 0xFFFU // ADC Post Processing Block 2 Delay Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBOFFREF register
//
//*************************************************************************************************
#define ADC_PPB2OFFREF_OFFREF_S 0U
#define ADC_PPB2OFFREF_OFFREF_M 0xFFFFU // ADC Post Processing Block 2 Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBTRIPHI register
//
//*************************************************************************************************
#define ADC_PPB2TRIPHI_LIMITHI_S 0U
#define ADC_PPB2TRIPHI_LIMITHI_M 0xFFFU  // ADC Post Processing Block 2 Trip High Limit
#define ADC_PPB2TRIPHI_HSIGN     0x1000U // ADC Post Processing Block 2 High Limit Sign Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBTRIPLO register
//
//*************************************************************************************************
#define ADC_PPB2TRIPLO_LIMITLO_S  0U
#define ADC_PPB2TRIPLO_LIMITLO_M  0xFFFU      // ADC Post Processing Block 2 Trip Low Limit
#define ADC_PPB2TRIPLO_LSIGN      0x1000U     // ADC Post Processing Block 2 Low Limit Sign Bit
#define ADC_PPB2TRIPLO_REQSTAMP_S 20U
#define ADC_PPB2TRIPLO_REQSTAMP_M 0xFFF00000U // ADC Post Processing Block 2 Request Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBOFFCAL register
//
//*************************************************************************************************
#define ADC_PPB2OFFCAL_OFFCAL_S 0U
#define ADC_PPB2OFFCAL_OFFCAL_M 0x3FFU // ADC Post Processing Block 2 Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBCONFIG register
//
//*************************************************************************************************
#define ADC_PPB3CONFIG_CONFIG_S   0U
#define ADC_PPB3CONFIG_CONFIG_M   0x1fU // ADC Post Processing Block 3 Configuration
#define ADC_PPB3CONFIG_TWOSCOMPEN 0x20U // ADC Post Processing Block 3 Two's Complement Enable
#define ADC_PPB3CONFIG_CBCEN      0x40U // ADC Post Processing Block 3 Cycle By Cycle Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBSTAMP register
//
//*************************************************************************************************
#define ADC_PPB3STAMP_DLYSTAMP_S 0U
#define ADC_PPB3STAMP_DLYSTAMP_M 0xFFFU // ADC Post Processing Block 3 Delay Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBOFFREF register
//
//*************************************************************************************************
#define ADC_PPB3OFFREF_OFFREF_S 0U
#define ADC_PPB3OFFREF_OFFREF_M 0xFFFFU // ADC Post Processing Block 3 Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBTRIPHI register
//
//*************************************************************************************************
#define ADC_PPB3TRIPHI_LIMITHI_S 0U
#define ADC_PPB3TRIPHI_LIMITHI_M 0xFFFU  // ADC Post Processing Block 3 Trip High Limit
#define ADC_PPB3TRIPHI_HSIGN     0x1000U // ADC Post Processing Block 3 High Limit Sign Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBTRIPLO register
//
//*************************************************************************************************
#define ADC_PPB3TRIPLO_LIMITLO_S  0U
#define ADC_PPB3TRIPLO_LIMITLO_M  0xFFFU      // ADC Post Processing Block 3 Trip Low Limit
#define ADC_PPB3TRIPLO_LSIGN      0x1000U     // ADC Post Processing Block 3 Low Limit Sign Bit
#define ADC_PPB3TRIPLO_REQSTAMP_S 20U
#define ADC_PPB3TRIPLO_REQSTAMP_M 0xFFF00000U // ADC Post Processing Block 3 Request Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBOFFCAL register
//
//*************************************************************************************************
#define ADC_PPB3OFFCAL_OFFCAL_S 0U
#define ADC_PPB3OFFCAL_OFFCAL_M 0x3FFU // ADC Post Processing Block 3 Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBCONFIG register
//
//*************************************************************************************************
#define ADC_PPB4CONFIG_CONFIG_S   0U
#define ADC_PPB4CONFIG_CONFIG_M   0x1fU // ADC Post Processing Block 4 Configuration
#define ADC_PPB4CONFIG_TWOSCOMPEN 0x20U // ADC Post Processing Block 4 Two's Complement Enable
#define ADC_PPB4CONFIG_CBCEN      0x40U // ADC Post Processing Block 4 Cycle By Cycle Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBSTAMP register
//
//*************************************************************************************************
#define ADC_PPB4STAMP_DLYSTAMP_S 0U
#define ADC_PPB4STAMP_DLYSTAMP_M 0xFFFU // ADC Post Processing Block 4 Delay Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBOFFREF register
//
//*************************************************************************************************
#define ADC_PPB4OFFREF_OFFREF_S 0U
#define ADC_PPB4OFFREF_OFFREF_M 0xFFFFU // ADC Post Processing Block 4 Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBTRIPHI register
//
//*************************************************************************************************
#define ADC_PPB4TRIPHI_LIMITHI_S 0U
#define ADC_PPB4TRIPHI_LIMITHI_M 0xFFFU  // ADC Post Processing Block 4 Trip High Limit
#define ADC_PPB4TRIPHI_HSIGN     0x1000U // ADC Post Processing Block 4 High Limit Sign Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBTRIPLO register
//
//*************************************************************************************************
#define ADC_PPB4TRIPLO_LIMITLO_S  0U
#define ADC_PPB4TRIPLO_LIMITLO_M  0xFFFU      // ADC Post Processing Block 4 Trip Low Limit
#define ADC_PPB4TRIPLO_LSIGN      0x1000U     // ADC Post Processing Block 4 Low Limit Sign Bit
#define ADC_PPB4TRIPLO_REQSTAMP_S 20U
#define ADC_PPB4TRIPLO_REQSTAMP_M 0xFFF00000U // ADC Post Processing Block 4 Request Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPBOFFCAL register
//
//*************************************************************************************************
#define ADC_PPB4OFFCAL_OFFCAL_S 0U
#define ADC_PPB4OFFCAL_OFFCAL_M 0x3FFU // ADC Post Processing Block 4 Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1RESULT register
//
//*************************************************************************************************
#define ADC_PPB1RESULT_PPBRESULT_S 0U
#define ADC_PPB1RESULT_PPBRESULT_M 0xFFFU      // ADC Post Processing Block 1 Result
#define ADC_PPB1RESULT_SIGN_S      12U
#define ADC_PPB1RESULT_SIGN_M      0xFFFFF000U // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2RESULT register
//
//*************************************************************************************************
#define ADC_PPB2RESULT_PPBRESULT_S 0U
#define ADC_PPB2RESULT_PPBRESULT_M 0xFFFU      // ADC Post Processing Block 2 Result
#define ADC_PPB2RESULT_SIGN_S      12U
#define ADC_PPB2RESULT_SIGN_M      0xFFFFF000U // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3RESULT register
//
//*************************************************************************************************
#define ADC_PPB3RESULT_PPBRESULT_S 0U
#define ADC_PPB3RESULT_PPBRESULT_M 0xFFFU      // ADC Post Processing Block 3 Result
#define ADC_PPB3RESULT_SIGN_S      12U
#define ADC_PPB3RESULT_SIGN_M      0xFFFFF000U // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4RESULT register
//
//*************************************************************************************************
#define ADC_PPB4RESULT_PPBRESULT_S 0U
#define ADC_PPB4RESULT_PPBRESULT_M 0xFFFU      // ADC Post Processing Block 4 Result
#define ADC_PPB4RESULT_SIGN_S      12U
#define ADC_PPB4RESULT_SIGN_M      0xFFFFF000U // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOCFRC1 register
//
//*************************************************************************************************
#define ADC_SOCFRC1_SOC0  0x1U     // SOC0 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC1  0x2U     // SOC1 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC2  0x4U     // SOC2 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC3  0x8U     // SOC3 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC4  0x10U    // SOC4 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC5  0x20U    // SOC5 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC6  0x40U    // SOC6 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC7  0x80U    // SOC7 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC8  0x100U   // SOC8 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC9  0x200U   // SOC9 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC10 0x400U   // SOC10 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC11 0x800U   // SOC11 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC12 0x1000U  // SOC12 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC13 0x2000U  // SOC13 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC14 0x4000U  // SOC14 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC15 0x8000U  // SOC15 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC16 0x10000U // SOC16 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC17 0x20000U // SOC17 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC18 0x40000U // SOC18 Force Start of Conversion Bit
#define ADC_SOCFRC1_SOC19 0x80000U // SOC19 Force Start of Conversion Bit
//*****************************************************************************
//
// Useful defines used within the driver functions. Not intended for use by
// application code.
//
//*****************************************************************************
#define ADC_NUM_INTERRUPTS 1U

#define ADC_SOCxCTL_OFFSET_BASE    ADC_O_SOC0CTL
#define ADC_RESULTx_OFFSET_BASE    ADC_O_RESULT0
#define ADC_INTSELxNy_OFFSET_BASE  ADC_O_INTSEL
#define ADC_PPBxRESULT_OFFSET_BASE ADC_O_PPBRESULT

#define ADC_PPBxCONFIG_STEP (ADC_O_PPB2CONFIG - ADC_O_PPB1CONFIG)
#define ADC_PPBxTRIPHI_STEP (ADC_O_PPB2TRIPHI - ADC_O_PPB1TRIPHI)
#define ADC_PPBxTRIPLO_STEP (ADC_O_PPB2TRIPLO - ADC_O_PPB1TRIPLO)
#define ADC_PPBxSTAMP_STEP  (ADC_O_PPB2STAMP - ADC_O_PPB1STAMP)
#define ADC_PPBxOFFCAL_STEP (ADC_O_PPB2OFFCAL - ADC_O_PPB1OFFCAL)
#define ADC_PPBxOFFREF_STEP (ADC_O_PPB2OFFREF - ADC_O_PPB1OFFREF)

#define ADC_PPBTRIP_MASK ((uint32_t)ADC_PPB1TRIPHI_LIMITHI_M | (uint32_t)ADC_PPB1TRIPHI_HSIGN)
// #define ADC_INT_REF_TSSLOPE         (*(int16_t *)((uintptr_t)0x710D5))
// #define ADC_INT_REF_TSOFFSET        (*(int16_t *)((uintptr_t)0x710D6))
// #define ADC_EXT_REF_TSSLOPE         (*(int16_t *)((uintptr_t)0x710D3))
// #define ADC_EXT_REF_TSOFFSET        (*(int16_t *)((uintptr_t)0x710D4))

#ifndef DOXYGEN_PDF_IGNORE
//*****************************************************************************
//
// Values that can be passed to ADC_enablePPBEvent(), ADC_disablePPBEvent(),
// ADC_enablePPBEventInterrupt(), ADC_disablePPBEventInterrupt(), and
// ADC_clearPPBEventStatus() as the intFlags and evtFlags parameters. They also
// make up the enumerated bit field returned by ADC_getPPBEventStatus().
//
//*****************************************************************************
#define ADC_EVT_TRIPHI 0x0001U //!< Trip High Event
#define ADC_EVT_TRIPLO 0x0002U //!< Trip Low Event
#define ADC_EVT_ZERO   0x0004U //!< Zero Crossing Event

//*****************************************************************************
//
// Values that can be passed to ADC_forceMultipleSOC() as socMask parameter.
// These values can be OR'd together to trigger multiple SOCs at a time.
//
//*****************************************************************************
#define ADC_FORCE_SOC0  0x0001U  //!< SW trigger ADC SOC 0
#define ADC_FORCE_SOC1  0x0002U  //!< SW trigger ADC SOC 1
#define ADC_FORCE_SOC2  0x0004U  //!< SW trigger ADC SOC 2
#define ADC_FORCE_SOC3  0x0008U  //!< SW trigger ADC SOC 3
#define ADC_FORCE_SOC4  0x0010U  //!< SW trigger ADC SOC 4
#define ADC_FORCE_SOC5  0x0020U  //!< SW trigger ADC SOC 5
#define ADC_FORCE_SOC6  0x0040U  //!< SW trigger ADC SOC 6
#define ADC_FORCE_SOC7  0x0080U  //!< SW trigger ADC SOC 7
#define ADC_FORCE_SOC8  0x0100U  //!< SW trigger ADC SOC 8
#define ADC_FORCE_SOC9  0x0200U  //!< SW trigger ADC SOC 9
#define ADC_FORCE_SOC10 0x0400U  //!< SW trigger ADC SOC 10
#define ADC_FORCE_SOC11 0x0800U  //!< SW trigger ADC SOC 11
#define ADC_FORCE_SOC12 0x1000U  //!< SW trigger ADC SOC 12
#define ADC_FORCE_SOC13 0x2000U  //!< SW trigger ADC SOC 13
#define ADC_FORCE_SOC14 0x4000U  //!< SW trigger ADC SOC 14
#define ADC_FORCE_SOC15 0x8000U  //!< SW trigger ADC SOC 15
#define ADC_FORCE_SOC16 0x10000U //!< SW trigger ADC SOC 16
#define ADC_FORCE_SOC17 0x20000U //!< SW trigger ADC SOC 17
#define ADC_FORCE_SOC18 0x40000U //!< SW trigger ADC SOC 18
#define ADC_FORCE_SOC19 0x80000U //!< SW trigger ADC SOC 19

#endif
// ####
#endif
