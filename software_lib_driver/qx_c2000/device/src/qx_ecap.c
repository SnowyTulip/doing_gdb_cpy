/**
 **************************************************************************
 * @file     qx_ecap.c
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#include "devicelib.h"

//*****************************************************************************
//
// ECAP_setEmulationMode
//
//*****************************************************************************
void ECAP_setEmulationMode(uint32_t base, ECAP_EmulationMode mode)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to FREE/SOFT bit
    //
    HWREGH(base + ECAP_O_ECCTL1)
        = ((HWREGH(base + ECAP_O_ECCTL1) & (~ECAP_ECCTL1_FREE_SOFT_M)) | ((uint16_t)mode << ECAP_ECCTL1_FREE_SOFT_S));
    EDIS;
}
