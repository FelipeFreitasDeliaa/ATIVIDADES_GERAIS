// Nome: João Pedro Soldera Snabaitis Markues
// RA: 176531
 
#include <stdio.h>
#include <stdlib.h>
 
typedef struct grafo {
    int n_vert;
    int **matriz;
} Grafo;
 
Grafo *inicializa(int n_vert) { 
    Grafo *g = malloc(sizeof(Grafo));
    g->n_vert = n_vert;
    g->matriz = malloc(n_vert * sizeof(int*));
 
    for (int i = 0; i< n_vert; i++) { // cria coluna matriz
        g->matriz[i] = malloc(n_vert * sizeof(int));
    }
 
    for (int i = 0; i < n_vert; i++) { // inicializa a matriz com 0 em todas as posicoes
        for (int j = 0; j < n_vert; j++) {
            g->matriz[i][j] = 0;
        }
    }
    return g;
}
 
void adiciona_aresta(Grafo *g, int x, int y) {
    g->matriz[x][y] = 1;
    g->matriz[y][x] = 1;
}
 
int dfs(Grafo *g, int x, int y, int *visitado) { // busca em profundidade
    if (x == y) return 1;
 
    visitado[x] = 1;
    for (int i = 0; i < g->n_vert; i++) {
        if (g->matriz[x][i] == 1 && !visitado[i]) {
            if (dfs(g, i, y, visitado)) return 1;
        }
    }
    return 0;
}
 
int caminho(Grafo *g, int x, int y) { // usa o dfs para verificacao de caminho
    int *visitado = malloc(g->n_vert * sizeof(int));
    for (int i = 0; i < g->n_vert; i++) {
        visitado[i] = 0;
    }
    int resposta = 0;
 
    if (dfs(g, x, y, visitado)) {
        resposta = 1;
    }
 
    free(visitado);
    return resposta;
}
 
int grauMin(Grafo *g) {
    int quantidade[g->n_vert];
    for (int i = 0; i < g->n_vert; i++) {
        int contador = 0;
        for (int j = 0; j < g->n_vert; j++) {
            if (g->matriz[i][j] == 1) contador ++;
        }
        quantidade[i] = contador;
    }
 
    int menor = quantidade[0];
    for (int i = 1; i < g->n_vert; i++) {
        if (quantidade[i] < menor) menor = quantidade[i];
    }
    for (int i = 0; i < g->n_vert; i++) {
        if (quantidade[i] == menor) return i;
    }
}
 
int grauMax(Grafo *g) {
    int quantidade[g->n_vert]; 
    for (int i = 0; i < g->n_vert; i++) {
        int contador = 0;
        for (int j = 0; j < g->n_vert; j++) {
            if (g->matriz[i][j] == 1) contador ++;
        }
        quantidade[i] = contador;
    }
 
    int maior = quantidade[0];
    for (int i = 1; i < g->n_vert; i++) {
        if (quantidade[i] > maior) maior = quantidade[i];
    }
    for (int i = 0; i < g->n_vert; i++) {
        if (quantidade[i] == maior) return i;
    }
}
 
void desaloca(Grafo *g) {
    for (int i = 0; i < g->n_vert; i++) { // libera colunas
        free(g->matriz[i]);
    }
    free(g->matriz); // libera vetor para inteiros
    free(g); // libera estrutura do grafo
}
 
int main() {
    int n_vert, n_ares; // leitura de vertices, arestas. cria grafo
    scanf("%d", &n_vert);
    scanf("%d", &n_ares);
    Grafo *g = inicializa(n_vert);
 
    for (int i = 0; i < n_ares; i++) { // cria arestas
        int x, y;
        scanf("%d", &x);
        scanf("%d", &y);
        adiciona_aresta(g, x, y);
    }
 
    int v1, v2; // leitura de vertices para verificar caminho
    scanf("%d", &v1);
    scanf("%d", &v2);
 
    printf("%d ", caminho(g, v1, v2));
    printf("%d ", grauMin(g));
    printf("%d", grauMax(g));
 
    desaloca(g);
    return 0;
}