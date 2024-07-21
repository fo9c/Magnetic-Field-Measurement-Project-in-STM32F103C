#ifndef _MYKEY_H
#define _MYKEY_H

#include "stm32f10x.h"

// 定义按键引脚
#define BUTTON1_GPIO_CLK     RCC_APB2Periph_GPIOA
#define BUTTON1_GPIO_PORT    GPIOA
#define BUTTON1_GPIO_PIN     GPIO_Pin_11

// 初始化按键
void Button_Init(void);

// 检测按键 1 是否按下
uint8_t Button1_IsPressed(void);

#endif
