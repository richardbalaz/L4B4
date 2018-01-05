﻿#ifndef UTIL_H_
#define UTIL_H_

/* Music util */

void util_music_play(int music[][2], int len);

enum util_music_composition {
	FREQUENCY,
	DURATION
};

/* LED/Button util */

int util_button_to_blinker(int button);

#endif /* UTIL_H_ */