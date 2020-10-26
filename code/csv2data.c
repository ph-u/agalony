/*
author: ph-u
script: csv2data.c
desc: supervised filter on csv RGB data
in: gcc csv2data.c -o p_c2d && ./p_c2d [data.csv] [ranges.csv]
out: [data_f.csv]
arg: 7
date: 20201025
*/

#include <stdio.h>
#include <stdlib.h>

// primers
int countlines(char *fileIN);

// main
int main(int argc, char *argv[]){
    if(argc!=2){
        printf("2 arguments needed\n")
        exit(EXIT_FAILURE); //https://stackoverflow.com/questions/20210718/how-to-exit-a-program-with-mixed-c-c-cleanly
    }
    FILE *fP = fopen(argv[1],"r");
    
}
int csvLines=countlines(argv[1])

// self-functions
int countlines(char *fileIN){
    return wcL;
}
