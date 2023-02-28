#include <stdio.h>
#include "hashing.h"
#include "../tokens/tokens.c"

int hash(char* string){
    int collect = 0;
    int index = 0;
    while(*(string + index)){
        collect += ((int)*(string + index) * 13 * (index + 1));
        index++;
    }
    printf("%d\n", collect + index);
    return collect + index;
}
