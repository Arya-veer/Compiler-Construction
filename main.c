#include <stdio.h>
#include "argparse/index.h"

int main(int argc, char* argv[]){
    Arguments* args = argparse(argc, argv);
    // printf("%s", args[FILENAME]);
    char* grammarFile = "manual/grammar.csv";
    char* inputFile = "codeInput.txt";
    parser(grammarFile,inputFile);
    // testAutomation(grammarFile);
    return 0;
}