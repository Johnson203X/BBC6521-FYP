/* System Level Headers */
#include "./SYSTEM/SYS/sys.h"

/* Matlab Command */
#define Send_ID	 											0x30
#define Send_Data 											0x31
#define Send_Cap    										0x32
#define Send_Parasitic_Data									0x33
#define Send_Parasitic_Cap 									0x34
#define Send_Cap_Configured    								0x35
#define Send_Initial_Data 									0x36
#define Send_Initial_Cap    								0x37
#define Send_Liquid_Level   								0x38
#define Motor_Spin_POS										0x39
#define Motor_Spin_NEG										0x3A
#define Set_Parasitic_Cap     			  					0x3B
#define Set_Initial_Cap 									0x3C
#define Send_filtered_data     								0x3D
#define Send_filtered_cap   			   					0x3E
#define Send_filtered_configured_cap  						0x3F
#define Reset_filter										0x40
#define Actuation											0x41


extern uint8_t len;
extern uint16_t times;

__packed typedef struct
{
		uint16_t device_id;
		uint16_t manufacturer_id;
    	uint32_t ch0_data;    
    	uint32_t ch1_data;    
		uint32_t ch2_data;
    	double ch0_cap;    
    	double ch1_cap;    
		double ch2_cap;	
		uint32_t ch0_parasitic_data;
		uint32_t ch1_parasitic_data;
		uint32_t ch2_parasitic_data;
		double ch0_parasitic_cap;
		double ch1_parasitic_cap;
		double ch2_parasitic_cap;
		double ch0_cap_configured;    
    	double ch1_cap_configured;    
		double ch2_cap_configured;
		uint32_t ch0_initial_data;
		uint32_t ch1_initial_data;
		uint32_t ch2_initial_data;
		double ch0_initial_cap;
		double ch1_initial_cap;
		double ch2_initial_cap;
		double liquid_level;
		uint32_t ch0_filtered_data;
		uint32_t ch1_filtered_data;
		uint32_t ch2_filtered_data;
		double ch0_filtered_cap;
		double ch1_filtered_cap;
		double ch2_filtered_cap;		
		double ch0_filtered_configured_cap;
		double ch1_filtered_configured_cap;
		double ch2_filtered_configured_cap;
}
sendData;

extern sendData g_SendData;

void matlab_listening(void);
void matlab_echo(void);
void matlab_readID(void);
void matlab_readData(void);
void matlab_readData_parasitic(void);
void matlab_readCap(void);
void matlab_readCap_parasitic(void);
void matlab_readCap_configured(void);
void matlab_readInitial_Data(void);
void matlab_readInitial_Cap(void);
void matlab_readLiquid_level(void);
void matlab_sendID(void);
void matlab_sendData(void);
void matlab_sendData_parasitic(void);
void matlab_sendCap(void);
void matlab_sendCap_parasitic(void);
void matlab_sendCap_configured(void);
void matlab_sendInitial_Data(void);
void matlab_sendInitial_Cap(void);
void matlab_sendLiquid_level(void);
void matlab_read_filteredData(void);
void matlab_send_filteredData(void);
void matlab_read_filteredcap(void);
void matlab_send_filteredcap(void);	
void matlab_read_filtered_configured_cap(void);
void matlab_send_filtered_configured_cap(void);
void matlab_reset_filter(void);
void matlab_actuaction(uint8_t liquid_level);

