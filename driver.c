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
#include "ast.h"
#include "parserDef.h"
#include "intermediateCodeGen.h"
#include "Codegen.h"
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


int main(int argc, char* argv[]){
    int option = -1;
    // printf("            FIRST AND FOLLOW SETS AUTOMATED         \n");
    // printf("            BOTH LEXICAL AND SYNTAX ANALYSIS MODULE IMPLEMENTED         \n");
    // printf("            MODULES WORK WITH ALL GIVEN TEST CASES\n");


    char* grammarFile = "grammar.txt";
    char* inputFile = argv[1];
    char* outputFile = argv[2];
    if(argc != 3){ printf("3 arguments expected, %d received\n",argc); return 0;}
    clock_t start_time = 0, end_time = 0;
    double total_CPU_time = 0, total_CPU_time_in_seconds = 0;
    int SIZE = 1024;
    while(option){
        switch (option)
        {
            case 0:
                return 0;
                break;

            case 1:
                printf("2\n");
                TwinBuffer* TB = initializeTwinBuffer(inputFile, SIZE);
                LEXEME* lex = simulateDFA(TB,1);
                while(lex->token != EOF_TOKEN){
                    lex = simulateDFA(TB,1);
                }
                fclose(TB->fp);
                cleanTwinBuffer(TB);
                break;

            case 2:{
                inputFile = argv[1];
                outputFile = argv[2];
                printf("RUNNING PARSER\n");
                TREENODE root = parser(grammarFile,inputFile,SIZE);
                setSizePT();
                inorderTraversal(root,0);
                break;
            }
            case 3:{
                inputFile = argv[1];
                printf("RUNNING PARSER\n");
                TREENODE root = parser(grammarFile,inputFile,SIZE);
                setSizePT();
                applyRule(root);
                setSizeAST();
                printf("\n\n\n\n\n\n\t\t\t\t\tPRINTING AST IN LEFT TO RIGHT & PREORDER \n\n\n\n");
                printAST(root->addr);
                break;
            }
            case 4:{
                inputFile = argv[1];
                printf("RUNNING PARSER\n");
                TREENODE root = parser(grammarFile,inputFile,SIZE);
                setSizePT();
                int pt = countParseTreeNodes(root,0);
                int pt_size = getSizePT();
                printf("NUMBER OF PARSE TREE NODES ARE: %d\t\t AND TOTAL MEMORY ALLOCATED IS %d BYTES\n\n",pt,pt_size);
                applyRule(root);
                int ast = pt - getSizeAST();
                setSizeAST();
                int ast_size = pt_size*ast/pt;

                printf("NUMBER OF AST NODES ARE: %d\t\t AND TOTAL MEMORY ALLOCATED IS %d BYTES\n\n",ast,ast_size);
                printf("COMPRESSION PERCENTAGE = %d %%\n\n",100*(pt-ast)/pt);
                break;
            }
            case 5:{
                inputFile = argv[1];
                printf("RUNNING PARSER\n");
                TREENODE root = parser(grammarFile,inputFile,SIZE);
                setSizePT();
                if(root == NULL){
                    break;
                }
                applyRule(root);
                setSizeAST();
                SYMBOLTABLE GLOBAL_SYMBOL_TABLE = initializeSymbolTable("module",0,10000);
                GST = GLOBAL_SYMBOL_TABLE;
                traversal(root->addr,GLOBAL_SYMBOL_TABLE);
                printf("\n\n\t\t\t\t\tTRAVERSAL 1 ENDED \n\n\n\n");
                traversalForDeclaredFuncs(root->addr,GLOBAL_SYMBOL_TABLE);
                printf("\n\n\t\t\t\t\tTRAVERSAL 2 ENDED \n\n\n\n");
                printFullTable(GST);
                break;
            }
            case 6:{
                inputFile = argv[1];
                printf("RUNNING PARSER\n");
                TREENODE root = parser(grammarFile,inputFile,SIZE);
                setSizePT();
                if(root == NULL){
                    break;
                }
                applyRule(root);
                setSizeAST();
                SYMBOLTABLE GLOBAL_SYMBOL_TABLE = initializeSymbolTable("module",0,10000);
                GST = GLOBAL_SYMBOL_TABLE;
                traversal(root->addr,GLOBAL_SYMBOL_TABLE);
                printf("\n\n\t\t\t\t\tTRAVERSAL 1 ENDED \n\n\n\n");
                traversalForDeclaredFuncs(root->addr,GLOBAL_SYMBOL_TABLE);
                printf("\n\n\t\t\t\t\tTRAVERSAL 2 ENDED \n\n\n\n");
                printf("\n\n\n\n\n\n\t\t\t\t\tPRINTING ACTIVATION RECORD SIZES \n\n\n\n");
                printFunctions(GST);
                break;
            }
            case 7:{
                inputFile = argv[1];
                printf("RUNNING PARSER\n");
                TREENODE root = parser(grammarFile,inputFile,SIZE);
                setSizePT();
                if(root == NULL){
                    break;
                }
                applyRule(root);
                setSizeAST();
                SYMBOLTABLE GLOBAL_SYMBOL_TABLE = initializeSymbolTable("module",0,10000);
                GST = GLOBAL_SYMBOL_TABLE;
                traversal(root->addr,GLOBAL_SYMBOL_TABLE);
                printf("\n\n\t\t\t\t\tTRAVERSAL 1 ENDED \n\n\n\n");
                traversalForDeclaredFuncs(root->addr,GLOBAL_SYMBOL_TABLE);
                printf("\n\n\t\t\t\t\tTRAVERSAL 2 ENDED \n\n\n\n");
                printf("\n\n\n\n\n\n\t\t\t\t\tPRINTING ACTIVATION RECORD SIZES \n\n\n\n");
                printArrayTable(GST);
                break;
            }
            case 8:{
                inputFile = argv[1];
                printf("RUNNING PARSER\n");
                TREENODE root = parser(grammarFile,inputFile,SIZE);
                setSizePT();
                if(root == NULL){
                    break;
                }
                applyRule(root);
                setSizeAST();
                SYMBOLTABLE GLOBAL_SYMBOL_TABLE = initializeSymbolTable("module",0,10000);
                GST = GLOBAL_SYMBOL_TABLE;
                traversal(root->addr,GLOBAL_SYMBOL_TABLE);
                printf("\n\n\t\t\t\t\tTRAVERSAL 1 ENDED \n\n\n\n");
                traversalForDeclaredFuncs(root->addr,GLOBAL_SYMBOL_TABLE);
                printf("\n\n\t\t\t\t\tTRAVERSAL 2 ENDED \n\n\n\n");
                break;
            }
            case 100:{
                start_time = clock();
                inputFile = argv[1];
                printf("RUNNING PARSER\n");
                TREENODE root = parser(grammarFile,inputFile,SIZE);
                applyRule(root);
                setSizeAST();
                SYMBOLTABLE GLOBAL_SYMBOL_TABLE = initializeSymbolTable("module",0,10000);
                GST = GLOBAL_SYMBOL_TABLE;
                traversal(root->addr,GLOBAL_SYMBOL_TABLE);
                printf("\n\n\t\t\t\t\tTRAVERSAL 1 ENDED \n\n\n\n");
                traversalForDeclaredFuncs(root->addr,GLOBAL_SYMBOL_TABLE);
                printf("\n\n\t\t\t\t\tTRAVERSAL 2 ENDED \n\n\n\n");
                end_time = clock();
                total_CPU_time = (end_time - start_time);
                printf("Clock Ticks = %lf\n",total_CPU_time);
                total_CPU_time_in_seconds = (double) total_CPU_time / CLOCKS_PER_SEC;
                printf("The code took %lf seconds.\n\n", total_CPU_time_in_seconds);
                break;
            }
            case 9:{
                inputFile = argv[1];
                printf("RUNNING PARSER\n");
                TREENODE root = parser(grammarFile,inputFile,SIZE);
                applyRule(root);
                SYMBOLTABLE GLOBAL_SYMBOL_TABLE = initializeSymbolTable("module",0,10000);
                GST = GLOBAL_SYMBOL_TABLE;
                traversal(root->addr,GLOBAL_SYMBOL_TABLE);
                printf("\n\n\t\t\t\t\tTRAVERSAL 1 ENDED \n\n\n\n");
                traversalForDeclaredFuncs(root->addr,GLOBAL_SYMBOL_TABLE);
                printf("\n\n\t\t\t\t\tTRAVERSAL 2 ENDED \n\n\n\n");
                // QR = initializeQuadruple();
                
                // printf("STARTING INTERMEDIATE CODE GENERATION\n\n");
                // traversalForCodeGeneration(root->addr,GLOBAL_SYMBOL_TABLE);
                // printf("PRINTING QUADRUPLE\n\n");
                // printQuadRuple();
                // printf("PRINTING QUADRUPLE\n\n");

                // printQuadRuple();
                // printf("STARTING CODE GENERATION\n\n");
                // CodeGeneration();
                break;
            }
            case 400:{
                start_time = clock();
                // the code process
                printf("RUNNING PARSER\n");
                TREENODE root = parser(grammarFile,inputFile,SIZE);
                applyRule(root);
                root = root->child->child;
                SYMBOLTABLE GLOBAL_SYMBOL_TABLE = initializeSymbolTable("module",0,10000);
                GST = GLOBAL_SYMBOL_TABLE;
                while(root!=NULL){
                    // printf("%s\n",NONTERMINALS_STRINGS[root->TREENODEDATA->nonterminal]);
                    // if(root->TREENODEDATA->nonterminal == driverModule) traversal()
                    // if(root->addr != NULL) printf("%d\n\n\n\n",root->addr->TREENODEDATA->terminal->token);
                    traversal(root->addr,GLOBAL_SYMBOL_TABLE);
                    root = root->next;
                }
                end_time = clock();
                total_CPU_time = (end_time - start_time);
                printf("Clock Ticks = %lf\n",total_CPU_time);
                total_CPU_time_in_seconds = (double) total_CPU_time / CLOCKS_PER_SEC;
                printf("The code took %lf seconds.\n\n", total_CPU_time_in_seconds);
                break;
            }
            default:
                break;
        }
        printf("Enter your option: ");
        scanf("%d", &option);
    }
}