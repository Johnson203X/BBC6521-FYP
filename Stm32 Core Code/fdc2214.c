/* Related Headers */
#include "./SYSTEM/DELAY/delay.h"
#include "./SYSTEM/USART/usart.h"
#include "./BSP/IIC/iic.h"
#include "./BSP/FDC2214/fdc2214.h"

/* FDC2214 Pin Connection Map to STM32F103ZET6 Lab board */

/*
	PB6  ->SCL
	PB7  ->SDA
	3.3V ->VDD ->PD11(PWR)
	GND  ->VSS
	GND  ->SD
	GND  ->CLKIN(USING INTERNAL CLOCK)
	GND  ->ADDR(0X2A) // 3.3V ->ADDR(0X2B)
*/


uint8_t Receive_Data[4];
uint8_t C_Data_8;
uint16_t C_Data_16;
uint32_t C_Data_32;
uint16_t chx_msb;
uint16_t chx_lsb;
uint32_t chx_tot;
uint8_t DATA_MSB_CHX;
uint8_t DATA_LSB_CHX;
uint32_t fdc2214_ch0_parasitic_data = 0;
uint32_t fdc2214_ch1_parasitic_data = 0;
uint32_t fdc2214_ch2_parasitic_data = 0;
double fdc2214_ch0_parasitic_cap = 0;
double fdc2214_ch1_parasitic_cap = 0;
double fdc2214_ch2_parasitic_cap = 0;
uint32_t fdc2214_ch0_initial_data = 0;
uint32_t fdc2214_ch1_initial_data = 0;
uint32_t fdc2214_ch2_initial_data = 0;
double fdc2214_ch0_initial_cap = 0;
double fdc2214_ch1_initial_cap = 0;
double fdc2214_ch2_initial_cap = 0;
double fdc2214_ch0_configured_cap = 0;
double fdc2214_ch1_configured_cap = 0;
double fdc2214_ch2_configured_cap = 0;
uint32_t fdc2214_ch0_filtered_data = 0;
uint32_t fdc2214_ch1_filtered_data = 0;
uint32_t fdc2214_ch2_filtered_data = 0;
double fdc2214_ch0_filtered_cap = 0;
double fdc2214_ch1_filtered_cap = 0;
double fdc2214_ch2_filtered_cap = 0;
double fdc2214_ch0_filtered_configured_cap = 0;
double fdc2214_ch1_filtered_configured_cap = 0;
double fdc2214_ch2_filtered_configured_cap = 0;

void fdc2214_init(void)
{
	iic_init();
}

void fdc2214_PWR(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    PWR_GPIO_CLK_ENABLE();                          
    gpio_init_struct.Pin = PWR_GPIO_PIN;                  
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;           
    gpio_init_struct.Pull = GPIO_PULLUP;                 
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          
    HAL_GPIO_Init(PWR_GPIO_PORT, &gpio_init_struct);     
}

void fdc2214_restart(void)
{
		FDC_PWR(0);
		delay_ms(500);
		FDC_PWR(1);
		fdc2214_start();
		delay_ms(500);
}

void fdc2214_f_clk(void)
{
/**
	RCC_MCO1SOURCE_HSI 8MHz
	RCC_MCO1SOURCE_HSE 8MHz
	RCC_MCO1SOURCE_PLLCLK 72/2=36MHz
*/
	HAL_RCC_MCOConfig(RCC_MCO1,RCC_MCO1SOURCE_PLLCLK,RCC_MCODIV_1);
	GPIO_InitTypeDef gpio_init_struct;
	gpio_init_struct.Pin = GPIO_PIN_8;                  
	gpio_init_struct.Mode = GPIO_MODE_AF_PP;                          
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          
	HAL_GPIO_Init(GPIOA, &gpio_init_struct);
}

uint8_t fdc2214_check(void)
{
	uint8_t check = 0;
	iic_start();
	iic_send_byte(FDC2214_LOW_ADDR_WRITE);
	check = !iic_wait_ack();
	return check;
}

void fdc2214_write_reg_16(uint8_t addr,uint16_t value)  
{ 
	iic_start();                   
	iic_send_byte(FDC2214_LOW_ADDR_WRITE);   
	iic_wait_ack();               
	iic_send_byte(addr);        
	iic_wait_ack();                 
	iic_send_byte(value>>8);    
	iic_wait_ack();               
	iic_send_byte(value&0xFF);      
	iic_wait_ack();                
	iic_stop();                    
	delay_ms(1);
}

uint16_t fdc2214_read_reg_16(uint8_t addr)
{
	iic_start();                  
	iic_send_byte(FDC2214_LOW_ADDR_WRITE);  
	iic_wait_ack();		
	iic_send_byte(addr);          
	iic_wait_ack();
	iic_start();
	iic_send_byte(FDC2214_LOW_ADDR_READ); 
	iic_wait_ack();
	Receive_Data[0]=iic_read_byte(1); 
	Receive_Data[1]=iic_read_byte(0);  
	iic_stop();	     
	C_Data_16=(Receive_Data[0]<<8)+ Receive_Data[1];
	return C_Data_16;
}

uint32_t fdc2214_read_reg_32(uint8_t addr)
{
	iic_start();                  
	iic_send_byte(FDC2214_LOW_ADDR_WRITE);  
	iic_wait_ack();		
	iic_send_byte(addr);          
	iic_wait_ack();
	iic_start();
	iic_send_byte(FDC2214_LOW_ADDR_READ); 
	iic_wait_ack();
	Receive_Data[0]=iic_read_byte(1); 
	Receive_Data[1]=iic_read_byte(1);  
	Receive_Data[2]=iic_read_byte(1); 
	Receive_Data[3]=iic_read_byte(0); 
	iic_stop();	
	C_Data_32=(Receive_Data[0]<<24)+ (Receive_Data[1]<<16)+ \
			(Receive_Data[2]<<8)+ Receive_Data[3];
	return C_Data_32;
}

uint16_t fdc2214_read_ch_lsb(uint8_t ch)
{
	switch(ch)
	{
		case 0:
			DATA_LSB_CHX = DATA_LSB_CH0;
			break;
		case 1:
			DATA_LSB_CHX = DATA_LSB_CH1;
			break;
		case 2:
			DATA_LSB_CHX = DATA_LSB_CH2;
			break;
		case 3:
			DATA_LSB_CHX = DATA_LSB_CH3;
			break;
	}
	chx_lsb = fdc2214_read_reg_16(DATA_LSB_CHX);
	return chx_lsb;
}

uint16_t fdc2214_read_ch_msb(uint8_t ch)
{
	switch(ch)
	{
		case 0:
			DATA_MSB_CHX = DATA_MSB_CH0;
			break;
		case 1:
			DATA_MSB_CHX = DATA_MSB_CH1;
			break;
		case 2:
			DATA_MSB_CHX = DATA_MSB_CH2;
			break;
		case 3:
			DATA_MSB_CHX = DATA_MSB_CH3;
			break;
	}
	chx_msb = fdc2214_read_reg_16(DATA_MSB_CHX)&0xFFF;
	return chx_msb;
}

uint32_t fdc2214_read_ch_tot(uint8_t ch)
{
	switch(ch)
	{
		case 0:
			DATA_MSB_CHX = DATA_MSB_CH0;
			DATA_LSB_CHX = DATA_LSB_CH0;
			break;
		case 1:
			DATA_MSB_CHX = DATA_MSB_CH1;
			DATA_LSB_CHX = DATA_LSB_CH1;
			break;
		case 2:
			DATA_MSB_CHX = DATA_MSB_CH2;
			DATA_LSB_CHX = DATA_LSB_CH2;
			break;
		case 3:
			DATA_MSB_CHX = DATA_MSB_CH3;
			DATA_LSB_CHX = DATA_LSB_CH3;
			break;
	}
	chx_msb = fdc2214_read_reg_16(DATA_MSB_CHX)&0xFFF;
	chx_lsb = fdc2214_read_reg_16(DATA_LSB_CHX);
	chx_tot = (chx_msb<<16 | chx_lsb);
	delay_ms(CHX_TIME);
	return chx_tot;
}

uint32_t fdc2214_read_ch_tot_avg_filter(uint8_t ch, uint16_t times)
{
	float chx_tot_avg_ans = 0;
	uint32_t chx_tot_avg[times];
	for(int i = 0; i< times; i++)
	{
		chx_tot_avg[i] = fdc2214_read_ch_tot(ch);
		delay_ms(CHX_TIME);
	}
	for(int i = 0; i< times; i++)
	{
		chx_tot_avg_ans += (float)chx_tot_avg[i]/(float)times;
	}
	return (uint32_t)chx_tot_avg_ans;
}


uint16_t fdc2214_read_status(void)
{
	return fdc2214_read_reg_16(STATUS);
}

uint16_t fdc2214_clock_dividers_value(uint8_t CHX_FIN_SEL,uint8_t CHX_FREF_DIVIDER)
{
	return (CHX_FIN_SEL<<12|CHX_FREF_DIVIDER);
}

uint16_t fdc2214_mux_config_value(uint8_t AUTOSCAN_EN, uint8_t RR_SEQUENCE,uint8_t DEGLITCH)
{
	return (AUTOSCAN_EN<<15|0x41<<3|RR_SEQUENCE<<13|DEGLITCH);
}

uint16_t fdc2214_drive_current_value(uint16_t CURRENT)
{
	return(CURRENT<<13);
}

uint16_t fdc2214_config_value(uint8_t ACTIVE_CHAN, uint8_t SLEEP_MODE_EN,\
								uint8_t SENSOR_ACTIVATE_SEL, uint8_t REF_CLK_SRC,\
								uint8_t INTB_DIS, uint8_t HIGH_CURRENT_DRV)
{
	return (ACTIVE_CHAN<<14|SLEEP_MODE_EN<<13|0x01<<12|SENSOR_ACTIVATE_SEL<<11|\
			0x01<<10|REF_CLK_SRC<<9|INTB_DIS<<7|HIGH_CURRENT_DRV<<6|0x01);
}

void fdc2214_start(void)  
{
	fdc2214_write_reg_16(RCOUNT_CH0,CHX_RCOUNT_DEFAULT);
	fdc2214_write_reg_16(RCOUNT_CH1,CHX_RCOUNT_DEFAULT);
	fdc2214_write_reg_16(RCOUNT_CH2,CHX_RCOUNT_DEFAULT);
	fdc2214_write_reg_16(RCOUNT_CH3,CHX_RCOUNT_DEFAULT);
	
	fdc2214_write_reg_16(SETTLECOUNT_CH0,CHX_SETTLECOUNT_DEFAULT);
	fdc2214_write_reg_16(SETTLECOUNT_CH1,CHX_SETTLECOUNT_DEFAULT);
	fdc2214_write_reg_16(SETTLECOUNT_CH2,CHX_SETTLECOUNT_DEFAULT);
	fdc2214_write_reg_16(SETTLECOUNT_CH3,CHX_SETTLECOUNT_DEFAULT);
	
	fdc2214_write_reg_16(CLOCK_DIVIDERS_C_CH0,fdc2214_clock_dividers_value(
		CHX_FIN_SEL_Differential_500_100_MHz,\
		CHX_FREF_DIVIDER_ONE\
	));
	fdc2214_write_reg_16(CLOCK_DIVIDERS_C_CH1,fdc2214_clock_dividers_value(
		CHX_FIN_SEL_Differential_500_100_MHz,\
		CHX_FREF_DIVIDER_ONE\
	));
	fdc2214_write_reg_16(CLOCK_DIVIDERS_C_CH2,fdc2214_clock_dividers_value(
		CHX_FIN_SEL_Differential_500_100_MHz,\
		CHX_FREF_DIVIDER_ONE\
	));
	fdc2214_write_reg_16(CLOCK_DIVIDERS_C_CH3,fdc2214_clock_dividers_value(
		CHX_FIN_SEL_Differential_500_100_MHz,\
		CHX_FREF_DIVIDER_ONE\
	));
	
	fdc2214_write_reg_16(ERROR_CONFIG,0x0000);
	
	fdc2214_write_reg_16(MUX_CONFIG,fdc2214_mux_config_value(\
		AUTOSCAN_EN_AUTO_CHANNEL_CONVERSION,\
		RR_SEQUENCE_MULTIPLEXING_CH0_CH1_CH2,\
		DEGLITCH_FILTER_BANDWIDTH_10MHz\
	));
	
	fdc2214_write_reg_16(DRIVE_CURRENT_CH0,fdc2214_drive_current_value(CURRENT_0555));
	fdc2214_write_reg_16(DRIVE_CURRENT_CH1,fdc2214_drive_current_value(CURRENT_0555));
	fdc2214_write_reg_16(DRIVE_CURRENT_CH2,fdc2214_drive_current_value(CURRENT_0555));
	fdc2214_write_reg_16(DRIVE_CURRENT_CH3,fdc2214_drive_current_value(CURRENT_0555));
	
	fdc2214_write_reg_16(CONFIG,fdc2214_config_value(
			ACTIVE_CHAN_0,\
			SLEEP_MODE_EN_ACTIVE,\
			SENSOR_ACTIVATE_SEL_HIGH_POWER,\
			REF_CLK_SRC_EX,\
			INTB_DIS_ASSERTED,\
			HIGH_CURRENT_DRV_NORMAL\
	));
}

void load_parasitic_chx_data(void)
{
	fdc2214_ch0_parasitic_data = fdc2214_read_ch_tot(0);
	fdc2214_ch1_parasitic_data = fdc2214_read_ch_tot(1);
	fdc2214_ch2_parasitic_data = fdc2214_read_ch_tot(2);
}

void load_parasitic_chx_cap(void)
{
	fdc2214_ch0_parasitic_cap = calculate_capacitance_pF(fdc2214_read_ch_tot(0),0);
	fdc2214_ch1_parasitic_cap = calculate_capacitance_pF(fdc2214_read_ch_tot(1),0);
	fdc2214_ch2_parasitic_cap = calculate_capacitance_pF(fdc2214_read_ch_tot(2),0);
}

void load_initial_chx_data(void)
{
	fdc2214_ch0_initial_data = fdc2214_read_ch_tot(0);
	fdc2214_ch1_initial_data = fdc2214_read_ch_tot(1);
	fdc2214_ch2_initial_data = fdc2214_read_ch_tot(2);
}

void load_initial_chx_cap(void)
{
	fdc2214_ch0_initial_cap = calculate_capacitance_pF(\
		fdc2214_read_ch_tot(0),fdc2214_ch0_parasitic_cap);
	fdc2214_ch1_initial_cap = calculate_capacitance_pF(\
		fdc2214_read_ch_tot(1),fdc2214_ch1_parasitic_cap);
	fdc2214_ch2_initial_cap = calculate_capacitance_pF(\
		fdc2214_read_ch_tot(2),fdc2214_ch2_parasitic_cap);
}

double calculate_capacitance_pF(uint32_t Data, double chx_parasitic_cap)
{
	double Weight_tmp = 19561.0;
	double Data_tmp = Data/1000000.0;
	Weight_tmp /= Data_tmp;
	Weight_tmp /= Data_tmp;
	Weight_tmp -= chx_parasitic_cap;
	return Weight_tmp;
}

double calculate_configured_capacitance_pF(uint32_t Data, double chx_parasitic_cap, double chx_init_cap)
{
	double Weight_tmp = 19561.0;
	double Data_tmp = Data/1000000.0;
	Weight_tmp /= Data_tmp;
	Weight_tmp /= Data_tmp;
	Weight_tmp -= chx_parasitic_cap;
	Weight_tmp -= chx_init_cap;
	return Weight_tmp;
}

double calculate_liquid_level(double cap)
{
	double height_mm = 230.3852*cap*cap + 146.0432*cap + 8.0630;
	return height_mm;
}

