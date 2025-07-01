#include <iostream>
#include <cstring>
#include "carta.h"

using namespace std;

int compare(tipo_inf s1, tipo_inf s2) {
    return strcmp(s1.nome_cognome, s2.nome_cognome);
}

void copy(tipo_inf& dest, tipo_inf source) {
    strcpy(dest.nome_cognome, source.nome_cognome);
    dest.punti = source.punti;
}

void print(tipo_inf data) {
    cout << data.nome_cognome << " " << data.punti;
} 