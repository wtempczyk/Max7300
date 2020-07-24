/*
 * max7300.c
 *
 *  Created on: 17 lip 2020
 *      Author: Wojciech Tempczyk
 *
 *"THE BEER-WARE LICENSE" :
 * As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return W.T. ;)
 */
#include "max7300.h"
#include "main.h"

#define ADR 0x80 //adress of your MAX7300 (when AD1 and AD0 connect with GND it is 0x80 (tab.3 page.12 of DS-DataSheet))
#define REG_CONF_04_07_ (0x09)  //adress of configuration register for 4-7 pins
#define REG_CONF_08_11_ (0x0A)  //adress of configuration register for 8-11 pins
#define REG_CONF_12_15_ (0x0B)  //adress of configuration register for 12-15 pins
#define REG_CONF_16_19_ (0x0C)  //adress of configuration register for 16-19 pins
#define REG_CONF_20_23_ (0x0D)  //adress of configuration register for 20-23 pins
#define REG_CONF_24_27_ (0x0E)  //adress of configuration register for 24-27 pins
#define REG_CONF_28_31_ (0x0F)  //adress of configuration register for 28-31 pins
#define REG_04_11_ (0x44) //adress to write or read 4-11 port
#define REG_12_19_ (0x4C) //adress to write or read 12-19 port
#define REG_20_27_ (0x54) //adress to write or read 20-27 port
#define REG_28_31_ (0x44) //adress to write or read 4-11 port
#define REG_SHUT (0x04) // adress of configuration register for shutdown mode

uint8_t data[1];  // to make CubeIDE Happy ;D
uint8_t dane[1];

int MAX7300_init(I2C_HandleTypeDef *hi2c)
{

	if(HAL_OK!=HAL_I2C_IsDeviceReady(hi2c, ADR, 2, 100)) //sprawdzenie czy urządzenie odpowiada
	{
		return 1;
	}
	HAL_Delay(10);
	data[0]=0x81;  //ustawienie pinu M i S w stan wysoki (str.16 DS)
	HAL_I2C_Mem_Write(hi2c, ADR, REG_SHUT, 1, data, 1, 100); //wyjście z shutdown
	HAL_Delay(10);
	data[0]=0x55;  //ustawienie pinów jako OUTPUTY (str.7 DS)
	HAL_I2C_Mem_Write(hi2c, ADR, REG_CONF_04_07_, 1, data, 1, 100);  //konfiguracja max7300 pod adresem(0x80), porty P04-P07  jako OUTPUT (bo tak trzeba) (str.6 - datasheet)
	HAL_Delay(10);
	HAL_I2C_Mem_Write(hi2c, ADR, REG_CONF_08_11_, 1, data, 1, 100);  //konfiguracja max7300 pod adresem(0x80), porty P08-P011  jako OUTPUT (bo tak trzeba) (str.6 - datasheet)
	HAL_Delay(10);
	HAL_I2C_Mem_Write(hi2c, ADR, REG_CONF_12_15_, 1, data, 1, 100);  //konfiguracja max7300 pod adresem(0x80), porty P08-P011  jako OUTPUT (bo tak trzeba) (str.6 - datasheet)
	HAL_Delay(10);
	HAL_I2C_Mem_Write(hi2c, ADR, REG_CONF_16_19_, 1, data, 1, 100);  //konfiguracja max7300 pod adresem(0x80), porty P08-P011  jako OUTPUT (bo tak trzeba) (str.6 - datasheet)
	HAL_Delay(10);
	HAL_I2C_Mem_Write(hi2c, ADR, REG_CONF_20_23_, 1, data, 1, 100);  //konfiguracja max7300 pod adresem(0x80), porty P08-P011  jako OUTPUT (bo tak trzeba) (str.6 - datasheet)
	HAL_Delay(10);
	data[0]=0xAA;  //ustawienie pinów jako INPUTY (str.7 DS)
	HAL_I2C_Mem_Write(hi2c, ADR, REG_CONF_24_27_, 1, data, 1, 100);  //konfiguracja max7300 pod adresem(0x80), porty P08-P011  jako OUTPUT (bo tak trzeba) (str.6 - datasheet)
	HAL_Delay(10);
	HAL_I2C_Mem_Write(hi2c, ADR, REG_CONF_28_31_, 1, data, 1, 100);  //konfiguracja max7300 pod adresem(0x80), porty P08-P011  jako OUTPUT (bo tak trzeba) (str.6 - datasheet)
	HAL_Delay(10);
	return 0;
}

void MAX7300_write(I2C_HandleTypeDef *hi2c, int pin, int stan)
{
	if(pin<4 || pin>31)
	{
		return;  //zabezpieczenie przed błędem
	}
	uint16_t reg=0;
	reg=(32+pin); //obliczanie adresu (bo adresy zaczynają się od 0x24 dla pin 4, a 32 DEC to 24 HEX )
	data[0]=stan;
	HAL_I2C_Mem_Write(hi2c, ADR, reg, 1, data, 1, 100); //konfiguracja max7300 pod adresem(0x80),
	HAL_Delay(10);
}

uint8_t MAX7300_read(I2C_HandleTypeDef *hi2c, int pin)
{
	if(pin<4 || pin>31)
	{
		return;  //zabezpieczenie przed błędem
	}
	dane[0]=5;
	uint16_t reg=0;
	reg=(32+pin); //obliczanie adresu (bo adresy zaczynają się od 0x24 dla pin 4, a 32 DEC to 24 HEX )
	HAL_I2C_Mem_Read(hi2c, ADR, reg, 1, dane, 1, 100);
	HAL_Delay(200);
	return dane[0];
}
