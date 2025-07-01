#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "coda.h"
#include "grafi.h"
#include "node.h"

using namespace std;

// Forward declarations
void stampa(graph g, node* nodes);
int* totalLike(graph g, node* nodes);
void follow(graph g, node* nodes, int u_id);
node* load_nodes_from_file(const string& filename, int num_nodes);
graph load_graph_from_file(const string& filename);

int main() {
    // Punto 1: Acquisizione del grafo
    graph g = load_graph_from_file("graph");
    
    // Punto 2: Acquisizione del contenuto dei nodi
    node* nodes = load_nodes_from_file("node", get_dim(g));

    cout << "--- Punto 1 & 2: Stampa grafo con archi in formato verbose ---" << endl;
    stampa(g, nodes);
    cout << endl;

    // Punto 3.a: Most Influential People
    cout << "--- Punto 3.a: Most Influential People ---" << endl;
    int* likes = totalLike(g, nodes);
    int max_likes = 0;
    for (int i = 0; i < get_dim(g); ++i) {
        if (likes[i] > max_likes) {
            max_likes = likes[i];
        }
    }

    if (max_likes > 0) {
        for (int i = 0; i < get_dim(g); ++i) {
            if (likes[i] == max_likes) {
                cout << nodes[i].cont << endl;
            }
        }
    }
    cout << endl;

    // Punto 3.b: Follow
    cout << "--- Punto 3.b: Follow ---" << endl;
    int start_node_id;
    cout << "Inserire l'identificativo di un nodo utente: ";
    cin >> start_node_id;

    if (start_node_id > 0 && start_node_id <= get_dim(g) && nodes[start_node_id - 1].tipo == 'U') {
        follow(g, nodes, start_node_id);
    } else {
        cout << "Nodo non valido o non di tipo utente." << endl;
    }

    delete[] nodes;
    delete[] likes;
    
    return 0;
}

graph load_graph_from_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Errore nell'apertura del file: " << filename << endl;
        return new_graph(0);
    }
    
    int num_nodes;
    file >> num_nodes;
    
    graph g = new_graph(num_nodes);
    
    int u, v;
    while (file >> u >> v) {
        add_arc(g, u, v, 1.0);
    }
    
    file.close();
    return g;
}

node* load_nodes_from_file(const string& filename, int num_nodes) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Errore nell'apertura del file: " << filename << endl;
        return nullptr;
    }

    node* nodes = new node[num_nodes];
    string line;

    for (int i = 0; i < num_nodes; ++i) {
        if (getline(file, line)) {
            strncpy(nodes[i].cont, line.c_str(), 80);
            nodes[i].cont[80] = '\0';
        }
        if (getline(file, line)) {
            if (!line.empty()) {
                nodes[i].tipo = line[0];
            }
        }
    }

    file.close();
    return nodes;
}

void stampa(graph g, node* nodes) {
    for (int i = 1; i <= get_dim(g); ++i) {
        adj_list adj = get_adjlist(g, i);
        while (adj != NULL) {
            int j = get_adjnode(adj);
            
            char u_tipo = nodes[i - 1].tipo;
            char v_tipo = nodes[j - 1].tipo;
            string u_cont = nodes[i - 1].cont;
            string v_cont = nodes[j - 1].cont;

            string relazione = "UNKNOWN";
            if (u_tipo == 'U' && v_tipo == 'U') relazione = "FOLLOW";
            else if (u_tipo == 'T' && v_tipo == 'U') relazione = "OWNER";
            else if (u_tipo == 'U' && v_tipo == 'T') relazione = "LIKE";

            cout << u_cont << " " << relazione << " " << v_cont << endl;

            adj = get_nextadj(adj);
        }
    }
}

int* totalLike(graph g, node* nodes) {
    int n = get_dim(g);
    int* user_likes = new int[n](); // Initialize with zeros

    // Step 1: Find ownership: which user owns which tweet
    int* tweet_owner = new int[n](); // tweet_owner[i] stores owner of tweet i
    for(int i=1; i<=n; ++i){
        if(nodes[i-1].tipo == 'T'){
            // Find who owns this tweet
            adj_list adj = get_adjlist(g, i); // Arcs from tweet i
            while(adj != NULL){
                int dest_node = get_adjnode(adj);
                if(nodes[dest_node-1].tipo == 'U'){
                    tweet_owner[i-1] = dest_node;
                    break;
                }
                adj = get_nextadj(adj);
            }
        }
    }

    // Step 2: Count likes for each tweet and attribute to owner
    for (int i = 1; i <= n; ++i) { // User who likes
        if (nodes[i-1].tipo == 'U') {
            adj_list adj = get_adjlist(g, i);
            while (adj != NULL) {
                int liked_node_idx = get_adjnode(adj);
                if (nodes[liked_node_idx-1].tipo == 'T') {
                    int owner_id = tweet_owner[liked_node_idx-1];
                    if(owner_id > 0){
                       user_likes[owner_id - 1]++;
                    }
                }
                adj = get_nextadj(adj);
            }
        }
    }
    
    delete[] tweet_owner;
    return user_likes;
}

void follow(graph g, node* nodes, int u_id) {
    cout << "L'utente " << nodes[u_id - 1].cont << " segue:" << endl;

    int n = get_dim(g);
    bool* visited = new bool[n + 1]();
    
    coda q = newQueue();
    q = enqueue(q, u_id);
    visited[u_id] = true;

    while (!isEmpty(q)) {
        int current_id = dequeue(q);

        adj_list adj = get_adjlist(g, current_id);
        while (adj != NULL) {
            int neighbor_id = get_adjnode(adj);
            // Check for U -> U relationship
            if (nodes[neighbor_id - 1].tipo == 'U' && !visited[neighbor_id]) {
                visited[neighbor_id] = true;
                q = enqueue(q, neighbor_id);
                cout << nodes[neighbor_id - 1].cont << endl;
            }
            adj = get_nextadj(adj);
        }
    }

    delete[] visited;
}
