#include "../peripherals/include/button.h"

#ifndef GAME_H_
#define GAME_H_

#define STARTING_BUTTON_1	BUTTON_YELLOW
#define STARTING_BUTTON_2	BUTTON_RED

#define ROUND_COUNT 16

void game_start();
void game_next_round();
void game_generate_sequence(int *sequence, int len);
void game_blink_sequence(int *sequence, int len);
int game_is_running();
int game_is_ready_to_start();

enum game_status {
	NOT_RUNNING,
	RUNNING,
	WON,
	GAME_OVER	
};

void button_pressed(int button);
void button_released(int button);

#endif /* GAME_H_ */