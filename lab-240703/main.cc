#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#include "tipo.h"
#include "bst.h"

// Function to read hotels from file and insert into BST
void load_hotels_from_file(bst& tree, const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Errore: impossibile aprire il file " << filename << endl;
        return;
    }
    
    int num_hotels;
    file >> num_hotels;
    
    cout << "Caricamento di " << num_hotels << " hotel dal file..." << endl;
    
    for (int i = 0; i < num_hotels; i++) {
        int rating;
        char nome[50], citta[30];
        
        file >> rating;
        file.ignore(); // ignore newline after rating
        file.getline(nome, 50);
        file.getline(citta, 30);
        
        tipo_inf hotel_info;
        strcpy(hotel_info.nome, nome);
        strcpy(hotel_info.citta, citta);
        
        bnode* new_node = bst_newNode(rating, hotel_info);
        bst_insert(tree, new_node);
        
        cout << "Inserito: " << rating << " stelle - ";
        print(hotel_info);
        cout << endl;
    }
    
    file.close();
}

// Function to print BST in order (descending rating due to reverse comparison)
void print_inorder(bst root) {
    if (root != NULL) {
        print_inorder(get_left(root));
        print_key(get_key(root));
        cout << " stelle - ";
        print(get_value(root));
        cout << endl;
        print_inorder(get_right(root));
    }
}

// Function to find and print hotels with specific rating
void find_hotels_by_rating(bst root, int target_rating) {
    cout << "\nRicerca hotel con " << target_rating << " stelle:" << endl;
    bnode* found = bst_search(root, target_rating);
    
    if (found != NULL) {
        cout << "Trovato: ";
        print_key(get_key(found));
        cout << " stelle - ";
        print(get_value(found));
        cout << endl;
    } else {
        cout << "Nessun hotel trovato con " << target_rating << " stelle." << endl;
    }
}

int main() {
    bst hotel_tree = NULL;
    
    cout << "=== Sistema di Gestione Hotel con BST ===" << endl;
    cout << "Nota: L'ordinamento è in ordine inverso (5 stelle a sinistra, 1 stella a destra)" << endl << endl;
    
    // Load hotels from file
    load_hotels_from_file(hotel_tree, "hotel.txt");
    
    cout << "\n=== Hotel ordinati per rating (decrescente) ===" << endl;
    print_inorder(hotel_tree);
    
    // Test search functionality
    find_hotels_by_rating(hotel_tree, 5);
    find_hotels_by_rating(hotel_tree, 3);
    find_hotels_by_rating(hotel_tree, 1);
    find_hotels_by_rating(hotel_tree, 6); // Should not be found
    
    // Test deletion
    cout << "\n=== Test di eliminazione ===" << endl;
    bnode* to_delete = bst_search(hotel_tree, 3);
    if (to_delete != NULL) {
        cout << "Eliminazione hotel con 3 stelle: ";
        print(get_value(to_delete));
        cout << endl;
        bst_delete(hotel_tree, to_delete);
        
        cout << "\nHotel dopo eliminazione:" << endl;
        print_inorder(hotel_tree);
    }
    
    return 0;
}
