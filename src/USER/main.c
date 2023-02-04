#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "timer.h"
#include "../GUI/lvgl/lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "timer.h"
#include "LVGL_test.h"
#include "touch.h"

void tim_lv_tick(void);

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	Delay_Init();      //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	
	Led_Init();					  //初始化LED
 	LCD_Init();           //初始化LCD FSMC接口
	LCD_Clear(BLACK);

	tp_dev.init();				//触摸屏初始化
	
	Timer_InitDef TIM_2_conf=
	{
		.TIMx = TIM2,
		.ms   = 1,
		.NVIC_Priority = 0,
		.event_handler = tim_lv_tick,
	};
	timer_init(&TIM_2_conf);
	
	lv_init(); //lvgl 系统初始化
	lv_port_disp_init(); //lvgl 显示接口初始化,放在 lv_init()的后面
	lv_port_indev_init();

	while(1) 
	{	
	 	lv_task_handler();
	}
}


void tim_lv_tick()
{
	lv_tick_inc(1);//lvgl 的 1ms 心跳
}


