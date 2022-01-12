#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#define LEFT_MOTOR 4
#define RIGHT_MOTOR 1

#define TURN_TOLERANCE 20
#define ADVANCE_TOLERANCE 50

volatile unsigned short leftReading = 0;
volatile unsigned short rightReading = 0;


void set_ddr(){
	DDRB |= (1 << LEFT_MOTOR) | (1 << RIGHT_MOTOR); //configure as output
}

void set_adc(){
	//start with ADC3 selected (left side)
	ADMUX = (1 << ADLAR) | (1 << MUX1) | (1 << MUX0);
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS0);
}

void start_adc(){
	ADCSRA |= (1 << ADSC);
}


ISR(ADC_vect){

	if (ADMUX & (1 << MUX1)){
		leftReading = ADCH;
	}
	else {
		rightReading = ADCH;
	}

	if (abs(rightReading - leftReading) > TURN_TOLERANCE){
		if (rightReading < leftReading){
			PORTB = (1 << LEFT_MOTOR);
		}
		else// if (rightReading > leftReading)
		{
			PORTB = (1 << RIGHT_MOTOR);
		}
	}
	else if (rightReading > ADVANCE_TOLERANCE){
		PORTB = (1 << LEFT_MOTOR) | (1 << RIGHT_MOTOR);
	}

	else {
		PORTB = 0x00;
	}

	ADMUX = ADMUX ^ (1 << MUX1); // FLIP ADC CHANNEL

	start_adc();
}


int main(){
	set_ddr();
	set_adc();
	start_adc();
	sei();
	while(1){


	}

	return(0);
}

