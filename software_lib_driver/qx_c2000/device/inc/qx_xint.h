/**
 **************************************************************************
 * @file     qx_xint.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_XINT_H
#define QX_XINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"
#include "hw_xint.h"

//---------------------------------------------------------------------------
// XINT Individual Register Bit Definitions:

struct XINT1CR_BITS
{                       // bits description
    vu32 ENABLE   : 1;  // 0 XINT1 Enable
    vu32 rsvd1    : 1;  // 1 Reserved
    vu32 POLARITY : 2;  // 3:2 XINT1 Polarity
    vu32 rsvd2    : 12; // 15:4 Reserved
};

union XINT1CR_REG
{
    vu32 all;
    struct XINT1CR_BITS bit;
};

struct XINT2CR_BITS
{                       // bits description
    vu32 ENABLE   : 1;  // 0 XINT2 Enable
    vu32 rsvd1    : 1;  // 1 Reserved
    vu32 POLARITY : 2;  // 3:2 XINT2 Polarity
    vu32 rsvd2    : 12; // 15:4 Reserved
};

union XINT2CR_REG
{
    vu32 all;
    struct XINT2CR_BITS bit;
};

struct XINT3CR_BITS
{                       // bits description
    vu32 ENABLE   : 1;  // 0 XINT3 Enable
    vu32 rsvd1    : 1;  // 1 Reserved
    vu32 POLARITY : 2;  // 3:2 XINT3 Polarity
    vu32 rsvd2    : 12; // 15:4 Reserved
};

union XINT3CR_REG
{
    vu32 all;
    struct XINT3CR_BITS bit;
};

struct XINT4CR_BITS
{                       // bits description
    vu32 ENABLE   : 1;  // 0 XINT4 Enable
    vu32 rsvd1    : 1;  // 1 Reserved
    vu32 POLARITY : 2;  // 3:2 XINT4 Polarity
    vu32 rsvd2    : 12; // 15:4 Reserved
};

union XINT4CR_REG
{
    vu32 all;
    struct XINT4CR_BITS bit;
};

struct XINT5CR_BITS
{                       // bits description
    vu32 ENABLE   : 1;  // 0 XINT5 Enable
    vu32 rsvd1    : 1;  // 1 Reserved
    vu32 POLARITY : 2;  // 3:2 XINT5 Polarity
    vu32 rsvd2    : 12; // 15:4 Reserved
};

union XINT5CR_REG
{
    vu32 all;
    struct XINT5CR_BITS bit;
};

struct XINT_REGS
{
    union XINT1CR_REG XINT1CR; // XINT1 configuration register
    union XINT2CR_REG XINT2CR; // XINT2 configuration register
    union XINT3CR_REG XINT3CR; // XINT3 configuration register
    union XINT4CR_REG XINT4CR; // XINT4 configuration register
    union XINT5CR_REG XINT5CR; // XINT5 configuration register
    vu32 rsvd1[3];             // Reserved
    vu32 XINT1CTR;             // XINT1 counter register
    vu32 XINT2CTR;             // XINT2 counter register
    vu32 XINT3CTR;             // XINT3 counter register
};

//---------------------------------------------------------------------------
// XINT External References & Function Declarations:
//

#define XINT_BASE (CPUSYS_BASE + 0x1B0U)
#define XintRegs ((struct XINT_REGS *)XINT_BASE)

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
