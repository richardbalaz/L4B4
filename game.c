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

int blinker_sequence[HARD_ROUND_COUNT];
int button_sequence[HARD_ROUND_COUNT];
int sequence_ptr;

int starting_buttons_state[BUTTON_COUNT];

/*
 * Start a new game
 */
void game_start(int difficulty)
{
	button_interrupts_disable();
	
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
	game_running = RUNNING;
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
	
	//free(blinker_sequence);		
	//blinker_sequence = (int *) malloc(round_count);
	
	led_counter_set(game_score);
	
	game_generate_sequence(blinker_sequence, round_count);
	
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
	button_interrupts_disable();
	
	_delay_ms(1000);
	
	round_current++;

	//button_sequence = (int *) realloc(button_sequence, round_current);
	sequence_ptr = 0;

	game_blink_sequence(blinker_sequence, round_current);		
		
	util_music_play(song_new_round, SONG_NEW_ROUND_LEN);

	button_interrupts_enable();
}

/*
 * End the game as winning
 */
void game_end_win()
{
	util_music_play(song_la_la_land, SONG_LA_LA_LAND_LEN);
}

/*
 * End the game as loss
 */
void game_end_over()
{
	util_music_play(song_game_over, SONG_GAME_OVER_LEN);
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

	led_blinker_turn_on(util_button_to_blinker(button));
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

	led_blinker_turn_off(util_button_to_blinker(button));
	
	/* Add button to sequence */
	button_sequence[sequence_ptr] = button;

	/* Check if correct button was released */
	if (button_sequence[sequence_ptr] == blinker_sequence[sequence_ptr]) {
		sequence_ptr++;
				
		/* Check if all buttons were pressed and released in this round */
		if (sequence_ptr == round_current) {
			game_score++;
			led_counter_set(game_score);
			
			/* Check if all rounds were passed */
			if (round_current == round_count) {
				//button_interrupts_disable();
				game_end_win();
				return;
			} else {
				game_next_round();
			}
		} else
			return;		
	} else {
		/* Released button doesn't match the blinker sequence - game over */
		game_end_over();
		return;		
	}
}