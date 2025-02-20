#include "psm.h"
#include <cstdio>

int main() {
	char command_x[100] = "";

	set_voltage(command_x, 56);

	for (int i = 0; command_x[i] != '\0'; i++) {
		printf("%c\n", command_x[i]);
	}

	return 0;
}