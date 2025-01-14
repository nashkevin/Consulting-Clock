#include "consulting_clock.hpp"
#include "pico/stdlib.h"

void Box::PollButtons()
{
    if (resetButton.GetState() == Button::State::Held)
    {
        ResetTimerDisplays();
        return;
    }

    for (uint8_t i = 0; i < TIMER_COUNT; i++)
    {
        Button::State state = timerButtons[i].GetState();
        if (state == Button::State::Held)
        {
            timers[i].ResetTimer();
            return;
        }
        if (state == Button::State::Pressed)
        {
            if (timers[i].isRunning)
            {
                timers[i].PauseTimer();
            }
            else
            {
                timers[i].StartTimer();
                for (uint8_t j = 0; j < TIMER_COUNT; j++)
                {
                    if (j != i) { timers[j].PauseTimer(); }
                }                
            }
            return;
        }
    }
}

void Box::UpdateTimerDisplays()
{
    if (showDisplaySwitch.IsClosed())
    {
        for (uint8_t i = 0; i < TIMER_COUNT; i++)
        {
            if (timers[i].isRunning)
            {
                timers[i].UpdateDisplay();
                break;
            }
        }
    }
}

void Box::ResetTimerDisplays()
{
    for (uint8_t i = 0; i < TIMER_COUNT; i++)
    {
        timers[i].ResetTimer();
        timers[i].UpdateDisplay(true);
    }

    sleep_ms(2000); // hold on zero for a couple seconds before turning off

    for (uint8_t i = 0; i < TIMER_COUNT; i++)
    {
        timers[i].UpdateDisplay(false);
    }
}
