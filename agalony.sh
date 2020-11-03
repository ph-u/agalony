#!/bin/bash

# author: ph-u
# script: agalony.sh
# desc: Semi-automated colony count pipeline
# in: bash agalony.sh [py/r] [full/path/of/photos_n_rangeCSV] [clear?] [ncpu]
# out: individual photo csv files, ColonyCount.csv all in same folder
# arg: 4
# date: 20201102

##### check input #####
[ -z $1 ] && grep "desc:\|in:" $0 | grep -v "grep" | cut -f 2 -d ":" && exit 1
if [[ $1 != "py" ]] && [[ $1 != "r" ]];then echo -e "unknown first input: python3 / R ?";exit 1;fi

##### orientate #####
mAs=`dirname $0`
mAs=`echo -e "${mAs}/code/"`
cd $2 && tAr=$2
if [[ -z $4 ]];then nCPU=1;else nCPU=$4;fi
echo -e "count started, `date`"

##### img process #####
for i in `ls|grep -e "\.jpg\|\.JPG\|\.png\|\.PNG\|\.tif\|\.TIF"`;do
	bash ${mAs}imgPipe.sh $1 ${mAs} ${tAr} ${i} &
## process thread as instructed
	while [[ `ps aux|grep -e "imgPipe.sh"|grep -v "grep\|vi"|wc -l` -ge ${nCPU} ]];do
		sleep 1
	done
done

##### count colony #####
bash ${mAs}ctCol.sh ${tAr}

##### clear output if instructed #####
if [[ $3 == "clear" ]];then
	for i in `ls|grep -e "\.jpg\|\.JPG\|\.png\|\.PNG\|\.tif\|\.TIF"`;do
		fIle=`echo -e ${i}|cut -f 1 -d "."`
		rm `ls|grep -e "${fIle}.csv"`
	done
fi

echo -e "count finished, `date`\nThx for using agalony"

exit 0

