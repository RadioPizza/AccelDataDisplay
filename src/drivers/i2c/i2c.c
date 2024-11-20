#include "i2c.h"

void I2C_Init(void)
{
    // Устанавливаем частоту периферийной шины в МГц (предполагается 16 МГц)
    I2C_FREQR = 16; // Частота тактирования периферии 16 МГц

    // Настраиваем скорость I2C (делитель частоты для получения 100 кГц)
    // CCR = F_master / (2 * F_SCL)
    // Для F_master = 16 МГц и F_SCL = 100 кГц: CCR = 80
    I2C_CCRL = 0x50; // 80 в десятичной системе
    I2C_CCRH = 0x00; // Биты 15-12 остаются 0 для стандартного режима

    // Устанавливаем максимальное время нарастания сигнала (Trise)
    // Trise = (F_master / 1МГц) + 1
    // Trise = 16 + 1 = 17
    I2C_TRISER = 17;

    // Включаем подтверждение ACK
    I2C_CR2 |= (1 << 2); // Устанавливаем бит ACK

    // Включаем периферийный модуль I2C
    I2C_CR1 |= (1 << 0); // Устанавливаем бит PE
}

void I2C_Start(void)
{
    I2C_CR2 |= (1 << 0); // Устанавливаем бит START
    // Ждем установки бита SB (Start Bit) в I2C_SR1
    while (!(I2C_SR1 & (1 << 0)))
        ;
}

void I2C_Stop(void)
{
    I2C_CR2 |= (1 << 1); // Устанавливаем бит STOP
}

void I2C_SendAddress(unsigned char address, unsigned char direction)
{
    // Объявляем все локальные переменные в начале функции
    unsigned char addr;
    unsigned char temp;

    // Формируем адрес с учетом режима (0 - запись, 1 - чтение)
    addr = (address << 1) | (direction & 0x01);
    I2C_DR = addr;

    // Ждем установки бита ADDR (Address Sent) в I2C_SR1
    while (!(I2C_SR1 & (1 << 1)))
        ;

    // Сбрасываем флаг ADDR чтением регистра состояния I2C_SR3
    temp = I2C_SR3;
    (void)temp; // Избегаем предупреждения о неиспользуемой переменной
}

void I2C_SendByte(unsigned char data)
{
    I2C_DR = data; // Записываем данные в регистр данных
    // Ждем установки бита TXE (Data Register Empty) в I2C_SR1
    while (!(I2C_SR1 & (1 << 7)))
        ;
}

unsigned char I2C_ReadByte(unsigned char ack)
{
    if (ack)
    {
        I2C_CR2 |= (1 << 2); // Включаем ACK
    }
    else
    {
        I2C_CR2 &= ~(1 << 2); // Выключаем ACK
    }
    // Ждем установки бита RXNE (Data Register Not Empty) в I2C_SR1
    while (!(I2C_SR1 & (1 << 6)))
        ;
    return I2C_DR; // Читаем полученные данные
}

void I2C_WriteRegister(unsigned char deviceAddress, unsigned char registerAddress, unsigned char data)
{
    I2C_Start();
    I2C_SendAddress(deviceAddress, 0); // Адрес устройства с записью (0)
    I2C_SendByte(registerAddress);     // Адрес регистра в устройстве
    I2C_SendByte(data);                // Данные для записи
    I2C_Stop();
}

unsigned char I2C_ReadRegister(unsigned char deviceAddress, unsigned char registerAddress)
{
    unsigned char data;
    I2C_Start();
    I2C_SendAddress(deviceAddress, 0); // Адрес устройства с записью (0)
    I2C_SendByte(registerAddress);     // Адрес регистра в устройстве
    I2C_Start();                       // Повторный старт
    I2C_SendAddress(deviceAddress, 1); // Адрес устройства с чтением (1)
    data = I2C_ReadByte(0);            // Читаем данные с NACK (0)
    I2C_Stop();
    return data;
}
