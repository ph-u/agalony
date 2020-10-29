#include <stdio.h> // r/w lines, print msg
#include <stdlib.h> // malloc, exit, atoi
#include <string.h> // str length
#include <unistd.h> // check file existence
int main(int argc, char *argv[]){
    int i;
    char* inFile1 = argv[1]; // data file
    size_t lBuf = 4*2+3*3+5+2; // max pixel y, x + max RGB + delimiters/"\n" + a few extra bytes
    char *LineBuf = (char*) malloc(lBuf*sizeof(int)); // mem for a int(4)/char(1) line
    FILE *inFile1f = fopen(inFile1, "r");
    i=0;
    while (fgets(LineBuf, lBuf, inFile1f)){
        i++;
        printf("%d - %s", i,LineBuf);
    }
    fclose(inFile1f);
    return 0;
}