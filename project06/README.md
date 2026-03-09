# Speed Controller

## Building

* `make` to build. Produces an executable called `speed`.
* `make clean` to clean up.

## Files

* `speed.c`: All the code

## Data

* `speed`: an integer that starts at 0 and can't go below 0.

## Functions

* `main()`: sets up signals, then loops waiting for input or signals
* `handle_usr1()`: decreases speed by 1
* `handle_usr2()`: increases speed by 1

## Notes

* Type `+` to increase speed, `-` to decrease, `q` to quit.
* Send `SIGUSR1` to decrease, `SIGUSR2` to increase.
* PID is printed on startup so you know what to send signals to.
