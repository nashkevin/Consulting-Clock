#include <cstdio>
#include "consulting_clock.hpp"
#include "pico/stdlib.h"

Switch::Switch(uint8_t pin)
{
    this->pin = pin;

    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
}

bool Switch::IsClosed()
{
    if (pin != 17 && gpio_get(pin) == 0)
    {
        printf("pin %d = %d\n", pin, gpio_get(pin));
    }
    return gpio_get(pin) == GPIO_LOW;
}
