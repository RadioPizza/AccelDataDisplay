/**
 * @file adxl345.h
 * @brief Библиотека-драйвер для акселерометра ADXL345, использующего SPI-интерфейс.
 *
 * Эта библиотека предоставляет функции для взаимодействия с акселерометром ADXL345 по SPI.
 */

#ifndef ADXL345_H
#define ADXL345_H

#include <stdint.h>  /* Для типов uint8_t и т.д. */

/* Определение адресов регистров */
#define ADXL345_REG_DEVID          0x00 /**< Регистр идентификатора устройства */
#define ADXL345_REG_THRESH_TAP     0x1D /**< Порог ударов */
#define ADXL345_REG_OFSX           0x1E /**< Смещение по оси X */
#define ADXL345_REG_OFSY           0x1F /**< Смещение по оси Y */
#define ADXL345_REG_OFSZ           0x20 /**< Смещение по оси Z */
#define ADXL345_REG_DUR            0x21 /**< Длительность удара */
#define ADXL345_REG_LATENT         0x22 /**< Задержка между ударами */
#define ADXL345_REG_WINDOW         0x23 /**< Окно между ударами */
#define ADXL345_REG_THRESH_ACT     0x24 /**< Порог активности */
#define ADXL345_REG_THRESH_INACT   0x25 /**< Порог неактивности */
#define ADXL345_REG_TIME_INACT     0x26 /**< Время неактивности */
#define ADXL345_REG_ACT_INACT_CTL  0x27 /**< Управление осями для детекции активности/неактивности */
#define ADXL345_REG_THRESH_FF      0x28 /**< Порог свободного падения */
#define ADXL345_REG_TIME_FF        0x29 /**< Время свободного падения */
#define ADXL345_REG_TAP_AXES       0x2A /**< Управление осями для одиночного/двойного удара */
#define ADXL345_REG_ACT_TAP_STATUS 0x2B /**< Источник одиночного/двойного удара */
#define ADXL345_REG_BW_RATE        0x2C /**< Частота данных и режим энергосбережения */
#define ADXL345_REG_POWER_CTL      0x2D /**< Управление энергопотреблением */
#define ADXL345_REG_INT_ENABLE     0x2E /**< Управление разрешением прерываний */
#define ADXL345_REG_INT_MAP        0x2F /**< Управление назначением прерываний */
#define ADXL345_REG_INT_SOURCE     0x30 /**< Источник прерываний */
#define ADXL345_REG_DATA_FORMAT    0x31 /**< Управление форматом данных */
#define ADXL345_REG_DATAX0         0x32 /**< Данные оси X младший байт */
#define ADXL345_REG_DATAX1         0x33 /**< Данные оси X старший байт */
#define ADXL345_REG_DATAY0         0x34 /**< Данные оси Y младший байт */
#define ADXL345_REG_DATAY1         0x35 /**< Данные оси Y старший байт */
#define ADXL345_REG_DATAZ0         0x36 /**< Данные оси Z младший байт */
#define ADXL345_REG_DATAZ1         0x37 /**< Данные оси Z старший байт */
#define ADXL345_REG_FIFO_CTL       0x38 /**< Управление FIFO */
#define ADXL345_REG_FIFO_STATUS    0x39 /**< Состояние FIFO */

/* Определение констант */
#define ADXL345_DEVICE_ID          0xE5 /**< Ожидаемый идентификатор устройства */

/* Прототипы функций */

/**
 * @brief Инициализация акселерометра ADXL345.
 *
 * Функция инициализирует ADXL345 путем настройки необходимых регистров.
 * Она устанавливает частоту данных, диапазон и настройки энергопотребления.
 */
void ADXL345_Init(void);

/**
 * @brief Чтение данных ускорения с акселерометра ADXL345.
 *
 * Функция считывает сырые данные ускорения по осям X, Y и Z из ADXL345.
 *
 * @param[out] x Указатель для хранения данных ускорения по оси X.
 * @param[out] y Указатель для хранения данных ускорения по оси Y.
 * @param[out] z Указатель для хранения данных ускорения по оси Z.
 */
void ADXL345_ReadAccel(int16_t* x, int16_t* y, int16_t* z);

/**
 * @brief Запись одного байта данных в регистр ADXL345.
 *
 * @param regAddr Адрес регистра для записи.
 * @param data Данные для записи.
 */
void ADXL345_WriteReg(uint8_t regAddr, uint8_t data);

/**
 * @brief Чтение значения из регистра ADXL345.
 *
 * Функция считывает один байт из указанного регистра ADXL345 по SPI.
 *
 * @param[in] regAddr Адрес регистра для чтения.
 * @return Значение, прочитанное из регистра.
 */
uint8_t ADXL345_ReadReg(uint8_t regAddr);

/**
 * @brief Чтение нескольких байт данных из последовательных регистров ADXL345.
 *
 * @param startRegAddr Адрес первого регистра для чтения.
 * @param buffer Указатель на буфер для хранения прочитанных данных.
 * @param length Количество байт для чтения.
 */
void ADXL345_ReadMultBytes(uint8_t startRegAddr, uint8_t* buffer, uint8_t length);

#endif /* ADXL345_H */