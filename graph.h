#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

/* Stores destination vertex and edge cost */
typedef struct edge {
    int to_vertex;
    int weight;
} Edge;

/* Node used inside the linked adjacency list */
typedef struct edgeNode {
    Edge edge;
    struct edgeNode *next;
} *EdgeNodePtr;

/* Represents one adjacency list for a vertex */
typedef struct edgeList {
    EdgeNodePtr head;
} EdgeList;

/* Main graph structure containing all vertices */
typedef struct graph {
    int V;
    EdgeList *edges;
} Graph;

/* Function declarations */
Graph create_graph(int v);
void add_edge(Graph *self, int from, int to, int w);
void print_graph(Graph *self);
void print_in_degrees(Graph *self);
void destroy_graph(Graph *self);

#endif