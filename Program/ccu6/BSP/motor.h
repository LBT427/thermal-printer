/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-07 22:02:17
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-12 14:26:11
 * @FilePath: \ccu6\BSP\motor.h
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _MOTOR_H
#define _MOTOR_H

#include "main.h"

#define advance  0
#define renegade 1

typedef struct motor
{
    uint8_t revolve_time; //���еĲ�ʱ�䣬ÿ10ms�жϻ��10��


    uint8_t step_number; //����
    uint8_t direction;   //ת������

    uint8_t step_time;  //���õĲ�ʱ��

    uint8_t circle;      //�趨��Ȧ��
    uint8_t angle;       //�趨�ĽǶ�


    // uint8_t Pulse_number;//�趨��������
    // uint8_t Pulse_speed; //�����ٶ�
    // uint8_t Pulse_time;  //����ʱ��
}motor_t;

//�����������ת����1
static uint16_t PositiveSequence[4] ={0x0200,0x0100,0x0080,0x0040};// D-C-B-A   
static uint16_t ReverseOrder[4]={0x0040,0x0080,0x0100,0x0200};// A-B-C-D.

void motor_revolve(void);//���ת�� ��10ms�жϵ���  
void motor_init(void);  //���������ʼ��
void Stepper_motor_GPIO_Write(uint8_t direction,uint8_t num);//�������GPIOд��
void set_motor_turn(uint8_t direction,uint16_t step_number,uint8_t step_time);//���õ��ת��,������ж���ת��
void motor_turn_now(uint8_t direction,uint16_t step_number,uint8_t step_time);//�����������������ת��
void motor_just_angle(int angle,int speed);  //���������ת�ǶȺ���
void motor_back_angle(int angle,int speed); //���������ת�ǶȺ���
void motor_just_circle(int ring,int speed); //���������תȦ����
void motor_back_circle(int ring,int speed);//���������תȦ����
void motor_stop(void);//�������ֹͣ

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

