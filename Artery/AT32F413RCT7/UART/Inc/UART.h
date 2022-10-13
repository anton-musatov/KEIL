#ifndef UART_H
#define UART_H

#define APM32F40X

#include "at32f413.h"                   // Device header

void InitUART(void);

void UART_tx(uint8_t * TXdata, uint8_t size);

#endif /*UART_H*/
