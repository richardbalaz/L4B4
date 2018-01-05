#include "include/mcu.h"
#include "include/game.h"
#include "include/util.h"

#include <util/delay.h>

#include "peripherals/include/speaker.h"
#include "peripherals/include/led.h"
#include "peripherals/include/button.h"

/*
 * Play frequency durations out from speaker
 */
void util_music_play(int music[][2], int len)
{
	for (int i = 0; i < len; i++) {
		if (music[i][FREQUENCY] > 0) {
			speaker_generate_tone(music[i][FREQUENCY], music[i][DURATION]);
		} else {
			for (int j = 0; j < (music[i][DURATION] / 10); j++)
			_delay_ms(10);
		}
	}
}

/*
 * Convert button to it's blinker
 */
int util_button_to_blinker(int button)
{
	switch (button) {
		case BUTTON_GREEN:
			return BLINKER_GREEN;
		case BUTTON_ORANGE:
			return BLINKER_ORANGE;
		case BUTTON_YELLOW:
			return BLINKER_YELLOW;
		case BUTTON_RED:
			return BLINKER_RED;
	}
}