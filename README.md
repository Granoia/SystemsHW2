# milk

//
//Questions
//
a) For the python file we ran a script that increases iterations exponentially until the standard deviation is less than 1%.
   The C versions were too variable for this method to work, so instead we let (size+iters) = 2^24.
   
b) We chose the median of 5 measurements because median resists outliers.

c) plots are available in Plot/plot.py

Unoptimized floats were slower than doubles, but optimized floats were equivalent. We believe that doubles are faster on the 64-bit architecture since they don't have to be trimmed, and the optimizer converts floats to double.

Memory was observed using the ./top command. The x86 and C files used about the same memory, but python used five times as much.

//FILES

//
//Helper Scripts-- used to generate data files.
//
cplotLooper.py <output>  Automatically runs ./__output__ on sizes from 2^8 to 2^24. The median of five runs at each size is stored in <output>.
plotLooper.py <output> Automatically runs update_locations.py on sizes from 2^8 to 2^24, increasing the iterations until runtime stabilizes. Results are stored in output.

//
//code
//
All .c files are compiled with -std=gnu99. _double and _float were tested with -O0 and -O3, but _x86 only compiles with -O0.

update_locations.py <size> <iters> <output>: Runs the benchmark in python and stores the result in output.
update_locations_double.c <size> <iters>: C benchmark with doubles. Results are stored in temp.txt.
update_locations_float.c <size> <iters>: C benchmark with floats. Results are stored in temp.txt.
update_locations_x86.c <size> <iters>: C benchmark with doubles and inline x86. Results are stored in temp.txt.

//
//plots
//
plot.py: Plots all of the data. Filenames are hardcoded.
.csv files: Data used for plot.py.
![Alt text](/plots/figure_1.png?raw=true "Plots")
