# SystemsHW2

We used two programs to determine cache size. [Stepper.c](\stepper.c) steps through a buffer with the formula j := (3*j + 7). Then the value at buffer[j] is written to a dummy variable. The [model2](\model2.c) algorithm initializes by creating a buffer with entries [0,1,2,...,254,255,0,1,2,...], and then shuffling it. The buffer is then accessed by randomly picking a 256-sized block of the buffer and accessing the nth value in the block, where n starts with zero and is set to the value of the previously accessed byte with each iteration. 

Both programs implement background subtraction by repeating all of the operations except for the read from memory. The duration of the repeat is subtracted from the duration of the original. 

Both programs demonstrated a clear jump in time per write at 2^18 kilobytes (256 megabytes). Model2 also demonstrates a jump at 256 kilobytes. The jump takes place between the 128 and 512 kB ranges. The continuous nature of the jump could be due to part of the buffer fitting in the cache while the other part remains uncached.

Cpuid was run [(cpuid.c)](\cpuid.c) and produced the following results [(cpuid.txt).](\cpuid.txt):<br/>

5A	Data TLB0: 2Mb or 4MB pages, 4-way set associative, 32 entries <br/>
03	Data TLB: 4 KB pages, 4-way set associative, 64 entries<br/>
76	Instruction TLB: 2M/4M pages, fully associative, 8 entries<br/>
B0	Instruction TLB: 4KB pages, fully associative, 32 entries<br/>
F0	64B prefetching<br/>
CA	Shared 2nd level TLB: 4KB page, 4-way associative, 512 entries<br/>

The latency of the first step (1-128 kB) is 0.5-1 ns, which agrees with the performance of the L1 cache on norvig (0.5ns). The latency of the second step (256kB - 8 mB) is 4-8ns, which agrees with the performance of the L2 cache on norvig (7ns). The latency of the third step is 40-90ns, which agrees with the performance of main memory on norvig (100ns).<\br>

Therefore the first step would appear to be the L1 cache, the second step the L2 cache, and the third step main memory. This is consistent with the buffer sizes; the L1 cache is 4kB*64 entries = 256kB, which is exactly where the first jump occurs. The L2 cache is 4MB*32 = 128MB, which is exactly where the second jumps begins.

#**============================The Model2 data:===========================**#
![](/graphs/model2_linear.png?raw=true "Optional Title")
![](/graphs/model2_log.png?raw=true "Optional Title")

#**==============================The Stepper data:============================**#
![](/graphs/adjusted_linear.png?raw=true "Optional Title")
![](/graphs/adjusted_log.png?raw=true "Optional Title")


