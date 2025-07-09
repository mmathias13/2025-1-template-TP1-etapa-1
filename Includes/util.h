#ifndef _UTIL_H
#define _UTIL_H

typedef enum 
{
    ADULTO = 1,
    INFANTIL = 0
} TipoUsuario;

typedef enum 
{
    PADRAO = 0,
    PREMIUM = 1
} TipoAssinatura;


void converteMinutos(int tempoMinutos, int *horas, int *minutos);

const char *descricaoIdioma(const char idioma[3]);

#endif