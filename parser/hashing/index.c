#include <stdio.h>
#include "hashing.h"
#include "../../utils/tokens/tokens.c"

int hash(char* string){
    int collect = 0;
    int index = 0;
    while(*(string + index)){
        collect += ((int)*(string + index) * 13 * (index + 1));
        index++;
    }
    return collect + index;
}

int main(){
    printf("Token\tHash Value\n");
    for(int i = 0; i < 53; i++){
        printf("%s\t%d\n", TOKENS_STRING[i], hash(TOKENS_STRING[i]));
    }
}
