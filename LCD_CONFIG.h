#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H

#include "Stm32_F103C6_gpio_driver.h"


//ports and pins for configuration

#define LCD_CONTROL_PORT GPIOA //PORT FOR RS,RW,EN,DATA PINS
#define DATA_PIN_START GPIO_PIN_0 //FOR FIRST PIN OF DATA PINS CONNECTED TO LCD

#define RS_PIN GPIO_PIN_8
#define RW_PIN GPIO_PIN_9
#define EN_PIN GPIO_PIN_10

/*
* to use 8 bit mode uncomment the EIGHT_BIT_MODE macro
* and comment in the FOUR_BIT_MODE macro
* vice versa
*/
#define EIGHT_BIT_MODE 8
//#define FOUR_BIT_MODE 4



#endif // LCD_CONFIG_H
