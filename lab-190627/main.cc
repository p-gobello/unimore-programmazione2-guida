#include <iostream>
#include <fstream>
#include <cstring>
#include "grafo.h"
#include "liste.h"
#include "tipo.h"

using namespace std;

// Funzione per contare le righe in un file per determinare il numero di nodi/POI
int count_lines(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Errore nell'apertura del file " << filename << endl;
        return 0;
    }
    int count = 0;
    string line;
    while (getline(file, line)) {
        count++;
    }
    file.close();
    return count;
}

// Funzione per caricare i Punti di Interesse da file
void load_pois(const char* filename, tipo_inf* pois, int num_pois) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Errore nell'apertura del file " << filename << endl;
        return;
    }
    for (int i = 0; i < num_pois; ++i) {
        file >> pois[i].id >> pois[i].nome >> pois[i].tipo;
    }
    file.close();
}

// Funzione per caricare il grafo da file
void load_graph(const char* filename, graph& g) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Errore nell'apertura del file " << filename << endl;
        return;
    }
    int u, v;
    float w;
    while (file >> u >> v >> w) {
        add_edge(g, u, v, w);
    }
    file.close();
}

int main() {
    const char* poi_filename = "PI.txt";
    const char* graph_filename = "G.txt";

    // 1. Contare i POI per sapere la dimensione del grafo
    int num_pois = count_lines(poi_filename);
    if (num_pois == 0) {
        return 1;
    }

    // 2. Creare e caricare l'array di POI
    tipo_inf* pois = new tipo_inf[num_pois];
    load_pois(poi_filename, pois, num_pois);

    // 3. Creare e caricare il grafo
    graph g = new_graph(num_pois);
    load_graph(graph_filename, g);

    // 4. Creare e popolare le liste per tipo di POI
    lista musei = NULL;
    lista edifici = NULL;
    lista piazze = NULL;

    for (int i = 0; i < num_pois; ++i) {
        switch (pois[i].tipo) {
            case 'm':
                musei = ord_insert_elem(musei, create_elem(pois[i]));
                break;
            case 'e':
                edifici = ord_insert_elem(edifici, create_elem(pois[i]));
                break;
            case 'p':
                piazze = ord_insert_elem(piazze, create_elem(pois[i]));
                break;
        }
    }

    // 5. Stampare i risultati
    cout << "--- MUSEI ---" << endl;
    print_list(musei);
    cout << endl;

    cout << "--- EDIFICI ---" << endl;
    print_list(edifici);
    cout << endl;

    cout << "--- PIAZZE ---" << endl;
    print_list(piazze);
    cout << endl;

    cout << "--- GRAFO ---" << endl;
    print_graph(g);
    cout << endl;

    // Deallocazione della memoria
    delete[] pois;
    // Aggiungere qui la deallocazione per il grafo e le liste se necessario

    return 0;
}
