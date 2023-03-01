#include <stdio.h>
#include <stdlib.h>

// #include "../rules/addRules.c"
#include "automation.h"
// FIRSTANDFOLLOWSETS[119][200]={0};
// int FOLLOWSETS[129][20] = {0};
int vis[129] = {0};


int check(int i, int val)
{
    for (int j = 1; j <= FOLLOWSETS[i][0]; j++)
    {
        if (FOLLOWSETS[i][j] == val)
            return 0;
    }
    return 1;
}

void follow(int numRules, LISTNODE *RULES, int i, int *vis1)
{
    // if (vis1[i] == 1)
    //     return;
    // printf("follow for %d \n", i);
    // vis1[i] = 1;

    for (int j = 0; j < numRules; j++)
    {
        // printf("(i,j) trying to match for %d , in rule %d \n",i,j);
        LISTNODE temp = RULES[j];
        temp = temp->next;
        while (temp)
        {
            if (temp->isTerminal == 0 && temp->NODETYPE->nonterminal == RULES[i]->NODETYPE->nonterminal)
            {
                // vis1[j] = 1;

            god:

                if (temp->next)
                {
                    LISTNODE help = temp->next;
                    if (help->isTerminal == 1)
                    {
                        // printf("(TERMINAL) in rule number %d ,my %d was terminal \n",j+1,i+1);
                        if (check(i, (int)help->NODETYPE->terminal))
                        {
                            FOLLOWSETS[i][0]++;
                            FOLLOWSETS[i][FOLLOWSETS[i][0]] = (int)help->NODETYPE->terminal;
                        }
                    }

                    else
                    {
                        for (int z = 0; z < numRules; z++)
                        {
                            // printf("(j,z) trying to match for %d , in rule %d \n",j,z);
                            if (help->isTerminal == 0 && help->NODETYPE->nonterminal == RULES[z]->NODETYPE->nonterminal)
                            {
                                LISTNODE help1 = RULES[z];
                                help1 = help1->next;

                                if (help1->isTerminal != -1)
                                {
                                    // printf("(NON-TERMINAL) in rule number %d , called by %d  ,working for %d\n ",z+1,j+1,i+1);

                                    vis1[z] = 1;
                                    for (int k = 1; k <= FIRSTANDFOLLOWSETS[z][0]; k++)
                                    {

                                        if (check(i, FIRSTANDFOLLOWSETS[z][k]))
                                        {
                                            FOLLOWSETS[i][0]++;
                                            FOLLOWSETS[i][FOLLOWSETS[i][0]] = FIRSTANDFOLLOWSETS[z][k];
                                        }
                                    }
                                }

                                else
                                {
                                    if (temp->next)
                                    {
                                        temp = temp->next;
                                        goto god;
                                    }
                                    else
                                    {
                                        follow(numRules, RULES, z, vis1);
                                        for (int k = 1; k <= FOLLOWSETS[z][0]; k++)
                                        {
                                            if (check(i, FOLLOWSETS[z][k]))
                                            {
                                                FOLLOWSETS[i][0]++;
                                                FOLLOWSETS[i][FOLLOWSETS[i][0]] = FOLLOWSETS[z][k];
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                else
                {
                king:
                    if (FOLLOWSETS[j][0] == 0)
                        follow(numRules, RULES, j, vis1);

                    for (int k = 1; k <= FOLLOWSETS[j][0]; k++)
                    {
                        if (check(i, FOLLOWSETS[j][k]))
                        {
                            FOLLOWSETS[i][0]++;
                            FOLLOWSETS[i][FOLLOWSETS[i][0]] = FOLLOWSETS[j][k];
                        }
                    }
                }
            }
            temp = temp->next;
        }
    }
}

void find(int *vis, LISTNODE *RULES, int i, int prev_i, LISTNODE prev_curr, int *follow_arr)
{
    // printf("i = %d, prev_i = %d\n",i,prev_i);
    if (vis[i] == 1)
    {
        return;
    }

    int numRules = 129;
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

    int numRules = 129;
    int follow_arr[50] = {0};

    for (int i = 0; i < numRules; i++)
    {
        find(vis, RULES, i, -1, NULL, follow_arr);
    }

    for (int i = 1; i <= follow_arr[0]; i++)
    {
        int vis1[129] = {0};
        FOLLOWSETS[0][0] = 1;
        FOLLOWSETS[0][1] = EOF_TOKEN;
        vis1[0] = 1;
        follow(numRules, RULES, follow_arr[i], vis1);
        // printf(" %d \n", follow_arr[i]);

        for (int j = 0; j <= FOLLOWSETS[follow_arr[i]][0]; j++)
        {

            FIRSTANDFOLLOWSETS[follow_arr[i]][j] = FOLLOWSETS[follow_arr[i]][j];
        }
        // printf("-----------------------------\n");
    }
    printf("First and Follow Automated\n");
    // printf("PRINTING FIRSTANDFOLLOW\n");
    // for (int i = 0; i < 129; i++)
    // {
    //     int size = FIRSTANDFOLLOWSETS[i][0];

    //     // printf("vis = %d, ", vis1[i]);
    //     printf("size = %d, ", FIRSTANDFOLLOWSETS[i][0]);
    //     for (int j = 1; j <= size; j++)
    //     {
    //         // {   if(j!=0)
    //         printf("%s, ", TERMINALS_STRINGS[FIRSTANDFOLLOWSETS[i][j]]);
    //     }
    //     printf("\n");
    // }
}
