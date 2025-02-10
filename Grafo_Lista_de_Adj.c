#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int vertice;
    struct no* prox;
} NO;

typedef struct Grafo {
    NO** lista_de_adj;
    int vertices;
    int arestas;
} GRAFO;

GRAFO* criar_grafo(int numero_de_vertices) {
    GRAFO* grafo = (GRAFO*)malloc(sizeof(GRAFO));

    grafo->vertices = numero_de_vertices;
    grafo->arestas = 0;

    grafo->lista_de_adj = (NO**)malloc(numero_de_vertices * sizeof(NO*));

    for (int i = 0; i < numero_de_vertices; i++) {
        grafo->lista_de_adj[i] = NULL;
    }

    return grafo;
}

NO* criar_no(int vertice_conectado) {
    NO* novo_no = (NO*)malloc(sizeof(NO));

    novo_no->vertice = vertice_conectado;
    novo_no->prox = NULL;

    return novo_no;
}

void conectar_vertices(GRAFO* grafo, int V1, int V2) {
    if (V1 < 0 || V1 >= grafo->vertices || V2 < 0 || V2 >= grafo->vertices) {
        printf("Conexao mal sucedida, vertice(s) nao existente(s)!\n");
        return;
    }

    // Verifica se a conexão V1 -> V2 já existe
    NO* atual = grafo->lista_de_adj[V1];
    while (atual != NULL) {
        if (atual->vertice == V2) {
            printf("Conexao ja existente!\n");
            return;
        }
        atual = atual->prox;
    }

    // Cria um novo nó para V2 e insere no início da lista de V1
    NO* novo_1 = criar_no(V2);
    novo_1->prox = grafo->lista_de_adj[V1];
    grafo->lista_de_adj[V1] = novo_1;

    // Cria um novo nó para V1 e insere no início da lista de V2
    NO* novo_2 = criar_no(V1);
    novo_2->prox = grafo->lista_de_adj[V2];
    grafo->lista_de_adj[V2] = novo_2;

    grafo->arestas++;
    printf("Conexao bem sucedida!\n");
}

void liberar_grafo(GRAFO* grafo_liberado) {
    for (int i = 0; i < grafo_liberado->vertices; i++) {
        NO* atual = grafo_liberado->lista_de_adj[i];
        while (atual != NULL) {
            NO* aux = atual;
            atual = atual->prox;
            free(aux);
        }
    }
    free(grafo_liberado->lista_de_adj);
    free(grafo_liberado);
    printf("Grafo liberado da memoria!\n");
}

int main() {
    int V;
    printf("Digite o numero de vertices do grafo:\n");
    scanf("%d", &V);
    GRAFO* G = criar_grafo(V);

    while (1) {
        int opcao;
        printf("Deseja realizar uma conexao? 1(SIM) 2(NAO):\n");
        scanf("%d", &opcao);
        if (opcao == 2) {
            break;
        } else {
            int V1, V2;
            printf("Digite os dois vertices que deseja conectar (separados por espaco):\n");
            scanf("%d %d", &V1, &V2);

            conectar_vertices(G, V1, V2);
        }
    }
    liberar_grafo(G);

    return 0;
}
