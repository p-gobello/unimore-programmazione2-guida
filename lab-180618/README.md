# Lab 180618: Loyalty Card Management

## Overview

This project implements a system for managing customer loyalty cards using a Binary Search Tree (BST). The system allows for the creation of cards, updating points based on daily purchases, and performing queries on the collected data. The BST is used to ensure efficient searching and ordered retrieval of cards based on their unique integer ID.

## Data Model

The core of the system is the loyalty card, which is stored in a BST where the card number is the key.

### Card Information (`carta.h`)

All information related to a customer's card, except for the ID, is defined in the `carta` module.

-   **`tipo_inf`**: A struct that holds the customer's full name (`char nome_cognome[41]`) and their total accumulated points (`int punti`).

```cpp
struct cliente {
    char nome_cognome[41];
    int punti;
};

typedef cliente tipo_inf;
```

### Relationships (BST)

The relationships are implicitly managed by the Binary Search Tree (`bst.h`, `bst.cc`):

-   **Key**: The loyalty card number (`tipo_key`, an `int`).
-   **Value**: The customer's card information (`tipo_inf`).
-   The BST structure ensures that all cards are stored in ascending order based on their key.

## Input

The program is fully interactive. All data, including the initial set of cards, range queries, and purchase updates, is entered by the user directly via the keyboard.

## Implemented Features

The `compito.cc` file contains the main logic, which is divided into the following points as per the assignment.

### 1. Initial Card Acquisition
- The program first asks the user for the number of cards to be created.
- It then interactively prompts for the details of each card (card number, name, and initial points) and inserts them into the BST.

### 2. Ordered Card Printing
- After the initial data entry, the program performs an in-order traversal of the BST to print the details of all cards in ascending order of their card number.

### 2.b. Point Summation in a Range (`totalePunti`)
- This feature calculates the total sum of points for all cards whose card number falls within a user-specified range `[inf, sup]`.
- The program prompts the user for the lower and upper bounds of the range and prints the resulting sum.

### 3. Purchase Updates
- The system enters a loop where the user can log daily purchases by providing a card number and the points accumulated in that transaction.
- If the card exists, its total points are updated.
- If the card does not exist, an error is reported.
- The loop terminates when the user enters non-numeric input.

### 4. Identifying Inactive Cards
- After the purchase update phase is complete, the program identifies and prints a list of all loyalty cards that did not have any purchases recorded during the session.

## Core Data Structures

-   **Binary Search Tree (`bst`)**: The primary data structure, provided in `bst.h` and `bst.cc`. It uses an integer key for the card number and is optimized for searching and ordered traversal.
-   **Card (`carta`)**: A module defining the `tipo_inf` data structure and its associated helper functions (`compare`, `copy`, `print`).

## How to Compile and Run

A `Makefile` is provided for easy compilation.

1.  **Compile the project**:
    ```sh
    make
    ```
2.  **Run the executable**:
    ```sh
    ./programma
    ```
The program will then guide the user through the interactive steps.

### Expected Output

Given the test data from the assignment PDF, the program will produce the following output:

**Initial Data Entry & Punto 2 (Ordered Print)**
```
// User enters 4 cards:
// 1236, Anna Viola, 22
// 4412, Paolo Rossi, 36
// 2628, Marco Neri, 176
// 3036, Mario Bianchi, 144

Punto 2: Stampa delle carte in ordine crescente di codice:
1236 Anna Viola 22
2628 Marco Neri 176
3036 Mario Bianchi 144
4412 Paolo Rossi 36
```

**Punto 2.b (Range Sum)**
```
// User enters range [2000, 4000]

Il totale dei punti per le carte nell'intervallo [2000, 4000] e': 320
```

**Punto 3 (Updates & Final Print)**
```
// User enters purchases:
// 4412, 34
// 1238, 37  (Error)
// 3036, 22

Errore: carta 1238 non trovata.

Stampa del BST dopo aggiornamenti:
1236 Anna Viola 22
2628 Marco Neri 176
3036 Mario Bianchi 166
4412 Paolo Rossi 70
```

**Punto 4 (Inactive Cards)**
```
Punto 4: Stampa delle carte senza acquisti in giornata:
1236 Anna Viola 22
2628 Marco Neri 176
``` 