#include <stdlib.h>

#ifndef INDEX_H
#define INDEX_H
#include "./parser.h"
    typedef char* Arguments;

    enum ArgumentsEnum
    {
        FILENAME
    };

    Arguments* argparse(int argc, char* argv[]);

#endif 