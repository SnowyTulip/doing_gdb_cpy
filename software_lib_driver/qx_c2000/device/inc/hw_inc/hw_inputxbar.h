#ifndef HW_INPUTXBAR_H
#define HW_INPUTXBAR_H

//*************************************************************************************************
//
// The following are defines for the XBAR register offsets
//
//*************************************************************************************************
#define XBAR_O_INPUT1SELECT      0x0U    // INPUT1 Input Select Register (GPIO0 to x)
#define XBAR_O_INPUT2SELECT      0x1U    // INPUT2 Input Select Register (GPIO0 to x)
#define XBAR_O_INPUT3SELECT      0x2U    // INPUT3 Input Select Register (GPIO0 to x)
#define XBAR_O_INPUT4SELECT      0x3U    // INPUT4 Input Select Register (GPIO0 to x)
#define XBAR_O_INPUT5SELECT      0x4U    // INPUT5 Input Select Register (GPIO0 to x)
#define XBAR_O_INPUT6SELECT      0x5U    // INPUT6 Input Select Register (GPIO0 to x)
#define XBAR_O_INPUT7SELECT      0x6U    // INPUT7 Input Select Register (GPIO0 to x)
#define XBAR_O_INPUT8SELECT      0x7U    // INPUT8 Input Select Register (GPIO0 to x)
#define XBAR_O_INPUT9SELECT      0x8U    // INPUT9 Input Select Register (GPIO0 to x)
#define XBAR_O_INPUT10SELECT     0x9U    // INPUT10 Input Select Register (GPIO0 to x)
#define XBAR_O_INPUT11SELECT     0xAU    // INPUT11 Input Select Register (GPIO0 to x)
#define XBAR_O_INPUT12SELECT     0xBU    // INPUT12 Input Select Register (GPIO0 to x)
#define XBAR_O_INPUT13SELECT     0xCU    // INPUT13 Input Select Register (GPIO0 to x)
#define XBAR_O_INPUT14SELECT     0xDU    // INPUT14 Input Select Register (GPIO0 to x)
#define XBAR_O_INPUT15SELECT     0xEU    // INPUT15 Input Select Register (GPIO0 to x)
#define XBAR_O_INPUT16SELECT     0xFU    // INPUT16 Input Select Register (GPIO0 to x)
#define XBAR_O_INPUTSELECTLOCK   0x1EU   // Input Select Lock Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the INPUTSELECTLOCK register
//
//*************************************************************************************************
#define XBAR_INPUTSELECTLOCK_INPUT1SELECT    0x1U      // Lock bit for INPUT1SELECT Register
#define XBAR_INPUTSELECTLOCK_INPUT2SELECT    0x2U      // Lock bit for INPUT2SELECT Register
#define XBAR_INPUTSELECTLOCK_INPUT3SELECT    0x4U      // Lock bit for INPUT3SELECT Register
#define XBAR_INPUTSELECTLOCK_INPUT4SELECT    0x8U      // Lock bit for INPUT4SELECT Register
#define XBAR_INPUTSELECTLOCK_INPUT5SELECT    0x10U     // Lock bit for INPUT5SELECT Register
#define XBAR_INPUTSELECTLOCK_INPUT6SELECT    0x20U     // Lock bit for INPUT6SELECT Register
#define XBAR_INPUTSELECTLOCK_INPUT7SELECT    0x40U     // Lock bit for INPUT7SELECT Register
#define XBAR_INPUTSELECTLOCK_INPUT8SELECT    0x80U     // Lock bit for INPUT8SELECT Register
#define XBAR_INPUTSELECTLOCK_INPUT9SELECT    0x100U    // Lock bit for INPUT9SELECT Register
#define XBAR_INPUTSELECTLOCK_INPUT10SELECT   0x200U    // Lock bit for INPUT10SELECT Register
#define XBAR_INPUTSELECTLOCK_INPUT11SELECT   0x400U    // Lock bit for INPUT11SELECT Register
#define XBAR_INPUTSELECTLOCK_INPUT12SELECT   0x800U    // Lock bit for INPUT12SELECT Register
#define XBAR_INPUTSELECTLOCK_INPUT13SELECT   0x1000U   // Lock bit for INPUT13SELECT Register
#define XBAR_INPUTSELECTLOCK_INPUT14SELECT   0x2000U   // Lock bit for INPUT14SELECT Register
#define XBAR_INPUTSELECTLOCK_INPUT15SELECT   0x4000U   // Lock bit for INPUT15SELECT Register
#define XBAR_INPUTSELECTLOCK_INPUT16SELECT   0x8000U   // Lock bit for INPUT16SELECT Register



#endif
