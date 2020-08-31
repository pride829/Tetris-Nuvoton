#include "NUC1xx.h"
#include "boardlib.h"
#include "Driver\DrvSYS.h"
#include "scankey.h"


	
GPIO_T * tGPIO_A, * tGPIO_C, * tGPIO_E;

uint32_t u32Reg_temp;
uint32_t u32Reg; //讀取暫存器時須用PIN欄位 將暫存器位址 存到變數u32Reg中(0*0x40)代表GPA; // to read the rigister

uint16_t act[3]={0xfffb,0xfffd,0xfffe}; 

void Init_board(void){
	tGPIO_A = (GPIO_T *)((uint32_t)GPIOA + (0*0x40));
	tGPIO_C = (GPIO_T *)((uint32_t)GPIOA + (2*0x40));
	tGPIO_E = (GPIO_T *)((uint32_t)GPIOA + (4*0x40));
	u32Reg = (uint32_t)&GPIOA->PIN + (0*0x40);
}

void read_keyboard(uint16_t count[], uint16_t speed){
	
		//推薦的速度為delay的1倍
		//count的長度必須至少有9
		//因為沒有物件可以使用 請在boardlib.c和引用者中都加入用來表示方向的巨集
		//當按下對應按鍵 count的對應元素就會往上加

	  tGPIO_A->DOUT = act[0];
		u32Reg_temp=inpw(u32Reg);
			
		if((u32Reg_temp & 0x8) == 0)// 左上
			count[LEFT_TOP]+= speed;
		else count[LEFT_TOP] = 0;
		
		if((u32Reg_temp & 0x10) == 0) // 左中
			count[LEFT_MID] += speed;
		else count[LEFT_MID] = 0;
			
		if((u32Reg_temp & 0x20) == 0) // 左下
			count[LEFT_BOT] += speed;
		else count[LEFT_BOT] = 0;
		
		tGPIO_A->DOUT = act[1]; 
		u32Reg_temp=inpw(u32Reg);			
		
		if((u32Reg_temp & 0x8) == 0) // 中上
			count[MID_TOP] += speed;
		else count[MID_TOP] = 0;
			
		if((u32Reg_temp & 0x10) == 0) // 中中
			count[MID_MID] += speed;
		else count[MID_MID] = 0;
			
		if((u32Reg_temp & 0x20) == 0) // 中下
			count[MID_BOT] += speed;
		else count[MID_BOT] = 0;
			
		tGPIO_A->DOUT = act[2];
		u32Reg_temp=inpw(u32Reg);		
		
		if((u32Reg_temp & 0x8) == 0) // 右上
			count[RIGHT_TOP] += speed;
		else count[RIGHT_TOP] = 0;
		
		if((u32Reg_temp & 0x10) == 0) // 右中
			count[RIGHT_MID] += speed;
		else count[RIGHT_MID] = 0;
			
		if((u32Reg_temp & 0x20) == 0) // 右下
			count[RIGHT_BOT] += speed;
		else count[RIGHT_BOT] = 0;

}



boolean is_pressed(uint8_t dir){

	switch(dir){
		
		case LEFT_TOP:

			tGPIO_A->DOUT = act[0];
			u32Reg_temp=inpw(u32Reg);
			return ((u32Reg_temp & 0x8) == 0);
		
		case LEFT_MID:
			
			tGPIO_A->DOUT = act[0];
			u32Reg_temp=inpw(u32Reg);
			return ((u32Reg_temp & 0x10) == 0);
		
		case LEFT_BOT:
			
			tGPIO_A->DOUT = act[0];
			u32Reg_temp=inpw(u32Reg);
			return ((u32Reg_temp & 0x20) == 0);
		
		case MID_TOP:
			
			tGPIO_A->DOUT = act[1];
			u32Reg_temp=inpw(u32Reg);
			return ((u32Reg_temp & 0x8) == 0);
		
		case MID_MID:
			
			tGPIO_A->DOUT = act[1];
			u32Reg_temp=inpw(u32Reg);
			return ((u32Reg_temp & 0x10) == 0);	
		
		case MID_BOT:
			
			tGPIO_A->DOUT = act[1];
			u32Reg_temp=inpw(u32Reg);
			return ((u32Reg_temp & 0x20) == 0);
		
		case RIGHT_TOP:
			
			tGPIO_A->DOUT = act[2];
			u32Reg_temp=inpw(u32Reg);
			return ((u32Reg_temp & 0x8) == 0);

		case RIGHT_MID:
			
			tGPIO_A->DOUT = act[2];
			u32Reg_temp=inpw(u32Reg);
			return ((u32Reg_temp & 0x10) == 0);		
		
		case RIGHT_BOT:
				 
			tGPIO_A->DOUT = act[2];
			u32Reg_temp=inpw(u32Reg);
			return ((u32Reg_temp & 0x20) == 0);
		
		default:
			
			return 0;
	}

	
}


boolean check_count(uint16_t count[], uint16_t bound, uint8_t index){
	
	if(count[index] > bound){
		count[index] = 0;
		return 1;
	}
		return 0;
	
}

uint16_t blink(uint16_t hex, uint16_t* blink_count, uint16_t speed){
	//推薦的速度為delay的1/2倍
	//共用blink_count 每一個都會增加其速度 其他請設為0
	
	*blink_count += speed;
	
	if(*blink_count < 32768) return hex;
	else return 0xffff;
	
}






uint16_t new_seg_intToHex(int8_t num){
	/*
	uint8_t seg_intToHex(uint8_t num)
	num為欲轉換的整數 範圍從0~9 回傳一個8位元的16進位值 代表seg的圖案
	如果超出0~9則回傳空圖案
	*/

//凡seg一律都用16位元以免出錯

	switch(num){

		case 0: return 0xff82;
		case 1: return 0xffEE;
		case 2: return 0xff07;
		case 3: return 0xff46;
		case 4: return 0xff6A;
		case 5: return 0xff52;
		case 6: return 0xff12;
		case 7: return 0xffE2;
		case 8: return 0xff02;
		case 9: return 0xff62;
		case 10: return 0xff57;
	}

	return 0xffff;

}




uint16_t seg_pos(int8_t num){
	/*
	uint8_t seg_pos(uint8_t num)
	num代表seg的位置 從左至右分別為0~3
	回傳tGPIOC->DOUT所應assign的值
	註:tGPIC->DOUT的第15~12位元同時也是單色LED
	*/

//2的8次方表示到511?

	switch(num){

		case 0: return 0xff80;
		case 1: return 0xff40;
		case 2: return 0xff20;
		case 3: return 0xff10;

	}

	return 0xff00;
	
}

uint16_t new_LED_intToHex(int8_t num){


	switch(num){

		case 0: return 0xefff;
		case 1: return 0xdfff;
		case 2: return 0xbfff;
		case 3: return 0x7fff;
		case 4: return 0x0fff;
	}

	return 0xffff;
	
}

uint16_t new_RGB_intToHex(int8_t num){


	switch(num){

		case 0: return 0xbfff;
		case 1: return 0xdfff;
		case 2: return 0xefff;

	}

	return 0xffff;
	
}

uint16_t new_RGB_charToHex(uint8_t c){


	switch(c){

		case 'r': return 0xbfff;
		case 'R': return 0xbfff;
		case 'g': return 0xdfff;
		case 'G': return 0xdfff;
		case 'b': return 0xefff;
		case 'B': return 0xefff;
	}

	return 0xffff;
	
}

void set_seg(uint16_t* seg, uint8_t c, int16_t x){
	// void set_seg(uint16_t* seg, uint8_t c, int16_t x)

	// *seg為欲設定seg圖案的16位元無號數的指標
	// c為設定seg用的無號數char 可以是大小寫
	// x為想要設定的1或0 必須是有號16位數 如果是-1則反向
	// 點為p
	

	char c_table[] = {'c','p','f','a','b','d','e','g'};

	char big_c_table[] = {'C','P','F','A','B','D','E','G'};
	
	int i;
	
	for(i = 0;c_table[i] != c && i < 8;i++){}

	if(i == 8){
		
			for(i = 0;big_c_table[i] != c && i < 8;i++){}
		
			if(i == 8) return;
				
	}
		
	
	if(x == -1)
			(*seg) ^= (1 << i);
	else
		(*seg) ^= (-x ^ (*seg) ) & (1 << i);


}

uint16_t to_seg(uint16_t seg, uint8_t c, int16_t x){


	char c_table[] = {'c','p','f','a','b','d','e','g'};

	char big_c_table[] = {'C','P','F','A','B','D','E','G'};
	
	int i;
	
	for(i = 0;c_table[i] != c && i < 8;i++){}

	if(i == 8){
		
			for(i = 0;big_c_table[i] != c && i < 8;i++){}
		
			if(i == 8) return seg;
				
	}
		
	
	if(x == -1)
			(seg) ^= (1 << i);
	else
		(seg) ^= (-x ^ (seg) ) & (1 << i);

	return seg;
	
}

void set_RGB(uint16_t* RGB , uint8_t c, int16_t x){
	// *RGB為RGB圖案的指標 應設定在tGPIO_E->DOUT
	// c為"RGB" 大小寫皆可
	// x為燈號 -1為反向
	
	int i;
	
	switch(c){
		
		case 0:
			i = 14;
			break;
		case 1:
			i = 13;
			break;
		case 2:
			i = 12;
			break;
		case 'B':
			i = 12;
			break;
		case 'b':
			i = 12;
			break;
		case 'G':
			i = 13;
			break;
		case 'g':
			i = 13;
			break;
		case 'R':
			i = 14;
			break;
		case 'r':
			i = 14;
			break;
		default:
			i = 0;
			break;
	}
	
	if(i){
		
		if(x == -1)
			(*RGB) ^= (1 << i);
		else
			(*RGB) ^= (-x ^ (*RGB)) & (1 << i);
		
		
	}
	
	
	
}

void set_LED(uint16_t* LED, uint8_t pos, int16_t x){
	//*LED為LED的16位元無號數
	// pos為從左至右 0~3
	
	if(pos > 3) return;
	
	if(x == -1)
		(*LED) ^= (1 << 12 + pos);
	else
		(*LED) ^= (-x ^ (*LED)) & (1 << (12 + pos));
	
	
}

void set_board_seg(uint16_t seg,uint8_t pos,uint32_t time){
	//依序傳入tGPIO_C,tGPIO_E作為暫存器位址
	//seg 為seg圖案
	//pos 為seg的pos,-1為指向空位置
	//time為delay的時間
	//tGPIO_C必須用位元運算處理 不可影響到其他位元
	

	
	
	tGPIO_C->DOUT &= 0xff0f;
	
	tGPIO_C->DOUT |= seg_pos(-1) & 0x00f0;
	
	tGPIO_E->DOUT = seg;
	
	tGPIO_C->DOUT &= 0xff0f;
	
	tGPIO_C->DOUT |= seg_pos(pos) & 0x00f0;
	
	
	if(time == 0) time = 1;
	
	DrvSYS_Delay(time);
	
	
}

void set_board_all_seg(uint16_t seg[] , uint32_t time){

	int i;
	
	//time/= 4;
	
	for(i = 0;i < 4;i++){
	
		tGPIO_C->DOUT &= 0xff0f;
		
		tGPIO_C->DOUT |= seg_pos(-1) & 0x00f0;
		
		tGPIO_E->DOUT = seg[i];
		
		tGPIO_C->DOUT &= 0xff0f;
		
		tGPIO_C->DOUT |= seg_pos(i) & 0x00f0;
		
		DrvSYS_Delay(time);
	
	}
	
	
}

void set_board_RGB(uint16_t RGB, uint32_t time){
	//傳入tGPIO_A和RGB圖案和time
	
	tGPIO_A->DOUT &= 0x0fff;
	
	RGB &= 0xf000;
	
	tGPIO_A->DOUT |= RGB;
	
	if(time == 0) time = 1;
	
	DrvSYS_Delay(time);
	
}

void set_board_LED(uint16_t LED, uint32_t time){
	//傳入tGPIO_A和RGB圖案和time
	
	//tGPIO_C必須用位元運算處理 不可影響到其他位元
	
	tGPIO_C->DOUT &= 0x0fff;
	
	LED &= 0xf000;
	
	tGPIO_C->DOUT |= LED;
	
	if(time == 0) time = 1;
	
	DrvSYS_Delay(time);
	
}







