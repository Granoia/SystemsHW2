import sys, os

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("plotLooper <file> <output> ")
        os.sys.exit(-1)
    filename = sys.argv[1]
    output = sys.argv[2]
    for i in range(8,24):
        size = str(2**i)
        iter = str(2**24 / i)
        os.sys('filename ' + size + ' ' + iter + ' ' + output)
    os.sys.exit(0)
