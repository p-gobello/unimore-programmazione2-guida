# Programming 2 Laboratory - Complete Analysis and Reference Guide

## Overview
This repository contains comprehensive analyses of 8 programming laboratory exercises focused on fundamental data structures and algorithms. Each lab demonstrates practical applications of core computer science concepts through real-world scenarios.

## Repository Structure
```
prove-lab-claude/
├── lab-180618/     # Binary Search Tree (BST) with Cards
├── lab-180719/     # Queue and Graph Implementation
├── lab-180911/     # Doubly Linked Lists with Inverted Index
├── lab-190205/     # Card Management with Doubly Linked Lists
├── lab-190627/     # Graph with Points of Interest + Lists
├── lab-210917/     # Calendar/Agenda Management
├── lab-220721/     # Multi-Player Card Game System
├── lab-240703/     # Hotel Management with BST
└── README.md       # This overview file
```

## Lab Summaries

### Lab 180618 - Binary Search Tree Fundamentals
**Core Focus**: BST implementation with playing cards

**Key Data Structures**:
- Binary Search Tree with parent pointers
- Card structure (suit + value)

**Essential Functions**:
- `bst_insert()` - Maintains BST property during insertion
- `bst_search()` - Efficient O(log n) search operations
- `bst_delete()` - Complex deletion with three cases (leaf, one child, two children)

**Learning Objectives**:
- Tree traversal algorithms
- BST property maintenance
- Pointer manipulation in tree structures
- Memory management with dynamic allocation

### Lab 180719 - Queue and Graph Fundamentals
**Core Focus**: FIFO queue implementation + graph adjacency lists

**Key Data Structures**:
- Queue with head/tail pointers for O(1) operations
- Graph using adjacency lists for space efficiency
- Weighted edges for realistic graph applications

**Essential Functions**:
- `enqueue()`/`dequeue()` - FIFO queue operations
- `add_arc()`/`add_edge()` - Graph construction
- Graph traversal accessors

**Learning Objectives**:
- Queue applications (BFS, task scheduling)
- Graph representation strategies
- Space-efficient adjacency lists vs. matrices
- Weighted graph concepts

### Lab 180911 - Advanced Linked Lists and Information Retrieval
**Core Focus**: Doubly linked lists with document indexing

**Key Data Structures**:
- Doubly linked lists with prev/next pointers
- Word structure for inverted index
- Document-word mapping system

**Essential Functions**:
- `ord_insert_elem()` - Maintains sorted order
- `ord_search()` - Optimized search with early termination
- Bidirectional list traversal

**Learning Objectives**:
- Information retrieval concepts
- Inverted index data structures
- Ordered vs. unordered data management
- Search optimization techniques

### Lab 190205 - Specialized Card Game Implementation
**Core Focus**: Playing card management with type-safe operations

**Key Data Structures**:
- Card structure with suit and value
- Doubly linked lists for hand management

**Essential Functions**:
- Card comparison strategies (by suit, by value)
- Card validation and duplicate detection
- Hand organization algorithms

**Learning Objectives**:
- Domain-specific data modeling
- Type safety in data structures
- Game rule implementation
- Data validation strategies

### Lab 190627 - Geographic Information Systems
**Core Focus**: City navigation with points of interest

**Key Data Structures**:
- Enhanced graph with weighted edges
- Point of Interest (POI) structure with metadata
- Combined graph + list data management

**Essential Functions**:
- POI categorization and filtering
- Path finding between locations
- Geographic data management

**Learning Objectives**:
- Real-world graph applications
- Multi-attribute data structures
- Spatial data management
- Location-based services concepts

### Lab 210917 - Temporal Data Management
**Core Focus**: Calendar/agenda system with time-based operations

**Key Data Structures**:
- Appointment structure (date, start time, end time, description)
- Chronologically ordered lists

**Essential Functions**:
- Time conflict detection
- Chronological insertion
- Temporal data validation

**Learning Objectives**:
- Time-based data structures
- Conflict detection algorithms
- Scheduling system design
- Temporal data validation

### Lab 220721 - Multi-Player Game Systems
**Core Focus**: Managing multiple card hands with game state

**Key Data Structures**:
- Multiple independent card lists
- Game state management
- Player hand validation

**Essential Functions**:
- Multi-hand card distribution
- Duplicate detection across collections
- Game state synchronization

**Learning Objectives**:
- Multi-collection data management
- Game state design patterns
- Data integrity across collections
- Comparative data analysis

### Lab 240703 - Advanced BST Applications
**Core Focus**: Hotel management system with rating-based search

**Key Data Structures**:
- BST with reverse ordering (higher ratings left)
- Hotel information with multiple attributes

**Essential Functions**:
- Rating-based tree organization
- Range queries for hotel search
- Quality-based filtering

**Learning Objectives**:
- Custom BST ordering strategies
- Multi-criteria data in single-key structures
- Business application design
- Search optimization for specific domains

## Core Computer Science Concepts Covered

### Data Structures Mastery

#### 1. **Linear Data Structures**
- **Linked Lists**: Single, doubly-linked with various applications
- **Queues**: FIFO implementation with efficient operations
- **Applications**: Task scheduling, BFS, buffer management

#### 2. **Tree Data Structures**
- **Binary Search Trees**: Self-organizing, searchable trees
- **Tree Traversals**: In-order, pre-order, post-order
- **Applications**: Databases, file systems, expression parsing

#### 3. **Graph Data Structures**
- **Adjacency Lists**: Space-efficient graph representation
- **Weighted Graphs**: Real-world applications with edge costs
- **Applications**: Navigation, social networks, optimization

### Algorithm Design Patterns

#### 1. **Search Algorithms**
- **Linear Search**: O(n) baseline for unsorted data
- **Binary Search**: O(log n) for sorted/tree structures
- **Early Termination**: Optimization for ordered data

#### 2. **Insertion Algorithms**
- **Head Insertion**: O(1) for lists and queues
- **Ordered Insertion**: O(n) maintaining sorted property
- **Tree Insertion**: O(log n) average for balanced trees

#### 3. **Deletion Algorithms**
- **Simple Deletion**: O(1) with direct pointer access
- **Tree Deletion**: Complex case handling (leaf, one child, two children)
- **Integrity Maintenance**: Preserving data structure properties

### Programming Techniques

#### 1. **Memory Management**
- Dynamic allocation with `new`/`delete`
- Pointer manipulation and validation
- Memory leak prevention

#### 2. **Modular Programming**
- Header/implementation file separation
- Generic type systems (`tipo_inf`)
- Interface design for reusability

#### 3. **Error Handling**
- Input validation
- Edge case management
- Graceful failure handling

## Real-World Applications

### 1. **Database Systems**
- **BSTs**: Index structures for fast lookups
- **B+ Trees**: Disk-based tree structures
- **Hash Tables**: Constant-time access patterns

### 2. **Operating Systems**
- **Queues**: Process scheduling, I/O buffers
- **Trees**: File system organization
- **Graphs**: Resource allocation, deadlock detection

### 3. **Web Applications**
- **Graphs**: Social networks, recommendation systems
- **Trees**: DOM structures, decision trees
- **Lists**: Dynamic content management

### 4. **Game Development**
- **Lists**: Inventory management, player stats
- **Trees**: Game state trees, AI decision making
- **Graphs**: Level design, pathfinding algorithms

### 5. **Geographic Information Systems**
- **Graphs**: Road networks, route planning
- **Trees**: Spatial indexing (QuadTrees, R-Trees)
- **Lists**: POI management, location services

## Study Guide for Exam Preparation

### Essential Algorithms to Master

#### 1. **Tree Operations**
```cpp
// BST Search Pattern
while (node != NULL) {
    if (target == node->key) return node;
    node = (target < node->key) ? node->left : node->right;
}
```

#### 2. **List Manipulation**
```cpp
// Doubly-linked insertion pattern
new_node->next = current->next;
if (current->next != NULL) current->next->prev = new_node;
current->next = new_node;
new_node->prev = current;
```

#### 3. **Queue Operations**
```cpp
// Efficient enqueue/dequeue
enqueue: tail->next = new_node; tail = new_node;
dequeue: temp = head; head = head->next; delete temp;
```

### Problem-Solving Strategies

#### 1. **Data Structure Selection**
- **Need fast search?** → Use BST or hash table
- **Need ordering?** → Use ordered lists or BST
- **Need FIFO/LIFO?** → Use queue/stack
- **Need relationships?** → Use graphs

#### 2. **Algorithm Optimization**
- **Early termination** in search algorithms
- **Amortized analysis** for frequent operations
- **Space-time tradeoffs** based on requirements

#### 3. **Common Pitfalls**
- **Pointer management**: Always update bidirectional links
- **Memory leaks**: Match every `new` with `delete`
- **Edge cases**: Empty structures, single elements
- **Data integrity**: Maintain invariants during operations

### Practice Problems

#### 1. **Implementation Challenges**
- Implement BST with iterative (not recursive) operations
- Create a queue using two stacks
- Design a graph with both adjacency list and matrix representations

#### 2. **Application Design**
- Design a file system using trees
- Implement a simple scheduling system with priorities
- Create a social network graph with friendship relationships

#### 3. **Algorithm Analysis**
- Compare time/space complexity of different implementations
- Analyze worst-case vs. average-case performance
- Design test cases for edge conditions

## Advanced Topics for Further Study

### 1. **Self-Balancing Trees**
- AVL Trees (height-balanced)
- Red-Black Trees (color-balanced)
- B-Trees (disk-optimized)

### 2. **Advanced Graph Algorithms**
- Dijkstra's shortest path
- Minimum spanning trees (Prim's, Kruskal's)
- Topological sorting

### 3. **Hash-Based Structures**
- Hash tables with collision resolution
- Bloom filters for membership testing
- Consistent hashing for distributed systems

### 4. **Concurrent Data Structures**
- Thread-safe implementations
- Lock-free data structures
- Parallel algorithms

## Conclusion

This laboratory series provides a comprehensive foundation in data structures and algorithms through practical, real-world applications. The progression from basic linked lists to complex multi-structure systems demonstrates the evolution of problem-solving skills essential for software development.

Each lab builds upon previous concepts while introducing new challenges, creating a scaffolded learning experience that prepares students for advanced computer science topics and professional software development.

The emphasis on practical applications—from card games to hotel management systems—illustrates how fundamental data structures solve real-world problems, making abstract concepts concrete and memorable for long-term retention and application.
