#include "../peripherals/include/button.h"

#ifndef GAME_H_
#define GAME_H_

#define EASY_STARTING_BUTTON_1	BUTTON_YELLOW
#define EASY_STARTING_BUTTON_2	BUTTON_RED

#define HARD_STARTING_BUTTON_1	BUTTON_GREEN
#define HARD_STARTING_BUTTON_2	BUTTON_ORANGE

#define EASY_ROUND_COUNT	8
#define HARD_ROUND_COUNT	16

#define BUTTON_START_TIMEOUT 2000

void game_start(int difficulty);
void game_next_round();
void game_generate_sequence(int *sequence, int len);
void game_blink_sequence(int *sequence, int len);
void game_end_win();
void game_end_over();
int game_is_running();
int game_is_ready_to_start();

enum game_status {
	NOT_RUNNING,
	RUNNING,
	WON,
	GAME_OVER
};

enum game_difficulty {
	EASY,
	HARD,
};


enum game_start_status {
	READY_EASY,
	READY_HARD,
	NOT_READY
};

void button_pressed(int button);
void button_released(int button);

#endif /* GAME_H_ */