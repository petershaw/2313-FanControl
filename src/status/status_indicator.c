
#include <stdlib.h>
#include <avr/io.h>

#include "status_indicator.h"

static int indicator_is_initalised = 0;

void init_status_indicator(void){
	STATUSLED_REGISTER 	|= _BV(STATUSLED_PIN);
	STATUSLED_PORT &= ~_BV(STATUSLED_PIN);
	indicator_is_initalised = 1;
}

void mark_as_error(void){
	if(indicator_is_initalised == 0){
		init_status_indicator();
	}
	STATUSLED_PORT |= _BV(STATUSLED_PIN);
}

void release_error(void){
	if(indicator_is_initalised == 0){
		init_status_indicator();
	}
	STATUSLED_PORT &= ~_BV(STATUSLED_PIN);
}