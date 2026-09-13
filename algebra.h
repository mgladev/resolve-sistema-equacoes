#pragma once

// Assinatura de todas as funções utilizadas na main.c

void recebe_matriz(int linhas, int colunas, double A[][colunas]);

int troca_linha(int linhas, int colunas, int linha_pivo, double* pivo, double A[][colunas]);

void zera_linha(int coluna, int colunas, double pivo, double a[], double b[]);

int escalona_matriz_aumentada(int linhas, int colunas, double A[][colunas]);

void resolve_sistema(int linhas, int colunas, int posto, double A[][colunas]);