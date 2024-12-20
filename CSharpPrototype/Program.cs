namespace Work_Timer_Box
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Thread thread = new(() =>
            {
                Box box = new();
                box.Start();
            });
            thread.SetApartmentState(ApartmentState.STA);
            thread.Start();
        }
    }
}
