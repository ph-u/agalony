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
#include <stdlib.h> // malloc, exit, atoi
#include <string.h> // str length
#include <unistd.h> // check file existence

// primers
int inRange(int nUm, int mIn, int mAx);
int dAta(char Line[], int cOlumn);

// main
int main(int argc, char *argv[]){
    int aRg = 3; // num of input arg
    int putNot = 0;
    int i; // loop index
    int ctCol; // count Columns
    int rgb; // compare rgb using inRange()

    // files
    char* inFile1 = argv[1]; // data file
    char* inFile2 = argv[2]; // supervised RGB file
    char* outFile = argv[3]; // filtered data file

    // text in data
    size_t lBuf = 4*2+3*3+5+2; // max pixel y, x + max RGB + delimiters/"\n" + a few extra bytes
    char *LineBuf = (char*) malloc(lBuf*sizeof(int)); // mem for a int(4)/char(1) line

    // text for RGB range
    size_t lBuf2 = 49+3*7+2; // [img name] + 6 cols of RGB ranges & 1 col on px:count ratio + a few extra bytes
    char *LineBuf2 = (char*) malloc(lBuf2*sizeof(int));

    // text variables
    const char s[2] = ",";
    char *tAke;
    char cpSrc[lBuf];
    char *tAke2;
    char cpBaseName[999];

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

    // get basename of input data file (inFile1)
    strcpy(cpBaseName,inFile1);
    char *rEst = cpBaseName; // fit strtok_r syntax
    tAke = strtok_r(rEst,".",&rEst);
    ctCol = 1;
    for(i=0;i<strlen(tAke);i++){
        if(strncmp(&tAke[i],"/",1)==0){ctCol++;}
    }
    for(i=0;i<ctCol-1;i++){
        tAke2 = strtok_r(tAke,"/",&tAke);
    }

    // find row containing supervised RGB ranges
    while (fgets(LineBuf2, lBuf2, inFile2f)){
        ctCol = 1;
        for(i=0;i<strlen(LineBuf2);i++){ // check col num
            if(LineBuf2[i]==','){ctCol++;}
        }
        if(ctCol<7){ // test RGB range file structure (optional px, so functional input either 7 or 8 columns)
            printf("ERROR: csv indicating RGB ranges wrong format (see below)\n\nimage,R1,G1,B1,R2,G2,B2,px\n\nRGB columns are COMPULSORY min/max value of pixels of interest (select the lightest & darkest coloured pixel for reference)\npx is the OPTIONAL column indicating how many pixels correspond to one counting unit (or colony on agar plate in the source image)\n");
            exit(1);
        }
        tAke = strtok_r(LineBuf2,s,&LineBuf2); // https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/
        if(strcmp(tAke,tAke2)==0){break;}else{tAke="n";}
    }
    if(strcmp(tAke,"n")==0){printf("range file does not contain necessary info\n");exit(1);}
    
    // data processing
    i=0;
    while (fgets(LineBuf, lBuf, inFile1f)){
        i++;
        strcpy(cpSrc,LineBuf);
        tAke = strtok(cpSrc,s);
        tAke = strtok(NULL,s);
        rgb = inRange(dAta(LineBuf,3),dAta(LineBuf2,2),dAta(LineBuf2,5)) + inRange(dAta(LineBuf,4),dAta(LineBuf2,3),dAta(LineBuf2,6)) + inRange(dAta(LineBuf,5),dAta(LineBuf2,4),dAta(LineBuf2,7)); // R+G+B, ==0 if in range
        if(strcmp(tAke,"x")!=0 && rgb != 0){putNot = 1;}
        if(putNot==0){
            fputs(LineBuf,outFilef);
        }else{
            putNot = 0;
        }
    }

    // clean quit
    fclose(inFile1f);
    fclose(inFile2f);
    fclose(outFilef);
    printf("%s -> %s\n", tAke2,outFile);
    return 0;
}

// functions
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
    char rEs[] = "...";
    for(i=0;i<strlen(Line);i++){ // count column
        if(Line[i]==','){ctCol++;} // scan for the right column
        if(ctCol==cOlumn && i0>0){rEs[i1]=Line[i];i1++;} // replace rEs content char by char
        if(ctCol==cOlumn){i0=1;} // cancel pre-","
    }
    return atoi(rEs);
}
