typedef struct node {
	int value;
	struct node* prev;
} nodeS;

typedef struct _stack {
	nodeS *top;
}stack;

stack* stack_create();
int stack_insert(stack* s, int x);
int stack_remove(stack* s, int* v);