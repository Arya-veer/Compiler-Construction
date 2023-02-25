#include <stdio.h>

int removeComments(char* src, char* dist){
    if(argc < 3) return 0;
    FILE* src = fopen(src,"r");
    FILE* dist = fopen(dist,"w");

    int shouldPrint = 1;

    int oldChar = getc(src);
    int newChar = getc(src);

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