#include "consulting_clock.hpp"

void PausableTimer::PauseTimer()
{
    if (isRunning)
    {
        isRunning = false;
        storedMinutes += Timer::GetElapsedMinutes();
        storedSeconds += Timer::GetElapsedSeconds();
    }
}

uint64_t PausableTimer::GetElapsed()
{
    return Timer::GetElapsed() + storedMinutes * US_TO_MIN + storedSeconds * US_TO_SEC;
}

uint16_t PausableTimer::GetElapsedMinutes()
{
    return GetElapsed() / US_TO_MIN;
}

uint16_t PausableTimer::GetElapsedSeconds()
{
    return GetElapsed() % US_TO_MIN / US_TO_SEC;
}

void PausableTimer::ResetTimer()
{
    Timer::ResetTimer();
    storedMinutes = 0;
    storedSeconds = 0;
}
