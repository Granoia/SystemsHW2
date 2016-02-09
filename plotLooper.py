import sys, os

for i in range(8,24):
    size = str(2**i)
    iter = str(1)
    os.system('update_locations.py ' + size + ' ' + iter)
    print("HAHAHA")