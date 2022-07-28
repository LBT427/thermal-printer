/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-07 22:02:17
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-12 14:26:11
 * @FilePath: \ccu6\BSP\motor.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _MOTOR_H
#define _MOTOR_H

#include "main.h"

#define advance  0
#define renegade 1

typedef struct motor
{
    uint8_t revolve_time; //运行的步时间，每10ms中断会加10，


    uint8_t step_number; //步数
    uint8_t direction;   //转动方向

    uint8_t step_time;  //设置的步时间

    uint8_t circle;      //设定的圈数
    uint8_t angle;       //设定的角度


    // uint8_t Pulse_number;//设定的脉冲数
    // uint8_t Pulse_speed; //脉冲速度
    // uint8_t Pulse_time;  //脉冲时间
}motor_t;

//步进电机正反转数组1
static uint16_t PositiveSequence[4] ={0x0200,0x0100,0x0080,0x0040};// D-C-B-A   
static uint16_t ReverseOrder[4]={0x0040,0x0080,0x0100,0x0200};// A-B-C-D.

void motor_revolve(void);//电机转动 被10ms中断调用  
void motor_init(void);  //步进电机初始化
void Stepper_motor_GPIO_Write(uint8_t direction,uint8_t num);//步进电机GPIO写入
void set_motor_turn(uint8_t direction,uint16_t step_number,uint8_t step_time);//设置电机转动,电机在中断中转动
void motor_turn_now(uint8_t direction,uint16_t step_number,uint8_t step_time);//电机在主函数中阻塞转动
void motor_just_angle(int angle,int speed);  //步进电机正转角度函数
void motor_back_angle(int angle,int speed); //步进电机反转角度函数
void motor_just_circle(int ring,int speed); //步进电机正转圈函数
void motor_back_circle(int ring,int speed);//步进电机反转圈函数
void motor_stop(void);//步进电机停止

//IN

#define MOTOR_1_Pin  GPIO_PIN_3
#define MOTOR_2_Pin  GPIO_PIN_4
#define MOTOR_3_Pin  GPIO_PIN_5
#define MOTOR_4_Pin  GPIO_PIN_6

#define MOTOR_1(x)  x?(GPIOA->BSRR=((1<<3))):(GPIOA->BSRR=(1<<3)<<16U)
#define MOTOR_2(x)  x?(GPIOA->BSRR=((1<<4))):(GPIOA->BSRR=(1<<4)<<16U)												     
#define MOTOR_3(x)  x?(GPIOA->BSRR=((1<<5))):(GPIOA->BSRR=(1<<5)<<16U)	
#define MOTOR_4(x)  x?(GPIOA->BSRR=((1<<6))):(GPIOA->BSRR=(1<<6)<<16U)	

#endif

