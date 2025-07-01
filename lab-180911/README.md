# Lab 180911 - Inverted Index Management System

## Overview
This program implements a small-scale inverted index system for document retrieval. An inverted index is a data structure used to accelerate word searches in a collection of documents. It maps each word to a list of document identifiers (posting list) in which the word appears.

The system can load an initial index from a file, update it with new documents, and perform search queries.

## Data Structures

### Word (`parola`)
The core data structure represents a word in the index:
```cpp
struct parola {
    char p[80];      // The word itself (up to 80 characters)
    int n_doc;       // The total number of documents containing the word
    lista l;         // A doubly-linked list (posting list) of document IDs
};
```
The inverted index is stored as a dynamic array of `parola` structs.

### Type Definitions
- `typedef elem* lista`: A doubly-linked list, used for the posting lists.
- `typedef int tipo_inf`: The type for document IDs (integers).

## Implemented Functions

The main logic is contained in `compito.cc`.

1.  **`parola* load(int& n)`**
    -   Loads an inverted index from a file named `inverted`.
    -   The file format expected is:
        1.  Number of unique words.
        2.  For each word: the word, the count of documents it's in, and the list of document IDs.
    -   Returns a dynamically allocated array of `parola` structs.

2.  **`void stampa(parola* ii, int n)`**
    -   Prints the entire inverted index in a human-readable format, showing each word and its corresponding posting list.

3.  **`void update(parola* &ii, int &size, const char* fileName)`**
    -   Updates the inverted index with words from a new document file.
    -   Handles two cases:
        -   **Existing Word**: Adds the new document ID to the word's posting list (if not already present).
        -   **New Word**: Dynamically resizes the index and adds the new word with its posting list.

4.  **`void AND(parola* ii, int size, const char* w1, const char* w2)`**
    -   Performs a logical AND query.
    -   Finds the intersection of the posting lists for two words (`w1` and `w2`).
    -   Prints the list of document IDs that contain *both* words.

5.  **`int* match(parola* ii, int size, char** wl, int n, int& result_size)`**
    -   Performs a broader match query for a list of words.
    -   Finds all documents that contain *at least one* of the specified words.
    -   Returns a new array of document IDs, sorted in descending order of relevance (i.e., by the number of query words they contain).

## Compilation and Execution

The project includes a `Makefile` for easy compilation.

```bash
# Navigate to the lab directory
cd lab-180911

# Clean previous builds and compile
make clean && make

# Run the program
./programa
```

## Sample Usage and Output

The program first loads the initial index, then prompts the user for a document to update the index with, and finally runs the `AND` and `match` queries.

### Expected Output

```
# Initial loaded index
Inverted Index Iniziale:
--- Inverted Index ---
Parola: computer
Numero documenti: 3
Documenti: 1 2 4 
------------------------
...

# Prompt for update file
Inserisci il nome del file del documento da aggiungere (es. doc): doc

# Index after updating with 'doc' file
Inverted Index Aggiornato:
--- Inverted Index ---
Parola: computer
Numero documenti: 4
Documenti: 1 2 4 5 
------------------------
Parola: laptop
Numero documenti: 2
Documenti: 1 3 
------------------------
Parola: tower
Numero documenti: 4
Documenti: 1 2 3 5 
------------------------
Parola: voltage
Numero documenti: 1
Documenti: 5 
------------------------

# Prompt for AND query
--- Ricerca AND ---
Inserisci la prima parola: computer
Inserisci la seconda parola: tower
Documenti che contengono computer AND tower:
1 2 5 

# Prompt for MATCH query
--- Ricerca MATCH ---
Inserisci una serie di parole separate da spazio (es. computer voltage):
computer voltage
Risultato del match (documenti ordinati per rilevanza):
5 1 2 4 
```
This demonstrates the full functionality of the system, from data loading and updating to executing complex search queries.
