# Lab 220721 - Card Game Management with Multiple Hands

## Overview
This lab implements card game management using doubly-linked lists to handle multiple sets of playing cards. It demonstrates managing different card hands/decks (g1 and g2) using the same data structure, typical for multiplayer card games or comparing different card sets.

## Data Structures

### Playing Card Structure (`tipo_inf`)
```cpp
typedef struct {
    char seme;       // Suit: 'P'(Picche/Spades), 'Q'(Quadri/Diamonds), 
                     //       'F'(Fiori/Clubs), 'C'(Cuori/Hearts)
    int valore;      // Value: 1-13 (Ace=1, Jack=11, Queen=12, King=13)
} tipo_inf;
```

### Doubly Linked List Node (`elem`)
```cpp
struct elem {
    tipo_inf inf;    // Card data
    elem* pun;       // Pointer to next card
    elem* prev;      // Pointer to previous card
};
```

## Sample Card Data Analysis

### Player 1 Hand (g1.txt)
**12 cards total:**
- **Picche (Spades)**: 2♠, 3♠, 4♠, 4♠ *(duplicate!)*
- **Quadri (Diamonds)**: 2♦, 3♦, 4♦
- **Fiori (Clubs)**: 3♣, 3♣ *(duplicate!)*
- **Cuori (Hearts)**: 2♥

*Note: Contains duplicate cards (4♠, 3♣) - may indicate errors or special game rules*

### Player 2 Hand (g2.txt)
**12 cards total:**
- **Picche (Spades)**: 6♠, 7♠, 6♠ *(duplicate!)*, 2♠
- **Quadri (Diamonds)**: 6♦, 7♦, 2♦, 1♦
- **Fiori (Clubs)**: 1♣
- **Cuori (Hearts)**: 1♥, 6♥, 2♥

*Note: Also contains duplicate 6♠*

## Implemented Functions

### Core List Operations

1. **`elem* new_elem(tipo_inf inf)`**
   - Creates new card element
   - Copies card data (suit and value)
   - Initializes pointers to NULL

2. **`lista insert_elem(lista l, elem* e)`**
   - Inserts card at head of list
   - Updates bidirectional links
   - **Use case**: Adding cards to hand, dealing cards

3. **`lista delete_elem(lista l, elem* e)`**
   - Removes specific card from hand
   - Updates all necessary pointers
   - **Use case**: Playing a card, discarding

4. **`elem* search(lista l, tipo_inf v)`**
   - Linear search for specific card
   - **Use case**: Checking if player has a particular card

### Accessor Functions

5. **`tipo_inf head(lista p)`** - Returns card data from first element
6. **`lista tail(lista p)`** - Returns next card in list
7. **`lista prev(lista p)`** - Returns previous card in list

### Card Type Operations

8. **`int compare(tipo_inf c1, tipo_inf c2)`**
   - Compares two cards for equality/ordering
   - **Possible strategies**:
     - Exact match (suit and value)
     - Value-first comparison
     - Suit-first comparison

9. **`void copy(tipo_inf& dest, tipo_inf source)`**
   - Copies card data from source to destination
   - Copies both suit and value fields

10. **`void print(tipo_inf inf)`**
    - Prints card in readable format
    - **Example**: "2♠", "Jack♥", "Ace♦"

## Card Game Algorithms and Concepts

### Multi-Hand Card Management

#### Hand Comparison
```cpp
// Compare hands for common cards
lista find_common_cards(lista hand1, lista hand2) {
    lista common = NULL;
    lista current1 = hand1;
    
    while (current1 != NULL) {
        if (search(hand2, head(current1)) != NULL) {
            elem* common_card = new_elem(head(current1));
            common = insert_elem(common, common_card);
        }
        current1 = tail(current1);
    }
    return common;
}
```

#### Card Counting
```cpp
// Count cards by suit
int count_suit(lista hand, char suit) {
    int count = 0;
    while (hand != NULL) {
        if (head(hand).seme == suit) count++;
        hand = tail(hand);
    }
    return count;
}

// Count cards by value
int count_value(lista hand, int value) {
    int count = 0;
    while (hand != NULL) {
        if (head(hand).valore == value) count++;
        hand = tail(hand);
    }
    return count;
}
```

#### Duplicate Detection
```cpp
bool has_duplicates(lista hand) {
    lista current = hand;
    while (current != NULL) {
        lista check = tail(current);
        while (check != NULL) {
            if (compare(head(current), head(check)) == 0)
                return true;
            check = tail(check);
        }
        current = tail(current);
    }
    return false;
}
```

### Game Rule Implementation

#### Card Game Validation
```cpp
// Check if hand is valid (no duplicates, proper count)
bool is_valid_hand(lista hand, int expected_count) {
    if (count_cards(hand) != expected_count) return false;
    return !has_duplicates(hand);
}

// Count total cards in hand
int count_cards(lista hand) {
    int count = 0;
    while (hand != NULL) {
        count++;
        hand = tail(hand);
    }
    return count;
}
```

#### Winning Conditions
```cpp
// Check for pairs
int count_pairs(lista hand) {
    int pairs = 0;
    lista current = hand;
    while (current != NULL) {
        int value_count = count_value(hand, head(current).valore);
        pairs += value_count / 2;
        current = tail(current);
    }
    return pairs;
}

// Check for sequences (requires sorted hand)
bool has_sequence(lista hand, int length) {
    // Implementation depends on specific game rules
    // Would need to sort hand first, then check consecutive values
}
```

### Data Analysis from Sample Files

#### Statistical Analysis
**g1.txt analysis:**
- Suits distribution: P(4), Q(3), F(2), C(3) *(includes duplicates)*
- Values distribution: 2(3), 3(4), 4(3) *(includes duplicates)*
- Data quality issues: Contains duplicates

**g2.txt analysis:**
- Suits distribution: P(4), Q(4), F(1), C(3) *(includes duplicates)*
- Values distribution: 1(3), 2(3), 6(4), 7(2) *(includes duplicates)*
- Data quality issues: Contains duplicates

## Practical Applications

### Multiplayer Card Games

#### Game Setup
```cpp
// Initialize multiple player hands
lista players[4] = {NULL, NULL, NULL, NULL};

// Deal cards to players
void deal_cards(lista& deck, lista players[], int num_players, int cards_per_player) {
    for (int round = 0; round < cards_per_player; round++) {
        for (int player = 0; player < num_players; player++) {
            if (deck != NULL) {
                elem* card = deck;
                deck = tail(deck);  // Remove from deck
                card->pun = card->prev = NULL;  // Isolate card
                players[player] = insert_elem(players[player], card);
            }
        }
    }
}
```

#### Game State Management
```cpp
struct game_state {
    lista players[4];        // Player hands
    lista discard_pile;      // Played cards
    lista deck;              // Remaining cards
    int current_player;      // Whose turn
    int round_number;        // Game progress
};
```

### Card Analysis Tools

#### Hand Strength Evaluation
```cpp
int evaluate_hand_strength(lista hand) {
    int score = 0;
    score += count_pairs(hand) * 10;        // Pairs worth 10 points
    score += count_suit(hand, 'P') * 2;     // Spades worth more
    // Add more scoring rules...
    return score;
}

// Compare two hands
int compare_hands(lista hand1, lista hand2) {
    return evaluate_hand_strength(hand1) - evaluate_hand_strength(hand2);
}
```

## General Concepts for Future Reference

### Multi-Collection Management
- **Separate hands**: Each player has independent card list
- **Shared resources**: Common deck, discard pile
- **State synchronization**: Keep all collections consistent
- **Memory management**: Proper cleanup when transferring cards

### Data Integrity in Card Games
- **Uniqueness**: Typically no duplicate cards in standard games
- **Conservation**: Total cards should remain constant
- **Validation**: Check hand sizes, card counts
- **Error handling**: Deal with invalid states gracefully

### Game Design Patterns

#### Turn-Based Systems
```cpp
class CardGame {
    lista player_hands[MAX_PLAYERS];
    lista community_cards;
    int current_player;
    
    void next_turn() { 
        current_player = (current_player + 1) % num_players; 
    }
};
```

#### Card Transfer Operations
- **Play card**: Remove from hand, add to discard/community
- **Draw card**: Remove from deck, add to hand  
- **Trade cards**: Move between player hands
- **Shuffle**: Randomize card order (requires additional logic)

### Performance Considerations

#### Memory Management
- **Card objects**: Fixed size per card (char + int)
- **List overhead**: Two pointers per card
- **Multiple lists**: Separate memory allocation per hand

#### Operation Efficiency
- **Search operations**: O(n) for finding specific cards
- **Hand size**: Typically small (5-20 cards), so O(n) acceptable
- **Frequent operations**: Insert/delete at head for performance

### Real-World Applications
- **Digital card games**: Poker, Blackjack, Hearts, Spades
- **Trading card games**: Magic, Pokemon, Yu-Gi-Oh
- **Casino software**: Multi-player table games
- **Educational games**: Teaching card game rules and probability
- **Simulation software**: Card game strategy analysis

This lab demonstrates managing multiple related data sets with the same structure, essential for multiplayer games and comparative data analysis applications.
