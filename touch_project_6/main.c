#include <atmel_start.h>
#include "touch.h"
extern volatile uint8_t measurement_done_touch;


int main(void)
{
	uint8_t key_status0 = 0;
	

	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* Enable interrupts */
	//SREG |= 0x80;

	/* If any of the two self-capacitance buttons is touched, the LED is turned ON
	 * When touch is released, the LED is turned OFF
	 */
	DDRB |= 1<<DDRB5;
	while (1) {
		/* Does acquisition and post-processing */
		touch_process();
		if (measurement_done_touch == 1) {
			measurement_done_touch = 0;

			key_status0 = get_sensor_state(0) & 0x80;
			
			if (0u != key_status0)
				PORTB &= ~(1<<PORTB5);
			else
				PORTB |= 1<<PORTB5;
		}
	}
}
