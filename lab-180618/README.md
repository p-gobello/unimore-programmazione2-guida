# Lab 180618 - Binary Search Tree (BST) Implementation

## Overview
This lab implements a Binary Search Tree (Albero Binario di Ricerca) data structure with operations for insertion, search, and deletion. The BST stores data of type `tipo_inf` (likely a card structure with suit and value) with integer keys.

## Data Structures

### Node Structure (`bnode`)
```cpp
struct bnode {
    tipo_key key;        // Integer key for ordering
    tipo_inf inf;        // Information/data stored
    bnode* left;         // Left child pointer  
    bnode* right;        // Right child pointer
    bnode* parent;       // Parent pointer (for easier deletion)
};
```

### BST Type
- `typedef bnode* bst` - The BST is represented as a pointer to the root node

## Implemented Functions

### Core BST Operations

1. **`bnode* bst_newNode(tipo_key k, tipo_inf i)`**
   - Creates a new node with given key and information
   - Initializes all pointers to NULL
   - Returns pointer to the new node

2. **`void bst_insert(bst& b, bnode* n)`**
   - Inserts a node into the BST maintaining the BST property
   - Uses iterative approach to find the correct position
   - Updates parent pointers correctly
   - **Algorithm**: Compare keys and traverse left/right until finding insertion point

3. **`bnode* bst_search(bst b, tipo_key k)`**
   - Searches for a node with the given key
   - Uses iterative approach
   - Returns pointer to found node or NULL if not found
   - **Algorithm**: Compare key with current node, go left/right accordingly

4. **`void bst_delete(bst& b, bnode* n)`**
   - Deletes a node from the BST while maintaining BST property
   - Handles three cases:
     - **Leaf node**: Simply remove
     - **One child**: Replace with child
     - **Two children**: Replace with largest element in left subtree (predecessor)
   - Updates parent pointers correctly
   - Uses helper function `update_father()` to update parent-child relationships

### Accessor Functions

5. **`tipo_key get_key(bnode* n)`** - Returns the key of a node
6. **`tipo_inf get_value(bnode* n)`** - Returns the information stored in a node  
7. **`bst get_left(bst t)`** - Returns left subtree
8. **`bst get_right(bst t)`** - Returns right subtree
9. **`bnode* get_parent(bnode* n)`** - Returns parent node

### Utility Functions

10. **`void print_key(tipo_key k)`** - Prints a key value
11. **`update_father(bnode* p, bnode* q)`** - Helper function to update parent-child links during deletion

## Key Algorithms and Concepts

### BST Property
- For any node: all keys in left subtree < node key < all keys in right subtree

### Insertion Algorithm
1. Start from root
2. Compare new key with current node
3. Go left if smaller, right if larger
4. When reaching NULL, insert the new node
5. Update parent pointers

### Deletion Algorithm (Most Complex)
1. **Case 1 - Leaf**: Remove node directly
2. **Case 2 - One child**: Replace node with its child
3. **Case 3 - Two children**: 
   - Find predecessor (largest element in left subtree)
   - Replace deleted node with predecessor
   - Remove predecessor from its original position

### Search Algorithm
- Simple traversal following BST property
- O(log n) average case, O(n) worst case

## General Concepts for Future Reference

### When to Use BST
- When you need sorted data with efficient insertion/deletion/search
- Dynamic data where size changes frequently
- Need for in-order traversal to get sorted sequence

### Time Complexities
- **Search**: O(log n) average, O(n) worst
- **Insert**: O(log n) average, O(n) worst  
- **Delete**: O(log n) average, O(n) worst

### Implementation Tips
1. Always maintain parent pointers for easier deletion
2. Handle edge cases (empty tree, single node, root deletion)
3. Use helper functions to reduce code duplication
4. Be careful with pointer updates during deletion

### Common Pitfalls
- Forgetting to update parent pointers
- Memory leaks (not freeing deleted nodes)
- Incorrect handling of deletion cases
- Not maintaining BST property after operations

This implementation provides a solid foundation for understanding tree data structures and can be extended with additional operations like in-order traversal, tree balancing, etc.
