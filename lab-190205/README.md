# Lab 190205 - Doubly Linked Lists with Playing Cards

## Overview
This lab implements doubly-linked lists specifically designed for managing playing cards (`carta`). It reuses the same list structure as previous labs but applies it to a card game context, demonstrating how generic list operations can work with different data types.

## Data Structures

### Card Structure (`carta`)
```cpp
typedef struct carta {
    char seme;       // Suit: 'C'(Cuori), 'Q'(Quadri), 'F'(Fiori), 'P'(Picche)
    int valore;      // Value: 1-13 (Ace=1, Jack=11, Queen=12, King=13)
} tipo_inf;
```

### Doubly Linked List Node (`elem`)
```cpp
struct elem {
    tipo_inf inf;    // Card data (carta structure)
    elem* pun;       // Pointer to next element
    elem* prev;      // Pointer to previous element
};
```

## Implemented Functions

### List Operations (Same as lab-180911 but for cards)

1. **`elem* new_elem(tipo_inf inf)`**
   - Creates new list element containing a card
   - Copies card data using `copy()` function
   - Initializes pointers to NULL

2. **`lista insert_elem(lista l, elem* e)`**
   - Inserts card at head of list
   - Maintains bidirectional links
   - **Use case**: Adding cards to hand/deck

3. **`lista delete_elem(lista l, elem* e)`**
   - Removes specific card from list
   - Updates all necessary pointers
   - **Use case**: Playing a card, discarding

4. **`lista ord_insert_elem(lista l, elem* e)`**
   - Inserts card maintaining sorted order
   - Order determined by card comparison function
   - **Use case**: Organizing hand by suit/value

### Search Operations

5. **`elem* search(lista l, tipo_inf v)`**
   - Linear search for specific card
   - **Use case**: Finding if hand contains specific card

6. **`elem* ord_search(lista l, tipo_inf v)`**
   - Optimized search for sorted card lists
   - Early termination when order exceeded
   - **Use case**: Searching organized card collections

### Card-Specific Type Operations

7. **`int compare(tipo_inf c1, tipo_inf c2)`**
   - Compares two cards for ordering
   - **Typical implementation**: 
     - Primary: suit comparison
     - Secondary: value comparison
   - **Example**: Hearts < Diamonds < Clubs < Spades, then by value

8. **`void copy(tipo_inf& dest, tipo_inf source)`**
   - Copies card from source to destination
   - Copies both suit and value fields

9. **`void print(tipo_inf inf)`**
   - Prints card in readable format
   - **Example output**: "Ace of Hearts", "King of Spades"

### Accessor Functions

10. **`tipo_inf head(lista p)`** - Returns card data from first element
11. **`lista tail(lista p)`** - Returns next element pointer
12. **`lista prev(lista p)`** - Returns previous element pointer

## Key Algorithms and Card Game Concepts

### Card Ordering Strategies

#### By Suit Priority
```cpp
int compare_by_suit(carta c1, carta c2) {
    if (c1.seme != c2.seme)
        return c1.seme - c2.seme;  // Compare suits first
    return c1.valore - c2.valore;   // Then values
}
```

#### By Value Priority
```cpp
int compare_by_value(carta c1, carta c2) {
    if (c1.valore != c2.valore)
        return c1.valore - c2.valore;  // Compare values first
    return c1.seme - c2.seme;        // Then suits
}
```

### Common Card Operations

#### Hand Management
- **Add card**: `insert_elem()` or `ord_insert_elem()`
- **Play card**: `search()` then `delete_elem()`
- **Check for card**: `search()` or `ord_search()`
- **Sort hand**: Build new list using `ord_insert_elem()`

#### Deck Operations
- **Shuffle**: Requires additional randomization logic
- **Deal**: Remove from head/tail
- **Count cards**: Traverse list

## Practical Applications

### Card Game Implementations

1. **Player Hands**
   - Use ordered lists for easy organization
   - Quick card lookup with `ord_search()`
   - Easy card removal when playing

2. **Deck Management**
   - Unordered list for shuffled deck
   - Head/tail operations for dealing
   - Search for specific cards

3. **Discard Pile**
   - Simple list with head insertion
   - Last played card always at head

4. **Sorting and Analysis**
   - Group cards by suit using multiple lists
   - Find patterns (sequences, pairs, etc.)

### Example Card Game Operations

#### Check for Pairs
```cpp
bool has_pair(lista hand) {
    lista current = hand;
    while (current != NULL) {
        lista check = tail(current);
        while (check != NULL) {
            if (head(current).valore == head(check).valore)
                return true;
            check = tail(check);
        }
        current = tail(current);
    }
    return false;
}
```

#### Count Cards by Suit
```cpp
int count_suit(lista hand, char suit) {
    int count = 0;
    while (hand != NULL) {
        if (head(hand).seme == suit)
            count++;
        hand = tail(hand);
    }
    return count;
}
```

## General Concepts for Future Reference

### Data Structure Reusability
- Same list implementation works for different data types
- Only `compare()`, `copy()`, and `print()` functions need modification
- Generic programming concept (templates in C++)

### Type Safety
- `typedef` provides clear data type definitions
- Encapsulation of card structure prevents invalid states
- Clear interface between list operations and data types

### Card Game Design Patterns

#### State Management
- **Player hands**: Ordered lists for organization
- **Game state**: Multiple lists for different card collections
- **History**: List of played cards

#### Validation
- Check card validity before operations
- Ensure no duplicate cards in game
- Validate game rules through list operations

### Performance Considerations

#### Memory Usage
- Each card requires: card data + 2 pointers
- Doubly linked allows O(1) deletion with card pointer
- Consider array representation for large card sets

#### Operation Efficiency
- **Insert at head**: O(1)
- **Ordered insert**: O(n)
- **Search**: O(n) for unsorted, early termination for sorted
- **Delete with pointer**: O(1)

### Real-World Applications
- **Digital card games**: Poker, Blackjack, Solitaire
- **Casino software**: Card tracking and verification
- **Educational games**: Teaching card game rules
- **Simulation software**: Probability analysis

This lab demonstrates how fundamental data structures can be applied to domain-specific problems like card games, showing the importance of generic design and proper data type abstraction.
