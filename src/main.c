#include "i2c.h"
#include "ssd1306.h"
#include "spi.h"
#include "adxl345.h"
#include "delay.h"

/**
 * @brief Инициализация всех периферийных устройств с выводом отладочной информации на OLED-дисплей.
 * @return 0 при успешной инициализации, 1 при ошибке
 */
uint8_t init(void)
{		
		// Иницилизация I2С
		if (I2C_Init(I2C_FAST_MODE) == 1) // Ошибка инициализации I2C
				return 1;

    // Инициализация и очистка OLED-дисплея
    SSD1306_Init();
    SSD1306_Clear();

    // Проверка OLED
    SSD1306_SetCursor(0, 0);
    SSD1306_WriteString("> Init OLED... ");
    SSD1306_WriteString("OK");

    // Проверка SPI
    SSD1306_SetCursor(0, 1);
    SSD1306_WriteString("> Init SPI... ");
    if (SPI_Init() == 0) // Успешная инициализация SPI
    {
        SSD1306_WriteString("OK");
    }
    else
    {
        SSD1306_WriteString("ERR");
        SSD1306_SetCursor(0, 2);
        SSD1306_WriteString("> Check SPI!");
        return 1; // Ошибка SPI
    }

    // Проверка ADXL345
    SSD1306_SetCursor(0, 2);
    SSD1306_WriteString("> Init ADXL345... ");
    if (ADXL345_Init() == 1) // Успешная инициализация ADXL345
    {
        SSD1306_WriteString("OK");
    }
    else
    {
        SSD1306_WriteString("ERROR");
        SSD1306_SetCursor(0, 3);
        SSD1306_WriteString("> Check ADXL345!");
        return 1; // Ошибка ADXL345
    }

    // Завершение инициализации
    SSD1306_SetCursor(0, 4);
    SSD1306_WriteString("> All Init OK!");
    delay(10000); // Задержка для отображения сообщения
    SSD1306_Clear();

    return 0; // Успешная инициализация
}

/**
 * @brief Точка входа в программу
 */
void main(void)
{
    // Вызов функции инициализации
    uint8_t init_status = init();

    // Если инициализация завершилась с ошибкой, остановить выполнение
    if (init_status != 0)
    {
        while (1)
            ;
    }

    // Основной цикл программы
    while (1)
    {
        // Здесь будет основной функционал программы
        SSD1306_SetCursor(0, 0);
        SSD1306_WriteString("> Running...");
        delay(1000);
        SSD1306_Clear();
        delay(1000);
    }
}