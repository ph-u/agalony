#!/bin/bash

# author: ph-u
# script: imgPipe.sh
# desc: single photo conversion and pixel filter
# in: bash imgPipe.sh [py/r] [self/path] [path/to/img] [img.ext]
# out: pixel-filtered csv in same folder as image
# arg: 2
# date: 20201102

##### no input #####
[ -z $1 ] && grep "desc:\|in:" $0 | grep -v "grep" | cut -f 2 -d ":" && exit 1

##### orientate #####
mAs=$2 && cd ${mAs}
pAh=$3
iMg=$4
oUt=`echo -e "${iMg}"|cut -f 1 -d "."`

##### process #####
if [[ $1 == "py" ]];then
	python3 img2csv.py ${pAh}/${iMg}
else
	Rscript img2csv.R ${pAh}/${iMg}
fi
./c2d ${pAh}/${oUt}.csv ${pAh}/range.csv ${pAh}/00F_${oUt}.csv

exit 0
