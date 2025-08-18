#ifndef _JOGO_H
#define _JOGO_H

#include "util.h"

typedef struct Jogo tJogo;

tJogo *criaJogo(char *linhaJogo);
void liberaJogo(void *dado);
char getTipoJogo(); // Assumindo que você criará esta função, que retorna 'J'
char *getCodJogo(void *dado);
char *getTituloJogo(void *dado);
TipoAssinatura getRestricaoAssinaturaJogo(void *dado);
TipoUsuario getRestricaoIdadeJogo(void *dado);
int getAnoDeLancamentoJogo(void *dado);
float getNotaMediaJogo(void *dado);
int getDuracaoEstimadaJogo(void *dado);
char *getCategoriaJogo(void *dado);
char *getDesenvolvedoraJogo(void *dado);

#endif // _JOGO_H