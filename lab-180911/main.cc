#include <iostream>
#include <cstring>

using namespace std;

#include "tipo.h"
#include "liste.h"

void print_list(lista l) {
    if (l == NULL) {
        cout << "Lista vuota" << endl;
        return;
    }
    
    cout << "Lista: ";
    while (l != NULL) {
        print(head(l));
        l = tail(l);
        if (l != NULL) cout << " -> ";
    }
    cout << endl;
}

lista delete_all_occurrences(lista l, tipo_inf value, bool& found) {
    found = false;
    elem* current = l;
    
    while (current != NULL) {
        elem* next = current->pun;  // Save next before potential deletion
        if (compare(current->inf, value) == 0) {
            l = delete_elem(l, current);
            found = true;
        }
        current = next;
    }
    
    return l;
}

lista create_list(int n, bool sorted) {
    lista l = NULL;
    
    cout << "Inserisci " << n << " valori:" << endl;
    for (int i = 0; i < n; i++) {
        tipo_inf value;
        cout << "Valore " << (i + 1) << ": ";
        cin >> value;
        
        elem* e = new_elem(value);
        if (sorted) {
            l = ord_insert_elem(l, e);
        } else {
            l = insert_elem(l, e);
        }
    }
    
    return l;
}

void search_in_list(lista l, bool is_sorted) {
    tipo_inf value;
    cout << "Inserisci il valore da cercare: ";
    cin >> value;
    
    elem* result;
    if (is_sorted) {
        result = ord_search(l, value);
        cout << "Ricerca ordinata utilizzata." << endl;
    } else {
        result = search(l, value);
        cout << "Ricerca lineare utilizzata." << endl;
    }
    
    if (result != NULL) {
        cout << "Valore " << value << " trovato nella lista." << endl;
    } else {
        cout << "Valore " << value << " non trovato nella lista." << endl;
    }
}

void print_menu() {
    cout << "\n=== GESTIONE LISTE DOPPIE ===" << endl;
    cout << "1. Crea lista non ordinata" << endl;
    cout << "2. Crea lista ordinata" << endl;
    cout << "3. Stampa lista" << endl;
    cout << "4. Cerca valore" << endl;
    cout << "5. Cancella tutte le occorrenze di un valore" << endl;
    cout << "0. Esci" << endl;
    cout << "Scelta: ";
}

int main() {
    lista l = NULL;
    bool is_sorted = false;
    int choice;
    
    cout << "Programma per la gestione di liste doppie" << endl;
    
    do {
        print_menu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                // Delete existing list
                while (l != NULL) {
                    elem* temp = l;
                    l = tail(l);
                    delete temp;
                }
                
                int n;
                cout << "Quanti elementi vuoi inserire? ";
                cin >> n;
                if (n > 0) {
                    l = create_list(n, false);
                    is_sorted = false;
                    cout << "Lista non ordinata creata." << endl;
                }
                break;
            }
            
            case 2: {
                // Delete existing list
                while (l != NULL) {
                    elem* temp = l;
                    l = tail(l);
                    delete temp;
                }
                
                int n;
                cout << "Quanti elementi vuoi inserire? ";
                cin >> n;
                if (n > 0) {
                    l = create_list(n, true);
                    is_sorted = true;
                    cout << "Lista ordinata creata." << endl;
                }
                break;
            }
            
            case 3: {
                print_list(l);
                if (is_sorted) {
                    cout << "(Lista ordinata)" << endl;
                } else {
                    cout << "(Lista non ordinata)" << endl;
                }
                break;
            }
            
            case 4: {
                if (l == NULL) {
                    cout << "Lista vuota. Crea prima una lista." << endl;
                } else {
                    search_in_list(l, is_sorted);
                }
                break;
            }
            
            case 5: {
                if (l == NULL) {
                    cout << "Lista vuota. Crea prima una lista." << endl;
                } else {
                    tipo_inf value;
                    cout << "Inserisci il valore da cancellare: ";
                    cin >> value;
                    
                    bool found;
                    l = delete_all_occurrences(l, value, found);
                    
                    if (found) {
                        cout << "Tutte le occorrenze di " << value << " sono state cancellate." << endl;
                    } else {
                        cout << "Valore " << value << " non trovato nella lista." << endl;
                    }
                }
                break;
            }
            
            case 0: {
                cout << "Uscita dal programma." << endl;
                break;
            }
            
            default: {
                cout << "Scelta non valida. Riprova." << endl;
                break;
            }
        }
        
    } while (choice != 0);
    
    // Cleanup: delete remaining list
    while (l != NULL) {
        elem* temp = l;
        l = tail(l);
        delete temp;
    }
    
    return 0;
}
