#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "TM1637.hpp"

uint8_t testdone[] =
{
    0, 0, 0, 0
};

int main() {
    stdio_init_all();
    printf("zzLET'S GIVE THIS A TRY\n");

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    //gpio_set_outover(PICO_DEFAULT_LED_PIN, GPIO_OVERRIDE_INVERT);

    gpio_init(5);
    gpio_set_dir(5, GPIO_IN);
    gpio_pull_up(5);

    gpio_init(27);
    gpio_set_dir(27, GPIO_OUT);
    gpio_init(26);
    gpio_set_dir(26, GPIO_OUT);

    TM1637 display(27, 26);

    bool isPressed = false;
    
    display.setBrightness(0);

    while (true)
    {
        testdone[0] = SEG_A;
        display.setSegments(testdone);
        sleep_ms(75);
        testdone[0] = 0;
        testdone[1] = SEG_A;
        display.setSegments(testdone);
        sleep_ms(75);
        testdone[1] = 0;
        testdone[2] = SEG_A;
        display.setSegments(testdone);
        sleep_ms(75);
        testdone[2] = 0;
        testdone[3] = SEG_A;
        display.setSegments(testdone);
        sleep_ms(30);
        testdone[3] = SEG_B;
        display.setSegments(testdone);
        sleep_ms(30);
        testdone[3] = SEG_C;
        display.setSegments(testdone);
        sleep_ms(30);
        testdone[3] = SEG_D;
        display.setSegments(testdone);
        sleep_ms(75);
        testdone[3] = 0;
        testdone[2] = SEG_D;
        display.setSegments(testdone);
        sleep_ms(75);
        testdone[2] = 0;
        testdone[1] = SEG_D;
        display.setSegments(testdone);
        sleep_ms(75);
        testdone[1] = 0;
        testdone[0] = SEG_D;
        display.setSegments(testdone);
        sleep_ms(30);
        testdone[0] = SEG_E;
        display.setSegments(testdone);
        sleep_ms(30);
        testdone[0] = SEG_F;
        display.setSegments(testdone);
        sleep_ms(30);
    }
    

    for (uint8_t i = 0; i <= 8; i++)
    {
        if (i == 8)
        {
            i = 0;
        }
        // if (isPressed)
        // {
            
        // }
        // isPressed = gpio_get(5) == 0;
        printf("%d\n", i);
        display.setBrightness(i);
        sleep_ms(1000);
        //display.setSegments(testdone);
    }
}
