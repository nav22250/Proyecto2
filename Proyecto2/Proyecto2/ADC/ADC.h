/*
 * ADC.h
 *
 * Created: 4/29/2024 5:06:19 PM
 *  Author: Nico
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void init_ADC(int referencia,int justificacion,int preescaler);
uint8_t readADC(int canal);



#endif /* ADC_H_ */