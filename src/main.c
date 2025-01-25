#include "delay.h"
#include "i2c.h"
#include "ssd1306.h"
#include "smile_bitmap.h"
#include "tim4.h"
#include "my_iostm8s103.h"
#include "spi.h"
#include "adxl345.h"
#include "eeprom.h"

#include "my_str.h"

/**
 * @brief Самотестирование EEPROM (Self-Test).
 *
 * @details Тест записывает и считывает тестовые данные для проверки работоспособности EEPROM.
 *
 * @return 0, если тест прошел успешно, 1, если произошла ошибка.
 */
uint8_t EEPROM_SelfTest(void)
{
    uint8_t test_data[] = {0x55, 0xAA, 0xFF};
    uint8_t read_data[3];
    uint8_t i;

    /* Записываем тестовые данные */
    if (EEPROM_Write(0x0000, test_data, sizeof(test_data)) != 0)
    {
        return 1; /* Ошибка записи */
    }

    /* Выводим записываемые данные */
    SSD1306_SetCursor(0, 1);
    SSD1306_WriteString("> Write data: ");
    SSD1306_SetCursor(0, 2);
    SSD1306_WriteString("> ");
    SSD1306_WriteInt(test_data[0]);
    SSD1306_WriteString(", ");
    SSD1306_WriteInt(test_data[1]);
    SSD1306_WriteString(", ");
    SSD1306_WriteInt(test_data[2]);

    /* Читаем записанные данные */
    if (EEPROM_Read(0x0000, read_data, sizeof(read_data)) != 0)
    {
        return 1; /* Ошибка чтения */
    }

    /* Выводим прочитанные данные */
    SSD1306_SetCursor(0, 3);
    SSD1306_WriteString("> Read data: ");
    SSD1306_SetCursor(0, 4);
    SSD1306_WriteString("> ");
    SSD1306_WriteInt(read_data[0]);
    SSD1306_WriteString(", ");
    SSD1306_WriteInt(read_data[1]);
    SSD1306_WriteString(", ");
    SSD1306_WriteInt(read_data[2]);

    /* Проверим соответствие данных */
    for (i = 0; i < sizeof(test_data); ++i)
    {
        if (test_data[i] != read_data[i])
        {
            return 1; /* Ошибка сравнения */
        }
    }
    return 0; /* Тест успешен */
}

#define LOG_DELAY 5000

/**
 * @brief Инициализация всех периферийных устройств с выводом отладочной информации на OLED-дисплей.
 * @return 0 при успешной инициализации, 1 при ошибке
 */
uint8_t init(void)
{
    // Иницилизация I2С
    if (I2C_Init(I2C_FAST_MODE) == 1)
        return 1; // Ошибка инициализации I2C

    // Инициализация и очистка OLED-дисплея
    SSD1306_Init();
    SSD1306_Clear();
    SSD1306_SetCursor(0, 0);
    SSD1306_WriteString("> Init OLED... ");
    SSD1306_WriteString("OK");
    delay(LOG_DELAY / 5);

    // Тестовая отрисовка изображения
    SSD1306_SetCursor(0, 2);
    SSD1306_WriteString("> Test OLED: draw BMP");
    SSD1306_DrawBitmap(56, 32, smile_bitmap, 16, 16);
    delay(LOG_DELAY);
    SSD1306_Clear();

    // Инициализация таймера
    SSD1306_SetCursor(0, 0);
    SSD1306_WriteString("> Init TIM4... ");
    TIM4_Init();
    SSD1306_WriteString("OK");
    SSD1306_SetCursor(0, 1);
    delay(LOG_DELAY / 2);
    SSD1306_Clear();

    // Вывод значений регистров TIM4
    SSD1306_SetCursor(0, 0);
    SSD1306_WriteString("TIM4 config:");
    delay(LOG_DELAY / 5);
    SSD1306_SetCursor(0, 1);
    SSD1306_WriteString("TIM4_CR1 = ");
    SSD1306_WriteInt(TIM4_CR1);
    delay(LOG_DELAY / 5);
    SSD1306_SetCursor(0, 2);
    SSD1306_WriteString("TIM4_IER = ");
    SSD1306_WriteInt(TIM4_IER);
    delay(LOG_DELAY / 5);
    SSD1306_SetCursor(0, 3);
    SSD1306_WriteString("TIM4_SR = ");
    SSD1306_WriteInt(TIM4_SR);
    delay(LOG_DELAY / 5);
    SSD1306_SetCursor(0, 4);
    SSD1306_WriteString("TIM4_EGR = ");
    SSD1306_WriteInt(TIM4_EGR);
    delay(LOG_DELAY / 5);
    SSD1306_SetCursor(0, 5);
    SSD1306_WriteString("TIM4_CNTR = ");
    SSD1306_WriteInt(TIM4_CNTR);
    delay(LOG_DELAY / 5);
    SSD1306_SetCursor(0, 6);
    SSD1306_WriteString("TIM4_PSCR = ");
    SSD1306_WriteInt(TIM4_PSCR);
    delay(LOG_DELAY / 5);
    SSD1306_SetCursor(0, 7);
    SSD1306_WriteString("TIM4_ARR = ");
    SSD1306_WriteInt(TIM4_ARR);
    delay(LOG_DELAY);
    SSD1306_Clear();

    // Инициализация SPI
    SSD1306_SetCursor(0, 0);
    SSD1306_WriteString("> Init SPI... ");
    if (SPI_Init() == 0)
    {
        SSD1306_WriteString("OK"); // Успешная инициализация SPI
    }
    else
    {
        SSD1306_WriteString("ERROR"); // Ошибка инициализации
        SSD1306_SetCursor(0, 1);
        SSD1306_WriteString("> Check SPI!");
        return 1;
    }
    delay(LOG_DELAY);
    SSD1306_Clear();

    // Инициализация ADXL345
    SSD1306_SetCursor(0, 0);
    SSD1306_WriteString("> Init ADXL345... ");
    if (ADXL345_Init() == 1) // Успешная инициализация ADXL345
    {
        SSD1306_WriteString("OK");
        SSD1306_SetCursor(0, 1);
        SSD1306_WriteString("> Device ID = ");
        SSD1306_WriteInt(ADXL345_ReadReg(ADXL345_REG_DEVID));
    }
    else
    {
        SSD1306_WriteString("ERROR");
        SSD1306_SetCursor(0, 1);
        SSD1306_WriteString("> Device ID = ");
        SSD1306_WriteInt(ADXL345_ReadReg(ADXL345_REG_DEVID));
        SSD1306_SetCursor(0, 2);
        SSD1306_WriteString("> Check ADXL345!");
        // return 1;
    }
    delay(LOG_DELAY);
    SSD1306_Clear();

    // Self test EEPROM
    SSD1306_SetCursor(0, 0);
    SSD1306_WriteString("> Test EEPROM... ");
    EEPROM_SelfTest();
    delay(LOG_DELAY);
    SSD1306_Clear();

    return 0;
}

/**
 * @brief Отрисовывает заголовки полей на OLED-дисплее.
 *
 * Функция очищает дисплей и выводит заголовки для отображения системного времени,
 * ускорений по осям X, Y, Z и углов крена и тангажа.
 */
void print_titles(void)
{
    SSD1306_Clear();
    SSD1306_SetCursor(0, 0);
    SSD1306_WriteString("System time: ");
    SSD1306_SetCursor(0, 2);
    SSD1306_WriteString("a_X: ");
    SSD1306_SetCursor(0, 3);
    SSD1306_WriteString("a_Y: ");
    SSD1306_SetCursor(0, 4);
    SSD1306_WriteString("a_Z: ");
    SSD1306_SetCursor(0, 5);
    SSD1306_WriteString("Roll: ");
    SSD1306_SetCursor(0, 6);
    SSD1306_WriteString("Pitch: ");
}

/**
 * @brief Выводит на OLED-дисплей значения системного времени, ускорений по осям X, Y, Z, углов крена и тангажа.
 *
 * @param time_str Строка, содержащая системное время в формате "ЧЧ:ММ:СС".
 * @param ax_str Строка, содержащая значение ускорения по оси X.
 * @param ay_str Строка, содержащая значение ускорения по оси Y.
 * @param az_str Строка, содержащая значение ускорения по оси Z.
 * @param roll_str Строка, содержащая значение угла крена.
 * @param pitch_str Строка, содержащая значение угла тангажа.
 */
void display_data(const char *time_str, const char *ax_str, const char *ay_str, const char *az_str, const char *roll_str, const char *pitch_str)
{
    // Вывод значений с единицами измерения
    SSD1306_SetCursor(80, 0);
    SSD1306_WriteString(time_str);

    SSD1306_SetCursor(42, 2);
    SSD1306_WriteString(ax_str);
    SSD1306_SetCursor(75, 2);
    SSD1306_WriteString("g");

    SSD1306_SetCursor(42, 3);
    SSD1306_WriteString(ay_str);
    SSD1306_SetCursor(75, 3);
    SSD1306_WriteString("g");

    SSD1306_SetCursor(42, 4);
    SSD1306_WriteString(az_str);
    SSD1306_SetCursor(75, 4);
    SSD1306_WriteString("g");

    SSD1306_SetCursor(42, 5);
    SSD1306_WriteString(roll_str);
    SSD1306_SetCursor(75, 5);
    SSD1306_WriteString("deg");

    SSD1306_SetCursor(42, 6);
    SSD1306_WriteString(pitch_str);
    SSD1306_SetCursor(75, 6);
    SSD1306_WriteString("deg");
}

/**
 * @brief Точка входа в программу
 */
void main(void)
{
    // Статус инициализации
    uint8_t init_status = 1;

    // Строка для хранения текущего времени
    char timeStr[9];

    // Вызов функции инициализации
    init_status = init();

    // Если инициализация завершилась с ошибкой, остановить выполнение
    if (init_status != 0)
    {
        while (1)
            ;
    }

    // Предварительная отрисовка названий полей
    print_titles();

    // Основной цикл программы
    while (1)
    {
        TIM4_GetTimeString(timeStr);
        display_data(timeStr, "0.0", "1.2", "-2.3", "0", "27.1");
        delay(100); // Обновление 10 раз в секунду
    }
}