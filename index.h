#include <stdlib.h>

#ifndef ARGPARSE_INDEX_H
#define ARGPARSE_INDEX_H
#include "./parser.h"
    typedef char* Arguments;

    enum ArgumentsEnum
    {
        FILENAME
    };

    Arguments* argparse(int argc, char* argv[]);

#endif 