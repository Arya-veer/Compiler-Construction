#include<stdio.h>
#include<stdlib.h>

#include"lexer.h"

void simulateDFA(){
    char* error;
    int state = 0;
    TwinBuffer TB;
    char* currBuff;
    while(1){
        currBuff = TB.curr?TB.buffFirst:TB.buffSecond;
        switch(state){
            case -1:
                error = "Lexical Error Occured";
                break;
            case 0:
                printf("START STATE\n");
                TB.lexemeBegin = TB.forward;
                

        }
    }
}