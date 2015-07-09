#include "bsp.h"
#include "includes.h"


void RCC_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}


void GPIO_LED_Config(void)
{	
	 GPIO_InitTypeDef GPIO_InitStructure;//����ṹ��
    /* GPIOA clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;  //GPIO_Pin_0|GPIO_Pin_1|
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* GPIOA clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}


/**************************************************************/
//�� �� ���� beep_init()
//�� �� �ߣ� MingH
//��ڲ����� ��
//����˵���� ��������ʼ�� 2.6Khz
//**************************************************************/
void  Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	uint16_t CCR1_Val = 1538;  //1538  2.6K  
	uint16_t PrescalerValue = 0;

	/* GPIOA clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);

	/* BEEP -- GPIOPA8 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);


	/* -----------------------------------------------------------------------
	   TIM1 Frequency = TIM1 counter clock/(ARR + 1)
	   TIM1 Channel1 duty cycle = (TIM1_CCR1/ TIM1_ARR)* 100 = 10%
	   TIM1 Channel2 duty cycle = (TIM1_CCR2/ TIM1_ARR)* 100 = 37.5%
	   TIM1 Channel3 duty cycle = (TIM1_CCR3/ TIM1_ARR)* 100 = 25%
	   TIM1 Channel4 duty cycle = (TIM1_CCR4/ TIM1_ARR)* 100 = 12.5%
	   ----------------------------------------------------------------------- */
	/* Compute the prescaler value */
	PrescalerValue = (uint16_t) (SystemCoreClock / 8000000) - 1; 
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 3076; //3076 2.6K   2000 4K
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 

	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;  
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;        

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	TIM_ARRPreloadConfig(TIM1, ENABLE);

	/* TIM1 enable counter */
	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, DISABLE); //ENABLE or DISABLE

}



/**************************************************************/
//�� �� ���� PWM_init()
//�� �� �ߣ� chenhonglin
//��ڲ����� ��
//����˵���� pwm��ʼ�����2.6Khz
//**************************************************************/
void  Pwm_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	uint16_t CCR1_Val = 1538;
	uint16_t PrescalerValue = 0;

	/* GPIOB clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM4 | RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);

	/************************
  PWMCH1-- GPIOPB8 
  PWMCH2-- GPIOPB9
  *************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOB, &GPIO_InitStructure);


	/* -----------------------------------------------------------------------
	   TIM4 Frequency = TIM4 counter clock/(ARR + 1)
	   TIM4 Channel1 duty cycle = (TIM4_CCR1/ TIM4_ARR)* 100 = 10%
	   TIM4 Channel2 duty cycle = (TIM4_CCR2/ TIM4_ARR)* 100 = 37.5%
	   TIM4 Channel3 duty cycle = (TIM4_CCR3/ TIM4_ARR)* 100 = 25%
	   TIM4 Channel4 duty cycle = (TIM4_CCR4/ TIM4_ARR)* 100 = 12.5%
	   ----------------------------------------------------------------------- */
	/* Compute the prescaler value */
	PrescalerValue = (uint16_t) (SystemCoreClock / 8000000) - 1; 
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 3076;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;  
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;        

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);

	TIM_ARRPreloadConfig(TIM4, ENABLE);

	/* TIM1 enable counter */
	TIM_Cmd(TIM4, ENABLE);
	TIM_CtrlPWMOutputs(TIM4, DISABLE); //ENABLE or DISABLE

}


/**************************************************************/
//�� �� ���� TIM2_Config()
//�� �� �ߣ� chenhonglin
//��ڲ����� ��
//����˵���� ��ʱ������ʱ�����ú�PWM����
//**************************************************************/
void TIM2_Config(void)
{
    TIM_OCInitTypeDef  TIM_OCInitStructure;//����ṹ��
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ;//����ṹ��
    /* �򿪶�ʱ��2����ʱ�� */ 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
                          
		/* ��ʱ��2������ʱ������ */
		/* ��ʱ����0������0xffΪһ����ʱ���� */
    TIM_TimeBaseStructure.TIM_Period = 0xff;
	
		/* ����Ԥ��Ƶ 2000 ��Ƶ */
    TIM_TimeBaseStructure.TIM_Prescaler = 1000;
	
		/* ����ʱ�ӷ�Ƶϵ�����˴�δ��Ƶ */
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
		/* ���ϼ���ģʽ */
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
		/* ������ʱ����ʼ�� */
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    
		
		//******************************//
    /* ��ʱ��2PWM����  CH1  PWM1 ģʽ */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		
		/* ʹ����� */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		
		/* ���ó�ʼ PWM ������Ϊ 0 */
    TIM_OCInitStructure.TIM_Pulse = 0;
		
		/* ����ʱ������ֵС�� TIM_Pulse ʱΪ�͵�ƽ */
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
		
		/* TIM2��CH1��ʼ�� */
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);
		
		/* ʹ�ܵ�Ԥװ�ؼĴ��� */
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
		
		
		//******************************//
    /* ��ʱ��2PWM����  CH2  PWM1 ģʽ */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		
		/* ʹ����� */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		
		/* ���ó�ʼ PWM ������Ϊ 0 */
    TIM_OCInitStructure.TIM_Pulse = 0;
		
		/* ����ʱ������ֵС�� TIM_Pulse ʱΪ�͵�ƽ */
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
		
		/* TIM2��CH2��ʼ�� */
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);
		
		/* ʹ�ܵ�Ԥװ�ؼĴ��� */
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
				
		
    /* ʹ�� TIM2 ���ؼĴ��� ARR */
    TIM_ARRPreloadConfig(TIM2, ENABLE);
		
    /* ʹ�ܶ�ʱ��2 */
    TIM_Cmd(TIM2, ENABLE);
		
		/* ʹ�ܶ�ʱ��2�� update�ж� */
    //TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);
}
/**************************************************************/
//�� �� ���� ADC_GPIO_Config()
//�� �� �ߣ� chenhonglin
//��ڲ����� ��
//����˵���� ADC GPIO����
//**************************************************************/
void ADC_GPIO_Config(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ��
	/* GPIOA clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	/* TIM2 PWM Channel1 -- GPIOPA0 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* GPIOA clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}

////////////////////////////////////////////////////////////////
#define ARRAYSIZE 2*4   //2ͨ��*4�ֽ�
#define ADC1_DR_Address    ((uint32_t)0x4001244C)
volatile uint16_t ADC_values[ARRAYSIZE];

/**************************************************************/
//�� �� ���� ADC_Config()
//�� �� �ߣ� chenhonglin
//��ڲ����� ��
//����˵���� ADC����
//**************************************************************/
void ADC_Config(void)
{ 
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 ;   // PC2 -> AD_SIG1  PC3-> AD_SIG2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
  
    
    //ADC1 configuration
    //select continuous conversion mode
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    //We will convert multiple channels
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    //we will convert one time
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//
    //select no external triggering
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    //right 12-bit data alignment in ADC data register
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    //2 channels conversion
    ADC_InitStructure.ADC_NbrOfChannel = 2;
    //load structure values to control and status registers
    ADC_Init(ADC1, &ADC_InitStructure);
    
    //configure each channel
    ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 1, ADC_SampleTime_41Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 2, ADC_SampleTime_41Cycles5);
    //Enable ADC1
    ADC_Cmd(ADC1, ENABLE);
    //enable DMA for ADC
    ADC_DMACmd(ADC1, ENABLE);
    //Enable ADC1 reset calibration register
    ADC_ResetCalibration(ADC1);
    //Check the end of ADC1 reset calibration register
    while(ADC_GetResetCalibrationStatus(ADC1));
    //Start ADC1 calibration
    ADC_StartCalibration(ADC1);
    //Check the end of ADC1 calibration
    while(ADC_GetCalibrationStatus(ADC1));  
}

/**************************************************************/
//�� �� ���� DMA_Config()
//�� �� �ߣ� chenhonglin
//��ڲ����� ��
//����˵���� DMA����
//**************************************************************/
void DMA_Config(void)
{ 
  DMA_InitTypeDef  DMA_InitStructure;
    //enable DMA1 clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//reset DMA1 channe1 to default values;
	DMA_DeInit(DMA1_Channel1);
	//channel will be used for memory to memory transfer
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	//setting normal mode (non circular)
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	//medium priority
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	//source and destination data size word=32bit
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	//automatic memory destination increment enable.
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//source address increment disable
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//Location assigned to peripheral register will be source
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	//chunk of data to be transfered
	DMA_InitStructure.DMA_BufferSize = ARRAYSIZE;
	//source and destination start addresses
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_values;
	//send values to DMA registers
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  //Enable DMA1 Channel transfer
  DMA_Cmd(DMA1_Channel1, ENABLE);
  //Start ADC1 Software Conversion
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  
	// Enable DMA1 Channel Transfer Complete interrupt
  /*
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
  
	NVIC_InitTypeDef NVIC_InitStructure;
  */
  
	//Enable DMA1 channel IRQ Channel
  /*
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  */
}
/**************************************************************/
//�� �� ���� Adc_Init()
//�� �� �ߣ� chenhonglin
//��ڲ����� ��
//����˵���� ADC���������ʼ��
//**************************************************************/
void  Adc_Init(void)
{
	ADC_GPIO_Config();	
	TIM2_Config();		
  ADC_Config();
  DMA_Config(); 
}


void SysTick_Init(void)
{
		SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC);  //ʹ�ܲ���ʼ��SysTick��ʱ��
}

void BSP_Init(void)
{
		SystemInit();    /*��ϵͳʱ�ӳ�ʼ��Ϊ72M*/
		SysTick_Init();   /*SysTick��ʼ������*/
    RCC_Config();
    GPIO_LED_Config();  
    Pwm_Init();
    Adc_Init();
    Beep_Init();
}


