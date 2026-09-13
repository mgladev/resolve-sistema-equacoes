#include <stdio.h>
#include <math.h>
#define EPSILON 1e-9

// Lê a Matriz Aumentada do Sistema
void recebe_matriz(int linhas, int colunas, double A[][colunas]){
    for(int i = 0; i<linhas; i++){
        for(int j = 0; j<colunas; j++){
            if(j == colunas -1){
                printf("Digite o termo independente da linha %d: ", i+1);
                scanf("%lf", &A[i][j]);
            } else {
                printf("Digite o coeficiente %d da linha %d: ", j+1, i+1);
                scanf("%lf", &A[i][j]);
            }
        }
    }
}

// Troca linhas que possuem pivô = 0
int troca_linha(int linhas, int colunas, int linha_pivo, double* pivo, double A[][colunas]){
    int l = -1;
    for(int i = linha_pivo+1; i<linhas; i++){
        if(fabs(A[i][linha_pivo]) > EPSILON){
            l = i;
            *pivo = A[i][linha_pivo];
            break;
        }
    }
    if(l != -1){
        for(int i = 0; i<colunas; i++){
            double temp = A[linha_pivo][i];
            A[linha_pivo][i] = A[l][i];
            A[l][i] = temp;
        }
        return 1; // teve como trocar
    }
    return 0; // não teve como trocar
}

// Zera as linhas abaixo do pivô por meio da terceira operação elementar
void zera_linha(int coluna, int colunas, double pivo, double a[], double b[]){
    double k = b[coluna]/pivo;
    for(int i = 0; i<colunas; i++){
        b[i] = b[i] - k*a[i];
    }
}

// Retorna o posto da matriz (quantidade de pivôs válidos encontrados) e escalona a Matriz Aumentada
int escalona_matriz_aumentada(int linhas, int colunas, double A[][colunas]){
    double pivo;
    int posto = 0, limite = (linhas < colunas-1) ? linhas : colunas-1;

    for(int i = 0; i<limite; i++){
        if(fabs(A[i][i]) > EPSILON){
            pivo = A[i][i];
        } else {
            int sucesso = troca_linha(linhas, colunas, i, &pivo, A);
            if(!sucesso) continue; // essa coluna não gerou pivô, não conta no posto
        }

        for(int j = i+1; j<linhas; j++){
            if(fabs(A[j][i]) > EPSILON){
                zera_linha(i, colunas, pivo, A[i], A[j]);
            }
        }
        posto++;
    }
    return posto;
}

void resolve_sistema(int linhas, int colunas, int posto, double A[][colunas]){
    int incognitas = colunas - 1;
    double solucao[incognitas];

    // Sistema Impossivel (SI)
    for(int i = 0; i<linhas; i++){
        int coef_zerados = 0;
        for(int j = 0; j<incognitas; j++){
            if(fabs(A[i][j]) < EPSILON) coef_zerados++;
        }
        if(coef_zerados == incognitas && fabs(A[i][colunas-1]) > EPSILON){
            printf("Sistema Impossivel (SI)\n");
            return;
        }
    }

    // Sistema Possível Indeterminado (SPI)
    if(posto < incognitas){
        printf("Sistema Possivel Indeterminado (SPI)\n");
        return;
    }

    // Sistema Possível Determinado (SPD)
    printf("Sistema Possivel Determinado (SPD)\n");
    for(int i = incognitas-1; i>-1; i--){
        double soma = 0;
        for(int j = i+1; j<incognitas; j++){
            soma += A[i][j]*solucao[j];
        }
        solucao[i] = (A[i][colunas-1]-soma)/A[i][i];
    }

    for(int i = 0; i<incognitas; i++){
        printf("x%d = %.4lf\n", i+1, solucao[i]);
    }
}