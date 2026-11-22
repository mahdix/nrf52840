#include "nrf52840.h"


#define LED_PIN 15   // Change to your board's LED GPIO

int main(void)
{
    // Configure LED pin as output
    NRF_P0->DIRSET = (1UL << LED_PIN);

    while (1)
    {
        // LED ON (active-low)
        NRF_P0->OUTCLR = (1UL << LED_PIN);

        // Simple delay
        for (volatile uint32_t i = 0; i < 1500000; i++);

        // LED OFF
        NRF_P0->OUTSET = (1UL << LED_PIN);

        // Simple delay
        for (volatile uint32_t i = 0; i < 500000; i++);
    }
}
