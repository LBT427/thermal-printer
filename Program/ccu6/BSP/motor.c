/*
 * @Author: liubotao
 * @Date: 2022-07-07 22:02:05
 * @LastEditors: user.name 
 * @LastEditTime: 2022-07-18 00:16:30
 * @FilePath: \ccu6\BSP\motor.c
 * @Description: 
 * 
 */

#include "motor.h"

motor_t Stepper_motor={0};

/*
*********************************************************************************************************
*	函 数 名: motor_stop
*	功能说明: 步进电机停止
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void motor_stop(void)  
{  
    MOTOR_1(0);
    MOTOR_2(0);
    MOTOR_3(0);
    MOTOR_4(0);
}
/*
*********************************************************************************************************
*	函 数 名: motor_init
*	功能说明: 步进电机初始化
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void motor_init(void)
{
    // GPIO初始化

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);

    /*Configure GPIO pins : PA3 PA4 PA5 PA6 */
    GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


    //结构体初始化

    Stepper_motor.step_time = 10;      //两步间隔10ms
    Stepper_motor.direction = advance; //转动方向
}

void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
  GPIOx->ODR = PortVal;
}
/*
*********************************************************************************************************
*	函 数 名: Stepper_motor_GPIO_Write
*	功能说明: 步进电机GPIO写入
*	形    参:  direction  方向
*	返 回 值: 无
*********************************************************************************************************
*/
void Stepper_motor_GPIO_Write(uint8_t direction,uint8_t num)
{
    //int num = Stepper_motor.step_number % 4; //计算当前步数是第几步
    if (direction)
    {
        if (num == 0)
        {
            MOTOR_1(1);
            MOTOR_2(0);
            MOTOR_3(0);
            MOTOR_4(1);
        }
        else if (num == 1)
        {
            MOTOR_1(1);
            MOTOR_2(0);
            MOTOR_3(0);
            MOTOR_4(0);
        }
        else if (num == 2)
        {
            MOTOR_1(0);
            MOTOR_2(1);
            MOTOR_3(0);
            MOTOR_4(1);
        }
        else if (num == 3)
        {
            MOTOR_1(0);
            MOTOR_2(0);
            MOTOR_3(1);
            MOTOR_4(0);
        }
    }
    else
    {
        if (num == 0)
        {
            MOTOR_1(0);
            MOTOR_2(0);
            MOTOR_3(1);
            MOTOR_4(0);
        }
        else if (num == 1)
        {
            MOTOR_1(0);
            MOTOR_2(1);
            MOTOR_3(0);
            MOTOR_4(1);
        }
        else if (num == 2)
        {
            MOTOR_1(1);
            MOTOR_2(0);
            MOTOR_3(0);
            MOTOR_4(0);
        }
        else if (num == 3)
        {
            MOTOR_1(1);
            MOTOR_2(0);
            MOTOR_3(0);
            MOTOR_4(1);
        }
    }
}
/*
*********************************************************************************************************
*	函 数 名: set_motor_turn
*	功能说明: 设置电机转动,电机在中断中转动
*	形    参: direction 转动方向   step_number 转动步数  step_time 步间隔时间（10ms分辨率）
*	返 回 值: 无
*********************************************************************************************************
*/
void set_motor_turn(uint8_t direction,uint16_t step_number,uint8_t step_time)
{
    Stepper_motor.direction = direction;
    Stepper_motor.step_number = step_number;
    Stepper_motor.step_time = step_time;
}

/*
*********************************************************************************************************
*	函 数 名: motor_turn_now
*	功能说明: 设置电机转动,电机在中断中转动
*	形    参: direction 转动方向   step_number 转动步数  step_time 步间隔时间
*	返 回 值: 无
*********************************************************************************************************
*/
void motor_turn_now(uint8_t direction,uint16_t step_number,uint8_t step_time)
{
    for (uint16_t num = 0; num <= step_number; num++)
    {
        Stepper_motor_GPIO_Write(direction,num % 4);
        HAL_Delay(step_time);
		motor_stop();
		//Stepper_motor.step_number--;
       
    }

}


/*
*********************************************************************************************************
*	函 数 名: motor_revolve
*	功能说明: 电机转动 被10ms中断调用
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void motor_revolve() 
{  
   
    Stepper_motor.revolve_time+=10;//步进计时
    if(Stepper_motor.step_number == 0)//如果步数为0，则停止转动
    {
       return;
    }
    else if(Stepper_motor.revolve_time < Stepper_motor.step_time)
    {
          //计算当前步数是第几步

        Stepper_motor_GPIO_Write(Stepper_motor.direction,(Stepper_motor.step_number) % 4);//步进计时到了，步进一步
        Stepper_motor.step_number--;//步数减一
        Stepper_motor.revolve_time = 0;//步进计时重新计时
    }

}


// //由于   *一个脉冲*   *输出轴*  转0.08789度（电机实转0.08789*64=5.625度），即步进角为5.625度。则转完A-B-C-D为  *8个脉冲*  
// //，即0.08789*8=0.70312度。若称A-B-C-D为一个周期，则j为需要的转完angle角度所需的周期数。
// //步进电机正转角度函数
// void motor_just_angle(int angle,int speed)
// {
// 	int i,j;
// 	j=(int)(angle/0.70312);
// 	for(i=0;i<j;i++)
// 	{
// 		motor_just(speed);
// 	}
// 	motor_stop();
// }
// //步进电机反转角度函数
// void motor_back_angle(int angle,int speed)
// {
// 	int i,j;
// 	j=(int)(angle/0.70312);
// 	for(i=0;i<j;i++)
// 	{
// 		motor_back(speed);
// 	}
// 	motor_stop();
// }
// //步进电机反转圈函数
// void motor_back_circle(int ring ,int speed)
// {
// 	int i;
// 	for(i=0;i<ring;i++)
// 	{
//         motor_back_angle(360,speed);
// 	}
// }

// //步进电机正转圈函数
// void motor_just_circle(int ring,int speed) //步进电机正转角度函数
// {
// 	int i;
// 	for(i=0;i<ring;i++)
// 	{
//         motor_just_angle(360,speed);
// 	}
// }
