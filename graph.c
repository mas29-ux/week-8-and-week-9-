#include "graph.h"

Graph create_graph(int v) {
    Graph g;

    g.V = v;
    g.edges = malloc(v * sizeof(EdgeList));

    for (int i = 0; i < v; i++) {
        g.edges[i].head = NULL;
    }

    return g;
}

void add_edge(Graph *self, int from, int to, int w) {
    EdgeNodePtr node = malloc(sizeof *node);

    node->edge.to_vertex = to;
    node->edge.weight = w;

    node->next = self->edges[from].head;
    self->edges[from].head = node;
}

void print_graph(Graph *self) {
    for (int i = 0; i < self->V; i++) {
        printf("%d -> ", i);

        EdgeNodePtr node = self->edges[i].head;

        while (node != NULL) {
            printf("(%d) ", node->edge.to_vertex);
            node = node->next;
        }

        printf("\n");
    }
}

void print_in_degrees(Graph *self) {
    int *incoming_count = malloc(self->V * sizeof(int));

    for (int i = 0; i < self->V; i++) {
        incoming_count[i] = 0;
    }

    for (int i = 0; i < self->V; i++) {
        EdgeNodePtr node = self->edges[i].head;

        while (node != NULL) {
            incoming_count[node->edge.to_vertex]++;
            node = node->next;
        }
    }

    printf("in-degrees:\n");

    for (int i = 0; i < self->V; i++) {
        printf("  vertex %d: %d\n", i, incoming_count[i]);
    }

    free(incoming_count);
}

void destroy_graph(Graph *self) {
    for (int i = 0; i < self->V; i++) {
        EdgeNodePtr node = self->edges[i].head;

        while (node != NULL) {
            EdgeNodePtr next_node = node->next;
            free(node);
            node = next_node;
        }
    }

    free(self->edges);
    self->V = 0;
}

/*
   Runs a basic PageRank calculation for a fixed number of rounds.
   Each vertex begins with rank 1.0, then passes its score evenly
   across its outgoing links during every iteration.
*/
void pagerank(Graph *self, int iterations) {
    int vertex_count = self->V;
    double damping = 0.85;

    /* Store how many outgoing links each vertex has */
    double *outgoing_count = malloc(vertex_count * sizeof(double));

    for (int i = 0; i < vertex_count; i++) {
        outgoing_count[i] = 0;

        EdgeNodePtr node = self->edges[i].head;

        while (node != NULL) {
            outgoing_count[i]++;
            node = node->next;
        }
    }

    /* Starting rank value for every vertex */
    double *rank = malloc(vertex_count * sizeof(double));

    for (int i = 0; i < vertex_count; i++) {
        rank[i] = 1.0;
    }

    double *received_rank = malloc(vertex_count * sizeof(double));

    for (int round = 0; round < iterations; round++) {

        /* Clear the amount collected by each vertex */
        for (int i = 0; i < vertex_count; i++) {
            received_rank[i] = 0.0;
        }

        /* Distribute rank from each vertex to its neighbours */
        for (int i = 0; i < vertex_count; i++) {
            if (outgoing_count[i] > 0) {
                EdgeNodePtr node = self->edges[i].head;

                while (node != NULL) {
                    int target = node->edge.to_vertex;
                    received_rank[target] += rank[i] / outgoing_count[i];
                    node = node->next;
                }
            }
        }

        /* Apply damping to calculate the next rank values */
        for (int i = 0; i < vertex_count; i++) {
            rank[i] = (1.0 - damping) + damping * received_rank[i];
        }
    }

    printf("pagerank results after %d iterations:\n", iterations);

    for (int i = 0; i < vertex_count; i++) {
        printf("  vertex %d: %.4f\n", i, rank[i]);
    }

    free(rank);
    free(received_rank);
    free(outgoing_count);
}