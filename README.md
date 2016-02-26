# SystemsHW2

We used two programs to determine cache size. Stepper.c steps through a buffer with the formula j := (3*j + 7). Then the value at buffer[j] is written to a dummy variable.

Both programs implement background subtraction by repeating all of the operations except for the read from memory. The duration of the repeat is subtracted from the duration of the original. 

Both programs demonstrated a clear jump in time per write at 2^18 kilobytes (260 megabytes). Model2 also demonstrates a jump at 256 kilobytes. The jump takes place between the 128 and 512 kB ranges. The continuous nature of the jump could be due to half the buffer fitting in the cache while the other half remains uncached.

Cupid 


The Model2 data:
![](/graphs/model2_linear.png?raw=true "Optional Title")
![](/graphs/model2_log.png?raw=true "Optional Title")

The Stepper data:
![](/graphs/adjusted_linear.png?raw=true "Optional Title")
![](/graphs/adjusted_log.png?raw=true "Optional Title")


