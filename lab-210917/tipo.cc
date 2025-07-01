#include <iostream>
#include <cstring>
#include "tipo.h"

using namespace std;

// Compara due appuntamenti per data e ora di inizio
int compare(tipo_inf a1, tipo_inf a2) {
    int data_cmp = strcmp(a1.data, a2.data);
    if (data_cmp != 0) {
        return data_cmp;
    }
    return strcmp(a1.orai, a2.orai);
}

// Copia i dati di un appuntamento
void copy(tipo_inf& dest, tipo_inf source) {
    strcpy(dest.data, source.data);
    strcpy(dest.orai, source.orai);
    strcpy(dest.oraf, source.oraf);
    strcpy(dest.descr, source.descr);
}

// Stampa un appuntamento in formato leggibile
void print(tipo_inf inf) {
    cout << inf.data[4] << inf.data[5] << "/" << inf.data[2] << inf.data[3] << "/" << inf.data[0] << inf.data[1];
    cout << " " << inf.orai[0] << inf.orai[1] << ":" << inf.orai[2] << inf.orai[3];
    cout << "-" << inf.oraf[0] << inf.oraf[1] << ":" << inf.oraf[2] << inf.oraf[3];
    cout << ": " << inf.descr << endl;
}
