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
    y = map(float,getColumn(filename,1))
    length = len(x)
    colors = ['red', 'green', 'blue']

    plt.figure(getHeader(filename))
    plt.title('linear scale')
    plt.xlabel("Array Size")
    plt.ylabel("Speed / Value (ns)")
    plt.ylim((0,.2))
    plt.xlim((6,25))
    plt.xticks(range(8,25,2), [r"$2^{ " + str(i) + "}$" for i in range(8,25,2)])
    plt.scatter(x, y)


if __name__ == '__main__':
    filename = sys.argv[1]
    plot(filename)
    plt.show(block=False)
    scale = raw_input("lin to save linear; log to save logarithmic\n")
    if scale == 'log':
        plt.title('log scale')
        plt.yscale('log')
        plt.ylim((0,.2))
        plt.yticks([.02,.04,.05,.06,.07,.08,.1,.2], ['.02','.04','.05','.06','.07','.08','.1','.2'])
    plt.savefig('new.png')
    plt.close()
    