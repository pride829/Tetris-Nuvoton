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

Ū����L �f�t�����ϥ� speed��ĳ�]��delay���@��

*/


boolean check_count(uint16_t count[], uint16_t bound, uint8_t index);




/*

check_count( count , bound , index );
count: ���צܤ֬�10�H�W���}�C
bound: count���֭� �V�� check_count���W�v�N�V�C
index: count��index ��L�MBlink�w�g�w�q�b����

*/

boolean is_pressed(uint8_t dir);

uint16_t blink(uint16_t hex, uint16_t* blink_count, uint16_t speed);

/*

blink(hex, &count[INDEX], speed);
�ϱo�@�ӿO���{�{
hex : 16�줸�L���ơA�ΨӥN��RGB LED�Ϊ�seg�A�ХΤ��ت��禡����
blink_count : �@�ӰO�ƭȪ���}
speed : ���{�{���t�� ���ˬ��`delay���@�b
�p�G�n�P�ɰ{�{ �ϥΦP�@��blink_count �ĤG�Ӥ���speed�]��0

*/

uint16_t new_seg_intToHex(int8_t num);

//��J�@�ӼƦr�^��seg���Ϯ� -1�^�ǪŹϮ�

uint16_t new_LED_intToHex(int8_t num);

//��J�@�ӼƦr�^��LED���Ϯ� -1�^�ǪŹϮ�

uint16_t new_RGB_intToHex(int8_t num);

//��J�@�ӼƦr�^��RGB���Ϯ� -1�^�ǪŹϮ�

uint16_t new_RGB_charToHex(uint8_t c);

//��JRGB�Ӧ^��RGB���Ϯ� �j�p�g�ҥi

uint16_t seg_pos(int8_t num);

//�^��tGPIO_C�ҨϥΪ���m -1�^�ǪŦ�m �q���ܥk��0~3

uint16_t to_seg(uint16_t seg, uint8_t c, int16_t x);

//��X�ק�L��seg�Ax�����n�O�@�Ӧ�����



void set_seg(uint16_t* seg, uint8_t c, int16_t x);

/*

�Nseg����c�ӿO��(�H�^����)�]��x
x��������

*/

void set_RGB(uint16_t* RGB , uint8_t c, int16_t x);

/*

�NRGB����c�ӿO��(�H�^����)�]��x
x��������

*/

void set_LED(uint16_t* LED, uint8_t pos, int16_t x);

//�P�W ����k0~3

void set_board_seg(uint16_t seg,uint8_t pos,uint32_t time);

// set_board_seg( seg , pos , time);

//�N16�줸�L���ƹϮ�seg�]�w��O�l�W time������

void set_board_all_seg(uint16_t seg[] , uint32_t time);

//set_board_all_seg(  seg[] , time);

//�@���]�w�|��seg

void set_board_RGB(uint16_t RGB, uint32_t time);

// set_board_RGB(  RGB, time);


//�]�wRGB

void set_board_LED(uint16_t LED, uint32_t time);

// set_board_LED(LED, time);

//�]�wLED
