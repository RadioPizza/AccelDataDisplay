#include "iostm8s103.h"
#include "delay.h"

// Настройка выводов порта D
void portD_init(void)
{
    PD_DDR |= 0x40;  // Установить PD6 как выход (бит 6 соответствует PD6)
    PD_CR1 |= 0x40;  // Установить push-pull режим для PD6
    PD_ODR &= ~0x40; // Установить PD6 в низкое состояние
}

int main(void)
{
    portD_init(); // Инициализация порта D

    while (1)
    {
        PD_ODR ^= 0x40; // Инвертировать состояние PD6 (бит 6)
        delay(500); // Задержка 500 миллисекунд
    }
}
