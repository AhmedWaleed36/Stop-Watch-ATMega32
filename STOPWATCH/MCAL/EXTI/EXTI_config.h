/*
 * EXTI_config.h
 *
 *  Created on: Jul 19, 2024
 *      Author: ahmed  waleed
 */

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

/*
 Options :-

 	 1-EXTI_LOW_LEVEL
 	 2-EXTI_ON_CHANGE
 	 3-EXTI_FALLING_EDGE
 	 4-EXTI_RISING_EDGE

 */

#define EXTI0_SENSE_MODE  EXTI_RISING_EDGE



#define EXTI1_SENSE_MODE  EXTI_RISING_EDGE

/*
 Options :-

 	 1-EXTI_FALLING_EDGE
 	 2-EXTI_RISING_EDGE


 */


#define EXTI2_SENSE_MODE  EXTI2_RISING_EDGE


#endif /* EXTI_CONFIG_H_ */
