#include "consulting_clock.hpp"

Button::Button(uint8_t pin, uint64_t requiredHoldTimeUs) : Switch(pin)
{
    this->requiredHoldTimeUs = requiredHoldTimeUs;
}

Button::State Button::GetState()
{
    if (IsClosed())
    {
        if (!isRunning)
        {
            StartTimer();
            return State::Pressed;
        }
        else if (requiredHoldTimeUs < GetElapsed())
        {
            return State::Held;
        }
    }
    ResetTimer();
    return State::Released;
}
