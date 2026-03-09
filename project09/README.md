# Producers and Consumers

## Building

Command line:

* `make` to build. An executable called `pc` will be produced.
* `make clean` to clean up all build products.

## Usage

```
./pc <num_producers> <num_consumers> <events_per_producer> <max_outstanding>
```

Example:

```
./pc 2 4 5 2
```

## Files

* `pc.c`: Main code, producer and consumer threads
* `eventbuf.c`: Shared event queue
* `eventbuf.h`: Header for the event queue

## Data

There is a shared FIFO queue of integers called the event buffer. Producers add events to it and consumers remove them. Three semaphores control access: one acts as a lock, one tracks how many events are in the queue, and one tracks how many empty spots are left.

## Functions

* `main()`
  * `sem_open_temp()`: Creates a semaphore that cleans itself up on exit
  * `producer_run()`: Each producer thread runs this — adds events to the queue
  * `consumer_run()`: Each consumer thread runs this — pulls events from the queue

## Notes

* Each producer generates events numbered `producer_id * 100 + event_number`
* When all producers finish, consumers are woken up and exit cleanly
cd ..
