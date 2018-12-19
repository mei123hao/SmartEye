#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h" 
#include "usart2.h"  
#include "timer.h" 
#include "dcmi.h" 
#include "M8266WIFIDrv.h"
#include "M8266WIFI_ops.h"
#include "brd_cfg.h"
#include "M8266HostIf.h"
#include "imgsend.h"
#include "image.h"
#include "ov2640.h" 
#include "usart3.h"

void M8266WIFI_Test(void);
int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //设置系统中断优先级分组2
	delay_init(168);                                  //初始化延时函数
	uart_init(115200);		                            //初始化串口波特率为115200
//	usart2_init(42,115200);		                        //初始化串口2波特率为230400
	usart3_init(230400);
	LED_Init();					                              //初始化LED 
	if (ov2640_mode == 0)  LCD_Init();					      //LCD初始化 
	KEY_Init();					                              //按键初始化 
//	TIM3_Int_Init(10000-1,8400-1);                    //10Khz计数,1秒钟中断一次
	
	
	while(OV2640_Init())                              //初始化OV2640
	{
		printf("OV2640 ERR\n");
		LED1=RESET;
		delay_ms(200);
	} 
  printf("OV2640 OK\n");

//note:要使用wifi传输去除下面注释	
//	M8266HostIf_Init();                               //wifi主机初始化
//	printf("wifi init successed!\n");
//	M8266WIFI_Module_Init_Via_SPI();                  //SPI接口初始化
//	printf("via spi sucessed!\n");
	  /****wifi配置***/
//	Wifi_Configure();	
	
	if(ov2640_mode)
		jpeg_test();
	else 
		rgb565_test(); 
}
