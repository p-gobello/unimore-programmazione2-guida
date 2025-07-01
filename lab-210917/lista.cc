#include <iostream>
#include <cstring>

using namespace std ;


#include "tipo.h"
#include "lista.h"

/*******************************/
/* DEFINIZIONE MODULO "liste" */
/*******************************/

tipo_inf head(lista p){return p->inf;}
lista tail(lista p){ return p->pun; }
lista prev(lista p){ return p->prev; }

elem* new_elem(tipo_inf inf) {
    elem* p = new elem;
    copy(p->inf, inf);
    p->pun = p->prev = NULL;
    return p;
}

lista insert_elem(lista l, elem* e) {
    e->pun = l;
    if (l != NULL) {
        l->prev = e;
    }
    e->prev = NULL;
    return e;
}

lista delete_elem(lista l, elem* e) {
    if (e == l) { // cancellazione in testa
        l = e->pun;
        if (l != NULL) {
            l->prev = NULL;
        }
    } else { // cancellazione non in testa
        e->prev->pun = e->pun;
        if (e->pun != NULL) {
            e->pun->prev = e->prev;
        }
    }
    delete e;
    return l;
}

elem* search(lista l, tipo_inf v) {
    while (l != NULL) {
        if (compare(l->inf, v) == 0) {
            return l;
        }
        l = l->pun;
    }
    return NULL;
}

// Inserimento ordinato in base a data e ora
lista inserimento_ordinato(lista l, tipo_inf inf) {
    elem* nuovo = new_elem(inf);
    if (l == NULL || compare(inf, head(l)) < 0) {
        return insert_elem(l, nuovo);
    }

    lista p = l;
    while (tail(p) != NULL && compare(inf, head(tail(p))) > 0) {
        p = tail(p);
    }

    nuovo->pun = tail(p);
    if (tail(p) != NULL) {
        tail(p)->prev = nuovo;
    }
    p->pun = nuovo;
    nuovo->prev = p;

    return l;
}

// Controlla se due appuntamenti si sovrappongono
bool controlla_sovrapposizioni(lista l, tipo_inf nuovo_app) {
    lista p = l;
    while (p != NULL) {
        tipo_inf app_esistente = head(p);
        if (strcmp(app_esistente.data, nuovo_app.data) == 0) { // stesso giorno
            // Converte le ore in minuti per un confronto più semplice
            int start_esistente = stoi(string(app_esistente.orai, 2)) * 60 + stoi(string(app_esistente.orai + 2, 2));
            int end_esistente = stoi(string(app_esistente.oraf, 2)) * 60 + stoi(string(app_esistente.oraf + 2, 2));
            int start_nuovo = stoi(string(nuovo_app.orai, 2)) * 60 + stoi(string(nuovo_app.orai + 2, 2));
            int end_nuovo = stoi(string(nuovo_app.oraf, 2)) * 60 + stoi(string(nuovo_app.oraf + 2, 2));

            if (start_nuovo < end_esistente && end_nuovo > start_esistente) {
                return true; // C'è sovrapposizione
            }
        }
        p = tail(p);
    }
    return false; // Nessuna sovrapposizione
}
