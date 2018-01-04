#ifndef MUSIC_H_
#define MUSIC_H_

void music_play(int music[][2], int len);

enum music_composition {
	FREQUENCY,
	DURATION	
};

#endif /* MUSIC_H_ */