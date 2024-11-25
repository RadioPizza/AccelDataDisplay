/* i2c.c */
#include "i2c.h"

void I2C_Init(void)
{
    /* Включаем тактирование периферии I2C */
    CLK_PCKENR1 |= 0x02; // Бит 1 соответствует I2C в PCKENR1

    /* Настраиваем частоту I2C */
    I2C_FREQR = 16; // Предполагаемая частота тактирования 16МГц

    /* Настраиваем регистры контроля тактирования для 100кГц */
    I2C_CCRL = 0x50; // Стандартный режим, 100кГц
    I2C_CCRH = 0x00;

    /* Максимальное время нарастания */
    I2C_TRISER = 17;

    /* Настраиваем регистры управления I2C */
    I2C_CR1 = 0x00;         // Сбрасываем регистр управления 1
    I2C_CR2 |= I2C_CR2_ACK; // Устанавливаем бит ACK в регистре CR2

    /* Устанавливаем собственный адрес (не используется в режиме мастера) */
    I2C_OARL = 0x00;
    I2C_OARH = 0x00; // В 7-битном режиме адресации бит ADDMODE должен быть сброшен

    /* Включаем периферию I2C */
    I2C_CR1 |= I2C_CR1_PE; // Устанавливаем бит PE для включения I2C
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

void I2C_WriteAddress(unsigned char address)
{
    I2C_DR = address; // Отправляем адрес
    while (!(I2C_SR1 & I2C_SR1_ADDR))
        ;          // Ждем установки флага ADDR
    (void)I2C_SR3; // Читаем SR3 для сброса флага ADDR
}

void I2C_WriteData(unsigned char data)
{
    I2C_DR = data; // Отправляем данные
    while (!(I2C_SR1 & I2C_SR1_TXE))
        ; // Ждем, пока TXE (регистр данных пуст)
}

unsigned char I2C_ReadData_ACK(void)
{
    I2C_CR2 |= I2C_CR2_ACK; // Устанавливаем бит ACK
    while (!(I2C_SR1 & I2C_SR1_RXNE))
        ;          // Ждем установки флага RXNE
    return I2C_DR; // Возвращаем полученные данные
}

unsigned char I2C_ReadData_NACK(void)
{
    I2C_CR2 &= ~I2C_CR2_ACK; // Сбрасываем бит ACK
    while (!(I2C_SR1 & I2C_SR1_RXNE))
        ;          // Ждем установки флага RXNE
    return I2C_DR; // Возвращаем полученные данные
}
