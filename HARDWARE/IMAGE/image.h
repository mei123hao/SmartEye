#ifndef __IMAGE_H_
#define __IMAGE_H_

#include "sys.h"

#define jpeg_buf_size 31*1024  			    //定义JPEG数据缓存jpeg_buf的大小(*4字节)
#define  ov2640_mode    1						    //工作模式:0,RGB565模式;1,JPEG模式
#define  transport_mode 0               //传输模式:0,通过蓝牙传输;1，通过wifi传输

void jpeg_data_process(void);
void jpeg_test(void);
void rgb565_test(void);


#endif
