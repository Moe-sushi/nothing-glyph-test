# NOTE:
You need to root your phone to use the sysfs interface.
# Phone(1):
TODO
# Phone(2):
The driver is registered in `/sys/bus/i2c/drivers/aw20036_led/0-003a/leds/led_strips` (aka. `/sys/devices/platform/soc/994000.i2c/i2c-0/0-003a/leds/led_strips`)      
Useful interfaces:
- `max_brightness`: the max value of brightness.
- `all_brightness`: write an (int) brightness value into it to enable all leds.
- `all_white_brightness`: for glyph torch.
- `operating_mode`: write 1 into it to use `frame_brightness` and `single_brightness` interface.
- `single_brightness`: write "led-number brightness" into it to control single led. number 13 for video led.
- `frame_brightness` write 32 brightness value into it to control all the leds,seems that it cannot control video light.

For test code to use `single_brightness`and `frame_brightness` interface, see phone2 directory.
