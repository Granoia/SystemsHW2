import sys, os, numpy, subprocess
#Determines the correct number of iterations and records data.?

def getIters(filename, size, output):
    currSize = 8
    while currSize <= 24:
        iters = 30 - currSize
        for i in range(5):
            subprocess.call(['./update_location', str(size), str(iters)])
        ls = []
        with open('temp.txt','r') as f:
            x = float(f.readline())
            y = float(f.readline())
            z = float(f.readline())
            w = float(f.readline())
            u = float(f.readline())
        ls = []
        ls.append(x)
        ls.append(y)
        ls.append(z)
        ls.append(w)
        ls.append(u)
        ls.sort
        median = ls[2]
        os.remove('temp.txt')
        with open(output,'a') as f:
            f.write(str(currSize) + ',' + str(median) + ',' + str(iters) + '\n')
        currSize += 1
            

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("plotLooper  <output>")
        os.sys.exit(-1)
    output = sys.argv[1]
    getIters('./update_location', 8, output)
