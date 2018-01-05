#include "include/mcu.h"
#include "include/game.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "peripherals/include/led.h"
#include "peripherals/include/button.h"
#include "peripherals/include/speaker.h"

/*
 * Setup hardware peripherals
 */
void setup()
{
	led_init();
	speaker_init();
	button_init(&button_pressed, &button_released);
}

/*
 * Main function called upon reset
 */
int main(void)
{
	setup();

	while (1) {	
		if(!game_is_running()) {
			int start_status = game_is_ready_to_start();
			
			if (start_status == NOT_READY)
				continue;
				
			_delay_ms(BUTTON_START_TIMEOUT);
			
			/* Check if start status is ready even after timeout */
			if (start_status == game_is_ready_to_start()) {
				switch (start_status) {
					case READY_EASY:
						game_start(EASY);
						break;
					case READY_HARD:
						game_start(HARD);
						break;
				}
			}
		}		
	}

}
