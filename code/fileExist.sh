#!/bin/bash

# author: ph-u
# script: fileExist.sh
# desc: check and delete existing intermediate files
# in: bash fileExist.sh [full/path]
# out: delete all remaining intermediate files
# arg: 1
# date: 20201120

cd $1
for i in `ls *.csv|grep -v "range"`;do
    rm ${i}&
done

exit