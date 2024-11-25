#include "i2c.h"

#define EEPROM_ADDRESS_WRITE 0xA0 // 1010 0000 - Адрес EEPROM для записи
#define EEPROM_ADDRESS_READ 0xA1  // 1010 0001 - Адрес EEPROM для чтения
#define MEMORY_ADDRESS 0x0000     // Адрес памяти внутри EEPROM

void main(void)
{
    unsigned char write_data = 0xAB; // Данные для записи
    unsigned char read_data = 0x00;  // Переменная для хранения прочитанных данных
    volatile unsigned long i;        // Переменная для задержки

    /* Инициализация I2C */
    I2C_Init();

    while (1)
    {
        /* ------ Запись данных в EEPROM ------ */
        I2C_Start();                                         // Условие START
        I2C_WriteAddress(EEPROM_ADDRESS_WRITE);              // Отправка адреса EEPROM для записи
        I2C_WriteData((unsigned char)(MEMORY_ADDRESS >> 8)); // Старший байт адреса памяти
        I2C_WriteData((unsigned char)(MEMORY_ADDRESS));      // Младший байт адреса памяти
        I2C_WriteData(write_data);                           // Отправка данных для записи
        I2C_Stop();                                          // Условие STOP

        /* Задержка для завершения записи в EEPROM (в соответствии с даташитом EEPROM) */
        for (i = 0; i < 30000; i++)
            ;

        /* ------ Чтение данных из EEPROM ------ */
        I2C_Start();                                         // Условие START
        I2C_WriteAddress(EEPROM_ADDRESS_WRITE);              // Отправка адреса EEPROM для записи (для указания адреса памяти)
        I2C_WriteData((unsigned char)(MEMORY_ADDRESS >> 8)); // Старший байт адреса памяти
        I2C_WriteData((unsigned char)(MEMORY_ADDRESS));      // Младший байт адреса памяти

        I2C_Start();                           // Повторное условие START (Repeated START)
        I2C_WriteAddress(EEPROM_ADDRESS_READ); // Отправка адреса EEPROM для чтения
        read_data = I2C_ReadData_NACK();       // Чтение данных с NACK
        I2C_Stop();                            // Условие STOP

        /* ------ Проверка прочитанных данных ------ */
        if (read_data == write_data)
        {
            // Данные прочитаны корректно
        }
        else
        {
            // Ошибка чтения/записи
        }

        /* Задержка перед следующим циклом */
        for (i = 0; i < 50000; i++)
            ;
    }
}
