#include "./BSP/FILTER/filter.h"
#include "./BSP/FDC2214/fdc2214.h"
#include "./SYSTEM/USART/usart.h"

uint32_t SlidingMeanFilter_ch0(uint32_t input)  
{	
	static int index_ch0 = -1;
  static uint32_t buffer_ch0[Window_Size];
	static uint32_t sum_ch0 = 0;
  uint32_t output = 0;
	
  if(index_ch0 == -1)
	{
    for(int i = 0; i < Window_Size; i++)
    {
      buffer_ch0[i] = input;
    }
    sum_ch0 = input * Window_Size;
    index_ch0 = 0;
  }
  else
  {
    sum_ch0 -= buffer_ch0[index_ch0];
    buffer_ch0[index_ch0] = input;
    sum_ch0 += input;
    index_ch0++;
    if(index_ch0 >= Window_Size)
    {
      index_ch0 = 0;
    }
  }
  output = (uint32_t)(sum_ch0 / Window_Size);
  return output;
}

uint32_t SlidingMeanFilter_ch1(uint32_t input)  
{	
	static int index_ch1 = -1;
  static uint32_t buffer_ch1[Window_Size];
	static uint32_t sum_ch1= 0;
  uint32_t output = 0;
	
  if(index_ch1 == -1)
	{
    for(int i = 0; i < Window_Size; i++)
    {
      buffer_ch1[i] = input;
    }
    sum_ch1 = input * Window_Size;
    index_ch1 = 0;
  }
  else
  {
    sum_ch1 -= buffer_ch1[index_ch1];
    buffer_ch1[index_ch1] = input;
    sum_ch1 += input;
    index_ch1++;
    if(index_ch1 >= Window_Size)
    {
      index_ch1 = 0;
    }
  }
  output = (uint32_t)(sum_ch1 / Window_Size);
  return output;
}

uint32_t SlidingMeanFilter_ch2(uint32_t input)  
{	
	static int index_ch2 = -1;
  static uint32_t buffer_ch2[Window_Size];
  static uint32_t sum_ch2 = 0;
  uint32_t output = 0;
	
  if(index_ch2 == -1)
	{
    for(int i = 0; i < Window_Size; i++)
    {
      buffer_ch2[i] = input;
    }
    sum_ch2 = input * Window_Size;
    index_ch2 = 0;
  }
  else
  {
    sum_ch2 -= buffer_ch2[index_ch2];
    buffer_ch2[index_ch2] = input;
    sum_ch2 += input;
    index_ch2++;
    if(index_ch2 >= Window_Size)
    {
      index_ch2 = 0;
    }
  }
  output = (uint32_t)(sum_ch2 / Window_Size);
  return output;
}