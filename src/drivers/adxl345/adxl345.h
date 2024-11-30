/**
 * @file adxl345.h
 * @brief Библиотека-драйвер для акселерометра ADXL345, использующего SPI-интерфейс
 *
 * Эта библиотека предоставляет функции для взаимодействия с акселерометром ADXL345 по SPI.
 */

#ifndef ADXL345_H
#define ADXL345_H

#include <stdint.h> /* Для типов uint8_t и т.д. */

/**
 * @defgroup ADXL345_REGISTERS Адреса регистров ADXL345
 * @brief Определения адресов регистров акселерометра ADXL345
 * @{
 */

/* Определение адресов регистров */
#define ADXL345_REG_DEVID          0x00 /**< @brief Регистр идентификатора устройства */
#define ADXL345_REG_THRESH_TAP     0x1D /**< @brief Порог ударов */
#define ADXL345_REG_OFSX           0x1E /**< @brief Смещение по оси X */
#define ADXL345_REG_OFSY           0x1F /**< @brief Смещение по оси Y */
#define ADXL345_REG_OFSZ           0x20 /**< @brief Смещение по оси Z */
#define ADXL345_REG_DUR            0x21 /**< @brief Длительность удара */
#define ADXL345_REG_LATENT         0x22 /**< @brief Задержка между ударами */
#define ADXL345_REG_WINDOW         0x23 /**< @brief Окно между ударами */
#define ADXL345_REG_THRESH_ACT     0x24 /**< @brief Порог активности */
#define ADXL345_REG_THRESH_INACT   0x25 /**< @brief Порог неактивности */
#define ADXL345_REG_TIME_INACT     0x26 /**< @brief Время неактивности */
#define ADXL345_REG_ACT_INACT_CTL  0x27 /**< @brief Управление осями для детекции активности/неактивности */
#define ADXL345_REG_THRESH_FF      0x28 /**< @brief Порог свободного падения */
#define ADXL345_REG_TIME_FF        0x29 /**< @brief Время свободного падения */
#define ADXL345_REG_TAP_AXES       0x2A /**< @brief Управление осями для одиночного/двойного удара */
#define ADXL345_REG_ACT_TAP_STATUS 0x2B /**< @brief Источник одиночного/двойного удара */
#define ADXL345_REG_BW_RATE        0x2C /**< @brief Частота данных и режим энергосбережения */
#define ADXL345_REG_POWER_CTL      0x2D /**< @brief Управление энергопотреблением */
#define ADXL345_REG_INT_ENABLE     0x2E /**< @brief Управление разрешением прерываний */
#define ADXL345_REG_INT_MAP        0x2F /**< @brief Управление назначением прерываний */
#define ADXL345_REG_INT_SOURCE     0x30 /**< @brief Источник прерываний */
#define ADXL345_REG_DATA_FORMAT    0x31 /**< @brief Управление форматом данных */
#define ADXL345_REG_DATAX0         0x32 /**< @brief Данные оси X младший байт */
#define ADXL345_REG_DATAX1         0x33 /**< @brief Данные оси X старший байт */
#define ADXL345_REG_DATAY0         0x34 /**< @brief Данные оси Y младший байт */
#define ADXL345_REG_DATAY1         0x35 /**< @brief Данные оси Y старший байт */
#define ADXL345_REG_DATAZ0         0x36 /**< @brief Данные оси Z младший байт */
#define ADXL345_REG_DATAZ1         0x37 /**< @brief Данные оси Z старший байт */
#define ADXL345_REG_FIFO_CTL       0x38 /**< @brief Управление FIFO */
#define ADXL345_REG_FIFO_STATUS    0x39 /**< @brief Состояние FIFO */

/** @} */ // end of ADXL345_REGISTERS

/**
 * @defgroup ADXL345_CONSTANTS Константы ADXL345
 * @brief Определения констант для акселерометра ADXL345
 * @{
 */

/* Определение констант */
#define ADXL345_DEVICE_ID          0xE5 /**< @brief Ожидаемый идентификатор устройства */

/** @} */ // end of ADXL345_CONSTANTS

/* Прототипы функций */

/**
 * @brief Инициализация акселерометра ADXL345
 *
 * Эта функция выполняет инициализацию акселерометра ADXL345 с заданными настройками.
 * Конфигурация:
 * - Полный диапазон измерений (Full Resolution)
 * - Диапазон измерений: ±4g
 * - Частота измерений: 100 Гц
 * - Включение режима измерений
 *
 * Последовательность инициализации:
 * - Проверка идентификатора устройства
 * - Настройка формата данных (DATA_FORMAT)
 * - Установка частоты измерений (BW_RATE)
 * - Включение режима измерений (POWER_CTL)
 *
 * @return uint8_t Статус инициализации
 * @retval 1  Успешная инициализация ADXL345
 * @retval 0  Ошибка инициализации (неверный идентификатор устройства)
 * 
 * @sa ADXL345_ReadReg
 * @sa ADXL345_WriteReg
 * @sa ADXL345_ReadAccel
 * 
 * @code
 *  // Пример использования:
 *  uint8_t result = ADXL345_Init();
 *  if (result == 1) {
 *    // ADXL345 успешно инициализирован
 *    // Можно начинать измерения
 *  } else {
 *    // Ошибка инициализации ADXL345
 *    // Обработка ошибки
 *  }
 * @endcode
 * 
 * @note Перед вызовом функции должен быть инициализирован интерфейс SPI
 * @warning Функция не проверяет корректность инициализации SPI
 */
uint8_t ADXL345_Init(void);

/**
 * @brief Чтение данных ускорения с акселерометра ADXL345
 *
 * Функция считывает сырые данные ускорения по осям X, Y и Z из ADXL345.
 *
 * @param[out] x Указатель для хранения данных ускорения по оси X
 * @param[out] y Указатель для хранения данных ускорения по оси Y
 * @param[out] z Указатель для хранения данных ускорения по оси Z
 */
void ADXL345_ReadAccel(int16_t *x, int16_t *y, int16_t *z);

/**
 * @brief Запись одного байта данных в регистр ADXL345
 *
 * @param regAddr Адрес регистра для записи
 * @param data Данные для записи
 */
void ADXL345_WriteReg(uint8_t regAddr, uint8_t data);

/**
 * @brief Чтение значения из регистра ADXL345
 *
 * Функция считывает один байт из указанного регистра ADXL345 по SPI.
 *
 * @param[in] regAddr Адрес регистра для чтения
 * @return Значение, прочитанное из регистра
 */
uint8_t ADXL345_ReadReg(uint8_t regAddr);

/**
 * @brief Чтение нескольких байт данных из последовательных регистров ADXL345
 *
 * @param startRegAddr Адрес первого регистра для чтения
 * @param buffer Указатель на буфер для хранения прочитанных данных
 * @param length Количество байт для чтения
 */
void ADXL345_ReadMultBytes(uint8_t startRegAddr, uint8_t *buffer, uint8_t length);

#endif /* ADXL345_H */