/*
 * hhFoc.c
 *
 *  Created on: Mar 12, 2025
 *      Author: KingPC
 */



#include"hhFoc.h"
#include"math.h"
#include"tim.h"
#include"../hhPwm/hhPwm.h"
#include "../hhSerial/hhSerial.h"
#include "../hhAS5600/hhAS5600.h"
struct Motor Motor0 = { 0 };
float voltage_power_supply;
int PP;
int DIR;
//限制只能输出low~high之间的数值
double _constrain(double amt, double low, double high) {
	if (amt < low) {
		return low;
	} else if (amt > high) {
		return high;
	} else {
		return amt;
	}
}
//限定角度只能是0~360度，不能出现负角度
float _normalizeAngle(float angle) {
	float a = fmod(angle, 2 * M_PI);  //取余保证角度是-360~360度
	if (a >= 0) {
		return a;
	} else {
		return a + 2 * M_PI;
	}
}
//由计算出三相电压设定PWM
void SetPwm(struct Motor *Motor) {
	//限制电压为0~最大设定电压
	Motor->Ua = _constrain(Motor->Ua, 0.0f, voltage_power_supply);
	Motor->Ub = _constrain(Motor->Ub, 0.0f, voltage_power_supply);
	Motor->Uc = _constrain(Motor->Uc, 0.0f, voltage_power_supply);
	//计算占空比并限定占空比的取值范围为0~1
	Motor->dc_a = _constrain(Motor->Ua / voltage_power_supply, 0.0f, 1.0f);
	Motor->dc_b = _constrain(Motor->Ub / voltage_power_supply, 0.0f, 1.0f);
	Motor->dc_c = _constrain(Motor->Uc / voltage_power_supply, 0.0f, 1.0f);
	//写入PWM,详情请看《5、ESP32前置知识.md》
	if (Motor->Mot_num == 0) {
		M0SetPwmA(Motor->dc_a);
		M0SetPwmB(Motor->dc_b);
		M0SetPwmC(Motor->dc_c);
	}
}
void setPhaseVoltage(struct Motor *Motor, float Uq, float Ud, float angle_el) {
	Uq = _constrain(Uq, -(voltage_power_supply) / 2,
			(voltage_power_supply) / 2);
	angle_el = _normalizeAngle(angle_el);
	// 帕克逆变换
	Motor->Ualpha = -Uq * sin(angle_el);
	Motor->Ubeta = Uq * cos(angle_el);
	// 克拉克逆变换
	Motor->Ua = Motor->Ualpha + voltage_power_supply / 2;
	Motor->Ub = (sqrt(3) * Motor->Ubeta - Motor->Ualpha) / 2 + voltage_power_supply / 2;
	Motor->Uc = (-Motor->Ualpha - sqrt(3) * Motor->Ubeta) / 2 + voltage_power_supply / 2;
	  //这里三相的每一相都 + voltage_power_supply/2;作用
	  //1.这里的三相Ua/Ub/Uc是参与Pwm计算的，而PWM在单片机中PWM输出电压输出范围是0V到供电电压Vdc(单片机)，不加voltage_power_supply/2 的话三相都有可能出现负数，导致单片机无法输出PWM(单片机无法输出负电压的PWM)
	  //2.这里还有一个干扰理解的，FOC三相中，在6步换相中，某一相肯定在某个时刻是电流流入(正电压)，某一其他时刻是电流流出(负电压)的，为什么前面说不能有负电压呢？
	  //3.其实并不冲突，首先肯定的是第2点中FOC换相时某一相在不同时刻会有正电压和负电压。这一相的正负电压就是由第1点的PWM(都是正电压没有负电压)产生了的。要理解这点就需要知道3路PWM是如何控制6个MOS管的了
	  //4.1路PWM可以控制2个半桥(上桥臂和下桥臂)
	  //**PWM为高电平时**：上桥臂MOS管导通，下桥臂MOS管关断，将电源电压施加到相应的绕组上。
	  //**PWM为低电平时**：上桥臂MOS管关断，在上桥臂关断后，稍等一段时间(死区时间，防止上下桥臂有短暂的导通造成短路)再让下桥臂导通。
	  //也就是说某一路PWM(都是正电压没有负电压)为高电平时，上桥臂导通，对应Ua线圈电流流入，这时Ua为正电压;PWM(都是正电压没有负电压)为低电平时,上桥臂关断,下桥臂导通。此时有可能在Ua线圈电流流出，这时Ua为负电压。
	SetPwm(Motor);
}
void hhFocInit(float power_supply, int _PP, int _DIR) {
	PP = _PP;
	DIR = _DIR;
	voltage_power_supply = power_supply;
	InitPwm();
	StartSerialITReceive();
	MyI2C_Init();
	HAL_TIM_Base_Start_IT(&htim4);
//	Serial_Printf("%s\r\n", "完成PWM初始化设置");
	printf("finish pwm init\n");
}
void SetsetPhaseVoltageM0(float Uq, float Ud, float angle_el) {
	setPhaseVoltage(&Motor0, Uq, Ud, angle_el);
}
float OpenLoopShaftAngle=0;
void hhOpenLoopVelM0(float target_velocity){
  //计算当前每个Loop的运行时间间隔
  float Ts = 1 * 1e-3f;
  // 通过乘以时间间隔和目标速度来计算需要转动的机械角度，存储在 shaft_angle 变量中。在此之前，还需要对轴角度进行归一化，以确保其值在 0 到 2π 之间。
  OpenLoopShaftAngle = _normalizeAngle(OpenLoopShaftAngle + target_velocity*Ts);
  float Uq = voltage_power_supply/3;
  SetsetPhaseVoltageM0(Uq,  0, PP * OpenLoopShaftAngle);
}

