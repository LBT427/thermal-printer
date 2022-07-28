#ifndef _BSP_H
#define _BSP_H


#include "main.h"
#include "adc.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"
#include "motor.h"
#include "printer.h"


void bsp_init(void);


// ���嶨ʱ��Ԥ��Ƶ����ʱ��ʵ��ʱ��Ƶ��Ϊ��72MHz/��BASIC_TIMx_PRESCALER+1��
#define BASIC_TIMx_PRESCALER 83
// ���嶨ʱ�����ڣ�����ʱ����ʼ������BASIC_TIMx_PERIODֵ�Ǹ��¶�ʱ�������ɶ�Ӧ�¼����ж�
#define BASIC_TIMx_PERIOD 9999

#define BASIC_TIMx TIM3
#define BASIC_TIM_RCC_CLK_ENABLE() __HAL_RCC_TIM3_CLK_ENABLE()
#define BASIC_TIM_RCC_CLK_DISABLE() __HAL_RCC_TIM3_CLK_DISABLE()
#define BASIC_TIM_IRQ       TIM3_IRQn
#define BASIC_TIM_INT_FUN   TIM3_IRQHandler
#define BASIC_TIM_MODE       TIM_COUNTERMODE_UP
#define BASIC_TIM_DIVISION   TIM_CLOCKDIVISION_DIV1                          
                           
extern TIM_HandleTypeDef TIM3_Handler; //��ʱ�����

//void BASIC_TIMx_Init(void);
//void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base);



//void delay_us(uint32_t nTimer)
//{

//	for(uint32_t i=0;i<nTimer;i++){
//		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
//        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
//        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
//        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
//        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
//        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
//        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
//        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
//        __NOP();__NOP();__NOP();__NOP();
//	}

//}





#endif
