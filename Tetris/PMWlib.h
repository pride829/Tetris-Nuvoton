#define MUSIC_START 0
#define MUSIC_STOP 3
#define MUSIC_LEVEL 0
#define MUSIC_SCALE 1
#define MUSIC_ACC 2

void PWM4_Freq(uint32_t PWM_frequency, uint8_t PWM_duty);

void InitPWM(void);

uint32_t toneToFreq( uint8_t level,uint8_t scale, uint8_t acc);

uint8_t search_music(uint8_t order, const uint8_t sheet[][3]);
