#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

queue* queue_create() {
	queue* q = (queue*) malloc(sizeof(queue));
	q->begin = q->end = NULL;
	return q;
}

int queue_insert(queue* q, var x) {
	nodeQ* n = (nodeQ*) malloc(sizeof(node));
	if (!n) return ERROR;

	n->next = NULL;
	n->value = x;

	if (!q->begin) q->begin = n;
	else q->end->next = n;
	
	q->end = n;

	return 0;
}

int queue_remove(queue* q, var* v) {
	if (queue_isEmpty(q)) return ERROR;

	*v = q->begin->value;

	nodeQ* next = q->begin->next;
	free(q->begin);
	q->begin = next;
	return 0;
}
