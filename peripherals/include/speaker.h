#ifndef SPEAKER_H_
#define SPEAKER_H_

#define SPEAKER_PORT	PORTA
#define SPEAKER_PIN		PIN5_bm

void speaker_init();
void speaker_generate_tone(long frequency, long duration);

#endif /* SPEAKER_H_ */