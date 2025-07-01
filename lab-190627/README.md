# Lab 190627: City Points of Interest Navigation System

## Overview

This project implements a navigation system for city points of interest (POI), combining graph data structures with ordered linked lists. The system reads POI information and their connections from files, manages them efficiently, and provides various analysis and search functionalities.

The program loads POI data (palaces, museums, squares) and their walking connections into a graph structure, enabling complex queries like homogeneous path finding and type-based filtering.

## Data Model

The navigation system is built upon an undirected graph with POI nodes and three main types of analysis functionalities.

### Node Types (`tipo.h`)

Points of interest are stored with both location and graph connectivity information.

-   **ID**: Unique identifier (1-8) for each POI
-   **Name**: Location name (up to 20 characters, e.g., "Palazzo Re Enzo")  
-   **Type**: Category character ('e' for edificio, 'm' for museo, 'p' for piazza)

```cpp
typedef struct {
    int id;           // Unique identifier (1-8)
    char nome[21];    // Name of the place (max 20 characters)
    char tipo;        // Type: 'e' (edificio), 'm' (museo), 'p' (piazza)
} tipo_inf;
```

### Connection Types (Graph Edges)

Edges in the undirected graph represent walkable connections between POIs:

-   **Bidirectional paths**: All connections work both ways
-   **Unweighted**: All connections have equal traversal cost
-   **Physical proximity**: Connections represent actual walkable routes

## Input Files

The program loads its data from two plain text files:

-   **`PI.txt`**: Defines POI information.
    -   Format: ID, name, type (3 lines per POI)
    -   Example: `1`, `Palazzo Re Enzo`, `e`

-   **`G.txt`**: Defines the graph's connection structure.
    -   Format: Each line contains two integers representing a bidirectional connection
    -   Example: `1 2` (Palazzo Re Enzo ↔ Palazzo Fava)

## Implemented Features

The `compito.cc` file contains the main logic divided into four main points as specified in the laboratory assignment.

### 1. Core POI Management (Punto 1)
- **`int carica(lista& pi)`**: Loads all POIs from `PI.txt` into an ordered linked list, returns count
- **`tipo_inf search_pi(lista pi, int id)`**: Efficient search for POI by ID using ordered list structure
- **Interactive search**: Main program allows repeated POI searches by ID

### 2.a. Graph Operations and Map Display (Punto 2.a)
- **`graph mappa(int n)`**: Creates undirected graph from `G.txt` with n nodes
- **`void stampa_mappa(graph g, lista pi)`**: Displays comprehensive map showing each POI and all its connections

### 3.a. Homogeneous Path Analysis (Punto 3.a)
- **`void trip(graph g, int node_id, lista pi)`**: Finds all POIs reachable via same-type paths
- **Type-restricted traversal**: Only follows paths through POIs of the same type (museums→museums, etc.)
- **Depth-First Search**: Uses recursive DFS with cycle detection for complete exploration

### 2.b. POI Type Filtering (Punto 2.b)
- **`lista genera(lista pi, char tipo)`**: Creates new ordered list containing only POIs of specified type
- **Maintains ordering**: Result list preserves ID-based ordering of original list

## Core Data Structures

The implementation relies on two fundamental data structures:

-   **Graph (`grafo`)**: Undirected graph using **adjacency lists**, efficient for sparse connections and neighbor traversal
-   **Ordered List (`liste`)**: **Doubly-linked list** maintaining POI data sorted by ID for efficient searching

## How to Compile and Run

A `Makefile` is provided for easy compilation.

1.  **Compile the project**:
    ```sh
    make
    ```
2.  **Run the executable**:
    ```sh
    ./compito
    ```

The program runs interactively, allowing testing of each implemented point through user input.

### Expected Output

Running the program with the provided data files (`PI.txt`, `G.txt`) produces the following results:

**Punto 1 Tests:**
- ID 1: `Palazzo Re Enzo e`
- ID 4: `Piazza S. Stefano p`

**Punto 2.a Map Display:**
```
Palazzo Re Enzo connesso a: Piazza Nettuno, Torre Asinelli, Torre Garisenda, Museo Archeologico, Palazzo Fava
Palazzo Fava connesso a: Museo Archeologico, Palazzo Re Enzo
Torre Asinelli connesso a: Palazzo Re Enzo, Torre Garisenda
Piazza S. Stefano connesso a: Palazzo Pepoli
Torre Garisenda connesso a: Torre Asinelli, Palazzo Re Enzo
Palazzo Pepoli connesso a: Piazza S. Stefano, Museo Archeologico
Museo Archeologico connesso a: Palazzo Fava, Palazzo Pepoli, Palazzo Re Enzo
Piazza Nettuno connesso a: Palazzo Re Enzo
```

**Punto 3.a Homogeneous Path Results:**
- From ID 1 (edificio): `5 3` (Torre Garisenda → Torre Asinelli)
- From ID 6 (museo): `7 2` (Museo Archeologico → Palazzo Fava)

**Punto 2.b Type Filtering (museums):**
```
Palazzo Fava m
Palazzo Pepoli m
Museo Archeologico m
```

## Technical Implementation

### File Loading Strategy
- **POI loading**: Line-by-line parsing with proper string handling for names containing spaces
- **Graph loading**: Simple integer pair reading for connection definitions
- **Error handling**: Robust file existence checking with informative error messages

### Algorithm Efficiency
- **Ordered insertion**: O(n) for maintaining sorted POI list
- **POI search**: O(log n) average case due to ordered list structure
- **Graph traversal**: O(V + E) for complete DFS exploration with type filtering
- **Memory management**: Dynamic allocation with proper cleanup

### Data Structure Integration
- **Graph-List correspondence**: Graph node IDs directly match POI IDs (1-indexed)
- **Type-based filtering**: Efficient traversal restricted by POI type during search
- **Bidirectional connections**: Undirected graph implementation using adjacency lists

This implementation successfully demonstrates advanced data structure integration for location-based navigation systems, providing efficient POI management and sophisticated path analysis capabilities.
