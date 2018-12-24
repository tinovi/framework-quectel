#include "variant.h"
#include "delay.h"

unsigned int __millis = 0;

unsigned int millis(void) {
	return __millis;
}

unsigned int seconds(void) {
	return __millis / 1000;
}

void delay(unsigned int t) {
	if (t < 10)
		t = 10;
	Ql_Sleep(t);
}

