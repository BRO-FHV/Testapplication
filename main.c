
#include <Console/lib_console.h>
#include <Led/lib_led.h>
#include <inttypes.h>
/*
 * main.c
 */
void main() {
	BroUdpInit(PORT);

	while (1) {
		if (BroUdpHasData(PORT)) {
			printf("echo\n");

			upd_package_t* package = BroUdpGetData(PORT);
			BroUdpSendData(package->sender, PORT, package->data, package->len);

			free(package->data);
			package->data = NULL;
			package->len = 0;
		}
	}
}
