/*
 * EXTI_program.c
 *
 *  Created on: Jul 19, 2024
 *      Author: ahmed  waleed
 */
#include "..\..\LIB\STD_TYPES.h"
#include "..\..\LIB\BIT_MATH.h"

#include "EXTI_config.h"
#include "EXTI_private.h"
#include "EXTI_interface.h"

void (*EXTI0_CallBack)(void) = NULL;
void (*EXTI1_CallBack)(void) = NULL;
void (*EXTI2_CallBack)(void) = NULL;

void EXTI0_Init() {
#if  EXTI0_SENSE_MODE == EXTI_LOW_LEVEL
	CLR_BIT(MCUCR, 0);
	CLR_BIT(MCUCR, 1);
#elif	EXTI0_SENSE_MODE == EXTI_ON_CHANGE
	SET_BIT(MCUCR,0);
	CLR_BIT(MCUCR,1);
#elif	EXTI0_SENSE_MODE == EXTI_FALLING_EDGE
	CLR_BIT(MCUCR, 0);
	SET_BIT(MCUCR, 1);
#elif	EXTI0_SENSE_MODE == EXTI_RISING_EDGE
	SET_BIT(MCUCR,0);
	SET_BIT(MCUCR,1);
#endif

	CLR_BIT(GICR, 6);
	SET_BIT(GIFR, 6);
}

void EXTI1_Init() {
#if  EXTI1_SENSE_MODE == EXTI_LOW_LEVEL
	CLR_BIT(MCUCR, 2);
	CLR_BIT(MCUCR, 3);
#elif	EXTI1_SENSE_MODE == EXTI_ON_CHANGE
	SET_BIT(MCUCR,2);
	CLR_BIT(MCUCR,3);
#elif	EXTI1_SENSE_MODE == EXTI_FALLING_EDGE
	CLR_BIT(MCUCR,2);
	SET_BIT(MCUCR,3);
#elif	EXTI1_SENSE_MODE == EXTI_RISING_EDGE
	SET_BIT(MCUCR, 2);
	SET_BIT(MCUCR, 3);
#endif
	CLR_BIT(GICR, 7);
	SET_BIT(GIFR, 7);
}

void EXTI2_Init() {
#if	EXTI2_SENSE_MODE == EXTI2_FALLING_EDGE
	CLR_BIT(MCUCSR, 6);
#elif	EXTI2_SENSE_MODE == EXTI2_RISING_EDGE
	SET_BIT(MCUCSR, 6);
#endif
	CLR_BIT(GICR, 5);
	SET_BIT(GIFR, 5);
}

void EXTI0_SetSignalSenseMode(u8 Copy_SenseMode) {
	switch (Copy_SenseMode) {
	case EXTI_LOW_LEVEL:
		CLR_BIT(MCUCR, 0);
		CLR_BIT(MCUCR, 1);
		break;
	case EXTI_ON_CHANGE:
		SET_BIT(MCUCR, 0);
		CLR_BIT(MCUCR, 1);
		break;
	case EXTI_FALLING_EDGE:
		CLR_BIT(MCUCR, 0);
		SET_BIT(MCUCR, 1);
		break;
	case EXTI_RISING_EDGE:
		SET_BIT(MCUCR, 0);
		SET_BIT(MCUCR, 1);
		break;

	}
}
void EXTI1_SetSignalSenseMode(u8 Copy_SenseMode) {
	switch (Copy_SenseMode) {
	case EXTI_LOW_LEVEL:
		CLR_BIT(MCUCR, 2);
		CLR_BIT(MCUCR, 3);
		break;
	case EXTI_ON_CHANGE:
		SET_BIT(MCUCR, 2);
		CLR_BIT(MCUCR, 3);
		break;
	case EXTI_FALLING_EDGE:
		CLR_BIT(MCUCR, 2);
		SET_BIT(MCUCR, 3);
		break;
	case EXTI_RISING_EDGE:
		SET_BIT(MCUCR, 2);
		SET_BIT(MCUCR, 3);
		break;

	}
}
void EXTI2_SetSignalSenseMode(u8 Copy_SenseMode) {
	switch (Copy_SenseMode) {
	case EXTI_FALLING_EDGE:
		CLR_BIT(MCUCSR, 6);
		break;
	case EXTI_RISING_EDGE:
		SET_BIT(MCUCSR, 6);
		break;

	}
}

void EXTI0_Enable() {
	SET_BIT(GICR, 6);
}
void EXTI0_Disable() {
	CLR_BIT(GICR, 6);
}

void EXTI1_Enable() {
	SET_BIT(GICR, 7);
}
void EXTI1_Disable() {
	CLR_BIT(GICR, 7);
}

void EXTI2_Enable() {
	SET_BIT(GICR, 5);
}
void EXTI2_Disable() {
	CLR_BIT(GICR, 5);
}

void EXTI0_ClearFlag() {
	SET_BIT(GIFR, 6);
}
void EXTI1_ClearFlag() {
	SET_BIT(GIFR, 7);
}
void EXTI2_ClearFlag() {
	SET_BIT(GIFR, 5);
}

void EXTI0_SetCallBack(void (*Copy_CallBack)(void)) {
	if (Copy_CallBack != NULL)
		EXTI0_CallBack = Copy_CallBack;
}
void EXTI1_SetCallBack(void (*Copy_CallBack)(void)) {
	if (Copy_CallBack != NULL)
		EXTI1_CallBack = Copy_CallBack;
}
void EXTI2_SetCallBack(void (*Copy_CallBack)(void)) {
	if (Copy_CallBack != NULL)
		EXTI2_CallBack = Copy_CallBack;
}

void __vector_1(void) __attribute__((signal,used));
void __vector_1(void) {
	if (EXTI0_CallBack != NULL) {
		EXTI0_CallBack();
		EXTI0_ClearFlag();
	}
}

void __vector_2(void) __attribute__((signal,used));
void __vector_2(void) {
	if (EXTI1_CallBack != NULL) {
		EXTI1_CallBack();
		EXTI1_ClearFlag();
	}
}

void __vector_3(void) __attribute__((signal,used));
void __vector_3(void) {
	if (EXTI2_CallBack != NULL) {
		EXTI2_CallBack();
		EXTI2_ClearFlag();
	}
}
