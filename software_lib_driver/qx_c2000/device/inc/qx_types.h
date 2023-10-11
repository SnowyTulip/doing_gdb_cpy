/**
 **************************************************************************
 * @file     qx_types.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_TYPES_H
#define QX_TYPES_H

//*****************************************************************************
// Macros for hardware access
//*****************************************************************************

#define HWREG(x)  (*((volatile uint32_t *)(x)))
#define HWREGH(x) (*((volatile uint16_t *)(x)))
#define HWREGB(x) (*((volatile uint8_t *)(x)))
/* #define HWREG_BP(x) __byte_peripheral_32((uint32_t *)(x)) */

//*****************************************************************************
// SUCCESS and FAILURE for API return value
//*****************************************************************************
#define STATUS_S_SUCCESS (0)
#define STATUS_E_FAILURE (-1)

#define SUCCESS true
#define FAIL false

//*****************************************************************************
// Definition of 8 bit types for USB Driver code to maintain portability
// between byte and word addressable cores of C2000 Devices.
//*****************************************************************************
// typedef uint16_t uint8_t;
// typedef int16_t int8_t;

//****************************************************************************
// For checking NULL pointers
//****************************************************************************
#ifndef NULL
#define NULL ((void *)0x0)
#endif

//*****************************************************************************
// Extern compiler intrinsic prototypes. See compiler User's Guide for details.
// These are provided to satisfy static analysis tools. The #ifndef is required
// because the '&' is for a C++-style reference, and although it is the correct
// prototype, it will not build in C code.
//*****************************************************************************
// #if (defined(__TMS320C28XX__) || defined(__TMS320C28XX_CLA__))
// #else
// extern int16_t &__byte(int16_t *array, uint16_t byte_index);
// extern uint32_t &__byte_peripheral_32(uint32_t *x);
// #endif

// C++ Bool Compatibility
#if defined(__cplusplus)
typedef bool _Bool;
#endif

typedef signed int int32_t;
typedef signed short int16_t;
typedef signed char int8_t;

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;

typedef const int32_t sc32;
typedef const int16_t sc16;
typedef const int8_t sc8;

typedef volatile int32_t vs32;
typedef volatile int16_t vs16;
typedef volatile int8_t vs8;

typedef volatile const int32_t vsc32;
typedef volatile const int16_t vsc16;
typedef volatile const int8_t vsc8;

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef const uint32_t uc32;
typedef const uint16_t uc16;
typedef const uint8_t uc8;

typedef volatile uint32_t vu32;
typedef volatile uint16_t vu16;
typedef volatile uint8_t vu8;

typedef volatile const uint32_t vuc32;
typedef volatile const uint16_t vuc16;
typedef volatile const uint8_t vuc8;

typedef float float32_t;

#endif
