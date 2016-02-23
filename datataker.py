import sys, os, numpy, subprocess
#Runs <sampleSize> number of trials per <size> from 2^8 to 2^24 (adjusting <iters> accordingly) and records the median value of each set of trials.
#<sampleSize> is set to 10 by default, adjusting __main__ is required to change that
#compile the thing being timed so that the executable name is fetch_values

def getIters(filename, size, output, sampleSize=10):
    currSize = 8
    while currSize <= 24:
        iters = 30 - currSize
        for i in range(sampleSize):
            subprocess.call(['./fetch_values', str(size), str(iters)])
        ls = []
        with open('temp.txt','r') as f:
            for i in range(sampleSize):
                x = float(f.readline())
                ls.append(x)
        ls.sort()
        median = ls[sampleSize // 2]
        os.remove('temp.txt')
        with open(output,'a') as f:
            f.write(str(currSize) + ',' + str(median) + ',' + str(iters) + '\n')
        currSize += 1
            

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("datataker  <output>")
        os.sys.exit(-1)
    output = sys.argv[1]
    getIters('./fetch_values', 8, output)
