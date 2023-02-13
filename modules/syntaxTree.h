#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node { 
    char *token; 
    struct node *childL; 
    struct node *childR;  
};

struct node* mkNode(struct node *childL, struct node *childR, char *token);
int *getMaxLvlLen(struct node *tree, int *tab, int lvl);
void printSyntaxTree_v2(struct node *tree, int *tab, int precCode, int curCode, int lvl, int espace);
void printSyntaxTree_v1(struct node* tree, int c);