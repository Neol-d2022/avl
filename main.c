#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "avl_tree.h"
//#include <conio.h>

int cmp(void *arg1, void *arg2) {
	return *(int*)arg1 - *(int*)arg2;
}

void shuffle(int *arr, size_t length) {
	if(length < 2) return;
	srand(time(0));
	size_t rnd, upper = length - 1;
	int tmp;
	for(size_t i = 0; i < upper; i++) {
		rnd = (size_t)rand() % (length - i - 1);
		tmp = arr[rnd];
		arr[rnd] = arr[i];
		arr[i] = tmp;
	}
}

void process(void *intPtr, void* dummy) {
	//printf("%d\n", *(int*)intPtr);
	*(int*)intPtr += 1;
}

#define ARR_LENGTH (size_t)16777216
#define DELETE_LIMIT (size_t)8388608

int main(int argc, char **argv) {
	int *arr = (int*)malloc(sizeof(arr[0]) * ARR_LENGTH);
	for(size_t i = 0; i < ARR_LENGTH; i++) {
		arr[i] = (int)i;
	}
	while(1) {
		shuffle(arr, ARR_LENGTH);
		printf("Test array initialized\n"); //getch();
		AVL_TREE* tree = AVL_Create(cmp, 0);
		printf("Tree created.\n"); //getch();
		/*try*/ {
			for(size_t i = 0 ; i < ARR_LENGTH; i++)
				AVL_Insert(tree, arr + i);
		}
		//catch(...) { abort(); }
		printf("Elements inserted.\n"); //getch();
		AVL_Traverse(tree, 0, process);
		printf("Traversal done.\n"); //getch();
		/*try*/ {
			for(size_t i = 0; i < DELETE_LIMIT; i++)
				AVL_Delete(tree, arr + i);
		}
		//catch(...) { abort(); }
		AVL_Destroy(tree);
		printf("Tree destroyed.\nNext round.\n"); //getch();
	}
	return 0;
}
