/**
 **************************************************************************
 * @file     qx_ipc.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_IPC_H
#define QX_IPC_H

#include "qx_define.h"

#define IPC_REC_START (0x007f0900)
#define IPC_SET_REG   (0x007f0900)
#define IPC_CLR_REG   (0x007f0904)
#define IPC_FLG_REG   (0x007f0908)
#define IPC_STS_REG   (0x007f090c)
#define IPC_ACK_REG   (0x007f0910)

#define IPC_CMD_START        (0x007f0a00)
#define IPC_SEND_COM_REG     (0x007f0a00)
#define IPC_SEND_ADDR_REG    (0x007f0a04)
#define IPC_SEND_DATA_REG    (0x007f0a08)
#define IPC_LOCAL_REPLY_REG  (0x007f0a0c)
#define IPC_REMOTE_REPLY_REG (0x007f0a10)
#define IPC_RECV_REPLY_REG   (0x007f0a14)
#define IPC_RECV_COM_REG     (0x007f0a18)
#define IPC_RECV_ADDR_REG    (0x007f0a1c)

//*****************************************************************************
//
//*****************************************************************************
typedef enum
{
    IPC_EVENT0 = 0,
    IPC_EVENT1,
    IPC_EVENT2,
    IPC_EVENT3,
    IPC_EVENT4,
    IPC_EVENT5,
    IPC_EVENT6,
    IPC_EVENT7,
    IPC_EVENT8,
    IPC_EVENT9,
    IPC_EVENT10,
    IPC_EVENT11,
    IPC_EVENT12,
    IPC_EVENT13,
    IPC_EVENT14,
    IPC_EVENT15,

    IPC_EVENT16,
    IPC_EVENT17,
    IPC_EVENT18,
    IPC_EVENT19,
    IPC_EVENT20,
    IPC_EVENT21,
    IPC_EVENT22,
    IPC_EVENT23,
    IPC_EVENT24,
    IPC_EVENT25,
    IPC_EVENT26,
    IPC_EVENT27,
    IPC_EVENT28,
    IPC_EVENT29,
    IPC_EVENT30,
    IPC_EVENT31,
} IPC_EVENT_INDEX;

//*****************************************************************************
//
//*****************************************************************************
typedef enum
{
    IPC_SHARE_REG_WR0 = 0x007f0a00,
    IPC_SHARE_REG_WR1 = 0x007f0a04,
    IPC_SHARE_REG_WR2 = 0x007f0a08,
    IPC_SHARE_REG_WR3 = 0x007f0a0c,
    IPC_SHARE_REG_R0  = 0x007f0a10,
    IPC_SHARE_REG_R1  = 0x007f0a14,
    IPC_SHARE_REG_R3  = 0x007f0a18,
    IPC_SHARE_REG_R4  = 0x007f0a1c,
} IPC_SHARE_REG;

//*****************************************************************************
//
//*****************************************************************************
#define GET_BIT(value, bit)   ((value) & (1 << (bit)))
#define SET_BIT(value, bit)   (value = (value | (1 << bit)))
#define CLEAR_BIT(value, bit) (value = (value & (~(1 << bit))))

//*****************************************************************************
//
//*****************************************************************************
STATIC_INLINE void IPC_set(IPC_EVENT_INDEX event)
{
    int *addr = (int *)IPC_SET_REG;
    int value = *addr;
    SET_BIT(value, event);
    *addr = value;
}

//*****************************************************************************
//
//*****************************************************************************
STATIC_INLINE void IPC_ack(IPC_EVENT_INDEX event)
{
    int *addr = (int *)IPC_ACK_REG;
    int value = *addr;
    SET_BIT(value, event);
    *addr = value;
    __builtin_dsp_nop();
}

//*****************************************************************************
//
//*****************************************************************************
STATIC_INLINE void IPC_clear(IPC_EVENT_INDEX event)
{
    int *addr = (int *)IPC_CLR_REG;
    int value = *addr;
    CLEAR_BIT(value, event);
    *addr = value;
}

//*****************************************************************************
// flag is affected by self
//*****************************************************************************
STATIC_INLINE int IPC_flag_all(void)
{
    int *addr = (int *)IPC_FLG_REG;
    int value = *addr;
    return value;
}

//*****************************************************************************
// flag is affected by the other core
//*****************************************************************************
STATIC_INLINE int IPC_status_all(void)
{
    int *addr = (int *)IPC_STS_REG;
    int value = *addr;
    return value;
}

//*****************************************************************************
// flag is affected by self
//*****************************************************************************
STATIC_INLINE int IPC_flag(IPC_EVENT_INDEX event)
{
    int *addr = (int *)IPC_FLG_REG;
    int value = *addr;
    value     = GET_BIT(value, event);
    return value;
}

//*****************************************************************************
// flag is affected by the other core
//*****************************************************************************
STATIC_INLINE int IPC_status(IPC_EVENT_INDEX event)
{
    int *addr = (int *)IPC_STS_REG;
    int value = *addr;
    value     = GET_BIT(value, event);
    return value;
}

//*****************************************************************************
//
//*****************************************************************************
STATIC_INLINE int IPC_read_send_com(void)
{
    int *addr = (int *)IPC_SEND_COM_REG;
    int value = *addr;
    return value;
}

//*****************************************************************************
//
//*****************************************************************************
STATIC_INLINE int IPC_read_share_reg(IPC_SHARE_REG reg)
{
    int *addr = (int *)reg;
    int value = *addr;
    return value;
}

//*****************************************************************************
//
//*****************************************************************************
STATIC_INLINE void IPC_write_share_reg(IPC_SHARE_REG reg, int value)
{
    int *addr = (int *)reg;
    *addr     = value;
}

//*****************************************************************************
// IPC_EVENT5 ~ IPC_EVENT31
//*****************************************************************************
void qx_ipc_post_block(IPC_EVENT_INDEX event);
void qx_ipc_wait_block(IPC_EVENT_INDEX event);
int qx_ipc_post(IPC_EVENT_INDEX event);
int qx_ipc_wait(IPC_EVENT_INDEX event);
#endif
