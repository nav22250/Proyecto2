/*
 * PWM1B.h
 *
 * Created: 4/29/2024 5:39:20 PM
 *  Author: Nico
 */ 


#ifndef PWM1B_H_
#define PWM1B_H_

#include <stdint.h>
#include <avr/io.h>

void PWM1B_Init();
void PWM1B_set_duty_cycle(uint8_t duty_cycle);



#endif /* PWM1B_H_ */