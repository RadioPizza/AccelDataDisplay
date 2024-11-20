#include "iostm8s103.h"

// Функция задержки
void delay(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 100; j++)
            ;
}

int main(void)
{
    // Инициализация PB5 как выход
    PB_DDR |= (1 << 5); // Настраиваем PB5 как выход
    PB_CR1 |= (1 << 5); // Включаем push-pull

    while (1)
    {
        // Устанавливаем PB5 (включаем светодиод)
        PB_ODR |= (1 << 5);
        delay(500); // Задержка 500 мс

        // Сбрасываем PB5 (выключаем светодиод)
        PB_ODR &= ~(1 << 5);
        delay(500); // Задержка 500 мс
    }

    return 0;
}