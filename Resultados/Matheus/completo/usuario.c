#include "usuario.h"
#include "util.h"
#include "conteudo.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Usuario
{
    char nomeCompleto[101];
    char identificador[15];
    char telefone[15];
    char endereco[151];
    char username[16];
    char senha[21];
    char dataNascimento[11];
    char email[51];
    int numProdutosConsumidos;
    int numAvaliacoesRealizadas;
    int totalMinutosConsumidos;
    TipoUsuario tipoUsuario;
    tConteudo **listaDeReproducao;
    int qtdNaListaDeReproducao;
    char **listaDeConsumidosIds;
    int qtdConsumidos;

    char cartaoDeCredito[13];
    TipoAssinatura tipoAssinatura;

    char cpfResponsavel[15];
};

tUsuario *criaUsuario(TipoUsuario tipo, TipoAssinatura assinatura, char *linhaDados)
{

    int i = 0;
    tUsuario *usuario = (tUsuario *)malloc(sizeof(tUsuario));
    char *token = (strtok(linhaDados, ";"));
    while (token != NULL)
    {
        if (i == 0)
        {
            strcpy(usuario->nomeCompleto, token);
        }
        else if (i == 1)
        {
            strcpy(usuario->identificador, token);
        }
        else if (i == 2)
        {
            strcpy(usuario->telefone, token);
        }
        else if (i == 3)
        {
            strcpy(usuario->endereco, token);
        }
        else if (i == 4)
        {
            strcpy(usuario->username, token);
        }
        else if (i == 5)
        {
            strcpy(usuario->senha, token);
        }
        else if (i == 6)
        {
            strcpy(usuario->dataNascimento, token);
        }
        else if (i == 7)
        {
            strcpy(usuario->email, token);
        }
        else if (i == 8)
        {
            if (tipo == ADULTO)
            {
                strcpy(usuario->cartaoDeCredito, token);
            }
            else
                strcpy(usuario->cpfResponsavel, token);
        }
        token = (strtok(NULL, ";"));
        i++;
    }

    usuario->numProdutosConsumidos = 0;
    usuario->numAvaliacoesRealizadas = 0;
    usuario->totalMinutosConsumidos = 0;
    usuario->qtdNaListaDeReproducao = 0;
    usuario->qtdConsumidos = 0;
    usuario->listaDeReproducao = NULL;
    usuario->listaDeConsumidosIds = NULL;

    usuario->tipoUsuario = tipo;
    usuario->tipoAssinatura = assinatura;

    if (tipo == ADULTO)
    {
        usuario->cpfResponsavel[0] = '\0';
    }
    else
        usuario->cartaoDeCredito[0] = '\0';

    return usuario;
}

void imprimeListaDeConsumidos(tUsuario *usuario)
{
    if (usuario->qtdConsumidos == 0)
    {
        printf("NENHUM CONTEUDO CONSUMIDO AINDA.\n"); // Mensagem sugestiva
    }
    else
    {
        for (int i = 0; i < usuario->qtdConsumidos; i++)
        {
            // A especificação pede ordem inversa (o último consumido aparece primeiro)
            int indice = usuario->qtdConsumidos - 1 - i;
            printf("%d-%s\n", i + 1, usuario->listaDeConsumidosIds[indice]);
        }
    }
}

void adicionaConteudoNaLista(tUsuario *usuario, tConteudo *conteudo)
{
    char *idNovoConteudo = getCodConteudo(conteudo);

    for (int i = 0; i < usuario->qtdNaListaDeReproducao; i++)
    {
        if (strcmp(getCodConteudo(usuario->listaDeReproducao[i]), idNovoConteudo) == 0)
        {
            return;
        }
    }

    if (getTipoUsuario(usuario) == INFANTIL && getRestricaoIdade(conteudo) == ADULTO)
    {
        printf("NAO EH POSSIVEL ADICIONAR O CONTEUDO %s A CONTA INFANTIL DO CPF %s!\n",
               idNovoConteudo, getCpfUsuario(usuario));
        return;
    }

    if (getAssinaturaUsuario(usuario) == PADRAO && getRestricaoConteudo(conteudo) == PREMIUM)
    {
        printf("NAO EH POSSIVEL ADICIONAR O CONTEUDO PREMIUM %s A CONTA PADRAO DO CPF %s!\n",
               idNovoConteudo, getCpfUsuario(usuario));
        return;
    }

    usuario->qtdNaListaDeReproducao++;
    usuario->listaDeReproducao = realloc(usuario->listaDeReproducao, usuario->qtdNaListaDeReproducao * sizeof(tConteudo *));
    usuario->listaDeReproducao[usuario->qtdNaListaDeReproducao - 1] = conteudo;
}

int removeConteudoDaLista(tUsuario *usuario, char *idConteudo)
{
    int indiceParaRemover = -1;
    for (int i = 0; i < usuario->qtdNaListaDeReproducao; i++)
    {
        if (strcmp(getCodConteudo(usuario->listaDeReproducao[i]), idConteudo) == 0)
        {
            indiceParaRemover = i;
            break;
        }
    }

    if (indiceParaRemover != -1)
    {
        for (int i = indiceParaRemover; i < usuario->qtdNaListaDeReproducao - 1; i++)
        {
            usuario->listaDeReproducao[i] = usuario->listaDeReproducao[i + 1];
        }

        usuario->qtdNaListaDeReproducao--;
        if (usuario->qtdNaListaDeReproducao > 0)
        {
            usuario->listaDeReproducao = realloc(usuario->listaDeReproducao, usuario->qtdNaListaDeReproducao * sizeof(tConteudo *));
        }
        else
        {
            free(usuario->listaDeReproducao);
            usuario->listaDeReproducao = NULL;
        }
        return 1;
    }
    return 0;
}

void imprimeListaDeReproducao(tUsuario *usuario)
{
    if (usuario->qtdNaListaDeReproducao == 0)
    {
        printf("LISTA DE REPRODUCAO VAZIA!\n");
    }
    else
    {
        printf("LISTA DE REPRODUCAO:\n");
        for (int i = 0; i < usuario->qtdNaListaDeReproducao; i++)
        {
            printf("%d-", i + 1);
            printaConteudo(usuario->listaDeReproducao[i]);
        }
    }

    int totalMinutos = 0;
    for (int i = 0; i < usuario->qtdNaListaDeReproducao; i++)
    {
        totalMinutos += getDuracaoConteudo(usuario->listaDeReproducao[i]);
    }

    int horas = 0;
    int minutos = 0;
    converteMinutos(totalMinutos, &horas, &minutos);
    printf("(TOTAL %02d:%02d horas)\n", horas, minutos);
}

tConteudo *consomePrimeiroDaLista(tUsuario *usuario)
{
    if (usuario == NULL || usuario->qtdNaListaDeReproducao == 0)
    {
        return NULL;
    }

    tConteudo *conteudoConsumido = usuario->listaDeReproducao[0];

    for (int i = 0; i < usuario->qtdNaListaDeReproducao - 1; i++)
    {
        usuario->listaDeReproducao[i] = usuario->listaDeReproducao[i + 1];
    }

    usuario->qtdNaListaDeReproducao--;
    if (usuario->qtdNaListaDeReproducao > 0)
    {
        usuario->listaDeReproducao = realloc(usuario->listaDeReproducao, usuario->qtdNaListaDeReproducao * sizeof(tConteudo *));
    }
    else
    {
        free(usuario->listaDeReproducao);
        usuario->listaDeReproducao = NULL;
    }

    return conteudoConsumido;
}

int getQtdConteudoNaLista(tUsuario *usuario)
{
    return usuario->qtdNaListaDeReproducao;
}

void liberaUsuario(tUsuario *usuario)
{
    if (usuario == NULL)
    {
        return;
    }
    if (usuario->listaDeReproducao != NULL)
    {
        free(usuario->listaDeReproducao);
    }
    if (usuario->listaDeConsumidosIds != NULL)
    {
        for (int i = 0; i < usuario->qtdConsumidos; i++)
        {
            free(usuario->listaDeConsumidosIds[i]);
        }
        free(usuario->listaDeConsumidosIds);
    }
    free(usuario);
}

char *getCpfUsuario(tUsuario *usuario)
{
    return usuario->identificador;
}

char *getUsernameUsuario(tUsuario *usuario)
{
    return usuario->username;
}

char *getSenhaUsuario(tUsuario *usuario)
{
    return usuario->senha;
}

TipoUsuario getTipoUsuario(tUsuario *usuario)
{
    return usuario->tipoUsuario;
}

TipoAssinatura getAssinaturaUsuario(tUsuario *usuario)
{
    return usuario->tipoAssinatura;
}

char *getNomeUsuario(tUsuario *usuario)
{
    return usuario->nomeCompleto;
}
char *getTelefoneUsuario(tUsuario *usuario)
{
    return usuario->telefone;
}
char *getEnderecoUsuario(tUsuario *usuario)
{
    return usuario->endereco;
}
char *getEmailUsuario(tUsuario *usuario)
{
    return usuario->email;
}
char *getDataNascimentoUsuario(tUsuario *usuario)
{
    return usuario->dataNascimento;
}
int getNumProdutosConsumidosUsuario(tUsuario *usuario)
{
    return usuario->numProdutosConsumidos;
}
int getTotalMinutosConsumidosUsuario(tUsuario *usuario)
{
    return usuario->totalMinutosConsumidos;
}
int getNumAvaliacoesRealizadasUsuario(tUsuario *usuario)
{
    return usuario->numAvaliacoesRealizadas;
}
char *getCartaoDeCreditoUsuario(tUsuario *usuario)
{
    return usuario->cartaoDeCredito;
}
char *getCpfResponsavelUsuario(tUsuario *usuario)
{
    return usuario->cpfResponsavel;
}