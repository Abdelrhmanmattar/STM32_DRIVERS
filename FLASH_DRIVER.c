/*
 * FLASH_DRIVER.c
 *
 *  Created on: Apr 27, 2024
 *      Author: abdelrhman mattar
 */

#include "FLASH_DRIVER.h"



HAL_StatusTypeDef FLASH_UNLOCK(void)
{
    HAL_StatusTypeDef status = HAL_OK;
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
    if (READ_BIT(FLASH->CR , 7) == 1){status = HAL_ERROR;}
    return status;
}
HAL_StatusTypeDef FLASH_LOCK(void)
{
    HAL_StatusTypeDef status = HAL_OK;
    SET_BIT(FLASH->CR , 7);
    if (READ_BIT(FLASH->CR , 7) == 0){status = HAL_ERROR;}
    return status;
}

//READ address from flash
uint32_t FLASH_READ(uint32_t address)
{
    return *(uint32_t*)address;
}


//WRITE data to flash
HAL_StatusTypeDef FLASH_WRITE_HALFWORD(uint16_t data, uint32_t address)
{
    HAL_StatusTypeDef status = HAL_OK;
    if(IS_VALID_ADDRESS(address) == 0){status = HAL_OUT_RANGE;}
    else if (READ_BIT(FLASH->CR , 7) == 0)
    {
        while(READ_BIT(FLASH->SR , 0) == 1);
        SET_BIT(FLASH->CR , 0);
        *(uint16_t*)address = data;
        while(READ_BIT(FLASH->SR , 0) == 1);
        if( data != *(uint16_t*)address){status = HAL_ERROR;}
    }
    return status;
}

HAL_StatusTypeDef FLASH_WRITE_SEQUENCE(uint16_t* data, uint32_t address, uint32_t size)
{
    HAL_StatusTypeDef status = HAL_OK;
    for(uint32_t i=0; i<size; i++)
    {
        status = FLASH_WRITE_HALFWORD(data[i], address + (i*2));
        if(status != HAL_OK){break;}
    }
    return status;
}

//ERASE flash
uint8_t FLASH_ERASE_PAGE(uint32_t address)
{
    HAL_StatusTypeDef status = HAL_OK;
    if(IS_VALID_ADDRESS(address) == 0){status = HAL_OUT_RANGE;}
    else if (READ_BIT(FLASH->CR , 7) == 0)
    {
        while(READ_BIT(FLASH->SR , 0) == 1);
        SET_BIT(FLASH->CR , 1);
        FLASH->AR = address;
        SET_BIT(FLASH->CR , 6);
        while(READ_BIT(FLASH->SR , 0) == 1);
    }
    else
    {
        status = HAL_ERROR;
    }
    return status;
}
uint8_t FLASH_ERASE_SEQUENCE(uint32_t address, uint32_t size)
{
    //this function take first address of the page to be erased
    //and the number of pages to be erased
    HAL_StatusTypeDef status = HAL_OK;
    for(uint32_t i=0; i<size; i++)
    {
        status = FLASH_ERASE_PAGE(address + (i*FLASH_PAGE_SIZE));
        if(status != HAL_OK){break;}
    }
    return status;
}