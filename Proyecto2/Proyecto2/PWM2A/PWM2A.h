/*
 * PWM2A.h
 *
 * Created: 5/13/2024 5:28:16 PM
 *  Author: Nico
 */ 


#ifndef PWM2A_H_
#define PWM2A_H_

#include <stdint.h>
#include <avr/io.h>

void init_PWM2A(int orientacion,int modo, int preescaler);
void init_PWM2B(int orientacion);
void duty_cycle2A(uint8_t duty);
void duty_cycle2B(uint16_t duty);


#endif /* PWM2A_H_ */