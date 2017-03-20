
# Settings for the basic options of the target board

# Name of target controller
MCU = attiny2313

# Frequency of the controller
F_CPU = 20000000UL

# Maximum Memory size of eeprom in byte
EE_MAX_SIZE = 128

# Define the board configuration
HAS_LCD				= 0
HAS_UART 			= 0
UART_BAUD_RATE		= 9600

# Boards-LED
LED_CHK				= 2
STATUSLED_REGISTER	= DDRD
STATUSLED_PORT		= PORTD
STATUSLED_PIN		= PD2


# Output debug messages on UART
DEBUG 				= 	1

BOARD_OPTS = 		-DHAS_LCD=$(HAS_LCD) \
					-DHAS_UART=$(HAS_UART) \
					-DUART_BAUD_RATE=$(UART_BAUD_RATE) \
					-DLED_CHK=$(LED_CHK) \
					-DSTATUSLED_REGISTER=$(STATUSLED_REGISTER) \
					-DSTATUSLED_PORT=$(STATUSLED_PORT) \
					-DSTATUSLED_PIN=$(STATUSLED_PIN) \
					-DDEBUG=$(DEBUG)