/*
 * main.c
 *
 *  Created on: Jul 19, 2024
 *      Author: ahmed  waleed
 */

#include "LIB\STD_TYPES.h"
#include "LIB\BIT_MATH.h"

#include "MCAL\GPIO\GPIO_private.h"
#include "MCAL\GPIO\GPIO_interface.h"
#include "MCAL\EXTI\EXTI_interface.h"
#include "MCAL\GIE\GIE_interface.h"
#include "MCAL\TIMER\TIMER_private.h"
#include "MCAL\TIMER\TIMER_interface.h"
#include "HAL\SSD\SSD_interface.h"
#include "HAL\LED\LED_interface.h"

u16 sw_counter = 0;
u16 sw_counter2 = 0;
u16 LED_co = 0;
u8 stopwatchdigits[6];
u8 LAPdigits[6];

LED_Type led = { PORTD_ID, PIN0_ID, ACTIVE_HIGH };

SSD_Type ssd1 = { SSD_COMMON_CATHODE, SSD_DECODER, PORTC_ID, PORTA_ID, PIN0_ID,
		SSD_LOW_NIBBLE };
SSD_Type ssd2 = { SSD_COMMON_CATHODE, SSD_DECODER, PORTC_ID, PORTA_ID, PIN1_ID,
		SSD_LOW_NIBBLE };
SSD_Type ssd3 = { SSD_COMMON_CATHODE, SSD_DECODER, PORTC_ID, PORTA_ID, PIN2_ID,
		SSD_LOW_NIBBLE };
SSD_Type ssd4 = { SSD_COMMON_CATHODE, SSD_DECODER, PORTC_ID, PORTA_ID, PIN3_ID,
		SSD_LOW_NIBBLE };
SSD_Type ssd5 = { SSD_COMMON_CATHODE, SSD_DECODER, PORTC_ID, PORTA_ID, PIN4_ID,
		SSD_LOW_NIBBLE };
SSD_Type ssd6 = { SSD_COMMON_CATHODE, SSD_DECODER, PORTC_ID, PORTA_ID, PIN5_ID,
		SSD_LOW_NIBBLE };

SSD_Type ssd11 = { SSD_COMMON_CATHODE, SSD_DECODER, PORTC_ID, PORTA_ID, PIN0_ID,
		SSD_HIGH_NIBBLE };
SSD_Type ssd22 = { SSD_COMMON_CATHODE, SSD_DECODER, PORTC_ID, PORTA_ID, PIN1_ID,
		SSD_HIGH_NIBBLE };
SSD_Type ssd33 = { SSD_COMMON_CATHODE, SSD_DECODER, PORTC_ID, PORTA_ID, PIN2_ID,
		SSD_HIGH_NIBBLE };
SSD_Type ssd44 = { SSD_COMMON_CATHODE, SSD_DECODER, PORTC_ID, PORTA_ID, PIN3_ID,
		SSD_HIGH_NIBBLE };
SSD_Type ssd55 = { SSD_COMMON_CATHODE, SSD_DECODER, PORTC_ID, PORTA_ID, PIN4_ID,
		SSD_HIGH_NIBBLE };
SSD_Type ssd66 = { SSD_COMMON_CATHODE, SSD_DECODER, PORTC_ID, PORTA_ID, PIN5_ID,
		SSD_HIGH_NIBBLE };

void StopWatch() {
	stopwatchdigits[0]++;
	if (stopwatchdigits[0] == 10) {
		stopwatchdigits[0] = 0;
		stopwatchdigits[1]++;
		if (stopwatchdigits[1] == 10) {
			stopwatchdigits[1] = 0;
			stopwatchdigits[2]++;
		}
	}
	if (stopwatchdigits[2] == 10) {
		stopwatchdigits[2] = 0;
		stopwatchdigits[3]++;
		if (stopwatchdigits[3] == 6) {
			stopwatchdigits[3] = 0;
			stopwatchdigits[4]++;
		}
	}
	if (stopwatchdigits[4] == 10) {
		stopwatchdigits[4] = 0;
		stopwatchdigits[5]++;
		if (stopwatchdigits[5] == 6) {
			stopwatchdigits[0] = 0;
			stopwatchdigits[1] = 0;
			stopwatchdigits[2] = 0;
			stopwatchdigits[3] = 0;
			stopwatchdigits[4] = 0;
			stopwatchdigits[5] = 0;
		}
	}
}

void ISR_TIMER0() {
	sw_counter++;
	LED_co++;
	if (sw_counter == 10) {
		StopWatch();
		sw_counter = 0;
	}
	if (LED_co == 500) {
		LED_Off(led);
		LED_co = 0;
	}
	TIMER0_SetCTC(122);
}
void ISR_TIMER2()
{
	PORTA = ~(1 << sw_counter2);
	SSD_SendNumber(ssd5, stopwatchdigits[sw_counter2]);
	SSD_SendNumber(ssd55, LAPdigits[sw_counter2]);
	sw_counter2++;
	if (sw_counter2 == 6)
		sw_counter2 = 0;

	TIMER2_SetCTC(250);

	if (sw_counter2 > 1 && sw_counter2 % 2 == 1)
		GPIO_SetPinValue(PORTD_ID, PIN1_ID, LOGIC_HIGH);
	else
		GPIO_SetPinValue(PORTD_ID, PIN1_ID, LOGIC_LOW);
}

void ISR_INT1() {
	TOG_BIT(TIMSK, TIMSK_OCIE0);
}
void ISR_INT2()
{
	if (RED_BIT(TIMSK , TIMSK_OCIE0) == 0)
	{
		stopwatchdigits[0] = 0;
		stopwatchdigits[1] = 0;
		stopwatchdigits[2] = 0;
		stopwatchdigits[3] = 0;
		stopwatchdigits[4] = 0;
		stopwatchdigits[5] = 0;
		LAPdigits[0] = 0;
		LAPdigits[1] = 0;
		LAPdigits[2] = 0;
		LAPdigits[3] = 0;
		LAPdigits[4] = 0;
		LAPdigits[5] = 0;
	}
	else
	{
		LED_On(led);
		LED_co = 0;
		LAPdigits[0] = stopwatchdigits[0];
		LAPdigits[1] = stopwatchdigits[1];
		LAPdigits[2] = stopwatchdigits[2];
		LAPdigits[3] = stopwatchdigits[3];
		LAPdigits[4] = stopwatchdigits[4];
		LAPdigits[5] = stopwatchdigits[5];

	}
}

int main() {
	GPIO_SetPortDirection(PORTA_ID, PORT_OUTPUT);
	GPIO_SetPinDirection(PORTD_ID, PIN1_ID, PIN_OUTPUT);

	LED_Init(led);
	LED_Off(led);

	SSD_Init(ssd1);
	SSD_Init(ssd2);
	SSD_Init(ssd3);
	SSD_Init(ssd4);
	SSD_Init(ssd5);
	SSD_Init(ssd6);
	SSD_Init(ssd11);
	SSD_Init(ssd22);
	SSD_Init(ssd33);
	SSD_Init(ssd44);
	SSD_Init(ssd55);
	SSD_Init(ssd66);

	EXTI1_Init();
	EXTI1_Enable();
	EXTI1_SetCallBack(ISR_INT1);

	EXTI2_Init();
	EXTI2_Enable();
	EXTI2_SetCallBack(ISR_INT2);

	TIMER_SetCallBack(ISR_TIMER0, TIMER0_CTC_VECTOR_ID);
	TIMER_SetCallBack(ISR_TIMER2, TIMER2_CTC_VECTOR_ID);

	TIMER0_Init();
	TIMER2_Init();
	TIMER0_DisableINT();

	GIE_Enable();

	while (1) {

	}
	return 0;
}
