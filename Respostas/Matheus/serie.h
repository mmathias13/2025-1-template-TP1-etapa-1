#ifndef _SERIE_H
#define _SERIE_H

#include "util.h"

typedef struct Serie tSerie;


tSerie *criaSerie(char *linhaSerie);
void liberaSerie(void *dado);
char getTipoSerie();
int getAnoLancamentoSerie(void *dado);
char *getCodConteudoSerie(void *dado);
char *getTituloSerie(void *dado);
TipoAssinatura getRestricaoAssinaturaSerie(void *dado);
TipoUsuario getRestricaoIdadeSerie(void *dado);
int getDuracaoPorEpisodioSerie(void *dado);
int getNumeroEpisodiosSerie(void *dado);
float getNotaMediaSerie(void *dado);

#endif