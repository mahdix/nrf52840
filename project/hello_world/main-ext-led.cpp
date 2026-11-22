#include "nrf52840.h"


volatile uint32_t system_ms = 0;

extern "C" void SysTick_Handler()
{
    ++system_ms;
}

static void delay_ms(uint32_t ms)
{
    uint32_t start = system_ms;

    while ((system_ms - start) < ms) {
        // Wait
    }
}

int main()
{
	// 64 MHz CPU clock → 1 ms SysTick
    SysTick_Config(SystemCoreClock / 1000);

	// P0.15 = onboard LED
	NRF_P0->DIRSET = (1UL << 15);

	while (true) {

		// LED ON
		NRF_P0->OUTSET = (1UL << 15);
		delay_ms(500);

		// LED OFF
		NRF_P0->OUTCLR = (1UL << 15);
		delay_ms(2000);
	}
}
