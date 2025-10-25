/*
 * hhPwm.c
 *
 *  Created on: Mar 11, 2025
 *      Author: KingPC
 */

#include "tim.h"
void InitPwm(){
	   HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	   HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	   HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
}
void M0SetPwmA(float Duty){
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,Duty * 4800.0f);
}
void M0SetPwmB(float Duty){
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,Duty * 4800.0f);
}
void M0SetPwmC(float Duty){
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,Duty * 4800.0f);
}


