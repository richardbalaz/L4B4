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
		if(game_is_running() == NOT_RUNNING) {
			int start_status = game_is_ready_to_start();
			
			if (start_status == NOT_READY)
				continue;
				
			_delay_ms(BUTTON_START_TIMEOUT);
			
			if (start_status == game_is_ready_to_start())
				game_start(start_status);
		}
		
	}

}
