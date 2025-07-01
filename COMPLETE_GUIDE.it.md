# Guida Completa alla Programmazione C++ per Strutture Dati e Algoritmi

## 📚 Indice
1. [Liste (Semplici, Doppie e Ordinate)](#1-liste)
2. [Implementazione di Grafi](#2-grafi)
3. [Documentazione Doxygen](#3-doxygen)
4. [I/O su File con fstream](#4-file-io)
5. [Ordinamento e Attraversamento BST](#5-operazioni-bst)
6. [Operazioni su String e char[]](#6-stringhe)
7. [Algoritmi di Ordinamento](#7-ordinamento)
8. [Algoritmi di Dijkstra e Prim](#8-algoritmi-grafi)
9. [Template Makefile](#9-makefile)

---

## 1. Liste (Semplici, Doppie e Ordinate) {#1-liste}

### 📋 Strutture Dati Fondamentali

```cpp
// Struttura generica del nodo per lista doppiamente collegata
struct Node {
    TipoInf info;        // TipoInf rappresenta il tipo di dato
    Node* next;          // Puntatore al nodo successivo
    Node* prev;          // Puntatore al nodo precedente
};

typedef Node* Lista;     // Lista è un puntatore al primo nodo (testa)
```

### 🔑 Concetti Chiave

**Liste Semplici vs Doppie:**
- **Semplici**: Solo puntatore `next`, attraversamento solo in avanti
- **Doppie**: Puntatori `next` e `prev`, attraversamento bidirezionale
- **Ordinate**: Mantengono l'ordine durante l'inserimento

### 🚀 Operazioni Essenziali

#### Inserimento in Testa (Lista Doppia)
```cpp
Lista inserisciInTesta(Lista head, Node* nuovo) {
    nuovo->next = head;          // Collega il nuovo nodo all'inizio
    nuovo->prev = NULL;          // Il precedente della nuova testa è NULL
    if (head != NULL) {
        head->prev = nuovo;      // Collega la vecchia testa al nuovo nodo
    }
    return nuovo;                // Il nuovo nodo diventa la testa
}
```

#### Attraversamento e Stampa della Lista
```cpp
void stampaLista(Lista head) {
    Node* curr = head;
    while (curr != NULL) {
        stampaInfo(curr->info);  // Stampa info (adatta al tuo TipoInf)
        curr = curr->next;
    }
}

// Stampa inversa per liste doppie
void stampaListaInversa(Lista head) {
    // Prima, raggiungi la coda
    Node* curr = head;
    while (curr != NULL && curr->next != NULL) {
        curr = curr->next;
    }
    
    // Poi attraversa all'indietro
    while (curr != NULL) {
        stampaInfo(curr->info);
        curr = curr->prev;
    }
}
```

#### Rimozione Nodo (Lista Doppia)
```cpp
Lista eliminaNodo(Lista head, Node* daEliminare) {
    if (head == daEliminare) {
        head = head->next;       // Se rimuovi la testa, aggiorna la testa
    }
    
    // Ricollega i vicini
    if (daEliminare->prev != NULL) {
        daEliminare->prev->next = daEliminare->next;
    }
    if (daEliminare->next != NULL) {
        daEliminare->next->prev = daEliminare->prev;
    }
    
    delete daEliminare;          // Dealloca il nodo
    return head;
}
```

#### Inserimento Ordinato
```cpp
Lista inserisciOrdinato(Lista head, Node* nuovo) {
    if (head == NULL || confronta(nuovo->info, head->info) <= 0) {
        return inserisciInTesta(head, nuovo);
    }
    
    // Trova la posizione corretta
    Node* curr = head;
    while (curr->next != NULL && confronta(nuovo->info, curr->next->info) > 0) {
        curr = curr->next;
    }
    
    // Inserisci nuovo dopo curr
    nuovo->next = curr->next;
    nuovo->prev = curr;
    if (curr->next != NULL) {
        curr->next->prev = nuovo;
    }
    curr->next = nuovo;
    
    return head;
}
```

### 🔧 Template Funzione di Confronto

La funzione `confronta` dovrebbe restituire:
- `< 0` se `a < b`
- `= 0` se `a == b`  
- `> 0` se `a > b`

```cpp
// Per interi
int confronta(int a, int b) {
    return a - b;
}

// Per strutture personalizzate (es. per data poi ora)
int confronta(Appuntamento a, Appuntamento b) {
    if (a.data != b.data) return a.data - b.data;
    return a.ora - b.ora;
}
```

### 📝 Pattern Comuni per Liste

#### Ricerca nella Lista
```cpp
Node* cerca(Lista head, TipoInf x) {
    Node* curr = head;
    while (curr != NULL) {
        if (confronta(curr->info, x) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;  // Non trovato
}
```

#### Lunghezza Lista
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

#### Pulizia Memoria
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

## 2. Implementazione di Grafi {#2-grafi}

### 📋 Strutture Dati Fondamentali

```cpp
struct adj_node {
    int node;           // Vertice adiacente (0-indicizzato internamente)
    float weight;       // Peso dell'arco
    adj_node* next;     // Puntatore al prossimo nodo adiacente
};

typedef adj_node* adj_list;

typedef struct {
    adj_list* nodes;    // Array di liste di adiacenza
    int dim;           // Numero di vertici
} graph;
```

### 🔑 Concetto Chiave: **Interfaccia 1-indicizzata, Memorizzazione 0-indicizzata**

| Input Utente | Memorizzazione Interna |
|--------------|------------------------|
| Nodo 1       | Indice 0              |
| Nodo 2       | Indice 1              |
| Nodo n       | Indice n-1            |

### 🚀 Funzioni Essenziali

#### Creazione Grafo
```cpp
graph new_graph(int n);  // Crea grafo con n vertici (da 1 a n)
```

#### Aggiunta Archi
```cpp
add_arc(g, u, v, weight);    // Arco diretto: u → v
add_edge(g, u, v, weight);   // Arco non diretto: u ↔ v
```

#### Accesso al Grafo
```cpp
int size = get_dim(g);                    // Ottieni numero di vertici
adj_list neighbors = get_adjlist(g, u);   // Ottieni lista adiacenza del vertice u
int vertex = get_adjnode(neighbors);      // Ottieni vertice da adj_node
adj_list next = get_nextadj(neighbors);   // Ottieni prossimo nodo nella lista
```

### 📝 Pattern Standard di Attraversamento

```cpp
// Template per visitare tutti i vicini del vertice u
adj_list current = get_adjlist(g, u);
while (current != NULL) {
    int neighbor = get_adjnode(current);
    float weight = current->weight;
    
    // FAI QUALCOSA con neighbor e weight
    
    current = get_nextadj(current);
}
```

### 🔥 Operazioni Comuni

#### Attraversamento DFS
```cpp
void dfs(graph g, int u, vector<bool>& visited) {
    visited[u-1] = true;  // Converti a 0-indicizzato per array visited
    cout << u << " ";
    
    adj_list current = get_adjlist(g, u);
    while (current != NULL) {
        int v = get_adjnode(current);
        if (!visited[v-1]) {  // Converti a 0-indicizzato
            dfs(g, v, visited);
        }
        current = get_nextadj(current);
    }
}
```

#### Attraversamento BFS
```cpp
void bfs(graph g, int start) {
    vector<bool> visited(get_dim(g), false);
    queue<int> q;
    
    q.push(start);
    visited[start-1] = true;  // Converti a 0-indicizzato
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";
        
        adj_list current = get_adjlist(g, u);
        while (current != NULL) {
            int v = get_adjnode(current);
            if (!visited[v-1]) {  // Converti a 0-indicizzato
                visited[v-1] = true;
                q.push(v);
            }
            current = get_nextadj(current);
        }
    }
}
```

---

## 3. Documentazione Doxygen {#3-doxygen}

### 🚀 Inizializzare Doxygen

```bash
doxygen -g Doxyfile
```

### ⚙️ Configurare Doxyfile

```bash
# Informazioni progetto
PROJECT_NAME           = "Nome del Tuo Progetto"
PROJECT_NUMBER         = "1.0"
PROJECT_BRIEF          = "Breve descrizione"

# Impostazioni input
INPUT                  = .
RECURSIVE              = YES
FILE_PATTERNS          = *.cpp *.h *.hpp *.cc *.cxx *.c++

# Impostazioni output
OUTPUT_DIRECTORY       = ./doc
GENERATE_HTML          = YES
GENERATE_LATEX         = YES

# Estrazione documentazione
EXTRACT_ALL            = YES
EXTRACT_PRIVATE        = YES
EXTRACT_STATIC         = YES

# Grafici e diagrammi
HAVE_DOT               = YES
CALL_GRAPH             = YES
CALLER_GRAPH           = YES
CLASS_DIAGRAMS         = YES
```

### 📝 Sintassi Documentazione

#### Documentazione File Header
```cpp
/**
 * @file esempio.h
 * @brief Breve descrizione del file
 * @author Il Tuo Nome
 * @date 2025-07-01
 */

/**
 * @class Calcolatrice
 * @brief Una semplice classe calcolatrice
 * 
 * Questa classe fornisce operazioni aritmetiche di base
 * per valori interi.
 */
class Calcolatrice {
private:
    int valore; ///< Valore corrente della calcolatrice

public:
    /**
     * @brief Costruttore con valore iniziale
     * @param valore_iniziale Valore iniziale per la calcolatrice
     */
    Calcolatrice(int valore_iniziale);
    
    /**
     * @brief Aggiungi un valore al risultato corrente
     * @param operando Valore da aggiungere
     * @return Riferimento a questa calcolatrice per concatenazione
     * 
     * Esempio di utilizzo:
     * @code
     * Calcolatrice calc;
     * calc.aggiungi(5).aggiungi(3); // Risultato: 8
     * @endcode
     */
    Calcolatrice& aggiungi(int operando);
    
    /**
     * @brief Ottieni il risultato corrente
     * @return Valore corrente della calcolatrice
     */
    int ottieniRisultato() const;
    
    /**
     * @brief Resetta la calcolatrice a zero
     * @note Questa operazione non può essere annullata
     */
    void reset();
};
```

### 🏷️ Tag Doxygen Comuni

| Tag | Descrizione | Esempio |
|-----|-------------|---------|
| `@brief` | Descrizione breve | `@brief Descrizione breve` |
| `@param` | Descrizione parametro | `@param nome Descrizione` |
| `@return` | Descrizione valore ritorno | `@return Descrizione del ritorno` |
| `@throws` | Descrizione eccezione | `@throws std::exception Quando...` |
| `@code` | Esempio di codice | `@code ... @endcode` |
| `@note` | Nota importante | `@note Questo è importante` |
| `@warning` | Messaggio di avvertimento | `@warning Attenzione a...` |
| `@see` | Riferimento incrociato | `@see AltraClasse::metodo()` |
| `@since` | Informazioni versione | `@since versione 1.2` |
| `@deprecated` | Funzione deprecata | `@deprecated Usa nuovoMetodo() invece` |

### 🔧 Generare Documentazione

```bash
doxygen Doxyfile
```

La documentazione verrà creata in `./doc/html/index.html`.

---

## 4. I/O su File con fstream {#4-file-io}

### 📖 Lettura File

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
file.ignore();  // Ignora il newline dopo il numero

for(int i = 0; i < num_hotel; i++) {
    tipo_inf hotel;
    file >> hotel.stelle;
    file.ignore();  // Ignora il newline dopo il numero
    file.getline(hotel.nome, 20);
    file.getline(hotel.luogo, 20);

    bst_insert(hotelBst, bst_newNode(hotel.stelle, hotel));
}

file.close();
```

### 💾 Scrittura File

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

### 🔄 Pattern I/O File

#### Lettura Tipi Dati Misti
```cpp
ifstream file("dati.txt");
string linea;
int numero;
float decimale;

// Leggi linea per linea
while(getline(file, linea)) {
    // Processa linea
}

// Leggi dati formattati
while(file >> numero >> decimale) {
    // Processa numero e decimale
}

file.close();
```

#### Operazioni File Binari
```cpp
// Scrittura binaria
ofstream binFile("dati.bin", ios::binary);
binFile.write(reinterpret_cast<char*>(&dati), sizeof(dati));
binFile.close();

// Lettura binaria
ifstream binFile("dati.bin", ios::binary);
binFile.read(reinterpret_cast<char*>(&dati), sizeof(dati));
binFile.close();
```

---

## 5. Ordinamento e Attraversamento BST {#5-operazioni-bst}

### 🌳 Struttura BST

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

### 📊 Operazioni di Ordinamento

#### Ordine Crescente (In-Order)
```cpp
void bst_inorder_asc(bst root) {
    if (root != nullptr) {
        bst_inorder_asc(root->left);   // Visita sottoalbero sinistro
        print_key(root->key);          // Processa nodo corrente
        bst_inorder_asc(root->right);  // Visita sottoalbero destro
    }
}
```

#### Ordine Decrescente (In-Order Inverso)
```cpp
void bst_inorder_desc(bst root) {
    if (root != nullptr) {
        bst_inorder_desc(root->right);  // Visita prima sottoalbero destro
        print_key(root->key);           // Processa nodo corrente
        bst_inorder_desc(root->left);   // Visita sottoalbero sinistro
    }
}
```

### 🔍 Attraversamenti DFS

#### Pre-Order DFS (Radice → Sinistro → Destro)
```cpp
void bst_dfs_preorder(bst root) {
    if (root != nullptr) {
        print_key(root->key);          // Processa prima la radice
        bst_dfs_preorder(root->left);  // Visita sottoalbero sinistro
        bst_dfs_preorder(root->right); // Visita sottoalbero destro
    }
}
```

#### Post-Order DFS (Sinistro → Destro → Radice)
```cpp
void bst_dfs_postorder(bst root) {
    if (root != nullptr) {
        bst_dfs_postorder(root->left);  // Visita sottoalbero sinistro
        bst_dfs_postorder(root->right); // Visita sottoalbero destro
        print_key(root->key);           // Processa per ultima la radice
    }
}
```

### 🌊 Attraversamento BFS

#### BFS Level-Order
```cpp
#include <queue>

void bst_bfs(bst root) {
    if (root == nullptr) return;
    
    queue<bnode*> q;
    q.push(root);
    
    while (!q.empty()) {
        bnode* current = q.front();
        q.pop();
        
        print_key(current->key);  // Processa nodo corrente
        
        // Aggiungi figli alla coda
        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
}
```

#### Implementazione Manuale Coda
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

## 6. Operazioni su String e char[] {#6-stringhe}

### 🔤 Definizioni di Base

#### Stringhe C-Style (char[])
```cpp
char str[] = "Ciao";        // Array di caratteri
char str[5] = {'C','i','a','o','\0'};  // Inizializzazione manuale
```

#### Stringhe C++ (std::string)
```cpp
#include <string>
string str = "Ciao";        // Oggetto string C++
string str("Ciao");         // Sintassi costruttore
```

### 📊 Differenze Chiave

| Caratteristica | `char[]` | `std::string` |
|----------------|----------|---------------|
| **Tipo** | Array di caratteri | Oggetto classe |
| **Dimensione** | Fissa alla dichiarazione | Dinamica |
| **Memoria** | Stack (solitamente) | Allocazione dinamica |
| **Terminatore null** | Richiesto (`\0`) | Gestito automaticamente |
| **Controllo limiti** | Nessuno | Disponibile con `.at()` |
| **Funzioni built-in** | Limitate (funzioni C) | Molti metodi |

### 🚀 Operazioni su String

#### Operazioni di Base
```cpp
string str = "Ciao";

// Lunghezza/Dimensione
cout << str.length() << endl;    // 4
cout << str.size() << endl;      // 4 (uguale a length)
cout << str.empty() << endl;     // false

// Accesso ai caratteri
cout << str[0] << endl;          // 'C' (nessun controllo limiti)
cout << str.at(0) << endl;       // 'C' (con controllo limiti)
cout << str.front() << endl;     // 'C' (primo carattere)
cout << str.back() << endl;      // 'o' (ultimo carattere)
```

#### Modifica
```cpp
string str = "Ciao";

// Aggiungi
str += " Mondo";                 // "Ciao Mondo"
str.append("!");                 // "Ciao Mondo!"
str.push_back('?');              // "Ciao Mondo!?"

// Inserisci
str.insert(4, " Bel");           // "Ciao Bel Mondo!?"

// Cancella
str.erase(8, 6);                 // Rimuove " Mondo"
str.pop_back();                  // Rimuove ultimo carattere

// Sostituisci
str.replace(0, 4, "Salve");      // "Salve Bel!"

// Svuota
str.clear();                     // ""
```

#### Ricerca e Sottostringhe
```cpp
string str = "Ciao Mondo Programmazione";

// Trova
size_t pos = str.find("Mondo");        // Restituisce 5
if (pos != string::npos) {
    cout << "Trovato alla posizione: " << pos << endl;
}

// Sottostringa
string sub = str.substr(5, 5);         // "Mondo"
string sub2 = str.substr(11);          // "Programmazione"
```

### 🔧 Operazioni char[]

```cpp
#include <cstring>

char str1[50] = "Ciao";
char str2[50] = "Mondo";

// Lunghezza
int len = strlen(str1);          // 4

// Copia
strcpy(str1, "Nuovo Testo");     // str1 diventa "Nuovo Testo"
strncpy(str1, "Sicuro", 49);     // Versione più sicura

// Concatena
strcat(str1, " ");               // Aggiungi spazio
strcat(str1, str2);              // str1 diventa "Nuovo Testo Mondo"

// Confronta
int result = strcmp(str1, str2); // Restituisce <0, 0, o >0

// Cerca
char* found = strstr(str1, "Testo");  // Trova sottostringa
char* found_char = strchr(str1, 'T'); // Trova carattere
```

### 🔄 Conversioni

#### char[] a string
```cpp
char char_array[] = "Ciao Mondo";

// Metodo 1: Costruttore (più comune)
string str1(char_array);

// Metodo 2: Assegnazione
string str2 = char_array;
```

#### string a char[]
```cpp
string str = "Ciao Mondo";

// Metodo 1: Usando c_str() (sola lettura)
const char* cstr = str.c_str();

// Metodo 2: Usando strcpy (copia modificabile)
char char_array[50];
strcpy(char_array, str.c_str());

// Metodo 3: Usando il metodo copy()
char manual_array[50];
str.copy(manual_array, str.length());
manual_array[str.length()] = '\0';  // Aggiungi terminatore null!
```

---

## 7. Algoritmi di Ordinamento {#7-ordinamento}

### 🏆 STL sort() - Più Pratico

```cpp
#include <algorithm>
#include <vector>

// Utilizzo di base
vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
sort(arr.begin(), arr.end());                    // Crescente
sort(arr.begin(), arr.end(), greater<int>());    // Decrescente

// Comparatore personalizzato
sort(arr.begin(), arr.end(), [](int a, int b) {
    return a > b;  // Ordine decrescente
});
```

**Complessità**: O(n log n) caso medio e peggiore  
**Spazio**: O(log n)

### ⚡ Quick Sort

```cpp
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);     // Ordina parte sinistra
        quickSort(arr, pi + 1, high);   // Ordina parte destra
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];    // Scegli ultimo elemento come pivot
    int i = (low - 1);        // Indice dell'elemento più piccolo
    
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

**Complessità**: O(n log n) caso medio, O(n²) caso peggiore  
**Spazio**: O(log n) caso medio

### 🔄 Merge Sort

```cpp
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(arr, left, mid);        // Ordina prima metà
        mergeSort(arr, mid + 1, right);   // Ordina seconda metà
        merge(arr, left, mid, right);     // Unisci metà ordinate
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Crea array temporanei
    vector<int> L(n1), R(n2);
    
    // Copia dati negli array temporanei
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Unisci gli array temporanei
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
    
    // Copia elementi rimanenti
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

**Complessità**: O(n log n) sempre  
**Spazio**: O(n)  
**Stabile**: Sì

### 📈 Altri Ordinamenti Importanti

#### Insertion Sort (Buono per Array Piccoli)
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

#### Heap Sort (Performance Garantita)
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
    
    // Costruisci heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    // Estrai elementi dall'heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
```

### 📊 Tabella di Confronto

| Algoritmo | Caso Migliore | Caso Medio | Caso Peggiore | Spazio | Stabile |
|-----------|---------------|------------|---------------|--------|---------|
| **STL sort()** | O(n log n) | O(n log n) | O(n log n) | O(log n) | No |
| **Quick Sort** | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| **Merge Sort** | O(n log n) | O(n log n) | O(n log n) | O(n) | Sì |
| **Insertion Sort** | O(n) | O(n²) | O(n²) | O(1) | Sì |
| **Heap Sort** | O(n log n) | O(n log n) | O(n log n) | O(1) | No |

---

## 8. Algoritmi di Grafi (Dijkstra e Prim) {#8-algoritmi-grafi}

### 🛣️ Algoritmo di Dijkstra (Cammini Minimi)

#### Implementazione Principale
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
    
    // Inizializza sorgente
    dist[source] = 0;
    pq.push({source, 0});
    
    while (!pq.empty()) {
        DijkstraNode current = pq.top();
        pq.pop();
        
        int u = current.vertex;
        
        if (visited[u]) continue;
        visited[u] = true;
        
        // Rilassa tutti i vertici adiacenti
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

#### Ricostruzione Percorso
```cpp
void print_shortest_paths(const vector<float>& dist, const vector<int>& parent, int source) {
    for (int i = 0; i < dist.size(); i++) {
        cout << "Al vertice " << i << ": ";
        if (dist[i] == FLT_MAX) {
            cout << "Nessun percorso\n";
        } else {
            cout << "Distanza = " << dist[i] << ", Percorso = ";
            
            // Ricostruisci percorso
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

### 🌳 Algoritmo di Prim (Albero di Copertura Minimo)

#### Implementazione Principale
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
    
    // Inizializza radice
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
        
        // Aggiorna chiavi dei vertici adiacenti
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

#### Visualizzazione MST
```cpp
void print_mst(const vector<int>& parent, const graph& g, float total_weight) {
    cout << "Albero di Copertura Minimo:\n";
    cout << "Archi nell'MST:\n";
    
    for (int i = 0; i < parent.size(); i++) {
        if (parent[i] != -1) {
            // Trova il peso dell'arco parent[i] - i
            adj_list adj = g.nodes[parent[i]];
            while (adj) {
                if (adj->node == i) {
                    cout << parent[i] << " - " << i 
                         << " (peso: " << adj->weight << ")\n";
                    break;
                }
                adj = adj->next;
            }
        }
    }
    cout << "Peso totale dell'MST: " << total_weight << "\n";
}
```

### 🔄 Differenze Chiave

| Aspetto | Dijkstra | Prim |
|---------|----------|------|
| **Scopo** | Cammini minimi da sorgente | Albero di copertura minimo |
| **Rilassamento** | `if (dist[u] + weight < dist[v])` | `if (weight < key[v])` |
| **Aggiornamenti** | `dist[v] = dist[u] + weight` | `key[v] = weight` |
| **Risultato** | Array distanze | Array padre (albero) |
| **Tipo Grafo** | Diretto/Non diretto | Solo non diretto |

**Complessità Temporale**: O((V + E) log V) con heap binario  
**Complessità Spaziale**: O(V)

---

## 9. Template Makefile {#9-makefile}

### 📋 Makefile Standard

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

### 🔧 Componenti Makefile

- **EXEC**: Nome dell'eseguibile
- **SRC**: File sorgenti (.cc, .cpp)
- **OBJ**: File oggetto (generati automaticamente da SRC)
- **CC**: Compilatore (g++, clang++)
- **CFLAGS**: Flag del compilatore
- **all**: Target di default
- **clean**: Rimuovi file generati
- **doc**: Genera documentazione
- **.PHONY**: Dichiara target non-file

### 🚀 Utilizzo

```bash
make              # Compila progetto
make clean        # Rimuovi file generati
make doc          # Genera documentazione
make clean-doc    # Rimuovi documentazione
```

---

## 💡 Riferimento Rapido Suggerimenti

### ⚠️ Errori Comuni

1. **Confusione indici** - Ricorda 1-indicizzato vs 0-indicizzato
2. **Accesso puntatore null** - Controlla sempre NULL/nullptr
3. **Memory leak** - Usa pulizia appropriata (delete, delete[])
4. **Buffer overflow** - Controlla limiti array
5. **Variabili non inizializzate** - Inizializza sempre

### 🎯 Buone Pratiche

1. **Usa const** quando non modifichi parametri
2. **Passa per riferimento** per oggetti grandi
3. **Controlla valori di ritorno** dalle operazioni su file
4. **Usa RAII** per gestione automatica risorse
5. **Documenta il codice** con commenti e Doxygen

### 🔍 Strategie di Debug

1. **Stampa valori intermedi** per tracciare esecuzione
2. **Usa debugger** (gdb) per analisi passo-passo
3. **Aggiungi asserzioni** per controllare precondizioni
4. **Testa con esempi piccoli** prima
5. **Disegna strutture dati** su carta