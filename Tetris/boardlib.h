#ifndef LEFT_TOP

	#define LEFT_TOP 0
	#define MID_TOP 1
	#define RIGHT_TOP 2
	#define LEFT_MID 3
	#define MID_MID 4
	#define RIGHT_MID 5
	#define LEFT_BOT 6
	#define MID_BOT 7
	#define RIGHT_BOT 8
	#define BLINK 9
	
#endif

typedef uint8_t boolean;

void Init_board(void);

void read_keyboard(uint16_t count[], uint16_t speed);

/*

read_keyboard(count , speed);

讀取鍵盤 搭配巨集使用 speed建議設為delay的一倍

*/


boolean check_count(uint16_t count[], uint16_t bound, uint8_t index);




/*

check_count( count , bound , index );
count: 長度至少為10以上的陣列
bound: count的閥值 越高 check_count的頻率就越低
index: count的index 鍵盤和Blink已經定義在巨集

*/

boolean is_pressed(uint8_t dir);

uint16_t blink(uint16_t hex, uint16_t* blink_count, uint16_t speed);

/*

blink(hex, &count[INDEX], speed);
使得一個燈號閃爍
hex : 16位元無號數，用來代表RGB LED或者seg，請用內建的函式產生
blink_count : 一個記數值的位址
speed : 為閃爍的速度 推薦為總delay的一半
如果要同時閃爍 使用同一個blink_count 第二個之後speed設為0

*/

uint16_t new_seg_intToHex(int8_t num);

//輸入一個數字回傳seg的圖案 -1回傳空圖案

uint16_t new_LED_intToHex(int8_t num);

//輸入一個數字回傳LED的圖案 -1回傳空圖案

uint16_t new_RGB_intToHex(int8_t num);

//輸入一個數字回傳RGB的圖案 -1回傳空圖案

uint16_t new_RGB_charToHex(uint8_t c);

//輸入RGB來回傳RGB的圖案 大小寫皆可

uint16_t seg_pos(int8_t num);

//回傳tGPIO_C所使用的位置 -1回傳空位置 從左至右為0~3

uint16_t to_seg(uint16_t seg, uint8_t c, int16_t x);

//輸出修改過的seg，x必須要是一個有號數



void set_seg(uint16_t* seg, uint8_t c, int16_t x);

/*

將seg的第c個燈號(以英文表示)設為x
x為有號數

*/

void set_RGB(uint16_t* RGB , uint8_t c, int16_t x);

/*

將RGB的第c個燈號(以英文表示)設為x
x為有號數

*/

void set_LED(uint16_t* LED, uint8_t pos, int16_t x);

//同上 左到右0~3

void set_board_seg(uint16_t seg,uint8_t pos,uint32_t time);

// set_board_seg( seg , pos , time);

//將16位元無號數圖案seg設定到板子上 time為延遲

void set_board_all_seg(uint16_t seg[] , uint32_t time);

//set_board_all_seg(  seg[] , time);

//一次設定四個seg

void set_board_RGB(uint16_t RGB, uint32_t time);

// set_board_RGB(  RGB, time);


//設定RGB

void set_board_LED(uint16_t LED, uint32_t time);

// set_board_LED(LED, time);

//設定LED
