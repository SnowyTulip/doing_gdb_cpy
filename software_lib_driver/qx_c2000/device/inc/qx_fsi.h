/**
 **************************************************************************
 * @file     qx_fsi.h
 * @version  v1.0.0
 * @date     2022-12-30
 **************************************************************************
 */

#ifndef QX_FSI_H
#define QX_FSI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qx_define.h"

//---------------------------------------------------------------------------
// FSI Individual Register Bit Definitions:

struct TX_MASTER_CTRL_BITS
{                      // bits description
    vu32 CORE_RST : 1; // 0 Transmitter Main Core Reset
    vu32 FLUSH    : 1; // 1 Flush Operation Start
    vu32 rsvd1    : 6; // 7:2 Reserved
    vu32 KEY      : 8; // 15:8 Write Key
};

union TX_MASTER_CTRL_REG
{
    vu32 all;
    struct TX_MASTER_CTRL_BITS bit;
};

struct TX_CLK_CTRL_BITS
{                          // bits description
    vu32 CLK_RST      : 1; // 0 Soft Reset for the Clock Divider
    vu32 CLK_EN       : 1; // 1 Clock Divider Enable
    vu32 PRESCALE_VAL : 8; // 9:2 Prescale value
    vu32 rsvd1        : 6; // 15:10 Reserved
};

union TX_CLK_CTRL_REG
{
    vu32 all;
    struct TX_CLK_CTRL_BITS bit;
};

struct TX_OPER_CTRL_LO_BITS
{                          // bits description
    vu32 DATA_WIDTH   : 2; // 1:0 Transmit Data width
    vu32 SPI_MODE     : 1; // 2 SPI Mode Select
    vu32 START_MODE   : 3; // 5:3 Transmission Start Mode Select
    vu32 SW_CRC       : 1; // 6 CRC Source Select
    vu32 PING_TO_MODE : 1; // 7 Ping Counter Reset Mode Select
    vu32 SEL_PLLCLK   : 1; // 8 Input Clock Select
    vu32 rsvd1        : 7; // 15:9 Reserved
};

union TX_OPER_CTRL_LO_REG
{
    vu32 all;
    struct TX_OPER_CTRL_LO_BITS bit;
};

struct TX_OPER_CTRL_HI_BITS
{                          // bits description
    vu32 EXT_TRIG_SEL : 5; // 4:0 External Trigger Select
    vu32 FORCE_ERR    : 1; // 5 Error Frame Force
    vu32 ECC_SEL      : 1; // 6 ECC Data Width Select
    vu32 rsvd1        : 9; // 15:7 Reserved
};

union TX_OPER_CTRL_HI_REG
{
    vu32 all;
    struct TX_OPER_CTRL_HI_BITS bit;
};

struct TX_FRAME_CTRL_BITS
{                        // bits description
    vu32 FRAME_TYPE : 4; // 3:0 Transmit Frame Type
    vu32 N_WORDS    : 4; // 7:4 Number of Words to be Transmitted
    vu32 rsvd1      : 7; // 14:8 Reserved
    vu32 START      : 1; // 15 Start Transmission
};

union TX_FRAME_CTRL_REG
{
    vu32 all;
    struct TX_FRAME_CTRL_BITS bit;
};

struct TX_FRAME_TAG_UDATA_BITS
{                       // bits description
    vu32 FRAME_TAG : 4; // 3:0 Frame Tag
    vu32 rsvd1     : 4; // 7:4 Reserved
    vu32 USER_DATA : 8; // 15:8 User Data
};

union TX_FRAME_TAG_UDATA_REG
{
    vu32 all;
    struct TX_FRAME_TAG_UDATA_BITS bit;
};

struct TX_BUF_PTR_LOAD_BITS
{                           // bits description
    vu32 BUF_PTR_LOAD : 4;  // 3:0 Buffer Pointer Force Load
    vu32 rsvd1        : 12; // 15:4 Reserved
};

union TX_BUF_PTR_LOAD_REG
{
    vu32 all;
    struct TX_BUF_PTR_LOAD_BITS bit;
};

struct TX_BUF_PTR_STS_BITS
{                           // bits description
    vu32 CURR_BUF_PTR  : 4; // 3:0 Current Buffer Pointer Index
    vu32 rsvd1         : 4; // 7:4 Reserved
    vu32 CURR_WORD_CNT : 5; // 12:8 Remaining Words in Buffer
    vu32 rsvd2         : 3; // 15:13 Reserved
};

union TX_BUF_PTR_STS_REG
{
    vu32 all;
    struct TX_BUF_PTR_STS_BITS bit;
};

struct TX_PING_CTRL_BITS
{                          // bits description
    vu32 CNT_RST      : 1; // 0 Ping Counter Reset
    vu32 TIMER_EN     : 1; // 1 Ping Counter Enable
    vu32 EXT_TRIG_EN  : 1; // 2 External Trigger Enable
    vu32 EXT_TRIG_SEL : 5; // 7:3 External Trigger Select
    vu32 rsvd1        : 8; // 15:8 Reserved
};

union TX_PING_CTRL_REG
{
    vu32 all;
    struct TX_PING_CTRL_BITS bit;
};


struct TX_PING_TO_REF_BIT
{                          // bits description
    vu32 TX_PING_TO_REF      : 32; // 0 Ping Counter Reset
};
union TX_PING_TO_REF_REG
{
    vu32 all;
    struct TX_PING_TO_REF_BIT bit;
};

struct TX_PING_TAG_BITS
{                    // bits description
    vu32 TAG   : 4;  // 3:0 Ping Frame Tag
    vu32 rsvd1 : 12; // 15:4 Reserved
};

union TX_PING_TAG_REG
{
    vu32 all;
    struct TX_PING_TAG_BITS bit;
};

struct TX_INT_CTRL_BITS
{                                  // bits description
    vu32 INT1_EN_FRAME_DONE   : 1; // 0 Enable Frame Done Interrupt to INT1
    vu32 INT1_EN_BUF_UNDERRUN : 1; // 1 Enable Buffer Underrun Interrupt to INT1
    vu32 INT1_EN_BUF_OVERRUN  : 1; // 2 Enable Buffer Overrun Interrupt to INT1
    vu32 INT1_EN_PING_TO      : 1; // 3 Enable Ping Timer Interrupt to INT1
    vu32 rsvd1                : 4; // 7:4 Reserved
    vu32 INT2_EN_FRAME_DONE   : 1; // 8 Enable Frame Done Interrupt to INT2
    vu32 INT2_EN_BUF_UNDERRUN : 1; // 9 Enable Buffer Underrun Interrupt to INT2
    vu32 INT2_EN_BUF_OVERRUN  : 1; // 10 Enable Buffer Overrun Interrupt to INT2
    vu32 INT2_EN_PING_TO      : 1; // 11 Enable Ping Timer Interrupt to INT2
    vu32 rsvd2                : 4; // 15:12 Reserved
};

union TX_INT_CTRL_REG
{
    vu32 all;
    struct TX_INT_CTRL_BITS bit;
};

struct TX_DMA_CTRL_BITS
{                         // bits description
    vu32 DMA_EVT_EN : 1;  // 0 DMA Event Enable
    vu32 rsvd1      : 15; // 15:1 Reserved
};

union TX_DMA_CTRL_REG
{
    vu32 all;
    struct TX_DMA_CTRL_BITS bit;
};

struct TX_LOCK_CTRL_BITS
{                   // bits description
    vu32 LOCK  : 1; // 0 Control Register Lock Enable
    vu32 rsvd1 : 7; // 7:1 Reserved
    vu32 KEY   : 8; // 15:8 Write Key
};

union TX_LOCK_CTRL_REG
{
    vu32 all;
    struct TX_LOCK_CTRL_BITS bit;
};

struct TX_EVT_STS_BITS
{                             // bits description
    vu32 FRAME_DONE     : 1;  // 0 Frame Done Flag
    vu32 BUF_UNDERRUN   : 1;  // 1 Buffer Underrun Flag
    vu32 BUF_OVERRUN    : 1;  // 2 Buffer Overrun Flag
    vu32 PING_TRIGGERED : 1;  // 3 Ping Frame Triggered Flag
    vu32 rsvd1          : 12; // 15:4 Reserved
};

union TX_EVT_STS_REG
{
    vu32 all;
    struct TX_EVT_STS_BITS bit;
};

struct TX_EVT_CLR_BITS
{                             // bits description
    vu32 FRAME_DONE     : 1;  // 0 Frame Done Flag Clear
    vu32 BUF_UNDERRUN   : 1;  // 1 Buffer Underrun Flag Clear
    vu32 BUF_OVERRUN    : 1;  // 2 Buffer Overrun Flag Clear
    vu32 PING_TRIGGERED : 1;  // 3 Ping Frame Triggered Flag Clear
    vu32 rsvd1          : 12; // 15:4 Reserved
};

union TX_EVT_CLR_REG
{
    vu32 all;
    struct TX_EVT_CLR_BITS bit;
};

struct TX_EVT_FRC_BITS
{                             // bits description
    vu32 FRAME_DONE     : 1;  // 0 Frame Done Flag Force
    vu32 BUF_UNDERRUN   : 1;  // 1 Buffer Underrun Flag Force
    vu32 BUF_OVERRUN    : 1;  // 2 Buffer Overrun Flag Force
    vu32 PING_TRIGGERED : 1;  // 3 Ping Frame Triggered Flag Force
    vu32 rsvd1          : 12; // 15:4 Reserved
};

union TX_EVT_FRC_REG
{
    vu32 all;
    struct TX_EVT_FRC_BITS bit;
};

struct TX_USER_CRC_BITS
{                      // bits description
    vu32 USER_CRC : 8; // 7:0 User-defined CRC
    vu32 rsvd1    : 8; // 15:8 Reserved
};

union TX_USER_CRC_REG
{
    vu32 all;
    struct TX_USER_CRC_BITS bit;
};

struct TX_ECC_DATA_BITS
{                        // bits description
    vu32 DATA_LOW  : 16; // 15:0 ECC Data Lower 16 Bits
    vu32 DATA_HIGH : 16; // 31:16 ECC Data Upper 16 Bits
};

union TX_ECC_DATA_REG
{
    vu32 all;
    struct TX_ECC_DATA_BITS bit;
};

struct TX_ECC_VAL_BITS
{                     // bits description
    vu32 ECC_VAL : 7; // 6:0 Computed ECC Value
    vu32 rsvd1   : 9; // 15:7 Reserved
};

union TX_ECC_VAL_REG
{
    vu32 all;
    struct TX_ECC_VAL_BITS bit;
};

struct FSI_TX_REGS
{
    union TX_MASTER_CTRL_REG TX_MASTER_CTRL;         //0x00 Transmit master control register
    union TX_CLK_CTRL_REG TX_CLK_CTRL;               //0x04 Transmit clock control register
    union TX_OPER_CTRL_LO_REG TX_OPER_CTRL_LO;       //0x08 Transmit operation control register low
    union TX_OPER_CTRL_HI_REG TX_OPER_CTRL_HI;       //0x0c Transmit operation control register high
    union TX_FRAME_CTRL_REG TX_FRAME_CTRL;           //0x10 Transmit frame control register
    union TX_FRAME_TAG_UDATA_REG TX_FRAME_TAG_UDATA; //0x14 Transmit frame tag and user data register
    union TX_BUF_PTR_LOAD_REG TX_BUF_PTR_LOAD;       //0x18 Transmit buffer pointer control load register
    union TX_BUF_PTR_STS_REG TX_BUF_PTR_STS;         //0x1c Transmit buffer pointer control status register
    union TX_PING_CTRL_REG TX_PING_CTRL;             //0x20 Transmit ping control register
    union TX_PING_TO_REF_REG TX_PING_TO_REF;         //0x24 Transmit ping timeout counter reference
    vu32 TX_PING_TO_CNT;                             //0x28 Transmit ping timeout current count
    union TX_INT_CTRL_REG TX_INT_CTRL;               //0x2c Transmit interrupt event control register
    union TX_LOCK_CTRL_REG TX_LOCK_CTRL;             //0x30 Transmit lock control register
    union TX_EVT_STS_REG TX_EVT_STS;                 //0x34 Transmit event and error status flag register
    union TX_EVT_CLR_REG TX_EVT_CLR;                 //0x38 Transmit event and error clear register
    union TX_EVT_FRC_REG TX_EVT_FRC;                 //0x3C Transmit event and error flag force register
    union TX_USER_CRC_REG TX_USER_CRC;               //0x40 Transmit user-defined CRC register                               // Reserved
    vu32 TX_BUF_BASE[16];                            //0x44-0x80 Base address for transmit buffer
    vu32 TX_DMA_CTRL;								 //0x84	 TX_DMA_CTR
    union TX_PING_TAG_REG TX_PING_TAG;               //0x88  Transmit ping tag register
};

struct RX_MASTER_CTRL_BITS
{                          // bits description
    vu32 CORE_RST     : 1; // 0 Receiver Main Core Reset
    vu32 INT_LOOPBACK : 1; // 1 Internal Loopback Enable
    vu32 SPI_PAIRING  : 1; // 2 Clock Pairing for SPI-like Behaviour
    vu32 rsvd1        : 5; // 7:3 Reserved
    vu32 KEY          : 8; // 15:8 Write Key
};

union RX_MASTER_CTRL_REG
{
    vu32 RX_MASTER_CTRL_all;
    struct RX_MASTER_CTRL_BITS bit;
};

struct RX_OPER_CTRL_BITS
{                              // bits description
    vu32 DATA_WIDTH       : 2; // 1:0 Receive Data Width Select
    vu32 SPI_MODE         : 1; // 2 SPI Mode Enable
    vu32 N_WORDS          : 4; // 6:3 Number of Words to be Received
    vu32 ECC_SEL          : 1; // 7 ECC Data Width Select
    vu32 PING_WD_RST_MODE : 1; // 8 Ping Watchdog Timeout Mode Select
    vu32 rsvd1            : 7; // 15:9 Reserved
};

union RX_OPER_CTRL_REG
{
    vu32 RX_OPER_CTRL_all;
    struct RX_OPER_CTRL_BITS bit;
};

struct RX_FRAME_INFO_BITS
{                         // bits description
    vu32 FRAME_TYPE : 4;  // 3:0 Received Frame Type
    vu32 rsvd1      : 12; // 15:4 Reserved
};

union RX_FRAME_INFO_REG
{
    vu32 RX_FRAME_INFO_all;
    struct RX_FRAME_INFO_BITS bit;
};

struct RX_FRAME_TAG_UDATA_BITS
{                       // bits description
    vu32 rsvd1     : 1; // 0 Reserved
    vu32 FRAME_TAG : 4; // 4:1 Received Frame Tag
    vu32 rsvd2     : 3; // 7:5 Reserved
    vu32 USER_DATA : 8; // 15:8 Received User Data
};

union RX_FRAME_TAG_UDATA_REG
{
    vu32 RX_FRAME_TAG_UDATA_all;
    struct RX_FRAME_TAG_UDATA_BITS bit;
};

struct RX_DMA_CTRL_BITS
{                         // bits description
    vu32 DMA_EVT_EN : 1;  // 0 DMA Event Enable
    vu32 rsvd1      : 15; // 15:1 Reserved
};

union RX_DMA_CTRL_REG
{
    vu32 RX_DMA_CTRL_all;
    struct RX_DMA_CTRL_BITS bit;
};

struct RX_EVT_STS_BITS
{                           // bits description
    vu32 PING_WD_TO    : 1; // 0 Ping Watchdog Timeout Flag
    vu32 FRAME_WD_TO   : 1; // 1 Frame Watchdog Timeout Flag.
    vu32 CRC_ERR       : 1; // 2 CRC Error Flag
    vu32 TYPE_ERR      : 1; // 3 Frame Type Error Flag
    vu32 EOF_ERR       : 1; // 4 End-of-Frame Error Flag
    vu32 BUF_OVERRUN   : 1; // 5 Receive Buffer Overrun Flag
    vu32 FRAME_DONE    : 1; // 6 Frame Done Flag
    vu32 BUF_UNDERRUN  : 1; // 7 Receive Buffer Underrun Flag
    vu32 ERR_FRAME     : 1; // 8 Error Frame Received Flag
    vu32 PING_FRAME    : 1; // 9 Ping Frame Received Flag
    vu32 FRAME_OVERRUN : 1; // 10 Frame Overrun Flag
    vu32 DATA_FRAME    : 1; // 11 Data Frame Received Flag
    vu32 rsvd1         : 4; // 15:12 Reserved
};

union RX_EVT_STS_REG
{
    vu32 RX_EVT_STS_all;
    struct RX_EVT_STS_BITS bit;
};

struct RX_CRC_INFO_BITS
{                      // bits description
    vu32 RX_CRC   : 8; // 7:0 Received CRC Value
    vu32 CALC_CRC : 8; // 15:8 Hardware Calculated CRC
};

union RX_CRC_INFO_REG
{
    vu32 RX_CRC_INFO_all;
    struct RX_CRC_INFO_BITS bit;
};

struct RX_EVT_CLR_BITS
{                           // bits description
    vu32 PING_WD_TO    : 1; // 0 Ping Watchdog Timeout Flag Clear
    vu32 FRAME_WD_TO   : 1; // 1 Frame Watchdog Timeout Flag Clear
    vu32 CRC_ERR       : 1; // 2 CRC Error Flag Clear
    vu32 TYPE_ERR      : 1; // 3 Frame Type Error Flag Clear
    vu32 EOF_ERR       : 1; // 4 End-of-Frame Error Flag Clear
    vu32 BUF_OVERRUN   : 1; // 5 Receive Buffer Overrun Flag Clear
    vu32 FRAME_DONE    : 1; // 6 Frame Done Flag Clear
    vu32 BUF_UNDERRUN  : 1; // 7 Receive Buffer Underrun Flag Clear
    vu32 ERR_FRAME     : 1; // 8 Error Frame Received Flag Clear
    vu32 PING_FRAME    : 1; // 9 PING Frame Received Flag Clear
    vu32 FRAME_OVERRUN : 1; // 10 Frame Overrun Flag Clear
    vu32 DATA_FRAME    : 1; // 11 Data Frame Received Flag Clear
    vu32 rsvd1         : 4; // 15:12 Reserved
};

union RX_EVT_CLR_REG
{
    vu32 RX_EVT_CLR_all;
    struct RX_EVT_CLR_BITS bit;
};

struct RX_EVT_FRC_BITS
{                           // bits description
    vu32 PING_WD_TO    : 1; // 0 Ping Watchdog Timeout Flag Force
    vu32 FRAME_WD_TO   : 1; // 1 Frame Watchdog Timeout Flag Force
    vu32 CRC_ERR       : 1; // 2 CRC Error Flag Force
    vu32 TYPE_ERR      : 1; // 3 Frame Type Error Flag Force
    vu32 EOF_ERR       : 1; // 4 End-of-Frame Error Flag Force
    vu32 BUF_OVERRUN   : 1; // 5 Receive Buffer Overrun Flag Force
    vu32 FRAME_DONE    : 1; // 6 Frame Done Flag Force
    vu32 BUF_UNDERRUN  : 1; // 7 Receive Buffer Underrun Flag Force
    vu32 ERR_FRAME     : 1; // 8 Error Frame Received Flag Force
    vu32 PING_FRAME    : 1; // 9 Ping Frame Received Flag Force
    vu32 FRAME_OVERRUN : 1; // 10 Frame Overrun Flag Force
    vu32 DATA_FRAME    : 1; // 11 Data Frame Received Flag Force
    vu32 rsvd1         : 4; // 15:12 Reserved
};

union RX_EVT_FRC_REG
{
    vu32 RX_EVT_FRC_all;
    struct RX_EVT_FRC_BITS bit;
};

struct RX_BUF_PTR_LOAD_BITS
{                           // bits description
    vu32 BUF_PTR_LOAD : 4;  // 3:0 Load value for receive buffer pointer
    vu32 rsvd1        : 12; // 15:4 Reserved
};

union RX_BUF_PTR_LOAD_REG
{
    vu32 RX_BUF_PTR_LOAD_all;
    struct RX_BUF_PTR_LOAD_BITS bit;
};

struct RX_BUF_PTR_STS_BITS
{                           // bits description
    vu32 CURR_BUF_PTR  : 4; // 3:0 Current Buffer Pointer Index
    vu32 rsvd1         : 4; // 7:4 Reserved
    vu32 CURR_WORD_CNT : 5; // 12:8 Available Words in Buffer
    vu32 rsvd2         : 3; // 15:13 Reserved
};

union RX_BUF_PTR_STS_REG
{
    vu32 RX_BUF_PTR_STS_all;
    struct RX_BUF_PTR_STS_BITS bit;
};

struct RX_FRAME_WD_CTRL_BITS
{                               // bits description
    vu32 FRAME_WD_CNT_RST : 1;  // 0 Frame Watchdog Counter Reset
    vu32 FRAME_WD_EN      : 1;  // 1 Frame Watchdog Counter Enable
    vu32 rsvd1            : 14; // 15:2 Reserved
};

union RX_FRAME_WD_CTRL_REG
{
    vu32 RX_FRAME_WD_CTRL_all;
    struct RX_FRAME_WD_CTRL_BITS bit;
};

struct RX_PING_WD_CTRL_BITS
{                          // bits description
    vu32 PING_WD_RST : 1;  // 0 Ping Watchdog Counter Reset
    vu32 PING_WD_EN  : 1;  // 1 Ping Watchdog Counter Enable
    vu32 rsvd1       : 14; // 15:2 Reserved
};

union RX_PING_WD_CTRL_REG
{
    vu32 RX_PING_WD_CTRL_all;
    struct RX_PING_WD_CTRL_BITS bit;
};

struct RX_PING_TAG_BITS
{                       // bits description
    vu32 rsvd1    : 1;  // 0 Reserved
    vu32 PING_TAG : 4;  // 4:1 Ping Frame Tag
    vu32 rsvd2    : 11; // 15:5 Reserved
};

union RX_PING_TAG_REG
{
    vu32 RX_PING_TAG_all;
    struct RX_PING_TAG_BITS bit;
};

struct RX_INT1_CTRL_BITS
{                                   // bits description
    vu32 INT1_EN_PING_WD_TO    : 1; // 0 Enable Ping Watchdog Timeout Interrupt to INT1
    vu32 INT1_EN_FRAME_WD_TO   : 1; // 1 Enable Frame Watchdog Timeout Interrupt to INT1
    vu32 INT1_EN_CRC_ERR       : 1; // 2 Enable CRC Error Interrupt to INT1
    vu32 INT1_EN_TYPE_ERR      : 1; // 3 Enable Frame Type Error Interrupt to INT1
    vu32 INT1_EN_EOF_ERR       : 1; // 4 Enable End-of-Frame Error Interrupt to INT1
    vu32 INT1_EN_OVERRUN       : 1; // 5 Enable Receive Buffer Overrun Interrupt to INT1
    vu32 INT1_EN_FRAME_DONE    : 1; // 6 Enable Frame Done Interrupt to INT1
    vu32 INT1_EN_UNDERRUN      : 1; // 7 Enable Buffer Underrun Interrupt to INT1
    vu32 INT1_EN_ERR_FRAME     : 1; // 8 Enable Error Frame Received Interrupt to INT1
    vu32 INT1_EN_PING_FRAME    : 1; // 9 Enable Ping Frame Received Interrupt to INT1
    vu32 INT1_EN_FRAME_OVERRUN : 1; // 10 Enable Frame Overrun Interrupt to INT1
    vu32 INT1_EN_DATA_FRAME    : 1; // 11 Enable Data Frame Received Interrupt to INT1
    vu32 rsvd1                 : 4; // 15:12 Reserved
};

union RX_INT1_CTRL_REG
{
    vu32 RX_INT1_CTRL_all;
    struct RX_INT1_CTRL_BITS bit;
};

//struct RX_INT2_CTRL_BITS
//{                                   // bits description
//    vu32 INT2_EN_PING_WD_TO    : 1; // 0 Enable Ping Watchdog Timeout Interrupt to INT2
//    vu32 INT2_EN_FRAME_WD_TO   : 1; // 1 Enable Frame Watchdog Timeout Interrupt to INT2
//    vu32 INT2_EN_CRC_ERR       : 1; // 2 Enable CRC Errror Interrupt to INT2
//    vu32 INT2_EN_TYPE_ERR      : 1; // 3 Enable Frame Type Error Interrupt to INT2
//    vu32 INT2_EN_EOF_ERR       : 1; // 4 Enable End-of-Frame Error Interrupt to INT2
//    vu32 INT2_EN_OVERRUN       : 1; // 5 Enable Buffer Overrun Interrupt to INT2
//    vu32 INT2_EN_FRAME_DONE    : 1; // 6 Enable Frame Done Interrupt to INT2
//    vu32 INT2_EN_UNDERRUN      : 1; // 7 Enable Buffer Underrun Interrupt to INT2
//    vu32 INT2_EN_ERR_FRAME     : 1; // 8 Enable Error Frame Received Interrupt to INT2
//    vu32 INT2_EN_PING_FRAME    : 1; // 9 Enable Ping Frame Received Interrupt to INT2
//    vu32 INT2_EN_FRAME_OVERRUN : 1; // 10 Enable Frame Overrun Interrupt to INT2
//    vu32 INT2_EN_DATA_FRAME    : 1; // 11 Enable Data Frame Received Interrupt to INT2
//    vu32 rsvd1                 : 4; // 15:12 Reserved
//};
//
//union RX_INT2_CTRL_REG
//{
//    vu32 all;
//    struct RX_INT2_CTRL_BITS bit;
//};

struct RX_LOCK_CTRL_BITS
{                   // bits description
    vu32 LOCK  : 1; // 0 Control Register Lock Enable
    vu32 rsvd1 : 7; // 7:1 Reserved
    vu32 KEY   : 8; // 15:8 Write Key
};

union RX_LOCK_CTRL_REG
{
    vu32 all;
    struct RX_LOCK_CTRL_BITS bit;
};

//struct RX_ECC_DATA_BITS
//{                        // bits description
//    vu32 DATA_LOW  : 16; // 15:0 ECC Data Lower 16 Bits
//    vu32 DATA_HIGH : 16; // 31:16 ECC Data Upper 16 Bits
//};
//
//union RX_ECC_DATA_REG
//{
//    vu32 all;
//    struct RX_ECC_DATA_BITS bit;
//};

//struct RX_ECC_VAL_BITS
//{                     // bits description
//    vu32 ECC_VAL : 7; // 6:0 Computed ECC Value
//    vu32 rsvd1   : 9; // 15:7 Reserved
//};
//
//union RX_ECC_VAL_REG
//{
//    vu32 all;
//    struct RX_ECC_VAL_BITS bit;
//};

//struct RX_ECC_LOG_BITS
//{                    // bits description
//    vu32 SBE   : 1;  // 0 Single Bit Error Detected
//    vu32 MBE   : 1;  // 1 Multiple Bit Errors Detected
//    vu32 rsvd1 : 14; // 15:2 Reserved
//};
//
//union RX_ECC_LOG_REG
//{
//    vu32 all;
//    struct RX_ECC_LOG_BITS bit;
//};

struct RX_DLYLINE_CTRL_BITS
{                       // bits description
    vu32 RXCLK_DLY : 5; // 4:0 Delay Line Tap Select for RXCLK
    vu32 RXD0_DLY  : 5; // 9:5 Delay Line Tap Select for RXD0
    vu32 RXD1_DLY  : 5; // 14:10 Delay Line Tap Select for RXD1
    vu32 rsvd1     : 1; // 15 Reserved
};

union RX_DLYLINE_CTRL_REG
{
    vu32 RX_DLYLINE_CTRL_all;
    struct RX_DLYLINE_CTRL_BITS bit;
};

struct RX_VIS_1_BITS
{                          // bits description
    vu32 rsvd1       : 3;  // 2:0 Reserved
    vu32 RX_CORE_STS : 1;  // 3 Receiver Core Status
    vu32 rsvd2       : 12; // 15:4 Reserved
    vu32 rsvd3       : 16; // 31:16 Reserved
};

union RX_VIS_1_REG
{
    vu32 RX_VIS_1_all;
    struct RX_VIS_1_BITS bit;
};

struct FSI_RX_REGS
{
    union RX_MASTER_CTRL_REG RX_MASTER_CTRL;         // 0x00 Receive master control register
    union RX_OPER_CTRL_REG RX_OPER_CTRL;             // 0x04 Receive operation control register
    union RX_FRAME_INFO_REG RX_FRAME_INFO;           // 0x08 Receive frame control register
    union RX_FRAME_TAG_UDATA_REG RX_FRAME_TAG_UDATA; // 0x0c Receive frame tag and user data register
    union RX_EVT_STS_REG RX_EVT_STS;                 // 0x10 Receive event and error status flag register
    union RX_CRC_INFO_REG RX_CRC_INFO;               // 0x14 Receive CRC info of received and computed CRC
    union RX_EVT_CLR_REG RX_EVT_CLR;                 // 0x18 Receive event and error clear registers
    union RX_EVT_FRC_REG RX_EVT_FRC;                 // 0x1c Receive event and error flag force register
    union RX_BUF_PTR_LOAD_REG RX_BUF_PTR_LOAD;       // 0x20 Receive buffer pointer load register
    union RX_BUF_PTR_STS_REG RX_BUF_PTR_STS;         // 0x24 Receive buffer pointer status register
    union RX_FRAME_WD_CTRL_REG RX_FRAME_WD_CTRL;     // 0x28 Receive frame watchdog control register
    vu32 RX_FRAME_WD_REF;                            // 0x2c Receive frame watchdog counter reference
    vu32 RX_FRAME_WD_CNT;                            // 0x30 Receive frame watchdog current count
    union RX_PING_WD_CTRL_REG RX_PING_WD_CTRL;       // 0x34 Receive ping watchdog control register
    vu32 RX_PING_WD_REF;                             // 0x38 Receive ping watchdog counter reference
    vu32 RX_PING_WD_CNT;                             // 0x3c Receive pingwatchdog current count
    union RX_INT1_CTRL_REG RX_INT1_CTRL;             // 0x40 Receive interrupt control register for RX_INT1
    union RX_LOCK_CTRL_REG RX_LOCK_CTRL;             // 0x44 Receive lock control register
    union RX_DLYLINE_CTRL_REG RX_DLYLINE_CTRL;       // 0x48 Receive delay line control register
    union RX_VIS_1_REG RX_VIS_1;                     // 0x4c Receive debug visibility register 1
    vu32 RX_BUF_BASE[16];                            // 0x50 address for receive data buffer
    union RX_DMA_CTRL_REG RX_DMA_CTRL;				 // 0x90 DMA_EVT
};

#define FsiTxaRegs ((struct FSI_TX_REGS *)FSITX_BASE)
#define FsiRxaRegs ((struct FSI_RX_REGS *)FSIRX_BASE)

//*****************************************************************************
// FSI
//*****************************************************************************
#define FSI_O_TX_MAIN_CTRL               FSI_O_TX_MASTER_CTRL
#define FSI_O_RX_MAIN_CTRL               FSI_O_RX_MASTER_CTRL

#define FSI_TX_MAIN_CTRL_CORE_RST        FSI_TX_MASTER_CTRL_CORE_RST
#define FSI_TX_MAIN_CTRL_FLUSH           FSI_TX_MASTER_CTRL_FLUSH
#define FSI_TX_MAIN_CTRL_KEY_S           FSI_TX_MASTER_CTRL_KEY_S
#define FSI_TX_MAIN_CTRL_KEY_M           FSI_TX_MASTER_CTRL_KEY_M

#define FSI_RX_MAIN_CTRL_CORE_RST        FSI_RX_MASTER_CTRL_CORE_RST
#define FSI_RX_MAIN_CTRL_INT_LOOPBACK    FSI_RX_MASTER_CTRL_INT_LOOPBACK
#define FSI_RX_MAIN_CTRL_SPI_PAIRING     FSI_RX_MASTER_CTRL_SPI_PAIRING
#define FSI_RX_MAIN_CTRL_INPUT_ISOLATE   FSI_RX_MASTER_CTRL_INPUT_ISOLATE
#define FSI_RX_MAIN_CTRL_DATA_FILTER_EN  FSI_RX_MASTER_CTRL_DATA_FILTER_EN
#define FSI_RX_MAIN_CTRL_KEY_S           FSI_RX_MASTER_CTRL_KEY_S
#define FSI_RX_MAIN_CTRL_KEY_M           FSI_RX_MASTER_CTRL_KEY_M

//*************************************************************************************************
//
// The following are defines for the FSI register offsets
//
//*************************************************************************************************
#define FSI_O_TX_MASTER_CTRL     0x0U // Transmit master control register
#define FSI_O_TX_CLK_CTRL        0x4U // Transmit clock control register
#define FSI_O_TX_OPER_CTRL_LO    0x8U // Transmit operation control register low
#define FSI_O_TX_OPER_CTRL_HI    0xCU // Transmit operation control register high
#define FSI_O_TX_FRAME_CTRL      0x10U // Transmit frame control register
#define FSI_O_TX_FRAME_TAG_UDATA 0x14U // Transmit frame tag and user data register
#define FSI_O_TX_BUF_PTR_LOAD    0x18U // Transmit buffer pointer control load register
#define FSI_O_TX_BUF_PTR_STS     0x1CU // Transmit buffer pointer control status register
#define FSI_O_TX_PING_CTRL   0x20U  // Transmit ping control register
#define FSI_O_TX_PING_TO_REF 0x24U  // Transmit ping timeout counter reference
#define FSI_O_TX_PING_TO_CNT 0x28U  // Transmit ping timeout current count
#define FSI_O_TX_INT_CTRL    0x2CU // Transmit interrupt event control register
#define FSI_O_TX_LOCK_CTRL   0x30U // Transmit lock control register
#define FSI_O_TX_EVT_STS     0x34U // Transmit event and error status flag register
#define FSI_O_TX_EVT_CLR     0x38U // Transmit event and error clear registers
#define FSI_O_TX_EVT_FRC     0x3CU // Transmit event and error flag force register
#define FSI_O_TX_USER_CRC    0x40U // Transmit user-defined CRC register

#define FSI_O_TX_ECC_DATA    0x20U // Transmit ECC data register
#define FSI_O_TX_ECC_VAL     0x22U // Transmit ECC value register
#define FSI_O_TX_BUF_BASE \
    (0x44U) // (0 <= i < 16) Base address for transmit
                  // buffer
#define FSI_O_TX_DMA_CTRL    0x84U // Transmit DMA event control register
#define FSI_O_TX_PING_TAG    0x88U// Transmit ping tag register

#define FSI_O_RX_MASTER_CTRL     0x0U  // Receive master control register
#define FSI_O_RX_OPER_CTRL       0x4U  // Receive operation control register
#define FSI_O_RX_FRAME_INFO      0x8U  // Receive frame control register
#define FSI_O_RX_FRAME_TAG_UDATA 0xCU  // Receive frame tag and user data register
#define FSI_O_RX_EVT_STS         0x10U  // Receive event and error status flag register
#define FSI_O_RX_CRC_INFO        0x14U  // Receive CRC info of received and computed CRC
#define FSI_O_RX_EVT_CLR         0x18U  // Receive event and error clear register
#define FSI_O_RX_EVT_FRC         0x1CU  // Receive event and error flag force register
#define FSI_O_RX_BUF_PTR_LOAD    0x20U  // Receive buffer pointer load register
#define FSI_O_RX_BUF_PTR_STS     0x24U  // Receive buffer pointer status register
#define FSI_O_RX_FRAME_WD_CTRL   0x28U // Receive frame watchdog control register
#define FSI_O_RX_FRAME_WD_REF    0x2CU // Receive frame watchdog counter reference
#define FSI_O_RX_FRAME_WD_CNT    0x30U // Receive frame watchdog current count
#define FSI_O_RX_PING_WD_CTRL    0x34U // Receive ping watchdog control register
#define FSI_O_RX_PING_TAG        0x17U // Receive ping tag register
#define FSI_O_RX_PING_WD_REF     0x38U // Receive ping watchdog counter reference
#define FSI_O_RX_PING_WD_CNT     0x3CU // Receive pingwatchdog current count
#define FSI_O_RX_INT1_CTRL       0x40U // Receive interrupt control register for
          // RX_INT1
//#define FSI_O_RX_INT2_CTRL \
//    0x40U                           // Receive interrupt control register for
#define FSI_O_RX_LOCK_CTRL    0x44U // Receive lock control register
#define FSI_O_RX_ECC_DATA     0x20U // Receive ECC data register
#define FSI_O_RX_ECC_VAL      0x22U // Receive ECC value register
#define FSI_O_RX_ECC_SEC_DATA 0x24U // Receive ECC corrected data register
#define FSI_O_RX_ECC_LOG      0x26U // Receive ECC log and status register
#define FSI_O_RX_DLYLINE_CTRL 0x48U // Receive delay line control register
#define FSI_O_RX_VIS_1        0x4CU // Receive debug visibility register 1
#define FSI_O_RX_BUF_BASE(i) \
    (0x50U + (i)) // (0 <= i < 16) Base address for receive data

#define FSI_O_RX_DMA_CTRL        0x90U  // Receive DMA event control register

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_MASTER_CTRL register
//
//*************************************************************************************************
#define FSI_TX_MASTER_CTRL_CORE_RST 0x1U // Transmitter Main Core Reset
#define FSI_TX_MASTER_CTRL_FLUSH    0x2U // Flush Operation Start
#define FSI_TX_MASTER_CTRL_KEY_S    8U
#define FSI_TX_MASTER_CTRL_KEY_M    0xFF00U // Write Key

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_CLK_CTRL register
//
//*************************************************************************************************
#define FSI_TX_CLK_CTRL_CLK_RST        0x1U // Soft Reset for the Clock Divider
#define FSI_TX_CLK_CTRL_CLK_EN         0x2U // Clock Divider Enable
#define FSI_TX_CLK_CTRL_PRESCALE_VAL_S 2U
#define FSI_TX_CLK_CTRL_PRESCALE_VAL_M 0x3FCU // Prescale value

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_OPER_CTRL_LO register
//
//*************************************************************************************************
#define FSI_TX_OPER_CTRL_LO_DATA_WIDTH_S 0U
#define FSI_TX_OPER_CTRL_LO_DATA_WIDTH_M 0x3U // Transmit Data width
#define FSI_TX_OPER_CTRL_LO_SPI_MODE     0x4U // SPI Mode Select
#define FSI_TX_OPER_CTRL_LO_START_MODE_S 3U
#define FSI_TX_OPER_CTRL_LO_START_MODE_M 0x38U  // Transmission Start Mode Select
#define FSI_TX_OPER_CTRL_LO_SW_CRC       0x40U  // CRC Source Select
#define FSI_TX_OPER_CTRL_LO_PING_TO_MODE 0x80U  // Ping Counter Reset Mode Select
#define FSI_TX_OPER_CTRL_LO_SEL_PLLCLK   0x100U // Input Clock Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_OPER_CTRL_HI register
//
//*************************************************************************************************
#define FSI_TX_OPER_CTRL_HI_EXT_TRIG_SEL_S 0U
#define FSI_TX_OPER_CTRL_HI_EXT_TRIG_SEL_M 0x1FU // External Trigger Select
#define FSI_TX_OPER_CTRL_HI_FORCE_ERR      0x20U // Error Frame Force
#define FSI_TX_OPER_CTRL_HI_ECC_SEL        0x40U // ECC Data Width Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_FRAME_CTRL register
//
//*************************************************************************************************
#define FSI_TX_FRAME_CTRL_FRAME_TYPE_S 0U
#define FSI_TX_FRAME_CTRL_FRAME_TYPE_M 0xFU // Transmit Frame Type
#define FSI_TX_FRAME_CTRL_N_WORDS_S    4U
#define FSI_TX_FRAME_CTRL_N_WORDS_M    0xF0U   // Number of Words to be Transmitted
#define FSI_TX_FRAME_CTRL_START        0x8000U // Start Transmission

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_FRAME_TAG_UDATA register
//
//*************************************************************************************************
#define FSI_TX_FRAME_TAG_UDATA_FRAME_TAG_S 0U
#define FSI_TX_FRAME_TAG_UDATA_FRAME_TAG_M 0xFU // Frame Tag
#define FSI_TX_FRAME_TAG_UDATA_USER_DATA_S 8U
#define FSI_TX_FRAME_TAG_UDATA_USER_DATA_M 0xFF00U // User Data

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_BUF_PTR_LOAD register
//
//*************************************************************************************************
#define FSI_TX_BUF_PTR_LOAD_BUF_PTR_LOAD_S 0U
#define FSI_TX_BUF_PTR_LOAD_BUF_PTR_LOAD_M 0xFU // Buffer Pointer Force Load

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_BUF_PTR_STS register
//
//*************************************************************************************************
#define FSI_TX_BUF_PTR_STS_CURR_BUF_PTR_S  0U
#define FSI_TX_BUF_PTR_STS_CURR_BUF_PTR_M  0xFU // Current Buffer Pointer Index
#define FSI_TX_BUF_PTR_STS_CURR_WORD_CNT_S 8U
#define FSI_TX_BUF_PTR_STS_CURR_WORD_CNT_M 0x1F00U // Remaining Words in Buffer

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_PING_CTRL register
//
//*************************************************************************************************
#define FSI_TX_PING_CTRL_CNT_RST        0x1U // Ping Counter Reset
#define FSI_TX_PING_CTRL_TIMER_EN       0x2U // Ping Counter Enable
#define FSI_TX_PING_CTRL_EXT_TRIG_EN    0x4U // External Trigger Enable
#define FSI_TX_PING_CTRL_EXT_TRIG_SEL_S 3U
#define FSI_TX_PING_CTRL_EXT_TRIG_SEL_M 0xF8U // External Trigger Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_PING_TAG register
//
//*************************************************************************************************
#define FSI_TX_PING_TAG_TAG_S 0U
#define FSI_TX_PING_TAG_TAG_M 0xFU // Ping Frame Tag

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_INT_CTRL register
//
//*************************************************************************************************
#define FSI_TX_INT_CTRL_INT1_EN_FRAME_DONE   0x1U   // Enable Frame Done Interrupt to INT1
#define FSI_TX_INT_CTRL_INT1_EN_BUF_UNDERRUN 0x2U   // Enable Buffer Underrun Interrupt to INT1
#define FSI_TX_INT_CTRL_INT1_EN_BUF_OVERRUN  0x4U   // Enable Buffer Overrun Interrupt to INT1
#define FSI_TX_INT_CTRL_INT1_EN_PING_TO      0x8U   // Enable Ping Timer Interrupt to INT1
#define FSI_TX_INT_CTRL_INT2_EN_FRAME_DONE   0x100U // Enable Frame Done Interrupt to INT2
#define FSI_TX_INT_CTRL_INT2_EN_BUF_UNDERRUN 0x200U // Enable Buffer Underrun Interrupt to INT2
#define FSI_TX_INT_CTRL_INT2_EN_BUF_OVERRUN  0x400U // Enable Buffer Overrun Interrupt to INT2
#define FSI_TX_INT_CTRL_INT2_EN_PING_TO      0x800U // Enable Ping Timer Interrupt to INT2

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_DMA_CTRL register
//
//*************************************************************************************************
#define FSI_TX_DMA_CTRL_DMA_EVT_EN 0x1U // DMA Event Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_LOCK_CTRL register
//
//*************************************************************************************************
#define FSI_TX_LOCK_CTRL_LOCK  0x1U // Control Register Lock Enable
#define FSI_TX_LOCK_CTRL_KEY_S 8U
#define FSI_TX_LOCK_CTRL_KEY_M 0xFF00U // Write Key

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_EVT_STS register
//
//*************************************************************************************************
#define FSI_TX_EVT_STS_FRAME_DONE     0x1U // Frame Done Flag
#define FSI_TX_EVT_STS_BUF_UNDERRUN   0x2U // Buffer Underrun Flag
#define FSI_TX_EVT_STS_BUF_OVERRUN    0x4U // Buffer Overrun Flag
#define FSI_TX_EVT_STS_PING_TRIGGERED 0x8U // Ping Frame Triggered Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_EVT_CLR register
//
//*************************************************************************************************
#define FSI_TX_EVT_CLR_FRAME_DONE     0x1U // Frame Done Flag Clear
#define FSI_TX_EVT_CLR_BUF_UNDERRUN   0x2U // Buffer Underrun Flag Clear
#define FSI_TX_EVT_CLR_BUF_OVERRUN    0x4U // Buffer Overrun Flag Clear
#define FSI_TX_EVT_CLR_PING_TRIGGERED 0x8U // Ping Frame Triggered Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_EVT_FRC register
//
//*************************************************************************************************
#define FSI_TX_EVT_FRC_FRAME_DONE     0x1U // Frame Done Flag Force
#define FSI_TX_EVT_FRC_BUF_UNDERRUN   0x2U // Buffer Underrun Flag Force
#define FSI_TX_EVT_FRC_BUF_OVERRUN    0x4U // Buffer Overrun Flag Force
#define FSI_TX_EVT_FRC_PING_TRIGGERED 0x8U // Ping Frame Triggered Flag Force

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_USER_CRC register
//
//*************************************************************************************************
#define FSI_TX_USER_CRC_USER_CRC_S 0U
#define FSI_TX_USER_CRC_USER_CRC_M 0xFFU // User-defined CRC

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_ECC_DATA register
//
//*************************************************************************************************
#define FSI_TX_ECC_DATA_DATA_LOW_S  0U
#define FSI_TX_ECC_DATA_DATA_LOW_M  0xFFFFU // ECC Data Lower 16 Bits
#define FSI_TX_ECC_DATA_DATA_HIGH_S 16U
#define FSI_TX_ECC_DATA_DATA_HIGH_M 0xFFFF0000U // ECC Data Upper 16 Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the TX_ECC_VAL register
//
//*************************************************************************************************
#define FSI_TX_ECC_VAL_ECC_VAL_S 0U
#define FSI_TX_ECC_VAL_ECC_VAL_M 0x7FU // Computed ECC Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_MASTER_CTRL register
//
//*************************************************************************************************
#define FSI_RX_MASTER_CTRL_CORE_RST     0x1U // Receiver Main Core Reset
#define FSI_RX_MASTER_CTRL_INT_LOOPBACK 0x2U // Internal Loopback Enable
#define FSI_RX_MASTER_CTRL_SPI_PAIRING  0x4U // Clock Pairing for SPI-like Behaviour
#define FSI_RX_MASTER_CTRL_KEY_S        8U
#define FSI_RX_MASTER_CTRL_KEY_M        0xFF00U // Write Key

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_OPER_CTRL register
//
//*************************************************************************************************
#define FSI_RX_OPER_CTRL_DATA_WIDTH_S     0U
#define FSI_RX_OPER_CTRL_DATA_WIDTH_M     0x3U // Receive Data Width Select
#define FSI_RX_OPER_CTRL_SPI_MODE         0x4U // SPI Mode Enable
#define FSI_RX_OPER_CTRL_N_WORDS_S        3U
#define FSI_RX_OPER_CTRL_N_WORDS_M        0x78U  // Number of Words to be Received
#define FSI_RX_OPER_CTRL_ECC_SEL          0x80U  // ECC Data Width Select
#define FSI_RX_OPER_CTRL_PING_WD_RST_MODE 0x100U // Ping Watchdog Timeout Mode Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_FRAME_INFO register
//
//*************************************************************************************************
#define FSI_RX_FRAME_INFO_FRAME_TYPE_S 0U
#define FSI_RX_FRAME_INFO_FRAME_TYPE_M 0xFU // Received Frame Type

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_FRAME_TAG_UDATA register
//
//*************************************************************************************************
#define FSI_RX_FRAME_TAG_UDATA_FRAME_TAG_S 1U
#define FSI_RX_FRAME_TAG_UDATA_FRAME_TAG_M 0x1EU // Received Frame Tag
#define FSI_RX_FRAME_TAG_UDATA_USER_DATA_S 8U
#define FSI_RX_FRAME_TAG_UDATA_USER_DATA_M 0xFF00U // Received User Data

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_DMA_CTRL register
//
//*************************************************************************************************
#define FSI_RX_DMA_CTRL_DMA_EVT_EN 0x1U // DMA Event Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_EVT_STS register
//
//*************************************************************************************************
#define FSI_RX_EVT_STS_PING_WD_TO    0x1U   // Ping Watchdog Timeout Flag
#define FSI_RX_EVT_STS_FRAME_WD_TO   0x2U   // Frame Watchdog Timeout Flag.
#define FSI_RX_EVT_STS_CRC_ERR       0x4U   // CRC Error Flag
#define FSI_RX_EVT_STS_TYPE_ERR      0x8U   // Frame Type Error Flag
#define FSI_RX_EVT_STS_EOF_ERR       0x10U  // End-of-Frame Error Flag
#define FSI_RX_EVT_STS_BUF_OVERRUN   0x20U  // Receive Buffer Overrun Flag
#define FSI_RX_EVT_STS_FRAME_DONE    0x40U  // Frame Done Flag
#define FSI_RX_EVT_STS_BUF_UNDERRUN  0x80U  // Receive Buffer Underrun Flag
#define FSI_RX_EVT_STS_ERR_FRAME     0x100U // Error Frame Received Flag
#define FSI_RX_EVT_STS_PING_FRAME    0x200U // Ping Frame Received Flag
#define FSI_RX_EVT_STS_FRAME_OVERRUN 0x400U // Frame Overrun Flag
#define FSI_RX_EVT_STS_DATA_FRAME    0x800U // Data Frame Received Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_CRC_INFO register
//
//*************************************************************************************************
#define FSI_RX_CRC_INFO_RX_CRC_S   0U
#define FSI_RX_CRC_INFO_RX_CRC_M   0xFFU // Received CRC Value
#define FSI_RX_CRC_INFO_CALC_CRC_S 8U
#define FSI_RX_CRC_INFO_CALC_CRC_M 0xFF00U // Hardware Calculated CRC

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_EVT_CLR register
//
//*************************************************************************************************
#define FSI_RX_EVT_CLR_PING_WD_TO    0x1U   // Ping Watchdog Timeout Flag Clear
#define FSI_RX_EVT_CLR_FRAME_WD_TO   0x2U   // Frame Watchdog Timeout Flag Clear
#define FSI_RX_EVT_CLR_CRC_ERR       0x4U   // CRC Error Flag Clear
#define FSI_RX_EVT_CLR_TYPE_ERR      0x8U   // Frame Type Error Flag Clear
#define FSI_RX_EVT_CLR_EOF_ERR       0x10U  // End-of-Frame Error Flag Clear
#define FSI_RX_EVT_CLR_BUF_OVERRUN   0x20U  // Receive Buffer Overrun Flag Clear
#define FSI_RX_EVT_CLR_FRAME_DONE    0x40U  // Frame Done Flag Clear
#define FSI_RX_EVT_CLR_BUF_UNDERRUN  0x80U  // Receive Buffer Underrun Flag Clear
#define FSI_RX_EVT_CLR_ERR_FRAME     0x100U // Error Frame Received Flag Clear
#define FSI_RX_EVT_CLR_PING_FRAME    0x200U // PING Frame Received Flag Clear
#define FSI_RX_EVT_CLR_FRAME_OVERRUN 0x400U // Frame Overrun Flag Clear
#define FSI_RX_EVT_CLR_DATA_FRAME    0x800U // Data Frame Received Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_EVT_FRC register
//
//*************************************************************************************************
#define FSI_RX_EVT_FRC_PING_WD_TO    0x1U   // Ping Watchdog Timeout Flag Force
#define FSI_RX_EVT_FRC_FRAME_WD_TO   0x2U   // Frame Watchdog Timeout Flag Force
#define FSI_RX_EVT_FRC_CRC_ERR       0x4U   // CRC Error Flag Force
#define FSI_RX_EVT_FRC_TYPE_ERR      0x8U   // Frame Type Error Flag Force
#define FSI_RX_EVT_FRC_EOF_ERR       0x10U  // End-of-Frame Error Flag Force
#define FSI_RX_EVT_FRC_BUF_OVERRUN   0x20U  // Receive Buffer Overrun Flag Force
#define FSI_RX_EVT_FRC_FRAME_DONE    0x40U  // Frame Done Flag Force
#define FSI_RX_EVT_FRC_BUF_UNDERRUN  0x80U  // Receive Buffer Underrun Flag Force
#define FSI_RX_EVT_FRC_ERR_FRAME     0x100U // Error Frame Received Flag Force
#define FSI_RX_EVT_FRC_PING_FRAME    0x200U // Ping Frame Received Flag Force
#define FSI_RX_EVT_FRC_FRAME_OVERRUN 0x400U // Frame Overrun Flag Force
#define FSI_RX_EVT_FRC_DATA_FRAME    0x800U // Data Frame Received Flag Force

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_BUF_PTR_LOAD register
//
//*************************************************************************************************
#define FSI_RX_BUF_PTR_LOAD_BUF_PTR_LOAD_S 0U
#define FSI_RX_BUF_PTR_LOAD_BUF_PTR_LOAD_M 0xFU // Load value for receive buffer pointer

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_BUF_PTR_STS register
//
//*************************************************************************************************
#define FSI_RX_BUF_PTR_STS_CURR_BUF_PTR_S  0U
#define FSI_RX_BUF_PTR_STS_CURR_BUF_PTR_M  0xFU // Current Buffer Pointer Index
#define FSI_RX_BUF_PTR_STS_CURR_WORD_CNT_S 8U
#define FSI_RX_BUF_PTR_STS_CURR_WORD_CNT_M 0x1F00U // Available Words in Buffer

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_FRAME_WD_CTRL register
//
//*************************************************************************************************
#define FSI_RX_FRAME_WD_CTRL_FRAME_WD_CNT_RST 0x1U // Frame Watchdog Counter Reset
#define FSI_RX_FRAME_WD_CTRL_FRAME_WD_EN      0x2U // Frame Watchdog Counter Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_PING_WD_CTRL register
//
//*************************************************************************************************
#define FSI_RX_PING_WD_CTRL_PING_WD_RST 0x1U // Ping Watchdog Counter Reset
#define FSI_RX_PING_WD_CTRL_PING_WD_EN  0x2U // Ping Watchdog Counter Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_PING_TAG register
//
//*************************************************************************************************
#define FSI_RX_PING_TAG_PING_TAG_S 1U
#define FSI_RX_PING_TAG_PING_TAG_M 0x1EU // Ping Frame Tag

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_INT1_CTRL register
//
//*************************************************************************************************
#define FSI_RX_INT1_CTRL_INT1_EN_PING_WD_TO \
    0x1U // Enable Ping Watchdog Timeout Interrupt
         // to INT1
#define FSI_RX_INT1_CTRL_INT1_EN_FRAME_WD_TO \
    0x2U                                      // Enable Frame Watchdog Timeout
                                              // Interrupt to INT1
#define FSI_RX_INT1_CTRL_INT1_EN_CRC_ERR 0x4U // Enable CRC Error Interrupt to INT1
#define FSI_RX_INT1_CTRL_INT1_EN_TYPE_ERR \
    0x8U // Enable Frame Type Error Interrupt to
         // INT1
#define FSI_RX_INT1_CTRL_INT1_EN_EOF_ERR \
    0x10U // Enable End-of-Frame Error Interrupt to
          // INT1
#define FSI_RX_INT1_CTRL_INT1_EN_OVERRUN \
    0x20U                                         // Enable Receive Buffer Overrun
                                                  // Interrupt to INT1
#define FSI_RX_INT1_CTRL_INT1_EN_FRAME_DONE 0x40U // Enable Frame Done Interrupt to INT1
#define FSI_RX_INT1_CTRL_INT1_EN_UNDERRUN \
    0x80U // Enable Buffer Underrun Interrupt to
          // INT1
#define FSI_RX_INT1_CTRL_INT1_EN_ERR_FRAME \
    0x100U // Enable Error Frame Received Interrupt
           // to INT1
#define FSI_RX_INT1_CTRL_INT1_EN_PING_FRAME \
    0x200U                                            // Enable Ping Frame Received Interrupt
                                                      // to INT1
#define FSI_RX_INT1_CTRL_INT1_EN_FRAME_OVERRUN 0x400U // Enable Frame Overrun Interrupt to INT1
#define FSI_RX_INT1_CTRL_INT1_EN_DATA_FRAME \
    0x800U // Enable Data Frame Received Interrupt
           // to INT1

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_INT2_CTRL register
//
//*************************************************************************************************
#define FSI_RX_INT2_CTRL_INT2_EN_PING_WD_TO \
    0x1U // Enable Ping Watchdog Timeout Interrupt
         // to INT2
#define FSI_RX_INT2_CTRL_INT2_EN_FRAME_WD_TO \
    0x2U                                      // Enable Frame Watchdog Timeout
                                              // Interrupt to INT2
#define FSI_RX_INT2_CTRL_INT2_EN_CRC_ERR 0x4U // Enable CRC Errror Interrupt to INT2
#define FSI_RX_INT2_CTRL_INT2_EN_TYPE_ERR \
    0x8U // Enable Frame Type Error Interrupt to
         // INT2
#define FSI_RX_INT2_CTRL_INT2_EN_EOF_ERR \
    0x10U // Enable End-of-Frame Error Interrupt to
          // INT2
#define FSI_RX_INT2_CTRL_INT2_EN_OVERRUN \
    0x20U                                         // Enable Buffer Overrun Interrupt to
                                                  // INT2
#define FSI_RX_INT2_CTRL_INT2_EN_FRAME_DONE 0x40U // Enable Frame Done Interrupt to INT2
#define FSI_RX_INT2_CTRL_INT2_EN_UNDERRUN \
    0x80U // Enable Buffer Underrun Interrupt to
          // INT2
#define FSI_RX_INT2_CTRL_INT2_EN_ERR_FRAME \
    0x100U // Enable Error Frame Received Interrupt
           // to INT2
#define FSI_RX_INT2_CTRL_INT2_EN_PING_FRAME \
    0x200U                                            // Enable Ping Frame Received Interrupt
                                                      // to INT2
#define FSI_RX_INT2_CTRL_INT2_EN_FRAME_OVERRUN 0x400U // Enable Frame Overrun Interrupt to INT2
#define FSI_RX_INT2_CTRL_INT2_EN_DATA_FRAME \
    0x800U // Enable Data Frame Received Interrupt
           // to INT2

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_LOCK_CTRL register
//
//*************************************************************************************************
#define FSI_RX_LOCK_CTRL_LOCK  0x1U // Control Register Lock Enable
#define FSI_RX_LOCK_CTRL_KEY_S 8U
#define FSI_RX_LOCK_CTRL_KEY_M 0xFF00U // Write Key

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_ECC_DATA register
//
//*************************************************************************************************
#define FSI_RX_ECC_DATA_DATA_LOW_S  0U
#define FSI_RX_ECC_DATA_DATA_LOW_M  0xFFFFU // ECC Data Lower 16 Bits
#define FSI_RX_ECC_DATA_DATA_HIGH_S 16U
#define FSI_RX_ECC_DATA_DATA_HIGH_M 0xFFFF0000U // ECC Data Upper 16 Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_ECC_VAL register
//
//*************************************************************************************************
#define FSI_RX_ECC_VAL_ECC_VAL_S 0U
#define FSI_RX_ECC_VAL_ECC_VAL_M 0x7FU // Computed ECC Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_ECC_LOG register
//
//*************************************************************************************************
#define FSI_RX_ECC_LOG_SBE 0x1U // Single Bit Error Detected
#define FSI_RX_ECC_LOG_MBE 0x2U // Multiple Bit Errors Detected

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_DLYLINE_CTRL register
//
//*************************************************************************************************
#define FSI_RX_DLYLINE_CTRL_RXCLK_DLY_S 0U
#define FSI_RX_DLYLINE_CTRL_RXCLK_DLY_M 0x1FU // Delay Line Tap Select for RXCLK
#define FSI_RX_DLYLINE_CTRL_RXD0_DLY_S  5U
#define FSI_RX_DLYLINE_CTRL_RXD0_DLY_M  0x3E0U // Delay Line Tap Select for RXD0
#define FSI_RX_DLYLINE_CTRL_RXD1_DLY_S  10U
#define FSI_RX_DLYLINE_CTRL_RXD1_DLY_M  0x7C00U // Delay Line Tap Select for RXD1

//*************************************************************************************************
//
// The following are defines for the bit fields in the RX_VIS_1 register
//
//*************************************************************************************************
#define FSI_RX_VIS_1_RX_CORE_STS 0x8U // Receiver Core Status

//*****************************************************************************
//
// FSI Tx defines
//
//*****************************************************************************

//*****************************************************************************
//
// FSI Tx events defines
//
// Values that can be passed to APIs to enable/disable interrupts and
// also to set/get/clear event status on FSI Tx operation.
//
// There are 4 supported interrupts related to Tx events-
// All are available as event status as well except 4th one.
//
//*****************************************************************************
#define FSI_TX_EVT_FRAME_DONE   (0x0001U) //!< Frame transmission done
#define FSI_TX_EVT_BUF_UNDERRUN (0x0002U) //!< Transmit buffer is underrun
#define FSI_TX_EVT_BUF_OVERRUN  (0x0004U) //!< Transmit buffer is overrun
#define FSI_TX_EVT_PING_TIMEOUT (0x0008U) //!< Ping Timer event

//*****************************************************************************
//
//! \brief Flag for event status not available as interrupt
//!
//! Ping frame transmission upon hardware trigger(ping watchdog or
//! external trigger) is shown as event status.
//
//*****************************************************************************
#define FSI_TX_EVT_PING_HW_TRIG (0x0008U)

//*****************************************************************************
//
//! \brief Mask of all Tx Events, ORing all event defines
//
//*****************************************************************************
#define FSI_TX_EVTMASK (0x000FU)

//*****************************************************************************
//
//! \brief Maximum number of external input for triggering frame-transmission
//
//*****************************************************************************
#define FSI_TX_MAX_NUM_EXT_TRIGGERS (0x0020U)

//*****************************************************************************
//
//! \brief Shifts needed to control FSI Tx interrupt generation on INT2
//
//*****************************************************************************
#define FSI_TX_INT2_CTRL_S (0x8U)

//*****************************************************************************
//
// FSI Rx Defines
//
//*****************************************************************************

//*****************************************************************************
//
// FSI Rx event defines
//
// Values that can be passed to APIs to enable/disable interrupts and
// also to set/get/clear event status on FSI Rx operation.
//
// There are 12 supported interrupts related to Rx events.
// All are available as event status as well.
//
//*****************************************************************************
#define FSI_RX_EVT_PING_WD_TIMEOUT  (0x0001U) //!< Ping Watchdog times out
#define FSI_RX_EVT_FRAME_WD_TIMEOUT (0x0002U) //!< Frame Watchdog times out
#define FSI_RX_EVT_CRC_ERR          (0x0004U) //!< Hardware computed CRC error
#define FSI_RX_EVT_TYPE_ERR         (0x0008U) //!< Invalid Frame type detected
#define FSI_RX_EVT_EOF_ERR          (0x0010U) //!< Invalid EndofFrame bit-pattern
#define FSI_RX_EVT_OVERRUN          (0x0020U) //!< Buffer Overrun in Rx buffer
#define FSI_RX_EVT_FRAME_DONE       (0x0040U) //!< Received frame without errors
#define FSI_RX_EVT_UNDERRUN         (0x0080U) //!< Software reads empty Rx buffer
#define FSI_RX_EVT_ERR_FRAME        (0x0100U) //!< Received error frame
#define FSI_RX_EVT_PING_FRAME       (0x0200U) //!< Received ping frame
#define FSI_RX_EVT_FRAME_OVERRUN    (0x0400U) //!< FRAME_DONE not cleared on receiving new frame
#define FSI_RX_EVT_DATA_FRAME       (0x0800U) //!< Received data frame

//*****************************************************************************
//
//! \brief Mask of all Rx Events, ORing all event defines
//
//*****************************************************************************
#define FSI_RX_EVTMASK (0x0FFFU)

//*****************************************************************************
//
//! \brief Maximum value in Rx delay line tap control
//
//*****************************************************************************
#define FSI_RX_MAX_DELAY_LINE_VAL (0x001FU)

//*****************************************************************************
//
// Common defines for both FSI Tx and Rx
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Maximum data length(16 words) for user/software defined data frame
//
//*****************************************************************************
#define FSI_MAX_LEN_NWORDS_DATA (0x000FU)

//*****************************************************************************
//
//! \brief Maximum value for user data field(8 bits)
//
//*****************************************************************************
#define FSI_MAX_VALUE_USERDATA (0x00FFU)

//*****************************************************************************
//
//! \brief Maximum value of Buffer pointer offset(4 bits)
//
//*****************************************************************************
#define FSI_MAX_VALUE_BUF_PTR_OFF (0x000FU)

//*****************************************************************************
//
//! \brief Key value for writing some FSI Tx/Rx registers
//
//*****************************************************************************
#define FSI_CTRL_REG_KEY (0x00A5U)

//*****************************************************************************
//
// typedefs
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Data lines used for transmit/receive operation
//!
//! \details Supported number of data lines is only 2 - 1 lane or 2 lanes
//
//*****************************************************************************
typedef enum
{
    FSI_DATA_WIDTH_1_LANE = 0x0000U,
    FSI_DATA_WIDTH_2_LANE = 0x0001U
} FSI_DataWidth;

//*****************************************************************************
//
//! \brief List of TX submodules that can be reset, can be used with reset APIs
//!
//! \details Three kind of resets can be made-
//!          1) reset entire Tx Module
//!          2) reset only TX clock
//!          3) reset ping timeout counter
//
//*****************************************************************************
typedef enum
{
    FSI_TX_MAIN_CORE_RESET        = 0x0000U,
    FSI_TX_CLOCK_RESET            = 0x0001U,
    FSI_TX_PING_TIMEOUT_CNT_RESET = 0x0002U
} FSI_TxSubmoduleInReset;

//*****************************************************************************
//
//! \brief Start Mode for Tx frame transmission
//!
//! \details Three start modes(that is, how transmission will start) are
//! supported-
//!          1. SW write of START bit in \b TX_PKT_CTRL register
//!          2. Rising edge on external trigger
//!          3. Either SW write of START bit or Frame completion
//
//*****************************************************************************
typedef enum
{
    FSI_TX_START_FRAME_CTRL              = 0x0000U,
    FSI_TX_START_EXT_TRIG                = 0x0001U,
    FSI_TX_START_FRAME_CTRL_OR_UDATA_TAG = 0x0002U
} FSI_TxStartMode;

//*****************************************************************************
//
//! \brief Various FSI frame types
//!
//! \details Three frame types exist-
//!          - \b Ping: Used for checking line integrity, can be sent by
//!                     software or automatically by hardware.
//!          - \b Error: Used typically during error conditions or when one
//!                      side wants to signal the other side for attention.
//!          - \b Data: Two subtypes exist based on data-length-
//!                     a) \b Fixed (1/2/4/6 words)
//!                     b) \b Nwords Software programs number of data words
//!
//!  \note 4 bit code for frame types- 0x1, 0x2 and 0x8 to 0xE are reserved
//
//*****************************************************************************
typedef enum
{
    FSI_FRAME_TYPE_PING       = 0x0000U,
    FSI_FRAME_TYPE_ERROR      = 0x000FU,
    FSI_FRAME_TYPE_1WORD_DATA = 0x0004U,
    FSI_FRAME_TYPE_2WORD_DATA = 0x0005U,
    FSI_FRAME_TYPE_4WORD_DATA = 0x0006U,
    FSI_FRAME_TYPE_6WORD_DATA = 0x0007U,
    FSI_FRAME_TYPE_NWORD_DATA = 0x0003U
} FSI_FrameType;

//*****************************************************************************
//
//! \brief Possible values of a FSI frame
//!
//! \details 4 bit field inside FSI frame is available to set tag value(0-15)
//
//*****************************************************************************
typedef enum
{
    FSI_FRAME_TAG0  = 0x0000U,
    FSI_FRAME_TAG1  = 0x0001U,
    FSI_FRAME_TAG2  = 0x0002U,
    FSI_FRAME_TAG3  = 0x0003U,
    FSI_FRAME_TAG4  = 0x0004U,
    FSI_FRAME_TAG5  = 0x0005U,
    FSI_FRAME_TAG6  = 0x0006U,
    FSI_FRAME_TAG7  = 0x0007U,
    FSI_FRAME_TAG8  = 0x0008U,
    FSI_FRAME_TAG9  = 0x0009U,
    FSI_FRAME_TAG10 = 0x000AU,
    FSI_FRAME_TAG11 = 0x000BU,
    FSI_FRAME_TAG12 = 0x000CU,
    FSI_FRAME_TAG13 = 0x000DU,
    FSI_FRAME_TAG14 = 0x000EU,
    FSI_FRAME_TAG15 = 0x000FU
} FSI_FrameTag;

//*****************************************************************************
//
//! \brief Ping timeout mode
//!
//! \details Ping timeout can reset and restart only on hardware initiated PING
//!          frames (PING Watchdog timeout)
//!          OR
//!          on any software initiated frame being sent out also based on
//!          which mode is selected
//
//*****************************************************************************
typedef enum
{
    FSI_PINGTIMEOUT_ON_HWINIT_PING_FRAME   = 0x0000U,
    FSI_PINGTIMEOUT_ON_HWSWINIT_PING_FRAME = 0x0001U
} FSI_PingTimeoutMode;

//! \brief ECC Computation width- 16 bit or 32 bit
//!
typedef enum
{
    FSI_32BIT_ECC_COMPUTE = 0x0000U,
    FSI_16BIT_ECC_COMPUTE = 0x0001U
} FSI_ECCComputeWidth;

//*****************************************************************************
//
//! \brief Interrupt lines supported in FSI
//!
//! \details Any event on FSI Tx or Rx can be enabled to trigger interrupt on 2
//!          interrupt lines to CPU/CLA- \b INT1 and \b INT2
//
//*****************************************************************************
typedef enum
{
    FSI_INT1 = 0x0000U,
    FSI_INT2 = 0x0001U
} FSI_InterruptNum;

//*****************************************************************************
//
//! \brief List of RX modules that can be reset, can be used with reset APIs
//!
//! \details Three submodules can be reset-
//!          1) RX main core
//!          2) frame watchdog counter
//!          3) ping watchdog counter
//
//*****************************************************************************
typedef enum
{
    FSI_RX_MAIN_CORE_RESET    = 0x0000U,
    FSI_RX_FRAME_WD_CNT_RESET = 0x0001U,
    FSI_RX_PING_WD_CNT_RESET  = 0x0002U
} FSI_RxSubmoduleInReset;

//*****************************************************************************
//
//! \brief Available Rx lines for delay tap selection
//!
//! \details Delay tapping can be done on 3 lines- 1)RXCLK 2)RXD0 and 3)RXD1
//
//*****************************************************************************
typedef enum
{
    FSI_RX_DELAY_CLK = 0x0000U,
    FSI_RX_DELAY_D0  = 0x0001U,
    FSI_RX_DELAY_D1  = 0x0002U
} FSI_RxDelayTapType;

//*****************************************************************************
//
//! \brief Indexes of available EPWM SOC triggers
//!
//! \details There are 16 ePWM SOC events as external triggers for FSI frame
//!          transfers. Indexes 24:31 are reserved out of total 32
//!          muxed external triggers.
//
//*****************************************************************************
typedef enum
{
    FSI_EXT_TRIGSRC_EPWM_XBARTRIP4  = 0U,
    FSI_EXT_TRIGSRC_EPWM_XBARTRIP5  = 1U,
    FSI_EXT_TRIGSRC_EPWM_XBARTRIP7  = 2U,
    FSI_EXT_TRIGSRC_EPWM_XBARTRIP8  = 3U,
    FSI_EXT_TRIGSRC_EPWM_XBARTRIP9  = 4U,
    FSI_EXT_TRIGSRC_EPWM_XBARTRIP10 = 5U,
    FSI_EXT_TRIGSRC_EPWM_XBARTRIP11 = 6U,
    FSI_EXT_TRIGSRC_EPWM_XBARTRIP12 = 7U,
    FSI_EXT_TRIGSRC_EPWM1_SOCA      = 8U,
    FSI_EXT_TRIGSRC_EPWM1_SOCB      = 9U,
    FSI_EXT_TRIGSRC_EPWM2_SOCA      = 10U,
    FSI_EXT_TRIGSRC_EPWM2_SOCB      = 11U,
    FSI_EXT_TRIGSRC_EPWM3_SOCA      = 12U,
    FSI_EXT_TRIGSRC_EPWM3_SOCB      = 13U,
    FSI_EXT_TRIGSRC_EPWM4_SOCA      = 14U,
    FSI_EXT_TRIGSRC_EPWM4_SOCB      = 15U,
    FSI_EXT_TRIGSRC_EPWM5_SOCA      = 16U,
    FSI_EXT_TRIGSRC_EPWM5_SOCB      = 17U,
    FSI_EXT_TRIGSRC_EPWM6_SOCA      = 18U,
    FSI_EXT_TRIGSRC_EPWM6_SOCB      = 19U,
    FSI_EXT_TRIGSRC_EPWM7_SOCA      = 20U,
    FSI_EXT_TRIGSRC_EPWM7_SOCB      = 21U,
    FSI_EXT_TRIGSRC_EPWM8_SOCA      = 22U,
    FSI_EXT_TRIGSRC_EPWM8_SOCB      = 23U,
} FSI_ExtFrameTriggerSrc;

//*****************************************************************************
//
// FSI Tx function prototypes/defintion
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Validates if FSI-Tx base address is correct
//!
//! \param[in] base is the base address of the FSI-Tx module
//!
//! \return returns \b true if the base address is valid and \b false otherwise
//
//*****************************************************************************
#ifdef DEBUG
static inline bool FSI_isTxBaseValid(uint32_t base)
{
    return ((base == FSITXA_BASE));
}
#endif

//*****************************************************************************
//brief Sends FLUSH pattern
//*****************************************************************************
static inline void FSI_sendTxFlush(uint32_t base)
{
    EALLOW;

//    FsiTxaRegs->TX_MASTER_CTRL.bit.KEY= 0xA5U;
//    FsiTxaRegs->TX_MASTER_CTRL.bit.FLUSH = 1;
    HWREGH(base + FSI_O_TX_MAIN_CTRL) |= ((uint16_t)FSI_TX_MAIN_CTRL_FLUSH |
                                           (FSI_CTRL_REG_KEY <<
                                           FSI_TX_MAIN_CTRL_KEY_S));

    EDIS;
}

//*****************************************************************************
// \brief Stops FLUSH pattern transmission
//*****************************************************************************
static inline void FSI_stopTxFlush(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    EALLOW;
//    FsiTxaRegs->TX_MASTER_CTRL.bit.KEY= 0xA5U;
//    FsiTxaRegs->TX_MASTER_CTRL.bit.FLUSH = 0;

    HWREGH(base + FSI_O_TX_MAIN_CTRL) = (((~FSI_TX_MAIN_CTRL_FLUSH) &
                                             HWREGH(base + FSI_O_TX_MAIN_CTRL)) |
                                             (FSI_CTRL_REG_KEY <<
                                             FSI_TX_MAIN_CTRL_KEY_S));
    EDIS;

}

//*****************************************************************************
// \brief Selects PLL clock as source for clock dividers
//*****************************************************************************
static inline void FSI_selectTxPLLClock(uint32_t base)
{
    EALLOW;

    FsiTxaRegs->TX_OPER_CTRL_LO.bit.SEL_PLLCLK=1;

    EDIS;
}

//*****************************************************************************
//
//! \brief sets clock division prescalar and enables the transmit clock
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_enableTxClock(uint32_t base)
{
    EALLOW;

    FsiTxaRegs->TX_CLK_CTRL.bit.CLK_EN =1;

    EDIS;
}

//*****************************************************************************
//
//! \brief Disables transmit clock
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_disableTxClock(uint32_t base)
{
    EALLOW;

    FsiTxaRegs->TX_CLK_CTRL.bit.CLK_EN = 0;

    EDIS;
}

//*****************************************************************************
//brief Sets the prescalar clock keeping the transmit clock in reset
//*****************************************************************************
static inline void FSI_configPrescalar(uint32_t base, uint16_t preScaleValue)
{


    EALLOW;
    // Disable Tx clock
    FsiTxaRegs->TX_CLK_CTRL.bit.CLK_EN = 0;

    // Set prescalar value
    FsiTxaRegs->TX_CLK_CTRL.bit.PRESCALE_VAL =  preScaleValue;

    EDIS;
}

//*****************************************************************************
// Sets Data width for transmission
//*****************************************************************************
static inline void FSI_setTxDataWidth(uint32_t base, FSI_DataWidth dataWidth)
{
    EALLOW;

    FsiTxaRegs->TX_OPER_CTRL_LO.bit.DATA_WIDTH = dataWidth;

    EDIS;
}

//*****************************************************************************
//  Enables SPI compatible mode
//*****************************************************************************
static inline void FSI_enableTxSPIMode(uint32_t base)
{
    EALLOW;
    FsiTxaRegs->TX_OPER_CTRL_LO.bit.SPI_MODE = 1;
    EDIS;
}

//*****************************************************************************
//  Disables SPI compatible mode
//*****************************************************************************
static inline void FSI_disableTxSPIMode(uint32_t base)
{
    EALLOW;
    FsiTxaRegs->TX_OPER_CTRL_LO.bit.SPI_MODE = 0 ;
    EDIS;
}

//*****************************************************************************
// Sets start mode for any frame transmission
//*****************************************************************************
static inline void FSI_setTxStartMode(uint32_t base, FSI_TxStartMode txStartMode)
{
    EALLOW;
    FsiTxaRegs->TX_OPER_CTRL_LO.bit.START_MODE  = txStartMode ;
    EDIS;
}

//*****************************************************************************
// Setting for when Ping timeout can reset and restart
//*****************************************************************************
static inline void FSI_setTxPingTimeoutMode(uint32_t base, FSI_PingTimeoutMode pingTimeoutMode)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    EALLOW;

    if (pingTimeoutMode == FSI_PINGTIMEOUT_ON_HWSWINIT_PING_FRAME)
    {
        FsiTxaRegs->TX_OPER_CTRL_LO.bit.PING_TO_MODE = 1;
    }
    else
    {
        FsiTxaRegs->TX_OPER_CTRL_LO.bit.PING_TO_MODE = 0 ;
    }

    EDIS;
}

//*****************************************************************************
// Sets a particular external input to trigger transmission
//*****************************************************************************
static inline void FSI_setTxExtFrameTrigger(uint32_t base, uint16_t extInputNum)
{
    EALLOW;
    FsiTxaRegs->TX_OPER_CTRL_HI.bit.EXT_TRIG_SEL = extInputNum;
    EDIS;
}

//*****************************************************************************
// Enables CRC value of a data frame to be forced to zero
//*****************************************************************************
static inline void FSI_enableTxCRCForceError(uint32_t base)
{
    EALLOW;
    FsiTxaRegs->TX_OPER_CTRL_HI.bit.FORCE_ERR = 1;
    EDIS;
}

//*****************************************************************************
//
//! \brief Disables forcing of CRC value of a data frame to zero
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_disableTxCRCForceError(uint32_t base)
{
    EALLOW;
    FsiTxaRegs->TX_OPER_CTRL_HI.bit.FORCE_ERR = 0;
    EDIS;
}

//*****************************************************************************
//
//! \brief Select between 16-bit and 32-bit ECC computation
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] eccComputeWidth is ECC Computation width
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_setTxECCComputeWidth(uint32_t base, FSI_ECCComputeWidth eccComputeWidth)
{
    EALLOW;

    if (eccComputeWidth == FSI_16BIT_ECC_COMPUTE)
    {
        FsiTxaRegs->TX_OPER_CTRL_HI.bit.ECC_SEL = 1;
    }
    else
    {
    	FsiTxaRegs->TX_OPER_CTRL_HI.bit.ECC_SEL = 0;
    }

    EDIS;
}

//*****************************************************************************
// Sets frame type for transmission
//*****************************************************************************
static inline void FSI_setTxFrameType(uint32_t base, FSI_FrameType frameType)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));
    FsiTxaRegs->TX_FRAME_CTRL.bit.FRAME_TYPE = frameType;
}

//*****************************************************************************
// Sets the frame size if frame type is user/software defined frame
//*****************************************************************************
static inline void FSI_setTxSoftwareFrameSize(uint32_t base, uint16_t nWords)
{
    ASSERT((nWords != 0) && ((nWords - 1) <= FSI_MAX_LEN_NWORDS_DATA));

    FsiTxaRegs->TX_FRAME_CTRL.bit.N_WORDS = nWords-1;

}

//*****************************************************************************
//Starts transmitting frames
//*****************************************************************************
static inline void FSI_startTxTransmit(uint32_t base)
{
    FsiTxaRegs->TX_FRAME_CTRL.bit.START =1 ;
}

//*****************************************************************************
// Sets frame tag for transmission
//*****************************************************************************
static inline void FSI_setTxFrameTag(uint32_t base, FSI_FrameTag frameTag)
{
    FsiTxaRegs->TX_FRAME_TAG_UDATA.bit.FRAME_TAG =frameTag ;
}

//*****************************************************************************
//
//! \brief Sets user defined data for transmission
//!        It is an extra data field(8 bit) apart from regular data
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] userDefData 8 bit user defined data value
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_setTxUserDefinedData(uint32_t base, uint16_t userDefData)
{
    ASSERT(userDefData <= FSI_MAX_VALUE_USERDATA);

    FsiTxaRegs->TX_FRAME_TAG_UDATA.bit.USER_DATA = userDefData;
}
//*****************************************************************************
// Sets the value for transmit buffer pointer at desired location
//*****************************************************************************
static inline void FSI_setTxBufferPtr(uint32_t base, uint16_t bufPtrOff)
{

    ASSERT(bufPtrOff <= FSI_MAX_VALUE_BUF_PTR_OFF);

    EALLOW;
    FsiTxaRegs->TX_BUF_PTR_LOAD.bit.BUF_PTR_LOAD = bufPtrOff;
    EDIS;
}

//*****************************************************************************
//
//! \brief Returns current buffer pointer location
//!
//! \param[in]  base is the FSI Tx module base address
//!
//! \return current buffer pointer location
//!
//! \note   there could be lag due to synchronization hence value is accurate
//!         only when no current transmission is happening
//
//*****************************************************************************
static inline uint16_t FSI_getTxBufferPtr(uint32_t base)
{
    return (HWREGH(base + FSI_O_TX_BUF_PTR_STS) & FSI_TX_BUF_PTR_STS_CURR_BUF_PTR_M);

}

//*****************************************************************************
//
//! \brief Returns valid number of data words present in buffer which have not
//!        been transmitted yet
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return number of data words present in buffer which have not been
//!         transmitted yet
//! \note   there could be lag due to synchronization hence value is accurate
//!         only when no current transmission is happening
//
//*****************************************************************************
static inline uint16_t FSI_getTxWordCount(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    return ((HWREGH(base + FSI_O_TX_BUF_PTR_STS) & FSI_TX_BUF_PTR_STS_CURR_WORD_CNT_M)
            >> FSI_TX_BUF_PTR_STS_CURR_WORD_CNT_S);
}

//*****************************************************************************
//
//! \brief Enables ping timer logic and once set time elapses it sends signal
//!        to transmitter to send ping frame
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] refValue 32 bit reference value for ping time-out counter
//! \param[in] pingFrameTag 4 bit tag value for ping time-out counter
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_enableTxPingTimer(uint32_t base, uint32_t refValue) //, FSI_FrameTag pingFrameTag
{


//   FsiTxaRegs->TX_PING_TAG.bit.TAG = pingFrameTag;

    EALLOW;
    FsiTxaRegs->TX_PING_TO_REF.all =refValue;
//    HWREG(base + FSI_O_TX_PING_TO_REF) = refValue;

    FsiTxaRegs->TX_PING_CTRL.bit.TIMER_EN = 1;
    EDIS;
}

//*****************************************************************************
//! \brief Sets the ping tag value, used by either timeout counter initiated
//!        PING frame transfer or by external ping trigger input.
//*****************************************************************************
static inline void FSI_setTxPingTag(uint32_t base, FSI_FrameTag frameTag)
{
    FsiTxaRegs->TX_PING_TAG.bit.TAG = frameTag;

}

//*****************************************************************************
//
//! \brief  Disables ping timer logic
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_disableTxPingTimer(uint32_t base)
{
    EALLOW;
    FsiTxaRegs->TX_PING_CTRL.bit.TIMER_EN = 0;
    EDIS;
}

//*****************************************************************************
//
//! \brief Enables external trigger to transmit a ping frame
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] extTrigSel can be one of the external inputs from 0 to 31.
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_enableTxExtPingTrigger(uint32_t base, uint16_t extTrigSel)
{

    EALLOW;

    // Select external input trigger

    FsiTxaRegs->TX_PING_CTRL.bit.EXT_TRIG_SEL = extTrigSel;
    // Enable ping frame transmission through external trigger

    FsiTxaRegs->TX_PING_CTRL.bit.EXT_TRIG_EN =1;

    EDIS;
}

//*****************************************************************************
//
//! \brief Disables external trigger logic
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_disableTxExtPingTrigger()
{
    EALLOW;

    FsiTxaRegs->TX_PING_CTRL.bit.EXT_TRIG_EN = 0;

    EDIS;
}

//*****************************************************************************
//! \brief Gives Current value of Ping Timeout Logic Counter
//*****************************************************************************
static inline uint32_t FSI_getTxCurrentPingTimeoutCounter(uint32_t base)
{

    return (HWREG(base + FSI_O_TX_PING_TO_CNT));
}

//*****************************************************************************
//
//! \brief Enables to generate DMA event on completion of a frame transfer

//*****************************************************************************
static inline void FSI_enableTxDMAEvent(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    EALLOW;
    HWREGH(base + FSI_O_TX_DMA_CTRL) |= FSI_TX_DMA_CTRL_DMA_EVT_EN;

    EDIS;
}

//*****************************************************************************
//
//! \brief Disable to generate DMA event on completion of a frame transfer
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_disableTxDMAEvent(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    EALLOW;
    HWREGH(base + FSI_O_TX_DMA_CTRL) &= ~FSI_TX_DMA_CTRL_DMA_EVT_EN;
    EDIS;
}

//*****************************************************************************
//
//! \brief Locks the control of all transmit control registers,once locked
//!        further writes will not take effect until system reset occurs
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \note System reset only can unlock registers once locked.
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_lockTxCtrl(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    EALLOW;
    HWREGH(base + FSI_O_TX_LOCK_CTRL)
        = ((uint16_t)FSI_TX_LOCK_CTRL_LOCK | (FSI_CTRL_REG_KEY << FSI_TX_LOCK_CTRL_KEY_S));


    FsiTxaRegs->TX_LOCK_CTRL.bit.KEY = 0xA5;
    FsiTxaRegs->TX_LOCK_CTRL.bit.LOCK = 1;

    EDIS;
}

//*****************************************************************************
//
//! \brief Returns current status of all the error flags
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return the status of error flags,each bit of integer is associated with
//!         one error flag.
//!
//! Example Usage - function will set the bits corresponding to respective
//!                 error flag in return value
//!     evtStatus = FSI_getTxEventStatus(FSI_base)
//!     if bit value of evtStatus is 12(01100) means
//!     FSI_TX_EVT_OVERRUN and FSI_TX_EVT_PING_HW_TRIG flags are set
//
//*****************************************************************************
static inline uint16_t FSI_getTxEventStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    return (HWREGH(base + FSI_O_TX_EVT_STS) & FSI_TX_EVTMASK);
}

//*****************************************************************************
//
//! \brief Enables user to set TX error flags
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] evtFlags contains list of event and error flags that are
//!             supposed to be set.
//!
//! \details Writing a 1 to this bit position will cause the corresponding bit
//!          in \b TX_EVT_ERR_STATUS register to get set. The purpose of this
//!          register is to allow software to simulate the effect of the event
//!          and test the associated software/ISR.
//!
//! Example Usage
//!     evtFlags = FSI_TX_EVT_FRAME_DONE & FSI_TX_EVT_OVERRUN
//!     FSI_forceTxEvents(FSI_base,evtFlags)
//!     Above call sets error flag to frameDone and overRun events
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_forceTxEvents(uint32_t base, uint16_t evtFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    EALLOW;
    HWREGH(base + FSI_O_TX_EVT_FRC) = (evtFlags & FSI_TX_EVTMASK);
    EDIS;
}

//*****************************************************************************
//
//! \brief Enables user to clear TX error flags
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] evtFlags contains list of event and error flags that are
//!             supposed to be cleared.
//!
//! \details Writing a 1 to this bit position will cause the corresponding bit
//!          in the TX_EVT_ERR_STATUS register to get cleared to 0
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_clearTxEvents(uint32_t base, uint16_t evtFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    EALLOW;
    HWREGH(base + FSI_O_TX_EVT_CLR) = (evtFlags & FSI_TX_EVTMASK);
    EDIS;
}

//*****************************************************************************
//! \brief Sets the CRC value to be picked transmission if transmission is
//!        configured to use user defined SW CRC
//*****************************************************************************
static inline void FSI_enableTxUserCRC(uint32_t base, uint16_t userCRCValue)
{

    EALLOW;
    FsiTxaRegs->TX_OPER_CTRL_LO.bit.SW_CRC =1;
    EDIS;
    FsiTxaRegs->TX_USER_CRC.bit.USER_CRC = userCRCValue;
}

//*****************************************************************************
//
//! \brief Sets the CRC value to be picked transmission if transmission is
//!        configured to use user defined SW CRC
//*****************************************************************************
static inline void FSI_disableTxUserCRC(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    EALLOW;
//    HWREGH(base + FSI_O_TX_OPER_CTRL_LO) &= ~FSI_TX_OPER_CTRL_LO_SW_CRC;
    FsiTxaRegs->TX_OPER_CTRL_LO.bit.SW_CRC =0;

    EDIS;
}

//*****************************************************************************
//
//! \brief Sets data for ECC logic computaion
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] data data value for which ECC needs to be computed
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_setTxECCdata(uint32_t base, uint32_t data)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    HWREG(base + FSI_O_TX_ECC_DATA) = data;

}

//*****************************************************************************
//
//! \brief Returns ECC value evaluated for 16/32 bit data
//!
//! \param[in] base is the FSI Tx module base address
//!
//! \return ECC value for input data
//
//*****************************************************************************
static inline uint16_t FSI_getTxECCValue(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    return (HWREGH(base + FSI_O_TX_ECC_VAL) & FSI_TX_ECC_VAL_ECC_VAL_M);
}

//*****************************************************************************
//
//! \brief  Enables user to generate interrupt on occurrence of FSI_TxEventList
//!         events
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] intNum is the type of interrupt to be generated
//!                    interrupt1 or interrupt2
//! \param[in] intFlags contains list of events on which interrupt
//!             should be generated.
//!
//! Example Usage
//!     intFlags = FSI_TX_EVT_FRAME_DONE && FSI_TX_EVT_BUF_OVERRUN
//!                             && FSI_TX_EVT_PING_TIMEOUT
//!     FSI_enableTxInterrupt(FSI_base, FSI_INT1, intFlags)
//!     above configuration will generate signal on interrupt line 1 upon
//!     frameDone, BufOverRun and PingTimeOut event
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_enableTxInterrupt(uint32_t base, FSI_InterruptNum intNum, uint16_t intFlags)
{
    EALLOW;

    if (intNum == FSI_INT1)
    {
        HWREGH(base + FSI_O_TX_INT_CTRL) |= (intFlags & FSI_TX_EVTMASK);
    }
    else
    {
        HWREGH(base + FSI_O_TX_INT_CTRL) |= ((intFlags & FSI_TX_EVTMASK) << FSI_TX_INT2_CTRL_S);
    }

    EDIS;
}

//*****************************************************************************
//
//! \brief Enables user to disable generation interrupt on occurrence of
//!        FSI_TxEventList events
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] intNum is the type of interrupt to be generated
//!                    interrupt1 or interrupt2
//! \param[in] intFlags contains list of events on which interrupt
//!            generation has to be disabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_disableTxInterrupt(uint32_t base, FSI_InterruptNum intNum, uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    EALLOW;

    if (intNum == FSI_INT1)
    {
        HWREGH(base + FSI_O_TX_INT_CTRL) &= ~(intFlags & FSI_TX_EVTMASK);
    }
    else
    {
        HWREGH(base + FSI_O_TX_INT_CTRL) &= ((~(intFlags & FSI_TX_EVTMASK) << FSI_TX_INT2_CTRL_S) | 0xFFU);
    }

    EDIS;
}

//*****************************************************************************
//
//! \brief Returns address of Tx data buffer
//!
//! \details Data buffer is consisting of 16 words from offset- 0x40 to 0x4e
//!
//! \param[in]  base is the FSI Tx module base address
//!
//! \return Tx data buffer address
//
//*****************************************************************************
static inline uint32_t FSI_getTxBufferAddress(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isTxBaseValid(base));

    return (base + FSI_O_TX_BUF_BASE);
}

//*****************************************************************************
//
//! \brief Resets clock or ping timeout counter or entire TX module
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] submodule the name of submodule which is supposed to be reset
//!
//! \return None.
//
//*****************************************************************************
extern void FSI_resetTxModule(uint32_t base, FSI_TxSubmoduleInReset submodule);

//*****************************************************************************
//
//! \brief Clears reset on clock or ping timeout counter or entire TX module
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] submodule the name of submodule, to be brought out of reset
//!
//! \return None.
//
//*****************************************************************************
extern void FSI_clearTxModuleReset(uint32_t base, FSI_TxSubmoduleInReset submodule);

//*****************************************************************************
//
//! \brief Writes data in FSI Tx buffer
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] array is the address of the array of words to be transmitted.
//! \param[in] length is the number of words in the array to be transmitted.
//! \param[in] bufOffset is the offset in Tx buffer where data will be written
//!
//! \note Data Overwrite protection is implemented in this function by ensuring
//!       not more than 16 words are written and also wrap around case is taken
//!       care when more words need to be written if last write happens at
//!       maximum offset in Tx buffer
//!
//! \return None.
//
//*****************************************************************************
extern void FSI_writeTxBuffer(uint32_t base, const uint16_t array[], uint16_t length, uint16_t bufOffset);

//*****************************************************************************

//*****************************************************************************
//
// FSI Rx function prototypes/definitions
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Checks the FSI-Rx base address
//!
//! \param base is the base address of the FSI-Rx module
//!
//! \return returns \b true if the base address is valid and \b false otherwise
//
//*****************************************************************************
#ifdef DEBUG
static inline bool FSI_isRxBaseValid(uint32_t base)
{
    return ((base == FSIRXA_BASE));
}
#endif

//*****************************************************************************
// Enables internal loopback where mux will select
//*****************************************************************************
static inline void FSI_enableRxInternalLoopback(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    EALLOW;
    HWREGH(base + FSI_O_RX_MAIN_CTRL)
        |= ((uint16_t)FSI_RX_MAIN_CTRL_INT_LOOPBACK | (FSI_CTRL_REG_KEY << FSI_RX_MAIN_CTRL_KEY_S));
    EDIS;
}

//*****************************************************************************
// Disables internal loopback where mux will not use internal pins coming from TX module
//*****************************************************************************
static inline void FSI_disableRxInternalLoopback(uint32_t base)
{
    EALLOW;
    HWREGH(base + FSI_O_RX_MAIN_CTRL) = (HWREGH(base + FSI_O_RX_MAIN_CTRL) & (~FSI_RX_MAIN_CTRL_INT_LOOPBACK))
                                        | (FSI_CTRL_REG_KEY << FSI_RX_MAIN_CTRL_KEY_S);
    EDIS;
}

//*****************************************************************************
// Receive clock is selected from the internal port coming from TX module
//*****************************************************************************
static inline void FSI_enableRxSPIPairing(uint32_t base)
{
    EALLOW;
    HWREGH(base + FSI_O_RX_MAIN_CTRL)
        |= ((uint16_t)FSI_RX_MAIN_CTRL_SPI_PAIRING | (FSI_CTRL_REG_KEY << FSI_RX_MAIN_CTRL_KEY_S));
    EDIS;
}

//*****************************************************************************
//Selects regular receive clock coming from the pins
//*****************************************************************************
static inline void FSI_disableRxSPIPairing(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    EALLOW;
    HWREGH(base + FSI_O_RX_MAIN_CTRL) = (HWREGH(base + FSI_O_RX_MAIN_CTRL) & (~FSI_RX_MAIN_CTRL_SPI_PAIRING))
                                        | (FSI_CTRL_REG_KEY << FSI_RX_MAIN_CTRL_KEY_S);
    EDIS;
}

//*****************************************************************************
// Selects number of data lines used for receiving
//*****************************************************************************
static inline void FSI_setRxDataWidth(uint32_t base, FSI_DataWidth dataWidth)
{
    EALLOW;
    FsiRxaRegs->RX_OPER_CTRL.bit.DATA_WIDTH = dataWidth;
    EDIS;
}

//*****************************************************************************
// Enables SPI compatible mode in FSI Rx
//*****************************************************************************
static inline void FSI_enableRxSPIMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    EALLOW;
    FsiRxaRegs->RX_OPER_CTRL.bit.SPI_MODE = 1;
    EDIS;
}

//*****************************************************************************
// Disables SPI compatible mode in FSI Rx
//*****************************************************************************
static inline void FSI_disableRxSPIMode(uint32_t base)
{
    EALLOW;
    FsiRxaRegs->RX_OPER_CTRL.bit.SPI_MODE = 0;
    EDIS;
}

//*****************************************************************************
//
//! \brief Sets the frame size if frame type is user/software defined frame
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] nWords  is number of data words in a software defined frame
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_setRxSoftwareFrameSize(uint32_t base, uint16_t nWords)
{
    EALLOW;
    FsiRxaRegs->RX_OPER_CTRL.bit.N_WORDS = nWords-1;
    EDIS;
}

//*****************************************************************************
//
// Select between 16-bit and 32-bit ECC computation
//*****************************************************************************
static inline void FSI_setRxECCComputeWidth(uint32_t base, FSI_ECCComputeWidth eccComputeWidth)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    EALLOW;

    if (eccComputeWidth == FSI_16BIT_ECC_COMPUTE)
    {
        HWREGH(base + FSI_O_RX_OPER_CTRL) |= FSI_RX_OPER_CTRL_ECC_SEL;
    }
    else
    {
        HWREGH(base + FSI_O_RX_OPER_CTRL) &= ~FSI_RX_OPER_CTRL_ECC_SEL;
    }

    EDIS;
}

//*****************************************************************************
// Setting for when Ping timeout can reset and restart
//*****************************************************************************
static inline void FSI_setRxPingTimeoutMode(uint32_t base, FSI_PingTimeoutMode pingTimeoutMode)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    EALLOW;

    if (pingTimeoutMode == FSI_PINGTIMEOUT_ON_HWSWINIT_PING_FRAME)
    {
        FsiRxaRegs->RX_OPER_CTRL.bit.PING_WD_RST_MODE = 1;
    }
    else
    {
        FsiRxaRegs->RX_OPER_CTRL.bit.PING_WD_RST_MODE = 0;
    }

    EDIS;
}

//*****************************************************************************
//brief Gets frame type received in the last successful frame
//*****************************************************************************
static inline FSI_FrameType FSI_getRxFrameType(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return ((FSI_FrameType)(HWREGH(base + FSI_O_RX_FRAME_INFO) & FSI_RX_FRAME_INFO_FRAME_TYPE_M));
}

//*****************************************************************************
// Enables to generate DMA event on completion of a successful frame reception
//*****************************************************************************
static inline void FSI_enableRxDMAEvent(uint32_t base)
{
    EALLOW;
    FsiRxaRegs->RX_DMA_CTRL.bit.DMA_EVT_EN =1;
    EDIS;
}

//*****************************************************************************
// Disables the DMA event generation on completion of a successful frame reception
//*****************************************************************************
static inline void FSI_disableRxDMAEvent(uint32_t base)
{
    EALLOW;
    FsiRxaRegs->RX_DMA_CTRL.bit.DMA_EVT_EN = 0;
    EDIS;
}

//*****************************************************************************
// Returns Frame tag received for the last successful frame
//*****************************************************************************
static inline uint16_t FSI_getRxFrameTag(uint32_t base)
{
    ASSERT(FSI_isRxBaseValid(base));
    return ((HWREGH(base + FSI_O_RX_FRAME_TAG_UDATA) & FSI_RX_FRAME_TAG_UDATA_FRAME_TAG_M)
            >> FSI_RX_FRAME_TAG_UDATA_FRAME_TAG_S);
}

//*****************************************************************************
// Returns User-Data(8-bit) field for received data frame.
//*****************************************************************************
static inline uint16_t FSI_getRxUserDefinedData(uint32_t base)
{
    return ((HWREGH(base + FSI_O_RX_FRAME_TAG_UDATA) & FSI_RX_FRAME_TAG_UDATA_USER_DATA_M)
            >> FSI_RX_FRAME_TAG_UDATA_USER_DATA_S);
}

//*****************************************************************************
//  Returns current status of all the evetn/error flags
//*****************************************************************************
static inline uint16_t FSI_getRxEventStatus(uint32_t base)
{
    return (HWREGH(base + FSI_O_RX_EVT_STS) & FSI_RX_EVTMASK);
}

//*****************************************************************************
//
//! \brief Enables user to set RX event/error flags
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] evtFlags contains list of error flags to be set
//!
//! \return None.
//!
//! Example Usage
//!     evtFlags = FSI_RX_EVT_EOF_ERR && FSI_RX_EVT_TYPE_ERR
//!     FSI_forceRxEvents(FSI_base,evtFlags)
//!     Above call sets error flag to FSI_RX_ERR_EOF_ERR and
//!     FSI_RX_ERR_TYPE_ERR events
//
//*****************************************************************************
static inline void FSI_forceRxEvents(uint32_t base, uint16_t evtFlags)
{
    EALLOW;
    HWREGH(base + FSI_O_RX_EVT_FRC) = (evtFlags & FSI_RX_EVTMASK);
    EDIS;
}

//*****************************************************************************
//! \brief Enables user to clear RX event/error flags
//*****************************************************************************
static inline void FSI_clearRxEvents(uint32_t base, uint16_t evtFlags)
{
    EALLOW;
    HWREGH(base + FSI_O_RX_EVT_CLR) = (evtFlags & FSI_RX_EVTMASK);
    EDIS;
}

//*****************************************************************************
// Returns CRC value received in data frame/frame
//*****************************************************************************
static inline uint16_t FSI_getRxReceivedCRC(uint32_t base)
{
    return (HWREGH(base + FSI_O_RX_CRC_INFO) & FSI_RX_CRC_INFO_RX_CRC_M);
}

//*****************************************************************************
// Computes and returns CRC value for data received
//*****************************************************************************
static inline uint16_t FSI_getRxComputedCRC(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return ((HWREGH(base + FSI_O_RX_CRC_INFO) & FSI_RX_CRC_INFO_CALC_CRC_M) >> FSI_RX_CRC_INFO_CALC_CRC_S);
}

//*****************************************************************************
//Sets the value for receive buffer pointer at desired location
//*****************************************************************************
static inline void FSI_setRxBufferPtr(uint32_t base, uint16_t bufPtrOff)
{
    ASSERT(bufPtrOff <= FSI_MAX_VALUE_BUF_PTR_OFF);
    EALLOW;
//    HWREGH(base + FSI_O_RX_BUF_PTR_LOAD) = bufPtrOff;
    FsiRxaRegs->RX_BUF_PTR_LOAD.RX_BUF_PTR_LOAD_all = bufPtrOff;

    EDIS;
}

//*****************************************************************************
// Returns current buffer pointer location
//*****************************************************************************
static inline uint16_t FSI_getRxBufferPtr(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return (HWREGH(base + FSI_O_RX_BUF_PTR_STS) & FSI_RX_BUF_PTR_STS_CURR_BUF_PTR_M);
}

//*****************************************************************************
// Returns valid number of data words present in buffer which have not been read out yet
//*****************************************************************************
static inline uint16_t FSI_getRxWordCount(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return ((HWREGH(base + FSI_O_RX_BUF_PTR_STS) & FSI_RX_BUF_PTR_STS_CURR_WORD_CNT_M)
            >> FSI_RX_BUF_PTR_STS_CURR_WORD_CNT_S);
}

//*****************************************************************************
//Enables the frame watchdog counter logic to count every time it start to receive a frame
//*****************************************************************************
static inline void FSI_enableRxFrameWatchdog(uint32_t base, uint32_t wdRef)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    EALLOW;
    FsiRxaRegs->RX_FRAME_WD_REF = wdRef;
    FsiRxaRegs->RX_FRAME_WD_CTRL.bit.FRAME_WD_EN = 1;
    EDIS;
}

//*****************************************************************************
// Disables the frame watchdog counter logic
//*****************************************************************************
static inline void FSI_disableRxFrameWatchdog(uint32_t base)
{
    EALLOW;
    FsiRxaRegs->RX_FRAME_WD_CTRL.bit.FRAME_WD_EN = 0;
    EDIS;
}

//*****************************************************************************
// Returns current value of frame watchdog counter
//*****************************************************************************
static inline uint32_t FSI_getRxFrameWatchdogCounter(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return (HWREG(base + FSI_O_RX_FRAME_WD_CNT));
}

//*****************************************************************************
//
//! \brief Enables the ping watchdog counter logic and once the set time
//!        elapses it will indicate ping watchdog time-out has occurred
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] wdRef reference value for ping watchdog time-out counter
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_enableRxPingWatchdog(uint32_t base, uint32_t wdRef)
{
    EALLOW;
    FsiRxaRegs->RX_PING_WD_REF = wdRef;
    FsiRxaRegs->RX_PING_WD_CTRL.bit.PING_WD_EN =1;
    EDIS;
}

//*****************************************************************************
//
//! \brief Disables the ping watchdog counter logic
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
static inline void FSI_disableRxPingWatchdog(uint32_t base)
{
    EALLOW;
    FsiRxaRegs->RX_PING_WD_CTRL.bit.PING_WD_EN =0;
    EDIS;
}

//*****************************************************************************
// Returns current value of ping watchdog counter
//*****************************************************************************
static inline uint32_t FSI_getRxPingWatchdogCounter(uint32_t base)
{
    ASSERT(FSI_isRxBaseValid(base));

    return (HWREG(base + FSI_O_RX_PING_WD_CNT));
}

//*****************************************************************************
// Returns the value of tag received for last ping frame
//*****************************************************************************
static inline uint16_t FSI_getRxPingTag(uint32_t base)
{
    return ((HWREGH(base + FSI_O_RX_PING_TAG) & FSI_RX_PING_TAG_PING_TAG_M) >> FSI_RX_PING_TAG_PING_TAG_S);
}

//*****************************************************************************
//
//!   Locks the control of all receive control registers,
//!         once locked further writes will not take effect until system
//!         reset occurs
//*****************************************************************************
static inline void FSI_lockRxCtrl(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    EALLOW;
    HWREGH(base + FSI_O_RX_LOCK_CTRL)
        = ((uint16_t)FSI_RX_LOCK_CTRL_LOCK | (FSI_CTRL_REG_KEY << FSI_RX_LOCK_CTRL_KEY_S));
    EDIS;
}

//*****************************************************************************
// Sets Rx ECC data on which ECC (SEC-DED) computaion logic runs
//*****************************************************************************
static inline void FSI_setRxECCData(uint32_t base, uint32_t rxECCdata)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    HWREG(base + FSI_O_RX_ECC_DATA) = rxECCdata;

}

//*****************************************************************************
//Sets received ECC value on which ECC (SEC-DED) computaion logic runs
//*****************************************************************************
static inline void FSI_setRxReceivedECCValue(uint32_t base, uint16_t rxECCvalue)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    //
    // ECC value can be passed as 8 bit value in USERDATA field in a frame
    //
    ASSERT(rxECCvalue <= FSI_MAX_VALUE_USERDATA);

    HWREGH(base + FSI_O_RX_ECC_VAL) = rxECCvalue;
}

//*****************************************************************************
// Returns ECC Corrected data
//*****************************************************************************
static inline uint32_t FSI_getRxECCCorrectedData(uint32_t base)
{
    return (HWREG(base + FSI_O_RX_ECC_SEC_DATA));
}

//*****************************************************************************
// Returns ECC Log details
//*****************************************************************************
static inline uint16_t FSI_getRxECCLog(uint32_t base)
{
    return (HWREGH(base + FSI_O_RX_ECC_LOG) & (FSI_RX_ECC_LOG_SBE | FSI_RX_ECC_LOG_MBE));
}

//*****************************************************************************
// Let user generate interrupt on occurrence of Rx events
//*****************************************************************************
static inline void FSI_enableRxInterrupt(uint32_t base, FSI_InterruptNum intNum, uint16_t intFlags)
{
    EALLOW;

    if (intNum == FSI_INT1)
    {
    	HWREG(base + FSI_O_RX_INT1_CTRL) |= (intFlags & 0x0FFFU);
    }
    else
    {
    	HWREG(base + FSI_O_RX_INT1_CTRL) |= ((intFlags & 0x0FFFU ) << 16U);
    }

    EDIS;
}

//*****************************************************************************
// Let user disable interrupt generation on Rx events
//*****************************************************************************
static inline void FSI_disableRxInterrupt(uint32_t base, FSI_InterruptNum intNum, uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    EALLOW;

    if (intNum == FSI_INT1)
    {
        HWREGH(base + FSI_O_RX_INT1_CTRL) &= ~(intFlags & FSI_RX_EVTMASK);
    }
    else
    {
      HWREGH(base + FSI_O_RX_INT1_CTRL) &= ~(intFlags & FSI_RX_EVTMASK);
    }

    EDIS;
}

//*****************************************************************************
//
//! \brief Returns address of Rx data buffer
//!
//! \details Data buffer is consisting of 16 words from offset- 0x40 to 0x4e
//!
//! \param[in]  base is the FSI Rx module base address
//!
//! \return Rx data buffer address
//
//*****************************************************************************
static inline uint32_t FSI_getRxBufferAddress(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(FSI_isRxBaseValid(base));

    return (base + FSI_O_RX_BUF_BASE(0));
}

//*****************************************************************************
//
//! \brief Resets frame watchdog,ping watchdog or entire RX module
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] submodule the name of module which is supposed to be reset
//!
//! \return None.
//
//*****************************************************************************
extern void FSI_resetRxModule(uint32_t base, FSI_RxSubmoduleInReset submodule);

//*****************************************************************************
//
//! \brief Clears resets on frame watchdog,ping watchdog or entire RX module
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] submodule module which is to be brought out of reset
//!
//! \return None.
//
//*****************************************************************************
extern void FSI_clearRxModuleReset(uint32_t base, FSI_RxSubmoduleInReset submodule);

//*****************************************************************************
//
//! \brief Reads data from FSI Rx buffer
//!
//! \param[in]  base is the FSI Rx module base address
//! \param[out] array is the address of the array of words to receive the data
//! \param[in]  length is the number of words in the array to be received
//! \param[in]  bufOffset is the offset in Rx buffer from where data will
//!             be read
//!
//! \note This function ensures that not more than 16 words are read and
//!       wrap around case is also taken care when more words need to be read
//!       wherein last read happens at maximum offset in Rx buffer
//!
//! \return None.
//
//*****************************************************************************
extern void FSI_readRxBuffer(uint32_t base, uint16_t array[], uint16_t length, uint16_t bufOffset);

//*****************************************************************************
//
//! \brief Adds delay for selected tap line
//!
//! \param[in] base is the FSI Rx module base address
//! \param[in] delayTapType the line for which delay needs to be added
//!            it can be either RXCLK,RXD0 or RXD1
//! \param[in] tapValue   5 bit value of the amount of delay to be added
//!
//! \return None.
//
//*****************************************************************************
extern void FSI_configRxDelayLine(uint32_t base, FSI_RxDelayTapType delayTapType, uint16_t tapValue);

//*****************************************************************************
//
//! \brief Initializes FSI Tx module
//!
//! \details Software based initialization of the FSI transmitter IP. This is
//!          typically needed only once during initialization or if the module
//!          needs to be reset due to an underrun condition that occurred during
//!          operation.
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] prescalar is the user configurable clock divider for PLL input
//!            clock
//!
//! \return None.
//
//*****************************************************************************
extern void FSI_performTxInitialization(uint32_t base, uint16_t prescalar);

//*****************************************************************************
//
//! \brief Initializes FSI Rx module
//!
//! \details Software based initialization of the FSI receiver module.This is
//!          typically needed only once during initialization. However, if there
//!          are framing errors in the received frames, then the receive module
//!          needs to be reset so that subsequent frames/packets can be handled
//!          fresh.
//!
//! \param[in] base is the FSI Rx module base address
//!
//! \return None.
//
//*****************************************************************************
extern void FSI_performRxInitialization(uint32_t base);

//*****************************************************************************
//
//! \brief Sends Flush pattern sequence
//!
//! \details Flush pattern sequence sent by a FSI transmit module will bring the
//!          FSI receive module out of reset so that it will then be ready to
//!          receive subsequent frames.
//!
//! \param[in] base is the FSI Tx module base address
//! \param[in] prescalar is the user configurable clock divider for PLL input
//!            clock
//!
//! \return None.
//
//*****************************************************************************
extern void FSI_executeTxFlushSequence(uint32_t base, uint16_t prescalar);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************

extern void delay_us(unsigned int t);

#ifdef __cplusplus
}
#endif

#endif
