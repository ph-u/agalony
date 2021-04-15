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

    size_t rangeBuf = 25; // rgb: [RGB,]*6+EOL (last , -> \0)
    char *rangeLine = (char*) malloc(rangeBuf*sizeof(int));
    size_t rgbBuf = 24; // same as groupPX.c
    char *rgbLine = (char*) malloc(rgbBuf*sizeof(int));

    // correct names & path -> open I/O files
    FILE *rangeFile = fIle(pAth, BaseName(inFile), "", "_rgb.csv", "r");
    FILE *dataFile = fIle(pAth, BaseName(inFile), "", "_agar.csv", "r");
    FILE *filterFile = fIle(pAth, BaseName(inFile), "", "_fil.csv", "w");

    fgets(rangeLine, rangeBuf, rangeFile);
    int minR = dAta(rangeLine, 1);
    int maxR = dAta(rangeLine, 2);
    int minG = dAta(rangeLine, 3);
    int maxG = dAta(rangeLine, 4);
    int minB = dAta(rangeLine, 5);
    int maxB = dAta(rangeLine, 6);
    free(rangeLine); // only need to free true mem; size_t is not a true mem
    fclose(rangeFile);

    int lIne = 0; // token to indicate header
    int mAtch; // token to show rgb match
    while(fgets(rgbLine, rgbBuf, dataFile)){
        mAtch = inRange(dAta(rgbLine,3),minR,maxR)+inRange(dAta(rgbLine,4),minG,maxG)+inRange(dAta(rgbLine,5),minB,maxB);
        if(mAtch==0 || lIne==0){
            fputs(rgbLine, filterFile);
        }
        if(lIne==0){lIne++;} // remove token
    }

    fclose(dataFile);
    fclose(filterFile);
}
