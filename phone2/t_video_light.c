#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#define operating_mode "/sys/devices/platform/soc/994000.i2c/i2c-0/0-003a/leds/led_strips/operating_mode"
#define single_brightness "/sys/devices/platform/soc/994000.i2c/i2c-0/0-003a/leds/led_strips/single_brightness"
#define always_on "/sys/devices/platform/soc/994000.i2c/i2c-0/0-003a/leds/led_strips/always_on"
void always_on_led(bool enable)
{
	int fd = open(always_on, O_RDWR);
	if (enable) {
		write(fd, "1\n", 2);
	} else {
		write(fd, "0\n", 2);
	}
	close(fd);
}
void write_single_led(short led, u_int brightness)
{
	always_on_led(true);
	int fd = open(operating_mode, O_RDWR);
	write(fd, "1\n", 2);
	close(fd);
	char buf[16] = { '\0' };
	sprintf(buf, "%d %d", led, brightness);
	fd = open(single_brightness, O_WRONLY);
	write(fd, buf, strlen(buf));
	close(fd);
}
int main(void)
{
	while(true) {
		write_single_led(13, 120);
		usleep(500000);
		write_single_led(13, 0);
		usleep(300000);
	}
	// Disable always on mode
	always_on_led(false);
	printf("\n");
}
