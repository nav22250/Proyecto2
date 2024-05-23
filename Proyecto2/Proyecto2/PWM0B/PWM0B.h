/*
 * PWM0B.h
 *
 * Created: 4/29/2024 5:09:31 PM
 *  Author: Nico
 */ 


#ifndef PWM0B_H_
#define PWM0B_H_

#include <avr/io.h>

void PWM0B_Init();
void PWM0B_SetDutyCycle(uint8_t duty_cycle);



#endif /* PWM0B_H_ */