#include "nrf52840.h"


// Resistor is on 104 which is mapped to D8, P1.04

static constexpr uint32_t LED_PIN = 4;
static constexpr uint32_t LEDS = (1UL << 4) | (1UL << 6);


void delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < ms; ++i)
    {
        for (volatile uint32_t j = 0; j < 8000; ++j)
        {
            __NOP();
        }
    }
}

int main()
{
    // Configure P1.06 as an output
    NRF_P1->DIRSET = LEDS;

    while (true)
    {
        // LED ON
        NRF_P1->OUTSET = LEDS;
        delay_ms(100);

        // LED OFF
        NRF_P1->OUTCLR = LEDS;
        delay_ms(200);


        // LED ON
        NRF_P1->OUTSET = LEDS;
        delay_ms(400);

        // LED OFF
        NRF_P1->OUTCLR = LEDS;
        delay_ms(800);

    }
}
