#include <stdint.h>
#include "TM4C123G_onboardio.h"

/* Port F (on-board IO) register addresses
   Please see TM4C123G data sheet for more information */
#define GPIO_CLK    (*((volatile uint32_t *)0x400FE608))
#define PORTF_DATA  (*((volatile uint32_t *)0x400253FC))
#define PORTF_DIR   (*((volatile uint32_t *)0x40025400))
#define PORTF_AFSEL (*((volatile uint32_t *)0x40025420))
#define PORTF_PUR   (*((volatile uint32_t *)0x40025510))
#define PORTF_DEN   (*((volatile uint32_t *)0x4002551C))
#define PORTF_CR    (*((volatile uint32_t *)0x40025524))
#define PORTF_AMSEL (*((volatile uint32_t *)0x40025528))
#define PORTF_CTL   (*((volatile uint32_t *)0x4002552C))
#define PORTF_LOCK  (*((volatile uint32_t *)0x40025520))

/* Port F GPIO Bits/Keys
   Please see TM4C123G data sheet for more information */
#define GPIO_PORTF     0x20
#define GPIO_PORTF_ALL 0x1F
#define PORTF_KEY      0x4C4F434B


// Disables alternate function select and analog mode select
static void _clear(void) {
    PORTF_AFSEL = 0x0;
    PORTF_AMSEL = 0x0;
    PORTF_CTL = 0x0;
}

// Enables system clock for GPIO Port F
static void _enable_clk(void) {
    GPIO_CLK |= GPIO_PORTF;
}

// Port F has special protection, so it must be unlocked before use as GPIO
static void _unlock(void) {
    PORTF_LOCK = PORTF_KEY;
    PORTF_CR = GPIO_PORTF_ALL;
}

void onboardio_enable(void) {
    _enable_clk();
    _unlock();
    _clear();
}

void onboardio_init(void) {
    sw_init(SW_ALL);
    led_init(LED_ALL);
}

void sw_init(enum SW sw) {
    PORTF_DIR &= ~(sw);
    PORTF_DEN |= sw;
    PORTF_PUR |= sw; // Pull-up resistor means switches are set active low 
}

bool sw_pressed(enum SW sw) {
    return !(PORTF_DATA & sw);
}

bool sw_released(enum SW sw) {
    // Keep track when each switch was last pressed (including SW_ALL)
    static bool sw_was_pressed[3];

    // Figure out which switch we are dealing with for ease of use
    bool *was_pressed;
    if (sw == SW_1) {
        was_pressed = &sw_was_pressed[0];
    } else if (sw == SW_2) {
        was_pressed = &sw_was_pressed[1];
    } else {
        was_pressed = &sw_was_pressed[2];
    }

    /* If the switch is not currently pressed but was pressed recently,
       we know it has just been released */
    if (!sw_pressed(sw) && *was_pressed) {
        *was_pressed = false;
        return true;
    } else if (sw_pressed(sw)) {
        *was_pressed = true;
    }

    return false;
}

void led_init(enum LED led) {
    PORTF_DIR |= led;
    PORTF_DEN |= led;
}

void led_turn_on(enum LED led) {
    PORTF_DATA |= led;
}

void led_turn_off(enum LED led) {
    PORTF_DATA &= ~(led);
}
