#ifndef TIPO_H
#define TIPO_H

#include <iostream>
#include <cstring>

struct hotel {
    char nome[50];
    char citta[30];
};

typedef hotel tipo_inf;

int compare(tipo_inf, tipo_inf);
void copy(tipo_inf&, tipo_inf);
void print(tipo_inf);

#endif
