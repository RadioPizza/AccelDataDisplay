/**
 * @file ssd1306.c
 * @brief Работа с OLED дисплеем 128x64 (SSD1306) по протоколу I2C.
 */

#include "ssd1306.h"
#include "i2c.h"
#include "font5x7.h"

void SSD1306_WriteCommand(uint8_t command)
{
    I2C_Start();
    I2C_WriteAddress(SSD1306_I2C_ADDRESS); // Адрес I2C + бит записи
    I2C_WriteData(SSD1306_COMMAND);        // Контрольный байт: Co = 0, D/C# = 0
    I2C_WriteData(command);                // Байт команды
    I2C_Stop();
}

void SSD1306_WriteData(uint8_t data)
{
    I2C_Start();
    I2C_WriteAddress(SSD1306_I2C_ADDRESS); // Адрес I2C + бит записи
    I2C_WriteData(SSD1306_DATA);           // Контрольный байт: Co = 0, D/C# = 1
    I2C_WriteData(data);                   // Байт данных
    I2C_Stop();
}

void SSD1306_Init(void)
{
    I2C_Init(I2C_FAST_MODE);

    // Последовательность инициализации для SSD1306
    SSD1306_WriteCommand(0xAE); // Выключить дисплей

    SSD1306_WriteCommand(0xD5); // Установка тактовой частоты
    SSD1306_WriteCommand(0x80); // Частота по умолчанию

    SSD1306_WriteCommand(0xA8); // Установка мультиплексного коэффициента
    SSD1306_WriteCommand(0x3F); // 1/64 duty

    SSD1306_WriteCommand(0xD3); // Установка смещения дисплея
    SSD1306_WriteCommand(0x00); // Нет смещения

    SSD1306_WriteCommand(0x40); // Установка стартовой линии

    SSD1306_WriteCommand(0x8D); // Настройка зарядового насоса
    SSD1306_WriteCommand(0x14); // Включить зарядовой насос

    SSD1306_WriteCommand(0x20); // Режим адресации памяти
    SSD1306_WriteCommand(0x00); // Горизонтальный режим адресации

    SSD1306_WriteCommand(0xA1); // Разворот сегментов
    SSD1306_WriteCommand(0xC8); // Направление сканирования COM

    SSD1306_WriteCommand(0xDA); // Конфигурация COM пинов
    SSD1306_WriteCommand(0x12);

    SSD1306_WriteCommand(0x81); // Контрастность
    SSD1306_WriteCommand(0xCF);

    SSD1306_WriteCommand(0xD9); // Установка периода предварительной зарядки
    SSD1306_WriteCommand(0xF1);

    SSD1306_WriteCommand(0xDB); // Установка уровня VCOMH
    SSD1306_WriteCommand(0x40);

    SSD1306_WriteCommand(0xA4); // Восстановить отображение из RAM
    SSD1306_WriteCommand(0xA6); // Нормальный режим отображения

    SSD1306_WriteCommand(0x2E); // Отключить прокрутку

    SSD1306_WriteCommand(0xAF); // Включить дисплей

    SSD1306_Clear(); // Очистить дисплей
}

void SSD1306_Clear(void)
{
    uint8_t page, column;

    for (page = 0; page < 8; page++)
    {
        SSD1306_WriteCommand(0xB0 | page); // Установка адреса страницы
        SSD1306_WriteCommand(0x00);        // Установка младшего адреса столбца
        SSD1306_WriteCommand(0x10);        // Установка старшего адреса столбца

        for (column = 0; column < 128; column++)
        {
            SSD1306_WriteData(0x00); // Очистить данные
        }
    }
}

void SSD1306_SetCursor(uint8_t column, uint8_t page)
{
    SSD1306_WriteCommand(0xB0 | (page & 0x07));          // Установка адреса страницы
    SSD1306_WriteCommand(0x00 | (column & 0x0F));        // Младший адрес столбца
    SSD1306_WriteCommand(0x10 | ((column >> 4) & 0x0F)); // Старший адрес столбца
}

void SSD1306_WriteChar(char c)
{
    unsigned char i;
    const unsigned char *bitmap;

    // Проверка на допустимый диапазон символов
    if (c < 32 || c > 126)
    {
        c = ' '; // Заменяем недопустимые символы пробелом
    }

    bitmap = font5x7[c - 32];

    for (i = 0; i < 5; i++)
    {
        SSD1306_WriteData(bitmap[i]);
    }

    SSD1306_WriteData(0x00); // Пробел между символами
}

void SSD1306_WriteString(const char *str)
{
    while (*str)
    {
        SSD1306_WriteChar(*str++);
    }
}

void SSD1306_DisplayOn(void)
{
    SSD1306_WriteCommand(0xAF);
}

void SSD1306_DisplayOff(void)
{
    SSD1306_WriteCommand(0xAE);
}

void SSD1306_DrawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t width, uint8_t height)
{
    uint8_t i, j;
    uint8_t byte_height = (height + 7) / 8; /**< Высота в байтах (количество страниц по вертикали). */

    for (j = 0; j < byte_height; j++)
    { /**< Проход по страницам. */
        for (i = 0; i < width; i++)
        { /**< Проход по пикселям по ширине. */
            /** Установка курсора в нужное место. */
            SSD1306_SetCursor(x + i, y / 8 + j); /**< y / 8 — определение страницы. */
            /** Отправка данных из битмапа на дисплей. */
            SSD1306_WriteData(bitmap[j * width + i]);
        }
    }
}
