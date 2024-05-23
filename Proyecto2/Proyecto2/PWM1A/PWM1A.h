/*
 * PWM1A.h
 *
 * Created: 4/29/2024 5:18:31 PM
 *  Author: Nico
 */ 


#ifndef PWM1A_H_
#define PWM1A_H_

#include <stdint.h>
#include <avr/io.h>

void init_PWM1A(int orientacion,int modo, int preescaler,uint16_t frecuency);
void init_PWM1B(int orientacion);
void duty_cycle1A(uint16_t duty);
void duty_cycle1B(uint16_t duty);

#endif /* PWM1A_H_ */