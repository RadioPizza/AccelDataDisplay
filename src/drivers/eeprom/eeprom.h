/**
 * @file eeprom.h
 * @brief Библиотека для работы с EEPROM M24512 по I2C.
 */

#ifndef EEPROM_H
#define EEPROM_H

#include "stdint.h"

/** @brief Адрес EEPROM. */
#define EEPROM_I2C_ADDRESS 0xA0 /**< 7-битный базовый адрес устройства (E0=E1=E2=0). */

/**
 * @brief Запись данных в EEPROM.
 * 
 * @param[in] mem_address Адрес в EEPROM, куда будут записаны данные (0x0000 - 0xFFFF).
 * @param[in] data Указатель на массив данных для записи.
 * @param[in] size Количество байт для записи.
 * 
 * @return 0 при успешной записи, 1 при ошибке.
 */
uint8_t EEPROM_Write(uint16_t mem_address, const uint8_t *data, uint16_t size);

/**
 * @brief Чтение данных из EEPROM.
 * 
 * @param[in] mem_address Адрес в EEPROM, откуда будут прочитаны данные (0x0000 - 0xFFFF).
 * @param[out] data Указатель на массив для сохранения прочитанных данных.
 * @param[in] size Количество байт для чтения.
 * 
 * @return 0 при успешном чтении, 1 при ошибке.
 */
uint8_t EEPROM_Read(uint16_t mem_address, uint8_t *data, uint16_t size);

#endif /* EEPROM_H */
