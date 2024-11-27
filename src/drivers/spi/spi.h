/**
 * @file spi.h
 * @brief Заголовочный файл драйвера SPI для STM8S103F3.
 *
 * Этот файл содержит прототипы функций и необходимые определения для работы с SPI.
 */

#ifndef SPI_H
#define SPI_H

#include <stdint.h>

/* Определение битов регистров SPI */
#define SPI_CR1_CPHA    (1 << 0)  /**< Фаза тактового сигнала */
#define SPI_CR1_CPOL    (1 << 1)  /**< Полярность тактового сигнала */
#define SPI_CR1_MSTR    (1 << 2)  /**< Выбор режима мастера */
#define SPI_CR1_BR      (7 << 3)  /**< Управление скоростью передачи (делитель) */
#define SPI_CR1_SPE     (1 << 6)  /**< Включение SPI */

#define SPI_CR2_SSI     (1 << 0)  /**< Внутренний выбор подчинённого (Slave Select) */
#define SPI_CR2_SSM     (1 << 1)  /**< Программное управление подчинённым устройством (Slave Management) */

#define SPI_SR_RXNE     (1 << 0)  /**< Флаг: Принятые данные доступны в буфере */
#define SPI_SR_TXE      (1 << 1)  /**< Флаг: Буфер передачи пуст */

/* Значения для управления скоростью передачи (делители) */
#define SPI_BAUDRATE_DIV2     (0 << 3)
#define SPI_BAUDRATE_DIV4     (1 << 3)
#define SPI_BAUDRATE_DIV8     (2 << 3)
#define SPI_BAUDRATE_DIV16    (3 << 3)
#define SPI_BAUDRATE_DIV32    (4 << 3)
#define SPI_BAUDRATE_DIV64    (5 << 3)
#define SPI_BAUDRATE_DIV128   (6 << 3)
#define SPI_BAUDRATE_DIV256   (7 << 3)

/**
 * @brief Инициализация периферийного модуля SPI.
 *
 * Конфигурирует периферийный модуль SPI микроконтроллера STM8S103F3 в режиме мастера
 * с заданными настройками (полярность, фаза тактового сигнала, скорость передачи и т.д.).
 */
void SPI_Init(void);

/**
 * @brief Передача и приём одного байта через SPI.
 *
 * Передаёт один байт по шине SPI и одновременно принимает байт с шины SPI.
 *
 * @param data Байт, который нужно передать.
 * @return Принятый байт с шины SPI.
 */
uint8_t SPI_ReadWriteByte(uint8_t data);

/**
 * @brief Включение периферийного модуля SPI.
 *
 * Устанавливает бит SPE в регистре управления SPI для включения периферийного модуля SPI.
 */
void SPI_Enable(void);

/**
 * @brief Выключение периферийного модуля SPI.
 *
 * Сбрасывает бит SPE в регистре управления SPI для выключения периферийного модуля SPI.
 */
void SPI_Disable(void);

#endif /* SPI_H */
