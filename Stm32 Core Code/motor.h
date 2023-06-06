#ifndef __MOTOR_H
#define __MOTOR_H

#include "./SYSTEM/SYS/sys.h"
 
#define ENA_GPIO_PORT                  GPIOC
#define ENA_GPIO_PIN                   GPIO_PIN_0
#define ENA_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)

#define DIR_GPIO_PORT                  GPIOC
#define DIR_GPIO_PIN                   GPIO_PIN_1
#define DIR_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)

#define PUL_GPIO_PORT                  GPIOC
#define PUL_GPIO_PIN                   GPIO_PIN_2
#define PUL_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)

#define ENA(x)   do{ x ? \
                      HAL_GPIO_WritePin(ENA_GPIO_PORT, ENA_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(ENA_GPIO_PORT, ENA_GPIO_PIN, GPIO_PIN_RESET); \
					}while(0)

#define DIR(x)   do{ x ? \
                      HAL_GPIO_WritePin(DIR_GPIO_PORT, DIR_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(DIR_GPIO_PORT, DIR_GPIO_PIN, GPIO_PIN_RESET); \
					}while(0)

#define PUL(x)   do{ x ? \
                      HAL_GPIO_WritePin(PUL_GPIO_PORT, PUL_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(PUL_GPIO_PORT, PUL_GPIO_PIN, GPIO_PIN_RESET); \
					}while(0)

#define Actuation_Speed_ms	1		
					
#define Forward  1
#define Backward 0
					
#define Precision_1_200			200
#define Precision_2A_400  	    400
#define Precision_2B_400  	    400
#define Precision_4_800 	 	800
#define Precision_8_1600		1600
#define Precision_16_3200 	    3200	
#define Precision_32_6400 	    6400							
			
void motor_init(void);					
void motor_1_circle(uint8_t direction, int precision);					
void motor_ratio(uint8_t direction, int precision, double motor_ratio);
					
#endif