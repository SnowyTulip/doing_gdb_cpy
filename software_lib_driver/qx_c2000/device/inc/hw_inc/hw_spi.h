#ifndef HW_SPI_H
#define HW_SPI_H

//*************************************************************************************************
//
// The following are defines for the SPI register offsets
//
//*************************************************************************************************
#define DW_SPI_CTRLR0      0x00U  // SPI Control Register 0
#define DW_SPI_CTRLR1      0x04U  // SPI Control Register 0
#define DW_SPI_SSIENR      0x08U  // SPI Enable Register
#define DW_SPI_MWCR        0x0CU  // SPI Microwire Control Register
#define DW_SPI_SER         0x10U  // SPI Slave Enable Register
#define DW_SPI_BAUDR       0x14U  // SPI Baudrate Select
#define DW_SPI_TXFTLR      0x18U  // SPI Transmit FIFO Threshold Level
#define DW_SPI_RXFTLR      0x1CU  // SPI Receive FIFO Threshold Level
#define DW_SPI_TXFLR       0x20U  // SPI Transmit FIFO Level Register
#define DW_SPI_RXFLR       0x24U  // SPI Receive FIFO Level Register
#define DW_SPI_SR          0x28U  // SPI Status Register
#define DW_SPI_IMR         0x2CU  // SPI Interrupt Mask Register
#define DW_SPI_ISR         0x30U  // SPI Interrupt Status Register
#define DW_SPI_RISR        0x34U  // SPI Raw Interrupt Status Register
#define DW_SPI_TXOICR      0x38U  // SPI Transmit FIFO Overflow Interrupt Clear Register
#define DW_SPI_RXOICR      0x3CU  // SPI Receive FIFO Overflow Interrupt Clear Register
#define DW_SPI_RXUICR      0x40U  // SPI Receive FIFO Underflow Interrupt Clear Register
#define DW_SPI_MSTICR      0x44U  // SPI Multi-Master Interrupt Clear Register
#define DW_SPI_ICR         0x48U  // SPI Interrupt Clear Register
#define DW_SPI_DMACR       0x4CU  // SPI DMA Control Register
#define DW_SPI_DMATDLR     0x50U  // SPI DMA Transmit Data Level
#define DW_SPI_DMARDLR     0x54U  // SPI DMA Transmit Data Level
#define DW_SPI_IDR         0x58U  // SPI DMA Receive Data Level
#define DW_SPI_VERSION     0x5CU  // SPI coreKit version ID register
#define DW_SPI_DR          0x60U  // SPI Data Register
#define DW_SPI_RX_DLY      0xF0U  // SPI Rx Sample Delay Register
#define DW_SPI_DUAL_CTRLR0 0x00U  // DUAL Quad SPI Control Register 0

//*************************************************************************************************
//
// The following are defines for the bit fields in the Control Register 0
//
//*************************************************************************************************
#define DW_PSSI_CTRLR0_DFS_MASK                 0x0000000FU
#define DW_PSSI_CTRLR0_DFS32_MASK               0x001F0000U
#define DW_PSSI_CTRLR0_DFS32_POS                16

#define DW_PSSI_CTRLR0_FRF_MASK                 0x00000030U
#define DW_SPI_CTRLR0_FRF_MOTO_SPI              (0x0 << 4)
#define DW_SPI_CTRLR0_FRF_TI_SSP                (0x1 << 4)
#define DW_SPI_CTRLR0_FRF_NS_MICROWIRE          (0x2 << 4)
#define DW_SPI_CTRLR0_FRF_RESV                  (0x3 << 4)

#define DW_PSSI_CTRLR0_MODE_MASK                0x000000C0U
#define DW_PSSI_CTRLR0_SCPHA                    (1UL << 6)
#define DW_PSSI_CTRLR0_SCPOL                    (1UL << 7)

#define DW_PSSI_CTRLR0_TMOD_MASK                0x00000300U
#define DW_SPI_CTRLR0_TMOD_TR                   (0x0 << 8)           /* xmit & recv */
#define DW_SPI_CTRLR0_TMOD_TO                   (0x1 << 8)           /* xmit only */
#define DW_SPI_CTRLR0_TMOD_RO                   (0x2 << 8)           /* recv only */
#define DW_SPI_CTRLR0_TMOD_EPROMREAD            (0x3 << 8)           /* eeprom read mode */

#define DW_PSSI_CTRLR0_SLV_OE                   (1UL << 10)
#define DW_PSSI_CTRLR0_SRL                      (1UL << 11)
#define DW_PSSI_CTRLR0_CFS                      (1UL << 12)

//*************************************************************************************************
//
// The following are defines for the bit fields in the Control Register 1
//
//*************************************************************************************************
#define DW_SPI_NDF_MASK                         0x0000FFFFU

//*************************************************************************************************
//
// The following are defines for the bit fields in the Status Register
//
//*************************************************************************************************
#define DW_SPI_SR_MASK                          0x0000007FU
#define DW_SPI_SR_BUSY                          (1UL << 0)
#define DW_SPI_SR_TF_NOT_FULL                   (1UL << 1)
#define DW_SPI_SR_TF_EMPT                       (1UL << 2)
#define DW_SPI_SR_RF_NOT_EMPT                   (1UL << 3)
#define DW_SPI_SR_RF_FULL                       (1UL << 4)
#define DW_SPI_SR_TX_ERR                        (1UL << 5)
#define DW_SPI_SR_DCOL                          (1UL << 6)

//*************************************************************************************************
//
// The following are defines for the bit fields in ISR, IMR, RISR Register
//
//*************************************************************************************************
#define DW_SPI_INT_MASK                         0x000003FU
#define DW_SPI_INT_TXEI                         (1UL << 0)
#define DW_SPI_INT_TXOI                         (1UL << 1)
#define DW_SPI_INT_RXUI                         (1UL << 2)
#define DW_SPI_INT_RXOI                         (1UL << 3)
#define DW_SPI_INT_RXFI                         (1UL << 4)
#define DW_SPI_INT_MSTI                         (1UL << 5)

//*************************************************************************************************
//
// The following are defines for the bit fields in DMACR Register
//
//*************************************************************************************************
#define DW_SPI_DMACR_RDMAE                      (1UL << 0)
#define DW_SPI_DMACR_TDMAE                      (1UL << 1)

#endif
