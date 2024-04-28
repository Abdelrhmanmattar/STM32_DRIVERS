#include "Stm32_F103C6_EXTI_driver.h"


//arrray of POINTERS TO ISRs
void (*EXTI_IRQ_FUN[16])(void) ;


void EXTI0_IRQHandler(void)
{
    EXTI_IRQ_FUN[0]();
    SET_BIT(EXTI->PR, 0);
}
void EXTI1_IRQHandler(void)
{
    EXTI_IRQ_FUN[1]();
    SET_BIT(EXTI->PR, 1);
}
void EXTI2_IRQHandler(void)
{
    EXTI_IRQ_FUN[2]();
    SET_BIT(EXTI->PR, 2);
}
void EXTI3_IRQHandler(void)
{
    EXTI_IRQ_FUN[3]();
    SET_BIT(EXTI->PR, 3);
}
void EXTI4_IRQHandler(void)
{
    EXTI_IRQ_FUN[4]();
    SET_BIT(EXTI->PR, 4);
}
void EXTI9_5_IRQHandler(void)
{
    for(uint8_t i = 5; i < 10; i++)
    {
        if(READ_BIT(EXTI->PR, i))
        {
            EXTI_IRQ_FUN[i]();
            SET_BIT(EXTI->PR, i);
        }
    }
}
void EXTI15_10_IRQHandler(void)
{
    for(uint8_t i = 10; i < 16; i++)
    {
        if(READ_BIT(EXTI->PR, i))
        {
            EXTI_IRQ_FUN[i]();
            SET_BIT(EXTI->PR, i);
        }
    }
}




void EXTI_INIT(EXTI_PIN_Config_t *pEXTI_PIN_Config)
{
    EXTI_UPDATE(pEXTI_PIN_Config);
}
void EXTI_DeInit(void)
{
    EXTI->IMR   = 0x00000000;
    EXTI->EMR   = 0x00000000;
    EXTI->RTSR  = 0x00000000;
    EXTI->FTSR  = 0x00000000;
    EXTI->SWIER = 0x00000000;
    EXTI->PR    = 0xFFFFFFFF;
}
void EXTI_UPDATE(EXTI_PIN_Config_t *pEXTI_PIN_Config)
{
    //1. Configure the GPIO pin as input
    PIN_CONFIG_t pin_conf;
    pin_conf.GPIO_PinNumber = pEXTI_PIN_Config->pin_conf.GPIO_Pin;
    pin_conf.GPIO_Direction = Input;
    pin_conf.GPIO_PinMode = Floating;
    MCAL_GPIO_Init(pEXTI_PIN_Config->pin_conf.pGPIOx, &pin_conf);

    //2. configure the AFIO register
    uint8_t index_EXTICR = pEXTI_PIN_Config->pin_conf.GPIO_Pin / 4;
    uint8_t postion_EXTICR = (pEXTI_PIN_Config->pin_conf.GPIO_Pin % 4) * 4;

    AFIO->EXTICR[index_EXTICR] &= ~(0xF << postion_EXTICR);
    uint8_t new_value = ((uint32_t)(pEXTI_PIN_Config->pin_conf.pGPIOx) - (uint32_t)(GPIOA)) / GPIO_OFFSET;
    AFIO->EXTICR[index_EXTICR] |= (new_value << postion_EXTICR);

    //3. Configure the Trigger mode
    CLR_BIT(EXTI->RTSR, pEXTI_PIN_Config->pin_conf.GPIO_Pin);
    CLR_BIT(EXTI->FTSR, pEXTI_PIN_Config->pin_conf.GPIO_Pin);

    EXTI->RTSR |= ((pEXTI_PIN_Config->TRIGGER_MODE & 0x1)        << pEXTI_PIN_Config->pin_conf.GPIO_Pin);
    EXTI->FTSR |= (((pEXTI_PIN_Config->TRIGGER_MODE >> 1) & 0x1) << pEXTI_PIN_Config->pin_conf.GPIO_Pin);
    
    //4. point to the ISR
    EXTI_IRQ_FUN[pEXTI_PIN_Config->pin_conf.GPIO_Pin] = pEXTI_PIN_Config->pCallback;
    
    //5. Enable the EXTI interrupt
    //6. Enable the NVIC interrupt
    if(pEXTI_PIN_Config->IRQ_Enable)
    {
        SET_BIT(EXTI->IMR, pEXTI_PIN_Config->pin_conf.GPIO_Pin);
        NVIC_ENABLE_IRQ(pEXTI_PIN_Config->pin_conf.IVT_IRQ_Number);
    }
    else
    {
        CLR_BIT(EXTI->IMR, pEXTI_PIN_Config->pin_conf.GPIO_Pin);
        NVIC_DISABLE_IRQ(pEXTI_PIN_Config->pin_conf.IVT_IRQ_Number);
    }
}
