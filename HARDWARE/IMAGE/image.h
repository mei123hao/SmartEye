#ifndef __IMAGE_H_
#define __IMAGE_H_

#include "sys.h"

#define jpeg_buf_size 31*1024  			    //����JPEG���ݻ���jpeg_buf�Ĵ�С(*4�ֽ�)
#define  ov2640_mode    1						    //����ģʽ:0,RGB565ģʽ;1,JPEGģʽ
#define  transport_mode 0               //����ģʽ:0,ͨ����������;1��ͨ��wifi����

void jpeg_data_process(void);
void jpeg_test(void);
void rgb565_test(void);


#endif
