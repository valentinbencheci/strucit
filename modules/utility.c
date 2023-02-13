#include "utility.h"

void printSpace(int c, int nbNL){
    for(int i = 0; i < nbNL; i++){
        printf("\n");
    }
	for(int i = 0; i < c; i++){
		printf(" ");
	}
}

int getIntLen(int n){
    char str[30];
	sprintf(str, "%d", n);
	return strlen(str);
}

int *addNewIntArray(int *tab, int size, int newVal){
	int *tmpTab = malloc(size * sizeof(int));

	for (int i = 0; i < size; i++){
		if (i == size - 1){
			*(tmpTab + i) = newVal;
			return tmpTab;
		} else {
			*(tmpTab + i) = *(tab + i);
		}
	}
}

char **addNewCharArray(char **tab, int size, char *newEl){
	char **tmpTab = malloc(size * 100 * sizeof(char));

	for (int i = 0; i < size; i++){
		if (i == size - 1){
			*(tmpTab + i) = strdup(newEl);
		} else {
			*(tmpTab + i) = strdup(*(tab + i));
		}
	}

	return tmpTab;
}

// int main(){
	// int *tab;
	// int array[] = {1, 2, 3, 4};
	// tab = array;
	// tab = addNewIntArray(tab, 5, 5);

	// for (int i = 0; i <  5; i++){
	// 	printf("\n%d", *(tab+i));
	// }

// 	char *tab[100];
// 	tab[0] = strdup("test1");
// 	tab[1] = strdup("test2");
// 	tab[2] = strdup("test3");
// 	char **res;
// 	res = tab;
// 	res = addNewCharArray(res, 4, "test4");

// 	for (int i = 0; i <  4; i++){
// 		printf("\n%s", res[i]);
// 	}
// }