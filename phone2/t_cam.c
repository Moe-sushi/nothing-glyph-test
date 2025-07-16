#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
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
	write(fd, to_write, strlen(to_write));
	close(fd);
}
int main(void)
{
	short leds[33] = { 0 };
	while (true) {
		memset(leds, 0, sizeof(leds));
		for (int i = 80; i > 0; i--) {
			leds[0] = i;
			leds[1] = i;
			write_leds(leds);
			usleep(10*(i+1)*(i+1));
		}
		leds[0] = 0;
		leds[1] = 0;
		write_leds(leds);
		usleep(1000000);
	}
	printf("\n");
}
