//                         GROUP - 30
// ID:  2020A7PS0094P                     Name:  Arya Veer Singh Chauhan
// ID:  2020A7PS0049P                     Name:  Madhav Madhusoodanan
// ID:  2020A7PS0016P                     Name:  Ruchika Sarkar
// ID:  2020A7PS0984P                     Name:  Utsav Goel
// ID:  2020A7PS0102P                     Name:  Hardik Jain

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lexer.h"
#include "parser.h"
// #include "./removeComments.c"

typedef char* Arguments;

enum ArgumentsEnum
{
    FILENAME
};


Arguments* argparse(int argc, char* argv[]){
    Arguments* arglist = NULL;
    arglist = (Arguments*) malloc(1 * sizeof(Arguments));
    arglist[FILENAME] = argv[1];

    return arglist;
}

short removeComments(char* srcName, char* distName){
    // if(argc < 3) return 0;
    FILE* src = fopen(srcName,"r");
    FILE* dist = fopen(distName,"w");

    short shouldPrint = 1;

    short oldChar = getc(src);
    short newChar = getc(src);

    while(oldChar != EOF){
        if(oldChar == '*' && newChar == '*') {
            shouldPrint = !shouldPrint;
            oldChar = getc(src);
            newChar = getc(src);
        }
        if(shouldPrint) putc(oldChar, dist);
        oldChar = newChar;
        newChar = getc(src);
    }
    return 0;
}

int main(int argc, char* argv[]){
    int option = -1;
    char* grammarFile = "grammar.txt";
    char* inputFile = argv[1];
    char* outputFile = argv[2];
    clock_t start_time = 0, end_time = 0;
    double total_CPU_time = 0, total_CPU_time_in_seconds = 0;
    int SIZE = atoi(argv[3]);
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
                TwinBuffer* TB = initializeTwinBuffer(inputFile, SIZE);
                LEXEME* lex = simulateDFA(TB,1);
                while(lex->token != EOF_TOKEN){
                    lex = simulateDFA(TB,1);
                }
                fclose(TB->fp);
                cleanTwinBuffer(TB);
                break;

            case 3:
                inputFile = argv[1];
                outputFile = argv[2];
                printf("RUNNING PARSER\n");
                parser(grammarFile,inputFile, outputFile,SIZE);
                break;

            case 4:
                start_time = clock();
                // the code process
                parser(grammarFile,inputFile,outputFile, SIZE);
                end_time = clock();
                total_CPU_time = (end_time - start_time);
                printf("Clock Ticks = %lf\n",total_CPU_time);
                total_CPU_time_in_seconds = (double) total_CPU_time / CLOCKS_PER_SEC;
                printf("The code took %lf seconds.\n\n", total_CPU_time_in_seconds);
                break;
            
            default:
                break;
        }
        printf("Enter your option: ");
        scanf("%d", &option);
    }
}