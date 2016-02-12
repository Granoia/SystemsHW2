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

def adjust(n):
	return 2**float(n)
	
def plot(filename):

	x = map(adjust,getColumn(filename,0))
	y = map(float,getColumn(filename,1))
	plt.plot(x, y)
	


if __name__ == '__main__':
	plt.xlabel("Particles")
	plt.ylabel("Average Speed / Particle (ns)")
	plt.ylim((0,400))
	plt.xlim((2**7,2**25))
	plt.xscale('symlog')
	plt.yscale('symlog')
	
	plot('python.csv')
	plot('double_O1.csv')
	plot('double_O3.csv')
	plot('float_O1.csv')
	plot('float_O3.csv')
	plot('x86.csv')
	
	plt.legend(['python','C-double, unoptimized','C-double, O3','C-float, unoptimized','C-float, O3'],loc='lower left')
	
	plt.show()