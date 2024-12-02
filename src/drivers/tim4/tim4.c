/** @file tim4.c
 *  @brief Реализация функций для работы с таймером TIM4
 */

#include "tim4.h"
#include "iostm8s103.h"

/** @brief Счетчик миллисекунд */
static volatile uint32_t milliseconds = 0;

void TIM4_Init(void)
{
    /* Остановка таймера */
    TIM4_CR1 = 0x00;
    
    /* Настройка предделителя на 128 */
    TIM4_PSCR = 0x07;
    
    /* Настройка периода для получения прерывания каждую миллисекунду
     * При частоте МК 16 МГц, предделителе 128:
     * 16000000 / 128 = 125000 Гц
     * Для частоты 1 кГц нужен период 125 */
    TIM4_ARR = 124; /* 125-1, так как счет начинается с 0 */
    
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
    uint32_t ms;
    
    /* Отключаем прерывания для атомарного чтения */
    __asm__("sim");
    ms = milliseconds;
    __asm__("rim");
    
    return ms;
}

uint32_t TIM4_GetSeconds(void)
{
    return TIM4_GetMillis() / 1000;
}

void TIM4_GetTimeString(char* timeStr)
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

/**
 * @brief Обработчик прерывания таймера TIM4
 * 
 * Вызывается каждую миллисекунду, инкрементирует счетчик миллисекунд
 */
void TIM4_UPD_OVF_IRQHandler(void) __interrupt(23)
{
    /* Инкремент счетчика миллисекунд */
    milliseconds++;
    
    /* Сброс флага прерывания */
    TIM4_SR = 0x00;
}