#!/bin/env Rscript

# author: ph-u
# script: img2csv.R
# desc: convert an image to csv
# in: Rscript img2csv.R [full/path/img.ext]
# out: a csv version of the image
# arg: 1
# date: 20201103
##### change log #####
#####################

aRg = (commandArgs(T))
suppressWarnings(suppressMessages(library(imager)))

##### in #####
rAw = load.image(aRg)

##### img convert #####
dIm = dim(rAw)
dAta = data.frame(
    y = rep(dIm[1]:1,dIm[2]),
    x = rep(dIm[2]:1,each=dIm[1]),
    R = as.vector(round(rAw[,,1]*255)),
    G = as.vector(round(rAw[,,2]*255)),
    B = as.vector(round(rAw[,,3]*255))
)
#plot(dAta[,2],dAta[,1],col=rgb(dAta[,3],dAta[,4],dAta[,5]),pch=16,cex=.1)

##### out #####
oUt = as.character(read.table(text=aRg, sep=".")[1,])
oUt = paste0(c(oUt[-length(oUt)],"csv"), collapse=".")
write.table(dAta, oUt, sep=",",quote=F, row.names=F)

cat(paste(aRg,"->",oUt,"\n"))
