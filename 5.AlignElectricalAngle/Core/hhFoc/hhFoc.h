/*
 * hhFoc.h
 *
 *  Created on: Mar 12, 2025
 *      Author: KingPC
 */

#ifndef HHFOC_HHFOC_H_
#define HHFOC_HHFOC_H_

struct Motor{
	int Mot_num;
	float zero_electric_angle;
	float Ua;
	float Ub;
	float Uc;
	float Ubeta;
	float Ualpha;
	float dc_a;
	float dc_b;
	float dc_c;
};

void hhFocInit(float power_supply, int _PP, int _DIR);
void SetsetPhaseVoltageM0( float Uq, float Ud, float angle_el);
void hhOpenLoopVelM0(float target_velocity);

#endif /* HHFOC_HHFOC_H_ */
