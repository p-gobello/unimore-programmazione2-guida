#include <iostream>
#include <fstream>
using namespace std;

#include "tipo.h"
#include "bst.h"

// Function to print BST in order (left-root-right)
void print_in_order(bst tree) {
    if (tree != NULL) {
        print_in_order(get_left(tree));
        cout << "Key: " << get_key(tree) << " - Card: ";
        print(get_value(tree));
        cout << endl;
        print_in_order(get_right(tree));
    }
}

// Function to count nodes in BST
int count_nodes(bst tree) {
    if (tree == NULL) return 0;
    return 1 + count_nodes(get_left(tree)) + count_nodes(get_right(tree));
}

// Function to find minimum key in BST
tipo_key find_min_key(bst tree) {
    if (tree == NULL) return -1;
    while (get_left(tree) != NULL) {
        tree = get_left(tree);
    }
    return get_key(tree);
}

// Function to find maximum key in BST
tipo_key find_max_key(bst tree) {
    if (tree == NULL) return -1;
    while (get_right(tree) != NULL) {
        tree = get_right(tree);
    }
    return get_key(tree);
}

int main() {
    cout << "=== Laboratorio 180618: Gestione BST con Carte ===" << endl;
    
    bst tree = NULL;
    int choice;
    
    do {
        cout << "\n=== MENU ===" << endl;
        cout << "1. Inserisci carta" << endl;
        cout << "2. Cerca carta per chiave" << endl;
        cout << "3. Elimina carta per chiave" << endl;
        cout << "4. Stampa BST in ordine" << endl;
        cout << "5. Statistiche BST" << endl;
        cout << "6. Inserisci carte predefinite" << endl;
        cout << "0. Esci" << endl;
        cout << "Scelta: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                tipo_key key;
                char seme;
                int valore;
                
                cout << "Inserisci chiave: ";
                cin >> key;
                cout << "Inserisci seme (C/Q/F/P): ";
                cin >> seme;
                cout << "Inserisci valore (1-13): ";
                cin >> valore;
                
                tipo_inf carta = {seme, valore};
                bnode* nuovo_nodo = bst_newNode(key, carta);
                bst_insert(tree, nuovo_nodo);
                
                cout << "Carta inserita: ";
                print(carta);
                cout << " con chiave " << key << endl;
                break;
            }
            
            case 2: {
                tipo_key key;
                cout << "Inserisci chiave da cercare: ";
                cin >> key;
                
                bnode* trovato = bst_search(tree, key);
                if (trovato) {
                    cout << "Carta trovata con chiave " << key << ": ";
                    print(get_value(trovato));
                    cout << endl;
                } else {
                    cout << "Nessuna carta trovata con chiave " << key << endl;
                }
                break;
            }
            
            case 3: {
                tipo_key key;
                cout << "Inserisci chiave da eliminare: ";
                cin >> key;
                
                bnode* da_eliminare = bst_search(tree, key);
                if (da_eliminare) {
                    cout << "Eliminando carta: ";
                    print(get_value(da_eliminare));
                    cout << endl;
                    bst_delete(tree, da_eliminare);
                    cout << "Carta eliminata con successo" << endl;
                } else {
                    cout << "Nessuna carta trovata con chiave " << key << endl;
                }
                break;
            }
            
            case 4: {
                if (tree == NULL) {
                    cout << "BST vuoto" << endl;
                } else {
                    cout << "\nBST in ordine crescente di chiavi:" << endl;
                    print_in_order(tree);
                }
                break;
            }
            
            case 5: {
                int num_nodi = count_nodes(tree);
                cout << "\n=== Statistiche BST ===" << endl;
                cout << "Numero di nodi: " << num_nodi << endl;
                
                if (num_nodi > 0) {
                    cout << "Chiave minima: " << find_min_key(tree) << endl;
                    cout << "Chiave massima: " << find_max_key(tree) << endl;
                } else {
                    cout << "BST vuoto" << endl;
                }
                break;
            }
            
            case 6: {
                cout << "Inserimento carte predefinite..." << endl;
                
                // Carte di esempio
                tipo_inf carte[] = {
                    {'P', 1},   // Asso di Picche
                    {'C', 13},  // Re di Cuori
                    {'Q', 7},   // 7 di Quadri
                    {'F', 11},  // Fante di Fiori
                    {'P', 13},  // Re di Picche
                    {'C', 1},   // Asso di Cuori
                    {'Q', 12},  // Regina di Quadri
                    {'F', 5}    // 5 di Fiori
                };
                
                tipo_key chiavi[] = {1, 13, 7, 11, 15, 2, 12, 5};
                
                for (int i = 0; i < 8; i++) {
                    bnode* nuovo_nodo = bst_newNode(chiavi[i], carte[i]);
                    bst_insert(tree, nuovo_nodo);
                    cout << "Inserita: ";
                    print(carte[i]);
                    cout << " con chiave " << chiavi[i] << endl;
                }
                break;
            }
            
            case 0:
                cout << "Uscita dal programma" << endl;
                break;
                
            default:
                cout << "Scelta non valida" << endl;
                break;
        }
        
    } while (choice != 0);
    
    cout << "\n=== Programma terminato ===" << endl;
    return 0;
}
