/*
 * PWM1B.c
 *
 * Created: 4/29/2024 5:39:46 PM
 *  Author: Nico
 */ 
#include "PWM1B.h"

void PWM1B_Init() {
	// Configuración del modo de funcionamiento PWM1 (Fast PWM, non-inverted mode)
	/*TCCR1A = 0;
	TCCR1B = 0;*/
	TCCR1A |=(1 << COM1B1); // Configura el modo de PWM y habilita la salida no invertida en OC1B (PB2)
	/*/TCCR1A |= (1<<WGM12)|(1<<WGM11);
	TCCR1B |= (1<<WGM13)|(1<<CS12);*/

	DDRB |= (1 << DDB2);// Configuración del pin PB2 (OC1B) como salida

	/*ICR1 = 0x9B;*/
}

void PWM1B_set_duty_cycle(uint8_t duty_cycle) {
	// Se establece el ciclo de trabajo (OCR1B) del PWM1
	OCR1B = duty_cycle;
}
