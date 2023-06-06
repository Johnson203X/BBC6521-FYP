#ifndef __PRINT_H
#define __PRINT_H

#include "./SYSTEM/SYS/sys.h"

void print_channel_detail(int ch);
void print_channel_tot(int ch);
void print_capacitance_tot(int ch);

void print_channel_detail_all(void);
void print_channel_tot_all(void);
void print_capacitance_tot_all(void);

void print_to_binary(int input,int bits);

#endif