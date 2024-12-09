/**
 * @file m24512.c
 * @brief Реализация функций для работы с EEPROM M24512
 */

#include "m24512.h"
#include "i2c.h"
#include "delay.h"

/** @brief Время ожидания завершения записи в мс */
#define M24512_WRITE_TIMEOUT 5

/**
 * @brief Проверка занятости устройства
 * 
 * @return Результат проверки
 * @retval 0 Устройство готово к работе
 * @retval 1 Устройство занято
 */
static uint8_t M24512_IsBusy(void)
{
    I2C_Start();
    I2C_WriteAddress(M24512_BASE_ADDR);
    I2C_Stop();
    return 0;
}

/**
 * @brief Ожидание готовности устройства
 * 
 * @return Результат ожидания
 * @retval 0 Устройство готово к работе
 * @retval 1 Таймаут ожидания готовности
 */
static uint8_t M24512_WaitReady(void)
{
    uint8_t timeout = 100; /* Максимальное время ожидания ~500 мс */
    
    while(M24512_IsBusy() && timeout) {
        delay(5);
        timeout--;
    }
    
    return (timeout == 0);
}

uint8_t M24512_Init(void)
{
    I2C_Start();
    I2C_WriteAddress(M24512_BASE_ADDR);
    I2C_Stop();
    return 0;
}

uint8_t M24512_WriteByte(uint16_t addr, uint8_t data)
{
    if(addr > M24512_MAX_ADDR) {
        return 1;
    }
    
    if(M24512_WaitReady()) {
        return 1;
    }
    
    I2C_Start();
    I2C_WriteAddress(M24512_BASE_ADDR);
    I2C_WriteData((uint8_t)(addr >> 8));
    I2C_WriteData((uint8_t)(addr & 0xFF));
    I2C_WriteData(data);
    I2C_Stop();
    
    delay(M24512_WRITE_TIMEOUT);
    
    return 0;
}

uint8_t M24512_ReadByte(uint16_t addr, uint8_t* data)
{
    if(addr > M24512_MAX_ADDR || data == 0) {
        return 1;
    }
    
    if(M24512_WaitReady()) {
        return 1;
    }
    
    I2C_Start();
    I2C_WriteAddress(M24512_BASE_ADDR);
    I2C_WriteData((uint8_t)(addr >> 8));
    I2C_WriteData((uint8_t)(addr & 0xFF));
    
    I2C_Start();
    I2C_WriteAddress(M24512_BASE_ADDR | 0x01);
    *data = I2C_ReadData_NACK();
    I2C_Stop();
    
    return 0;
}