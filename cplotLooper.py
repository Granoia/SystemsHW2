import sys, os, numpy, subprocess
#Determines the correct number of iterations and records data.?

def getIters(filename, size, output):
    iters = 1
    while True:
        if iters > 20:
            break
        for i in range(3):
            subprocess.call(['./update_location', str(size), str(iters), 'temp.txt'])
        with open('temp.txt','r') as f:
            x = float(f.readline())
            y = float(f.readline())
            z = float(f.readline())
        os.remove('temp.txt')
        if numpy.std([x,y,z,]) < x/100:
            with open(output,'a') as f:
                f.write(str(size) + ',' + str((x+y+z)/3) + ',' + str(iters) + '\n')
            break
        else:
            iters += 1
            

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("plotLooper  <output>")
        os.sys.exit(-1)
    output = sys.argv[1]
    
    for i in range(8,25):
        getIters('.\update_location', i, output)
