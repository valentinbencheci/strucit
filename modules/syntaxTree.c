#include "syntaxTree.h"
#include "utility.h"

struct node* mkNode(struct node *childL, struct node *childR, char *token){	
	struct node *newNode = (struct node *)malloc(sizeof(struct node));
	char *newStr = (char *)malloc(strlen(token)+1);

	strcpy(newStr, token);
	newNode->childL = childL;
	newNode->childR = childR;
	newNode->token = newStr;

	return(newNode);
}

int *getMaxLvlLen(struct node *tree, int *tab, int lvl){
	if (strlen(tree->token) > *(tab + lvl)){
		*(tab + lvl) = strlen(tree->token);
	}
	
	if (tree->childL){
		tab = getMaxLvlLen(tree->childL, tab, lvl + 1);
	}
	if (tree->childR){
		tab = getMaxLvlLen(tree->childR, tab, lvl + 1);
	}
	
	return tab;
}

void printSyntaxTree_v2(struct node *tree, int *tab, int precCode, int curCode, int lvl, int espace){
	if (tree->childR){
		printSyntaxTree_v2(tree->childR, tab, curCode, curCode + 1, lvl + 1, espace + 8 + getIntLen(precCode) + getIntLen(curCode) + *(tab + lvl));
	}

	printSpace(espace, 2);
	printf("[%d] %s [%d]", precCode, tree->token, curCode);

	if (tree->childL){
		printSyntaxTree_v2(tree->childL, tab, curCode, curCode + 2, lvl + 1, espace + 8 + getIntLen(precCode) + getIntLen(curCode) + *(tab + lvl));
	}	
}

void printSyntaxTree_v1(struct node* tree, int espace){
	printSpace(espace, 1);
	printf("--> %s", tree->token);
	if (tree->childL) {
		printSyntaxTree_v1(tree->childL, espace + 2);
	}
	if (tree->childR) {
		printSyntaxTree_v1(tree->childR, espace + 2);
	}
}