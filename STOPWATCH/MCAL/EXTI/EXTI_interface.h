/*
 * EXTI_interface.h
 *
 *  Created on: Jul 19, 2024
 *      Author: ahmed  waleed
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define 	 EXTI_LOW_LEVEL			0
#define 	 EXTI_ON_CHANGE			1
#define 	 EXTI_FALLING_EDGE  	2
#define 	 EXTI_RISING_EDGE		3

#define 	 EXTI2_FALLING_EDGE  	0
#define 	 EXTI2_RISING_EDGE		1

void EXTI0_Init();
void EXTI1_Init();
void EXTI2_Init();

void EXTI0_SetSignalSenseMode(u8 Copy_SenseMode);
void EXTI1_SetSignalSenseMode(u8 Copy_SenseMode);
void EXTI2_SetSignalSenseMode(u8 Copy_SenseMode);

void EXTI0_Enable();
void EXTI0_Disable();

void EXTI1_Enable();
void EXTI1_Disable();

void EXTI2_Enable();
void EXTI2_Disable();

void EXTI0_ClearFlag();
void EXTI1_ClearFlag();
void EXTI2_ClearFlag();

void EXTI0_SetCallBack       ( void (*Copy_CallBack)(void) );
void EXTI1_SetCallBack       ( void (*Copy_CallBack)(void) );
void EXTI2_SetCallBack       ( void (*Copy_CallBack)(void) );

#endif /* EXTI_INTERFACE_H_ */
