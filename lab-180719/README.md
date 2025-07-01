# Lab 180719 - Queue and Graph Implementation

## Overview
This lab implements two fundamental data structures:
1. **Queue (Coda)** - FIFO (First In, First Out) data structure using linked lists
2. **Graph (Grafi)** - Adjacency list representation of weighted graphs

## Data Structures

### Queue Implementation (`coda`)

#### Node Structure (`elem`)
```cpp
struct elem {
    tipo_inf inf;    // Data stored (int in this case)
    elem* pun;       // Pointer to next element
};
```

#### Queue Structure
```cpp
typedef struct {
    lista head;      // Pointer to first element
    elem* tail;      // Pointer to last element  
} coda;
```

### Graph Implementation (`graph`)

#### Adjacency Node Structure (`adj_node`)
```cpp
struct adj_node {
    int node;              // Adjacent node index
    float weight;          // Edge weight
    struct adj_node* next; // Next adjacent node
};
```

#### Graph Structure
```cpp
typedef struct {
    adj_list* nodes;  // Array of adjacency lists
    int dim;          // Number of nodes
} graph;
```

## Implemented Functions

### Queue Operations

1. **`coda newQueue()`**
   - Creates an empty queue
   - Initializes both head and tail to NULL
   - Returns the new empty queue

2. **`coda enqueue(coda c, tipo_inf i)`**
   - Adds element to the rear of the queue
   - Creates new element using `new_elem()`
   - Updates tail pointer and links elements
   - **Special case**: If queue is empty, both head and tail point to new element

3. **`tipo_inf dequeue(coda& c)`**
   - Removes and returns element from front of queue
   - Updates head pointer to next element
   - Frees memory of removed element
   - **Note**: Doesn't check for empty queue (should be verified with `isEmpty()`)

4. **`tipo_inf first(coda c)`**
   - Returns the front element without removing it
   - Peek operation for queue

5. **`bool isEmpty(coda c)`**
   - Checks if queue is empty
   - Returns true if head is NULL

6. **`static elem* new_elem(tipo_inf inf)`**
   - Helper function to create new queue elements
   - Allocates memory and initializes values

### Graph Operations

7. **`graph new_graph(int n)`**
   - Creates a new graph with n nodes
   - Allocates array of adjacency lists
   - Initializes all adjacency lists to NULL (empty)

8. **`void add_arc(graph& G, int u, int v, float w)`**
   - Adds directed edge from node u to node v with weight w
   - **Implementation**: Adds to head of adjacency list (most recent first)
   - **Note**: Nodes are 1-indexed in interface, 0-indexed internally

9. **`void add_edge(graph& g, int u, int v, float w)`**
   - Adds undirected edge between nodes u and v
   - **Implementation**: Calls `add_arc()` twice (u→v and v→u)

10. **`int get_dim(graph g)`**
    - Returns number of nodes in the graph

11. **`adj_list get_adjlist(graph g, int u)`**
    - Returns adjacency list for node u
    - Converts from 1-indexed to 0-indexed

12. **`int get_adjnode(adj_list l)`**
    - Returns the node index from adjacency list element
    - Converts from 0-indexed to 1-indexed

13. **`adj_list get_nextadj(adj_list l)`**
    - Returns next element in adjacency list
    - Used for traversing neighbors

## Key Algorithms and Concepts

### Queue (FIFO) Properties
- **Enqueue**: Add to rear (tail)
- **Dequeue**: Remove from front (head)
- **Time Complexity**: O(1) for all operations
- **Space Complexity**: O(n) where n is number of elements

### Queue Implementation Strategy
- **Two pointers**: Head for removal, tail for insertion
- **Linked list**: Dynamic size, efficient insertion/deletion
- **Edge cases**: Empty queue, single element queue

### Graph Representation (Adjacency Lists)
- **Space efficient**: Only store existing edges
- **Good for sparse graphs**: Space = O(V + E)
- **Edge iteration**: O(degree(v)) for node v

### Graph Implementation Details
- **1-indexed interface**: User-friendly node numbering (1 to n)
- **0-indexed internal**: Array-friendly storage (0 to n-1)
- **Head insertion**: New edges added to front of adjacency lists
- **Weighted edges**: Support for float weights

## General Concepts for Future Reference

### When to Use Queues
- **BFS (Breadth-First Search)**: Level-order traversal
- **Task scheduling**: Process requests in order
- **Buffering**: Handle data streams
- **Simulation**: Model waiting lines

### When to Use Adjacency Lists for Graphs
- **Sparse graphs**: Few edges relative to nodes
- **Need to iterate neighbors**: Common in graph algorithms
- **Dynamic graphs**: Frequent edge additions
- **Memory efficiency**: Important consideration

### Implementation Best Practices

#### Queue Design Patterns
1. Always check `isEmpty()` before `dequeue()`
2. Use both head and tail pointers for efficiency
3. Handle memory management properly
4. Consider circular arrays for fixed-size queues

#### Graph Design Patterns  
1. Consistent indexing (1-based interface, 0-based internal)
2. Separate directed/undirected edge functions
3. Accessor functions for data encapsulation
4. Consider edge weights in design

### Common Applications
- **Queue + BFS**: Shortest path in unweighted graphs
- **Graph traversal**: Explore connected components
- **Topological sorting**: Using DFS or BFS
- **Network analysis**: Social networks, web graphs

### Time Complexities
- **Queue operations**: O(1)
- **Graph creation**: O(V)
- **Add edge**: O(1)
- **Find edge**: O(degree(v))
- **Space**: Queue O(n), Graph O(V + E)

This lab demonstrates fundamental data structures essential for many algorithms, particularly graph algorithms that rely on both queues (for BFS) and efficient graph representation.
