# Seat Reservations

## Building

* type `make` to build
* executable will be called `reservations`

## Files

* `reservations.c`: all the code

## Data

There is an array called `seat_taken[]` where each element is 0 if the seat is free or 1 if its taken. There is also a counter `seat_taken_count` that tracks how many seats are reserved at a time.

Each broker runs as its own thread and they all try to reserve and unreserve seats at the same time.

## Functions

* `main()`: parses the arguments, allocates memory, and starts the broker threads
* `reserve_seat(n)`: reserves seat n and increments the count, returns -1 if already taken
* `free_seat(n)`: frees seat n and decrements the count, returns -1 if already free
* `verify_seat_count()`: counts taken seats in the array and checks it matches seat_taken_count
* `seat_broker()`: the thread function, does random reserve and free transactions and verifies after each one

## Notes

* uses a recursive mutex to avoid data races on the shared data
* dont use too many brokers or it will slow down your computer