/*
 * Debug.h
 *
 *  Created on: Dec 7, 2021
 *      Author: maxlell
 * Usage:
 * You need to make sure that the New Line character is transmitted
 * at the end, otherwise the Terminal only prints out the string of
 * characters, once its buffer is filled up
 */

#ifndef PRINTF_H
#define PRINTF_H

#include <stdio.h>
#include "main.h"

#define SERIAL_COM
// #define SWV_TRACE

#ifdef SERIAL_COM
#include "usart.h"

void Printf_SetUartPort(UART_HandleTypeDef *huart);
#endif

int _write(int file, char *ptr, int len);

#endif /* PRINTF_H */
