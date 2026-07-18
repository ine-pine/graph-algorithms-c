// graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define INF 1000000000

typedef struct {
    int data[MAX+1];
    int front, rear;
} Queue;

void dfs(int n, int adj[MAX+1][MAX+1]);
void bfs(int n, int adj[MAX+1][MAX+1]);
void dijkstra(int n, int adj[MAX+1][MAX+1]);

int processInput1(const char* filename);
int processInput2(const char* filename);

#endif
