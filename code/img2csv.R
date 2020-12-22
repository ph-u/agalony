#!/bin/env Rscript

# author: ph-u
# script: img2csv.R
# desc: convert an image to csv
# in: Rscript img2csv.R [full/path/img.ext] [H/P]
# out: a csv version of the image
# arg: 2
# date: 20201103
# ver: 4.0.1
##### change log #####
# 20201123: expand functionality - horizontal & portrait photos
#####################

aRg = (commandArgs(T))
suppressWarnings(suppressMessages(library(imager)))

##### in #####
rAw = load.image(aRg[1])

##### img convert #####
dIm = dim(rAw)
if(aRg[2]=="H"){
    y_axis = rep(dIm[2]:1,each=dIm[1])
    x_axis = rep(1:dIm[1],dIm[2])
}else{
    y_axis = rep(dIm[1]:1,dIm[2])
    x_axis = rep(dIm[2]:1,each=dIm[1])
}
dAta = data.frame(
    y = y_axis,
    x = x_axis,
    R = as.vector(round(rAw[,,1]*255)),
    G = as.vector(round(rAw[,,2]*255)),
    B = as.vector(round(rAw[,,3]*255))
)

##### out #####
oUt = as.character(read.table(text=aRg[1], sep=".")[1,])
oUt = paste0(c(oUt[-length(oUt)],"csv"), collapse=".")
write.table(dAta, oUt, sep=",",quote=F, row.names=F)

cat(paste(aRg[1],"->",oUt,"\n"))
