#include "../include/mcu.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "include/button.h"
#include "include/led.h"

/* Function pointers for button event */
void (*button_pressed_handler)(int);
void (*button_released_handler)(int);

/*
 * Initialize input pins for buttons and enable pull-ups
 */
void button_init(void (*button_event_pressed_handler)(int),
				 void (*button_event_released_handler)(int))
{
	/* Set as input pin */
	BUTTON_GREEN_PORT.DIRCLR = BUTTON_GREEN_PIN;
	BUTTON_ORANGE_PORT.DIRCLR = BUTTON_ORANGE_PIN;
	BUTTON_YELLOW_PORT.DIRCLR = BUTTON_YELLOW_PIN;
	BUTTON_RED_PORT.DIRCLR = BUTTON_RED_PIN;
	
	/* Enable pull-up and interrupt */
	BUTTON_GREEN_PORT.BUTTON_GREEN_PIN_CTRL = PORT_ISC_BOTHEDGES_gc | PORT_PULLUPEN_bm;
	BUTTON_ORANGE_PORT.BUTTON_ORANGE_PIN_CTRL = PORT_ISC_BOTHEDGES_gc | PORT_PULLUPEN_bm;
	BUTTON_YELLOW_PORT.BUTTON_YELLOW_PIN_CTRL = PORT_ISC_BOTHEDGES_gc | PORT_PULLUPEN_bm;
	BUTTON_RED_PORT.BUTTON_RED_PIN_CTRL = PORT_ISC_BOTHEDGES_gc | PORT_PULLUPEN_bm;

	button_pressed_handler = button_event_pressed_handler;
	button_released_handler = button_event_released_handler;
	
	/* Enable global interrupts */
	sei();
	
}

/*
 * Enable hardware interrupts for buttons
 */
void button_interrupts_enable()
{
	BUTTON_GREEN_PORT.BUTTON_GREEN_PIN_CTRL |= PORT_ISC_BOTHEDGES_gc;
	BUTTON_ORANGE_PORT.BUTTON_ORANGE_PIN_CTRL |= PORT_ISC_BOTHEDGES_gc;
	BUTTON_YELLOW_PORT.BUTTON_YELLOW_PIN_CTRL |= PORT_ISC_BOTHEDGES_gc;
	BUTTON_RED_PORT.BUTTON_RED_PIN_CTRL |= PORT_ISC_BOTHEDGES_gc;	
}

/*
 * Disable hardware interrupts for buttons
 */
void button_interrupts_disable()
{
	BUTTON_GREEN_PORT.BUTTON_GREEN_PIN_CTRL &= ~(PORT_ISC_BOTHEDGES_gc);
	BUTTON_ORANGE_PORT.BUTTON_ORANGE_PIN_CTRL &= ~(PORT_ISC_BOTHEDGES_gc);
	BUTTON_YELLOW_PORT.BUTTON_YELLOW_PIN_CTRL &= ~(PORT_ISC_BOTHEDGES_gc);
	BUTTON_RED_PORT.BUTTON_RED_PIN_CTRL &= ~(PORT_ISC_BOTHEDGES_gc);
}

/*
 * Return 1 if 'button' is pressed or 0 if released
 */
int button_is_pressed(int button)
{
	switch (button) {
		case BUTTON_GREEN: {
			if (!(BUTTON_GREEN_PORT.IN & BUTTON_GREEN_PIN))
				return 1;
			break;
		}
		case BUTTON_ORANGE: {
			if (!(BUTTON_ORANGE_PORT.IN & BUTTON_ORANGE_PIN))
				return 1;
			break;
		}
		case BUTTON_YELLOW: {
			if (!(BUTTON_YELLOW_PORT.IN & BUTTON_YELLOW_PIN))
				return 1;
			break;
		}
		case BUTTON_RED: {
			if (!(BUTTON_RED_PORT.IN & BUTTON_RED_PIN))
				return 1;
			break;
		}
	}
		
	return 0;
}

/*
 * Call handler for button event
 */
void button_call_handler(int button)
{
	/* Button debounce */
	_delay_ms(BUTTON_BOUNCE_MS);
	
	if (button_is_pressed(button)) {
		(*button_pressed_handler)(button);
	} else {
		(*button_released_handler)(button);
	}
}

/*
 * Interrupt service routine for PORTA
 */
ISR(PORTA_PORT_vect)
{
	#if BUTTON_GREEN_INT_PORT == INT_PORTA
	if (PORTA.INTFLAGS & BUTTON_GREEN_PIN) {
		button_call_handler(BUTTON_GREEN);
	}
	#endif
	#if BUTTON_ORANGE_INT_PORT == INT_PORTA
	if (PORTA.INTFLAGS & BUTTON_ORANGE_PIN) {
		button_call_handler(BUTTON_ORANGE);
	}
	#endif
	#if BUTTON_YELLOW_INT_PORT == INT_PORTA
	if (PORTA.INTFLAGS & BUTTON_YELLOW_PIN) {
		button_call_handler(BUTTON_YELLOW);
	}
	#endif
	#if BUTTON_RED_INT_PORT == INT_PORTA
	if (PORTA.INTFLAGS & BUTTON_RED_PIN) {
		button_call_handler(BUTTON_RED);
	}
	#endif
	
	/* Clear interrupt flag, so the next one can occur */
	PORTA.INTFLAGS = 0xff;
}

/*
 * Interrupt service routine for PORTB 
 */
ISR(PORTB_PORT_vect)
{
	#if BUTTON_GREEN_INT_PORT == INT_PORTB
	if (PORTB.INTFLAGS & BUTTON_GREEN_PIN) {
		button_call_handler(BUTTON_GREEN);
	}
	#endif
	#if BUTTON_ORANGE_INT_PORT == INT_PORTB
	if (PORTB.INTFLAGS & BUTTON_ORANGE_PIN) {
		button_call_handler(BUTTON_ORANGE);
	}
	#endif
	#if BUTTON_YELLOW_INT_PORT == INT_PORTB
	if (PORTB.INTFLAGS & BUTTON_YELLOW_PIN) {
		button_call_handler(BUTTON_YELLOW);
	}
	#endif
	#if BUTTON_RED_INT_PORT == INT_PORTB
	if (PORTB.INTFLAGS & BUTTON_RED_PIN) {
		button_call_handler(BUTTON_RED);
	}
	#endif	
	
	/* Clear interrupt flag, so the next one can occur */
	PORTB.INTFLAGS = 0xff;
}

/*
 * Interrupt service routine for PORTC
 */
ISR(PORTC_PORT_vect)
{
	#if BUTTON_GREEN_INT_PORT == INT_PORTC
	if (PORTC.INTFLAGS & BUTTON_GREEN_PIN) {
		button_call_handler(BUTTON_GREEN);
	}
	#endif
	#if BUTTON_ORANGE_INT_PORT == INT_PORTC
	if (PORTC.INTFLAGS & BUTTON_ORANGE_PIN) {
		button_call_handler(BUTTON_ORANGE);
	}
	#endif
	#if BUTTON_YELLOW_INT_PORT == INT_PORTC
	if (PORTC.INTFLAGS & BUTTON_YELLOW_PIN) {
		button_call_handler(BUTTON_YELLOW);
	}
	#endif
	#if BUTTON_RED_INT_PORT == INT_PORTC
	if (PORTC.INTFLAGS & BUTTON_RED_PIN) {
		button_call_handler(BUTTON_RED);
	}
	#endif

	/* Clear interrupt flag, so the next one can occur */
	PORTC.INTFLAGS = 0xff;
}