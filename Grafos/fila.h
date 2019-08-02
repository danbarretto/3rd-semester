
#define ERROR -1

typedef int var;

typedef struct node {
	var value;
	struct node* next;
} nodeQ;

typedef struct _queue {
	nodeQ *begin, *end;
}queue;

queue* queue_create();
int queue_insert(queue* q, var x);
int queue_remove(queue* q, var* v);