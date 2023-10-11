/**
 **************************************************************************
 * @file     qx_dma.c
 * @version  v1.0.0
 * @date     2023-05-23
 * @brief    contains all the functions for the SW_axi_dmac firmware library
 **************************************************************************
 */

#include "devicelib.h"
#include "qx_dma.h"
#include "common.h"

void DMAX_chanSetup(DMAXChanConfig *config)
{
    if (config->channel < 1 || config->channel > 6)
        return;

    if (DMAX_isChanEnable(config->channel))
        return;

    DMAX_setChanAddr(config->channel, config->src_addr, config->dst_addr);
    DMAX_setChanBlockTS(config->channel, config->block_size);
    DMAX_setChanWidth(config->channel, config->src_width, config->dst_width);
    DMAX_setBurstLength(config->channel, config->src_msize, config->dst_msize);
    DMAX_setTT_FC(config->channel, config->tt_fc);
    DMAX_setHSInterface(config->channel, config->src_hs_i, config->dst_hs_i);
    DMAX_setChanPrior(config->channel, config->prior);
}

void DMAX_interrupt(void)
{
    u8 i;
    u32 status, cstatus;

    status = DMAX_getIRQStatus();
    if (status & DMAX_IRQ_COMMON_ACTIVE)
        DMAX_DMACReset();
    if (status & DMAX_IRQ_CH1_ACTIVE)
    {
        cstatus = DMAX_getChanIntStatus(1);
        if (cstatus & DMAX_IRQ_ALL_ERR)
            DMAX_clearChanIntStatus(1, cstatus);
    }
    if (status & DMAX_IRQ_CH2_ACTIVE)
    {
        cstatus = DMAX_getChanIntStatus(2);
        if (cstatus & DMAX_IRQ_ALL_ERR)
            DMAX_clearChanIntStatus(2, cstatus);
    }
    if (status & DMAX_IRQ_CH3_ACTIVE)
    {
        cstatus = DMAX_getChanIntStatus(3);
        if (cstatus & DMAX_IRQ_ALL_ERR)
            DMAX_clearChanIntStatus(3, cstatus);
    }
    if (status & DMAX_IRQ_CH4_ACTIVE)
    {
        cstatus = DMAX_getChanIntStatus(4);
        if (cstatus & DMAX_IRQ_ALL_ERR)
            DMAX_clearChanIntStatus(4, cstatus);
    }
    if (status & DMAX_IRQ_CH1_ACTIVE)
    {
        cstatus = DMAX_getChanIntStatus(5);
        if (cstatus & DMAX_IRQ_ALL_ERR)
            DMAX_clearChanIntStatus(5, cstatus);
    }
    if (status & DMAX_IRQ_CH1_ACTIVE)
    {
        cstatus = DMAX_getChanIntStatus(6);
        if (cstatus & DMAX_IRQ_ALL_ERR)
            DMAX_clearChanIntStatus(6, cstatus);
    }
}

void DMAX_commonInit(void)
{
    DMAX_DMACEnable();
    DMAX_IRQEnable();
}
