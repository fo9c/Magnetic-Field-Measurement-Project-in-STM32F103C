#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "AD.h"
#include "Delay.h"

#include "MYOLED.h"
#include "MyUtils.h"
#include "MYTIME.h"

// 展示欢迎界面（Welcome to Measurement System）
void ShowWelcomeInterface(void){
	OLED_Clear();
	OLED_ShowString(35, 4, "Welcome", OLED_8X16); 
	OLED_ShowString(56, 18, "to", OLED_8X16); 
	OLED_ShowString(22, 32, "Measurement", OLED_8X16);
	OLED_ShowString(40, 48, "System", OLED_8X16);
	OLED_Update();
}

// 展示校准模式界面（Calibrate Mode）
void ShowModeInterface(void){
	OLED_Clear();
	OLED_ShowString(30, 14, "Calibrate", OLED_8X16); 
	OLED_ShowString(51, 32, "Mode", OLED_8X16);
	OLED_Update();
}

// 展示测量模式界面（Measurement Mode）
void ShowMeasurementModeInterface(void) {
	OLED_Clear();
	OLED_ShowString(25, 14, "Measurement", OLED_8X16); 
	OLED_ShowString(51, 32, "Mode", OLED_8X16);
	OLED_Update();
}

// 展示按键继续界面（Press key to the next）
void ShowNextInterface(void){
	OLED_ShowString(0, 0, "                ", OLED_8X16);
	OLED_ShowString(0, 16, "                ", OLED_8X16);
	OLED_ShowString(0, 32, "                ", OLED_8X16);
	OLED_ShowString(0, 19, "________________", OLED_8X16);
	OLED_ShowString(28, 3, "Press key...", OLED_6X8); 
	OLED_ShowString(38, 15, "Next", OLED_8X16); 
	OLED_ShowString(73, 16, "->", OLED_8X16); 
	OLED_ShowString(0, 35, "F", OLED_8X16);
	OLED_ShowString(8, 37, "inal:", OLED_6X8);
	OLED_Update();
}

// 展示校准界面（测量Kh）
void ShowAdjustInterface(int Number){
	// 显示校准数据页面
	OLED_Clear();
	OLED_ShowString(0, 0, "1", OLED_8X16); 
	OLED_ShowString(8, 0, "st:", OLED_6X8);
	OLED_ShowString(0, 19, "________________", OLED_8X16);
	OLED_ShowString(58, 0, "|", OLED_8X16); 
	OLED_ShowString(58, 16, "|", OLED_8X16); 
	OLED_ShowString(65, 0, "2", OLED_8X16); 
	OLED_ShowString(74, 0, "st:", OLED_6X8);
	OLED_ShowString(0, 35, "F", OLED_8X16);
	OLED_ShowString(8, 37, "inal:", OLED_6X8);
	OLED_ShowString(20, 48, "K  =", OLED_8X16);
	OLED_ShowString(27, 55, "H", OLED_6X8);
	OLED_ShowNum(33, 55, Number, 1, OLED_6X8);
	OLED_ShowString(7, 21, "V1", OLED_6X8);
	OLED_ShowString(20, 21, "= -", OLED_6X8);
	OLED_ShowString(74, 21, "V2", OLED_6X8);
	OLED_ShowString(88, 21, "=", OLED_6X8);
	OLED_ShowString(27, 21, "?????", OLED_6X8); // 显示值Vh1
	OLED_ShowString(96, 21, "?????", OLED_6X8); // 显示值Vh2
	OLED_ShowString(70, 47, "?????", OLED_8X16); // 显示值Kh
	OLED_Update();
}
	

// 展示测量界面（B/K）
void ShowMeasureInterface(){
	OLED_Clear();
	OLED_ShowString(0, 19, "________________", OLED_8X16);
	OLED_ShowString(0, 0, "Magnetic field:", OLED_6X8);
	OLED_ShowString(13, 12, "B  =", OLED_8X16);
	OLED_ShowString(0, 37, "Scale factor K:", OLED_6X8);
	OLED_ShowString(13, 48, "K  =", OLED_8X16);
	OLED_ShowString(20, 55, "H", OLED_6X8);
	OLED_Update();
}

// 展示第一步校准界面（Step1）
void ShowStep1Interface(void) {
	OLED_Clear();
	OLED_ShowString(38, 14, "Step 1", OLED_8X16); 
	OLED_ShowString(30, 35, "Change Is", OLED_8X16);
	OLED_Update();
}

// 展示第二步校准界面（Step2）
void ShowStep2Interface(void) {
	OLED_Clear();
	OLED_ShowString(38, 14, "Step 2", OLED_8X16); 
	OLED_ShowString(30, 35, "Change Im", OLED_8X16);
	OLED_Update();
}
// 展示前置测试界面
void ShowTestInterface(void) {
	OLED_Clear();
	OLED_ShowString(35, 12, "Testing", OLED_8X16); 
	OLED_ShowString(19, 35, "Hall sensor", OLED_8X16);

	OLED_Update();
}
