#include <iostream>
#include <cstring>
#include "tipo.h"

using namespace std;

// Funzione di comparazione per tipo_inf basata sull'ID
int compare(tipo_inf p1, tipo_inf p2) {
    return p1.id - p2.id;
}

// Funzione per copiare un tipo_inf
void copy(tipo_inf& dest, tipo_inf source) {
    dest.id = source.id;
    strcpy(dest.nome, source.nome);
    dest.tipo = source.tipo;
}

// Funzione per stampare un tipo_inf
void print(tipo_inf p) {
    cout << p.nome << " " << p.tipo << endl;
} 