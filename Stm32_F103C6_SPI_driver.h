#ifndef  __SPI_H
#define __SPI_H


//-----------------------------
//Includes
//-----------------------------
#include "std_macros.h"
#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"


//-----------------------------
//User type ENUMs
//-----------------------------
typedef enum
{
    POLLING_DISABLE = 0,
    POLLING_ENABLE  = 1
}PollingMechanism;


typedef union 
{
    struct
    {
        uint8_t RXNEIE          : 1;
        uint8_t TXEIE           : 1;
        uint8_t ERRIE           : 1;
        uint8_t reserved        : 5;
    }SPI_IQR_BITS;
    uint8_t SPI_IQR_REGIGSTER;
}SPI_IQR_HANDLER_t;

//typedef uint8_t SPI_IQR_HANDLER_t;
typedef struct
{
    uint16_t DEVICE_MODE        ; //@ref SPI_DEVICE_MODE
    uint16_t COMMUNICATION_MODE ; //@ref SPI_COMMUNICATION_MODE
    uint16_t FRAME_FORMAT       ; //@ref SPI_FRAME_FORMAT
    uint16_t DATA_SIZE          ; //@ref SPI_DATA_FRAME_SIZE
    uint16_t CLOCK_POLARITY     ; //@ref SPI_CLOCK_POLARITY
    uint16_t CLOCK_PHASE        ; //@ref SPI_CLOCK_PHASE
    uint16_t SS_MANAGEMENT      ; //@ref SPI_SS_MANAGEMENT
    uint16_t BAUD_RATE          ; //@ref SPI_BAUD_RATE
    SPI_IQR_HANDLER_t IQR_ENABLE; //@ref SPI_IQR_ENABLE
    void (*SPI_IQR_HANDLER)(SPI_IQR_HANDLER_t IQR_STATUS); //@ref SPI_IQR_HANDLER
}SPI_CONFIG_t;

//@ref SPI_DEVICE_MODE
/*
 SPI control register 1 (SPI_CR1)
 Bit 2 MSTR: Master selection
0: Slave configuration
1: Master configuration
*/
#define SPI_SLAVE_MODE   (uint32_t)0ul
#define SPI_MASTER_MODE (uint32_t)(1ul<<2)


//@ref SPI_COMMUNICATION_MODE
/*
 SPI control register 1 (SPI_CR1)
Bit 15 BIDIMODE: Bidirectional data mode enable
0: 2-line unidirectional data mode selected
1: 1-line bidirectional data mode selected

Bit 14 BIDIOE: Output enable in bidirectional mode
This bit combined with the BIDImode bit selects the direction of transfer in bidirectional mode
0: Output disabled (receive-only mode) 
1: Output enabled (transmit-only mode)

Bit 10 RXONLY: Receive only
This bit combined with the BIDImode bit selects the direction of transfer in 2-line 
unidirectional mode. This bit is also useful in a multislave system in which this particular 
slave is not accessed, the output from the accessed slave is not corrupted.
0: Full duplex (Transmit and receive)
1: Output disabled (Receive-only mode)
*/
#define SPI_Direction_2Lines_RXTX			(uint32_t)0ul
#define SPI_Direction_2Lines_RX				(uint32_t)(1ul<<10) 
#define SPI_Direction_1Line_RX				(uint32_t)(1ul<<15)
#define SPI_Direction_1Line_TX				(uint32_t)((1ul<<15)|(1ul<<14))

//@ref SPI_FRAME_FORMAT
/*
 SPI control register 1 (SPI_CR1)
 Bit 7 LSBFIRST: Frame format
0: MSB transmitted first
1: LSB transmitted first
*/
#define SPI_MSB_FIRST (uint32_t)0ul
#define SPI_LSB_FIRST (uint32_t)(1ul<<7)

//@ref SPI_DATA_FRAME_SIZE
/*
 SPI control register 1 (SPI_CR1)
 Bit 11 DFF: Data frame format
0: 8-bit data frame format is selected for transmission/reception
1: 16-bit data frame format is selected for transmission/reception
This bit should be written only when SPI is disabled (SPE = ‘0’)
*/  
#define SPI_8BIT_DATA_FRAME  (uint32_t)0ul
#define SPI_16BIT_DATA_FRAME (uint32_t)(1ul<<11)


//@ref SPI_CLOCK_POLARITY
/*
 SPI control register 1 (SPI_CR1)
 Bit1 CPOL: Clock polarity
0: CK to 0 when idle
1: CK to 1 when idle
*/
#define SPI_CLOCK_POLARITY_LOW  (uint32_t)0ul
#define SPI_CLOCK_POLARITY_HIGH (uint32_t)(1ul<<1)

//@ref SPI_CLOCK_PHASE
/*
 SPI control register 1 (SPI_CR1)
 Bit 0 CPHA: Clock phase
0: The first clock transition is the first data capture edge
1: The second clock transition is the first data capture edge
*/
#define SPI_CLOCK_PHASE_1EDGE  (uint32_t)0ul
#define SPI_CLOCK_PHASE_2EDGE  (uint32_t)(1ul<<0)

//@ref SPI_SS_MANAGEMENT
/*
    SPI control register 1 (SPI_CR1)

Bit 9 SSM: Software slave management
When the SSM bit is set, the NSS pin input is replaced with the value from the SSI bit.
0: Software slave management disabled
1: Software slave management enabled
 
Bit 8 SSI: Internal slave select
This bit has an effect only when the SSM bit is set. The value of this bit is forced onto the 
NSS pin and the IO value of the NSS pin is ignored.

     SPI control register 2 (SPI_CR2)
Bit 2 SSOE: SS output enable
0: SS output is disabled in master mode and the cell can work in multimaster configuration
1: SS output is enabled in master mode and when the cell is enabled. The cell cannot work 
in a multimaster environment.

*/
///Hardware
#define SPI_NSS_HARD_SLAVE                    (uint32_t)0ul
#define SPI_NSS_Hard_Master_output_enable     (uint32_t)(1ul<<2)       // CR2 -> Bit 2SSOE: SS output enable
#define SPI_NSS_Hard_Master_output_disable   ~(uint32_t)(1ul<<2)      // CR2 -> Bit 2SSOE: SS output enable

//Software
#define SPI_NSS_Soft_Reset                    (uint32_t)(1ul<<9)       // Bit 9SSM: Software slave management
#define SPI_NSS_Soft_set                      (uint32_t)((1ul<<9)|(1ul<<8))

//@ref SPI_BAUD_RATE
/*
    SPI control register 1 (SPI_CR1)
    Bits 5:3 BR[2:0]: Baud rate control
*/
#define SPI_BaudRate_DIV2   (uint32_t)(0ul<<3)
#define SPI_BaudRate_DIV4   (uint32_t)(1ul<<3)
#define SPI_BaudRate_DIV8   (uint32_t)(2ul<<3)
#define SPI_BaudRate_DIV16  (uint32_t)(3ul<<3)
#define SPI_BaudRate_DIV32  (uint32_t)(4ul<<3)
#define SPI_BaudRate_DIV64  (uint32_t)(5ul<<3)
#define SPI_BaudRate_DIV128 (uint32_t)(6ul<<3)
#define SPI_BaudRate_DIV256 (uint32_t)(7ul<<3)

//@ref SPI_IQR_ENABLE
/*
SPI control register 2 (SPI_CR2)
    Bit 7 TXEIE: Tx buffer empty interrupt enable
    0: TXE interrupt masked 
    1: TXE interrupt not masked.

    Bit 6 RXNEIE: RX buffer not empty interrupt enable
    0: RXNE interrupt masked 
    1: RXNE interrupt not masked.

    Bit 5 ERRIE: Error interrupt enable
    0: Error interrupt is masked
    1: Error interrupt is enabled
*/
#define SPI_IQR_NONE          (uint32_t)(0ul<<5)
#define SPI_IQR_ENABLE_ERRIE  (uint32_t)(1ul<<5)
#define SPI_IQR_ENABLE_RXNEIE (uint32_t)(1ul<<6)
#define SPI_IQR_ENABLE_TXEIE  (uint32_t)(1ul<<7)
#define SPI_IQR_ENABLE_ALL    (uint32_t)((1ul<<5)|(1ul<<6)|(1ul<<7))
#define SPI_IQR_DISABLE_ALL  ~(uint32_t)((1ul<<5)|(1ul<<6)|(1ul<<7))


/*
* ===============================================
*      APIs Supported by "MCAL SPI DRIVER"
* ===============================================
*/


/**================================================================
* @Fn-        - SPI_init
* @brief - used to initialize the SPI peripheral based on the user configuration & SPI1/2
* @param [in] - SPI_CONFIG_t *SPI_pinConfig - SPI configuration structure
* @param [in] - SPI_RegDef_t *SPIx - SPI peripheral base address of SPI1/2
* @retval - none
* Note- This function should be called first before any other SPI functions , not forget call SPI_GPIO_SetPins() after this function
*/
void SPI_init(SPI_CONFIG_t *SPI_pinConfig, SPI_RegDef_t *SPIx);

/**================================================================
* @Fn-       - SPI_DeInit
* @brief - used to deinitialize the SPI peripheral using RESET peripheral register
* @param [in] - SPI_RegDef_t *SPIx - SPI peripheral base address of SPI1/2/3
* @param [out] - None
* @retval - None
* Note- this function will reset the SPI peripheral 1 or 2
*/
void SPI_DeInit(SPI_RegDef_t *SPIx);


/**================================================================
* @Fn-       - SPI_SendData
* @brief - this function will send data based on the polling mechanism
* @param [in] - SPI_RegDef_t *SPIx - SPI peripheral base address of SPI1/2/
* @param [in] - uint16_t pData - data to be sent
* @param [in] - PollingMechanism PollingEn - enable/disable polling mechanism
* @retval - None
* Note- None
*/
void SPI_SendData(SPI_RegDef_t *SPIx, uint16_t pData,  PollingMechanism PollingEn );
/**================================================================
* @Fn-      - SPI_RecieveData
* @brief - this function will recieve data based on the polling mechanism
* @param [in] - SPI_RegDef_t *SPIx - SPI peripheral base address of SPI1/2/
* @param [in] - PollingMechanism PollingEn - enable/disable polling mechanism
* @param [out] - uint16_t *pData - data to be recieved 
* @retval - None
* Note- None
*/
void SPI_RecieveData(volatile SPI_RegDef_t *pSPIx, uint16_t *pData, PollingMechanism PollingEn);

/**================================================================
* @Fn- SPI_GPIO_SetPins
* @brief - This function will set the GPIO pins for SPI1/2 based on recommended configuration
* @param [in] - SPI_RegDef_t *SPIx - SPI peripheral base address of SPI1/2
* @param [out] - None
* @retval - None
* Note- None
*/
void SPI_GPIO_SetPins(SPI_RegDef_t *SPIx);
void SPI_GPIO_SetPins_V2(SPI_RegDef_t *SPIx);

/**================================================================
* @Fn- SPI_RXTX
* @brief - This function will send and recieve data based on the polling mechanism
* @param [in] - SPI_RegDef_t *SPIx - SPI peripheral base address of SPI1/2
* @param [in] - PollingMechanism PollingEn - enable/disable polling mechanism
* @param [in/out] - uint16_t *pData - data to be sent and will change to recieved data
* @retval - None
* Note- None
*/
void SPI_RXTX(SPI_RegDef_t *SPIx, uint16_t *pData,  PollingMechanism PollingEn);


void pin_en_en(uint8_t flag);

#endif //__SPI_H
