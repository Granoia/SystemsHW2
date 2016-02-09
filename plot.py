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
    plt.xlabel("Particles")
    plt.ylabel("Speed / Particle")
    plt.ylim((0,2))
    plt.xlim((0,2**24))
    plt.xscale('symlog')
    plt.plot(x, y)
    plt.show()


if __name__ == '__main__':
    filename = sys.argv[1]
    plot(filename)
