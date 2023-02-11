#include <stdio.h>
#include "argparse/index.h"

int main(int argc, char* argv[]){
    Arguments* args = argparse(argc, argv);
    printf("%s", args[FILENAME]);
}