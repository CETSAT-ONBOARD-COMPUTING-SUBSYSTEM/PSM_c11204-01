#pragma once

#include <stdint.h>


#define voltage_conversion (double)(0.001812)
#define current_conversion (double)(0.004980000000000001)


#define PM_STX ('\02')
#define PM_ETX ('\03')
#define PM_CR ('\r')


void send_serial_command_nocheck(char* command_x, const char* command, int value);


void hv_disable(char* command_x);

void hv_enable(char* command_x);

void reset(char* command_x);

void set_voltage(char* command_x, int value);

void get_voltage(char* command_x);

void get_current(char* command_x);

void get_power(char* command_x);

void get_status_raw(char* command_x);
