# Lab 240703 - Binary Search Tree with Hotel Management System

## Overview
This lab implements a Binary Search Tree (BST) data structure for managing hotel information. The system stores hotels with ratings, names, and cities, using the rating as the search key for efficient hotel lookup and management operations.

## Data Structures

### Hotel Information Structure (`tipo_inf`)
Based on the `hotel.txt` file format, the data likely represents:
```cpp
// Inferred structure from hotel.txt format
typedef struct {
    char nome[50];     // Hotel name (e.g., "Al parco", "Lo specchio")
    char citta[30];    // City (e.g., "Firenze", "Bologna")  
    // Rating used as BST key
} tipo_inf;
```

### BST Node Structure (`bnode`)
```cpp
struct bnode {
    tipo_key key;      // Hotel rating (1-5 stars)
    tipo_inf inf;      // Hotel information (name, city)
    bnode* left;       // Left subtree (lower ratings)
    bnode* right;      // Right subtree (higher ratings)
    bnode* parent;     // Parent node pointer
};
```

### BST Type
- `typedef bnode* bst` - Tree represented as pointer to root node
- `typedef int tipo_key` - Rating as integer key (1-5)

## Sample Hotel Data Analysis

From `hotel.txt`:

### Hotels by Rating (BST Key)
- **Rating 1**: Il tortellino (Bologna)
- **Rating 2**: Il portico (Firenze)  
- **Rating 3**: Al parco (Firenze), Carlo Alberto (Bologna)
- **Rating 4**: Lo specchio (Bologna)
- **Rating 5**: Michelangelo (Firenze), Piazza Nettuno (Bologna)

### Geographic Distribution
- **Bologna**: Il tortellino (1★), Carlo Alberto (3★), Lo specchio (4★), Piazza Nettuno (5★)
- **Firenze**: Il portico (2★), Al parco (3★), Michelangelo (5★)

## Implemented Functions

### Core BST Operations

1. **`bnode* bst_newNode(tipo_key k, tipo_inf i)`**
   - Creates new hotel node with given rating and information
   - Initializes all pointers to NULL
   - **Use case**: Adding new hotel to system

2. **`void bst_insert(bst& b, bnode* n)`**
   - Inserts hotel maintaining BST property by rating
   - **Key insight**: Uses `compare_key(s1,s2) = s2-s1` (reverse order!)
   - **Result**: Higher ratings go LEFT, lower ratings go RIGHT
   - **Tree structure**: 5★ hotels at leftmost, 1★ hotels at rightmost

3. **`bnode* bst_search(bst b, tipo_key k)`**
   - Searches for hotels with specific rating
   - Returns first hotel found with that rating
   - **Use case**: "Find all 4-star hotels"

4. **`void bst_delete(bst& b, bnode* n)`**
   - Removes hotel from BST maintaining structure
   - Handles three deletion cases with debug output:
     - **Leaf hotel**: Simple removal
     - **One child**: Replace with child subtree
     - **Two children**: Replace with predecessor (rightmost in left subtree)

### Accessor Functions

5. **`tipo_key get_key(bnode* n)`** - Returns hotel rating
6. **`tipo_inf get_value(bnode* n)`** - Returns hotel information
7. **`bst get_left(bst t)`** - Returns higher-rated hotels subtree
8. **`bst get_right(bst t)`** - Returns lower-rated hotels subtree
9. **`bnode* get_parent(bnode* n)`** - Returns parent node

### Utility Functions

10. **`void print_key(tipo_key k)`** - Prints hotel rating
11. **`update_father(bnode* p, bnode* q)`** - Helper for maintaining parent-child links

## Key Algorithms and Hotel Management Concepts

### Rating-Based Tree Structure

#### Reverse Ordering (Important!)
The compare function `compare_key(s1,s2) = s2-s1` creates **reverse ordering**:
```
       4★ (Lo specchio)
      /                \
   5★ (Michelangelo)    3★ (Al parco)
   /                    /             \
5★ (Piazza Nettuno)  []          2★ (Il portico)
                                  \
                                  1★ (Il tortellino)
```

#### Tree Traversal for Hotels
```cpp
// Get hotels in descending rating order (in-order traversal)
void print_hotels_by_rating_desc(bst root) {
    if (root != NULL) {
        print_hotels_by_rating_desc(get_left(root));   // Higher ratings first
        print(get_value(root));                        // Current hotel
        print_hotels_by_rating_desc(get_right(root));  // Lower ratings last
    }
}
```

### Hotel Search and Management

#### Find Hotels by Rating Range
```cpp
void find_hotels_in_range(bst root, int min_rating, int max_rating) {
    if (root == NULL) return;
    
    int current_rating = get_key(root);
    
    // Due to reverse ordering: left = higher, right = lower
    if (current_rating > min_rating) 
        find_hotels_in_range(get_right(root), min_rating, max_rating);
        
    if (current_rating >= min_rating && current_rating <= max_rating)
        print(get_value(root));
        
    if (current_rating < max_rating)
        find_hotels_in_range(get_left(root), min_rating, max_rating);
}
```

#### Find Best Hotels (Highest Ratings)
```cpp
// Due to reverse ordering, best hotels are in leftmost path
bnode* find_best_hotel(bst root) {
    if (root == NULL) return NULL;
    while (get_left(root) != NULL) {
        root = get_left(root);
    }
    return root;  // Leftmost = highest rating
}
```

#### Hotel Statistics
```cpp
int count_hotels_by_rating(bst root, int target_rating) {
    if (root == NULL) return 0;
    
    int count = 0;
    if (get_key(root) == target_rating) count = 1;
    
    return count + 
           count_hotels_by_rating(get_left(root), target_rating) +
           count_hotels_by_rating(get_right(root), target_rating);
}
```

## Practical Applications

### Hotel Booking System

#### Quality-Based Search
- **Premium search**: Find 4-5 star hotels (leftmost nodes)
- **Budget search**: Find 1-2 star hotels (rightmost nodes)
- **Specific rating**: Direct search with `bst_search()`

#### Recommendation Engine
```cpp
// Recommend hotels near target rating
lista recommend_similar_hotels(bst hotels, int target_rating, int tolerance) {
    lista recommendations = NULL;
    find_hotels_in_range(hotels, 
                        target_rating - tolerance, 
                        target_rating + tolerance);
    return recommendations;
}
```

#### Hotel Management Operations
```cpp
// Add new hotel to system
void add_hotel(bst& hotel_tree, int rating, string name, string city) {
    tipo_inf hotel_info;
    // Initialize hotel_info with name and city
    bnode* new_hotel = bst_newNode(rating, hotel_info);
    bst_insert(hotel_tree, new_hotel);
}

// Remove hotel (e.g., closed business)
void remove_hotel(bst& hotel_tree, int rating, string name) {
    bnode* hotel = bst_search(hotel_tree, rating);
    // Additional logic to find specific hotel by name if multiple with same rating
    if (hotel != NULL) {
        bst_delete(hotel_tree, hotel);
    }
}
```

### Travel Planning Integration

#### City-Based Filtering
```cpp
// Find all hotels in specific city (requires full tree traversal)
void find_hotels_in_city(bst root, string target_city) {
    if (root == NULL) return;
    
    if (get_value(root).citta == target_city) {
        print(get_value(root));
    }
    
    find_hotels_in_city(get_left(root), target_city);
    find_hotels_in_city(get_right(root), target_city);
}
```

## General Concepts for Future Reference

### Reverse Ordering in BSTs
- **Design choice**: Higher values left, lower values right
- **Impact on algorithms**: All traversal logic reversed
- **Use case**: When you want "best first" ordering in left-to-right traversal
- **Common mistake**: Forgetting about reverse ordering in range queries

### Multi-Criteria Data in BSTs
- **Primary key**: Rating for BST ordering
- **Secondary data**: Name and city stored but not used for ordering
- **Limitation**: Cannot efficiently search by secondary criteria
- **Solution**: Multiple BSTs or more complex data structures

### Hotel Rating System Design

#### Rating Standardization
- **Range**: 1-5 stars standard
- **Granularity**: Integer vs. decimal ratings (4.5 stars)
- **Consistency**: Same rating criteria across all hotels

#### Handling Duplicate Ratings
- **Multiple hotels, same rating**: BST insertion typically goes right
- **Search considerations**: `bst_search()` returns first found
- **Complete search**: Need traversal to find all hotels with specific rating

### Performance Considerations

#### Time Complexities
- **Search by rating**: O(log n) average, O(n) worst case
- **Insert new hotel**: O(log n) average, O(n) worst case
- **Delete hotel**: O(log n) average, O(n) worst case
- **Find hotels in city**: O(n) - requires full traversal

#### Memory Usage
- **Node overhead**: 3 pointers + key + hotel data per node
- **Tree balance**: Affects performance significantly
- **Consider**: Self-balancing trees (AVL, Red-Black) for guaranteed performance

### Real-World Extensions

#### Enhanced Hotel System
```cpp
typedef struct {
    char nome[100];
    char citta[50];
    char indirizzo[200];
    float rating;              // Allow decimal ratings
    int num_rooms;
    float price_per_night;
    bool wifi_available;
    bool parking_available;
    char amenities[500];
} enhanced_hotel;
```

#### Multi-Index System
- **Primary BST**: By rating for quality-based search
- **Secondary BST**: By price for budget-based search  
- **Hash table**: By city for location-based search
- **Combined queries**: Intersection of multiple search results

This lab demonstrates how BSTs can be effectively used for managing real-world data with natural ordering criteria, while highlighting important considerations like reverse ordering and multi-criteria search requirements.
