/*FELIPE FREITAS D' ELIA
PROCESSO SELETIVO - CODELAB 2024*/

#include <stdio.h>
#include <string.h>

int eh_palindromo(char sequencia[], int inicio, int fim) {
    while (inicio < fim) {
        if (sequencia[inicio] != sequencia[fim]) {
            return 0;
        }
        inicio++;
        fim--;
    }
    return 1;
}

void encontra_maior_palindromo(char sequencia[], int *inicio_palindromo, int *fim_palindromo, int quantidade) {

    int tamanho_maximo = 0;
    int tamanho_palindromo;

    for (int i = 0; i < quantidade; i++) {

        for (int j = i; j < quantidade; j++) {
            if (eh_palindromo(sequencia, i, j)) {
                tamanho_palindromo = j - i + 1;

                if (tamanho_palindromo > tamanho_maximo) {
                    tamanho_maximo = tamanho_palindromo;
                    *inicio_palindromo = i;
                    *fim_palindromo = j;
                }
            }
        }
    }
}

int main() {
    char sequencia[1000];
    int inicio_palindromo = 0, fim_palindromo = 0;
    int quantidade = 0;

    fgets(sequencia, sizeof(sequencia), stdin);

    for (int i = 0; i < 1000; i++) {
        if (sequencia[i] == '\n') {
            sequencia[i] = '\0';
            break;
        }
        quantidade++;
    }
    encontra_maior_palindromo(sequencia, &inicio_palindromo, &fim_palindromo, quantidade);

    printf("\nO maior palindromo e: ");
    for (int i = inicio_palindromo; i <= fim_palindromo; i++) {
        printf ("%c", sequencia[i]);
    }
    printf("\n");

    return 0;
}
