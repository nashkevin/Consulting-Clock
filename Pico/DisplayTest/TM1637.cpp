#include <cstdint>
#include <stdio.h>
#include "pico/stdlib.h"
#include "TM1637.hpp"

const uint8_t digitEncoding[] =
{
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111,
};

TM1637::TM1637(uint8_t pinCLK, uint8_t pinDIO)
{
    this->pinCLK = pinCLK;
    this->pinDIO = pinDIO;
    this->brightness = MAX_BRIGHTNESS;

    gpio_set_dir(pinCLK, GPIO_OUT);
    gpio_set_dir(pinDIO, GPIO_OUT);

    gpio_put(pinCLK, LOW);
    gpio_put(pinDIO, LOW);

    printf("clk function %d\n", gpio_get_function(pinCLK));
    printf("dio function %d\n", gpio_get_function(pinDIO));

    // gpio_set_function(pinCLK, GPIO_FUNC_SIO);
    // gpio_set_function(pinDIO, GPIO_FUNC_SIO);

    // gpio_pull_up(pinCLK);
    // gpio_pull_up(pinDIO);

    pause();
}


void TM1637::setBrightness(uint8_t brightness)
{
    this->brightness = (MAX_BRIGHTNESS < brightness) ? MAX_BRIGHTNESS : brightness;
    writeDataCommand();
    writeDisplayCommand();
}

void TM1637::setSegments(const uint8_t *bytes, const uint8_t length, uint8_t position)
{
    if (DIGIT_COUNT < position)
    {
        position = DIGIT_COUNT;
    }
    writeDataCommand();
    start();

    writeByte(CMD_ADDR | position);

    for (uint8_t i = 0; i < length; i++)
    {
        writeByte(bytes[i]);
    }
    stop();
    writeDisplayCommand();
}


void TM1637::start()
{
    gpio_put(pinDIO, LOW);
    pause();
    gpio_put(pinCLK, LOW);
    pause();
}

void TM1637::stop()
{
    gpio_put(pinDIO, LOW);
    pause();
    gpio_put(pinCLK, HIGH);
    pause();
    gpio_put(pinDIO, HIGH);
    pause();
}

void TM1637::pause()
{
    sleep_us(CLK_PAUSE_US);
}

void TM1637::writeDataCommand()
{
    start();
    writeByte(CMD_DATA);
    stop();
}

void TM1637::writeDisplayCommand()
{
    start();
    writeByte(CMD_DISP | DISP_ON | this->brightness);
    stop();
}

void TM1637::writeByte(uint8_t b)
{
    for (uint8_t i = 0; i < BITS_IN_BYTE; i++)
    {
        gpio_put(pinDIO, (b >> i) & HIGH);
        pause();
        gpio_put(pinCLK, HIGH);
        pause();
        gpio_put(pinCLK, LOW);
        pause();
    }
    gpio_put(pinCLK, LOW);
    pause();
    gpio_put(pinCLK, HIGH);
    pause();
    gpio_put(pinCLK, LOW);
    pause();
    
    // commands are answered with an ACK signal,
    // but we're not sophisticated enough to care
}
