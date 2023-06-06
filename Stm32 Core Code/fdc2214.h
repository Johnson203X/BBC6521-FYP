#ifndef __FDC2214_H
#define __FDC2214_H

#include "./SYSTEM/SYS/sys.h"

#define PWR_GPIO_PORT                  GPIOD
#define PWR_GPIO_PIN                   GPIO_PIN_11
#define PWR_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

#define FDC_PWR(x)   do{ x ? \
                      HAL_GPIO_WritePin(PWR_GPIO_PORT, PWR_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(PWR_GPIO_PORT, PWR_GPIO_PIN, GPIO_PIN_RESET); \
					}while(0)

#define F_CLK_GPIO_PORT                  GPIOD
#define F_CLK_GPIO_PIN                   GPIO_PIN_12
#define F_CLK_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)
					
#define FDC_F_CLK(x)   do{ x ? \
                      HAL_GPIO_WritePin(F_CLK_GPIO_PORT, F_CLK_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(F_CLK_GPIO_PORT, F_CLK_GPIO_PIN, GPIO_PIN_RESET); \
					}while(0)			
					
#define F_CLK_TOGGLE()   do{ HAL_GPIO_TogglePin(F_CLK_GPIO_PORT, F_CLK_GPIO_PIN); }while(0)

#define DATA_MSB_CH0 					0x00
#define DATA_LSB_CH0 					0x01
#define DATA_MSB_CH1 					0x02
#define DATA_LSB_CH1 					0x03
#define DATA_MSB_CH2 					0x04
#define DATA_LSB_CH2 					0x05
#define DATA_MSB_CH3 					0x06
#define DATA_LSB_CH3 					0x07
#define RCOUNT_CH0 						0x08
#define RCOUNT_CH1 						0x09
#define RCOUNT_CH2 						0x0A
#define RCOUNT_CH3 						0x0B
#define OFFSET_CH0 						0x0C 
#define OFFSET_CH1 						0x0D
#define OFFSET_CH2 						0x0E
#define OFFSET_CH3 						0x0F
#define SETTLECOUNT_CH0 				0x10
#define SETTLECOUNT_CH1 				0x11
#define SETTLECOUNT_CH2 				0x12
#define SETTLECOUNT_CH3 				0x13
#define CLOCK_DIVIDERS_C_CH0 			0x14
#define CLOCK_DIVIDERS_C_CH1 			0x15
#define CLOCK_DIVIDERS_C_CH2 			0x16
#define CLOCK_DIVIDERS_C_CH3 			0x17
#define STATUS 							0x18
#define ERROR_CONFIG 					0x19 
#define CONFIG 							0x1A 
#define MUX_CONFIG 						0x1B
#define DRIVE_CURRENT_CH0 				0x1E
#define DRIVE_CURRENT_CH1 				0x1F
#define DRIVE_CURRENT_CH2 				0x20
#define DRIVE_CURRENT_CH3 				0x21
#define RESET_DEV 						0x1C
#define MANUFACTURER_ID 				0x7E
#define DEVICE_ID 						0x7F

#define IIC_WRITE		0x00
#define IIC_READ		0x01

#define FDC2214_LOW_ADDR	0x2A
#define FDC2214_HIGH_ADDR	0x2B

#define INT_OSC_Frequency 40

#define MANUFACTURER_ID_VALUE 				0x5449

#define DEVICE_ID_VALUE_FDC211X 			0x3054
#define DEVICE_ID_VALUE_FDC221X 			0x3055

#define H_Ref 1.0

#define  FDC2214_LOW_ADDR_WRITE		(FDC2214_LOW_ADDR<<1|IIC_WRITE)
#define  FDC2214_LOW_ADDR_READ  	(FDC2214_LOW_ADDR<<1|IIC_READ)
#define  FDC2214_HIGH_ADDR_WRITE	(FDC2214_HIGH_ADDR<<1|IIC_WRITE)
#define  FDC2214_HIGH_ADDR_READ		(FDC2214_HIGH_ADDR<<1|IIC_READ)

#define CHX_RCOUNT_DEFAULT	0x2000

#define CHX_SETTLECOUNT_DEFAULT	0x000A

#define CHX_FIN_SEL_Differential_001_875_MHz	0x01
#define CHX_FIN_SEL_Differential_500_100_MHz	0x02
#define CHX_FIN_SEL_Single_ended							0x02
#define CHX_FREF_DIVIDER_ONE									0x01
#define CHX_FREF_DIVIDER_TWO									0x02

#define  AUTOSCAN_EN_CONTINUOUS_CONVERSION_SINGLE_CHANNEL_SELECTED_BY_CONFIG	0x00
#define  AUTOSCAN_EN_AUTO_CHANNEL_CONVERSION																	0x01
#define  RR_SEQUENCE_MULTIPLEXING_CH0_CH1 																		0x00
#define  RR_SEQUENCE_MULTIPLEXING_CH0_CH1_CH2																	0x01
#define  RR_SEQUENCE_MULTIPLEXING_CH0_CH1_CH2_CH3 														0x02
#define  RR_SEQUENCE_MULTIPLEXING_CH0_CH1_DUPLICATE 													0x03

#define  DEGLITCH_FILTER_BANDWIDTH_1MHz			0x01
#define  DEGLITCH_FILTER_BANDWIDTH_3_3MHz		0x04
#define  DEGLITCH_FILTER_BANDWIDTH_10MHz		0x05
#define  DEGLITCH_FILTER_BANDWIDTH_33MHz		0x07

#define  CURRENT_0555	0x0C
#define  CURRENT_1571	0x0F

#define  ACTIVE_CHAN_0				 						0x00
#define  ACTIVE_CHAN_1										0x01
#define  ACTIVE_CHAN_2										0x02
#define  ACTIVE_CHAN_3										0x03
#define  SLEEP_MODE_EN_ACTIVE							0x00
#define  SLEEP_MODE_EN_SLEEP							0x01
#define  SENSOR_ACTIVATE_SEL_HIGH_POWER		0x00
#define  SENSOR_ACTIVATE_SEL_LOW_POWER		0x01
#define  REF_CLK_SRC_IN										0x00
#define  REF_CLK_SRC_EX										0x01
#define  INTB_DIS_ASSERTED								0x00
#define  INTB_DIS_NOT_ASSERTED						0x01
#define  HIGH_CURRENT_DRV_NORMAL					0x00
#define  HIGH_CURRENT_DRV_HIGH						0x01

#define CHX_TIME 4

extern uint32_t fdc2214_ch0_parasitic_data;
extern uint32_t fdc2214_ch1_parasitic_data;
extern uint32_t fdc2214_ch2_parasitic_data;
extern double fdc2214_ch0_parasitic_cap;
extern double fdc2214_ch1_parasitic_cap;
extern double fdc2214_ch2_parasitic_cap;
extern uint32_t fdc2214_ch0_initial_data;
extern uint32_t fdc2214_ch1_initial_data;
extern uint32_t fdc2214_ch2_initial_data;
extern double fdc2214_ch0_initial_cap;
extern double fdc2214_ch1_initial_cap;
extern double fdc2214_ch2_initial_cap;
extern double fdc2214_ch0_configured_cap;
extern double fdc2214_ch1_configured_cap;
extern double fdc2214_ch2_configured_cap;
extern uint32_t fdc2214_ch0_filtered_data;
extern uint32_t fdc2214_ch1_filtered_data;
extern uint32_t fdc2214_ch2_filtered_data;
extern double fdc2214_ch0_filtered_cap;
extern double fdc2214_ch1_filtered_cap;
extern double fdc2214_ch2_filtered_cap;
extern double fdc2214_ch0_filtered_configured_cap;
extern double fdc2214_ch1_filtered_configured_cap;
extern double fdc2214_ch2_filtered_configured_cap;

void fdc2214_init(void);

void fdc2214_PWR(void);

void fdc2214_f_clk(void);

void fdc2214_start(void);

void fdc2214_restart(void);

uint8_t fdc2214_check(void);

void fdc2214_write_reg_16(uint8_t addr,uint16_t value);

uint16_t fdc2214_clock_dividers_value(uint8_t CHX_FIN_SEL,uint8_t CHX_FREF_DIVIDER);

uint16_t fdc2214_mux_config_value(uint8_t AUTOSCAN_EN, uint8_t RR_SEQUENCE,uint8_t DEGLITCH);

uint16_t fdc2214_drive_current_value(uint16_t CURRENT);

uint16_t fdc2214_config_value(uint8_t ACTIVE_CHAN, uint8_t SLEEP_MODE_EN,\
								uint8_t SENSOR_ACTIVATE_SEL, uint8_t REF_CLK_SRC,\
								uint8_t INTB_DIS, uint8_t HIGH_CURRENT_DRV);

uint16_t fdc2214_read_reg_16(uint8_t addr);
uint32_t fdc2214_read_reg_32(uint8_t addr);

uint16_t fdc2214_read_ch_msb(uint8_t ch);
uint16_t fdc2214_read_ch_lsb(uint8_t ch);
uint32_t fdc2214_read_ch_tot(uint8_t ch);

uint32_t fdc2214_read_ch_tot_avg_filter(uint8_t ch, uint16_t times);

uint16_t fdc2214_read_status(void);

void load_parasitic_chx_data(void);
	
void load_parasitic_chx_cap(void);
	
void load_initial_chx_data(void);
	
void load_initial_chx_cap(void);

double calculate_capacitance_pF(uint32_t Data, double chx_parasitic_cap);

double calculate_configured_capacitance_pF(uint32_t Data, double chx_parasitic_cap, double chx_init_cap);

double calculate_liquid_level(double cap);
		
#endif
