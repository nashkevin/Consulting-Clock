#include "consulting_clock.hpp"


TimerDisplay::TimerDisplay(uint8_t pinClk, uint8_t pinDio) : hw(pinClk, pinDio) {}

void TimerDisplay::UpdateDisplay(bool isShowZero)
{
    if (isRunning)
    {
        minutes = GetElapsedMinutes();
        seconds = GetElapsedSeconds();
    } else {
        minutes = 0 < storedMinutes ? storedMinutes : 0;
        seconds = 0 < storedSeconds ? storedSeconds : 0;
    }

    if (isRunning || 0 < seconds || 0 < minutes)
    {
        hw.SetTime(minutes, seconds);
    }
    else if (isShowZero)
    {
        hw.SetZero();
    } else {
        hw.SetOff();
    }
}
