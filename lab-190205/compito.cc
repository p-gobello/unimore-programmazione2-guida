#include <iostream>
#include "tipo.h"
#include "liste.h"

using namespace std;

void pesca(lista& carte) {
    tipo_inf c;
    cout << "Inserisci seme (C, F, P, Q): ";
    cin >> c.seme;
    cout << "Inserisci valore (1-13): ";
    cin >> c.valore;
    elem* e = new_elem(c);
    carte = ord_insert_elem(carte, e);
}

void stampa(lista carte) {
    while (carte != NULL) {
        print(head(carte));
        cout << " ";
        carte = tail(carte);
    }
    cout << endl;
}

carta* scala(lista carte, int& lunghezza) {
    if (carte == NULL) {
        lunghezza = 0;
        return NULL;
    }

    //lista best_start = NULL;
    //int max_len = 0;

    lista current = carte;
    while (current != NULL) {
        lista runner = current;
        int current_len = 1;
        while (tail(runner) != NULL && 
               head(tail(runner)).seme == head(runner).seme &&
               head(tail(runner)).valore == head(runner).valore + 1) {
            current_len++;
            runner = tail(runner);
        }

        if (current_len >= 3) {
             // check if it is the "maximal" sequence
            bool is_maximal = true;
            if(prev(current) != NULL && 
                head(prev(current)).seme == head(current).seme &&
                head(prev(current)).valore == head(current).valore -1)
                is_maximal = false;

            if(is_maximal){
                lunghezza = current_len;
                return &current->inf;
            }
        }
        current = tail(current);
    }

    lunghezza = 0;
    return NULL;
}

carta* best_scala(lista carte, int& lunghezza) {
    lista best_start_node = NULL;
    int max_punteggio = 0;
    lunghezza = 0;

    lista current = carte;
    while (current != NULL) {
        lista runner = current;
        int current_len = 1;
        while (tail(runner) != NULL && 
               head(tail(runner)).seme == head(runner).seme &&
               head(tail(runner)).valore == head(runner).valore + 1) {
            current_len++;
            runner = tail(runner);
        }

        if (current_len >= 3) {
            bool is_maximal = true;
            if(prev(current) != NULL && 
                head(prev(current)).seme == head(current).seme &&
                head(prev(current)).valore == head(current).valore -1)
                is_maximal = false;

            if(is_maximal){
                int current_punteggio = 0;
                lista temp = current;
                for(int i=0; i<current_len; i++){
                    current_punteggio += head(temp).valore;
                    temp = tail(temp);
                }

                if(current_punteggio > max_punteggio){
                    max_punteggio = current_punteggio;
                    best_start_node = current;
                    lunghezza = current_len;
                }
            }
        }
        current = tail(current);
    }
    if(best_start_node == NULL)
        return NULL;
    return &best_start_node->inf;
}

int cala(lista& carte) {
    int lunghezza;
    carta* s = best_scala(carte, lunghezza);
    if (s == NULL) {
        return 0;
    }

    elem* start_node = search(carte, *s);
    int punteggio = 0;
    for (int i = 0; i < lunghezza; i++) {
        punteggio += head(start_node).valore;
        elem* next = tail(start_node);
        carte = delete_elem(carte, start_node);
        start_node = next;
    }
    return punteggio;
}

int main() {
    lista g1 = NULL;
    lista g2 = NULL;
    int n_carte;

    cout << "Quante carte per giocatore? ";
    cin >> n_carte;

    cout << endl << "Giocatore 1:" << endl;
    for (int i = 0; i < n_carte; i++) {
        cout << "Carta " << i + 1 << endl;
        pesca(g1);
    }

    cout << endl << "Giocatore 2:" << endl;
    for (int i = 0; i < n_carte; i++) {
        cout << "Carta " << i + 1 << endl;
        pesca(g2);
    }

    cout << endl << "Carte del giocatore 1: ";
    stampa(g1);
    cout << "Carte del giocatore 2: ";
    stampa(g2);

    int p1_score = 0;
    int p2_score = 0;

    for (int i = 0; i < 2; i++) {
        cout << endl << "--- TURNO " << i + 1 << " ---" << endl;

        // Giocatore 1
        cout << endl << "Turno del Giocatore 1" << endl;
        cout << "Pesca una carta:" << endl;
        pesca(g1);
        p1_score += cala(g1);
        cout << "Carte in mano: ";
        stampa(g1);
        cout << "Punteggio: " << p1_score << endl;
        if (g1 == NULL) {
            cout << "Fine gioco!! Vince giocatore 1" << endl;
            return 0;
        }

        // Giocatore 2
        cout << endl << "Turno del Giocatore 2" << endl;
        cout << "Pesca una carta:" << endl;
        pesca(g2);
        p2_score += cala(g2);
        cout << "Carte in mano: ";
        stampa(g2);
        cout << "Punteggio: " << p2_score << endl;
        if (g2 == NULL) {
            cout << "Fine gioco!! Vince giocatore 2" << endl;
            return 0;
        }
    }

    cout << endl << "--- PUNTEGGIO FINALE ---" << endl;
    cout << "Giocatore 1: " << p1_score << endl;
    cout << "Giocatore 2: " << p2_score << endl;
    if (p1_score > p2_score) {
        cout << "Vince Giocatore 1" << endl;
    } else if (p2_score > p1_score) {
        cout << "Vince Giocatore 2" << endl;
    } else {
        cout << "Pareggio" << endl;
    }

    return 0;
}
