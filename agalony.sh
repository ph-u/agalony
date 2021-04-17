#!/bin/bash

# author: ph-u
# script: agalony.sh
# desc: Semi-automated colony count pipeline - options {python3 = p, Rscript = r, clear intermediate files = c}
# in: bash agalony.sh [options] [full/path/of/photos_n_rangeCSV] [ncpu]
# out: individual photo csv files, ColonyCount.csv all in same folder
# arg: 3
# date: 20201102, 20210415

##### check input #####
[ -z $1 ] && grep "desc:\|in:" $0 | grep -v "grep" | cut -f 2 -d ":" && exit 1
oPtions=$1
if [[ ${oPtions} =~ [Pp] ]];then sC="py"
elif [[ ${oPtions} =~ [Rr] ]];then sC="r"
else echo -e "Do you want python3 (p) or Rscript (r)?";exit 1;fi

##### orientate #####
mAs=`dirname $0`
mAs=`echo -e "${mAs}/code/"`
tAr=$2
if [[ -z $3 ]];then nCPU=1;else nCPU=$3;fi
echo -e "count started, `date`"

##### clear past intermediate files #####
bash ${mAs}fileExist.sh ${tAr} 2> /dev/null
rm ${tAr}/00Colony.csv 2> /dev/null

##### img process #####
for i in `ls ${tAr}|grep -e "\.jpg\|\.JPG\|\.jpeg\|\.JPEG\|\.png\|\.PNG\|\.tif\|\.TIF"`;do
	bash ${mAs}imgPipe.sh ${sC} ${mAs} ${tAr} ${i} &
## process thread as instructed
	while [[ `ps aux|grep -e "imgPipe.sh"|grep -v "grep\|vi"|wc -l` -ge ${nCPU} ]];do
		sleep 1
	done
done

while [[ `ps aux|grep -e "imgPipe.sh"|grep -v "grep\|vi"|wc -l` -ge 1 ]];do
	sleep 1
done ## ensure all filters finish work

##### count colony #####
bash ${mAs}ctCol.sh ${tAr}

##### clear output if instructed #####
[[ ${oPtions} =~ [Cc] ]] && bash ${mAs}fileExist.sh ${tAr}
echo -e "count finished, `date`\nThx for using agalony"
exit 0
