#include <stdio.h>
#include <time.h>
#include "argparse/index.h"
#include "removeComments/removeComments.c"

int main(int argc, char* argv[]){
    int option = -1;
    char* grammarFile = "manual/grammar.csv";
    clock_t start_time = 0, end_time = 0;
    double total_CPU_time = 0, total_CPU_time_in_seconds = 0;
    while(option){
        switch (option)
        {
            case 0:
                return 0;
                break;

            case 1:
                removeComments(argv[1], "/dev/stdout");
                printf("\n");
                break;

            case 2:
                printf("2\n");
                break;

            case 3:
                printf("%s\n",argv[1]);
                char* inputFile = argv[1];
                parser(grammarFile,inputFile);
                break;

            case 4:
                start_time = clock();
                // the code process
                end_time = clock();
                total_CPU_time = (double) (end_time - start_time);
                total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;
                printf("The code took %lf seconds.\n\n", total_CPU_time_in_seconds);
                break;
            
            default:
                break;
        }
        printf("Enter your option: ");
        scanf("%d", &option);
    }
}