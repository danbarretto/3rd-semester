#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

stack* stack_create() {
	stack* s = (stack*) malloc(sizeof(stack));
	s->top = NULL;
	return s;
}

int stack_insert(stack* s, int x) {
	nodeS* n = (nodeS*) malloc(sizeof(nodeS));
	if (!n) return ERROR;

	n->value = x;
	n->prev = s->top;
	s->top = n;

	return 0;
}

int stack_remove(stack* s, int* v) {
	if (stack_isEmpty(s)) return ERROR;

	*v = s->top->value;
	nodeS* prev = s->top->prev;
	
	free(s->top);
	s->top = prev;
	return 0;
}

