#!/bin/bash

# author: ph-u
# script: ctCol.sh
# desc: count colony number by pixels and given pixel-colony ratio
# in: bash ctCol.sh [full/path/of/photo_n_rangeCSV]
# out: full/path/of/photo_n_rangeCSV/00Colony.csv
# arg: 1
# date: 20201102

##### check input #####
[ -z $1 ] && grep "desc:\|in:" $0 | grep -v "grep" | cut -f 2 -d ":" && exit 1

##### orientate #####
cd $1
echo -e "image_title,num_of_colony" > 00Colony.csv

##### count #####
for i in `ls *_fil.csv`;do
	nAm=`echo -e "${i}" | awk -F "_fil" '{ print $1 }' | cut -f 1 -d "."`
	lIn=`grep -e "${nAm}," range.csv | cut -f 15 -d ","`
	if [[ ${lIn} =~ [0-9]+ ]];then
		tTT=`wc -l < ${i}`
		nUm=`echo -e "${tTT}/${lIn}"|bc` ## round down interger division
	else
		nUm="NA"
	fi
	echo -e "${nAm},${nUm}" >> 00Colony.csv
done

exit 0
