using System.Windows.Input;

namespace Work_Timer_Box
{
    public class Button(Key key) : Timer
    {
        private readonly Key key = key;
        private readonly int requiredHoldTime;

        public Button(Key key, int requiredHoldTime) : this(key)
        {
            this.requiredHoldTime = requiredHoldTime;
        }

        public bool IsNewPress()
        {
            return !IsRunning && IsDown();
        }

        public bool IsButtonHoldSufficient()
        {
            if (IsDown() && requiredHoldTime < GetElapsed())
            {
                return true;
            }
            return false;
        }

        public bool IsDown()
        {
            if (Keyboard.IsKeyDown(key))
            {
                StartTimer();
                return true;
            }
            else
            {
                ResetTimer();
            }
            return false;
        }
    }
}
