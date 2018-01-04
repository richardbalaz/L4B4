#include "include/speaker.h"

#include "../include/mcu.h"

#include <avr/io.h>
#include <util/delay.h>

/*
 * Initialize output pins for counters and blinkers
 */
void speaker_init()
{
	SPEAKER_PORT.DIRSET = SPEAKER_PIN;
	SPEAKER_PORT.OUTCLR = SPEAKER_PIN;
}

/*
 * Play frequency at specified duration in milliseconds
 * This function is I/O blocking
 */
void speaker_generate_tone(long frequency, long duration)
{
	long period_us = 1000000L / frequency;
	long elapsed_us = 0L;
	long half_period_wait = 149000L / frequency;
	
	while(elapsed_us < (duration * 1000L)) {
		SPEAKER_PORT.OUTSET = SPEAKER_PIN;
		
		for (long i = 0L; i < half_period_wait; i++)
		{
			_NOP();
		}
		
		SPEAKER_PORT.OUTCLR = SPEAKER_PIN;
		
		for (long i = 0L; i < half_period_wait; i++)
		{
			_NOP();
		}
		
		elapsed_us += period_us;
	}
	
}