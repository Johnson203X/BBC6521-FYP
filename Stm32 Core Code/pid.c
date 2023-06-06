#include "main.h"
#include "./SYSTEM/SYS/sys.h"
#include "./SYSTEM/USART/usart.h"
#include "./BSP/PID/pid.h"
#include "./BSP/FDC2214/fdc2214.h"
#include "./BSP/MOTOR/motor.h"
#include "./BSP/FILTER/filter.h"

struct _pid{
	float SetData;
	float ActualData;
	float err;
	float err_next;
	float err_last;
	float Kp, Ki, Kd;
}pid;


void PID_init(void){
	pid.SetData = 0.0;
	pid.ActualData = 0.0;
	pid.err = 0.0;
	pid.err_last = 0.0;
	pid.err_next = 0.0;

	pid.Kp = 0.2;
	pid.Ki = 0.04; 
	pid.Kd = 0.2;
}

float PID_realize_err(float data){
	double sum = 0;
	for(int i = 0; i < 10; i ++)
	{
		double tmp = calculate_configured_capacitance_pF(\
										SlidingMeanFilter_ch1(fdc2214_read_ch_tot(1)),\
										fdc2214_ch1_parasitic_cap,\
										fdc2214_ch1_initial_cap);
		sum += tmp;
	}
	pid.ActualData = sum/10.0;
	
	printf("1 %.10f\n",pid.ActualData);
	float incrementData;
	pid.SetData = data;
	printf("2 %.10f\n",pid.SetData);
	pid.err = pid.SetData - pid.ActualData;
	printf("3 %.10f\n",pid.err);
  incrementData= pid.Kp*(pid.err - pid.err_next) + pid.Ki*pid.err + pid.Kd*(pid.err - 2 * pid.err_next + pid.err_last);//Core
	printf("4 %.10f\n",incrementData);
	float ratio = incrementData/pid.ActualData * 1000;
	printf("5 %.10f\n",ratio);
	if(pid.err > 0)
	{
		motor_ratio(0,200,0.1);
	}
	else if(pid.err < 0)
	{
		motor_ratio(1,200,0.1);
	}
	else
	{
		
	}
	pid.err_last = pid.err_next;
	pid.err_next = pid.err;
	printf("6 %.10f\n",pid.err_last);
	printf("7 %.10f\n",pid.err_next);
	return pid.ActualData;
}

float PID_realize(float data){
	double sum = 0;
	for(int i = 0; i < 10; i ++)
	{
		double tmp = calculate_configured_capacitance_pF(\
										SlidingMeanFilter_ch1(fdc2214_read_ch_tot(1)),\
										fdc2214_ch1_parasitic_cap,\
										fdc2214_ch1_initial_cap);
		sum += tmp;
	}
	pid.ActualData = sum/10.0;
	
	printf("%.10f,",pid.ActualData);
	float incrementData;
	pid.SetData = data;
	printf("%.10f,",pid.SetData);
	pid.err = pid.SetData - pid.ActualData;
	printf("%.10f,",pid.err);
  incrementData= pid.Kp*(pid.err - pid.err_next) + pid.Ki*pid.err + pid.Kd*(pid.err - 2 * pid.err_next + pid.err_last);//Core
	printf("%.10f,",incrementData);
	float ratio = incrementData/pid.SetData * 10;
	printf("%.10f,",ratio);
	float abs_ratio = fabs(ratio);
	printf("%.10f,",abs_ratio);
	if(incrementData > 0)
	{
		motor_ratio(0,200,abs_ratio);
	}
	else if(incrementData < 0)
	{
		motor_ratio(1,200,abs_ratio);
	}
	else
	{
		
	}
	pid.err_last = pid.err_next;
	pid.err_next = pid.err;
	printf("%.10f,",pid.err_last);
	printf("%.10f\n",pid.err_next);
	return pid.ActualData;
}

float PID_realize_filter(float data){
	double sum = 0;
	for(int i = 0; i < 10; i ++)
	{
		double tmp = calculate_configured_capacitance_pF(\
										SlidingMeanFilter_ch1(fdc2214_read_ch_tot(1)),\
										fdc2214_ch1_parasitic_cap,\
										fdc2214_ch1_initial_cap);
		sum += tmp;
	}
	pid.ActualData = sum/10.0;
	
	printf("%.10f,",pid.ActualData);
	float incrementData;
	pid.SetData = data;
	printf("%.10f,",pid.SetData);
	pid.err = pid.SetData - pid.ActualData;
	if(fabs(pid.err/pid.SetData) < 0.1)
	{
		pid.err = 0;
	}
	printf("%.10f,",pid.err);
  incrementData= pid.Kp*(pid.err - pid.err_next) + pid.Ki*pid.err + pid.Kd*(pid.err - 2 * pid.err_next + pid.err_last);//Core
	printf("%.10f,",incrementData);
	float ratio = incrementData/pid.SetData * 10;
	printf("%.10f,",ratio);
	float abs_ratio = fabs(ratio);
	printf("%.10f,",abs_ratio);
	if(incrementData > 0)
	{
		motor_ratio(0,200,abs_ratio);
	}
	else if(incrementData < 0)
	{
		motor_ratio(1,200,abs_ratio);
	}
	else
	{
		
	}
	pid.err_last = pid.err_next;
	pid.err_next = pid.err;
	printf("%.10f,",pid.err_last);
	printf("%.10f\n",pid.err_next);
	return pid.ActualData;
}

