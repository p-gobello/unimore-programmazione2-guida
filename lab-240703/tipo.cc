#include "tipo.h"
#include <cstring>
#include <iostream>

using namespace std;

int compare(tipo_inf a, tipo_inf b) {
    // Compare hotels by name first, then by city
    int name_cmp = strcmp(a.nome, b.nome);
    if (name_cmp != 0) {
        return name_cmp;
    }
    return strcmp(a.citta, b.citta);
}

void copy(tipo_inf& dest, tipo_inf src) {
    strcpy(dest.nome, src.nome);
    strcpy(dest.citta, src.citta);
}

void print(tipo_inf hotel) {
    cout << "Hotel: " << hotel.nome << ", Città: " << hotel.citta;
}
