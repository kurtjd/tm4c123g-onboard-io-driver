#include <stdbool.h>


// Represents the bit number for each switch
enum SW {
    SW_1   = 0x10,
    SW_2   = 0x01,
    SW_ALL = 0x11
};

// Represents the bit number for each LED
enum LED {
    LED_RED    = 0x02,
    LED_GREEN  = 0x08,
    LED_BLUE   = 0x04,
    LED_YELLOW = 0x0A,
    LED_PURPLE = 0x06,
    LED_CYAN   = 0x0C,
    LED_WHITE  = 0x0E,
    LED_ALL    = LED_WHITE
};


// Enables on-board IO to allow for reading and writing data
void onboardio_enable(void);

// Initializes all on-board switches and LEDs
void onboardio_init(void);

// Initializes a given switch
void sw_init(enum SW sw);

// Returns true if a given switch is being pressed, otherwise false
bool sw_pressed(enum SW sw);

// Returns true if a given switch has been released, otherwise false
bool sw_released(enum SW sw);

// Initializes a given LED
void led_init(enum LED led);

// Turns on a given LED
void led_turn_on(enum LED led);

// Turns off a given LED
void led_turn_off(enum LED led);
