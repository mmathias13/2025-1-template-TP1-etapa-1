#ifndef _DISTRIBUIDOR_H
#define _DISTRIBUIDOR_H

#include "conteudo.h"

typedef struct Distribuidor tDistribuidor;

tDistribuidor* criaDistribuidor(char* linhaDados);
void liberaDistribuidor(tDistribuidor* distribuidor);
void adicionaConteudoOfertado(tDistribuidor* distribuidor, tConteudo* conteudo);
char* getCnpjDistribuidor(tDistribuidor* distribuidor);

#endif