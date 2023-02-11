#include "index.h"

Arguments* argparse(int argc, char* argv[]){
    Arguments* arglist = NULL;
    arglist = (Arguments*) malloc(1 * sizeof(Arguments));
    arglist[FILENAME] = argv[1];

    return arglist;
}