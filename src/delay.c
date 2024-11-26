/** @file delay.c
 *  @brief Реализация функции задержки на указанный промежуток времени.
 */

#include "delay.h"

void delay(uint32_t ms)
{
    while (ms--)
    {
        volatile uint16_t i;
        for (i = 0; i < 1000; ++i)
        {
            _asm("nop"); // Ассемблерная команда "ничего не делать"
        }
    }
}
