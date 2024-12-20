using System.Text;
using System.Windows.Input;

namespace Work_Timer_Box
{
    public class Box
    {
        public static long CurrentTime { get; private set; }

        private readonly TimerDisplay[] timers = [new(), new(), new(), new(), new()];
        private readonly Button[] timerButtons = [
            new(Key.NumPad1, 2),
            new(Key.NumPad2, 2),
            new(Key.NumPad3, 2),
            new(Key.NumPad4, 2),
            new(Key.NumPad5, 2),
        ];
        private readonly Button resetButton = new(Key.NumPad0, 2);

        public void Start()
        {
            while (!Keyboard.IsKeyDown(Key.Escape))
            {
                CurrentTime = DateTimeOffset.UtcNow.ToUnixTimeSeconds();
                PollButtons();
                UpdateTimerDisplays();
                Thread.Sleep(15);
                Console.Clear();
            }
        }

        private void PollButtons()
        {
            if (resetButton.IsButtonHoldSufficient())
            {
                ResetTimerDisplays();
                return;
            }

            for (int i = 0; i < timerButtons.Length; i++)
            {
                if (timerButtons[i].IsNewPress())
                {
                    if (timers[i].IsRunning)
                    {
                        timers[i].PauseTimer();
                    }
                    else
                    {
                        timers[i].StartTimer();
                        for (int j = 0; j < timers.Length; j++)
                        {
                            if (j != i)
                            {
                                timers[j].PauseTimer();
                            }
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

        private void UpdateTimerDisplays()
        {
            if (!IsHideSwitchOn())
            {
                StringBuilder sb = new();

                for (int i = 0; i < timers.Length; i++)
                {
                    sb.Append(timers[i].UpdateDisplay());
                    sb.Append("  ");
                }

                if (0 < sb.Length)
                {
                    Console.WriteLine(sb.ToString());
                }
            }
        }

        private void ResetTimerDisplays()
        {
            StringBuilder sb = new();

            for (int i = 0; i < timers.Length; i++)
            {
                timers[i].ResetTimer();
                sb.Append(timers[i].UpdateDisplay(isShowZero: true));
                sb.Append("  ");
            }

            if (0 < sb.Length)
            {
                Console.WriteLine(sb.ToString());
            }

            Thread.Sleep(2000); // hold on zero for a couple seconds before turning off

            for (int i = 0; i < timers.Length; i++)
            {
                timers[i].ResetTimer();
            }
        }

        // box hardware will include a switch to turn off display while timers keep going
        private static bool IsHideSwitchOn()
        {
            return false;
        }
    }
}
