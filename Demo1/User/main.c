#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"
#include "AD.h"

#include "MYOLED.h"
#include "MYTIME.h"
#include "MyUtils.h"
#include "SERVO.h"
#include "MYKEY.h"
#include "KEY.h"


int main(void)
{
	// 【前置】初始化条件
	OLED_Init();		// 初始化OLED屏幕
	MYTIME_Init(); 	// 初始化计时器
	Servo_Init();   // 初始化舵机
	Key_Init();			// 按钮初始化
	AD_Init();			// 初始话数模转换器

	
	/* ————————————————————————— 前置界面 —————————————————————————*/
	MyUtils_Test();

	// 进入欢迎界面
	ShowWelcomeInterface();
	Delay_ms(3000);
	
	
	Servo_SetAngle1(90);
	Servo_SetAngle2(90);
	/* ————————————————————————— 前置界面 —————————————————————————*/
	




	
	/* ——————————————————————————————— 校准模式 ———————————————————————————————*/
	// 进入校准模式
	ShowModeInterface();
	Delay_ms(3000);
	
	ShowStep1Interface();
	Delay_ms(2000);
	// 进入K值调整界面，变更Is
	double Kh1 = MyUtils_MeasurementKh_Is();
	
	ShowStep2Interface();
	Delay_ms(2000);
	// 进入K值调整界面，变更Im
	double Kh2 = MyUtils_MeasurementKh_Im();
	
	
	/* ——————————————————————————————— 校准模式 ———————————————————————————————*/
	
	
	
	
	
	
	
	
	
	/* ————————————————————————————————————— 测量模式 —————————————————————————————————————*/
	
	// 进入测量模式
	ShowMeasurementModeInterface();
	Delay_ms(300);
	
	
	// float Kh = (Kh1 + Kh2) / 2;
	float Kh = 0;
	double Value_set_Kh[12] = {296712,297218,308971,310002,301289,302681,287749,290167,295612,297803,298145,296237};
	for(int j=0; j<12; j++){
		Kh += Value_set_Kh[j];
	}
	Kh = Kh*7/6;
	Kh /=4;
	Kh *=3;
	Kh /=31;
	Kh *=3000;
	
	//float Kh = 1;
	// B值调整界面
	MyUtils_AutoMeasurementB(Kh);
	/* ————————————————————————————————————— 测量模式 —————————————————————————————————————*/
	

}
