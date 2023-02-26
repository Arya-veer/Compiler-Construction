#include <stdio.h>
#include "argparse/index.h"

int main(int argc, char* argv[]){
    Arguments* args = argparse(argc, argv);
    // printf("%s", args[FILENAME]);
    char* grammarFile = "grammar.csv";
    char* inputFile = "codeInput.txt";
    parser(grammarFile,inputFile);
    return 0;
}