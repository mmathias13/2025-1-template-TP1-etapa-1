#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avaliacao.h"
#include "conteudo.h"
#include "distribuidor.h"
#include "filme.h"
#include "jogo.h"
#include "serie.h"
#include "usuario.h"
#include "util.h"

int main()
{

    char linha[512]; // Buffer para ler os comandos

    // --- Listas Principais do Sistema---
    tUsuario **usuarios = NULL;
    int qtdUsuarios = 0;

    tDistribuidor **distribuidores = NULL;
    int qtdDistribuidores = 0;

    tConteudo **conteudos = NULL;
    int qtdConteudos = 0;

    while (fgets(linha, 512, stdin) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0'; // Tira o \n da string lida
        if (strcmp(linha, "OUT") == 0)      // Compara o comando escrito para parar o loop se o usuário digitar "OUT"
            break;

        char *comando = strtok(linha, " ");

        char *args = strtok(NULL, "");

        if (strcmp(comando, "CAT") == 0)
        {
            printf("DEBUG: Comando CAT recebido com argumentos: '%s'\n", args);
            char *tipo_ator_str = strtok(args, " ");

            if (strcmp(tipo_ator_str, "USUARIO") == 0)
            {
                char *subtipo_str = strtok(NULL, " ");
                char *linhaDados = strtok(NULL, "");

                TipoUsuario tipo;
                TipoAssinatura assinatura;

                if (strcmp(subtipo_str, "INFANTIL") == 0)
                {
                    tipo = INFANTIL;
                    assinatura = PADRAO;
                }
                else
                {
                    tipo = ADULTO;
                    if (strcmp(subtipo_str, "PREMIUM") == 0)
                    {
                        assinatura = PREMIUM;
                    }
                    else
                    {
                        assinatura = PADRAO;
                    }
                }

                qtdUsuarios++;
                usuarios = realloc(usuarios, qtdUsuarios * sizeof(tUsuario *));
                usuarios[qtdUsuarios - 1] = criaUsuario(tipo, assinatura, linhaDados);
                printf("DEBUG: Usuario criado com sucesso!\n");
            }
            else if (strcmp(tipo_ator_str, "DISTRIBUIDOR") == 0)
            {
                char *linhaDados = strtok(NULL, "");

                qtdDistribuidores++;
                distribuidores = realloc(distribuidores, qtdDistribuidores * sizeof(tDistribuidor *));
                distribuidores[qtdDistribuidores - 1] = criaDistribuidor(linhaDados);

                printf("DEBUG: Distribuidor criado com sucesso!\n");
            }
        }
        else if (strcmp(comando, "CAC") == 0)
        {
            char *cnpjDistribuidor = strtok(args, " ");
            char *tipoConteudoStr = strtok(NULL, ";");
            char *linhaDados = strtok(NULL, "");

            char tipo = tipoConteudoStr[0];
            void *dadoEspecifico = NULL;

            if (tipo == 'F')
            {
                dadoEspecifico = criaFilme(linhaDados);
            }
            else if (tipo == 'S')
            {
                dadoEspecifico = criaSerie(linhaDados);
            }
            else if (tipo == 'J')
            {
                dadoEspecifico = criaJogo(linhaDados);
            }

            if (dadoEspecifico != NULL)
            {
                tConteudo *novoConteudo = NULL;

                if (tipo == 'F')
                {
                    novoConteudo = criaConteudo(dadoEspecifico,
                                                getAnoLancamentoFilme, getCodConteudoFilme, getNotaMediaFilme,
                                                getTituloFilme, getDuracaoFilme, printaFilme,
                                                getRestricaoAssinaturaFilme, getTipoFilme, getRestricaoIdadeFilme,
                                                liberaFilme);
                }
                else if (tipo == 'S')
                {
                    novoConteudo = criaConteudo(dadoEspecifico,
                                                getAnoLancamentoSerie, getCodConteudoSerie, getNotaMediaSerie,
                                                getTituloSerie, getDuracaoPorEpisodioSerie, NULL,
                                                getRestricaoAssinaturaSerie, getTipoSerie, getRestricaoIdadeSerie,
                                                liberaSerie);
                }
                else if (tipo == 'J')
                {
                    novoConteudo = criaConteudo(dadoEspecifico,
                                                getAnoDeLancamentoJogo, getCodJogo, getNotaMediaJogo,
                                                getTituloJogo, getDuracaoEstimadaJogo, NULL,
                                                getRestricaoAssinaturaJogo, getTipoJogo, getRestricaoIdadeJogo,
                                                liberaJogo);
                }

                qtdConteudos++;
                conteudos = realloc(conteudos, qtdConteudos * sizeof(tConteudo *));
                conteudos[qtdConteudos - 1] = novoConteudo;

                printf("CONTEUDO CADASTRADO COM SUCESSO!\n");
            }
        }
        else if (strcmp(comando, "ACL") == 0)
        {
            char *cpfUsuario = strtok(args, " ");
            char *idConteudo = strtok(NULL, "");

            tUsuario *usuarioAlvo = NULL;
            for (int i = 0; i < qtdUsuarios; i++)
            {
                if (strcmp(getCpfUsuario(usuarios[i]), cpfUsuario) == 0)
                {
                    usuarioAlvo = usuarios[i];
                    break;
                }
            }

            tConteudo *conteudoAlvo = NULL;
            if (usuarioAlvo != NULL)
            {
                for (int i = 0; i < qtdConteudos; i++)
                {
                    if (strcmp(getCodConteudo(conteudos[i]), idConteudo) == 0)
                    {
                        conteudoAlvo = conteudos[i];
                        break;
                    }
                }
            }

            if (usuarioAlvo != NULL && conteudoAlvo != NULL)
            {
                adicionaConteudoNaLista(usuarioAlvo, conteudoAlvo);
                imprimeListaDeReproducao(usuarioAlvo);
            }
            else if (usuarioAlvo == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
            }
            else
            {
                printf("O CONTEUDO %s NAO ESTA CADASTRADO!\n", idConteudo);
            }
        }
        else if (strcmp(comando, "RCL") == 0)
        {
            char *cpfUsuario = strtok(args, " ");
            char *idConteudo = strtok(NULL, "");

            tUsuario *usuarioAlvo = NULL;
            for (int i = 0; i < qtdUsuarios; i++)
            {
                if (strcmp(getCpfUsuario(usuarios[i]), cpfUsuario) == 0)
                {
                    usuarioAlvo = usuarios[i];
                    break;
                }
            }

            if (usuarioAlvo != NULL)
            {
                if (removeConteudoDaLista(usuarioAlvo, idConteudo))
                {
                    printf("O CONTEUDO %s FOI REMOVIDO DA LISTA DE REPRODUCAO DO USUARIO %s!\n", idConteudo, cpfUsuario);
                }
                else
                {
                    printf("O CONTEUDO NAO ESTA PRESENTE NA LISTA DE REPRODUCAO DO USUARIO %s!\n", cpfUsuario);
                }
                imprimeListaDeReproducao(usuarioAlvo);
            }
            else
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
            }
        }
        else if (strcmp(comando, "MLR") == 0)
        {
            char *cpfUsuario = strtok(args, " ");

            tUsuario *usuarioAlvo = NULL;
            for (int i = 0; i < qtdUsuarios; i++)
            {
                if (strcmp(getCpfUsuario(usuarios[i]), cpfUsuario) == 0)
                {
                    usuarioAlvo = usuarios[i];
                    break;
                }
            }

            if (usuarioAlvo != NULL)
            {
                imprimeListaDeReproducao(usuarioAlvo);
            }
            else
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
            }
        }
        else if (strcmp(comando, "CPCLR") == 0)
        {
            char *cpfUsuario = strtok(args, " ");
            tUsuario *usuarioAlvo = NULL;
            for (int i = 0; i < qtdUsuarios; i++)
            {
                if (strcmp(getCpfUsuario(usuarios[i]), cpfUsuario) == 0)
                {
                    usuarioAlvo = usuarios[i];
                    break;
                }
            }

            if (usuarioAlvo == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
            }
            else if (getQtdConteudoNaLista(usuarioAlvo) == 0)
            {
                printf("LISTA DO USUARIO %s ESTA VAZIA! OPERACAO NAO PERMITIDA!\n", cpfUsuario);
            }
            else
            {
                tConteudo *conteudoConsumido = consomePrimeiroDaLista(usuarioAlvo);

                printf("CONTEUDO %s FOI CONSUMIDO PELO USUARIO %s!\n", getTituloConteudo(conteudoConsumido), cpfUsuario);

                if (getTipoUsuario(usuarioAlvo) == ADULTO)
                {
                    printf("DIGITE UMA NOTA ENTRE 1 E 5\n");
                    char linhaNota[10];
                    fgets(linhaNota, 10, stdin);
                    int nota = atoi(linhaNota);

                    if (nota >= 1 && nota <= 5)
                    {
                        tAvaliacao *novaAvaliacao = criaAvaliacao(cpfUsuario, nota);
                        inserirAvaliacaoConteudo(conteudoConsumido, novaAvaliacao);
                        printf("CONTEUDO %s AVALIADO COM NOTA %d!\n", getTituloConteudo(conteudoConsumido), nota);
                    }
                }
            }
        }
        else if (strcmp(comando, "RGC") == 0)
        {
            char *cpfUsuario = strtok(args, " ");
            tUsuario *usuarioAlvo = NULL;

            for (int i = 0; i < qtdUsuarios; i++)
            {
                if (strcmp(getCpfUsuario(usuarios[i]), cpfUsuario) == 0)
                {
                    usuarioAlvo = usuarios[i];
                    break;
                }
            }

            if (usuarioAlvo != NULL)
            {
                printf("RELATORIO GERAL DE CONTEUDO\n");
                int contadorImpressao = 0;
                TipoUsuario tipoUsuario = getTipoUsuario(usuarioAlvo);
                TipoAssinatura assinaturaUsuario = getAssinaturaUsuario(usuarioAlvo);

                for (int i = 0; i < qtdConteudos; i++)
                {
                    tConteudo *conteudoAtual = conteudos[i];
                    int podeImprimir = 1;

                    if (assinaturaUsuario == PADRAO && getRestricaoConteudo(conteudoAtual) == PREMIUM)
                    {
                        podeImprimir = 0;
                    }
                    if (tipoUsuario == INFANTIL && getRestricaoIdade(conteudoAtual) == ADULTO)
                    {
                        podeImprimir = 0;
                    }

                    if (podeImprimir)
                    {
                        contadorImpressao++;
                        printf("%d-", contadorImpressao);
                        printaConteudo(conteudoAtual);
                    }
                }

                if (contadorImpressao == 0)
                {
                    printf("NENHUM CONTEUDO ENCONTRADO!\n");
                }
            }
            else
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
            }
        }
        else if (strcmp(comando, "GRU") == 0)
        {
            char *cpfUsuario = strtok(args, " ");
            tUsuario *usuarioAlvo = NULL;

            for (int i = 0; i < qtdUsuarios; i++)
            {
                if (strcmp(getCpfUsuario(usuarios[i]), cpfUsuario) == 0)
                {
                    usuarioAlvo = usuarios[i];
                    break;
                }
            }

            if (usuarioAlvo == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
            }
            else
            {
                printf("DIGITE A SENHA:\n");
                char senhaDigitada[50];
                fgets(senhaDigitada, 50, stdin);
                senhaDigitada[strcspn(senhaDigitada, "\n")] = '\0';

                if (strcmp(getSenhaUsuario(usuarioAlvo), senhaDigitada) != 0)
                {
                    printf("SENHA INCORRETA! OPERACAO NAO PERMITIDA!\n");
                }
                else
                {
                    printf("RELATORIO USUARIO DE CPF %s\n", getCpfUsuario(usuarioAlvo));
                    printf("NOME: %s\n", getNomeUsuario(usuarioAlvo));
                    printf("TELEFONE: %s\n", getTelefoneUsuario(usuarioAlvo));
                    printf("ENDERECO: %s\n", getEnderecoUsuario(usuarioAlvo));
                    printf("NOME DE USUARIO: %s\n", getUsernameUsuario(usuarioAlvo));

                    printf("SENHA: ");
                    for (int i = 0; i < strlen(getSenhaUsuario(usuarioAlvo)); i++)
                    {
                        printf("*");
                    }
                    printf("\n");

                    printf("E-MAIL: %s\n", getEmailUsuario(usuarioAlvo));
                    printf("DATA NASCIMENTO: %s\n", getDataNascimentoUsuario(usuarioAlvo));
                    printf("NUM. CONTEUDOS CONSUMIDOS: %d\n", getNumProdutosConsumidosUsuario(usuarioAlvo));

                    int totalMinutos = getTotalMinutosConsumidosUsuario(usuarioAlvo);
                    int horas = 0;
                    int minutos = 0;
                    converteMinutos(totalMinutos, &horas, &minutos);
                    printf("TOTAL HORAS CONSUMIDAS: %02d:%02d\n", horas, minutos);

                    printf("NUM. AVALIACOES REALIZADAS: %d\n", getNumAvaliacoesRealizadasUsuario(usuarioAlvo));

                    if (getTipoUsuario(usuarioAlvo) == ADULTO)
                    {
                        printf("USUARIO 18+ %s\n", getAssinaturaUsuario(usuarioAlvo) == PREMIUM ? "PREMIUM" : "PADRAO");
                        printf("CARTAO NUM.: %s\n", getCartaoDeCreditoUsuario(usuarioAlvo));
                    }
                    else
                    {
                        printf("USUARIO INFANTIL %s\n", getAssinaturaUsuario(usuarioAlvo) == PREMIUM ? "PREMIUM" : "PADRAO");
                        printf("CPF RESPONSAVEL: %s\n", getCpfResponsavelUsuario(usuarioAlvo));
                    }

                    imprimeListaDeReproducao(usuarioAlvo);

                    printf("LISTA DE CONTEUDOS CONSUMIDOS:\n");
                    imprimeListaDeConsumidos(usuarioAlvo);
                }
            }
        }
        else
        {
            printf("Comando desconhecido: %s\n", comando);
        }
    }

    return 0;
}