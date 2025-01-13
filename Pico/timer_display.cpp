#include "consulting_clock.hpp"
#include "TM1637.hpp"


TimerDisplay::TimerDisplay(uint8_t pinClk, uint8_t pinDio) : hw(pinClk, pinDio) {}

void TimerDisplay::UpdateDisplay(bool isShowZero)
{
    if (isRunning)
    {
        minutes = GetElapsedMinutes();
        seconds = GetElapsedSeconds();
    }
    else
    {
        if (0 < storedMinutes)
        {
            minutes = storedMinutes;
        }
        if (0 < storedSeconds)
        {
            seconds = storedSeconds;
        }
    }

    if (isRunning || 0 < seconds || 0 < minutes)
    {
        hw.setTime(minutes, seconds);
    }
    else if (isShowZero)
    {
        hw.setZero();
    } else {
        hw.setOff();
    }
}