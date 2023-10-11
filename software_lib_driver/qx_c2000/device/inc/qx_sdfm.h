/**
 **************************************************************************
 * @file     qx_sdfm.h
 * @version  v1.0.0
 * @date     2023-12-30
 **************************************************************************
 */

#ifndef QX_SDFM_H
#define QX_SDFM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"
#include "hw_sdfm.h"

//---------------------------------------------------------------------------
// SDFM Individual Register Bit Definitions:

struct SDIFLG_BITS
{                      // bits description
    vu32 IFH1     : 1; // 0 High-level Interrupt flag for Ch1
    vu32 IFL1     : 1; // 1 Low-level Interrupt flag for Ch1
    vu32 IFH2     : 1; // 2 High-level Interrupt flag for Ch2
    vu32 IFL2     : 1; // 3 Low-level Interrupt flag for Ch2
    vu32 IFH3     : 1; // 4 High-level Interrupt flag for Ch3
    vu32 IFL3     : 1; // 5 Low-level Interrupt flag for Ch3
    vu32 IFH4     : 1; // 6 High-level Interrupt flag for Ch4
    vu32 IFL4     : 1; // 7 Low-level Interrupt flag for Ch4
    vu32 MF1      : 1; // 8 Modulator Failure for Filter 1
    vu32 MF2      : 1; // 9 Modulator Failure for Filter 2
    vu32 MF3      : 1; // 10 Modulator Failure for Filter 3
    vu32 MF4      : 1; // 11 Modulator Failure for Filter 4
    vu32 AF1      : 1; // 12 Acknowledge flag for Filter 1
    vu32 AF2      : 1; // 13 Acknowledge flag for Filter 2
    vu32 AF3      : 1; // 14 Acknowledge flag for Filter 3
    vu32 AF4      : 1; // 15 Acknowledge flag for Filter 4
    vu32 SDFFOVF1 : 1; // 16 FIFO Overflow Flag for Ch1.
    vu32 SDFFOVF2 : 1; // 17 FIFO Overflow Flag for Ch2
    vu32 SDFFOVF3 : 1; // 18 FIFO Overflow Flag for Ch3
    vu32 SDFFOVF4 : 1; // 19 FIFO Overflow Flag for Ch4
    vu32 SDFFINT1 : 1; // 20 SDFIFO interrupt for Ch1
    vu32 SDFFINT2 : 1; // 21 SDFIFO interrupt for Ch2
    vu32 SDFFINT3 : 1; // 22 SDFIFO interrupt for Ch3
    vu32 SDFFINT4 : 1; // 23 SDFIFO interrupt for Ch4
    vu32 rsvd1    : 7; // 30:24 Reserved
    vu32 MIF      : 1; // 31 Master Interrupt Flag
};

union SDIFLG_REG
{
    vu32 all;
    struct SDIFLG_BITS bit;
};

struct SDIFLGCLR_BITS
{                      // bits description
    vu32 IFH1     : 1; // 0 High-level Interrupt flag for Ch1
    vu32 IFL1     : 1; // 1 Low-level Interrupt flag for Ch1
    vu32 IFH2     : 1; // 2 High-level Interrupt flag for Ch2
    vu32 IFL2     : 1; // 3 Low-level Interrupt flag for Ch2
    vu32 IFH3     : 1; // 4 High-level Interrupt flag for Ch3
    vu32 IFL3     : 1; // 5 Low-level Interrupt flag for Ch3
    vu32 IFH4     : 1; // 6 High-level Interrupt flag for Ch4
    vu32 IFL4     : 1; // 7 Low-level Interrupt flag for Ch4
    vu32 MF1      : 1; // 8 Modulator Failure for Filter 1
    vu32 MF2      : 1; // 9 Modulator Failure for Filter 2
    vu32 MF3      : 1; // 10 Modulator Failure for Filter 3
    vu32 MF4      : 1; // 11 Modulator Failure for Filter 4
    vu32 AF1      : 1; // 12 Acknowledge flag for Filter 1
    vu32 AF2      : 1; // 13 Acknowledge flag for Filter 2
    vu32 AF3      : 1; // 14 Acknowledge flag for Filter 3
    vu32 AF4      : 1; // 15 Acknowledge flag for Filter 4
    vu32 SDFFOVF1 : 1; // 16 SDFIFO overflow clear Ch1
    vu32 SDFFOVF2 : 1; // 17 SDFIFO overflow clear Ch2
    vu32 SDFFOVF3 : 1; // 18 SDFIFO overflow clear Ch3
    vu32 SDFFOVF4 : 1; // 19 SDFIFO overflow clear Ch4
    vu32 SDFFINT1 : 1; // 20 SDFIFO Interrupt flag-clear bit for Ch1
    vu32 SDFFINT2 : 1; // 21 SDFIFO Interrupt flag-clear bit for Ch2
    vu32 SDFFINT3 : 1; // 22 SDFIFO Interrupt flag-clear bit for Ch3
    vu32 SDFFINT4 : 1; // 23 SDFIFO Interrupt flag-clear bit for Ch4
    vu32 rsvd1    : 7; // 30:24 Reserved
    vu32 MIF      : 1; // 31 Master Interrupt Flag
};

union SDIFLGCLR_REG
{
    vu32 all;
    struct SDIFLGCLR_BITS bit;
};

struct SDCTL_BITS
{                   // bits description
    vu16 HZ1   : 1; // 0 High-level Threshold crossing (Z) flag Ch1
    vu16 HZ2   : 1; // 1 High-level Threshold crossing (Z) flag Ch2
    vu16 HZ3   : 1; // 2 High-level Threshold crossing (Z) flag Ch3
    vu16 HZ4   : 1; // 3 High-level Threshold crossing (Z) flag Ch4
    vu16 rsvd1 : 9; // 12:4 Reserved
    vu16 MIE   : 1; // 13 Master SDy_ERR Interrupt enable
    vu16 rsvd2 : 1; // 14 Reserved
    vu16 rsvd3 : 1; // 15 Reserved
};

union SDCTL_REG
{
    vu16 all;
    struct SDCTL_BITS bit;
};

struct SDMFILEN_BITS
{                   // bits description
    vu16 rsvd1 : 4; // 3:0 Reserved
    vu16 rsvd2 : 3; // 6:4 Reserved
    vu16 rsvd3 : 2; // 8:7 Reserved
    vu16 rsvd4 : 1; // 9 Reserved
    vu16 rsvd5 : 1; // 10 Reserved
    vu16 MFE   : 1; // 11 Master Filter Enable.
    vu16 rsvd6 : 1; // 12 Reserved
    vu16 rsvd7 : 3; // 15:13 Reserved
};

union SDMFILEN_REG
{
    vu16 all;
    struct SDMFILEN_BITS bit;
};

struct SDSTATUS_BITS
{                   // bits description
    vu16 HZ1   : 1; // 0 High-level Threshold crossing (Z) flag Ch1
    vu16 HZ2   : 1; // 1 High-level Threshold crossing (Z) flag Ch2
    vu16 HZ3   : 1; // 2 High-level Threshold crossing (Z) flag Ch3
    vu16 HZ4   : 1; // 3 High-level Threshold crossing (Z) flag Ch4
    vu16 rsvd1 : 4; // 7:4 Reserved
    vu16 rsvd2 : 1; // 8 Reserved
    vu16 rsvd3 : 1; // 9 Reserved
    vu16 rsvd4 : 1; // 10 Reserved
    vu16 rsvd5 : 1; // 11 Reserved
    vu16 rsvd6 : 1; // 12 Reserved
    vu16 rsvd7 : 1; // 13 Reserved
    vu16 rsvd8 : 1; // 14 Reserved
    vu16 rsvd9 : 1; // 15 Reserved
};

union SDSTATUS_REG
{
    vu16 all;
    struct SDSTATUS_BITS bit;
};

struct SDCTLPARM1_BITS
{                    // bits description
    vu16 MOD   : 2;  // 1:0 Modulator clocking modes
    vu16 rsvd1 : 1;  // 2 Reserved
    vu16 rsvd2 : 1;  // 3 Reserved
    vu16 rsvd3 : 1;  // 4 Reserved
    vu16 rsvd4 : 11; // 15:5 Reserved
};

union SDCTLPARM1_REG
{
    vu16 all;
    struct SDCTLPARM1_BITS bit;
};

struct SDDFPARM1_BITS
{                      // bits description
    vu16 DOSR     : 8; // 7:0 Data Filter Oversample Ratio= DOSR+1
    vu16 FEN      : 1; // 8 Filter Enable
    vu16 AE       : 1; // 9 Ack Enable
    vu16 SST      : 2; // 11:10 Data filter Structure (SincFast/1/2/3)
    vu16 SDSYNCEN : 1; // 12 Data Filter Reset Enable
    vu16 rsvd1    : 3; // 15:13 Reserved
};

union SDDFPARM1_REG
{
    vu16 all;
    struct SDDFPARM1_BITS bit;
};

struct SDDPARM1_BITS
{                    // bits description
    vu16 rsvd1 : 10; // 9:0 Reserved
    vu16 DR    : 1;  // 10 Data Representation (0/1 = 16/32b 2's complement)
    vu16 SH    : 5;  // 15:11 Shift Control (# bits to shift in 16b mode)
};

union SDDPARM1_REG
{
    vu16 all;
    struct SDDPARM1_BITS bit;
};

struct SDCMPH1_BITS
{                    // bits description
    vu16 HLT   : 15; // 14:0 High-level threshold for the comparator filter output
    vu16 rsvd1 : 1;  // 15 Reserved
};

union SDCMPH1_REG
{
    vu16 all;
    struct SDCMPH1_BITS bit;
};

struct SDCMPL1_BITS
{                    // bits description
    vu16 LLT   : 15; // 14:0 Low-level threshold for the comparator filter output
    vu16 rsvd1 : 1;  // 15 Reserved
};

union SDCMPL1_REG
{
    vu16 all;
    struct SDCMPL1_BITS bit;
};

struct SDCPARM1_BITS
{                     // bits description
    vu16 COSR    : 5; // 4:0 Comparator Oversample Ratio. Actual rate COSR+1
    vu16 IEH     : 1; // 5 High-level Interrupt enable.
    vu16 IEL     : 1; // 6 Low-level interrupt enable
    vu16 CS1_CS0 : 2; // 8:7 Comparator Filter Structure (SincFast/1/2/3)
    vu16 MFIE    : 1; // 9 Modulator Failure Interrupt enable
    vu16 HZEN    : 1; // 10 High level (Z) Threshold crossing output enable
    vu16 rsvd1   : 2; // 12:11 Reserved
    vu16 CEN     : 1; // 13 Comparator Enable
    vu16 rsvd2   : 2; // 15:14 Reserved
};

union SDCPARM1_REG
{
    vu16 all;
    struct SDCPARM1_BITS bit;
};

struct SDDATA1_BITS
{                       // bits description
    vu32 DATA16   : 16; // 15:0 Lo-order 16b in 32b mode
    vu32 DATA32HI : 16; // 31:16 Hi-order 16b in 32b mode, 16-bit Data in 16b mode
};

union SDDATA1_REG
{
    vu32 all;
    struct SDDATA1_BITS bit;
};

struct SDDATFIFO1_BITS
{                       // bits description
    vu32 DATA16   : 16; // 15:0 Lo-order 16b in 32b mode
    vu32 DATA32HI : 16; // 31:16 Hi-order 16b in 32b mode, 16-bit Data in 16b mode
};

union SDDATFIFO1_REG
{
    vu32 all;
    struct SDDATFIFO1_BITS bit;
};

struct SDCMPHZ1_BITS
{                    // bits description
    vu16 HLTZ  : 15; // 14:0 High-level threshold (Z) for the comparator filter output
    vu16 rsvd1 : 1;  // 15 Reserved
};

union SDCMPHZ1_REG
{
    vu16 all;
    struct SDCMPHZ1_BITS bit;
};

struct SDFIFOCTL1_BITS
{                      // bits description
    vu16 SDFFIL   : 5; // 4:0 SDFIFO Interrupt Level
    vu16 rsvd1    : 1; // 5 Reserved
    vu16 SDFFST   : 5; // 10:6 SDFIFO Status
    vu16 rsvd2    : 1; // 11 Reserved
    vu16 FFIEN    : 1; // 12 SDFIFO data ready Interrupt Enable
    vu16 FFEN     : 1; // 13 SDFIFO Enable
    vu16 DRINTSEL : 1; // 14 Data-Ready Interrupt Source Select
    vu16 OVFIEN   : 1; // 15 SDFIFO Overflow interrupt enable
};

union SDFIFOCTL1_REG
{
    vu16 all;
    struct SDFIFOCTL1_BITS bit;
};

struct SDSYNC1_BITS
{                         // bits description
    vu16 SYNCSEL     : 6; // 5:0 SDSYNC Source Select
    vu16 WTSYNCEN    : 1; // 6 Wait-for-Sync Enable
    vu16 WTSYNFLG    : 1; // 7 Wait-for-Sync Flag
    vu16 WTSYNCLR    : 1; // 8 Wait-for-Sync Flag Clear
    vu16 FFSYNCCLREN : 1; // 9 FIFO Clear-on-SDSYNC Enable
    vu16 WTSCLREN    : 1; // 10 WTSYNFLG Clear-on-FIFOINT Enable
    vu16 rsvd1       : 5; // 15:11 Reserved
};

union SDSYNC1_REG
{
    vu16 all;
    struct SDSYNC1_BITS bit;
};

struct SDCTLPARM2_BITS
{                    // bits description
    vu16 MOD   : 2;  // 1:0 Modulator clocking modes
    vu16 rsvd1 : 1;  // 2 Reserved
    vu16 rsvd2 : 1;  // 3 Reserved
    vu16 rsvd3 : 1;  // 4 Reserved
    vu16 rsvd4 : 11; // 15:5 Reserved
};

union SDCTLPARM2_REG
{
    vu16 all;
    struct SDCTLPARM2_BITS bit;
};

struct SDDFPARM2_BITS
{                      // bits description
    vu16 DOSR     : 8; // 7:0 Data Filter Oversample Ratio= DOSR+1
    vu16 FEN      : 1; // 8 Filter Enable
    vu16 AE       : 1; // 9 Ack Enable
    vu16 SST      : 2; // 11:10 Data filter Structure (SincFast/1/2/3)
    vu16 SDSYNCEN : 1; // 12 Data Filter Reset Enable
    vu16 rsvd1    : 3; // 15:13 Reserved
};

union SDDFPARM2_REG
{
    vu16 all;
    struct SDDFPARM2_BITS bit;
};

struct SDDPARM2_BITS
{                    // bits description
    vu16 rsvd1 : 10; // 9:0 Reserved
    vu16 DR    : 1;  // 10 Data Representation (0/1 = 16/32b 2's complement)
    vu16 SH    : 5;  // 15:11 Shift Control (# bits to shift in 16b mode)
};

union SDDPARM2_REG
{
    vu16 all;
    struct SDDPARM2_BITS bit;
};

struct SDCMPH2_BITS
{                    // bits description
    vu16 HLT   : 15; // 14:0 High-level threshold for the comparator filter output
    vu16 rsvd1 : 1;  // 15 Reserved
};

union SDCMPH2_REG
{
    vu16 all;
    struct SDCMPH2_BITS bit;
};

struct SDCMPL2_BITS
{                    // bits description
    vu16 LLT   : 15; // 14:0 Low-level threshold for the comparator filter output
    vu16 rsvd1 : 1;  // 15 Reserved
};

union SDCMPL2_REG
{
    vu16 all;
    struct SDCMPL2_BITS bit;
};

struct SDCPARM2_BITS
{                     // bits description
    vu16 COSR    : 5; // 4:0 Comparator Oversample Ratio. Actual rate COSR+1
    vu16 IEH     : 1; // 5 High-level Interrupt enable.
    vu16 IEL     : 1; // 6 Low-level interrupt enable
    vu16 CS1_CS0 : 2; // 8:7 Comparator Filter Structure (SincFast/1/2/3)
    vu16 MFIE    : 1; // 9 Modulator Failure Interrupt enable
    vu16 HZEN    : 1; // 10 High level (Z) Threshold crossing output enable
    vu16 rsvd1   : 2; // 12:11 Reserved
    vu16 CEN     : 1; // 13 Comparator Enable
    vu16 rsvd2   : 2; // 15:14 Reserved
};

union SDCPARM2_REG
{
    vu16 all;
    struct SDCPARM2_BITS bit;
};

struct SDDATA2_BITS
{                       // bits description
    vu32 DATA16   : 16; // 15:0 Lo-order 16b in 32b mode
    vu32 DATA32HI : 16; // 31:16 Hi-order 16b in 32b mode, 16-bit Data in 16b mode
};

union SDDATA2_REG
{
    vu32 all;
    struct SDDATA2_BITS bit;
};

struct SDDATFIFO2_BITS
{                       // bits description
    vu32 DATA16   : 16; // 15:0 Lo-order 16b in 32b mode
    vu32 DATA32HI : 16; // 31:16 Hi-order 16b in 32b mode, 16-bit Data in 16b mode
};

union SDDATFIFO2_REG
{
    vu32 all;
    struct SDDATFIFO2_BITS bit;
};

struct SDCMPHZ2_BITS
{                    // bits description
    vu16 HLTZ  : 15; // 14:0 High-level threshold (Z) for the comparator filter output
    vu16 rsvd1 : 1;  // 15 Reserved
};

union SDCMPHZ2_REG
{
    vu16 all;
    struct SDCMPHZ2_BITS bit;
};

struct SDFIFOCTL2_BITS
{                      // bits description
    vu16 SDFFIL   : 5; // 4:0 SDFIFO Interrupt Level
    vu16 rsvd1    : 1; // 5 Reserved
    vu16 SDFFST   : 5; // 10:6 SDFIFO Status
    vu16 rsvd2    : 1; // 11 Reserved
    vu16 FFIEN    : 1; // 12 SDFIFO data ready Interrupt Enable
    vu16 FFEN     : 1; // 13 SDFIFO Enable
    vu16 DRINTSEL : 1; // 14 Data-Ready Interrupt Source Select
    vu16 OVFIEN   : 1; // 15 SDFIFO Overflow interrupt enable
};

union SDFIFOCTL2_REG
{
    vu16 all;
    struct SDFIFOCTL2_BITS bit;
};

struct SDSYNC2_BITS
{                         // bits description
    vu16 SYNCSEL     : 6; // 5:0 SDSYNC Source Select
    vu16 WTSYNCEN    : 1; // 6 Wait-for-Sync Enable
    vu16 WTSYNFLG    : 1; // 7 Wait-for-Sync Flag
    vu16 WTSYNCLR    : 1; // 8 Wait-for-Sync Flag Clear
    vu16 FFSYNCCLREN : 1; // 9 FIFO Clear-on-SDSYNC Enable
    vu16 WTSCLREN    : 1; // 10 WTSYNFLG Clear-on-FIFOINT Enable
    vu16 rsvd1       : 5; // 15:11 Reserved
};

union SDSYNC2_REG
{
    vu16 all;
    struct SDSYNC2_BITS bit;
};

struct SDCTLPARM3_BITS
{                    // bits description
    vu16 MOD   : 2;  // 1:0 Modulator clocking modes
    vu16 rsvd1 : 1;  // 2 Reserved
    vu16 rsvd2 : 1;  // 3 Reserved
    vu16 rsvd3 : 1;  // 4 Reserved
    vu16 rsvd4 : 11; // 15:5 Reserved
};

union SDCTLPARM3_REG
{
    vu16 all;
    struct SDCTLPARM3_BITS bit;
};

struct SDDFPARM3_BITS
{                      // bits description
    vu16 DOSR     : 8; // 7:0 Data Filter Oversample Ratio= DOSR+1
    vu16 FEN      : 1; // 8 Filter Enable
    vu16 AE       : 1; // 9 Ack Enable
    vu16 SST      : 2; // 11:10 Data filter Structure (SincFast/1/2/3)
    vu16 SDSYNCEN : 1; // 12 Data Filter Reset Enable
    vu16 rsvd1    : 3; // 15:13 Reserved
};

union SDDFPARM3_REG
{
    vu16 all;
    struct SDDFPARM3_BITS bit;
};

struct SDDPARM3_BITS
{                    // bits description
    vu16 rsvd1 : 10; // 9:0 Reserved
    vu16 DR    : 1;  // 10 Data Representation (0/1 = 16/32b 2's complement)
    vu16 SH    : 5;  // 15:11 Shift Control (# bits to shift in 16b mode)
};

union SDDPARM3_REG
{
    vu16 all;
    struct SDDPARM3_BITS bit;
};

struct SDCMPH3_BITS
{                    // bits description
    vu16 HLT   : 15; // 14:0 High-level threshold for the comparator filter output
    vu16 rsvd1 : 1;  // 15 Reserved
};

union SDCMPH3_REG
{
    vu16 all;
    struct SDCMPH3_BITS bit;
};

struct SDCMPL3_BITS
{                    // bits description
    vu16 LLT   : 15; // 14:0 Low-level threshold for the comparator filter output
    vu16 rsvd1 : 1;  // 15 Reserved
};

union SDCMPL3_REG
{
    vu16 all;
    struct SDCMPL3_BITS bit;
};

struct SDCPARM3_BITS
{                     // bits description
    vu16 COSR    : 5; // 4:0 Comparator Oversample Ratio. Actual rate COSR+1
    vu16 IEH     : 1; // 5 High-level Interrupt enable.
    vu16 IEL     : 1; // 6 Low-level interrupt enable
    vu16 CS1_CS0 : 2; // 8:7 Comparator Filter Structure (SincFast/1/2/3)
    vu16 MFIE    : 1; // 9 Modulator Failure Interrupt enable
    vu16 HZEN    : 1; // 10 High level (Z) Threshold crossing output enable
    vu16 rsvd1   : 2; // 12:11 Reserved
    vu16 CEN     : 1; // 13 Comparator Enable
    vu16 rsvd2   : 2; // 15:14 Reserved
};

union SDCPARM3_REG
{
    vu16 all;
    struct SDCPARM3_BITS bit;
};

struct SDDATA3_BITS
{                       // bits description
    vu32 DATA16   : 16; // 15:0 Lo-order 16b in 32b mode
    vu32 DATA32HI : 16; // 31:16 Hi-order 16b in 32b mode, 16-bit Data in 16b mode
};

union SDDATA3_REG
{
    vu32 all;
    struct SDDATA3_BITS bit;
};

struct SDDATFIFO3_BITS
{                       // bits description
    vu32 DATA16   : 16; // 15:0 Lo-order 16b in 32b mode
    vu32 DATA32HI : 16; // 31:16 Hi-order 16b in 32b mode, 16-bit Data in 16b mode
};

union SDDATFIFO3_REG
{
    vu32 all;
    struct SDDATFIFO3_BITS bit;
};

struct SDCMPHZ3_BITS
{                    // bits description
    vu16 HLTZ  : 15; // 14:0 High-level threshold (Z) for the comparator filter output
    vu16 rsvd1 : 1;  // 15 Reserved
};

union SDCMPHZ3_REG
{
    vu16 all;
    struct SDCMPHZ3_BITS bit;
};

struct SDFIFOCTL3_BITS
{                      // bits description
    vu16 SDFFIL   : 5; // 4:0 SDFIFO Interrupt Level
    vu16 rsvd1    : 1; // 5 Reserved
    vu16 SDFFST   : 5; // 10:6 SDFIFO Status
    vu16 rsvd2    : 1; // 11 Reserved
    vu16 FFIEN    : 1; // 12 SDFIFO data ready Interrupt Enable
    vu16 FFEN     : 1; // 13 SDFIFO Enable
    vu16 DRINTSEL : 1; // 14 Data-Ready Interrupt Source Select
    vu16 OVFIEN   : 1; // 15 SDFIFO Overflow interrupt enable
};

union SDFIFOCTL3_REG
{
    vu16 all;
    struct SDFIFOCTL3_BITS bit;
};

struct SDSYNC3_BITS
{                         // bits description
    vu16 SYNCSEL     : 6; // 5:0 SDSYNC Source Select
    vu16 WTSYNCEN    : 1; // 6 Wait-for-Sync Enable
    vu16 WTSYNFLG    : 1; // 7 Wait-for-Sync Flag
    vu16 WTSYNCLR    : 1; // 8 Wait-for-Sync Flag Clear
    vu16 FFSYNCCLREN : 1; // 9 FIFO Clear-on-SDSYNC Enable
    vu16 WTSCLREN    : 1; // 10 WTSYNFLG Clear-on-FIFOINT Enable
    vu16 rsvd1       : 5; // 15:11 Reserved
};

union SDSYNC3_REG
{
    vu16 all;
    struct SDSYNC3_BITS bit;
};

struct SDCTLPARM4_BITS
{                    // bits description
    vu16 MOD   : 2;  // 1:0 Modulator clocking modes
    vu16 rsvd1 : 1;  // 2 Reserved
    vu16 rsvd2 : 1;  // 3 Reserved
    vu16 rsvd3 : 1;  // 4 Reserved
    vu16 rsvd4 : 11; // 15:5 Reserved
};

union SDCTLPARM4_REG
{
    vu16 all;
    struct SDCTLPARM4_BITS bit;
};

struct SDDFPARM4_BITS
{                      // bits description
    vu16 DOSR     : 8; // 7:0 Data Filter Oversample Ratio= DOSR+1
    vu16 FEN      : 1; // 8 Filter Enable
    vu16 AE       : 1; // 9 Ack Enable
    vu16 SST      : 2; // 11:10 Data filter Structure (SincFast/1/2/3)
    vu16 SDSYNCEN : 1; // 12 Data Filter Reset Enable
    vu16 rsvd1    : 3; // 15:13 Reserved
};

union SDDFPARM4_REG
{
    vu16 all;
    struct SDDFPARM4_BITS bit;
};

struct SDDPARM4_BITS
{                    // bits description
    vu16 rsvd1 : 10; // 9:0 Reserved
    vu16 DR    : 1;  // 10 Data Representation (0/1 = 16/32b 2's complement)
    vu16 SH    : 5;  // 15:11 Shift Control (# bits to shift in 16b mode)
};

union SDDPARM4_REG
{
    vu16 all;
    struct SDDPARM4_BITS bit;
};

struct SDCMPH4_BITS
{                    // bits description
    vu16 HLT   : 15; // 14:0 High-level threshold for the comparator filter output
    vu16 rsvd1 : 1;  // 15 Reserved
};

union SDCMPH4_REG
{
    vu16 all;
    struct SDCMPH4_BITS bit;
};

struct SDCMPL4_BITS
{                    // bits description
    vu16 LLT   : 15; // 14:0 Low-level threshold for the comparator filter output
    vu16 rsvd1 : 1;  // 15 Reserved
};

union SDCMPL4_REG
{
    vu16 all;
    struct SDCMPL4_BITS bit;
};

struct SDCPARM4_BITS
{                     // bits description
    vu16 COSR    : 5; // 4:0 Comparator Oversample Ratio. Actual rate COSR+1
    vu16 IEH     : 1; // 5 High-level Interrupt enable.
    vu16 IEL     : 1; // 6 Low-level interrupt enable
    vu16 CS1_CS0 : 2; // 8:7 Comparator Filter Structure (SincFast/1/2/3)
    vu16 MFIE    : 1; // 9 Modulator Failure Interrupt enable
    vu16 HZEN    : 1; // 10 High level (Z) Threshold crossing output enable
    vu16 rsvd1   : 2; // 12:11 Reserved
    vu16 CEN     : 1; // 13 Comparator Enable
    vu16 rsvd2   : 2; // 15:14 Reserved
};

union SDCPARM4_REG
{
    vu16 all;
    struct SDCPARM4_BITS bit;
};

struct SDDATA4_BITS
{                       // bits description
    vu32 DATA16   : 16; // 15:0 Lo-order 16b in 32b mode
    vu32 DATA32HI : 16; // 31:16 Hi-order 16b in 32b mode, 16-bit Data in 16b mode
};

union SDDATA4_REG
{
    vu32 all;
    struct SDDATA4_BITS bit;
};

struct SDDATFIFO4_BITS
{                       // bits description
    vu32 DATA16   : 16; // 15:0 Lo-order 16b in 32b mode
    vu32 DATA32HI : 16; // 31:16 Hi-order 16b in 32b mode, 16-bit Data in 16b mode
};

union SDDATFIFO4_REG
{
    vu32 all;
    struct SDDATFIFO4_BITS bit;
};

struct SDCMPHZ4_BITS
{                    // bits description
    vu16 HLTZ  : 15; // 14:0 High-level threshold (Z) for the comparator filter output
    vu16 rsvd1 : 1;  // 15 Reserved
};

union SDCMPHZ4_REG
{
    vu16 all;
    struct SDCMPHZ4_BITS bit;
};

struct SDFIFOCTL4_BITS
{                      // bits description
    vu16 SDFFIL   : 5; // 4:0 SDFIFO Interrupt Level
    vu16 rsvd1    : 1; // 5 Reserved
    vu16 SDFFST   : 5; // 10:6 SDFIFO Status
    vu16 rsvd2    : 1; // 11 Reserved
    vu16 FFIEN    : 1; // 12 SDFIFO data ready Interrupt Enable
    vu16 FFEN     : 1; // 13 SDFIFO Enable
    vu16 DRINTSEL : 1; // 14 Data-Ready Interrupt Source Select
    vu16 OVFIEN   : 1; // 15 SDFIFO Overflow interrupt enable
};

union SDFIFOCTL4_REG
{
    vu16 all;
    struct SDFIFOCTL4_BITS bit;
};

struct SDSYNC4_BITS
{                         // bits description
    vu16 SYNCSEL     : 6; // 5:0 SDSYNC Source Select
    vu16 WTSYNCEN    : 1; // 6 Wait-for-Sync Enable
    vu16 WTSYNFLG    : 1; // 7 Wait-for-Sync Flag
    vu16 WTSYNCLR    : 1; // 8 Wait-for-Sync Flag Clear
    vu16 FFSYNCCLREN : 1; // 9 FIFO Clear-on-SDSYNC Enable
    vu16 WTSCLREN    : 1; // 10 WTSYNFLG Clear-on-FIFOINT Enable
    vu16 rsvd1       : 5; // 15:11 Reserved
};

union SDSYNC4_REG
{
    vu16 all;
    struct SDSYNC4_BITS bit;
};

struct SDFM_REGS
{
    union SDIFLG_REG SDIFLG;         // SD Interrupt Flag Register
    union SDIFLGCLR_REG SDIFLGCLR;   // SD Interrupt Flag Clear Register
    union SDCTL_REG SDCTL;           // SD Control Register
    vu16 rsvd1;                      // Reserved
    union SDMFILEN_REG SDMFILEN;     // SD Master Filter Enable
    union SDSTATUS_REG SDSTATUS;     // SD Status Register
    vu16 rsvd2[8];                   // Reserved
    union SDCTLPARM1_REG SDCTLPARM1; // Control Parameter Register for Ch1
    union SDDFPARM1_REG SDDFPARM1;   // Data Filter Parameter Register for Ch1
    union SDDPARM1_REG SDDPARM1;     // Data Parameter Register for Ch1
    union SDCMPH1_REG SDCMPH1;       // High-level Threshold Register for Ch1
    union SDCMPL1_REG SDCMPL1;       // Low-level Threshold Register for Ch1
    union SDCPARM1_REG SDCPARM1;     // Comparator Filter Parameter Register for Ch1
    union SDDATA1_REG SDDATA1;       // Data Filter Data Register (16 or 32bit) for Ch1
    union SDDATFIFO1_REG SDDATFIFO1; // Filter Data FIFO Output(32b) for Ch1
    vu16 SDCDATA1;                   // Comparator Filter Data Register (16b) for Ch1
    vu16 rsvd3;                      // Reserved
    union SDCMPHZ1_REG SDCMPHZ1;     // High-level (Z) Threshold Register for Ch1
    union SDFIFOCTL1_REG SDFIFOCTL1; // FIFO Control Register for Ch1
    union SDSYNC1_REG SDSYNC1;       // SD Filter Sync control for Ch1
    vu16 rsvd4;                      // Reserved
    union SDCTLPARM2_REG SDCTLPARM2; // Control Parameter Register for Ch2
    union SDDFPARM2_REG SDDFPARM2;   // Data Filter Parameter Register for Ch2
    union SDDPARM2_REG SDDPARM2;     // Data Parameter Register for Ch2
    union SDCMPH2_REG SDCMPH2;       // High-level Threshold Register for Ch2
    union SDCMPL2_REG SDCMPL2;       // Low-level Threshold Register for Ch2
    union SDCPARM2_REG SDCPARM2;     // Comparator Filter Parameter Register for Ch2
    union SDDATA2_REG SDDATA2;       // Data Filter Data Register (16 or 32bit) for Ch2
    union SDDATFIFO2_REG SDDATFIFO2; // Filter Data FIFO Output(32b) for Ch2
    vu16 SDCDATA2;                   // Comparator Filter Data Register (16b) for Ch2
    vu16 rsvd5;                      // Reserved
    union SDCMPHZ2_REG SDCMPHZ2;     // High-level (Z) Threshold Register for Ch2
    union SDFIFOCTL2_REG SDFIFOCTL2; // FIFO Control Register for Ch2
    union SDSYNC2_REG SDSYNC2;       // SD Filter Sync control for Ch2
    vu16 rsvd6;                      // Reserved
    union SDCTLPARM3_REG SDCTLPARM3; // Control Parameter Register for Ch3
    union SDDFPARM3_REG SDDFPARM3;   // Data Filter Parameter Register for Ch3
    union SDDPARM3_REG SDDPARM3;     // Data Parameter Register for Ch3
    union SDCMPH3_REG SDCMPH3;       // High-level Threshold Register for Ch3
    union SDCMPL3_REG SDCMPL3;       // Low-level Threshold Register for Ch3
    union SDCPARM3_REG SDCPARM3;     // Comparator Filter Parameter Register for Ch3
    union SDDATA3_REG SDDATA3;       // Data Filter Data Register (16 or 32bit) for Ch3
    union SDDATFIFO3_REG SDDATFIFO3; // Filter Data FIFO Output(32b) for Ch3
    vu16 SDCDATA3;                   // Comparator Filter Data Register (16b) for Ch3
    vu16 rsvd7;                      // Reserved
    union SDCMPHZ3_REG SDCMPHZ3;     // High-level (Z) Threshold Register for Ch3
    union SDFIFOCTL3_REG SDFIFOCTL3; // FIFO Control Register for Ch3
    union SDSYNC3_REG SDSYNC3;       // SD Filter Sync control for Ch3
    vu16 rsvd8;                      // Reserved
    union SDCTLPARM4_REG SDCTLPARM4; // Control Parameter Register for Ch4
    union SDDFPARM4_REG SDDFPARM4;   // Data Filter Parameter Register for Ch4
    union SDDPARM4_REG SDDPARM4;     // Data Parameter Register for Ch4
    union SDCMPH4_REG SDCMPH4;       // High-level Threshold Register for Ch4
    union SDCMPL4_REG SDCMPL4;       // Low-level Threshold Register for Ch4
    union SDCPARM4_REG SDCPARM4;     // Comparator Filter Parameter Register for Ch4
    union SDDATA4_REG SDDATA4;       // Data Filter Data Register (16 or 32bit) for Ch4
    union SDDATFIFO4_REG SDDATFIFO4; // Filter Data FIFO Output(32b) for Ch4
    vu16 SDCDATA4;                   // Comparator Filter Data Register (16b) for Ch4
    vu16 rsvd9;                      // Reserved
    union SDCMPHZ4_REG SDCMPHZ4;     // High-level (Z) Threshold Register for Ch4
    union SDFIFOCTL4_REG SDFIFOCTL4; // FIFO Control Register for Ch4
    union SDSYNC4_REG SDSYNC4;       // SD Filter Sync control for Ch4
};

//---------------------------------------------------------------------------
// SDFM External References & Function Declarations:
//
#define Sdfm1Regs ((SDFM_REGS *)SDFM_BASE)

//*****************************************************************************
//
// Defines for the API.
//
//*****************************************************************************
//! Macro to get the low threshold
//!
#define SDFM_GET_LOW_THRESHOLD(C) ((uint16_t)(C))

//! Macro to get the high threshold
//!
#define SDFM_GET_HIGH_THRESHOLD(C) ((uint16_t)((uint32_t)(C) >> 16U))

//! Macro to convert comparator over sampling ratio to acceptable bit location
//!
#define SDFM_SET_OSR(X) (((X)-1) << 8U)
//! Macro to convert the data shift bit values to acceptable bit location
//!
#define SDFM_SHIFT_VALUE(X) ((X) << 2U)

//! Macro to combine high threshold and low threshold values
//!
#define SDFM_THRESHOLD(H, L) ((((uint32_t)(H)) << 16U) | (L))

//! Macro to set the FIFO level to acceptable bit location
//!
#define SDFM_SET_FIFO_LEVEL(X) ((X) << 7U)

//! Macro to set and enable the zero cross threshold value.
//!
#define SDFM_SET_ZERO_CROSS_THRESH_VALUE(X) (0x8000 | (X))

//! Macros to enable or disable filter.
//!
#define SDFM_FILTER_DISABLE 0x0U
#define SDFM_FILTER_ENABLE  0x2U

//*****************************************************************************
//
//! Values that can be returned from SDFM_getThresholdStatus()
//
//*****************************************************************************
typedef enum
{
    SDFM_OUTPUT_WITHIN_THRESHOLD = 0, //!< SDFM output is within threshold
    SDFM_OUTPUT_ABOVE_THRESHOLD  = 1, //!< SDFM output is above threshold
    SDFM_OUTPUT_BELOW_THRESHOLD  = 2  //!< SDFM output is below threshold
} SDFM_OutputThresholdStatus;

//*****************************************************************************
//
//! Values that can be passed to all functions as the \e filterNumber
//! parameter.
//
//*****************************************************************************
typedef enum
{
    SDFM_FILTER_1 = 0, //!< Digital filter 1
    SDFM_FILTER_2 = 1, //!< Digital filter 2
    SDFM_FILTER_3 = 2, //!< Digital filter 3
    SDFM_FILTER_4 = 3  //!< Digital filter 4
} SDFM_FilterNumber;

//*****************************************************************************
//
//! Values that can be passed to SDFM_setFilterType(),
//! SDFM_setComparatorFilterType() as the \e filterType parameter.
//
//*****************************************************************************
typedef enum
{
    //! Digital filter with SincFast structure.
    SDFM_FILTER_SINC_FAST = 0x00,
    //! Digital filter with Sinc1 structure
    SDFM_FILTER_SINC_1 = 0x10,
    //! Digital filter with Sinc3 structure.
    SDFM_FILTER_SINC_2 = 0x20,
    //! Digital filter with Sinc4 structure.
    SDFM_FILTER_SINC_3 = 0x30
} SDFM_FilterType;

//*****************************************************************************
//
//! Values that can be passed to SDFM_setupModulatorClock(),as the
//! \e clockMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Modulator clock is identical to the data rate
    SDFM_MODULATOR_CLK_EQUAL_DATA_RATE = 0,
    //! Modulator clock is half the data rate
    SDFM_MODULATOR_CLK_HALF_DATA_RATE = 1,
    //! Modulator clock is off. Data is Manchester coded.
    SDFM_MODULATOR_CLK_OFF = 2,
    //! Modulator clock is double the data rate.
    SDFM_MODULATOR_CLK_DOUBLE_DATA_RATE = 3
} SDFM_ModulatorClockMode;

//*****************************************************************************
//
//! Values that can be passed to SDFM_setOutputDataFormat(),as the
//! \e dataFormat parameter.
//
//*****************************************************************************
typedef enum
{
    //! Filter output is in 16 bits 2's complement format.
    SDFM_DATA_FORMAT_16_BIT = 0,
    //! Filter output is in 32 bits 2's complement format.
    SDFM_DATA_FORMAT_32_BIT = 1
} SDFM_OutputDataFormat;

//*****************************************************************************
//
//! Values that can be passed to SDFM_setDataReadyInterruptSource(),as the
//! \e dataReadySource parameter.
//
//*****************************************************************************
typedef enum
{
    //! Data ready interrupt source is direct (non -FIFO).
    SDFM_DATA_READY_SOURCE_DIRECT = 0,
    //! Data ready interrupt source is FIFO.
    SDFM_DATA_READY_SOURCE_FIFO = 1
} SDFM_DataReadyInterruptSource;

//*****************************************************************************
//
//! Values that can be passed to SDFM_setPWMSyncSource(),as the
//! \e syncSource parameter.
//
//*****************************************************************************
typedef enum
{
    SDFM_SYNC_PWM1_SOCA = 0,  //!< SDFM sync source is PWM1 SOCA
    SDFM_SYNC_PWM1_SOCB = 1,  //!< SDFM sync source is PWM1 SOCB
    SDFM_SYNC_PWM2_SOCA = 4,  //!< SDFM sync source is PWM2 SOCA
    SDFM_SYNC_PWM2_SOCB = 5,  //!< SDFM sync source is PWM2 SOCB
    SDFM_SYNC_PWM3_SOCA = 8,  //!< SDFM sync source is PWM3 SOCA
    SDFM_SYNC_PWM3_SOCB = 9,  //!< SDFM sync source is PWM3 SOCB
    SDFM_SYNC_PWM4_SOCA = 12, //!< SDFM sync source is PWM4 SOCA
    SDFM_SYNC_PWM4_SOCB = 13, //!< SDFM sync source is PWM4 SOCB
    SDFM_SYNC_PWM5_SOCA = 16, //!< SDFM sync source is PWM5 SOCA
    SDFM_SYNC_PWM5_SOCB = 17, //!< SDFM sync source is PWM5 SOCB
    SDFM_SYNC_PWM6_SOCA = 20, //!< SDFM sync source is PWM6 SOCA
    SDFM_SYNC_PWM6_SOCB = 21, //!< SDFM sync source is PWM6 SOCB
    SDFM_SYNC_PWM7_SOCA = 24, //!< SDFM sync source is PWM7 SOCA
    SDFM_SYNC_PWM7_SOCB = 25, //!< SDFM sync source is PWM7 SOCB
    SDFM_SYNC_PWM8_SOCA = 28, //!< SDFM sync source is PWM8 SOCA
    SDFM_SYNC_PWM8_SOCB = 29  //!< SDFM sync source is PWM8 SOCB
} SDFM_PWMSyncSource;

//*****************************************************************************
//
//! Values that can be passed to SDFM_setFIFOClearOnSyncMode(),as the
//! \e fifoClearSyncMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! SDFM FIFO buffer is not cleared on Sync signal
    SDFM_FIFO_NOT_CLEARED_ON_SYNC = 0,
    //! SDFM FIFO buffer is cleared on Sync signal
    SDFM_FIFO_CLEARED_ON_SYNC = 1
} SDFM_FIFOClearSyncMode;

//*****************************************************************************
//
//! Values that can be passed to SDFM_setWaitForSyncClearMode(),as the
//! \e syncClearMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Wait for sync cleared using software.
    SDFM_MANUAL_CLEAR_WAIT_FOR_SYNC = 0,
    //! Wait for sync cleared automatically
    SDFM_AUTO_CLEAR_WAIT_FOR_SYNC = 1
} SDFM_WaitForSyncClearMode;

//*****************************************************************************
//
// Values that can be passed to SDFM_enableInterrupt and SDFM_disableInterrupt
// as intFlags parameter
//
//*****************************************************************************
//! Interrupt is generated if Modulator fails.
//!
#define SDFM_MODULATOR_FAILURE_INTERRUPT 0x200U
//! Interrupt on Comparator low-level threshold.
//!
#define SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT 0x40U
//! Interrupt on Comparator high-level threshold.
//!
#define SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT 0x20U
//! Interrupt on Acknowledge flag
//!
#define SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT 0x1U
//! Interrupt on FIFO level
//!
#define SDFM_FIFO_INTERRUPT 0x1000U
//! Interrupt on FIFO overflow
//!
#define SDFM_FIFO_OVERFLOW_INTERRUPT 0x8000U

//*****************************************************************************
//
// Values that can be passed to SDFM_clearInterruptFlag flags parameter
//
//*****************************************************************************
//! Main interrupt flag
//!
#define SDFM_MAIN_INTERRUPT_FLAG 0x80000000U
//! Filter 1 high -level threshold flag
//!
#define SDFM_FILTER_1_HIGH_THRESHOLD_FLAG 0x1U
//! Filter 1 low -level threshold flag
//!
#define SDFM_FILTER_1_LOW_THRESHOLD_FLAG 0x2U
//! Filter 2 high -level threshold flag
//!
#define SDFM_FILTER_2_HIGH_THRESHOLD_FLAG 0x4U
//! Filter 2 low -level threshold flag
//!
#define SDFM_FILTER_2_LOW_THRESHOLD_FLAG 0x8U
//! Filter 3 high -level threshold flag
//!
#define SDFM_FILTER_3_HIGH_THRESHOLD_FLAG 0x10U
//! Filter 3 low -level threshold flag
//!
#define SDFM_FILTER_3_LOW_THRESHOLD_FLAG 0x20U
//! Filter 4 high -level threshold flag
//!
#define SDFM_FILTER_4_HIGH_THRESHOLD_FLAG 0x40U
//! Filter 4 low -level threshold flag
//!
#define SDFM_FILTER_4_LOW_THRESHOLD_FLAG 0x80U
//! Filter 1 modulator failed flag
//!
#define SDFM_FILTER_1_MOD_FAILED_FLAG 0x100U
//! Filter 2 modulator failed flag
//!
#define SDFM_FILTER_2_MOD_FAILED_FLAG 0x200U
//! Filter 3 modulator failed flag
//!
#define SDFM_FILTER_3_MOD_FAILED_FLAG 0x400U
//! Filter 4 modulator failed flag
//!
#define SDFM_FILTER_4_MOD_FAILED_FLAG 0x800U
//! Filter 1 new data flag
//!
#define SDFM_FILTER_1_NEW_DATA_FLAG 0x1000U
//! Filter 2 new data flag
//!
#define SDFM_FILTER_2_NEW_DATA_FLAG 0x2000U
//! Filter 3 new data flag
//!
#define SDFM_FILTER_3_NEW_DATA_FLAG 0x4000U
//! Filter 4 new data flag
//!
#define SDFM_FILTER_4_NEW_DATA_FLAG 0x8000U
//! Filter 1 FIFO overflow flag
//!
#define SDFM_FILTER_1_FIFO_OVERFLOW_FLAG 0x10000U
//! Filter 2 FIFO overflow flag
//!
#define SDFM_FILTER_2_FIFO_OVERFLOW_FLAG 0x20000U
//! Filter 3 FIFO overflow flag
//!
#define SDFM_FILTER_3_FIFO_OVERFLOW_FLAG 0x40000U
//! Filter 4 FIFO overflow flag
//!
#define SDFM_FILTER_4_FIFO_OVERFLOW_FLAG 0x80000U
//! Filter 1 FIFO overflow flag
//!
#define SDFM_FILTER_1_FIFO_INTERRUPT_FLAG 0x100000U
//! Filter 2 FIFO overflow flag
//!
#define SDFM_FILTER_2_FIFO_INTERRUPT_FLAG 0x200000U
//! Filter 3 FIFO overflow flag
//!
#define SDFM_FILTER_3_FIFO_INTERRUPT_FLAG 0x400000U
//! Filter 4 FIFO overflow flag
//!
#define SDFM_FILTER_4_FIFO_INTERRUPT_FLAG 0x800000U

//*****************************************************************************
//
//! \internal
//! Checks SDFM base address.
//!
//! \param base specifies the SDFM module base address.
//!
//! This function determines if SDFM module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool SDFM_isBaseValid(uint32_t base)
{
    return ((base == SDFM1_BASE));
}
#endif

//*****************************************************************************
//
//! Enable external reset
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function enables data filter to be reset by an external source (PWM
//! compare output).
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_enableExternalReset(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Set the SDSYNCEN bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U)) |= SDFM_SDDFPARM1_SDSYNCEN;
    EDIS;
}

//*****************************************************************************
//
//! Disable external reset
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function disables data filter from being reset by an external source
//! (PWM compare output).
//!
//! \return None.
//*****************************************************************************
static inline void SDFM_disableExternalReset(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Clear the SDSYNCEN bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U)) &= ~SDFM_SDDFPARM1_SDSYNCEN;
    EDIS;
}

//*****************************************************************************
//
//! Enable filter
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function enables the filter specified by the \e filterNumber variable.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_enableFilter(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Set the FEN bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U)) |= SDFM_SDDFPARM1_FEN;
    EDIS;
}

//*****************************************************************************
//
//! Disable filter
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function disables the filter specified by the \e filterNumber
//! variable.
//!
//! \return None.
//*****************************************************************************
static inline void SDFM_disableFilter(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Clear the FEN bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U)) &= ~SDFM_SDDFPARM1_FEN;
    EDIS;
}

//*****************************************************************************
//
//! Enable FIFO buffer
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function enables the filter FIFO buffer specified by the
//! \e filterNumber variable.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_enableFIFOBuffer(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Set the FFEN bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDFIFOCTL1 + ((uint32_t)filterNumber * 16U)) |= SDFM_SDFIFOCTL1_FFEN;
    EDIS;
}

//*****************************************************************************
//
//! Disable FIFO buffer
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function disables the filter FIFO buffer specified by the
//! \e filterNumber variable.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_disableFIFOBuffer(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Clear the FFEN bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDFIFOCTL1 + ((uint32_t)filterNumber * 16U)) &= ~SDFM_SDFIFOCTL1_FFEN;
    EDIS;
}

//*****************************************************************************
//
//! Return the Zero Cross Trip status
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the Zero Cross Trip status for the filter
//! specified by filterNumber variable.
//!
//! \return \b true if Comparator filter output >= High-level threshold (Z)
//!         \b false if Comparator filter output < High-level threshold (Z)
//
//*****************************************************************************
static inline bool SDFM_getZeroCrossTripStatus(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    return (((HWREGH(base + SDFM_O_SDSTATUS) >> (uint16_t)filterNumber) & 0x1U) == 1U);
}

//*****************************************************************************
//
//! Clear the Zero Cross Trip status
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//!  This function clears the Zero Cross Trip status for the filter
//!  specified by filterNumber variable.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_clearZeroCrossTripStatus(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Set SDCTL MIE bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDCTL) |= ((uint16_t)1U << (uint16_t)filterNumber);
    EDIS;
}

//*****************************************************************************
//
//! Enable Comparator.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//!  This function enables the Comparator for the selected filter.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_enableComparator(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Set CEN bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDCPARM1 + ((uint32_t)filterNumber * 16U)) |= SDFM_SDCPARM1_CEN;
    EDIS;
}

//*****************************************************************************
//
//! Disable Comparator.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//!  This function disables the Comparator for the selected filter.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_disableComparator(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Clear CEN bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDCPARM1 + ((uint32_t)filterNumber * 16U)) &= ~SDFM_SDCPARM1_CEN;
    EDIS;
}

//*****************************************************************************
//
//! Set filter type.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param filterType is the filter type or structure.
//!
//! This function sets the filter type or structure to be used as specified by
//! filterType for the selected filter number as specified by filterNumber.
//!
//! \return None.
//*****************************************************************************
static inline void SDFM_setFilterType(uint32_t base, SDFM_FilterNumber filterNumber, SDFM_FilterType filterType)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));

    address = base + SDFM_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to SST bits
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & (~SDFM_SDDFPARM1_SST_M)) | ((uint16_t)filterType << 6U);
    EDIS;
}

//*****************************************************************************
//
//! Set data filter over sampling ratio.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param overSamplingRatio is the data filter over sampling ratio.
//!
//! This function sets the filter oversampling ratio for the filter specified
//! by the filterNumber variable.Valid values for the variable
//! overSamplingRatio are 0 to 255 inclusive. The actual oversampling ratio
//! will be this value plus one.
//!
//! \return None.
//*****************************************************************************
static inline void SDFM_setFilterOverSamplingRatio(
    uint32_t base, SDFM_FilterNumber filterNumber, uint16_t overSamplingRatio)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));
    ASSERT(overSamplingRatio < 256U);

    address = base + SDFM_O_SDDFPARM1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to DOSR bits
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & (~SDFM_SDDFPARM1_DOSR_M)) | overSamplingRatio;
    EDIS;
}

//*****************************************************************************
//
//! Set modulator clock mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param clockMode is the modulator clock mode.
//!
//! This function sets the modulator clock mode specified by clockMode
//! for the filter specified by filterNumber.
//!
//!
//! \return None.
//*****************************************************************************
static inline void SDFM_setupModulatorClock(
    uint32_t base, SDFM_FilterNumber filterNumber, SDFM_ModulatorClockMode clockMode)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));

    address = base + SDFM_O_SDCTLPARM1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to MOD bits
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & (~SDFM_SDCTLPARM1_MOD_M)) | (uint16_t)clockMode;

    EDIS;
}

//*****************************************************************************
//
//! Set the output data format
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param dataFormat is the output data format.
//!
//! This function sets the output data format for the filter specified by
//! filterNumber.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setOutputDataFormat(
    uint32_t base, SDFM_FilterNumber filterNumber, SDFM_OutputDataFormat dataFormat)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));

    address = base + SDFM_O_SDDPARM1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to DR bit
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & (~SDFM_SDDPARM1_DR)) | ((uint16_t)dataFormat << 10U);
    EDIS;
}

//*****************************************************************************
//
//! Set data shift value.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param shiftValue is the data shift value.
//!
//! This function sets the shift value for the 16 bit 2's complement data
//! format. The valid maximum value for shiftValue is 31.
//!
//! \b Note: Use this function with 16 bit 2's complement data format only.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setDataShiftValue(uint32_t base, SDFM_FilterNumber filterNumber, uint16_t shiftValue)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));
    ASSERT(shiftValue < 32U);

    address = base + SDFM_O_SDDPARM1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to SH bit
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & (~SDFM_SDDPARM1_SH_M)) | (shiftValue << SDFM_SDDPARM1_SH_S);
    EDIS;
}

//*****************************************************************************
//
//! Set Filter output high-level threshold.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param highThreshold is the high-level threshold.
//!
//! This function sets the unsigned high-level threshold value for the
//! Comparator filter output. If the output value of the filter exceeds
//! highThreshold and interrupt generation is enabled, an interrupt will be
//! issued.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setCompFilterHighThreshold(
    uint32_t base, SDFM_FilterNumber filterNumber, uint16_t highThreshold)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));
    ASSERT(highThreshold < 0x7FFFU);

    address = base + SDFM_O_SDCMPH1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to HLT bit
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & ~SDFM_SDCMPH1_HLT_M) | highThreshold;
    EDIS;
}

//*****************************************************************************
//
//! Set Filter output low-level threshold.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param lowThreshold is the low-level threshold.
//!
//! This function sets the unsigned low-level threshold value for the
//! Comparator filter output. If the output value of the filter gets below
//! lowThreshold and interrupt generation is enabled, an interrupt will be
//! issued.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setCompFilterLowThreshold(uint32_t base, SDFM_FilterNumber filterNumber, uint16_t lowThreshold)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));
    ASSERT(lowThreshold < 0x7FFFU);

    address = base + SDFM_O_SDCMPL1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to LLT bit
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & ~SDFM_SDCMPL1_LLT_M) | lowThreshold;
    EDIS;
}

//*****************************************************************************
//
//! Set Filter output zero-cross threshold.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param zeroCrossThreshold is the zero-cross threshold.
//!
//! This function sets the unsigned zero-cross threshold value for the
//! Comparator filter output.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setCompFilterZeroCrossThreshold(
    uint32_t base, SDFM_FilterNumber filterNumber, uint16_t zeroCrossThreshold)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));
    ASSERT(zeroCrossThreshold < 0x7FFFU);

    address = base + SDFM_O_SDCMPHZ1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to ZCT bit
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & ~SDFM_SDCMPHZ1_HLTZ_M) | zeroCrossThreshold;

    EDIS;
}

//*****************************************************************************
//
//! Enable zero-cross Edge detect mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function enables Zero Cross Edge detection.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_enableZeroCrossEdgeDetect(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Set ZCEN bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDCPARM1 + ((uint32_t)filterNumber * 16U)) |= SDFM_SDCPARM1_HZEN;
    EDIS;
}

//*****************************************************************************
//
//! Disable zero-cross Edge detect mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function disables Zero Cross Edge detection.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_disableZeroCrossEdgeDetect(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Clear ZCEN bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDCPARM1 + ((uint32_t)filterNumber * 16U)) &= ~SDFM_SDCPARM1_HZEN;
    EDIS;
}

//*****************************************************************************
//
//! Enable SDFM interrupts.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param intFlags is the interrupt source.
//!
//! This function enables the low threshold , high threshold or modulator
//! failure interrupt as determined by intFlags for the filter specified
//! by filterNumber.
//! Valid values for intFlags are:
//!  SDFM_MODULATOR_FAILURE_INTERRUPT , SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT,
//!  SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT, SDFM_FIFO_INTERRUPT,
//!  SDFM_FIFO_OVERFLOW_INTERRUPT,SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_enableInterrupt(uint32_t base, SDFM_FilterNumber filterNumber, uint16_t intFlags)
{
    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = (uint16_t)filterNumber * 16U;

    EALLOW;

    //
    // Low, high threshold, Modulator failure
    //
    if ((intFlags
            & (SDFM_MODULATOR_FAILURE_INTERRUPT | SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT
                | SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT))
        != 0U)
    {
        //
        // Set IEL or IEH or MFIE bit of SDFM_O_SDCPARMx
        //
        HWREGH(base + SDFM_O_SDCPARM1 + offset)
            |= (intFlags
                & (SDFM_MODULATOR_FAILURE_INTERRUPT | SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT
                    | SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT));
    }

    //
    // Data filter acknowledge interrupt
    //
    if ((intFlags & SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT) != 0U)
    {
        HWREGH(base + SDFM_O_SDDFPARM1 + offset) |= SDFM_SDDFPARM1_AE;
    }

    //
    // FIFO , FIFO overflow interrupt
    //
    if ((intFlags & (SDFM_FIFO_INTERRUPT | SDFM_FIFO_OVERFLOW_INTERRUPT)) != 0U)
    {
        //
        // Set OVFIEN or FFIEN bits of SDFM_O_SDFIFOCTLx
        //
        HWREGH(base + SDFM_O_SDFIFOCTL1 + offset) |= (intFlags & (SDFM_FIFO_INTERRUPT | SDFM_FIFO_OVERFLOW_INTERRUPT));
    }
    EDIS;
}

//*****************************************************************************
//
//! Disable SDFM interrupts.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param intFlags is the interrupt source.
//!
//! This function disables the low threshold , high threshold or modulator
//! failure interrupt as determined by intFlags for the filter
//! specified by filterNumber.
//! Valid values for intFlags are:
//!  SDFM_MODULATOR_FAILURE_INTERRUPT , SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT,
//!  SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT, SDFM_FIFO_INTERRUPT,
//!  SDFM_FIFO_OVERFLOW_INTERRUPT,SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_disableInterrupt(uint32_t base, SDFM_FilterNumber filterNumber, uint16_t intFlags)
{
    uint16_t offset;

    ASSERT(SDFM_isBaseValid(base));

    offset = (uint16_t)filterNumber * 16U;

    EALLOW;

    //
    // Low, high threshold, modulator failure interrupts
    //
    if ((intFlags
            & (SDFM_MODULATOR_FAILURE_INTERRUPT | SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT
                | SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT))
        != 0U)
    {
        //
        // Set IEL or IEH or MFIE bit of SDFM_O_SDCPARMx
        //
        HWREGH(base + SDFM_O_SDCPARM1 + offset)
            &= ~(intFlags
                 & (SDFM_MODULATOR_FAILURE_INTERRUPT | SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT
                     | SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT));
    }

    //
    // Data filter acknowledge interrupt
    //
    if ((intFlags & SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT) != 0U)
    {
        HWREGH(base + SDFM_O_SDDFPARM1 + offset) &= ~SDFM_SDDFPARM1_AE;
    }

    //
    // FIFO , FIFO overflow interrupt
    //
    if ((intFlags & (SDFM_FIFO_INTERRUPT | SDFM_FIFO_OVERFLOW_INTERRUPT)) != 0U)
    {
        //
        // Set OVFIEN or FFIEN bits of SDFM_O_SDFIFOCTLx
        //
        HWREGH(base + SDFM_O_SDFIFOCTL1 + offset) &= ~(intFlags & (SDFM_FIFO_INTERRUPT | SDFM_FIFO_OVERFLOW_INTERRUPT));
    }
    EDIS;
}

//*****************************************************************************
//
//! Set the comparator filter type.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param filterType is the comparator filter type or structure.
//!
//! This function sets the Comparator filter type or structure to be used as
//! specified by filterType for the selected filter number as specified by
//! filterNumber.
//!
//! \return None.
//*****************************************************************************
static inline void SDFM_setComparatorFilterType(
    uint32_t base, SDFM_FilterNumber filterNumber, SDFM_FilterType filterType)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));

    address = base + SDFM_O_SDCPARM1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to CS1_CS0 bits
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & (~SDFM_SDCPARM1_CS1_CS0_M)) | ((uint16_t)filterType << 3U);
    EDIS;
}

//*****************************************************************************
//
//! Set Comparator filter over sampling ratio.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param overSamplingRatio is the comparator filter over sampling ration.
//!
//! This function sets the comparator filter oversampling ratio for the filter
//! specified by the filterNumber.Valid values for the variable
//! overSamplingRatio are 0 to 31 inclusive.
//! The actual oversampling ratio will be this value plus one.
//!
//! \return None.
//*****************************************************************************
static inline void SDFM_setCompFilterOverSamplingRatio(
    uint32_t base, SDFM_FilterNumber filterNumber, uint16_t overSamplingRatio)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));
    ASSERT(overSamplingRatio < 32U);

    address = base + SDFM_O_SDCPARM1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to COSR bits
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & (~SDFM_SDCPARM1_COSR_M)) | overSamplingRatio;
    EDIS;
}

//*****************************************************************************
//
//! Get the filter data output.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the latest data filter output. Depending on the
//! filter data output format selected, the valid value will be the lower 16
//! bits or the whole 32 bits of the returned value.
//!
//! \return Returns the latest data filter output.
//*****************************************************************************
static inline uint32_t SDFM_getFilterData(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Read SDDATA bits
    //
    return (HWREG(base + SDFM_O_SDDATA1 + ((uint32_t)filterNumber * 16U)));
}

//*****************************************************************************
//
//! Get the Comparator threshold status.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the Comparator output threshold status for the given
//! filterNumber.
//!
//! \return Returns the following status flags.
//! - \b SDFM_OUTPUT_WITHIN_THRESHOLD if the output is within the
//!                                   specified threshold.
//! - \b SDFM_OUTPUT_ABOVE_THRESHOLD  if the output is above the high
//!                                   threshold
//! - \b SDFM_OUTPUT_BELOW_THRESHOLD  if the output is below the low
//!                                   threshold.
//!
//*****************************************************************************
static inline SDFM_OutputThresholdStatus SDFM_getThresholdStatus(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Read SDIFLG high/low threshold bits
    //
    return ((SDFM_OutputThresholdStatus)((HWREG(base + SDFM_O_SDIFLG) >> (2U * (uint16_t)filterNumber)) & 0x3U));
}

//*****************************************************************************
//
//! Get the Modulator status.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the Modulator status.
//!
//! \return Returns true if the Modulator is operating normally
//!         Returns false if the Modulator has failed
//!
//*****************************************************************************
static inline bool SDFM_getModulatorStatus(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Read SDIFLG MF1, MF2, MF3 OR MF4 bits
    //
    return (((HWREG(base + SDFM_O_SDIFLG) >> ((uint16_t)filterNumber + 8U)) & 0x1U) != 0x1U);
}

//*****************************************************************************
//
//! Check if new Filter data is available.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns new filter data status.
//!
//! \return Returns \b true if new filter data is available
//!         Returns \b false if no new filter data is available
//!
//*****************************************************************************
static inline bool SDFM_getNewFilterDataStatus(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Read SDIFLG AF1, AF2, AF3 OR AF4 bits
    //
    return (((HWREG(base + SDFM_O_SDIFLG) >> ((uint16_t)filterNumber + 12U)) & 0x1U) == 0x1U);
}

//*****************************************************************************
//
//! Check if FIFO buffer is overflowed.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the status of the FIFO buffer overflow for the given
//! filter value.
//!
//! \return Returns \b true if FIFO buffer is overflowed
//!         Returns \b false if FIFO buffer is not overflowed
//!
//*****************************************************************************
static inline bool SDFM_getFIFOOverflowStatus(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Read SDIFLG SDFFOVF1, SDFFOVF2, SDFFOVF3 OR SDFFOVF4 bits
    //
    return (((HWREG(base + SDFM_O_SDIFLG) >> ((uint16_t)filterNumber + 16U)) & 0x1U) == 0x1U);
}

//*****************************************************************************
//
//! Check FIFO buffer interrupt status.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the status of the FIFO buffer interrupt for the given
//! filter.
//!
//! \return Returns \b true if FIFO buffer interrupt has occurred.
//!         Returns \b false if FIFO buffer interrupt has not occurred.
//!
//*****************************************************************************
static inline bool SDFM_getFIFOISRStatus(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Read SDIFLG SDFFINT1, SDFFINT2, SDFFINT3 OR SDFFINT4 bits
    //
    return (((HWREG(base + SDFM_O_SDIFLG) >> ((uint16_t)filterNumber + 20U)) & 0x1U) == 0x1U);
}

//*****************************************************************************
//
//! Get pending interrupt.
//!
//! \param base is the base address of the SDFM module
//!
//! This function returns any pending interrupt status.
//!
//! \return Returns \b true if there is a pending interrupt.
//!         Returns \b false if no interrupt is pending.
//!
//*****************************************************************************
static inline bool SDFM_getIsrStatus(uint32_t base)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Read SDIFLG MIF
    //
    return ((HWREG(base + SDFM_O_SDIFLG) >> 31U) == 0x1U);
}

//*****************************************************************************
//
//! Clear pending flags.
//!
//! \param base is the base address of the SDFM module
//! \param flag is the SDFM status
//!
//! This function clears the specified pending interrupt flag.
//! Valid values are
//! SDFM_MAIN_INTERRUPT_FLAG,SDFM_FILTER_1_NEW_DATA_FLAG,
//! SDFM_FILTER_2_NEW_DATA_FLAG,SDFM_FILTER_3_NEW_DATA_FLAG,
//! SDFM_FILTER_4_NEW_DATA_FLAG,SDFM_FILTER_1_MOD_FAILED_FLAG,
//! SDFM_FILTER_2_MOD_FAILED_FLAG,SDFM_FILTER_3_MOD_FAILED_FLAG,
//! SDFM_FILTER_4_MOD_FAILED_FLAG,SDFM_FILTER_1_HIGH_THRESHOLD_FLAG,
//! SDFM_FILTER_1_LOW_THRESHOLD_FLAG,SDFM_FILTER_2_HIGH_THRESHOLD_FLAG,
//! SDFM_FILTER_2_LOW_THRESHOLD_FLAG,SDFM_FILTER_3_HIGH_THRESHOLD_FLAG,
//! SDFM_FILTER_3_LOW_THRESHOLD_FLAG,SDFM_FILTER_4_HIGH_THRESHOLD_FLAG,
//! SDFM_FILTER_4_LOW_THRESHOLD_FLAG,SDFM_FILTER_1_FIFO_OVERFLOW_FLAG,
//! SDFM_FILTER_2_FIFO_OVERFLOW_FLAG,SDFM_FILTER_3_FIFO_OVERFLOW_FLAG
//! SDFM_FILTER_4_FIFO_OVERFLOW_FLAG,SDFM_FILTER_1_FIFO_INTERRUPT_FLAG,
//! SDFM_FILTER_2_FIFO_INTERRUPT_FLAG,SDFM_FILTER_3_FIFO_INTERRUPT_FLAG
//! SDFM_FILTER_4_FIFO_INTERRUPT_FLAG or any combination of the above flags.
//!
//! \return None
//!
//*****************************************************************************
static inline void SDFM_clearInterruptFlag(uint32_t base, uint32_t flag)
{
    ASSERT(SDFM_isBaseValid(base));
    ASSERT((flag & 0x80FFFFFFU) == flag);

    //
    // Write to  SDIFLGCLR register
    //
    HWREG(base + SDFM_O_SDIFLGCLR) |= flag;
}

//*****************************************************************************
//
//! Enable main interrupt.
//!
//! \param base is the base address of the SDFM module
//!
//! This function enables the main SDFM interrupt.
//!
//! \return None
//!
//*****************************************************************************
static inline void SDFM_enableMainInterrupt(uint32_t base)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Set SDCTL MIE bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDCTL) |= SDFM_SDCTL_MIE;
    EDIS;
}

//*****************************************************************************
//
//! Disable main interrupt.
//!
//! \param base is the base address of the SDFM module
//!
//! This function disables the main SDFM interrupt.
//!
//! \return None
//!
//*****************************************************************************
static inline void SDFM_disableMainInterrupt(uint32_t base)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Clear SDCTL MIE bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDCTL) &= ~SDFM_SDCTL_MIE;
    EDIS;
}

//*****************************************************************************
//
//! Enable main filter.
//!
//! \param base is the base address of the SDFM module
//!
//! This function enables main filter.
//!
//! \return None
//!
//*****************************************************************************
static inline void SDFM_enableMainFilter(uint32_t base)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Set SDMFILEN MFE bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDMFILEN) |= SDFM_SDMFILEN_MFE;
    EDIS;
}

//*****************************************************************************
//
//! Disable main filter.
//!
//! \param base is the base address of the SDFM module
//!
//! This function disables main filter.
//!
//! \return None
//!
//*****************************************************************************
static inline void SDFM_disableMainFilter(uint32_t base)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Clear SDMFILEN MFE bit
    //
    EALLOW;
    HWREGH(base + SDFM_O_SDMFILEN) &= ~SDFM_SDMFILEN_MFE;
    EDIS;
}

//*****************************************************************************
//
//! Return the FIFO data count
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the FIFO data count.
//!
//! \return Returns the number of data words available in FIFO buffer.
//
//*****************************************************************************
static inline uint16_t SDFM_getFIFODataCount(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Read SDFFST
    //
    return ((HWREGH(base + SDFM_O_SDFIFOCTL1 + ((uint32_t)filterNumber * 16U)) & SDFM_SDFIFOCTL1_SDFFST_M)
            >> SDFM_SDFIFOCTL1_SDFFST_S);
}

//*****************************************************************************
//
//! Return the Comparator sinc filter data
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the Comparator sinc filter data output.
//!
//! \return Returns the Comparator sinc filter data output.
//!
//
//*****************************************************************************
static inline uint16_t SDFM_getComparatorSincData(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Read SDCDATA
    //
    return (HWREGH(base + SDFM_O_SDCDATA1 + ((uint32_t)filterNumber * 16U)));
}

//*****************************************************************************
//
//! Return the FIFO data
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the latest FIFO data.
//!
//! \return Returns the latest FIFO data.
//!
//! \note Discard the upper 16 bits if the output data format is 16bits.
//
//*****************************************************************************
static inline uint32_t SDFM_getFIFOData(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Read SDDATFIFO
    //
    return (HWREG(base + SDFM_O_SDDATFIFO1 + ((uint32_t)filterNumber * 16U)));
}

//*****************************************************************************
//
//! Set the FIFO interrupt level.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param fifoLevel is the FIFO interrupt level.
//!
//! This function sets the FIFO interrupt level. Interrupt is generated when
//! the FIFO buffer word count gets to or exceeds the value of \e fifoLevel.
//! Maximum value for \e fifoLevel is 16.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setFIFOInterruptLevel(uint32_t base, SDFM_FilterNumber filterNumber, uint16_t fifoLevel)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));
    ASSERT(fifoLevel <= 16U);

    address = base + SDFM_O_SDFIFOCTL1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to SDFFIL bit
    //
    EALLOW;
    HWREGH(address) = ((HWREGH(address) & (~SDFM_SDFIFOCTL1_SDFFIL_M)) | fifoLevel);
    EDIS;
}

//*****************************************************************************
//
//! Set data ready interrupt source.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param dataReadySource is the data ready interrupt source.
//!
//! This function sets the data ready interrupt source.
//! Valid values for \e dataReadySource:
//!   - SDFM_DATA_READY_SOURCE_DIRECT - Direct data ready
//!   - SDFM_DATA_READY_SOURCE_FIFO  - FIFO data ready.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setDataReadyInterruptSource(
    uint32_t base, SDFM_FilterNumber filterNumber, SDFM_DataReadyInterruptSource dataReadySource)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));

    address = base + SDFM_O_SDFIFOCTL1 + ((uint32_t)filterNumber * 16U);

    //
    // Write to DRINTSEL
    //
    EALLOW;
    HWREGH(address) = (HWREGH(address) & ~SDFM_SDFIFOCTL1_DRINTSEL) | ((uint16_t)dataReadySource << 14U);
    EDIS;
}

//*****************************************************************************
//
//! Get the wait-for-sync event status.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function returns the Wait-for-Sync event status.
//!
//! \return Returns true if sync event has occurred.
//!         Returns false if sync event has not occurred.
//
//*****************************************************************************
static inline bool SDFM_getWaitForSyncStatus(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    //
    // Read WTSYNFLG bit
    //
    return (((HWREGH(base + SDFM_O_SDSYNC1 + ((uint32_t)filterNumber * 16U)) & SDFM_SDSYNC1_WTSYNFLG) >> 7U) == 0x1U);
}

//*****************************************************************************
//
//! Clear the Wait-for-sync event status.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function clears the Wait-for-sync event status.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_clearWaitForSyncFlag(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    EALLOW;

    //
    // Clear WTSYNCLR bit
    //
    HWREGH(base + SDFM_O_SDSYNC1 + ((uint32_t)filterNumber * 16U)) |= SDFM_SDSYNC1_WTSYNCLR;
    EDIS;
}

//*****************************************************************************
//
//! Enable wait for sync mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function enables the wait for sync mode. Data to FIFO will be written
//! only after PWM sync event.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_enableWaitForSync(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    EALLOW;

    //
    // Set WTSYNCEN bit
    //
    HWREGH(base + SDFM_O_SDSYNC1 + ((uint32_t)filterNumber * 16U)) |= SDFM_SDSYNC1_WTSYNCEN;
    EDIS;
}

//*****************************************************************************
//
//! Disable wait for sync mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//!
//! This function disables the wait for sync mode. Data to FIFO will be written
//! every Data ready event.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_disableWaitForSync(uint32_t base, SDFM_FilterNumber filterNumber)
{
    ASSERT(SDFM_isBaseValid(base));

    EALLOW;

    //
    // Clear WTSYNCEN bit
    //
    HWREGH(base + SDFM_O_SDSYNC1 + ((uint32_t)filterNumber * 16U)) &= ~SDFM_SDSYNC1_WTSYNCEN;
    EDIS;
}

//*****************************************************************************
//
//! Set the PWM sync mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param syncSource is the PWM sync source.
//!
//! This function sets the PWM sync source for the specific SDFM filter. Valid
//! values for syncSource are SDFM_SYNC_PWMx_CMPy. Where x ranges from 1 to 8
//! Representing PWM1 to PWM8 respectively and y ranges from A to D
//! representing PWM comparators A to D.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setPWMSyncSource(uint32_t base, SDFM_FilterNumber filterNumber, SDFM_PWMSyncSource syncSource)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));

    address = base + SDFM_O_SDSYNC1 + ((uint32_t)filterNumber * 16U);

    EALLOW;

    //
    // Write to SYNCSEL bits
    //
    HWREGH(address) = (HWREGH(address) & ~SDFM_SDSYNC1_SYNCSEL_M) | (uint16_t)syncSource;
    EDIS;

    //
    // Enable SDSYNC reset to data filter
    //
    SDFM_enableExternalReset(base, filterNumber);
}

//*****************************************************************************
//
//! Set FIFO clear on sync mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param fifoClearSyncMode is the FIFO clear on sync mode.
//!
//! This function sets the FIFO clear mode for the specified filter when a sync
//! happens depending on the value of fifoClearSyncMode.
//! Valid values for fifoClearSyncMode are:
//!  - SDFM_FIFO_NOT_CLEARED_ON_SYNC - FIFO is not cleared on sync.
//!  - SDFM_FIFO_CLEARED_ON_SYNC - FIFO is cleared on sync.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setFIFOClearOnSyncMode(
    uint32_t base, SDFM_FilterNumber filterNumber, SDFM_FIFOClearSyncMode fifoClearSyncMode)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));

    address = base + SDFM_O_SDSYNC1 + ((uint32_t)filterNumber * 16U);

    EALLOW;

    //
    // Write to FFSYNCCLREN bit
    //
    HWREGH(address) = (HWREGH(address) & ~SDFM_SDSYNC1_FFSYNCCLREN) | ((uint16_t)fifoClearSyncMode << 9U);
    EDIS;
}

//*****************************************************************************
//
//! Set Wait-for-sync clear mode.
//!
//! \param base is the base address of the SDFM module
//! \param filterNumber is the filter number.
//! \param syncClearMode is the wait-for-sync clear mode.
//!
//! This function sets the Wait-For-sync clear mode depending on the value of
//! syncClearMode.
//! Valid values for syncClearMode are:
//!   - SDFM_MANUAL_CLEAR_WAIT_FOR_SYNC - Wait-for-sync flag is cleared by
//!                                       invoking SDFM_clearWaitForSyncFlag().
//!   - SDFM_AUTO_CLEAR_WAIT_FOR_SYNC   - Wait-for-sync flag is cleared
//!                                       automatically on FIFO interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void SDFM_setWaitForSyncClearMode(
    uint32_t base, SDFM_FilterNumber filterNumber, SDFM_WaitForSyncClearMode syncClearMode)
{
    uint32_t address;

    ASSERT(SDFM_isBaseValid(base));

    address = base + SDFM_O_SDSYNC1 + ((uint32_t)filterNumber * 16U);

    EALLOW;

    //
    // Write to WTSCLREN  bit
    //
    HWREGH(address) = (HWREGH(address) & ~SDFM_SDSYNC1_WTSCLREN) | ((uint16_t)syncClearMode << 10U);
    EDIS;
}

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Configures SDFM comparator for filter config & threshold values
//!
//! \param base is the base address of the SDFM module
//! \param config1 is the filter number, filter type and over sampling ratio.
//! \param config2 is high-level and low-level threshold values.
//! \param config3 is the zero-cross threshold value.
//!
//! This function configures the comparator filter for filter config and
//! threshold values based on provided inputs.
//!
//! The config1 parameter is the logical OR of the filter number, filter type
//! and oversampling ratio.
//! The bit definitions for config1 are as follow:
//!   - config1.[3:0]  filter number
//!   - config1.[7:4]  filter type
//!   - config1.[15:8] Over sampling Ratio
//! Valid values for filter number and filter type are defined in
//! SDFM_FilterNumber and SDFM_FilterType enumerations respectively.
//! SDFM_SET_OSR(X) macro can be used to set the value of the oversampling
//! ratio ,which ranges [1,32] inclusive, in the appropriate bit location.
//! For example the value
//! (SDFM_FILTER_1 | SDFM_FILTER_SINC_2 | SDFM_SET_OSR(16))
//! will select Filter 1, SINC 2 type with an oversampling ratio of 16.
//!
//! The config2 parameter is the logical OR of the filter high and low
//! threshold values.
//! The bit definitions for config2 are as follow:
//!   - config2.[15:0]  low threshold
//!   - config2.[31:16] high threshold
//! The upper 16 bits define the high threshold and the lower
//! 16 bits define the low threshold.
//! SDFM_THRESHOLD(H,L) can be used to combine the high and low thresholds.
//!
//! The config3 parameter is the logical OR of the zero cross threshold
//! enable flag and the zero-cross threshold value.
//! The bit definitions for config3 are as follow:
//!   - config3.[15] - Enable or disable zero cross threshold. Valid values
//!                    are 1 or 0 to enable or disable the zero cross threshold
//!                    respectively.
//!   -config3.[14:0] - Zero Cross Threshold value.
//! The SDFM_SET_ZERO_CROSS_THRESH_VALUE(X) macro can be used to specify the
//! zero-cross threshold value and OR the 1 to enable it.
//!
//! \return None.
//!
//*****************************************************************************
extern void SDFM_configComparator(uint32_t base, uint16_t config1, uint32_t config2, uint16_t config3);

//*****************************************************************************
//
//! Configure SDFM data filter
//!
//! \param base is the base address of the SDFM module
//! \param config1 is the filter number, filter type and over sampling ratio
//!                configuration.
//! \param config2 is filter switch, data representation and data shift values
//!                configuration.
//!
//! This function configures the data filter based on configurations
//! config1 and config2.
//!
//! The config1 parameter is the logical OR of the filter number, filter type
//! and oversampling ratio.
//! The bit definitions for config1 are as follow:
//!   - config1.[3:0]  Filter number
//!   - config1.[7:4]  Filter type
//!   - config1.[15:8] Over sampling Ratio
//! Valid values for filter number and filter type are defined in
//! SDFM_FilterNumber and SDFM_FilterType enumerations respectively.
//! SDFM_SET_OSR(X) macro can be used to set the value of the oversampling
//! ratio , which ranges [1,256] inclusive , in the appropriate bit location
//! for config1. For example the value
//! (SDFM_FILTER_2 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(64))
//! will select Filter 2 , SINC 3 type with an oversampling ratio of 64.
//!
//! The config2 parameter is the logical OR of data representation, filter
//! switch, and data shift values
//! The bit definitions for config2 are as follow:
//!   - config2.[0]  Data representation
//!   - config2.[1]  Filter switch
//!   - config2.[15:2]  Shift values
//! Valid values for data representation are given in SDFM_OutputDataFormat
//! enumeration. SDFM_FILTER_DISABLE or SDFM_FILTER_ENABLE will define the
//! filter switch values.SDFM_SHIFT_VALUE(X) macro can be used to set the value
//! of the data shift value,which ranges [0,31] inclusive, in the appropriate
//! bit location for config2.
//! The shift value is valid only in SDFM_DATA_FORMAT_16_BIT data
//! representation format.
//!
//! \return None.
//!
//*****************************************************************************
extern void SDFM_configDataFilter(uint32_t base, uint16_t config1, uint16_t config2);

//*****************************************************************************
//
//! Configure SDFM comparator Zero Cross threshold
//!
//! \param base is the base address of the SDFM module
//! \param config1 is the filter number, filter type and over sampling ratio.
//! \param config2 is the zero cross threshold value.
//!
//! This function configures the comparator filter zero cross threshold values
//! based on configurations config1 and config2.
//!
//! The config1 parameter is the logical OR of the filter number, filter type
//! and oversampling ratio.
//! The bit definitions for config1 are as follow:
//!   - config1.[3:0]  filter number
//!   - config1.[7:4]  filter type
//!   - config1.[15:8] Over sampling Ratio
//! Valid values for filter number and filter type are defined in
//! SDFM_FilterNumber and SDFM_FilterType enumerations respectively.
//! SDFM_SET_OSR(X) macro can be used to set the value of the oversampling
//! ratio ,which ranges [1,32] inclusive, in the appropriate bit location.
//! For example the value
//! (SDFM_FILTER_1 | SDFM_FILTER_SINC_2 | SDFM_SET_OSR(16))
//! will select Filter 1 , SINC 2 type with an oversampling ratio of 16.
//!
//! The config2 parameter is the value of the zero cross threshold. The maximum
//! acceptable value is 32767.
//!
//! \return None.
//!
//*****************************************************************************
extern void SDFM_configZeroCrossComparator(uint32_t base, uint16_t config1, uint16_t config2);

//*****************************************************************************
//
//! Configure SDFM data filter FIFO
//!
//! \param base is the base address of the SDFM module
//! \param config1 is the filter number, filter type and over sampling ratio
//!                configuration.
//! \param config2 is filter switch, data representation and data shift values
//!                and FIFO level configuration.
//!
//! This function enables and configures the data filter FIFO based on
//! configurations config1 and config2.
//!
//! The config1 parameter is the logical OR of the filter number, filter type
//! and oversampling ratio.
//! The bit definitions for config1 are as follow:
//!   - config1.[3:0]  filter number
//!   - config1.[7:4]  filter type
//!   - config1.[15:8] Over sampling Ratio
//! Valid values for filter number and filter type are defined in
//! SDFM_FilterNumber and SDFM_FilterType enumerations respectively.
//! SDFM_SET_OSR(X) macro can be used to set the value of the oversampling
//! ratio , which ranges [1,256] inclusive , in the appropriate bit location
//! for config1. For example the value
//! (SDFM_FILTER_2 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(64))
//! will select Filter 2 , SINC 3 type with an oversampling ratio of 64.
//!
//! The config2 parameter is the logical OR of data representation, filter
//! switch, data shift value, and FIFO level
//! The bit definitions for config2 are as follow:
//!   - config2.[0]  Data representation
//!   - config2.[1]  filter switch.
//!   - config2.[6:2]  shift values.
//!   - config2.[15:7] FIFO level
//! Valid values for data representation are given in SDFM_OutputDataFormat
//! enumeration. SDFM_FILTER_DISABLE or SDFM_FILTER_ENABLE will define the
//! filter switch values.SDFM_SHIFT_VALUE(X) macro can be used to set the value
//! of the data shift value,which ranges [0,31] inclusive, in the appropriate
//! bit location for config2.
//! The value of FIFO level ranges [1,16] inclusive. The macro
//! SDFM_SET_FIFO_LEVEL(X) can be used to set the value of the FIFO level.
//!
//! \return None.
//!
//*****************************************************************************
extern void SDFM_configDataFilterFIFO(uint32_t base, uint16_t config1, uint16_t config2);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
