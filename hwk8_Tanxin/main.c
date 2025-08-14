#include "graph.h"  
#include <stdlib.h>  
#include <string.h>
#include <stdio.h>

typedef struct Vertex_ {
    char label;  /* Room ID */
    VertexColor color;
} Vertex;

/*Vertex definition  */
int match_vertex(const void *v1, const void *v2) {
    const Vertex *a = (const Vertex *)v1;
    const Vertex *b = (const Vertex *)v2;
    return a->label == b->label;
}
/* Depth-first search (DFS) */
int dfs(Graph *graph, Vertex *current, char exit_label) {
    /*Recursive function that searches from current to exit_label */
    current->color = gray;
    /* Mark current vertex as discovered */
    AdjList *adjlist;
    if (graph_adjlist(graph, current, &adjlist) != 0)
        return 0;
    /* Get the adjacency list for current. Return 0 if failed. */
    ListElmt *element = list_head(&adjlist->adjacent);
    while (element != NULL) {
        Vertex *adj = (Vertex *)list_data(element);
        /* Loop over each adjacent vertex*/
        if (adj->label == exit_label)
            return 1;

        if (adj->color == white) {
            if (dfs(graph, adj, exit_label))
                return 1;
        }

        element = list_next(element);
    }
    /* Recursively explore unvisited neighbors */
    current->color = black;
    return 0;
}

/* isExitReachable Function */
int isExitReachable(Graph *pMaze, char entrance, char exit) {
    ListElmt *element;

    // Reset all vertex colors
    for (element = list_head(&pMaze->adjlists); element != NULL; element = list_next(element)) {
        Vertex *v = (Vertex *)((AdjList *)list_data(element))->vertex;
        v->color = white;
    }
   /* Prepare for DFS */
    Vertex *start = NULL;
    for (element = list_head(&pMaze->adjlists); element != NULL; element = list_next(element)) {
        Vertex *v = (Vertex *)((AdjList *)list_data(element))->vertex;
        /*Find the entrance node in the graph */
        if (v->label == entrance) {
            start = v;
            break;
        }
    }

    if (start == NULL) return 0;
    return dfs(pMaze, start, exit);
}



void add_vertex(Graph *g, char label) {
    Vertex *v = malloc(sizeof(Vertex));
    v->label = label;
    v->color = white;
    graph_ins_vertex(g, v);
}

void add_edge(Graph *g, char from, char to) {
    ListElmt *element;
    Vertex *v_from = NULL;
    Vertex *v_to = NULL;

    // Find the real 'from' vertex
    for (element = list_head(&g->adjlists); element != NULL; element = list_next(element)) {
        Vertex *v = (Vertex *)((AdjList *)list_data(element))->vertex;
        if (v->label == from) v_from = v;
        if (v->label == to) v_to = v;
    }

    if (v_from && v_to) {
        graph_ins_edge(g, v_from, v_to);
        graph_ins_edge(g, v_to, v_from);
    }
}

/* Maze construction */
void build_maze1(Graph *g) {
    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    for (int i = 0; i < 7; ++i) add_vertex(g, vertices[i]);

    add_edge(g, 'A', 'C');
    add_edge(g, 'A', 'D');
    add_edge(g, 'B', 'D');
    add_edge(g, 'C', 'F');
    add_edge(g, 'D', 'E');
    add_edge(g, 'D', 'G');
    add_edge(g, 'E', 'G');
    add_edge(g, 'F', 'G');
}
/* Adds undirected edges for Maze #1 (which has a valid path from A to G) */
void build_maze2(Graph *g) {
    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    for (int i = 0; i < 7; ++i) add_vertex(g, vertices[i]);

    add_edge(g, 'A', 'C');
    add_edge(g, 'A', 'D');
    add_edge(g, 'B', 'D');
    add_edge(g, 'C', 'F');
    add_edge(g, 'E', 'G');
}
/* main function */
int main() {
    Graph maze1, maze2;
    graph_init(&maze1, match_vertex, free);
    graph_init(&maze2, match_vertex, free);

    build_maze1(&maze1);
    build_maze2(&maze2);

    printf("Testing Maze #1 (A to G):\n");
    int result1 = isExitReachable(&maze1, 'A', 'G');
    printf("  Result: %s\n\n", result1 ? "reachable" : "not reachable");

    printf("Testing Maze #2 (A to G):\n");
    int result2 = isExitReachable(&maze2, 'A', 'G');
    printf("  Result: %s\n\n", result2 ? "reachable" : "not reachable");

    graph_destroy(&maze1);
    graph_destroy(&maze2);
    return 0;
}
