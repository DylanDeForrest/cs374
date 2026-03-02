# Dylan'sGrayscaler

## Building

* type `make` to build
* executable will be called `grayscaler`

## Files

* `grayscaler.c`: all the code for the grayscaler
* `ppm.c`: library for reading and writing PPM images
* `ppm.h`: header for the ppm library

## Data

There is a `struct ppm` that holds the image data including width, height, and a pixel data array. There is also a `struct thread_data` that holds everything a thread needs, like the image pointer, what row to start on, how many rows to process, and the rgb sums it computes.

## Functions

* `main()`: parses args, reads the image, splits it into slices, launches threads, computes averages, writes output
* `greyscale_slice()`: the thread function, converts its slice of the image to grayscale and tracks the sum of rgb values

## Notes

* the number of threads is specified on the command line
* the last thread gets any extra rows if the image height doesnt divide evenly
* each thread prints its starting y coordinate and slice height
* the main thread computes the average rgb from the sums returned by each thread
