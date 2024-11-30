/**
 * @file adxl345.c
 * @brief Реализация функций для работы с акселерометром ADXL345 по SPI
 */

#include "adxl345.h"
#include "spi.h"
#include "iostm8s103.h"

/* Макросы для управления линией CS (Chip Select) */
#define ADXL345_CS_LOW() (PA_ODR &= ~(1 << 3)) /**< Установить линию CS в низкий уровень */
#define ADXL345_CS_HIGH() (PA_ODR |= (1 << 3)) /**< Установить линию CS в высокий уровень */

uint8_t ADXL345_Init(void)
{
    /* Проверка идентификатора устройства */
    uint8_t deviceId = ADXL345_ReadReg(ADXL345_REG_DEVID);
    if (deviceId != ADXL345_DEVICE_ID)
    {
        return 1; /**< Ошибка инициализации: неправильный идентификатор устройства */
    }

    /* Установка диапазона измерений и формата данных */
    /* Устанавливаем полный дуплекс*/
    /* Устанавливаем полный диапазон ("Full Resolution") */
    /* Устанавливаем +/-4g */
    ADXL345_WriteReg(ADXL345_REG_DATA_FORMAT, 0x49);

    /* Установка частоты данных */
    /* Устанавливаем частоту данных 100 Гц */
    ADXL345_WriteReg(ADXL345_REG_BW_RATE, 0x0A);

    /* Включение измерений */
    /* Устанавливаем бит Measure в регистре POWER_CTL */
    ADXL345_WriteReg(ADXL345_REG_POWER_CTL, 0x08);

    return 0; // Успешная инициализация
}

void ADXL345_ReadAccel(int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t buffer[6];

    /* Считываем 6 последовательных регистров данных, начиная с DATAX0 */
    ADXL345_ReadMultBytes(ADXL345_REG_DATAX0, buffer, 6);

    /* Преобразуем полученные данные в 16-битные значения */
    *x = (int16_t)((buffer[1] << 8) | buffer[0]);
    *y = (int16_t)((buffer[3] << 8) | buffer[2]);
    *z = (int16_t)((buffer[5] << 8) | buffer[4]);
}

void ADXL345_WriteReg(uint8_t regAddr, uint8_t data)
{
    ADXL345_CS_LOW(); /* Активируем устройство путем опускания CS */

    /* Отправляем адрес регистра с установленным битом записи (бит RW = 0) */
    SPI_ReadWriteByte(regAddr & 0x3F); /* Обеспечиваем, что биты RW и MB установлены в 0 */

    /* Отправляем данные */
    SPI_ReadWriteByte(data);

    ADXL345_CS_HIGH(); /* Деактивируем устройство путем поднятия CS */
}

uint8_t ADXL345_ReadReg(uint8_t regAddr)
{
    uint8_t data;

    ADXL345_CS_LOW(); /* Активируем устройство */

    /* Отправляем адрес регистра с установленным битом чтения (бит RW = 1) */
    SPI_ReadWriteByte(0x80 | (regAddr & 0x3F)); /* Устанавливаем бит RW в 1 для чтения */

    /* Читаем данные */
    data = SPI_ReadWriteByte(0x00); // Отправляем dummy byte для чтения данных

    ADXL345_CS_HIGH(); /* Деактивируем устройство */

    return data;
}

void ADXL345_ReadMultBytes(uint8_t startRegAddr, uint8_t *buffer, uint8_t length)
{
    uint8_t i;

    ADXL345_CS_LOW(); /* Активируем устройство */

    /* Отправляем адрес регистра с установленными битами чтения и многобайтной передачи (RW = 1, MB = 1) */
    SPI_ReadWriteByte(0xC0 | (startRegAddr & 0x3F));

    /* Читаем данные */
    for (i = 0; i < length; i++)
    {
        buffer[i] = SPI_ReadWriteByte(0x00);
    }

    ADXL345_CS_HIGH(); /* Деактивируем устройство */
}