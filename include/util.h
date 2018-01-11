#ifndef UTIL_H_
#define UTIL_H_

/* Music util */

void util_music_play(const int music[][2], int len);

enum util_music_composition {
	FREQUENCY,
	DURATION
};

/* LED/Button util */

int util_button_to_blinker(int button);

void util_mcu_self_destruction();

/* Watchdog timer, TODO: move to peripherals */

void wdt_on();
void wdt_off();

#endif /* UTIL_H_ */