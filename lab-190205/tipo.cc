/*******************************/
/* IMPLEMENTAZIONE MODULO "tipo" */
/*******************************/
#include <iostream>
#include "tipo.h"

using namespace std;

int compare(tipo_inf c1, tipo_inf c2) {
    if (c1.seme < c2.seme) return -1;
    if (c1.seme > c2.seme) return 1;
    if (c1.valore < c2.valore) return -1;
    if (c1.valore > c2.valore) return 1;
    return 0;
}

void copy(tipo_inf& dest, tipo_inf source) {
    dest.seme = source.seme;
    dest.valore = source.valore;
}

void print(tipo_inf c) {
    cout << c.valore << c.seme;
}
