/**
 **************************************************************************
 * @file     qx32m_spi.c
 * @version  v1.0.0
 * @date     2022-08-30
 * @brief    contains all the functions for the spi firmware library
 **************************************************************************
 */

#include "qx_spi.h"

void SPI_setTransferMode(SPI_Type *spi, SPI_TransferMode type)
{
    if (!spi)
        return;
    SPI_moduleDisable(spi);

    switch (type)
    {
        case SPI_TRANS_MODE_TR:
            spi->CTRL0.bit.TMOD = 0x0;
            break;
        case SPI_TRANS_MODE_TO:
            spi->CTRL0.bit.TMOD = 0x1;
            break;
        case SPI_TRANS_MODE_RO:
            spi->CTRL0.bit.TMOD = 0x2;
            break;
        case SPI_TRANS_EEPROM_READ:
            spi->CTRL0.bit.TMOD = 0x3;
            break;
    }

    SPI_moduleEnable(spi);
}

void SPI_setSampleMode(SPI_Type *spi, SPI_SampleMode mode)
{
    if (!spi)
        return;
    SPI_moduleDisable(spi);

    switch (mode)
    {
        case SPI_SAMPLE_POS_0:
            spi->CTRL0.bit.SCPOL = 0;
            spi->CTRL0.bit.SCPH  = 0;
            break;
        case SPI_SAMPLE_POS_1:
            spi->CTRL0.bit.SCPOL = 1;
            spi->CTRL0.bit.SCPH  = 1;
            break;
        case SPI_SAMPLE_NEG_0:
            spi->CTRL0.bit.SCPOL = 1;
            spi->CTRL0.bit.SCPH  = 0;
            break;
        case SPI_SAMPLE_NEG_1:
            spi->CTRL0.bit.SCPOL = 0;
            spi->CTRL0.bit.SCPH  = 1;
            break;
        default:
            spi->CTRL0.bit.SCPOL = 0;
            spi->CTRL0.bit.SCPH  = 0;
            break;
    }

    SPI_moduleEnable(spi);
}

void SPI_disableInterrupt(SPI_Type *spi, SPI_InterruptMask type)
{
    if (!spi)
        return;

    switch (type)
    {
        case SPI_INT_MASK_TXE:
            spi->IM.bit.TXEIM = 0;
            break;
        case SPI_INT_MASK_TXO:
            spi->IM.bit.TXOIM = 0;
            break;
        case SPI_INT_MASK_RXU:
            spi->IM.bit.RXUIM = 0;
            break;
        case SPI_INT_MASK_RXO:
            spi->IM.bit.RXOIM = 0;
            break;
        case SPI_INT_MASK_RXF:
            spi->IM.bit.RXFIM = 0;
            break;
        case SPI_INT_MASK_MST:
            spi->IM.bit.MSTIM = 0;
            break;
        case SPI_INT_MASK_ALL:
            spi->IM.all = 0;
    }
}

void SPI_enableInterrupt(SPI_Type *spi, SPI_InterruptMask type)
{
    if (!spi)
        return;

    switch (type)
    {
        case SPI_INT_MASK_TXE:
            spi->IM.bit.TXEIM = 1;
            break;
        case SPI_INT_MASK_TXO:
            spi->IM.bit.TXOIM = 1;
            break;
        case SPI_INT_MASK_RXU:
            spi->IM.bit.RXUIM = 1;
            break;
        case SPI_INT_MASK_RXO:
            spi->IM.bit.RXOIM = 1;
            break;
        case SPI_INT_MASK_RXF:
            spi->IM.bit.RXFIM = 1;
            break;
        case SPI_INT_MASK_MST:
            spi->IM.bit.MSTIM = 1;
            break;
        case SPI_INT_MASK_ALL:
            spi->IM.all = 0x3F;
    }
}

void SPI_setCLKDivider(SPI_Type *spi, u32 clkdiv)
{
    if (!spi)
        return;

    SPI_moduleDisable(spi);

    if (clkdiv < 4)
        clkdiv = 4;
    if (clkdiv > 128)
        clkdiv = 128;
    spi->BAUD = (u32)clkdiv;

    SPI_moduleEnable(spi);
}

void SPI_masterInit(SPI_Type *spi, SPI_Config *config)
{
    if (!spi)
        return;

    SPI_setFrameFormat(spi, SPI_FRF_MOTOROLA);

    // set ssi to spi mode
    SPI_setTransferWidth(spi, config->data_width);
    SPI_setSampleMode(spi, config->sample_mode);
    SPI_setTransferMode(spi, config->trans_mode);

    // set the transfer baud rate
    SPI_setBaudRate(spi, SRC_CLK_FREQ, config->baudrate);

    // set FIFO threshold levels
    SPI_setFIFOThresholdLevel(spi, config->rx_ftl, config->tx_ftl);

    // set rx sample delay
#if SPI_HAS_RX_SAMPLE_DELAY == 1
    SPI_setRXSampleDelay(spi);
#endif

    // disable txe interrupt
    SPI_disableInterrupt(spi, SPI_INT_MASK_ALL);
    SPI_slaveEnable(spi);
}

void SPI_slaveInit(SPI_Type *spi, SPI_Config *config)
{
    if (!spi)
        return;

    SPI_setFrameFormat(spi, SPI_FRF_MOTOROLA);

    // set ssi to spi mode
    SPI_setTransferWidth(spi, config->data_width);
    SPI_setSampleMode(spi, config->sample_mode);
    SPI_setTransferMode(spi, config->trans_mode);

    // set FIFO threshold levels
    SPI_setFIFOThresholdLevel(spi, config->rx_ftl, config->tx_ftl);

    // disable txe interrupt
    SPI_disableInterrupt(spi, SPI_INT_MASK_ALL);
}

void SPI_sendData(SPI_Type *spi, char *buf)
{
    short width;

    if (!spi)
        return;

    width = spi->CTRL0.bit.DFS_32;

    switch (width)
    {
        case SPI_DATA_BITS_8:
            spi->DATA[0] = *buf;
            break;

        case SPI_DATA_BITS_16:
            spi->DATA[0] = *(short *)buf;
            break;

        case SPI_DATA_BITS_32:
            spi->DATA[0] = *(long *)buf;
            break;
        default:
            break;
    }
}

void SPI_receiveData(SPI_Type *spi, char *buf)
{
    short width;

    if (!spi)
        return;

    width = spi->CTRL0.bit.DFS_32;

    switch (width)
    {
        case SPI_DATA_BITS_8:
            *(buf) = spi->DATA[0];
            break;

        case SPI_DATA_BITS_16:
            *((short *)buf) = spi->DATA[0];
            break;

        case SPI_DATA_BITS_32:
            *((long *)buf) = spi->DATA[0];
            break;
        default:
            break;
    }
}

void SPI_sendDataWithPolling(SPI_Type *spi, char *buf, u32 length)
{
    u32 txfl;
    short width;

    if (!length || !spi)
        return;

    width = spi->CTRL0.bit.DFS_32;
    if (width == SPI_DATA_BITS_8)
    {
        while (length > 0)
        {
            txfl = SPI_getFIFOLevel(spi, 0);
            if (txfl >= 0 && txfl < SSI_RX_FIFO_DEPTH)
            {
                SPI_sendData(spi, buf);
                buf += 1;
                length -= 1;
            }
        }
    }
    else if (width == SPI_DATA_BITS_16)
    {
        while (length > 0)
        {
            txfl = SPI_getFIFOLevel(spi, 0);
            if (txfl >= 0 && txfl < SSI_RX_FIFO_DEPTH)
            {
                SPI_sendData(spi, buf);
                buf += 2;
                length -= 2;
            }
        }
    }
    else if (width == SPI_DATA_BITS_32)
    {
        while (length > 0)
        {
            txfl = SPI_getFIFOLevel(spi, 0);
            if (txfl >= 0 && txfl < SSI_RX_FIFO_DEPTH)
            {
                SPI_sendData(spi, buf);
                buf += 4;
                length -= 4;
            }
        }
    }
}

u32 SPI_recvDataWithPolling(SPI_Type *spi, char *buf)
{
    u32 rxfl;
    short width;
    u32 count = 0;

    if (!spi)
        return -1;

    width = spi->CTRL0.bit.DFS_32;
    rxfl  = SPI_getFIFOLevel(spi, 1);
    if (width == SPI_DATA_BITS_8)
    {
        while (rxfl)
        {
            rxfl = SPI_getFIFOLevel(spi, 1);
            if (rxfl > 0 && rxfl <= SSI_TX_FIFO_DEPTH)
            {
                SPI_receiveData(spi, buf);
                buf += 1;
                count += 1;
            }
        }
    }
    else if (width == SPI_DATA_BITS_16)
    {
        while (rxfl)
        {
            rxfl = SPI_getFIFOLevel(spi, 1);
            if (rxfl > 0 && rxfl <= SSI_TX_FIFO_DEPTH)
            {
                SPI_receiveData(spi, buf);
                buf += 2;
                count += 2;
            }
        }
    }
    else if (width == SPI_DATA_BITS_32)
    {
        while (rxfl)
        {
            rxfl = SPI_getFIFOLevel(spi, 1);
            if (rxfl > 0 && rxfl <= SSI_TX_FIFO_DEPTH)
            {
                SPI_receiveData(spi, buf);
                buf += 4;
                count += 4;
            }
        }
    }

    return count;
}

void SPI_sendDataWithInterrupt(SPI_Type *spi)
{
    int i;
    u8 txftl;
    short width;

    if (!spi)
        return;

    width = spi->CTRL0.bit.DFS_32;
    txftl = SPI_getFIFOThresholdLevel(spi, 0);

    for (i = 0; i < SSI_TX_FIFO_DEPTH - txftl; i++)
    {
        if (spi_send.length > 0)
        {
            SPI_sendData(spi, spi_send.buf);
            spi_send.buf    = spi_send.buf + (width + 1) / 8;
            spi_send.length = spi_send.length - (width + 1) / 8;
        }
        else
            break;
    }

    if (spi_send.length > 0)
        SPI_enableInterrupt(spi, SPI_INT_MASK_TXE);
    else
        SPI_disableInterrupt(spi, SPI_INT_MASK_TXE);
}

void SPI_recvDataWithInterrupt(SPI_Type *spi)
{
    int i;
    u8 rxftl;
    short width;

    if (!spi)
        return;

    width = spi->CTRL0.bit.DFS_32;
    rxftl = SPI_getFIFOThresholdLevel(spi, 1);

    for (i = 0; i <= rxftl; i++)
    {
        SPI_receiveData(spi, spi_recv.buf);
        spi_recv.buf    = spi_recv.buf + (width + 1) / 8;
        spi_recv.length = spi_recv.length + (width + 1) / 8;
    }
}

//*****************************************************************************
//
// SPI_setConfig
//
//*****************************************************************************
void SPI_setConfig(uint32_t base, uint32_t lspclkHz, SPI_TransferProtocol protocol, SPI_Mode mode, uint32_t bitRate,
    uint16_t dataWidth)
{
    SPI_Type *spi;

    // Check the arguments.
    ASSERT(SPI_isBaseValid(base));
    ASSERT(bitRate <= (lspclkHz / 4U));
    ASSERT((lspclkHz / bitRate) <= 128U);
    ASSERT((dataWidth >= 4U) && (dataWidth <= 32U));

    spi = (SPI_Type *)base;
    // Set data width.
    SPI_setTransferWidth(spi, dataWidth);

    // Set polarity and phase
    SPI_setSampleMode(spi, (SPI_SampleMode)protocol);

    // Set the clock.
    SPI_setBaudRate(spi, lspclkHz, bitRate);
}

//*****************************************************************************
//
// SPI_setBaudRate
//
//*****************************************************************************
void SPI_setBaudRate(SPI_Type *spi, uint32_t lspclkHz, uint32_t bitRate)
{
    uint32_t baud;

    // Check the arguments.
    ASSERT(bitRate <= (lspclkHz / 4U));
    ASSERT((lspclkHz / bitRate) <= 128U);

    SPI_moduleDisable(spi);

    baud      = lspclkHz / bitRate;
    spi->BAUD = (u32)baud;

    SPI_moduleEnable(spi);
}

//*****************************************************************************
//
// SPI_moduleEnableInterrupt
//
//*****************************************************************************
void SPI_moduleEnableInterrupt(uint32_t base, uint32_t intFlags)
{
    // Check the arguments.
    ASSERT(SPI_isBaseValid(base));

    // Enable the specified interrupts.
    if ((intFlags & DW_SPI_INT_TXEI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) |= DW_SPI_INT_TXEI;
    }

    if ((intFlags & DW_SPI_INT_TXOI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) |= DW_SPI_INT_TXOI;
    }

    if ((intFlags & DW_SPI_INT_RXUI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) |= DW_SPI_INT_RXUI;
    }

    if ((intFlags & DW_SPI_INT_RXOI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) |= DW_SPI_INT_RXOI;
    }

    if ((intFlags & DW_SPI_INT_RXFI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) |= DW_SPI_INT_RXFI;
    }

    if ((intFlags & DW_SPI_INT_MSTI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) |= DW_SPI_INT_MSTI;
    }
}

//*****************************************************************************
//
// SPI_moduleDisableInterrupt
//
//*****************************************************************************
void SPI_moduleDisableInterrupt(uint32_t base, uint32_t intFlags)
{
    // Check the arguments.
    ASSERT(SPI_isBaseValid(base));

    // Disable the specified interrupts.
    if ((intFlags & DW_SPI_INT_TXEI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) &= ~DW_SPI_INT_TXEI;
    }

    if ((intFlags & DW_SPI_INT_TXOI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) &= ~DW_SPI_INT_TXOI;
    }

    if ((intFlags & DW_SPI_INT_RXUI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) &= ~DW_SPI_INT_RXUI;
    }

    if ((intFlags & DW_SPI_INT_RXOI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) &= ~DW_SPI_INT_RXOI;
    }

    if ((intFlags & DW_SPI_INT_RXFI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) &= ~DW_SPI_INT_RXFI;
    }

    if ((intFlags & DW_SPI_INT_MSTI) != 0U)
    {
        HWREG(base + DW_SPI_IMR) &= ~DW_SPI_INT_MSTI;
    }
}

//*****************************************************************************
//
// SPI_getInterruptStatus
//
//*****************************************************************************
uint32_t SPI_getInterruptStatus(uint32_t base)
{
    uint32_t temp = 0;

    // Check the arguments.
    ASSERT(SPI_isBaseValid(base));

    temp |= HWREG(base + DW_SPI_ISR);

    return (temp);
}

//*****************************************************************************
//
// SPI_clearInterruptStatus
//
//*****************************************************************************
void SPI_clearInterruptStatus(uint32_t base, uint32_t intFlags)
{
    uint32_t temp;
    // Check the arguments.
    ASSERT(SPI_isBaseValid(base));

    // Clear the specified interrupt sources.
    if ((intFlags & DW_SPI_INT_TXOI) != 0U)
    {
        temp = HWREG(base + DW_SPI_TXOICR);
    }

    if ((intFlags & DW_SPI_INT_RXOI) != 0U)
    {
        temp = HWREG(base + DW_SPI_RXOICR);
    }

    if ((intFlags & DW_SPI_INT_RXUI) != 0U)
    {
        temp = HWREG(base + DW_SPI_RXUICR);
    }

    if ((intFlags & DW_SPI_INT_MSTI) != 0U)
    {
        temp = HWREG(base + DW_SPI_MSTICR);
    }
}

//*****************************************************************************
//
// SPI_pollingNonFIFOTransaction
//
//*****************************************************************************
uint16_t SPI_pollingNonFIFOTransaction(uint32_t base, uint16_t charLength, uint16_t data)
{
    uint16_t rxData;

    ASSERT((charLength >= 4U) && (charLength <= 16U));
    ASSERT(data < ((uint32_t)1U << charLength));

    // Set the character length
    SPI_setcharLength(base, charLength);

    // Write to SPI Transmit buffer
    SPI_writeDataBlockingNonFIFO(base, data << (16U - charLength));

    // Read SPI Receive buffer
    rxData = SPI_readDataBlockingNonFIFO(base);

    return (rxData);
}
//*****************************************************************************
//
// SPI_pollingFIFOTransaction
//
//*****************************************************************************

void SPI_pollingFIFOTransaction(
    uint32_t base, uint16_t charLength, uint16_t *pTxBuffer, uint16_t *pRxBuffer, uint16_t numOfWords, uint16_t txDelay)
{
    ASSERT((charLength >= 4U) && (charLength <= 16U));
    SPI_setcharLength(base, charLength);

    // Determine the number of 16-level words from number of words to be
    // transmitted / received
    uint16_t numOfEightWords = numOfWords / (uint16_t)SPI_FIFO_TXFULL;

    // Determine the number of remaining words from number of words to be
    // transmitted / received
    uint16_t remainingWords = numOfWords % (uint16_t)SPI_FIFO_TXFULL;

    uint16_t count        = 0;
    uint16_t i            = 0;
    uint16_t txBuffer_pos = 0;
    uint16_t rxBuffer_pos = 0;

    // Number of transactions is based on numOfSixteenWords
    // Each transaction will transmit and receive 16 words.
    while (count < numOfEightWords)
    {
        // Fill-up the SPI Transmit FIFO buffers
        for (i = 1; i <= (uint16_t)SPI_FIFO_TXFULL; i++)
        {
            SPI_writeDataBlockingFIFO(base, pTxBuffer[txBuffer_pos] << (16U - charLength));
            txBuffer_pos++;
        }

        // Wait till SPI Receive FIFO buffer is full
        while (SPI_getRxFIFOStatus(base) < SPI_FIFO_RXFULL)
        { }

        // Read the SPI Receive FIFO buffers
        for (i = 1U; i <= (uint16_t)SPI_FIFO_RXFULL; i++)
        {
            if (pRxBuffer == NULL)
            {
                SPI_readDataBlockingFIFO(base);
            }
            else
            {
                pRxBuffer[rxBuffer_pos] = SPI_readDataBlockingFIFO(base);
                rxBuffer_pos++;
            }
        }

        count++;
    }

    // Number of transactions is based on remainingWords
    for (i = 0U; i < remainingWords; i++)
    {
        SPI_writeDataBlockingFIFO(base, pTxBuffer[txBuffer_pos] << (16U - charLength));
        txBuffer_pos++;
    }

    // Wait till SPI Receive FIFO buffer remaining words
    while ((uint16_t)SPI_getRxFIFOStatus(base) < remainingWords)
    { }

    // Read the SPI Receive FIFO buffers
    for (i = 0; i < remainingWords; i++)
    {
        if (pRxBuffer == NULL)
        {
            SPI_readDataBlockingFIFO(base);
        }
        else
        {
            pRxBuffer[rxBuffer_pos] = SPI_readDataBlockingFIFO(base);
            rxBuffer_pos++;
        }
    }
}

//*****************************************************************************
//
// SPI_transmit24Bits
//
//*****************************************************************************
void SPI_transmit24Bits(uint32_t base, uint32_t data, uint16_t txDelay)
{
    uint16_t i;
    uint16_t rxBuffer[3];
    uint16_t txBuffer[3];

    ASSERT(data < ((uint32_t)1U << 24U));

    // Empty Receive buffer
    for (i = 0U; i < 3U; i++)
    {
        rxBuffer[i] = 0U;
    }

    // Fill Transmit buffer with appropriate data
    txBuffer[0] = (uint16_t)(data >> 16U);  // data[23:16]
    txBuffer[1] = (uint16_t)(data) >> 8U;   // data[15:8]
    txBuffer[2] = (uint16_t)(data)&0x00FFU; // data[7:0]

    // Three 8-bits make a 24-bit
    // Character length = 8
    // number of bytes = 3
    SPI_pollingFIFOTransaction(base, 8U, txBuffer, rxBuffer, 3U, txDelay);
}
//*****************************************************************************
//
// SPI_receive16Bits
//
//*****************************************************************************

uint16_t SPI_receive16Bits(uint32_t base, SPI_endianess endianness, uint16_t dummyData, uint16_t txDelay)
{
    uint16_t i;
    uint16_t txBuffer[2];
    uint16_t rxBuffer[2];
    uint16_t rxData = 0U;

    ASSERT(dummyData <= 0xFFU);
    ASSERT(endianness == SPI_DATA_LITTLE_ENDIAN);

    // Empty Transmit buffer
    for (i = 0U; i < 2U; i++)
    {
        txBuffer[i] = dummyData;
        rxBuffer[i] = 0U;
    }

    // Send dummy words to receive data from peripheral
    SPI_pollingFIFOTransaction(base, 8U, txBuffer, rxBuffer, 2U, txDelay);

    rxData = (rxBuffer[1] << 8) | rxBuffer[0];

    return (rxData);
}
//*****************************************************************************
//
// SPI_receive24Bits
//
//*****************************************************************************

uint32_t SPI_receive24Bits(uint32_t base, SPI_endianess endianness, uint16_t dummyData, uint16_t txDelay)
{
    uint16_t i;
    uint16_t txBuffer[3];
    uint16_t rxBuffer[3];
    uint32_t rxData = 0;

    ASSERT(dummyData <= 0xFFU);
    ASSERT(endianness == SPI_DATA_LITTLE_ENDIAN);

    // Empty Transmit buffer
    for (i = 0U; i < 3U; i++)
    {
        txBuffer[i] = dummyData;
        rxBuffer[i] = 0U;
    }

    // Send dummy words to receive data from peripheral
    // Two 8-bits make a 16-bit
    // Character length = 8
    // number of bytes = 2
    SPI_pollingFIFOTransaction(base, 8U, txBuffer, rxBuffer, 3U, txDelay);

    rxData = ((uint32_t)rxBuffer[2] << 16) | ((uint32_t)rxBuffer[1] << 8) | (uint32_t)rxBuffer[0];

    return (rxData);
}
//*****************************************************************************
//
// SPI_transmit32Bits
//
//*****************************************************************************

void SPI_transmit32Bits(uint32_t base, uint32_t data, uint16_t txDelay)
{
    uint16_t i;
    uint16_t txBuffer[2];
    uint16_t rxBuffer[2];

    // Empty Receive buffer
    for (i = 0U; i < 2U; i++)
    {
        rxBuffer[i] = 0U;
    }

    // Fill Transmit buffer with appropriate data
    txBuffer[0] = (uint16_t)(data >> 16U); // data[31:16]
    txBuffer[1] = (uint16_t)(data);        // data[15:0]

    //
    // Two 16-bits make a 32-bit
    // Character length = 16
    // number of bytes = 2
    //
    SPI_pollingFIFOTransaction(base, 16U, txBuffer, rxBuffer, 2U, txDelay);
}
//*****************************************************************************
//
// SPI_receive32Bits
//
//*****************************************************************************

uint32_t SPI_receive32Bits(uint32_t base, SPI_endianess endianness, uint16_t dummyData, uint16_t txDelay)
{
    uint16_t i;
    uint16_t txBuffer[4];
    uint16_t rxBuffer[4];
    uint32_t rxData = 0U;

    ASSERT(dummyData <= 0xFFU);
    ASSERT(endianness == SPI_DATA_LITTLE_ENDIAN);

    // Empty Transmit buffer
    for (i = 0U; i < 4U; i++)
    {
        txBuffer[i] = dummyData;
        rxBuffer[i] = 0U;
    }

    // Send dummy words to receive data from peripheral
    // Four 8-bits make a 32-bit
    // Character length = 8
    // number of bytes = 4
    SPI_pollingFIFOTransaction(base, 8U, txBuffer, rxBuffer, 4U, txDelay);

    rxData = ((uint32_t)rxBuffer[3] << 24U) | ((uint32_t)rxBuffer[2] << 16U) | ((uint32_t)rxBuffer[1] << 8U)
             | (uint32_t)rxBuffer[0];

    return (rxData);
}
