#include "tipo.h"
#include <cstring>

using namespace std;

int compare(tipo_inf a, tipo_inf b){
    if(a.numero < b.numero)
        return -1;
    if(a.numero > b.numero)
        return 1;
    if(a.seme < b.seme)
        return -1;
    if(a.seme > b.seme)
        return 1;
    return 0;
}

void copy(tipo_inf& a, tipo_inf b){
    a.numero = b.numero;
    a.seme = b.seme;
}

void print(tipo_inf a){
    cout << a.numero << " " << a.seme;
}
