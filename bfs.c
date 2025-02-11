 //implementação de busca em largura 

#include <stdio.h>
#include <stdlib.h>
#define TAMANHO 40

typedef struct no {
    int vertice;
    struct no* prox;
} NO;

/*
Vizitado é onde será guardado, todos os nós que 
foram vizitados na busca em largura
*/

typedef struct Grafo {
    NO** lista_de_adj;
    int vertices;
    int arestas;
    int* vizitados;
} GRAFO;

GRAFO* criar_grafo(int numero_de_vertices) {
    GRAFO* grafo = (GRAFO*)malloc(sizeof(GRAFO));
    grafo->vertices = numero_de_vertices;
    grafo->arestas = 0;
    grafo->lista_de_adj = (NO**)malloc(numero_de_vertices * sizeof(NO*));
    grafo->vizitados = malloc (numero_de_vertices * sizeof(int));
    for (int i = 0; i < numero_de_vertices; i++) {
        grafo->lista_de_adj[i] = NULL;
        grafo->vizitados[i] = 0;
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

void imprimir_grafo(GRAFO* grafo){
    int v;
    printf ("Grafo:\n");
    for (v = 0; v < grafo->vertices; v++){
        NO* aux = grafo -> lista_de_adj[v];
        printf("Vertice %d: ", v);
        while (aux){
            printf ("%d -> ", aux -> vertice);
            aux = aux -> prox;
        }
    }
    printf ("\n");
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

/*
            STRUCT FILA
"int primeiro" é a frente da fila, é de onde
os valores sairão primeiro.
"int ultimo" é a traseira da fila, é de onde
os valores novos serão colocados.

Portanto, eles marcam o índice da fila onde irei 
adicionar ou remover, se eu for adicionar, adiciono
no índice primeiro, caso contrário, removo do índice
ultimo
*/

typedef struct fila{
    int itens[TAMANHO];
    int primeiro; //frente da fila
    int ultimo; //ultimo da fila
}FILA;

/*
            CRIAÇÃO DA FILA
Essa função cria um ponteiro do tipo fila
denominado "F". Aloca espaço de memória do
espaço da estrutura FILA para esse ponteiro

Feito isso, a função atribui valor -1 para a variavel primeiro
e para variável último Isso é feito justamente pois inicialmente
não tem nenhum elemento na fila

Ao final, a função retorna o endereço de memória da fila criada
*/

FILA* criar_fila (){
    FILA* F = (FILA*)malloc(sizeof(FILA));
    F -> primeiro = -1;
    F -> ultimo = -1;
    
    return F;
}

/*
            VERIFICAR SE É VAZIA
Essa função recebe como argumento a fila criada
Se o último índice da fila for -1, ela retorna 1
*/

int ehVazia(FILA* F){
    if (F -> ultimo == -1)
        return 1;
    else 
        return 0;
}

/*
            ADICIONAR NA FILA:
Essa função é responsável por adicionar um elemento na fila.
prieiro ela verifica se ela está cheia. Se o índice último 
for igual ao tamanho da fila - 1 (termina no índice 39),
significa que ela está cheia.

Caso contrário, a função confere se a fila está vazia. Se
o índice frente for -1, significa que ela está vazia e, dessa
forma, muda o índice para 0 (já que um elemento foi adicionado)

Ao adicionar um elemento, incrementa a variável último. Nos
próximos passos, se a fila já estiver vazia, incremento apenas
o último índice

Logo depois valor é adicionado nessa última posição que foi 
incrementada
*/

void adicionar_na_fila(FILA* F, int valor){
    if (F -> ultimo == TAMANHO - 1){
        printf ("A fila está cheia!");
    }
    else{
        if (F -> primeiro == -1){
            F -> primeiro = 0;
        }
        F -> ultimo++;
        F -> itens[F -> ultimo] = valor;
    }
}

/*
            RETIRAR DA FILA:
Essa função remove os elementos que estão na frente da 
fila.
A função verifica primeiro se a fila está vazia
Caso contrário, é atribuido a variavel item, o primeiro
item da fila. Feito isso, o índice da frente da fila
aumenta
Caso o índice frente fique maior que o índice último,
sinal que a fila ficou vazia, e por isso, os índices
são resetados para -1

Ao final, a função retorna item, que foi o índice da fila
que foi removido
*/

int remover_da_fila(FILA* F){
    int item;
    if (ehVazia(F)){
        printf ("Fila está vazia");
        item = -1;
    }
    else{
        item = F -> itens[F->primeiro];
        F -> primeiro++;
        if (F -> primeiro > F -> ultimo){
            printf("Resetando fila");
            F -> primeiro = F -> ultimo = -1;
        }
    }
    return item;
}

/*
            IMPRIMIR FILA: 
Essa função percorre a fila e imprime ela
*/
void imprimir_fila(FILA* F){
    int i = F -> primeiro;

    if (ehVazia(F)){
        printf ("Fila Está vazia\n");
    }
    else{
        printf ("A Fila contém:\n");
        for (i = F -> primeiro; i < F -> ultimo; i++){
            printf ("%d ", F -> itens[i]);
        }
    }
}

/*
            BUSCA EM LARGURA
*/

void busca_em_largura (GRAFO* grafo, int vertice_inicial){
    FILA* F = criar_fila();

    grafo -> vizitados[vertice_inicial] = 1;
    adicionar_na_fila(F, vertice_inicial);

    while(!ehVazia(F)){
        imprimir_fila(F);
        int vertice_atual = remover_da_fila(F);
        printf ("Visitado %d\n", vertice_atual);

        NO* aux = grafo -> lista_de_adj[vertice_atual];

        while (aux){
            int vertice_adj = aux -> vertice;

            if(grafo -> vizitados[vertice_adj] == 0){
                grafo -> vizitados[vertice_adj] = 1;
                adicionar_na_fila(F, vertice_adj);
            }
            aux = aux -> prox;
        }
    }
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

    imprimir_grafo(G);

    busca_em_largura(G, 0);

    liberar_grafo(G);
    return 0;
}
