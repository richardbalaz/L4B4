#include "include/mcu.h"
#include "include/game.h"
#include "include/util.h"

#include <util/delay.h>

#include <avr/pgmspace.h>

#include "peripherals/include/speaker.h"
#include "peripherals/include/led.h"
#include "peripherals/include/button.h"

/*
 * Play frequency durations out from speaker
 */
void util_music_play(const int music[][2], int len)
{
	for (int i = 0; i < len; i++) {
		int freq = pgm_read_word(&(music[i][FREQUENCY]));
		int dur = pgm_read_word(&(music[i][DURATION]));
		
		if (freq > 0) {
			_delay_ms(15);
			speaker_generate_tone(freq, dur);
		} else {
			for (int j = 0; j < (dur / 10); j++)
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
	
	return 0;
}

/*
 * Self-destruct the MCU
 */
void util_mcu_self_destruction()
{
	/* Request the access for protected I/O */
	CPU_CCP = CCP_IOREG_gc;
	
	/* Set timer to 8ms */
	WDT.CTRLA = WDT_PERIOD_8CLK_gc;
	
	/* Wait for death */
	while(1) {
		continue;
	}
}