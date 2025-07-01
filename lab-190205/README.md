# Lab 190205 - Scala 40 Card Game

## Project Goal
This project implements a simplified, two-player card game based on Scala 40. The program manages each player's hand of cards using a sorted, doubly-linked list. The cards are sorted first by suit, then by value. The game logic involves players drawing cards, forming "scale" (runs of consecutive cards of the same suit), and playing them to score points.

## Data Structures

### `carta`
A simple struct representing a playing card with a `seme` (suit) and `valore` (value).
```cpp
typedef struct carta {
    char seme;   // C, F, P, Q
    int valore;  // 1-13
} tipo_inf;
```

### `lista`
A doubly-linked list used to manage each player's hand.

## Implemented Functions

### `compito.cc`
This file contains the core game logic.

*   **`void pesca(lista& carte)`**: Prompts the user to enter a suit and value for a new card and adds it to the player's hand in the correct sorted position.
*   **`void stampa(lista carte)`**: Prints all the cards in a player's hand.
*   **`carta* scala(lista carte, int& lunghezza)`**: Finds the first *maximal* scale (a run of 3 or more consecutive cards of the same suit) in a hand. It returns a pointer to the first card of the scale and its length.
*   **`carta* best_scala(lista carte, int& lunghezza)`**: Finds the *best* scale in a hand, defined as the scale with the highest total point value.
*   **`int cala(lista& carte)`**: Uses `best_scala` to find the best scale, removes the cards of that scale from the player's hand, and returns the total score of the played scale.
*   **`int main()`**: The main game loop. It initializes the game for two players, handles turns where players draw and play cards, tracks scores, and declares a winner.

### `tipo.cc`
*   **`int compare(tipo_inf c1, tipo_inf c2)`**: The comparison function used to sort cards. It sorts primarily by suit (`C` < `F` < `P` < `Q`) and secondarily by value.

### `liste.cc`
Contains the standard implementation for doubly-linked list operations (`ord_insert_elem`, `delete_elem`, etc.).

## How to Compile and Run
The project includes a `Makefile`. To compile, navigate to the `lab-190205` directory and run:
```sh
make
```
This will create an executable named `gioco`. To run the program:
```sh
./gioco
```
The program will then prompt for the number of cards per player and the specific cards for each player's initial hand.

## Example Execution

Based on the test data provided in the lab sheet:

**Initial Setup:**
- 6 cards per player.
- Player 1 Hand: `12Q 2P 10Q 3P 11Q 4P`
- Player 2 Hand: `1F 6F 3F 5F 1C 4F`

**Turn 1:**
- Player 1 draws `9Q`, plays the best scale (`10Q 11Q 12Q`), and scores 33 points.
- Player 2 draws `2C`, plays their only scale (`3F 4F 5F 6F`), and scores 18 points.

**Turn 2:**
- Player 1 draws `13Q` and now has a new scale (`9Q 10Q 11Q 12Q 13Q`). They play it, emptying their hand and winning the game.

The program correctly handles this logic, identifying the best scale and updating player hands and scores accordingly. 