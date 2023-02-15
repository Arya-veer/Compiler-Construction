#include<stdio.h>
#include "../utils/Buffer/readFile.c"
#include "../utils/Buffer/twinBuffer.c"
#include "tokenize.c"

int main(){
    TwinBuffer TB = initializeTwinBuffer("_text.txt");
    populateTwinBuffer(&TB);
    incrementForward(&TB);
    incrementForward(&TB);
    incrementForward(&TB);
    incrementForward(&TB);
    incrementForward(&TB);
    incrementForward(&TB);
    // incrementForward(&TB);
    // incrementForward(&TB);

    tokenize(&TB,2);

    fclose(TB.fp);
}
