#include<stdio.h>
#include "../utils/Buffer/readFile.c"
#include "../utils/Buffer/twinBuffer.c"
#include "lexer.c"
#include "tokenize.c"


int main(){
    TwinBuffer TB = initializeTwinBuffer("_text.txt");

    simulateDFA(&TB);

    fclose(TB.fp);
}
