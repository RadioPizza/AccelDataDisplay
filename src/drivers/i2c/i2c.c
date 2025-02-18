/**
 * @file i2c.с
 * @brief Реализация функций для работы с I2C на микроконтроллерах STM8S103xxxx
 */

#include "i2c.h"
#include "my_iostm8s103.h"

uint8_t I2C_Init(I2C_Mode_t mode)
{
    uint16_t CCR;
    uint8_t CCRL_Value;
    uint8_t CCRH_Value;
    uint8_t TRISER_Value;

    /* Включаем тактирование периферии I2C */
    CLK_PCKENR1 |= 0x02; // Бит 1 соответствует I2C в PCKENR1

    /* Настраиваем частоту I2C */
    I2C_FREQR = 16; // Частота тактирования 16 МГц

    /* Настраиваем параметры в зависимости от режима */
    if (mode == I2C_STANDARD_MODE)
    {
        /* Стандартный режим (100 кГц) */
        CCRL_Value = 0x50;
        CCRH_Value = 0x00;
        TRISER_Value = 17;
    }
    else
    { /* I2C_FAST_MODE */
        /* Быстрый режим (400 кГц) */
        CCR = 13;                                                // Вычислено ранее
        CCRL_Value = (uint8_t)(CCR & 0xFF);                      // Младшие 8 бит CCR
        CCRH_Value = (uint8_t)((CCR >> 8) & 0x0F) | I2C_CCRH_FS; // Старшие биты CCR + бит FS (Fast Mode)
        TRISER_Value = 6;
    }

    /* Устанавливаем CCRL и CCRH */
    I2C_CCRL = CCRL_Value;
    I2C_CCRH = CCRH_Value;

    /* Устанавливаем максимальное время нарастания */
    I2C_TRISER = TRISER_Value;

    /* Сбрасываем регистр управления 1 */
    I2C_CR1 = 0x00;

    /* Устанавливаем бит ACK в регистре CR2 */
    I2C_CR2 |= I2C_CR2_ACK;

    /* Устанавливаем собственный адрес (не используется в режиме мастера) */
    I2C_OARL = 0x00;
    I2C_OARH = 0x00; // В 7-битном режиме адресации бит ADDMODE должен быть сброшен

    /* Включаем периферию I2C */
    I2C_CR1 |= I2C_CR1_PE; // Устанавливаем бит PE для включения I2C

    /* Проверяем успешность инициализации */
    return (I2C_CR1 & I2C_CR1_PE) ? 0 : 1;
}

void I2C_Start(void)
{
    I2C_CR2 |= I2C_CR2_START; // Генерируем условие START
    while (!(I2C_SR1 & I2C_SR1_SB))
        ; // Ждем установки флага SB (Start Bit)
}

void I2C_Stop(void)
{
    I2C_CR2 |= I2C_CR2_STOP; // Генерируем условие STOP
}

void I2C_WriteAddress(uint8_t address)
{
    I2C_DR = address; // Отправляем адрес
    while (!(I2C_SR1 & I2C_SR1_ADDR))
        ;          // Ждем установки флага ADDR
    (void)I2C_SR3; // Читаем SR3 для сброса флага ADDR
}

void I2C_WriteData(uint8_t data)
{
    I2C_DR = data; // Отправляем данные
    while (!(I2C_SR1 & I2C_SR1_TXE))
        ; // Ждем, пока TXE (регистр данных пуст)
}

uint8_t I2C_ReadData_ACK(void)
{
    I2C_CR2 |= I2C_CR2_ACK; // Устанавливаем бит ACK
    while (!(I2C_SR1 & I2C_SR1_RXNE))
        ;          // Ждем установки флага RXNE
    return I2C_DR; // Возвращаем полученные данные
}

uint8_t I2C_ReadData_NACK(void)
{
    I2C_CR2 &= ~I2C_CR2_ACK; // Сбрасываем бит ACK
    while (!(I2C_SR1 & I2C_SR1_RXNE))
        ;          // Ждем установки флага RXNE
    return I2C_DR; // Возвращаем полученные данные
}
