#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main(){
    char* keywords[4] = {"integer","boolean","of","declar\0"};
    typedef enum {TK_INT,TK_BOOL,TK_OF,TK_DECLARE} KW ;
    char* keyword = "declar";
    printf("Printing\n");
    int i = 0;
    KW kw = (KW) 1;
    printf("%d\n",kw==TK_BOOL);

    for(i = 0;i<4;i++) {
        printf("%s\n",keywords[i]);
        printf("%d\n",strcmp(keywords[i],keyword));
        
    }
    return 0;
}