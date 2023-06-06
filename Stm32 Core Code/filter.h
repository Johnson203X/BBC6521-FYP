#ifndef __FILTER_H
#define __FILTER_H

#include "./SYSTEM/SYS/sys.h"

#define Window_Size 10

uint32_t SlidingMeanFilter_ch0(uint32_t input);
uint32_t SlidingMeanFilter_ch1(uint32_t input);
uint32_t SlidingMeanFilter_ch2(uint32_t input);

#endif

