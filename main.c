#include <Led/lib_led.h>
#include <Eth/lib_eth.h>
#include <stdlib/stdlib.h>
#include <lib_basic.h>

#define PORT					2000
#define LENGTH_USERNAME 		7 //Byte
#define CMD_LED					1

uint8_t BROADCAST_IP[] = { 255, 255, 255, 255 };

typedef struct {
	uint8_t username[LENGTH_USERNAME];
	uint8_t cmd;
} tCmd;

typedef struct {
	tCmd cmd;
	uint8_t led;
	uint8_t state;
} tCmd_Led;

/*
 * main.c
 */
int main(void) {
	lib_udp_init(PORT);

	while (1) {
		if (lib_udp_has_data(PORT)) {
			lib_udp_package_t* package = lib_udp_get_data(PORT);
			tCmd* command = (tCmd*) (package->data);

			if (CMD_LED == command->cmd) {
				tCmd_Led* ledCmd = (tCmd_Led*) (package->data);

				if (ledCmd->led >= 1 && ledCmd->led <= 4) {
					switch (ledCmd->led) {
					case 2:
						if (ledCmd->state) {
							lib_led_on_1();
						} else {
							lib_led_off_1();
						}
						break;
					case 3:
						if (ledCmd->state) {
							lib_led_on_2();
						} else {
							lib_led_off_2();
						}
						break;
					case 4:
						if (ledCmd->state) {
							lib_led_on_3();
						} else {
							lib_led_off_3();
						}
						break;
					}

					//BROADCAST TO ALL LISTENERS
					lib_udp_send_data(BROADCAST_IP, PORT, package->data, package->len);
				}
			}

			lib_free(package->data);
			package->data = NULL;
			package->len = 0;
		}
	}
}
