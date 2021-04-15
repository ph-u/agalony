/*
author: ph-u
script: aglony.h
desc: func for data extraction & comparison
in: #include "agalony.h" in C-script
out: none
arg: 0
date: 20201120
*/

#ifndef _AGALONY_H_
#define _AGALONY_H_

#include <stdlib.h> // atoi
#include <string.h> // strlen
#include <unistd.h> // access()
#include <math.h> // sqrt

int inRange(int nUm, int mIn, int mAx){
    int tEst = 0;
    if(mIn > mAx){
        int mId = mIn;
        mIn = mAx;
        mAx = mId;
    }
    if(nUm < mIn || nUm > mAx){tEst++;}
    return tEst;
}

int inCircle(int x, int y, float h, float k, float r1, float r2){
    float rMin,rMax;
    if(r1<r2){ // check whether r1 is the smaller circle
        rMin = r1;
        rMax = r2;
    }else{
        rMin = r2;
        rMax = r1;
    }
    int rEs;
    float dIst = sqrt((x-h)*(x-h) + (y-k)*(y-k));

    if(dIst<rMin){rEs = 0;} // in small circle
    else if (dIst>rMax){rEs = 2;} // beyond large circle
    else{rEs = 1;} // in rim area
    return rEs; // 0: in; 1: rim; 2 = out
}

char* BaseName(char* FileName){
    const char s[2] = ".";
    char bNamLine[99];
    strcpy(bNamLine,FileName);
    char* bNamePt = bNamLine; // fit strtok_r syntax
    return strtok_r(bNamePt,".",&bNamePt);
}

FILE* fIle(char *paTh, char *fileName, char fnamReplace[], char posFix[], char RWE[2]){
    char pATh[999];strcpy(pATh,paTh); // every string has to be cp prevent namespace overlap
    char *nAm0;
    if(strcmp(fnamReplace,"")==0){
        char fNam[999];strcpy(fNam,fileName); // strcat need one pointer & one char[]
        nAm0 = strcat(pATh, fNam);
    }else{
        nAm0 = strcat(pATh,fnamReplace);
    }
    char *nAm1 = strcat(nAm0, posFix);
    if(strcmp(RWE,"r")==0 && access(nAm1, R_OK) == -1){
        printf("%s not readable/exist in path\n", nAm1);
        exit(1);
    }
    return fopen(nAm1, RWE);
}

#endif
