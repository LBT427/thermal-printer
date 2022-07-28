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
*	�� �� ��: motor_stop
*	����˵��: �������ֹͣ
*	��    ��: ��
*	�� �� ֵ: ��
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
*	�� �� ��: motor_init
*	����˵��: ���������ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void motor_init(void)
{
    // GPIO��ʼ��

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);

    /*Configure GPIO pins : PA3 PA4 PA5 PA6 */
    GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


    //�ṹ���ʼ��

    Stepper_motor.step_time = 10;      //�������10ms
    Stepper_motor.direction = advance; //ת������
}

void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
  GPIOx->ODR = PortVal;
}
/*
*********************************************************************************************************
*	�� �� ��: Stepper_motor_GPIO_Write
*	����˵��: �������GPIOд��
*	��    ��:  direction  ����
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Stepper_motor_GPIO_Write(uint8_t direction,uint8_t num)
{
    //int num = Stepper_motor.step_number % 4; //���㵱ǰ�����ǵڼ���
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
*	�� �� ��: set_motor_turn
*	����˵��: ���õ��ת��,������ж���ת��
*	��    ��: direction ת������   step_number ת������  step_time �����ʱ�䣨10ms�ֱ��ʣ�
*	�� �� ֵ: ��
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
*	�� �� ��: motor_turn_now
*	����˵��: ���õ��ת��,������ж���ת��
*	��    ��: direction ת������   step_number ת������  step_time �����ʱ��
*	�� �� ֵ: ��
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
*	�� �� ��: motor_revolve
*	����˵��: ���ת�� ��10ms�жϵ���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void motor_revolve() 
{  
   
    Stepper_motor.revolve_time+=10;//������ʱ
    if(Stepper_motor.step_number == 0)//�������Ϊ0����ֹͣת��
    {
       return;
    }
    else if(Stepper_motor.revolve_time < Stepper_motor.step_time)
    {
          //���㵱ǰ�����ǵڼ���

        Stepper_motor_GPIO_Write(Stepper_motor.direction,(Stepper_motor.step_number) % 4);//������ʱ���ˣ�����һ��
        Stepper_motor.step_number--;//������һ
        Stepper_motor.revolve_time = 0;//������ʱ���¼�ʱ
    }

}


// //����   *һ������*   *�����*  ת0.08789�ȣ����ʵת0.08789*64=5.625�ȣ�����������Ϊ5.625�ȡ���ת��A-B-C-DΪ  *8������*  
// //����0.08789*8=0.70312�ȡ�����A-B-C-DΪһ�����ڣ���jΪ��Ҫ��ת��angle�Ƕ��������������
// //���������ת�ǶȺ���
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
// //���������ת�ǶȺ���
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
// //���������תȦ����
// void motor_back_circle(int ring ,int speed)
// {
// 	int i;
// 	for(i=0;i<ring;i++)
// 	{
//         motor_back_angle(360,speed);
// 	}
// }

// //���������תȦ����
// void motor_just_circle(int ring,int speed) //���������ת�ǶȺ���
// {
// 	int i;
// 	for(i=0;i<ring;i++)
// 	{
//         motor_just_angle(360,speed);
// 	}
// }
