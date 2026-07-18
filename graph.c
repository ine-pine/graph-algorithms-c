#include "graph.h"

/****************************************
 * Utility: Queue for BFS
 ****************************************/

void initQueue(Queue* q) { q->front = q->rear = 0; }
int isEmpty(Queue* q) { return q->front == q->rear; }
void enqueue(Queue* q, int x) { q->data[q->rear++] = x; }
int dequeue(Queue* q) { return q->data[q->front++]; }

/****************************************
 * DFS
 ****************************************/
void dfsUtil(int v, int n, int adj[MAX+1][MAX+1], int visited[MAX+1]) {
    visited[v] = 1;
    printf("%d", v);

    for (int i = 1; i <= n; i++) {
        if (adj[v][i] == 1 && !visited[i]) {
            printf(" - ");
            dfsUtil(i, n, adj, visited);
        }
    }
}

void dfs(int n, int adj[MAX+1][MAX+1]) {
    int visited[MAX+1] = {0};
    dfsUtil(1, n, adj, visited);
    printf("\n");
}

/****************************************
 * BFS
 ****************************************/
void bfs(int n, int adj[MAX+1][MAX+1]) {
    int visited[MAX+1] = {0};
    Queue q; initQueue(&q);

    enqueue(&q, 1);
    visited[1] = 1;

    int first = 1;
    while (!isEmpty(&q)) {
        int v = dequeue(&q);
        if (!first) printf(" - ");
        printf("%d", v);
        first = 0;

        for (int i = 1; i <= n; i++) {
            if (adj[v][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(&q, i);
            }
        }
    }
    printf("\n");
}

/****************************************
 * Dijkstra
 ****************************************/
void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d", j);
        return;
    }
    printPath(parent, parent[j]);
    printf(" - %d", j);
}

void dijkstra(int n, int adj[MAX+1][MAX+1]) {
    int dist[MAX+1], parent[MAX+1], visited[MAX+1] = {0};

    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[1] = 0;

    for (int c = 1; c <= n; c++) {
        int u = -1, min = INF;

        for (int i = 1; i <= n; i++)
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }

        if (u == -1) break; // 남은 정점이 모두 도달 불가능 -> 더 이상 확정할 정점 없음

        visited[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (adj[u][v] > 0) {
                int nd = dist[u] + adj[u][v];
                if (nd < dist[v]) {
                    parent[v] = u;
                    dist[v] = nd;
                }
            }
        }
    }

    printf("시작점: 1\n");

    for (int i = 2; i <= n; i++) {
        printf("정점 [%d]: ", i);
        printPath(parent, i);
        if (dist[i] == INF)
            printf(", 길이: 도달 불가\n");
        else
            printf(", 길이: %d\n", dist[i]);
    }
}

/****************************************
 * Input Parsing: input1 (DFS/BFS)
 ****************************************/
int processInput1(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) { printf("%s not found.\n", filename); return 0; }

    printf("1. 그래프 탐방 수행 결과\n\n");

    char line[300];
    int graphCount = 0;

    while (fgets(line, sizeof(line), fp)) {
        int n;
        if (sscanf(line, "%d", &n) != 1) continue;
        if (n > 100) return 0; // 안전장치
        graphCount++;
        int adj[MAX+1][MAX+1] = {0};

        for (int i = 1; i <= n; i++) {
            if (!fgets(line, sizeof(line), fp)) return 0;

            // 노드 번호 순서가 실제 입력과 일치하는지 체크
            int nodeCheck;
            char* p = line;

            if (sscanf(p, "%d", &nodeCheck) != 1) {
                printf("입력 오류: 노드 번호를 읽을 수 없습니다. (i=%d)\n", i);
                return 0;
            }
            if (nodeCheck != i) {
                printf("입력 오류: 노드 번호가 순서대로 주어지지 않았습니다. (기대: %d, 입력: %d)\n",
                    i, nodeCheck);
                return 0;
            }

            // nodeCheck 숫자 건너뛰기
            while (*p != ' ' && *p != '\0') p++;
            while (*p == ' ') p++;

            int to;
            while (sscanf(p, "%d", &to) == 1) {
                adj[i][to] = 1;

                while (*p != ' ' && *p != '\0') p++;
                while (*p == ' ') p++;
            }
        }


        printf("그래프 [%d]\n----------------------------\n", graphCount);
        printf("깊이 우선 탐색\n");
        dfs(n, adj);
        printf("너비 우선 탐색\n");
        bfs(n, adj);
        printf("============================\n\n");
    }

    fclose(fp);
    return 1;
}


/****************************************
 * Input Parsing: input2 (Dijkstra)
 ****************************************/
int processInput2(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) { printf("%s not found.\n", filename); return 0; }

    printf("2. 최단 경로 구하기 수행 결과\n\n");

    char line[300];
    int graphCount = 0;

    while (fgets(line, sizeof(line), fp)) {
        int n;
        if (sscanf(line, "%d", &n) != 1) continue;
        if (n > 100) return 0; // 안전장치
        
        graphCount++;
        int adj[MAX+1][MAX+1] = {0};

        for (int i = 1; i <= n; i++) {
            if (!fgets(line, sizeof(line), fp)) return 0;

            int node, to, w;
            char* p = line;

            if (sscanf(p, "%d", &node) != 1) {
                printf("입력 오류: 노드 번호를 읽을 수 없습니다. (i=%d)\n", i);
                return 0;
            }

            if (node != i) {
                printf("입력 오류: 노드 번호가 순서대로 주어지지 않았습니다. (기대: %d, 입력: %d)\n",
                    i, node);
                return 0;
            }

            // node 번호 건너뛰기
            while (*p != ' ' && *p != '\0') p++;
            while (*p == ' ') p++;

            while (sscanf(p, "%d %d", &to, &w) == 2) {
                if (w < 0) {
                    printf("입력 오류: 음수 가중치는 허용되지 않습니다.\n");
                    return -1;
                }

                adj[node][to] = w;

                // 다음 숫자로 이동
                while (*p != ' ' && *p != '\0') p++;
                while (*p == ' ') p++;
                while (*p != ' ' && *p != '\0') p++;
                while (*p == ' ') p++;
            }
        }


        printf("그래프 [%d]\n----------------------------\n", graphCount);
        dijkstra(n, adj);
        printf("=========================\n\n");
    }

    fclose(fp);
    return 1;
}
