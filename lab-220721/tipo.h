#ifndef TIPO_H
#define TIPO_H

#include <iostream>

struct carta{
    int numero;
    char seme;
};

typedef carta tipo_inf;

int compare(tipo_inf, tipo_inf);
void copy(tipo_inf&, tipo_inf);
void print(tipo_inf);


#endif
