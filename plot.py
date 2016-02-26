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
    
    
def plot(filename):
    x = map(float,getColumn(filename,0))
    y = map(float,getColumn(filename,2))
    length = len(x)
    colors = ['red', 'green', 'blue']
    plt.figure(getHeader(filename))
    plt.title('log scale')
    plt.xlabel("Array Size")
    plt.ylabel("Speed / Value (ns)")
    plt.ylim((min(y)*1.2,max(y)*1.2))
    plt.xlim((6,30))
    plt.xticks(range(8,30,2), [r"$2^{ " + str(i) + "}$" for i in range(8,30,2)])
    plt.yscale('symlog')
    ticks = [.1,1,2,4,6,8,10,20,40,80,100]
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