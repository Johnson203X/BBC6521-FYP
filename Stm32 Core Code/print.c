#include "./SYSTEM/USART/usart.h"
#include "./BSP/FDC2214/fdc2214.h"
#include "./BSP/PRINT/print.h"
#include "./BSP/FILTER/filter.h"

uint16_t msb = 0;
uint16_t lsb = 0;
uint32_t tot = 0;

void print_channel_detail(int ch)
{
	msb = fdc2214_read_ch_msb(ch);
	lsb = fdc2214_read_ch_lsb(ch);
	tot = fdc2214_read_ch_tot(ch);
	printf("CH%d_MSB: %d	CH%d_LSB: %d	CH%d_TOT: %d\n",\
		ch,msb,\
		ch,lsb,\
		ch,tot);
	print_to_binary(lsb,16);
	print_to_binary(msb,16);
	print_to_binary(tot,32);	
}

void print_channel_tot(int ch)
{
	tot = fdc2214_read_ch_tot(ch);
	printf("%d ",tot);
	printf("%d ",KalmanFilter(tot));
}

void print_capacitance_tot(int ch)
{
	tot = fdc2214_read_ch_tot(ch);
	printf("%.10f ",calculate_capacitance_pF(tot,0));
}

void print_channel_tot_all(void)
{	
	for(int ch = 0; ch < 3; ch++)
	{
		print_channel_tot(ch);
	}
	printf("\n");	
}

void print_channel_detail_all(void)
{	
	for(int ch = 0; ch < 3; ch++)
	{
		print_channel_detail(ch);
	}
	printf("\n");	
}

void print_capacitance_tot_all(void)
{	
	for(int ch = 0; ch < 3; ch++)
	{
		print_capacitance_tot(ch);
	}
	printf("\n");	
}

void print_to_binary(int input,int bits)
{
	for(int i =0; i < bits; i++)
	{
		int pointer = 0x1;
		pointer = pointer<<(bits-i-1);
		if(input&pointer)
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
		if(((i+1)%4==0) && (i!=bits-1))
		{
			printf(" | ");
		}
	}
	printf("\n");	
}