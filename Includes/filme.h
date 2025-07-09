#ifndef _FILME_H
#define _FILME_H

#include "util.h"

typedef struct Filme tFilme;

int getAnoLancamentoFilme(void *dado);
char* getCodConteudoFilme(void *dado);
char* getTituloFilme(void *dado);
int getDuracaoFilme(void *dado);
float getNotaMediaFilme(void *dado);
void printaFilme(void *dado);
tFilme* criaFilme(char *linhaFilme);
TipoAssinatura getRestricaoAssinaturaFilme(void *dado);
char getTipoFilme();
TipoUsuario getRestricaoIdadeFilme(void *dado);
void liberaFilme(void *dado);

#endif