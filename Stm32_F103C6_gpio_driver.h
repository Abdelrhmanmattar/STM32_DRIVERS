#ifndef INC_STM32_F103C6_GPIO_DRIVER_H_
#define INC_STM32_F103C6_GPIO_DRIVER_H_


//-----------------------------
//Includes
//-----------------------------
#include "stm32f103x6.h"

//-----------------------------
//User type definitions (structures) 
//-----------------------------
typedef struct
{
    uint8_t GPIO_PinNumber;     //Possible values from @ref GPIO_PIN_NUMBERS
    uint8_t GPIO_PinMode;       //Possible values from @ref GPIO_PIN_MODES
    uint8_t GPIO_Direction;     //Possible values from @ref GPIO_PIN_DIRECTION&SPEED
}PIN_CONFIG_t;

//-------------------------------------------------------------------------------------

//-----------------------------
//Macros Configuration References
//-----------------------------



//@ref GPIO_PIN_state
#define GPIO_PIN_SET    	1
#define GPIO_PIN_RESET     0

//@ref GPIO_RETURN_LOCK
#define GPIO_RETURN_LOCK_Enabled    	1
#define GPIO_RETURN_LOCK_ERROR     	    0


//@ref GPIO_PIN_NUMBERS
#define GPIO_PIN_0      0
#define GPIO_PIN_1      1
#define GPIO_PIN_2      2
#define GPIO_PIN_3      3
#define GPIO_PIN_4      4
#define GPIO_PIN_5      5
#define GPIO_PIN_6      6
#define GPIO_PIN_7      7
#define GPIO_PIN_8      8
#define GPIO_PIN_9      9
#define GPIO_PIN_10     10
#define GPIO_PIN_11     11
#define GPIO_PIN_12     12
#define GPIO_PIN_13     13
#define GPIO_PIN_14     14
#define GPIO_PIN_15     15

#define GPIO_PIN_ALL    0xFFFF
#define GPIO_MASK       0x0000FFFFUL

//@ref GPIO_PIN_MODES
//for input pins
#define Analog         0b00
#define Floating       0b01
#define Input_PullUp   0b10
#define Input_PullDown 0b11

//for output pins
#define Output_General_PushPull         0b00
#define Output_General_OpenDrain        0b01
#define Output_Alternate_PushPull       0b10
#define Output_Alternate_OpenDrain      0b11

//@ref GPIO_PIN_DIRECTION&SPEED
#define Input           0b00
#define Output_10MHz    0b01
#define Output_2MHz     0b10
#define Output_50MHz    0b11

//-------------------------------------------------------------------------------------


/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

/**================================================================
* @Fn-     MCAL_GPIO_Init
* @brief - Initialize the GPIO pin according to the specified configuration
* @param [in] - GPIOx - Base address of the GPIO port
* @param [in] - pinConfig - Pointer to the configuration structure
* @retval - None
* Note- use GPIOx which are supported by the package you are using
*/
void MCAL_GPIO_Init(GPIOx_RegDef_t *GPIOx, PIN_CONFIG_t *pinConfig);

/**================================================================
* @Fn- MCAL_GPIO_DeInit
* @brief - De-Initialize the GPIO pin
* @param [in] - GPIOx - Base address of the GPIO port
* @param [out] - None
* @retval - None
* Note- NONE
*/
void MCAL_GPIO_DeInit(GPIOx_RegDef_t *GPIOx);

/**================================================================
* @Fn- MCAL_GPIO_ReadPin
* @brief - Read the value from a GPIOx pinx and return the value
* @param [in] - GPIOx - Base address of the GPIO port
* @param [in] - PinNumber - Pin number of the GPIO port
* @retval - uint8_t - Value read from the pin
* Note- 
*/
uint8_t MCAL_GPIO_ReadPin(GPIOx_RegDef_t *GPIOx, uint8_t PinNumber);


/**================================================================
* @Fn- MCAL_GPIO_ReadPort
* @brief - Read the value from a GPIOx port and return the value
* @param [in] - GPIOx - Base address of the GPIO port
* @param [out] - None
* @retval - uint16_t - Value read from the port
* Note- NONE
*/
uint16_t MCAL_GPIO_ReadPort(GPIOx_RegDef_t *GPIOx);
/**================================================================
* @Fn- MCAL_GPIO_WritePin
* @brief - Write the value to a GPIOx pinx 
* @param [in] - GPIOx - Base address of the GPIO port
* @param [in] - PinNumber - Pin number of the GPIO port
* @param [in] - Value - Value to be written
* @retval - None
* Note- None
*/
void MCAL_GPIO_WritePin(GPIOx_RegDef_t *GPIOx, uint8_t PinNumber, uint8_t Value);

/**================================================================
* @Fn- MCAL_GPIO_WritePort
* @brief - Write the value to a GPIOx port
* @param [in] - GPIOx - Base address of the GPIO port
* @param [in] - Value - Value to be written
* @retval - None
* Note- None
*/
void MCAL_GPIO_WritePort(GPIOx_RegDef_t *GPIOx, uint16_t Value);

/**================================================================
* @Fn- MCAL_GPIO_TogglePin
* @brief - Toggle the value of a GPIOx pinx
* @param [in] - GPIOx - Base address of the GPIO port
* @param [in] - PinNumber - Pin number of the GPIO port
* @retval - None
* Note-
*/
void MCAL_GPIO_TogglePin(GPIOx_RegDef_t *GPIOx, uint8_t PinNumber);

/**================================================================
* @Fn- MCAL_GPIO_LockPin
* @brief - Lock the GPIOx pinx
* @param [in] - GPIOx - Base address of the GPIO port
* @param [in] - PinNumber - Pin number of the GPIO port
* @retval - uint8_t - Return GPIO_RETURN_LOCK_Enabled if the pin is locked, GPIO_RETURN_LOCK_ERROR if the pin is not locked @ref GPIO_RETURN_LOCK
* Note-
*/
uint8_t MCAL_GPIO_LockPin(GPIOx_RegDef_t *GPIOx, uint8_t PinNumber);

#endif /* INC_STM32_F103C6_GPIO_DRIVER_H_ */

/**================================================================
* @Fn-
* @brief -
* @param [in] -
* @param [out] -
* @retval -
* Note-
*/
