#ifndef MY_MATH_H
#define MY_MATH_H

#include <stdint.h>

/**
 * @brief Вычисление квадратного корня из числа.
 *
 * @param x Входное число (должно быть >= 0)
 * @return Квадратный корень из x
 */
float my_sqrt(float x);

/**
 * @brief Вычисление арктангенса с использованием метода разложения Тейлора.
 *
 * Ограничено диапазоном |z| <= 1 для улучшения сходимости.
 *
 * @param z Отношение y/x
 * @return Арктангенс z в радианах
 */
float my_atan(float z);

/**
 * @brief Вычисление арктангенса двух переменных.
 *
 * @param y Координата Y
 * @param x Координата X
 * @return Арктангенс y/x в радианах
 */
float my_atan2(float y, float x);

/**
 * @brief Вычисление угла крена (вращение вокруг оси X).
 *
 * @param x Данные ускорения по оси X
 * @param y Данные ускорения по оси Y
 * @param z Данные ускорения по оси Z
 * @return Угол крена в градусах
 */
float calculate_roll(int16_t x, int16_t y, int16_t z);

/**
 * @brief Вычисление угла тангажа (вращение вокруг оси Y).
 *
 * @param x Данные ускорения по оси X
 * @param y Данные ускорения по оси Y
 * @param z Данные ускорения по оси Z
 * @return Угол тангажа в градусах
 */
float calculate_pitch(int16_t x, int16_t y, int16_t z);

#endif // MY_MATH_H