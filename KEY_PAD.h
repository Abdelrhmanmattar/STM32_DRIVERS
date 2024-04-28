#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "Stm32_F103C6_gpio_driver.h"


//------------------
// Keypad Connection port
//------------------
#define KEYPAD_PORT GPIOB

//------------------
// Keypad Connection pins
//------------------
#define R0 GPIO_PIN_0
#define R1 GPIO_PIN_1
#define R2 GPIO_PIN_3
#define R3 GPIO_PIN_4
#define C0 GPIO_PIN_5
#define C1 GPIO_PIN_6
#define C2 GPIO_PIN_7
#define C3 GPIO_PIN_8

//------------------
// Keypad functions
//------------------
void Keypad_init(void);
uint8_t Keypad_getkey(void);



#endif /* KEYPAD_H_ */