
#include <Console/lib_console.h>
/*
 * main.c
 */
int main(void) {
	int i = 0;
	while(i < 1000){
		i = i + 1;
		lib_print("New int: %d", i);
	}
	return 0;
}
