#include <math.h>
#include<stdio.h>


int findValue(char* number){
    int counter = 0;
    int n = strlen(number);
    int ret = 0;
    for(int c = 0;c<n;c++){
        ret = ret*10 + number[c]-'0';
    }
    return ret;
}