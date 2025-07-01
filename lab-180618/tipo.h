/*******************************/
/* HEADER MODULO "tipo" */
/*******************************/

#ifndef TIPO_H
#define TIPO_H

typedef struct carta {
    char seme;    // 'C'(Cuori), 'Q'(Quadri), 'F'(Fiori), 'P'(Picche)
    int valore;   // 1-13 (Ace=1, Jack=11, Queen=12, King=13)
} tipo_inf;

int compare(tipo_inf, tipo_inf);
void copy(tipo_inf&, tipo_inf);
void print(tipo_inf);

#endif
