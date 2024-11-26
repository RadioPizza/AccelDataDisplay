/**
 * @file main.c
 * @brief Пример работы с OLED-дисплеем на основе драйвера SSD1306
 *
 * Данный файл демонстрирует инициализацию OLED-дисплея, вывод текста и изображений, 
 * а также пример простейшей анимации.
 */

#include <stdint.h>
#include "ssd1306.h"
#include "smile_bitmap.h"
#include "delay.h"

/**
 * @brief Главная функция программы.
 * Выполняет демонстрацию работы с дисплеем SSD1306 и простой анимацией.
 */
void main(void)
{
    int16_t i = 0;

    /**
     * @section Initialization Инициализация дисплея
     */
    SSD1306_Init();      /**< Запуск и настройка SSD1306 */
    SSD1306_DisplayOn(); /**< Включаем дисплей */

    /**
     * @section Clearing Очистка дисплея
     */
    SSD1306_Clear(); /**< Полностью очищаем экран (заполняем черным цветом) */

    /**
     * @section Text Вывод текста
     */
    SSD1306_SetCursor(0, 0);                /**< Устанавливаем курсор в начало дисплея (верх левый угол) */
    SSD1306_WriteString("~Hello world!");   /**< Выводим текст "~Hello world!" */
    delay(200);                             /**< Задержка для задержки видимости на 200 мс */
    SSD1306_SetCursor(0, 2);                /**< Перемещаем курсор чуть ниже (вторая строка) */
    SSD1306_WriteString("Testing OLED");    /**< Печать текста "Testing OLED" */
    delay(200);                             /**< Задержка для отображения */

    /**
     * @section Bitmap Вывод картинки
     */
    SSD1306_DrawBitmap(32, 32, smile_bitmap, 16, 16); /**< Рисуем картинку "смайлик" размером 16x16 по координатам (32, 32) */
    delay(7000);                                      /**< Показываем картинку 7 секунд */

    /**
     * @section DisplayTest Тест Display On/Off
     * Демонстрирует включение и выключение дисплея.
     */
    for (i = 0; i < 3; i++)
    {
        SSD1306_DisplayOff(); /**< Выключаем дисплей */
        delay(500);           /**< Время задержки 500 мс */
        SSD1306_DisplayOn();  /**< Включаем дисплей */
        delay(2000);          /**< Время задержки 2 секунды */
    }

    /**
     * @section Animation Анимация с перемещением текста
     * Демонстрирует простой пример вертикального сдвига текста.
     */
    SSD1306_Clear();    /**< Очищаем дисплей перед началом анимации */
    while (1)
    {
        uint8_t page;
        for (page = 0; page < 8; page++)    /**< Пробегаем по всем 8 страницам (логическим строкам дисплея) */
        {
            if (page > 0)
            {
                SSD1306_SetCursor(8, page - 1); /**< Стираем предыдущую надпись */
                SSD1306_WriteString("       ");
            }
            SSD1306_SetCursor(8, page);         /**< Устанавливаем курсор и выводим текст */
            SSD1306_WriteString("Moving!");
            delay(300);                         /**< Задержка между переходами текста */
        }
        SSD1306_SetCursor(8, 7);        /**< Устанавливаем курсор на последнюю строку */
        SSD1306_WriteString("       "); /**< Стираем текст на 8 строке */
    }
}
