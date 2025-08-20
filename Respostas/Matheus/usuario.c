#include "usuario.h"
#include "util.h"
#include "conteudo.h"
#include <stdlib.h>
#include <string.h>

struct Usuario
{
    // --- Campos Comuns ---
    char nomeCompleto[101];
    char identificador[15]; // CPF
    char telefone[15];
    char endereco[151];
    char username[16];
    char senha[21]; // Corrigido

    // --- Campos Específicos de Usuário ---
    char dataNascimento[11];
    char email[51]; // Corrigido
    int numProdutosConsumidos;
    int numAvaliacoesRealizadas;
    int totalMinutosConsumidos;
    TipoUsuario tipoUsuario; // Corrigido

    // Lista de Reprodução (Faltando)
    tConteudo **listaDeReproducao;
    int qtdNaListaDeReproducao;

    // Lista de Consumidos (Faltando)
    char **listaDeConsumidosIds; // Armazenando IDs como strings
    int qtdConsumidos;

    // --- Campos de Subtipos ---
    // Adulto
    char cartaoDeCredito[13];
    TipoAssinatura tipoAssinatura;

    // Infantil
    char cpfResponsavel[15];
};

tUsuario *criaUsuario(TipoUsuario tipo, TipoAssinatura assinatura, char *linhaDados)
{

    int i = 0;
    tUsuario *usuario = (tUsuario *)malloc(sizeof(tUsuario));
    char *token = (strtok(linhaDados, ';'));
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
        token = (strtok(NULL, ';'));
        i++;
    }

    //Inicializando contadores com 0
    usuario->numProdutosConsumidos = 0;
    usuario->numAvaliacoesRealizadas = 0;
    usuario->totalMinutosConsumidos = 0;
    usuario->qtdNaListaDeReproducao = 0;
    usuario->qtdConsumidos = 0;
    usuario->listaDeReproducao = NULL;
    usuario->listaDeConsumidosIds = NULL;

    //Salvar o tipo e a assinatura do usuário
    usuario->tipoUsuario = tipo;
    usuario->tipoAssinatura = assinatura;

    //Evitando lixo em campos não utilizados
    if (tipo == ADULTO){
        usuario->cpfResponsavel[0] = '\0';
    } else
        usuario->cartaoDeCredito[0] = '\0';

    return usuario;
}

void adicionaConteudoNaLista(tUsuario* usuario, tConteudo* conteudo) {
    char* idNovoConteudo = getCodConteudo(conteudo);

    for (int i = 0; i < usuario->qtdNaListaDeReproducao; i++) {
        if (strcmp(getCodConteudo(usuario->listaDeReproducao[i]), idNovoConteudo) == 0) {
            return;
        }
    }

    if (getTipoUsuario(usuario) == INFANTIL && getRestricaoIdade(conteudo) == ADULTO) {
        printf("NAO EH POSSIVEL ADICIONAR O CONTEUDO %s A CONTA INFANTIL DO CPF %s!\n",
               idNovoConteudo, getCpfUsuario(usuario));
        return;
    }

    if (getAssinaturaUsuario(usuario) == PADRAO && getRestricaoConteudo(conteudo) == PREMIUM) {
        printf("NAO EH POSSIVEL ADICIONAR O CONTEUDO PREMIUM %s A CONTA PADRAO DO CPF %s!\n",
               idNovoConteudo, getCpfUsuario(usuario));
        return;
    }

    usuario->qtdNaListaDeReproducao++;
    usuario->listaDeReproducao = realloc(usuario->listaDeReproducao, usuario->qtdNaListaDeReproducao * sizeof(tConteudo*));
    usuario->listaDeReproducao[usuario->qtdNaListaDeReproducao - 1] = conteudo;
}

int removeConteudoDaLista(tUsuario* usuario, char* idConteudo) {
    int indiceParaRemover = -1;
    for (int i = 0; i < usuario->qtdNaListaDeReproducao; i++) {
        if (strcmp(getCodConteudo(usuario->listaDeReproducao[i]), idConteudo) == 0) {
            indiceParaRemover = i;
            break;
        }
    }

    if (indiceParaRemover != -1) {
        for (int i = indiceParaRemover; i < usuario->qtdNaListaDeReproducao - 1; i++) {
            usuario->listaDeReproducao[i] = usuario->listaDeReproducao[i + 1];
        }

        usuario->qtdNaListaDeReproducao--;
        if (usuario->qtdNaListaDeReproducao > 0) {
            usuario->listaDeReproducao = realloc(usuario->listaDeReproducao, usuario->qtdNaListaDeReproducao * sizeof(tConteudo*));
        } else {
            free(usuario->listaDeReproducao);
            usuario->listaDeReproducao = NULL;
        }
        return 1;
    }
    return 0;
}

void imprimeListaDeReproducao(tUsuario* usuario) {
    if (usuario->qtdNaListaDeReproducao == 0) {
        printf("LISTA DE REPRODUCAO VAZIA!\n");
    } else {
        printf("LISTA DE REPRODUCAO:\n");
        for (int i = 0; i < usuario->qtdNaListaDeReproducao; i++) {
            printf("%d-", i + 1);
            printaConteudo(usuario->listaDeReproducao[i]);
        }
    }

    int totalMinutos = 0;
    for (int i = 0; i < usuario->qtdNaListaDeReproducao; i++) {
        totalMinutos += getDuracaoConteudo(usuario->listaDeReproducao[i]);
    }

    int horas = 0;
    int minutos = 0;
    converteMinutos(totalMinutos, &horas, &minutos);
    printf("(TOTAL %02d:%02d horas)\n", horas, minutos);
}

tConteudo* consomePrimeiroDaLista(tUsuario* usuario) {
    if (usuario == NULL || usuario->qtdNaListaDeReproducao == 0) {
        return NULL;
    }

    tConteudo* conteudoConsumido = usuario->listaDeReproducao[0];

    for (int i = 0; i < usuario->qtdNaListaDeReproducao - 1; i++) {
        usuario->listaDeReproducao[i] = usuario->listaDeReproducao[i + 1];
    }

    usuario->qtdNaListaDeReproducao--;
    if (usuario->qtdNaListaDeReproducao > 0) {
        usuario->listaDeReproducao = realloc(usuario->listaDeReproducao, usuario->qtdNaListaDeReproducao * sizeof(tConteudo*));
    } else {
        free(usuario->listaDeReproducao);
        usuario->listaDeReproducao = NULL;
    }

    return conteudoConsumido;
}

int getQtdConteudoNaLista(tUsuario* usuario) {
    return usuario->qtdNaListaDeReproducao;
}