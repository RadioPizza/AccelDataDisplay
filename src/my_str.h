/**
 * @file my_str.h
 * @brief Заголовочный файл для работы со строками.
 *
 * Этот файл содержит объявление функций для работы со строками,
 * включая преобразование целого числа в строку.
 */

#ifndef MY_STR_H
#define MY_STR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Преобразует целое число в строку.
     *
     * Функция преобразует целое число в строковое представление и
     * записывает результат в переданный буфер.
     *
     * @param[in] num Целое число, которое необходимо преобразовать.
     * @param[out] str Указатель на буфер, в который будет записана строка.
     */
    void int_to_str(int32_t num, char *str);

#ifdef __cplusplus
}
#endif

#endif /* MY_STR_H */