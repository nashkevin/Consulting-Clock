#include "consulting_clock.hpp"

Button::Button(uint8_t pin, uint64_t requiredHoldTimeUs) : Switch(pin)
{
    this->requiredHoldTimeUs = requiredHoldTimeUs;
}

bool Button::IsNewPress()
{
    return !isRunning && IsDown();
}

bool Button::IsButtonHoldSufficient()
{
    if (requiredHoldTimeUs == 0)
    {
        return true;
    }
    return IsDown() && requiredHoldTimeUs < GetElapsed();
}

bool Button::IsDown()
{
    bool isDown = Switch::IsDown();
    if (0 < requiredHoldTimeUs)
    {
        if (isDown)
        {
            StartTimer();
        } else {
            ResetTimer();
        }
    }
    return isDown;
}
