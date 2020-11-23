#!/bin/bash

# author: ph-u
# script: build.sh
# desc: Build agalony pipeline
# in: bash build.sh
# out: set-up agalony
# arg: 0
# date: 20201103

##### orientate #####
mAs=`dirname $0` && cd ${mAs}
mAs=`echo -e "${mAs}/code/"`

##### process #####
[[ `which python|wc -l` -lt 1 ]] && [[ `which R|wc -l` -lt 1 ]] && echo -e "need python3 or R" ## python3 / R exist?

if [[ `which python|wc -l` -ge 1 ]];then
	pip3 2> tEst.txt 1> tEst.txt ## pip3 exist?
	if [[ `wc -l < tEst.txt` -gt 1 ]]
	then pip3 install -r requirements.txt ## install python3 packages
	else echo -e "need pip package installer for python3"
	fi
	rm tEst.txt
fi

if [[ `which R|wc -l` -ge 1 ]];then
	Rscript -e "if(suppressMessages(suppressWarnings(require(imager)))==F){install.packages('imager', dependencies=T, repos='https://cloud.r-project.org/')}"
fi

cd ${mAs}
gcc groupPX.c -o p_gPx
gcc filterPX.c -o p_fPx

echo -e "agalony successfully-built\n\n       Thank you for taking a step towards reproducible projects\n\nIf you encounter pip3 installation error [No module named 'pkg_resources'], please manual install the needed 3 pkgs listed in requirements.txt using pip3"
exit 0

