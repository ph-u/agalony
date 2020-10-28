/*
author: ph-u
script: csv2data.c
desc: extract within range RGB data
in: gcc csv2data.c -o c2d && ./c2d [full/path/in.csv] [full/path/range.csv] [full/path/out.csv]
out: full/path/out.csv
arg: 3
date: 20201025 (dumped), 20201026
*/

#include <stdio.h> // r/w lines, print msg
#include <stdlib.h> // malloc, exit, free, atoi
#include <string.h> // str length
#include <unistd.h> // check file existence

// primers
int inRange(int nUm, int mIn, int mAx);
int dAta(char Line[], int cOlumn);

// main
int main(int argc, char *argv[]){
    int aRg = 3;
    char* inFile1 = argv[1];
    char* inFile2 = argv[2];
    char* outFile = argv[3];
    size_t lBuf = 4*2+3*3+5; // max pixel y, x + max RGB + delimiters/"\n"
    char *LineBuf = (char*) malloc(lBuf*sizeof(int)); // mem for a int(4)/char(1) line
    int putNot = 0;
    int headNot = 0;
    const char s[2] = ",";
    char *tAke; // determine string is file header ot not
    char cpSrc[4*2+3*3+5];

    // test inputs
    if(argc != aRg+1){printf("exactly %d arg required\n",aRg);exit(1);}
    if(access(inFile1, R_OK) == -1 || access(inFile2, R_OK) == -1){ // https://www.man7.org/linux/man-pages/man0/unistd.h.0p.html
        printf("input(s) not readable/exist in path\n");
        exit(1);
    }
    if(access(outFile, F_OK) != -1){remove(outFile);} // if outfile eist, delete the file

    // files
    FILE *inFile1f = fopen(inFile1, "r");
    FILE *inFile2f = fopen(inFile2, "r");
    FILE *outFilef = fopen(outFile, "w");

    // file processing
    while (fgets(LineBuf, lBuf, inFile1f) != NULL){
        strcpy(cpSrc,LineBuf);
        tAke = strtok(cpSrc,s);
        tAke = strtok(NULL,s);
        headNot = strcmp(tAke,"x");
        if(headNot!=0){
            printf("%d, %d: %s", headNot,dAta(LineBuf,3),LineBuf);
        }
        if(putNot == 0){
            fputs(LineBuf,outFilef);
        }
        putNot = 0;
    }

    // clean quit
    free(LineBuf);
    fclose(inFile1f);
    fclose(inFile2f);
    fclose(outFilef);
    printf("%s -> %s\n", inFile1,outFile);
    return 0;
}

// functions
int inRange(int nUm, int mIn, int mAx){
    int tEst = 0;
    if(nUm < mIn || nUm > mAx){tEst = 1;}
    return tEst;
}
int dAta(char Line[], int cOlumn){
    // can't use strtok because of mem error (https://stackoverflow.com/questions/2385697/why-is-strtok-causing-a-segmentation-fault)
    int i;
    int ctCol = 1;
    int i0 = 0;
    char rEs[] = "987";
    for(i=0;i<strlen(Line);i++){ // count column
        if(Line[i]==','){ctCol++;} // scan for the right column
        if(ctCol==cOlumn && i0>0){printf("%d,", i);}
        if(ctCol==cOlumn){i0=1;} // cancel pre-","
    }
    return atoi(rEs);
}
