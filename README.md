# milk


//
//Helper Scripts
//
update_location.py <size> <iters> <output>: Runs the benchmark and stores the result in output.
plotLooper.py update_location.py <output>: Automatically runs the benchmark on sizes from 2^8 to 2^24, increasing the iterations until runtime stabilizes. Results are stored in output.

//
//Code
//
update_location <size> <iters> <output>: Runs the benchmark in C and stores the result in output.

plot.py: Plots all of the data. Filenames are hardcoded.