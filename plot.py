import csv
import sys
import StringIO
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def getColumn(filename, column):
    results = csv.reader(open(filename), delimiter=",")
    return [result[column] for result in results]
    
def getHeader(filename):
    header = open(filename, 'r')
    return header.readline()

def normalize(i):
        return i - 10
    
def plot(filename):
    x = map(float,getColumn(filename,0))
    x = map(normalize,x)
    y = map(float,getColumn(filename,2))
    length = len(x)
    colors = ['red', 'green', 'blue']
    plt.figure(getHeader(filename))
    plt.title('linear scale')
    plt.xlabel("Array Size (kB)")
    plt.ylabel("Speed / Value (ns)")
    plt.ylim((min(y)*1.2,max(y)*1.2))
    plt.xlim((-1,20))
    plt.xticks(range(0,20,2), [r"$2^{ " + str(i) + "}$" for i in range(0,20,2)])
    ticks = [0,1,2,3,4,5,6,7,8]
    plt.yticks(ticks, map(str,ticks))
    plt.scatter(x, y)


if __name__ == '__main__':
    filename = sys.argv[1]
    plot(filename)
    plt.show(block=False)
    scale = raw_input("lin to save linear; log to save logarithmic\n")
    if scale == 'log':
        plt.title('log scale')
        plt.yscale('log')
        plt.ylim((0,8))
        plt.yticks([.01,.02,.04,.08,.16,.32,.64,1.2,2,4,8])
        plt.savefig('new.png')
    elif scale == 'lin':
        plt.savefig('new.png')
    plt.close()
    sys.exit(0)