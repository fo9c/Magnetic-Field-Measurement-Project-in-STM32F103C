#ifndef _MYOLED_H_
#define _MYOLED_H_

// 展示校准界面（Welcome to Measurement System）
void ShowWelcomeInterface(void);

// 展示校准模式界面（Calibrate Mode）
void ShowModeInterface(void);

// 展示测量模式界面（Measurement Mode）
void ShowMeasurementModeInterface(void);
	
// 展示按键继续界面（Press key to the next）
void ShowNextInterface(void);
	
// 展示校准界面（测量Kh）
void ShowAdjustInterface(int Number);
	
// 展示测量界面（B/K）
void ShowMeasureInterface(void);

// 展示第一步校准界面（Step1）
void ShowStep1Interface(void);

// 展示第二步校准界面（Step2）
void ShowStep2Interface(void);

// 展示前置测试界面
void ShowTestInterface(void);

#endif
