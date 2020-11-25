#!/bin/env python3

# author: ph-u
# script: img2csv.py
# desc: convert an image to csv
# in: python3 img2csv.py [full/path/img.ext] [H/P]
# out: a csv version of the image
# arg: 2
# date: 20201025
##### change log #####
# 20201123: expand functionality - horizontal & portrait photos
#####################

"""convert an image to csv"""
__appname__="img2csv.py"
__author__="ph-u"
__version__="0.0.1"
__license__="None"

##### check #####
import sys, os, csv
fIle = sys.argv[1]
if(len(sys.argv)!=3): sys.exit("only two arguments")
if os.path.exists(fIle)==False: sys.exit(fIle + " does not exist in path " + os.getcwd() + "\nwrong full path?")

##### pkg #####
import matplotlib.image as mim

##### in #####
fIl = fIle.split(".")
del fIl[-1]
nAm = ".".join(fIl) + ".csv"
iMg = mim.imread(fIle)

##### axis identification #####
axis1 = list(range(len(iMg),0,-1))
if sys.argv[2] == 'H':
    axis2 = list(range(1,len(iMg[0])+1))
else:
    axis2 = list(range(len(iMg[0]),0,-1))

##### out #####
if os.path.exists(nAm): os.remove(nAm)
with open(nAm,'w', newline='\n') as outFile:
    dAta = csv.writer(outFile, delimiter=',')
    dAta.writerow(["y", "x", "R", "G", "B"])
    x = y = 0
    while y < len(axis1):
        if sys.argv[2] == 'H':
            XY = [axis1[y], axis2[x]]
        else:
            XY = [axis2[x], axis1[y]]
        dAta.writerow([XY[0], XY[1], iMg[y][x][0], iMg[y][x][1], iMg[y][x][2]])
        x += 1
        if x == len(axis2):
            x = 0
            y += 1

sys.exit(fIle + " -> " + nAm)
