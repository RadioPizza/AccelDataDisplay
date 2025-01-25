/** @file tim4.h
 *  @brief Библиотека для работы с таймером TIM4
 *
 *  Данная библиотека предоставляет функции для работы с таймером TIM4
 *  микроконтроллера STM8S103F3P6. Реализует системный таймер с точностью
 *  до миллисекунд и функции получения системного времени.
 */

#ifndef TIM4_H
#define TIM4_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Инициализация таймера TIM4
     *
     * Настраивает TIM4 как системный таймер с периодом 1 мс
     */
    void TIM4_Init(void);

    /**
     * @brief Получение количества миллисекунд с момента запуска
     * @return uint32_t Количество миллисекунд
     */
    uint32_t TIM4_GetMillis(void);

    /**
     * @brief Получение количества секунд с момента запуска
     * @return uint32_t Количество секунд
     */
    uint32_t TIM4_GetSeconds(void);

    /**
     * @brief Получение системного времени в формате строки "ЧЧ:ММ:СС"
     * @param[out] timeStr Указатель на строку для записи времени (минимум 9 байт)
     */
    void TIM4_GetTimeString(char *timeStr);

#ifdef __cplusplus
}
#endif

#endif /* TIM4_H */