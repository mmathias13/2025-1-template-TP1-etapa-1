#ifndef _USUARIO_H
#define _USUARIO_H

#include "util.h"
#include "conteudo.h"

// Declaração do TAD Opaco
typedef struct Usuario tUsuario;

// --- Protótipos das Funções ---

// Função de Criação
tUsuario* criaUsuario(TipoUsuario tipo, TipoAssinatura assinatura, char* linhaDados);

// Função para Liberar a Memória
void liberaUsuario(tUsuario* usuario);

// Funções "get" para obter dados do usuário
char* getCpfUsuario(tUsuario* usuario);
char* getUsernameUsuario(tUsuario* usuario);
char* getSenhaUsuario(tUsuario* usuario);
TipoUsuario getTipoUsuario(tUsuario* usuario);
TipoAssinatura getAssinaturaUsuario(tUsuario* usuario);
char* getNomeUsuario(tUsuario* usuario);
char* getTelefoneUsuario(tUsuario* usuario);
char* getEnderecoUsuario(tUsuario* usuario);
char* getEmailUsuario(tUsuario* usuario);
char* getDataNascimentoUsuario(tUsuario* usuario);
int getNumProdutosConsumidosUsuario(tUsuario* usuario);
int getTotalMinutosConsumidosUsuario(tUsuario* usuario);
int getNumAvaliacoesRealizadasUsuario(tUsuario* usuario);
char* getCartaoDeCreditoUsuario(tUsuario* usuario);
char* getCpfResponsavelUsuario(tUsuario* usuario);

// Funções para manipular a lista de reprodução
void adicionaConteudoNaLista(tUsuario* usuario, tConteudo* conteudo);
int removeConteudoDaLista(tUsuario* usuario, char* idConteudo);
tConteudo* consomePrimeiroDaLista(tUsuario* usuario);
void imprimeListaDeReproducao(tUsuario* usuario);
int getQtdConteudoNaLista(tUsuario* usuario);
void imprimeListaDeConsumidos(tUsuario* usuario);


#endif // _USUARIO_H