#ifndef MUSIC_SONGS_H_
#define MUSIC_SONGS_H_

#define MUSIC_NEW_GAME_LEN 9
int music_new_game[MUSIC_NEW_GAME_LEN][2] = {
	{261, 250},
	{349, 125},
	{440, 125},
	{523, 125},
	{0, 125},
	{440, 125},
	{0, 125},
	{0, 250},
	{523, 125},
};

#define MUSIC_LA_LA_LAND_LEN 15
int music_la_la_land[MUSIC_LA_LA_LAND_LEN][2] = {
	{277, 350},
	{369, 350},
	{415, 350},
	{440, 350},
	{415, 350},
	{369, 350},
	{293, 800},
	{0, 350},
	{293, 350},
	{369, 350},
	{415, 350},
	{440, 350},
	{415, 350},
	{369, 350},
	{277, 800},
};

#endif /* MUSIC_SONGS_H_ */