#include "jogo.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Jogo
{
    char identificadorJogo[11];
    char tituloJogo[101];
    TipoAssinatura restricaoAssinatura;
    TipoUsuario restricaoIdade;
    int anoDeLancamentoJogo;
    float notaMediaJogo;
    int duracaoEstimadaJogo;
    char categoria[16];
    char desenvolvedora[21];

} tJogo;

tJogo *criaJogo(char *linhaJogo)
{
    int i = 0;
    tJogo *jogo = (tJogo *)malloc(sizeof(tJogo));
    char *token = strtok(linhaJogo, ";");

    while (token != NULL)
    {
        if (i == 0)
        {
            strcpy(jogo->identificadorJogo, token);
        }
        else if (i == 1)
        {
            strcpy(jogo->tituloJogo, token);
        }
        else if (i == 2)
        {
            jogo->restricaoAssinatura = atoi(token);
        }
        else if (i == 3)
        {
            jogo->restricaoIdade = atoi(token);
        }
        else if (i == 4)
        {
            jogo->anoDeLancamentoJogo = atoi(token);
        }
        else if (i == 5)
        {
            jogo->duracaoEstimadaJogo = atoi(token);
        }
        else if (i == 6)
        {
            strcpy(jogo->categoria, token);
        }
        else if (i == 7)
        {
            strcpy(jogo->desenvolvedora, token);
        }
        token = strtok(NULL, ";");
        i++;
    }

    jogo->notaMediaJogo = 0.0;
    return jogo;
}

char *getCodJogo(void *dado){
    tJogo *jogo = (tJogo*)dado;
    return jogo->identificadorJogo;
}

char *getTituloJogo(void *dado){
    tJogo *jogo = (tJogo*)dado;
    return jogo->tituloJogo;
}

TipoAssinatura getRestricaoAssinaturaJogo(void *dado){
    tJogo *jogo = (tJogo*)dado;
    return jogo->restricaoAssinatura;
}

TipoUsuario getRestricaoIdadeJogo(void *dado){
    tJogo *jogo = (tJogo*)dado;
    return jogo->restricaoIdade;
}

int getAnoLancamentoJogo(void *dado){
    tJogo *jogo = (tJogo*)dado;
    return jogo->anoDeLancamentoJogo;
}

float getNotaMediaJogo(void *dado){
    tJogo *jogo = (tJogo*)dado;
    return jogo->notaMediaJogo;
}

int getDuracaoEstimadaJogo(void *dado){
    tJogo *jogo = (tJogo*)dado;
    return jogo->duracaoEstimadaJogo;
}

char *getCategoriaJogo(void *dado){
    tJogo *jogo = (tJogo*)dado;
    return jogo->categoria;
}

char *getDesenvolvedoraJogo(void *dado){
    tJogo *jogo = (tJogo*)dado;
    return jogo->desenvolvedora;
}

char getTipoJogo(){
    return 'J';
}

void liberaJogo(void *dado){
    free(dado);
}