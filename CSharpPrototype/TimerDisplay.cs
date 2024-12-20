using System.Text;

namespace Work_Timer_Box
{
    public class TimerDisplay : PausableTimer
    {
        private long minutes = 0;
        private long seconds = 0;

        // this would ordinarily be void and write to hardware segments
        public string UpdateDisplay(bool isShowZero = false)
        {
            if (IsRunning)
            {
                minutes = GetElapsedMinutes();
                seconds = GetElapsedSeconds();
            }
            else
            {
                if (0 < StoredMinutes)
                {
                    minutes = StoredMinutes;
                }
                if (0 < StoredSeconds)
                {
                    seconds = StoredSeconds;
                }
            }

            if (IsRunning || 0 < seconds || 0 < minutes)
            {
                StringBuilder sb = new();

                sb.Append('[');
                if (minutes < 10) sb.Append('0');
                sb.Append(minutes);
                sb.Append(':');
                if (seconds < 10) sb.Append('0');
                sb.Append(seconds);
                sb.Append(']');

                return sb.ToString();
            }
            return isShowZero ? "[00:00]" : "[  :  ]";
        }
    }
}
