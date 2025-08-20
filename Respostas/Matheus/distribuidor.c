#include "distribuidor.h"
#include "conteudo.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Distribuidor
{

    //---Informações Gerais---
    char nomeDistribuidor[101];
    char identificadorDistribuidor[19]; // CNPJ
    char telefone[15];
    char endereco[151];
    char nomeUsuario[16];
    char senha[21];

    //---Específicas Distribuidores---
    int numeroProdutosOfertados;
    tConteudo **listaConteudosOfertados;
    int qtdOfertados;

} tDistribuidor;

tDistribuidor *criaDistribuidor(char *linhaDados)
{

    int i = 0;
    tDistribuidor *distribuidor = (tDistribuidor *)malloc(sizeof(tDistribuidor));
    char *token = strtok(linhaDados, ";");
    while (token != NULL)
    {
        if (i == 0)
        {
            strcpy(distribuidor->nomeDistribuidor, token);
        }
        else if (i == 1)
        {
            strcpy(distribuidor->identificadorDistribuidor, token);
        }
        else if (i == 2)
        {
            strcpy(distribuidor->telefone, token);
        }
        else if (i == 3)
        {
            strcpy(distribuidor->endereco, token);
        }
        else if (i == 4)
        {
            strcpy(distribuidor->nomeUsuario, token);
        }
        else if (i == 5)
        {
            strcpy(distribuidor->senha, token);
        }
        token = strtok(NULL, ";");
        i++;
    }
    distribuidor->numeroProdutosOfertados = 0;
    distribuidor->qtdOfertados = 0;
    distribuidor->listaConteudosOfertados = NULL;
    return distribuidor;
}

void liberaDistribuidor(tDistribuidor* distribuidor) {
    if (distribuidor == NULL) {
        return;
    }

    for (int i = 0; i < distribuidor->qtdOfertados; i++) {
        liberaConteudo(distribuidor->listaConteudosOfertados[i]);
    }

    if (distribuidor->listaConteudosOfertados != NULL) {
        free(distribuidor->listaConteudosOfertados);
    }

    free(distribuidor);
}

void adicionaConteudoOfertado(tDistribuidor* distribuidor, tConteudo* conteudo) {
    if (distribuidor == NULL || conteudo == NULL) {
        return;
    }
    
    distribuidor->qtdOfertados++;
    distribuidor->numeroProdutosOfertados++;
    distribuidor->listaConteudosOfertados = realloc(distribuidor->listaConteudosOfertados, distribuidor->qtdOfertados * sizeof(tConteudo*));
    distribuidor->listaConteudosOfertados[distribuidor->qtdOfertados - 1] = conteudo;
}

char* getCnpjDistribuidor(tDistribuidor* distribuidor) {
    if (distribuidor == NULL) {
        return NULL;
    }
    return distribuidor->identificadorDistribuidor;
}