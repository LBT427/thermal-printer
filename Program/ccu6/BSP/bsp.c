/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-07-07 23:31:09
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-07-08 16:37:37
 * @FilePath: \ccu6\BSP\bsp.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "bsp.h"


TIM_HandleTypeDef TIM3_Handler;                           //定时器句柄 
void BASIC_TIMx_Init(void)
{
 
	TIM3_Handler.Instance           =  BASIC_TIMx;            //定时器选择
	TIM3_Handler.Init.Prescaler     =  BASIC_TIMx_PRESCALER;  //预分频值
	TIM3_Handler.Init.Period        =  BASIC_TIMx_PERIOD;     //自动重装载值
	TIM3_Handler.Init. CounterMode  =  BASIC_TIM_MODE;        //计数模式
	TIM3_Handler.Init.ClockDivision =  BASIC_TIM_DIVISION;    //时钟分频
	HAL_TIM_Base_Init(&TIM3_Handler);                         //初始化定时器
    HAL_TIM_Base_Start_IT(&TIM3_Handler);				      //开启定时器中断

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
   /* 基本定时器外设时钟使能 */
    BASIC_TIM_RCC_CLK_ENABLE();
 
    /* 外设中断配置 */
    HAL_NVIC_SetPriority(BASIC_TIM_IRQ, 1, 0);
    HAL_NVIC_EnableIRQ(BASIC_TIM_IRQ);//使能中断
 
}

//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM3_Handler);//调用HAL库中的中断服务函数
}
void bsp_init(void)
{
  
    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_USART1_UART_Init();
    MX_USB_DEVICE_Init();
    BASIC_TIMx_Init();

    motor_init();  //步进电机初始化
	printer_init();//打印头初始化


}

//回调函数，定时器中断服务函数调用。10ms中断一次
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&TIM3_Handler))
    {
		 
        // motor_revolve();
		
	}
}
