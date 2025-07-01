# Lab 190627 - Graph with Points of Interest and Lists

## Overview
This lab combines graph data structures with doubly-linked lists to represent a city navigation system with points of interest (POI). The graph represents connections between locations, while lists can manage collections of POIs with different attributes (museums, palaces, towers, etc.).

## Data Structures

### Point of Interest Structure (`tipo_inf`)
```cpp
typedef struct {
    int id;           // Unique identifier for the location
    char nome[21];    // Name of the place (max 20 characters)
    char tipo;        // Type: 'e' (edificio), 'm' (museo), 'p' (piazza)
} tipo_inf;
```

### Graph Implementation (Adjacency Lists)

#### Adjacency Node (`adj_node`)
```cpp
struct adj_node {
    int node;              // Connected node ID
    float weight;          // Distance/weight of connection
    struct adj_node* next; // Next adjacent node
};
```

#### Graph Structure
```cpp
typedef struct {
    adj_list* nodes;  // Array of adjacency lists
    int dim;          // Number of nodes in graph
} graph;
```

### Doubly Linked List (for POI collections)

#### List Element (`elem`)
```cpp
struct elem {
    tipo_inf inf;    // Point of Interest data
    elem* pun;       // Next element pointer
    elem* prev;      // Previous element pointer
};
```

## Sample Data Analysis

### Points of Interest (PI.txt)
The file shows Bologna landmarks:
- **ID 1**: Palazzo Re Enzo (edificio - 'e')
- **ID 2**: Palazzo Fava (museo - 'm') 
- **ID 3**: Torre Asinelli (edificio - 'e')
- **ID 4**: Piazza S. Stefano (piazza - 'p')
- **ID 5**: Torre Garisenda (edificio - 'e')
- **ID 6**: Palazzo Pepoli (museo - 'm')
- **ID 7**: Museo Archeologico (museo - 'm')
- **ID 8**: Piazza Nettuno (piazza - 'p')

### Graph Connections (G.txt)
Represents walkable paths between locations:
- 1→2, 1→7, 1→5, 1→8 (Palazzo Re Enzo connects to multiple locations)
- 5→3 (Torre Garisenda to Torre Asinelli)
- 3→1 (Torre Asinelli back to Palazzo Re Enzo)
- 7→6 (Museo Archeologico to Palazzo Pepoli)
- 6→4 (Palazzo Pepoli to Piazza S. Stefano)
- 2→7 (Palazzo Fava to Museo Archeologico)

## Implemented Functions

### Graph Operations

1. **`graph new_graph(int n)`**
   - Creates graph with n nodes
   - Initializes all adjacency lists to NULL
   - Allocates array of adjacency list pointers

2. **`void add_arc(graph& G, int u, int v, float w)`**
   - Adds directed edge from u to v with weight w
   - Uses 1-indexed interface, 0-indexed internal storage
   - Inserts at head of adjacency list

3. **`void add_edge(graph& g, int u, int v, float w)`**
   - Adds undirected edge (bidirectional connection)
   - Calls `add_arc()` twice for both directions
   - **Use case**: Walkable streets between locations

4. **Graph Accessor Functions**:
   - `int get_dim(graph g)` - Returns number of nodes
   - `adj_list get_adjlist(graph g, int u)` - Gets adjacency list for node u
   - `int get_adjnode(adj_list l)` - Gets node ID from adjacency element
   - `adj_list get_nextadj(adj_list l)` - Gets next adjacent node

### POI List Operations

5. **`elem* new_elem(tipo_inf inf)`**
   - Creates new list element with POI data
   - Copies POI information (ID, name, type)

6. **List Management Functions**:
   - `lista insert_elem(lista l, elem* e)` - Insert POI at head
   - `lista delete_elem(lista l, elem* e)` - Remove specific POI
   - `lista ord_insert_elem(lista l, elem* e)` - Insert maintaining order

7. **POI Search Functions**:
   - `elem* search(lista l, tipo_inf v)` - Linear search for POI
   - `elem* ord_search(lista l, tipo_inf v)` - Search in ordered list

### POI Type Operations

8. **`int compare(tipo_inf p1, tipo_inf p2)`**
   - Compares two POIs for ordering
   - **Possible strategies**:
     - By ID (numerical order)
     - By name (alphabetical)
     - By type, then name
     - By type, then ID

9. **`void copy(tipo_inf& dest, tipo_inf source)`**
   - Copies POI data including ID, name, and type
   - Handles string copying for name field

10. **`void print(tipo_inf inf)`**
    - Prints POI in readable format
    - **Example**: "1: Palazzo Re Enzo (edificio)"

## Key Algorithms and Applications

### City Navigation System

#### Path Finding
```cpp
// Find all locations reachable from starting point
void explore_from(graph g, int start) {
    adj_list current = get_adjlist(g, start);
    while (current != NULL) {
        int destination = get_adjnode(current);
        // Process destination
        current = get_nextadj(current);
    }
}
```

#### POI Classification
```cpp
// Create separate lists by POI type
lista museums = NULL, palaces = NULL, squares = NULL;

void classify_poi(tipo_inf poi) {
    elem* new_poi = new_elem(poi);
    switch (poi.tipo) {
        case 'm': museums = insert_elem(museums, new_poi); break;
        case 'e': palaces = insert_elem(palaces, new_poi); break;
        case 'p': squares = insert_elem(squares, new_poi); break;
    }
}
```

### Tourist Route Planning

#### Find POIs by Type
```cpp
lista find_museums(lista all_poi) {
    lista museums = NULL;
    while (all_poi != NULL) {
        if (head(all_poi).tipo == 'm') {
            elem* museum = new_elem(head(all_poi));
            museums = insert_elem(museums, museum);
        }
        all_poi = tail(all_poi);
    }
    return museums;
}
```

#### Check Connectivity
```cpp
bool are_connected(graph g, int start, int end) {
    adj_list adj = get_adjlist(g, start);
    while (adj != NULL) {
        if (get_adjnode(adj) == end)
            return true;
        adj = get_nextadj(adj);
    }
    return false;
}
```

## Practical Applications

### Tourism and Navigation
- **Route planning**: Find paths between attractions
- **POI filtering**: Show only museums, or only squares
- **Distance calculation**: Use edge weights for walking times
- **Tour optimization**: Visit multiple POIs efficiently

### Urban Planning
- **Accessibility analysis**: Check connections between locations
- **Category distribution**: Analyze spatial distribution of POI types
- **Infrastructure planning**: Identify poorly connected areas

### Mobile Applications
- **Location-based services**: Find nearby attractions
- **Augmented reality**: Display information about visible POIs
- **Social features**: Share visited locations, create custom tours

## General Concepts for Future Reference

### Combining Data Structures
- **Graph + Lists**: Nodes with rich attribute data
- **Spatial + Categorical**: Geographic connections with typed content
- **Static structure + Dynamic collections**: Fixed graph with changing POI lists

### POI Data Management

#### Comparison Strategies
1. **ID-based**: Simple numerical ordering
2. **Name-based**: Alphabetical for user browsing
3. **Type-then-name**: Group by category, sort within category
4. **Geographic**: By location (requires coordinate data)

#### Search Optimization
- **By type**: Pre-filter before searching
- **By name**: Use ordered lists with `ord_search()`
- **By ID**: Direct access if using arrays
- **Fuzzy search**: Partial name matching

### Real-World Extensions

#### Enhanced POI Structure
```cpp
typedef struct {
    int id;
    char nome[50];
    char tipo;
    float latitude, longitude;  // GPS coordinates
    int rating;                 // User rating 1-5
    char description[200];      // Detailed description
    bool wheelchair_accessible; // Accessibility info
} enhanced_poi;
```

#### Weighted Graph Applications
- **Walking time**: Edge weights as minutes
- **Difficulty**: Terrain difficulty for routing
- **Popularity**: Crowding factor for route planning
- **Accessibility**: Wheelchair-friendly paths

### Performance Considerations

#### Memory Usage
- **POI data**: Fixed size per POI (ID + name + type)
- **Graph storage**: O(V + E) for adjacency lists
- **List overhead**: Additional pointers per element

#### Time Complexities
- **Add POI to list**: O(1) at head, O(n) ordered
- **Find POI**: O(n) linear search
- **Graph traversal**: O(V + E) for full exploration
- **Check connection**: O(degree(v)) for specific node

This lab demonstrates the integration of graph algorithms with structured data management, providing a foundation for developing location-based applications and geographic information systems.
