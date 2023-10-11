/**
 **************************************************************************
 * @file     qx_gpio.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_GPIO_H
#define QX_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"
#include "qx_xint.h"
#include "hw_gpio.h"

struct GPA_CTRL_BITS
{                      // bits description
    vu32 QUALPRD0 : 8; // 7:0 Qualification sampling period for GPIO0 to GPIO7
    vu32 QUALPRD1 : 8; // 15:8 Qualification sampling period for GPIO8 to GPIO15
    vu32 QUALPRD2 : 8; // 23:16 Qualification sampling period for GPIO16 to GPIO23
    vu32 QUALPRD3 : 8; // 31:24 Qualification sampling period for GPIO24 to GPIO31
};

union GPA_CTRL_REG
{
    vu32 all;
    struct GPA_CTRL_BITS bit;
};

struct GPA_AMSEL_BITS
{                     // bits description
    vu32 rsvd1  : 22; // 21:0 Reserved
    vu32 GPIO22 : 1;  // 22 Analog Mode select for this pin
    vu32 GPIO23 : 1;  // 23 Analog Mode select for this pin
};

union GPA_AMSEL_REG
{
    vu32 all;
    struct GPA_AMSEL_BITS bit;
};

struct GPA_16_L_BITS
{                    // bits description
    vu32 GPIO0  : 2; // 1:0 Select input qualification type for GPIO0
    vu32 GPIO1  : 2; // 3:2 Select input qualification type for GPIO1
    vu32 GPIO2  : 2; // 5:4 Select input qualification type for GPIO2
    vu32 GPIO3  : 2; // 7:6 Select input qualification type for GPIO3
    vu32 GPIO4  : 2; // 9:8 Select input qualification type for GPIO4
    vu32 GPIO5  : 2; // 11:10 Select input qualification type for GPIO5
    vu32 GPIO6  : 2; // 13:12 Select input qualification type for GPIO6
    vu32 GPIO7  : 2; // 15:14 Select input qualification type for GPIO7
    vu32 GPIO8  : 2; // 17:16 Select input qualification type for GPIO8
    vu32 GPIO9  : 2; // 19:18 Select input qualification type for GPIO9
    vu32 GPIO10 : 2; // 21:20 Select input qualification type for GPIO10
    vu32 GPIO11 : 2; // 23:22 Select input qualification type for GPIO11
    vu32 GPIO12 : 2; // 25:24 Select input qualification type for GPIO12
    vu32 GPIO13 : 2; // 27:26 Select input qualification type for GPIO13
    vu32 GPIO14 : 2; // 29:28 Select input qualification type for GPIO14
    vu32 GPIO15 : 2; // 31:30 Select input qualification type for GPIO15
};

union GPA_16_L_REG
{
    vu32 all;
    struct GPA_16_L_BITS bit;
};

struct GPA_16_H_BITS
{                    // bits description
    vu32 GPIO16 : 2; // 1:0 Select input qualification type for GPIO16
    vu32 GPIO17 : 2; // 3:2 Select input qualification type for GPIO17
    vu32 GPIO18 : 2; // 5:4 Select input qualification type for GPIO18
    vu32 GPIO19 : 2; // 7:6 Select input qualification type for GPIO19
    vu32 GPIO20 : 2; // 9:8 Select input qualification type for GPIO20
    vu32 GPIO21 : 2; // 11:10 Select input qualification type for GPIO21
    vu32 GPIO22 : 2; // 13:12 Select input qualification type for GPIO22
    vu32 GPIO23 : 2; // 15:14 Select input qualification type for GPIO23
    vu32 GPIO24 : 2; // 17:16 Select input qualification type for GPIO24
    vu32 GPIO25 : 2; // 19:18 Select input qualification type for GPIO25
    vu32 GPIO26 : 2; // 21:20 Select input qualification type for GPIO26
    vu32 GPIO27 : 2; // 23:22 Select input qualification type for GPIO27
    vu32 GPIO28 : 2; // 25:24 Select input qualification type for GPIO28
    vu32 GPIO29 : 2; // 27:26 Select input qualification type for GPIO29
    vu32 GPIO30 : 2; // 29:28 Select input qualification type for GPIO30
    vu32 GPIO31 : 2; // 31:30 Select input qualification type for GPIO31
};

union GPA_16_H_REG
{
    vu32 all;
    struct GPA_16_H_BITS bit;
};

struct GPA_32_BITS
{                    // bits description
    vu32 GPIO0  : 1; // 0 Defines direction for this pin in GPIO mode
    vu32 GPIO1  : 1; // 1 Defines direction for this pin in GPIO mode
    vu32 GPIO2  : 1; // 2 Defines direction for this pin in GPIO mode
    vu32 GPIO3  : 1; // 3 Defines direction for this pin in GPIO mode
    vu32 GPIO4  : 1; // 4 Defines direction for this pin in GPIO mode
    vu32 GPIO5  : 1; // 5 Defines direction for this pin in GPIO mode
    vu32 GPIO6  : 1; // 6 Defines direction for this pin in GPIO mode
    vu32 GPIO7  : 1; // 7 Defines direction for this pin in GPIO mode
    vu32 GPIO8  : 1; // 8 Defines direction for this pin in GPIO mode
    vu32 GPIO9  : 1; // 9 Defines direction for this pin in GPIO mode
    vu32 GPIO10 : 1; // 10 Defines direction for this pin in GPIO mode
    vu32 GPIO11 : 1; // 11 Defines direction for this pin in GPIO mode
    vu32 GPIO12 : 1; // 12 Defines direction for this pin in GPIO mode
    vu32 GPIO13 : 1; // 13 Defines direction for this pin in GPIO mode
    vu32 GPIO14 : 1; // 14 Defines direction for this pin in GPIO mode
    vu32 GPIO15 : 1; // 15 Defines direction for this pin in GPIO mode
    vu32 GPIO16 : 1; // 16 Defines direction for this pin in GPIO mode
    vu32 GPIO17 : 1; // 17 Defines direction for this pin in GPIO mode
    vu32 GPIO18 : 1; // 18 Defines direction for this pin in GPIO mode
    vu32 GPIO19 : 1; // 19 Defines direction for this pin in GPIO mode
    vu32 GPIO20 : 1; // 20 Defines direction for this pin in GPIO mode
    vu32 GPIO21 : 1; // 21 Defines direction for this pin in GPIO mode
    vu32 GPIO22 : 1; // 22 Defines direction for this pin in GPIO mode
    vu32 GPIO23 : 1; // 23 Defines direction for this pin in GPIO mode
    vu32 GPIO24 : 1; // 24 Defines direction for this pin in GPIO mode
    vu32 GPIO25 : 1; // 25 Defines direction for this pin in GPIO mode
    vu32 GPIO26 : 1; // 26 Defines direction for this pin in GPIO mode
    vu32 GPIO27 : 1; // 27 Defines direction for this pin in GPIO mode
    vu32 GPIO28 : 1; // 28 Defines direction for this pin in GPIO mode
    vu32 GPIO29 : 1; // 29 Defines direction for this pin in GPIO mode
    vu32 GPIO30 : 1; // 30 Defines direction for this pin in GPIO mode
    vu32 GPIO31 : 1; // 31 Defines direction for this pin in GPIO mode
};

union GPA_32_REG
{
    vu32 all;
    struct GPA_32_BITS bit;
};

struct GPB_CTRL_BITS
{                      // bits description
    vu32 QUALPRD0 : 8; // 7:0 Qualification sampling period for GPIO32 to GPIO39
    vu32 QUALPRD1 : 8; // 15:8 Qualification sampling period for GPIO40 to GPIO47
    vu32 QUALPRD2 : 8; // 23:16 Qualification sampling period for GPIO48 to GPIO55
    vu32 QUALPRD3 : 8; // 31:24 Qualification sampling period for GPIO56 to GPIO63
};

union GPB_CTRL_REG
{
    vu32 all;
    struct GPB_CTRL_BITS bit;
};

struct GPB_16_L_BITS
{                    // bits description
    vu32 GPIO32 : 2; // 1:0 Select input qualification type for GPIO32
    vu32 GPIO33 : 2; // 3:2 Select input qualification type for GPIO33
    vu32 GPIO34 : 2; // 5:4 Select input qualification type for GPIO34
    vu32 GPIO35 : 2; // 7:6 Select input qualification type for GPIO35
    vu32 rsvd1  : 2; // Reserved
    vu32 GPIO37 : 2; // 11:10 Select input qualification type for GPIO37
    vu32 rsvd2  : 2; // Reserved
    vu32 GPIO39 : 2; // 15:14 Select input qualification type for GPIO39
    vu32 GPIO40 : 2; // 17:16 Select input qualification type for GPIO40
    vu32 GPIO41 : 2; // 19:18 Select input qualification type for GPIO41
    vu32 GPIO42 : 2; // 21:20 Select input qualification type for GPIO42
    vu32 GPIO43 : 2; // 23:22 Select input qualification type for GPIO43
    vu32 GPIO44 : 2; // 25:24 Select input qualification type for GPIO44
    vu32 GPIO45 : 2; // 27:26 Select input qualification type for GPIO45
    vu32 GPIO46 : 2; // 29:28 Select input qualification type for GPIO46
    vu32 GPIO47 : 2; // 31:30 Select input qualification type for GPIO47
};

union GPB_16_L_REG
{
    vu32 all;
    struct GPB_16_L_BITS bit;
};

struct GPB_16_H_BITS
{                    // bits description
    vu32 GPIO48 : 2; // 1:0 Select input qualification type for GPIO48
    vu32 GPIO49 : 2; // 3:2 Select input qualification type for GPIO49
    vu32 GPIO50 : 2; // 5:4 Select input qualification type for GPIO50
    vu32 GPIO51 : 2; // 7:6 Select input qualification type for GPIO51
    vu32 GPIO52 : 2; // 9:8 Select input qualification type for GPIO52
    vu32 GPIO53 : 2; // 11:10 Select input qualification type for GPIO53
    vu32 GPIO54 : 2; // 13:12 Select input qualification type for GPIO54
    vu32 GPIO55 : 2; // 15:14 Select input qualification type for GPIO55
    vu32 GPIO56 : 2; // 17:16 Select input qualification type for GPIO56
    vu32 GPIO57 : 2; // 19:18 Select input qualification type for GPIO57
    vu32 GPIO58 : 2; // 21:20 Select input qualification type for GPIO58
    vu32 GPIO59 : 2; // 23:22 Select input qualification type for GPIO59
    vu32 rsvd1  : 2; // Reserved
    vu32 rsvd2  : 2; // Reserved
    vu32 rsvd3  : 2; // Reserved
    vu32 rsvd4  : 2; // Reserved
};

union GPB_16_H_REG
{
    vu32 all;
    struct GPB_16_H_BITS bit;
};

struct GPB_32_BITS
{                    // bits description
    vu32 GPIO32 : 1; // 0 Defines direction for this pin in GPIO mode
    vu32 GPIO33 : 1; // 1 Defines direction for this pin in GPIO mode
    vu32 GPIO34 : 1; // 2 Defines direction for this pin in GPIO mode
    vu32 GPIO35 : 1; // 3 Defines direction for this pin in GPIO mode
    vu32 rsvd1  : 1; // 4 Defines direction for this pin in GPIO mode
    vu32 GPIO37 : 1; // 5 Defines direction for this pin in GPIO mode
    vu32 rsvd2  : 1; // 6 Defines direction for this pin in GPIO mode
    vu32 GPIO39 : 1; // 7 Defines direction for this pin in GPIO mode
    vu32 GPIO40 : 1; // 8 Defines direction for this pin in GPIO mode
    vu32 GPIO41 : 1; // 9 Defines direction for this pin in GPIO mode
    vu32 GPIO42 : 1; // 10 Defines direction for this pin in GPIO mode
    vu32 GPIO43 : 1; // 11 Defines direction for this pin in GPIO mode
    vu32 GPIO44 : 1; // 12 Defines direction for this pin in GPIO mode
    vu32 GPIO45 : 1; // 13 Defines direction for this pin in GPIO mode
    vu32 GPIO46 : 1; // 14 Defines direction for this pin in GPIO mode
    vu32 GPIO47 : 1; // 15 Defines direction for this pin in GPIO mode
    vu32 GPIO48 : 1; // 16 Defines direction for this pin in GPIO mode
    vu32 GPIO49 : 1; // 17 Defines direction for this pin in GPIO mode
    vu32 GPIO50 : 1; // 18 Defines direction for this pin in GPIO mode
    vu32 GPIO51 : 1; // 19 Defines direction for this pin in GPIO mode
    vu32 GPIO52 : 1; // 20 Defines direction for this pin in GPIO mode
    vu32 GPIO53 : 1; // 21 Defines direction for this pin in GPIO mode
    vu32 GPIO54 : 1; // 22 Defines direction for this pin in GPIO mode
    vu32 GPIO55 : 1; // 23 Defines direction for this pin in GPIO mode
    vu32 GPIO56 : 1; // 24 Defines direction for this pin in GPIO mode
    vu32 GPIO57 : 1; // 25 Defines direction for this pin in GPIO mode
    vu32 GPIO58 : 1; // 26 Defines direction for this pin in GPIO mode
    vu32 GPIO59 : 1; // 27 Defines direction for this pin in GPIO mode
    vu32 rsvd3  : 1; // 28 Defines direction for this pin in GPIO mode
    vu32 rsvd4  : 1; // 29 Defines direction for this pin in GPIO mode
    vu32 rsvd5  : 1; // 30 Defines direction for this pin in GPIO mode
    vu32 rsvd6  : 1; // 31 Defines direction for this pin in GPIO mode
};

union GPB_32_REG
{
    vu32 all;
    struct GPB_32_BITS bit;
};

struct GPH_CTRL_BITS
{                      // bits description
    vu32 QUALPRD0 : 8; // 7:0 Qualification sampling period for GPIO224 to GPIO231
    vu32 QUALPRD1 : 8; // 15:8 Qualification sampling period for GPIO232 to GPIO239
    vu32 QUALPRD2 : 8; // 23:16 Qualification sampling period for GPIO240 to GPIO247
    vu32 rsvd1    : 8; // 31:24 Reserved
};

union GPH_CTRL_REG
{
    vu32 all;
    struct GPH_CTRL_BITS bit;
};

struct GPH_QSEL1_BITS
{                     // bits description
    vu32 GPIO224 : 2; // 1:0 Select input qualification type for this GPIO Pin
    vu32 GPIO225 : 2; // 3:2 Select input qualification type for this GPIO Pin
    vu32 GPIO226 : 2; // 5:4 Select input qualification type for this GPIO Pin
    vu32 GPIO227 : 2; // 7:6 Select input qualification type for this GPIO Pin
    vu32 GPIO228 : 2; // 9:8 Select input qualification type for this GPIO Pin
    vu32 GPIO229 : 2; // 11:10 Select input qualification type for this GPIO Pin
    vu32 GPIO230 : 2; // 13:12 Select input qualification type for this GPIO Pin
    vu32 GPIO231 : 2; // 15:14 Select input qualification type for this GPIO Pin
    vu32 GPIO232 : 2; // 17:16 Select input qualification type for this GPIO Pin
    vu32 GPIO233 : 2; // 19:18 Select input qualification type for this GPIO Pin
    vu32 GPIO234 : 2; // 21:20 Select input qualification type for this GPIO Pin
    vu32 GPIO235 : 2; // 23:22 Select input qualification type for this GPIO Pin
    vu32 GPIO236 : 2; // 25:24 Select input qualification type for this GPIO Pin
    vu32 GPIO237 : 2; // 27:26 Select input qualification type for this GPIO Pin
    vu32 GPIO238 : 2; // 29:28 Select input qualification type for this GPIO Pin
    vu32 GPIO239 : 2; // 31:30 Select input qualification type for this GPIO Pin
};

union GPH_QSEL1_REG
{
    vu32 all;
    struct GPH_QSEL1_BITS bit;
};

struct GPH_QSEL2_BITS
{                     // bits description
    vu32 GPIO240 : 2; // 1:0 Select input qualification type for this GPIO Pin
    vu32 GPIO241 : 2; // 3:2 Select input qualification type for this GPIO Pin
    vu32 GPIO242 : 2; // 5:4 Select input qualification type for this GPIO Pin
    vu32 GPIO243 : 2; // 7:6 Select input qualification type for this GPIO Pin
    vu32 GPIO244 : 2; // 9:8 Select input qualification type for this GPIO Pin
    vu32 GPIO245 : 2; // 11:10 Select input qualification type for this GPIO Pin
    vu32 GPIO246 : 2; // 13:12 Select input qualification type for this GPIO Pin
    vu32 GPIO247 : 2; // 15:14 Select input qualification type for this GPIO Pin
    vu32 rsvd1   : 2; // 17:16 Reserved
    vu32 rsvd2   : 2; // 19:18 Reserved
    vu32 rsvd3   : 2; // 21:20 Reserved
    vu32 rsvd4   : 2; // 23:22 Reserved
    vu32 rsvd5   : 2; // 25:24 Reserved
    vu32 rsvd6   : 2; // 27:26 Reserved
    vu32 rsvd7   : 2; // 29:28 Reserved
    vu32 rsvd8   : 2; // 31:30 Reserved
};

union GPH_QSEL2_REG
{
    vu32 all;
    struct GPH_QSEL2_BITS bit;
};

struct GPH_32_BITS
{ // bits description
    vu32 GPIO224 : 1;
    vu32 GPIO225 : 1;
    vu32 GPIO226 : 1;
    vu32 GPIO227 : 1;
    vu32 GPIO228 : 1;
    vu32 GPIO229 : 1;
    vu32 GPIO230 : 1;
    vu32 GPIO231 : 1;
    vu32 GPIO232 : 1;
    vu32 GPIO233 : 1;
    vu32 GPIO234 : 1;
    vu32 GPIO235 : 1;
    vu32 GPIO236 : 1;
    vu32 GPIO237 : 1;
    vu32 GPIO238 : 1;
    vu32 GPIO239 : 1;
    vu32 GPIO240 : 1;
    vu32 GPIO241 : 1;
    vu32 GPIO242 : 1;
    vu32 GPIO243 : 1;
    vu32 GPIO244 : 1;
    vu32 GPIO245 : 1;
    vu32 GPIO246 : 1;
    vu32 GPIO247 : 1;
    vu32 rsvd1   : 1;
    vu32 rsvd2   : 1;
    vu32 rsvd3   : 1;
    vu32 rsvd4   : 1;
    vu32 rsvd5   : 1;
    vu32 rsvd6   : 1;
    vu32 rsvd7   : 1;
    vu32 rsvd8   : 1;
};

union GPH_32_REG
{
    vu32 all;
    struct GPH_32_BITS bit;
};

struct GPIO_CTRL_REGS
{
    union GPA_CTRL_REG GPACTRL;   // GPIO A Qualification Sampling Period (GPIO0 to GPIO31) offset:0x00
    union GPA_16_L_REG GPAQSEL1;  // GPIO A Qualification Type (GPIO0 to GPIO15) offset:0x04
    union GPA_16_H_REG GPAQSEL2;  // GPIO A Qualification Type (GPIO16 to GPIO31) offset:0x08
    union GPA_16_L_REG GPAMUX1;   // GPIO A Peripheral Mux (GPIO0 to GPIO15) offset:0x0C
    union GPA_16_H_REG GPAMUX2;   // GPIO A Peripheral Mux (GPIO16 to GPIO31) offset:0x10
    union GPA_32_REG GPADIR;      // GPIO A Direction (GPIO0 to GPIO31) offset:0x14
    union GPA_32_REG GPAPUD;      // GPIO A Pull-Up Disable (GPIO0 to GPIO31) offset:0x18
    union GPA_32_REG GPAINV;      // GPIO A Input Inversion (GPIO0 to GPIO31) offset:0x1C
    union GPA_32_REG GPAODR;      // GPIO A Open Drain Output Mode (GPIO0 to GPIO31) offset:0x20
    union GPA_AMSEL_REG GPAAMSEL; // GPIO A Analog Mode Select (GPIO0 to GPIO31) offset:0x24
    union GPA_16_L_REG GPAGMUX1;  // GPIO A Peripheral Group Mux (GPIO0 to GPIO15) offset:0x28
    union GPA_16_H_REG GPAGMUX2;  // GPIO A Peripheral Group Mux (GPIO16 to GPIO31) offset:0x2C
    union GPA_32_REG GPALOCK;     // GPIO A Lock Register (GPIO0 to GPIO31) offset:0x30
    union GPA_32_REG GPACR;       // GPIO A Lock Register (GPIO0 to GPIO31) offset:0x34
    vu32 rsvd0[6];                // reserved offset: 0x38 ~ 0x4c
    union GPB_CTRL_REG GPBCTRL;   // GPIO B Qualification Sampling Period (GPIO32 to GPIO63) offset:0x50
    union GPB_16_L_REG GPBQSEL1;  // GPIO B Qualification Type (GPIO32 to GPIO47) offset:0x54
    union GPB_16_H_REG GPBQSEL2;  // GPIO B Qualification Type (GPIO48 to GPIO63) offset:0x58
    union GPB_16_L_REG GPBMUX1;   // GPIO B Peripheral Mux (GPIO32 to GPIO47) offset:0x5C
    union GPB_16_H_REG GPBMUX2;   // GPIO B Peripheral Mux (GPIO48 to GPIO63) offset:0x60
    union GPB_32_REG GPBDIR;      // GPIO B Direction (GPIO32 to GPIO63) offset:0x64
    union GPB_32_REG GPBPUD;      // GPIO B Pull-Up Disable (GPIO32 to GPIO63) offset:0x68
    vu32 rsvd1;                   // reserved offset: 0x6C
    union GPB_32_REG GPBINV;      // GPIO B Input Inversion (GPIO32 to GPIO63) offset:0x70
    union GPB_32_REG GPBODR;      // GPIO B Open Drain Output Mode (GPIO32 to GPIO63) offset:0x74
    union GPB_16_L_REG GPBGMUX1;  // GPIO B Peripheral Group Mux (GPIO32 to GPIO47) offset:0x78
    union GPB_16_H_REG GPBGMUX2;  // GPIO B Peripheral Group Mux (GPIO48 to GPIO63) offset:0x7C
    union GPB_32_REG GPBLOCK;     // GPIO B Lock Register (GPIO32 to GPIO63) offset:0x80
    union GPB_32_REG GPBCR;       // GPIO B Lock Register (GPIO32 to GPIO63) offset:0x84
    vu32 vsvd2[6];                // reserved offset:0x88~0x9C
    union GPH_CTRL_REG GPHCTRL;   // GPIO H Qualification Sampling Period (GPIO224 to GPIO255) offset:0xA0
    union GPH_QSEL1_REG GPHQSEL1; // GPIO H Qualification Type (GPIO224 to GPIO239) offset:0xA4
    union GPH_QSEL2_REG GPHQSEL2; // GPIO H Qualification Type (GPIO240 to GPIO255) offset:0xA8
    union GPH_32_REG GPHPUD;      // GPIO H Pull-Up Disable (GPIO224 to GPIO255) offset:0xAC
    union GPH_32_REG GPHINV;      // GPIO H Input Inversion (GPIO224 to GPIO255) offset:0xB0
    union GPH_32_REG GPHAMSEL;    // GPIO H Analog Mode Select (GPIO224 to GPIO255) offset:0xB4
    union GPH_32_REG GPHLOCK;     // GPIO H Lock Register (GPIO224 to GPIO255) offset:0xB8
    union GPH_32_REG GPHCR;       // GPIO H Lock Commit Register (GPIO224 to GPIO255) offset:0xBC
};

struct GPIO_DATA_REGS
{
    union GPA_32_REG GPADAT;    // GPIO A Data Register (GPIO0 to GPIO31)
    union GPA_32_REG GPASET;    // GPIO A Output Set (GPIO0 to GPIO31)
    union GPA_32_REG GPACLEAR;  // GPIO A Output Clear (GPIO0 to GPIO31)
    union GPA_32_REG GPATOGGLE; // GPIO A Output Toggle (GPIO0 to GPIO31)
    union GPB_32_REG GPBDAT;    // GPIO B Data Register (GPIO32 to GPIO63)
    union GPB_32_REG GPBSET;    // GPIO B Output Set (GPIO32 to GPIO63)
    union GPB_32_REG GPBCLEAR;  // GPIO B Output Clear (GPIO32 to GPIO63)
    union GPB_32_REG GPBTOGGLE; // GPIO B Output Toggle (GPIO32 to GPIO63)
};

#define GpioCtrlRegs ((volatile struct GPIO_CTRL_REGS *)GPIOCTRL_BASE)
#define GpioDataRegs ((volatile struct GPIO_DATA_REGS *)GPIODATA_BASE)

//*****************************************************************************
// Values that can be passed to GPIO_xxxConfig() as the pin parameter
//*****************************************************************************
typedef enum
{
    GPIO_PIN_0  = 0,
    GPIO_PIN_1  = 1,
    GPIO_PIN_2  = 2,
    GPIO_PIN_3  = 3,
    GPIO_PIN_4  = 4,
    GPIO_PIN_5  = 5,
    GPIO_PIN_6  = 6,
    GPIO_PIN_7  = 7,
    GPIO_PIN_8  = 8,
    GPIO_PIN_9  = 9,
    GPIO_PIN_10 = 10,
    GPIO_PIN_11 = 11,
    GPIO_PIN_12 = 12,
    GPIO_PIN_13 = 13,
    GPIO_PIN_14 = 14,
    GPIO_PIN_15 = 15,
    GPIO_PIN_16 = 16,
    GPIO_PIN_17 = 17,
    GPIO_PIN_18 = 18,
    GPIO_PIN_19 = 19,
    GPIO_PIN_20 = 20,
    GPIO_PIN_21 = 21,
    GPIO_PIN_22 = 22,
    GPIO_PIN_23 = 23,
    GPIO_PIN_24 = 24,
    GPIO_PIN_25 = 25,
    GPIO_PIN_26 = 26,
    GPIO_PIN_27 = 27,
    GPIO_PIN_28 = 28,
    GPIO_PIN_29 = 29,
    GPIO_PIN_30 = 30,
    GPIO_PIN_31 = 31,
    GPIO_PIN_32 = 32,
    GPIO_PIN_33 = 33,
    GPIO_PIN_34 = 34,
    GPIO_PIN_35 = 35,
    // GPIO_PIN_36 Reserved
    GPIO_PIN_37 = 37,
    // GPIO_PIN_38 Reserved
    GPIO_PIN_39 = 39,
    GPIO_PIN_40 = 40,
    GPIO_PIN_41 = 41,
    GPIO_PIN_42 = 42,
    GPIO_PIN_43 = 43,
    GPIO_PIN_44 = 44,
    GPIO_PIN_45 = 45,
    GPIO_PIN_46 = 46,
    GPIO_PIN_47 = 47,
    GPIO_PIN_48 = 48,
    GPIO_PIN_49 = 49,
    GPIO_PIN_50 = 50,
    GPIO_PIN_51 = 51,
    GPIO_PIN_52 = 52,
    GPIO_PIN_53 = 53,
    GPIO_PIN_54 = 54,
    GPIO_PIN_55 = 55,
    GPIO_PIN_56 = 56,
    GPIO_PIN_57 = 57,
    GPIO_PIN_58 = 58,
    GPIO_PIN_59 = 59,
    // GPIO_PIN_60~63 Reserved
} GPIO_PinNum;

//*****************************************************************************
// Values that can be passed to GPIO_setPinConfig() as the pinConfig parameter
//*****************************************************************************
//*****************************************************************************
// 0x00000003 = MUX register value
// 0x0000000C = GMUX register value
// 0x0000FF00 = Shift amount within mux registers
// 0xFFFF0000 = Offset of MUX register
//*****************************************************************************
typedef enum
{
    GPIO_0_GPIO0          = 0x000C0000U,
    GPIO_0_EPWM1_A        = 0x000C0001U,
    GPIO_0_I2CA_SDA       = 0x000C0006U,
    GPIO_1_GPIO1          = 0x000C0200U,
    GPIO_1_EPWM1_B        = 0x000C0201U,
    GPIO_1_I2CA_SCL       = 0x000C0206U,
    GPIO_2_GPIO2          = 0x000C0400U,
    GPIO_2_EPWM2_A        = 0x000C0401U,
    GPIO_2_OUTPUTXBAR1    = 0x000C0405U,
    GPIO_2_PMBUSA_SDA     = 0x000C0406U,
    GPIO_2_SCIA_TX        = 0x000C0409U,
    GPIO_2_FSIRXA_D1      = 0x000C040AU,
    GPIO_3_GPIO3          = 0x000C0600U,
    GPIO_3_EPWM2_B        = 0x000C0601U,
    GPIO_3_OUTPUTXBAR2    = 0x000C0602U,
    GPIO_3_OUTPUTXBAR2_2  = 0x000C0605U,
    GPIO_3_PMBUSA_SCL     = 0x000C0606U,
    GPIO_3_SPIA_CLK       = 0x000C0607U,
    GPIO_3_SCIA_RX        = 0x000C0609U,
    GPIO_3_FSIRXA_D0      = 0x000C060AU,
    GPIO_4_GPIO4          = 0x000C0800U,
    GPIO_4_EPWM3_A        = 0x000C0801U,
    GPIO_4_OUTPUTXBAR3    = 0x000C0805U,
    GPIO_4_CANA_TX        = 0x000C0806U,
    GPIO_4_FSIRXA_CLK     = 0x000C080AU,
    GPIO_5_GPIO5          = 0x000C0A00U,
    GPIO_5_EPWM3_B        = 0x000C0A01U,
    GPIO_5_OUTPUTXBAR3    = 0x000C0A03U,
    GPIO_5_CANA_RX        = 0x000C0A06U,
    GPIO_5_SPIA_STE       = 0x000C0A07U,
    GPIO_5_FSITXA_D1      = 0x000C0A09U,
    GPIO_6_GPIO6          = 0x000C0C00U,
    GPIO_6_EPWM4_A        = 0x000C0C01U,
    GPIO_6_OUTPUTXBAR4    = 0x000C0C02U,
    GPIO_6_SYNCOUT        = 0x000C0C03U,
    GPIO_6_EQEP1_A        = 0x000C0C05U,
    GPIO_6_CANB_TX        = 0x000C0C06U,
    GPIO_6_SPIB_SOMI      = 0x000C0C07U,
    GPIO_6_FSITXA_D0      = 0x000C0C09U,
    GPIO_7_GPIO7          = 0x000C0E00U,
    GPIO_7_EPWM4_B        = 0x000C0E01U,
    GPIO_7_OUTPUTXBAR5    = 0x000C0E03U,
    GPIO_7_EQEP1_B        = 0x000C0E05U,
    GPIO_7_CANB_RX        = 0x000C0E06U,
    GPIO_7_SPIB_SIMO      = 0x000C0E07U,
    GPIO_7_FSITXA_CLK     = 0x000C0E09U,
    GPIO_8_GPIO8          = 0x000C1000U,
    GPIO_8_EPWM5_A        = 0x000C1001U,
    GPIO_8_CANB_TX        = 0x000C1002U,
    GPIO_8_ADCSOCAO       = 0x000C1003U,
    GPIO_8_EQEP1_STROBE   = 0x000C1005U,
    GPIO_8_SCIA_TX        = 0x000C1006U,
    GPIO_8_SPIA_SIMO      = 0x000C1007U,
    GPIO_8_I2CA_SCL       = 0x000C1009U,
    GPIO_8_FSITXA_D1      = 0x000C100AU,
    GPIO_9_GPIO9          = 0x000C1200U,
    GPIO_9_EPWM5_B        = 0x000C1201U,
    GPIO_9_SCIB_TX        = 0x000C1202U,
    GPIO_9_OUTPUTXBAR6    = 0x000C1203U,
    GPIO_9_EQEP1_INDEX    = 0x000C1205U,
    GPIO_9_SCIA_RX        = 0x000C1206U,
    GPIO_9_SPIA_CLK       = 0x000C1207U,
    GPIO_9_FSITXA_D0      = 0x000C120AU,
    GPIO_10_GPIO10        = 0x000C1400U,
    GPIO_10_EPWM6_A       = 0x000C1401U,
    GPIO_10_CANB_RX       = 0x000C1402U,
    GPIO_10_ADCSOCBO      = 0x000C1403U,
    GPIO_10_EQEP1_A       = 0x000C1405U,
    GPIO_10_SCIB_TX       = 0x000C1406U,
    GPIO_10_SPIA_SOMI     = 0x000C1407U,
    GPIO_10_I2CA_SDA      = 0x000C1409U,
    GPIO_10_FSITXA_CLK    = 0x000C140AU,
    GPIO_11_GPIO11        = 0x000C1600U,
    GPIO_11_EPWM6_B       = 0x000C1601U,
    GPIO_11_SCIB_RX       = 0x000C1602U,
    GPIO_11_OUTPUTXBAR7   = 0x000C1603U,
    GPIO_11_EQEP1_B       = 0x000C1605U,
    GPIO_11_SCIB_RX_2     = 0x000C1606U,
    GPIO_11_SPIA_STE      = 0x000C1607U,
    GPIO_11_FSIRXA_D1     = 0x000C1609U,
    GPIO_12_GPIO12        = 0x000C1800U,
    GPIO_12_EPWM7_A       = 0x000C1801U,
    GPIO_12_CANB_TX       = 0x000C1802U,
    GPIO_12_EQEP1_STROBE  = 0x000C1805U,
    GPIO_12_SCIB_TX       = 0x000C1806U,
    GPIO_12_PMBUSA_CTL    = 0x000C1807U,
    GPIO_12_FSIRXA_D0     = 0x000C1809U,
    GPIO_13_GPIO13        = 0x000C1A00U,
    GPIO_13_EPWM7_B       = 0x000C1A01U,
    GPIO_13_CANB_RX       = 0x000C1A02U,
    GPIO_13_EQEP1_INDEX   = 0x000C1A05U,
    GPIO_13_SCIB_RX       = 0x000C1A06U,
    GPIO_13_PMBUSA_ALERT  = 0x000C1A07U,
    GPIO_13_FSIRXA_CLK    = 0x000C1A09U,
    GPIO_14_GPIO14        = 0x000C1C00U,
    GPIO_14_EPWM8_A       = 0x000C1C01U,
    GPIO_14_SCIB_TX       = 0x000C1C02U,
    GPIO_14_OUTPUTXBAR3   = 0x000C1C06U,
    GPIO_14_PMBUSA_SDA    = 0x000C1C07U,
    GPIO_14_SPIB_CLK      = 0x000C1C09U,
    GPIO_14_EQEP2_A       = 0x000C1C0AU,
    GPIO_15_GPIO15        = 0x000C1E00U,
    GPIO_15_EPWM8_B       = 0x000C1E01U,
    GPIO_15_SCIB_RX       = 0x000C1E02U,
    GPIO_15_OUTPUTXBAR4   = 0x000C1E06U,
    GPIO_15_PMBUSA_SCL    = 0x000C1E07U,
    GPIO_15_SPIB_STE      = 0x000C1E09U,
    GPIO_15_EQEP2_B       = 0x000C1E0AU,
    GPIO_16_GPIO16        = 0x00100000U,
    GPIO_16_SPIA_SIMO     = 0x00100001U,
    GPIO_16_CANB_TX       = 0x00100002U,
    GPIO_16_OUTPUTXBAR7   = 0x00100003U,
    GPIO_16_EPWM5_A       = 0x00100005U,
    GPIO_16_SCIA_TX       = 0x00100006U,
    GPIO_16_SD1_D1        = 0x00100007U,
    GPIO_16_EQEP1_STROBE  = 0x00100009U,
    GPIO_16_PMBUSA_SCL    = 0x0010000AU,
    GPIO_16_XCLKOUT       = 0x0010000BU,
    GPIO_17_GPIO17        = 0x00100200U,
    GPIO_17_SPIA_SOMI     = 0x00100201U,
    GPIO_17_CANB_RX       = 0x00100202U,
    GPIO_17_OUTPUTXBAR8   = 0x00100203U,
    GPIO_17_EPWM5_B       = 0x00100205U,
    GPIO_17_SCIA_RX       = 0x00100206U,
    GPIO_17_SD1_C1        = 0x00100207U,
    GPIO_17_EQEP1_INDEX   = 0x00100209U,
    GPIO_17_PMBUSA_SDA    = 0x0010020AU,
    GPIO_20_GPIO20        = 0x00100800U,
    GPIO_21_GPIO21        = 0x00100A00U,
    GPIO_22_GPIO22_VFBSW  = 0x00100C00U,
    GPIO_22_EQEP1_STROBE  = 0x00100C01U,
    GPIO_22_SCIB_TX       = 0x00100C03U,
    GPIO_22_SPIB_CLK      = 0x00100C06U,
    GPIO_22_SD1_D4        = 0x00100C07U,
    GPIO_22_LINA_TX       = 0x00100C09U,
    GPIO_23_GPIO23_VSW    = 0x00100E00U,
    GPIO_23_GPIO23        = 0x00100E04U,
    GPIO_24_GPIO24        = 0x00101000U,
    GPIO_24_OUTPUTXBAR1   = 0x00101001U,
    GPIO_24_EQEP2_A       = 0x00101002U,
    GPIO_24_EPWM8_A       = 0x00101005U,
    GPIO_24_SPIB_SIMO     = 0x00101006U,
    GPIO_24_SD1_D1        = 0x00101007U,
    GPIO_24_PMBUSA_SCL    = 0x0010100AU,
    GPIO_24_SCIA_TX       = 0x0010100BU,
    GPIO_24_ERRORSTS      = 0x0010100DU,
    GPIO_25_GPIO25        = 0x00101200U,
    GPIO_25_OUTPUTXBAR2   = 0x00101201U,
    GPIO_25_EQEP2_B       = 0x00101202U,
    GPIO_25_SPIB_SOMI     = 0x00101206U,
    GPIO_25_SD1_C1        = 0x00101207U,
    GPIO_25_FSITXA_D1     = 0x00101209U,
    GPIO_25_PMBUSA_SDA    = 0x0010120AU,
    GPIO_25_SCIA_RX       = 0x0010120BU,
    GPIO_26_GPIO26        = 0x00101400U,
    GPIO_26_OUTPUTXBAR3   = 0x00101401U,
    GPIO_26_EQEP2_INDEX   = 0x00101402U,
    GPIO_26_OUTPUTXBAR3_2 = 0x00101405U,
    GPIO_26_SPIB_CLK      = 0x00101406U,
    GPIO_26_SD1_D2        = 0x00101407U,
    GPIO_26_FSITXA_D0     = 0x00101409U,
    GPIO_26_PMBUSA_CTL    = 0x0010140AU,
    GPIO_26_I2CA_SDA      = 0x0010140BU,
    GPIO_27_GPIO27        = 0x00101600U,
    GPIO_27_OUTPUTXBAR4   = 0x00101601U,
    GPIO_27_EQEP2_STROBE  = 0x00101602U,
    GPIO_27_SPIB_STE      = 0x00101606U,
    GPIO_27_SD1_C2        = 0x00101607U,
    GPIO_27_FSITXA_CLK    = 0x00101609U,
    GPIO_27_PMBUSA_ALERT  = 0x0010160AU,
    GPIO_27_I2CA_SCL      = 0x0010160BU,
    GPIO_28_GPIO28        = 0x00101800U,
    GPIO_28_SCIA_RX       = 0x00101801U,
    GPIO_28_EPWM7_A       = 0x00101803U,
    GPIO_28_OUTPUTXBAR5   = 0x00101805U,
    GPIO_28_EQEP1_A       = 0x00101806U,
    GPIO_28_SD1_D3        = 0x00101807U,
    GPIO_28_EQEP2_STROBE  = 0x00101809U,
    GPIO_28_LINA_TX       = 0x0010180AU,
    GPIO_28_SPIB_CLK      = 0x0010180BU,
    GPIO_28_ERRORSTS      = 0x0010180DU,
    GPIO_29_GPIO29        = 0x00101A00U,
    GPIO_29_SCIA_TX       = 0x00101A01U,
    GPIO_29_EPWM7_B       = 0x00101A03U,
    GPIO_29_OUTPUTXBAR6   = 0x00101A05U,
    GPIO_29_EQEP1_B       = 0x00101A06U,
    GPIO_29_SD1_C3        = 0x00101A07U,
    GPIO_29_EQEP2_INDEX   = 0x00101A09U,
    GPIO_29_LINA_RX       = 0x00101A0AU,
    GPIO_29_SPIB_STE      = 0x00101A0BU,
    GPIO_29_ERRORSTS      = 0x00101A0DU,
    GPIO_30_GPIO30        = 0x00101C00U,
    GPIO_30_CANA_RX       = 0x00101C01U,
    GPIO_30_SPIB_SIMO     = 0x00101C03U,
    GPIO_30_OUTPUTXBAR7   = 0x00101C05U,
    GPIO_30_EQEP1_STROBE  = 0x00101C06U,
    GPIO_30_SD1_D4        = 0x00101C07U,
    GPIO_31_GPIO31        = 0x00101E00U,
    GPIO_31_CANA_TX       = 0x00101E01U,
    GPIO_31_SPIB_SOMI     = 0x00101E03U,
    GPIO_31_OUTPUTXBAR8   = 0x00101E05U,
    GPIO_31_EQEP1_INDEX   = 0x00101E06U,
    GPIO_31_SD1_C4        = 0x00101E07U,
    GPIO_31_FSIRXA_D1     = 0x00101E09U,
    GPIO_32_GPIO32        = 0x005C0000U,
    GPIO_32_I2CA_SDA      = 0x005C0001U,
    GPIO_32_SPIB_CLK      = 0x005C0003U,
    GPIO_32_EPWM8_B       = 0x005C0005U,
    GPIO_32_LINA_TX       = 0x005C0006U,
    GPIO_32_SD1_D3        = 0x005C0007U,
    GPIO_32_FSIRXA_D0     = 0x005C0009U,
    GPIO_32_CANA_TX       = 0x005C000AU,
    GPIO_33_GPIO33        = 0x005C0200U,
    GPIO_33_I2CA_SCL      = 0x005C0201U,
    GPIO_33_SPIB_STE      = 0x005C0203U,
    GPIO_33_OUTPUTXBAR4   = 0x005C0205U,
    GPIO_33_LINA_RX       = 0x005C0206U,
    GPIO_33_SD1_C3        = 0x005C0207U,
    GPIO_33_FSIRXA_CLK    = 0x005C0209U,
    GPIO_33_CANA_RX       = 0x005C020AU,
    GPIO_34_GPIO34        = 0x005C0400U,
    GPIO_34_OUTPUTXBAR1   = 0x005C0401U,
    GPIO_34_PMBUSA_SDA    = 0x005C0406U,
    GPIO_35_GPIO35        = 0x005C0600U,
    GPIO_35_SCIA_RX       = 0x005C0601U,
    GPIO_35_I2CA_SDA      = 0x005C0603U,
    GPIO_35_CANA_RX       = 0x005C0605U,
    GPIO_35_PMBUSA_SCL    = 0x005C0606U,
    GPIO_35_LINA_RX       = 0x005C0607U,
    GPIO_35_EQEP1_A       = 0x005C0609U,
    GPIO_35_PMBUSA_CTL    = 0x005C060AU,
    GPIO_35_TDI           = 0x005C060FU,
    GPIO_37_GPIO37        = 0x005C0A00U,
    GPIO_37_OUTPUTXBAR2   = 0x005C0A01U,
    GPIO_37_I2CA_SCL      = 0x005C0A03U,
    GPIO_37_SCIA_TX       = 0x005C0A05U,
    GPIO_37_CANA_TX       = 0x005C0A06U,
    GPIO_37_LINA_TX       = 0x005C0A07U,
    GPIO_37_EQEP1_B       = 0x005C0A09U,
    GPIO_37_PMBUSA_ALERT  = 0x005C0A0AU,
    GPIO_37_TDO           = 0x005C0A0FU,
    GPIO_39_GPIO39        = 0x005C0E00U,
    GPIO_39_CANB_RX       = 0x005C0E06U,
    GPIO_39_FSIRXA_CLK    = 0x005C0E07U,
    GPIO_40_GPIO40        = 0x005C1000U,
    GPIO_40_PMBUSA_SDA    = 0x005C1006U,
    GPIO_40_FSIRXA_D0     = 0x005C1007U,
    GPIO_40_SCIB_TX       = 0x005C1009U,
    GPIO_40_EQEP1_A       = 0x005C100AU,
    GPIO_41_GPIO41        = 0x005C1200U,
    GPIO_41_SPIA_CLK      = 0x005C1201U,
    GPIO_41_SCIB_TX       = 0x005C1202U,
    GPIO_41_CANA_RX       = 0x005C1203U,
    GPIO_41_EPWM6A        = 0x005C1205U,
    GPIO_41_I2CA_SCL      = 0x005C1206U,
    GPIO_41_SD1_D2        = 0x005C1207U,
    GPIO_41_EQEP2_A       = 0x005C1209U,
    GPIO_41_PMBUS_CTL     = 0x005C120AU,
    GPIO_41_XCLKOUT       = 0x005C120BU,
    GPIO_42_GPIO42        = 0x005C1400U,
    GPIO_43_GPIO43        = 0x005C1600U,
    GPIO_44_GPIO44        = 0x005C1800U,
    GPIO_45_GPIO45        = 0x005C1A00U,
    GPIO_46_GPIO46        = 0x005C1C00U,
    GPIO_47_GPIO47        = 0x005C1E00U,
    GPIO_48_GPIO48        = 0x00600000U,
    GPIO_49_GPIO49        = 0x00600200U,
    GPIO_50_GPIO50        = 0x00600400U,
    GPIO_51_GPIO51        = 0x00600600U,
    GPIO_52_GPIO52        = 0x00600800U,
    GPIO_53_GPIO53        = 0x00600A00U,
    GPIO_54_GPIO54        = 0x00600C00U,
    GPIO_55_GPIO55        = 0x00600E00U,
    GPIO_56_GPIO56        = 0x00601000U,
    GPIO_56_SPIA_CLK      = 0x00601001U,
    GPIO_56_EQEP2_STROBE  = 0x00601005U,
    GPIO_56_SCIB_TX       = 0x00601006U,
    GPIO_56_SD1_D3        = 0x00601007U,
    GPIO_56_SPIB_SIMO     = 0x00601009U,
    GPIO_56_EQEP1_A       = 0x0060100BU,
    GPIO_57_GPIO57        = 0x00601200U,
    GPIO_57_SPIA_STE      = 0x00601201U,
    GPIO_57_EQEP2_INDEX   = 0x00601205U,
    GPIO_57_SCIB_RX       = 0x00601206U,
    GPIO_57_SD1_C3        = 0x00601207U,
    GPIO_57_SPIB_SOMI     = 0x00601209U,
    GPIO_57_EQEP1_B       = 0x0060120BU,
    GPIO_58_GPIO58        = 0x00601400U,
    GPIO_58_OUTPUTXBAR1   = 0x00601405U,
    GPIO_58_SPIB_CLK      = 0x00601406U,
    GPIO_58_SD1_D4        = 0x00601407U,
    GPIO_58_LINA_TX       = 0x00601409U,
    GPIO_58_CANB_TX       = 0x0060140AU,
    GPIO_58_EQEP1_STROBE  = 0x0060140BU,
    GPIO_59_GPIO59        = 0x00601600U,
    GPIO_59_OUTPUTXBAR2   = 0x00601605U,
    GPIO_59_SPIB_STE      = 0x00601606U,
    GPIO_59_SD1_C4        = 0x00601607U,
    GPIO_59_LINA_RX       = 0x00601609U,
    GPIO_59_CANB_RX       = 0x0060160AU,
    GPIO_59_EQEP1_INDEX   = 0x0060160BU,
} GPIO_PinMux;

//*****************************************************************************
// Values that can be passed to GPIO_setPadConfig() as the pinType parameter
// and returned by GPIO_getPadConfig().
//*****************************************************************************
typedef enum
{
    GPIO_PIN_TYPE_STD    = 0x00U, // Push-pull output or floating input
    GPIO_PIN_TYPE_PULLUP = 0x01U, // Pull-up enable for input
    GPIO_PIN_TYPE_INVERT = 0x02U, // Invert polarity on input
    GPIO_PIN_TYPE_OD     = 0x04U, // Open-drain on output
} GPIO_PinType;

//*****************************************************************************
//
//! Values that can be passed to GPIO_setDirectionMode() as the \e pinIO
//! parameter and returned from GPIO_getDirectionMode().
//
//*****************************************************************************
typedef enum
{
    GPIO_DIR_MODE_IN  = 0, //!< Pin is a GPIO input
    GPIO_DIR_MODE_OUT = 1, //!< Pin is a GPIO output
} GPIO_Direction;

//*****************************************************************************
//
//! Values that can be passed to GPIO_setInterruptType() as the \e intType
//! parameter and returned from GPIO_getInterruptType().
//
//*****************************************************************************
typedef enum
{
    GPIO_INT_TYPE_FALLING_EDGE = 0x00, //!< Interrupt on falling edge
    GPIO_INT_TYPE_RISING_EDGE  = 0x04, //!< Interrupt on rising edge
    GPIO_INT_TYPE_BOTH_EDGES   = 0x0c  //!< Interrupt on both edges
} GPIO_IntType;

//*****************************************************************************
//
//! Values that can be passed to GPIO_setQualificationMode() as the
//! \e qualification parameter and returned by GPIO_getQualificationMode().
//
//*****************************************************************************
typedef enum
{
    GPIO_QUAL_SYNC    = 0, //!< Synchronization to SYSCLK
    GPIO_QUAL_3SAMPLE = 1, //!< Qualified with 3 samples
    GPIO_QUAL_6SAMPLE = 2, //!< Qualified with 6 samples
    GPIO_QUAL_ASYNC   = 3, //!< No synchronization
} GPIO_QualificationMode;

//*****************************************************************************
//
//! Values that can be passed to GPIO_setAnalogMode() as the \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    GPIO_ANALOG_DISABLED = 0, //!< Pin is in digital mode
    GPIO_ANALOG_ENABLED  = 1, //!< Pin is in analog mode
} GPIO_AnalogMode;

//*****************************************************************************
//
//! Values that can be passed to GPIO_setControllerCore() as the \e core parameter.
//
//*****************************************************************************
typedef enum
{
    GPIO_CORE_CPU1      = 0, //!< CPU1 selected as controller core
    GPIO_CORE_CPU1_CLA1 = 1, //!< CPU1's CLA1 selected as controller core
} GPIO_CoreSelect;

//*****************************************************************************
//
//! Values that can be passed to GPIO_readPortData(), GPIO_setPortPins(),
//! GPIO_clearPortPins(), and GPIO_togglePortPins() as the \e port parameter.
//
//*****************************************************************************
typedef enum
{
    GPIO_PORT_A = 0, //!< GPIO port A
    GPIO_PORT_B = 1, //!< GPIO port B
} GPIO_Port;

//*****************************************************************************
//
//! Values that can be passed to GPIO_setInterruptPin(),
//! GPIO_setInterruptType(), GPIO_getInterruptType(), GPIO_enableInterrupt(),
//! GPIO_disableInterrupt(), as the \e extIntNum parameter.
//
//*****************************************************************************
typedef enum
{
    GPIO_INT_XINT1 = 0, //!< External Interrupt 1
    GPIO_INT_XINT2 = 1, //!< External Interrupt 2
    GPIO_INT_XINT3 = 2, //!< External Interrupt 3
    GPIO_INT_XINT4 = 3, //!< External Interrupt 4
    GPIO_INT_XINT5 = 4, //!< External Interrupt 5
} GPIO_ExternalIntNum;

#ifdef DEBUG
static inline bool GPIO_isPinValid(uint32_t pin)
{
    return ((pin <= 59U) || ((pin != 36U) && (pin != 38U)));
}
#endif

//*****************************************************************************
//
//! Sets the interrupt type for the specified pin.
//!
//! \param extIntNum specifies the external interrupt.
//! \param intType specifies the type of interrupt trigger mechanism.
//!
//! This function sets up the various interrupt trigger mechanisms for the
//! specified pin on the selected GPIO port.
//!
//! The following defines can be used to specify the external interrupt for the
//! \e extIntNum parameter:
//!
//! - \b GPIO_INT_XINT1
//! - \b GPIO_INT_XINT2
//! - \b GPIO_INT_XINT3
//! - \b GPIO_INT_XINT4
//! - \b GPIO_INT_XINT5
//!
//! One of the following flags can be used to define the \e intType
//! parameter:
//!
//! - \b GPIO_INT_TYPE_FALLING_EDGE sets detection to edge and trigger to
//!   falling
//! - \b GPIO_INT_TYPE_RISING_EDGE sets detection to edge and trigger to rising
//! - \b GPIO_INT_TYPE_BOTH_EDGES sets detection to both edges
//!
//! \return None.
//
//*****************************************************************************
static inline void GPIO_setInterruptType(GPIO_ExternalIntNum extIntNum, GPIO_IntType intType)
{
    // Write the selected polarity to the appropriate register.
    HWREG(XINT_BASE + ((uint16_t)extIntNum << 2))
        = (HWREG(XINT_BASE + ((uint16_t)extIntNum << 2)) & ~XINT_1CR_POLARITY_M) | (uint16_t)intType;
}

//*****************************************************************************
//
//! Gets the interrupt type for a pin.
//!
//! \param extIntNum specifies the external interrupt.
//!
//! This function gets the interrupt type for a interrupt. The interrupt can be
//! configured as a falling-edge, rising-edge, or both-edges detected
//! interrupt.
//!
//! The following defines can be used to specify the external interrupt for the
//! \e extIntNum parameter:
//!
//! - \b GPIO_INT_XINT1
//! - \b GPIO_INT_XINT2
//! - \b GPIO_INT_XINT3
//! - \b GPIO_INT_XINT4
//! - \b GPIO_INT_XINT5
//!
//! \return Returns one of the flags described for GPIO_setInterruptType().
//
//*****************************************************************************
static inline GPIO_IntType GPIO_getInterruptType(GPIO_ExternalIntNum extIntNum)
{
    // Read the selected polarity from the appropriate register.
    return ((GPIO_IntType)(HWREGH(XINT_BASE + ((uint16_t)extIntNum << 2)) & XINT_1CR_POLARITY_M));
    return 0;
}

//*****************************************************************************
//
//! Enables the specified external interrupt.
//!
//! \param extIntNum specifies the external interrupt.
//!
//! This function enables the indicated external interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.
//!
//! The following defines can be used to specify the external interrupt for the
//! \e extIntNum parameter:
//!
//! - \b GPIO_INT_XINT1
//! - \b GPIO_INT_XINT2
//! - \b GPIO_INT_XINT3
//! - \b GPIO_INT_XINT4
//! - \b GPIO_INT_XINT5
//!
//! \return None.
//
//*****************************************************************************
static inline void GPIO_enableInterrupt(GPIO_ExternalIntNum extIntNum)
{
    // Set the enable bit for the specified interrupt.
    HWREGH(XINT_BASE + ((uint16_t)extIntNum << 2)) |= XINT_1CR_ENABLE;
}

//*****************************************************************************
//
//! Disables the specified external interrupt.
//!
//! \param extIntNum specifies the external interrupt.
//!
//! This function disables the indicated external interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.
//!
//! The following defines can be used to specify the external interrupt for the
//! \e extIntNum parameter:
//!
//! - \b GPIO_INT_XINT1
//! - \b GPIO_INT_XINT2
//! - \b GPIO_INT_XINT3
//! - \b GPIO_INT_XINT4
//! - \b GPIO_INT_XINT5
//!
//! \return None.
//
//*****************************************************************************
static inline void GPIO_disableInterrupt(GPIO_ExternalIntNum extIntNum)
{
    // Clear the enable bit for the specified interrupt
    HWREGH(XINT_BASE + ((uint16_t)extIntNum << 2)) &= ~XINT_1CR_ENABLE;
}

//*****************************************************************************
//
//! Gets the value of the external interrupt counter.
//!
//! \param extIntNum specifies the external interrupt.
//!
//! The following defines can be used to specify the external interrupt for the
//! \e extIntNum parameter:
//!
//! - \b GPIO_INT_XINT1
//! - \b GPIO_INT_XINT2
//! - \b GPIO_INT_XINT3
//!
//! \b Note: The counter is clocked at the SYSCLKOUT rate.
//!
//! \return Returns external interrupt counter value.
//
//*****************************************************************************
static inline uint16_t GPIO_getInterruptCounter(GPIO_ExternalIntNum extIntNum)
{
    /* ASSERT(extIntNum <= GPIO_INT_XINT3); */
    // Read the counter value from the appropriate register.
    /* return((HWREGH(XINT_BASE + XINT_O_1CTR + (uint16_t)extIntNum))); */
    return 0;
}

//*****************************************************************************
//
//! Reads the value present on the specified pin.
//!
//! \param pin is the identifying GPIO number of the pin.
//!
//! The value at the specified pin are read, as specified by \e pin. The value
//! is returned for both input and output pins.
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin.
//!
//! \return Returns the value in the data register for the specified pin.
//
//*****************************************************************************
static inline uint32_t GPIO_readPin(uint32_t pin)
{
    ASSERT(GPIO_isPinValid(pin));
    if (pin / 32U == 0)
        return ((GpioDataRegs->GPADAT.all >> (pin % 32U)) & (uint32_t)0x1U);
    else
        return ((GpioDataRegs->GPBDAT.all >> (pin % 32U)) & (uint32_t)0x1U);
}

//*****************************************************************************
//
//! Writes a value to the specified pin.
//!
//! \param pin is the identifying GPIO number of the pin.
//! \param outVal is the value to write to the pin.
//!
//! Writes the corresponding bit values to the output pin specified by
//! \e pin.  Writing to a pin configured as an input pin has no effect.
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin.
//!
//! \return None.
//
//*****************************************************************************
extern void GPIO_writePin(uint32_t pin, uint32_t outVal);

//*****************************************************************************
//
//! Toggles the specified pin.
//!
//! \param pin is the identifying GPIO number of the pin.
//!
//! Writes the corresponding bit values to the output pin specified by
//! \e pin.  Writing to a pin configured as an input pin has no effect.
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin.
//!
//! \return None.
//
//*****************************************************************************
static inline void GPIO_togglePin(uint32_t pin)
{
    ASSERT(GPIO_isPinValid(pin));
    if (pin / 32U == 0)
        GpioDataRegs->GPATOGGLE.all = (uint32_t)1U << (pin % 32U);
    else
        GpioDataRegs->GPBTOGGLE.all = (uint32_t)1U << (pin % 32U);
}

//*****************************************************************************
//
//! Reads the data on the specified port.
//!
//! \param port is the GPIO port being accessed in the form of \b GPIO_PORT_X
//! where X is the port letter.
//!
//! \return Returns the value available on pin for the specified port. Each
//! bit of the the return value represents a pin on the port, where bit 0
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//
//*****************************************************************************
static inline uint32_t GPIO_readPortData(GPIO_Port port)
{
    if (port == GPIO_PORT_A)
        return GpioDataRegs->GPADAT.all;
    else
        return GpioDataRegs->GPBDAT.all;
}

//*****************************************************************************
//
//! Writes a value to the specified port.
//!
//! \param port is the GPIO port being accessed.
//! \param outVal is the value to write to the port.
//!
//! This function writes the value \e outVal to the port specified by the
//! \e port parameter which takes a value in the form of \b GPIO_PORT_X where X
//! is the port letter. For example, use \b GPIO_PORT_A to affect port A
//! (GPIOs 0-31).
//!
//! The \e outVal is a bit-packed value, where each bit represents a bit on a
//! GPIO port. Bit 0 represents GPIO port pin 0, bit 1 represents GPIO port
//! pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
static inline void GPIO_writePortData(uint32_t port, uint32_t outVal)
{
    if (port == GPIO_PORT_A)
        GpioDataRegs->GPADAT.all = outVal;
    else
        GpioDataRegs->GPBDAT.all = outVal;
}

//*****************************************************************************
//
//! Sets all of the specified pins on the specified port.
//!
//! \param port is the GPIO port being accessed.
//! \param pinMask is a mask of which of the 32 pins on the port are affected.
//!
//! This function sets all of the pins specified by the \e pinMask parameter on
//! the port specified by the \e port parameter which takes a value in the
//! form of \b GPIO_PORT_X where X is the port letter. For example, use
//! \b GPIO_PORT_A to affect port A (GPIOs 0-31).
//!
//! The \e pinMask is a bit-packed value, where each bit that is set identifies
//! the pin to be set. Bit 0 represents GPIO port pin 0, bit 1 represents GPIO
//! port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
static inline void GPIO_setPortPins(GPIO_Port port, uint32_t pinMask)
{
    if (port == GPIO_PORT_A)
        GpioDataRegs->GPASET.all = pinMask;
    else
        GpioDataRegs->GPASET.all = pinMask;
}

//*****************************************************************************
//
//! Clears all of the specified pins on the specified port.
//!
//! \param port is the GPIO port being accessed.
//! \param pinMask is a mask of which of the 32 pins on the port are affected.
//!
//! This function clears all of the pins specified by the \e pinMask parameter
//! on the port specified by the \e port parameter which takes a value in the
//! form of \b GPIO_PORT_X where X is the port letter. For example, use
//! \b GPIO_PORT_A to affect port A (GPIOs 0-31).
//!
//! The \e pinMask is a bit-packed value, where each bit that is \b set
//! identifies the pin to be cleared. Bit 0 represents GPIO port pin 0, bit 1
//! represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
static inline void GPIO_clearPortPins(GPIO_Port port, uint32_t pinMask)
{
    if (port == GPIO_PORT_A)
        GpioDataRegs->GPACLEAR.all = pinMask;
    else
        GpioDataRegs->GPACLEAR.all = pinMask;
}

//*****************************************************************************
//
//! Toggles all of the specified pins on the specified port.
//!
//! \param port is the GPIO port being accessed.
//! \param pinMask is a mask of which of the 32 pins on the port are affected.
//!
//! This function toggles all of the pins specified by the \e pinMask parameter
//! on the port specified by the \e port parameter which takes a value in the
//! form of \b GPIO_PORT_X where X is the port letter. For example, use
//! \b GPIO_PORT_A to affect port A (GPIOs 0-31).
//!
//! The \e pinMask is a bit-packed value, where each bit that is set identifies
//! the pin to be toggled. Bit 0 represents GPIO port pin 0, bit 1 represents
//! GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
static inline void GPIO_togglePortPins(GPIO_Port port, uint32_t pinMask)
{
    if (port == GPIO_PORT_A)
        GpioDataRegs->GPATOGGLE.all = pinMask;
    else
        GpioDataRegs->GPATOGGLE.all = pinMask;
}

//*****************************************************************************
//
//! Locks the configuration of the specified pins on the specified port.
//!
//! \param port is the GPIO port being accessed.
//! \param pinMask is a mask of which of the 32 pins on the port are affected.
//!
//! This function locks the configuration registers of the pins specified by
//! the \e pinMask parameter on the port specified by the \e port parameter
//! which takes a value in the form of \b GPIO_PORT_X where X is the port
//! letter. For example, use \b GPIO_PORT_A to affect port A (GPIOs 0-31).
//!
//! The \e pinMask is a bit-packed value, where each bit that is set identifies
//! the pin to be locked. Bit 0 represents GPIO port pin 0, bit 1 represents
//! GPIO port pin 1, 0xFFFFFFFF represents all pins on that port, and so on.
//!
//! Note that this function is for locking the configuration of a pin such as
//! the pin muxing, direction, open drain mode, and other settings. It does not
//! affect the ability to change the value of the pin.
//!
//! \return None.
//
//*****************************************************************************
static inline void GPIO_lockPortConfig(GPIO_Port port, uint32_t pinMask)
{
    EALLOW;
    if (port == GPIO_PORT_A)
        GpioCtrlRegs->GPALOCK.all |= pinMask;
    else
        GpioCtrlRegs->GPBLOCK.all |= pinMask;
    EDIS;
}

//*****************************************************************************
//
//! Unlocks the configuration of the specified pins on the specified port.
//!
//! \param port is the GPIO port being accessed.
//! \param pinMask is a mask of which of the 32 pins on the port are affected.
//!
//! This function unlocks the configuration registers of the pins specified by
//! the \e pinMask parameter on the port specified by the \e port parameter
//! which takes a value in the form of \b GPIO_PORT_X where X is the port
//! letter. For example, use \b GPIO_PORT_A to affect port A (GPIOs 0-31).
//!
//! The \e pinMask is a bit-packed value, where each bit that is set identifies
//! the pin to be unlocked. Bit 0 represents GPIO port pin 0, bit 1 represents
//! GPIO port pin 1, 0xFFFFFFFF represents all pins on that port, and so on.
//!
//! \return None.
//
//*****************************************************************************
static inline void GPIO_unlockPortConfig(GPIO_Port port, uint32_t pinMask)
{

    EALLOW;
    if (port == GPIO_PORT_A)
        GpioCtrlRegs->GPALOCK.all &= ~pinMask;
    else
        GpioCtrlRegs->GPBLOCK.all &= ~pinMask;
    EDIS;
}

//*****************************************************************************
//
//! Commits the lock configuration of the specified pins on the specified port.
//!
//! \param port is the GPIO port being accessed.
//! \param pinMask is a mask of which of the 32 pins on the port are affected.
//!
//! This function commits the lock configuration registers of the pins
//! specified by the \e pinMask parameter on the port specified by the \e port
//! parameter which takes a value in the form of \b GPIO_PORT_X where X is the
//! port letter. For example, use \b GPIO_PORT_A to affect port A (GPIOs 0-31).
//!
//! The \e pinMask is a bit-packed value, where each bit that is set identifies
//! the pin to be locked. Bit 0 represents GPIO port pin 0, bit 1 represents
//! GPIO port pin 1, 0xFFFFFFFF represents all pins on that port, and so on.
//!
//! Note that once this function is called, GPIO_lockPortConfig() and
//! GPIO_unlockPortConfig() will no longer have any effect on the specified
//! pins.
//!
//! \return None.
//
//*****************************************************************************
static inline void GPIO_commitPortConfig(GPIO_Port port, uint32_t pinMask)
{
    if (port == GPIO_PORT_A)
        GpioCtrlRegs->GPACR.all |= pinMask;
    else
        GpioCtrlRegs->GPBCR.all |= pinMask;
}

//*****************************************************************************
//
//! Gets the direction mode of a pin.
//!
//! \param pin is the identifying GPIO number of the pin.
//!
//! This function gets the direction mode for a specified pin.  The pin can be
//! configured as either an input or output The type of direction is returned
//! as an enumerated data type.
//!
//! \return Returns one of the enumerated data types described for
//! GPIO_setDirectionMode().
//
//*****************************************************************************
static inline GPIO_Direction GPIO_getDirectionMode(uint32_t pin)
{
    ASSERT(GPIO_isPinValid(pin));

    if (pin / 32U == 0)
        return ((GpioCtrlRegs->GPADIR.all >> (pin % 32U)) & 1U);
    else
        return ((GpioCtrlRegs->GPBDIR.all >> (pin % 32U)) & 1U);
}

//*****************************************************************************
//
//! Sets the direction and mode of the specified pin.
//!
//! \param pin is the identifying GPIO number of the pin.
//! \param pinIO is the pin direction mode.
//!
//! This function configures the specified pin on the selected GPIO port as
//! either input or output.
//!
//! The parameter \e pinIO is an enumerated data type that can be one of the
//! following values:
//!
//! - \b GPIO_DIR_MODE_IN
//! - \b GPIO_DIR_MODE_OUT
//!
//! where \b GPIO_DIR_MODE_IN specifies that the pin is programmed as an input
//! and \b GPIO_DIR_MODE_OUT specifies that the pin is programmed as an output.
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin.
//!
//! \return None.
//
//*****************************************************************************
extern void GPIO_setDirectionMode(uint32_t pin, GPIO_Direction pinIO);

//*****************************************************************************
//
//! Sets the pin for the specified external interrupt.
//!
//! \param pin is the identifying GPIO number of the pin.
//! \param extIntNum specifies the external interrupt.
//!
//! This function sets which pin triggers the selected external interrupt.
//!
//! The following defines can be used to specify the external interrupt for the
//! \e extIntNum parameter:
//!
//! - \b GPIO_INT_XINT1
//! - \b GPIO_INT_XINT2
//! - \b GPIO_INT_XINT3
//! - \b GPIO_INT_XINT4
//! - \b GPIO_INT_XINT5
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin.
//!
//! \sa XBAR_setInputPin()
//!
//! \return None.
//
//*****************************************************************************
extern void GPIO_setInterruptPin(uint32_t pin, GPIO_ExternalIntNum extIntNum);

//*****************************************************************************
//
//! Sets the pad configuration for the specified pin.
//!
//! \param pin is the identifying GPIO number of the pin.
//! \param pinType specifies the pin type.
//!
//! This function sets the pin type for the specified pin. The parameter
//! \e pinType can be the following values:
//!
//! - \b GPIO_PIN_TYPE_STD specifies a push-pull output or a floating input
//! - \b GPIO_PIN_TYPE_PULLUP specifies the pull-up is enabled for an input
//! - \b GPIO_PIN_TYPE_OD specifies an open-drain output pin
//! - \b GPIO_PIN_TYPE_INVERT specifies inverted polarity on an input
//!
//! \b GPIO_PIN_TYPE_INVERT may be OR-ed with \b GPIO_PIN_TYPE_STD or
//! \b GPIO_PIN_TYPE_PULLUP.
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin.
//!
//! \return None.
//
//*****************************************************************************
extern void GPIO_setPadConfig(uint32_t pin, uint32_t pinType);

//*****************************************************************************
//
//! Gets the pad configuration for a pin.
//!
//! \param pin is the identifying GPIO number of the pin.
//!
//! This function returns the pin type for the specified pin.  The value
//! returned corresponds to the values used in GPIO_setPadConfig().
//!
//! \return Returns a bit field of the values \b GPIO_PIN_TYPE_STD,
//! \b GPIO_PIN_TYPE_PULLUP, \b GPIO_PIN_TYPE_OD, and \b GPIO_PIN_TYPE_INVERT.
//
//*****************************************************************************
extern uint32_t GPIO_getPadConfig(uint32_t pin);

//*****************************************************************************
//
//! Sets the qualification mode for the specified pin.
//!
//! \param pin is the identifying GPIO number of the pin.
//! \param qualification specifies the qualification mode of the pin.
//!
//! This function sets the qualification mode for the specified pin. The
//! parameter \e qualification can be one of the following values:
//! - \b GPIO_QUAL_SYNC
//! - \b GPIO_QUAL_3SAMPLE
//! - \b GPIO_QUAL_6SAMPLE
//! - \b GPIO_QUAL_ASYNC
//!
//! To set the qualification sampling period, use
//! GPIO_setQualificationPeriod().
//!
//! \return None.
//
//*****************************************************************************
extern void GPIO_setQualificationMode(uint32_t pin, GPIO_QualificationMode qualification);

//*****************************************************************************
//
//! Gets the qualification type for the specified pin.
//!
//! \param pin is the identifying GPIO number of the pin.
//!
//! \return Returns the qualification mode in the form of one of the values
//! \b GPIO_QUAL_SYNC, \b GPIO_QUAL_3SAMPLE, \b GPIO_QUAL_6SAMPLE, or
//! \b GPIO_QUAL_ASYNC.
//
//*****************************************************************************
extern GPIO_QualificationMode GPIO_getQualificationMode(uint32_t pin);

//*****************************************************************************
//
//! Sets the qualification period for a set of pins
//!
//! \param pin is the identifying GPIO number of the pin.
//! \param divider specifies the output drive strength.
//!
//! This function sets the qualification period for a set of \b 8 \b pins,
//! specified by the \e pin parameter. For instance, passing in 3 as the value
//! of \e pin will set the qualification period for GPIO0 through GPIO7, and a
//! value of 98 will set the qualification period for GPIO96 through GPIO103.
//! This is because the register field that configures the divider is shared.
//!
//! To think of this in terms of an equation, configuring \e pin as \b n will
//! configure GPIO (n & ~(7)) through GPIO ((n & ~(7)) + 7).
//!
//! \e divider is the value by which the frequency of SYSCLKOUT is divided. It
//! can be 1 or an even value between 2 and 510 inclusive.
//!
//! \return None.
//
//*****************************************************************************
extern void GPIO_setQualificationPeriod(uint32_t pin, uint32_t divider);

//*****************************************************************************
//
//! Selects the controller core of a specified pin.
//!
//! \param pin is the identifying GPIO number of the pin.
//! \param core is the core that is controller of the specified pin.
//!
//! This function configures which core owns the specified pin's data registers
//! (DATA, SET, CLEAR, and TOGGLE). The \e core parameter is an enumerated data
//! type that specifies the core, such as \b GPIO_CORE_CPU1_CLA1 to make CPU1's
//! CLA1 controller of the pin.
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin.
//!
//! \return None.
//
//*****************************************************************************
extern void GPIO_setControllerCore(uint32_t pin, GPIO_CoreSelect core);

//*****************************************************************************
//
//! Sets the analog mode of the specified pin.
//!
//! \param pin is the identifying GPIO number of the pin.
//! \param mode is the selected analog mode.
//!
//! This function configures the specified pin for either analog or digital
//! mode. Not all GPIO pins have the ability to be switched to analog mode,
//! so refer to the technical reference manual for details. This setting should
//! be thought of as another level of muxing.
//!
//! The parameter \e mode is an enumerated data type that can be one of the
//! following values:
//!
//! - \b GPIO_ANALOG_DISABLED - Pin is in digital mode
//! - \b GPIO_ANALOG_ENABLED - Pin is in analog mode
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin.
//!
//! \return None.
//
//*****************************************************************************
extern void GPIO_setAnalogMode(uint32_t pin, GPIO_AnalogMode mode);

//*****************************************************************************
//
//! Configures the alternate function of a GPIO pin.
//!
//! \param pinConfig is the pin configuration value, specified as only one
//! of the \b GPIO_#_???? values.
//!
//! This function configures the pin mux that selects the peripheral function
//! associated with a particular GPIO pin.  Only one peripheral function at a
//! time can be associated with a GPIO pin, and each peripheral function should
//! only be associated with a single GPIO pin at a time (despite the fact that
//! many of them can be associated with more than one GPIO pin).
//!
//! The available mappings are supplied in <tt>pin_map.h</tt>.
//!
//! \return None.
//
//*****************************************************************************
extern void GPIO_setPinConfig(GPIO_PinMux pinMux);

//*****************************************************************************
// Configures the all essential function of a GPIO pin.
//*****************************************************************************
void GPIO_Config(uint32_t pin, GPIO_PinMux mux, GPIO_Direction dir, GPIO_PinType type, GPIO_QualificationMode qual);

#ifdef __cplusplus
}
#endif

#endif
