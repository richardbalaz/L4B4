#include "include/mcu.h"
#include "include/game.h"
#include "include/music.h"

#include <util/delay.h>

#include "peripherals/include/speaker.h"

void music_play(int music[][2], int len)
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
