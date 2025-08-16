#include "filme.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Filme
{

    char identificadorFilme[11];
    char tituloFilme[101];
    TipoAssinatura restricaoAssinatura;
    TipoUsuario restricaoIdade;
    int anoDeLancamentoFilme;
    float notaMediaFilme;
    int duracaoFilme;
    char disponibilidadeIdioma[3];

} tFilme;

int getAnoLancamentoFilme(void *dado)
{
    tFilme *filme = (tFilme *)dado;
    return filme->anoDeLancamentoFilme;
}

char *getCodConteudoFilme(void *dado)
{
    tFilme *filme = (tFilme *)dado;
    return filme->identificadorFilme;
}

char *getTituloFilme(void *dado)
{
    tFilme *filme = (tFilme *)dado;
    return filme->tituloFilme;
}

int getDuracaoFilme(void *dado)
{
    tFilme *filme = (tFilme *)dado;
    return filme->duracaoFilme;
}

float getNotaMediaFilme(void *dado)
{
    tFilme *filme = (tFilme *)dado;
    return filme->notaMediaFilme;
}

TipoAssinatura getRestricaoAssinaturaFilme(void *dado)
{
    tFilme *filme = (tFilme *)dado;
    return filme->restricaoAssinatura;
}

TipoUsuario getRestricaoIdadeFilme(void *dado)
{
    tFilme *filme = (tFilme *)dado;
    return filme->restricaoIdade;
}

char getTipoFilme()
{
    return 'F';
}

void printaFilme(void *dado)
{
    tFilme *filme = (tFilme *)dado;
    int horas, minutos;
    converteMinutos(filme->duracaoFilme, &horas, &minutos);
    printf("FILME #%s; %s; %02d:%02d; %s; %d \n", filme->identificadorFilme, filme->tituloFilme, horas, minutos, descricaoIdioma(filme->disponibilidadeIdioma), filme->anoDeLancamentoFilme);
}

tFilme *criaFilme(char *linhaFilme)
{
    int i = 0;

    tFilme *filme = (tFilme *)malloc(sizeof(tFilme));

    char *token = strtok(linhaFilme, ";");

    while (token != NULL)
    {
        if (i == 0)
        {
            strcpy(filme->identificadorFilme, token);
        }
        else if (i == 1)
        {
            strcpy(filme->tituloFilme, token);
        }
        else if (i == 2)
        {
            filme->restricaoAssinatura = atoi(token);
        }
        else if (i == 3)
        {
            filme->restricaoIdade = atoi(token);
        }
        else if (i == 4)
        {
            filme->anoDeLancamentoFilme = atoi(token);
        }
        else if (i == 5)
        {
            filme->notaMediaFilme = atof(token);
        }
        else if (i == 6)
        {
            filme->duracaoFilme = atoi(token);
        }
        else if (i == 7)
        {
            strcpy(filme->disponibilidadeIdioma, token);
        }
        token = strtok(NULL, ";");
        i++;
    }
    return filme;
}

void liberaFilme(void *dado)
{
    free(dado);
}