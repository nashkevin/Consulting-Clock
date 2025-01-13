/**
 * @file    tm1637.hpp
 * @brief   Provides control methods for the TM1637 display module.
 * @author  Kevin Nash
 * @date    2025-01-12
 */

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
const uint8_t DIGIT_COUNT = 4; // how many sets of 7-segments are in a display unit

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
        uint8_t display[DIGIT_COUNT] = { };

        void Start();
        void Stop();
        void Pause();

        void WriteDataCommand();
        void WriteDisplayCommand();

        void WriteByte(uint8_t b);
        
    public:
        TM1637(uint8_t pinClk, uint8_t pinDio);
        
        void setBrightness(uint8_t brightness);

        /// @brief Sets the state of one or more 7-segment displays.
        /// 
        /// Starting at position, writes bytes until length is reached.
        /// @param bytes the encoded state(s)
        /// @param length the number of bytes encoded (how many displays affected)
        /// @param position starting index of the first affected display
        void setSegments(const uint8_t bytes[], const uint8_t length = 1, uint8_t position = 0);
        
        void setTime(uint16_t minutes, uint16_t seconds);
        void setZero();
        void setOff();
};
