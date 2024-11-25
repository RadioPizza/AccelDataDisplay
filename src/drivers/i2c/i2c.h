// i2c.h
#ifndef I2C_H
#define I2C_H

#include "iostm8s103.h"

// Битовые маски для регистров I2C
#define I2C_CR1_PE ((unsigned char)0x01)
#define I2C_CR2_START ((unsigned char)0x01)
#define I2C_CR2_STOP ((unsigned char)0x02)
#define I2C_CR2_ACK ((unsigned char)0x04)
#define I2C_SR1_SB ((unsigned char)0x01)
#define I2C_SR1_ADDR ((unsigned char)0x02)
#define I2C_SR1_TXE ((unsigned char)0x80)
#define I2C_SR1_RXNE ((unsigned char)0x40)
#define I2C_OARH_ADDMODE ((unsigned char)0x80)

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WriteAddress(unsigned char address);
void I2C_WriteData(unsigned char data);
unsigned char I2C_ReadData_ACK(void);
unsigned char I2C_ReadData_NACK(void);
#endif // I2C_H
