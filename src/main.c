#include "ssd1306.h" // Заголовочный файл с функциями для SSD1306

// Пример маленького изображения (битмап 16x16 пикселей в hex)
const unsigned char test_bitmap[] = {
    0xFF, 0x81, 0xBD, 0xA1,
    0xA1, 0xBD, 0x81, 0xFF,
    0xFF, 0x81, 0xBD, 0xA1,
    0xA1, 0xBD, 0x81, 0xFF,
    0xFF, 0xFF, 0xC7, 0xBB,
    0xBB, 0xBB, 0xBB, 0xBB,
    0xBB, 0xBB, 0xBB, 0xBB,
    0xBB, 0xC7, 0xFF, 0xFF};

// Функция задержки
void delay(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 100; j++)
            ;
}

// Тест программы
int main(void)
{
    int i = 0;

    // 1. Инициализация дисплея
    SSD1306_Init();      // Запуск и настройка SSD1306
    SSD1306_DisplayOn(); // Включить дисплей

    // 2. Очистка дисплея
    SSD1306_Clear(); // Очистить весь экран (залить черным)

    // 3. Тест: Вывод текста
    SSD1306_SetCursor(0, 0);       // Установка курсора в начало (верхний левый угол)
    SSD1306_WriteString("Hello!"); // Вывод текста "Hello!" на дисплей

    SSD1306_SetCursor(0, 2);             // Перемещение курсора на вторую строку
    SSD1306_WriteString("Testing OLED"); // Вывод текста на дисплей

    // 4. Тест вывода тестовой картинки
    SSD1306_DrawBitmap(32, 32, test_bitmap, 16, 16); // Рисуем битмап в позиции (16, 4)
    delay(5000);

    // 5. Проверка Display On/Off

    for (i = 0; i < 3; i++)
    {
        SSD1306_DisplayOff(); // Выключить дисплей
        delay(500);           // Подождать 500 мс
        SSD1306_DisplayOn();  // Включить дисплей
        delay(2000);          // Подождать 500 мс
    }

    // 6. Цикл с перемещением текста (анимация)
    SSD1306_Clear();
    while (1)
    {
        unsigned char page;
        for (page = 0; page < 8; page++)
        {
            if (page > 0)
            {
                SSD1306_SetCursor(8, page - 1);
                SSD1306_WriteString("       ");
            }
            SSD1306_SetCursor(8, page);
            SSD1306_WriteString("Moving!");
            delay(300);
        }
        SSD1306_SetCursor(8, 7);
        SSD1306_WriteString("       ");
    }
}
