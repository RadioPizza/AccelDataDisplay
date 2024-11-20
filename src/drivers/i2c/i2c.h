#ifndef I2C_H
#define I2C_H

#include "iostm8s103.h"

// Инициализация модуля I2C
void I2C_Init(void);

// Генерация стартового условия
void I2C_Start(void);

// Генерация стоп-условия
void I2C_Stop(void);

// Отправка адреса устройства с указанием режима (чтение/запись)
void I2C_SendAddress(unsigned char address, unsigned char direction);

// Отправка байта данных
void I2C_SendByte(unsigned char data);

// Чтение байта данных с возможностью отправки ACK/NACK
unsigned char I2C_ReadByte(unsigned char ack);

// Функция записи байта данных в указанный регистр устройства
void I2C_WriteRegister(unsigned char deviceAddress, unsigned char registerAddress, unsigned char data);

// Функция чтения байта данных из указанного регистра устройства
unsigned char I2C_ReadRegister(unsigned char deviceAddress, unsigned char registerAddress);

#endif // I2C_H
