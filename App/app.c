
#include "includes.h"

static OS_STK START_TASK_STK[START_TASK_STK_SIZE];   /*创建任务堆栈*/
void start_task(void *pdata);    /*声明任务函数*/


static OS_STK LED0_TASK_STK[LED0_STK_SIZE];            

void led0_task(void *pdata);  


static OS_STK LED1_TASK_STK[LED1_STK_SIZE];             

void led1_task(void *pdata); 


static OS_STK LED2_TASK_STK[LED2_STK_SIZE];             

void led2_task(void *pdata); 


static OS_STK BEEP_TASK_STK[BEEP_STK_SIZE];             

void beep_task(void *pdata); 


static OS_STK PWM_TASK_STK[PWM_STK_SIZE];             

void pwm_task(void *pdata); 


static OS_STK ADC_TASK_STK[ADC_STK_SIZE];             

void adc_task(void *pdata); 



int main(void)
{
   BSP_Init();     /*底层外设初始化*/
   OSInit();     /*操作系统初始化*/
    
   /*创建任务*/ 
   OSTaskCreate(  start_task,    /*任务函数指针*/ 
                  (void *)0,      /*传递给任务的参数*/
                  &START_TASK_STK[START_TASK_STK_SIZE - 1],     /*任务栈顶指针*/
                  START_TASK_PRIO      /*任务优先级*/
              );
   
   OSStart();      /*启动任务*/
   return 0;
}

void start_task(void *pdata)
{
    (void)pdata;                 

    
    OSTaskCreate( led0_task,
								  (void *)0,
								  &LED0_TASK_STK[LED0_STK_SIZE-1],
								  LED0_TASK_PRIO
								);                                         
    OSTaskCreate( led1_task,
									(void *)0,
									&LED1_TASK_STK[LED1_STK_SIZE-1],
									LED1_TASK_PRIO
								); 
    
		OSTaskCreate( led2_task,
									(void *)0,
									&LED2_TASK_STK[LED2_STK_SIZE-1],
									LED2_TASK_PRIO
								);  
    OSTaskCreate( beep_task,
									(void *)0,
									&BEEP_TASK_STK[BEEP_STK_SIZE-1],
									BEEP_TASK_PRIO
								);     
    OSTaskCreate( pwm_task,
									(void *)0,
									&PWM_TASK_STK[PWM_STK_SIZE-1],
									PWM_TASK_PRIO
								);  
    OSTaskCreate( adc_task,
									(void *)0,
									&ADC_TASK_STK[ADC_STK_SIZE-1],
									ADC_TASK_PRIO
								);                                 
    OSTaskSuspend(START_TASK_PRIO);       
    OSTaskDel (OS_PRIO_SELF);                        
}


void led0_task(void *pdata)
{   
    INT32U tick = 0;
   (void)pdata;
	 while(1)
	 {  
      if (tick % 2 == 0)
          GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
			else     
          GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
      tick++;
			OSTimeDlyHMSM(0, 0, 0, 200);   
	 }
}

 

void led1_task(void *pdata)
{  
    INT32U tick = 0;
   (void)pdata;
	 while(1)
	 {
      if (tick % 2 == 0)
          GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
			else   
          GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
      tick++;
			OSTimeDlyHMSM(0, 0, 0, 400);   
	 }
}


void led2_task(void *pdata)
{   
    INT32U tick = 0;
   (void)pdata;
	 while(1)
	 {
      if (tick % 2 == 0)
          GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET);
			else   
          GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET);
      tick++;
			OSTimeDlyHMSM(0, 0, 0, 600);   
	 }
}


void beep_task(void *pdata)
{ 
   INT32U tick = 0;
   (void)pdata;
   while(1)
	 {
      if(tick % 2 == 0)
          TIM_CtrlPWMOutputs(TIM1, ENABLE); //ENABLE or DISABLE
      
      else
          TIM_CtrlPWMOutputs(TIM1, DISABLE); //ENABLE or DISABLE  
      tick++;
      OSTimeDlyHMSM(0, 0, 0, 500);     
	 }
}


void pwm_task(void *pdata)
{   
    INT32U tick = 0;
   (void)pdata;
	 while(1)
	 {    
      if(tick % 2 == 0)
          TIM_CtrlPWMOutputs(TIM4, DISABLE); //ENABLE or DISABLE
      else
          TIM_CtrlPWMOutputs(TIM4, ENABLE); //ENABLE or DISABLE
      tick++;
			OSTimeDlyHMSM(0, 0, 0, 500);   
	 }
}

void adc_task(void *pdata)
{   
   extern volatile uint16_t ADC_values[];
   (void)pdata;
	 while(1)
	 {    
      uint8_t pwmwave = 0; //ad采样转换为pwm值调节RGB_B RGB_R的亮度
      uint8_t index;
      uint16_t value[2];
      for(index = 0; index<2; index++) //2 channel
      {
          value[index] = (uint16_t)((ADC_values[index]+ADC_values[index+2]+ADC_values[index+4]+ADC_values[index+6])/4);
      }
      pwmwave = value[0] >> 8;
      TIM2->CCR1 = pwmwave;
      pwmwave = value[1] >> 8;
      TIM2->CCR2 = pwmwave;
			OSTimeDly(10);   
	 }
}




