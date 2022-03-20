# Tiva LaunchPad On-Board IO Driver/Library
This is a very simple driver/library meant to make interfacing with the on-board
IO devices (LEDs and switches) of the Tiva LaunchPad (TM4C123G) easy and intuitive. I made
this mainly as a learning experience to get familiar with reading a data sheet
and reading/writing directly to registers, though hopefully others may find it
useful.

## Usage
1. Copy TM4C123G_onboardio.h and TM4C123G_onboardio.c into your project folder
2. Include `TM4C123G_onboardio.h` into your source file

### API
- Enable board IO (must be done before anything else)  
`void onboardio_enable(void)`


- Initialize all board IO devices at once  
`void onboardio_init(void)`


- Initialize a swich  
`void sw_init(enum SW sw)`


- Check if a switch is pressed  
`bool sw_pressed(enum SW sw)`


- Check if a switch has been released  
`bool sw_released(enum SW sw)`


- Initialize an LED  
`void led_init(enum LED led)`


- Turn on an LED  
`void led_turn_on(enum LED led)`


- Turn off an LED  
`void led_turn_off(enum LED led)`

### Switches
- SW_1
- SW_2
- SW_ALL

### LEDs
- LED_RED
- LED_GREEN
- LED_BLUE
- LED_YELLOW
- LED_PURPLE
- LED_CYAN
- LED_WHITE
- LED_ALL


## Example
This is a simple example where pressing switch 1 on your board will cycle
between the different color LEDs.

```c
#include "TM4C123G_onboardio.h"

// Uses the LED enum provided by library to match 0-6 to a color
static enum LED LED_COLORS[] = {
    LED_RED,
    LED_GREEN,
    LED_BLUE,
    LED_YELLOW,
    LED_PURPLE,
    LED_CYAN,
    LED_WHITE,
};

int main(void) {
    int cur_led = 0;

    // Enable on-board IO and initialize switch 1 as well as all LEDs
    onboardio_enable();
    sw_init(SW_1);
    led_init(LED_ALL);

    // Turn on the LED initially
    led_turn_on(LED_COLORS[cur_led]);

    while (1) {
        // Cycle to the next color if switch 1 is released
        if (sw_released(SW_1)) {
            led_turn_off(LED_COLORS[cur_led]);

            cur_led++;
            if (cur_led > 6) {
                cur_led = 0;
            }

            led_turn_on(LED_COLORS[cur_led]);
        }
    }
}
```
