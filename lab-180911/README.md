# Lab 180911 - Doubly Linked Lists and Inverted Index

## Overview
This lab implements doubly-linked lists with various operations and appears to be designed for creating an inverted index data structure for document search. The implementation includes ordered and unordered list operations, search functionality, and supports a word-document mapping system.

## Data Structures

### Doubly Linked List Node (`elem`)
```cpp
struct elem {
    tipo_inf inf;    // Data stored (int in this case)
    elem* pun;       // Pointer to next element (tail)
    elem* prev;      // Pointer to previous element
};
```

### Word Structure (`parola`)
```cpp
struct parola {
    char p[80];      // Word string (up to 80 characters)
    int n_doc;       // Number of documents containing this word
    lista l;         // List of document IDs containing this word
};
```

### Type Definition
- `typedef elem* lista` - List represented as pointer to first element
- `typedef int tipo_inf` - Information type is integer

## Implemented Functions

### Core List Operations

1. **`elem* new_elem(tipo_inf inf)`**
   - Creates a new list element with given information
   - Initializes both pointers (pun, prev) to NULL
   - Uses `copy()` function for proper data assignment

2. **`lista insert_elem(lista l, elem* e)`**
   - Inserts element at the head of the list
   - Updates bidirectional links properly
   - Returns new head of the list
   - **Time Complexity**: O(1)

3. **`lista delete_elem(lista l, elem* e)`**
   - Removes specified element from the list
   - Handles two cases:
     - Element is head: update list head
     - Element is not head: update previous element's link
   - Updates bidirectional links
   - Frees memory of deleted element
   - **Time Complexity**: O(1) if element pointer is known

4. **`lista ord_insert_elem(lista l, elem* e)`**
   - Inserts element maintaining sorted order
   - Finds correct position by comparing values
   - Handles special cases (empty list, insert at head)
   - Updates all necessary pointers
   - **Time Complexity**: O(n) for finding position

### Search Operations

5. **`elem* search(lista l, tipo_inf v)`**
   - Linear search through entire list
   - Returns pointer to element if found, NULL otherwise
   - **Use case**: Unsorted lists
   - **Time Complexity**: O(n)

6. **`elem* ord_search(lista l, tipo_inf v)`**
   - Optimized search for sorted lists
   - Stops when current value exceeds target (early termination)
   - Returns pointer to element if found, NULL otherwise
   - **Use case**: Sorted lists
   - **Time Complexity**: O(n) worst case, but better average case

### Accessor Functions

7. **`tipo_inf head(lista p)`** - Returns data from first element
8. **`lista tail(lista p)`** - Returns pointer to next element  
9. **`lista prev(lista p)`** - Returns pointer to previous element

### Type Operations (from `tipo.cc`)

10. **`int compare(tipo_inf s1, tipo_inf s2)`**
    - Compares two integer values
    - Returns: negative if s1 < s2, zero if equal, positive if s1 > s2

11. **`void copy(tipo_inf& dest, tipo_inf source)`**
    - Copies source value to destination
    - Simple assignment for integers

12. **`void print(tipo_inf inf)`**
    - Prints the integer value

## Key Algorithms and Concepts

### Doubly Linked List Properties
- **Bidirectional traversal**: Can move forward and backward
- **Efficient deletion**: O(1) when element pointer is known
- **Memory overhead**: Extra pointer per node
- **Cache locality**: Generally worse than arrays

### Ordered vs Unordered Operations
- **Unordered lists**: Faster insertion O(1), slower search O(n)
- **Ordered lists**: Slower insertion O(n), potentially faster search

### Inverted Index Concept
Based on the file structure (`doc`, `inverted`, `parola.h`), this appears to implement:
- **Document collection**: List of words in documents
- **Inverted index**: Mapping from words to document IDs
- **Word frequency**: Track which documents contain each word

#### Sample Data Analysis
**doc file**: Contains document 5 with words: computer, tower, voltage
**inverted file**: Shows inverted index format:
- 3 unique words
- computer appears in documents 1, 2, 4
- laptop appears in documents 1, 3  
- tower appears in documents 1, 2, 3

## General Concepts for Future Reference

### When to Use Doubly Linked Lists
- **Frequent deletions**: When you have element pointers
- **Bidirectional traversal**: Need to move both directions
- **Undo operations**: Stack-like behavior with backward movement
- **LRU caches**: Need to move elements to front/back efficiently

### Doubly vs Singly Linked Lists

#### Advantages of Doubly Linked
- O(1) deletion with element pointer
- Bidirectional traversal
- Easier implementation of some algorithms

#### Disadvantages
- Extra memory per node
- More complex pointer management
- Slightly slower insertion due to extra pointer updates

### Search Strategy Selection
```cpp
// Choose search method based on list ordering
if (list_is_sorted) {
    result = ord_search(list, value);  // Early termination possible
} else {
    result = search(list, value);      // Full traversal needed
}
```

### Ordered Insertion Strategy
1. **Empty list or insert at head**: Direct insertion
2. **Find position**: Traverse until finding correct spot
3. **Insert between nodes**: Update 4 pointers carefully
4. **Maintain ordering**: Essential for ord_search() to work

### Implementation Best Practices

#### Pointer Management
1. Always update both directions in doubly linked lists
2. Handle edge cases (empty list, single element, head/tail operations)
3. Check for NULL pointers before dereferencing
4. Free memory properly to avoid leaks

#### Search Optimization
- Use ord_search() only on sorted lists
- Consider binary search for very large sorted lists
- Cache frequently accessed elements
- Use appropriate data structure for access pattern

### Applications
- **Text processing**: Word indexing and search
- **Database indexing**: B+ trees use similar concepts
- **Browser history**: Back/forward navigation
- **Music playlists**: Previous/next song functionality
- **Undo/Redo systems**: Bidirectional operation history

### Time Complexities Summary
- **Insert (head)**: O(1)
- **Insert (ordered)**: O(n)
- **Delete (with pointer)**: O(1)
- **Search (unsorted)**: O(n)
- **Search (sorted)**: O(n) worst case, better average
- **Space**: O(n) with double pointer overhead

This lab provides essential foundation for understanding linked data structures and their applications in information retrieval systems like search engines and databases.
