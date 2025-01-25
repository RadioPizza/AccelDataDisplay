/**
 * @file eeprom.c
 * @brief Реализация функций работы с EEPROM M24512 по I2C.
 */

#include "eeprom.h"
#include "i2c.h"
#include "my_iostm8s103.h"
#include "ssd1306.h"
#include "my_str.h"
#include "delay.h"

uint8_t EEPROM_Write(uint16_t mem_address, const uint8_t *data, uint16_t size) {
    uint16_t i;
    uint8_t mem_high = (uint8_t)((mem_address >> 8) & 0xFF);
    uint8_t mem_low = (uint8_t)(mem_address & 0xFF);

    for (i = 0; i < size; ++i) {
        /* Генерируем START */
        I2C_Start();
        while (!(I2C_SR1 & I2C_SR1_SB)); /* Ждем, пока START сгенерируется */

        /* Отправляем адрес устройства */
        I2C_WriteAddress(EEPROM_I2C_ADDRESS & 0xFE); /* бит на запись */

        /* Отправляем старший и младший байты адреса памяти */
        I2C_WriteData(mem_high);
        while (!(I2C_SR1 & I2C_SR1_TXE));

        I2C_WriteData(mem_low);
        while (!(I2C_SR1 & I2C_SR1_TXE));

        /* Отправляем данные */
        I2C_WriteData(data[i]);
        while (!(I2C_SR1 & I2C_SR1_TXE));

        /* Генерируем STOP */
        I2C_Stop();
        while (I2C_CR2 & I2C_CR2_STOP);

        /* Дадим EEPROM время на запись */
        delay(20);
    }

    return 0;
}

uint8_t EEPROM_Read(uint16_t mem_address, uint8_t *data, uint16_t size) {
    uint8_t mem_high = (uint8_t)((mem_address >> 8) & 0xFF);
    uint8_t mem_low = (uint8_t)(mem_address & 0xFF);
		uint16_t i;

    /* Генерируем START */
    I2C_Start();
    while (!(I2C_SR1 & I2C_SR1_SB)); /* Ждем, пока START сгенерируется */

    /* Отправляем адрес устройства */
    I2C_WriteAddress(EEPROM_I2C_ADDRESS & 0xFE); /* бит на запись */

    /* Отправляем старший и младший байты адреса памяти */
    I2C_WriteData(mem_high);
    while (!(I2C_SR1 & I2C_SR1_TXE));

    I2C_WriteData(mem_low);
    while (!(I2C_SR1 & I2C_SR1_TXE));

    /* Генерируем повторный START */
    I2C_Start();
    while (!(I2C_SR1 & I2C_SR1_SB));

    /* Отправляем адрес устройства с битом на чтение */
    I2C_WriteAddress(EEPROM_I2C_ADDRESS | 0x01);

    /* Читаем данные */
    for (i = 0; i < size; ++i) {
        if (i == size - 1) {
            /* Последний байт - NACK */
            data[i] = I2C_ReadData_NACK();
        } else {
            /* Все остальные байты - ACK */
            data[i] = I2C_ReadData_ACK();
        }
    }

    /* Генерируем STOP */
    I2C_Stop();
    while (I2C_CR2 & I2C_CR2_STOP);

    return 0;
}
