#include<stdio.h>
#include "../utils/Buffer/readFile.c"
#include "../utils/Buffer/twinBuffer.c"
#include "lexer.c"
#include "tokenize.c"


int main(){
    TwinBuffer TB = initializeTwinBuffer("_text.txt");
    int line = 0;
    LEXEME* lexm = simulateDFA(&TB);
    while(lexm != NULL){
        lexm = simulateDFA(&TB);
    }

    printErrors();

    fclose(TB.fp);
}
