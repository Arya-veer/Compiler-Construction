#include <stdio.h>
#include <stdlib.h>

// #include "../rules/addRules.c"
#include "automation.h"
// int FIRSTANDFOLLOWSETS[119][200];
int FOLLOWSETS[119][20];

// void follow(int numRules, LISTNODE *RULES, int i)
// {
//     for (int j = 0; j < numRules; j++)
//     {
//         LISTNODE temp = RULES[j];
//         temp = temp->next;
//         while (temp)
//         {
//             if (temp->NODETYPE->nonterminal == RULES[i]->NODETYPE->nonterminal)
//             {
//                 if (temp->next)
//                 {
//                     LISTNODE help = temp->next;
//                     if (help->NODETYPE->terminal == 1)
//                     {
//                         FOLLOWSETS[i][0]++;
//                         FOLLOWSETS[i][FOLLOWSETS[i][0]] = (int)help->NODETYPE->terminal;
//                     }

//                     // else
//                     // {
//                     //     for (int k = FOLLOWSETS[i][0] + 1; k <= FOLLOWSETS[i][0] + FIRSTANDFOLLOWSETS[j][0]; k++)
//                     //     {
//                     //         FIRSTANDFOLLOWSETS[i][k] = FIRSTANDFOLLOWSETS[j][k - FIRSTANDFOLLOWSETS[i][0]];
//                     //     }
//                     // }
//                 }

//                 else
//                 {
//                     follow(numRules, RULES, j);
//                     for (int k = FOLLOWSETS[i][0] + 1; k <= FOLLOWSETS[i][0] + FOLLOWSETS[j][0]; k++)
//                     {
//                         FOLLOWSETS[i][k] = FOLLOWSETS[j][k - FOLLOWSETS[i][0]];
//                     }
//                 }
//             }
//             temp = temp->next;
//         }
//     }
//     return;
// }

void find(int *vis, LISTNODE *RULES, int i, int prev_i, LISTNODE prev_curr, int *follow_arr)
{
    // printf("i = %d, prev_i = %d\n",i,prev_i);
    if (vis[i] == 1)
    {
        return;
    }

    int numRules = 119;
    LISTNODE curr = RULES[i];
    // curr = curr->next;

label:
    if (curr->next)
        curr = curr->next;

    if (curr->isTerminal == 1)
    {
        // printf("THIS IS TERMINAL\n");
        int terminal = (int)curr->NODETYPE->terminal;
        vis[i] = 1;
        FIRSTANDFOLLOWSETS[i][0]++;
        FIRSTANDFOLLOWSETS[i][FIRSTANDFOLLOWSETS[i][0]] = terminal;
        return;
    }

    if (curr->isTerminal == 0)
    {
        vis[i] = 1;
        for (int j = 0; j < numRules; j++)
        {
            if (RULES[j]->NODETYPE->nonterminal == curr->NODETYPE->nonterminal)
            {

                if (vis[j] != 1 && vis[j] != 2)
                {
                    find(vis, RULES, j, i, curr, follow_arr);
                }

                if (vis[j] == 2)
                {
                    LISTNODE helper = curr;
                    while (helper->NODETYPE->nonterminal != RULES[j]->NODETYPE->nonterminal)
                    {
                        helper = helper->next;
                    }
                    curr = helper;
                    goto label;
                }

                for (int k = FIRSTANDFOLLOWSETS[i][0] + 1; k <= FIRSTANDFOLLOWSETS[i][0] + FIRSTANDFOLLOWSETS[j][0]; k++)
                {
                    FIRSTANDFOLLOWSETS[i][k] = FIRSTANDFOLLOWSETS[j][k - FIRSTANDFOLLOWSETS[i][0]];
                }
                FIRSTANDFOLLOWSETS[i][0] += FIRSTANDFOLLOWSETS[j][0];
            }
        }
    }

    else
    {
        if (vis[i] != 2)
        {
            vis[i] = 2;
            follow_arr[0]++;
            follow_arr[follow_arr[0]] = i;
            // printf("WILL NEED FOLLOW\n");
            return;
        }
    }
}

void automateFirstandFollow(LISTNODE *RULES)
{

    int vis[119] = {0};
    int numRules = 119;
    int follow_arr[50] = {0};

    for (int i = 0; i < numRules; i++)
    {
        find(vis, RULES, i, -1, NULL, follow_arr);
    }

    // for (int i = 1; i <= follow_arr[0]; i++)
    // {
    //     printf(" %d \n" , follow_arr[i]);
    //     follow(numRules, RULES, follow_arr[i]);
    //     for (int j = 0; j < FOLLOWSETS[follow_arr[i]][0]; j++)
    //     {
    //         FIRSTANDFOLLOWSETS[follow_arr[i]][j] = FOLLOWSETS[follow_arr[i]][j];
    //     }
    // }

    printf("PRINTING FIRSTANDFOLLOW\n");
    for (int i = 0; i < 119; i++)
    {
        int size = FIRSTANDFOLLOWSETS[i][0];
        printf("size = %d, ", size);
        for (int j = 1; j <= size; j++)
        {
            printf("%d, ", FIRSTANDFOLLOWSETS[i][j]);
        }
        printf("\n");
    }
}
