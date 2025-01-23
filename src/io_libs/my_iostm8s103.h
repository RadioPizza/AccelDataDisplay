#ifndef IOSTM8S103_H
#define IOSTM8S103_H

/* PORTS section */
/* Port A */
#define PA_ODR        (*(volatile char*)0x5000)  /* Data Output Latch reg */
#define PA_IDR        (*(volatile char*)0x5001)  /* Input Pin Value reg */
#define PA_DDR        (*(volatile char*)0x5002)  /* Data Direction */
#define PA_CR1        (*(volatile char*)0x5003)  /* Control register 1 */
#define PA_CR2        (*(volatile char*)0x5004)  /* Control register 2 */

/* Port B */
#define PB_ODR        (*(volatile char*)0x5005)  /* Data Output Latch reg */
#define PB_IDR        (*(volatile char*)0x5006)  /* Input Pin Value reg */
#define PB_DDR        (*(volatile char*)0x5007)  /* Data Direction */
#define PB_CR1        (*(volatile char*)0x5008)  /* Control register 1 */
#define PB_CR2        (*(volatile char*)0x5009)  /* Control register 2 */

/* Port C */
#define PC_ODR        (*(volatile char*)0x500a)  /* Data Output Latch reg */
#define PC_IDR        (*(volatile char*)0x500b)  /* Input Pin Value reg */
#define PC_DDR        (*(volatile char*)0x500c)  /* Data Direction */
#define PC_CR1        (*(volatile char*)0x500d)  /* Control register 1 */
#define PC_CR2        (*(volatile char*)0x500e)  /* Control register 2 */

/* Port D */
#define PD_ODR        (*(volatile char*)0x500f)  /* Data Output Latch reg */
#define PD_IDR        (*(volatile char*)0x5010)  /* Input Pin Value reg */
#define PD_DDR        (*(volatile char*)0x5011)  /* Data Direction */
#define PD_CR1        (*(volatile char*)0x5012)  /* Control register 1 */
#define PD_CR2        (*(volatile char*)0x5013)  /* Control register 2 */

/* Port E */
#define PE_ODR        (*(volatile char*)0x5014)  /* Data Output Latch reg */
#define PE_IDR        (*(volatile char*)0x5015)  /* Input Pin Value reg */
#define PE_DDR        (*(volatile char*)0x5016)  /* Data Direction */
#define PE_CR1        (*(volatile char*)0x5017)  /* Control register 1 */
#define PE_CR2        (*(volatile char*)0x5018)  /* Control register 2 */

/* Port F */
#define PF_ODR        (*(volatile char*)0x5019)  /* Data Output Latch reg */
#define PF_IDR        (*(volatile char*)0x501a)  /* Input Pin Value reg */
#define PF_DDR        (*(volatile char*)0x501b)  /* Data Direction */
#define PF_CR1        (*(volatile char*)0x501c)  /* Control register 1 */
#define PF_CR2        (*(volatile char*)0x501d)  /* Control register 2 */

/* FLASH section */
#define FLASH_CR1     (*(volatile char*)0x505a)  /* Flash Control Register 1 */
#define FLASH_CR2     (*(volatile char*)0x505b)  /* Flash Control Register 2 */
#define FLASH_NCR2    (*(volatile char*)0x505c)  /* Flash Complementary Control Reg 2 */
#define FLASH_FPR     (*(volatile char*)0x505d)  /* Flash Protection reg */
#define FLASH_NFPR    (*(volatile char*)0x505e)  /* Flash Complementary Protection reg */
#define FLASH_IAPSR   (*(volatile char*)0x505f)  /* Flash in-appl Prog. Status reg */
#define FLASH_PUKR    (*(volatile char*)0x5062)  /* Flash Program memory unprotection reg */
#define FLASH_DUKR    (*(volatile char*)0x5064)  /* Data EEPROM unprotection reg */

/* External Interrupt Controller section */
#define EXTI_CR1      (*(volatile char*)0x50a0)  /* Ext Int Ctrl reg 1 */
#define EXTI_CR2      (*(volatile char*)0x50a1)  /* Ext Int Ctrl reg 2 */

/* RSTC section */
#define RST_SR        (*(volatile char*)0x50b3)  /* Reset Status register */

/* CLOCK section */
#define CLK_ICKCR     (*(volatile char*)0x50c0)  /* Internal Clock Control reg */
#define CLK_ECKCR     (*(volatile char*)0x50c1)  /* External Clock Control reg */
#define CLK_CMSR      (*(volatile char*)0x50c3)  /* Master Status reg */
#define CLK_SWR       (*(volatile char*)0x50c4)  /* Master Switch reg */
#define CLK_SWCR      (*(volatile char*)0x50c5)  /* Switch Control reg */
#define CLK_CKDIVR    (*(volatile char*)0x50c6)  /* Divider register */
#define CLK_PCKENR1   (*(volatile char*)0x50c7)  /* Peripheral Clock Gating reg 1 */
#define CLK_CSSR      (*(volatile char*)0x50c8)  /* Security System register */
#define CLK_CCOR      (*(volatile char*)0x50c9)  /* Configurable Clock Ctrl reg */
#define CLK_PCKENR2   (*(volatile char*)0x50ca)  /* Peripheral Clock Gating reg 2 */
#define CLK_CANCCR    (*(volatile char*)0x50cb)  /* Can Clock Control reg */
#define CLK_HSITRIMR  (*(volatile char*)0x50cc)  /* HSI Calibration Trimming reg */
#define CLK_SWIMCCR   (*(volatile char*)0x50cd)  /* SWIM Clock Control reg */

/* WATCHDOG section */
#define WWDG_CR       (*(volatile char*)0x50d1)  /* WWDG Control register */
#define WWDG_WR       (*(volatile char*)0x50d2)  /* WWDG Window register */
#define IWDG_KR       (*(volatile char*)0x50e0)  /* IWDG Key register */
#define IWDG_PR       (*(volatile char*)0x50e1)  /* IWDG Prescaler register */
#define IWDG_RLR      (*(volatile char*)0x50e2)  /* IWDG Reload register */

/* AWU section */
#define AWU_CSR1      (*(volatile char*)0x50f0)  /* AWU Control/Status reg 1 */
#define AWU_APR       (*(volatile char*)0x50f1)  /* AWU Async Prescale Buffer reg */
#define AWU_TBR       (*(volatile char*)0x50f2)  /* AWU Timebase selection reg */
#define BEEP_CSR      (*(volatile char*)0x50f3)  /* BEEP control/status reg */

/* SPI section */
#define SPI_CR1       (*(volatile char*)0x5200)  /* SPI Control register 1 */
#define SPI_CR2       (*(volatile char*)0x5201)  /* SPI Control register 2 */
#define SPI_ICR       (*(volatile char*)0x5202)  /* SPI Interrupt/Ctrl reg */
#define SPI_SR        (*(volatile char*)0x5203)  /* SPI Status register */
#define SPI_DR        (*(volatile char*)0x5204)  /* SPI Data I/O reg */
#define SPI_CRCPR     (*(volatile char*)0x5205)  /* SPI CRC Polynomial reg */
#define SPI_RXCRCR    (*(volatile char*)0x5206)  /* SPI Rx CRC register */
#define SPI_TXCRCR    (*(volatile char*)0x5207)  /* SPI Tx CRC register */

/* TIMER 4 section */
#define TIM4_CR1      (*(volatile char*)0x5340)  /* Control register 1 */
#define TIM4_IER      (*(volatile char*)0x5343)  /* Interrupt enable reg */
#define TIM4_SR       (*(volatile char*)0x5344)  /* Status register */
#define TIM4_EGR      (*(volatile char*)0x5345)  /* Event Generation reg */
#define TIM4_CNTR     (*(volatile char*)0x5346)  /* Counter register */
#define TIM4_PSCR     (*(volatile char*)0x5347)  /* Prescaler register */
#define TIM4_ARR      (*(volatile char*)0x5348)  /* Auto-reload register */

/* I2C section */
#define I2C_CR1       (*(volatile char*)0x5210)  /* Control register 1 */
#define I2C_CR2       (*(volatile char*)0x5211)  /* Control register 2 */
#define I2C_FREQR     (*(volatile char*)0x5212)  /* Frequency register */
#define I2C_OARL      (*(volatile char*)0x5213)  /* Own Address reg low */
#define I2C_OARH      (*(volatile char*)0x5214)  /* Own Address reg high */
#define I2C_DR        (*(volatile char*)0x5216)  /* Data Register */
#define I2C_SR1       (*(volatile char*)0x5217)  /* Status Register 1 */
#define I2C_SR2       (*(volatile char*)0x5218)  /* Status Register 2 */
#define I2C_SR3       (*(volatile char*)0x5219)  /* Status Register 3 */
#define I2C_ITR       (*(volatile char*)0x521a)  /* Interrupt Control reg */
#define I2C_CCRL      (*(volatile char*)0x521b)  /* Clock Control reg low */
#define I2C_CCRH      (*(volatile char*)0x521c)  /* Clock Control reg high */
#define I2C_TRISER    (*(volatile char*)0x521d)  /* Trise reg */
#define I2C_PECR      (*(volatile char*)0x521e)  /* Packet Error Checking reg */

#endif // IOSTM8S103_H