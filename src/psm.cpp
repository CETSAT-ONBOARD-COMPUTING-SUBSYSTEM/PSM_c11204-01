#include "psm.h"
#include <stdio.h>
#include <string.h>


uint32_t convert_command(const char* command, char* command_hex) {
	uint32_t sum = 0;
	for (int i = 0; command[i] != '\0'; i++) {
		sum += command[i];
		sprintf(&command_hex[i * 2], "%x", command[i]);
	}

	return sum;
}

void send_serial_command_nocheck(char* command_x, const char* command, int value) {
	char command_hex[100] = "";
	uint32_t command_checksum = convert_command(command, command_hex);
	
	char value_hex[100] = "";
	sprintf(value_hex, "%x", value);

	char voltage_hex[100] = "";
	uint32_t voltage_checksum = convert_command(value_hex, voltage_hex);

	char total_checksum_str[100] = "";
	uint32_t total_checksum = (PM_STX + command_checksum + PM_ETX + (value != 0) * voltage_checksum) & 0xff;
	sprintf(total_checksum_str, "%x", total_checksum);


	// char command_x[100] = "";
	command_x[strlen(command_x)] = PM_STX;
	strncat(command_x, command, strlen(command));
	if (value != 0) {
		strncat(command_x, value_hex, strlen(value_hex));
	}
	command_x[strlen(command_x)] = PM_ETX;
	for (int i = 0; total_checksum_str[i] != '\0'; i++) {
		total_checksum_str[i] -= 32;
	}
	strncat(command_x, total_checksum_str, strlen(total_checksum_str));
	command_x[strlen(command_x)] = PM_CR;
}


void hv_disable(char* command_x) {
	send_serial_command_nocheck(command_x, "HOF", 0);
}
// # ['\x02', 'HOF', '\x03', 'E', '2', '\r']
void hv_enable(char* command_x) {
	send_serial_command_nocheck(command_x, "HON", 0);
}
// # ['\x02', 'HON', '\x03', 'E', 'A', '\r']

void reset(char* command_x) {
	send_serial_command_nocheck(command_x, "HRE", 0);
}
// # ['\x02', 'HRE', '\x03', 'E', '4', '\r']

void set_voltage(char* command_x, int value) {
	send_serial_command_nocheck(command_x, "HBV", (int)((double)(value) / voltage_conversion));
}
// # ['\x02', 'HBV', '4', 'b', '7', '4', '\x03', 'E', '6', '\r']

void get_voltage(char* command_x) {
	send_serial_command_nocheck(command_x, "HGV", 0);
}
// # ['\x02', 'HGV', '\x03', 'E', 'A', '\r']

void get_current(char* command_x) {
	send_serial_command_nocheck(command_x, "HGC", 0);
}
// # ['\x02', 'HGC', '\x03', 'D', '7', '\r']

void get_power(char* command_x) {
	send_serial_command_nocheck(command_x, "HPO", 0);
}
// # ['\x02', 'HPO', '\x03', 'E', 'C', '\r']

void get_status_raw(char* command_x) {
	send_serial_command_nocheck(command_x, "HGS", 0);
}
// # ['\x02', 'HGS', '\x03', 'E', '7', '\r']	