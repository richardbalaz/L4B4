#include "include/led.h"

/*
 * Initialize output pins for counters and blinkers
 */
void led_init()
{
	/* Set as output pin */
	COUNTER_1_PORT.DIRSET = COUNTER_1_PIN;
	COUNTER_2_PORT.DIRSET = COUNTER_2_PIN;
	COUNTER_4_PORT.DIRSET = COUNTER_4_PIN;
	COUNTER_8_PORT.DIRSET = COUNTER_8_PIN;
	
	/* Write digital low */
	COUNTER_1_PORT.OUTCLR = COUNTER_1_PIN;
	COUNTER_2_PORT.OUTCLR = COUNTER_2_PIN;
	COUNTER_4_PORT.OUTCLR = COUNTER_4_PIN;
	COUNTER_8_PORT.OUTCLR = COUNTER_8_PIN;

	/* Set as output pin */
	BLINKER_GREEN_PORT.DIRSET = BLINKER_GREEN_PIN;
	BLINKER_ORANGE_PORT.DIRSET = BLINKER_ORANGE_PIN;
	BLINKER_YELLOW_PORT.DIRSET = BLINKER_YELLOW_PIN;
	BLINKER_RED_PORT.DIRSET = BLINKER_RED_PIN;

	/* Write digital low */
	BLINKER_GREEN_PORT.OUTCLR = BLINKER_GREEN_PIN;
	BLINKER_ORANGE_PORT.OUTCLR = BLINKER_ORANGE_PIN;
	BLINKER_YELLOW_PORT.OUTCLR = BLINKER_YELLOW_PIN;
	BLINKER_RED_PORT.OUTCLR = BLINKER_RED_PIN;
}

/*
 * Turn the specific 'counter' LED on
 */
void led_counter_turn_on(int counter)
{
	switch (counter) {
		case COUNTER_1: {
			COUNTER_1_PORT.OUTSET = COUNTER_1_PIN;
			break;
		}
		case COUNTER_2: {
			COUNTER_2_PORT.OUTSET = COUNTER_2_PIN;
			break;
		}
		case COUNTER_4: {
			COUNTER_4_PORT.OUTSET = COUNTER_4_PIN;
			break;				
		}
		case COUNTER_8: {
			COUNTER_8_PORT.OUTSET = COUNTER_8_PIN;
			break;
		}
	}
}

/*
 * Toggle the specific 'counter' LED
 */
void led_counter_toggle(int counter)
{
	switch (counter) {
		case COUNTER_1: {
			COUNTER_1_PORT.OUTTGL = COUNTER_1_PIN;
			break;
		}
		case COUNTER_2: {
			COUNTER_2_PORT.OUTTGL = COUNTER_2_PIN;
			break;
		}
		case COUNTER_4: {
			COUNTER_4_PORT.OUTTGL = COUNTER_4_PIN;
			break;				
		}
		case COUNTER_8: {
			COUNTER_8_PORT.OUTTGL = COUNTER_8_PIN;
			break;
		}
	}
}

/*
 * Turn the specific 'counter' LED off
 */
void led_counter_turn_off(int counter)
{
	switch (counter) {
		case COUNTER_1: {
			COUNTER_1_PORT.OUTCLR = COUNTER_1_PIN;
			break;
		}
		case COUNTER_2: {
			COUNTER_2_PORT.OUTCLR = COUNTER_2_PIN;
			break;
		}
		case COUNTER_4: {
			COUNTER_4_PORT.OUTCLR = COUNTER_4_PIN;
			break;				
		}
		case COUNTER_8: {
			COUNTER_8_PORT.OUTCLR = COUNTER_8_PIN;
			break;
		}
	}
}

/*
 * Set counter LEDs to number in binary (0-15)
 */
void led_counter_set(uint8_t number)
{
	if (number & (1 << 0)) {
		led_counter_turn_on(COUNTER_1);
	} else {
		led_counter_turn_off(COUNTER_1);
	}

	if (number & (1 << 1)) {
		led_counter_turn_on(COUNTER_2);
	} else {
		led_counter_turn_off(COUNTER_2);
	}

	if (number & (1 << 2)) {
		led_counter_turn_on(COUNTER_4);
	} else {
		led_counter_turn_off(COUNTER_4);
	}

	if (number & (1 << 3)) {
		led_counter_turn_on(COUNTER_8);
	} else {
		led_counter_turn_off(COUNTER_8);
	}
}

/*
 * Turn the specific 'blinker' LED on
 */
void led_blinker_turn_on(int blinker)
{
	switch (blinker) {
		case BLINKER_GREEN: {
			BLINKER_GREEN_PORT.OUTSET = BLINKER_GREEN_PIN;
			break;
		}
		case BLINKER_ORANGE: {
			BLINKER_ORANGE_PORT.OUTSET = BLINKER_ORANGE_PIN;
			break;
		}
		case BLINKER_YELLOW: {
			BLINKER_YELLOW_PORT.OUTSET = BLINKER_YELLOW_PIN;
			break;				
		}
		case BLINKER_RED: {
			BLINKER_RED_PORT.OUTSET = BLINKER_RED_PIN;
			break;
		}
	}
}

/*
 * Turn the specific 'blinker' LED off
 */
void led_blinker_turn_off(int blinker)
{
	switch (blinker) {
		case BLINKER_GREEN: {
			BLINKER_GREEN_PORT.OUTCLR = BLINKER_GREEN_PIN;
			break;
		}
		case BLINKER_ORANGE: {
			BLINKER_ORANGE_PORT.OUTCLR = BLINKER_ORANGE_PIN;
			break;
		}
		case BLINKER_YELLOW: {
			BLINKER_YELLOW_PORT.OUTCLR = BLINKER_YELLOW_PIN;
			break;
		}
		case BLINKER_RED: {
			BLINKER_RED_PORT.OUTCLR = BLINKER_RED_PIN;
			break;
		}
	}
}