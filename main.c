#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
void SystemInit() {} 

	

	
void init()
{
	uint32_t delay ; // dummy variable to use it down there and make sure that the clock has worked
	SYSCTL_RCGCGPIO_R |= 0x20;  // enabling the clock for port F  			0010 0000
	delay = 1;
	GPIO_PORTF_LOCK_R = 0x4C4F434B ; //The port F isn't locked and i can use all of it's pins
	GPIO_PORTF_CR_R = 0x1F ; // Unlocking the first 5 pins only which i'll use 0001 1111
	GPIO_PORTF_AFSEL_R = 0;
	GPIO_PORTF_PCTL_R = 0;
	GPIO_PORTF_AMSEL_R = 0;
	GPIO_PORTF_DIR_R = 0x0E;  // making pins 1 and 2 and 3 as outputs		0000 1110
	GPIO_PORTF_DEN_R = 0x1F;  // Making the first 5 pins digital 			  0001 1111
	GPIO_PORTF_PUR_R = 0x11 ; // Switchs at pin 0 and pin 4 						0001 0001			 pull up makes the switch not floating when it's off
	GPIO_PORTF_LOCK_R = 0x4C4F434B ; //The port F isn't locked and i can use all of it's pins
	GPIO_PORTF_CR_R = 0x1F ; // Unlocking the first 5 pins only which i'll use 0001 1111
	
}

/*

	/* SW1			SW2					LED
	@		4				 0
		
			1 (OFF)	 0 (ON)    --> 1
			0 (ON)	 1 (OFF)	 --> 2
			0	(ON)	 0 (ON)	   --> 3
	
	/*

	int main()
	{
		init();

		while(1)
		{
			if((GPIO_PORTF_DATA_R & 0x11) == 0x10)  // SW2(on pin0) = ON 
			{
				GPIO_PORTF_DATA_R = 0x02 ;  //LED#1 (on pin 1) = ON   0000 0010  RED
			}
				
			else if((GPIO_PORTF_DATA_R & 0x11) == 0x01)  // SW1(on pin4) = ON  
			{
				GPIO_PORTF_DATA_R = 0x04 ;  //LED#2 (on pin 2) = ON   0000 0100   BLUE
			}
			
			else if ((GPIO_PORTF_DATA_R & 0x11) == 0x00 ) // SW1 , SW2 = ON
			{
				GPIO_PORTF_DATA_R = 0x08 ;  //LED#3 (on pin 3) = ON   0000 1000   GREEN
			}
			
			else
			{
				GPIO_PORTF_DATA_R = 0x00; //Turn off all the leds
			}
		}
	}
	*/
	
	
	
	//SYSTIC CODE
	
	void Systic_init()
{
	NVIC_ST_CTRL_R = 0 ; //safart kol 7aga fel register da (clear)
	NVIC_ST_RELOAD_R = 16000 -1 ;  // 1 millisecond 
	NVIC_ST_CURRENT_R = 0 ;
	NVIC_ST_CTRL_R = 5 ;   //0101 bsh8l el enable w el clk sec
}

void delay_nanosec( uint32_t timee )
{
	NVIC_ST_CTRL_R = 0 ;
	NVIC_ST_RELOAD_R = 16*timee -1 ; 
	NVIC_ST_CURRENT_R = 0 ;
	NVIC_ST_CTRL_R = 5 ;
	while ((NVIC_ST_CTRL_R & 0x10000) == 0) {}
}


int main()
{
	float distancee;
	int i=0 ,counte = 0 ;
	init();
	Systic_init();

	while(counte ==0)
	{
		if((GPIO_PORTF_DATA_R & 0x11) == 0x01)  // SW1(on pin4) = ON
		{
			while(i == 0)
			{
				if((GPIO_PORTF_DATA_R & 0x11) == 0x10)  // SW2(on pin0) = ON 
				{ break;}
				
				if(NVIC_ST_CTRL_R & 0x10000 ) //b3ml check 3al flag elli fe bit 16 
				{
					GPIO_PORTF_DATA_R ^= 0x02 ;  //LED#1 (on pin 1) = ON   0000 0010  RED
					counte ++;
				}	
			}
		}
	}
		
	distancee =(counte )* (17.150); //in CM
	for (;i<1000000000;i++){}

}