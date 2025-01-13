#include <stdio.h>
#include "consulting_clock.hpp"
#include "pico/stdlib.h"


int main()
{
    stdio_init_all();
    Box box = Box();

    while (true) {
        box.PollButtons();
        box.UpdateTimerDisplays();
        sleep_ms(500); // action only required every second
    }
}
