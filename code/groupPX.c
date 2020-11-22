/*
author: ph-u
script: groupPX.c
desc: group pixels into three groups: in, rim, out
in: gcc groupPX.c -o p_gPx && ./p_gPx [full/path] [in.csv]
out: [full/path/out_agar.csv] [full/path/out_rgb.csv]
arg: 2
date: 20201120
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "agalony.h"

int main(int argc, char *argv[]){
    char *pAth = argv[1];
    char *inFile = argv[2];
    char *rEf;
    int lIne = 0, nEed, pxLoc, coLoc1, coLoc2, i; // tokens
    int minR=255/2,minG=255/2,minB=255/2,maxR=255/2,maxG=255/2,maxB=255/2;

    size_t rangeBuf = 65+35; // 65 char for XY coordinates + 35 char for img name
    char *rangeLine = (char*) malloc(rangeBuf*sizeof(int)); // mem ratio of int:char = 4:1
    size_t rgbBuf = 28; // x,y (5 char each) + R,G,B (4 char each) + few buffer (8 char)
    char *rgbLine = (char*) malloc(rgbBuf*sizeof(int));

    // correct names & path -> open read files
    char ffcp3[999];
    strcpy(ffcp3,pAth);
    char* ff = strcat(ffcp3,BaseName(inFile)); // strcat(pAth,BaseName(inFile)); will change variable "pAth"

    char ffcp4[999];
    strcpy(ffcp4,ff);
    char daTa[] = ".csv";
    char* dT = strcat(ffcp4,daTa);
    if(access(dT, R_OK) == -1){printf("data file not readable/exist in path\n");exit(1);}
    FILE* dataCSV = fopen(dT, "r");

    char ffcp0[999];
    strcpy(ffcp0,pAth);
    char rAnge[] = "range.csv";
    char* rG = strcat(ffcp0,rAnge);
    if(access(rG, R_OK) == -1){printf("range.csv not readable/exist in path\n");exit(1);}
    FILE* rangeDt = fopen(rG, "r");

    // check & get coordination data from range.csv
    while (fgets(rangeLine, rangeBuf, rangeDt)){
        rEf = strtok_r(rangeLine,",",&rangeLine);
        if(strcmp(rEf, BaseName(inFile))==0){break;}else{rEf="n";}
    }
    if(strcmp(rEf,"n")==0){
        printf("range file does not contain necessary info for %s\n",BaseName(inFile));
        exit(1);
    }

    // correct names & path -> open write files
    char ffcp1[999];
    strcpy(ffcp1,ff);
    char aGar[] = "_agar.csv";
    char* aG = strcat(ffcp1,aGar);
    FILE* agarPxl = fopen(aG, "w");

    char ffcp2[999];
    strcpy(ffcp2,ff);
    char rGb[] = "_rgb.csv";
    char* pX = strcat(ffcp2,rGb);
    FILE* rgbRang = fopen(pX, "w");

    // plate radius
    float rimR1 = abs(dAta(rangeLine,2)-dAta(rangeLine,4))/2;
    float rimR2 = abs(dAta(rangeLine,3)-dAta(rangeLine,5))/2;
    // plate centre
    float rimX = (dAta(rangeLine,2)+dAta(rangeLine,4))/2;
    float rimY = (dAta(rangeLine,3)+dAta(rangeLine,5))/2;
    // colony radii
    float colR11 = abs(dAta(rangeLine,6)-dAta(rangeLine,8))/2;
    float colR12 = abs(dAta(rangeLine,7)-dAta(rangeLine,9))/2;
    float colR21 = abs(dAta(rangeLine,10)-dAta(rangeLine,12))/2;
    float colR22 = abs(dAta(rangeLine,11)-dAta(rangeLine,13))/2;
    // colony centres
    float col1X = (dAta(rangeLine,6)+dAta(rangeLine,8))/2;
    float col1Y = (dAta(rangeLine,7)+dAta(rangeLine,9))/2;
    float col2X = (dAta(rangeLine,10)+dAta(rangeLine,12))/2;
    float col2Y = (dAta(rangeLine,11)+dAta(rangeLine,13))/2;
    // oval shapes: flat [0] / slim [1]
    int rimShp=0, c1Shp=0, c2Shp=0;
    if(rimR1 < rimR2){rimShp++;}
    if(colR11 < colR12){c1Shp++;}
    if(colR21 < colR22){c2Shp++;}

    // pixel filtering & segragation
    // [LIMITATION: sharp boundary oval colonies]
    int tEstLine = 0;
    while (fgets(rgbLine, rgbBuf, dataCSV)){
        nEed = 0; // set token value
        if(lIne==0){lIne++;}else{ // data header skip number checking

            // get tokens for boundaries: rim, colony_1, colony_2
            pxLoc = inCircle(dAta(rgbLine,2), dAta(rgbLine,1), rimX, rimY, rimR1, rimR2);
            coLoc1 = inCircle(dAta(rgbLine,2), dAta(rgbLine,1), col1X, col1Y, colR11, colR12);
            coLoc2 = inCircle(dAta(rgbLine,2), dAta(rgbLine,1), col2X, col2Y, colR21, colR22);

            if(pxLoc == 2){nEed++;} // no px outside rim
            if(pxLoc == 1){
                if(rimShp==0){ // flat oval
                    if(dAta(rgbLine,1) > rimY+rimR2 || dAta(rgbLine,1) < rimY-rimR2){nEed++;} // no too high/low
                }else{ // circle || slim oval
                    if(dAta(rgbLine,2) > rimX+rimR1 || dAta(rgbLine,2) < rimX-rimR1){nEed++;} // no too right/left
                }
            }
            if(nEed==0){ // check the need of extracting RGB info
                if(coLoc1 == 0 || coLoc2 == 0) {lIne=7;} // yes in sample area

                if(coLoc1 == 1){
                    if(c1Shp==0){ // flat oval
                        if(dAta(rgbLine,1) < col1Y+colR12 && dAta(rgbLine,1) > col1Y-colR12){lIne=7;} // yes within Y-limits
                    }else{ // circle || slim oval
                        if(dAta(rgbLine,2) < col1X+colR11 && dAta(rgbLine,2) > col1X-colR11){lIne=7;} // yes within X-limits
                    }
                }
                
                if(coLoc2 == 1){
                    if(c2Shp==0){ // flat oval
                        if(dAta(rgbLine,1) < col2Y+colR22 && dAta(rgbLine,1) > col2Y-colR22){lIne=7;} // yes within Y-limits
                    }else{ // circle || slim oval
                        if(dAta(rgbLine,2) < col2X+colR21 && dAta(rgbLine,2) > col2X-colR21){lIne=7;} // yes within X-limits
                    }
                }

            }
        }

        if(nEed==0){
            fputs(rgbLine,agarPxl);
            if(lIne==7){
                if(dAta(rgbLine,3) < minR){minR = dAta(rgbLine,3);}else
                if(dAta(rgbLine,3) > maxR){maxR = dAta(rgbLine,3);}
                if(dAta(rgbLine,4) < minG){minG = dAta(rgbLine,4);}else
                if(dAta(rgbLine,4) > maxG){maxG = dAta(rgbLine,4);}
                if(dAta(rgbLine,5) < minB){minB = dAta(rgbLine,5);}else
                if(dAta(rgbLine,5) > maxB){maxB = dAta(rgbLine,5);}
                lIne = 1; // reset token
            }
        }
    }
    fprintf(rgbRang, "%d,%d,%d,%d,%d,%d\n",minR,maxR,minG,maxG,minB,maxB); // https://www.cplusplus.com/reference/cstdio/fprintf/

    // ending
    fclose(dataCSV);
    fclose(rangeDt);
    fclose(agarPxl);
    fclose(rgbRang);
}