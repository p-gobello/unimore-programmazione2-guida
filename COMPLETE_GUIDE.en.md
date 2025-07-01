# Complete C++ Programming Guide for Data Structures and Algorithms

## 📚 Table of Contents
1. [Lists (Single, Double, and Ordered)](#1-lists)
2. [Graphs Implementation](#2-graphs)
3. [Doxygen Documentation](#3-doxygen)
4. [File I/O with fstream](#4-file-io)
5. [BST Ordering and Traversal](#5-bst-operations)
6. [String and char[] Operations](#6-strings)
7. [Sorting Algorithms](#7-sorting)
8. [Dijkstra and Prim Algorithms](#8-graph-algorithms)
9. [Makefile Template](#9-makefile)

---

## 1. Lists (Single, Double, and Ordered) {#1-lists}

### 📋 Core Data Structures

```cpp
// Generic node structure for double linked list
struct Node {
    TipoInf info;        // TipoInf represents the data type
    Node* next;          // Pointer to next node
    Node* prev;          // Pointer to previous node
};

typedef Node* Lista;     // Lista is a pointer to the first node (head)
```

### 🔑 Key Concepts

**Single vs Double Lists:**
- **Single**: Only `next` pointer, forward traversal only
- **Double**: Both `next` and `prev` pointers, bidirectional traversal
- **Ordered**: Maintains sorted order during insertion

### 🚀 Essential Operations

#### Head Insertion (Double List)
```cpp
Lista inserisciInTesta(Lista head, Node* nuovo) {
    nuovo->next = head;          // Connect new node to beginning
    nuovo->prev = NULL;          // Previous of new head is NULL
    if (head != NULL) {
        head->prev = nuovo;      // Connect old head back to new node
    }
    return nuovo;                // New node becomes the head
}
```

#### List Traversal and Printing
```cpp
void stampaLista(Lista head) {
    Node* curr = head;
    while (curr != NULL) {
        stampaInfo(curr->info);  // Print info (adapt to your TipoInf)
        curr = curr->next;
    }
}

// Reverse printing for double lists
void stampaListaInversa(Lista head) {
    // First, reach the tail
    Node* curr = head;
    while (curr != NULL && curr->next != NULL) {
        curr = curr->next;
    }
    
    // Then traverse backwards
    while (curr != NULL) {
        stampaInfo(curr->info);
        curr = curr->prev;
    }
}
```

#### Node Removal (Double List)
```cpp
Lista eliminaNodo(Lista head, Node* daEliminare) {
    if (head == daEliminare) {
        head = head->next;       // If removing head, update head
    }
    
    // Reconnect neighbors
    if (daEliminare->prev != NULL) {
        daEliminare->prev->next = daEliminare->next;
    }
    if (daEliminare->next != NULL) {
        daEliminare->next->prev = daEliminare->prev;
    }
    
    delete daEliminare;          // Deallocate node
    return head;
}
```

#### Ordered Insertion
```cpp
Lista inserisciOrdinato(Lista head, Node* nuovo) {
    if (head == NULL || confronta(nuovo->info, head->info) <= 0) {
        return inserisciInTesta(head, nuovo);
    }
    
    // Find correct position
    Node* curr = head;
    while (curr->next != NULL && confronta(nuovo->info, curr->next->info) > 0) {
        curr = curr->next;
    }
    
    // Insert nuovo after curr
    nuovo->next = curr->next;
    nuovo->prev = curr;
    if (curr->next != NULL) {
        curr->next->prev = nuovo;
    }
    curr->next = nuovo;
    
    return head;
}
```

### 🔧 Comparison Function Template

The `confronta` function should return:
- `< 0` if `a < b`
- `= 0` if `a == b`  
- `> 0` if `a > b`

```cpp
// For integers
int confronta(int a, int b) {
    return a - b;
}

// For custom structures (e.g., by date then time)
int confronta(Appuntamento a, Appuntamento b) {
    if (a.data != b.data) return a.data - b.data;
    return a.ora - b.ora;
}
```

### 📝 Common List Patterns

#### Search in List
```cpp
Node* cerca(Lista head, TipoInf x) {
    Node* curr = head;
    while (curr != NULL) {
        if (confronta(curr->info, x) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;  // Not found
}
```

#### List Length
```cpp
int lunghezzaLista(Lista head) {
    int count = 0;
    Node* curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}
```

#### Memory Cleanup
```cpp
void distruggiLista(Lista& head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
```

---

## 2. Graphs Implementation {#2-graphs}

### 📋 Core Data Structures

```cpp
struct adj_node {
    int node;           // Adjacent vertex (0-indexed internally)
    float weight;       // Edge weight
    adj_node* next;     // Pointer to next adjacent node
};

typedef adj_node* adj_list;

typedef struct {
    adj_list* nodes;    // Array of adjacency lists
    int dim;           // Number of vertices
} graph;
```

### 🔑 Key Concept: **1-indexed Interface, 0-indexed Storage**

| User Input | Internal Storage |
|------------|------------------|
| Node 1     | Index 0         |
| Node 2     | Index 1         |
| Node n     | Index n-1       |

### 🚀 Essential Functions

#### Graph Creation
```cpp
graph new_graph(int n);  // Creates graph with n vertices (1 to n)
```

#### Adding Edges
```cpp
add_arc(g, u, v, weight);    // Directed edge: u → v
add_edge(g, u, v, weight);   // Undirected edge: u ↔ v
```

#### Graph Access
```cpp
int size = get_dim(g);                    // Get number of vertices
adj_list neighbors = get_adjlist(g, u);   // Get adjacency list of vertex u
int vertex = get_adjnode(neighbors);      // Get vertex from adj_node
adj_list next = get_nextadj(neighbors);   // Get next node in list
```

### 📝 Standard Traversal Pattern

```cpp
// Template for visiting all neighbors of vertex u
adj_list current = get_adjlist(g, u);
while (current != NULL) {
    int neighbor = get_adjnode(current);
    float weight = current->weight;
    
    // DO SOMETHING with neighbor and weight
    
    current = get_nextadj(current);
}
```

### 🔥 Common Operations

#### DFS Traversal
```cpp
void dfs(graph g, int u, vector<bool>& visited) {
    visited[u-1] = true;  // Convert to 0-indexed for visited array
    cout << u << " ";
    
    adj_list current = get_adjlist(g, u);
    while (current != NULL) {
        int v = get_adjnode(current);
        if (!visited[v-1]) {  // Convert to 0-indexed
            dfs(g, v, visited);
        }
        current = get_nextadj(current);
    }
}
```

#### BFS Traversal
```cpp
void bfs(graph g, int start) {
    vector<bool> visited(get_dim(g), false);
    queue<int> q;
    
    q.push(start);
    visited[start-1] = true;  // Convert to 0-indexed
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";
        
        adj_list current = get_adjlist(g, u);
        while (current != NULL) {
            int v = get_adjnode(current);
            if (!visited[v-1]) {  // Convert to 0-indexed
                visited[v-1] = true;
                q.push(v);
            }
            current = get_nextadj(current);
        }
    }
}
```

---

## 3. Doxygen Documentation {#3-doxygen}

### 🚀 Initialize Doxygen

```bash
doxygen -g Doxyfile
```

### ⚙️ Configure Doxyfile

```bash
# Project information
PROJECT_NAME           = "Your Project Name"
PROJECT_NUMBER         = "1.0"
PROJECT_BRIEF          = "Brief description"

# Input settings
INPUT                  = .
RECURSIVE              = YES
FILE_PATTERNS          = *.cpp *.h *.hpp *.cc *.cxx *.c++

# Output settings
OUTPUT_DIRECTORY       = ./doc
GENERATE_HTML          = YES
GENERATE_LATEX         = YES

# Documentation extraction
EXTRACT_ALL            = YES
EXTRACT_PRIVATE        = YES
EXTRACT_STATIC         = YES

# Graphs and diagrams
HAVE_DOT               = YES
CALL_GRAPH             = YES
CALLER_GRAPH           = YES
CLASS_DIAGRAMS         = YES
```

### 📝 Documentation Syntax

#### Header File Documentation
```cpp
/**
 * @file example.h
 * @brief Brief description of the file
 * @author Your Name
 * @date 2025-07-01
 */

/**
 * @class Calculator
 * @brief A simple calculator class
 * 
 * This class provides basic arithmetic operations
 * for integer values.
 */
class Calculator {
private:
    int value; ///< Current calculator value

public:
    /**
     * @brief Constructor with initial value
     * @param initial_value Initial value for the calculator
     */
    Calculator(int initial_value);
    
    /**
     * @brief Add a value to the current result
     * @param operand Value to add
     * @return Reference to this calculator for chaining
     * 
     * Example usage:
     * @code
     * Calculator calc;
     * calc.add(5).add(3); // Result: 8
     * @endcode
     */
    Calculator& add(int operand);
    
    /**
     * @brief Get the current result
     * @return Current calculator value
     */
    int getResult() const;
    
    /**
     * @brief Reset calculator to zero
     * @note This operation cannot be undone
     */
    void reset();
};
```

### 🏷️ Common Doxygen Tags

| Tag | Description | Example |
|-----|-------------|---------|
| `@brief` | Brief description | `@brief Short description` |
| `@param` | Parameter description | `@param name Description` |
| `@return` | Return value description | `@return Description of return` |
| `@throws` | Exception description | `@throws std::exception When...` |
| `@code` | Code example | `@code ... @endcode` |
| `@note` | Important note | `@note This is important` |
| `@warning` | Warning message | `@warning Be careful with...` |
| `@see` | Cross-reference | `@see OtherClass::method()` |
| `@since` | Version information | `@since version 1.2` |
| `@deprecated` | Deprecated feature | `@deprecated Use newMethod() instead` |

### 🔧 Generate Documentation

```bash
doxygen Doxyfile
```

Documentation will be created in `./doc/html/index.html`.

---

## 4. File I/O with fstream {#4-file-io}

### 📖 Reading Files

```cpp
#include <fstream>
#include <iostream>
using namespace std;

ifstream file("hotel.txt");
if(!file.is_open()) {
    cout << "Errore di apertura file hotel." << endl;
    return -1;
}

int num_hotel;
file >> num_hotel;
file.ignore();  // Ignore newline after number

for(int i = 0; i < num_hotel; i++) {
    tipo_inf hotel;
    file >> hotel.stelle;
    file.ignore();  // Ignore newline after number
    file.getline(hotel.nome, 20);
    file.getline(hotel.luogo, 20);

    bst_insert(hotelBst, bst_newNode(hotel.stelle, hotel));
}

file.close();
```

### 💾 Writing Files

```cpp
ofstream outFile("output.txt");
if(!outFile.is_open()) {
    cout << "Errore creazione file output." << endl;
    return -1;
}

outFile << "Numero hotel: " << count << endl;
for(int i = 0; i < count; i++) {
    outFile << hotels[i].stelle << endl;
    outFile << hotels[i].nome << endl;
    outFile << hotels[i].luogo << endl;
}

outFile.close();
```

### 🔄 File I/O Patterns

#### Reading Mixed Data Types
```cpp
ifstream file("data.txt");
string line;
int number;
float decimal;

// Read line by line
while(getline(file, line)) {
    // Process line
}

// Read formatted data
while(file >> number >> decimal) {
    // Process number and decimal
}

file.close();
```

#### Binary File Operations
```cpp
// Writing binary
ofstream binFile("data.bin", ios::binary);
binFile.write(reinterpret_cast<char*>(&data), sizeof(data));
binFile.close();

// Reading binary
ifstream binFile("data.bin", ios::binary);
binFile.read(reinterpret_cast<char*>(&data), sizeof(data));
binFile.close();
```

---

## 5. BST Ordering and Traversal {#5-bst-operations}

### 🌳 BST Structure

```cpp
struct bnode {
    tipo_key key;
    tipo_inf inf;
    bnode* left;
    bnode* right;
    bnode* parent;
};

typedef bnode* bst;
```

### 📊 Ordering Operations

#### Ascending Order (In-Order)
```cpp
void bst_inorder_asc(bst root) {
    if (root != nullptr) {
        bst_inorder_asc(root->left);   // Visit left subtree
        print_key(root->key);          // Process current node
        bst_inorder_asc(root->right);  // Visit right subtree
    }
}
```

#### Descending Order (Reverse In-Order)
```cpp
void bst_inorder_desc(bst root) {
    if (root != nullptr) {
        bst_inorder_desc(root->right);  // Visit right subtree first
        print_key(root->key);           // Process current node
        bst_inorder_desc(root->left);   // Visit left subtree
    }
}
```

### 🔍 DFS Traversals

#### Pre-Order DFS (Root → Left → Right)
```cpp
void bst_dfs_preorder(bst root) {
    if (root != nullptr) {
        print_key(root->key);          // Process root first
        bst_dfs_preorder(root->left);  // Visit left subtree
        bst_dfs_preorder(root->right); // Visit right subtree
    }
}
```

#### Post-Order DFS (Left → Right → Root)
```cpp
void bst_dfs_postorder(bst root) {
    if (root != nullptr) {
        bst_dfs_postorder(root->left);  // Visit left subtree
        bst_dfs_postorder(root->right); // Visit right subtree
        print_key(root->key);           // Process root last
    }
}
```

### 🌊 BFS Traversal

#### Level-Order BFS
```cpp
#include <queue>

void bst_bfs(bst root) {
    if (root == nullptr) return;
    
    queue<bnode*> q;
    q.push(root);
    
    while (!q.empty()) {
        bnode* current = q.front();
        q.pop();
        
        print_key(current->key);  // Process current node
        
        // Add children to queue
        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
}
```

#### Manual Queue Implementation
```cpp
struct queue_node {
    bnode* data;
    queue_node* next;
};

struct simple_queue {
    queue_node* front;
    queue_node* rear;
};

void init_queue(simple_queue& q) {
    q.front = q.rear = nullptr;
}

void enqueue(simple_queue& q, bnode* data) {
    queue_node* new_node = new queue_node;
    new_node->data = data;
    new_node->next = nullptr;
    
    if (q.rear == nullptr) {
        q.front = q.rear = new_node;
    } else {
        q.rear->next = new_node;
        q.rear = new_node;
    }
}

bnode* dequeue(simple_queue& q) {
    if (q.front == nullptr) return nullptr;
    
    queue_node* temp = q.front;
    bnode* data = temp->data;
    q.front = q.front->next;
    
    if (q.front == nullptr) {
        q.rear = nullptr;
    }
    
    delete temp;
    return data;
}
```

---

## 6. String and char[] Operations {#6-strings}

### 🔤 Basic Definitions

#### C-Style Strings (char[])
```cpp
char str[] = "Hello";        // Array of characters
char str[6] = {'H','e','l','l','o','\0'};  // Manual initialization
```

#### C++ Strings (std::string)
```cpp
#include <string>
string str = "Hello";        // C++ string object
string str("Hello");         // Constructor syntax
```

### 📊 Key Differences

| Feature | `char[]` | `std::string` |
|---------|----------|---------------|
| **Type** | Array of characters | Class object |
| **Size** | Fixed at declaration | Dynamic |
| **Memory** | Stack (usually) | Dynamic allocation |
| **Null terminator** | Required (`\0`) | Handled automatically |
| **Bounds checking** | None | Available with `.at()` |
| **Built-in functions** | Limited (C functions) | Many methods |

### 🚀 String Operations

#### Basic Operations
```cpp
string str = "Hello";

// Length/Size
cout << str.length() << endl;    // 5
cout << str.size() << endl;      // 5 (same as length)
cout << str.empty() << endl;     // false

// Access characters
cout << str[0] << endl;          // 'H' (no bounds checking)
cout << str.at(0) << endl;       // 'H' (with bounds checking)
cout << str.front() << endl;     // 'H' (first character)
cout << str.back() << endl;      // 'o' (last character)
```

#### Modification
```cpp
string str = "Hello";

// Append
str += " World";                 // "Hello World"
str.append("!");                 // "Hello World!"
str.push_back('?');              // "Hello World!?"

// Insert
str.insert(5, " Big");           // "Hello Big World!?"

// Erase
str.erase(10, 6);                // Remove " World"
str.pop_back();                  // Remove last character

// Replace
str.replace(0, 5, "Hi");         // "Hi Big!"

// Clear
str.clear();                     // ""
```

#### Search and Substring
```cpp
string str = "Hello World Programming";

// Find
size_t pos = str.find("World");        // Returns 6
if (pos != string::npos) {
    cout << "Found at position: " << pos << endl;
}

// Substring
string sub = str.substr(6, 5);         // "World"
string sub2 = str.substr(12);          // "Programming"
```

### 🔧 char[] Operations

```cpp
#include <cstring>

char str1[50] = "Hello";
char str2[50] = "World";

// Length
int len = strlen(str1);          // 5

// Copy
strcpy(str1, "New Text");        // str1 becomes "New Text"
strncpy(str1, "Safe", 49);       // Safer version

// Concatenate
strcat(str1, " ");               // Append space
strcat(str1, str2);              // str1 becomes "New Text World"

// Compare
int result = strcmp(str1, str2); // Returns <0, 0, or >0

// Search
char* found = strstr(str1, "Text");  // Find substring
char* found_char = strchr(str1, 'T'); // Find character
```

### 🔄 Conversions

#### char[] to string
```cpp
char char_array[] = "Hello World";

// Method 1: Constructor (most common)
string str1(char_array);

// Method 2: Assignment
string str2 = char_array;
```

#### string to char[]
```cpp
string str = "Hello World";

// Method 1: Using c_str() (read-only)
const char* cstr = str.c_str();

// Method 2: Using strcpy (modifiable copy)
char char_array[50];
strcpy(char_array, str.c_str());

// Method 3: Using copy() method
char manual_array[50];
str.copy(manual_array, str.length());
manual_array[str.length()] = '\0';  // Add null terminator!
```

---

## 7. Sorting Algorithms {#7-sorting}

### 🏆 STL sort() - Most Practical

```cpp
#include <algorithm>
#include <vector>

// Basic usage
vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
sort(arr.begin(), arr.end());                    // Ascending
sort(arr.begin(), arr.end(), greater<int>());    // Descending

// Custom comparator
sort(arr.begin(), arr.end(), [](int a, int b) {
    return a > b;  // Descending order
});
```

**Complexity**: O(n log n) average and worst case  
**Space**: O(log n)

### ⚡ Quick Sort

```cpp
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);     // Sort left part
        quickSort(arr, pi + 1, high);   // Sort right part
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];    // Choose last element as pivot
    int i = (low - 1);        // Index of smaller element
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
```

**Complexity**: O(n log n) average, O(n²) worst case  
**Space**: O(log n) average

### 🔄 Merge Sort

```cpp
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(arr, left, mid);        // Sort first half
        mergeSort(arr, mid + 1, right);   // Sort second half
        merge(arr, left, mid, right);     // Merge sorted halves
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    vector<int> L(n1), R(n2);
    
    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Merge temp arrays back
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
```

**Complexity**: O(n log n) always  
**Space**: O(n)  
**Stable**: Yes

### 📈 Other Important Sorts

#### Insertion Sort (Good for Small Arrays)
```cpp
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
```

#### Heap Sort (Guaranteed Performance)
```cpp
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    
    if (l < n && arr[l] > arr[largest])
        largest = l;
    
    if (r < n && arr[r] > arr[largest])
        largest = r;
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
```

### 📊 Comparison Table

| Algorithm | Best Case | Average Case | Worst Case | Space | Stable |
|-----------|-----------|--------------|------------|-------|--------|
| **STL sort()** | O(n log n) | O(n log n) | O(n log n) | O(log n) | No |
| **Quick Sort** | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| **Merge Sort** | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| **Insertion Sort** | O(n) | O(n²) | O(n²) | O(1) | Yes |
| **Heap Sort** | O(n log n) | O(n log n) | O(n log n) | O(1) | No |

---

## 8. Graph Algorithms (Dijkstra and Prim) {#8-graph-algorithms}

### 🛣️ Dijkstra's Algorithm (Shortest Paths)

#### Core Implementation
```cpp
struct DijkstraNode {
    int vertex;
    float distance;
    
    bool operator>(const DijkstraNode& other) const {
        return distance > other.distance;
    }
};

vector<float> dijkstra(const graph& g, int source, vector<int>& parent) {
    int n = g.dim;
    vector<float> dist(n, FLT_MAX);
    parent.assign(n, -1);
    vector<bool> visited(n, false);
    
    priority_queue<DijkstraNode, vector<DijkstraNode>, greater<DijkstraNode>> pq;
    
    // Initialize source
    dist[source] = 0;
    pq.push({source, 0});
    
    while (!pq.empty()) {
        DijkstraNode current = pq.top();
        pq.pop();
        
        int u = current.vertex;
        
        if (visited[u]) continue;
        visited[u] = true;
        
        // Relax all adjacent vertices
        adj_list adj = g.nodes[u];
        while (adj) {
            int v = adj->node;
            float weight = adj->weight;
            
            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({v, dist[v]});
            }
            adj = adj->next;
        }
    }
    
    return dist;
}
```

#### Path Reconstruction
```cpp
void print_shortest_paths(const vector<float>& dist, const vector<int>& parent, int source) {
    for (int i = 0; i < dist.size(); i++) {
        cout << "To vertex " << i << ": ";
        if (dist[i] == FLT_MAX) {
            cout << "No path\n";
        } else {
            cout << "Distance = " << dist[i] << ", Path = ";
            
            // Reconstruct path
            vector<int> path;
            int current = i;
            while (current != -1) {
                path.push_back(current);
                current = parent[current];
            }
            
            for (int j = path.size() - 1; j >= 0; j--) {
                cout << path[j];
                if (j > 0) cout << " -> ";
            }
            cout << "\n";
        }
    }
}
```

### 🌳 Prim's Algorithm (Minimum Spanning Tree)

#### Core Implementation
```cpp
struct PrimNode {
    int vertex;
    float key;
    
    bool operator>(const PrimNode& other) const {
        return key > other.key;
    }
};

vector<int> prim(const graph& g, int root, float& total_weight) {
    int n = g.dim;
    vector<float> key(n, FLT_MAX);
    vector<int> parent(n, -1);
    vector<bool> in_mst(n, false);
    
    priority_queue<PrimNode, vector<PrimNode>, greater<PrimNode>> pq;
    
    // Initialize root
    key[root] = 0;
    pq.push({root, 0});
    total_weight = 0;
    
    while (!pq.empty()) {
        PrimNode current = pq.top();
        pq.pop();
        
        int u = current.vertex;
        
        if (in_mst[u]) continue;
        in_mst[u] = true;
        
        if (parent[u] != -1) {
            total_weight += key[u];
        }
        
        // Update keys of adjacent vertices
        adj_list adj = g.nodes[u];
        while (adj) {
            int v = adj->node;
            float weight = adj->weight;
            
            if (!in_mst[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({v, weight});
            }
            adj = adj->next;
        }
    }
    
    return parent;
}
```

#### MST Display
```cpp
void print_mst(const vector<int>& parent, const graph& g, float total_weight) {
    cout << "Minimum Spanning Tree:\n";
    cout << "Edges in MST:\n";
    
    for (int i = 0; i < parent.size(); i++) {
        if (parent[i] != -1) {
            // Find the weight of edge parent[i] - i
            adj_list adj = g.nodes[parent[i]];
            while (adj) {
                if (adj->node == i) {
                    cout << parent[i] << " - " << i 
                         << " (weight: " << adj->weight << ")\n";
                    break;
                }
                adj = adj->next;
            }
        }
    }
    cout << "Total weight of MST: " << total_weight << "\n";
}
```

### 🔄 Key Differences

| Aspect | Dijkstra | Prim |
|--------|----------|------|
| **Purpose** | Shortest paths from source | Minimum spanning tree |
| **Relaxation** | `if (dist[u] + weight < dist[v])` | `if (weight < key[v])` |
| **Updates** | `dist[v] = dist[u] + weight` | `key[v] = weight` |
| **Result** | Distance array | Parent array (tree) |
| **Graph Type** | Directed/Undirected | Undirected only |

**Time Complexity**: O((V + E) log V) with binary heap  
**Space Complexity**: O(V)

---

## 9. Makefile Template {#9-makefile}

### 📋 Standard Makefile

```makefile
# Nome dell'eseguibile
EXEC = programma

# File sorgenti
SRC = compito.cc hotel.cc bst.cc

# File oggetto
OBJ = $(SRC:.cc=.o)

# Compilatore
CC = g++

# Opzioni di compilazione (-DDEBUG attiva stampa con print_tree)
#CFLAGS = -Wall -g
# Per abilitare la stampa dell'albero in debug, scommenta la riga sotto:
CFLAGS = -Wall -g -DDEBUG

# Regola di default
all: $(EXEC)

# Regola per creare l'eseguibile
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Regola per compilare i .cc in .o
%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

# Pulizia dei file oggetto ed eseguibile
clean:
	rm -f $(OBJ) $(EXEC)

# Generazione documentazione
doc:
	doxygen Doxyfile

clean-doc:
	rm -rf doc/

.PHONY: all clean doc clean-doc
```

### 🔧 Makefile Components

- **EXEC**: Name of the executable
- **SRC**: Source files (.cc, .cpp)
- **OBJ**: Object files (automatically generated from SRC)
- **CC**: Compiler (g++, clang++)
- **CFLAGS**: Compiler flags
- **all**: Default target
- **clean**: Remove generated files
- **doc**: Generate documentation
- **.PHONY**: Declare non-file targets

### 🚀 Usage

```bash
make              # Compile project
make clean        # Remove generated files
make doc          # Generate documentation
make clean-doc    # Remove documentation
```

---

## 💡 Quick Reference Tips

### ⚠️ Common Pitfalls

1. **Index confusion** - Remember 1-indexed vs 0-indexed
2. **Null pointer access** - Always check for NULL/nullptr
3. **Memory leaks** - Use proper cleanup (delete, delete[])
4. **Buffer overflow** - Check array bounds
5. **Uninitialized variables** - Always initialize

### 🎯 Best Practices

1. **Use const** when you don't modify parameters
2. **Pass by reference** for large objects
3. **Check return values** from file operations
4. **Use RAII** for automatic resource management
5. **Document your code** with comments and Doxygen

### 🔍 Debugging Strategies

1. **Print intermediate values** to trace execution
2. **Use debugger** (gdb) for step-by-step analysis
3. **Add assertions** to check preconditions
4. **Test with small examples** first
5. **Draw data structures** on paper