/*
 * FLASH_DRIVER.h
 *
 *  Created on: Apr 27, 2024
 *      Author: abdelrhman mattar
 */

#ifndef FLASH_DRIVER_H_
#define FLASH_DRIVER_H_


//-----------------------------
//defines
//-----------------------------
#define FLASH_KEY1          0x45670123UL
#define FLASH_KEY2          0xCDEF89ABUL

#define FLASH_PAGE_SIZE     1024UL
#define FLASH_START_ADDRESS FLASH_BASE
#define FLASH_PAGE_NUMBER   128UL
#define FLASH_END_ADDRESS   (FLASH_BASE + (FLASH_PAGE_SIZE * FLASH_PAGE_NUMBER) - 1)

//INCLUDES
#include "stm32f103x6.h"
#include "std_macros.h"
#include "inttypes.h"


//-----------------------------
//user definintions 
//-----------------------------
typedef enum
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_OUT_RANGE  = 0x03U
} HAL_StatusTypeDef;


//
#define IS_VALID_ADDRESS(address) ((address >= FLASH_START_ADDRESS) && (address <= FLASH_END_ADDRESS))

HAL_StatusTypeDef FLASH_UNLOCK(void);
HAL_StatusTypeDef FLASH_LOCK(void);

//READ address from flash
uint32_t FLASH_READ(uint32_t address);

//WRITE data to flash
HAL_StatusTypeDef FLASH_WRITE_HALFWORD(uint16_t data, uint32_t address);
HAL_StatusTypeDef FLASH_WRITE_SEQUENCE(uint16_t* data, uint32_t address, uint32_t size);

//ERASE flash
uint8_t FLASH_ERASE_PAGE(uint32_t address);
uint8_t FLASH_ERASE_SEQUENCE(uint32_t address, uint32_t size);




#endif /* FLASH_DRIVER_H_ */
