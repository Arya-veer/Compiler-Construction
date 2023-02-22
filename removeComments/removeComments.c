#include <stdio.h>

int main(int argc, char* argv[]){
    if(argc < 3) return 0;
    FILE* src = fopen(argv[1],"r");
    FILE* dist = fopen(argv[2],"w");

    int shouldPrint = 1;

    int oldChar = getc(src);
    int newChar = getc(src);

    while(newChar != EOF){
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