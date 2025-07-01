#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "tipo.h"
#include "liste.h"

using namespace std;

void demazziere(lista& mazzo, lista& g1, lista& g2) {
    while (mazzo != NULL) {
        elem* card = new_elem(head(mazzo));
        g1 = insert_elem(g1, card);
        mazzo = tail(mazzo);
        if (mazzo != NULL) {
            card = new_elem(head(mazzo));
            g2 = insert_elem(g2, card);
            mazzo = tail(mazzo);
        }
    }
}

void print_list(lista l) {
    while (l != NULL) {
        print(head(l));
        l = tail(l);
    }
}

int main() {
    srand(time(NULL));

    lista mazzo = NULL;
    char semi[] = {'C', 'Q', 'F', 'P'};

    // Create deck
    for (int s = 0; s < 4; s++) {
        for (int v = 1; v <= 10; v++) {
            tipo_inf card;
            card.seme = semi[s];
            card.valore = v;
            mazzo = insert_elem(mazzo, new_elem(card));
        }
    }

    // Shuffle deck
    for (int i = 0; i < 100; i++) {
        int r1 = rand() % 40;
        int r2 = rand() % 40;
        elem* e1 = mazzo;
        for (int j = 0; j < r1; j++) e1 = tail(e1);
        elem* e2 = mazzo;
        for (int j = 0; j < r2; j++) e2 = tail(e2);
        tipo_inf tmp = e1->inf;
        e1->inf = e2->inf;
        e2->inf = tmp;
    }

    lista g1 = NULL;
    lista g2 = NULL;

    demazziere(mazzo, g1, g2);

    cout << "Giocatore 1:" << endl;
    print_list(g1);
    cout << endl;

    cout << "Giocatore 2:" << endl;
    print_list(g2);
    cout << endl;

    return 0;
}
