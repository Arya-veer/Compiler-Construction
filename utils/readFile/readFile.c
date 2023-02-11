#include <stdio.h>
#include <math.h>
#include <string.h>
#include <readfile.h>


TwinBuffer populateTwinBuff(char* fname){
    TwinBuffer TB;
    TB.fp = fopen(fname,"w");
    size_t charsRead;
}