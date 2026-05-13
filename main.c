#include "graph.h"

/*
   Reads an unweighted graph from a file.
   Each edge entry only contains source
   and destination vertex values.
*/
Graph load_graph_unweighted(char *filename) {

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("unable to open file %s\n", filename);

        Graph empty_graph = {0, NULL};
        return empty_graph;
    }

    int total_vertices;

    fscanf(file, "%d", &total_vertices);

    Graph g = create_graph(total_vertices);

    int source;
    int destination;

    /* Read edges until no more data exists */
    while (fscanf(file, "%d,%d", &source, &destination) == 2) {
        add_edge(&g, source, destination, 0);
    }

    fclose(file);

    return g;
}

int main() {

    printf("=== week 9 - pagerank ===\n\n");

    Graph g = load_graph_unweighted("pagerank_test.txt");

    printf("graph has %d vertices\n\n", g.V);

    print_in_degrees(&g);

    printf("\n");

    /* Execute PageRank repeatedly to refine scores */
    pagerank(&g, 100);

    destroy_graph(&g);

    return 0;
}