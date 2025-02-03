## About

This is a fairly simple electronics project I started to solve the problem of tracking how much time I spend
doing things. I dubbed it "Consulting Clock", but the name isn't important.

Manually tracking time is a pain, and doing so retrospectively is even worse. There are probably apps for this
sort of thing, but I like to minimize my reliance on smartphones. You could use a stopwatch, but if
you wanted to spread your time across multiple tasks within a single work session, you'd need more than one.

Thus this box of stopwatches was born.

The (nearly) finished prototype looks something like this
![image](https://github.com/user-attachments/assets/38c301e4-a153-41fd-a19e-fb8f7e7e2b55)

It's made up of five buttons plus a reset button, five displays, a display muting switch, all of which are
connected to a Pi Pico flashed with the software within the `Pico` folder of this repository and surrounded
by a rigid material (plywood does the trick).

## Functions

- Pressing a top button will start counting time on the display below it; if a count is running on a different
display, it will be paused automatically. Only one counter can run at a time.

- Pressing the top button above a running counter will pause that counter.

- Pressing and holding a top button will reset the count and turn off the display below it.

- Pressing and holding the Reset All (side) button will reset all counts and turn off all displays.

- The Display Switch toggles whether displays are lit. It can be used to hide the displays if they are
distracting. However, it does not stop a counter in progress nor clear stored time. You can start a counter,
then set the switch to OFF, and when you set it back ON, the counter will be accurate to the time you started
it.

- When the Display Switch is OFF, pressing the Reset All button will change the display brightness. The
display modules have eight brightness levels. Each button press will increase the level by one, until the
maximum brightness is reached, at which point the brightness will be set to the minimum level.

- Each display uses a `mm:ss` format until 99 minutes are reached, and then the format becomes `hh:mm`.


## Planning Documents
![image](https://github.com/user-attachments/assets/dd8e6f7d-5712-434d-bb7e-95afcd01d34c)
![image](https://github.com/user-attachments/assets/7190c644-a616-464b-9561-7789d0f01bb7)





