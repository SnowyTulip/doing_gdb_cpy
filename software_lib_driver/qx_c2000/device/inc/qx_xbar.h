/**
 **************************************************************************
 * @file     qx_xbar.h
 * @version  v1.0.0
 * @date     2023-8-30
 **************************************************************************
 */

#ifndef QX_XBAR_H
#define QX_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"

#include "hw_inputxbar.h"
#include "hw_outputxbar.h"
#include "hw_epwmxbar.h"
#include "hw_xbar.h"
#include "hw_xint.h"

//---------------------------------------------------------------------------
// INPUT_XBAR Individual Register Bit Definitions:

struct INPUTSELECTLOCK_BITS
{                            // bits description
    vu32 INPUT1SELECT  : 1;  // 0 Lock bit for INPUT1SELECT Register
    vu32 INPUT2SELECT  : 1;  // 1 Lock bit for INPUT2SELECT Register
    vu32 INPUT3SELECT  : 1;  // 2 Lock bit for INPUT3SELECT Register
    vu32 INPUT4SELECT  : 1;  // 3 Lock bit for INPUT4SELECT Register
    vu32 INPUT5SELECT  : 1;  // 4 Lock bit for INPUT5SELECT Register
    vu32 INPUT6SELECT  : 1;  // 5 Lock bit for INPUT6SELECT Register
    vu32 INPUT7SELECT  : 1;  // 6 Lock bit for INPUT7SELECT Register
    vu32 INPUT8SELECT  : 1;  // 7 Lock bit for INPUT8SELECT Register
    vu32 INPUT9SELECT  : 1;  // 8 Lock bit for INPUT9SELECT Register
    vu32 INPUT10SELECT : 1;  // 9 Lock bit for INPUT10SELECT Register
    vu32 INPUT11SELECT : 1;  // 10 Lock bit for INPUT11SELECT Register
    vu32 INPUT12SELECT : 1;  // 11 Lock bit for INPUT12SELECT Register
    vu32 INPUT13SELECT : 1;  // 12 Lock bit for INPUT13SELECT Register
    vu32 INPUT14SELECT : 1;  // 13 Lock bit for INPUT14SELECT Register
    vu32 INPUT15SELECT : 1;  // 14 Lock bit for INPUT15SELECT Register
    vu32 INPUT16SELECT : 1;  // 15 Lock bit for INPUT16SELECT Register
    vu32 rsvd1         : 16; // 31:16 Reserved
};

union INPUTSELECTLOCK_REG
{
    vu32 all;
    struct INPUTSELECTLOCK_BITS bit;
};

struct INPUT_XBAR_REGS
{
    vu32 INPUT1SELECT;                         // INPUT1 Input Select Register (GPIO0 to x)
    vu32 INPUT2SELECT;                         // INPUT2 Input Select Register (GPIO0 to x)
    vu32 INPUT3SELECT;                         // INPUT3 Input Select Register (GPIO0 to x)
    vu32 INPUT4SELECT;                         // INPUT4 Input Select Register (GPIO0 to x)
    vu32 INPUT5SELECT;                         // INPUT5 Input Select Register (GPIO0 to x)
    vu32 INPUT6SELECT;                         // INPUT6 Input Select Register (GPIO0 to x)
    vu32 INPUT7SELECT;                         // INPUT7 Input Select Register (GPIO0 to x)
    vu32 INPUT8SELECT;                         // INPUT8 Input Select Register (GPIO0 to x)
    vu32 INPUT9SELECT;                         // INPUT9 Input Select Register (GPIO0 to x)
    vu32 INPUT10SELECT;                        // INPUT10 Input Select Register (GPIO0 to x)
    vu32 INPUT11SELECT;                        // INPUT11 Input Select Register (GPIO0 to x)
    vu32 INPUT12SELECT;                        // INPUT12 Input Select Register (GPIO0 to x)
    vu32 INPUT13SELECT;                        // INPUT13 Input Select Register (GPIO0 to x)
    vu32 INPUT14SELECT;                        // INPUT14 Input Select Register (GPIO0 to x)
    vu32 INPUT15SELECT;                        // INPUT15 Input Select Register (GPIO0 to x)
    vu32 INPUT16SELECT;                        // INPUT16 Input Select Register (GPIO0 to x)
    vu32 rsvd1[16];                            // Reserved
    union INPUTSELECTLOCK_REG INPUTSELECTLOCK; // Input Select Lock Register, offset: 0x80
};

//---------------------------------------------------------------------------
// OUTPUT_XBAR Individual Register Bit Definitions:

struct OUTPUT1MUX0TO15CFG_BITS
{                   // bits description
    vu32 MUX0  : 2; // 1:0 Mux0 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX1  : 2; // 3:2 Mux1 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX2  : 2; // 5:4 Mux2 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX3  : 2; // 7:6 Mux3 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX4  : 2; // 9:8 Mux4 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX5  : 2; // 11:10 Mux5 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX6  : 2; // 13:12 Mux6 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX7  : 2; // 15:14 Mux7 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX8  : 2; // 17:16 Mux8 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX9  : 2; // 19:18 Mux9 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX10 : 2; // 21:20 Mux10 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX11 : 2; // 23:22 Mux11 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX12 : 2; // 25:24 Mux12 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX13 : 2; // 27:26 Mux13 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX14 : 2; // 29:28 Mux14 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX15 : 2; // 31:30 Mux15 Configuration for OUTPUT1 of OUTPUT-XBAR
};

union OUTPUT1MUX0TO15CFG_REG
{
    vu32 all;
    struct OUTPUT1MUX0TO15CFG_BITS bit;
};

struct OUTPUT1MUX16TO31CFG_BITS
{                   // bits description
    vu32 MUX16 : 2; // 1:0 Mux16 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX17 : 2; // 3:2 Mux17 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX18 : 2; // 5:4 Mux18 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX19 : 2; // 7:6 Mux19 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX20 : 2; // 9:8 Mux20 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX21 : 2; // 11:10 Mux21 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX22 : 2; // 13:12 Mux22 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX23 : 2; // 15:14 Mux23 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX24 : 2; // 17:16 Mux24 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX25 : 2; // 19:18 Mux25 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX26 : 2; // 21:20 Mux26 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX27 : 2; // 23:22 Mux27 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX28 : 2; // 25:24 Mux28 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX29 : 2; // 27:26 Mux29 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX30 : 2; // 29:28 Mux30 Configuration for OUTPUT1 of OUTPUT-XBAR
    vu32 MUX31 : 2; // 31:30 Mux31 Configuration for OUTPUT1 of OUTPUT-XBAR
};

union OUTPUT1MUX16TO31CFG_REG
{
    vu32 all;
    struct OUTPUT1MUX16TO31CFG_BITS bit;
};

struct OUTPUT2MUX0TO15CFG_BITS
{                   // bits description
    vu32 MUX0  : 2; // 1:0 Mux0 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX1  : 2; // 3:2 Mux1 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX2  : 2; // 5:4 Mux2 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX3  : 2; // 7:6 Mux3 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX4  : 2; // 9:8 Mux4 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX5  : 2; // 11:10 Mux5 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX6  : 2; // 13:12 Mux6 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX7  : 2; // 15:14 Mux7 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX8  : 2; // 17:16 Mux8 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX9  : 2; // 19:18 Mux9 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX10 : 2; // 21:20 Mux10 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX11 : 2; // 23:22 Mux11 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX12 : 2; // 25:24 Mux12 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX13 : 2; // 27:26 Mux13 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX14 : 2; // 29:28 Mux14 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX15 : 2; // 31:30 Mux15 Configuration for OUTPUT2 of OUTPUT-XBAR
};

union OUTPUT2MUX0TO15CFG_REG
{
    vu32 all;
    struct OUTPUT2MUX0TO15CFG_BITS bit;
};

struct OUTPUT2MUX16TO31CFG_BITS
{                   // bits description
    vu32 MUX16 : 2; // 1:0 Mux16 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX17 : 2; // 3:2 Mux17 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX18 : 2; // 5:4 Mux18 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX19 : 2; // 7:6 Mux19 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX20 : 2; // 9:8 Mux20 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX21 : 2; // 11:10 Mux21 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX22 : 2; // 13:12 Mux22 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX23 : 2; // 15:14 Mux23 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX24 : 2; // 17:16 Mux24 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX25 : 2; // 19:18 Mux25 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX26 : 2; // 21:20 Mux26 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX27 : 2; // 23:22 Mux27 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX28 : 2; // 25:24 Mux28 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX29 : 2; // 27:26 Mux29 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX30 : 2; // 29:28 Mux30 Configuration for OUTPUT2 of OUTPUT-XBAR
    vu32 MUX31 : 2; // 31:30 Mux31 Configuration for OUTPUT2 of OUTPUT-XBAR
};

union OUTPUT2MUX16TO31CFG_REG
{
    vu32 all;
    struct OUTPUT2MUX16TO31CFG_BITS bit;
};

struct OUTPUT3MUX0TO15CFG_BITS
{                   // bits description
    vu32 MUX0  : 2; // 1:0 Mux0 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX1  : 2; // 3:2 Mux1 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX2  : 2; // 5:4 Mux2 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX3  : 2; // 7:6 Mux3 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX4  : 2; // 9:8 Mux4 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX5  : 2; // 11:10 Mux5 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX6  : 2; // 13:12 Mux6 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX7  : 2; // 15:14 Mux7 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX8  : 2; // 17:16 Mux8 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX9  : 2; // 19:18 Mux9 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX10 : 2; // 21:20 Mux10 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX11 : 2; // 23:22 Mux11 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX12 : 2; // 25:24 Mux12 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX13 : 2; // 27:26 Mux13 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX14 : 2; // 29:28 Mux14 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX15 : 2; // 31:30 Mux15 Configuration for OUTPUT3 of OUTPUT-XBAR
};

union OUTPUT3MUX0TO15CFG_REG
{
    vu32 all;
    struct OUTPUT3MUX0TO15CFG_BITS bit;
};

struct OUTPUT3MUX16TO31CFG_BITS
{                   // bits description
    vu32 MUX16 : 2; // 1:0 Mux16 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX17 : 2; // 3:2 Mux17 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX18 : 2; // 5:4 Mux18 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX19 : 2; // 7:6 Mux19 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX20 : 2; // 9:8 Mux20 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX21 : 2; // 11:10 Mux21 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX22 : 2; // 13:12 Mux22 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX23 : 2; // 15:14 Mux23 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX24 : 2; // 17:16 Mux24 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX25 : 2; // 19:18 Mux25 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX26 : 2; // 21:20 Mux26 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX27 : 2; // 23:22 Mux27 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX28 : 2; // 25:24 Mux28 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX29 : 2; // 27:26 Mux29 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX30 : 2; // 29:28 Mux30 Configuration for OUTPUT3 of OUTPUT-XBAR
    vu32 MUX31 : 2; // 31:30 Mux31 Configuration for OUTPUT3 of OUTPUT-XBAR
};

union OUTPUT3MUX16TO31CFG_REG
{
    vu32 all;
    struct OUTPUT3MUX16TO31CFG_BITS bit;
};

struct OUTPUT4MUX0TO15CFG_BITS
{                   // bits description
    vu32 MUX0  : 2; // 1:0 Mux0 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX1  : 2; // 3:2 Mux1 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX2  : 2; // 5:4 Mux2 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX3  : 2; // 7:6 Mux3 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX4  : 2; // 9:8 Mux4 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX5  : 2; // 11:10 Mux5 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX6  : 2; // 13:12 Mux6 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX7  : 2; // 15:14 Mux7 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX8  : 2; // 17:16 Mux8 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX9  : 2; // 19:18 Mux9 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX10 : 2; // 21:20 Mux10 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX11 : 2; // 23:22 Mux11 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX12 : 2; // 25:24 Mux12 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX13 : 2; // 27:26 Mux13 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX14 : 2; // 29:28 Mux14 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX15 : 2; // 31:30 Mux15 Configuration for OUTPUT4 of OUTPUT-XBAR
};

union OUTPUT4MUX0TO15CFG_REG
{
    vu32 all;
    struct OUTPUT4MUX0TO15CFG_BITS bit;
};

struct OUTPUT4MUX16TO31CFG_BITS
{                   // bits description
    vu32 MUX16 : 2; // 1:0 Mux16 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX17 : 2; // 3:2 Mux17 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX18 : 2; // 5:4 Mux18 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX19 : 2; // 7:6 Mux19 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX20 : 2; // 9:8 Mux20 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX21 : 2; // 11:10 Mux21 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX22 : 2; // 13:12 Mux22 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX23 : 2; // 15:14 Mux23 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX24 : 2; // 17:16 Mux24 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX25 : 2; // 19:18 Mux25 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX26 : 2; // 21:20 Mux26 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX27 : 2; // 23:22 Mux27 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX28 : 2; // 25:24 Mux28 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX29 : 2; // 27:26 Mux29 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX30 : 2; // 29:28 Mux30 Configuration for OUTPUT4 of OUTPUT-XBAR
    vu32 MUX31 : 2; // 31:30 Mux31 Configuration for OUTPUT4 of OUTPUT-XBAR
};

union OUTPUT4MUX16TO31CFG_REG
{
    vu32 all;
    struct OUTPUT4MUX16TO31CFG_BITS bit;
};

struct OUTPUT5MUX0TO15CFG_BITS
{                   // bits description
    vu32 MUX0  : 2; // 1:0 Mux0 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX1  : 2; // 3:2 Mux1 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX2  : 2; // 5:4 Mux2 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX3  : 2; // 7:6 Mux3 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX4  : 2; // 9:8 Mux4 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX5  : 2; // 11:10 Mux5 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX6  : 2; // 13:12 Mux6 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX7  : 2; // 15:14 Mux7 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX8  : 2; // 17:16 Mux8 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX9  : 2; // 19:18 Mux9 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX10 : 2; // 21:20 Mux10 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX11 : 2; // 23:22 Mux11 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX12 : 2; // 25:24 Mux12 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX13 : 2; // 27:26 Mux13 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX14 : 2; // 29:28 Mux14 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX15 : 2; // 31:30 Mux15 Configuration for OUTPUT5 of OUTPUT-XBAR
};

union OUTPUT5MUX0TO15CFG_REG
{
    vu32 all;
    struct OUTPUT5MUX0TO15CFG_BITS bit;
};

struct OUTPUT5MUX16TO31CFG_BITS
{                   // bits description
    vu32 MUX16 : 2; // 1:0 Mux16 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX17 : 2; // 3:2 Mux17 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX18 : 2; // 5:4 Mux18 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX19 : 2; // 7:6 Mux19 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX20 : 2; // 9:8 Mux20 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX21 : 2; // 11:10 Mux21 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX22 : 2; // 13:12 Mux22 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX23 : 2; // 15:14 Mux23 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX24 : 2; // 17:16 Mux24 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX25 : 2; // 19:18 Mux25 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX26 : 2; // 21:20 Mux26 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX27 : 2; // 23:22 Mux27 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX28 : 2; // 25:24 Mux28 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX29 : 2; // 27:26 Mux29 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX30 : 2; // 29:28 Mux30 Configuration for OUTPUT5 of OUTPUT-XBAR
    vu32 MUX31 : 2; // 31:30 Mux31 Configuration for OUTPUT5 of OUTPUT-XBAR
};

union OUTPUT5MUX16TO31CFG_REG
{
    vu32 all;
    struct OUTPUT5MUX16TO31CFG_BITS bit;
};

struct OUTPUT6MUX0TO15CFG_BITS
{                   // bits description
    vu32 MUX0  : 2; // 1:0 Mux0 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX1  : 2; // 3:2 Mux1 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX2  : 2; // 5:4 Mux2 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX3  : 2; // 7:6 Mux3 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX4  : 2; // 9:8 Mux4 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX5  : 2; // 11:10 Mux5 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX6  : 2; // 13:12 Mux6 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX7  : 2; // 15:14 Mux7 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX8  : 2; // 17:16 Mux8 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX9  : 2; // 19:18 Mux9 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX10 : 2; // 21:20 Mux10 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX11 : 2; // 23:22 Mux11 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX12 : 2; // 25:24 Mux12 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX13 : 2; // 27:26 Mux13 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX14 : 2; // 29:28 Mux14 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX15 : 2; // 31:30 Mux15 Configuration for OUTPUT6 of OUTPUT-XBAR
};

union OUTPUT6MUX0TO15CFG_REG
{
    vu32 all;
    struct OUTPUT6MUX0TO15CFG_BITS bit;
};

struct OUTPUT6MUX16TO31CFG_BITS
{                   // bits description
    vu32 MUX16 : 2; // 1:0 Mux16 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX17 : 2; // 3:2 Mux17 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX18 : 2; // 5:4 Mux18 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX19 : 2; // 7:6 Mux19 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX20 : 2; // 9:8 Mux20 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX21 : 2; // 11:10 Mux21 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX22 : 2; // 13:12 Mux22 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX23 : 2; // 15:14 Mux23 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX24 : 2; // 17:16 Mux24 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX25 : 2; // 19:18 Mux25 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX26 : 2; // 21:20 Mux26 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX27 : 2; // 23:22 Mux27 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX28 : 2; // 25:24 Mux28 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX29 : 2; // 27:26 Mux29 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX30 : 2; // 29:28 Mux30 Configuration for OUTPUT6 of OUTPUT-XBAR
    vu32 MUX31 : 2; // 31:30 Mux31 Configuration for OUTPUT6 of OUTPUT-XBAR
};

union OUTPUT6MUX16TO31CFG_REG
{
    vu32 all;
    struct OUTPUT6MUX16TO31CFG_BITS bit;
};

struct OUTPUT7MUX0TO15CFG_BITS
{                   // bits description
    vu32 MUX0  : 2; // 1:0 Mux0 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX1  : 2; // 3:2 Mux1 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX2  : 2; // 5:4 Mux2 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX3  : 2; // 7:6 Mux3 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX4  : 2; // 9:8 Mux4 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX5  : 2; // 11:10 Mux5 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX6  : 2; // 13:12 Mux6 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX7  : 2; // 15:14 Mux7 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX8  : 2; // 17:16 Mux8 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX9  : 2; // 19:18 Mux9 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX10 : 2; // 21:20 Mux10 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX11 : 2; // 23:22 Mux11 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX12 : 2; // 25:24 Mux12 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX13 : 2; // 27:26 Mux13 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX14 : 2; // 29:28 Mux14 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX15 : 2; // 31:30 Mux15 Configuration for OUTPUT7 of OUTPUT-XBAR
};

union OUTPUT7MUX0TO15CFG_REG
{
    vu32 all;
    struct OUTPUT7MUX0TO15CFG_BITS bit;
};

struct OUTPUT7MUX16TO31CFG_BITS
{                   // bits description
    vu32 MUX16 : 2; // 1:0 Mux16 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX17 : 2; // 3:2 Mux17 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX18 : 2; // 5:4 Mux18 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX19 : 2; // 7:6 Mux19 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX20 : 2; // 9:8 Mux20 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX21 : 2; // 11:10 Mux21 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX22 : 2; // 13:12 Mux22 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX23 : 2; // 15:14 Mux23 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX24 : 2; // 17:16 Mux24 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX25 : 2; // 19:18 Mux25 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX26 : 2; // 21:20 Mux26 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX27 : 2; // 23:22 Mux27 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX28 : 2; // 25:24 Mux28 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX29 : 2; // 27:26 Mux29 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX30 : 2; // 29:28 Mux30 Configuration for OUTPUT7 of OUTPUT-XBAR
    vu32 MUX31 : 2; // 31:30 Mux31 Configuration for OUTPUT7 of OUTPUT-XBAR
};

union OUTPUT7MUX16TO31CFG_REG
{
    vu32 all;
    struct OUTPUT7MUX16TO31CFG_BITS bit;
};

struct OUTPUT8MUX0TO15CFG_BITS
{                   // bits description
    vu32 MUX0  : 2; // 1:0 Mux0 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX1  : 2; // 3:2 Mux1 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX2  : 2; // 5:4 Mux2 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX3  : 2; // 7:6 Mux3 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX4  : 2; // 9:8 Mux4 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX5  : 2; // 11:10 Mux5 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX6  : 2; // 13:12 Mux6 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX7  : 2; // 15:14 Mux7 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX8  : 2; // 17:16 Mux8 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX9  : 2; // 19:18 Mux9 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX10 : 2; // 21:20 Mux10 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX11 : 2; // 23:22 Mux11 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX12 : 2; // 25:24 Mux12 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX13 : 2; // 27:26 Mux13 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX14 : 2; // 29:28 Mux14 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX15 : 2; // 31:30 Mux15 Configuration for OUTPUT8 of OUTPUT-XBAR
};

union OUTPUT8MUX0TO15CFG_REG
{
    vu32 all;
    struct OUTPUT8MUX0TO15CFG_BITS bit;
};

struct OUTPUT8MUX16TO31CFG_BITS
{                   // bits description
    vu32 MUX16 : 2; // 1:0 Mux16 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX17 : 2; // 3:2 Mux17 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX18 : 2; // 5:4 Mux18 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX19 : 2; // 7:6 Mux19 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX20 : 2; // 9:8 Mux20 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX21 : 2; // 11:10 Mux21 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX22 : 2; // 13:12 Mux22 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX23 : 2; // 15:14 Mux23 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX24 : 2; // 17:16 Mux24 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX25 : 2; // 19:18 Mux25 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX26 : 2; // 21:20 Mux26 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX27 : 2; // 23:22 Mux27 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX28 : 2; // 25:24 Mux28 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX29 : 2; // 27:26 Mux29 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX30 : 2; // 29:28 Mux30 Configuration for OUTPUT8 of OUTPUT-XBAR
    vu32 MUX31 : 2; // 31:30 Mux31 Configuration for OUTPUT8 of OUTPUT-XBAR
};

union OUTPUT8MUX16TO31CFG_REG
{
    vu32 all;
    struct OUTPUT8MUX16TO31CFG_BITS bit;
};

struct OUTPUT1MUXENABLE_BITS
{                   // bits description
    vu32 MUX0  : 1; // 0 Mux0 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX1  : 1; // 1 Mux1 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX2  : 1; // 2 Mux2 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX3  : 1; // 3 Mux3 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX4  : 1; // 4 Mux4 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX5  : 1; // 5 Mux5 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX6  : 1; // 6 Mux6 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX7  : 1; // 7 Mux7 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX8  : 1; // 8 Mux8 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX9  : 1; // 9 Mux9 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX10 : 1; // 10 Mux10 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX11 : 1; // 11 Mux11 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX12 : 1; // 12 Mux12 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX13 : 1; // 13 Mux13 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX14 : 1; // 14 Mux14 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX15 : 1; // 15 Mux15 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX16 : 1; // 16 Mux16 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX17 : 1; // 17 Mux17 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX18 : 1; // 18 Mux18 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX19 : 1; // 19 Mux19 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX20 : 1; // 20 Mux20 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX21 : 1; // 21 Mux21 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX22 : 1; // 22 Mux22 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX23 : 1; // 23 Mux23 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX24 : 1; // 24 Mux24 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX25 : 1; // 25 Mux25 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX26 : 1; // 26 Mux26 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX27 : 1; // 27 Mux27 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX28 : 1; // 28 Mux28 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX29 : 1; // 29 Mux29 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX30 : 1; // 30 Mux30 to drive OUTPUT1 of OUTPUT-XBAR
    vu32 MUX31 : 1; // 31 Mux31 to drive OUTPUT1 of OUTPUT-XBAR
};

union OUTPUT1MUXENABLE_REG
{
    vu32 all;
    struct OUTPUT1MUXENABLE_BITS bit;
};

struct OUTPUT2MUXENABLE_BITS
{                   // bits description
    vu32 MUX0  : 1; // 0 Mux0 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX1  : 1; // 1 Mux1 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX2  : 1; // 2 Mux2 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX3  : 1; // 3 Mux3 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX4  : 1; // 4 Mux4 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX5  : 1; // 5 Mux5 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX6  : 1; // 6 Mux6 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX7  : 1; // 7 Mux7 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX8  : 1; // 8 Mux8 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX9  : 1; // 9 Mux9 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX10 : 1; // 10 Mux10 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX11 : 1; // 11 Mux11 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX12 : 1; // 12 Mux12 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX13 : 1; // 13 Mux13 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX14 : 1; // 14 Mux14 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX15 : 1; // 15 Mux15 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX16 : 1; // 16 Mux16 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX17 : 1; // 17 Mux17 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX18 : 1; // 18 Mux18 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX19 : 1; // 19 Mux19 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX20 : 1; // 20 Mux20 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX21 : 1; // 21 Mux21 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX22 : 1; // 22 Mux22 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX23 : 1; // 23 Mux23 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX24 : 1; // 24 Mux24 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX25 : 1; // 25 Mux25 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX26 : 1; // 26 Mux26 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX27 : 1; // 27 Mux27 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX28 : 1; // 28 Mux28 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX29 : 1; // 29 Mux29 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX30 : 1; // 30 Mux30 to drive OUTPUT2 of OUTPUT-XBAR
    vu32 MUX31 : 1; // 31 Mux31 to drive OUTPUT2 of OUTPUT-XBAR
};

union OUTPUT2MUXENABLE_REG
{
    vu32 all;
    struct OUTPUT2MUXENABLE_BITS bit;
};

struct OUTPUT3MUXENABLE_BITS
{                   // bits description
    vu32 MUX0  : 1; // 0 Mux0 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX1  : 1; // 1 Mux1 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX2  : 1; // 2 Mux2 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX3  : 1; // 3 Mux3 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX4  : 1; // 4 Mux4 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX5  : 1; // 5 Mux5 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX6  : 1; // 6 Mux6 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX7  : 1; // 7 Mux7 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX8  : 1; // 8 Mux8 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX9  : 1; // 9 Mux9 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX10 : 1; // 10 Mux10 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX11 : 1; // 11 Mux11 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX12 : 1; // 12 Mux12 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX13 : 1; // 13 Mux13 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX14 : 1; // 14 Mux14 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX15 : 1; // 15 Mux15 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX16 : 1; // 16 Mux16 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX17 : 1; // 17 Mux17 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX18 : 1; // 18 Mux18 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX19 : 1; // 19 Mux19 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX20 : 1; // 20 Mux20 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX21 : 1; // 21 Mux21 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX22 : 1; // 22 Mux22 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX23 : 1; // 23 Mux23 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX24 : 1; // 24 Mux24 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX25 : 1; // 25 Mux25 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX26 : 1; // 26 Mux26 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX27 : 1; // 27 Mux27 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX28 : 1; // 28 Mux28 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX29 : 1; // 29 Mux29 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX30 : 1; // 30 Mux30 to drive OUTPUT3 of OUTPUT-XBAR
    vu32 MUX31 : 1; // 31 Mux31 to drive OUTPUT3 of OUTPUT-XBAR
};

union OUTPUT3MUXENABLE_REG
{
    vu32 all;
    struct OUTPUT3MUXENABLE_BITS bit;
};

struct OUTPUT4MUXENABLE_BITS
{                   // bits description
    vu32 MUX0  : 1; // 0 Mux0 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX1  : 1; // 1 Mux1 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX2  : 1; // 2 Mux2 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX3  : 1; // 3 Mux3 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX4  : 1; // 4 Mux4 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX5  : 1; // 5 Mux5 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX6  : 1; // 6 Mux6 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX7  : 1; // 7 Mux7 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX8  : 1; // 8 Mux8 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX9  : 1; // 9 Mux9 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX10 : 1; // 10 Mux10 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX11 : 1; // 11 Mux11 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX12 : 1; // 12 Mux12 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX13 : 1; // 13 Mux13 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX14 : 1; // 14 Mux14 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX15 : 1; // 15 Mux15 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX16 : 1; // 16 Mux16 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX17 : 1; // 17 Mux17 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX18 : 1; // 18 Mux18 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX19 : 1; // 19 Mux19 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX20 : 1; // 20 Mux20 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX21 : 1; // 21 Mux21 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX22 : 1; // 22 Mux22 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX23 : 1; // 23 Mux23 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX24 : 1; // 24 Mux24 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX25 : 1; // 25 Mux25 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX26 : 1; // 26 Mux26 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX27 : 1; // 27 Mux27 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX28 : 1; // 28 Mux28 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX29 : 1; // 29 Mux29 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX30 : 1; // 30 Mux30 to drive OUTPUT4 of OUTPUT-XBAR
    vu32 MUX31 : 1; // 31 Mux31 to drive OUTPUT4 of OUTPUT-XBAR
};

union OUTPUT4MUXENABLE_REG
{
    vu32 all;
    struct OUTPUT4MUXENABLE_BITS bit;
};

struct OUTPUT5MUXENABLE_BITS
{                   // bits description
    vu32 MUX0  : 1; // 0 Mux0 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX1  : 1; // 1 Mux1 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX2  : 1; // 2 Mux2 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX3  : 1; // 3 Mux3 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX4  : 1; // 4 Mux4 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX5  : 1; // 5 Mux5 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX6  : 1; // 6 Mux6 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX7  : 1; // 7 Mux7 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX8  : 1; // 8 Mux8 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX9  : 1; // 9 Mux9 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX10 : 1; // 10 Mux10 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX11 : 1; // 11 Mux11 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX12 : 1; // 12 Mux12 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX13 : 1; // 13 Mux13 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX14 : 1; // 14 Mux14 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX15 : 1; // 15 Mux15 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX16 : 1; // 16 Mux16 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX17 : 1; // 17 Mux17 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX18 : 1; // 18 Mux18 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX19 : 1; // 19 Mux19 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX20 : 1; // 20 Mux20 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX21 : 1; // 21 Mux21 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX22 : 1; // 22 Mux22 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX23 : 1; // 23 Mux23 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX24 : 1; // 24 Mux24 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX25 : 1; // 25 Mux25 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX26 : 1; // 26 Mux26 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX27 : 1; // 27 Mux27 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX28 : 1; // 28 Mux28 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX29 : 1; // 29 Mux29 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX30 : 1; // 30 Mux30 to drive OUTPUT5 of OUTPUT-XBAR
    vu32 MUX31 : 1; // 31 Mux31 to drive OUTPUT5 of OUTPUT-XBAR
};

union OUTPUT5MUXENABLE_REG
{
    vu32 all;
    struct OUTPUT5MUXENABLE_BITS bit;
};

struct OUTPUT6MUXENABLE_BITS
{                   // bits description
    vu32 MUX0  : 1; // 0 Mux0 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX1  : 1; // 1 Mux1 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX2  : 1; // 2 Mux2 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX3  : 1; // 3 Mux3 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX4  : 1; // 4 Mux4 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX5  : 1; // 5 Mux5 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX6  : 1; // 6 Mux6 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX7  : 1; // 7 Mux7 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX8  : 1; // 8 Mux8 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX9  : 1; // 9 Mux9 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX10 : 1; // 10 Mux10 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX11 : 1; // 11 Mux11 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX12 : 1; // 12 Mux12 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX13 : 1; // 13 Mux13 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX14 : 1; // 14 Mux14 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX15 : 1; // 15 Mux15 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX16 : 1; // 16 Mux16 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX17 : 1; // 17 Mux17 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX18 : 1; // 18 Mux18 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX19 : 1; // 19 Mux19 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX20 : 1; // 20 Mux20 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX21 : 1; // 21 Mux21 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX22 : 1; // 22 Mux22 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX23 : 1; // 23 Mux23 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX24 : 1; // 24 Mux24 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX25 : 1; // 25 Mux25 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX26 : 1; // 26 Mux26 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX27 : 1; // 27 Mux27 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX28 : 1; // 28 Mux28 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX29 : 1; // 29 Mux29 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX30 : 1; // 30 Mux30 to drive OUTPUT6 of OUTPUT-XBAR
    vu32 MUX31 : 1; // 31 Mux31 to drive OUTPUT6 of OUTPUT-XBAR
};

union OUTPUT6MUXENABLE_REG
{
    vu32 all;
    struct OUTPUT6MUXENABLE_BITS bit;
};

struct OUTPUT7MUXENABLE_BITS
{                   // bits description
    vu32 MUX0  : 1; // 0 Mux0 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX1  : 1; // 1 Mux1 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX2  : 1; // 2 Mux2 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX3  : 1; // 3 Mux3 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX4  : 1; // 4 Mux4 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX5  : 1; // 5 Mux5 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX6  : 1; // 6 Mux6 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX7  : 1; // 7 Mux7 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX8  : 1; // 8 Mux8 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX9  : 1; // 9 Mux9 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX10 : 1; // 10 Mux10 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX11 : 1; // 11 Mux11 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX12 : 1; // 12 Mux12 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX13 : 1; // 13 Mux13 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX14 : 1; // 14 Mux14 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX15 : 1; // 15 Mux15 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX16 : 1; // 16 Mux16 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX17 : 1; // 17 Mux17 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX18 : 1; // 18 Mux18 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX19 : 1; // 19 Mux19 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX20 : 1; // 20 Mux20 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX21 : 1; // 21 Mux21 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX22 : 1; // 22 Mux22 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX23 : 1; // 23 Mux23 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX24 : 1; // 24 Mux24 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX25 : 1; // 25 Mux25 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX26 : 1; // 26 Mux26 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX27 : 1; // 27 Mux27 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX28 : 1; // 28 Mux28 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX29 : 1; // 29 Mux29 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX30 : 1; // 30 Mux30 to drive OUTPUT7 of OUTPUT-XBAR
    vu32 MUX31 : 1; // 31 Mux31 to drive OUTPUT7 of OUTPUT-XBAR
};

union OUTPUT7MUXENABLE_REG
{
    vu32 all;
    struct OUTPUT7MUXENABLE_BITS bit;
};

struct OUTPUT8MUXENABLE_BITS
{                   // bits description
    vu32 MUX0  : 1; // 0 Mux0 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX1  : 1; // 1 Mux1 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX2  : 1; // 2 Mux2 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX3  : 1; // 3 Mux3 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX4  : 1; // 4 Mux4 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX5  : 1; // 5 Mux5 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX6  : 1; // 6 Mux6 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX7  : 1; // 7 Mux7 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX8  : 1; // 8 Mux8 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX9  : 1; // 9 Mux9 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX10 : 1; // 10 Mux10 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX11 : 1; // 11 Mux11 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX12 : 1; // 12 Mux12 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX13 : 1; // 13 Mux13 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX14 : 1; // 14 Mux14 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX15 : 1; // 15 Mux15 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX16 : 1; // 16 Mux16 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX17 : 1; // 17 Mux17 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX18 : 1; // 18 Mux18 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX19 : 1; // 19 Mux19 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX20 : 1; // 20 Mux20 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX21 : 1; // 21 Mux21 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX22 : 1; // 22 Mux22 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX23 : 1; // 23 Mux23 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX24 : 1; // 24 Mux24 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX25 : 1; // 25 Mux25 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX26 : 1; // 26 Mux26 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX27 : 1; // 27 Mux27 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX28 : 1; // 28 Mux28 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX29 : 1; // 29 Mux29 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX30 : 1; // 30 Mux30 to drive OUTPUT8 of OUTPUT-XBAR
    vu32 MUX31 : 1; // 31 Mux31 to drive OUTPUT8 of OUTPUT-XBAR
};

union OUTPUT8MUXENABLE_REG
{
    vu32 all;
    struct OUTPUT8MUXENABLE_BITS bit;
};

struct OUTPUTLATCH_BITS
{                      // bits description
    vu32 OUTPUT1 : 1;  // 0 Records the OUTPUT1 of OUTPUT-XBAR
    vu32 OUTPUT2 : 1;  // 1 Records the OUTPUT2 of OUTPUT-XBAR
    vu32 OUTPUT3 : 1;  // 2 Records the OUTPUT3 of OUTPUT-XBAR
    vu32 OUTPUT4 : 1;  // 3 Records the OUTPUT4 of OUTPUT-XBAR
    vu32 OUTPUT5 : 1;  // 4 Records the OUTPUT5 of OUTPUT-XBAR
    vu32 OUTPUT6 : 1;  // 5 Records the OUTPUT6 of OUTPUT-XBAR
    vu32 OUTPUT7 : 1;  // 6 Records the OUTPUT7 of OUTPUT-XBAR
    vu32 OUTPUT8 : 1;  // 7 Records the OUTPUT8 of OUTPUT-XBAR
    vu32 rsvd1   : 8;  // 15:8 Reserved
    vu32 rsvd2   : 16; // 31:16 Reserved
};

union OUTPUTLATCH_REG
{
    vu32 all;
    struct OUTPUTLATCH_BITS bit;
};

struct OUTPUTLATCHCLR_BITS
{                      // bits description
    vu32 OUTPUT1 : 1;  // 0 Clears the Output-Latch for OUTPUT1 of OUTPUT-XBAR
    vu32 OUTPUT2 : 1;  // 1 Clears the Output-Latch for OUTPUT2 of OUTPUT-XBAR
    vu32 OUTPUT3 : 1;  // 2 Clears the Output-Latch for OUTPUT3 of OUTPUT-XBAR
    vu32 OUTPUT4 : 1;  // 3 Clears the Output-Latch for OUTPUT4 of OUTPUT-XBAR
    vu32 OUTPUT5 : 1;  // 4 Clears the Output-Latch for OUTPUT5 of OUTPUT-XBAR
    vu32 OUTPUT6 : 1;  // 5 Clears the Output-Latch for OUTPUT6 of OUTPUT-XBAR
    vu32 OUTPUT7 : 1;  // 6 Clears the Output-Latch for OUTPUT7 of OUTPUT-XBAR
    vu32 OUTPUT8 : 1;  // 7 Clears the Output-Latch for OUTPUT8 of OUTPUT-XBAR
    vu32 rsvd1   : 8;  // 15:8 Reserved
    vu32 rsvd2   : 16; // 31:16 Reserved
};

union OUTPUTLATCHCLR_REG
{
    vu32 all;
    struct OUTPUTLATCHCLR_BITS bit;
};

struct OUTPUTLATCHFRC_BITS
{                      // bits description
    vu32 OUTPUT1 : 1;  // 0 Sets the Output-Latch for OUTPUT1 of OUTPUT-XBAR
    vu32 OUTPUT2 : 1;  // 1 Sets the Output-Latch for OUTPUT2 of OUTPUT-XBAR
    vu32 OUTPUT3 : 1;  // 2 Sets the Output-Latch for OUTPUT3 of OUTPUT-XBAR
    vu32 OUTPUT4 : 1;  // 3 Sets the Output-Latch for OUTPUT4 of OUTPUT-XBAR
    vu32 OUTPUT5 : 1;  // 4 Sets the Output-Latch for OUTPUT5 of OUTPUT-XBAR
    vu32 OUTPUT6 : 1;  // 5 Sets the Output-Latch for OUTPUT6 of OUTPUT-XBAR
    vu32 OUTPUT7 : 1;  // 6 Sets the Output-Latch for OUTPUT7 of OUTPUT-XBAR
    vu32 OUTPUT8 : 1;  // 7 Sets the Output-Latch for OUTPUT8 of OUTPUT-XBAR
    vu32 rsvd1   : 8;  // 15:8 Reserved
    vu32 rsvd2   : 16; // 31:16 Reserved
};

union OUTPUTLATCHFRC_REG
{
    vu32 all;
    struct OUTPUTLATCHFRC_BITS bit;
};

struct OUTPUTLATCHENABLE_BITS
{                      // bits description
    vu32 OUTPUT1 : 1;  // 0 Selects the output latch to drive OUTPUT1 for OUTPUT-XBAR
    vu32 OUTPUT2 : 1;  // 1 Selects the output latch to drive OUTPUT2 for OUTPUT-XBAR
    vu32 OUTPUT3 : 1;  // 2 Selects the output latch to drive OUTPUT3 for OUTPUT-XBAR
    vu32 OUTPUT4 : 1;  // 3 Selects the output latch to drive OUTPUT4 for OUTPUT-XBAR
    vu32 OUTPUT5 : 1;  // 4 Selects the output latch to drive OUTPUT5 for OUTPUT-XBAR
    vu32 OUTPUT6 : 1;  // 5 Selects the output latch to drive OUTPUT6 for OUTPUT-XBAR
    vu32 OUTPUT7 : 1;  // 6 Selects the output latch to drive OUTPUT7 for OUTPUT-XBAR
    vu32 OUTPUT8 : 1;  // 7 Selects the output latch to drive OUTPUT8 for OUTPUT-XBAR
    vu32 rsvd1   : 8;  // 15:8 Reserved
    vu32 rsvd2   : 16; // 31:16 Reserved
};

union OUTPUTLATCHENABLE_REG
{
    vu32 all;
    struct OUTPUTLATCHENABLE_BITS bit;
};

struct OUTPUTINV_BITS
{                      // bits description
    vu32 OUTPUT1 : 1;  // 0 Selects polarity for OUTPUT1 of OUTPUT-XBAR
    vu32 OUTPUT2 : 1;  // 1 Selects polarity for OUTPUT2 of OUTPUT-XBAR
    vu32 OUTPUT3 : 1;  // 2 Selects polarity for OUTPUT3 of OUTPUT-XBAR
    vu32 OUTPUT4 : 1;  // 3 Selects polarity for OUTPUT4 of OUTPUT-XBAR
    vu32 OUTPUT5 : 1;  // 4 Selects polarity for OUTPUT5 of OUTPUT-XBAR
    vu32 OUTPUT6 : 1;  // 5 Selects polarity for OUTPUT6 of OUTPUT-XBAR
    vu32 OUTPUT7 : 1;  // 6 Selects polarity for OUTPUT7 of OUTPUT-XBAR
    vu32 OUTPUT8 : 1;  // 7 Selects polarity for OUTPUT8 of OUTPUT-XBAR
    vu32 rsvd1   : 8;  // 15:8 Reserved
    vu32 rsvd2   : 16; // 31:16 Reserved
};

union OUTPUTINV_REG
{
    vu32 all;
    struct OUTPUTINV_BITS bit;
};

struct OUTPUTLOCK_BITS
{                    // bits description
    vu32 LOCK  : 1;  // 0 Locks the configuration for OUTPUT-XBAR
    vu32 rsvd1 : 15; // 15:1 Reserved
    vu32 KEY   : 16; // 31:16 Write Protection KEY
};

union OUTPUTLOCK_REG
{
    vu32 all;
    struct OUTPUTLOCK_BITS bit;
};

struct OUTPUT_XBAR_REGS
{
    union OUTPUT1MUX0TO15CFG_REG OUTPUT1MUX0TO15CFG;   // Output X-BAR Mux Configuration for Output 1
    union OUTPUT1MUX16TO31CFG_REG OUTPUT1MUX16TO31CFG; // Output X-BAR Mux Configuration for Output 1
    union OUTPUT2MUX0TO15CFG_REG OUTPUT2MUX0TO15CFG;   // Output X-BAR Mux Configuration for Output 2
    union OUTPUT2MUX16TO31CFG_REG OUTPUT2MUX16TO31CFG; // Output X-BAR Mux Configuration for Output 2
    union OUTPUT3MUX0TO15CFG_REG OUTPUT3MUX0TO15CFG;   // Output X-BAR Mux Configuration for Output 3
    union OUTPUT3MUX16TO31CFG_REG OUTPUT3MUX16TO31CFG; // Output X-BAR Mux Configuration for Output 3
    union OUTPUT4MUX0TO15CFG_REG OUTPUT4MUX0TO15CFG;   // Output X-BAR Mux Configuration for Output 4
    union OUTPUT4MUX16TO31CFG_REG OUTPUT4MUX16TO31CFG; // Output X-BAR Mux Configuration for Output 4
    union OUTPUT5MUX0TO15CFG_REG OUTPUT5MUX0TO15CFG;   // Output X-BAR Mux Configuration for Output 5
    union OUTPUT5MUX16TO31CFG_REG OUTPUT5MUX16TO31CFG; // Output X-BAR Mux Configuration for Output 5
    union OUTPUT6MUX0TO15CFG_REG OUTPUT6MUX0TO15CFG;   // Output X-BAR Mux Configuration for Output 6
    union OUTPUT6MUX16TO31CFG_REG OUTPUT6MUX16TO31CFG; // Output X-BAR Mux Configuration for Output 6
    union OUTPUT7MUX0TO15CFG_REG OUTPUT7MUX0TO15CFG;   // Output X-BAR Mux Configuration for Output 7
    union OUTPUT7MUX16TO31CFG_REG OUTPUT7MUX16TO31CFG; // Output X-BAR Mux Configuration for Output 7
    union OUTPUT8MUX0TO15CFG_REG OUTPUT8MUX0TO15CFG;   // Output X-BAR Mux Configuration for Output 8
    union OUTPUT8MUX16TO31CFG_REG OUTPUT8MUX16TO31CFG; // Output X-BAR Mux Configuration for Output 8
    union OUTPUT1MUXENABLE_REG OUTPUT1MUXENABLE;       // Output X-BAR Mux Enable  for Output 1
    union OUTPUT2MUXENABLE_REG OUTPUT2MUXENABLE;       // Output X-BAR Mux Enable  for Output 2
    union OUTPUT3MUXENABLE_REG OUTPUT3MUXENABLE;       // Output X-BAR Mux Enable  for Output 3
    union OUTPUT4MUXENABLE_REG OUTPUT4MUXENABLE;       // Output X-BAR Mux Enable  for Output 4
    union OUTPUT5MUXENABLE_REG OUTPUT5MUXENABLE;       // Output X-BAR Mux Enable  for Output 5
    union OUTPUT6MUXENABLE_REG OUTPUT6MUXENABLE;       // Output X-BAR Mux Enable  for Output 6
    union OUTPUT7MUXENABLE_REG OUTPUT7MUXENABLE;       // Output X-BAR Mux Enable  for Output 7
    union OUTPUT8MUXENABLE_REG OUTPUT8MUXENABLE;       // Output X-BAR Mux Enable  for Output 8
    union OUTPUTLATCH_REG OUTPUTLATCH;                 // Output X-BAR Output Latch
    union OUTPUTLATCHCLR_REG OUTPUTLATCHCLR;           // Output X-BAR Output Latch Clear
    union OUTPUTLATCHFRC_REG OUTPUTLATCHFRC;           // Output X-BAR Output Latch Clear
    union OUTPUTLATCHENABLE_REG OUTPUTLATCHENABLE;     // Output X-BAR Output Latch Enable
    union OUTPUTINV_REG OUTPUTINV;                     // Output X-BAR Output Inversion
    vu32 rsvd1[4];                                     // Reserved
    union OUTPUTLOCK_REG OUTPUTLOCK;                   // Output X-BAR Configuration Lock register
};

//---------------------------------------------------------------------------
// EPWM_XBAR Individual Register Bit Definitions:

struct TRIP4MUX0TO15CFG_BITS
{                   // bits description
    vu32 MUX0  : 2; // 1:0 Mux0 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX1  : 2; // 3:2 Mux1 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX2  : 2; // 5:4 Mux2 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX3  : 2; // 7:6 Mux3 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX4  : 2; // 9:8 Mux4 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX5  : 2; // 11:10 Mux5 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX6  : 2; // 13:12 Mux6 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX7  : 2; // 15:14 Mux7 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX8  : 2; // 17:16 Mux8 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX9  : 2; // 19:18 Mux9 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX10 : 2; // 21:20 Mux10 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX11 : 2; // 23:22 Mux11 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX12 : 2; // 25:24 Mux12 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX13 : 2; // 27:26 Mux13 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX14 : 2; // 29:28 Mux14 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX15 : 2; // 31:30 Mux15 Configuration for TRIP4 of EPWM-XBAR
};

union TRIP4MUX0TO15CFG_REG
{
    vu32 all;
    struct TRIP4MUX0TO15CFG_BITS bit;
};

struct TRIP4MUX16TO31CFG_BITS
{                   // bits description
    vu32 MUX16 : 2; // 1:0 Mux16 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX17 : 2; // 3:2 Mux17 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX18 : 2; // 5:4 Mux18 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX19 : 2; // 7:6 Mux19 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX20 : 2; // 9:8 Mux20 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX21 : 2; // 11:10 Mux21 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX22 : 2; // 13:12 Mux22 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX23 : 2; // 15:14 Mux23 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX24 : 2; // 17:16 Mux24 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX25 : 2; // 19:18 Mux25 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX26 : 2; // 21:20 Mux26 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX27 : 2; // 23:22 Mux27 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX28 : 2; // 25:24 Mux28 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX29 : 2; // 27:26 Mux29 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX30 : 2; // 29:28 Mux30 Configuration for TRIP4 of EPWM-XBAR
    vu32 MUX31 : 2; // 31:30 Mux31 Configuration for TRIP4 of EPWM-XBAR
};

union TRIP4MUX16TO31CFG_REG
{
    vu32 all;
    struct TRIP4MUX16TO31CFG_BITS bit;
};

struct TRIP5MUX0TO15CFG_BITS
{                   // bits description
    vu32 MUX0  : 2; // 1:0 Mux0 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX1  : 2; // 3:2 Mux1 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX2  : 2; // 5:4 Mux2 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX3  : 2; // 7:6 Mux3 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX4  : 2; // 9:8 Mux4 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX5  : 2; // 11:10 Mux5 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX6  : 2; // 13:12 Mux6 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX7  : 2; // 15:14 Mux7 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX8  : 2; // 17:16 Mux8 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX9  : 2; // 19:18 Mux9 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX10 : 2; // 21:20 Mux10 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX11 : 2; // 23:22 Mux11 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX12 : 2; // 25:24 Mux12 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX13 : 2; // 27:26 Mux13 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX14 : 2; // 29:28 Mux14 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX15 : 2; // 31:30 Mux15 Configuration for TRIP5 of EPWM-XBAR
};

union TRIP5MUX0TO15CFG_REG
{
    vu32 all;
    struct TRIP5MUX0TO15CFG_BITS bit;
};

struct TRIP5MUX16TO31CFG_BITS
{                   // bits description
    vu32 MUX16 : 2; // 1:0 Mux16 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX17 : 2; // 3:2 Mux17 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX18 : 2; // 5:4 Mux18 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX19 : 2; // 7:6 Mux19 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX20 : 2; // 9:8 Mux20 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX21 : 2; // 11:10 Mux21 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX22 : 2; // 13:12 Mux22 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX23 : 2; // 15:14 Mux23 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX24 : 2; // 17:16 Mux24 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX25 : 2; // 19:18 Mux25 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX26 : 2; // 21:20 Mux26 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX27 : 2; // 23:22 Mux27 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX28 : 2; // 25:24 Mux28 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX29 : 2; // 27:26 Mux29 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX30 : 2; // 29:28 Mux30 Configuration for TRIP5 of EPWM-XBAR
    vu32 MUX31 : 2; // 31:30 Mux31 Configuration for TRIP5 of EPWM-XBAR
};

union TRIP5MUX16TO31CFG_REG
{
    vu32 all;
    struct TRIP5MUX16TO31CFG_BITS bit;
};

struct TRIP7MUX0TO15CFG_BITS
{                   // bits description
    vu32 MUX0  : 2; // 1:0 Mux0 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX1  : 2; // 3:2 Mux1 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX2  : 2; // 5:4 Mux2 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX3  : 2; // 7:6 Mux3 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX4  : 2; // 9:8 Mux4 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX5  : 2; // 11:10 Mux5 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX6  : 2; // 13:12 Mux6 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX7  : 2; // 15:14 Mux7 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX8  : 2; // 17:16 Mux8 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX9  : 2; // 19:18 Mux9 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX10 : 2; // 21:20 Mux10 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX11 : 2; // 23:22 Mux11 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX12 : 2; // 25:24 Mux12 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX13 : 2; // 27:26 Mux13 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX14 : 2; // 29:28 Mux14 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX15 : 2; // 31:30 Mux15 Configuration for TRIP7 of EPWM-XBAR
};

union TRIP7MUX0TO15CFG_REG
{
    vu32 all;
    struct TRIP7MUX0TO15CFG_BITS bit;
};

struct TRIP7MUX16TO31CFG_BITS
{                   // bits description
    vu32 MUX16 : 2; // 1:0 Mux16 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX17 : 2; // 3:2 Mux17 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX18 : 2; // 5:4 Mux18 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX19 : 2; // 7:6 Mux19 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX20 : 2; // 9:8 Mux20 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX21 : 2; // 11:10 Mux21 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX22 : 2; // 13:12 Mux22 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX23 : 2; // 15:14 Mux23 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX24 : 2; // 17:16 Mux24 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX25 : 2; // 19:18 Mux25 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX26 : 2; // 21:20 Mux26 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX27 : 2; // 23:22 Mux27 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX28 : 2; // 25:24 Mux28 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX29 : 2; // 27:26 Mux29 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX30 : 2; // 29:28 Mux30 Configuration for TRIP7 of EPWM-XBAR
    vu32 MUX31 : 2; // 31:30 Mux31 Configuration for TRIP7 of EPWM-XBAR
};

union TRIP7MUX16TO31CFG_REG
{
    vu32 all;
    struct TRIP7MUX16TO31CFG_BITS bit;
};

struct TRIP8MUX0TO15CFG_BITS
{                   // bits description
    vu32 MUX0  : 2; // 1:0 Mux0 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX1  : 2; // 3:2 Mux1 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX2  : 2; // 5:4 Mux2 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX3  : 2; // 7:6 Mux3 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX4  : 2; // 9:8 Mux4 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX5  : 2; // 11:10 Mux5 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX6  : 2; // 13:12 Mux6 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX7  : 2; // 15:14 Mux7 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX8  : 2; // 17:16 Mux8 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX9  : 2; // 19:18 Mux9 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX10 : 2; // 21:20 Mux10 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX11 : 2; // 23:22 Mux11 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX12 : 2; // 25:24 Mux12 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX13 : 2; // 27:26 Mux13 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX14 : 2; // 29:28 Mux14 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX15 : 2; // 31:30 Mux15 Configuration for TRIP8 of EPWM-XBAR
};

union TRIP8MUX0TO15CFG_REG
{
    vu32 all;
    struct TRIP8MUX0TO15CFG_BITS bit;
};

struct TRIP8MUX16TO31CFG_BITS
{                   // bits description
    vu32 MUX16 : 2; // 1:0 Mux16 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX17 : 2; // 3:2 Mux17 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX18 : 2; // 5:4 Mux18 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX19 : 2; // 7:6 Mux19 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX20 : 2; // 9:8 Mux20 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX21 : 2; // 11:10 Mux21 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX22 : 2; // 13:12 Mux22 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX23 : 2; // 15:14 Mux23 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX24 : 2; // 17:16 Mux24 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX25 : 2; // 19:18 Mux25 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX26 : 2; // 21:20 Mux26 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX27 : 2; // 23:22 Mux27 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX28 : 2; // 25:24 Mux28 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX29 : 2; // 27:26 Mux29 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX30 : 2; // 29:28 Mux30 Configuration for TRIP8 of EPWM-XBAR
    vu32 MUX31 : 2; // 31:30 Mux31 Configuration for TRIP8 of EPWM-XBAR
};

union TRIP8MUX16TO31CFG_REG
{
    vu32 all;
    struct TRIP8MUX16TO31CFG_BITS bit;
};

struct TRIP9MUX0TO15CFG_BITS
{                   // bits description
    vu32 MUX0  : 2; // 1:0 Mux0 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX1  : 2; // 3:2 Mux1 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX2  : 2; // 5:4 Mux2 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX3  : 2; // 7:6 Mux3 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX4  : 2; // 9:8 Mux4 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX5  : 2; // 11:10 Mux5 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX6  : 2; // 13:12 Mux6 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX7  : 2; // 15:14 Mux7 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX8  : 2; // 17:16 Mux8 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX9  : 2; // 19:18 Mux9 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX10 : 2; // 21:20 Mux10 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX11 : 2; // 23:22 Mux11 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX12 : 2; // 25:24 Mux12 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX13 : 2; // 27:26 Mux13 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX14 : 2; // 29:28 Mux14 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX15 : 2; // 31:30 Mux15 Configuration for TRIP9 of EPWM-XBAR
};

union TRIP9MUX0TO15CFG_REG
{
    vu32 all;
    struct TRIP9MUX0TO15CFG_BITS bit;
};

struct TRIP9MUX16TO31CFG_BITS
{                   // bits description
    vu32 MUX16 : 2; // 1:0 Mux16 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX17 : 2; // 3:2 Mux17 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX18 : 2; // 5:4 Mux18 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX19 : 2; // 7:6 Mux19 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX20 : 2; // 9:8 Mux20 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX21 : 2; // 11:10 Mux21 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX22 : 2; // 13:12 Mux22 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX23 : 2; // 15:14 Mux23 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX24 : 2; // 17:16 Mux24 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX25 : 2; // 19:18 Mux25 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX26 : 2; // 21:20 Mux26 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX27 : 2; // 23:22 Mux27 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX28 : 2; // 25:24 Mux28 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX29 : 2; // 27:26 Mux29 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX30 : 2; // 29:28 Mux30 Configuration for TRIP9 of EPWM-XBAR
    vu32 MUX31 : 2; // 31:30 Mux31 Configuration for TRIP9 of EPWM-XBAR
};

union TRIP9MUX16TO31CFG_REG
{
    vu32 all;
    struct TRIP9MUX16TO31CFG_BITS bit;
};

struct TRIP10MUX0TO15CFG_BITS
{                   // bits description
    vu32 MUX0  : 2; // 1:0 Mux0 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX1  : 2; // 3:2 Mux1 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX2  : 2; // 5:4 Mux2 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX3  : 2; // 7:6 Mux3 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX4  : 2; // 9:8 Mux4 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX5  : 2; // 11:10 Mux5 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX6  : 2; // 13:12 Mux6 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX7  : 2; // 15:14 Mux7 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX8  : 2; // 17:16 Mux8 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX9  : 2; // 19:18 Mux9 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX10 : 2; // 21:20 Mux10 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX11 : 2; // 23:22 Mux11 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX12 : 2; // 25:24 Mux12 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX13 : 2; // 27:26 Mux13 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX14 : 2; // 29:28 Mux14 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX15 : 2; // 31:30 Mux15 Configuration for TRIP10 of EPWM-XBAR
};

union TRIP10MUX0TO15CFG_REG
{
    vu32 all;
    struct TRIP10MUX0TO15CFG_BITS bit;
};

struct TRIP10MUX16TO31CFG_BITS
{                   // bits description
    vu32 MUX16 : 2; // 1:0 Mux16 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX17 : 2; // 3:2 Mux17 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX18 : 2; // 5:4 Mux18 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX19 : 2; // 7:6 Mux19 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX20 : 2; // 9:8 Mux20 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX21 : 2; // 11:10 Mux21 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX22 : 2; // 13:12 Mux22 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX23 : 2; // 15:14 Mux23 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX24 : 2; // 17:16 Mux24 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX25 : 2; // 19:18 Mux25 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX26 : 2; // 21:20 Mux26 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX27 : 2; // 23:22 Mux27 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX28 : 2; // 25:24 Mux28 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX29 : 2; // 27:26 Mux29 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX30 : 2; // 29:28 Mux30 Configuration for TRIP10 of EPWM-XBAR
    vu32 MUX31 : 2; // 31:30 Mux31 Configuration for TRIP10 of EPWM-XBAR
};

union TRIP10MUX16TO31CFG_REG
{
    vu32 all;
    struct TRIP10MUX16TO31CFG_BITS bit;
};

struct TRIP11MUX0TO15CFG_BITS
{                   // bits description
    vu32 MUX0  : 2; // 1:0 Mux0 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX1  : 2; // 3:2 Mux1 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX2  : 2; // 5:4 Mux2 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX3  : 2; // 7:6 Mux3 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX4  : 2; // 9:8 Mux4 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX5  : 2; // 11:10 Mux5 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX6  : 2; // 13:12 Mux6 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX7  : 2; // 15:14 Mux7 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX8  : 2; // 17:16 Mux8 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX9  : 2; // 19:18 Mux9 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX10 : 2; // 21:20 Mux10 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX11 : 2; // 23:22 Mux11 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX12 : 2; // 25:24 Mux12 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX13 : 2; // 27:26 Mux13 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX14 : 2; // 29:28 Mux14 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX15 : 2; // 31:30 Mux15 Configuration for TRIP11 of EPWM-XBAR
};

union TRIP11MUX0TO15CFG_REG
{
    vu32 all;
    struct TRIP11MUX0TO15CFG_BITS bit;
};

struct TRIP11MUX16TO31CFG_BITS
{                   // bits description
    vu32 MUX16 : 2; // 1:0 Mux16 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX17 : 2; // 3:2 Mux17 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX18 : 2; // 5:4 Mux18 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX19 : 2; // 7:6 Mux19 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX20 : 2; // 9:8 Mux20 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX21 : 2; // 11:10 Mux21 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX22 : 2; // 13:12 Mux22 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX23 : 2; // 15:14 Mux23 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX24 : 2; // 17:16 Mux24 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX25 : 2; // 19:18 Mux25 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX26 : 2; // 21:20 Mux26 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX27 : 2; // 23:22 Mux27 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX28 : 2; // 25:24 Mux28 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX29 : 2; // 27:26 Mux29 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX30 : 2; // 29:28 Mux30 Configuration for TRIP11 of EPWM-XBAR
    vu32 MUX31 : 2; // 31:30 Mux31 Configuration for TRIP11 of EPWM-XBAR
};

union TRIP11MUX16TO31CFG_REG
{
    vu32 all;
    struct TRIP11MUX16TO31CFG_BITS bit;
};

struct TRIP12MUX0TO15CFG_BITS
{                   // bits description
    vu32 MUX0  : 2; // 1:0 Mux0 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX1  : 2; // 3:2 Mux1 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX2  : 2; // 5:4 Mux2 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX3  : 2; // 7:6 Mux3 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX4  : 2; // 9:8 Mux4 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX5  : 2; // 11:10 Mux5 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX6  : 2; // 13:12 Mux6 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX7  : 2; // 15:14 Mux7 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX8  : 2; // 17:16 Mux8 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX9  : 2; // 19:18 Mux9 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX10 : 2; // 21:20 Mux10 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX11 : 2; // 23:22 Mux11 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX12 : 2; // 25:24 Mux12 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX13 : 2; // 27:26 Mux13 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX14 : 2; // 29:28 Mux14 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX15 : 2; // 31:30 Mux15 Configuration for TRIP12 of EPWM-XBAR
};

union TRIP12MUX0TO15CFG_REG
{
    vu32 all;
    struct TRIP12MUX0TO15CFG_BITS bit;
};

struct TRIP12MUX16TO31CFG_BITS
{                   // bits description
    vu32 MUX16 : 2; // 1:0 Mux16 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX17 : 2; // 3:2 Mux17 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX18 : 2; // 5:4 Mux18 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX19 : 2; // 7:6 Mux19 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX20 : 2; // 9:8 Mux20 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX21 : 2; // 11:10 Mux21 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX22 : 2; // 13:12 Mux22 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX23 : 2; // 15:14 Mux23 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX24 : 2; // 17:16 Mux24 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX25 : 2; // 19:18 Mux25 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX26 : 2; // 21:20 Mux26 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX27 : 2; // 23:22 Mux27 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX28 : 2; // 25:24 Mux28 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX29 : 2; // 27:26 Mux29 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX30 : 2; // 29:28 Mux30 Configuration for TRIP12 of EPWM-XBAR
    vu32 MUX31 : 2; // 31:30 Mux31 Configuration for TRIP12 of EPWM-XBAR
};

union TRIP12MUX16TO31CFG_REG
{
    vu32 all;
    struct TRIP12MUX16TO31CFG_BITS bit;
};

struct TRIP4MUXENABLE_BITS
{                   // bits description
    vu32 MUX0  : 1; // 0 mux0 to drive TRIP4 of EPWM-XBAR
    vu32 MUX1  : 1; // 1 Mux1 to drive TRIP4 of EPWM-XBAR
    vu32 MUX2  : 1; // 2 Mux2 to drive TRIP4 of EPWM-XBAR
    vu32 MUX3  : 1; // 3 Mux3 to drive TRIP4 of EPWM-XBAR
    vu32 MUX4  : 1; // 4 Mux4 to drive TRIP4 of EPWM-XBAR
    vu32 MUX5  : 1; // 5 Mux5 to drive TRIP4 of EPWM-XBAR
    vu32 MUX6  : 1; // 6 Mux6 to drive TRIP4 of EPWM-XBAR
    vu32 MUX7  : 1; // 7 Mux7 to drive TRIP4 of EPWM-XBAR
    vu32 MUX8  : 1; // 8 Mux8 to drive TRIP4 of EPWM-XBAR
    vu32 MUX9  : 1; // 9 Mux9 to drive TRIP4 of EPWM-XBAR
    vu32 MUX10 : 1; // 10 Mux10 to drive TRIP4 of EPWM-XBAR
    vu32 MUX11 : 1; // 11 Mux11 to drive TRIP4 of EPWM-XBAR
    vu32 MUX12 : 1; // 12 Mux12 to drive TRIP4 of EPWM-XBAR
    vu32 MUX13 : 1; // 13 Mux13 to drive TRIP4 of EPWM-XBAR
    vu32 MUX14 : 1; // 14 Mux14 to drive TRIP4 of EPWM-XBAR
    vu32 MUX15 : 1; // 15 Mux15 to drive TRIP4 of EPWM-XBAR
    vu32 MUX16 : 1; // 16 Mux16 to drive TRIP4 of EPWM-XBAR
    vu32 MUX17 : 1; // 17 Mux17 to drive TRIP4 of EPWM-XBAR
    vu32 MUX18 : 1; // 18 Mux18 to drive TRIP4 of EPWM-XBAR
    vu32 MUX19 : 1; // 19 Mux19 to drive TRIP4 of EPWM-XBAR
    vu32 MUX20 : 1; // 20 Mux20 to drive TRIP4 of EPWM-XBAR
    vu32 MUX21 : 1; // 21 Mux21 to drive TRIP4 of EPWM-XBAR
    vu32 MUX22 : 1; // 22 Mux22 to drive TRIP4 of EPWM-XBAR
    vu32 MUX23 : 1; // 23 Mux23 to drive TRIP4 of EPWM-XBAR
    vu32 MUX24 : 1; // 24 Mux24 to drive TRIP4 of EPWM-XBAR
    vu32 MUX25 : 1; // 25 Mux25 to drive TRIP4 of EPWM-XBAR
    vu32 MUX26 : 1; // 26 Mux26 to drive TRIP4 of EPWM-XBAR
    vu32 MUX27 : 1; // 27 Mux27 to drive TRIP4 of EPWM-XBAR
    vu32 MUX28 : 1; // 28 Mux28 to drive TRIP4 of EPWM-XBAR
    vu32 MUX29 : 1; // 29 Mux29 to drive TRIP4 of EPWM-XBAR
    vu32 MUX30 : 1; // 30 Mux30 to drive TRIP4 of EPWM-XBAR
    vu32 MUX31 : 1; // 31 Mux31 to drive TRIP4 of EPWM-XBAR
};

union TRIP4MUXENABLE_REG
{
    vu32 all;
    struct TRIP4MUXENABLE_BITS bit;
};

struct TRIP5MUXENABLE_BITS
{                   // bits description
    vu32 MUX0  : 1; // 0 mux0 to drive TRIP5 of EPWM-XBAR
    vu32 MUX1  : 1; // 1 Mux1 to drive TRIP5 of EPWM-XBAR
    vu32 MUX2  : 1; // 2 Mux2 to drive TRIP5 of EPWM-XBAR
    vu32 MUX3  : 1; // 3 Mux3 to drive TRIP5 of EPWM-XBAR
    vu32 MUX4  : 1; // 4 Mux4 to drive TRIP5 of EPWM-XBAR
    vu32 MUX5  : 1; // 5 Mux5 to drive TRIP5 of EPWM-XBAR
    vu32 MUX6  : 1; // 6 Mux6 to drive TRIP5 of EPWM-XBAR
    vu32 MUX7  : 1; // 7 Mux7 to drive TRIP5 of EPWM-XBAR
    vu32 MUX8  : 1; // 8 Mux8 to drive TRIP5 of EPWM-XBAR
    vu32 MUX9  : 1; // 9 Mux9 to drive TRIP5 of EPWM-XBAR
    vu32 MUX10 : 1; // 10 Mux10 to drive TRIP5 of EPWM-XBAR
    vu32 MUX11 : 1; // 11 Mux11 to drive TRIP5 of EPWM-XBAR
    vu32 MUX12 : 1; // 12 Mux12 to drive TRIP5 of EPWM-XBAR
    vu32 MUX13 : 1; // 13 Mux13 to drive TRIP5 of EPWM-XBAR
    vu32 MUX14 : 1; // 14 Mux14 to drive TRIP5 of EPWM-XBAR
    vu32 MUX15 : 1; // 15 Mux15 to drive TRIP5 of EPWM-XBAR
    vu32 MUX16 : 1; // 16 Mux16 to drive TRIP5 of EPWM-XBAR
    vu32 MUX17 : 1; // 17 Mux17 to drive TRIP5 of EPWM-XBAR
    vu32 MUX18 : 1; // 18 Mux18 to drive TRIP5 of EPWM-XBAR
    vu32 MUX19 : 1; // 19 Mux19 to drive TRIP5 of EPWM-XBAR
    vu32 MUX20 : 1; // 20 Mux20 to drive TRIP5 of EPWM-XBAR
    vu32 MUX21 : 1; // 21 Mux21 to drive TRIP5 of EPWM-XBAR
    vu32 MUX22 : 1; // 22 Mux22 to drive TRIP5 of EPWM-XBAR
    vu32 MUX23 : 1; // 23 Mux23 to drive TRIP5 of EPWM-XBAR
    vu32 MUX24 : 1; // 24 Mux24 to drive TRIP5 of EPWM-XBAR
    vu32 MUX25 : 1; // 25 Mux25 to drive TRIP5 of EPWM-XBAR
    vu32 MUX26 : 1; // 26 Mux26 to drive TRIP5 of EPWM-XBAR
    vu32 MUX27 : 1; // 27 Mux27 to drive TRIP5 of EPWM-XBAR
    vu32 MUX28 : 1; // 28 Mux28 to drive TRIP5 of EPWM-XBAR
    vu32 MUX29 : 1; // 29 Mux29 to drive TRIP5 of EPWM-XBAR
    vu32 MUX30 : 1; // 30 Mux30 to drive TRIP5 of EPWM-XBAR
    vu32 MUX31 : 1; // 31 Mux31 to drive TRIP5 of EPWM-XBAR
};

union TRIP5MUXENABLE_REG
{
    vu32 all;
    struct TRIP5MUXENABLE_BITS bit;
};

struct TRIP7MUXENABLE_BITS
{                   // bits description
    vu32 MUX0  : 1; // 0 mux0 to drive TRIP7 of EPWM-XBAR
    vu32 MUX1  : 1; // 1 Mux1 to drive TRIP7 of EPWM-XBAR
    vu32 MUX2  : 1; // 2 Mux2 to drive TRIP7 of EPWM-XBAR
    vu32 MUX3  : 1; // 3 Mux3 to drive TRIP7 of EPWM-XBAR
    vu32 MUX4  : 1; // 4 Mux4 to drive TRIP7 of EPWM-XBAR
    vu32 MUX5  : 1; // 5 Mux5 to drive TRIP7 of EPWM-XBAR
    vu32 MUX6  : 1; // 6 Mux6 to drive TRIP7 of EPWM-XBAR
    vu32 MUX7  : 1; // 7 Mux7 to drive TRIP7 of EPWM-XBAR
    vu32 MUX8  : 1; // 8 Mux8 to drive TRIP7 of EPWM-XBAR
    vu32 MUX9  : 1; // 9 Mux9 to drive TRIP7 of EPWM-XBAR
    vu32 MUX10 : 1; // 10 Mux10 to drive TRIP7 of EPWM-XBAR
    vu32 MUX11 : 1; // 11 Mux11 to drive TRIP7 of EPWM-XBAR
    vu32 MUX12 : 1; // 12 Mux12 to drive TRIP7 of EPWM-XBAR
    vu32 MUX13 : 1; // 13 Mux13 to drive TRIP7 of EPWM-XBAR
    vu32 MUX14 : 1; // 14 Mux14 to drive TRIP7 of EPWM-XBAR
    vu32 MUX15 : 1; // 15 Mux15 to drive TRIP7 of EPWM-XBAR
    vu32 MUX16 : 1; // 16 Mux16 to drive TRIP7 of EPWM-XBAR
    vu32 MUX17 : 1; // 17 Mux17 to drive TRIP7 of EPWM-XBAR
    vu32 MUX18 : 1; // 18 Mux18 to drive TRIP7 of EPWM-XBAR
    vu32 MUX19 : 1; // 19 Mux19 to drive TRIP7 of EPWM-XBAR
    vu32 MUX20 : 1; // 20 Mux20 to drive TRIP7 of EPWM-XBAR
    vu32 MUX21 : 1; // 21 Mux21 to drive TRIP7 of EPWM-XBAR
    vu32 MUX22 : 1; // 22 Mux22 to drive TRIP7 of EPWM-XBAR
    vu32 MUX23 : 1; // 23 Mux23 to drive TRIP7 of EPWM-XBAR
    vu32 MUX24 : 1; // 24 Mux24 to drive TRIP7 of EPWM-XBAR
    vu32 MUX25 : 1; // 25 Mux25 to drive TRIP7 of EPWM-XBAR
    vu32 MUX26 : 1; // 26 Mux26 to drive TRIP7 of EPWM-XBAR
    vu32 MUX27 : 1; // 27 Mux27 to drive TRIP7 of EPWM-XBAR
    vu32 MUX28 : 1; // 28 Mux28 to drive TRIP7 of EPWM-XBAR
    vu32 MUX29 : 1; // 29 Mux29 to drive TRIP7 of EPWM-XBAR
    vu32 MUX30 : 1; // 30 Mux30 to drive TRIP7 of EPWM-XBAR
    vu32 MUX31 : 1; // 31 Mux31 to drive TRIP7 of EPWM-XBAR
};

union TRIP7MUXENABLE_REG
{
    vu32 all;
    struct TRIP7MUXENABLE_BITS bit;
};

struct TRIP8MUXENABLE_BITS
{                   // bits description
    vu32 MUX0  : 1; // 0 mux0 to drive TRIP8 of EPWM-XBAR
    vu32 MUX1  : 1; // 1 Mux1 to drive TRIP8 of EPWM-XBAR
    vu32 MUX2  : 1; // 2 Mux2 to drive TRIP8 of EPWM-XBAR
    vu32 MUX3  : 1; // 3 Mux3 to drive TRIP8 of EPWM-XBAR
    vu32 MUX4  : 1; // 4 Mux4 to drive TRIP8 of EPWM-XBAR
    vu32 MUX5  : 1; // 5 Mux5 to drive TRIP8 of EPWM-XBAR
    vu32 MUX6  : 1; // 6 Mux6 to drive TRIP8 of EPWM-XBAR
    vu32 MUX7  : 1; // 7 Mux7 to drive TRIP8 of EPWM-XBAR
    vu32 MUX8  : 1; // 8 Mux8 to drive TRIP8 of EPWM-XBAR
    vu32 MUX9  : 1; // 9 Mux9 to drive TRIP8 of EPWM-XBAR
    vu32 MUX10 : 1; // 10 Mux10 to drive TRIP8 of EPWM-XBAR
    vu32 MUX11 : 1; // 11 Mux11 to drive TRIP8 of EPWM-XBAR
    vu32 MUX12 : 1; // 12 Mux12 to drive TRIP8 of EPWM-XBAR
    vu32 MUX13 : 1; // 13 Mux13 to drive TRIP8 of EPWM-XBAR
    vu32 MUX14 : 1; // 14 Mux14 to drive TRIP8 of EPWM-XBAR
    vu32 MUX15 : 1; // 15 Mux15 to drive TRIP8 of EPWM-XBAR
    vu32 MUX16 : 1; // 16 Mux16 to drive TRIP8 of EPWM-XBAR
    vu32 MUX17 : 1; // 17 Mux17 to drive TRIP8 of EPWM-XBAR
    vu32 MUX18 : 1; // 18 Mux18 to drive TRIP8 of EPWM-XBAR
    vu32 MUX19 : 1; // 19 Mux19 to drive TRIP8 of EPWM-XBAR
    vu32 MUX20 : 1; // 20 Mux20 to drive TRIP8 of EPWM-XBAR
    vu32 MUX21 : 1; // 21 Mux21 to drive TRIP8 of EPWM-XBAR
    vu32 MUX22 : 1; // 22 Mux22 to drive TRIP8 of EPWM-XBAR
    vu32 MUX23 : 1; // 23 Mux23 to drive TRIP8 of EPWM-XBAR
    vu32 MUX24 : 1; // 24 Mux24 to drive TRIP8 of EPWM-XBAR
    vu32 MUX25 : 1; // 25 Mux25 to drive TRIP8 of EPWM-XBAR
    vu32 MUX26 : 1; // 26 Mux26 to drive TRIP8 of EPWM-XBAR
    vu32 MUX27 : 1; // 27 Mux27 to drive TRIP8 of EPWM-XBAR
    vu32 MUX28 : 1; // 28 Mux28 to drive TRIP8 of EPWM-XBAR
    vu32 MUX29 : 1; // 29 Mux29 to drive TRIP8 of EPWM-XBAR
    vu32 MUX30 : 1; // 30 Mux30 to drive TRIP8 of EPWM-XBAR
    vu32 MUX31 : 1; // 31 Mux31 to drive TRIP8 of EPWM-XBAR
};

union TRIP8MUXENABLE_REG
{
    vu32 all;
    struct TRIP8MUXENABLE_BITS bit;
};

struct TRIP9MUXENABLE_BITS
{                   // bits description
    vu32 MUX0  : 1; // 0 mux0 to drive TRIP9 of EPWM-XBAR
    vu32 MUX1  : 1; // 1 Mux1 to drive TRIP9 of EPWM-XBAR
    vu32 MUX2  : 1; // 2 Mux2 to drive TRIP9 of EPWM-XBAR
    vu32 MUX3  : 1; // 3 Mux3 to drive TRIP9 of EPWM-XBAR
    vu32 MUX4  : 1; // 4 Mux4 to drive TRIP9 of EPWM-XBAR
    vu32 MUX5  : 1; // 5 Mux5 to drive TRIP9 of EPWM-XBAR
    vu32 MUX6  : 1; // 6 Mux6 to drive TRIP9 of EPWM-XBAR
    vu32 MUX7  : 1; // 7 Mux7 to drive TRIP9 of EPWM-XBAR
    vu32 MUX8  : 1; // 8 Mux8 to drive TRIP9 of EPWM-XBAR
    vu32 MUX9  : 1; // 9 Mux9 to drive TRIP9 of EPWM-XBAR
    vu32 MUX10 : 1; // 10 Mux10 to drive TRIP9 of EPWM-XBAR
    vu32 MUX11 : 1; // 11 Mux11 to drive TRIP9 of EPWM-XBAR
    vu32 MUX12 : 1; // 12 Mux12 to drive TRIP9 of EPWM-XBAR
    vu32 MUX13 : 1; // 13 Mux13 to drive TRIP9 of EPWM-XBAR
    vu32 MUX14 : 1; // 14 Mux14 to drive TRIP9 of EPWM-XBAR
    vu32 MUX15 : 1; // 15 Mux15 to drive TRIP9 of EPWM-XBAR
    vu32 MUX16 : 1; // 16 Mux16 to drive TRIP9 of EPWM-XBAR
    vu32 MUX17 : 1; // 17 Mux17 to drive TRIP9 of EPWM-XBAR
    vu32 MUX18 : 1; // 18 Mux18 to drive TRIP9 of EPWM-XBAR
    vu32 MUX19 : 1; // 19 Mux19 to drive TRIP9 of EPWM-XBAR
    vu32 MUX20 : 1; // 20 Mux20 to drive TRIP9 of EPWM-XBAR
    vu32 MUX21 : 1; // 21 Mux21 to drive TRIP9 of EPWM-XBAR
    vu32 MUX22 : 1; // 22 Mux22 to drive TRIP9 of EPWM-XBAR
    vu32 MUX23 : 1; // 23 Mux23 to drive TRIP9 of EPWM-XBAR
    vu32 MUX24 : 1; // 24 Mux24 to drive TRIP9 of EPWM-XBAR
    vu32 MUX25 : 1; // 25 Mux25 to drive TRIP9 of EPWM-XBAR
    vu32 MUX26 : 1; // 26 Mux26 to drive TRIP9 of EPWM-XBAR
    vu32 MUX27 : 1; // 27 Mux27 to drive TRIP9 of EPWM-XBAR
    vu32 MUX28 : 1; // 28 Mux28 to drive TRIP9 of EPWM-XBAR
    vu32 MUX29 : 1; // 29 Mux29 to drive TRIP9 of EPWM-XBAR
    vu32 MUX30 : 1; // 30 Mux30 to drive TRIP9 of EPWM-XBAR
    vu32 MUX31 : 1; // 31 Mux31 to drive TRIP9 of EPWM-XBAR
};

union TRIP9MUXENABLE_REG
{
    vu32 all;
    struct TRIP9MUXENABLE_BITS bit;
};

struct TRIP10MUXENABLE_BITS
{                   // bits description
    vu32 MUX0  : 1; // 0 mux0 to drive TRIP10 of EPWM-XBAR
    vu32 MUX1  : 1; // 1 Mux1 to drive TRIP10 of EPWM-XBAR
    vu32 MUX2  : 1; // 2 Mux2 to drive TRIP10 of EPWM-XBAR
    vu32 MUX3  : 1; // 3 Mux3 to drive TRIP10 of EPWM-XBAR
    vu32 MUX4  : 1; // 4 Mux4 to drive TRIP10 of EPWM-XBAR
    vu32 MUX5  : 1; // 5 Mux5 to drive TRIP10 of EPWM-XBAR
    vu32 MUX6  : 1; // 6 Mux6 to drive TRIP10 of EPWM-XBAR
    vu32 MUX7  : 1; // 7 Mux7 to drive TRIP10 of EPWM-XBAR
    vu32 MUX8  : 1; // 8 Mux8 to drive TRIP10 of EPWM-XBAR
    vu32 MUX9  : 1; // 9 Mux9 to drive TRIP10 of EPWM-XBAR
    vu32 MUX10 : 1; // 10 Mux10 to drive TRIP10 of EPWM-XBAR
    vu32 MUX11 : 1; // 11 Mux11 to drive TRIP10 of EPWM-XBAR
    vu32 MUX12 : 1; // 12 Mux12 to drive TRIP10 of EPWM-XBAR
    vu32 MUX13 : 1; // 13 Mux13 to drive TRIP10 of EPWM-XBAR
    vu32 MUX14 : 1; // 14 Mux14 to drive TRIP10 of EPWM-XBAR
    vu32 MUX15 : 1; // 15 Mux15 to drive TRIP10 of EPWM-XBAR
    vu32 MUX16 : 1; // 16 Mux16 to drive TRIP10 of EPWM-XBAR
    vu32 MUX17 : 1; // 17 Mux17 to drive TRIP10 of EPWM-XBAR
    vu32 MUX18 : 1; // 18 Mux18 to drive TRIP10 of EPWM-XBAR
    vu32 MUX19 : 1; // 19 Mux19 to drive TRIP10 of EPWM-XBAR
    vu32 MUX20 : 1; // 20 Mux20 to drive TRIP10 of EPWM-XBAR
    vu32 MUX21 : 1; // 21 Mux21 to drive TRIP10 of EPWM-XBAR
    vu32 MUX22 : 1; // 22 Mux22 to drive TRIP10 of EPWM-XBAR
    vu32 MUX23 : 1; // 23 Mux23 to drive TRIP10 of EPWM-XBAR
    vu32 MUX24 : 1; // 24 Mux24 to drive TRIP10 of EPWM-XBAR
    vu32 MUX25 : 1; // 25 Mux25 to drive TRIP10 of EPWM-XBAR
    vu32 MUX26 : 1; // 26 Mux26 to drive TRIP10 of EPWM-XBAR
    vu32 MUX27 : 1; // 27 Mux27 to drive TRIP10 of EPWM-XBAR
    vu32 MUX28 : 1; // 28 Mux28 to drive TRIP10 of EPWM-XBAR
    vu32 MUX29 : 1; // 29 Mux29 to drive TRIP10 of EPWM-XBAR
    vu32 MUX30 : 1; // 30 Mux30 to drive TRIP10 of EPWM-XBAR
    vu32 MUX31 : 1; // 31 Mux31 to drive TRIP10 of EPWM-XBAR
};

union TRIP10MUXENABLE_REG
{
    vu32 all;
    struct TRIP10MUXENABLE_BITS bit;
};

struct TRIP11MUXENABLE_BITS
{                   // bits description
    vu32 MUX0  : 1; // 0 mux0 to drive TRIP11 of EPWM-XBAR
    vu32 MUX1  : 1; // 1 Mux1 to drive TRIP11 of EPWM-XBAR
    vu32 MUX2  : 1; // 2 Mux2 to drive TRIP11 of EPWM-XBAR
    vu32 MUX3  : 1; // 3 Mux3 to drive TRIP11 of EPWM-XBAR
    vu32 MUX4  : 1; // 4 Mux4 to drive TRIP11 of EPWM-XBAR
    vu32 MUX5  : 1; // 5 Mux5 to drive TRIP11 of EPWM-XBAR
    vu32 MUX6  : 1; // 6 Mux6 to drive TRIP11 of EPWM-XBAR
    vu32 MUX7  : 1; // 7 Mux7 to drive TRIP11 of EPWM-XBAR
    vu32 MUX8  : 1; // 8 Mux8 to drive TRIP11 of EPWM-XBAR
    vu32 MUX9  : 1; // 9 Mux9 to drive TRIP11 of EPWM-XBAR
    vu32 MUX10 : 1; // 10 Mux10 to drive TRIP11 of EPWM-XBAR
    vu32 MUX11 : 1; // 11 Mux11 to drive TRIP11 of EPWM-XBAR
    vu32 MUX12 : 1; // 12 Mux12 to drive TRIP11 of EPWM-XBAR
    vu32 MUX13 : 1; // 13 Mux13 to drive TRIP11 of EPWM-XBAR
    vu32 MUX14 : 1; // 14 Mux14 to drive TRIP11 of EPWM-XBAR
    vu32 MUX15 : 1; // 15 Mux15 to drive TRIP11 of EPWM-XBAR
    vu32 MUX16 : 1; // 16 Mux16 to drive TRIP11 of EPWM-XBAR
    vu32 MUX17 : 1; // 17 Mux17 to drive TRIP11 of EPWM-XBAR
    vu32 MUX18 : 1; // 18 Mux18 to drive TRIP11 of EPWM-XBAR
    vu32 MUX19 : 1; // 19 Mux19 to drive TRIP11 of EPWM-XBAR
    vu32 MUX20 : 1; // 20 Mux20 to drive TRIP11 of EPWM-XBAR
    vu32 MUX21 : 1; // 21 Mux21 to drive TRIP11 of EPWM-XBAR
    vu32 MUX22 : 1; // 22 Mux22 to drive TRIP11 of EPWM-XBAR
    vu32 MUX23 : 1; // 23 Mux23 to drive TRIP11 of EPWM-XBAR
    vu32 MUX24 : 1; // 24 Mux24 to drive TRIP11 of EPWM-XBAR
    vu32 MUX25 : 1; // 25 Mux25 to drive TRIP11 of EPWM-XBAR
    vu32 MUX26 : 1; // 26 Mux26 to drive TRIP11 of EPWM-XBAR
    vu32 MUX27 : 1; // 27 Mux27 to drive TRIP11 of EPWM-XBAR
    vu32 MUX28 : 1; // 28 Mux28 to drive TRIP11 of EPWM-XBAR
    vu32 MUX29 : 1; // 29 Mux29 to drive TRIP11 of EPWM-XBAR
    vu32 MUX30 : 1; // 30 Mux30 to drive TRIP11 of EPWM-XBAR
    vu32 MUX31 : 1; // 31 Mux31 to drive TRIP11 of EPWM-XBAR
};

union TRIP11MUXENABLE_REG
{
    vu32 all;
    struct TRIP11MUXENABLE_BITS bit;
};

struct TRIP12MUXENABLE_BITS
{                   // bits description
    vu32 MUX0  : 1; // 0 mux0 to drive TRIP12 of EPWM-XBAR
    vu32 MUX1  : 1; // 1 Mux1 to drive TRIP12 of EPWM-XBAR
    vu32 MUX2  : 1; // 2 Mux2 to drive TRIP12 of EPWM-XBAR
    vu32 MUX3  : 1; // 3 Mux3 to drive TRIP12 of EPWM-XBAR
    vu32 MUX4  : 1; // 4 Mux4 to drive TRIP12 of EPWM-XBAR
    vu32 MUX5  : 1; // 5 Mux5 to drive TRIP12 of EPWM-XBAR
    vu32 MUX6  : 1; // 6 Mux6 to drive TRIP12 of EPWM-XBAR
    vu32 MUX7  : 1; // 7 Mux7 to drive TRIP12 of EPWM-XBAR
    vu32 MUX8  : 1; // 8 Mux8 to drive TRIP12 of EPWM-XBAR
    vu32 MUX9  : 1; // 9 Mux9 to drive TRIP12 of EPWM-XBAR
    vu32 MUX10 : 1; // 10 Mux10 to drive TRIP12 of EPWM-XBAR
    vu32 MUX11 : 1; // 11 Mux11 to drive TRIP12 of EPWM-XBAR
    vu32 MUX12 : 1; // 12 Mux12 to drive TRIP12 of EPWM-XBAR
    vu32 MUX13 : 1; // 13 Mux13 to drive TRIP12 of EPWM-XBAR
    vu32 MUX14 : 1; // 14 Mux14 to drive TRIP12 of EPWM-XBAR
    vu32 MUX15 : 1; // 15 Mux15 to drive TRIP12 of EPWM-XBAR
    vu32 MUX16 : 1; // 16 Mux16 to drive TRIP12 of EPWM-XBAR
    vu32 MUX17 : 1; // 17 Mux17 to drive TRIP12 of EPWM-XBAR
    vu32 MUX18 : 1; // 18 Mux18 to drive TRIP12 of EPWM-XBAR
    vu32 MUX19 : 1; // 19 Mux19 to drive TRIP12 of EPWM-XBAR
    vu32 MUX20 : 1; // 20 Mux20 to drive TRIP12 of EPWM-XBAR
    vu32 MUX21 : 1; // 21 Mux21 to drive TRIP12 of EPWM-XBAR
    vu32 MUX22 : 1; // 22 Mux22 to drive TRIP12 of EPWM-XBAR
    vu32 MUX23 : 1; // 23 Mux23 to drive TRIP12 of EPWM-XBAR
    vu32 MUX24 : 1; // 24 Mux24 to drive TRIP12 of EPWM-XBAR
    vu32 MUX25 : 1; // 25 Mux25 to drive TRIP12 of EPWM-XBAR
    vu32 MUX26 : 1; // 26 Mux26 to drive TRIP12 of EPWM-XBAR
    vu32 MUX27 : 1; // 27 Mux27 to drive TRIP12 of EPWM-XBAR
    vu32 MUX28 : 1; // 28 Mux28 to drive TRIP12 of EPWM-XBAR
    vu32 MUX29 : 1; // 29 Mux29 to drive TRIP12 of EPWM-XBAR
    vu32 MUX30 : 1; // 30 Mux30 to drive TRIP12 of EPWM-XBAR
    vu32 MUX31 : 1; // 31 Mux31 to drive TRIP12 of EPWM-XBAR
};

union TRIP12MUXENABLE_REG
{
    vu32 all;
    struct TRIP12MUXENABLE_BITS bit;
};

struct TRIPOUTINV_BITS
{                     // bits description
    vu32 TRIP4  : 1;  // 0 Selects polarity for TRIP4 of EPWM-XBAR
    vu32 TRIP5  : 1;  // 1 Selects polarity for TRIP5 of EPWM-XBAR
    vu32 TRIP7  : 1;  // 2 Selects polarity for TRIP7 of EPWM-XBAR
    vu32 TRIP8  : 1;  // 3 Selects polarity for TRIP8 of EPWM-XBAR
    vu32 TRIP9  : 1;  // 4 Selects polarity for TRIP9 of EPWM-XBAR
    vu32 TRIP10 : 1;  // 5 Selects polarity for TRIP10 of EPWM-XBAR
    vu32 TRIP11 : 1;  // 6 Selects polarity for TRIP11 of EPWM-XBAR
    vu32 TRIP12 : 1;  // 7 Selects polarity for TRIP12 of EPWM-XBAR
    vu32 rsvd1  : 8;  // 15:8 Reserved
    vu32 rsvd2  : 16; // 31:16 Reserved
};

union TRIPOUTINV_REG
{
    vu32 all;
    struct TRIPOUTINV_BITS bit;
};

struct TRIPLOCK_BITS
{                    // bits description
    vu32 LOCK  : 1;  // 0 Locks the configuration for EPWM-XBAR
    vu32 rsvd1 : 15; // 15:1 Reserved
    vu32 KEY   : 16; // 31:16 Write protection KEY
};

union TRIPLOCK_REG
{
    vu32 all;
    struct TRIPLOCK_BITS bit;
};

struct EPWM_XBAR_REGS
{
    union TRIP4MUX0TO15CFG_REG TRIP4MUX0TO15CFG;     // ePWM XBAR Mux Configuration for TRIP4		0x00
    union TRIP4MUX16TO31CFG_REG TRIP4MUX16TO31CFG;   // ePWM XBAR Mux Configuration for TRIP4		0x04
    union TRIP5MUX0TO15CFG_REG TRIP5MUX0TO15CFG;     // ePWM XBAR Mux Configuration for TRIP5		0x08
    union TRIP5MUX16TO31CFG_REG TRIP5MUX16TO31CFG;   // ePWM XBAR Mux Configuration for TRIP5		0x0c
    union TRIP7MUX0TO15CFG_REG TRIP7MUX0TO15CFG;     // ePWM XBAR Mux Configuration for TRIP7		0x10
    union TRIP7MUX16TO31CFG_REG TRIP7MUX16TO31CFG;   // ePWM XBAR Mux Configuration for TRIP7		0x14
    union TRIP8MUX0TO15CFG_REG TRIP8MUX0TO15CFG;     // ePWM XBAR Mux Configuration for TRIP8		0x18
    union TRIP8MUX16TO31CFG_REG TRIP8MUX16TO31CFG;   // ePWM XBAR Mux Configuration for TRIP8		0x1c
    union TRIP9MUX0TO15CFG_REG TRIP9MUX0TO15CFG;     // ePWM XBAR Mux Configuration for TRIP9		0x20
    union TRIP9MUX16TO31CFG_REG TRIP9MUX16TO31CFG;   // ePWM XBAR Mux Configuration for TRIP9		0x24
    union TRIP10MUX0TO15CFG_REG TRIP10MUX0TO15CFG;   // ePWM XBAR Mux Configuration for TRIP10		0x28
    union TRIP10MUX16TO31CFG_REG TRIP10MUX16TO31CFG; // ePWM XBAR Mux Configuration for TRIP10		0x2C
    union TRIP11MUX0TO15CFG_REG TRIP11MUX0TO15CFG;   // ePWM XBAR Mux Configuration for TRIP11		0x30
    union TRIP11MUX16TO31CFG_REG TRIP11MUX16TO31CFG; // ePWM XBAR Mux Configuration for TRIP11		0x34
    union TRIP12MUX0TO15CFG_REG TRIP12MUX0TO15CFG;   // ePWM XBAR Mux Configuration for TRIP12		0x38
    union TRIP12MUX16TO31CFG_REG TRIP12MUX16TO31CFG; // ePWM XBAR Mux Configuration for TRIP12		0x3c
    union TRIP4MUXENABLE_REG TRIP4MUXENABLE;         // ePWM XBAR Mux Enable for TRIP4
    union TRIP5MUXENABLE_REG TRIP5MUXENABLE;         // ePWM XBAR Mux Enable for TRIP5
    union TRIP7MUXENABLE_REG TRIP7MUXENABLE;         // ePWM XBAR Mux Enable for TRIP7
    union TRIP8MUXENABLE_REG TRIP8MUXENABLE;         // ePWM XBAR Mux Enable for TRIP8
    union TRIP9MUXENABLE_REG TRIP9MUXENABLE;         // ePWM XBAR Mux Enable for TRIP9
    union TRIP10MUXENABLE_REG TRIP10MUXENABLE;       // ePWM XBAR Mux Enable for TRIP10
    union TRIP11MUXENABLE_REG TRIP11MUXENABLE;       // ePWM XBAR Mux Enable for TRIP11
    union TRIP12MUXENABLE_REG TRIP12MUXENABLE;       // ePWM XBAR Mux Enable for TRIP12
    vu32 rsvd1[8];                                   // Reserved
    union TRIPOUTINV_REG TRIPOUTINV;                 // ePWM XBAR Output Inversion Register
    vu32 rsvd2[4];                                   // Reserved
    union TRIPLOCK_REG TRIPLOCK;                     // ePWM XBAR Configuration Lock register
};

//---------------------------------------------------------------------------
// EPWM_XBAR External References & Function Declarations:
#define EPwmXbarRegs ((struct EPWM_XBAR_REGS *)EPWMXBAR_BASE)

struct XBAR1_BITS
{                        // bits description
    vu32 INPUT1     : 1; // 0 Input Flag for INPUT1 Signal
    vu32 INPUT2     : 1; // 1 Input Flag for INPUT2 Signal
    vu32 INPUT3     : 1; // 2 Input Flag for INPUT3 Signal
    vu32 INPUT4     : 1; // 3 Input Flag for INPUT4 Signal
    vu32 INPUT5     : 1; // 4 Input Flag for INPUT5 Signal
    vu32 INPUT6     : 1; // 5 Input Flag for INPUT6 Signal
    vu32 ADCSOCA    : 1; // 6 Input Flag for ADCSOCA Signal
    vu32 ADCSOCB    : 1; // 7 Input Flag for ADCSOCB Signal
    vu32 INPUT7     : 1; // 8 Input Flag for INPUT7 Signal
    vu32 INPUT8     : 1; // 9 Input Flag for INPUT8 Signal
    vu32 INPUT9     : 1; // 10 Input Flag for INPUT9 Signal
    vu32 INPUT10    : 1; // 11 Input Flag for INPUT10\ Signal
    vu32 INPUT11    : 1; // 12 Input Flag for INPUT11 Signal
    vu32 INPUT12    : 1; // 13 Input Flag for INPUT12 Signal
    vu32 INPUT13    : 1; // 14 Input Flag for INPUT13 Signal
    vu32 INPUT14    : 1; // 15 Input Flag for INPUT14 Signal
    vu32 ECAP1_OUT  : 1; // 16 Input Flag for ECAP1.OUT Signal
    vu32 ECAP2_OUT  : 1; // 17 Input Flag for ECAP2.OUT Signal
    vu32 ECAP3_OUT  : 1; // 18 Input Flag for ECAP3.OUT Signal
    vu32 ECAP4_OUT  : 1; // 19 Input Flag for ECAP4.OUT Signal
    vu32 ECAP5_OUT  : 1; // 20 Input Flag for ECAP5.OUT Signal
    vu32 ECAP6_OUT  : 1; // 21 Input Flag for ECAP6.OUT Signal
    vu32 EXTSYNCOUT : 1; // 22 Input Flag for EXTSYNCOUT Signal
    vu32 ECAP7_OUT  : 1; // 23 Input Flag for ECAP6.OUT Signal
    vu32 ERRORSTS   : 1; // 24 Input Flag for ERRORSTS Signal
};

union XBAR1_REG
{
    vu32 all;
    struct XBAR1_BITS bit;
};

struct XBAR2_BITS
{                             // bits description
    vu32 ADCAEVT1        : 1; // 0 Input Flag for ADCAEVT1 Signal
    vu32 ADCBEVT1        : 1; // 1 Input Flag for ADCBEVT1 Signal
    vu32 ADCCEVT1        : 1; // 2 Input Flag for ADCCEVT1 Signal
    vu32 ADCAEVT2        : 1; // 3 Input Flag for ADCAEVT2 Signal
    vu32 ADCBEVT2        : 1; // 4 Input Flag for ADCBEVT2 Signal
    vu32 ADCCEVT2        : 1; // 5 Input Flag for ADCCEVT2 Signal
    vu32 ADCAEVT3        : 1; // 6 Input Flag for ADCAEVT3 Signal
    vu32 ADCBEVT3        : 1; // 7 Input Flag for ADCBEVT3 Signal
    vu32 ADCCEVT3        : 1; // 8 Input Flag for ADCCEVT3 Signal
    vu32 ADCAEVT4        : 1; // 9 Input Flag for ADCAEVT4 Signal
    vu32 ADCBEVT4        : 1; // 10 Input Flag for ADCBEVT4 Signal
    vu32 ADCCEVT4        : 1; // 11 Input Flag for ADCCEVT4 Signal
    vu32 SD1FLT1_COMPH   : 1; // 12 Input Flag for SD1FLT1.COMPH Signal
    vu32 SD1FLT1_COMPL   : 1; // 13 Input Flag for SD1FLT1.COMPL Signal
    vu32 SD1FLT1_COMPZ   : 1; // 14 Input Flag for SD1FLT1.COMPZ Signal
    vu32 SD1FLT1_COMPH_L : 1; // 15 Input Flag for SD1FLT1.COMPH OR SD1FLT1.COMPL Signal
    vu32 SD1FLT2_COMPH   : 1; // 16 Input Flag for SD1FLT2.COMPH Signal
    vu32 SD1FLT2_COMPL   : 1; // 17 Input Flag for SD1FLT2.COMPL Signal
    vu32 SD1FLT2_COMPZ   : 1; // 18 Input Flag for SD1FLT2.COMPZ Signal
    vu32 SD1FLT2_COMPH_L : 1; // 19 Input Flag for SD1FLT2.COMPH OR SD1FLT1.COMPL Signal
    vu32 SD1FLT3_COMPH   : 1; // 20 Input Flag for SD1FLT3.COMPH Signal
    vu32 SD1FLT3_COMPL   : 1; // 21 Input Flag for SD1FLT3.COMPL Signal
    vu32 SD1FLT3_COMPZ   : 1; // 22 Input Flag for SD1FLT3.COMPZ Signal
    vu32 SD1FLT3_COMPH_L : 1; // 23 Input Flag for SD1FLT3.COMPH OR SD1FLT1.COMPL Signal
    vu32 SD1FLT4_COMPH   : 1; // 24 Input Flag for SD1FLT4.COMPH Signal
    vu32 SD1FLT4_COMPL   : 1; // 25 Input Flag for SD1FLT4.COMPL Signal
    vu32 SD1FLT4_COMPZ   : 1; // 26 Input Flag for SD1FLT4.COMPZ Signal
    vu32 SD1FLT4_COMPH_L : 1; // 27 Input Flag for SD1FLT4.COMPH OR SD1FLT1.COMPL Signal
    vu32 SD1FLT1_DRINT   : 1; // 28 Input Flag for SD1FLT1.DRINT Signal
    vu32 SD1FLT2_DRINT   : 1; // 29 Input Flag for SD1FLT2.DRINT Signal
    vu32 SD1FLT3_DRINT   : 1; // 30 Input Flag for SD1FLT3.DRINT Signal
    vu32 SD1FLT4_DRINT   : 1; // 31 Input Flag for SD1FLT4.DRINT Signal
};

union XBAR2_REG
{
    vu32 all;
    struct XBAR2_BITS bit;
};

struct XBAR3_BITS
{                              // bits description
    vu32 CMPSS1_CTRIPH    : 1; // 0 Input Flag for CMPSS1.CTRIPH Signal
    vu32 CMPSS1_CTRIPL    : 1; // 1 Input Flag for CMPSS1.CTRIPL Signal
    vu32 CMPSS1_CTRIPOUTH : 1; // 2 Input Flag for CMPSS1.CTRIPOUTH Signal
    vu32 CMPSS1_CTRIPOUTL : 1; // 3 Input Flag for CMPSS1.CTRIPOUTL Signal
    vu32 CMPSS2_CTRIPH    : 1; // 4 Input Flag for CMPSS2.CTRIPH Signal
    vu32 CMPSS2_CTRIPL    : 1; // 5 Input Flag for CMPSS2.CTRIPL Signal
    vu32 CMPSS2_CTRIPOUTH : 1; // 6 Input Flag for CMPSS2.CTRIPOUTH Signal
    vu32 CMPSS2_CTRIPOUTL : 1; // 7 Input Flag for CMPSS2.CTRIPOUTL Signal
    vu32 CMPSS3_CTRIPH    : 1; // 8 Input Flag for CMPSS3.CTRIPH Signal
    vu32 CMPSS3_CTRIPL    : 1; // 9 Input Flag for CMPSS3.CTRIPL Signal
    vu32 CMPSS3_CTRIPOUTH : 1; // 10 Input Flag for CMPSS3.CTRIPOUTH Signal
    vu32 CMPSS3_CTRIPOUTL : 1; // 11 Input Flag for CMPSS3.CTRIPOUTL Signal
    vu32 CMPSS4_CTRIPH    : 1; // 12 Input Flag for CMPSS4.CTRIPH Signal
    vu32 CMPSS4_CTRIPL    : 1; // 13 Input Flag for CMPSS4.CTRIPL Signal
    vu32 CMPSS4_CTRIPOUTH : 1; // 14 Input Flag for CMPSS4.CTRIPOUTH Signal
    vu32 CMPSS4_CTRIPOUTL : 1; // 15 Input Flag for CMPSS4.CTRIPOUTL Signal
    vu32 CMPSS5_CTRIPH    : 1; // 16 Input Flag for CMPSS5.CTRIPH Signal
    vu32 CMPSS5_CTRIPL    : 1; // 17 Input Flag for CMPSS5.CTRIPL Signal
    vu32 CMPSS5_CTRIPOUTH : 1; // 18 Input Flag for CMPSS5.CTRIPOUTH Signal
    vu32 CMPSS5_CTRIPOUTL : 1; // 19 Input Flag for CMPSS5.CTRIPOUTL Signal
    vu32 CMPSS6_CTRIPH    : 1; // 20 Input Flag for CMPSS6.CTRIPH Signal
    vu32 CMPSS6_CTRIPL    : 1; // 21 Input Flag for CMPSS6.CTRIPL Signal
    vu32 CMPSS6_CTRIPOUTH : 1; // 22 Input Flag for CMPSS6.CTRIPOUTH Signal
    vu32 CMPSS6_CTRIPOUTL : 1; // 23 Input Flag for CMPSS6.CTRIPOUTL Signal
    vu32 CMPSS7_CTRIPH    : 1; // 24 Input Flag for CMPSS7.CTRIPH Signal
    vu32 CMPSS7_CTRIPL    : 1; // 25 Input Flag for CMPSS7.CTRIPL Signal
    vu32 CMPSS7_CTRIPOUTH : 1; // 26 Input Flag for CMPSS7.CTRIPOUTH Signal
    vu32 CMPSS7_CTRIPOUTL : 1; // 27 Input Flag for CMPSS7.CTRIPOUTL Signal
};

union XBAR3_REG
{
    vu32 all;
    struct XBAR3_BITS bit;
};

struct XBAR_REGS
{
    union XBAR1_REG XBARFLG1; // 0x00 X-Bar Input Flag Register 1
    union XBAR2_REG XBARFLG2; // 0x04 X-Bar Input Flag Register 2
    union XBAR3_REG XBARFLG3; // 0x08 X-Bar Input Flag Register 3
    union XBAR1_REG XBARCLR1; // 0x0C X-Bar Input Flag Clear Register 1
    union XBAR2_REG XBARCLR2; // 0x10 X-Bar Input Flag Clear Register 2
    union XBAR3_REG XBARCLR3; // 0x14 X-Bar Input Flag Clear Register 3
};

#define OutputXbarRegs ((struct OUTPUT_XBAR_REGS *)OUTPUTXBAR_BASE)
#define InputXbarRegs  ((struct INPUT_XBAR_REGS *)INPUTXBAR_BASE)
#define XbarRegs       ((struct XBAR_REGS *)XBAR_FLAG_BASE)

//*****************************************************************************
//
//! The following values define the \e input parameter for XBAR_setInputPin().
//
//*****************************************************************************
typedef enum
{
    XBAR_INPUT1  = 0,  // eCAPx, ePWM X-BAR, ePWM[TZ1,TRIP1], Output X-BAR
    XBAR_INPUT2  = 1,  // eCAPx, ePWM X-BAR, ePWM[TZ2,TRIP2], Output X-BAR
    XBAR_INPUT3  = 2,  // eCAPx, ePWM X-BAR, ePWM[TZ3,TRIP3], Output X-BAR
    XBAR_INPUT4  = 3,  // eCAPx, ePWM X-BAR, XINT1, Output X-BA
    XBAR_INPUT5  = 4,  // eCAPx, ePWM X-BAR, XINT2, ADCEXTSOC, EXTSYNCIN1, Output X-BAR
    XBAR_INPUT6  = 5,  // eCAPx, ePWM X-BAR, XINT3, ePWM[TRIP6], EXTSYNCIN2, Output X-BAR
    XBAR_INPUT7  = 6,  // eCAPx, ePWM X-BAR
    XBAR_INPUT8  = 7,  // eCAPx, ePWM X-BAR
    XBAR_INPUT9  = 8,  // eCAPx, ePWM X-BAR
    XBAR_INPUT10 = 9,  // eCAPx, ePWM X-BAR
    XBAR_INPUT11 = 10, // eCAPx, ePWM X-BAR
    XBAR_INPUT12 = 11, // eCAPx, ePWM X-BAR
    XBAR_INPUT13 = 12, // eCAPx, ePWM X-BAR, XINT4
    XBAR_INPUT14 = 13, // eCAPx, ePWM X-BAR, XINT5
    XBAR_INPUT15 = 14, // eCAPx
    XBAR_INPUT16 = 15, // eCAPx
} XBAR_InputNum;

typedef enum
{
    XBAR_INPUT_GPIO0  = 0,
    XBAR_INPUT_GPIO1  = 1,
    XBAR_INPUT_GPIO2  = 2,
    XBAR_INPUT_GPIO3  = 3,
    XBAR_INPUT_GPIO4  = 4,
    XBAR_INPUT_GPIO5  = 5,
    XBAR_INPUT_GPIO6  = 6,
    XBAR_INPUT_GPIO7  = 7,
    XBAR_INPUT_GPIO8  = 8,
    XBAR_INPUT_GPIO9  = 9,
    XBAR_INPUT_GPIO10 = 10,
    XBAR_INPUT_GPIO11 = 11,
    XBAR_INPUT_GPIO12 = 12,
    XBAR_INPUT_GPIO13 = 13,
    XBAR_INPUT_GPIO14 = 14,
    XBAR_INPUT_GPIO15 = 15,
} XBAR_InputGpio;

//*****************************************************************************
//
//! The following values define the \e output parameter for
//! XBAR_setOutputMuxConfig(), XBAR_enableOutputMux(), and
//! XBAR_disableOutputMux().
//
//*****************************************************************************
typedef enum
{
    XBAR_OUTPUT1 = 0x00, //!< OUTPUT1 of the Output X-BAR
    XBAR_OUTPUT2 = 0x04, //!< OUTPUT2 of the Output X-BAR
    XBAR_OUTPUT3 = 0x08, //!< OUTPUT3 of the Output X-BAR
    XBAR_OUTPUT4 = 0x0C, //!< OUTPUT4 of the Output X-BAR
    XBAR_OUTPUT5 = 0x10, //!< OUTPUT5 of the Output X-BAR
    XBAR_OUTPUT6 = 0x14, //!< OUTPUT6 of the Output X-BAR
    XBAR_OUTPUT7 = 0x18, //!< OUTPUT7 of the Output X-BAR
    XBAR_OUTPUT8 = 0x1C, //!< OUTPUT8 of the Output X-BAR
} XBAR_OutputNum;

//*****************************************************************************
//
//! The following values define the \e trip parameter for
//! XBAR_setEPWMMuxConfig(), XBAR_enableEPWMMux(), and XBAR_disableEPWMMux().
//
//*****************************************************************************
typedef enum
{
    XBAR_TRIP4  = 0x00, //!< TRIP4 of the ePWM X-BAR
    XBAR_TRIP5  = 0x04, //!< TRIP5 of the ePWM X-BAR
    XBAR_TRIP7  = 0x08, //!< TRIP7 of the ePWM X-BAR
    XBAR_TRIP8  = 0x0C, //!< TRIP8 of the ePWM X-BAR
    XBAR_TRIP9  = 0x10, //!< TRIP9 of the ePWM X-BAR
    XBAR_TRIP10 = 0x14, //!< TRIP10 of the ePWM X-BAR
    XBAR_TRIP11 = 0x18, //!< TRIP11 of the ePWM X-BAR
    XBAR_TRIP12 = 0x1C, //!< TRIP12 of the ePWM X-BAR
} XBAR_TripNum;

//*****************************************************************************
//
// The following values define the trip parameter for XBAR_setCLBMuxConfig(),
// XBAR_enableCLBMux(), and XBAR_disableCLBMux().
//
//*****************************************************************************
typedef enum
{
    XBAR_AUXSIG0 = 0,
    XBAR_AUXSIG1 = 2,
    XBAR_AUXSIG2 = 4,
    XBAR_AUXSIG3 = 6,
    XBAR_AUXSIG4 = 8,
    XBAR_AUXSIG5 = 10,
    XBAR_AUXSIG6 = 12,
    XBAR_AUXSIG7 = 14,
} XBAR_AuxSigNum;

//*****************************************************************************
//
//! The following values define the \e muxs parameter for
//! XBAR_enableOutputMux().
//
//*****************************************************************************
#define XBAR_MUX00 0x00000001U //!< Mask for X-BAR mux 0
#define XBAR_MUX01 0x00000002U //!< Mask for X-BAR mux 1
#define XBAR_MUX02 0x00000004U //!< Mask for X-BAR mux 2
#define XBAR_MUX03 0x00000008U //!< Mask for X-BAR mux 3
#define XBAR_MUX04 0x00000010U //!< Mask for X-BAR mux 4
#define XBAR_MUX05 0x00000020U //!< Mask for X-BAR mux 5
#define XBAR_MUX06 0x00000040U //!< Mask for X-BAR mux 6
#define XBAR_MUX07 0x00000080U //!< Mask for X-BAR mux 7
#define XBAR_MUX08 0x00000100U //!< Mask for X-BAR mux 8
#define XBAR_MUX09 0x00000200U //!< Mask for X-BAR mux 9
#define XBAR_MUX10 0x00000400U //!< Mask for X-BAR mux 10
#define XBAR_MUX11 0x00000800U //!< Mask for X-BAR mux 11
#define XBAR_MUX12 0x00001000U //!< Mask for X-BAR mux 12
#define XBAR_MUX13 0x00002000U //!< Mask for X-BAR mux 13
#define XBAR_MUX14 0x00004000U //!< Mask for X-BAR mux 14
#define XBAR_MUX15 0x00008000U //!< Mask for X-BAR mux 15
#define XBAR_MUX16 0x00010000U //!< Mask for X-BAR mux 16
#define XBAR_MUX17 0x00020000U //!< Mask for X-BAR mux 17
#define XBAR_MUX18 0x00040000U //!< Mask for X-BAR mux 18
#define XBAR_MUX19 0x00080000U //!< Mask for X-BAR mux 19
#define XBAR_MUX20 0x00100000U //!< Mask for X-BAR mux 20
#define XBAR_MUX21 0x00200000U //!< Mask for X-BAR mux 21
#define XBAR_MUX22 0x00400000U //!< Mask for X-BAR mux 22
#define XBAR_MUX23 0x00800000U //!< Mask for X-BAR mux 23
#define XBAR_MUX24 0x01000000U //!< Mask for X-BAR mux 24
#define XBAR_MUX25 0x02000000U //!< Mask for X-BAR mux 25
#define XBAR_MUX26 0x04000000U //!< Mask for X-BAR mux 26
#define XBAR_MUX27 0x08000000U //!< Mask for X-BAR mux 27
#define XBAR_MUX28 0x10000000U //!< Mask for X-BAR mux 28
#define XBAR_MUX29 0x20000000U //!< Mask for X-BAR mux 29
#define XBAR_MUX30 0x40000000U //!< Mask for X-BAR mux 30
#define XBAR_MUX31 0x80000000U //!< Mask for X-BAR mux 31

//*****************************************************************************
//
//! The following values define the \e muxConfig parameter for
//! XBAR_setOutputMuxConfig().
//
//*****************************************************************************
typedef enum
{
	XBAR_OUT_MUX00_CMPSS                  = 0x0000,
    XBAR_OUT_MUX00_ADCAEVT1               = 0x0002,
    XBAR_OUT_MUX00_ECAP1_OUT              = 0x0003,
    XBAR_OUT_MUX01_INPUTXBAR1             = 0x0201,
    XBAR_OUT_MUX01_ADCCEVT1               = 0x0203,
    XBAR_OUT_MUX02_ADCAEVT2               = 0x0402,
    XBAR_OUT_MUX02_ECAP2_OUT              = 0x0403,
    XBAR_OUT_MUX03_INPUTXBAR2             = 0x0601,
    XBAR_OUT_MUX03_ADCCEVT2               = 0x0603,
    XBAR_OUT_MUX04_ADCAEVT3               = 0x0802,
    XBAR_OUT_MUX04_ECAP3_OUT              = 0x0803,
    XBAR_OUT_MUX05_INPUTXBAR3             = 0x0A01,
    XBAR_OUT_MUX05_ADCCEVT3               = 0x0A03,
    XBAR_OUT_MUX06_ADCAEVT4               = 0x0C02,
    XBAR_OUT_MUX06_ECAP4_OUT              = 0x0C03,
    XBAR_OUT_MUX07_INPUTXBAR4             = 0x0E01,
    XBAR_OUT_MUX07_ADCCEVT4               = 0x0E03,
    XBAR_OUT_MUX08_ADCBEVT1               = 0x1002,
    XBAR_OUT_MUX08_ECAP5_OUT              = 0x1003,
    XBAR_OUT_MUX09_INPUTXBAR5             = 0x1201,
    XBAR_OUT_MUX10_ADCBEVT2               = 0x1402,
    XBAR_OUT_MUX10_ECAP6_OUT              = 0x1403,
    XBAR_OUT_MUX11_INPUTXBAR6             = 0x1601,
    XBAR_OUT_MUX12_ADCBEVT3               = 0x1802,
    XBAR_OUT_MUX12_ECAP7_OUT              = 0x1803,
    XBAR_OUT_MUX13_ADCSOCA                = 0x1A01,
    XBAR_OUT_MUX14_ADCBEVT4               = 0x1C02,
    XBAR_OUT_MUX14_EXTSYNCOUT             = 0x1C03,
    XBAR_OUT_MUX15_ADCSOCB                = 0x1E01,
    XBAR_OUT_MUX16_SD1FLT1_COMPH          = 0x2000,
    XBAR_OUT_MUX16_SD1FLT1_COMPH_OR_COMPL = 0x2001,
    XBAR_OUT_MUX17_SD1FLT1_COMPL          = 0x2200,
    XBAR_OUT_MUX18_SD1FLT2_COMPH          = 0x2400,
    XBAR_OUT_MUX18_SD1FLT2_COMPH_OR_COMPL = 0x2401,
    XBAR_OUT_MUX19_SD1FLT2_COMPL          = 0x2600,
    XBAR_OUT_MUX20_SD1FLT3_COMPH          = 0x2800,
    XBAR_OUT_MUX20_SD1FLT3_COMPH_OR_COMPL = 0x2801,
    XBAR_OUT_MUX21_SD1FLT3_COMPL          = 0x2A00,
    XBAR_OUT_MUX22_SD1FLT4_COMPH          = 0x2C00,
    XBAR_OUT_MUX22_SD1FLT4_COMPH_OR_COMPL = 0x2C01,
    XBAR_OUT_MUX23_SD1FLT4_COMPL          = 0x2E00,
} XBAR_OutputMuxConfig;

//*****************************************************************************
//
//! The following values define the \e muxConfig parameter for
//! XBAR_setEPWMMuxConfig().
//
//*****************************************************************************
typedef enum
{
	XBAR_EPWM_MUX00_CMPSS                  = 0x0001,
    XBAR_EPWM_MUX00_ADCAEVT1               = 0x0002,
    XBAR_EPWM_MUX00_ECAP1_OUT              = 0x0003,
    XBAR_EPWM_MUX01_INPUTXBAR1             = 0x0201,
    XBAR_EPWM_MUX01_ADCCEVT1               = 0x0203,
    XBAR_EPWM_MUX02_ADCAEVT2               = 0x0402,
    XBAR_EPWM_MUX02_ECAP2_OUT              = 0x0403,
    XBAR_EPWM_MUX03_INPUTXBAR2             = 0x0601,
    XBAR_EPWM_MUX03_ADCCEVT2               = 0x0603,
    XBAR_EPWM_MUX04_ADCAEVT3               = 0x0802,
    XBAR_EPWM_MUX04_ECAP3_OUT              = 0x0803,
    XBAR_EPWM_MUX05_INPUTXBAR3             = 0x0A01,
    XBAR_EPWM_MUX05_ADCCEVT3               = 0x0A03,
    XBAR_EPWM_MUX06_ADCAEVT4               = 0x0C02,
    XBAR_EPWM_MUX06_ECAP4_OUT              = 0x0C03,
    XBAR_EPWM_MUX07_INPUTXBAR4             = 0x0E01,
    XBAR_EPWM_MUX07_ADCCEVT4               = 0x0E03,
    XBAR_EPWM_MUX08_ADCBEVT1               = 0x1002,
    XBAR_EPWM_MUX08_ECAP5_OUT              = 0x1003,
    XBAR_EPWM_MUX09_INPUTXBAR5             = 0x1201,
    XBAR_EPWM_MUX10_ADCBEVT2               = 0x1402,
    XBAR_EPWM_MUX10_ECAP6_OUT              = 0x1403,
    XBAR_EPWM_MUX11_INPUTXBAR6             = 0x1601,
    XBAR_EPWM_MUX12_ADCBEVT3               = 0x1802,
    XBAR_EPWM_MUX12_ECAP7_OUT              = 0x1803,
    XBAR_EPWM_MUX13_ADCSOCA                = 0x1A01,
    XBAR_EPWM_MUX14_ADCBEVT4               = 0x1C02,
    XBAR_EPWM_MUX14_EXTSYNCOUT             = 0x1C03,
    XBAR_EPWM_MUX15_ADCSOCB                = 0x1E01,
    XBAR_EPWM_MUX16_SD1FLT1_COMPH          = 0x2000,
    XBAR_EPWM_MUX16_SD1FLT1_COMPH_OR_COMPL = 0x2001,
    XBAR_EPWM_MUX17_SD1FLT1_COMPL          = 0x2200,
    XBAR_EPWM_MUX17_INPUTXBAR7             = 0x2201,
    XBAR_EPWM_MUX18_SD1FLT2_COMPH          = 0x2400,
    XBAR_EPWM_MUX18_SD1FLT2_COMPH_OR_COMPL = 0x2401,
    XBAR_EPWM_MUX19_SD1FLT2_COMPL          = 0x2600,
    XBAR_EPWM_MUX19_INPUTXBAR8             = 0x2601,
    XBAR_EPWM_MUX20_SD1FLT3_COMPH          = 0x2800,
    XBAR_EPWM_MUX20_SD1FLT3_COMPH_OR_COMPL = 0x2801,
    XBAR_EPWM_MUX21_SD1FLT3_COMPL          = 0x2A00,
    XBAR_EPWM_MUX21_INPUTXBAR9             = 0x2A01,
    XBAR_EPWM_MUX22_SD1FLT4_COMPH          = 0x2C00,
    XBAR_EPWM_MUX22_SD1FLT4_COMPH_OR_COMPL = 0x2C01,
    XBAR_EPWM_MUX23_SD1FLT4_COMPL          = 0x2E00,
    XBAR_EPWM_MUX23_INPUTXBAR10            = 0x2E01,
    XBAR_EPWM_MUX25_INPUTXBAR11            = 0x3201,
    XBAR_EPWM_MUX27_INPUTXBAR12            = 0x3601,
    XBAR_EPWM_MUX29_INPUTXBAR13            = 0x3A01,
    XBAR_EPWM_MUX31_INPUTXBAR14            = 0x3E01,
} XBAR_EPWMMuxConfig;

//*****************************************************************************
//
//! The following values define the \e inputFlag parameter for
//! XBAR_getInputFlagStatus() and XBAR_clearInputFlag().
//
//*****************************************************************************
typedef enum
{
    // XBARFLG1
    XBAR_INPUT_FLG_INPUT1     = 0x0000,
    XBAR_INPUT_FLG_INPUT2     = 0x0001,
    XBAR_INPUT_FLG_INPUT3     = 0x0002,
    XBAR_INPUT_FLG_INPUT4     = 0x0003,
    XBAR_INPUT_FLG_INPUT5     = 0x0004,
    XBAR_INPUT_FLG_INPUT6     = 0x0005,
    XBAR_INPUT_FLG_ADCSOCA    = 0x0006,
    XBAR_INPUT_FLG_ADCSOCB    = 0x0007,
    XBAR_INPUT_FLG_INPUT7     = 0x0008,
    XBAR_INPUT_FLG_INPUT8     = 0x0009,
    XBAR_INPUT_FLG_INPUT9     = 0x000A,
    XBAR_INPUT_FLG_INPUT10    = 0x000B,
    XBAR_INPUT_FLG_INPUT11    = 0x000C,
    XBAR_INPUT_FLG_INPUT12    = 0x000D,
    XBAR_INPUT_FLG_INPUT13    = 0x000E,
    XBAR_INPUT_FLG_INPUT14    = 0x000F,
    XBAR_INPUT_FLG_ECAP1_OUT  = 0x0010,
    XBAR_INPUT_FLG_ECAP2_OUT  = 0x0011,
    XBAR_INPUT_FLG_ECAP3_OUT  = 0x0012,
    XBAR_INPUT_FLG_ECAP4_OUT  = 0x0013,
    XBAR_INPUT_FLG_ECAP5_OUT  = 0x0014,
    XBAR_INPUT_FLG_ECAP6_OUT  = 0x0015,
    XBAR_INPUT_FLG_EXTSYNCOUT = 0x0016,
    XBAR_INPUT_FLG_ECAP7_OUT  = 0x0017,

    // XBARFLG2
    XBAR_INPUT_FLG_ADCAEVT1        = 0x1000,
    XBAR_INPUT_FLG_ADCBEVT1        = 0x1001,
    XBAR_INPUT_FLG_ADCCEVT1        = 0x1002,
    XBAR_INPUT_FLG_ADCAEVT2        = 0x1003,
    XBAR_INPUT_FLG_ADCBEVT2        = 0x1004,
    XBAR_INPUT_FLG_ADCCEVT2        = 0x1005,
    XBAR_INPUT_FLG_ADCAEVT3        = 0x1006,
    XBAR_INPUT_FLG_ADCBEVT3        = 0x1007,
    XBAR_INPUT_FLG_ADCCEVT3        = 0x1008,
    XBAR_INPUT_FLG_ADCAEVT4        = 0x1009,
    XBAR_INPUT_FLG_ADCBEVT4        = 0x100A,
    XBAR_INPUT_FLG_ADCCEVT4        = 0x100B,
    XBAR_INPUT_FLG_SD1FLT1_COMPH   = 0x100C,
    XBAR_INPUT_FLG_SD1FLT1_COMPL   = 0x100D,
    XBAR_INPUT_FLG_SD1FLT1_COMPH_L = 0x100E,
    XBAR_INPUT_FLG_SD1FLT2_COMPH   = 0x100F,
    XBAR_INPUT_FLG_SD1FLT2_COMPL   = 0x1010,
    XBAR_INPUT_FLG_SD1FLT2_COMPH_L = 0x1011,
    XBAR_INPUT_FLG_SD1FLT3_COMPH   = 0x1012,
    XBAR_INPUT_FLG_SD1FLT3_COMPL   = 0x1013,
    XBAR_INPUT_FLG_SD1FLT3_COMPH_L = 0x1014,
    XBAR_INPUT_FLG_SD1FLT4_COMPH   = 0x1015,
    XBAR_INPUT_FLG_SD1FLT4_COMPL   = 0x1016,
    XBAR_INPUT_FLG_SD1FLT4_COMPH_L = 0x1017,
} XBAR_InputFlag;

//*****************************************************************************
//
//! Enables the Output X-BAR mux values to be passed to the output signal.
//!
//! \param output is the X-BAR output being configured.
//! \param muxes is a bit field of the muxes to be enabled.
//!
//! This function enables the mux values to be passed to the X-BAR output
//! signal. The \e output parameter is a value \b XBAR_OUTPUTy where y is
//! the output number between 1 and 8 inclusive.
//!
//! The \e muxes parameter is a bit field of the muxes being enabled where bit
//! 0 represents mux 0, bit 1 represents mux 1 and so on. Defines are provided
//! in the form of \b XBAR_MUXnn that can be OR'd together to enable several
//! muxes on an output at the same time. For example, passing this function
//! ( \b XBAR_MUX04 | \b XBAR_MUX10 ) would enable muxes 4 and 10.
//!
//! \return None.
//
//*****************************************************************************
static inline void XBAR_enableOutputMux(XBAR_OutputNum output, uint32_t muxes)
{
    EALLOW;
    HWREG(&OutputXbarRegs->OUTPUT1MUXENABLE + output) |= muxes;
    EDIS;
}

//*****************************************************************************
//
//! Disables the Output X-BAR mux values from being passed to the output.
//!
//! \param output is the X-BAR output being configured.
//! \param muxes is a bit field of the muxes to be disabled.
//!
//! This function disables the mux values from being passed to the X-BAR output
//! signal. The \e output parameter is a value \b XBAR_OUTPUTy where y is
//! the output number between 1 and 8 inclusive.
//!
//! The \e muxes parameter is a bit field of the muxes being disabled where bit
//! 0 represents mux 0, bit 1 represents mux 1 and so on. Defines are provided
//! in the form of \b XBAR_MUXnn that can be OR'd together to disable several
//! muxes on an output at the same time. For example, passing this function
//! ( \b XBAR_MUX04 | \b XBAR_MUX10 ) would disable muxes 4 and 10.
//!
//! \return None.
//
//*****************************************************************************
static inline void XBAR_disableOutputMux(XBAR_OutputNum output, uint32_t muxes)
{
    EALLOW;
    HWREG(&OutputXbarRegs->OUTPUT1MUXENABLE + output) &= ~(muxes);
    EDIS;
}

//*****************************************************************************
//
//! Enables or disables the output latch to drive the selected output.
//!
//! \param output is the X-BAR output being configured.
//! The valid inputs are XBAR_OUTPUTy where y is from 1 to 8.
//! \param enable is a flag that determines whether or not the latch is
//! selected to drive the X-BAR output.
//!
//! This function sets the Output X-BAR output signal latch mode. If the
//! \e enable parameter is \b true, the output specified by \e output will be
//! driven by the output latch.
//!
//! \return None.
//
//*****************************************************************************
static inline void XBAR_setOutputLatchMode(XBAR_OutputNum output, bool enable)
{
    EALLOW;
    // Set or clear the latch setting bit based on the enable parameter.
    if (enable)
        OutputXbarRegs->OUTPUTLATCHENABLE.all |= 0x1U << ((uint16_t)output >> 2U);
    else
        OutputXbarRegs->OUTPUTLATCHENABLE.all &= ~(0x1U << ((uint16_t)output >> 2U));
    EDIS;
}

//*****************************************************************************
//
//! Returns the status of the output latch
//!
//! \param output is the X-BAR output being checked.
//! The valid inputs are XBAR_OUTPUTy where y is from 1 to 8.
//!
//! \return Returns \b true if the output corresponding to \e output was
//! triggered. If not, it will return \b false.
//
//*****************************************************************************
static inline bool XBAR_getOutputLatchStatus(XBAR_OutputNum output)
{
    // Get the status of the Output X-BAR output latch.
    return ((OutputXbarRegs->OUTPUTLATCH.all & (0x1U << ((uint16_t)output >> 2U))) != 0U);
}

//*****************************************************************************
//
//! Clears the output latch for the specified output.
//!
//! \param output is the X-BAR output being configured.
//! The valid inputs are XBAR_OUTPUTy where y is from 1 to 8.
//!
//! This function clears the Output X-BAR output latch. The output to be
//! configured is specified by the \e output parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void XBAR_clearOutputLatch(XBAR_OutputNum output)
{
    // Set the bit that clears the corresponding OUTPUTLATCH bit.
    OutputXbarRegs->OUTPUTLATCHCLR.all |= 0x1U << ((uint16_t)output >> 2U);
}

//*****************************************************************************
//
//! Forces the output latch for the specified output.
//!
//! \param output is the X-BAR output being configured.
//! The valid inputs are XBAR_OUTPUTy where y is from 1 to 8.
//!
//! This function forces the Output X-BAR output latch. The output to be
//! configured is specified by the \e output parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void XBAR_forceOutputLatch(XBAR_OutputNum output)
{
    // Set the bit that forces the corresponding OUTPUTLATCH bit.
    OutputXbarRegs->OUTPUTLATCHFRC.all = (uint16_t)0x1U << ((uint16_t)output >> 2U);
}

//*****************************************************************************
//
//! Configures the polarity of an Output X-BAR output.
//!
//! \param output is the X-BAR output being configured.
//! The valid inputs are XBAR_OUTPUTy where y is from 1 to 8.
//! \param invert is a flag that determines whether the output is active-high
//! or active-low.
//!
//! This function inverts the Output X-BAR signal if the \e invert parameter is
//! \b true. If \e invert is \b false, the signal will be passed as is. The
//! \e output parameter is a value \b XBAR_OUTPUTy where y is the output
//! number between 1 and 8 inclusive.
//!
//! \return None.
//
//*****************************************************************************
static inline void XBAR_invertOutputSignal(XBAR_OutputNum output, bool invert)
{
    // Set or clear the polarity setting bit based on the invert parameter.
    EALLOW;
    if (invert)
        OutputXbarRegs->OUTPUTINV.all |= 0x1U << ((uint16_t)output >> 2U);
    else
        OutputXbarRegs->OUTPUTINV.all &= ~(0x1U << ((uint16_t)output >> 2U));
    EDIS;
}

//*****************************************************************************
//
//! Enables the ePWM X-BAR mux values to be passed to an ePWM module.
//!
//! \param trip is the X-BAR output being configured.
//! \param muxes is a bit field of the muxes to be enabled.
//!
//! This function enables the mux values to be passed to the X-BAR trip
//! signal. The \e trip parameter is a value \b XBAR_TRIPy where y is
//! the number of the trip signal on the ePWM.
//!
//! The \e muxes parameter is a bit field of the muxes being enabled where bit
//! 0 represents mux 0, bit 1 represents mux 1 and so on. Defines are provided
//! in the form of \b XBAR_MUXnn that can be logically OR'd together to
//! enable several muxes on an output at the same time.
//!
//! \return None.
//
//*****************************************************************************
static inline void XBAR_enableEPWMMux(XBAR_TripNum trip, uint32_t muxes)
{
    EALLOW;
    HWREG(&EPwmXbarRegs->TRIP4MUXENABLE + trip) |= muxes;
    EDIS;
}

//*****************************************************************************
//
//! Disables the ePWM X-BAR mux values to be passed to an ePWM module.
//!
//! \param trip is the X-BAR output being configured.
//! \param muxes is a bit field of the muxes to be disabled.
//!
//! This function disables the mux values to be passed to the X-BAR trip
//! signal. The \e trip parameter is a value \b XBAR_TRIPy where y is
//! the number of the trip signal on the ePWM.
//!
//! The \e muxes parameter is a bit field of the muxes being disabled where bit
//! 0 represents mux 0, bit 1 represents mux 1 and so on. Defines are provided
//! in the form of \b XBAR_MUXnn that can be logically OR'd together to
//! disable several muxes on an output at the same time.
//!
//! \return None.
//
//*****************************************************************************
static inline void XBAR_disableEPWMMux(XBAR_TripNum trip, uint32_t muxes)
{
    EALLOW;
    HWREG(&EPwmXbarRegs->TRIP4MUXENABLE + trip) &= ~(muxes);
    EDIS;
}

//*****************************************************************************
//
//! Configures the polarity of an ePWM X-BAR output.
//!
//! \param trip is the X-BAR output being configured.
//! \param invert is a flag that determines whether the output is active-high
//! or active-low.
//!
//! This function inverts the ePWM X-BAR trip signal if the \e invert
//! parameter is \b true. If \e invert is \b false, the signal will be passed
//! as is. The \e trip parameter is a value \b XBAR_TRIPy where y is
//! the number of the trip signal on the ePWM X-BAR that is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void XBAR_invertEPWMSignal(XBAR_TripNum trip, bool invert)
{
    // Set or clear the polarity setting bit based on the invert parameter.
    EALLOW;
    if (invert)
        EPwmXbarRegs->TRIPOUTINV.all |= 0x1U << ((uint16_t)trip >> 2U);
    else
        EPwmXbarRegs->TRIPOUTINV.all &= ~(0x1U << ((uint16_t)trip >> 2U));
    EDIS;
}

//*****************************************************************************
//
//! Sets the GPIO / non-GPIO pin for an Input X-BAR input.
//!
//! \param input is the X-BAR input being configured.
//! \param pin is the identifying number of the pin.
//!
//! This function configures which GPIO is assigned to an Input X-BAR input.
//! The \e input parameter is a value in the form of a define \b XBAR_INPUTy
//! where y is a the input number for the Input X-BAR.
//!
//! The pin is specified by its numerical value. For example, GPIO12 is
//! specified by passing 12 as \e pin.
//!
//! For the other non - GPIO values:
//! 0x0010: '1' will be driven to the destination
//! ...
//! 0xFFFE: '1' will be driven to the destination
//! 0xFFFF: '0' will be driven to the destination
//! NOTE: Pin value greater than the available number of GPIO pins on a
//! device (except 0xFFFF) will cause the destination to be driven '1'.
//!
//! \return None.
//
//*****************************************************************************
static inline void XBAR_setInputPin(XBAR_InputNum input, XBAR_InputGpio pin)
{
    EALLOW;
    HWREGH(INPUTXBAR_BASE + input * 4) = pin;
    EDIS;
}

//*****************************************************************************
//
//! Locks an input to the Input X-BAR.
//!
//! \param input is an input to the Input X-BAR.
//!
//! This function locks the specific input on the Input X-BAR.
//!
//! \return None.
//
//*****************************************************************************
static inline void XBAR_lockInput(XBAR_InputNum input)
{
    EALLOW;
    InputXbarRegs->INPUTSELECTLOCK.all = 1UL << (uint16_t)input;
    EDIS;
}

//*****************************************************************************
//
//! Locks the Output X-BAR.
//!
//! This function locks the Output X-BAR.
//!
//! \return None.
//
//*****************************************************************************
static inline void XBAR_lockOutput(void)
{
    // Lock the Output X-BAR with the OUTPUTLOCK register.
    // Write key 0x5A5A to the KEY bits and 1 to LOCK bit.
    EALLOW;
    OutputXbarRegs->OUTPUTLOCK.bit.KEY  = 0x5A5A;
    OutputXbarRegs->OUTPUTLOCK.bit.LOCK = 1;
    EDIS;
}

//*****************************************************************************
//
//! Locks the ePWM X-BAR.
//!
//! This function locks the ePWM X-BAR.
//!
//! \return None.
//
//*****************************************************************************
static inline void XBAR_lockEPWM(void)
{
    // Lock the ePWM X-BAR with the TRIPLOCK register.
    // Write key 0x5A5A to the KEY bits and 1 to LOCK bit.
    EALLOW;
    EPwmXbarRegs->TRIPLOCK.bit.KEY  = 0x5A5A;
    EPwmXbarRegs->TRIPLOCK.bit.LOCK = 1;
    EDIS;
}

//*****************************************************************************
//
//! Configures the Output X-BAR mux that determines the signals passed to an
//! output.
//!
//! \param output is the X-BAR output being configured.
//! \param muxConfig is mux configuration that specifies the signal.
//!
//! This function configures an Output X-BAR mux. This determines which
//! signal(s) should be passed through the X-BAR to a GPIO. The \e output
//! parameter is a value \b XBAR_OUTPUTy where y is a the output number
//! between 1 and 8 inclusive.
//!
//! The \e muxConfig parameter for OUTPUT XBAR is the mux configuration
//! value that specifies which signal will be passed from the mux. The
//! values have the format of \b XBAR_OUT_MUXnn_xx where the 'xx' is
//! the signal and nn is the mux number.
//!
//! This function may be called for each mux of an output and their values will
//! be logically OR'd before being passed to the output signal. This means that
//! this function may be called, for example, with the argument
//! \b XBAR_OUT_MUX00_ECAP1_OUT and then with the argument
//! \b XBAR_OUT_MUX01_INPUTXBAR1, resulting in the values of MUX00 and MUX01
//! being logically OR'd if both are enabled. Calling the function twice for
//! the same mux on the output will result in the configuration in the second
//! call overwriting the first.
//!
//! \return None.
//
//*****************************************************************************
extern void XBAR_setOutputMuxConfig(XBAR_OutputNum output, XBAR_OutputMuxConfig muxConfig);

//*****************************************************************************
//
//! Configures the ePWM X-BAR mux that determines the signals passed to an
//! ePWM module.
//!
//! \param trip is the X-BAR output being configured.
//! \param muxConfig is mux configuration that specifies the signal.
//!
//! This function configures an ePWM X-BAR mux. This determines which signal(s)
//! should be passed through the X-BAR to an ePWM module. The \e trip
//! parameter is a value \b XBAR_TRIPy where y is a the number of the trip
//! signal on the ePWM.
//!
//! The \e muxConfig parameter is the mux configuration value that specifies
//! which signal will be passed from the mux. The values have the format of
//! \b XBAR_EPWM_MUXnn_xx where the 'xx' is the signal and nn is the mux
//! number (0 through 31). The possible values are found in <tt>xbar.h</tt>
//!
//! This function may be called for each mux of an output and their values will
//! be logically OR'd before being passed to the trip signal. This means that
//! this function may be called, for example, with the argument
//! \b XBAR_EPWM_MUX00_ECAP1_OUT and then with the argument
//! \b XBAR_EPWM_MUX01_INPUTXBAR1, resulting in the values of MUX00 and MUX01
//! being logically OR'd if both are enabled. Calling the function twice for
//! the same mux on the output will result in the configuration in the second
//! call overwriting the first.
//!
//! \return None.
//
//*****************************************************************************
extern void XBAR_setEPWMMuxConfig(XBAR_TripNum trip, XBAR_EPWMMuxConfig muxConfig);

//*****************************************************************************
//
//! Returns the status of the input latch.
//!
//! \param inputFlag is the X-BAR input latch being checked. Values are in the
//! format of /b XBAR_INPUT_FLG_XXXX where "XXXX" is name of the signal.
//!
//! \return Returns \b true if the X-BAR input corresponding to the
//! \e inputFlag has been triggered. If not, it will return \b false.
//
//*****************************************************************************
extern bool XBAR_getInputFlagStatus(XBAR_InputFlag inputFlag);

//*****************************************************************************
//
//! Clears the input latch for the specified input latch.
//!
//! \param inputFlag is the X-BAR input latch being cleared.
//!
//! This function clears the Input X-BAR input latch. The input latch to be
//! cleared is specified by the \e inputFlag parameter.
//!
//! \return None.
//
//*****************************************************************************
extern void XBAR_clearInputFlag(XBAR_InputFlag inputFlag);

#ifdef __cplusplus
}
#endif

#endif
