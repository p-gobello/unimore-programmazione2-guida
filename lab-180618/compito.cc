#include <iostream>
#include "bst.h"

using namespace std;

// Funzione per stampare il BST in-order (Punto 2)
void stampa_bst_in_ordine(bst b) {
    if (b != NULL) {
        stampa_bst_in_ordine(get_left(b));
        cout << get_key(b) << " ";
        print(get_value(b));
        cout << endl;
        stampa_bst_in_ordine(get_right(b));
    }
}

// Funzione ricorsiva per calcolare la somma dei punti (Punto 2.b)
int totalePunti_rec(bst b, tipo_key min_key, tipo_key max_key) {
    if (b == NULL) {
        return 0;
    }

    int sum = 0;
    tipo_key current_key = get_key(b);

    if (current_key > min_key) {
        sum += totalePunti_rec(get_left(b), min_key, max_key);
    }

    if (current_key >= min_key && current_key <= max_key) {
        sum += get_value(b).punti;
    }

    if (current_key < max_key) {
        sum += totalePunti_rec(get_right(b), min_key, max_key);
    }

    return sum;
}

// Funzione wrapper per totalePunti (Punto 2.b)
int totalePunti(bst b, tipo_key min_key, tipo_key max_key) {
    return totalePunti_rec(b, min_key, max_key);
}

// Funzione per stampare le carte che non hanno effettuato acquisti (Punto 4)
void stampa_non_aggiornati(bst all_cards, bst purchased_cards) {
    if (all_cards == NULL) {
        return;
    }
    stampa_non_aggiornati(get_left(all_cards), purchased_cards);
    
    if (bst_search(purchased_cards, get_key(all_cards)) == NULL) {
        cout << get_key(all_cards) << " ";
        print(get_value(all_cards));
        cout << endl;
    }

    stampa_non_aggiornati(get_right(all_cards), purchased_cards);
}

int main() {
    bst tree = NULL;
    int n;

    cout << "Quante carte vuoi inserire? ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        tipo_key key;
        tipo_inf inf;

        cout << "Inserisci codice carta: ";
        cin >> key;

        cout << "Inserisci nome e cognome: ";
        cin.ignore();
        cin.getline(inf.nome_cognome, 41);

        cout << "Inserisci punti: ";
        cin >> inf.punti;

        bnode* node = bst_newNode(key, inf);
        bst_insert(tree, node);
    }
    cout << endl;

    cout << "Punto 2: Stampa delle carte in ordine crescente di codice:" << endl;
    stampa_bst_in_ordine(tree);
    cout << endl;

    // Punto 2.b
    cout << "Punto 2.b: Calcolo totale punti in un intervallo" << endl;
    tipo_key min_k, max_k;
    cout << "Inserisci estremo inferiore codice carta: ";
    cin >> min_k;
    cout << "Inserisci estremo superiore codice carta: ";
    cin >> max_k;
    int punti_totali = totalePunti(tree, min_k, max_k);
    cout << "Il totale dei punti per le carte nell'intervallo [" << min_k << ", " << max_k << "] e': " << punti_totali << endl;
    cout << endl;

    // Punto 3 e 4
    cout << "Punto 3: Aggiornamento punti per acquisti" << endl;
    cout << "Inserisci gli acquisti (codice_carta punti). Inserisci una lettera per terminare." << endl;
    
    bst acquisti_tree = NULL;
    tipo_key acquisto_key;
    int punti_acq;

    while (cin >> acquisto_key) {
        cin >> punti_acq;
        
        bnode* card_node = bst_search(tree, acquisto_key);
        if (card_node != NULL) {
            card_node->inf.punti += punti_acq;
            
            if(bst_search(acquisti_tree, acquisto_key) == NULL) {
                tipo_inf dummy_inf = {"", 0}; 
                bnode* acquisto_node = bst_newNode(acquisto_key, dummy_inf);
                bst_insert(acquisti_tree, acquisto_node);
            }
        } else {
             cout << "Errore: carta " << acquisto_key << " non trovata." << endl;
        }
    }

    cout << endl << "Stampa del BST dopo aggiornamenti:" << endl;
    stampa_bst_in_ordine(tree);
    cout << endl;

    cout << "Punto 4: Stampa delle carte senza acquisti in giornata:" << endl;
    stampa_non_aggiornati(tree, acquisti_tree);
    cout << endl;
    
    return 0;
} 