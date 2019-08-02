#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pilha.h"
#include "fila.h"

#define MAXV 100
#define WHITE 0
#define GREY 1
#define BLACK 2

typedef struct EdgeNode {
	int v;
	int weight;
	struct EdgeNode *next;
} EdgeNode;

typedef struct {
	EdgeNode *begin, *end;
} VertexNode;

typedef struct graph {
	VertexNode adj[MAXV];
	size_t qttVertex;
}Graph;

Graph* graph_create(size_t qttVertex) {
	if (qttVertex >= MAXV) return NULL;

	Graph* g = malloc(sizeof(Graph));

	g->qttVertex = qttVertex;
	for (int i = 0; i < qttVertex; i++) {
		g->adj[i].begin = malloc(sizeof(EdgeNode));
		g->adj[i].begin->v = -1;
		g->adj[i].begin->weight = -1;
		g->adj[i].begin->next = NULL;
		g->adj[i].end = g->adj[i].begin;
	}

	return g;
}

void addEdge(Graph* g, int u, int v, int w) {
	if (u >= g->qttVertex || v >= g->qttVertex) return;

	g->adj[u].end->next = malloc(sizeof(EdgeNode));
	g->adj[u].end = g->adj[u].end->next;
	g->adj[u].end->v = v;
	g->adj[u].end->weight = w;
	g->adj[u].end->next = NULL;
}

void removeEdge(Graph* g, int u, int v, int w) {
	if (u >= g->qttVertex || v >= g->qttVertex) return;

	bool found = false;;	
	EdgeNode *prev = g->adj[u].begin;
	EdgeNode *aux = prev->next;

	while (aux != NULL && !found) {
		if (aux->v == v && w == aux->weight) {
			found = true;
			prev->next = aux->next;

			if (g->adj[u].end == aux) g->adj[u].end = prev;
			free(aux);
		} else {
			prev = aux;
			aux = aux->next;
		}
	}
}

void destroy(Graph* g) {
	for (int u = 0; u < g->qttVertex; u++) {
		EdgeNode* aux = g->adj[u].begin;
		while(aux != NULL) {
			EdgeNode* cur = aux->next;
			free(aux);
			aux = cur;
		}
	}

	free(g);
}


void dfs(Graph* g, int start, int* currTime, int *color, int* tempoD, int* tempoP){
    color[start] = GREY;
    tempoD[start] = ++(*currTime);
    for(int i=0; i<g->qttVertex; i++){
        if(color[i]==WHITE){
            dfs(g, i, currTime, color, tempoD, tempoP);
        }else if(color[i]==GREY){
            printf("GRAFO CíCLICO!\n");
            return;
        }
    }
    color[start] = BLACK;
    tempoP[start] = ++(*currTime);
}

void ordenTop(Graph* G, int vert, int* vis, stack* q){
    vis[vert] = 1;
    for(int i=0; i<G->qttVertex; i++){
        if(vis[i]==0) ordenTop(G, i, vis, q);
    }
    queue_insert(q, vert);
}

void tarjan(Graph* G, int vert,int* vis,int* low, int* tempoD, int* tempoP, stack* st, int* currTime){
    tempoD[vert] = ++(*currTime);
    stack_insert(st, vert);
    vis[vert] = 1;
    low[vert] = tempoD[vert];
    for(int i=0; i<G->qttVertex; i++){
        if(tempoD[i]==0){
            tarjan(G, vert, vis, low, tempoD, tempoP, st, currTime);
            low[vert] = low[vert] < low[i] ? low[vert] : low[i];
        }else if(vis[i]){
                low[vert] = low[vert] < tempoD[i] ? low[vert] : tempoD[i];
        }
    }
    if(low[vert]==tempoD[vert]){
        nodeS* aux = st->top;
        while(aux->value!=vert){
            printf("%d\n", aux->value);
            vis[aux->value] = 0;
            stack_remove(st, aux->value);
        }
        printf("%d\n", st->top->value);
        vis[st->top->value] = 0;
        stack_remove(st, st->top->value);
    }
}


