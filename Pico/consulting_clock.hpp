/**
 * @file    consulting_clock.hpp
 * @brief   
 * @author  Kevin Nash
 * @date    2025-01-12
 */

#include "TM1637.hpp"

const uint32_t US_TO_MIN = 60'000'000;
const uint32_t US_TO_SEC = 1'000'000;
const uint8_t SEC_TO_MIN = 60;
const uint8_t MIN_TO_HOUR = 60;

const uint8_t GPIO_LOW = 0;
const uint8_t GPIO_HIGH = 0; // only use to write - for reads, use !LOW

const uint64_t HOLD_TIME_US = 3'000'000; // 3 seconds

const uint8_t TIMER_COUNT = 5;

class Box
{
    private:
        TimerDisplay timers[TIMER_COUNT] =
        {
            {2, 3}, {4, 5}, {6, 7}, {8, 9}, {10, 11}
        };
        Button timerButtons[TIMER_COUNT] =
        {
            {28}, {27}, {26}, {22}, {21}
        };
        Button resetButton = Button(20);
        Switch hideDisplaySwitch = Switch(17);
    
    public:
        void PollButtons();
        void UpdateTimerDisplays();
        void ResetTimerDisplays();
};

class Button : public Switch, public Timer
{
    private:
        uint64_t requiredHoldTimeUs;

    public:
        Button(uint8_t pin, uint64_t requiredHoldTimeUs = HOLD_TIME_US);

        bool IsNewPress();
        bool IsButtonHoldSufficient();
        bool IsDown() override;
};

class PausableTimer : public Timer
{
    public:
        uint16_t storedMinutes = 0;
        uint16_t storedSeconds = 0;

        /// @brief Stores the current elapsed time and sets a non-running state
        void PauseTimer();
        /// @return elapsed time plus stored time in microseconds
        uint64_t GetElapsed() override;
        /// @return whole minutes of elapsed time plus stored minutes
        uint16_t GetElapsedMinutes() override;
        /// @return whole second remainder of elapsed time plus stored time
        uint16_t GetElapsedSeconds() override;
        void ResetTimer() override;
};

class Switch
{
    protected:
        uint8_t pin;

    public:
        Switch(uint8_t pin);

        virtual bool IsDown();
};

class Timer
{
    public:
        bool isRunning = false;
        uint64_t startTime = 0;

        virtual void StartTimer();
        /// @return elapsed time in microseconds
        virtual uint64_t GetElapsed();
        /// @return whole minutes of elapsed time
        virtual uint16_t GetElapsedMinutes();
        /// @return whole second remainder of elapsed time
        virtual uint16_t GetElapsedSeconds();
        virtual void ResetTimer();
};

class TimerDisplay : public PausableTimer
{
    private:
        uint16_t minutes = 0;
        uint16_t seconds = 0;
        TM1637 hw;
    public:
        TimerDisplay(uint8_t pinClk, uint8_t pinDio);

        /// @brief Change the hardware state
        /// @param isShowZero when timer is zero, show zeroes if true, turn off otherwise
        void UpdateDisplay(bool isShowZero = false);
};
