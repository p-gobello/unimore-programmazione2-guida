/**
 * @file compito.cc
 * @brief Implementation of bipartite graph for product rating system
 * 
 * This program implements a bipartite graph system for managing user ratings
 * of products. Users and products are represented as nodes, and edges represent
 * ratings (1-5 stars) from users to products.
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

#include "grafo.h"
#include "tipo.h"

/**
 * @brief Creates and loads node information from nodi.txt file
 * @param n Reference to store the number of nodes
 * @return Pointer to dynamically allocated array of tipo_inf structures
 */
tipo_inf* creaNodi(int& n) {
    ifstream file("nodi.txt");
    if (!file.is_open()) {
        cout << "Error: Cannot open nodi.txt file" << endl;
        n = 0;
        return NULL;
    }
    
    file >> n;
    file.ignore(); // Skip newline after number
    
    tipo_inf* nodes = new tipo_inf[n];
    
    for (int i = 0; i < n; i++) {
        file.getline(nodes[i].descrizione, 20);
        file >> nodes[i].tipo;
        file.ignore(); // Skip newline after tipo
        
        // Remove trailing spaces from descrizione
        int len = strlen(nodes[i].descrizione);
        while (len > 0 && nodes[i].descrizione[len-1] == ' ') {
            nodes[i].descrizione[len-1] = '\0';
            len--;
        }
    }
    
    file.close();
    return nodes;
}

/**
 * @brief Finds node index by description
 * @param nodes Array of nodes
 * @param dim Number of nodes
 * @param desc Description to search for
 * @return Index of the node, -1 if not found
 */
int findNodeByDescription(tipo_inf* nodes, int dim, const char* desc) {
    for (int i = 0; i < dim; i++) {
        if (strcmp(nodes[i].descrizione, desc) == 0) {
            return i + 1; // Return 1-based index
        }
    }
    return -1;
}

/**
 * @brief Print ratings for each user
 * @param g Graph containing the ratings
 * @param nodes Array of node information
 * @param dim Number of nodes
 */
void stampa(graph g, tipo_inf* nodes, int dim) {
    for (int i = 0; i < dim; i++) {
        if (nodes[i].tipo == 'U') { // User node
            adj_list current = get_adjlist(g, i + 1);
            while (current != NULL) {
                int product_idx = get_adjnode(current) - 1;
                float rating = get_adjweight(current);
                cout << nodes[i].descrizione << " valuta " << (int)rating 
                     << " " << nodes[product_idx].descrizione << endl;
                current = get_nextadj(current);
            }
        }
    }
}

/**
 * @brief Calculate average rating given by a specific user
 * @param account User account name
 * @param g Graph containing the ratings
 * @param nodes Array of node information
 * @param dim Number of nodes
 * @return Average rating, -1 if user not found
 */
float media_utente(char* account, graph g, tipo_inf* nodes, int dim) {
    int user_idx = -1;
    
    // Find user index
    for (int i = 0; i < dim; i++) {
        if (nodes[i].tipo == 'U' && strcmp(nodes[i].descrizione, account) == 0) {
            user_idx = i + 1;
            break;
        }
    }
    
    if (user_idx == -1) {
        return -1; // User not found
    }
    
    adj_list current = get_adjlist(g, user_idx);
    float sum = 0;
    int count = 0;
    
    while (current != NULL) {
        sum += get_adjweight(current);
        count++;
        current = get_nextadj(current);
    }
    
    return (count > 0) ? sum / count : 0;
}

/**
 * @brief Calculate average rating of a specific product
 * @param prod Product name
 * @param g Graph containing the ratings
 * @param nodes Array of node information
 * @param dim Number of nodes
 * @return Average rating, -1 if product not found
 */
float media_prod(char* prod, graph g, tipo_inf* nodes, int dim) {
    int product_idx = -1;
    
    // Find product index
    for (int i = 0; i < dim; i++) {
        if (nodes[i].tipo == 'P' && strcmp(nodes[i].descrizione, prod) == 0) {
            product_idx = i + 1;
            break;
        }
    }
    
    if (product_idx == -1) {
        return -1; // Product not found
    }
    
    float sum = 0;
    int count = 0;
    
    // Search through all users to find ratings for this product
    for (int i = 0; i < dim; i++) {
        if (nodes[i].tipo == 'U') {
            adj_list current = get_adjlist(g, i + 1);
            while (current != NULL) {
                if (get_adjnode(current) == product_idx) {
                    sum += get_adjweight(current);
                    count++;
                    break;
                }
                current = get_nextadj(current);
            }
        }
    }
    
    return (count > 0) ? sum / count : 0;
}

/**
 * @brief Suggest products to a user based on similar ratings
 * @param account User account name
 * @param prod Product that the user has rated
 * @param g Graph containing the ratings
 * @param nodes Array of node information
 * @param dim Number of nodes
 */
void suggerisci(char* account, char* prod, graph g, tipo_inf* nodes, int dim) {
    int user_idx = -1, product_idx = -1;
    float user_rating = 0;
    
    // Find user and product indices
    for (int i = 0; i < dim; i++) {
        if (nodes[i].tipo == 'U' && strcmp(nodes[i].descrizione, account) == 0) {
            user_idx = i + 1;
        }
        if (nodes[i].tipo == 'P' && strcmp(nodes[i].descrizione, prod) == 0) {
            product_idx = i + 1;
        }
    }
    
    if (user_idx == -1 || product_idx == -1) {
        return; // User or product not found
    }
    
    // Find user's rating for the specified product
    adj_list current = get_adjlist(g, user_idx);
    bool found_rating = false;
    while (current != NULL) {
        if (get_adjnode(current) == product_idx) {
            user_rating = get_adjweight(current);
            found_rating = true;
            break;
        }
        current = get_nextadj(current);
    }
    
    if (!found_rating) {
        return; // User hasn't rated this product
    }
    
    // Find other users who rated the same product with the same rating
    for (int i = 0; i < dim; i++) {
        if (nodes[i].tipo == 'U' && i + 1 != user_idx) {
            adj_list user_ratings = get_adjlist(g, i + 1);
            bool same_rating = false;
            
            // Check if this user rated the product with the same rating
            while (user_ratings != NULL) {
                if (get_adjnode(user_ratings) == product_idx && 
                    get_adjweight(user_ratings) == user_rating) {
                    same_rating = true;
                    break;
                }
                user_ratings = get_nextadj(user_ratings);
            }
            
            if (same_rating) {
                // Find products this user rated with at least 3 stars
                user_ratings = get_adjlist(g, i + 1);
                while (user_ratings != NULL) {
                    int other_product = get_adjnode(user_ratings);
                    float rating = get_adjweight(user_ratings);
                    
                    if (other_product != product_idx && rating >= 3) {
                        // Check if the original user hasn't rated this product
                        bool already_rated = false;
                        adj_list original_user_ratings = get_adjlist(g, user_idx);
                        while (original_user_ratings != NULL) {
                            if (get_adjnode(original_user_ratings) == other_product) {
                                already_rated = true;
                                break;
                            }
                            original_user_ratings = get_nextadj(original_user_ratings);
                        }
                        
                        if (!already_rated) {
                            cout << "Suggerimento: " << nodes[other_product - 1].descrizione << endl;
                        }
                    }
                    user_ratings = get_nextadj(user_ratings);
                }
            }
        }
    }
}

/**
 * @brief Main function - orchestrates the entire program
 * @return 0 on success
 */
int main() {
    int n;
    tipo_inf* nodes = creaNodi(n);
    
    if (nodes == NULL) {
        cout << "Error loading nodes" << endl;
        return 1;
    }
    
    // Create graph
    graph g = new_graph(n);
    
    // Load ratings from valutazioni.txt
    ifstream ratings_file("valutazioni.txt");
    if (!ratings_file.is_open()) {
        cout << "Error: Cannot open valutazioni.txt file" << endl;
        delete[] nodes;
        return 1;
    }
    
    string user, product;
    float rating;
    
    while (ratings_file >> user >> product >> rating) {
        int user_idx = findNodeByDescription(nodes, n, user.c_str());
        int product_idx = findNodeByDescription(nodes, n, product.c_str());
        
        if (user_idx != -1 && product_idx != -1) {
            add_arc(g, user_idx, product_idx, rating);
        }
    }
    ratings_file.close();
    
    // Print ratings for each user
    cout << "=== Stampa valutazioni per utente ===" << endl;
    stampa(g, nodes, n);
    cout << endl;
    
    // Test media-utente
    char account[20];
    cout << "Inserisci account per calcolare media utente: ";
    cin >> account;
    float avg_user = media_utente(account, g, nodes, n);
    if (avg_user >= 0) {
        cout << avg_user << endl;
    } else {
        cout << "Utente non trovato" << endl;
    }
    cout << endl;
    
    // Test suggerisci
    char prod_name[20];
    cout << "Inserisci account per suggerimenti: ";
    cin >> account;
    cout << "Inserisci prodotto valutato: ";
    cin >> prod_name;
    suggerisci(account, prod_name, g, nodes, n);
    cout << endl;
    
    // Test media-prod
    cout << "Inserisci prodotto per calcolare media: ";
    cin >> prod_name;
    float avg_prod = media_prod(prod_name, g, nodes, n);
    if (avg_prod >= 0) {
        cout << avg_prod << endl;
    } else {
        cout << "Prodotto non trovato" << endl;
    }
    
    delete[] nodes;
    return 0;
}
