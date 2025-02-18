/**
 * @file ssd1306.h
 * @brief Драйвер для OLED дисплея на базе контроллера SSD1306
 *
 * В данном файле содержатся определения, константы и прототипы функций для
 * инициализации и управления OLED дисплеем, работающим по интерфейсу I2C.
 */

#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>

/**
 * @def SSD1306_I2C_ADDRESS
 * @brief I2C адрес дисплея SSD1306
 *
 * Значение адреса используется для инициализации и обмена данными с дисплеем по шине I2C.
 */
#define SSD1306_I2C_ADDRESS 0x78

/**
 * @def SSD1306_COMMAND
 * @brief Индикатор передачи командных данных
 *
 * Используется для обозначения того, что последующие байты содержат команды для дисплея.
 */
#define SSD1306_COMMAND 0x00

/**
 * @def SSD1306_DATA
 * @brief Индикатор передачи данных
 *
 * Используется для обозначения того, что последующие байты содержат графические данные для отображения.
 */
#define SSD1306_DATA 0x40

/**
 * @brief Инициализирует дисплей SSD1306
 * @details Настраивает основные параметры дисплея, включая разрешение, режим работы и интерфейс связи.
 *          Необходима для подготовки дисплея к приему данных.
 * @warning Функция не проверяет корректность инициализации I2C. Убедитесь, что шина I2C настроена правильно перед вызовом.
 */
void SSD1306_Init(void);

/**
 * @brief Очищает содержимое дисплея
 *
 * Заполняет весь дисплей черным цветом (гасит все пиксели), подготавливая его к рисованию новой информации.
 *
 * @note После очистки курсор остается на предыдущей позиции. Для изменения позиции используйте @ref SSD1306_SetCursor.
 */
void SSD1306_Clear(void);

/**
 * @brief Устанавливает позицию курсора
 *
 * Задает текущую позицию курсора для последующей отрисовки символов или графических объектов.
 *
 * @param[in] column Колонка (X-координата) от 0 до 127
 * @param[in] page   Страница (Y-координата) от 0 до 7 (для дисплея 128x64)
 *
 * @note Координаты начинаются с нуля. Убедитесь, что указанные значения находятся в допустимых пределах.
 */
void SSD1306_SetCursor(uint8_t column, uint8_t page);

/**
 * @brief Выводит одиночный символ на дисплей
 *
 * Отображает указанный символ в текущей позиции курсора с использованием встроенного шрифта.
 *
 * @param[in] c Символ для отображения
 *
 * @note После отображения символа курсор автоматически перемещается к следующей позиции.
 * @see SSD1306_WriteString
 */
void SSD1306_WriteChar(char c);

/**
 * @brief Выводит строку символов на дисплей
 *
 * Последовательно выводит символы строки на дисплей, начиная с текущей позиции курсора.
 *
 * @param[in] str Указатель на строку (массив символов), заканчивающуюся нулевым байтом
 *
 * @note Длина строки должна соответствовать доступному пространству на дисплее или быть обрезанной.
 * @see SSD1306_WriteChar
 */
void SSD1306_WriteString(const char *str);

/**
 * @brief Выводит целое число на дисплей
 *
 * Преобразует заданное целое число в строку и выводит ее на дисплей, начиная с текущей позиции курсора.
 * Использует функцию @ref int_to_str из `my_str.h` для преобразования числа в строку.
 *
 * @param[in] num Целое число типа int32_t для отображения. Диапазон значений зависит от размера типа `int32_t`.
 *
 * @note Функция использует статический буфер для хранения строки.
 * @see SSD1306_WriteString, int_to_str
 */
void SSD1306_WriteInt(int32_t num);

/**
 * @brief Отображает битовое изображение на дисплее
 *
 * Рисует изображение на дисплее по заданным координатам. Изображение должно быть закодировано в массиве bitmap.
 *
 * @param[in] x       Начальная X-координата (колонка) от 0 до ширины дисплея
 * @param[in] y       Начальная Y-координата (страница) от 0 до количества страниц дисплея
 * @param[in] bitmap  Указатель на массив байтов, содержащий битовое изображение
 * @param[in] width   Ширина изображения в пикселях
 * @param[in] height  Высота изображения в пикселях
 *
 * @note Формат изображения: вертикальная ориентация, 1 бит на пиксель.
 */
void SSD1306_DrawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t width, uint8_t height);

/**
 * @brief Включает дисплей
 *
 * Активирует отображение содержимого дисплея после его отключения или перехода в спящий режим.
 *
 * @note Эта функция должна вызываться после SSD1306_DisplayOff() для возобновления отображения.
 */
void SSD1306_DisplayOn(void);

/**
 * @brief Выключает дисплей
 *
 * Отключает отображение содержимого дисплея, переводя его в режим сна.
 * При этом содержимое дисплея сохраняется в памяти контроллера.
 *
 */
void SSD1306_DisplayOff(void);

#endif // SSD1306_H
