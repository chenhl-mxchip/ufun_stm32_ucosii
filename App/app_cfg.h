#ifndef __APP_CFG_H__
#define __APP_CFG_H__


//START task
#define START_TASK_PRIO        4     /*TaskStart�������ȼ�Ϊ0*/
#define START_TASK_STK_SIZE    128    /*TaskStart����Ķ�ջ��С*/
                               
                     
//LED0 task

#define LED0_TASK_PRIO         5            
#define LED0_STK_SIZE          32           

                                              

//LED1  task

#define LED1_TASK_PRIO         6            

#define LED1_STK_SIZE          32           

        

//LED2  task

#define LED2_TASK_PRIO          7            

#define LED2_STK_SIZE           32           


//Beep  task
#define BEEP_TASK_PRIO          8            

#define BEEP_STK_SIZE           32   


//PWM   task
#define PWM_TASK_PRIO           9            

#define PWM_STK_SIZE            32   


//ADC    task  
#define ADC_TASK_PRIO           10            

#define ADC_STK_SIZE            64  



#endif

