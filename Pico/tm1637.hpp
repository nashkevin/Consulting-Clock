/**
 * @file    tm1637.hpp
 * @brief   Provides control methods for the TM1637 display part.
 * @author  Kevin Nash
 * @date    2025-01-12
 */

#pragma once
#include <cstdint>

const uint8_t CMD_DATA = 0b01000000; // data command
const uint8_t CMD_DISP = 0b10000000; // display command
const uint8_t CMD_ADDR = 0b11000000; // address command

/* segment bits */
const uint8_t SEG_A   = 0b00000001;
const uint8_t SEG_B   = 0b00000010;
const uint8_t SEG_C   = 0b00000100;
const uint8_t SEG_D   = 0b00001000;
const uint8_t SEG_E   = 0b00010000;
const uint8_t SEG_F   = 0b00100000;
const uint8_t SEG_G   = 0b01000000;
const uint8_t SEG_SEP = 0b10000000; // colon separator, don't-care except on the digit to its left (X1:XX)

/* bit that controls display on/off */
const uint8_t DISP_ON = 0b00001000;

const uint8_t CLK_PAUSE_US = 10; // microseconds between CLK transmissions

const uint8_t MAX_BRIGHTNESS = 7; // defined by TM1637 spec, 1/16th pulse width increments
const uint8_t MODULE_COUNT = 4; // how many 7-segment modules are in a display

const uint8_t BITS_IN_BYTE = 8; // a true constant in modern computing

/* segment encoding for each index as a digit */
const uint8_t DIGIT_ENCODING[] =
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
    0b01101111
};

/* segment encoding for an uppercase H */
const uint8_t H_ENCODING = 0b11110110;


/**
 * The TM1637 datasheet is available from the Titan Micro Electronics website
 * http://www.titanmec.com/product/display-drivers/led-panel-display-driver-chip/p/2.html
 * 
 * Several constants are derived from the information provided therein.
 */
class TM1637
{
    private:
        uint8_t pinClk;
        uint8_t pinDio;
        uint8_t brightness;
        uint8_t display[MODULE_COUNT] = { };

        void Start();
        void Stop();
        void Pause();

        void WriteByte(uint8_t b);

        void WriteDataCommand();
        void WriteDisplayCommand();

        /// @brief Sets the state of one or more 7-segment modules.
        /// 
        /// Starting at `position`, writes `bytes` until `length` is reached.
        /// @param bytes the encoded state(s)
        /// @param length the number of bytes encoded (how many modules affected)
        /// @param position starting index of the first affected module
        void SetSegments(const uint8_t* bytes, const uint8_t length = 1, uint8_t position = 0);

        /// @brief Flips a single display module vertically
        /// @return a byte that has the ABC segments swapped with DEF,
        ///         other bits match `b`
        static uint8_t GetFlippedByte(uint8_t b);
        
    public:
        TM1637(uint8_t pinClk, uint8_t pinDio);
        
        void SetBrightness(uint8_t brightness);
        
        void SetTime(uint16_t minutes, uint16_t seconds);
        void SetZero();
        void SetOff();

        /// @brief Rotates the entire display 180 degrees.
        ///
        /// Each module has its position reversed and its segments rotated 180 degrees.
        /// This allows the hardware to be panel mounted upside-down if necessary.
        void FlipVertical();
};
