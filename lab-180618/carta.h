/*******************************/
/* HEADER MODULO "carta" 	   */
/*******************************/
#ifndef CARTA_H_
#define CARTA_H_

struct cliente {
    char nome_cognome[41];
    int punti;
};

typedef cliente tipo_inf;

int compare(tipo_inf,tipo_inf);
void copy(tipo_inf&,tipo_inf);
void print(tipo_inf);

#endif /* CARTA_H_ */
