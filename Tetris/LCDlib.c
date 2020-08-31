#include "LCDlib.h"
#include "Driver\DrvSYS.h"
#include "NUC1xx.h"
#include "LCD_Driver.h"
#include "scankey.h"
#include "string.h"

unsigned char DisplayBuf [8*128];
extern  SPI_T * SPI_PORT[4]={SPI0, SPI3, SPI2, SPI3};


//數字的圖形
unsigned char number[][8] ={
		0x00,0x7e,0xc3,0xc3,0xc3,0xc3,0x7e,0x00,//0
		0x00,0xc4,0xc6,0xff,0xff,0xc0,0xc0,0x00,//1
		0x00,0xe4,0xf2,0xfb,0xdf,0xce,0xc0,0x00,//2
		0x00,0x42,0x89,0x89,0x8b,0x4e,0x30,0x00,//3
		0x30,0x28,0x26,0x23,0xff,0x20,0x20,0x00,//4
		0x00,0x8f,0x89,0x89,0x89,0x71,0x00,0x00,//5
		0x3c,0x7e,0xd3,0x89,0x8c,0x8c,0xf8,0x70,//6
		0x00,0x0f,0x01,0x01,0x01,0xff,0x00,0x00,//7
		0x00,0xff,0x91,0x91,0x91,0x91,0xff,0x00,//8
		0x00,0x0f,0x09,0x09,0x09,0xff,0x00,0x00,//9
		0x00,0xfc,0x12,0x11,0x12,0xfc,0x00,0x00,//A
		0x00,0xff,0x91,0x91,0x91,0x9f,0xf0,0x00,//B
		0x00,0xff,0x81,0x81,0x81,0x83,0xc3,0xc0,//C
		0x00,0xff,0x81,0x81,0x81,0x82,0x7c,0x00,//D
		0x00,0xff,0x89,0x89,0x89,0x89,0x89,0x00,//E
		0x00,0xff,0x09,0x09,0x09,0x09,0x09,0x00,//F
	
}; 

//符號的圖形
unsigned char symbol[][8] ={
		0x00,0x18,0x18,0x7e,0x7e,0x18,0x18,0x00, // +
		0x00,0x18,0x18,0x18,0x18,0x18,0x18,0x00, // -
		0x00,0x42,0x66,0x18,0x18,0x66,0x42,0x00, // x
		0x00,0x42,0x66,0x18,0x18,0x66,0x42,0x00, // X
		0x00,0x18,0x18,0x5a,0x5a,0x18,0x18,0x00, // \'
		0x00,0x7e,0x7e,0x7e,0x7e,0x7a,0x7e,0x00, // cube
		0x00,0x7e,0x42,0x42,0x4e,0x4a,0x7e,0x00, // hollow cube
		0x00,0x06,0x06,0x7e,0x7e,0x06,0x06,0x00, // T
		0x00,0x7e,0x7e,0x1a,0x3a,0x6a,0x46,0x00, // R
		0x00,0x42,0x42,0x7e,0x7e,0x42,0x42,0x00, // I
		0x00,0x5e,0x5a,0x5a,0x5a,0x5a,0x7a,0x00 // S
	
};

//英文大寫的圖型
unsigned char alphabet[][8] ={
		0x00,0x7c,0x7e,0x12,0x12,0x7e,0x7c,0x00,//A
		0x00,0xff,0x91,0x91,0x91,0x9f,0xf0,0x00,//B
		0x00,0xff,0x81,0x81,0x81,0x83,0xc3,0xc0,//C
		0x00,0xff,0x81,0x81,0x81,0x82,0x7c,0x00,//D
		0x00,0x7e,0x5a,0x5a,0x5a,0x5a,0x5a,0x00,//E
		0x00,0xff,0x09,0x09,0x09,0x09,0x09,0x00 //F
};
	
	

void Initial_Lcd(){
		uint8_t x, y;
		SYSCLK->APBCLK.SPI3_EN  =1;			 //enable spi function 
		SYS->IPRSTC2.SPI3_RST   =1;			 //reset spi function
		SYS->IPRSTC2.SPI3_RST   =0;

		/* set GPIO to SPI mode*/
		SYS->GPDMFP.SPI3_SS0 	=1;
		SYS->GPDMFP.SPI3_CLK 	=1;
		//SYS->GPDMFP.SPI3_MISO0 	=1;
		SYS->GPDMFP.SPI3_MOSI0 	=1;

		SPI_PORT[3]->CNTRL.CLKP = 1;							//CLKP HIGH IDLE
		SPI_PORT[3]->CNTRL.TX_BIT_LEN = 9;						//TX LEGTH 9
		SPI_PORT[3]->CNTRL.TX_NEG = 1;							//SET TX_NEG
		SPI_PORT[3]->DIVIDER.DIVIDER=0X03;					    //SET DIV

		SPI_PORT[3]->SSR.SSR=1;									//ENABLE SLAVE SELECT
		// Set BR
		SPI_PORT[3]->TX[0] =0xEB;
		SPI_PORT[3]->CNTRL.GO_BUSY = 1;
			while ( SPI_PORT[3]->CNTRL.GO_BUSY == 1 );
		// Set PM
		SPI_PORT[3]->SSR.SSR=0;

		SPI_PORT[3]->SSR.SSR=1;
		//outp32(SPI3_Tx0, 0x81);	
		SPI_PORT[3]->TX[0] =0x81;
		SPI_PORT[3]->CNTRL.GO_BUSY = 1;
			while ( SPI_PORT[3]->CNTRL.GO_BUSY == 1 );
		SPI_PORT[3]->TX[0] =0xa0;
		SPI_PORT[3]->CNTRL.GO_BUSY = 1;
			while ( SPI_PORT[3]->CNTRL.GO_BUSY == 1 );
		SPI_PORT[3]->SSR.SSR=0;

		SPI_PORT[3]->SSR.SSR=1;
		//outp32(SPI3_Tx0, 0xC0);
		SPI_PORT[3]->TX[0] =0xc0;	
		SPI_PORT[3]->CNTRL.GO_BUSY = 1;
			while ( SPI_PORT[3]->CNTRL.GO_BUSY == 1 );
		// Set Display Enable
		SPI_PORT[3]->SSR.SSR=0;

		SPI_PORT[3]->SSR.SSR=1;
		SPI_PORT[3]->TX[0] = 0XAF;
		SPI_PORT[3]->CNTRL.GO_BUSY = 1;
			while ( SPI_PORT[3]->CNTRL.GO_BUSY == 1 );
		for (y=0; y< 128; y++) 
		{
			for (x=0; x< 8; x++) 
			{
					SPI_PORT[3]->TX[0] = 0xB0 | x;	
					SPI_PORT[3]->CNTRL.GO_BUSY = 1;
						while ( SPI_PORT[3]->CNTRL.GO_BUSY == 1 );	 //check data out?

						
					//cloumn MSB
					SPI_PORT[3]->TX[0] =0x10 |((129-y)>>4)&0xF;
					SPI_PORT[3]->CNTRL.GO_BUSY = 1;
						while ( SPI_PORT[3]->CNTRL.GO_BUSY == 1 );	  //check data out?
							
							
					// cloumn LSB
					SPI_PORT[3]->TX[0] =0x00 | ((129-y) & 0xF);		
					SPI_PORT[3]->CNTRL.GO_BUSY = 1;
						while ( SPI_PORT[3]->CNTRL.GO_BUSY == 1 );	  //check data out?
							
					// Write Data
					//SPI_PORT[3]->SSR.SSR=1;	   //chip select
					SPI_PORT[3]->TX[0] =0x100 | 0;    	//write data
					SPI_PORT[3]->CNTRL.GO_BUSY = 1;
						while ( SPI_PORT[3]->CNTRL.GO_BUSY == 1 ); //check data out?
			}
		}
}







void drawNumber(uint8_t x,uint8_t y,uint8_t num){
	
	draw(x,y,8,8,&number[num][0]);
	
}

void drawSymbol(uint8_t x,uint8_t y,uint8_t c){

	int8_t c_table[] = {'+','-','x','X','\\','c','h','T','R','I','S',-1};
	//除號用正斜線代替
	int i = 0;
	while(c_table[i] != c && c_table[i] != -1)
		i++;
	
	if(c_table[i] != -1)
		draw(x,y,8,8,&symbol[i][0]);
	
}

void drawAlphabet(uint8_t x,uint8_t y,uint8_t c){
		draw(x,y,8,8,&alphabet[ (uint8_t)c - (uint8_t)'A' ][0]);
}


void clear(uint8_t x,uint8_t y,uint8_t len){
	
	unsigned char e = 0x00;
	
	draw(x,y,len,1,&e);
	
}

unsigned char* imgNumber(uint8_t num){
	
	return &number[num][0];
}

uint8_t pointY(uint8_t Y){
	return (4+Y*8)%128;
}


void double_draw(uint8_t x,uint8_t y,uint8_t len,uint8_t data_len,unsigned char* data_arr){
	unsigned char large_data_arr[2][8];
	
	int i,j;
	
	memset(large_data_arr,0,16);
	
	for(i = 0;i < 8;i++){
		for(j = 0;j < 8;j++){ // j是目前data_arr的位元數
			large_data_arr[j/4][i] |= ((data_arr[i] >> j) & 1) << ( (j%4) *2); 
			large_data_arr[j/4][i] |= ((data_arr[i] >> j) & 1) << ( (j%4) *2 + 1); 
		}
	}
	
	draw(x,y,len,data_len,&large_data_arr[0][0]);
	draw(x+1,y,len,data_len,&large_data_arr[1][0]);
	
}

void draw(uint8_t x,uint8_t y,uint8_t len,uint8_t data_len,unsigned char* data_arr)
{
			// data_len是所輸入資料陣列的長度
			// len是欲繪圖的長度，若長度不足則會重複繪圖
			// y不能是0 y+len也不能超過255
			// 輸入資料陣列來繪圖
			// 若是要能夠無邊界 必須依靠呼叫的程式
	
	
			uint8_t loc;
	
			for( loc = (y == 0) ? y = 1 : y ; y < loc + len  && y < 130; y++){
	
				unsigned char data = data_arr[ (y - loc) / (len / data_len) ];

				x = x % 8;

				SPI_PORT[3]->TX[0] = 0xB0 | x;	
				SPI_PORT[3]->CNTRL.GO_BUSY = 1;
					while ( SPI_PORT[3]->CNTRL.GO_BUSY == 1 );	 //check data out?

					
				//cloumn MSB
				SPI_PORT[3]->TX[0] = 0x10 | ((129-y)>>4) &0xF;
				SPI_PORT[3]->CNTRL.GO_BUSY = 1;
					while ( SPI_PORT[3]->CNTRL.GO_BUSY == 1 );	  //check data out?
						
						
				// cloumn LSB
				SPI_PORT[3]->TX[0] = 0x00 | ((129-y) & 0xF);		
				SPI_PORT[3]->CNTRL.GO_BUSY = 1;
					while ( SPI_PORT[3]->CNTRL.GO_BUSY == 1 );	  //check data out?
						
				// Write Data
				SPI_PORT[3]->TX[0] = 0x100 | data;    	//write data
				SPI_PORT[3]->CNTRL.GO_BUSY = 1;
					while ( SPI_PORT[3]->CNTRL.GO_BUSY == 1 ); //check data out?
		
	
			}
	
	
	
}
