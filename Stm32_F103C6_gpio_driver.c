#include "Stm32_F103C6_gpio_driver.h"

void MCAL_GPIO_Init(GPIOx_RegDef_t *GPIOx, PIN_CONFIG_t *pinConfig)
{
    volatile uint32_t *pGPIOx = (pinConfig->GPIO_PinNumber>7)?&GPIOx->CRH:&GPIOx->CRL;

    // Clear the CNF bits and MODE bits before setting them
    uint32_t tem =  0x0000000f << (4*(pinConfig->GPIO_PinNumber%8));
    *pGPIOx &= ~(tem);//%8 to get the pin number in the range of 8 - 15 for CRH and 0 - 7 for CRL
    uint8_t temp = 0;
    uint8_t mode = (pinConfig->GPIO_PinMode>2)?(2):pinConfig->GPIO_PinMode;
    temp |= ((mode<<2) | (pinConfig->GPIO_Direction));
    *pGPIOx |= (temp << (4*(pinConfig->GPIO_PinNumber%8)));
    
    if(pinConfig->GPIO_Direction==Input)
    {
        if(pinConfig->GPIO_PinMode==Input_PullUp)
        {
            GPIOx->ODR |= (1<<pinConfig->GPIO_PinNumber);
        }
        else if(pinConfig->GPIO_PinMode==Input_PullDown)
        {
            GPIOx->ODR &= ~(1<<pinConfig->GPIO_PinNumber);
        }
    } 
    
}


void MCAL_GPIO_DeInit(GPIOx_RegDef_t *GPIOx)
{
    uint32_t temp = (uint32_t)GPIOx-(uint32_t)GPIOA_BASE;
    temp = temp/0x400;           //0x400 is the size of each GPIO peripheral
    RCC->APB2RSTR |= (1<<(temp+2)); //+2 because the reset bit for GPIOA is at 2nd bit in APB2RSTR
    RCC->APB2RSTR &= ~(1<<(temp+2)); 
}


uint8_t MCAL_GPIO_ReadPin(GPIOx_RegDef_t *GPIOx, uint8_t PinNumber)
{
    return  ((GPIOx->IDR >> PinNumber) & 0x1);
}

uint16_t MCAL_GPIO_ReadPort(GPIOx_RegDef_t *GPIOx)
{
    return (uint16_t)GPIOx->IDR;
}

void MCAL_GPIO_WritePin(GPIOx_RegDef_t *GPIOx, uint8_t PinNumber, uint8_t Value)
{
    if (Value == GPIO_PIN_SET)
    {
        GPIOx->ODR |= (1<<PinNumber);
    }
    else
    {
        GPIOx->ODR &= ~(1<<PinNumber);
    }
}

void MCAL_GPIO_WritePort(GPIOx_RegDef_t *GPIOx, uint16_t Value)
{
    GPIOx->ODR = Value;
}
void MCAL_GPIO_TogglePin(GPIOx_RegDef_t *GPIOx, uint8_t PinNumber)
{
    GPIOx->ODR ^= (1<<PinNumber);
}

uint8_t MCAL_GPIO_LockPin(GPIOx_RegDef_t *GPIOx, uint8_t PinNumber)
{
    uint32_t temp = (1<<16) | (1<<PinNumber);
    GPIOx->BRR = temp; //Set LCKK bit and the pin number to lock the pin
    GPIOx->BRR = (1<<PinNumber); //Reset the pin number to lock the pin
    GPIOx->BRR = temp; //Set the LCKK bit
    temp = GPIOx->LCKR; //Read the LCKR register to lock the pin
    if(temp & (1<<16))
    {
        return GPIO_RETURN_LOCK_Enabled;
    }
    return GPIO_RETURN_LOCK_ERROR;
}
