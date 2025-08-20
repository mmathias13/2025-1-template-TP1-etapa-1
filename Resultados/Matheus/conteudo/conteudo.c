#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "avaliacao.h"
#include "conteudo.h"

struct Conteudo
{
    void *dado; // O ponteiro para o tFilme, tSerie ou tJogo

    // A lista de 'botões programados' (ponteiros de função)
    func_ptr_codConteudo codConteudo;
    func_ptr_titulo titulo;
    func_ptr_anoLancamento anoLancamento;
    func_ptr_notaMedia notaMedia;
    func_ptr_duracao duracao;
    func_ptr_printaConteudo printaConteudo;
    func_ptr_restricaoConteudo restricaoConteudo;
    func_ptr_tipoConteudo tipoConteudo;
    func_ptr_restricaoIdade restricaoIdade;
    func_ptr_liberaConteudo liberaConteudo;

    // A lista de avaliações
    tAvaliacao **avaliacoes;
    int qtdAvaliacoes;
};

// Vários callbacks
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

/// @brief Função que cria uma variável do tipo conteúdo. Olhar os tipos dos callbacks acima
/// @param dado Um ponteiro para um objeto genérico (Filme, Série ou Jogo)
/// @param anoLancamento Um callback para a função que retorna o ano de lançamento do conteúdo
/// @param codConteudo Um callback para a função que retorna o codigo do conteúdo
/// @param notaMedia Um callback para a função que retorna a nota media do conteúdo
/// @param titulo Um callback para a função que retorna o titulo do conteúdo
/// @param duracao Um callback para a função que retorna a duracao do conteúdo
/// @param printaConteudo Um callback para a função que imprime o conteúdo
/// @param restricaoConteudo Um callback para a função que retorna restricao do conteudo (Assinatura)
/// @param tipoConteudo Um callback para a função que retorna o tipo do conteudo
/// @param restricaoIdade Um callback para a função que retorna restricao de idade do conteudo
/// @param liberaConteudo Um callback para a função que libera o conteúdo
/// @return Uma variável do tipo tConteudo* que armazena os parâmetros listados
tConteudo *criaConteudo(void *dado,
                        func_ptr_anoLancamento anoLancamento,
                        func_ptr_codConteudo codConteudo,
                        func_ptr_notaMedia notaMedia,
                        func_ptr_titulo titulo,
                        func_ptr_duracao duracao,
                        func_ptr_printaConteudo printaConteudo,
                        func_ptr_restricaoConteudo restricaoConteudo,
                        func_ptr_tipoConteudo tipoConteudo,
                        func_ptr_restricaoIdade restricaoIdade,
                        func_ptr_liberaConteudo liberaConteudo)
{
    tConteudo *conteudo = (tConteudo *)malloc(sizeof(tConteudo));
    conteudo->dado = dado;
    conteudo->anoLancamento = anoLancamento;
    conteudo->codConteudo = codConteudo;
    conteudo->notaMedia = notaMedia;
    conteudo->titulo = titulo;
    conteudo->duracao = duracao;
    conteudo->printaConteudo = printaConteudo;
    conteudo->restricaoConteudo = restricaoConteudo;
    conteudo->tipoConteudo = tipoConteudo;
    conteudo->restricaoIdade = restricaoIdade;
    conteudo->liberaConteudo = liberaConteudo;
    conteudo->avaliacoes = NULL;
    conteudo->qtdAvaliacoes = 0;

    return conteudo;
}

/// @brief Retorna o tipo da assinatura necessária para assistir um conteúdo (olhar util.h/.c)
/// @param conteudo - Um ponteiro para um conteúdo
/// @return o tipo da assinatura necessária para assistir um conteúdo
TipoAssinatura getRestricaoConteudo(tConteudo *conteudo){
    return conteudo->restricaoConteudo(conteudo->dado);
}

/// @brief Imprime as informações de um conteúdo de acordo com o especificado (especificação/Casos)
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
void printaConteudo(tConteudo *conteudo){
    conteudo->printaConteudo(conteudo->dado);
}

/// @brief Retorna o tipo do conteúdo
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @return o tipo do conteúdo
char getTipoConteudo(tConteudo *conteudo){
    return conteudo->tipoConteudo();
}

/// @brief Retorna a duração do conteudo
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @return A duração do conteudo
int getDuracaoConteudo(tConteudo *conteudo)
{
    return conteudo->duracao(conteudo->dado);
}

/// @brief Retorna o codigo unico do conteudo
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @return o codigo unico do conteudo
char *getCodConteudo(tConteudo *conteudo)
{
    return conteudo->codConteudo(conteudo->dado);
}

/// @brief Retorna a restrição de idade do conteudo (olhar util.c/.h)
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @return a restrição de idade do conteudo
TipoUsuario getRestricaoIdade(tConteudo *conteudo)
{
    return conteudo->restricaoIdade(conteudo->dado);
}

/// @brief Insere uma avaliação a em um conteúdo c
/// @param c um ponteiro para uma variável do tipo conteúdo
/// @param a um ponteiro para uma avaliação

void inserirAvaliacaoConteudo(tConteudo *c, tAvaliacao *a)
{
    c->qtdAvaliacoes++;

    c->avaliacoes = realloc(c->avaliacoes, c->qtdAvaliacoes * sizeof(tAvaliacao *));

    c->avaliacoes[c->qtdAvaliacoes - 1] = a;
}

/// @brief Função que imprime o conteúdo com a nota dada pelo usuário de cpf
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @param cpf O cpf da pessoa que deu a nota
void printaConteudoComNota(tConteudo *conteudo, char* cpf) {
    printaConteudo(conteudo);
    
    tAvaliacao *avaliacao = buscaNotaAvaliacao(conteudo, cpf);

    if (avaliacao != NULL) {
        int nota = getNotaAvaliacao(avaliacao);
        printf("    -> Sua avaliacao: %d\n", nota);
    }
}

/// @brief Função que retorna a avaliação de um conteúdo dado pelo usuário de cpf
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @param cpf o cpf da pessoa que fez a avaliação
/// @return A avaliação que a pessoa deu ao conteúdo, se ela existir
tAvaliacao *buscaNotaAvaliacao(tConteudo *conteudo, char *cpf)
{
    for (int i = 0; i < conteudo->qtdAvaliacoes; i++)
    {
        if (strcmp(cpf, getCpfAvaliacao(conteudo->avaliacoes[i])) == 0)
        {
            return conteudo->avaliacoes[i];
        }
    }
    return NULL;
}

/// @brief Retorna a quantidade de avaliações de um conteúdo
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @return A quantidade de avaliações de um conteúdo
int getQtdAvaliacoes(tConteudo *conteudo)
{
    return conteudo->qtdAvaliacoes;
}

/// @brief Retorna a avaliação da posição "pos" do vetor de avaliações de um conteúdo
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @param pos A posição da avaliação no conteúdo
/// @return Um ponteiro para uma variável da avaliação, se existir.
tAvaliacao *getAvaliacaoPosicao(tConteudo *conteudo, int pos)
{
    return conteudo->avaliacoes[pos];
}

/// @brief Retorna o título do conteúdo
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @return  o título do conteúdo
char *getTituloConteudo(tConteudo *conteudo)
{
    return conteudo->titulo(conteudo->dado);
}

/// @brief Retorna a nota media do conteúdo
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @return a nota media do conteúdo
float getNotaMediaConteudo(tConteudo *conteudo)
{
    return conteudo->notaMedia(conteudo->dado);
}

/// @brief Função que libera a memória alocada para um conteúdo
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
void liberaConteudo(tConteudo *conteudo)
{

    if (conteudo == NULL)
    {
        return;
    }

    conteudo->liberaConteudo(conteudo->dado);

    for (int i = 0; i < conteudo->qtdAvaliacoes; i++)
    {
        liberaAvaliacao(conteudo->avaliacoes[i]);
    }

    if (conteudo->avaliacoes != NULL)
    {
        free(conteudo->avaliacoes);
    }

    free(conteudo);
}

/// @brief Retorna o ponteiro genérico para o conteúdo (variável filme/jogo/serie)
/// @param conteudo um ponteiro para uma variável do tipo conteúdo
/// @return o ponteiro genérico para o conteúdo armazenado pelo tad genérico
void *getDadoConteudo(tConteudo *conteudo)
{
    return conteudo->dado;
}