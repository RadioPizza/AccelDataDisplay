/**
 * @file m24512.c
 * @brief Реализация функций для работы с EEPROM M24512
 */

#include "m24512.h"
#include "i2c.h"

/** @brief Время ожидания записи в мс */
#define M24512_WRITE_TIMEOUT 5

/**
 * @brief Инициализация M24512
 * 
 * @return uint8_t Результат инициализации:
 *         - 0: успешно
 *         - 1: ошибка
 */
uint8_t M24512_Init(void)
{
    /* Проверка связи с микросхемой */
    I2C_Start();
    I2C_WriteAddress(M24512_BASE_ADDR);
    I2C_Stop();
    
    return 0;
}

/**
 * @brief Запись байта данных по указанному адресу
 * 
 * @param[in] addr Адрес для записи (0x0000 - 0xFFFF)
 * @param[in] data Байт данных для записи
 * @return uint8_t Результат операции:
 *         - 0: успешно
 *         - 1: ошибка
 */
uint8_t M24512_WriteByte(uint16_t addr, uint8_t data)
{
    if(addr > M24512_MAX_ADDR)
        return 1;
        
    /* Начало передачи */
    I2C_Start();
    
    /* Отправка адреса устройства */
    I2C_WriteAddress(M24512_BASE_ADDR);
    
    /* Отправка старшего байта адреса памяти */
    I2C_WriteData((uint8_t)(addr >> 8));
    
    /* Отправка младшего байта адреса памяти */
    I2C_WriteData((uint8_t)(addr & 0xFF));
    
    /* Отправка данных */
    I2C_WriteData(data);
    
    /* Завершение передачи */
    I2C_Stop();
    
    /* Ожидание завершения записи */
    delay(M24512_WRITE_TIMEOUT);
    
    return 0;
}

/**
 * @brief Чтение байта данных с указанного адреса
 * 
 * @param[in] addr Адрес для чтения (0x0000 - 0xFFFF)
 * @param[out] data Указатель на переменную для сохранения прочитанного байта
 * @return uint8_t Результат операции:
 *         - 0: успешно
 *         - 1: ошибка
 */
uint8_t M24512_ReadByte(uint16_t addr, uint8_t* data)
{
    if(addr > M24512_MAX_ADDR || data == 0)
        return 1;
        
    /* Установка адреса чтения */
    I2C_Start();
    I2C_WriteAddress(M24512_BASE_ADDR);
    I2C_WriteData((uint8_t)(addr >> 8));
    I2C_WriteData((uint8_t)(addr & 0xFF));
    
    /* Повторный старт для чтения */
    I2C_Start();
    I2C_WriteAddress(M24512_BASE_ADDR | 0x01);
    
    /* Чтение данных */
    *data = I2C_ReadData_NACK();
    
    /* Завершение передачи */
    I2C_Stop();
    
    return 0;
}