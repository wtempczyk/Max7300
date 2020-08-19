/*
 * max7300.h
 *
 *  Created on: 17 lip 2020
 *      Author: Wojciech Tempczyk
 *
 *"THE BEER-WARE LICENSE" :
 * As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return W.T. ;)
 */

#ifndef MAX7300_MAX7300_H_
#define MAX7300_MAX7300_H_

#include "main.h"


int MAX7300_init(I2C_HandleTypeDef *hi2c);
void MAX7300_write(I2C_HandleTypeDef *hi2c, int pin, int stan);
uint8_t MAX7300_read(I2C_HandleTypeDef *hi2c, int pin);

#endif /* MAX7300_MAX7300_H_ */
