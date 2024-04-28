#ifndef __STM32_F103C6_EXTI_DRIVER_H
#define __STM32_F103C6_EXTI_DRIVER_H




//-----------------------------
//Includes
//-----------------------------

#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "std_macros.h"

//-----------------------------

//====================================
//User type definitions (structures)
//====================================
// @ref EXTI_Trigger_define
typedef enum
{
    EXTI_Rising_edge  = 1,
    EXTI_Falling_edge = 2,
    EXTI_BOTH_edges   = 3
} EXTI_Trigger_define;

/*
* @brief EXTI_Mapping_t
* This structure is used to map the EXTI line with the GPIO pin
* @param pGPIOx: pointer to the GPIO port 
* @param GPIO_Pin: GPIO pin number
* @param IVT_IRQ_Number: Interrupt vector table number 
*/
typedef struct
{
    GPIOx_RegDef_t *pGPIOx;
    uint8_t GPIO_Pin;
    uint8_t IVT_IRQ_Number;
}EXTI_Mapping_t;

/*
* @brief EXTI_PIN_Config_t
* This structure is used to configure the EXTI line
* @param pin_conf: EXTI_Mapping_t structure , this must be initialized based on @ref EXTI_Mapping
* @param TRIGGER_MODE: Trigger mode for the EXTI line  @ref EXTI_Trigger_define
* @param IRQ_Enable: Enable or disable the IRQ 1(Enable) 0(Disable)
* @param pCallback: pointer to the callback function called in ISR
*/
typedef struct
{
    EXTI_Mapping_t pin_conf;
    EXTI_Trigger_define TRIGGER_MODE;
    uint8_t IRQ_Enable;
    void (*pCallback)(void);
}EXTI_PIN_Config_t;
//===============================================
//      Macros Configuration References
//===============================================
//@ref EXTI_Mapping

#define EXTI0PA0			(EXTI_Mapping_t){GPIOA , GPIO_PIN_0 , EXTI0_IRQ }
#define EXTI0PB0			(EXTI_Mapping_t){GPIOB , GPIO_PIN_0 , EXTI0_IRQ }
#define EXTI0PC0			(EXTI_Mapping_t){GPIOC , GPIO_PIN_0 , EXTI0_IRQ }
#define EXTI0PD0			(EXTI_Mapping_t){GPIOD , GPIO_PIN_0 , EXTI0_IRQ }

#define EXTI1PA1			(EXTI_Mapping_t){GPIOA , GPIO_PIN_1 , EXTI1_IRQ }
#define EXTI1PB1			(EXTI_Mapping_t){GPIOB , GPIO_PIN_1 , EXTI1_IRQ }
#define EXTI1PC1			(EXTI_Mapping_t){GPIOC , GPIO_PIN_1 , EXTI1_IRQ }
#define EXTI1PD1			(EXTI_Mapping_t){GPIOD , GPIO_PIN_1 , EXTI1_IRQ }

#define EXTI2PA2			(EXTI_Mapping_t){GPIOA , GPIO_PIN_2 , EXTI2_IRQ }
#define EXTI2PB2			(EXTI_Mapping_t){GPIOB , GPIO_PIN_2 , EXTI2_IRQ }
#define EXTI2PC2			(EXTI_Mapping_t){GPIOC , GPIO_PIN_2 , EXTI2_IRQ }
#define EXTI2PD2			(EXTI_Mapping_t){GPIOD , GPIO_PIN_2 , EXTI2_IRQ }

#define EXTI3PA3			(EXTI_Mapping_t){GPIOA , GPIO_PIN_3 , EXTI3_IRQ }
#define EXTI3PB3			(EXTI_Mapping_t){GPIOB , GPIO_PIN_3 , EXTI3_IRQ }
#define EXTI3PC3			(EXTI_Mapping_t){GPIOC , GPIO_PIN_3 , EXTI3_IRQ }
#define EXTI3PD3			(EXTI_Mapping_t){GPIOD , GPIO_PIN_3 , EXTI3_IRQ }

#define EXTI4PA4			(EXTI_Mapping_t){GPIOA , GPIO_PIN_4 , EXTI4_IRQ }
#define EXTI4PB4			(EXTI_Mapping_t){GPIOB , GPIO_PIN_4 , EXTI4_IRQ }
#define EXTI4PC4			(EXTI_Mapping_t){GPIOC , GPIO_PIN_4 , EXTI4_IRQ }
#define EXTI4PD4			(EXTI_Mapping_t){GPIOD , GPIO_PIN_4 , EXTI4_IRQ }

#define EXTI5PA5			(EXTI_Mapping_t){GPIOA , GPIO_PIN_5 , EXTI5_IRQ }
#define EXTI5PB5			(EXTI_Mapping_t){GPIOB , GPIO_PIN_5 , EXTI5_IRQ }
#define EXTI5PC5			(EXTI_Mapping_t){GPIOC , GPIO_PIN_5 , EXTI5_IRQ }
#define EXTI5PD5			(EXTI_Mapping_t){GPIOD , GPIO_PIN_5 , EXTI5_IRQ }

#define EXTI6PA6			(EXTI_Mapping_t){GPIOA , GPIO_PIN_6 , EXTI6_IRQ }
#define EXTI6PB6			(EXTI_Mapping_t){GPIOB , GPIO_PIN_6 , EXTI6_IRQ }
#define EXTI6PC6			(EXTI_Mapping_t){GPIOC , GPIO_PIN_6 , EXTI6_IRQ }
#define EXTI6PD6			(EXTI_Mapping_t){GPIOD , GPIO_PIN_6 , EXTI6_IRQ }

#define EXTI7PA7			(EXTI_Mapping_t){GPIOA , GPIO_PIN_7 , EXTI7_IRQ }
#define EXTI7PB7			(EXTI_Mapping_t){GPIOB , GPIO_PIN_7 , EXTI7_IRQ }
#define EXTI7PC7			(EXTI_Mapping_t){GPIOC , GPIO_PIN_7 , EXTI7_IRQ }
#define EXTI7PD7			(EXTI_Mapping_t){GPIOD , GPIO_PIN_7 , EXTI7_IRQ }

#define EXTI8PA8			(EXTI_Mapping_t){GPIOA , GPIO_PIN_8 , EXTI8_IRQ }
#define EXTI8PB8			(EXTI_Mapping_t){GPIOB , GPIO_PIN_8 , EXTI8_IRQ }
#define EXTI8PC8			(EXTI_Mapping_t){GPIOC , GPIO_PIN_8 , EXTI8_IRQ }
#define EXTI8PD8			(EXTI_Mapping_t){GPIOD , GPIO_PIN_8 , EXTI8_IRQ }

#define EXTI9PA9			(EXTI_Mapping_t){GPIOA , GPIO_PIN_9 , EXTI9_IRQ }
#define EXTI9PB9			(EXTI_Mapping_t){GPIOB , GPIO_PIN_9 , EXTI9_IRQ }
#define EXTI9PC9			(EXTI_Mapping_t){GPIOC , GPIO_PIN_9 , EXTI9_IRQ }
#define EXTI9PD9			(EXTI_Mapping_t){GPIOD , GPIO_PIN_9 , EXTI9_IRQ }

#define EXTI10PA10			(EXTI_Mapping_t){GPIOA , GPIO_PIN_10 , EXTI10_IRQ }
#define EXTI10PB10			(EXTI_Mapping_t){GPIOB , GPIO_PIN_10 , EXTI10_IRQ }
#define EXTI10PC10			(EXTI_Mapping_t){GPIOC , GPIO_PIN_10 , EXTI10_IRQ }
#define EXTI10PD10			(EXTI_Mapping_t){GPIOD , GPIO_PIN_10 , EXTI10_IRQ }

#define EXTI11PA11			(EXTI_Mapping_t){GPIOA , GPIO_PIN_11 , EXTI11_IRQ }
#define EXTI11PB11			(EXTI_Mapping_t){GPIOB , GPIO_PIN_11 , EXTI11_IRQ }
#define EXTI11PC11			(EXTI_Mapping_t){GPIOC , GPIO_PIN_11 , EXTI11_IRQ }
#define EXTI11PD11			(EXTI_Mapping_t){GPIOD , GPIO_PIN_11 , EXTI11_IRQ }

#define EXTI12PA12			(EXTI_Mapping_t){GPIOA , GPIO_PIN_12 , EXTI12_IRQ }
#define EXTI12PB12			(EXTI_Mapping_t){GPIOB , GPIO_PIN_12 , EXTI12_IRQ }
#define EXTI12PC12			(EXTI_Mapping_t){GPIOC , GPIO_PIN_12 , EXTI12_IRQ }
#define EXTI12PD12			(EXTI_Mapping_t){GPIOD , GPIO_PIN_12 , EXTI12_IRQ }

#define EXTI13PA13			(EXTI_Mapping_t){GPIOA , GPIO_PIN_13 , EXTI13_IRQ }
#define EXTI13PB13			(EXTI_Mapping_t){GPIOB , GPIO_PIN_13 , EXTI13_IRQ }
#define EXTI13PC13			(EXTI_Mapping_t){GPIOC , GPIO_PIN_13 , EXTI13_IRQ }
#define EXTI13PD13			(EXTI_Mapping_t){GPIOD , GPIO_PIN_13 , EXTI13_IRQ }

#define EXTI14PA14			(EXTI_Mapping_t){GPIOA , GPIO_PIN_14 , EXTI14_IRQ }
#define EXTI14PB14			(EXTI_Mapping_t){GPIOB , GPIO_PIN_14 , EXTI14_IRQ }
#define EXTI14PC14			(EXTI_Mapping_t){GPIOC , GPIO_PIN_14 , EXTI14_IRQ }
#define EXTI14PD14			(EXTI_Mapping_t){GPIOD , GPIO_PIN_14 , EXTI14_IRQ }

#define EXTI15PA15			(EXTI_Mapping_t){GPIOA , GPIO_PIN_15 , EXTI15_IRQ }
#define EXTI15PB15			(EXTI_Mapping_t){GPIOB , GPIO_PIN_15 , EXTI15_IRQ }
#define EXTI15PC15			(EXTI_Mapping_t){GPIOC , GPIO_PIN_15 , EXTI15_IRQ }
#define EXTI15PD15			(EXTI_Mapping_t){GPIOD , GPIO_PIN_15 , EXTI15_IRQ }








//====================================
//APIs Supported by this driver
//====================================

void EXTI_INIT(EXTI_PIN_Config_t *pEXTI_PIN_Config);
void EXTI_DeInit(void);
void EXTI_UPDATE(EXTI_PIN_Config_t *pEXTI_PIN_Config);










#endif   //__STM32_F103C6_EXTI_DRIVER_H__
