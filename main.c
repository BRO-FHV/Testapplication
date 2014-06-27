#include <Led/lib_led.h>
#include <Eth/lib_eth.h>
#include <stdlib/stdlib.h>
#include <lib_basic.h>
#include <inttypes.h>

#define PORT					2000

uint8_t BROADCAST_IP[] = { 255, 255, 255, 255 };

#define LENGTH_USERNAME 		7 //Byte

#define CMD_LED					1

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
void main() {
	SwiUdpInit(PORT);

	while (1) {
		if (SwiUdpHasData(PORT)) {
			swi_udp_package_t* package = SwiUdpGetData(PORT);
			tCmd* command = (tCmd*) (package->data);

			if (CMD_LED == command->cmd) {
				tCmd_Led* ledCmd = (tCmd_Led*) (package->data);

				if (ledCmd->led >= 1 && ledCmd->led <= 4) {
					switch (ledCmd->led) {
					case 1:
						if(ledCmd->state) {
							lib_led_on_0();
						} else {
							lib_led_off_0();
						}
						break;
					case 2:
						if(ledCmd->state) {
							lib_led_on_1();
						} else {
							lib_led_off_1();
						}
						break;
					case 3:
						if(ledCmd->state) {
							lib_led_on_2();
						} else {
							lib_led_off_2();
						}
						break;
					case 4:
						if(ledCmd->state) {
							lib_led_on_3();
						} else {
							lib_led_off_3();
						}
						break;
					}

					//BROADCAST TO ALL LISTENERS
					SwiUdpSendData(BROADCAST_IP, PORT, package->data, package->len);
				}
			}

			lib_free(package->data);
			package->data = NULL;
			package->len = 0;
		}
	}
}
