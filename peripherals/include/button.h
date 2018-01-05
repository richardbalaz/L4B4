#include <avr/io.h>

#ifndef BUTTON_H_
#define BUTTON_H_

#define BUTTON_GREEN_PORT		PORTC
#define BUTTON_GREEN_INT_PORT	INT_PORTC
#define BUTTON_GREEN_PIN		PIN0_bm
#define BUTTON_GREEN_PIN_CTRL	PIN0CTRL

#define BUTTON_ORANGE_PORT		PORTB
#define BUTTON_ORANGE_INT_PORT	INT_PORTB
#define BUTTON_ORANGE_PIN		PIN2_bm
#define BUTTON_ORANGE_PIN_CTRL	PIN2CTRL

#define BUTTON_YELLOW_PORT		PORTC
#define BUTTON_YELLOW_INT_PORT	INT_PORTC
#define BUTTON_YELLOW_PIN		PIN1_bm
#define BUTTON_YELLOW_PIN_CTRL	PIN1CTRL

#define BUTTON_RED_PORT			PORTB
#define BUTTON_RED_INT_PORT		INT_PORTB
#define BUTTON_RED_PIN			PIN3_bm
#define BUTTON_RED_PIN_CTRL		PIN3CTRL

#define BUTTON_COUNT			4
#define BUTTON_BOUNCE_MS		10

enum buttons {
	BUTTON_GREEN,
	BUTTON_ORANGE,
	BUTTON_YELLOW,
	BUTTON_RED	
};

enum interrupt_ports {
	INT_PORTA,
	INT_PORTB,
	INT_PORTC
};

void button_init();
void button_interrupts_enable();
void button_interrupts_disable();

int button_is_pressed(int button);

void button_call_handler(int button);

#endif /* BUTTON_H_ */