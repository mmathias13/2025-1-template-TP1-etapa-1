#ifndef _AVALIACAO_H
#define _AVALIACAO_H

typedef struct Avaliacao tAvaliacao;

tAvaliacao* criaAvaliacao(char* cpf, int nota);
int getNotaAvaliacao(tAvaliacao *a);
char* getCpfAvaliacao(tAvaliacao *a);



#endif