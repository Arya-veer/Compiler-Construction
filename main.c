#include <stdio.h>
#include "argparse/index.h"
#include "removeComments/removeComments.c"

int main(int argc, char* argv[]){
    int option = -1;
    
    while(option){
        switch (option)
        {
            case 0:
                return 0;
                break;

            case 1:
                removeComments(argv[1], "/dev/stdout");
                break;

            case 2:
                printf("2\n");
                break;

            case 3:
                printf("3\n");
                break;

            case 4:
                printf("4\n");
                break;
            
            default:
                break;
        }
        printf("Enter your option: ");
        scanf(" %d", &option);
    }
}