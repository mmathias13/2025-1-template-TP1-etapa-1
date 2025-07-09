#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "util.h"

void converteMinutos(int tempoMinutos, int *horas, int *minutos) {
    if (horas != NULL && minutos != NULL) {
        *horas = tempoMinutos / 60;
        *minutos = tempoMinutos % 60;
    }
}

const char *descricaoIdioma(const char idioma[3]) {
    if (strcmp(idioma, "L") == 0)
        return "LEGENDADO";
    else if (strcmp(idioma, "D") == 0)
        return "DUBLADO";
    else if (strcmp(idioma, "DL") == 0 || strcmp(idioma, "LD") == 0)
        return "DUBLADO/LEGENDADO";
    else
        return NULL;
}
