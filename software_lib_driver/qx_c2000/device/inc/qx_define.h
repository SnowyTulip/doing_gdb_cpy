/**
 **************************************************************************
 * @file     qx_define.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_DEFINE_H
#define QX_DEFINE_H

#ifdef __cplusplus
extern "C" {
#endif

/* #include <stdint.h> */
#include <stdbool.h>

#include "qx_types.h"
#include "qx_cpu.h"
#include "qx_memmap.h"
#include "qx_debug.h"

#define VERSION_NUMBER 010000U

/* #define USE_ALWAYS_INLINE // use always inline toogle */

#ifndef USE_ALWAYS_INLINE
#define STATIC_INLINE static inline
#else
#define STATIC_INLINE __attribute__((always_inline)) static inline
#endif

#define STATIC_ALWAYS_INLINE __attribute__((always_inline)) static inline

#define SYS_CLK 16000000U /* system clock config */

STATIC_INLINE uint32_t Version_getLibVersion(void)
{
    return (VERSION_NUMBER);
}

#ifdef __cplusplus
}
#endif

#endif
