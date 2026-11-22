#include "nrf52840.h"


// Resistor is on 104 which is mapped to D8, P1.04

// P0
static constexpr uint32_t P0_00 = 1UL << 0;
static constexpr uint32_t P0_01 = 1UL << 1;
static constexpr uint32_t P0_02 = 1UL << 2;
static constexpr uint32_t P0_03 = 1UL << 3;
static constexpr uint32_t P0_04 = 1UL << 4;
static constexpr uint32_t P0_05 = 1UL << 5;
static constexpr uint32_t P0_06 = 1UL << 6;
static constexpr uint32_t P0_07 = 1UL << 7;
static constexpr uint32_t P0_08 = 1UL << 8;
static constexpr uint32_t P0_09 = 1UL << 9;
static constexpr uint32_t P0_10 = 1UL << 10;
static constexpr uint32_t P0_11 = 1UL << 11;
static constexpr uint32_t P0_12 = 1UL << 12;
static constexpr uint32_t P0_13 = 1UL << 13;
static constexpr uint32_t P0_14 = 1UL << 14;
static constexpr uint32_t P0_15 = 1UL << 15;
static constexpr uint32_t P0_16 = 1UL << 16;
static constexpr uint32_t P0_17 = 1UL << 17;
static constexpr uint32_t P0_18 = 1UL << 18;
static constexpr uint32_t P0_19 = 1UL << 19;
static constexpr uint32_t P0_20 = 1UL << 20;
static constexpr uint32_t P0_21 = 1UL << 21;
static constexpr uint32_t P0_22 = 1UL << 22;
static constexpr uint32_t P0_23 = 1UL << 23;
static constexpr uint32_t P0_24 = 1UL << 24;
static constexpr uint32_t P0_25 = 1UL << 25;
static constexpr uint32_t P0_26 = 1UL << 26;
static constexpr uint32_t P0_27 = 1UL << 27;
static constexpr uint32_t P0_28 = 1UL << 28;
static constexpr uint32_t P0_29 = 1UL << 29;
static constexpr uint32_t P0_30 = 1UL << 30;
static constexpr uint32_t P0_31 = 1UL << 31;


// P1
static constexpr uint32_t P1_00 = 1UL << 0;
static constexpr uint32_t P1_01 = 1UL << 1;
static constexpr uint32_t P1_02 = 1UL << 2;
static constexpr uint32_t P1_03 = 1UL << 3;
static constexpr uint32_t P1_04 = 1UL << 4;
static constexpr uint32_t P1_05 = 1UL << 5;
static constexpr uint32_t P1_06 = 1UL << 6;
static constexpr uint32_t P1_07 = 1UL << 7;
static constexpr uint32_t P1_08 = 1UL << 8;
static constexpr uint32_t P1_09 = 1UL << 9;
static constexpr uint32_t P1_10 = 1UL << 10;
static constexpr uint32_t P1_11 = 1UL << 11;
static constexpr uint32_t P1_12 = 1UL << 12;
static constexpr uint32_t P1_13 = 1UL << 13;
static constexpr uint32_t P1_14 = 1UL << 14;
static constexpr uint32_t P1_15 = 1UL << 15;


static uint32_t R3 = P0_17;
static uint32_t R4 = P1_13;
static uint32_t R1 = P0_09;
static uint32_t R2 = P0_10;
static uint32_t R5 = P1_11;
static uint32_t T1 = P0_22;
static uint32_t T2 = P0_11;
static uint32_t T3 = P1_00;
static uint32_t T4 = P0_24;
static uint32_t T5 = P0_20;

static void R3_LOW()
{
    NRF_P0->OUTCLR = (1UL << 17);
}

static void R3_HIGH()
{
    NRF_P0->OUTSET = (1UL << 17);
}

static void R4_LOW()
{
    NRF_P1->OUTCLR = (1UL << 13);
}

static void R4_HIGH()
{
    NRF_P1->OUTSET = (1UL << 13);
}

static void R1_HIGH()
{
    NRF_P0->OUTSET = (1UL << 9);
}

static void R1_LOW()
{
    NRF_P0->OUTCLR = (1UL << 9);
}

static void R2_HIGH()
{
    NRF_P0->OUTSET = (1UL << 10);
}

static void R2_LOW()
{
    NRF_P0->OUTCLR = (1UL << 10);
}

static void R5_HIGH()
{
    NRF_P1->OUTSET = (1UL << 11);
}

static void R5_LOW()
{
    NRF_P1->OUTCLR = (1UL << 11);
}

static void T1_HIGH()
{
    NRF_P0->OUTSET = T1;
}

static void T2_HIGH()
{
    NRF_P0->OUTSET = T2;
}

static void T3_HIGH()
{
    NRF_P1->OUTSET = T3;
}

static void T4_HIGH()
{
    NRF_P0->OUTSET = T4;
}

static void T5_HIGH()
{
    NRF_P0->OUTSET = T5;
}

static void T1_LOW()
{
    NRF_P0->OUTCLR = T1;
}

static void T2_LOW()
{
    NRF_P0->OUTCLR = T2;
}

static void T3_LOW()
{
    NRF_P1->OUTCLR = T3;
}

static void T4_LOW()
{
    NRF_P0->OUTCLR = T4;
}

static void T5_LOW()
{
    NRF_P0->OUTCLR = T5;
}


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

static uint32_t SEG_A = T3;
static uint32_t SEG_B = R5;
static uint32_t SEG_C = R1;
static uint32_t SEG_D = R2;
static uint32_t SEG_E = T1;
static uint32_t SEG_F = T4;
static uint32_t SEG_G = T5;

static uint32_t SEG_ALL =
    SEG_A | SEG_B | SEG_C | SEG_D |
    SEG_E | SEG_F | SEG_G;

static uint32_t DIGIT[10] =
{
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,       // 0
    SEG_B | SEG_A,                                       // 1
    SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,               // 2
    SEG_E | SEG_F | SEG_C | SEG_D | SEG_G,               // 3
    SEG_B | SEG_D | SEG_E | SEG_G,                       // 4
    SEG_E | SEG_C | SEG_B | SEG_F | SEG_G,               // 5
    SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,       // 6
    SEG_D | SEG_E | SEG_C,                               // 7
    SEG_ALL,                                             // 8
    SEG_E | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G        // 9
};

static uint32_t SEG_P0 =
    R1 | R2 | T1 | T4 | T5;

static uint32_t SEG_P1 =
    R5 | T3;

static void display_digit(uint8_t digit)
{
    if (digit > 9)
        return;

    uint32_t mask = DIGIT[digit];

    // Turn all segments off first
    NRF_P0->OUTCLR = SEG_P0;
    NRF_P1->OUTCLR = SEG_P1;

    // Turn required segments on
    NRF_P0->OUTSET = mask & SEG_P0;
    NRF_P1->OUTSET = mask & SEG_P1;
}

static void select_upper()
{
    R4_HIGH();  // lower digit off
    R3_LOW();   // upper digit on
}

static void select_lower()
{
    R3_HIGH();  // upper digit off
    R4_LOW();   // lower digit on
}
// Blank all segment lines. Always do this before switching which digit
// is selected (R3/R4), otherwise the previous digit's segment pattern
// briefly "ghosts" onto the newly selected digit.
static void blank_segments()
{
    NRF_P0->OUTCLR = SEG_P0;
    NRF_P1->OUTCLR = SEG_P1;
}

// Show only the upper digit for one multiplex frame.
static void show_upper(uint8_t value)
{
    blank_segments();
    select_upper();
    display_digit(value);
}

// Show only the lower digit for one multiplex frame.
static void show_lower(uint8_t value)
{
    blank_segments();
    select_lower();
    display_digit(value);
}


int main()
{
    NRF_P0->DIRSET = P0_17 | P0_20 | P0_24;
    NRF_P1->DIRSET = P1_6;

    // The number being counted, updated once every UPDATE_INTERVAL_MS.
    uint8_t number = 0;
    uint32_t elapsed_ms = 0;

    // How long each digit stays lit per multiplex pass. Needs to be short
    // enough (a few ms) that both digits appear lit at once to the eye.
    const uint32_t REFRESH_MS = 2;
    const uint32_t UPDATE_INTERVAL_MS = 500;

    while (true) {
        uint8_t upper = number / 10;
        uint8_t lower = number % 10;

        // One multiplex cycle: light upper digit briefly, then lower digit
        // briefly. Repeating this fast enough makes both appear lit
        // simultaneously (persistence of vision).
        show_upper(upper);
        delay_ms(REFRESH_MS);

        show_lower(lower);
        delay_ms(REFRESH_MS);

        elapsed_ms += 2 * REFRESH_MS;
        if (elapsed_ms >= UPDATE_INTERVAL_MS) {
            elapsed_ms = 0;
            number++;
            if (number > 99) number = 0;
        }
    }
}
