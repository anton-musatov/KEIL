#ifndef CAN_H
#define CAN_H

#include "at32f413.h"                   // Device header

void InitCAN(void);
void CAN_Transmit(uint32_t id, uint8_t* data);

#endif /*CAN_H*/
