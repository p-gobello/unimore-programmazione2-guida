#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "coda.h"
#include "grafi.h"
#include "node.h"

// Function to read and load graph from file
graph load_graph_from_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return new_graph(0);
    }
    
    int num_nodes;
    file >> num_nodes;
    
    graph g = new_graph(num_nodes);
    
    int u, v;
    cout << "Loading graph with " << num_nodes << " nodes from " << filename << ":" << endl;
    
    while (file >> u >> v) {
        cout << "Adding edge: " << u << " -> " << v << endl;
        add_arc(g, u, v, 1.0); // Default weight of 1.0
    }
    
    file.close();
    return g;
}

// Function to read node information from file  
void load_nodes_from_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    
    cout << "\nLoading node information from " << filename << ":" << endl;
    
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            cout << "Node data: " << line << endl;
        }
    }
    
    file.close();
}
void print_graph(graph g) {
    cout << "Graph adjacency lists:" << endl;
    for (int i = 1; i <= get_dim(g); i++) {
        cout << "Node " << i << ": ";
        adj_list current = get_adjlist(g, i);
        while (current != NULL) {
            cout << get_adjnode(current) << "(w:" << current->weight << ") ";
            current = get_nextadj(current);
        }
        cout << endl;
    }
}

// BFS traversal using queue
void bfs_traversal(graph g, int start_node) {
    cout << "\nBFS traversal starting from node " << start_node << ":" << endl;
    
    bool* visited = new bool[get_dim(g) + 1];
    for (int i = 0; i <= get_dim(g); i++) {
        visited[i] = false;
    }
    
    coda q = newQueue();
    q = enqueue(q, start_node);
    visited[start_node] = true;
    
    cout << "Visiting order: ";
    
    while (!isEmpty(q)) {
        int current = dequeue(q);
        cout << current << " ";
        
        // Visit all adjacent nodes
        adj_list adj = get_adjlist(g, current);
        while (adj != NULL) {
            int neighbor = get_adjnode(adj);
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q = enqueue(q, neighbor);
            }
            adj = get_nextadj(adj);
        }
    }
    cout << endl;
    
    delete[] visited;
}

// Demonstrate queue operations
void demonstrate_queue() {
    cout << "=== Queue Operations Demo ===" << endl;
    
    coda q = newQueue();
    
    cout << "Initial queue empty: " << (isEmpty(q) ? "true" : "false") << endl;
    
    // Enqueue some values
    cout << "\nEnqueuing values 10, 20, 30:" << endl;
    q = enqueue(q, 10);
    q = enqueue(q, 20);
    q = enqueue(q, 30);
    
    cout << "Queue empty after enqueuing: " << (isEmpty(q) ? "true" : "false") << endl;
    cout << "First element: " << first(q) << endl;
    
    // Dequeue values
    cout << "\nDequeuing values:" << endl;
    while (!isEmpty(q)) {
        cout << "Dequeued: " << dequeue(q) << endl;
    }
    
    cout << "Queue empty after dequeuing all: " << (isEmpty(q) ? "true" : "false") << endl;
}

int main() {
    cout << "=== Lab 180719: Queue and Graph Implementation ===" << endl;
    
    // Demonstrate queue functionality
    demonstrate_queue();
    
    cout << "\n=== Graph Operations Demo ===" << endl;
    
    // Load graph from file instead of creating manually
    graph g = load_graph_from_file("graph");
    
    if (get_dim(g) == 0) {
        cout << "Failed to load graph from file" << endl;
        return 1;
    }
    
    cout << "\nGraph loaded successfully with " << get_dim(g) << " nodes" << endl;
    
    // Print the graph structure
    print_graph(g);
    
    // Demonstrate BFS traversal using queue
    bfs_traversal(g, 1);
    
    // Load and display node information
    load_nodes_from_file("node");
    
    // Demonstrate finding paths
    cout << "\n=== Path Analysis ===" << endl;
    for (int node = 1; node <= get_dim(g); node++) {
        adj_list adj = get_adjlist(g, node);
        int degree = 0;
        cout << "Node " << node << " connects to: ";
        while (adj != NULL) {
            cout << get_adjnode(adj) << " ";
            degree++;
            adj = get_nextadj(adj);
        }
        cout << "(degree: " << degree << ")" << endl;
    }
    
    cout << "\n=== Program Complete ===" << endl;
    
    return 0;
}
