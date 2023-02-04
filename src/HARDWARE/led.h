/*
 * @Author: your name
 * @Date: 2020-09-02 17:37:49
 * @LastEditTime: 2020-09-02 17:44:32
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \stm32F407模板\src\HARDWARE\Led\led.h
 */
#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"
#include "sys.h"
void Led_Init();

#define LED1 PFout(9)
#define LED2 PFout(10)

#endif // !__LED_H
