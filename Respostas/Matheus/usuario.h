#ifndef _USUARIO_H
#define _USUARIO_H

#include "util.h"
#include "conteudo.h"

typedef struct Usuario tUsuario;


tUsuario* criaUsuario(TipoUsuario tipo, TipoAssinatura assinatura, char* linhaDados);
void liberaUsuario(tUsuario* usuario);
char* getCpfUsuario(tUsuario* usuario);
char* getUsernameUsuario(tUsuario* usuario);
char* getSenhaUsuario(tUsuario* usuario);
void imprimeListaDeConsumidos(tUsuario* usuario);
TipoUsuario getTipoUsuario(tUsuario* usuario);
TipoAssinatura getAssinaturaUsuario(tUsuario* usuario);
void adicionaConteudoNaLista(tUsuario* usuario, tConteudo* conteudo);
int removeConteudoDaLista(tUsuario* usuario, char* idConteudo); 
tConteudo* consomePrimeiroDaLista(tUsuario* usuario);
void imprimeListaDeReproducao(tUsuario* usuario);
int getQtdConteudoNaLista(tUsuario* usuario);


#endif