#include "consulting_clock.hpp"
#include "pico/stdlib.h"

void Box::PollButtons()
{
    if (resetButton.IsButtonHoldSufficient())
    {
        ResetTimerDisplays();
        return;
    }

    for (uint8_t i = 0; i < TIMER_COUNT; i++)
    {
        if (timerButtons[i].IsNewPress())
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

        if (timerButtons[i].IsButtonHoldSufficient())
        {
            timers[i].ResetTimer();
            return;
        }
    }
    
}

void Box::UpdateTimerDisplays()
{
    if (!hideDisplaySwitch.IsDown())
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
