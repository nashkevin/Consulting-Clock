#include "consulting_clock.hpp"
#include "pico/time.h"

void Timer::StartTimer()
{
    if (!isRunning)
    {
        isRunning = true;
        startTime = time_us_64();
    }
}

uint64_t Timer::GetElapsed()
{
    return startTime == 0 ? 0 : time_us_64() - startTime;
}

uint16_t Timer::GetElapsedMinutes()
{
    return Timer::GetElapsed() / US_TO_MIN;
}

uint16_t Timer::GetElapsedSeconds()
{
    return Timer::GetElapsed() % US_TO_MIN / US_TO_SEC;
}

void Timer::ResetTimer()
{
    if (isRunning)
    {
        isRunning = false;
        startTime = 0;
    }
}

void Timer::RestartTimer()
{
    startTime = 0;
}
