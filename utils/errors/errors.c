#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>


// char errors[30][200];
// int numError = 0;

// void storeInFormat(char* errorString,const char* format,...){
//     va_list arglist;
//     va_start(arglist,format);
//     vsprintf(errorString,format,arglist);
//     va_end(arglist);

// }

void lexicalError(char errorChar,short int lineNo,char* str){
    printf("Lexical Error occured at line %hi, \"%s\" ,  invalid character '%c'",lineNo,str,errorChar);
}

// void printErrors(){
//     for(int i = 0;i<numError;i++){
//         printf("%s\n",errors[i]);
//     }
// }