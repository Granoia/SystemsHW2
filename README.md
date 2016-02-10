# milk



update_location.py <size> <iters> <output>: Runs the benchmark and stores the result in output.
plotLooper.py update_location.py <output>: Automatically runs the benchmark on sizes from 2^8 to 2^24, increasing the iterations until runtime stabilizes. Results are stored in output.

hw1port.c <size> <iters> <output>: Runs the benchmark in C and stores the result in output.
cplotLooper.py <output>: Runs the benchmark (must be compiled as update_location) on sizes from 2^8 to 2^24. Results are stored in output.

plot.py <file.csv>: Plots a csv file.


assembly.c <size> <iters>:  C code with inline assembly. Didn't work for us.

