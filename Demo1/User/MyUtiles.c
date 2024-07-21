#include "OLED.h"
#include "Delay.h"
#include "KEY.h"
#include "SERVO.h"
#include "AD.h"

#include "MYTIME.h"
#include "MyUtils.h"
#include "MYKEY.h"
#include "MYOLED.h"

// 第一步实验
#define Is_PRESET_1 3.0
#define Is_PRESET_2 3.0
#define Is_PRESET_3 3.0
#define Is_PRESET_4 3.0
#define Is_PRESET_5 3.0
#define Is_PRESET_6 3.0
#define K_PRESET_Is 2.25
#define Im_PRESET 0.1

// 第二步实验
#define Im_PRESET_1 3.0
#define Im_PRESET_2 6.0
#define Im_PRESET_3 9.0
#define Im_PRESET_4 12.0
#define Im_PRESET_5 15.0
#define Im_PRESET_6 18.0
#define K_PRESET_Im 2.25
#define Is_PRESET 0.3

#define Is_MeasureB_PRESET 0.3

// 自动测量磁场强度B
void MyUtils_AutoMeasurementB(float Kh){

	// 设置屏幕，输出标准K值
	ShowMeasureInterface();
	ShowNextInterface();
	OLED_ShowNum(60, 48, Kh/100, 7, OLED_8X16);
	OLED_Update();
	

	while(1) {
		if (Key_GetNum()) {
			// 转动电机测量Bx并输出
			// MyUtils_Test_By();
			Delay_ms(200);
			double Vh_x = MyUtils_GetVh();
			double Bx = Vh_x / (Is_MeasureB_PRESET * Kh);
			ShowMeasureInterface();
			OLED_ShowNum(59, 12, Bx, 7, OLED_8X16);
			OLED_ShowNum(60, 48, Kh, 7, OLED_8X16);
			OLED_ShowString(21, 12, "x", OLED_8X16);
			OLED_ShowString(50, 12, "-", OLED_8X16);
			OLED_Update();
			Delay_ms(2500);
			
			// 转动电机测量By并输出
			MyUtils_Test_By();
			Delay_ms(200);
			double Vh_y = MyUtils_GetVh();
			double By = Vh_y / (Is_MeasureB_PRESET * Kh);
			ShowMeasureInterface();
			OLED_ShowNum(59, 12, By, 7, OLED_8X16);
			OLED_ShowNum(60, 48, Kh, 7, OLED_8X16);
			OLED_ShowString(21, 12, "y", OLED_8X16);
			OLED_ShowString(50, 12, "-", OLED_8X16);
			OLED_Update();
			Delay_ms(2500);
			
			// 转动电机测量Bz并输出
			Servo_SetAngle3(150);
			Delay_ms(285);
			Servo_SetAngle3(90);
			
			Delay_ms(2000);
			
			Servo_SetAngle3(30);
			Delay_ms(256);
			Servo_SetAngle3(90);
	
			Delay_ms(200);
			double Vh_z = MyUtils_GetVh();
			double Bz = Vh_z / (Is_MeasureB_PRESET * Kh);
			ShowMeasureInterface();
			OLED_ShowNum(59, 12, Bz, 7, OLED_8X16);
			OLED_ShowNum(60, 48, Kh, 7, OLED_8X16);
			OLED_ShowString(21, 12, "z", OLED_8X16);
			OLED_Update();
			Delay_ms(2500);
			
			
			// 展示三个数值
			OLED_Clear();
			OLED_ShowString(0, 0, "Magnetic field:", OLED_6X8);
			OLED_ShowString(13, 12, "Bx =", OLED_8X16);
			OLED_ShowString(13, 29, "By =", OLED_8X16);
			OLED_ShowString(13, 48, "Bz =", OLED_8X16);
			OLED_ShowString(13, 48, "Bz =", OLED_8X16);
			OLED_ShowNum(60, 12, Bx, 7, OLED_8X16);
			OLED_ShowNum(60, 29, By, 7, OLED_8X16);
			OLED_ShowNum(60, 48, Bz, 7, OLED_8X16);
			OLED_Update();
			while(1) {
				if (Key_GetNum()) {
					break;
				}
			}
			
		}
	}
}


// 计算第n个Kh=Vh/（Is*Im*K）变更Is
double MyUtils_MeasurementKh_Is(void) {
	double MeasuredVh_1 = 1.0;
	double MeasuredVh_2 = 1.0;
	int MeasurementTime = 1;
	double Sum_Kh_n = 0;
	int Number = 0;
	int Number_Kh = 0;
	
	while(MeasurementTime <= 6) {
		ShowAdjustInterface(MeasurementTime);		// K值调整界面
		
		// 计算值Vh1
		while(1) {
			if (Key_GetNum()) {
				// 获取霍尔传感器的值..........................
				OLED_ShowNum(27, 21, MyUtils_GetVh()/100, 5, OLED_6X8); // 显示值Vh1
				Number++;
				OLED_Update();
				break;
			}
		}

		// 计算值Vh2
		while(1) {
			if (Key_GetNum()) {
				// 获取霍尔传感器的值.....................................
				MeasuredVh_2 = MyUtils_GetVh();
				OLED_ShowNum(96, 21,  MyUtils_GetVh()/100, 5, OLED_6X8); // 显示值Vh2
				Number++;
				OLED_Update();
				break;
			}
		}
		
		// 计算第n个Kh值
		double result = (MeasuredVh_1 + MeasuredVh_2) / 2;
		result /= K_PRESET_Is;
		result /= Im_PRESET;
		if (MeasurementTime >= 1 && MeasurementTime <= 6) {
			switch (MeasurementTime) {
					case 1:
							result /= Is_PRESET_1;
							break;
					case 2:
							result /= Is_PRESET_2;
							break;
					case 3:
							result /= Is_PRESET_3;
							break;
					case 4:
							result /= Is_PRESET_4;
							break;
					case 5:
							result /= Is_PRESET_5;
							break;
					case 6:
							result /= Is_PRESET_6;
							break;
			}
		}
		Sum_Kh_n += result;
		OLED_ShowNum(70, 48, result, 8, OLED_8X16);
		Number_Kh++;
		result = 0;
		OLED_Update();
		Delay_ms(1500);
		ShowNextInterface(); // “按下Key继续”界面
		
		while(1) {
			if (Key_GetNum()) {
				MeasurementTime++;
				break;
			}
		}
		
	}
	return Sum_Kh_n/6;
}


// 计算第n个Kh=Vh/（Is*Im*K）变更Im
double MyUtils_MeasurementKh_Im(void) {
	double MeasuredVh_1 = 1.0;
	double MeasuredVh_2 = 1.0;
	int MeasurementTime = 1;
	double Sum_Kh_n = 0;
	int Number = 0;
	int Number_Kh = 0;
	while(MeasurementTime <= 6) {
		ShowAdjustInterface(MeasurementTime);		// K值调整界面
		
		// 计算值Vh1
		while(1) {
			if (Key_GetNum()) {
				// 获取霍尔传感器的值.................................
				OLED_ShowNum(27, 21, MyUtils_GetVh()/10, 5, OLED_6X8); // 显示值Vh1
				Number++;
				OLED_Update();
				break;
			}
		}

		// 计算值Vh2
		while(1) {
			if (Key_GetNum()) {
				// 获取霍尔传感器的值2
				OLED_ShowNum(96, 21, MyUtils_GetVh()/10, 5, OLED_6X8); // 显示值Vh2
				Number++;
				OLED_Update();
				break;
			}
		}
		
		// 计算第n个Kh值
		double result = (MeasuredVh_1 + MeasuredVh_2) / 2;
		result /= K_PRESET_Im;
		result /= Is_PRESET;
		if (MeasurementTime >= 1 && MeasurementTime <= 6) {
			switch (MeasurementTime) {
					case 1:
							result /= Im_PRESET_1;
							break;
					case 2:
							result /= Im_PRESET_2;
							break;
					case 3:
							result /= Im_PRESET_3;
							break;
					case 4:
							result /= Im_PRESET_4;
							break;
					case 5:
							result /= Im_PRESET_5;
							break;
					case 6:
							result /= Im_PRESET_6;
							break;
			}
		}
		Sum_Kh_n += result;
		OLED_ShowNum(60, 48, result, 6, OLED_8X16);
		Number_Kh++;
		result = 0;
		OLED_Update();
		Delay_ms(1500);
		ShowNextInterface(); // “按下Key继续”界面
		while(1) {
			if (Key_GetNum()) {
				MeasurementTime++;
				break;
			}
		}
		
	}
	return Sum_Kh_n;
}

// 延时器（单位毫秒）
void MyUtils_DelayTime(uint32_t delay_ms) {
	delay_ms = delay_ms / 10;
  uint32_t start = MYTIME_GetMilliseconds();
  while (MYTIME_GetMilliseconds() - start < delay_ms) {
      // 等待直到达到延迟时间
  }
}
// 前置自动化测试
void MyUtils_Test(void) {
	OLED_ShowString(28, 14, "Press Key", OLED_8X16); 
	OLED_ShowString(21, 35, "to continue", OLED_8X16);
	OLED_Update();
	while(1) {
		if (Key_GetNum()) {
			break;
		}
	}
	
	ShowTestInterface();
	
	Servo_SetAngle1(150);
	Servo_SetAngle2(150);
	Delay_ms(100);
	OLED_ShowString(95, 50, ".", OLED_8X16); 
	Delay_ms(100);
	OLED_Update();
	
	Servo_SetAngle1(90);
	Servo_SetAngle2(90);
	Delay_ms(100);
	OLED_ShowString(97, 50, ".", OLED_8X16); 
	Delay_ms(100);
	OLED_Update();
	
	Servo_SetAngle1(30);
	Servo_SetAngle2(30);
	Delay_ms(100);
	OLED_ShowString(99, 50, ".", OLED_8X16); 
	Delay_ms(100);
	OLED_Update();
	
	Servo_SetAngle1(90);
	Servo_SetAngle2(90);
	Delay_ms(100);
	OLED_ShowString(101, 50, ".", OLED_8X16);
	Delay_ms(300);
	OLED_Update();
	
	if(AD_GetValue() == 0) {
		OLED_Clear();
		OLED_ShowString(18, 14, "Hall sensor", OLED_8X16); 
		OLED_ShowString(30, 35, "Error!!!!", OLED_8X16);
		OLED_Update();
	} else {
		OLED_Clear();
		OLED_ShowString(22, 14, "Everything", OLED_8X16); 
		OLED_ShowString(56, 35, "OK", OLED_8X16);
		OLED_Update();
	}
	while(1) {
		if (Key_GetNum()) {
			break;
		}
	}
}

// 获取Vh绝对值(10-e3)
float MyUtils_GetVh(void) {
	float RawData = 0;
	while(1) {
		RawData = AD_GetValue();
		if(RawData != 0) {
			break;
		}
	}
	float result = 0;
	if (RawData > 2170) {
			result = RawData - 2170;
	} else if (RawData > 2170) {
			result = 2170 - RawData;
	}
	result *= 1660;
	result /= 2048;
	return result;
}

// 自动测试By(转动大盘)
void MyUtils_Test_By(void) {
	Servo_SetAngle2(150);
	Delay_ms(285);
	Servo_SetAngle2(90);
	
	Delay_ms(2000);
	
	Servo_SetAngle2(30);
	Delay_ms(256);
	Servo_SetAngle2(90);
}
