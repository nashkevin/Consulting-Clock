#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "TM1637.hpp"

uint8_t testOff[] =
{
    0, 0, 0, 0
};
uint8_t testOn[] =
{
    0b00000110, 0b11011011, 0b01001111, 0b01100110 // 1234
};

const uint8_t PIN_DISP_1_CLK = 2;
const uint8_t PIN_DISP_1_DIO = 3;
const uint8_t PIN_DISP_2_CLK = 4;
const uint8_t PIN_DISP_2_DIO = 5;
const uint8_t PIN_DISP_3_CLK = 6;
const uint8_t PIN_DISP_3_DIO = 7;
const uint8_t PIN_DISP_4_CLK = 8;
const uint8_t PIN_DISP_4_DIO = 9;
const uint8_t PIN_DISP_5_CLK = 10;
const uint8_t PIN_DISP_5_DIO = 11;

const uint8_t PIN_SWCH = 19;

const uint32_t US_TO_MIN = 60000000;
const uint32_t US_TO_SEC = 1000000;

uint8_t switchState;
uint64_t startTime;
uint64_t currentTime;
uint8_t currentMinute;
uint8_t currentSecond;

void setupGPIO()
{
    stdio_init_all();

    gpio_init(PIN_SWCH);
    gpio_set_dir(PIN_SWCH, GPIO_IN);
    gpio_pull_up(PIN_SWCH);

    gpio_init(PIN_DISP_1_CLK);
    gpio_set_dir(PIN_DISP_1_CLK, GPIO_OUT);
    gpio_init(PIN_DISP_1_DIO);
    gpio_set_dir(PIN_DISP_1_DIO, GPIO_OUT);

    gpio_init(PIN_DISP_2_CLK);
    gpio_set_dir(PIN_DISP_2_CLK, GPIO_OUT);
    gpio_init(PIN_DISP_2_DIO);
    gpio_set_dir(PIN_DISP_2_DIO, GPIO_OUT);

    gpio_init(PIN_DISP_3_CLK);
    gpio_set_dir(PIN_DISP_3_CLK, GPIO_OUT);
    gpio_init(PIN_DISP_3_DIO);
    gpio_set_dir(PIN_DISP_3_DIO, GPIO_OUT);

    gpio_init(PIN_DISP_4_CLK);
    gpio_set_dir(PIN_DISP_4_CLK, GPIO_OUT);
    gpio_init(PIN_DISP_4_DIO);
    gpio_set_dir(PIN_DISP_4_DIO, GPIO_OUT);

    gpio_init(PIN_DISP_5_CLK);
    gpio_set_dir(PIN_DISP_5_CLK, GPIO_OUT);
    gpio_init(PIN_DISP_5_DIO);
    gpio_set_dir(PIN_DISP_5_DIO, GPIO_OUT);
}

int main() {
    setupGPIO();
    printf("ttHERE WE GO\n");
    startTime = time_us_64();

    TM1637 display1(PIN_DISP_1_CLK, PIN_DISP_1_DIO);
    TM1637 display2(PIN_DISP_2_CLK, PIN_DISP_2_DIO);
    TM1637 display3(PIN_DISP_3_CLK, PIN_DISP_3_DIO);
    TM1637 display4(PIN_DISP_4_CLK, PIN_DISP_4_DIO);
    TM1637 display5(PIN_DISP_5_CLK, PIN_DISP_5_DIO);

    display1.setBrightness(0);
    display2.setBrightness(0);
    display3.setBrightness(0);
    display4.setBrightness(0);
    display5.setBrightness(0);

    while (true)
    {
        switchState = gpio_get(PIN_SWCH);
        printf("switch = %d\n", switchState);

        if (switchState == LOW)
        {
            currentTime = time_us_64();
            currentMinute = currentTime / US_TO_MIN;
            currentSecond = currentTime % US_TO_MIN / US_TO_SEC;

            display1.setTime(currentMinute, currentSecond);;
            display2.setTime(currentMinute, currentSecond);
            display3.setTime(currentMinute, currentSecond);
            display4.setTime(currentMinute, currentSecond);
            display5.setTime(currentMinute, currentSecond);
        }
        sleep_ms(500); // let our chip rest after all that long division
    }
}
