/**
 **************************************************************************
 * @file     qx_sci.c
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#include "devicelib.h"

void SCI_setConfig(sci_type *sci, u32 baud_int, u8 baud_fra, SCI_DataWidthType data_bit, SCI_StopBitType stop_bit,
    SCI_ParityType parity)
{
    SCI_setBaud(sci, baud_int, baud_fra);
    SCI_setParityMode(sci, parity);
    sci->LCR.bit.DLS  = data_bit;
    sci->LCR.bit.STOP = stop_bit;
}

void SCI_setParityMode(sci_type *sci, SCI_ParityType parity)
{
    while (sci->USR.bit.BUSY) /* wait no busy */
        ;
    if (parity == SCI_PARITY_NONE)
    {
        sci->LCR.bit.PEN = 0;
    }
    else if (parity == SCI_PARITY_EVEN)
    {
        sci->LCR.bit.PEN = 1;
        sci->LCR.bit.EPS = 1;
    }
    else if (parity == SCI_PARITY_ODD)
    {
        sci->LCR.bit.PEN = 1;
        sci->LCR.bit.EPS = 0;
    }
}

void SCI_setBaud(sci_type *sci, u32 baud_int, u8 baud_fra)
{
    while (sci->USR.bit.BUSY) /* wait no busy */
        ;
    sci->LCR.bit.DLAB = 1; /* unlock band rate set */
    sci->DLL          = (baud_int & 0x0000ffff);
    sci->DLH          = (baud_int & 0xffff0000) >> 16;
    sci->DLF          = baud_fra; /* bandrate Fractional part */
    sci->LCR.bit.DLAB = 0;        /* lock the band rate set */
}

void SCI_writeCharArray(sci_type *sci, void *array, u32 len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        while (!sci->LSR.bit.THRE)
            ;
        sci->THR = *((u8 *)array + i);
    }
}

void SCI_readCharArray(sci_type *sci, void *array, u32 len)
{
    int i = 0;
    for (i = 0; i < len; i++)
    {
        while (!sci->LSR.bit.DR)
            ;
        *((u8 *)array + i) = (u8)(sci->RBR);
    }
}
