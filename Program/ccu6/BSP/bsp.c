/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-07 23:31:09
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-08 16:37:37
 * @FilePath: \ccu6\BSP\bsp.c
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "bsp.h"


TIM_HandleTypeDef TIM3_Handler;                           //��ʱ����� 
void BASIC_TIMx_Init(void)
{
 
	TIM3_Handler.Instance           =  BASIC_TIMx;            //��ʱ��ѡ��
	TIM3_Handler.Init.Prescaler     =  BASIC_TIMx_PRESCALER;  //Ԥ��Ƶֵ
	TIM3_Handler.Init.Period        =  BASIC_TIMx_PERIOD;     //�Զ���װ��ֵ
	TIM3_Handler.Init. CounterMode  =  BASIC_TIM_MODE;        //����ģʽ
	TIM3_Handler.Init.ClockDivision =  BASIC_TIM_DIVISION;    //ʱ�ӷ�Ƶ
	HAL_TIM_Base_Init(&TIM3_Handler);                         //��ʼ����ʱ��
    HAL_TIM_Base_Start_IT(&TIM3_Handler);				      //������ʱ���ж�

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
   /* ������ʱ������ʱ��ʹ�� */
    BASIC_TIM_RCC_CLK_ENABLE();
 
    /* �����ж����� */
    HAL_NVIC_SetPriority(BASIC_TIM_IRQ, 1, 0);
    HAL_NVIC_EnableIRQ(BASIC_TIM_IRQ);//ʹ���ж�
 
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM3_Handler);//����HAL���е��жϷ�����
}
void bsp_init(void)
{
  
    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_USART1_UART_Init();
    MX_USB_DEVICE_Init();
    BASIC_TIMx_Init();

    motor_init();  //���������ʼ��
	printer_init();//��ӡͷ��ʼ��


}

//�ص���������ʱ���жϷ��������á�10ms�ж�һ��
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&TIM3_Handler))
    {
		 
        // motor_revolve();
		
	}
}
