#include "consulting_clock.hpp"
#include "pico/stdlib.h"


int main()
{
    stdio_init_all();
    Box box = Box();
    box.ResetTimerDisplays();

    while (true) {
        box.PollInputs();
        box.UpdateTimerDisplays();
        //box.TestDisplay();
    }
}
