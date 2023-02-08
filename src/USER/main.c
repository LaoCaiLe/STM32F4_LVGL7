/*
 * @Author: your name
 * @Date: 2020-07-25 21:49:00
 * @LastEditTime: 2020-09-11 22:14:28
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \stm32F407ZGT\src\USER\main.c
 * width 320
 * Height 480
 */
#include "stm32f4xx.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "sys.h"
#include "lcd.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_demos.h"
#include "lv_examples.h"
#include "touch.h"
#include "timer.h"


void tim_lv_tick();

int main(void)
{ 
  delay_init(168);
  Led_Init();

  Timer_InitDef TIM_2_conf=
	{
		.TIMx = TIM2,
		.ms   = 1,
		.NVIC_Priority = 0,
		.event_handler = tim_lv_tick,
	};
	timer_init(&TIM_2_conf);

  lv_init();
  lv_port_disp_init();
  lv_port_indev_init();

  lv_demo_music();

  while(1)
  {
    lv_task_handler();
  }
}

void tim_lv_tick()
{
  lv_tick_inc(1); // lvgl 的 1ms 心跳
}