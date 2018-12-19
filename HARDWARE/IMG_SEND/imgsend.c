#include "sys.h"
#include "imgsend.h"
#include "M8266WIFIDrv.h"
#include "M8266WIFI_ops.h"
#include "brd_cfg.h"
#include "M8266HostIf.h"
#include "usart2.h"
#include "delay.h"
#include "usart3.h"


//#define TEST_SEND_DATA_SIZE 4096                //分块发送数组大小
void M8266wifi_sendimg(u8 *jpeg_buffer,u32 data_len)        //jpeg_buffer指向缓存的jpeg数组
{
	u16 status = 0;
	u8  link_no=0;
	u16 sent = 0;
//	u16 batch;
	
	while(1)
	{
		sent = M8266WIFI_SPI_Send_Data(jpeg_buffer,data_len,link_no, &status);
		if( (sent!=data_len) || ( (status&0xFF)!= 0 ) ) 
		{
			if( (status&0xFF)==0x12 )  				   // 0x12 = Module send buffer full, and normally sent return with 0, i.e. this packet has not been sent anyway
			{                              
					M8266HostIf_delay_us(250);       // if 500Kbytes/s, need 2ms for 1Kbytes packet to be sent. If use 250us here, may repeat query 8- times, but in a small interval
					//M8266WIFI_Module_delay_ms(1);	 // if 500Kbytes/s, need 2ms for 1Kbytes packet to be sent. If use 1ms here,   may repeat query 2- times, but in a large interval
					if(sent<data_len)
						 M8266WIFI_SPI_Send_Data(jpeg_buffer+sent, data_len-sent, link_no, &status);  // try to resend it					
			}
			else if(  ((status&0xFF)==0x14)      // 0x14 = connection of link_no not present
							||((status&0xFF)==0x15) )    // 0x15 = connection of link_no closed
			{
				// do some work here, including re-establish the closed connect or link here and re-send the packet if any
				// additional work here
				  if(sent<data_len)
						M8266WIFI_SPI_Send_Data(jpeg_buffer+sent, data_len-sent, link_no, &status);
					M8266HostIf_delay_us(249);	
			}
			else if	( (status&0xFF)==0x18)       // 0x18 = TCP server in listening states and no tcp clients connecting to so far
			{
					M8266HostIf_delay_us(251);	
			}				
			else                                 // 0x10, 0x11 here may due to spi failure during sending, and normally packet has been sent partially, i.e. sent!=0
			{
					M8266HostIf_delay_us(200);
				// do some work here					  
					if(sent<data_len)
						M8266WIFI_SPI_Send_Data(jpeg_buffer+sent, data_len-sent, link_no, &status);  // try to resend the left packet
			}
		}
		else if(status==0||sent==data_len)
			break;
	}
	
}


void Bluetooth_Sendimg(u8 *p,u32 data_len)
{
	u32 i;
	for(i=0;i<data_len*4;i++)		//dma传输1次等于4字节,所以乘以4.
	{
			while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);	//循环发送,直到发送完毕  		
			USART_SendData(USART3,p[i]);
	}
}






