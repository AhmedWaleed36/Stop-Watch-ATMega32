/*
 * TIMER_interface.h
 *
 *  Created on: Jul 29, 2024
 *      Author: ahmed  waleed
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_


/* Define indexes for the global pointer to func for ISR  */

#define TIMER0_OVF_VECTOR_ID		11
#define TIMER0_CTC_VECTOR_ID		10
#define TIMER1_OVF_VECTOR_ID		9
#define TIMER1_CTCB_VECTOR_ID		8
#define TIMER1_CTCA_VECTOR_ID		7
#define TIMER1_ICU_VECTOR_ID		6
#define TIMER2_OVF_VECTOR_ID		5
#define TIMER2_CTC_VECTOR_ID		4

void TIMER0_Init(void) ;
void TIMER0_EnableINT(void) ;
void TIMER0_DisableINT(void) ;
void TIMER0_SetPreload (u8 Copy_Preload) ;
void TIMER0_SetCTC (u8 Copy_CTC) ;
u8   TIMER0_GetTimerCounterValue (void) ;

void TIMER2_Init(void) ;
void TIMER2_EnableINT(void) ;
void TIMER2_DisableINT(void) ;
void TIMER2_SetPreload (u8 Copy_Preload) ;
void TIMER2_SetCTC (u8 Copy_CTC) ;
u8   TIMER2_GetTimerCounterValue (void) ;


void TIMER_SetCallBack(void (*Copy_CallBackFunc)(void) , u8 Copy_VectorID);
#endif /* TIMER_INTERFACE_H_ */
