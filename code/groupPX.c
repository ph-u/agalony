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
#include <math.h>
#include "agalony.h" // it included other necessary libs for this script

int main(int argc, char *argv[]){
    char *pAth = argv[1], *inFile = argv[2], *rEf;
    const char s[2]=",";
    int lIne = 0, nEed, i; // tokens

    size_t rangeBuf = 65+35; // 65 char for XY coordinates + 35 char for img name
    char *rangeLine = (char*) malloc(rangeBuf*sizeof(int)); // mem ratio of int:char = 4:1
    size_t rgbBuf = 24; // x,y (5 char each) + R,G,B (4 char each) + EOL (2 char)
    char *rgbLine = (char*) malloc(rgbBuf*sizeof(int));

    // correct names & path -> open read files
    FILE* dataCSV = fIle(pAth, BaseName(inFile), "", ".csv", "r");
    FILE* rangeDt = fIle(pAth, rEf, "range", ".csv", "r"); // rEf is a blank placeholder pointer here

    // check for coordination data line in range.csv
    while (fgets(rangeLine, rangeBuf, rangeDt)){
        rEf = strtok_r(rangeLine,",",&rangeLine);
        if(strcmp(rEf, BaseName(inFile))==0){break;}else{rEf="n";}
    }
    if(strcmp(rEf,"n")==0){
        printf("range file does not contain necessary info for %s\n",BaseName(inFile));
        exit(1);
    }

    // get range.csv data
    int rX1,rX2,rY1,rY2, c1X1,c1X2,c1Y1,c1Y2, c2X1,c2X2,c2Y1,c2Y2;
    rEf = strtok(rangeLine,s);
    i=0;while(rEf!=NULL){
	    if(i==0){rX1=atoi(rEf);}else if(i==1){rY1=atoi(rEf);}else if(i==2){rX2=atoi(rEf);}else if(i==3){rY2=atoi(rEf);}else if(i==4){c1X1=atoi(rEf);}else if(i==5){c1Y1=atoi(rEf);}else if(i==6){c1X2=atoi(rEf);}else if(i==7){c1Y2=atoi(rEf);}else if(i==8){c2X1=atoi(rEf);}else if(i==9){c2Y1=atoi(rEf);}else if(i==10){c2X2=atoi(rEf);}else if(i==11){c2Y2=atoi(rEf);}
	    rEf = strtok(NULL,s);i++;
    }

    // correct names & path -> open write files
    FILE* agarPxl = fIle(pAth, BaseName(inFile), "", "_agar.csv", "w");
    FILE* rgbRang = fIle(pAth, BaseName(inFile), "", "_rgb.csv", "w");

    float // calculate area attributes
    rimR1 = abs(rX1-rX2)/2, rimR2 = abs(rY1-rY2)/2, colR11 = abs(c1X1-c1X2)/2, colR12 = abs(c1Y1-c1Y2)/2, colR21 = abs(c2X1-c2X2)/2, colR22 = abs(c2Y1-c2Y2)/2, // radius
    rimX = (rX1+rX2)/2, rimY = (rY1+rY2)/2, col1X = (c1X1+c1X2)/2, col1Y = (c1Y1+c1Y2)/2, col2X = (c2X1+c2X2)/2, col2Y = (c2Y1+c2Y2)/2; // centre
    // oval shapes: flat [0] / slim [1]
    int rimShp=0, c1Shp=0, c2Shp=0;
    if(rimR1 < rimR2){rimShp++;}
    if(colR11 < colR12){c1Shp++;}
    if(colR21 < colR22){c2Shp++;}

    // pixel filtering & segragation
    // [LIMITATION: sharp boundary oval colonies]
    int minR,minG,minB, maxR=0,maxG=0,maxB=0, dX,dY,dR,dG,dB; // RGB tokens & data
    while (fgets(rgbLine, rgbBuf, dataCSV)){
        nEed = 0; // set token value
        if(lIne==0){lIne++;}else{ // data header skip number checking

            // get rgbLine data
	    char cPy[rgbBuf];
	    strcpy(cPy,rgbLine);
	    rEf = strtok(cPy,s);
	    i=0;while(rEf!=NULL){
		    if(i==0){dY=atoi(rEf);}else if(i==1){dX=atoi(rEf);}else if(i==2){dR=atoi(rEf);}else if(i==3){dG=atoi(rEf);}else{dB=atoi(rEf);}
		    rEf = strtok(NULL,s);i++;
	    }
	    int // get tokens for boundaries: rim, colony_1, colony_2
            pxLoc = inCircle(dX, dY, rimX, rimY, rimR1, rimR2),
	    coLoc1 = inCircle(dX, dY, col1X, col1Y, colR11, colR12),
            coLoc2 = inCircle(dX, dY, col2X, col2Y, colR21, colR22);

            if(pxLoc == 2){nEed++;}else // no px outside rim
            if(pxLoc == 1){
                if(rimShp==0){ // flat oval
                    if(dY > rimY+rimR2 || dY < rimY-rimR2){nEed++;} // no too high/low
                }else{ // circle || slim oval
                    if(dX > rimX+rimR1 || dX < rimX-rimR1){nEed++;} // no too right/left
                }
            }
            if(nEed==0){ // check the need of extracting RGB info
                if(coLoc1 == 0 || coLoc2 == 0) {lIne=7;} // yes in restricted sample area
            }
        }

        if(nEed==0){
            fputs(rgbLine,agarPxl);
            if(lIne==7){
		if(maxR==0){minR = maxR = dR;}else if(dR < minR){minR = dR;}else if(dR > maxR){maxR = dR;}
		if(maxG==0){minG = maxG = dG;}else if(dG < minG){minG = dG;}else if(dG > maxG){maxG = dG;}
		if(maxB==0){minB = maxB = dB;}else if(dB < minB){minB = dB;}else if(dB > maxB){maxB = dB;}
                lIne = 1; // reset token
            }
        }
    }
    fprintf(rgbRang, "%d,%d,%d,%d,%d,%d\n",minR,maxR,minG,maxG,minB,maxB); // https://www.cplusplus.com/reference/cstdio/fprintf/

    fclose(dataCSV);
    fclose(rangeDt);
    fclose(agarPxl);
    fclose(rgbRang);
}
