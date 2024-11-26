/** @file delay.h
 *  @brief Функция для создания задержек.
 */

#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
    #endif

        /**
         * @brief Задержка на указанное количество миллисекунд.
         *
         * @param ms Количество миллисекунд задержки.
         */
        void delay(uint32_t ms);

    #ifdef __cplusplus
}
#endif

#endif // DELAY_H
