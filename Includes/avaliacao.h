#ifndef _AVALIACAO_H
#define _AVALIACAO_H

typedef struct Avaliacao tAvaliacao;


/// @brief Função que cria um objeto do tipo tAvaliação*
/// @param cpf - CPF da pessoa que fez a avaliação
/// @param nota - A nota que a pessoa deu
/// @return O objeto avaliação criado
tAvaliacao* criaAvaliacao(char* cpf, int nota);


/// @brief Retorna a nota de uma avaliação
/// @param a 
/// @return A nota de uma avaliação
int getNotaAvaliacao(tAvaliacao *a);


/// @brief Retorna o CPF de quem fez aquela avaliação
/// @param a 
/// @return O CPF do responsável pela avaliação
char* getCpfAvaliacao(tAvaliacao *a);

/// @brief Função que libera a memória alocada para uma avaliação
/// @param avaliacao um ponteiro para uma variável do tipo tAvaliacao
void liberaAvaliacao(tAvaliacao *avaliacao);

#endif