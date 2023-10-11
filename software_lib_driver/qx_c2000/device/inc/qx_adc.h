/**
 **************************************************************************
 * @file     qx_adc.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_ADC_H
#define QX_ADC_H

#include "qx_define.h"
#include "hw_adc.h"

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// ADC Individual Register Bit Definitions:

struct ADCCTL_BITS
{                         // bits description
    vu32 SWLDO_HS_LU : 1; // 0 Output data type selection
    vu32 SELVI_HD_LS : 1; // 1 Input type selection
    vu32 INTPULSEPOS : 1; // 2 ADC Interrupt Pulse Position
    vu32 rsvd1       : 1; // 3 Reserved
    vu32 BIAS_C      : 3; // 6:4 SAR comparator power dissipation control signal
    vu32 ADCPWDNZ    : 1; // 7 ADC Power Down
    vu32 CLK_DLY_SEL : 2; // 9:8 Data sampling clock delay selection signal
    vu32 MD_ADC      : 2; // 11:10 ADC work mode control signal
    vu32 rsvd2       : 4; // 15:12 Reserved
    vu32 ADCBSY      : 1; // 16 ADC Busy
    vu32 PRESCALE    : 5; // 21:17 ADC clock divider
    vu32 ADCBSYCHN   : 5; // 26:22 Reserved
    vu32 rsvd3       : 5; // 31:27 Reserved
};

union ADCCTL_REG
{
    vu32 all;
    struct ADCCTL_BITS bit;
};

struct ADCINTFLG_BITS
{                      // bits description
    vu32 ADCINT1 : 1;  // 0: ADC Interrupt 1 Flag
    vu32 ADCINT2 : 1;  // 1: ADC Interrupt 2 Flag
    vu32 ADCINT3 : 1;  // 2: ADC Interrupt 3 Flag
    vu32 ADCINT4 : 1;  // 3: ADC Interrupt 4 Flag
    vu32 rsvd1   : 28; // 31:4 Reserved
};

union ADCINTFLG_REG
{
    vu32 all;
    struct ADCINTFLG_BITS bit;
};

struct ADCINTSEL_BITS
{                      // bits description
    vu32 INT1SEL  : 5; // 4:0 ADCINT EOC Source Select
    vu32 INT1EN   : 1; // 5 ADCINT Interrupt Enable
    vu32 INT1CONT : 1; // 6 ADCINT Continue to Interrupt Mode
    vu32 rsvd1    : 1; // 7 Reserved
    vu32 INT2SEL  : 5; // 12:8 ADCINT EOC Source Select
    vu32 INT2EN   : 1; // 13 ADCINT Interrupt Enable
    vu32 INT2CONT : 1; // 14 ADCINT Continue to Interrupt Mode
    vu32 rsvd2    : 1; // 15 Reserved
    vu32 INT3SEL  : 5; // 20:16 ADCINT EOC Source Select
    vu32 INT3EN   : 1; // 21 ADCINT Interrupt Enable
    vu32 INT3CONT : 1; // 22 ADCINT Continue to Interrupt Mode
    vu32 rsvd3    : 1; // 23 Reserved
    vu32 INT4SEL  : 5; // 28:24 ADCINT EOC Source Select
    vu32 INT4EN   : 1; // 29 ADCINT Interrupt Enable
    vu32 INT4CONT : 1; // 30 ADCINT Continue to Interrupt Mode
    vu32 rsvd4    : 1; // 31 Reserved
};

union ADCINTSEL_REG
{
    vu32 all;
    struct ADCINTSEL_BITS bit;
};

struct ADCINTFLGCLR_BITS
{                      // bits description
    vu32 ADCINT1 : 1;  // 0: ADC Interrupt Flag Clear
    vu32 ADCINT2 : 1;  // 1: ADC Interrupt Flag Clear
    vu32 ADCINT3 : 1;  // 2: ADC Interrupt Flag Clear
    vu32 ADCINT4 : 1;  // 3: ADC Interrupt Flag Clear
    vu32 rsvd1   : 28; // 31:4 Reserved
};

union ADCINTFLGCLR_REG
{
    vu32 all;
    struct ADCINTFLGCLR_BITS bit;
};

struct ADCINTOVF_BITS
{                      // bits description
    vu32 ADCINT1 : 1;  // 0: ADC Interrupt Overflow Flags
    vu32 ADCINT2 : 1;  // 1: ADC Interrupt Overflow Flags
    vu32 ADCINT3 : 1;  // 2: ADC Interrupt Overflow Flags
    vu32 ADCINT4 : 1;  // 3: ADC Interrupt Overflow Flags
    vu32 rsvd1   : 28; // 31:4 Reserved
};

union ADCINTOVF_REG
{
    vu32 all;
    struct ADCINTOVF_BITS bit;
};

struct ADCINTOVFCLR_BITS
{                      // bits description
    vu32 ADCINT1 : 1;  // 0: ADC Interrupt Overflow Clear Bits
    vu32 ADCINT2 : 1;  // 1: ADC Interrupt Overflow Clear Bits
    vu32 ADCINT3 : 1;  // 2: ADC Interrupt Overflow Clear Bits
    vu32 ADCINT4 : 1;  // 3: ADC Interrupt Overflow Clear Bits
    vu32 rsvd1   : 28; // 31:4 Reserved
};

union ADCINTOVFCLR_REG
{
    vu32 all;
    struct ADCINTOVFCLR_BITS bit;
};

struct ADCSOC0CTL_BITS
{                      // bits description
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC0 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC0 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC0 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC0CTL_REG
{
    vu32 all;
    struct ADCSOC0CTL_BITS bit;
};

struct ADCSOC1CTL_BITS
{
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC1 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC1 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC1 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC1CTL_REG
{
    vu32 all;
    struct ADCSOC1CTL_BITS bit;
};

struct ADCSOC2CTL_BITS
{
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC2 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC2 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC2 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC2CTL_REG
{
    vu32 all;
    struct ADCSOC2CTL_BITS bit;
};

struct ADCSOC3CTL_BITS
{
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC3 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC3 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC3 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC3CTL_REG
{
    vu32 all;
    struct ADCSOC3CTL_BITS bit;
};

struct ADCSOC4CTL_BITS
{
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC4 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC4 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC4 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC4CTL_REG
{
    vu32 all;
    struct ADCSOC4CTL_BITS bit;
};

struct ADCSOC5CTL_BITS
{
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC5 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC5 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC5 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC5CTL_REG
{
    vu32 all;
    struct ADCSOC5CTL_BITS bit;
};

struct ADCSOC6CTL_BITS
{
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC6 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC6 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC6 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC6CTL_REG
{
    vu32 all;
    struct ADCSOC6CTL_BITS bit;
};

struct ADCSOC7CTL_BITS
{                      // bits description
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC6 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC6 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC6 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC7CTL_REG
{
    vu32 all;
    struct ADCSOC7CTL_BITS bit;
};

struct ADCSOC8CTL_BITS
{                      // bits description
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC6 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC6 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC6 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC8CTL_REG
{
    vu32 all;
    struct ADCSOC8CTL_BITS bit;
};

struct ADCSOC9CTL_BITS
{                      // bits description
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC6 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC6 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC6 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC9CTL_REG
{
    vu32 all;
    struct ADCSOC9CTL_BITS bit;
};

struct ADCSOC10CTL_BITS
{                      // bits description
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC6 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC6 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC6 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC10CTL_REG
{
    vu32 all;
    struct ADCSOC10CTL_BITS bit;
};

struct ADCSOC11CTL_BITS
{                      // bits description
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC6 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC6 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC6 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC11CTL_REG
{
    vu32 all;
    struct ADCSOC11CTL_BITS bit;
};

struct ADCSOC12CTL_BITS
{                      // bits description
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC6 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC6 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC6 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC12CTL_REG
{
    vu32 all;
    struct ADCSOC12CTL_BITS bit;
};

struct ADCSOC13CTL_BITS
{                      // bits description
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC6 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC6 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC6 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC13CTL_REG
{
    vu32 all;
    struct ADCSOC13CTL_BITS bit;
};

struct ADCSOC14CTL_BITS
{                      // bits description
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC6 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC6 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC6 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC14CTL_REG
{
    vu32 all;
    struct ADCSOC14CTL_BITS bit;
};

struct ADCSOC15CTL_BITS
{                      // bits description
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC6 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC6 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC6 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC15CTL_REG
{
    vu32 all;
    struct ADCSOC15CTL_BITS bit;
};
struct ADCSOC16CTL_BITS
{                      // bits description
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC6 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC6 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC6 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC16CTL_REG
{
    vu32 all;
    struct ADCSOC16CTL_BITS bit;
};

struct ADCSOC17CTL_BITS
{                      // bits description
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC6 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC6 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC6 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC17CTL_REG
{
    vu32 all;
    struct ADCSOC17CTL_BITS bit;
};

struct ADCSOC18CTL_BITS
{                      // bits description
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC6 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC6 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC6 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC18CTL_REG
{
    vu32 all;
    struct ADCSOC18CTL_BITS bit;
};

struct ADCSOC19CTL_BITS
{                      // bits description
    vu32 rsvd1   : 3;  // 2:0 Reserved
    vu32 TRIGSEL : 5;  // 7:3 SOC6 Trigger Source Select
    vu32 ACQPS   : 4;  // 11:8 SOC6 Acquisition Prescale
    vu32 CHSEL   : 5;  // 16:12 SOC6 Channel Select
    vu32 rsvd2   : 15; // 31:17 Reserved
};

union ADCSOC19CTL_REG
{
    vu32 all;
    struct ADCSOC19CTL_BITS bit;
};

struct ADCEVTSTAT_BITS
{                         // bits description
    vu32 PPB1TRIPHI : 1;  // 0   Post Processing Block Trip High Flag
    vu32 PPB1TRIPLO : 1;  // 1   Post Processing Block Trip Low Flag
    vu32 PPB1ZERO   : 1;  // 2   Post Processing Block Zero Crossing Flag
    vu32 PPB2TRIPHI : 1;  // 3   Post Processing Block Trip High Flag
    vu32 PPB2TRIPLO : 1;  // 4   Post Processing Block Trip Low Flag
    vu32 PPB2ZERO   : 1;  // 5   Post Processing Block Zero Crossing Flag
    vu32 PPB3TRIPHI : 1;  // 6   Post Processing Block Trip High Flag
    vu32 PPB3TRIPLO : 1;  // 7   Post Processing Block Trip Low Flag
    vu32 PPB3ZERO   : 1;  // 8   Post Processing Block Zero Crossing Flag
    vu32 PPB4TRIPHI : 1;  // 9   Post Processing Block Trip High Flag
    vu32 PPB4TRIPLO : 1;  // 10   Post Processing Block Trip Low Flag
    vu32 PPB4ZERO   : 1;  // 11   Post Processing Block Zero Crossing Flag
    vu32 rsvd1      : 20; // 31:12 Reserved
};

union ADCEVTSTAT_REG
{
    vu32 all;
    struct ADCEVTSTAT_BITS bit;
};

struct ADCEVTCLR_BITS
{                         // bits description
    vu32 PPB1TRIPHI : 1;  // 0   Post Processing Block Trip High Flag
    vu32 PPB1TRIPLO : 1;  // 1   Post Processing Block Trip Low Flag
    vu32 PPB1ZERO   : 1;  // 2   Post Processing Block Zero Crossing Flag
    vu32 PPB2TRIPHI : 1;  // 3   Post Processing Block Trip High Flag
    vu32 PPB2TRIPLO : 1;  // 4   Post Processing Block Trip Low Flag
    vu32 PPB2ZERO   : 1;  // 5   Post Processing Block Zero Crossing Flag
    vu32 PPB3TRIPHI : 1;  // 6   Post Processing Block Trip High Flag
    vu32 PPB3TRIPLO : 1;  // 7   Post Processing Block Trip Low Flag
    vu32 PPB3ZERO   : 1;  // 8   Post Processing Block Zero Crossing Flag
    vu32 PPB4TRIPHI : 1;  // 9   Post Processing Block Trip High Flag
    vu32 PPB4TRIPLO : 1;  // 10   Post Processing Block Trip Low Flag
    vu32 PPB4ZERO   : 1;  // 11   Post Processing Block Zero Crossing Flag
    vu32 rsvd1      : 20; // 31:12 Reserved
};

union ADCEVTCLR_REG
{
    vu32 all;
    struct ADCEVTCLR_BITS bit;
};

struct ADCEVTSEL_BITS
{                         // bits description
    vu32 PPB1TRIPHI : 1;  // 0 Post Processing Block 1 Trip High Event Enable
    vu32 PPB1TRIPLO : 1;  // 1 Post Processing Block 1 Trip Low Event Enable
    vu32 PPB1ZERO   : 1;  // 2 Post Processing Block 1 Zero Crossing Event Enable
    vu32 PPB2TRIPHI : 1;  // 3 Post Processing Block 1 Trip High Event Enable
    vu32 PPB2TRIPLO : 1;  // 4 Post Processing Block 1 Trip Low Event Enable
    vu32 PPB2ZERO   : 1;  // 5 Post Processing Block 1 Zero Crossing Event Enable
    vu32 PPB3TRIPHI : 1;  // 6 Post Processing Block 1 Trip High Event Enable
    vu32 PPB3TRIPLO : 1;  // 7 Post Processing Block 1 Trip Low Event Enable
    vu32 PPB3ZERO   : 1;  // 8 Post Processing Block 1 Zero Crossing Event Enable
    vu32 PPB4TRIPHI : 1;  // 9 Post Processing Block 1 Trip High Event Enable
    vu32 PPB4TRIPLO : 1;  // 10 Post Processing Block 1 Trip Low Event Enable
    vu32 PPB4ZERO   : 1;  // 11 Post Processing Block 1 Zero Crossing Event Enable
    vu32 rsvd       : 20; // 31:12 Reserved
};

union ADCEVTSEL_REG
{
    vu32 all;
    struct ADCEVTSEL_BITS bit;
};

struct ADCEVTINTSEL_BITS
{                         // bits description
    vu32 PPB1TRIPHI : 1;  // 0 Post Processing Block Trip High Interrupt Enable
    vu32 PPB1TRIPLO : 1;  // 1 Post Processing Block Trip Low Interrupt Enable
    vu32 PPB1ZERO   : 1;  // 2 Post Processing Block Zero Crossing Interrupt Enable
    vu32 PPB2TRIPHI : 1;  // 3 Post Processing Block Trip High Interrupt Enable
    vu32 PPB2TRIPLO : 1;  // 4 Post Processing Block Trip Low Interrupt Enable
    vu32 PPB2ZERO   : 1;  // 5 Post Processing Block Zero Crossing Interrupt Enable
    vu32 PPB3TRIPHI : 1;  // 6 Post Processing Block Trip High Interrupt Enable
    vu32 PPB3TRIPLO : 1;  // 7 Post Processing Block Trip Low Interrupt Enable
    vu32 PPB3ZERO   : 1;  // 8 Post Processing Block Zero Crossing Interrupt Enable
    vu32 PPB4TRIPHI : 1;  // 9 Post Processing Block Trip High Interrupt Enable
    vu32 PPB4TRIPLO : 1;  // 10 Post Processing Block Trip Low Interrupt Enable
    vu32 PPB4ZERO   : 1;  // 11 Post Processing Block Zero Crossing Interrupt Enable
    vu32 rsvd1      : 20; // 32:12	Reserved
};

union ADCEVTINTSEL_REG
{
    vu32 all;
    struct ADCEVTINTSEL_BITS bit;
};

struct ADCCOUNTER_BITS
{                        // bits description
    vu32 FREECOUNT : 12; // 11:0 ADC Free Running Counter Value
    vu32 rsvd1     : 4;  // 15:12 Reserved
};

union ADCCOUNTER_REG
{
    vu32 all;
    struct ADCCOUNTER_BITS bit;
};

struct ADCREV_BITS
{                  // bits description
    vu32 TYPE : 8; // 7:0 ADC Type
    vu32 REV  : 8; // 15:8 ADC Revision
};

union ADCREV_REG
{
    vu32 all;
    struct ADCREV_BITS bit;
};

struct ADCPPB1CONFIG_BITS
{                         // bits description
    vu32 CONFIG     : 5;  // 4:0 ADC Post Processing Block 1 Configuration
    vu32 TWOSCOMPEN : 1;  // 5 ADC Post Processing Block 1 Two's Complement Enable
    vu32 CBCEN      : 1;  // 6 Cycle By Cycle Enable
    vu32 rsvd1      : 25; // 31:6 Reserved
};

union ADCPPB1CONFIG_REG
{
    vu32 all;
    struct ADCPPB1CONFIG_BITS bit;
};

struct ADCPPB1STAMP_BITS
{                       // bits description
    vu32 DLYSTAMP : 12; // 11:0 ADC Post Processing Block 1 Delay Time Stamp
    vu32 rsvd1    : 20; // 31:12 Reserved
};

union ADCPPB1STAMP_REG
{
    vu32 all;
    struct ADCPPB1STAMP_BITS bit;
};

struct ADCPPB1OFFREF_BITS
{                     // bits description
    vu32 OFFREF : 16; // 15:0 ADC Post Processing Block Offset Correction
    vu32 rsvd   : 16; // 31:16 Reserved
};

union ADCPPB1OFFREF_REG
{
    vu32 all;
    struct ADCPPB1OFFREF_BITS bit;
};

struct ADCPPB1TRIPHI_BITS
{                      // bits description
    vu32 LIMITHI : 12; // 11:0 ADC Post Processing Block 1 Trip High Limit
    vu32 HSIGN   : 1;  // 12 High Limit Sign Bit
    vu32 rsvd1   : 19; // 31:13 Reserved
};

union ADCPPB1TRIPHI_REG
{
    vu32 all;
    struct ADCPPB1TRIPHI_BITS bit;
};

struct ADCPPB1TRIPLO_BITS
{                       // bits description
    vu32 LIMITLO  : 12; // 11:0 ADC Post Processing Block Trip Low Limit
    vu32 LSIGN    : 1;  // 12 Low Limit Sign Bit
    vu32 rsvd1    : 7;  // 19:13 Reserved
    vu32 REQSTAMP : 12; // 31:20 ADC Post Processing Block Request Time Stamp
};

union ADCPPB1TRIPLO_REG
{
    vu32 all;
    struct ADCPPB1TRIPLO_BITS bit;
};

struct ADCPPB1OFFCAL_BITS
{                     // bits description
    vu32 OFFCAL : 10; // 9:0 ADC Post Processing Block Offset Correction
    vu32 rsvd1  : 22; // 31:10 Reserved
};

union ADCPPB1OFFCAL_REG
{
    vu32 all;
    struct ADCPPB1OFFCAL_BITS bit;
};

struct ADCPPB2CONFIG_BITS
{
    vu32 CONFIG     : 5;  // 4:0 ADC Post Processing Block 2 Configuration
    vu32 TWOSCOMPEN : 1;  // 5 ADC Post Processing Block 2 Two's Complement Enable
    vu32 CBCEN      : 1;  // 6 Cycle By Cycle Enable
    vu32 rsvd1      : 25; // 31:6 Reserved
};

union ADCPPB2CONFIG_REG
{
    vu32 all;
    struct ADCPPB2CONFIG_BITS bit;
};

struct ADCPPB2STAMP_BITS
{
    vu32 DLYSTAMP : 12; // 11:0 ADC Post Processing Block 2 Delay Time Stamp
    vu32 rsvd1    : 20; // 31:12 Reserved
};

union ADCPPB2STAMP_REG
{
    vu32 all;
    struct ADCPPB2STAMP_BITS bit;
};

struct ADCPPB2OFFREF_BITS
{
    vu32 OFFREF : 16; // 15:0 ADC Post Processing Block Offset Correction
    vu32 rsvd   : 16; // 31:16 Reserved
};

union ADCPPB2OFFREF_REG
{
    vu32 all;
    struct ADCPPB2OFFREF_BITS bit;
};

struct ADCPPB2TRIPHI_BITS
{
    vu32 LIMITHI : 12; // 11:0 ADC Post Processing Block 2 Trip High Limit
    vu32 HSIGN   : 1;  // 12 High Limit Sign Bit
    vu32 rsvd1   : 19; // 31:13 Reserved
};

union ADCPPB2TRIPHI_REG
{
    vu32 all;
    struct ADCPPB2TRIPHI_BITS bit;
};

struct ADCPPB2TRIPLO_BITS
{
    vu32 LIMITLO  : 12; // 11:0 ADC Post Processing Block Trip Low Limit
    vu32 LSIGN    : 1;  // 12 Low Limit Sign Bit
    vu32 rsvd1    : 7;  // 19:13 Reserved
    vu32 REQSTAMP : 12; // 31:20 ADC Post Processing Block Request Time Stamp
};

union ADCPPB2TRIPLO_REG
{
    vu32 all;
    struct ADCPPB2TRIPLO_BITS bit;
};

struct ADCPPB2OFFCAL_BITS
{                     // bits description
    vu32 OFFCAL : 10; // 9:0 ADC Post Processing Block Offset Correction
    vu32 rsvd1  : 22; // 31:10 Reserved
};

union ADCPPB2OFFCAL_REG
{
    vu32 all;
    struct ADCPPB2OFFCAL_BITS bit;
};

struct ADCPPB3CONFIG_BITS
{
    vu32 CONFIG     : 5;  // 4:0 ADC Post Processing Block 3 Configuration
    vu32 TWOSCOMPEN : 1;  // 5 ADC Post Processing Block 3 Two's Complement Enable
    vu32 CBCEN      : 1;  // 6 Cycle By Cycle Enable
    vu32 rsvd1      : 25; // 31:7 Reserved
};

union ADCPPB3CONFIG_REG
{
    vu32 all;
    struct ADCPPB3CONFIG_BITS bit;
};

struct ADCPPB3STAMP_BITS
{
    vu32 DLYSTAMP : 12; // 11:0 ADC Post Processing Block 3 Delay Time Stamp
    vu32 rsvd1    : 20; // 31:12 Reserved
};

union ADCPPB3STAMP_REG
{
    vu32 all;
    struct ADCPPB3STAMP_BITS bit;
};

struct ADCPPB3OFFREF_BITS
{
    vu32 OFFREF : 16; // 15:0 ADC Post Processing Block Offset Correction
    vu32 rsvd   : 16; // 31:16 Reserved
};

union ADCPPB3OFFREF_REG
{
    vu32 all;
    struct ADCPPB3OFFREF_BITS bit;
};

struct ADCPPB3TRIPHI_BITS
{
    vu32 LIMITHI : 12; // 11:0 ADC Post Processing Block 3 Trip High Limit
    vu32 HSIGN   : 1;  // 12 High Limit Sign Bit
    vu32 rsvd1   : 19; // 31:13 Reserved
};

union ADCPPB3TRIPHI_REG
{
    vu32 all;
    struct ADCPPB3TRIPHI_BITS bit;
};

struct ADCPPB3TRIPLO_BITS
{
    vu32 LIMITLO  : 12; // 11:0 ADC Post Processing Block Trip Low Limit
    vu32 LSIGN    : 1;  // 12 Low Limit Sign Bit
    vu32 rsvd1    : 7;  // 19:13 Reserved
    vu32 REQSTAMP : 12; // 31:20 ADC Post Processing Block Request Time Stamp
};

union ADCPPB3TRIPLO_REG
{
    vu32 all;
    struct ADCPPB3TRIPLO_BITS bit;
};

struct ADCPPB3OFFCAL_BITS
{                     // bits description
    vu32 OFFCAL : 10; // 9:0 ADC Post Processing Block Offset Correction
    vu32 rsvd1  : 22; // 31:10 Reserved
};

union ADCPPB3OFFCAL_REG
{
    vu32 all;
    struct ADCPPB3OFFCAL_BITS bit;
};

struct ADCPPB4CONFIG_BITS
{
    vu32 CONFIG     : 5;  // 4:0 ADC Post Processing Block 4 Configuration
    vu32 TWOSCOMPEN : 1;  // 5 ADC Post Processing Block 4 Two's Complement Enable
    vu32 CBCEN      : 1;  // 6 Cycle By Cycle Enable
    vu32 rsvd1      : 25; // 31:7 Reserved
};

union ADCPPB4CONFIG_REG
{
    vu32 all;
    struct ADCPPB4CONFIG_BITS bit;
};

struct ADCPPB4STAMP_BITS
{
    vu32 DLYSTAMP : 12; // 11:0 ADC Post Processing Block 4 Delay Time Stamp
    vu32 rsvd1    : 20; // 31:12 Reserved
};

union ADCPPB4STAMP_REG
{
    vu32 all;
    struct ADCPPB4STAMP_BITS bit;
};

struct ADCPPB4OFFREF_BITS
{
    vu32 OFFREF : 16; // 15:0 ADC Post Processing Block 4 Offset Correction
    vu32 rsvd   : 16; // 31:16 Reserved
};

union ADCPPB4OFFREF_REG
{
    vu32 all;
    struct ADCPPB4OFFREF_BITS bit;
};

struct ADCPPB4TRIPHI_BITS
{
    vu32 LIMITHI : 12; // 11:0 ADC Post Processing Block 4 Trip High Limit
    vu32 HSIGN   : 1;  // 12 High Limit Sign Bit
    vu32 rsvd1   : 19; // 31:13 Reserved
};

union ADCPPB4TRIPHI_REG
{
    vu32 all;
    struct ADCPPB4TRIPHI_BITS bit;
};

struct ADCPPB4TRIPLO_BITS
{
    vu32 LIMITLO  : 12; // 11:0 ADC Post Processing Block Trip Low Limit
    vu32 LSIGN    : 1;  // 12 Low Limit Sign Bit
    vu32 rsvd1    : 7;  // 19:13 Reserved
    vu32 REQSTAMP : 12; // 31:20 ADC Post Processing Block Request Time Stamp
};

union ADCPPB4TRIPLO_REG
{
    vu32 all;
    struct ADCPPB4TRIPLO_BITS bit;
};

struct ADCPPB4OFFCAL_BITS
{                     // bits description
    vu32 OFFCAL : 10; // 9:0 ADC Post Processing Block Offset Correction
    vu32 rsvd1  : 22; // 31:10 Reserved
};

union ADCPPB4OFFCAL_REG
{
    vu32 all;
    struct ADCPPB4OFFCAL_BITS bit;
};

struct ADCSOCFRC_BITS
{                    // bits description
    vu32 SOC0  : 1;  // 0 SOC0 Force Start of Conversion Bit
    vu32 SOC1  : 1;  // 1 SOC1 Force Start of Conversion Bit
    vu32 SOC2  : 1;  // 2 SOC2 Force Start of Conversion Bit
    vu32 SOC3  : 1;  // 3 SOC3 Force Start of Conversion Bit
    vu32 SOC4  : 1;  // 4 SOC4 Force Start of Conversion Bit
    vu32 SOC5  : 1;  // 5 SOC5 Force Start of Conversion Bit
    vu32 SOC6  : 1;  // 6 SOC6 Force Start of Conversion Bit
    vu32 SOC7  : 1;  // 7 SOC7 Force Start of Conversion Bit
    vu32 SOC8  : 1;  // 8 SOC8 Force Start of Conversion Bit
    vu32 SOC9  : 1;  // 9 SOC9 Force Start of Conversion Bit
    vu32 SOC10 : 1;  // 10 SOC10 Force Start of Conversion Bit
    vu32 SOC11 : 1;  // 11 SOC11 Force Start of Conversion Bit
    vu32 SOC12 : 1;  // 12 SOC12 Force Start of Conversion Bit
    vu32 SOC13 : 1;  // 13 SOC13 Force Start of Conversion Bit
    vu32 SOC14 : 1;  // 14 SOC14 Force Start of Conversion Bit
    vu32 SOC15 : 1;  // 15 SOC15 Force Start of Conversion Bit
    vu32 SOC16 : 1;  // 16 SOC16 Force Start of Conversion Bit
    vu32 SOC17 : 1;  // 17 SOC17 Force Start of Conversion Bit
    vu32 SOC18 : 1;  // 18 SOC18 Force Start of Conversion Bit
    vu32 SOC19 : 1;  // 19 SOC19 Force Start of Conversion Bit
    vu32 rsvd  : 12; // 20:31 Reserved
};

union ADCSOCFRC_REG
{
    vu32 all;
    struct ADCSOCFRC_BITS bit;
};

struct ADCSOCFLG_BITS
{                    // bits description
    vu32 SOC0  : 1;  // 0 SOC0 Start of Conversion Flag
    vu32 SOC1  : 1;  // 1 SOC1 Start of Conversion Flag
    vu32 SOC2  : 1;  // 2 SOC2 Start of Conversion Flag
    vu32 SOC3  : 1;  // 3 SOC3 Start of Conversion Flag
    vu32 SOC4  : 1;  // 4 SOC4 Start of Conversion Flag
    vu32 SOC5  : 1;  // 5 SOC5 Start of Conversion Flag
    vu32 SOC6  : 1;  // 6 SOC6 Start of Conversion Flag
    vu32 SOC7  : 1;  // 7 SOC7 Start of Conversion Flag
    vu32 SOC8  : 1;  // 8 SOC8 Start of Conversion Flag
    vu32 SOC9  : 1;  // 9 SOC9 Start of Conversion Flag
    vu32 SOC10 : 1;  // 10 SOC10 Start of Conversion Flag
    vu32 SOC11 : 1;  // 11 SOC11 Start of Conversion Flag
    vu32 SOC12 : 1;  // 12 SOC12 Start of Conversion Flag
    vu32 SOC13 : 1;  // 13 SOC13 Start of Conversion Flag
    vu32 SOC14 : 1;  // 14 SOC14 Start of Conversion Flag
    vu32 SOC15 : 1;  // 15 SOC15 Start of Conversion Flag
    vu32 SOC16 : 1;  // 16 SOC16 Start of Conversion Flag
    vu32 SOC17 : 1;  // 17 SOC17 Start of Conversion Flag
    vu32 SOC18 : 1;  // 18 SOC18 Start of Conversion Flag
    vu32 SOC19 : 1;  // 19 SOC19 Start of Conversion Flag
    vu32 rsvd  : 12; // 20:31 Reserved
};

union ADCSOCFLG_REG
{
    vu32 all;
    struct ADCSOCFLG_BITS bit;
};

struct ADCSOCOVF_BITS
{                    // bits description
    vu32 SOC0  : 1;  // 0 SOC0 Start of Conversion Overflow Flag
    vu32 SOC1  : 1;  // 1 SOC1 Start of Conversion Overflow Flag
    vu32 SOC2  : 1;  // 2 SOC2 Start of Conversion Overflow Flag
    vu32 SOC3  : 1;  // 3 SOC3 Start of Conversion Overflow Flag
    vu32 SOC4  : 1;  // 4 SOC4 Start of Conversion Overflow Flag
    vu32 SOC5  : 1;  // 5 SOC5 Start of Conversion Overflow Flag
    vu32 SOC6  : 1;  // 6 SOC6 Start of Conversion Overflow Flag
    vu32 SOC7  : 1;  // 7 SOC7 Start of Conversion Overflow Flag
    vu32 SOC8  : 1;  // 8 SOC8 Start of Conversion Overflow Flag
    vu32 SOC9  : 1;  // 9 SOC9 Start of Conversion Overflow Flag
    vu32 SOC10 : 1;  // 10 SOC10 Start of Conversion Overflow Flag
    vu32 SOC11 : 1;  // 11 SOC11 Start of Conversion Overflow Flag
    vu32 SOC12 : 1;  // 12 SOC12 Start of Conversion Overflow Flag
    vu32 SOC13 : 1;  // 13 SOC13 Start of Conversion Overflow Flag
    vu32 SOC14 : 1;  // 14 SOC14 Start of Conversion Overflow Flag
    vu32 SOC15 : 1;  // 15 SOC15 Start of Conversion Overflow Flag
    vu32 SOC16 : 1;  // 12 SOC16 Start of Conversion Overflow Flag
    vu32 SOC17 : 1;  // 13 SOC17 Start of Conversion Overflow Flag
    vu32 SOC18 : 1;  // 14 SOC18 Start of Conversion Overflow Flag
    vu32 SOC19 : 1;  // 15 SOC19 Start of Conversion Overflow Flag
    vu32 rsvd  : 12; // 20:31 Reserved
};

union ADCSOCOVF_REG
{
    vu32 all;
    struct ADCSOCOVF_BITS bit;
};

struct ADCSOCOVFCLR_BITS
{                    // bits description
    vu32 SOC0  : 1;  // 0 SOC0 Clear Start of Conversion Overflow Bit
    vu32 SOC1  : 1;  // 1 SOC1 Clear Start of Conversion Overflow Bit
    vu32 SOC2  : 1;  // 2 SOC2 Clear Start of Conversion Overflow Bit
    vu32 SOC3  : 1;  // 3 SOC3 Clear Start of Conversion Overflow Bit
    vu32 SOC4  : 1;  // 4 SOC4 Clear Start of Conversion Overflow Bit
    vu32 SOC5  : 1;  // 5 SOC5 Clear Start of Conversion Overflow Bit
    vu32 SOC6  : 1;  // 6 SOC6 Clear Start of Conversion Overflow Bit
    vu32 SOC7  : 1;  // 7 SOC7 Clear Start of Conversion Overflow Bit
    vu32 SOC8  : 1;  // 8 SOC8 Clear Start of Conversion Overflow Bit
    vu32 SOC9  : 1;  // 9 SOC9 Clear Start of Conversion Overflow Bit
    vu32 SOC10 : 1;  // 10 SOC10 Clear Start of Conversion Overflow Bit
    vu32 SOC11 : 1;  // 11 SOC11 Clear Start of Conversion Overflow Bit
    vu32 SOC12 : 1;  // 12 SOC12 Clear Start of Conversion Overflow Bit
    vu32 SOC13 : 1;  // 13 SOC13 Clear Start of Conversion Overflow Bit
    vu32 SOC14 : 1;  // 14 SOC14 Clear Start of Conversion Overflow Bit
    vu32 SOC15 : 1;  // 15 SOC15 Clear Start of Conversion Overflow Bit
    vu32 SOC16 : 1;  // 12 SOC16 Clear Start of Conversion Overflow Bit
    vu32 SOC17 : 1;  // 13 SOC17 Clear Start of Conversion Overflow Bit
    vu32 SOC18 : 1;  // 14 SOC18 Clear Start of Conversion Overflow Bit
    vu32 SOC19 : 1;  // 15 SOC19 Clear Start of Conversion Overflow Bit
    vu32 rsvd  : 12; // 20:31 Reserved
};

union ADCSOCOVFCLR_REG
{
    vu32 all;
    struct ADCSOCOVFCLR_BITS bit;
};

struct ADCINTCYCLE_BITS
{                    // bits description
    vu32 DELAY : 16; // 15:0 ADC Interrupt Pulse Positiont
    vu32 rsvd  : 16; // 31:16 Reserved
};

union ADCINTCYCLE_REG
{
    vu32 all;
    struct ADCINTCYCLE_BITS bit;
};

struct ADC_REGS
{
    union ADCCTL_REG ADCCTL;               // ADC Control Register
    union ADCINTFLG_REG ADCINTFLG;         // ADC Interrupt Flag Register
    union ADCINTSEL_REG ADCINTSEL;         // ADC Interrupt Enable/Disable Register
    union ADCINTFLGCLR_REG ADCINTFLGCLR;   // ADC Interrupt Flag Clear Register
    union ADCINTOVF_REG ADCINTOVF;         // ADC Interrupt Overflow Register
    union ADCINTOVFCLR_REG ADCINTOVFCLR;   // ADC Interrupt Overflow Clear Register
    union ADCSOC0CTL_REG ADCSOC0CTL;       // ADC SOC0 Control Register
    union ADCSOC1CTL_REG ADCSOC1CTL;       // ADC SOC1 Control Register
    union ADCSOC2CTL_REG ADCSOC2CTL;       // ADC SOC2 Control Register
    union ADCSOC3CTL_REG ADCSOC3CTL;       // ADC SOC3 Control Register
    union ADCSOC4CTL_REG ADCSOC4CTL;       // ADC SOC4 Control Register
    union ADCSOC5CTL_REG ADCSOC5CTL;       // ADC SOC5 Control Register
    union ADCSOC6CTL_REG ADCSOC6CTL;       // ADC SOC6 Control Register
    union ADCSOC7CTL_REG ADCSOC7CTL;       // ADC SOC7 Control Register
    union ADCSOC8CTL_REG ADCSOC8CTL;       // ADC SOC8 Control Register
    union ADCSOC9CTL_REG ADCSOC9CTL;       // ADC SOC9 Control Register
    union ADCSOC10CTL_REG ADCSOC10CTL;     // ADC SOC10 Control Register
    union ADCSOC11CTL_REG ADCSOC11CTL;     // ADC SOC11 Control Register
    union ADCSOC12CTL_REG ADCSOC12CTL;     // ADC SOC12 Control Register
    union ADCSOC13CTL_REG ADCSOC13CTL;     // ADC SOC13 Control Register
    union ADCSOC14CTL_REG ADCSOC14CTL;     // ADC SOC14 Control Register
    union ADCSOC15CTL_REG ADCSOC15CTL;     // ADC SOC15 Control Register
    union ADCSOC16CTL_REG ADCSOC16CTL;     // ADC SOC16 Control Register
    union ADCSOC17CTL_REG ADCSOC17CTL;     // ADC SOC17 Control Register
    union ADCSOC18CTL_REG ADCSOC18CTL;     // ADC SOC18 Control Register
    union ADCSOC19CTL_REG ADCSOC19CTL;     // ADC SOC19 Control Register
    union ADCEVTSTAT_REG ADCEVTSTAT;       // ADC Event Status Register
    union ADCEVTCLR_REG ADCEVTCLR;         // ADC Event Clear Register
    union ADCEVTSEL_REG ADCEVTSEL;         // ADC Event Selection Register
    union ADCEVTINTSEL_REG ADCEVTINTSEL;   // ADC Event Interrupt Selection Register
    union ADCCOUNTER_REG ADCCOUNTER;       // ADC Counter Register
    union ADCREV_REG ADCREV;               // ADC Revision Register
    union ADCPPB1CONFIG_REG ADCPPB1CONFIG; // ADC Post Processing Block 1 Configuration Register
    union ADCPPB1STAMP_REG ADCPPB1STAMP;   // ADC Post Processing Block 1 Timestamp Register
    union ADCPPB1OFFREF_REG ADCPPB1OFFREF; // ADC PPB1 Offset Reference Register
    union ADCPPB1TRIPHI_REG ADCPPB1TRIPHI; // ADC PPB1 Trip High Register
    union ADCPPB1TRIPLO_REG ADCPPB1TRIPLO; // ADC PPB1 Trip Low/Trigger Time Stamp Register
    union ADCPPB1OFFCAL_REG ADCPPB1OFFCAL; // ADC PPB1 Offset Calibration Register
    union ADCPPB2CONFIG_REG ADCPPB2CONFIG; // ADC Post Processing Block 2 Configuration Register
    union ADCPPB2STAMP_REG ADCPPB2STAMP;   // ADC Post Processing Block 2 Timestamp Register
    union ADCPPB2OFFREF_REG ADCPPB2OFFREF; // ADC PPB2 Offset Reference Register
    union ADCPPB2TRIPHI_REG ADCPPB2TRIPHI; // ADC PPB2 Trip High Register
    union ADCPPB2TRIPLO_REG ADCPPB2TRIPLO; // ADC PPB2 Trip Low/Trigger Time Stamp Register
    union ADCPPB2OFFCAL_REG ADCPPB2OFFCAL; // ADC PPB2 Offset Calibration Register
    union ADCPPB3CONFIG_REG ADCPPB3CONFIG; // ADC Post Processing Block 3 Configuration Register
    union ADCPPB3STAMP_REG ADCPPB3STAMP;   // ADC Post Processing Block 3 Timestamp Register
    union ADCPPB3OFFREF_REG ADCPPB3OFFREF; // ADC PPB3 Offset Reference Register
    union ADCPPB3TRIPHI_REG ADCPPB3TRIPHI; // ADC PPB3 Trip High Register
    union ADCPPB3TRIPLO_REG ADCPPB3TRIPLO; // ADC PPB3 Trip Low/Trigger Time Stamp Register
    union ADCPPB3OFFCAL_REG ADCPPB3OFFCAL; // ADC PPB3 Offset Calibration Register
    union ADCPPB4CONFIG_REG ADCPPB4CONFIG; // ADC Post Processing Block 4 Configuration Register
    union ADCPPB4STAMP_REG ADCPPB4STAMP;   // ADC Post Processing Block 4 Timestamp Register
    union ADCPPB4OFFREF_REG ADCPPB4OFFREF; // ADC PPB4 Offset Reference Register
    union ADCPPB4TRIPHI_REG ADCPPB4TRIPHI; // ADC PPB4 Trip High Register
    union ADCPPB4TRIPLO_REG ADCPPB4TRIPLO; // ADC PPB4 Trip Low/Trigger Time Stamp Register
    union ADCPPB4OFFCAL_REG ADCPPB4OFFCAL; // ADC PPB4 Offset Calibration Register
    union ADCSOCFRC_REG ADCSOCFRC;         // ADC SOC Force Register
    union ADCSOCFLG_REG ADCSOCFLG;         // ADC SOC Force Register
    union ADCSOCOVF_REG ADCSOCOVF;         // ADC SOC Force Register
    union ADCSOCOVFCLR_REG ADCSOCOVFCLR;   // ADC SOC Force Register
    union ADCINTCYCLE_REG ADCINTCYCLE;     // ADC Early Interrupt Generation Cycle
};

struct ADCRESULT0_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // 31:12 Reserved
};

union ADCRESULT0_REG
{
    vu32 all;
    struct ADCRESULT0_BITS bit;
};

struct ADCRESULT1_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // Reserved
};

union ADCRESULT1_REG
{
    vu32 all;
    struct ADCRESULT1_BITS bit;
};

struct ADCRESULT2_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // Reserved
};

union ADCRESULT2_REG
{
    vu32 all;
    struct ADCRESULT2_BITS bit;
};

struct ADCRESULT3_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // Reserved
};

union ADCRESULT3_REG
{
    vu32 all;
    struct ADCRESULT3_BITS bit;
};

struct ADCRESULT4_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // Reserved
};

union ADCRESULT4_REG
{
    vu32 all;
    struct ADCRESULT4_BITS bit;
};

struct ADCRESULT5_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // Reserved
};

union ADCRESULT5_REG
{
    vu32 all;
    struct ADCRESULT5_BITS bit;
};

struct ADCRESULT6_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // Reserved
};

union ADCRESULT6_REG
{
    vu32 all;
    struct ADCRESULT6_BITS bit;
};

struct ADCRESULT7_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // Reserved
};

union ADCRESULT7_REG
{
    vu32 all;
    struct ADCRESULT7_BITS bit;
};

struct ADCRESULT8_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // 31:12 Reserved
};

union ADCRESULT8_REG
{
    vu32 all;
    struct ADCRESULT8_BITS bit;
};

struct ADCRESULT9_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // 31:12 Reserved
};

union ADCRESULT9_REG
{
    vu32 all;
    struct ADCRESULT9_BITS bit;
};

struct ADCRESULT10_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // 31:12 Reserved
};

union ADCRESULT10_REG
{
    vu32 all;
    struct ADCRESULT10_BITS bit;
};

struct ADCRESULT11_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // 31:12 Reserved
};

union ADCRESULT11_REG
{
    vu32 all;
    struct ADCRESULT11_BITS bit;
};

struct ADCRESULT12_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // 31:12 Reserved
};

union ADCRESULT12_REG
{
    vu32 all;
    struct ADCRESULT12_BITS bit;
};

struct ADCRESULT13_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // 31:12 Reserved
};

union ADCRESULT13_REG
{
    vu32 all;
    struct ADCRESULT13_BITS bit;
};

struct ADCRESULT14_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // 31:12 Reserved
};

union ADCRESULT14_REG
{
    vu32 all;
    struct ADCRESULT14_BITS bit;
};

struct ADCRESULT15_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // 31:12 Reserved
};

union ADCRESULT15_REG
{
    vu32 all;
    struct ADCRESULT15_BITS bit;
};

struct ADCRESULT16_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // 31:12 Reserved
};

union ADCRESULT16_REG
{
    vu32 all;
    struct ADCRESULT16_BITS bit;
};

struct ADCRESULT17_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // 31:12 Reserved
};

union ADCRESULT17_REG
{
    vu32 all;
    struct ADCRESULT17_BITS bit;
};

struct ADCRESULT18_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // 31:12 Reserved
};

union ADCRESULT18_REG
{
    vu32 all;
    struct ADCRESULT18_BITS bit;
};

struct ADCRESULT19_BITS
{
    vu32 RESULT : 12; // ADC Result
    vu32 rsvd1  : 20; // 31:12 Reserved
};

union ADCRESULT19_REG
{
    vu32 all;
    struct ADCRESULT19_BITS bit;
};

struct ADCPPB1RESULT_BITS
{                         // bits description
    vu32 PPB1RESULT : 12; // 11:0 ADC Post Processing Block 1 Result
    vu32 SIGN       : 20; // 31:12 Sign Extended Bits
};

union ADCPPB1RESULT_REG
{
    vu32 all;
    struct ADCPPB1RESULT_BITS bit;
};

struct ADCPPB2RESULT_BITS
{                         // bits description
    vu32 PPB2RESULT : 12; // 11:0 ADC Post Processing Block 2 Result
    vu32 SIGN       : 20; // 31:12 Sign Extended Bits
};

union ADCPPB2RESULT_REG
{
    vu32 all;
    struct ADCPPB2RESULT_BITS bit;
};

struct ADCPPB3RESULT_BITS
{                         // bits description
    vu32 PPB3RESULT : 12; // 11:0 ADC Post Processing Block 3 Result
    vu32 SIGN       : 20; // 31:12 Sign Extended Bits
};

union ADCPPB3RESULT_REG
{
    vu32 all;
    struct ADCPPB3RESULT_BITS bit;
};

struct ADCPPB4RESULT_BITS
{                         // bits description
    vu32 PPB4RESULT : 12; // 11:0 ADC Post Processing Block 4 Result
    vu32 SIGN       : 20; // 31:12 Sign Extended Bits
};

union ADCPPB4RESULT_REG
{
    vu32 all;
    struct ADCPPB4RESULT_BITS bit;
};

struct ADC_RESULT_REGS
{
    union ADCRESULT0_REG ADCRESULT0;       // ADC Result 0 Register
    union ADCRESULT1_REG ADCRESULT1;       // ADC Result 1 Register
    union ADCRESULT2_REG ADCRESULT2;       // ADC Result 2 Register
    union ADCRESULT3_REG ADCRESULT3;       // ADC Result 3 Register
    union ADCRESULT4_REG ADCRESULT4;       // ADC Result 4 Register
    union ADCRESULT5_REG ADCRESULT5;       // ADC Result 5 Register
    union ADCRESULT6_REG ADCRESULT6;       // ADC Result 6 Register
    union ADCRESULT7_REG ADCRESULT7;       // ADC Result 7 Register
    union ADCRESULT8_REG ADCRESULT8;       // ADC Result 8 Register
    union ADCRESULT9_REG ADCRESULT9;       // ADC Result 9 Register
    union ADCRESULT10_REG ADCRESULT10;     // ADC Result 10 Register
    union ADCRESULT11_REG ADCRESULT11;     // ADC Result 11 Register
    union ADCRESULT12_REG ADCRESULT12;     // ADC Result 12 Register
    union ADCRESULT13_REG ADCRESULT13;     // ADC Result 13 Register
    union ADCRESULT14_REG ADCRESULT14;     // ADC Result 14 Register
    union ADCRESULT15_REG ADCRESULT15;     // ADC Result 15 Register
    union ADCRESULT16_REG ADCRESULT16;     // ADC Result 16 Register
    union ADCRESULT17_REG ADCRESULT17;     // ADC Result 17 Register
    union ADCRESULT18_REG ADCRESULT18;     // ADC Result 18 Register
    union ADCRESULT19_REG ADCRESULT19;     // ADC Result 19 Register
    union ADCPPB1RESULT_REG ADCPPB1RESULT; // ADC Post Processing Block1 Result Register
    union ADCPPB2RESULT_REG ADCPPB2RESULT; // ADC Post Processing Block2 Result Register
    union ADCPPB3RESULT_REG ADCPPB3RESULT; // ADC Post Processing Block3 Result Register
    union ADCPPB4RESULT_REG ADCPPB4RESULT; // ADC Post Processing Block4 Result Register
};

//---------------------------------------------------------------------------
// ADC External References & Function Declarations:
//
#define ADCA_RESULT_BASE 0x0100B100U
#define ADCB_RESULT_BASE 0x0100B300U
#define ADCC_RESULT_BASE 0x0100B500U

#define AdcaRegs       ((struct ADC_REGS *)ADCA_REGS_BASE)
#define AdcaResultRegs ((struct ADC_RESULT_REGS *)(ADCA_REGS_BASE + 0x100U))

#define AdcbRegs       ((struct ADC_REGS *)ADCB_REGS_BASE)
#define AdcbResultRegs ((struct ADC_RESULT_REGS *)(ADCB_REGS_BASE + 0x100U))

#define AdccRegs       ((struct ADC_REGS *)ADCC_REGS_BASE)
#define AdccResultRegs ((struct ADC_RESULT_REGS *)(ADCC_REGS_BASE + 0x100U))

//*****************************************************************************
//
//! Values that can be passed to ADC_setPrescaler() as the \e clkPrescale
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_CLK_DIV_2_0  = 1U,  //!< ADCCLK = (input clock) / 2.0
    ADC_CLK_DIV_4_0  = 2U,  //!< ADCCLK = (input clock) / 4.0
    ADC_CLK_DIV_6_0  = 3U,  //!< ADCCLK = (input clock) / 6.0
    ADC_CLK_DIV_8_0  = 4U,  //!< ADCCLK = (input clock) / 8.0
    ADC_CLK_DIV_10_0 = 5U,  //!< ADCCLK = (input clock) / 10.0
    ADC_CLK_DIV_12_0 = 6U,  //!< ADCCLK = (input clock) / 12.0
    ADC_CLK_DIV_14_0 = 7U,  //!< ADCCLK = (input clock) / 14.0
    ADC_CLK_DIV_16_0 = 8U,  //!< ADCCLK = (input clock) / 16.0
    ADC_CLK_DIV_18_0 = 9U,  //!< ADCCLK = (input clock) / 18.0
    ADC_CLK_DIV_20_0 = 10U, //!< ADCCLK = (input clock) / 20.0
    ADC_CLK_DIV_22_0 = 11U, //!< ADCCLK = (input clock) / 22.0
    ADC_CLK_DIV_24_0 = 12U, //!< ADCCLK = (input clock) / 24.0
    ADC_CLK_DIV_26_0 = 13U, //!< ADCCLK = (input clock) / 26.0
    ADC_CLK_DIV_28_0 = 14U, //!< ADCCLK = (input clock) / 28.0
    ADC_CLK_DIV_30_0 = 15U, //!< ADCCLK = (input clock) / 30.0
    ADC_CLK_DIV_32_0 = 16U, //!< ADCCLK = (input clock) / 32.0
    ADC_CLK_DIV_34_0 = 17U, //!< ADCCLK = (input clock) / 34.0
    ADC_CLK_DIV_36_0 = 18U, //!< ADCCLK = (input clock) / 36.0
    ADC_CLK_DIV_38_0 = 19U, //!< ADCCLK = (input clock) / 38.0
    ADC_CLK_DIV_40_0 = 20U, //!< ADCCLK = (input clock) / 40.0
    ADC_CLK_DIV_42_0 = 21U, //!< ADCCLK = (input clock) / 42.0
    ADC_CLK_DIV_44_0 = 22U, //!< ADCCLK = (input clock) / 44.0
    ADC_CLK_DIV_46_0 = 23U, //!< ADCCLK = (input clock) / 46.0
    ADC_CLK_DIV_48_0 = 24U, //!< ADCCLK = (input clock) / 48.0
    ADC_CLK_DIV_50_0 = 25U, //!< ADCCLK = (input clock) / 50.0
    ADC_CLK_DIV_52_0 = 26U, //!< ADCCLK = (input clock) / 52.0
    ADC_CLK_DIV_54_0 = 27U, //!< ADCCLK = (input clock) / 54.0
    ADC_CLK_DIV_56_0 = 28U, //!< ADCCLK = (input clock) / 56.0
    ADC_CLK_DIV_58_0 = 29U, //!< ADCCLK = (input clock) / 58.0
    ADC_CLK_DIV_60_0 = 30U, //!< ADCCLK = (input clock) / 60.0
    ADC_CLK_DIV_62_0 = 31U  //!< ADCCLK = (input clock) / 62.0
} ADC_ClkPrescale;

typedef enum
{
    ADC_SAMPLE_WINDOW_1  = 0U,  //!< Set ADC acquisition window duration to 1
    ADC_SAMPLE_WINDOW_2  = 1U,  //!< Set ADC acquisition window duration to 2
    ADC_SAMPLE_WINDOW_3  = 2U,  //!< Set ADC acquisition window duration to 3
    ADC_SAMPLE_WINDOW_4  = 3U,  //!< Set ADC acquisition window duration to 4
    ADC_SAMPLE_WINDOW_5  = 4U,  //!< Set ADC acquisition window duration to 5
    ADC_SAMPLE_WINDOW_6  = 5U,  //!< Set ADC acquisition window duration to 6
    ADC_SAMPLE_WINDOW_7  = 6U,  //!< Set ADC acquisition window duration to 7
    ADC_SAMPLE_WINDOW_8  = 7U,  //!< Set ADC acquisition window duration to 8
    ADC_SAMPLE_WINDOW_10 = 8U,  //!< Set ADC acquisition window duration to 10
    ADC_SAMPLE_WINDOW_20 = 9U,  //!< Set ADC acquisition window duration to 20
    ADC_SAMPLE_WINDOW_30 = 10U, //!< Set ADC acquisition window duration to 30
    ADC_SAMPLE_WINDOW_40 = 11U, //!< Set ADC acquisition window duration to 40
    ADC_SAMPLE_WINDOW_50 = 12U, //!< Set ADC acquisition window duration to 50
    ADC_SAMPLE_WINDOW_60 = 13U, //!< Set ADC acquisition window duration to 60
    ADC_SAMPLE_WINDOW_70 = 14U, //!< Set ADC acquisition window duration to 70
    ADC_SAMPLE_WINDOW_80 = 15U  //!< Set ADC acquisition window duration to 80
} ADC_SampleWindow;

//*****************************************************************************
//
//! Values that can be passed to ADC_setupSOC() as the \e trigger
//! parameter to specify the event that will trigger a conversion to start.
//! It is also used with ADC_setBurstModeConfig() and
//! ADC_triggerRepeaterSelect().
//
//*****************************************************************************
typedef enum
{
    ADC_TRIGGER_SW_ONLY    = 0U,  //!< Software only
    ADC_TRIGGER_CPU0_TINT0 = 1U,  //!< CPU0 Timer 0, TINT0
    ADC_TRIGGER_CPU0_TINT1 = 2U,  //!< CPU0 Timer 1, TINT1
    ADC_TRIGGER_CPU0_TINT2 = 3U,  //!< CPU0 Timer 2, TINT2
    ADC_TRIGGER_GPIO       = 4U,  //!< GPIO, ADCEXTSOC
    ADC_TRIGGER_EPWM1_SOCA = 5U,  //!< ePWM1, ADCSOCA
    ADC_TRIGGER_EPWM1_SOCB = 6U,  //!< ePWM1, ADCSOCB
    ADC_TRIGGER_EPWM2_SOCA = 7U,  //!< ePWM2, ADCSOCA
    ADC_TRIGGER_EPWM2_SOCB = 8U,  //!< ePWM2, ADCSOCB
    ADC_TRIGGER_EPWM3_SOCA = 9U,  //!< ePWM3, ADCSOCA
    ADC_TRIGGER_EPWM3_SOCB = 10U, //!< ePWM3, ADCSOCB
    ADC_TRIGGER_EPWM4_SOCA = 11U, //!< ePWM4, ADCSOCA
    ADC_TRIGGER_EPWM4_SOCB = 12U, //!< ePWM4, ADCSOCB
    ADC_TRIGGER_EPWM5_SOCA = 13U, //!< ePWM5, ADCSOCA
    ADC_TRIGGER_EPWM5_SOCB = 14U, //!< ePWM5, ADCSOCB
    ADC_TRIGGER_EPWM6_SOCA = 15U, //!< ePWM6, ADCSOCA
    ADC_TRIGGER_EPWM6_SOCB = 16U, //!< ePWM6, ADCSOCB
    ADC_TRIGGER_EPWM7_SOCA = 17U, //!< ePWM7, ADCSOCA
    ADC_TRIGGER_EPWM7_SOCB = 18U, //!< ePWM7, ADCSOCB
    ADC_TRIGGER_EPWM8_SOCA = 19U, //!< ePWM8, ADCSOCA
    ADC_TRIGGER_EPWM8_SOCB = 20U, //!< ePWM8, ADCSOCB
    ADC_TRIGGER_CPU1_TINT0 = 21U, //!< CPU1 Timer 0, TINT0
    ADC_TRIGGER_CPU1_TINT1 = 22U, //!< CPU1 Timer 1, TINT1
    ADC_TRIGGER_CPU1_TINT2 = 23U  //!< CPU1 Timer 2, TINT2
} ADC_Trigger;

//*****************************************************************************
//
//! Values that can be passed to ADC_setupSOC() as the \e channel
//! parameter. This is the input pin on which the signal to be converted is
//! located.
//
//*****************************************************************************
typedef enum
{
    ADC_CH_ADCIN0  = 0U,  //!< ADCIN0 is converted
    ADC_CH_ADCIN1  = 1U,  //!< ADCIN1 is converted
    ADC_CH_ADCIN2  = 2U,  //!< ADCIN2 is converted
    ADC_CH_ADCIN3  = 3U,  //!< ADCIN3 is converted
    ADC_CH_ADCIN4  = 4U,  //!< ADCIN4 is converted
    ADC_CH_ADCIN5  = 5U,  //!< ADCIN5 is converted
    ADC_CH_ADCIN6  = 6U,  //!< ADCIN6 is converted
    ADC_CH_ADCIN7  = 7U,  //!< ADCIN7 is converted
    ADC_CH_ADCIN8  = 8U,  //!< ADCIN8 is converted
    ADC_CH_ADCIN9  = 9U,  //!< ADCIN9 is converted
    ADC_CH_ADCIN10 = 10U, //!< ADCIN10 is converted
    ADC_CH_ADCIN11 = 11U, //!< ADCIN11 is converted
    ADC_CH_ADCIN12 = 12U, //!< ADCIN12 is converted
    ADC_CH_ADCIN13 = 13U, //!< ADCIN13 is converted
    ADC_CH_ADCIN14 = 14U, //!< ADCIN14 is converted
    ADC_CH_ADCIN15 = 15U, //!< ADCIN15 is converted
    ADC_CH_ADCIN16 = 16U, //!< ADCIN16 is converted
    ADC_CH_ADCIN17 = 17U, //!< ADCIN17 is converted
    ADC_CH_ADCIN18 = 18U, //!< ADCIN18 is converted
    ADC_CH_ADCIN19 = 19U  //!< ADCIN19 is converted
} ADC_Channel;

//*****************************************************************************
//
//! Values that can be passed in as the \e ppbNumber parameter for several
//! functions.
//
//*****************************************************************************
typedef enum
{
    ADC_PPB_NUMBER1 = 0U, //!< Post-processing block 1
    ADC_PPB_NUMBER2 = 1U, //!< Post-processing block 2
    ADC_PPB_NUMBER3 = 2U, //!< Post-processing block 3
    ADC_PPB_NUMBER4 = 3U  //!< Post-processing block 4
} ADC_PPBNumber;

//*****************************************************************************
//
//! Values that can be passed in as the \e socNumber parameter for several
//! functions. This value identifies the start-of-conversion (SOC) that a
//! function is configuring or accessing. Note that in some cases (for example,
//! ADC_setInterruptSource()) \e socNumber is used to refer to the
//! corresponding end-of-conversion (EOC).
//
//*****************************************************************************
typedef enum
{
    ADC_SOC_NUMBER0  = 0U,  //!< SOC/EOC number 0
    ADC_SOC_NUMBER1  = 1U,  //!< SOC/EOC number 1
    ADC_SOC_NUMBER2  = 2U,  //!< SOC/EOC number 2
    ADC_SOC_NUMBER3  = 3U,  //!< SOC/EOC number 3
    ADC_SOC_NUMBER4  = 4U,  //!< SOC/EOC number 4
    ADC_SOC_NUMBER5  = 5U,  //!< SOC/EOC number 5
    ADC_SOC_NUMBER6  = 6U,  //!< SOC/EOC number 6
    ADC_SOC_NUMBER7  = 7U,  //!< SOC/EOC number 7
    ADC_SOC_NUMBER8  = 8U,  //!< SOC/EOC number 8
    ADC_SOC_NUMBER9  = 9U,  //!< SOC/EOC number 9
    ADC_SOC_NUMBER10 = 10U, //!< SOC/EOC number 10
    ADC_SOC_NUMBER11 = 11U, //!< SOC/EOC number 11
    ADC_SOC_NUMBER12 = 12U, //!< SOC/EOC number 12
    ADC_SOC_NUMBER13 = 13U, //!< SOC/EOC number 13
    ADC_SOC_NUMBER14 = 14U, //!< SOC/EOC number 14
    ADC_SOC_NUMBER15 = 15U, //!< SOC/EOC number 15
    ADC_SOC_NUMBER16 = 16U, //!< SOC/EOC number 16
    ADC_SOC_NUMBER17 = 17U, //!< SOC/EOC number 17
    ADC_SOC_NUMBER18 = 18U, //!< SOC/EOC number 18
    ADC_SOC_NUMBER19 = 19U  //!< SOC/EOC number 19
} ADC_SOCNumber;

//*****************************************************************************
//
//! Values that can be passed in as the \e trigger parameter for the
//! ADC_setInterruptSOCTrigger() function.
//
//*****************************************************************************
typedef enum
{
    ADC_INT_SOC_TRIGGER_NONE   = 0U, //!< No ADCINT will trigger the SOC
    ADC_INT_SOC_TRIGGER_ADCINT = 1U, //!< ADCINT will trigger the SOC
} ADC_IntSOCTrigger;

//*****************************************************************************
//
//! Values that can be passed to ADC_setInterruptPulseMode() as the
//! \e pulseMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Occurs at the end of the acquisition window
    ADC_PULSE_END_OF_ACQ_WIN = 0x0U,
    //! Occurs at the end of the conversion
    ADC_PULSE_END_OF_CONV = 0x1U
} ADC_PulseMode;

//*****************************************************************************
//
//! Values that can be passed to ADC_enableInterrupt(), ADC_disableInterrupt(),
//! and ADC_getInterruptStatus() as the \e adcIntNum parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_INT_NUMBER1 = 0U, //!< ADCINT1 Interrupt
    ADC_INT_NUMBER2 = 1U, //!< ADCINT2 Interrupt
    ADC_INT_NUMBER3 = 2U, //!< ADCINT3 Interrupt
    ADC_INT_NUMBER4 = 3U  //!< ADCINT4 Interrupt
} ADC_IntNumber;

//*****************************************************************************
//
//! Values that can be passed to ADC_setVREF() as the \e refMode parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_REFERENCE_INTERNAL = 0U,
    ADC_REFERENCE_EXTERNAL = 1U
} ADC_ReferenceMode;

//*****************************************************************************
//
//! Values that can be passed to ADC_setVREF() as the refVoltage parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_REFERENCE_3_3V       = 0U,
    ADC_REFERENCE_2_0V       = 1U,
    ADC_REFERENCE_2_5V       = 2U,
    ADC_REFERENCE_BYPASS_AVD = 3U
} ADC_ReferenceVoltage;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks an ADC base address.
//!
//! \param base specifies the ADC module base address.
//!
//! This function determines if a ADC module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool ADC_isBaseValid(uint32_t base)
{
    return ((base == ADCA_BASE) || (base == ADCB_BASE) || (base == ADCC_BASE));
}
#endif

//*****************************************************************************
//
//! Configures the analog-to-digital converter module prescaler.
//!
//! \param base is the base address of the ADC module.
//! \param clkPrescale is the ADC clock prescaler.
//!
//! This function configures the ADC module's ADCCLK.
//!
//! The \e clkPrescale parameter specifies the value by which the input clock
//! is divided to make the ADCCLK.  The clkPrescale value can be specified with
//! any of the following enum values:
//! \b ADC_CLK_DIV_1_0, \b ADC_CLK_DIV_2_0, \b ADC_CLK_DIV_3_0, ...,
//! \b ADC_CLK_DIV_6_0, \b ADC_CLK_DIV_7_0, or \b ADC_CLK_DIV_8_0.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_setPrescaler(uint32_t base, ADC_ClkPrescale clkPrescale)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Set the configuration of the ADC module prescaler.
    //
    EALLOW;
    ((struct ADC_REGS *)base)->ADCCTL.bit.PRESCALE = clkPrescale;
    EDIS;
}
//*****************************************************************************
//
//! Sets the timing of the end-of-conversion pulse
//!
//! \param base is the base address of the ADC module.
//! \param pulseMode is the generation mode of the EOC pulse.
//!
//! This function configures the end-of-conversion (EOC) pulse generated by ADC.
//! This pulse will be generated either at the end of the acquisition window
//! plus a number of SYSCLK cycles configured by ADC_setInterruptCycleOffset()
//! (pass \b ADC_PULSE_END_OF_ACQ_WIN into \e pulseMode) or at the end of the
//! voltage conversion, one cycle prior to the ADC result latching into it's
//! result register (pass \b ADC_PULSE_END_OF_CONV into \e pulseMode).
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_setInterruptPulseMode(uint32_t base, ADC_PulseMode pulseMode)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Set the position of the pulse.
    //
    EALLOW;
    ((struct ADC_REGS *)base)->ADCCTL.bit.INTPULSEPOS = pulseMode;
    EDIS;
}

//*****************************************************************************
//
//! Sets the timing of early interrupt generation.
//!
//! \param base is the base address of the ADC module.
//! \param cycleOffset is the cycles from an SOC falling edge to an early
//! interrupt pulse.
//!
//! This function configures cycle offset between the negative edge of a sample
//! pulse and an early interrupt pulse being generated. This number of cycles
//! is specified with the \e cycleOffset parameter.
//!
//! This function only applies when early interrupt generation is enabled. That
//! means the ADC_setInterruptPulseMode() function \e pulseMode parameter is
//! configured as \b ADC_PULSE_END_OF_ACQ_WIN.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_setInterruptCycleOffset(uint32_t base, uint16_t cycleOffset)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Set the position of the pulse.
    //
    EALLOW;
    ((struct ADC_REGS *)base)->ADCINTCYCLE.bit.DELAY = cycleOffset;
    EDIS;
}
//*****************************************************************************
//
//! Configures a start-of-conversion (SOC) in the ADC.
//!
//! \param base is the base address of the ADC module.
//! \param socNumber is the number of the start-of-conversion.
//! \param trigger the source that will cause the SOC.
//! \param channel is the number associated with the input signal.
//! \param sampleWindow is the acquisition window duration.
//!
//! This function configures the a start-of-conversion (SOC) in the ADC module.
//!
//! The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
//! from 0 to 7 specifying which SOC is to be configured on the ADC module
//! specified by \e base.
//!
//! The \e trigger specifies the event that causes the SOC such as software, a
//! timer interrupt, an ePWM event, or an ADC interrupt. It should be a value
//! in the format of \b ADC_TRIGGER_XXXX where XXXX is the event such as
//! \b ADC_TRIGGER_SW_ONLY, \b ADC_TRIGGER_CPU1_TINT0, \b ADC_TRIGGER_GPIO,
//! \b ADC_TRIGGER_EPWM1_SOCA, and so on.
//!
//! The \e channel parameter specifies the channel to be converted. In
//! single-ended mode this is a single pin given by \b ADC_CH_ADCINx where x is
//! the number identifying the pin between 0 and 7 inclusive.
//!
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_setupSOC(
    uint32_t base, ADC_SOCNumber socNumber, ADC_Trigger trigger, ADC_Channel channel, ADC_SampleWindow sampleWindow)
{
    uint32_t ctlRegAddr;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Calculate address for the SOC control register.
    //
    ctlRegAddr = base + 0x18U + ((uint32_t)socNumber * 4U);

    //
    // Set the configuration of the specified SOC.
    //
    EALLOW;
    ((struct ADCSOC0CTL_BITS *)ctlRegAddr)->CHSEL   = channel;
    ((struct ADCSOC0CTL_BITS *)ctlRegAddr)->ACQPS   = sampleWindow;
    ((struct ADCSOC0CTL_BITS *)ctlRegAddr)->TRIGSEL = trigger;
    EDIS;
}

//*****************************************************************************
//
//! Powers up the analog-to-digital converter core.
//!
//! \param base is the base address of the ADC module.
//!
//! This function powers up the analog circuitry inside the analog core.
//!
//! \note Allow at least a 500us delay before sampling after calling this API.
//! If you enable multiple ADCs, you can delay after they all have begun
//! powering up.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_enableConverter(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Set the bit that powers up the analog circuitry.
    //
    EALLOW;
    ((struct ADC_REGS *)base)->ADCCTL.bit.ADCPWDNZ = 1;
    EDIS;
}

//*****************************************************************************
//
//! Powers down the analog-to-digital converter module.
//!
//! \param base is the base address of the ADC module.
//!
//! This function powers down the analog circuitry inside the analog core.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_disableConverter(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Clear the bit that powers down the analog circuitry.
    //
    EALLOW;
    ((struct ADC_REGS *)base)->ADCCTL.bit.ADCPWDNZ = 0;
    EDIS;
}

//*****************************************************************************
//
//! Forces a SOC flag to a 1 in the analog-to-digital converter.
//!
//! \param base is the base address of the ADC module.
//! \param socNumber is the number of the start-of-conversion.
//!
//! This function forces the SOC flag associated with the SOC specified by
//! \e socNumber. This initiates a conversion once that SOC is given
//! priority. This software trigger can be used whether or not the SOC has been
//! configured to accept some other specific trigger.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_forceSOC(uint32_t base, ADC_SOCNumber socNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Write to the register that will force a 1 to the corresponding SOC flag
    //
    ((struct ADC_REGS *)base)->ADCSOCFRC.all = ((uint16_t)1U << (uint16_t)socNumber);
}

//*****************************************************************************
//
//! Forces multiple SOC flags to 1 in the analog-to-digital converter.
//!
//! \param base is the base address of the ADC module.
//! \param socMask is the SOCs to be forced through software
//!
//! This function forces the SOCFRC1 flags associated with the SOCs specified
//! by \e socMask. This initiates a conversion once the desired SOCs are given
//! priority. This software trigger can be used whether or not the SOC has been
//! configured to accept some other specific trigger.
//! Valid values for \e socMask parameter can be any of the individual
//! ADC_FORCE_SOCx values or any of their OR'd combination to trigger multiple
//! SOCs.
//!
//! \note To trigger SOC0, SOC1 and SOC2, value (ADC_FORCE_SOC0 |
//! ADC_FORCE_SOC1 | ADC_FORCE_SOC2) should be passed as socMask.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_forceMultipleSOC(uint32_t base, uint32_t socMask)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Write to the register that will force a 1 to desired SOCs
    //
    ((struct ADC_REGS *)base)->ADCSOCFRC.all = socMask;
}

//*****************************************************************************
//
//! Gets the current ADC interrupt status.
//!
//! \param base is the base address of the ADC module.
//!
//! This function returns the interrupt status for the analog-to-digital
//! converter.
//!
//! \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to get
//! the interrupt status for the given interrupt number of the ADC module.
//!
//! \return \b true if the interrupt flag for the specified interrupt number is
//! set and \b false if it is not.
//
//*****************************************************************************
static inline bool ADC_getInterruptStatus(uint32_t base, ADC_IntNumber adcIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    //
    // Get the specified ADC interrupt status.
    //
    return ((((struct ADC_REGS *)base)->ADCINTFLG.all) & (1U << (uint16_t)adcIntNum)) != 0U;
}

//*****************************************************************************
//
//! Clears ADC interrupt sources.
//!
//! \param base is the base address of the ADC module.
//!
//! This function clears the specified ADC interrupt sources so that they no
//! longer assert. If not in continuous mode, this function must be called
//! before any further interrupt pulses may occur.
//!
//! \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to express
//! which of the four interrupts of the ADC module should be cleared.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_clearInterruptStatus(uint32_t base, ADC_IntNumber adcIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Clear the specified interrupt.
    //
    ((struct ADC_REGS *)base)->ADCINTFLGCLR.all = ((uint16_t)1U << (uint16_t)adcIntNum);
}

//*****************************************************************************
//
//! Gets the current ADC interrupt overflow status.
//!
//! \param base is the base address of the ADC module.
//!
//! This function returns the interrupt overflow status for the
//! analog-to-digital converter. An overflow condition is generated
//! irrespective of the continuous mode.
//!
//! \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to get
//! the interrupt overflow status for the given interrupt number.
//!
//! \return \b true if the interrupt overflow flag for the specified interrupt
//! number is set and \b false if it is not.
//
//*****************************************************************************
static inline bool ADC_getInterruptOverflowStatus(uint32_t base, ADC_IntNumber adcIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the specified ADC interrupt status.
    //
    return ((((struct ADC_REGS *)base)->ADCINTOVF.all) & (1U << (uint16_t)adcIntNum)) != 0U;
}

//*****************************************************************************
//
//! Clears ADC interrupt overflow sources.
//!
//! \param base is the base address of the ADC module.
//!
//! This function clears the specified ADC interrupt overflow sources so that
//! they no longer assert. If software tries to clear the overflow in the same
//! cycle that hardware tries to set the overflow, then hardware has priority.
//!
//! \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to express
//! which of the four interrupt overflow status of the ADC module
//! should be cleared.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_clearInterruptOverflowStatus(uint32_t base, ADC_IntNumber adcIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Clear the specified interrupt overflow bit.
    //
    ((struct ADC_REGS *)base)->ADCINTOVFCLR.all = ((uint16_t)1U << (uint16_t)adcIntNum);
}

//*****************************************************************************
//
//! Reads the conversion result.
//!
//! \param resultBase is the base address of the ADC results.
//! \param socNumber is the number of the start-of-conversion.
//!
//! This function returns the conversion result that corresponds to the base
//! address passed into \e resultBase and the SOC passed into \e socNumber.
//!
//! The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
//! from 0 to 7 specifying which SOC's result is to be read.
//!
//! \note Take care that you are using a base address for the result registers
//! (ADCxRESULT_BASE) and not a base address for the control registers.
//!
//! \return Returns the conversion result.
//
//*****************************************************************************
static inline uint16_t ADC_readResult(uint32_t resultBase, ADC_SOCNumber socNumber)
{
    //
    // Check the arguments.
    //
    ASSERT((resultBase == ADCARESULT_BASE) || (resultBase == ADCBRESULT_BASE) || (resultBase == ADCCRESULT_BASE));
    //
    // Return the ADC result for the selected SOC.
    //
    return ((union ADCRESULT0_REG *)(resultBase + ((uint32_t)socNumber << 2)))->all;
}

//*****************************************************************************
//
//! Determines whether the ADC is busy or not.
//!
//! \param base is the base address of the ADC.
//!
//! This function allows the caller to determine whether or not the ADC is
//! busy and can sample another channel.
//!
//! \return Returns \b true if the ADC is sampling or \b false if all
//! samples are complete.
//
//*****************************************************************************
static inline bool ADC_isBusy(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Determine if the ADC is busy.
    //
    return (((struct ADC_REGS *)base)->ADCCTL.bit.ADCBSY) != 0U;
}

//*****************************************************************************
//
//! Configures a post-processing block (PPB) in the ADC.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param socNumber is the number of the start-of-conversion.
//!
//! This function associates a post-processing block with a SOC.
//!
//! The \e ppbNumber is a value \b ADC_PPB_NUMBERX where X is a value from 1 to
//! 4 inclusive that identifies a PPB to be configured.  The \e socNumber
//! number is a value \b ADC_SOC_NUMBERX where X is a number from 0 to 15
//! specifying which SOC is to be configured on the ADC module specified by
//! \e base.
//!
//! \note You can have more that one PPB associated with the same SOC, but a
//! PPB can only be configured to correspond to one SOC at a time. Also note
//! that when you have multiple PPBs for the same SOC, the calibration offset
//! that actually gets applied will be that of the PPB with the highest number.
//! Since SOC0 is the default for all PPBs, look out for unintentional
//! overwriting of a lower numbered PPB's offset.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_setupPPB(uint32_t base, ADC_PPBNumber ppbNumber, ADC_SOCNumber socNumber)
{
    uint32_t ppbAddress;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    ppbAddress = base + (0x18U * (uint32_t)ppbNumber) + 0x80U;
    //
    // Write the configuration to the register.
    //
    EALLOW;
    ((struct ADCPPB1CONFIG_BITS *)ppbAddress)->CONFIG = socNumber;
    EDIS;
}

//*****************************************************************************
//
//! Enables individual ADC PPB event sources.
//!
//! \param base is the base address of the ADC module.
//! \param evtFlags is a bit mask of the event sources to be enabled.
//!
//! This function enables the indicated ADC PPB event sources.  This will allow
//! the specified events to propagate through the X-BAR to a pin or to an ePWM
//! module.  The \e evtFlags parameter can be any of the \b ADC_EVT_TRIPHI,
//! \b ADC_EVT_TRIPLO, or \b ADC_EVT_ZERO values.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_enablePPBEvent(uint32_t base, ADC_PPBNumber ppbNumber, uint16_t evtFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT((evtFlags & ~0x7U) == 0U);

    //
    // Enable the specified event.
    //
    EALLOW;
    ((struct ADC_REGS *)base)->ADCEVTSEL.all |= evtFlags << ((uint16_t)ppbNumber * 3U);
    EDIS;
}

//*****************************************************************************
//
//! Disables individual ADC PPB event sources.
//!
//! \param base is the base address of the ADC module.
//! \param evtFlags is a bit mask of the event sources to be enabled.
//!
//! This function disables the indicated ADC PPB event sources.  This will stop
//! the specified events from propagating through the X-BAR to other modules.
//! The \e evtFlags parameter can be any of the \b ADC_EVT_TRIPHI,
//! \b ADC_EVT_TRIPLO, or \b ADC_EVT_ZERO values.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_disablePPBEvent(uint32_t base, ADC_PPBNumber ppbNumber, uint16_t evtFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT((evtFlags & ~0x7U) == 0U);

    //
    // Disable the specified event.
    //
    EALLOW;
    ((struct ADC_REGS *)base)->ADCEVTSEL.all &= ~(evtFlags << ((uint16_t)ppbNumber * 3U));
    EDIS;
}

//*****************************************************************************
//
//! Enables individual ADC PPB event interrupt sources.
//!
//! \param base is the base address of the ADC module.
//! \param intFlags is a bit mask of the interrupt sources to be enabled.
//!
//! This function enables the indicated ADC PPB interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.  The \e intFlags
//! parameter can be any of the \b ADC_EVT_TRIPHI, \b ADC_EVT_TRIPLO, or
//! \b ADC_EVT_ZERO values.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_enablePPBEventInterrupt(uint32_t base, ADC_PPBNumber ppbNumber, uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT((intFlags & ~0x7U) == 0U);

    //
    // Enable the specified event interrupts.
    //
    EALLOW;
    ((struct ADC_REGS *)base)->ADCEVTINTSEL.all |= intFlags << ((uint16_t)ppbNumber * 4U);
    EDIS;
}

//*****************************************************************************
//
//! Disables individual ADC PPB event interrupt sources.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param intFlags is a bit mask of the interrupt source to be disabled.
//!
//! This function disables the indicated ADC PPB interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.  The \e intFlags
//! parameter can be any of the \b ADC_EVT_TRIPHI, \b ADC_EVT_TRIPLO, or
//! \b ADC_EVT_ZERO values.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_disablePPBEventInterrupt(uint32_t base, ADC_PPBNumber ppbNumber, uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT((intFlags & ~0x7U) == 0U);

    //
    // Disable the specified event interrupts.
    //
    EALLOW;
    ((struct ADC_REGS *)base)->ADCEVTINTSEL.all &= ~(intFlags << ((uint16_t)ppbNumber * 4U));
    EDIS;
}

//*****************************************************************************
//
//! Gets the current ADC event status.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the event status for the analog-to-digital converter.
//!
//! \return Returns the current event status, enumerated as a bit field of
//! \b ADC_EVT_TRIPHI, \b ADC_EVT_TRIPLO, and \b ADC_EVT_ZERO.
//
//*****************************************************************************
static inline uint16_t ADC_getPPBEventStatus(uint32_t base, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the event status for the specified post-processing block.
    //
    return ((((union ADCEVTSTAT_REG *)(base + 0x68))->all >> ((uint16_t)ppbNumber * 3U)) & 0x7U);
}

//*****************************************************************************
//
//! Clears ADC event flags.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param evtFlags is a bit mask of the event source to be cleared.
//!
//! This function clears the indicated ADC PPB event flags. After an event
//! occurs this function must be called to allow additional events to be
//! produced. The \e evtFlags parameter can be any of the \b ADC_EVT_TRIPHI,
//! \b ADC_EVT_TRIPLO, or \b ADC_EVT_ZERO values.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_clearPPBEventStatus(uint32_t base, ADC_PPBNumber ppbNumber, uint16_t evtFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT((evtFlags & ~0x7U) == 0U);

    //
    // Clear the specified event interrupts.
    //
    ((struct ADC_REGS *)base)->ADCEVTCLR.all |= (evtFlags << ((uint16_t)ppbNumber * 3U));
}

//*****************************************************************************
//
//! Enables cycle-by-cycle clear of ADC PPB event flags.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function enables the automatic cycle-by-cycle clear of ADC PPB event
//! flags. When enabled, the desired PPB event flags are automatically cleared
//! on the next PPBxRESULT load, unless a set condition is also occurring at
//! the same time, in which case the set takes precedence.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_enablePPBEventCBCClear(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint32_t ppbAddress;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ppbAddress = base + (0x18U * (uint32_t)ppbNumber) + 0x80U;
    //
    // Set automatic cycle-by-cycle flag clear bit
    //
    EALLOW;
    ((struct ADCPPB1CONFIG_BITS *)ppbAddress)->CBCEN = 1;
    EDIS;
}

//*****************************************************************************
//
//! Disables cycle-by-cycle clear of ADC PPB event flags.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function disables the cycle-by-cycle clear of ADC PPB event flags. When
//! disabled, the desired PPB event flags are to be cleared explicitly in
//! software inorder to generate next set of interrupts/events.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_disablePPBEventCBCClear(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint32_t ppbAddress;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ppbAddress = base + (0x18U * (uint32_t)ppbNumber) + 0x80U;
    //
    // Clear automatic cycle-by-cycle flag clear bit
    //
    EALLOW;
    ((struct ADCPPB1CONFIG_BITS *)ppbAddress)->CBCEN = 0;
    EDIS;
}

//*****************************************************************************
//
//! Reads the processed conversion result from the PPB.
//!
//! \param resultBase is the base address of the ADC results.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the processed conversion result that corresponds to
//! the base address passed into \e resultBase and the PPB passed into
//! \e ppbNumber.
//!
//! \note Take care that you are using a base address for the result registers
//! (ADCxRESULT_BASE) and not a base address for the control registers.
//!
//! \return Returns the signed 32-bit conversion result.
//
//*****************************************************************************
static inline int32_t ADC_readPPBResult(uint32_t resultBase, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT((resultBase == ADCARESULT_BASE) || (resultBase == ADCBRESULT_BASE) || (resultBase == ADCCRESULT_BASE));
    //
    // Return the result of selected PPB.
    //
    return ((union ADCPPB1RESULT_REG *)(resultBase + 0x50U + ((uint32_t)ppbNumber * 4U)))->all;
}

//*****************************************************************************
//
//! Reads sample delay time stamp from a PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the sample delay time stamp. This delay is the number
//! of system clock cycles between the SOC being triggered and when it began
//! converting.
//!
//! \return Returns the delay time stamp.
//
//*****************************************************************************
static inline uint16_t ADC_getPPBDelayTimeStamp(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint32_t ppbAddress;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ppbAddress = base + (0x18U * (uint32_t)ppbNumber) + 0x84U;
    //
    // Return the delay time stamp.
    //
    return ((struct ADCPPB1STAMP_BITS *)ppbAddress)->DLYSTAMP;
}

//*****************************************************************************
//
//! Sets the post processing block offset correction.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param offset is the 10-bit signed value subtracted from ADC the output.
//!
//! This function sets the PPB offset correction value.  This value can be used
//! to digitally remove any system-level offset inherent in the ADCIN circuit
//! before it is stored in the appropriate result register. The \e offset
//! parameter is \b subtracted from the ADC output and is a signed value from
//! -512 to 511 inclusive. For example, when \e offset = 1, ADCRESULT = ADC
//! output - 1. When \e offset = -512, ADCRESULT = ADC output - (-512) or ADC
//! output + 512.
//!
//! Passing a zero in to the \e offset parameter will effectively disable the
//! calculation, allowing the raw ADC result to be passed unchanged into the
//! result register.
//!
//! \note If multiple PPBs are applied to the same SOC, the offset that will be
//! applied will be that of the PPB with the highest number.
//!
//! \return None
//
//*****************************************************************************
static inline void ADC_setPPBCalibrationOffset(uint32_t base, ADC_PPBNumber ppbNumber, int16_t offset)
{
    uint32_t ppbAddress;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ppbAddress = base + (0x18U * (uint32_t)ppbNumber) + 0x94U;
    //
    // Write the offset amount.
    //
    EALLOW;
    ((struct ADCPPB1OFFCAL_BITS *)ppbAddress)->OFFCAL = offset;
    EDIS;
}

//*****************************************************************************
//
//! Sets the post processing block reference offset.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param offset is the 16-bit unsigned value subtracted from ADC the output.
//!
//! This function sets the PPB reference offset value. This can be used to
//! either calculate the feedback error or convert a unipolar signal to bipolar
//! by subtracting a reference value. The result will be stored in the
//! appropriate PPB result register which can be read using ADC_readPPBResult().
//!
//! Passing a zero in to the \e offset parameter will effectively disable the
//! calculation and will pass the ADC result to the PPB result register
//! unchanged.
//!
//! \note If in 12-bit mode, you may only pass a 12-bit value into the \e offset
//! parameter.
//!
//! \return None
//
//*****************************************************************************
static inline void ADC_setPPBReferenceOffset(uint32_t base, ADC_PPBNumber ppbNumber, uint16_t offset)
{
    uint32_t ppbAddress;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ppbAddress = base + (0x18U * (uint32_t)ppbNumber) + 0x88U;
    //
    // Write the offset amount.
    //
    ((struct ADCPPB1OFFREF_BITS *)ppbAddress)->OFFREF = offset;
}

//*****************************************************************************
//
//! Enables two's complement capability in the PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function enables two's complement in the post-processing block
//! specified by the \e ppbNumber parameter. When enabled, a two's complement
//! will be performed on the output of the offset subtraction before it is
//! stored in the appropriate PPB result register. In other words, the PPB
//! result will be the reference offset value minus the the ADC result value
//! (ADCPPBxRESULT = ADCSOCxOFFREF - ADCRESULTx).
//!
//! \return None
//
//*****************************************************************************
static inline void ADC_enablePPBTwosComplement(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint32_t ppbAddress;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ppbAddress = base + (0x18U * (uint32_t)ppbNumber) + 0x80U;

    //
    // Enable PPB two's complement.
    //
    EALLOW;
    ((struct ADCPPB1CONFIG_BITS *)ppbAddress)->TWOSCOMPEN = 1;
    EDIS;
}

//*****************************************************************************
//
//! Disables two's complement capability in the PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function disables two's complement in the post-processing block
//! specified by the \e ppbNumber parameter. When disabled, a two's complement
//! will \b NOT be performed on the output of the offset subtraction before it
//! is stored in the appropriate PPB result register. In other words, the PPB
//! result will be the ADC result value minus the reference offset value
//! (ADCPPBxRESULT = ADCRESULTx - ADCSOCxOFFREF).
//!
//! \return None
//
//*****************************************************************************
static inline void ADC_disablePPBTwosComplement(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint32_t ppbAddress;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ppbAddress = base + (0x18U * (uint32_t)ppbNumber) + 0x80U;

    //
    // Disable PPB two's complement.
    //
    EALLOW;
    ((struct ADCPPB1CONFIG_BITS *)ppbAddress)->TWOSCOMPEN = 0;
    EDIS;
}

//*****************************************************************************
//
//! Enables an ADC interrupt source.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function enables the indicated ADC interrupt source.  Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.
//!
//! \e adcIntNum can take the value \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to express
//! which of the four interrupts of the ADC module should be enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_enableInterrupt(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t shiftVal;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    shiftVal = ((uint16_t)adcIntNum) * 8U + 5U;

    //
    // Enable the specified ADC interrupt.
    //
    EALLOW;

    ((struct ADC_REGS *)base)->ADCINTSEL.all |= (1 << shiftVal);

    EDIS;
}

//*****************************************************************************
//
//! Disables an ADC interrupt source.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function disables the indicated ADC interrupt source.
//! Only the sources that are enabled can be reflected to the processor
//! interrupt. Disabled sources have no effect on the processor.
//!
//! \e adcIntNum can take the value \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to express
//! which of the four interrupts of the ADC module should be disabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_disableInterrupt(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    shiftVal = ((uint16_t)adcIntNum) * 8U + 5U;

    //
    // Disable the specified ADC interrupt.
    //
    EALLOW;

    ((struct ADC_REGS *)base)->ADCINTSEL.all &= ~(1 << shiftVal);

    EDIS;
}

//*****************************************************************************
//
//! Sets the source EOC for an analog-to-digital converter interrupt.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//! \param socNumber is the number of the start-of-conversion.
//!
//! This function sets which conversion is the source of an ADC interrupt.
//!
//! The \e intTrigger number is a value \b ADC_SOC_NUMBERX where X is a number
//! from 0 to 15 specifying which EOC is to be configured on the ADC module
//! specified by \e base. Refer \b ADC_SOCNumber enum for valid values for
//! this input.
//!
//! \e adcIntNum can take the value \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to express
//! which of the four interrupts of the ADC module is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_setInterruptSource(uint32_t base, ADC_IntNumber adcIntNum, uint16_t intTrigger)
{
    uint16_t shiftVal;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(intTrigger < 20U);

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    shiftVal = (uint16_t)adcIntNum * 8U;
    //
    // Set the specified ADC interrupt source.
    //
    EALLOW;

    ((struct ADC_REGS *)base)->ADCINTSEL.all
        = ((((struct ADC_REGS *)base)->ADCINTSEL.all) & ~(0x1f << shiftVal)) | (intTrigger << shiftVal);

    EDIS;
}

//*****************************************************************************
//
//! Enables continuous mode for an ADC interrupt.
//!
//! \param base is the base address of the ADC.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function enables continuous mode for the ADC interrupt passed into
//! \e adcIntNum. This means that pulses will be generated for the specified
//! ADC interrupt whenever an EOC pulse is generated irrespective of whether or
//! not the flag bit is set.
//!
//! \e adcIntNum can take the value \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to express
//! which of the four interrupts of the ADC module is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_enableContinuousMode(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    shiftVal = ((uint16_t)adcIntNum) * 8U + 6U;

    //
    // Enable continuous mode for the specified ADC interrupt.
    //
    EALLOW;

    ((struct ADC_REGS *)base)->ADCINTSEL.all |= (1 << shiftVal);

    EDIS;
}

//*****************************************************************************
//
//! Disables continuous mode for an ADC interrupt.
//!
//! \param base is the base address of the ADC.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function disables continuous mode for the ADC interrupt passed into
//! \e adcIntNum. This means that pulses will not be generated for the
//! specified ADC interrupt until the corresponding interrupt flag for the
//! previous interrupt occurrence has been cleared using
//! ADC_clearInterruptStatus().
//!
//! \e adcIntNum can take the value \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to express
//! which of the four interrupts of the ADC module is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void ADC_disableContinuousMode(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    shiftVal = ((uint16_t)adcIntNum) * 8U + 6U;

    //
    // Disable continuous mode for the specified ADC interrupt.
    //
    EALLOW;

    ((struct ADC_REGS *)base)->ADCINTSEL.all &= ~(1 << shiftVal);

    EDIS;
}
//*****************************************************************************
//
//! Configures the ADC module's reference mode and offset trim
//!
//! \param base is the base address of the ADC module.
//! \param refMode is the reference mode being used (\b ADC_REFERENCE_INTERNAL
//!        or \b ADC_REFERENCE_EXTERNAL).
//! \param refVoltage is the reference voltage being used
//!        (\b ADC_REFERENCE_2_5V or \b ADC_REFERENCE_3_3V). This is ignored
//!        when the reference mode is external.
//!
//! This function configures the ADC module's reference mode and loads the
//! corresponding offset trims.
//!
//! \note When the \e refMode parameter is \b ADC_REFERENCE_EXTERNAL, the value
//! of the \e refVoltage parameter has no effect on the operation of the ADC.
//!
//! \return None.
//
//*****************************************************************************
extern void ADC_setVREF(uint32_t base, ADC_ReferenceMode refMode, ADC_ReferenceVoltage refVoltage);

//*****************************************************************************
//
//! Sets the windowed trip limits for a PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param tripHiLimit is the value is the digital comparator trip high limit.
//! \param tripLoLimit is the value is the digital comparator trip low limit.
//!
//! This function sets the windowed trip limits for a PPB. These values set
//! the digital comparator so that when one of the values is exceeded, either a
//! high or low trip event will occur.
//!
//! The \e ppbNumber is a value \b ADC_PPB_NUMBERX where X is a value from 1 to
//! 4 inclusive that identifies a PPB to be configured.
//!
//! If using 16-bit mode, you may pass a 17-bit number into the \e tripHiLimit
//! and \e tripLoLimit parameters where the 17th bit is the sign bit (that is
//! a value from -65536 and 65535). In 12-bit mode, only bits 12:0 will be
//! compared against bits 12:0 of the PPB result.
//!
//!
//! \return None.
//
//*****************************************************************************
extern void ADC_setPPBTripLimits(uint32_t base, ADC_PPBNumber ppbNumber, int32_t tripHiLimit, int32_t tripLoLimit);

#ifdef __cplusplus
}
#endif

#endif
