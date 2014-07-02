#include <Led/lib_led.h>
#include <stdlib/stdlib.h>
#include <lib_basic.h>

/*
 * main.c
 */
int main(void) {
	int state = 1;
	lib_led_on_0();

	while (1) {
		if(state) {
			lib_led_off_0();
			state = 0;
		} else {
			lib_led_on_0();
			state = 1;
		}
	}
}
