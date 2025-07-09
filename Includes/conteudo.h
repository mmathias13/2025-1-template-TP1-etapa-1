#ifndef _CONTEUDO_H
#define _CONTEUDO_H

#include "util.h"
#include "avaliacao.h"
typedef struct Conteudo tConteudo;

typedef char *(*func_ptr_codConteudo)(void *dado);
typedef char *(*func_ptr_titulo)(void *dado);
typedef int (*func_ptr_anoLancamento)(void *dado);
typedef float (*func_ptr_notaMedia)(void *dado);
typedef int (*func_ptr_duracao)(void *dado);
typedef void (*func_ptr_printaConteudo)(void *dado);
typedef void (*func_ptr_liberaConteudo)(void *dado);
typedef TipoAssinatura (*func_ptr_restricaoConteudo)(void *dado);
typedef TipoUsuario (*func_ptr_restricaoIdade)(void *dado);
typedef char (*func_ptr_tipoConteudo)();


TipoAssinatura getRestricaoConteudo(tConteudo *conteudo);
void printaConteudo(tConteudo *conteudo);
char getTipoConteudo(tConteudo *conteudo);
int getDuracaoConteudo(tConteudo *conteudo);
char *getCodConteudo(tConteudo *conteudo);
TipoUsuario getRestricaoIdade(tConteudo *conteudo);
void inserirAvaliacaoConteudo(tConteudo *c, tAvaliacao *a);
void printaConteudoComNota(tConteudo *conteudo, char* cpf);
tAvaliacao* buscaNotaAvaliacao(tConteudo *conteudo, char* cpf);
int getQtdAvaliacoes(tConteudo *conteudo);
tAvaliacao* getAvaliacaoPosicao(tConteudo *conteudo, int pos);
char* getTituloConteudo(tConteudo *conteudo);
float getNotaMediaConteudo(tConteudo *conteudo);
void liberaConteudo(tConteudo *conteudo);
void* getDadoConteudo(tConteudo *conteudo);

#endif