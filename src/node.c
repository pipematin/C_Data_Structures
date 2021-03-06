#include <stdlib.h> // Supplies malloc(), calloc(), and realloc()
#include <string.h> // Supplies memcpy(), strlen(), strcpy(), strcat(), strcmp(), strlwr(), strupr()

#include "node.h"

Node* nodeCreate(void *data, Node *before, Node *next, size_t dataSize, freeFunction freeFn,
	compareFunction compFn, toStringFunction toStringFn, copyFunction copyFn){
	// input check
	if(data == NULL || dataSize <= 0) return NULL;

	//variables
	Node *node = NULL;

	// allocate memory for node struct. Return NULL if not posible
	node = (Node*)malloc(sizeof(Node));
	if(node == NULL) return NULL;

	// copy the data
	node->copyFn = copyFn;
	node->data = node->copyFn(data);
	if(node->data == NULL){
		free(node);
		return NULL;
	}

	// assign static values
	node->dataSize = dataSize;
	node->freeFn = freeFn;
	node->compFn = compFn;
	node->toStringFn = toStringFn;
	node->next = next;
	node->before = before;

	return node;
}

void nodeDestroy(Node *node){
	// input check
	if(node == NULL) return;

	if(node->freeFn){
		node->freeFn(node->data);
	}

	free(node);
}

char* nodeToString(Node *node){
	// input check
	if( node == NULL || !node->toStringFn) return NULL;

	return node->toStringFn(node->data);
}

COMPARATION nodeCompare(Node *node1, Node *node2){
	// input check
	if( node1 == NULL || node2 == NULL || !node1->compFn
		|| node1->compFn != node2->compFn) return ER;

	return node1->compFn(node1->data, node2->data);
}