#include <stdio.h>
#include <cstdint>
#include "consulting_clock.hpp"
#include "pico/stdlib.h"
#include "TM1637.hpp"


TM1637::TM1637(uint8_t pinClk, uint8_t pinDio)
{
    this->pinClk = pinClk;
    this->pinDio = pinDio;
    this->brightness = DEFAULT_BRIGHTNESS;

    gpio_set_dir(pinClk, GPIO_OUT);
    gpio_set_dir(pinDio, GPIO_OUT);

    gpio_put(pinClk, GPIO_LOW);
    gpio_put(pinDio, GPIO_LOW);

    gpio_set_function(pinClk, GPIO_FUNC_SIO);
    gpio_set_function(pinDio, GPIO_FUNC_SIO);

    Pause();
}


void TM1637::Start()
{
    gpio_put(pinDio, GPIO_LOW);
    Pause();
    gpio_put(pinClk, GPIO_LOW);
    Pause();
}

void TM1637::Stop()
{
    gpio_put(pinDio, GPIO_LOW);
    Pause();
    gpio_put(pinClk, GPIO_HIGH);
    Pause();
    gpio_put(pinDio, GPIO_HIGH);
    Pause();
}

void TM1637::Pause()
{
    sleep_us(CLK_PAUSE_US);
}

void TM1637::WriteByte(uint8_t b)
{
    for (uint8_t i = 0; i < BITS_IN_BYTE; i++)
    {
        gpio_put(pinDio, (b >> i) & GPIO_HIGH);
        Pause();
        gpio_put(pinClk, GPIO_HIGH);
        Pause();
        gpio_put(pinClk, GPIO_LOW);
        Pause();
    }
    gpio_put(pinClk, GPIO_LOW);
    Pause();
    gpio_put(pinClk, GPIO_HIGH);
    Pause();
    gpio_put(pinClk, GPIO_LOW);
    Pause();
    
    // commands are answered with an ACK signal,
    // but we're not sophisticated enough to care
}

void TM1637::WriteDataCommand()
{
    Start();
    WriteByte(CMD_DATA);
    Stop();
}

void TM1637::WriteDisplayCommand()
{
    Start();
    WriteByte(CMD_DISP | DISP_ON | this->brightness);
    Stop();
}

void TM1637::SetSegments(const uint8_t *bytes, const uint8_t length, uint8_t position)
{
    if (MODULE_COUNT < position)
    {
        position = MODULE_COUNT;
    }
    WriteDataCommand();
    Start();

    WriteByte(CMD_ADDR | position);

    for (uint8_t i = 0; i < length; i++)
    {
        WriteByte(bytes[i]);
    }
    Stop();
    WriteDisplayCommand();
}

uint8_t TM1637::GetFlippedByte(uint8_t b)
{
    return
        (b & (SEG_A | SEG_B | SEG_C)) << 3 |
        (b & (SEG_D | SEG_E | SEG_F)) >> 3 |
        (b & (SEG_G | SEG_SEP));
}


void TM1637::SetBrightness(uint8_t brightness)
{
    this->brightness = (MAX_BRIGHTNESS < brightness) ? MAX_BRIGHTNESS : brightness;
    WriteDataCommand();
    WriteDisplayCommand();
}

void TM1637::SetBrightness()
{
    brightness = (MAX_BRIGHTNESS <= brightness) ? 0 : brightness + 1;
}

void TM1637::SetDigits(uint16_t digits)
{
    uint16_t divisor = 1000;
    for (uint8_t i = 0; i < MODULE_COUNT; i++)
    {
        display[i] = (digits < divisor) ? 0 : DIGIT_ENCODING[digits / divisor % 10];
        divisor /= 10;
    }
    SetSegments(display, MODULE_COUNT, 0);
}

void TM1637::SetTime(uint16_t minutes, uint16_t seconds)
{
    if (MODULE_COUNT != 4)
    {
        //throw std::logic_error("Only four-digit displays are supported currently");
        return;
    }

    if (minutes <= 99) // possible to show mm:ss
    {
        if (minutes < 10)
        {
            display[0] = 0;
            display[1] = DIGIT_ENCODING[minutes];
        } else {
            display[0] = DIGIT_ENCODING[minutes / 10];
            display[1] = DIGIT_ENCODING[minutes % 10];
        }
        display[2] = DIGIT_ENCODING[seconds / 10];
        display[3] = DIGIT_ENCODING[seconds % 10];
    }
    else // display hh:mm
    {
        if (600 <= minutes) // both hour digits needed
        {
            display[0] = DIGIT_ENCODING[minutes / MIN_TO_HOUR];      // no room for an H here, but
            display[1] = DIGIT_ENCODING[minutes / MIN_TO_HOUR / 10]; // 10-hour daily tasks are rare
        } else {
            display[0] = H_ENCODING; // show an H to make it clear we're showing hh:mm
            display[1] = DIGIT_ENCODING[minutes / MIN_TO_HOUR];
        }
        display[2] = DIGIT_ENCODING[minutes % MIN_TO_HOUR];
        display[3] = DIGIT_ENCODING[minutes % MIN_TO_HOUR / 10];
    }

    display[1] |= SEG_SEP; // set colon lit

    SetSegments(display, MODULE_COUNT, 0);
}

void TM1637::SetZero()
{
    for (uint8_t i = 0; i < MODULE_COUNT; i++)
    {
        display[i] = DIGIT_ENCODING[0];
    }
    if (1 < MODULE_COUNT)
    {
        display[1] |= SEG_SEP;
    }

    SetSegments(display, MODULE_COUNT, 0);
}

void TM1637::SetOff()
{
    for (uint8_t i = 0; i < MODULE_COUNT; i++)
    {
        display[i] = 0;
    }

    SetSegments(display, MODULE_COUNT, 0);
}

// XXX - broken, in need of debugging
void TM1637::FlipVertical()
{
    for (uint8_t i = 0; i < MODULE_COUNT / 2; i++)
    {
        // TODO - need to transfer the colon bit to the new position
        uint8_t temp = GetFlippedByte(display[i]);
        display[i] = GetFlippedByte(MODULE_COUNT - (i + 1));
        display[MODULE_COUNT - (i + 1)] = temp;
    }

    SetSegments(display, MODULE_COUNT, 0);
}
