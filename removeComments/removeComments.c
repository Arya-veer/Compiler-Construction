#include <stdio.h>

short removeComments(char* srcName, char* distName){
    // if(argc < 3) return 0;
    FILE* src = fopen(srcName,"r");
    FILE* dist = fopen(distName,"w");

    short shouldPrint = 1;

    short oldChar = getc(src);
    short newChar = getc(src);

    while(oldChar != EOF){
        if(oldChar == '*' && newChar == '*') {
            shouldPrint = !shouldPrint;
            oldChar = getc(src);
            newChar = getc(src);
        }
        if(shouldPrint) putc(oldChar, dist);
        oldChar = newChar;
        newChar = getc(src);
    }
    return 0;
}