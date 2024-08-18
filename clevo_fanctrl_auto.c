// Simple fan control utility for Clevo W650SJ (and maybe others CLEVO)
// by Maxime F4HWD (https://github.com/F4HWD/Clevo-W650SJ_FanControl)
// inspired by fanctrl by Jonas Diemer (diemer@gmx.de)
// Based on LGXfan created by Tord Lindstrom (pukko@home.se)

// Run as root.


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/io.h>
#include <unistd.h>


#define EC_SC 0x66
#define EC_DATA 0x62


#define IBF 1
#define OBF 0
#define EC_SC_READ_CMD 0x80
#define EC_SC_WRITE_CMD 0x81
#define EC_SC_SCI_CMD 0x84

// EC addresses
#define EC_TEMP 0x68
#define EC_CURRENT_FAN_SPEED 0x71
#define EC_TEMP_THRESHOLDS_1 0x69
#define EC_FAN_SPEEDS_1 0x72

static int wait_ec(const uint32_t port, const uint32_t flag, const char value)
{
	uint8_t data;
	int i;

	i = 0;
	data = inb(port);

	while ( (((data >> flag)&0x1)!=value) && (i++ < 100)) {
		usleep(1000);
		data = inb(port);
	}
	if (i >= 100)
	{
		printf("wait_ec error on port 0x%x, data=0x%x, flag=0x%x, value=0x%x\n", port, data, flag, value);
		return 1;
	}

	return 0;
}

static uint8_t read_ec(const uint32_t port)
{
	uint8_t value;

	wait_ec(EC_SC, IBF, 0);
	outb(EC_SC_READ_CMD, EC_SC);

	wait_ec(EC_SC, IBF, 0);
	outb(port, EC_DATA);

	wait_ec(EC_SC, OBF, 1);
	value = inb(EC_DATA);

	return value;
}

static void write_ec(const uint32_t port, const uint8_t value)
{
	wait_ec(EC_SC, IBF, 0);
	outb(EC_SC_WRITE_CMD, EC_SC);

	wait_ec(EC_SC, IBF, 0);
	outb(port, EC_DATA);

	wait_ec(EC_SC, IBF, 0);
	outb(value, EC_DATA);

	wait_ec(EC_SC, IBF, 0);

	return;
}

static void do_ec(const uint32_t cmd, const uint32_t port, const uint8_t value)
{
	wait_ec(EC_SC, IBF, 0);
	outb(cmd, EC_SC);

	wait_ec(EC_SC, IBF, 0);
	outb(port, EC_DATA);

	wait_ec(EC_SC, IBF, 0);
	outb(value, EC_DATA);

	wait_ec(EC_SC, IBF, 0);

	return;
}

static void set_fan_speed(int duty_percentage)
{
	double v_d = ((double) duty_percentage) / 100.0 * 255.0;
	int v_i = (int) v_d;
	do_ec(0x99, 0x01, v_i);
	do_ec(0x99, 0x02, v_i);
}

int main() {
		int Result;
		Result = ioperm(0x62,1,1);
		Result += ioperm(0x66,1,1);
		while(1) {
		if (Result==0) {
			// Temperature < 55°C = fan 50%
			if (read_ec(0x0B) < 55) {
				set_fan_speed(50);
			}
			// Temperature < 60°C = fan 55%
			else if (read_ec(0x0B) < 60) {
				set_fan_speed(55);
			}
			// Temperature < 65°C = fan 70%
			else if (read_ec(0x0B) < 65) {
				set_fan_speed(70);
			}
			// Temperature < 70°C = fan 75%
			else if (read_ec(0x0B) < 70) {
				set_fan_speed(75);
			}
			// Temperature < 75°C = fan 80%
			else if (read_ec(0x0B) < 75) {
				set_fan_speed(80);
			}
			// Temperature < 80°C = fan 85%
			else if (read_ec(0x0B) < 80) {
				set_fan_speed(85);
			}
			// Temperature < 90°C = fan 90%
			else if (read_ec(0x0B) < 90) {
				set_fan_speed(90);
			}
			// Temperature > 90°C = fan 100%
			else {
				set_fan_speed(100);
			}
			sleep(3);
		}
		else {
			exit(1);
		}
	}
	return 0;
}
