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


/// @brief Função que converte uma quantidade de minutos em horas e minutos
/// @param tempoMinutos Um inteiro. Ex: 280 
/// @param horas A quantidade inteira de horas que cabem no tempoMinutos. Ex: Para 280, cabem 6 horas
/// @param minutos A quantidade inteira de minutos que restaram após subtrair as horas inteiras. Ex: 20 
void converteMinutos(int tempoMinutos, int *horas, int *minutos);

/// @brief Função que, dada uma sigla de idioma, retorna o significado dela
/// @param idioma - Sigla L/D/DL
/// @return Uma string "Legendado", para entrada L, "Dublado", para entrada D, e "Dublado/Legendado" para entrada DL
const char *descricaoIdioma(const char idioma[3]);

#endif