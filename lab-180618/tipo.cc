#include <iostream>
#include <cstring>
using namespace std;

#include "tipo.h"

/*******************************/
/* DEFINIZIONE MODULO "tipo" */
/*******************************/

int compare(tipo_inf c1, tipo_inf c2) {
    // First compare by suit, then by value
    if (c1.seme != c2.seme) {
        return c1.seme - c2.seme;
    }
    return c1.valore - c2.valore;
}

void copy(tipo_inf& dest, tipo_inf source) {
    dest.seme = source.seme;
    dest.valore = source.valore;
}

void print(tipo_inf inf) {
    cout << inf.valore;
    switch(inf.seme) {
        case 'C': cout << "♥"; break;  // Cuori = Hearts
        case 'Q': cout << "♦"; break;  // Quadri = Diamonds  
        case 'F': cout << "♣"; break;  // Fiori = Clubs
        case 'P': cout << "♠"; break;  // Picche = Spades
        default: cout << inf.seme; break;
    }
}
