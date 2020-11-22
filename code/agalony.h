/*
author: ph-u
script: aglony.h
desc: func for data extraction & comparison
in: #include <agalony.h> in C-script
out: none
arg: 0
date: 20201120
*/

#ifndef _AGALONY_H_
#define _AGALONY_H_

#include <stdlib.h> // atoi
#include <string.h> // strlen
#include <math.h> // sqrt

int inRange(int nUm, int mIn, int mAx){
    int tEst = 0;
    if(mIn > mAx){
        int mId = mIn;
        mIn = mAx;
        mAx = mId;
    }
    if(nUm < mIn || nUm > mAx){tEst = 1;}
    return tEst;
}

int dAta(char Line[], int cOlumn){
    // can't use strtok because of mem error (https://stackoverflow.com/questions/2385697/why-is-strtok-causing-a-segmentation-fault)
    int i; // loop index
    int ctCol = 1;
    int i0 = 0;
    int i1 = 0; // rEs char index
    char rEs[] = "....";
    for(i=0;i<strlen(Line);i++){ // count column
        if(Line[i]==','){ctCol++;} // scan for the right column
        if(cOlumn==1){i0=1;} // get start of line if 1st column is wanted
        if(ctCol==cOlumn && i0>0){rEs[i1]=Line[i];i1++;} // replace rEs content char by char
        if(ctCol==cOlumn){i0=1;} // cancel pre-","
    }
    return atoi(rEs);
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

#endif
