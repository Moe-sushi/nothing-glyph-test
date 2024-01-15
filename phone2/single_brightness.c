#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#define operating_mode "/sys/devices/platform/soc/994000.i2c/i2c-0/0-003a/leds/led_strips/operating_mode"
#define single_brightness "/sys/devices/platform/soc/994000.i2c/i2c-0/0-003a/leds/led_strips/single_brightness"
void write_single_led(short led, u_int brightness)
{
	int fd = open(operating_mode, O_RDWR);
	write(fd, "1\n", 2);
	close(fd);
	char buf[16] = { '\0' };
	sprintf(buf, "%d %d", led, brightness);
	// Uncomment this line to show what's written into single_brightness.
        // printf("\n%s\n",buf);
	fd = open(single_brightness, O_WRONLY);
	write(fd, buf, strlen(buf));
	close(fd);
}
int main(void)
{
	for (int i = 0; i <= 33; i++) {
		printf("\r\033[34mLED \033[32m%2d \033[34m ON\033[0m\a", i);
		fflush(stdout);
		write_single_led(i, 114);
		sleep(1);
		write_single_led(i, 0);
	}
	printf("\n");
}
