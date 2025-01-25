#include "i2c.h"
#include "ssd1306.h"
#include "spi.h"
#include "adxl345.h"
#include "delay.h"
#include "tim4.h"
#include "eeprom.h"
#include "my_iostm8s103.h"

/**
 * @brief Инициализация всех периферийных устройств с выводом отладочной информации на OLED-дисплей.
 * @return 0 при успешной инициализации, 1 при ошибке
 */
uint8_t init(void)
{
    uint8_t test_data = 0x55; // Тестовый байт данных
    uint8_t read_data;        // Буфер для чтения

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
    /*
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
    return 1;
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
    return 1;
}

// Проверка EEPROM
SSD1306_SetCursor(0, 3);
SSD1306_WriteString("> Init EEPROM... ");

if (M24512_Init() != 0) {
    SSD1306_WriteString("ERR");
    SSD1306_SetCursor(0, 4);
    SSD1306_WriteString("> Check EEPROM!");
    return 1;
}

// Тест записи/чтения EEPROM
if (M24512_WriteByte(0x0000, test_data) != 0) {
    SSD1306_WriteString("ERR");
    SSD1306_SetCursor(0, 4);
    SSD1306_WriteString("> EEPROM Write Err!");
    return 1;
}

if (M24512_ReadByte(0x0000, &read_data) != 0 || read_data != test_data) {
    SSD1306_WriteString("ERR");
    SSD1306_SetCursor(0, 4);
    SSD1306_WriteString("> EEPROM Read Err!");
    return 1;
}

SSD1306_WriteString("OK");
    */
    // Инициализация таймера
    SSD1306_SetCursor(0, 4);
    SSD1306_WriteString("> Init TIM4... ");
    TIM4_Init();
    SSD1306_WriteString("OK");

    // Завершение инициализации
    SSD1306_SetCursor(0, 5);
    SSD1306_WriteString("> All Init OK!");
    delay(2000); // Задержка для отображения сообщения
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
    SSD1306_SetCursor(0, 1);
    SSD1306_WriteString("a_X: ");
    SSD1306_SetCursor(0, 2);
    SSD1306_WriteString("a_Y: ");
    SSD1306_SetCursor(0, 3);
    SSD1306_WriteString("a_Z: ");
    SSD1306_SetCursor(0, 4);
    SSD1306_WriteString("Roll: ");
    SSD1306_SetCursor(0, 5);
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
    SSD1306_SetCursor(75, 0);
    SSD1306_WriteString(time_str);

    SSD1306_SetCursor(40, 1);
    SSD1306_WriteString(ax_str);

    SSD1306_SetCursor(40, 2);
    SSD1306_WriteString(ay_str);

    SSD1306_SetCursor(40, 3);
    SSD1306_WriteString(az_str);

    SSD1306_SetCursor(40, 4);
    SSD1306_WriteString(roll_str);

    SSD1306_SetCursor(40, 5);
    SSD1306_WriteString(pitch_str);
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
        display_data(timeStr, "0.0 g", "1.2 g", "-2.3 g", "0 DEG", "27.1 DEG");
        delay(100); // Обновление 10 раз в секунду
    }
}