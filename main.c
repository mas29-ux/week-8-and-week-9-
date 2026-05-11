#include "graph.h"

/*
   Reads graph information from a text file.

   File structure:
   - Line 1  : total number of vertices
   - Next lines : startVertex,endVertex,edgeWeight
*/
Graph read_graph_file(char *path) {
    FILE *fp = fopen(path, "r");

    // verify that the file opened correctly
    if (fp == NULL) {
        printf("unable to access file: %s\n", path);

        Graph empty_graph = {0, NULL};
        return empty_graph;
    }

    int total_vertices;

    // get number of vertices from the first line
    fscanf(fp, "%d", &total_vertices);

    Graph graph = create_graph(total_vertices);

    int start;
    int end;
    int weight;

    // keep reading edges until the file ends
    while (fscanf(fp, "%d,%d,%d", &start, &end, &weight) == 3) {
        add_edge(&graph, start, end, weight);
    }

    // release file resource
    fclose(fp);

    return graph;
}

int main() {
    printf("=== week 8 - graph file loading ===\n\n");

    // create graph using file data
    Graph graph = read_graph_file("graph.txt");

    printf("graph adjacency list:\n");
    print_graph(&graph);

    printf("\n");

    // display incoming edge count for every vertex
    print_in_degrees(&graph);

    // clear allocated memory
    destroy_graph(&graph);

    return 0;
}