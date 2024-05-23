/*
 * PWM0B.c
 *
 * Created: 4/29/2024 5:09:46 PM
 *  Author: Nico
 */ 
#include "PWM0B.h"

void PWM0B_Init() {
	DDRD |= (1 << PD5);         // Configurar PD5 (OC0B) como salida

	// Configuración del Timer0 para PWM
	TCCR0A |= (1 << COM0B1); // Modo PWM rápido, no inversor
	TCCR0B |= (1 << CS00);      // Sin prescaler
}

void PWM0B_SetDutyCycle(uint8_t duty_cycle) {
	OCR0B = duty_cycle;
}