#include <stdio.h>
#include <stdlib.h>

int main(){
    char c;
    FILE* fp = fopen("input.txt", "r");
    while ((c = fgetc(fp)) != EOF){
        if(c == ' ') printf("\n");
        else if(c == '\b') printf(" 5\n");
    }
}