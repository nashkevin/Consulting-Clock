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
    if (pin == 22)
    {
        printf("Btn 4 (pin 22) = %d\n", gpio_get(pin));
    }
    if (pin == 28)
    {
        printf("Btn 1 (pin 28) = %d\n", gpio_get(pin));
    }
    return gpio_get(pin) == GPIO_LOW;
}
