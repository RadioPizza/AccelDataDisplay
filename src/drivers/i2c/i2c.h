/**
 * @file i2c.h
 * @brief Библиотека-драйвер для работы с аппартаным интерфейсом I2C
 * 
 * Этот файл содержит прототипы функций и необходимые определения для работы с SPI.
 */

#ifndef I2C_H
#define I2C_H

#include <stdint.h> /* Для типов uint8_t и т.д. */

/** @defgroup I2C_CR1_Bit_Masks Битовые маски регистра I2C Control Register 1 (CR1)
 * @{
 */

/** @brief Включение периферии I2C. */
#define I2C_CR1_PE ((uint8_t)0x01)

/** @} */

/** @defgroup I2C_CR2_Bit_Masks Битовые маски регистра I2C Control Register 2 (CR2)
 * @{
 */

/** @brief Генерация условия START */
#define I2C_CR2_START ((uint8_t)0x01)

/** @brief Генерация условия STOP */
#define I2C_CR2_STOP ((uint8_t)0x02)

/** @brief Включение подтверждения (ACK) */
#define I2C_CR2_ACK ((uint8_t)0x04)

/** @} */

/** @defgroup I2C_SR1_Bit_Masks Битовые маски регистра I2C Status Register 1 (SR1)
 * @{
 */

/** @brief Бит Start */
#define I2C_SR1_SB ((uint8_t)0x01)

/** @brief Адрес отправлен/совпадение адреса */
#define I2C_SR1_ADDR ((uint8_t)0x02)

/** @brief Регистр приёма не пуст (RXNE) */
#define I2C_SR1_RXNE ((uint8_t)0x40)

/** @brief Регистр передачи пуст (TXE) */
#define I2C_SR1_TXE ((uint8_t)0x80)

/** @} */

/** @defgroup I2C_OARH_Bit_Masks Битовые маски регистра I2C Own Address Register High (OARH)
 * @{
 */

/** @brief Режим адресации (10-бит/7-бит) */
#define I2C_OARH_ADDMODE ((uint8_t)0x80)

/** @} */

/** @defgroup I2C_CCRH_Bit_Masks Битовые маски регистра I2C Clock Control Register High (CCRH)
 * @{
 */

/** @brief Выбор режима Fast Mode */
#define I2C_CCRH_FS ((uint8_t)0x80)

/** @} */

/**
 * @enum I2C_Mode_t
 * @brief Режимы работы I2C
 *
 * Этот перечисляемый тип определяет рабочие режимы для инициализации шины I2C:
 * - Стандартный режим (100 кГц)
 * - Быстрый режим (400 кГц)
 */
typedef enum
{
    I2C_STANDARD_MODE, /**< Стандартный режим (100 кГц) */
    I2C_FAST_MODE      /**< Быстрый режим (400 кГц) */
} I2C_Mode_t;

/**
 * @brief Универсальная инициализация I2C
 *
 * Инициализирует периферию I2C в выбранном режиме:
 * стандартном (100 кГц) или быстром (400 кГц).
 *
 * @param mode Режим работы I2C (I2C_STANDARD_MODE или I2C_FAST_MODE)
 */
void I2C_Init(I2C_Mode_t mode);

/**
 * @brief Генерирует условие START на шине I2C
 */
void I2C_Start(void);

/**
 * @brief Генерирует условие STOP на шине I2C
 */
void I2C_Stop(void);

/**
 * @brief Отправляет адрес ведомого устройства на шину I2C
 * @param address Адрес ведомого устройства
 */
void I2C_WriteAddress(uint8_t address);

/**
 * @brief Отправляет байт данных на шину I2C
 * @param data Байтовые данные для отправки
 */
void I2C_WriteData(uint8_t data);

/**
 * @brief Читает байт данных с шины I2C с подтверждением (ACK)
 * @return Принятый байт данных
 */
uint8_t I2C_ReadData_ACK(void);

/**
 * @brief Читает байт данных с шины I2C без подтверждения (NACK)
 * @return Принятый байт данных
 */
uint8_t I2C_ReadData_NACK(void);

#endif /* I2C_H */
