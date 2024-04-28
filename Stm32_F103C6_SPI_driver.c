/*
 * Stm32_F103C6_gpio_driver.c
 *
 *  Created on: Apr 18, 2024
 *      Author: abdelrhman mattar
 */
#include "Stm32_F103C6_SPI_driver.h"
SPI_CONFIG_t* SPI_ARRAY[2]={NULL, NULL};

void SPI_init(SPI_CONFIG_t *SPI_pinConfig, SPI_RegDef_t *SPIx)
{
	uint16_t tmpreg_CR1 = 0;
	uint16_t tmpreg_CR2 = 0;
    if(SPIx == SPI1)
    {
        SPI1_ClockEnable();
        SPI_ARRAY[0] = SPI_pinConfig;
    }
    else if(SPIx == SPI2)
    {
        SPI2_ClockEnable();
        SPI_ARRAY[1] = SPI_pinConfig;
    }
    //SET DEVICE MODE
    tmpreg_CR1 = SPI_pinConfig->DEVICE_MODE;

    //SET COMMUNICATION MODE
    tmpreg_CR1 |= SPI_pinConfig->COMMUNICATION_MODE;

    //SET FRAME FORMAT
    tmpreg_CR1 |= SPI_pinConfig->FRAME_FORMAT;

    //SET DATA FRAME SIZE
    tmpreg_CR1 |= SPI_pinConfig->DATA_SIZE;

    //SET CLOCK POLARITY
    tmpreg_CR1 |= SPI_pinConfig->CLOCK_POLARITY;
    //SET CLOCK PHASE
    tmpreg_CR1 |= SPI_pinConfig->CLOCK_PHASE;

    //SET BAUD RATE
    tmpreg_CR1 |= SPI_pinConfig->BAUD_RATE;




    //SS_MANAGEMENT
	if(SPI_pinConfig->SS_MANAGEMENT == SPI_NSS_Hard_Master_output_enable){
		tmpreg_CR2 |= SPI_pinConfig->SS_MANAGEMENT;
	}
	else if(SPI_pinConfig->SS_MANAGEMENT== SPI_NSS_Hard_Master_output_disable){
		tmpreg_CR2 &= SPI_pinConfig->SS_MANAGEMENT;
	}
	else{
		tmpreg_CR1 |= SPI_pinConfig->SS_MANAGEMENT;
	}
    //SET IQR ENABLE
    if(SPI_pinConfig->IQR_ENABLE.SPI_IQR_REGIGSTER == 0) //DISABLE ALL SPI_IQR
    {
        tmpreg_CR2 &= SPI_IQR_DISABLE_ALL;
        if(SPIx == SPI1)     {NVIC_DISABLE_IRQ(SPI1_IRQ);}
        else if(SPIx == SPI2){NVIC_DISABLE_IRQ(SPI2_IRQ);}
    }
    else
    {
        tmpreg_CR2 |= SPI_pinConfig->IQR_ENABLE.SPI_IQR_REGIGSTER;
        if(SPIx == SPI1)     {NVIC_ENABLE_IRQ(SPI1_IRQ);}
        else if(SPIx == SPI2){NVIC_ENABLE_IRQ(SPI2_IRQ);}
    }

    //enable SPI
    SET_BIT(tmpreg_CR1, 6);

    //SET SPI_CR1
    SPIx->CR1 = tmpreg_CR1;
    //SET SPI_CR2
    SPIx->CR2 = tmpreg_CR2;

    SPIx->I2SCFGR &= ~(1<<11); //disable I2S mode

}

void SPI_DeInit(SPI_RegDef_t *SPIx)
{
    if(SPIx == SPI1)
    {
        SPI1_RESET();
        NVIC_DISABLE_IRQ(SPI1_IRQ);
        SPI_ARRAY[0] = NULL;
    }
    else if(SPIx == SPI2)
    {
        SPI2_RESET();
        NVIC_DISABLE_IRQ(SPI2_IRQ);
        SPI_ARRAY[1] = NULL;
    }   
}

void SPI_SendData(SPI_RegDef_t *SPIx, uint16_t pData,  PollingMechanism PollingEn )
{
    if(PollingEn==POLLING_ENABLE)
        while(READ_BIT(SPIx->SR, 1) == 0);

    SPIx->DR = pData;
}
void SPI_RecieveData(volatile SPI_RegDef_t *pSPIx, uint16_t *pData, PollingMechanism PollingEn)
{
    if (PollingEn == POLLING_ENABLE)
        while (!(READ_BIT(pSPIx->SR, 0)));

    *pData = pSPIx->DR;
}

void SPI_RXTX(SPI_RegDef_t *SPIx, uint16_t *pData,  PollingMechanism PollingEn)
{
    if(PollingEn==POLLING_ENABLE)
        while(READ_BIT(SPIx->SR, 1) == 0);
    SPIx->DR = *pData;
    if(PollingEn==POLLING_ENABLE)
        while(READ_BIT(SPIx->SR, 0) == 0);
    *pData = SPIx->DR;
}

void SPI_GPIO_SetPins_V2(SPI_RegDef_t *SPIx)
{
    GPIOx_RegDef_t  *GPIOx;
    PIN_CONFIG_t    spi_pins;
    uint8_t         pin_increase = 0;
    uint8_t         index        = 0;
    if(SPIx==SPI1)          {GPIOx = GPIOA;  pin_increase = 0; index = 0;}
    else if(SPIx==SPI2)     {GPIOx = GPIOB;  pin_increase = 8; index = 1;}
    else return;
	// PA4 : SPI1_NSS
	// PA5 : SPI1_SCK
	// PA6 : SPI1_MISO
	// PA7 : SPI1_MOSI
    if (SPI_ARRAY[index]->DEVICE_MODE == SPI_MASTER_MODE)
    {
        // PA4
        spi_pins.GPIO_PinNumber = GPIO_PIN_4+pin_increase;
        if (SPI_ARRAY[index]->SS_MANAGEMENT == SPI_NSS_Hard_Master_output_enable)
        {
            spi_pins.GPIO_PinMode = Output_Alternate_PushPull;
            spi_pins.GPIO_Direction = Output_10MHz;
            MCAL_GPIO_Init(GPIOx, &spi_pins);
        }
        else if (SPI_ARRAY[index]->SS_MANAGEMENT == SPI_NSS_Hard_Master_output_disable)
        {
            spi_pins.GPIO_PinMode = Floating;
            spi_pins.GPIO_Direction = Input;
            MCAL_GPIO_Init(GPIOx, &spi_pins);
        }

        // PA5
        spi_pins.GPIO_PinNumber = GPIO_PIN_5+pin_increase;
        spi_pins.GPIO_PinMode = Output_Alternate_PushPull;
        spi_pins.GPIO_Direction = Output_10MHz;
        MCAL_GPIO_Init(GPIOx, &spi_pins);

        // PA6
        spi_pins.GPIO_PinNumber = GPIO_PIN_6+pin_increase;
        spi_pins.GPIO_PinMode = Floating;
        spi_pins.GPIO_Direction = Input;
        MCAL_GPIO_Init(GPIOx, &spi_pins);

        // PA7
        spi_pins.GPIO_PinNumber = GPIO_PIN_7+pin_increase;
        spi_pins.GPIO_PinMode = Output_Alternate_PushPull;
        spi_pins.GPIO_Direction = Output_10MHz;
        MCAL_GPIO_Init(GPIOx, &spi_pins);
    }
    else if (SPI_ARRAY[index]->DEVICE_MODE == SPI_SLAVE_MODE)
    {
		// PA4 : SPI1_NSS
		// PA5 : SPI1_SCK
		// PA6 : SPI1_MISO
		// PA7 : SPI1_MOSI
        if (SPI_ARRAY[index]->SS_MANAGEMENT == SPI_NSS_HARD_SLAVE)
        {
            spi_pins.GPIO_PinNumber = GPIO_PIN_4+pin_increase;
            spi_pins.GPIO_PinMode = Floating;
            spi_pins.GPIO_Direction = Input;
            MCAL_GPIO_Init(GPIOx, &spi_pins);
        }
        // PA5
        spi_pins.GPIO_PinNumber = GPIO_PIN_5+pin_increase;
        spi_pins.GPIO_PinMode = Floating;
        spi_pins.GPIO_Direction = Input;
        MCAL_GPIO_Init(GPIOx, &spi_pins);
        // PA6
        spi_pins.GPIO_PinNumber = GPIO_PIN_6+pin_increase;
        spi_pins.GPIO_PinMode = Output_Alternate_PushPull;
        spi_pins.GPIO_Direction = Output_10MHz;
        MCAL_GPIO_Init(GPIOx, &spi_pins);
        // PA7
        spi_pins.GPIO_PinNumber = GPIO_PIN_7+pin_increase;
        spi_pins.GPIO_PinMode = Floating;
        spi_pins.GPIO_Direction = Input;
        MCAL_GPIO_Init(GPIOx, &spi_pins);
    }
}



//IRQ Handling

void SPI1_IRQHandler(void)
{
    SPI_IQR_HANDLER_t IQR_STATUS;
    IQR_STATUS.SPI_IQR_BITS.RXNEIE=READ_BIT(SPI1->SR, 0);
    IQR_STATUS.SPI_IQR_BITS.TXEIE=READ_BIT(SPI1->SR, 1);
    IQR_STATUS.SPI_IQR_BITS.ERRIE=READ_BIT(SPI1->SR, 4);

    if(SPI_ARRAY[0]->SPI_IQR_HANDLER != NULL)
    {
        SPI_ARRAY[0]->SPI_IQR_HANDLER(IQR_STATUS);
    }
}

void SPI2_IRQHandler(void)
{
    SPI_IQR_HANDLER_t IQR_STATUS;
    IQR_STATUS.SPI_IQR_BITS.RXNEIE=READ_BIT(SPI2->SR, 0);
    IQR_STATUS.SPI_IQR_BITS.TXEIE=READ_BIT(SPI2->SR, 1);
    IQR_STATUS.SPI_IQR_BITS.ERRIE=READ_BIT(SPI2->SR, 4);

    if(SPI_ARRAY[1]->SPI_IQR_HANDLER != NULL)
    {
        SPI_ARRAY[1]->SPI_IQR_HANDLER(IQR_STATUS);
    }
}


void pin_en_en(uint8_t flag)
{
	if(flag)
	{
		SET_BIT(SPI1->CR1 ,8);
	}
	else
	{
		CLR_BIT(SPI1->CR1,8);
	}
}
