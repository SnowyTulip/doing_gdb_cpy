/**
 **************************************************************************
 * @file     qx_i2c.c
 * @version  v1.0.0
 * @date     2022-08-30
 * @brief    contains all the functions for the i2c firmware library
 **************************************************************************
 */

#include "qx_i2c.h"

void I2C_initController(I2C_TypeDef *i2c, u32 sysclkHz, u32 bitRate)
{ }

void I2C_enableInterrupt(I2C_TypeDef *i2c, I2C_InterruptFlag flag)
{
    switch (flag)
    {
        case I2C_INT_NONE:
        	i2c->IC_INTR_MASK.all = 0x0000U;
            break;
        case I2C_INT_RX_UNDERFLOW:
            i2c->IC_INTR_MASK.bit.M_RX_UNDER = 1;
            break;
        case I2C_INT_RX_OVERFLOW:
            i2c->IC_INTR_MASK.bit.M_RX_OVER = 1;
            break;
        case I2C_INT_RX_FULL:
            i2c->IC_INTR_MASK.bit.M_RX_FULL = 1;
            break;
        case I2C_INT_TX_OVERFLOW:
            i2c->IC_INTR_MASK.bit.M_TX_OVER = 1;
            break;
        case I2C_INT_TX_EMPTY:
            i2c->IC_INTR_MASK.bit.M_TX_EMPTY = 1;
            break;
        case I2C_INT_RD_REQUEST:
            i2c->IC_INTR_MASK.bit.M_RD_REQ = 1;
            break;
        case I2C_INT_TX_ABORT:
            i2c->IC_INTR_MASK.bit.M_TX_ABRT = 1;
            break;
        case I2C_INT_RX_DONE:
            i2c->IC_INTR_MASK.bit.M_RX_DONE = 1;
            break;
        case I2C_INT_ACTIVITY:
            i2c->IC_INTR_MASK.bit.M_ACTIVITY = 1;
            break;
        case I2C_INT_STOP_DET:
            i2c->IC_INTR_MASK.bit.M_STOP_DET = 1;
            break;
        case I2C_INT_START_DET:
            i2c->IC_INTR_MASK.bit.M_START_DET = 1;
            break;
        case I2C_INT_GEN_CALL:
            i2c->IC_INTR_MASK.bit.M_GEN_CALL = 1;
            break;
        case I2C_INT_RESTART_DET:
            i2c->IC_INTR_MASK.bit.M_RESTART_DET = 1;
            break;
        case I2C_INT_ALL:
            i2c->IC_INTR_MASK.all = I2C_INT_ALL;
            break;
    }
}

void I2C_disableInterrupt(I2C_TypeDef *i2c, I2C_InterruptFlag flag)
{
    switch (flag)
    {
        case I2C_INT_NONE:
            break;
        case I2C_INT_RX_UNDERFLOW:
            i2c->IC_INTR_MASK.bit.M_RX_UNDER = 0;
            break;
        case I2C_INT_RX_OVERFLOW:
            i2c->IC_INTR_MASK.bit.M_RX_OVER = 0;
            break;
        case I2C_INT_RX_FULL:
            i2c->IC_INTR_MASK.bit.M_RX_FULL = 0;
            break;
        case I2C_INT_TX_OVERFLOW:
            i2c->IC_INTR_MASK.bit.M_TX_OVER = 0;
            break;
        case I2C_INT_TX_EMPTY:
            i2c->IC_INTR_MASK.bit.M_TX_EMPTY = 0;
            break;
        case I2C_INT_RD_REQUEST:
            i2c->IC_INTR_MASK.bit.M_RD_REQ = 0;
            break;
        case I2C_INT_TX_ABORT:
            i2c->IC_INTR_MASK.bit.M_TX_ABRT = 0;
            break;
        case I2C_INT_RX_DONE:
            i2c->IC_INTR_MASK.bit.M_RX_DONE = 0;
            break;
        case I2C_INT_ACTIVITY:
            i2c->IC_INTR_MASK.bit.M_ACTIVITY = 0;
            break;
        case I2C_INT_STOP_DET:
            i2c->IC_INTR_MASK.bit.M_STOP_DET = 0;
            break;
        case I2C_INT_START_DET:
            i2c->IC_INTR_MASK.bit.M_START_DET = 0;
            break;
        case I2C_INT_GEN_CALL:
            i2c->IC_INTR_MASK.bit.M_GEN_CALL = 0;
            break;
        case I2C_INT_RESTART_DET:
            i2c->IC_INTR_MASK.bit.M_RESTART_DET = 0;
            break;
        case I2C_INT_ALL:
            i2c->IC_INTR_MASK.all = 0U;
            break;
    }
}

void I2C_clearInterruptStatus(I2C_TypeDef *i2c, I2C_InterruptFlag flag)
{
    u32 tmp;

    switch (flag)
    {
        case I2C_INT_NONE:
            break;
        case I2C_INT_RX_UNDERFLOW:
            tmp = i2c->IC_CLR_RX_UNDER;
            break;
        case I2C_INT_RX_OVERFLOW:
            tmp = i2c->IC_CLR_RX_OVER;
            break;
        case I2C_INT_RX_FULL:
            break;
        case I2C_INT_TX_OVERFLOW:
            tmp = i2c->IC_CLR_TX_OVER;
            break;
        case I2C_INT_TX_EMPTY:
            break;
        case I2C_INT_RD_REQUEST:
            tmp = i2c->IC_CLR_RD_REQ;
            break;
        case I2C_INT_TX_ABORT:
            tmp = i2c->IC_CLR_TX_ABRT;
            break;
        case I2C_INT_RX_DONE:
            tmp = i2c->IC_CLR_RX_DONE;
            break;
        case I2C_INT_ACTIVITY:
            tmp = i2c->IC_CLR_ACTIVITY;
            break;
        case I2C_INT_STOP_DET:
            tmp = i2c->IC_CLR_STOP_DET;
            break;
        case I2C_INT_START_DET:
            tmp = i2c->IC_CLR_START_DET;
            break;
        case I2C_INT_GEN_CALL:
            tmp = i2c->IC_CLR_GEN_CALL;
            break;
        case I2C_INT_RESTART_DET:
            tmp = i2c->IC_CLR_RESTART_DET;
            break;
        case I2C_INT_ALL:
            tmp = i2c->IC_CLR_INTR;
            break;
    }
}

void I2C_configModuleFrequency(I2C_TypeDef *i2c, u32 sysclkHz)
{ }
