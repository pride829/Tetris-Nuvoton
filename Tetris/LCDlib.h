#include "stdint.h"
//�o�̤��ޥδN�����uint8_t �گu�������D������..

//�@�}�l�����I�s
void Initial_Lcd(void);


/*
draw(x, y, len, data_len, data_arr);
data_arr����ܥιϧ�  �O�@��unsigned char���}�C
����ץ�data_len �w�q

*/
void draw(uint8_t x,uint8_t y,uint8_t len,uint8_t data_len,unsigned char* data_arr);
//�o�̤@�}�l���uint8_t���w�q ����?


/*
double_draw�i�H�N��J����ƪ��׼W���@��
*/
void double_draw(uint8_t x,uint8_t y,uint8_t len,uint8_t data_len,unsigned char* data_arr);

/*
drawNumber(x, y, num);
��J�@��16�i��ƨõe�X
*/
void drawNumber(uint8_t x,uint8_t y,uint8_t num);

/*
drawSymbol(x, y, c);
��J�@�ӲŸ��õe�X
*/
void drawSymbol(uint8_t x,uint8_t y,uint8_t c);

/*

drawAlphabet(x, y, c);
��J�@�ӭ^��õe�X

*/

void drawAlphabet(uint8_t x,uint8_t y,uint8_t c);

/*

clear(x, y, len);
�H���׬�8���ťն񺡫��w���e��

*/

void clear(uint8_t x,uint8_t y,uint8_t len);


/*

imgNumber(num);
�^�Ǥ@�ӼƦr���Ϯ�

*/

unsigned char* imgNumber(uint8_t num);


/*

pointY(Y);
�^�Ǥ@�ӱN�e�����Φ�8����Y�I�Ҧb ��draw��k�ϥ�

*/

uint8_t pointY(uint8_t Y);

