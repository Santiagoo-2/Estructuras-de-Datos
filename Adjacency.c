#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===== Configuración del grafo ===== */
#define N 4  // número de vértices
const char LABELS[N] = {'A','B','C','D'};

/* Mapeo de etiqueta -> índice 0..N-1 */
int idx_of(char c){
    for(int i=0;i<N;i++) if(LABELS[i]==c) return i;
    return -1;
}

/* -------- Matriz de adyacencia (no dirigida) -------- */
void build_undirected_adj_matrix(int adj[N][N], const char edges[][2], int m){
    // limpia
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) adj[i][j]=0;
    // coloca aristas no dirigidas
    for(int k=0;k<m;k++){
        int u = idx_of(edges[k][0]);
        int v = idx_of(edges[k][1]);
        if(u==-1 || v==-1) continue;
        adj[u][v] = 1;
        adj[v][u] = 1;
    }
}

void print_matrix(int adj[N][N]){
    printf("\nAdjacency matrix (undirected) — order A,B,C,D\n    ");
    for(int j=0;j<N;j++) printf("%c ", LABELS[j]);
    printf("\n");
    for(int i=0;i<N;i++){
        printf("%c | ", LABELS[i]);
        for(int j=0;j<N;j++) printf("%d ", adj[i][j]);
        printf("\n");
    }
}

/* --------Lista de adyacencia (dirigido) -------- */
typedef struct Node{
    int v;
    struct Node* next;
} Node;

void add_edge_dir(Node* adj[], int u, int v){
    Node* p = (Node*)malloc(sizeof(Node));
    p->v = v; p->next = adj[u];
    adj[u] = p;
}

void build_directed_adj_list(Node* adj[], const char edges[][2], int m){
    for(int i=0;i<N;i++) adj[i]=NULL;
    for(int k=0;k<m;k++){
        int u = idx_of(edges[k][0]);
        int v = idx_of(edges[k][1]);
        if(u==-1 || v==-1) continue;
        add_edge_dir(adj, u, v);  // sólo u -> v
    }
}

void print_adj_list(Node* adj[]){
    printf("\nAdjacency list (directed)\n");
    for(int u=0; u<N; u++){
        printf("%c: ", LABELS[u]);
        Node* p = adj[u];
        if(!p) { printf("—"); }
        while(p){
            printf("%c", LABELS[p->v]);
            if(p->next) printf(", ");
            p = p->next;
        }
        printf("\n");
    }
}

void free_adj_list(Node* adj[]){
    for(int i=0;i<N;i++){
        Node* p = adj[i];
        while(p){ Node* q=p; p=p->next; free(q); }
        adj[i]=NULL;
    }
}

int main(void){
    // E = {(A,B), (A,C), (B,D)}
    const char undirected_edges[][2] = {{'A','B'},{'A','C'},{'B','D'}};
    const int M = sizeof(undirected_edges)/sizeof(undirected_edges[0]);

    // 1) Matriz no dirigida
    int mat[N][N];
    build_undirected_adj_matrix(mat, undirected_edges, M);
    print_matrix(mat);

    // 2) Lista dirigida (A->B, A->C, B->D)
    Node* list[N];
    build_directed_adj_list(list, undirected_edges, M);
    print_adj_list(list);
    free_adj_list(list);

    return 0;
}
