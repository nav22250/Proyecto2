//*****************************************************************************
//Universidad del Valle de Guatemala
//IE2023 Programacionde Microcontroladores
//Author : Nicole Navas
//Proyecto: Proyecto 2
//IDescripcion: Codigo de una cara robotica 
//Hardware: ATMega328P
//Created: 5/6/2024 10:08:47 PM
//Actualizado: 5/6/2024 10:08:47 PM
//*****************************************************************************
// Encabezado
//*****************************************************************************

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#define DEBOUNCE_DELAY_MS 50

#include "PWM0A/PWM0A.h"
#include "PWM0B/PWM0B.h"
#include "PWM1A/PWM1A.h"
#include "PWM1B/PWM1B.h"
#include "PWM2A/PWM2A.h"
#include "ADC/ADC.h"
#include "UART/UART.h"



volatile uint8_t modo = 0;
uint8_t guardar1 = 0;
uint8_t guardar2 = 0; 
uint8_t guardar3 = 0; 
uint8_t memoriaeeprom = 0;
volatile uint8_t PuertoADC=3;
volatile uint8_t valor=0;

int CharToInt(char num){
	return num - '0';
}

int unir(int n1, int n2, int n3){
	return n1*100+ n2*10 + n3;
}

uint16_t reescalar(uint8_t valor, uint8_t max_origen, uint16_t max_destino) {
	// Escalar el valor al rango 0 - max_destino
	uint16_t valor_reescalado = (float)valor / max_origen * max_destino;
	//INICIAR TIMER0 (DUTY CYCLE)
	return valor_reescalado;
}
void setup() {
	
	DDRC = 0; // Configurar del PC0 al PC7 como entradas

	PORTC |= (1 << DDC0) | (1 << DDC1) | (1 << DDC2); // Habilitar resistencias pull-up en PC0 y PC1
	
	DDRD |= (1 << DDD2)|(1 << DDD5)|(1 << DDD4); //Habilitar pines del PD2 al PD4 como salidas para LEDS
	DDRD |= (1 << DDD5)|(1 << DDD6); //Habilitar salidas para servos 
	DDRB |= (1 << DDB1)|(1 << DDB2)|(1 << DDB3);//Habilitar salidas para los demas servos

	PCICR |= (1 << PCIE1);
	PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10);
	

	sei(); // Habilitar interrupciones
}

void cambioADC (void){
	if (PuertoADC ==4){
		valor= readADC(4);
		uint16_t valor_reescalado = reescalar(valor, 255, 40);
		duty_cycle1A(valor_reescalado);
		PuertoADC++;
	}else if (PuertoADC ==5){
		valor=readADC(5);
		uint16_t valor_reescalado = reescalar(valor, 255, 40);
		duty_cycle1B(valor_reescalado);
		PuertoADC++;
	}else if (PuertoADC ==6){
		valor=readADC(6);
		uint16_t valor_reescalado = reescalar(valor, 255, 40);
		duty_cycle2A(valor_reescalado);
		PuertoADC++;
	}else if (PuertoADC ==7){
		valor=readADC(7);
		uint16_t valor_reescalado = reescalar(valor, 255, 40);
		duty_cycle2B(valor_reescalado);
		PuertoADC++;
	}else {
		PuertoADC =4;
	}
}

ISR(PCINT1_vect) {
	static uint8_t prev_state = 1;
	if (!(PINC & (1 << PC0))) { 
		modo++;
	}
	if (!(PINC & (1 << PC1))) {
		guardar2++;
		guardar1 = guardar2;
		geeprom();
	}
	if (!(PINC & (1 << PC2))) {
		guardar3++;
		switch (guardar3){
			case 1:
			memoriaeeprom = eeprom_read_byte((uint8_t*)0);
			duty_cycle1A(memoriaeeprom);
			memoriaeeprom = eeprom_read_byte((uint8_t*)1);
			duty_cycle1B(memoriaeeprom);
			memoriaeeprom = eeprom_read_byte((uint8_t*)2);
			duty_cycle2A(memoriaeeprom);
			memoriaeeprom = eeprom_read_byte((uint8_t*)3);
			duty_cycle2B(memoriaeeprom);
			break;
			
			case 2:
			memoriaeeprom = eeprom_read_byte((uint8_t*)5);
			duty_cycle1A(memoriaeeprom);
			memoriaeeprom = eeprom_read_byte((uint8_t*)6);
			duty_cycle1B(memoriaeeprom);
			memoriaeeprom = eeprom_read_byte((uint8_t*)7);
			duty_cycle2A(memoriaeeprom);
			memoriaeeprom = eeprom_read_byte((uint8_t*)8);
			duty_cycle2B(memoriaeeprom);
			break;
			
			case 3:
			memoriaeeprom = eeprom_read_byte((uint8_t*)10);
			duty_cycle1A(memoriaeeprom);
			memoriaeeprom = eeprom_read_byte((uint8_t*)11);
			duty_cycle1B(memoriaeeprom);
			memoriaeeprom = eeprom_read_byte((uint8_t*)12);
			duty_cycle2A(memoriaeeprom);
			memoriaeeprom = eeprom_read_byte((uint8_t*)13);
			duty_cycle2B(memoriaeeprom);
			break;
			
			case 4:
			memoriaeeprom = eeprom_read_byte((uint8_t*)15);
			duty_cycle1A(memoriaeeprom);
			memoriaeeprom = eeprom_read_byte((uint8_t*)16);
			duty_cycle1B(memoriaeeprom);
			memoriaeeprom = eeprom_read_byte((uint8_t*)17);
			duty_cycle2A(memoriaeeprom);
			memoriaeeprom = eeprom_read_byte((uint8_t*)18);
			duty_cycle2B(memoriaeeprom);
			break;
			
			case 5:
			guardar2=1;
			break;
		}
	}
}
void geeprom (void){
	if (guardar1 == 1) {
			valor= readADC(3);
			uint16_t valor_reescalado = reescalar(valor, 255, 40);
			eeprom_write_byte((uint8_t*)0, valor_reescalado);
			valor= readADC(4);
			 valor_reescalado = reescalar(valor, 255, 40);
			eeprom_write_byte((uint8_t*)1, valor_reescalado);
			valor= readADC(5);
			 valor_reescalado = reescalar(valor, 255, 40);
			eeprom_write_byte((uint8_t*)2, valor_reescalado);
			valor= readADC(6);
			 valor_reescalado = reescalar(valor, 255, 40);
			eeprom_write_byte((uint8_t*)3, valor_reescalado);
			guardar1=0;

	}
	
	if (guardar1 == 2) {

			valor= readADC(3);
			uint16_t valor_reescalado = reescalar(valor, 255, 40);
			eeprom_write_byte((uint8_t*)5, valor_reescalado);
			valor= readADC(4);
			 valor_reescalado = reescalar(valor, 255, 40);
			eeprom_write_byte((uint8_t*)6, valor_reescalado);
			valor= readADC(5);
			 valor_reescalado = reescalar(valor, 255, 40);
			eeprom_write_byte((uint8_t*)7, valor_reescalado);
			valor= readADC(6);
			 valor_reescalado = reescalar(valor, 255, 40);
			eeprom_write_byte((uint8_t*)8, valor_reescalado);
			guardar1=0;
		
	}
	
	if (guardar1 == 3) {
			valor= readADC(3);
			uint16_t valor_reescalado = reescalar(valor, 255, 40);
			eeprom_write_byte((uint8_t*)10, valor_reescalado);
			valor= readADC(4);
			 valor_reescalado = reescalar(valor, 255, 40);
			eeprom_write_byte((uint8_t*)11, valor_reescalado);
			valor= readADC(5);
			 valor_reescalado = reescalar(valor, 255, 40);
			eeprom_write_byte((uint8_t*)12, valor_reescalado);
			valor= readADC(6);
			 valor_reescalado = reescalar(valor, 255, 40);
			eeprom_write_byte((uint8_t*)13, valor_reescalado);
			guardar1=0;
		
	}
	
	if (guardar1 == 4) {
			valor= readADC(3);
			uint16_t valor_reescalado = reescalar(valor, 255, 40);
			eeprom_write_byte((uint8_t*)15, valor_reescalado);
			valor= readADC(4);
			 valor_reescalado = reescalar(valor, 255, 40);
			eeprom_write_byte((uint8_t*)16, valor_reescalado);
			valor= readADC(5);
			 valor_reescalado = reescalar(valor, 255, 40);
			eeprom_write_byte((uint8_t*)17, valor_reescalado);
			valor= readADC(6);
			 valor_reescalado = reescalar(valor, 255, 40);
			eeprom_write_byte((uint8_t*)18, valor_reescalado);
			guardar1=0;
			guardar2=0;
		
	}
}

int main(void)
{
	cli();
	setup();
	CLKPR = CLKPCE;
	CLKPR = CLKPS0;
	
	init_ADC(0,0,128);
	int top = 155;
	int preescaler=1024;
	init_PWM1A(0,6,preescaler, top);
	init_PWM1B(0);
	init_PWM2A(0, 3, preescaler);
	init_PWM2B(0);
	sei();
	
    while (1) {
	    // Control de modos
			if (modo == 0) {
		    PORTD = (1 << DDD2);
			cambioADC();
		    } else if (modo == 1) {
		    PORTD = (1 << DDD5);
			guardar3=0;
			
		    } else if (modo == 2) {
			char recibido1;
			char recibido2;
			char recibido3;
			
			int n1;
			int n2;
			int n3;
			uint16_t valor_reescalado;
			int num;
		    PORTD = (1 << DDD4);
			
			writeUART_car('1');
			recibido1=receivedChar();
			recibido2=receivedChar();
			recibido3=receivedChar();
			
			n1=CharToInt(recibido1);
			n2=CharToInt(recibido2);
			n3=CharToInt(recibido3);
			
			num= unir(n1,n2,n3);
			valor_reescalado = reescalar(num, 255, 40);
			duty_cycle1A(valor_reescalado);
			
			writeUART_car('2');
			recibido1=receivedChar();
			recibido2=receivedChar();
			recibido3=receivedChar();
			
			n1=CharToInt(recibido1);
			n2=CharToInt(recibido2);
			n3=CharToInt(recibido3);
			
			num= unir(n1,n2,n3);
			valor_reescalado = reescalar(num, 255, 40);
			duty_cycle1B(valor_reescalado);
			
			writeUART_car('3');
			recibido1=receivedChar();
			recibido2=receivedChar();
			recibido3=receivedChar();
			
			n1=CharToInt(recibido1);
			n2=CharToInt(recibido2);
			n3=CharToInt(recibido3);
			
			num= unir(n1,n2,n3);
			 valor_reescalado = reescalar(num, 255, 40);
			duty_cycle2A(valor_reescalado);
			
			writeUART_car('4');
			recibido1=receivedChar();
			recibido2=receivedChar();
			recibido3=receivedChar();
			
			n1=CharToInt(recibido1);
			n2=CharToInt(recibido2);
			n3=CharToInt(recibido3);
			
			num= unir(n1,n2,n3);
			 valor_reescalado = reescalar(num, 255, 40);
			duty_cycle2B(valor_reescalado);
	    } else if (modo >= 3) {
			modo=0;
		}
    }

    return 0;
}