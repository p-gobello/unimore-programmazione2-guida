#include <iostream>
#include <fstream>
#include <cstring>
#include "grafo.h"
#include "liste.h"
#include "tipo.h"

using namespace std;

// Punto 1:
int carica(lista& pi) {
    ifstream file("PI.txt");
    if (!file) {
        cout << "Errore apertura file PI.txt" << endl;
        return 0;
    }
    int count = 0;
    tipo_inf p;
    while (file >> p.id) {
        file.ignore(); 
        file.getline(p.nome, 21);
        file >> p.tipo;
        
        elem* e = create_elem(p);
        pi = ord_insert_elem(pi, e);
        count++;
    }
    file.close();
    return count;
}

tipo_inf search_pi(lista pi, int id) {
    tipo_inf p_search;
    p_search.id = id;
    elem* e = ord_search(pi, p_search);
    if (e != NULL) {
        return head(e);
    } else {
        tipo_inf not_found;
        not_found.id = -1;
        strcpy(not_found.nome, "NON TROVATO");
        not_found.tipo = ' ';
        return not_found;
    }
}

// Punto 2.a:
graph mappa(int n) {
    graph g = new_graph(n);
    ifstream file("G.txt");
    if (!file) {
        cout << "Errore apertura file G.txt" << endl;
        return g;
    }
    int u, v;
    while (file >> u >> v) {
        // Il grafo non è orientato, il peso non è specificato
        add_edge(g, u, v, 1.0f); 
    }
    file.close();
    return g;
}

void stampa_mappa(graph g, lista pi) {
    cout << "\n--- Mappa della citta' ---" << endl;
    for (int i = 1; i <= get_dim(g); i++) {
        tipo_inf current_pi = search_pi(pi, i);
        if (current_pi.id != -1) {
            cout << current_pi.nome << " connesso a: ";
            adj_list adj = get_adjlist(g, i);
            while (adj != NULL) {
                int adj_node_id = get_adjnode(adj);
                tipo_inf adj_pi = search_pi(pi, adj_node_id);
                if (adj_pi.id != -1) {
                    cout << adj_pi.nome;
                    if(get_nextadj(adj) != NULL) cout << ", ";
                }
                adj = get_nextadj(adj);
            }
            cout << endl;
        }
    }
}

// Punto 3.a
void trip_recursive(graph g, int u, lista pi, char target_type, bool visited[]) {
    visited[u-1] = true;
    
    tipo_inf pi_u = search_pi(pi, u);
    cout << pi_u.id << " ";

    adj_list adj = get_adjlist(g, u);
    while (adj != NULL) {
        int v = get_adjnode(adj);
        if (!visited[v-1]) {
            tipo_inf pi_v = search_pi(pi, v);
            if (pi_v.id != -1 && pi_v.tipo == target_type) {
                trip_recursive(g, v, pi, target_type, visited);
            }
        }
        adj = get_nextadj(adj);
    }
}

void trip(graph g, int node_id, lista pi) {
    tipo_inf start_pi = search_pi(pi, node_id);
    if (start_pi.id == -1) {
        cout << "Nodo di partenza non trovato." << endl;
        return;
    }
    
    bool* visited = new bool[get_dim(g)];
    for (int i = 0; i < get_dim(g); i++) {
        visited[i] = false;
    }

    cout << "\nPercorso omogeneo da " << node_id << " (tipo '" << start_pi.tipo << "'): ";
    
    // Marco il nodo di partenza come visitato ma lo escludo dalla stampa iniziale
    visited[node_id-1] = true;

    adj_list adj = get_adjlist(g, node_id);
    while(adj != NULL){
        int v = get_adjnode(adj);
        if(!visited[v-1]){
            tipo_inf pi_v = search_pi(pi, v);
            if(pi_v.id != -1 && pi_v.tipo == start_pi.tipo){
                trip_recursive(g, v, pi, start_pi.tipo, visited);
            }
        }
        adj = get_nextadj(adj);
    }
    cout << endl;

    delete[] visited;
}

// Punto 2.b
lista genera(lista pi, char tipo) {
    lista result_list = NULL;
    lista current = pi;
    while (current != NULL) {
        if (head(current).tipo == tipo) {
            elem* new_e = create_elem(head(current));
            result_list = ord_insert_elem(result_list, new_e);
        }
        current = tail(current);
    }
    return result_list;
}

int main() {
    lista points_of_interest = NULL;
    int num_pi = carica(points_of_interest);
    cout << "Caricati " << num_pi << " punti di interesse." << endl;
    
    // Punto 1 test
    int id_to_find;
    cout << "\n--- Test Punto 1: Ricerca PI per ID ---" << endl;
    cout << "Inserisci l'ID del punto di interesse da cercare (-1 per saltare): ";
    cin >> id_to_find;
    while(id_to_find != -1) {
        tipo_inf result = search_pi(points_of_interest, id_to_find);
        if (result.id != -1) {
            cout << "Punto di interesse trovato: ";
            print(result);
        } else {
            cout << "Punto di interesse con ID " << id_to_find << " non trovato." << endl;
        }
        cout << "\nInserisci l'ID del punto di interesse da cercare (-1 per saltare): ";
        cin >> id_to_find;
    }

    // Punto 2.a: Creazione e stampa mappa
    cout << "\n--- Punto 2.a: Caricamento e stampa mappa ---" << endl;
    graph city_map = mappa(num_pi);
    stampa_mappa(city_map, points_of_interest);

    // Punto 3.a: Test trip
    cout << "\n--- Punto 3.a: Ricerca percorso omogeneo ---" << endl;
    cout << "Inserisci l'ID del punto di interesse di partenza per il trip (-1 per saltare): ";
    cin >> id_to_find;
    if(id_to_find != -1) {
        trip(city_map, id_to_find, points_of_interest);
    }

    // Punto 2.b: Test genera
    cout << "\n--- Punto 2.b: Genera lista per tipo ---" << endl;
    char tipo_to_find;
    cout << "Inserisci il tipo di PI da elencare ('n' per saltare): ";
    cin >> tipo_to_find;
    if(tipo_to_find != 'n') {
        lista filtered_list = genera(points_of_interest, tipo_to_find);
        cout << "Lista dei PI di tipo '" << tipo_to_find << "':" << endl;
        print_list(filtered_list);
    }

    return 0;
} 