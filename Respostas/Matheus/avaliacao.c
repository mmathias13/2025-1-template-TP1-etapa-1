#include "avaliacao.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Avaliacao
{

    char cpf[15];
    int nota;

} tAvaliacao;

tAvaliacao *criaAvaliacao(char *cpf, int nota)
{
    tAvaliacao *avaliacao = (tAvaliacao*) malloc(sizeof(tAvaliacao));

    if (avaliacao == NULL)
    {
        printf("Erro na alocação de memória para avaliação!\n");
        exit(1);
    }

    strcpy(avaliacao->cpf, cpf);
    avaliacao->nota = nota;

    return avaliacao;
}

int getNotaAvaliacao(tAvaliacao *a){
    return a->nota;
}

char* getCpfAvaliacao(tAvaliacao *a){
    return a->cpf;
}

void liberaAvaliacao(tAvaliacao *avaliacao){
    free(avaliacao);
}
