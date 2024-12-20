namespace Work_Timer_Box
{
    public class Timer
    {
        public bool IsRunning { get; protected set; }
        public long StartTime { get; protected set; }

        public virtual void StartTimer()
        {
            if (!IsRunning)
            {
                IsRunning = true;
                StartTime = Box.CurrentTime;
            }
        }

        public virtual long GetElapsed()
        {
            return StartTime == 0 ? 0 : Box.CurrentTime - StartTime;
        }

        public virtual long GetElapsedMinutes()
        {
            return UnixTimeToMinutes(GetElapsed());
        }

        public virtual long GetElapsedSeconds()
        {
            return UnixTimeToSeconds(GetElapsed());
        }

        public virtual void ResetTimer()
        {
            if (IsRunning)
            {
                IsRunning = false;
                StartTime = 0;
            }
        }


        public static long UnixTimeToMinutes(long time)
        {
            return time / 60;
        }

        public static long UnixTimeToSeconds(long time)
        {
            return time % 60;
        }
    }
}
