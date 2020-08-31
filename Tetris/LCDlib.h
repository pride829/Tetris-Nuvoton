#include "stdint.h"
//這裡不引用就不能用uint8_t 我真的不知道為什麼..

//一開始必須呼叫
void Initial_Lcd(void);


/*
draw(x, y, len, data_len, data_arr);
data_arr為顯示用圖形  是一個unsigned char的陣列
其長度由data_len 定義

*/
void draw(uint8_t x,uint8_t y,uint8_t len,uint8_t data_len,unsigned char* data_arr);
//這裡一開始顯示uint8_t未定義 為何?


/*
double_draw可以將輸入的資料長度增高一倍
*/
void double_draw(uint8_t x,uint8_t y,uint8_t len,uint8_t data_len,unsigned char* data_arr);

/*
drawNumber(x, y, num);
輸入一個16進位數並畫出
*/
void drawNumber(uint8_t x,uint8_t y,uint8_t num);

/*
drawSymbol(x, y, c);
輸入一個符號並畫出
*/
void drawSymbol(uint8_t x,uint8_t y,uint8_t c);

/*

drawAlphabet(x, y, c);
輸入一個英文並畫出

*/

void drawAlphabet(uint8_t x,uint8_t y,uint8_t c);

/*

clear(x, y, len);
以高度為8的空白填滿指定的畫面

*/

void clear(uint8_t x,uint8_t y,uint8_t len);


/*

imgNumber(num);
回傳一個數字的圖案

*/

unsigned char* imgNumber(uint8_t num);


/*

pointY(Y);
回傳一個將畫面切割成8塊的Y點所在 給draw方法使用

*/

uint8_t pointY(uint8_t Y);

