#include "include/mcu.h"
#include "include/game.h"
#include "include/util.h"
#include "include/songs.h"

#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "peripherals/include/led.h"
#include "peripherals/include/button.h"
#include "peripherals/include/speaker.h"
#include "peripherals/include/eeprom.h"

int game_running = NOT_RUNNING;
int game_difficulty;
int game_score;

int round_current;
int round_count;

int *led_sequence;
int *button_sequence;

int starting_buttons_state[BUTTON_COUNT];

/*
 * Start a new game
 */
void game_start(int difficulty)
{
	cli();
	
	/* Set seed for rand session */
	srand(eeprom_get_next_seed());
	
	/* Intro score blinking */
	for (int i = 0; i < 3; i++) {
		led_counter_set(15);
		_delay_ms(600);
		led_counter_set(0);
		_delay_ms(600);
	}
	
	/* Reset variables */
	game_score = 0;
	round_current = 0;
	
	game_difficulty = difficulty;

	switch (difficulty) {
		case EASY:
			round_count = EASY_ROUND_COUNT;
			break;
		case HARD:
			round_count = HARD_ROUND_COUNT;
			break;			
	}
	
	free(led_sequence);
	free(button_sequence);
	
	led_sequence = (int *) malloc(round_count);
	button_sequence = (int *) malloc(round_count);
	
	led_counter_set(game_score);
	
	game_running = RUNNING;
	
	game_next_round();
	
	while(1) {
		
	}
	
	// sleep ??
}

/*
 * Return whether the game is running
 */
int game_is_running()
{
	return (game_running == RUNNING);
}

/*
 * Return whether the game is ready to start
 */
int game_is_ready_to_start()
{
	if (starting_buttons_state[EASY_STARTING_BUTTON_1] 
	    && starting_buttons_state[EASY_STARTING_BUTTON_2]) {
		return READY_EASY;
	} else if (starting_buttons_state[HARD_STARTING_BUTTON_1]
			   && starting_buttons_state[HARD_STARTING_BUTTON_2]) {
		return READY_HARD;			   
	}
	
	return NOT_READY;
}

/*
 * Generate and blink out next round
 */
void game_next_round()
{
	cli();
	
	_delay_ms(1000);
	
	round_current++;
	
	game_generate_sequence(led_sequence, round_current);
	game_blink_sequence(led_sequence, round_current);		
		
	util_music_play(song_new_game, SONG_NEW_GAME_LEN);
		
	sei();
}

/*
 * Generates random sequence of buttons to sequence array
 */
void game_generate_sequence(int *sequence, int len)
{
	for (int i = 0; i < len; i++)
		sequence[i] = rand() % BUTTON_COUNT;
}

/*
 * Blink the sequence out to LEDs
 */
void game_blink_sequence(int *sequence, int len)
{
	for (int i = 0; i < len; i++) {
		led_blinker_turn_on(sequence[i]);
		_delay_ms(750);
		led_blinker_turn_off(sequence[i]);
		_delay_ms(750);
	}
}

/*
 * Automatically called handler after button pressing
 */
void button_pressed(int button)
{
	if (!game_is_running()) {
		starting_buttons_state[button] = 1;		
		return;
	}
}

/*
 * Automatically called handler after button releasing
 */
void button_released(int button)
{
	if (!game_is_running()) {
		starting_buttons_state[button] = 0;
		return;
	}
}