#include "./SYSTEM/DELAY/delay.h"
#include "./BSP/MOTOR/motor.h"

void motor_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    ENA_GPIO_CLK_ENABLE();
	DIR_GPIO_CLK_ENABLE();
    PUL_GPIO_CLK_ENABLE();                              
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;        
    gpio_init_struct.Pull = GPIO_PULLUP;                  
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;        
	gpio_init_struct.Pin = ENA_GPIO_PIN;                   
    HAL_GPIO_Init(ENA_GPIO_PORT, &gpio_init_struct);       
    gpio_init_struct.Pin = DIR_GPIO_PIN;                  
    HAL_GPIO_Init(DIR_GPIO_PORT, &gpio_init_struct);       
    gpio_init_struct.Pin = PUL_GPIO_PIN;                  
    HAL_GPIO_Init(PUL_GPIO_PORT, &gpio_init_struct);  
    ENA(0);                                              
    DIR(0);    
	PUL(0);
}
					
void motor_1_circle(uint8_t direction, int precision)
{
		int count = 0;
		while(count < precision)
		{
			ENA(1);
			DIR(direction);
			PUL(0);	
			delay_ms(Actuation_Speed_ms);
			PUL(1);
			delay_ms(Actuation_Speed_ms);	
			count++;
		}
		ENA(0);
		DIR(0);
		PUL(0);
}

void motor_ratio(uint8_t direction, int precision, double ratio)
{
		int times = (int)(precision * ratio);
		int count = 0;
		while(count < times)
		{
			ENA(1);
			DIR(direction);
			PUL(0);	
			delay_ms(Actuation_Speed_ms);
			PUL(1);
			delay_ms(Actuation_Speed_ms);	
			count++;
		}
		ENA(0);
		DIR(0);
		PUL(0);
}