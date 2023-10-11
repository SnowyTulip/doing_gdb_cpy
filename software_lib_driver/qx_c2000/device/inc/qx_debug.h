/**
 **************************************************************************
 * @file     qx_debug.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_DEBUG_H
#define QX_DEBUG_H

extern void __error__(const char *filename, uint32_t line);

#ifdef DEBUG
#define ASSERT(expr)                       \
    do                                     \
    {                                      \
        if (!(expr))                       \
            __error__(__FILE__, __LINE__); \
    } while ((_Bool)0)
#else
#define ASSERT(expr)
#endif

#endif
