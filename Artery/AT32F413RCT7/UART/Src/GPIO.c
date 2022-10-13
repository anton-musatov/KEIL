#include "at32f413.h"                   // Device header

#include "GPIO.h"

void GPIOInit(void)
{
	CRM->apb2en_bit.gpiocen = 1;
	
	GPIOC->cfghr_bit.iofc13 = 0; 		//Сбрасываем биты в ноль
	GPIOC->cfghr_bit.iomc13 = 3; 	
	
}
