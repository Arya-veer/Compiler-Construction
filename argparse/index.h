#include <stdlib.h>
typedef char* Arguments;

enum ArgumentsEnum
{
    FILENAME
};

Arguments* argparse(int argc, char* argv[]);