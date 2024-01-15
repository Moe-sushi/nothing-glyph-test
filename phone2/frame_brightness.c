#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#define operating_mode "/sys/devices/platform/soc/994000.i2c/i2c-0/0-003a/leds/led_strips/operating_mode"
#define frame_brightness "/sys/devices/platform/soc/994000.i2c/i2c-0/0-003a/leds/led_strips/frame_brightness"
void write_leds(short leds[33])
{
	int fd = open(operating_mode, O_RDWR);
	write(fd, "1\n", 2);
	close(fd);
	char buf[8] = { '\0' };
	char to_write[128] = { '\0' };
	for (int i = 0; i < 33; i++) {
		sprintf(buf, "%d ", leds[i]);
		strcat(to_write, buf);
	}
	fd = open(frame_brightness, O_WRONLY);
	// Uncomment this line to show what's written into frame_brightness.
	// printf("\n%s\n",to_write);
	write(fd, to_write, strlen(to_write));
	close(fd);
}
int main(void)
{
	short leds[33] = { 0 };
	for (int i = 0; i <= 33; i++) {
		printf("\r\033[34mLED \033[32m%2d \033[34m ON\033[0m\a", i);
		fflush(stdout);
		memset(leds, 0, sizeof(leds));
		leds[i] = 114;
		write_leds(leds);
		sleep(1);
	}
	printf("\n");
}
