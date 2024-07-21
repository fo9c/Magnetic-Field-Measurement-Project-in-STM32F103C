#ifndef _MyUtils_H
#define _MyUtils_H

#include "stm32f10x.h"

// 自动测量磁场强度B
void MyUtils_AutoMeasurementB(float kh);

// 计算第n个Kh=Vh/（Is*Im*K）变更Is
double MyUtils_MeasurementKh_Is(void);

// 计算第n个Kh=Vh/（Is*Im*K）变更Im
double MyUtils_MeasurementKh_Im(void);

// 延时器（单位毫秒）
void MyUtils_DelayTime(uint32_t milliseconds);

// 前置自动化测试
void MyUtils_Test(void);

// 获取Vh绝对值(10-e3)
float MyUtils_GetVh(void);

// 自动测试By
void MyUtils_Test_By(void);

#endif
