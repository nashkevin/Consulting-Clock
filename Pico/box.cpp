#include "consulting_clock.hpp"
#include "pico/stdlib.h"

void Box::PollButtons()
{
    if (resetButton.GetState() == Button::State::HeldLong)
    {
        ResetTimerDisplays();
        return;
    }

    for (uint8_t i = 0; i < TIMER_COUNT; i++)
    {
        Button::State state = timerButtons[i].GetState();
        if (state == Button::State::HeldLong)
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
    for (uint8_t i = 0; i < TIMER_COUNT; i++)
    {
        if (showDisplaySwitch.IsClosed())
        {
            timers[i].UpdateDisplay();
        } else {
            timers[i].ClearDisplay();
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

void Box::TestDisplay()
{
    for (uint16_t m = 0; m < 100; m++)
    {
        for (uint16_t s = 0; s < 60; s++)
        {
            timers[0].SetTime(m, s);
            sleep_ms(100);
        }        
    }
}
