#include "tim4.h"
#include "my_iostm8s103.h"
#include <stdint.h>

volatile uint32_t time_ms = 0;

void TIM4_Init(void);
uint32_t TIM4_GetMillis(void);
uint32_t TIM4_GetSeconds(void);
void TIM4_GetTimeString(char *timeStr);

@far @interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
    time_ms++;
    TIM4_SR = 0; // Сброс флага прерывания
}

void TIM4_Init(void)
{
    _asm("rim"); // Глобальное разрешение прерываний

    /* Остановка таймера */
    TIM4_CR1 = 0x00;

    /* Настройка предделителя на 8 */
    TIM4_PSCR = 0x03;

    /* Настройка значения тактов таймера для получения прерывания каждую миллисекунду */
    TIM4_ARR = 250;

    /* Сброс счетчика */
    TIM4_CNTR = 0x00;

    /* Очистка флага прерывания */
    TIM4_SR = 0x00;

    /* Разрешение прерывания по переполнению */
    TIM4_IER = 0x01;

    /* Запуск таймера */
    TIM4_CR1 = 0x01;
}

uint32_t TIM4_GetMillis(void)
{
    return time_ms;
}

uint32_t TIM4_GetSeconds(void)
{
    return TIM4_GetMillis() / 1000;
}

void TIM4_GetTimeString(char *timeStr)
{
    uint32_t totalSeconds = TIM4_GetSeconds();
    uint8_t hours = (uint8_t)(totalSeconds / 3600);
    uint8_t minutes = (uint8_t)((totalSeconds % 3600) / 60);
    uint8_t seconds = (uint8_t)(totalSeconds % 60);

    /* Форматирование строки времени */
    timeStr[0] = '0' + (hours / 10);
    timeStr[1] = '0' + (hours % 10);
    timeStr[2] = ':';
    timeStr[3] = '0' + (minutes / 10);
    timeStr[4] = '0' + (minutes % 10);
    timeStr[5] = ':';
    timeStr[6] = '0' + (seconds / 10);
    timeStr[7] = '0' + (seconds % 10);
    timeStr[8] = '\0';
}