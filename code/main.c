#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void init_ports()
{
    // Set PD0-PD3 as output (LEDs)
    DDRD |= 0x0F;

    // Set PD4 as input (Button)
    DDRD &= ~(1 << PD4);

    // Enable internal pull-up on PD4
    PORTD |= (1 << PD4);
}

int main(void)
{
    uint8_t counter = 0;

    init_ports();

    while (1)
    {
        // Button pressed (active LOW)
        if (!(PIND & (1 << PD4)))
        {
            _delay_ms(50); // Debounce delay

            if (!(PIND & (1 << PD4)))
            {
                counter++;

                if (counter > 15)
                    counter = 0;

                PORTD = (PORTD & 0xF0) | (counter & 0x0F);

                while (!(PIND & (1 << PD4))); // Wait until button released
            }
        }
    }

    return 0;
}
