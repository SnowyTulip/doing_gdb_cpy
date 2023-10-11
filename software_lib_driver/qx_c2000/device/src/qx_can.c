/**
 **************************************************************************
 * @file     qx_can.c
 * @version  v1.0.0
 * @date     2022-12-30
 * @brief    contains all the functions for the misc firmware library
 **************************************************************************
 */

#include "devicelib.h"

void CAN_sendStandardFrame(CAN_REGS *can, u32 sta_id, CAN_FrameDataType rtr, const void *msg, u8 msglen)
{
    u32 id = sta_id << 5;
    while (CAN_isTransmitterBusy(can))
        ;
    can->BUFF.BUFF[0] = (rtr << 2) | (msglen & 0x0F); /* SFF + RTR + msglen */
    can->BUFF.BUFF[1] = (id >> 8) & 0xFF;             /* high 8 identifier */
    can->BUFF.BUFF[2] = (id & 0xFF) | (rtr << 4);     /* low  3 identifier + RTR */
    for (u32 i = 0; i < (msglen & 0x0F); i++)
        can->BUFF.BUFF[3 + i] = *((u8 *)msg + i);
    CAN_setCmd(can, CAN_CMD_TRANS_REQUEST);
}

void CAN_sendExtendFrame(CAN_REGS *can, u32 ext_id, CAN_FrameDataType rtr, const void *msg, u8 msglen)
{
    u32 id = ext_id << 3;
    while (CAN_isTransmitterBusy(can))
        ;
    can->BUFF.BUFF[0] = 0x80 | (rtr << 2) | (msglen & 0x0F); // EFF + RTR + msglen
    can->BUFF.BUFF[1] = (id >> 24) & 0xFF;                   /* 28-21bit identifier */
    can->BUFF.BUFF[2] = (id >> 16) & 0xFF;                   /* 20-13bit identifier */
    can->BUFF.BUFF[3] = (id >> 8) & 0xFF;                    /* 12-5bit identifier */
    can->BUFF.BUFF[4] = (id & 0xFF) | (rtr << 2);            /* 4-0bit identifier + RTR */
    for (u32 i = 0; i < (msglen & 0x0F); i++)
        can->BUFF.BUFF[5 + i] = *((u8 *)msg + i);
    CAN_setCmd(can, CAN_CMD_TRANS_REQUEST);
}

void CAN_recvFrameBlocking(CAN_REGS *can, void *msg)
{
    for (u32 i = 0; i < 13; i++)
        *((u8 *)msg + i) = can->BUFF.BUFF[i];
    /* release the recv buffer for wait recv next frame */
    can->CMD.bit.RRB = 1;
}

void CAN_recvFrameNonBlocking(CAN_REGS *can, void *msg)
{
    if (can->SR.bit.RBS)
    {
        for (u32 i = 0; i < 13; i++)
            *((u8 *)msg + i) = can->BUFF.BUFF[i];
    }
    /* release the recv buffer for wait recv next frame */
    can->CMD.bit.RRB = 1;
}
