#include "DrvPWM.h"
#include "PMWlib.h"

uint16_t toneMap[][8][2] = {
	0,0, 262,277, 294,311, 330,330, 349,370, 392,415, 440,464, 494,494,
	0,0, 523,554, 587,622, 659,659, 698,740, 784,831, 880,932, 988,988,
	0,0, 1046,1109, 1175,1245, 1318,1318, 1397,1480, 1568,1661, 1760,1865, 1976,1976
};


void InitPWM(void)
{
//-------------------------------------------------------------------------------------
 	// Step 1. GPIO initial, 

	SYS->GPBMFP.TM3_PWM4=1; 	//set GPB_MFP11 for PWM4
	SYS->ALTMFP.PB11_PWM4=1; 	//set PB11_PWM4 for PWM4
	
	
				
//-------------------------------------------------------------------------------------
	// Step 2. Enable and Select PWM clock source

	//-------------------------------------------------------
	SYSCLK->APBCLK.PWM45_EN = 1; //Enable PWM4 & PWM5 clock
	
	//-------------------------------------------------------
	//PWM0 and PWM1 clock source select
	//00=external, 01=32.768k, 10=HCLK, 11=22.1184M
	
	SYSCLK->CLKSEL2.PWM45_S = 0; //Select 12Mhz for PWM clock source

	//-------------------------------------------------------
	//Clock input is divided by (CP + 1)

	PWMB->PPR.CP01=1;		//PWM45	
	
	//-------------------------------------------------------
	// PWM clock = clock source/(Prescaler + 1)/divider
	//PWM Timer 0 Clock Source Divider 
	//000=2, 001=4, 010=8, 011=16, 100=1
	
	PWMB->CSR.CSR0=0;		//PWM4	
				         
//-------------------------------------------------------------------------------------
	
	//PWM-Timer 0 Auto-reload/One-Shot Mode 
	//CNR and CMR will be auto-cleared after setting CH0MOD form 0 to 1.
	//0:One-shot mode, 1:Auto-load mode

	PWMB->PCR.CH0MOD=1;	//PWM4
								
	//-------------------------------------------------------
	//PWM frequency = PWMxy_CLK/[(prescale+1)*(clock divider)*(CNR+1)];
	//Duty ratio = (CMR+1)/(CNR+1).
	//CMR >= CNR: PWM output is always high.
	//CMR < CNR: PWM low width = (CNR-CMR) unit; PWM high width = (CMR+1) unit.
	//CMR = 0: PWM low width = (CNR) unit; PWM high width = 1 unit
	
	PWMB->CNR0=0xFFFF; //PWM4
	
	//-------------------------------------------------------
	//CMR determin the PWM duty

	PWMB->CMR0=0xFFFF; 	//PWM4


	//-------------------------------------------------------
	//PWM-Timer 0 Output Inverter Enable
	//Inverter->0:off, 1:on
	
	PWMB->PCR.CH0INV=0;			//PWM4 
	
	//-------------------------------------------------------
	//PWM-Timer 0 Enable (PWM timer 0 for group A and PWM timer 4 for group B
	//PWM function->0:Disable, 1:Enable
	
	PWMB->PCR.CH0EN=1;	//PWM4			
	//-------------------------------------------------------
	// Enable PWM channel 0 output to pin
	//Output to pin->0:Diasble, 1:Enable
	

	PWMB->POE.PWM0=1;	//PWM4			
	
}

void PWM4_Freq(uint32_t PWM_frequency, uint8_t PWM_duty)
{
	uint8_t  PWM_PreScaler;
	uint16_t PWM_ClockDivider;
	uint16_t CNR0, CMR0;
	uint32_t PWM_Clock;

 	if (PWM_frequency == 0) 
		PWMB->POE.PWM0=0;
	else
	{		
		PWMB->POE.PWM0=1;
		// PWM setting
		if(	SYSCLK->CLKSEL2.PWM45_S == 0)/*外部clock*/
			PWM_Clock = 12000000; // Clock source = 12 MHz
		if(	SYSCLK->CLKSEL2.PWM45_S == 3)/*內部clock*/
			PWM_Clock = 22118400; // Clock source = 22.1184MHz
		
		PWM_PreScaler = 20;    // clock is divided by (PreScaler + 1)

		PWM_ClockDivider = 2;  // 0: 1/2, 1: 1/4, 2: 1/8, 3: 1/16, 4: 1

    //PWM_Freq = PWM_Clock / (PWM_PreScaler + 1) / PWM_ClockDivider / (PWM_CNR0 + 1); 
		CNR0 = PWM_Clock / PWM_frequency / (PWM_PreScaler + 1) / PWM_ClockDivider - 1;

		// Duty Cycle = (CMR0+1) / (CNR0+1)
		CMR0 = (CNR0 +1) * PWM_duty /100  - 1;

		//PWM setting	  
		PWMB->CSR.CSR0 = 4;                // 0: 1/2, 1: 1/4, 2: 1/8, 3: 1/16, 4: 1
		PWMB->PPR.CP01 = PWM_PreScaler;    // set PreScaler
		PWMB->CNR0 = CNR0;	 			   // set CNR0
		PWMB->CMR0 = CMR0;				   // set CMR0
	}
}

uint32_t toneToFreq(uint8_t level,uint8_t scale, uint8_t acc){
	/*
		scale是音階
		level是高音 低音或中音
		acc是是否有升降音
	*/
	return toneMap[level][scale][acc];
}

uint8_t search_music(uint8_t order, const uint8_t sheet[][3]){
	
	uint8_t i;
	
	for(i = 0;order != 0;i++)
		if(sheet[i][0] == MUSIC_START)
			order--;
	
	return i;
	
	
	
}
