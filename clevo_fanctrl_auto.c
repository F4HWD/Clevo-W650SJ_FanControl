// Simple fan control utility for Clevo W650SJ (and maybe others CLEVO)
// by Maxime F4HWD (https://github.com/F4HWD/Clevo-W650SJ_FanControl)
// inspired by fanctrl by Jonas Diemer (diemer@gmx.de)
// Based on LGXfan created by Tord Lindstrom (pukko@home.se)

// Run as root.


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <unistd.h>

#define EC_SC 0x66
#define EC_DATA 0x62

#define IBF 1
#define OBF 0
#define EC_SC_READ_CMD 0x80
#define EC_SC_WRITE_CMD 0x81


static int wait_ec(uint32_t port, uint32_t flag, char value)
{
    for (int i = 0; i < 100; i++) {
        uint8_t data = inb(port);
        if (((data >> flag) & 0x1) == value) {
            return 0;
        }
        usleep(1000);
    }
    printf("wait_ec error on port 0x%x, flag=0x%x, value=0x%x\n", port, flag, value);
    return 1;
}

static void do_ec(uint32_t cmd, uint32_t port, uint8_t value)
{
    wait_ec(EC_SC, IBF, 0);
    outb(cmd, EC_SC);

    wait_ec(EC_SC, IBF, 0);
    outb(port, EC_DATA);

    wait_ec(EC_SC, IBF, 0);
    outb(value, EC_DATA);

    wait_ec(EC_SC, IBF, 0);
}

static void set_fan_speed(int duty_percentage)
{
    int value = (int)(duty_percentage * 2.55);
    do_ec(0x99, 0x01, value);
}

static uint8_t read_ec(uint32_t port)
{
    wait_ec(EC_SC, IBF, 0);
    outb(EC_SC_READ_CMD, EC_SC);

    wait_ec(EC_SC, IBF, 0);
    outb(port, EC_DATA);

    wait_ec(EC_SC, OBF, 1);
    return inb(EC_DATA);
}

int main() {
    if (ioperm(EC_DATA, 1, 1) || ioperm(EC_SC, 1, 1)) {
        perror("ioperm");
        exit(1);
    }

// You can change values below, but at your own risk
// temp variable in °C
// set_fan_speed in %

    while (1) {
        uint8_t temp = read_ec(0x0B);
        if (temp < 55) {
            set_fan_speed(58);
        } else if (temp < 65) {
            set_fan_speed(70);
        } else if (temp < 70) {
            set_fan_speed(75);
        } else if (temp < 75) {
            set_fan_speed(80);
        } else if (temp < 80) {
            set_fan_speed(85);
        } else if (temp < 90) {
            set_fan_speed(90);
        } else {
            set_fan_speed(100);
        }
        sleep(3);
    }

    return 0;
}
