/**
 **************************************************************************
 * @file     qx_flash.h
 * @version  v1.0.0
 * @date     2023-8-30
 **************************************************************************
 */

#ifndef QX_FLASH_H
#define QX_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"
#include "qx_sysctl.h"

struct CONFIG_BITS
{                  // bits description
    vu32 SRP1 : 1; // 0 Status Register Protection
    vu32 QE   : 1; // 1 QSPI Enable
    vu32 LB0  : 1; // 2 Security Register Lock
    vu32 LB1  : 1; // 3 Security Register Lock
    vu32 DC   : 1; // 4 Dummy Configuration
    vu32 rsvd : 1; // 5 reserved
    vu32 CMP  : 1; // 6 Complement Protect
    vu32 SUS  : 1; // 7 Suspend
};

union CONFIG_REG
{
    vu32 all;
    struct CONFIG_BITS bit;
};

struct STATUS_BITS
{                  // bits description
    vu32 WIP  : 1; // 1 Erase/Write In Progress
    vu32 WEL  : 1; // 2 Write Enable Latch
    vu32 BP0  : 1; // 3 Block 0 Protect
    vu32 BP1  : 1; // 4 Block 2 Protect
    vu32 BP2  : 1; // 5 Block 3 Protect
    vu32 BP3  : 1; // 6 Block 4 Protect
    vu32 SRP0 : 1; // 7 Status Register Protection
};

union STATUS_REG
{
    vu32 all;
    struct STATUS_BITS bit;
};

struct FLASH_CTRL_REGS
{
    vu32 ERASE;              // Flash Erase Register
    union CONFIG_REG CONFIG; // Flash Config Register
    union STATUS_REG STATUS; // Flash Status Register
};

#define Flash0CtrlRegs ((struct FLASH_CTRL_REGS *)FLASH_CTRL_BASE)

//*****************************************************************************
//
//! Values that can be passed to Flash_setBankPowerMode() as the bank parameter
//
//*****************************************************************************
typedef enum
{
    FLASH_ERASE_SECTOR = 0,
    FLASH_ERASE_BLOCK  = 1,
    FLASH_ERASE_CHIP   = 2,
} Flash_EraseType;

//*****************************************************************************
//
// Delay instruction that allows for register configuration to complete.
//
//*****************************************************************************
#define FLASH_DELAY_CONFIG __asm(" RPT #7 || NOP")

#ifdef DEBUG
static inline bool Flash_isCtrlBaseValid(uint32_t ctrlBase)
{
    return ((ctrlBase == FLASH0CTRL_BASE));
}
#endif

static inline void Flash_setClkDiv(u32 div)
{
    DevCfgRegs->FLASHCLKDIV.bit.CLK_FLASH_DIV_NUM = div;
}

static inline void Flash_enableQspiMode()
{
    Flash0CtrlRegs->CONFIG.bit.QE = 1;
    while (Flash0CtrlRegs->STATUS.bit.WIP)
        ;
}

static inline void Flash_disableQspiMode()
{
    Flash0CtrlRegs->CONFIG.bit.QE = 0;
    while (Flash0CtrlRegs->STATUS.bit.WIP)
        ;
}

static inline vu32 Flash_readWord(u32 addr)
{
    return HWREG(addr);
}

static inline void Flash_writeWord(u32 addr, vu32 val)
{
    HWREG(addr) = val;
}

extern void Flash_initModule(u32 div, u32 qspi_en);
extern void Flash_eraseChip(void);
extern void Flash_eraseBlock(vu32 addr);
extern void Flash_eraseSector(vu32 addr);

#ifdef __cplusplus
}
#endif

#endif
