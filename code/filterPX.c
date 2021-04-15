/*
author: ph-u
script: filterPX.c
desc: extract pixel within range RGB data
in: gcc filterPX.c -o p_fPx && ./p_fPx [full/path] [in.csv]
out: [full/path/out_fil.csv]
arg: 2
date: 20201122
*/

#include <stdio.h>
#include "agalony.h" // it included other necessary libs for this script

int main(int argc, char *argv[]){
    char *pAth = argv[1], *inFile = argv[2];
    const char s[2]=",";

    size_t rangeBuf = 25; // rgb: [RGB,]*6+EOL (last , -> \0)
    char *rangeLine = (char*) malloc(rangeBuf*sizeof(int));
    size_t rgbBuf = 24; // same as groupPX.c
    char *rgbLine = (char*) malloc(rgbBuf*sizeof(int));

    // correct names & path -> open I/O files
    FILE *rangeFile = fIle(pAth, BaseName(inFile), "", "_rgb.csv", "r");
    FILE *dataFile = fIle(pAth, BaseName(inFile), "", "_agar.csv", "r");
    FILE *filterFile = fIle(pAth, BaseName(inFile), "", "_fil.csv", "w");

    int minR,minG,minB,maxR,maxG,maxB, i=0;
    fgets(rangeLine, rangeBuf, rangeFile);
    char *rEf = strtok(rangeLine,s);
    while(rEf!=NULL){
	    if(i==0){minR=atoi(rEf);}else if(i==1){maxR=atoi(rEf);}else if(i==2){minG=atoi(rEf);}else if(i==3){maxG=atoi(rEf);}else if(i==4){minB=atoi(rEf);}else{maxB=atoi(rEf);}
	    rEf = strtok(NULL,s);i++;
    }
    free(rangeLine); // only need to free true mem; size_t is not a true mem
    fclose(rangeFile);

    int lIne=0,mAtch=0, // token
    dY,dX,dR,dG,dB; // data
    char cPy[rgbBuf];
    while(fgets(rgbLine, rgbBuf, dataFile)){
        if(lIne==0){lIne++;}else{ // remove token
	strcpy(cPy,rgbLine);
	rEf = strtok(cPy,s);
	i=0;while(rEf!=NULL){
		if(i==0){dY=atoi(rEf);}else if(i==1){dX=atoi(rEf);}else if(i==2){dR=atoi(rEf);}else if(i==3){dG=atoi(rEf);}else{dB=atoi(rEf);}
		rEf = strtok(NULL,s);i++;
	}
        mAtch = inRange(dR,minR,maxR)+inRange(dG,minG,maxG)+inRange(dB,minB,maxB);
	}
        if(mAtch==0){fputs(rgbLine, filterFile);}
	}

    fclose(dataFile);
    fclose(filterFile);
}
