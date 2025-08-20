#include "serie.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Serie{

    char identificadorSerie[11];
    char tituloSerie[101];
    TipoAssinatura restricaoAssinatura;
    TipoUsuario restricaoIdade;
    int anoDeLancamentoSerie;
    float notaMediaSerie;
    int duracaoPorEpisodioSerie;
    int numeroEpisodios;
    char disponibilidadeIdioma[3];

} tSerie;

tSerie *criaSerie(char *linhaSerie)
{
    int i = 0;

    tSerie *serie = (tSerie *)malloc(sizeof(tSerie));

    char *token = strtok(linhaSerie, ";");

    while (token != NULL)
    {
        if (i == 0)
        {
            strcpy(serie->identificadorSerie, token);
        }
        else if (i == 1)
        {
            strcpy(serie->tituloSerie, token);
        }
        else if (i == 2)
        {
            serie->restricaoAssinatura = atoi(token);
        }
        else if (i == 3)
        {
            serie->restricaoIdade = atoi(token);
        }
        else if (i == 4)
        {
            serie->anoDeLancamentoSerie = atoi(token);
        }
        else if (i == 5)
        {
            serie->duracaoPorEpisodioSerie = atoi(token);
        }
        else if (i == 6)
        {
            serie->numeroEpisodios = atoi(token);
        }
        else if (i == 7)
        {
            strcpy(serie->disponibilidadeIdioma, token);
        }
        token = strtok(NULL, ";");
        i++;
    }
    
    serie->notaMediaSerie = 0.0;
    return serie;
}

int getAnoLancamentoSerie(void *dado){
    tSerie *serie = (tSerie *)dado;
    return serie->anoDeLancamentoSerie;
}

char *getCodConteudoSerie(void *dado){
    tSerie *serie = (tSerie*)dado;
    return serie->identificadorSerie;
}

char *getTituloSerie(void *dado){
    tSerie *serie = (tSerie *)dado;
    return serie->tituloSerie;
}

TipoAssinatura getRestricaoAssinaturaSerie(void *dado){
    tSerie *serie = (tSerie *)dado;
    return serie->restricaoAssinatura;
}

TipoUsuario getRestricaoIdadeSerie(void *dado){
    tSerie *serie = (tSerie *)dado;
    return serie->restricaoIdade;
}

int getDuracaoPorEpisodioSerie(void *dado){
    tSerie *serie = (tSerie*)dado;
    return serie->duracaoPorEpisodioSerie;
}

int getNumeroEpisodiosSerie(void *dado){
    tSerie *serie = (tSerie *)dado;
    return serie->numeroEpisodios;
}

float getNotaMediaSerie(void *dado){
    tSerie *serie = (tSerie *)dado;
    return serie->notaMediaSerie;
}

char getTipoSerie(){
    return 'S';
}

void liberaSerie(void *dado)
{
    free(dado);
}