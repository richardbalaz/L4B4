#ifndef SONGS_H_
#define SONGS_H_

#define SONG_NEW_ROUND_LEN 9
int song_new_round[SONG_NEW_ROUND_LEN][2] = {
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

#define SONG_GAME_OVER_LEN 9
int song_game_over[SONG_GAME_OVER_LEN][2] = {
	{233, 500},
	{184, 500},
	{155, 500},
	{116, 1200},
};

#define SONG_LA_LA_LAND_LEN 15
int song_la_la_land[SONG_LA_LA_LAND_LEN][2] = {
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

#endif /* SONGS_H_ */