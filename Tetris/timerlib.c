#include "Driver/DrvSYS.h"




void InitTIMER0(uint16_t speed)
{
	/* Step 1. Enable and Select Timer clock source */          
	SYSCLK->CLKSEL1.TMR0_S = 0;	//Select 12Mhz for Timer0 clock source 
  SYSCLK->APBCLK.TMR0_EN =1;	//Enable Timer0 clock source

	/* Step 2. Select Operation mode */	
	TIMER0->TCSR.MODE=1;		//Select periodic mode for operation mode

	/* Step 3. Select Time out period = (Period of timer clock input) * (8-bit Prescale + 1) * (24-bit TCMP)*/
	TIMER0->TCSR.PRESCALE=255;	// Set Prescale [0~255]
	TIMER0->TCMPR = speed;		// Set TCMPR [0~16777215]
								// (1/12000000)*(255+1)*(27650)= 0.58 sec or 1.695Hz


	/* Step 4. Enable interrupt */
	TIMER0->TCSR.IE = 1;
	NVIC_EnableIRQ(TMR0_IRQn);	//Enable Timer0 Interrupt

	/* Step 5. Enable Timer module */
	TIMER0->TCSR.CRST = 1;		//Reset up counter
	TIMER0->TCSR.CEN = 1;		//Enable Timer0

  	//TIMER0->TCSR.TDR_EN=1;		// Enable TDR function
}

void InitTIMER1(uint16_t speed)
{
	/* Step 1. Enable and Select Timer clock source */          
		SYSCLK->CLKSEL1.TMR1_S = 0;	//Select 12Mhz for Timer0 clock source 
    SYSCLK->APBCLK.TMR1_EN =1;	//Enable Timer0 clock source

	/* Step 2. Select Operation mode */	
	TIMER1->TCSR.MODE=1;		//Select periodic mode for operation mode

	/* Step 3. Select Time out period = (Period of timer clock input) * (8-bit Prescale + 1) * (24-bit TCMP)*/
	TIMER1->TCSR.PRESCALE=255;	// Set Prescale [0~255]
	TIMER1->TCMPR = speed;		// Set TCMPR [0~16777215]
								// (1/12000000)*(255+1)*(20000)= 0.426 sec 

	/* Step 4. Enable interrupt */
	TIMER1->TCSR.IE = 1;
	NVIC_EnableIRQ(TMR1_IRQn);	//Enable Timer0 Interrupt

	/* Step 5. Enable Timer module */
	TIMER1->TCSR.CRST = 1;		//Reset up counter
	TIMER1->TCSR.CEN = 1;		//Enable Timer0

//  	TIMER0->TCSR.TDR_EN=1;		// Enable TDR function
}

void InitHCLK12M(void)
{
	UNLOCKREG();

	//External 4~24 MHz High Speed Crystal Enable (write-protection bit)
	SYSCLK->PWRCON.XTL12M_EN = 1;//1 = Enable external 12 MHz

	//HCLK clock source select (write-protection bits)
	SYSCLK->CLKSEL0.HCLK_S = 0;//000 = Clock source from external 12 MHz

	LOCKREG();
	
}


