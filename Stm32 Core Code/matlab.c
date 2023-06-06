#include "./SYSTEM/SYS/sys.h"
#include "./SYSTEM/USART/usart.h"
#include "./BSP/MATLAB/matlab.h"
#include "./BSP/LED/led.h"
#include "./BSP/FDC2214/fdc2214.h"
#include "./BSP/MOTOR/motor.h"
#include "./BSP/FILTER/filter.h"
#include "./BSP/PID/pid.h"

uint8_t len;
uint16_t times = 0;
uint32_t data = 0;

sendData g_SendData;

void matlab_listening(void)
{

	if(g_usart_rx_sta & 0x8000)
	{
		uint8_t command = g_usart_rx_buf[0];
		switch(command)	
		{
			case Send_ID:
				matlab_readID();
				matlab_sendID();
				break;
			case Send_Data:
				matlab_readData();
				matlab_sendData();
				break;
			case Send_Cap:
				matlab_readCap();
				matlab_sendCap();
				break;
			case Send_Parasitic_Data:
				matlab_readData_parasitic();
				matlab_sendData_parasitic();
				break;
			case Send_Parasitic_Cap:
				matlab_readCap_parasitic();
				matlab_sendCap_parasitic();
				break;
			case Send_Cap_Configured:
				matlab_readCap_configured();
				matlab_sendCap_configured();
				break;
			case Send_Initial_Data:
				matlab_readInitial_Data();
				matlab_sendInitial_Data();  
				break;
			case Send_Initial_Cap:
				matlab_readInitial_Cap();
				matlab_sendInitial_Cap();
				break;
			case Send_Liquid_Level:
				matlab_readLiquid_level();
				matlab_sendLiquid_level();
				break;
			case Motor_Spin_POS:
				motor_ratio(0,200,0.1);
				printf("%d\r\n",200);
				break;
			case Motor_Spin_NEG:
				motor_ratio(1,200,0.1);
				printf("%d\r\n",200);
				break;
			case Set_Parasitic_Cap:
				load_parasitic_chx_data();
				load_parasitic_chx_cap();
				printf("%d\r\n",200);
				break;
			case Set_Initial_Cap:
				load_initial_chx_data();
				load_initial_chx_cap();
				printf("%d\r\n",200);
				break;
			case Send_filtered_data:
				matlab_read_filteredData();
				matlab_send_filteredData();
				break;
			case Send_filtered_cap:
				matlab_read_filteredcap();
				matlab_send_filteredcap();
				break;
			case Send_filtered_configured_cap:
				matlab_read_filtered_configured_cap();
				matlab_send_filtered_configured_cap();
				break;
			case Reset_filter:
				matlab_reset_filter();
				printf("%d\r\n",200);
				break;
			case Actuation:
				matlab_actuaction(g_usart_rx_buf[1]);
				break;
			default:
				matlab_echo();
				break;
		}
		g_usart_rx_sta = 0;
	}
	else
	{
		times ++;

		if(times % 5000 == 0)
		{
			LED0(0);
			LED1(0);
			LED0_TOGGLE();
		}
		
		if(times % 200 == 0)
		{
			LED1_TOGGLE();
		}
		
		if(times % 30 == 0)
		{
			LED0_TOGGLE();
		}
	}
}

void matlab_echo(void)
{
		len = g_usart_rx_sta & 0x3ff;
		HAL_UART_Transmit(&g_uart1_handle,(uint8_t*)g_usart_rx_buf,len,1000);
		while(__HAL_UART_GET_FLAG(&g_uart1_handle,UART_FLAG_TC)!=SET);
}

void matlab_readID(void)
{
		g_SendData.device_id = fdc2214_read_reg_16(DEVICE_ID);
		g_SendData.manufacturer_id = fdc2214_read_reg_16(MANUFACTURER_ID);
}

void matlab_sendID(void)
{
		printf("%d\r\n",g_SendData.device_id);
		printf("%d\r\n",g_SendData.manufacturer_id);
}

void matlab_readData(void)
{
		g_SendData.ch0_data = fdc2214_read_ch_tot(0);
		g_SendData.ch1_data = fdc2214_read_ch_tot(1);
		g_SendData.ch2_data = fdc2214_read_ch_tot(2);
}

void matlab_readCap(void)
{
		g_SendData.ch0_cap = calculate_capacitance_pF(fdc2214_read_ch_tot(0),0);
		g_SendData.ch1_cap = calculate_capacitance_pF(fdc2214_read_ch_tot(1),0);
		g_SendData.ch2_cap = calculate_capacitance_pF(fdc2214_read_ch_tot(2),0);
}

void matlab_readData_parasitic(void)
{
		g_SendData.ch0_parasitic_data = fdc2214_ch0_parasitic_data;
		g_SendData.ch1_parasitic_data = fdc2214_ch1_parasitic_data;
		g_SendData.ch2_parasitic_data = fdc2214_ch2_parasitic_data;
}

void matlab_readCap_parasitic(void)
{
		g_SendData.ch0_parasitic_cap = fdc2214_ch0_parasitic_cap;
		g_SendData.ch1_parasitic_cap = fdc2214_ch1_parasitic_cap;
		g_SendData.ch2_parasitic_cap = fdc2214_ch2_parasitic_cap;
}

void matlab_readCap_configured(void)
{
		g_SendData.ch0_cap_configured = calculate_configured_capacitance_pF(fdc2214_read_ch_tot(0),fdc2214_ch0_parasitic_cap,fdc2214_ch0_initial_cap);
		g_SendData.ch1_cap_configured = calculate_configured_capacitance_pF(fdc2214_read_ch_tot(1),fdc2214_ch1_parasitic_cap,fdc2214_ch1_initial_cap);
		g_SendData.ch2_cap_configured = calculate_configured_capacitance_pF(fdc2214_read_ch_tot(2),fdc2214_ch2_parasitic_cap,fdc2214_ch2_initial_cap);
}

void matlab_readInitial_Data(void)
{
		g_SendData.ch0_initial_data = fdc2214_ch0_initial_data;
		g_SendData.ch1_initial_data = fdc2214_ch1_initial_data;
		g_SendData.ch2_initial_data = fdc2214_ch2_initial_data;
}

void matlab_readInitial_Cap(void)
{
		g_SendData.ch0_initial_cap = fdc2214_ch0_initial_cap;
		g_SendData.ch1_initial_cap = fdc2214_ch1_initial_cap;
		g_SendData.ch2_initial_cap = fdc2214_ch2_initial_cap;
}

void matlab_readLiquid_level(void)
{
		g_SendData.liquid_level = calculate_liquid_level(calculate_configured_capacitance_pF(\
							SlidingMeanFilter_ch1(fdc2214_read_ch_tot(1)),\
							fdc2214_ch1_parasitic_cap,fdc2214_ch1_initial_cap));
}

void matlab_sendData(void)
{
		printf("%d\r\n",g_SendData.ch0_data);
		printf("%d\r\n",g_SendData.ch1_data);
		printf("%d\r\n",g_SendData.ch2_data);
		while(__HAL_UART_GET_FLAG(&g_uart1_handle,UART_FLAG_TC)!=SET);
}

void matlab_sendCap(void)
{
		printf("%.10f\r\n",g_SendData.ch0_cap);
		printf("%.10f\r\n",g_SendData.ch1_cap);
		printf("%.10f\r\n",g_SendData.ch2_cap);
		while(__HAL_UART_GET_FLAG(&g_uart1_handle,UART_FLAG_TC)!=SET);
}

void matlab_sendData_parasitic(void)
{
		printf("%d\r\n",g_SendData.ch0_parasitic_data);
		printf("%d\r\n",g_SendData.ch1_parasitic_data);
		printf("%d\r\n",g_SendData.ch2_parasitic_data);
		while(__HAL_UART_GET_FLAG(&g_uart1_handle,UART_FLAG_TC)!=SET);
}

void matlab_sendCap_parasitic(void)
{
		printf("%.10f\r\n",fdc2214_ch0_parasitic_cap);
		printf("%.10f\r\n",fdc2214_ch1_parasitic_cap);
		printf("%.10f\r\n",fdc2214_ch2_parasitic_cap);
		while(__HAL_UART_GET_FLAG(&g_uart1_handle,UART_FLAG_TC)!=SET);
}

void matlab_sendCap_configured(void)
{
		printf("%.10f\r\n",g_SendData.ch0_cap_configured);
		printf("%.10f\r\n",g_SendData.ch1_cap_configured);
		printf("%.10f\r\n",g_SendData.ch2_cap_configured);
		while(__HAL_UART_GET_FLAG(&g_uart1_handle,UART_FLAG_TC)!=SET);
}

void matlab_sendInitial_Data(void)
{
		printf("%d\r\n",g_SendData.ch0_initial_data);
		printf("%d\r\n",g_SendData.ch1_initial_data);
		printf("%d\r\n",g_SendData.ch2_initial_data);
		while(__HAL_UART_GET_FLAG(&g_uart1_handle,UART_FLAG_TC)!=SET);
}

void matlab_sendInitial_Cap(void)
{
		printf("%.10f\r\n",g_SendData.ch0_initial_cap);
		printf("%.10f\r\n",g_SendData.ch1_initial_cap);
		printf("%.10f\r\n",g_SendData.ch2_initial_cap);
		while(__HAL_UART_GET_FLAG(&g_uart1_handle,UART_FLAG_TC)!=SET);
}

void matlab_sendLiquid_level(void)
{
		printf("%.10f\r\n",g_SendData.liquid_level);
		while(__HAL_UART_GET_FLAG(&g_uart1_handle,UART_FLAG_TC)!=SET);
}

void matlab_read_filteredData(void)
{
	g_SendData.ch0_filtered_data = SlidingMeanFilter_ch0(fdc2214_read_ch_tot(0));
	g_SendData.ch1_filtered_data = SlidingMeanFilter_ch1(fdc2214_read_ch_tot(1));
	g_SendData.ch2_filtered_data = SlidingMeanFilter_ch2(fdc2214_read_ch_tot(2));
}

void matlab_send_filteredData(void)
{
		printf("%d\r\n",g_SendData.ch0_filtered_data);
		printf("%d\r\n",g_SendData.ch1_filtered_data);
		printf("%d\r\n",g_SendData.ch2_filtered_data);
		while(__HAL_UART_GET_FLAG(&g_uart1_handle,UART_FLAG_TC)!=SET);
}

void matlab_read_filteredcap(void)
{
		g_SendData.ch0_filtered_cap = calculate_configured_capacitance_pF(SlidingMeanFilter_ch0(fdc2214_read_ch_tot(0)),0,0);
		g_SendData.ch1_filtered_cap = calculate_configured_capacitance_pF(SlidingMeanFilter_ch1(fdc2214_read_ch_tot(1)),0,0);
		g_SendData.ch2_filtered_cap = calculate_configured_capacitance_pF(SlidingMeanFilter_ch2(fdc2214_read_ch_tot(2)),0,0);
}

void matlab_send_filteredcap(void)
{
		printf("%.10f\r\n",g_SendData.ch0_filtered_cap);
		printf("%.10f\r\n",g_SendData.ch1_filtered_cap);
		printf("%.10f\r\n",g_SendData.ch2_filtered_cap);
		while(__HAL_UART_GET_FLAG(&g_uart1_handle,UART_FLAG_TC)!=SET);
}

void matlab_read_filtered_configured_cap(void)
{
		g_SendData.ch0_filtered_configured_cap = calculate_configured_capacitance_pF(SlidingMeanFilter_ch0(fdc2214_read_ch_tot(0)),fdc2214_ch0_parasitic_cap,fdc2214_ch0_initial_cap);
		g_SendData.ch1_filtered_configured_cap = calculate_configured_capacitance_pF(SlidingMeanFilter_ch1(fdc2214_read_ch_tot(1)),fdc2214_ch1_parasitic_cap,fdc2214_ch1_initial_cap);
		g_SendData.ch2_filtered_configured_cap = calculate_configured_capacitance_pF(SlidingMeanFilter_ch2(fdc2214_read_ch_tot(2)),fdc2214_ch2_parasitic_cap,fdc2214_ch2_initial_cap);
}

void matlab_send_filtered_configured_cap(void)
{
		printf("%.10f\r\n",g_SendData.ch0_filtered_configured_cap);
		printf("%.10f\r\n",g_SendData.ch1_filtered_configured_cap);
		printf("%.10f\r\n",g_SendData.ch2_filtered_configured_cap);
		while(__HAL_UART_GET_FLAG(&g_uart1_handle,UART_FLAG_TC)!=SET);
}

void matlab_reset_filter(void)
{
	/** */
}

void matlab_actuaction(uint8_t liquid_level)
{
	float cap = 0.0063 * liquid_level - 0.0445;
	PID_realize(0.20);
}