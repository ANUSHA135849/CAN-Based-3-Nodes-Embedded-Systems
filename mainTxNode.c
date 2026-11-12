#include <lpc21xx.h>    
#include "types.h"    
#include "can.h"
#include"can_defines.h"    
#include "lcd.h"
#include "delay.h"
#include "ds18b20.h"
#include"Interrupts.h"
#include"defines.h"
volatile u32 eint0_flag,eint1_flag;
#define LED 4
int main(void)   
{   
      s32 temp=15;
	unsigned char tp,tpd;
	struct CAN_Frame txFrame,rxFrame; //i=sizeof(txFrame);    
       	txFrame.vbf.RTR=0; //data frame   
	txFrame.vbf.DLC=1;
	Init_CAN1();
	Enable_EINT0();
	Enable_EINT1(); 
	LCD_Init();//LCD initialization
	Write_CMD_LCD(0x80);//selecting starting line and staring pos
    Write_str_LCD("DS18B20 Interface:");
    DelayMS(1000);
    Write_CMD_LCD(0xC0);
	IODIR0|=(0xf<<LED);  
    IOPIN0|=(0xf<<LED); 
	while(1)   
        {  
		temp=ReadTemp();	//READING TEMPERATURE FROM DS18B20 USING 1-WIRE PROTOCAL
		/*if(temp==-1)
		{
		   Write_CMD_LCD(0xC0);
		   Write_str_LCD("                ");
		   Write_CMD_LCD(0xC0);
		   Write_str_LCD("Sensor fails");
		}
		else
		{	*/
		tp  = temp>>4;	  //GETTING INTEGER PART
		tpd=(temp&0x08)?0x35:0x30;//GETTING FRACTIONAL PART
		Write_CMD_LCD(0xC0);
		//Write_str_LCD("                ");
		Write_CMD_LCD(0xC0);
 		Write_str_LCD("Temp =");
		Write_int_LCD(tp);
		Write_DAT_LCD('.');
		Write_DAT_LCD(tpd);
		Write_str_LCD(" C  ");
		
	    if((eint0_flag==1) && (eint1_flag==0))
	   {  
			txFrame.ID=4;
            txFrame.Data1='L';
			CAN1_Tx(txFrame);	
		}
		else if(eint0_flag>1)
		{
		        eint0_flag=0;
			     txFrame.ID=4;
                        txFrame.Data1=0;
                        CAN1_Tx(txFrame);
		}
        else if((eint1_flag==1) && (eint0_flag==0))
	    { 
                 txFrame.Data1='R';
			     txFrame.ID=5;
                 CAN1_Tx(txFrame);
		  }
	      else if(eint1_flag>1)
		  {
			      eint1_flag=0;
			      txFrame.Data1=0;
                             txFrame.ID=5;
                             CAN1_Tx(txFrame);
		  }		 
		if(C1GSR & RBS_BIT_READ)
		  {	  
		    CAN1_Rx(&rxFrame);
		    if(rxFrame.ID==3)
		    {
			     WRITENIBBLE(IOPIN0,LED,rxFrame.Data1);
		    }
		  }	 
       }   
}



