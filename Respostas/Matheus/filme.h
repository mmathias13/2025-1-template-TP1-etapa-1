#ifndef _FILME_H
#define _FILME_H

#include "util.h"

typedef struct Filme tFilme;

/// @brief Retorna o ano de lançamento de um filme
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme*
/// @return O ano de lançamento do filme
int getAnoLancamentoFilme(void *dado);

/// @brief Retorna o codigo (id único) de um filme
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme*
/// @return O codigo (id único) do filme
char* getCodConteudoFilme(void *dado);

/// @brief Retorna o título de um filme
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme*
/// @return O título do filme
char* getTituloFilme(void *dado);

/// @brief Retorna a duração de um filme
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme*
/// @return A duração do filme
int getDuracaoFilme(void *dado);

/// @brief Retorna a nota média de um filme
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme*
/// @return A nota média do filme
float getNotaMediaFilme(void *dado);

/// @brief Função que imprime as informações de um filme conforme especificação do trabalho
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme*
void printaFilme(void *dado);


/// @brief Cria uma variável do tipo tFilme
/// @param linhaFilme - A string lida do teclado com as informações de um filme (sem o F)
/// @return O objeto criado
tFilme* criaFilme(char *linhaFilme);

/// @brief Retorna o tipo de assinatura de um filme
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme*
/// @return O tipo da assinatura do filme (olhar util.h/.c)
TipoAssinatura getRestricaoAssinaturaFilme(void *dado);

/// @brief Retorna o tipo de um filme
/// @return o caractere usado para representar um filme: 'F'
char getTipoFilme();

/// @brief Retorna o tipo do usuario que pode assistir ao filme
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme*
/// @return O tipo do usuario que pode assistir ao filme (olhar util.h/.c)
TipoUsuario getRestricaoIdadeFilme(void *dado);

/// @brief Função que libera a memória alocada dinamicamente para armazenar um filmea
/// @param dado Um ponteiro para um dado genérico, que deve ser convertido para tFilme* e posteriormente liberado
void liberaFilme(void *dado);

#endif