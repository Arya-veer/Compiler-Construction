#include "argparse/index.h"
#include <stdio.h>

int main(int argc, char* argv[]){
    Arguments* args = argparse(argc, argv);
    printf("%s", args[FILENAME]);
}