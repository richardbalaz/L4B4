#include <avr/io.h>

#ifndef LED_H_
#define LED_H_

/* MCU's port-pin definition for counters */
#define COUNTER_1_PORT	PORTA
#define COUNTER_1_PIN	PIN6_bm

#define COUNTER_2_PORT	PORTA
#define COUNTER_2_PIN	PIN7_bm
 
#define COUNTER_4_PORT	PORTA
#define COUNTER_4_PIN	PIN1_bm
 
#define COUNTER_8_PORT	PORTA
#define COUNTER_8_PIN	PIN2_bm

/* MCU's port-pin definition for blinkers */
#define BLINKER_GREEN_PORT	PORTA
#define BLINKER_GREEN_PIN	PIN3_bm

#define BLINKER_ORANGE_PORT	PORTA
#define BLINKER_ORANGE_PIN	PIN4_bm

#define BLINKER_YELLOW_PORT	PORTB
#define BLINKER_YELLOW_PIN	PIN0_bm

#define BLINKER_RED_PORT	PORTB
#define BLINKER_RED_PIN		PIN1_bm

/* Specific counter LED */
enum counter {
	COUNTER_1,
	COUNTER_2,
	COUNTER_4,
	COUNTER_8
};

/* Specific blinker LED */
enum blinker {
	BLINKER_GREEN,
	BLINKER_ORANGE,
	BLINKER_YELLOW,
	BLINKER_RED
};

void led_init();

void led_counter_turn_on(int counter);
void led_counter_turn_off(int counter);
void led_counter_toggle(int counter);
void led_counter_set(uint8_t number);

void led_blinker_turn_on(int blinker);
void led_blinker_turn_off(int blinker);

#endif /* LED_H_ */