#include "stm32f10x.h"                  // Device header
#include "MYKEY.h"

void Button_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 开启按键端口的时钟
    RCC_APB2PeriphClockCmd(BUTTON1_GPIO_CLK, ENABLE);

    // 选择按键的引脚
    GPIO_InitStructure.GPIO_Pin = BUTTON1_GPIO_PIN;
    // 设置按键的引脚为浮空输入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    // 使用结构体初始化按键
    GPIO_Init(BUTTON1_GPIO_PORT, &GPIO_InitStructure);
}

uint8_t Button1_IsPressed(void)
{
    if (GPIO_ReadInputDataBit(BUTTON1_GPIO_PORT, BUTTON1_GPIO_PIN) == 1) 
    {
        // 等待按键释放
        while (GPIO_ReadInputDataBit(BUTTON1_GPIO_PORT, BUTTON1_GPIO_PIN) == 1);
        return 1;
    }
    else
        return 0;
}
