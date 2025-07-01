#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#include "tipo.h"
#include "liste.h"
#include "parola.h"

// Funzione per stampare una lista di documenti
void print_doc_list(lista l) {
    while (l != NULL) {
        print(head(l));
        cout << " ";
        l = tail(l);
    }
    cout << endl;
}

// Punto 1: Carica l'inverted index dal file
parola* load(int& n) {
    ifstream file("inverted");
    if (!file) {
        cout << "Errore nell'apertura del file inverted" << endl;
        n = 0;
        return NULL;
    }

    file >> n;
    parola* inverted_index = new parola[n];

    for (int i = 0; i < n; i++) {
        file >> inverted_index[i].p;
        file >> inverted_index[i].n_doc;
        inverted_index[i].l = NULL;

        for (int j = 0; j < inverted_index[i].n_doc; j++) {
            tipo_inf doc_id;
            file >> doc_id;
            elem* e = new_elem(doc_id);
            // Manteniamo la lista ordinata per coerenza
            inverted_index[i].l = ord_insert_elem(inverted_index[i].l, e);
        }
    }

    file.close();
    return inverted_index;
}

// Punto 1: Stampa l'inverted index
void stampa(parola* ii, int n) {
    if (ii == NULL) return;
    cout << "--- Inverted Index ---" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Parola: " << ii[i].p << endl;
        cout << "Numero documenti: " << ii[i].n_doc << endl;
        cout << "Documenti: ";
        print_doc_list(ii[i].l);
        cout << "------------------------" << endl;
    }
}

// Punto 2: Aggiorna l'inverted index con un nuovo documento
void update(parola* &ii, int &size, const char* fileName) {
    ifstream file(fileName);
    if (!file) {
        cout << "Errore nell'apertura del file " << fileName << endl;
        return;
    }

    int doc_id;
    file >> doc_id;

    char word[80];
    while (file >> word) {
        int word_index = -1;
        // Cerca se la parola esiste già nell'indice
        for (int i = 0; i < size; i++) {
            if (strcmp(ii[i].p, word) == 0) {
                word_index = i;
            }
        }

        if (word_index != -1) { // Parola trovata
            // Controlla se il doc_id è già nella lista
            if (search(ii[word_index].l, doc_id) == NULL) {
                // Aggiungi il doc_id alla lista se non presente
                elem* e = new_elem(doc_id);
                ii[word_index].l = ord_insert_elem(ii[word_index].l, e);
                ii[word_index].n_doc++;
            }
        } else { // Parola non trovata, va aggiunta
            // Alloca un nuovo array più grande
            parola* new_ii = new parola[size + 1];
            // Copia i vecchi dati
            for (int i = 0; i < size; i++) {
                new_ii[i] = ii[i];
            }

            // Aggiungi la nuova parola
            strcpy(new_ii[size].p, word);
            new_ii[size].n_doc = 1;
            new_ii[size].l = NULL;
            elem* e = new_elem(doc_id);
            new_ii[size].l = insert_elem(new_ii[size].l, e);

            // Libera la vecchia memoria e aggiorna i puntatori
            delete[] ii;
            ii = new_ii;
            size++;
        }
    }

    file.close();
}

void AND(parola* ii, int size, const char* w1, const char* w2);
struct DocMatch {
    int id;
    int count;
};
int* match(parola* ii, int size, char** wl, int n, int& result_size);

int main() {
    int index_size = 0;
    parola* inverted_index = load(index_size);

    cout << "Inverted Index Iniziale:" << endl;
    stampa(inverted_index, index_size);

    char fileName[100];
    cout << "\nInserisci il nome del file del documento da aggiungere (es. doc): ";
    cin >> fileName;

    update(inverted_index, index_size, fileName);

    cout << "\nInverted Index Aggiornato:" << endl;
    stampa(inverted_index, index_size);

    char w1[80], w2[80];
    cout << "\n--- Ricerca AND ---" << endl;
    cout << "Inserisci la prima parola: ";
    cin >> w1;
    cout << "Inserisci la seconda parola: ";
    cin >> w2;

    cout << "Documenti che contengono " << w1 << " AND " << w2 << ":" << endl;
    AND(inverted_index, index_size, w1, w2);

    cout << "\n--- Ricerca MATCH ---" << endl;
    cout << "Inserisci una serie di parole separate da spazio (es. computer voltage):" << endl;
    
    // Pulisco il buffer di input
    cin.ignore(10000, '\n');

    char query_line[256];
    cin.getline(query_line, 256);

    // Conteggio delle parole nella query
    int n_words = 0;
    char** query_words = new char*[30]; // Supponiamo max 30 parole
    char* word = strtok(query_line, " ");
    while (word != NULL) {
        query_words[n_words] = new char[strlen(word) + 1];
        strcpy(query_words[n_words], word);
        n_words++;
        word = strtok(NULL, " ");
    }

    if (n_words > 0) {
        int result_size = 0;
        int* matched_docs = match(inverted_index, index_size, query_words, n_words, result_size);

        cout << "Risultato del match (documenti ordinati per rilevanza):" << endl;
        for (int i = 0; i < result_size; i++) {
            cout << matched_docs[i] << " ";
        }
        cout << endl;

        // Deallocazione memoria dei risultati e della query
        delete[] matched_docs;
        for (int i = 0; i < n_words; i++) {
            delete[] query_words[i];
        }
        delete[] query_words;
    }
    
    // Deallocazione della memoria
    if(inverted_index != NULL){
        for(int i=0; i<index_size; i++){
            // Dealloco la lista di documenti per ogni parola
            while(inverted_index[i].l != NULL){
                inverted_index[i].l = delete_elem(inverted_index[i].l, inverted_index[i].l);
            }
        }
        delete[] inverted_index; // Dealloco l'array di parole
    }

    return 0;
}

// Punto 3.a: Stampa i documenti che contengono entrambe le parole
void AND(parola* ii, int size, const char* w1, const char* w2) {
    lista l1 = NULL;
    lista l2 = NULL;

    // Cerca le liste di documenti per le due parole
    for (int i = 0; i < size; i++) {
        if (strcmp(ii[i].p, w1) == 0) {
            l1 = ii[i].l;
        }
        if (strcmp(ii[i].p, w2) == 0) {
            l2 = ii[i].l;
        }
    }

    if (l1 == NULL || l2 == NULL) {
        cout << "Una o entrambe le parole non trovate." << endl;
        return;
    }

    // Intersezione delle due liste (essendo ordinate)
    lista p1 = l1;
    lista p2 = l2;
    while (p1 != NULL && p2 != NULL) {
        if (head(p1) < head(p2)) {
            p1 = tail(p1);
        } else if (head(p2) < head(p1)) {
            p2 = tail(p2);
        } else {
            print(head(p1));
            cout << " ";
            p1 = tail(p1);
            p2 = tail(p2);
        }
    }
    cout << endl;
}

// Punto 3.b: Restituisce i documenti che contengono almeno una delle parole, ordinati per rilevanza
int* match(parola* ii, int size, char** wl, int n, int& result_size) {
    result_size = 0;
    if (size == 0 || n == 0) {
        return NULL;
    }

    // 1. Trova l'ID massimo dei documenti per dimensionare gli array di conteggio
    int max_id = 0;
    for (int i = 0; i < size; i++) {
        lista l = ii[i].l;
        while (l != NULL) {
            if (head(l) > max_id) {
                max_id = head(l);
            }
            l = tail(l);
        }
    }

    // 2. Crea e inizializza gli array di conteggio
    int* counts = new int[max_id + 1];
    bool* seen = new bool[max_id + 1];
    for (int i = 0; i <= max_id; i++) {
        counts[i] = 0;
        seen[i] = false;
    }

    // 3. Popola i conteggi
    for (int i = 0; i < n; i++) { // Per ogni parola nella query
        for (int j = 0; j < size; j++) { // Cerca la parola nell'indice
            if (strcmp(wl[i], ii[j].p) == 0) {
                lista l = ii[j].l;
                while (l != NULL) {
                    int doc_id = head(l);
                    counts[doc_id]++;
                    seen[doc_id] = true;
                    l = tail(l);
                }
            }
        }
    }

    // 4. Prepara per l'ordinamento
    for (int i = 0; i <= max_id; i++) {
        if (seen[i]) {
            result_size++;
        }
    }

    if (result_size == 0) {
        delete[] counts;
        delete[] seen;
        return NULL;
    }

    DocMatch* sorted_docs = new DocMatch[result_size];
    int current = 0;
    for (int i = 0; i <= max_id; i++) {
        if (seen[i]) {
            sorted_docs[current].id = i;
            sorted_docs[current].count = counts[i];
            current++;
        }
    }
    
    // 5. Ordina (Bubble sort decrescente)
    for (int i = 0; i < result_size - 1; i++) {
        for (int j = 0; j < result_size - i - 1; j++) {
            if (sorted_docs[j].count < sorted_docs[j + 1].count) {
                DocMatch temp = sorted_docs[j];
                sorted_docs[j] = sorted_docs[j+1];
                sorted_docs[j+1] = temp;
            }
        }
    }

    // 6. Crea l'array di risultati finale
    int* result = new int[result_size];
    for (int i = 0; i < result_size; i++) {
        result[i] = sorted_docs[i].id;
    }

    // 7. Pulisci la memoria temporanea
    delete[] counts;
    delete[] seen;
    delete[] sorted_docs;

    return result;
}
