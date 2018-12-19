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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //����ϵͳ�ж����ȼ�����2
	delay_init(168);                                  //��ʼ����ʱ����
	uart_init(115200);		                            //��ʼ�����ڲ�����Ϊ115200
//	usart2_init(42,115200);		                        //��ʼ������2������Ϊ230400
	usart3_init(230400);
	LED_Init();					                              //��ʼ��LED 
	if (ov2640_mode == 0)  LCD_Init();					      //LCD��ʼ�� 
	KEY_Init();					                              //������ʼ�� 
//	TIM3_Int_Init(10000-1,8400-1);                    //10Khz����,1�����ж�һ��
	
	
	while(OV2640_Init())                              //��ʼ��OV2640
	{
		printf("OV2640 ERR\n");
		LED1=RESET;
		delay_ms(200);
	} 
  printf("OV2640 OK\n");

//note:Ҫʹ��wifi����ȥ������ע��	
//	M8266HostIf_Init();                               //wifi������ʼ��
//	printf("wifi init successed!\n");
//	M8266WIFI_Module_Init_Via_SPI();                  //SPI�ӿڳ�ʼ��
//	printf("via spi sucessed!\n");
	  /****wifi����***/
//	Wifi_Configure();	
	
	if(ov2640_mode)
		jpeg_test();
	else 
		rgb565_test(); 
}
