#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//-----------------------------
//Includes
//-----------------------------
#include <stdio.h>
#include "stdlib.h"
#include "inttypes.h"
//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_BASE                              0x08000000UL
#define SYSTEM_MEMORY_BASE                      0x1FFFF000UL
#define SRAM_BASE                               0x20000000UL
#define Peripherals_BASE                        0x40000000UL
#define Cortex_M3_Internal_Peripherals_BASE     0xE0000000UL
#define NVIC_BASE                               0xE000E100UL // @ref to NVIC register map
//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------


//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------

//RCC                                          //@ref to RCC register map
#define RCC_BASE                                0x40021000UL
//FLASH                                        //@ref to FLASH register map
#define Flash_memory_interface                              0x40022000UL
//-----------------------------
//Base addresses for APB2 Peripherals
//-----------------------------

//GPIO                                        //@ref to GPIO register map
//A,B fully included in LQFP48 Package
#define GPIOA_BASE                              0x40010800UL
#define GPIOB_BASE                              0x40010C00UL
//C,D partially included in LQFP48 Package
#define GPIOC_BASE                              0x40011000UL
#define GPIOD_BASE                              0x40011400UL
//E not included in LQFP48 Package
#define GPIOE_BASE                              0x40011800UL

//differance between GPIOx base addresses
#define GPIO_OFFSET                             0x400UL



//EXTI                                        //@ref to EXTI register map
#define EXTI_BASE 							    0x40010400UL

//AFIO                                        //@ref to AFIO register map
#define AFIO_BASE 							    0x40010000UL



//----------------------------------------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*

//RCC register map and reset values
typedef struct
{
    uint32_t CR;
    uint32_t CFGR;
    uint32_t CIR;
    uint32_t APB2RSTR;
    uint32_t APB1RSTR;
    uint32_t AHBENR;
    uint32_t APB2ENR;
    uint32_t APB1ENR;
    uint32_t BDCR;
    uint32_t CSR;
}RCC_RegDef_t;


//FLASH 
typedef struct
{
    uint32_t ACR;
    uint32_t KEYR;
    uint32_t OPTKEYR;
    uint32_t SR;
    uint32_t CR;
    uint32_t AR;
    uint32_t RESERVED;
    uint32_t OBR;
    uint32_t WRPR;
}FLASH_RegDef_t;

//GPIO

typedef struct
{
    uint32_t CRL;
    uint32_t CRH;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t BRR;
    uint32_t LCKR;
}GPIOx_RegDef_t;

//AFIO
typedef struct
{
    uint32_t EVCR;
    uint32_t MAPR;
    uint32_t EXTICR[4];
    uint32_t MAPR2;
}AFIO_RegDef_t;

//EXTI
typedef struct
{
    uint32_t IMR;
    uint32_t EMR;
    uint32_t RTSR;
    uint32_t FTSR;
    uint32_t SWIER;
    uint32_t PR;
}EXTI_RegDef_t;

//NVIC
typedef struct
{
    uint32_t ISER[3];
}NVIC_Enable_Registers_t;

typedef struct
{
    uint32_t ICER[3];
}NVIC_Disable_Registers_t;


//----------------------------------------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*

//RCC
//@ref to RCC Instants
#define RCC                                 ((volatile RCC_RegDef_t*)RCC_BASE)

//FLASH
//@ref to FLASH Instants
#define FLASH                               ((volatile FLASH_RegDef_t*)Flash_memory_interface)

//GPIO
//@ref to GPIO Instants
#define GPIOA                               ((volatile GPIOx_RegDef_t*)GPIOA_BASE)
#define GPIOB                               ((volatile GPIOx_RegDef_t*)GPIOB_BASE)
#define GPIOC                               ((volatile GPIOx_RegDef_t*)GPIOC_BASE)
#define GPIOD                               ((volatile GPIOx_RegDef_t*)GPIOD_BASE)
#define GPIOE                               ((volatile GPIOx_RegDef_t*)GPIOE_BASE)
//AFIO
//@ref to AFIO Instants
#define AFIO                                ((volatile AFIO_RegDef_t*)AFIO_BASE)

//EXTI
//@ref to EXTI Instants
#define EXTI                                ((volatile EXTI_RegDef_t*)EXTI_BASE)




//NVIC
// @ref to NVIC register map
#define NVIC_ISER                           ((volatile NVIC_Enable_Registers_t*)NVIC_BASE)
#define NVIC_ICER                           ((volatile NVIC_Disable_Registers_t*)NVIC_BASE+0x80UL)
// @ref NVIC_IQR_NUMBERS
#define NVIC_ENABLE_IRQ(IRQ_Number)         (NVIC_ISER->ISER[IRQ_Number/32] |= (1 << (IRQ_Number % 32)))
#define NVIC_DISABLE_IRQ(IRQ_Number)        (NVIC_ICER->ICER[IRQ_Number/32] |= (1 << (IRQ_Number % 32)))                  


//----------------------------------------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

//GPIOx
#define GPIOA_ClockEnable()                 (RCC->APB2ENR |= (1<<2))
#define GPIOB_ClockEnable()                 (RCC->APB2ENR |= (1<<3))
#define GPIOC_ClockEnable()                 (RCC->APB2ENR |= (1<<4))
#define GPIOD_ClockEnable()                 (RCC->APB2ENR |= (1<<5))
#define GPIOE_ClockEnable()                 (RCC->APB2ENR |= (1<<6))
#define GPIOF_ClockEnable()                 (RCC->APB2ENR |= (1<<7))
#define GPIOG_ClockEnable()                 (RCC->APB2ENR |= (1<<8))


//AFIO
#define AFIO_ClockEnable()                  (RCC->APB2ENR |= (1<<0))

//----------------------------------------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//External Interrupt Macros:
//-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-
//Line Number
#define EXTI0  0
#define EXTI1  1
#define EXTI2  2
#define EXTI3  3
#define EXTI4  4
#define EXTI5  5
#define EXTI6  6
#define EXTI7  7
#define EXTI8  8
#define EXTI9  9
#define EXTI10 10
#define EXTI11 11
#define EXTI12 12
#define EXTI13 13
#define EXTI14 14
#define EXTI15 15

// Interrupt request line Number
// @ref NVIC_IQR_NUMBERS
#define EXTI0_IRQ   6
#define EXTI1_IRQ   7
#define EXTI2_IRQ   8
#define EXTI3_IRQ   9
#define EXTI4_IRQ   10
#define EXTI5_IRQ   23
#define EXTI6_IRQ   23
#define EXTI7_IRQ   23
#define EXTI8_IRQ   23
#define EXTI9_IRQ   23
#define EXTI10_IRQ  40
#define EXTI11_IRQ  40
#define EXTI12_IRQ  40
#define EXTI13_IRQ  40
#define EXTI14_IRQ  40
#define EXTI15_IRQ  40







//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*



#endif /* INC_STM32F103X6_H_ */
