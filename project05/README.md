# Append Log

## Building

* `make` to build. Makes an executable called `appendlog`.
* `make clean` to remove the executable and log file.

## Files

* `appendlog.c`: All the code
* `Makefile`: For building

## Data

The program creates a file called `logfile.dat` that holds up to 1048576 records, each 32 bytes long. The first 8 bytes of the file are a header that tracks how many records there are and where the next one goes. The rest is the actual records.

## Functions

* `main()`: Opens the file, forks the child processes, waits for them, then prints the log
* `append_record()`: Figures out where to write the next record and writes it
* `lock_region()`: Locks a part of the file so two processes don't write at the same time
* `unlock_region()`: Unlocks the region when done

## Notes

* Run it like: `./appendlog 3 foo 5 bar`
* Each pair is a count and a prefix. Each child process writes that many records.
* The order of records might be different every run depending on how the OS schedules the processes.

## Questions

**What could go wrong if we didn't lock the header?**

Two processes could read the same offset at the same time and both try to write to the same spot. One would overwrite the other. The count would also be wrong because both processes would read the same number, add one, and write the same value back.

**What could go wrong if we didn't lock the record?**

In this program nothing would really break since each process gets its own slot from the header. But if another program was reading the file at the same time, it could read a record that was only halfway written and see garbage data. The lock makes sure the write is fully done before anyone else can read that spot.
