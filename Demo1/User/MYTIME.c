#include "OLED.h"     // OLED 屏幕的驱动头文件

#include "MYTIME.h"


volatile uint32_t milliseconds = 0;

// 定时器初始化函数
void MYTIME_Init(void) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // 使能 TIM2 时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // 定时器基本配置
    TIM_TimeBaseStructure.TIM_Period = 4999; 
    TIM_TimeBaseStructure.TIM_Prescaler = 71; 
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // 配置 NVIC
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // 使能定时器中断
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    // 启动定时器
    TIM_Cmd(TIM2, ENABLE);
}

// 定时器中断服务例程
void TIM2_IRQHandler(void) {
    if (TIM_GetITStatus(TIM2, TIM_IT_Update)!= RESET) {
        // 清除中断标志
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

        // 更新毫秒计数器
        milliseconds++;

        // 这其他需要在每毫秒执行的代码...
    }
}

// 获取当前计时的毫秒数
uint32_t MYTIME_GetMilliseconds(void) {
    return milliseconds;
}

// 在 OLED 屏幕输出计时
void MYTIME_ShowOnOLED(uint8_t X, uint8_t Y, uint8_t Length) {
	OLED_ShowNum(X, Y, milliseconds, Length, OLED_8X16);// OLED 显示函数
}
