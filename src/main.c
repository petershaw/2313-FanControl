//
//  main.c
//  AtTiny2313 fan control
//
//

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include <uart.h>

#include "config.h"
#include "status/status_indicator.h"

/* define CPU frequency in Hz in Makefile */
#ifndef F_CPU
#error "F_CPU undefined, please define CPU frequency in Hz in Makefile"
#endif

// DUMMY FUNCTION
// ---------------------------------------------
void *dummy(void){return (void *) NULL;}

// TIMER
volatile unsigned int tick;
volatile unsigned int millisekunden;
volatile unsigned int sekunde;
volatile unsigned int minute;
volatile unsigned int stunde;
volatile unsigned int process;

// INTERRUPT SERVICE
// ---------------------------------------------
// Row multiplexer
ISR (TIMER0_COMPA_vect){
    tick++;
    if(tick == 500){
        tick = 0;
        millisekunden++;
        if(millisekunden == 1000){
            sekunde++;
            millisekunden = 0;
            if(sekunde == 60){
                minute++;
                sekunde = 0;
            }
            if(minute == 60){
                stunde++;
                minute = 0;
            }
            if(stunde == 24){
                stunde = 0;
            }
        }
    }
}

int main(void) {

	// SETUP
	init_status_indicator();
	mark_as_error();
		
	_delay_ms(300);
	
			
	// INIT MULTIPLEX TIMER
    // -----------------------------------------
    TCCR0A |= 1<<WGM01;
    // Timer 0, Prescaller /1024; OVF-Interrupt
    TCCR0B |=  (0<<CS02) | (1<<CS01) | (0<<CS00);
    // Overflow Interrupt erlauben
    TIMSK |= (1<<OCIE0A);
    // Set MAX
    OCR0A |= 5 -1;
    
    
	#if HAS_UART > 0
    	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU) );
    	//init_uart();
	#endif
    	
   	release_error();		 
	sei();
    _delay_ms(100);
	
	#if DEBUG > 0
	    uart_puts("-- fan control --\n");
	#endif    
    process = FALSE;
    
	// LOOP
	while(1){

		if(sekunde % 2 == 0){
            if(process == FALSE) {
                process = TRUE;
                mark_as_error();
                #if HAS_UART > 0
                    char buf[10];
                    itoa(sekunde, buf, 10);
                    uart_puts(buf );
                    uart_puts("\n");
                #endif
            }
        } else {
            process = FALSE;
			release_error();
		}

	}
}
