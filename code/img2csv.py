#!/bin/env python3

# author: ph-u
# script: img2csv.py
# desc: convert an image to csv
# in: python3 img2csv.py [full/path/img.ext]
# out: a csv version of the image
# arg: 1
# date: 20201025
##### change log #####
#####################

"""convert an image to csv"""
__appname__="img2csv.py"
__author__="ph-u"
__version__="0.0.1"
__license__="None"
## source: https://stackoverflow.com/questions/54570134/convert-image-files-to-a-csv-file

##### check #####
import sys, os
fIle = sys.argv[1]
if(len(sys.argv)!=2): sys.exit("only one arg is allowed")
if os.path.exists(fIle)==False: sys.exit(fIle + " does not exist in path " + os.getcwd() + "\nwrong full path?")

##### pkg #####
from PIL import Image as pI ## pkg Pillow
from numpy import array, moveaxis, indices, dstack
from pandas import DataFrame as dF

##### in #####
fIl = fIle.split(".")
del fIl[-1]
nAm = ".".join(fIl) + ".csv"
iMg = pI.open(fIle)

##### img convert #####
pXl = iMg.convert("RGB")
rGb = array(pXl.getdata()).reshape(iMg.size + (3,))
iDx = moveaxis(indices(iMg.size), 0, 2)
aLl = dstack((iDx, rGb)).reshape((-1, 5))
dAta = dF(aLl, columns=["y", "x", "R", "G", "B"])

##### out #####
if os.path.exists(nAm): os.remove(nAm)
dAta.to_csv(nAm, index=False)

sys.exit(fIle + " -> " + nAm)
