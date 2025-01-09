#include <cstdint>

#define CMD_DATA 0b01000000 // data command
#define CMD_DISP 0b10000000 // display command
#define CMD_ADDR 0b11000000 // address command

/* segment bits */
#define SEG_A    0b00000001
#define SEG_B    0b00000010
#define SEG_C    0b00000100
#define SEG_D    0b00001000
#define SEG_E    0b00010000
#define SEG_F    0b00100000
#define SEG_G    0b01000000
#define SEG_SEP  0b10000000 // colon separator, don't-care except on the digit to its left (X1:XX)

/* bit to enable display */
#define DISP_ON  0b00001000

#define CLK_PAUSE_US 10 // microseconds between CLK transmissions

#define MAX_BRIGHTNESS 7 // defined by TM1637 spec, 1/16th pulse width increments
#define DIGIT_COUNT 4 // how many sets of 7-segments are in a display unit

#define BITS_IN_BYTE 8 // a true constant in modern computing
#define LOW 0
#define HIGH 1

/**
 * The TM1637 datasheet is available from the Titan Micro Electronics website
 * http://www.titanmec.com/product/display-drivers/led-panel-display-driver-chip/p/2.html
 * 
 * Several constants are derived from the information provided therein.
 */
class TM1637
{
    public:
        TM1637(uint8_t pinCLK, uint8_t pinDIO);
        
        void setBrightness(uint8_t brightness);
        /// @brief Set the state of a 7-segment display
        /// @param bytes the encoded state
        /// @param length the number of bytes encoded
        /// @param position which 7-segment display is selected
        void setSegments(const uint8_t* bytes, const uint8_t length = 4, uint8_t position = 0);
        void setTime(uint8_t minutes, uint8_t seconds);
    
    protected:
        uint8_t pinCLK;
        uint8_t pinDIO;
        uint8_t brightness;

        void start();
        void stop();
        void pause();

        void writeDataCommand();
        void writeDisplayCommand();

        void writeByte(uint8_t b);
};
