/*
 * TIMER_program.c
 *
 *  Created on: Jul 29, 2024
 *      Author: ahmed  waleed
 */
#include"..\..\LIB\STD_TYPES.h"
#include"..\..\LIB\BIT_MATH.h"
#include "TIMER_private.h"
#include"TIMER_config.h"
#include"TIMER_interface.h"

static void (*TIMERS_CallBackFunc[16])(void) = {NULL} ;  /* we have 8 interrupt sources in timer  */

void TIMER0_Init(void) {
#if TIMER0_WAVEFORM_GENERATION_MODE == TIMER_NORMAL_MODE
	/*initialize Ovf mode*/
	CLR_BIT(TCCR0, TCCR0_WGM00);
	CLR_BIT(TCCR0, TCCR0_WGM01);
	/*Preload value*/
	TCNT0 = TIMER0_PRELOAD_VAL;
	/*Timer0 OVF Interrupt Enable*/
#if TIMER0_OVERFLOW_INTERRUPT == DISABLE
	CLR_BIT(TIMSK, TIMSK_TOIE0);
#elif TIMER0_OVERFLOW_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_TOIE0);
#endif

#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_PWM_MODE

#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_CTC_MODE
	/*initialize CTC mode*/
	CLR_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);
	/*Set the Required CTC Value*/
	OCR0 = TIMER0_CTC_VAL;
	/*Timer0 Compare Match Interrupt Enable*/
#if TIMER0_CTC_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_OCIE0);
#elif TIMER0_CTC_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_OCIE0);
#endif

#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_FAST_PWM_MODE

#endif
	/*Set the Required Prescaler*/
	TCCR0 &= TIMER_PRESCALER_MASK ;
	TCCR0 |= TIMER0_PRESCALER ;
}
void TIMER0_EnableINT(void) {
	SET_BIT(TIMSK , TIMSK_OCIE0);
}
void TIMER0_DisableINT(void){
	CLR_BIT(TIMSK , TIMSK_OCIE0);
}
void TIMER0_SetPreload(u8 Copy_Preload) {
	TCNT0=Copy_Preload;
}
void TIMER0_SetCTC(u8 Copy_CTC) {
	OCR0=Copy_CTC;

}
u8 TIMER0_GetTimerCounterValue(void) {
	return TCNT0;
}

void TIMER2_Init(void)
{
		#if TIMER2_WAVEFORM_GENERATION_MODE == TIMER_NORMAL_MODE

			/*Initialize Waveform Generation Mode as Normal Mode*/
			CLR_BIT(TCCR2 , TCCR2_WGM20) ;
			CLR_BIT(TCCR2 , TCCR2_WGM21) ;

			/*Set the Required Preload Value*/
			TCNT2 = TIMER2_PRELOAD_VAL ;

			/*Timer2 Overflow Interrupt Enable*/
			#if TIMER2_OVERFLOW_INTERRUPT == DISABLE
				CLR_BIT(TIMSK , TIMSK_TOIE2) ;
			#elif TIMER2_OVERFLOW_INTERRUPT == ENABLE
				SET_BIT(TIMSK , TIMSK_TOIE2) ;
			#endif

		#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_PWM_MODE

		#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_CTC_MODE

			/*Initialize Waveform Generation Mode as CTC Mode*/
			CLR_BIT(TCCR2 , TCCR2_WGM20) ;
			SET_BIT(TCCR2 , TCCR2_WGM21) ;

			/*Set the Required CTC Value*/
			OCR2 = TIMER2_CTC_VAL ;

			/*Timer2 Compare Match Interrupt Enable*/
			#if TIMER2_CTC_INTERRUPT == DISABLE
				CLR_BIT(TIMSK , TIMSK_OCIE2) ;
			#elif TIMER2_CTC_INTERRUPT == ENABLE
				SET_BIT(TIMSK , TIMSK_OCIE2) ;
			#endif

		#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_FAST_PWM_MODE


		#endif

	/*Set the Required Prescaler*/
	TCCR2 &= TIMER_PRESCALER_MASK ;
	TCCR2 |= TIMER2_PRESCALER ;
}
void TIMER2_EnableINT(void) {
	SET_BIT(TIMSK , TIMSK_OCIE2) ;
}
void TIMER2_DisableINT(void){
	CLR_BIT(TIMSK , TIMSK_OCIE2) ;
}
void TIMER2_SetPreload(u8 Copy_Preload) {
	TCNT2=Copy_Preload;
}
void TIMER2_SetCTC(u8 Copy_CTC) {
	OCR2=Copy_CTC;

}
u8 TIMER2_GetTimerCounterValue(void) {
	return TCNT2;
}




void TIMER_SetCallBack(void (*Copy_CallBackFunc)(void) , u8 Copy_VectorID)
{

	if (Copy_CallBackFunc != NULL)
	{
		TIMERS_CallBackFunc[Copy_VectorID] = Copy_CallBackFunc ;
	}

}
/*TIMER0 Normal Mode ISR*/
void __vector_11 (void)		__attribute__((signal)) ;
void __vector_11 (void)
{
	if (TIMERS_CallBackFunc[TIMER0_OVF_VECTOR_ID] != NULL)
	{
		TIMERS_CallBackFunc[TIMER0_OVF_VECTOR_ID]() ;
	}
}

/*TIMER0 CTC Mode ISR*/
void __vector_10 (void)		__attribute__((signal)) ;
void __vector_10 (void)
{
	if (TIMERS_CallBackFunc[TIMER0_CTC_VECTOR_ID] != NULL)
	{
		TIMERS_CallBackFunc[TIMER0_CTC_VECTOR_ID]() ;
	}
}

/*TIMER2 Normal Mode ISR*/
void __vector_5 (void)		__attribute__((signal)) ;
void __vector_5 (void)
{
	if (TIMERS_CallBackFunc[TIMER2_OVF_VECTOR_ID] != NULL)
	{
		TIMERS_CallBackFunc[TIMER2_OVF_VECTOR_ID]() ;
	}
}

/*TIMER2 CTC Mode ISR*/
void __vector_4 (void)		__attribute__((signal)) ;
void __vector_4 (void)
{
	if (TIMERS_CallBackFunc[TIMER2_CTC_VECTOR_ID] != NULL)
	{
		TIMERS_CallBackFunc[TIMER2_CTC_VECTOR_ID]() ;
	}
}
