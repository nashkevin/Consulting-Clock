namespace Work_Timer_Box
{
    public class PausableTimer : Timer
    {
        public long StoredMinutes { get; private set; }
        public long StoredSeconds { get; private set; }

        public void PauseTimer()
        {
            if (IsRunning)
            {
                IsRunning = false;
                StoredMinutes += UnixTimeToMinutes(base.GetElapsed());
                StoredSeconds += UnixTimeToSeconds(base.GetElapsed());
            }
        }

        public override long GetElapsed()
        {
            return base.GetElapsed() + 60 * StoredMinutes + StoredSeconds;
        }

        public override long GetElapsedMinutes()
        {
            return UnixTimeToMinutes(base.GetElapsed() + StoredSeconds) + StoredMinutes;
        }

        public override long GetElapsedSeconds()
        {
            return UnixTimeToSeconds(base.GetElapsed() + StoredSeconds);
        }

        public override void ResetTimer()
        {
            base.ResetTimer();
            StoredMinutes = 0;
            StoredSeconds = 0;
        }
    }
}
