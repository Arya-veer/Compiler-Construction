#include <stdio.h>
#include "readFile.c"
#include "twinBuffer.c"

int main(){
    // initiate twinBuffer
    TwinBuffer TB = initializeTwinBuffer("_text.txt");

    // populate twinBuffer
    populateTwinBuffer(&TB);

    // getCharacterAtForward x3

    // incrementForward, decrementForward
    char zero = getCharacterAtForward(&TB);
    incrementForward(&TB);
    char one = getCharacterAtForward(&TB);
    incrementForward(&TB);
    char two = getCharacterAtForward(&TB);
    incrementForward(&TB);
    char three = getCharacterAtForward(&TB);

    printf("zero = %c, one = %c, two = %c, three = %c \n", zero, one, two, three );
    
    // findLexemeLength == 2
    printf("length = %d \n", findLexemeLength(&TB));

    // extractLexeme and compare string
    char* ptr = extractLexeme(&TB);
    printf("string = %s", ptr);

    fclose(TB.fp);
}