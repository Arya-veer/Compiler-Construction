#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>


char errors[30][200];
int numError = 0;

void storeInFormat(char* errorString,const char* format,...){
    va_list arglist;
    va_start(arglist,format);
    vsprintf(errorString,format,arglist);
    va_end(arglist);

}

void lexicalError(char errorChar,int lineNo,char* str){
    storeInFormat(errors[numError],"Lexical Error occured at line %d, \"%s\" ,  invalid character '%c'",lineNo,str,errorChar);
    numError++;
}

void printErrors(){
    for(int i = 0;i<numError;i++){
        printf("%s\n",errors[i]);
    }
}