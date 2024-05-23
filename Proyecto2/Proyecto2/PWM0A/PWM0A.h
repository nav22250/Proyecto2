/*
 * PWM0A.h
 *
 * Created: 4/29/2024 5:03:23 PM
 *  Author: Nico
 */ 


#ifndef PWM0A_H_
#define PWM0A_H_

#include <avr/io.h>

void PWM0A_Init();
void PWM0A_SetDutyCycle(uint8_t duty_cycle);



#endif /* PWM0A_H_ */