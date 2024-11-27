/**
 * @file spi.h
 * @brief Библиотека-драйвер для работы с аппаратным интерфейсом SPI
 *
 * Этот файл содержит прототипы функций и необходимые определения для работы с SPI.
 */

#ifndef SPI_H
#define SPI_H

#include <stdint.h> /* Для типов uint8_t и т.д. */

/**
 * @defgroup SPI_CR1 Биты регистра управления SPI_CR1
 * @brief Определения битов регистра SPI_CR1
 * @{
 */
#define SPI_CR1_CPHA    (1 << 0)  /**< @brief Фаза тактового сигнала */
#define SPI_CR1_CPOL    (1 << 1)  /**< @brief Полярность тактового сигнала */
#define SPI_CR1_MSTR    (1 << 2)  /**< @brief Выбор режима мастера */
#define SPI_CR1_BR      (7 << 3)  /**< @brief Управление скоростью передачи (делитель) */
#define SPI_CR1_SPE     (1 << 6)  /**< @brief Включение SPI */
/** @} */ // end of SPI_CR1

/**
 * @defgroup SPI_CR2 Биты регистра управления SPI_CR2
 * @brief Определения битов регистра SPI_CR2
 * @{
 */
#define SPI_CR2_SSI     (1 << 0)  /**< @brief Внутренний выбор подчинённого (Slave Select) */
#define SPI_CR2_SSM     (1 << 1)  /**< @brief Программное управление подчинённым устройством (Slave Management) */
/** @} */ // end of SPI_CR2

/**
 * @defgroup SPI_SR Биты регистра состояния SPI_SR
 * @brief Определения битов регистра состояния SPI_SR
 * @{
 */
#define SPI_SR_RXNE     (1 << 0)  /**< @brief Флаг: Принятые данные доступны в буфере */
#define SPI_SR_TXE      (1 << 1)  /**< @brief Флаг: Буфер передачи пуст */
/** @} */ // end of SPI_SR

/**
 * @defgroup SPI_BAUDRATE Скорости передачи SPI (делители)
 * @brief Определения для управления скоростью передачи данных через SPI
 * @{
 */
#define SPI_BAUDRATE_DIV2     (0 << 3)  /**< @brief Делитель скорости передачи: 2 */
#define SPI_BAUDRATE_DIV4     (1 << 3)  /**< @brief Делитель скорости передачи: 4 */
#define SPI_BAUDRATE_DIV8     (2 << 3)  /**< @brief Делитель скорости передачи: 8 */
#define SPI_BAUDRATE_DIV16    (3 << 3)  /**< @brief Делитель скорости передачи: 16 */
#define SPI_BAUDRATE_DIV32    (4 << 3)  /**< @brief Делитель скорости передачи: 32 */
#define SPI_BAUDRATE_DIV64    (5 << 3)  /**< @brief Делитель скорости передачи: 64 */
#define SPI_BAUDRATE_DIV128   (6 << 3)  /**< @brief Делитель скорости передачи: 128 */
#define SPI_BAUDRATE_DIV256   (7 << 3)  /**< @brief Делитель скорости передачи: 256 */
/** @} */ // end of SPI_BAUDRATE

/**
 * @brief Инициализация периферийного модуля SPI
 *
 * Конфигурирует периферийный модуль SPI микроконтроллера STM8S103F3 в режиме мастера
 * с заданными настройками (полярность, фаза тактового сигнала, скорость передачи и т.д.).
 */
void SPI_Init(void);

/**
 * @brief Передача и приём одного байта через SPI
 *
 * Передаёт один байт по шине SPI и одновременно принимает байт с шины SPI.
 *
 * @param data Байт, который нужно передать
 * @return Принятый байт с шины SPI
 */
uint8_t SPI_ReadWriteByte(uint8_t data);

/**
 * @brief Включение периферийного модуля SPI
 *
 * Устанавливает бит SPE в регистре управления SPI для включения периферийного модуля SPI.
 */
void SPI_Enable(void);

/**
 * @brief Выключение периферийного модуля SPI
 *
 * Сбрасывает бит SPE в регистре управления SPI для выключения периферийного модуля SPI.
 */
void SPI_Disable(void);

#endif /* SPI_H */
