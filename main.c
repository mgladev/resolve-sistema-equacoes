#include <stdio.h>
#include "algebra.h"

int main(){
    int linhas, incognitas;
    printf("Digite a quantidade de linhas e incognitas: ");
    scanf("%d %d", &linhas, &incognitas);

    double A[linhas][incognitas + 1];

    // Lê a Matriz Aumentada do Sistema
    recebe_matriz(linhas, incognitas +1, A);

    // Escalona a Matriz Aumentada "ignorando" a última linha, guarda o posto da matriz na variável "posto"
    int posto = escalona_matriz_aumentada(linhas, incognitas+1, A);

    // Dá a Solução do Sistema
    resolve_sistema(linhas, incognitas+1, posto, A);

    return 0;
}