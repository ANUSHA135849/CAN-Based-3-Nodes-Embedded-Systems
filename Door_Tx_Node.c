#include <LPC21xx.h>   
#include"can.h"	   
#include"defines.h"
#include"delay.h"
#include"can_defines.h"
#define LED 8
#define AL_SW1 4 
#define AL_SW2 5
#define AL_SW3 6
#define AL_SW4 7 
struct CAN_Frame txFrame; 
 u8 temp=0x3C,prev=16;
main()   
{	
  //struct CAN_Frame txFrame; 
  	IODIR0|=(0xf<<LED);  
    IOPIN0|=(0xf<<LED);  
  txFrame.ID=3;   txFrame.vbf.RTR=0;  
  Init_CAN1(); 
  txFrame.vbf.DLC=1;
  
  while(1)   
	{
	        if(((IOPIN0>>AL_SW1)&1)==0)
		       CLRBIT(temp,2);
									//IOCLR0|=1<<LED;
	       else	
		       SETBIT(temp,2);
	       if(((IOPIN0>>AL_SW2)&1)==0)
		        CLRBIT(temp,3);
	       else
		        SETBIT(temp,3);
	        if(((IOPIN0>>AL_SW3)&1)==0)
		       CLRBIT(temp,4);
	       else	
		       SETBIT(temp,4);	
	       if(((IOPIN0>>AL_SW4)&1)==0)
		        CLRBIT(temp,5);
	       else
		        SETBIT(temp,5);
				 //if((C1GSR&TBS1_BIT_READ))
				 //{
				 if(prev!=temp)
				 {
	                             txFrame.Data1=((temp>>2)&0xf);
	                            CAN1_Tx(txFrame);
				     prev=temp;
			      WRITENIBBLE(IOPIN0,LED,txFrame.Data1);
				 }
			}
       }  
	     

