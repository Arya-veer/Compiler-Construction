
#include<utils/tokens/tokens.h>

struct lexeme{
    TOKENS token;
    int lineNo;
    union lexemeData{
        char data[20];
        int intData;
        float floatData;
    };
};

typedef struct lexeme LEX;