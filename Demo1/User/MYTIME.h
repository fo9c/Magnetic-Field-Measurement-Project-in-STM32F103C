#ifndef MYTIME_H
#define MYTIME_H

#include "stm32f10x.h"

// 初始化计时器
void MYTIME_Init(void);

// 获取当前计时的毫秒数
uint32_t MYTIME_GetMilliseconds(void);

// 定时器中断服务例程
void TIM2_IRQHandler(void);

// 在 OLED 屏幕输出计时
void MYTIME_ShowOnOLED(uint8_t X, uint8_t Y, uint8_t Length);

#endif
