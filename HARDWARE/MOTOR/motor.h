#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"
#include "timer.h"
#include "delay.h"

void motor1_go(u16 pwm);
void motor1_back(u16 pwm);
void motor1_stop(void);
void motor2_go(u16 pwm);
void motor2_back(u16 pwm);
void motor2_stop(void);
void left(void);
void right(void);
void go(void);
void stop(void);

#endif



