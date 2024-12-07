/**
 * @file m24512.h
 * @brief Библиотека-драйвер для работы с EEPROM M24512
 * 
 * Этот файл содержит прототипы функций и необходимые определения 
 * для работы с микросхемой памяти M24512 по интерфейсу I2C.
 */

#ifndef M24512_H
#define M24512_H

#include <stdint.h>
#include "i2c.h" // Добавляем включение i2c.h

/** @brief Базовый адрес устройства M24512 на шине I2C */
#define M24512_BASE_ADDR    0xA0

/** @brief Максимальный адрес памяти */
#define M24512_MAX_ADDR     0xFFFF

/**
 * @brief Инициализация M24512
 * 
 * @return uint8_t Результат инициализации:
 *         - 0: успешно
 *         - 1: ошибка
 */
uint8_t M24512_Init(void);

/**
 * @brief Запись байта данных по указанному адресу
 * 
 * @param[in] addr Адрес для записи (0x0000 - 0xFFFF)
 * @param[in] data Байт данных для записи
 * @return uint8_t Результат операции:
 *         - 0: успешно
 *         - 1: ошибка
 */
uint8_t M24512_WriteByte(uint16_t addr, uint8_t data);

/**
 * @brief Чтение байта данных с указанного адреса
 * 
 * @param[in] addr Адрес для чтения (0x0000 - 0xFFFF)
 * @param[out] data Указатель на переменную для сохранения прочитанного байта
 * @return uint8_t Результат операции:
 *         - 0: успешно
 *         - 1: ошибка
 */
uint8_t M24512_ReadByte(uint16_t addr, uint8_t* data);

// Прототипы функций I2C, используемых в драйвере.
// Эти функции должны быть определены в i2c.c и i2c.h

/**
 * @brief Инициирует I2C Start condition.
 */
void I2C_Start(void);

/**
 * @brief Инициирует I2C Stop condition.
 */
void I2C_Stop(void);

/**
 * @brief Отправляет I2C адрес устройства и ожидает подтверждения (ACK).
 * 
 * @param[in] address Адрес устройства на шине I2C.
 * @return uint8_t Результат операции:
 *         - 0: успешно (получен ACK)
 *         - 1: ошибка (получен NACK или тайм-аут)
 */
uint8_t I2C_WriteAddress(uint8_t address);

/**
 * @brief Отправляет байт данных и ожидает подтверждения (ACK).
 * 
 * @param[in] data Байт данных для отправки.
 * @return uint8_t Результат операции:
 *         - 0: успешно (получен ACK)
 *         - 1: ошибка (получен NACK или тайм-аут)
 */
uint8_t I2C_WriteData(uint8_t data);

/**
 * @brief Читает байт данных и отправляет NACK (Not Acknowledge).
 * 
 * @return uint8_t Прочитанный байт данных.
 */
uint8_t I2C_ReadData_NACK(void);

/**
 * @brief Задержка на указанное количество миллисекунд.
 * 
 * @param[in] ms Время задержки в миллисекундах.
 */
void delay(uint32_t ms);

#endif /* M24512_H */