# Lab prova_grafi_250305 - Bipartite Graph Product Rating System

## Overview
This lab implements a **bipartite graph system** for managing and analyzing user ratings of products online. The system models users and products as nodes in a graph, with weighted edges representing ratings (1-5 stars) from users to products. This implementation demonstrates practical applications of graph data structures in recommendation systems and data mining.

## Data Structures

### Node Information Structure (`tipo_inf`)
```cpp
typedef struct {
    char descrizione[20];  // Node description (user account or product name)
    char tipo;            // Node type: 'U' for User, 'P' for Product
} tipo_inf;
```

### Graph Structure
- **Bipartite Graph**: Nodes are either users ('U') or products ('P')
- **Directed Edges**: From users to products only
- **Weighted Edges**: Edge weights represent star ratings (1-5)
- **Adjacency List Representation**: Efficient storage for sparse graphs

### Graph Node Structure (`adj_node`)
```cpp
struct adj_node {
    int node;              // Target node index
    float weight;          // Rating (1-5 stars)
    struct adj_node* next; // Next node in adjacency list
};
```

## Sample Data Analysis

### From `nodi.txt` (7 nodes):
- **Users**: Paolo (1), Giovanna (3), Carla (4), Pino (5)
- **Products**: Ciabatta (2), Scatola (6), Gioco (7)

### From `valutazioni.txt` (Rating Graph):
- **Paolo**: Ciabatta (5★), Gioco (2★) → Average: 3.5
- **Giovanna**: Gioco (3★), Scatola (4★) → Average: 3.5
- **Carla**: Scatola (5★) → Average: 5.0
- **Pino**: Gioco (3★) → Average: 3.0

### Product Ratings:
- **Ciabatta**: 5★ (Paolo) → Average: 5.0
- **Scatola**: 4★ (Giovanna), 5★ (Carla) → Average: 4.5
- **Gioco**: 2★ (Paolo), 3★ (Giovanna), 3★ (Pino) → Average: 2.67

## Implemented Functions

### Core Data Management

1. **`tipo_inf* creaNodi(int& n)`**
   - Loads node information from `nodi.txt`
   - Creates dynamic array of user and product nodes
   - **Input file format**: Number of nodes, then pairs of (description, type)
   - **Returns**: Array of nodes and count via reference

2. **`void stampa(graph g, tipo_inf* nodes, int dim)`**
   - Prints all user ratings in format: "User valuta Rating Product"
   - Traverses adjacency lists for all user nodes
   - **Use case**: Overview of all ratings in the system

### Analytics Functions

3. **`float media_utente(char* account, graph g, tipo_inf* nodes, int dim)`**
   - Calculates average rating given by a specific user
   - **Algorithm**: Sum all ratings by user / number of products rated
   - **Example**: Paolo rated Ciabatta (5★) and Gioco (2★) → Average: 3.5

4. **`float media_prod(char* prod, graph g, tipo_inf* nodes, int dim)`**
   - Calculates average rating received by a specific product
   - **Algorithm**: Sum all ratings for product / number of users who rated it
   - **Example**: Scatola rated by Giovanna (4★) and Carla (5★) → Average: 4.5

### Recommendation System

5. **`void suggerisci(char* account, char* prod, graph g, tipo_inf* nodes, int dim)`**
   - Recommends products based on collaborative filtering
   - **Algorithm**:
     - Find users who rated the same product with the same rating
     - Suggest products these users rated with ≥3 stars
     - Exclude products already rated by the target user
   - **Example**: Pino and Giovanna both rated Gioco with 3★, so suggest Scatola (4★) to Pino

## Key Algorithms and Concepts

### Bipartite Graph Properties

#### Graph Structure Validation
```cpp
// In a bipartite graph, edges only exist between different node types
bool is_valid_bipartite(graph g, tipo_inf* nodes, int dim) {
    for (int i = 0; i < dim; i++) {
        if (nodes[i].tipo == 'U') {  // User nodes
            adj_list current = get_adjlist(g, i + 1);
            while (current != NULL) {
                int target = get_adjnode(current) - 1;
                if (nodes[target].tipo != 'P') return false; // Must connect to product
                current = get_nextadj(current);
            }
        }
    }
    return true;
}
```

#### Rating Distribution Analysis
```cpp
void analyze_rating_distribution(graph g, tipo_inf* nodes, int dim) {
    int rating_counts[6] = {0}; // Index 0 unused, 1-5 for star ratings
    
    for (int i = 0; i < dim; i++) {
        if (nodes[i].tipo == 'U') {
            adj_list current = get_adjlist(g, i + 1);
            while (current != NULL) {
                int rating = (int)get_adjweight(current);
                rating_counts[rating]++;
                current = get_nextadj(current);
            }
        }
    }
    
    for (int i = 1; i <= 5; i++) {
        cout << i << " stars: " << rating_counts[i] << " ratings" << endl;
    }
}
```

### Collaborative Filtering Implementation

#### Find Similar Users
```cpp
vector<int> find_similar_users(int user_id, graph g, tipo_inf* nodes, int dim) {
    vector<int> similar_users;
    adj_list user_ratings = get_adjlist(g, user_id);
    
    // For each other user, calculate similarity
    for (int i = 0; i < dim; i++) {
        if (nodes[i].tipo == 'U' && i + 1 != user_id) {
            int common_products = 0;
            int similar_ratings = 0;
            
            // Compare ratings with current user
            adj_list other_ratings = get_adjlist(g, i + 1);
            // Implementation of similarity calculation...
            
            if (similarity_score > threshold) {
                similar_users.push_back(i + 1);
            }
        }
    }
    return similar_users;
}
```

#### Product Recommendation Score
```cpp
float calculate_recommendation_score(int user_id, int product_id, 
                                   graph g, tipo_inf* nodes, int dim) {
    float score = 0;
    int count = 0;
    
    // Find users who rated this product
    for (int i = 0; i < dim; i++) {
        if (nodes[i].tipo == 'U' && i + 1 != user_id) {
            adj_list ratings = get_adjlist(g, i + 1);
            while (ratings != NULL) {
                if (get_adjnode(ratings) == product_id) {
                    // Weight by user similarity
                    float similarity = calculate_user_similarity(user_id, i + 1);
                    score += get_adjweight(ratings) * similarity;
                    count++;
                    break;
                }
                ratings = get_nextadj(ratings);
            }
        }
    }
    
    return (count > 0) ? score / count : 0;
}
```

## Practical Applications

### E-commerce Recommendation Systems

#### Amazon-style "Customers who bought this also bought"
```cpp
void customers_also_bought(char* product, graph g, tipo_inf* nodes, int dim) {
    int product_idx = find_product_index(product, nodes, dim);
    if (product_idx == -1) return;
    
    map<int, int> co_purchased;
    
    // Find users who rated this product
    for (int i = 0; i < dim; i++) {
        if (nodes[i].tipo == 'U') {
            bool rated_target = false;
            adj_list ratings = get_adjlist(g, i + 1);
            
            // Check if user rated target product
            while (ratings != NULL) {
                if (get_adjnode(ratings) == product_idx) {
                    rated_target = true;
                    break;
                }
                ratings = get_nextadj(ratings);
            }
            
            // If yes, count all other products they rated
            if (rated_target) {
                ratings = get_adjlist(g, i + 1);
                while (ratings != NULL) {
                    int other_product = get_adjnode(ratings);
                    if (other_product != product_idx) {
                        co_purchased[other_product]++;
                    }
                    ratings = get_nextadj(ratings);
                }
            }
        }
    }
    
    // Print most co-purchased items
    for (const auto& pair : co_purchased) {
        cout << "Also bought: " << nodes[pair.first - 1].descrizione 
             << " (" << pair.second << " times)" << endl;
    }
}
```

### Social Network Analysis

#### User Influence Scoring
```cpp
float calculate_user_influence(int user_id, graph g, tipo_inf* nodes, int dim) {
    adj_list ratings = get_adjlist(g, user_id);
    float total_ratings = 0;
    int product_count = 0;
    
    while (ratings != NULL) {
        total_ratings += get_adjweight(ratings);
        product_count++;
        ratings = get_nextadj(ratings);
    }
    
    // Influence = number of products rated * average rating
    return product_count * (total_ratings / product_count);
}
```

#### Product Popularity Analysis
```cpp
struct ProductStats {
    string name;
    int rating_count;
    float average_rating;
    float popularity_score;
};

vector<ProductStats> analyze_product_popularity(graph g, tipo_inf* nodes, int dim) {
    vector<ProductStats> stats;
    
    for (int i = 0; i < dim; i++) {
        if (nodes[i].tipo == 'P') {
            ProductStats ps;
            ps.name = nodes[i].descrizione;
            ps.rating_count = 0;
            float total_rating = 0;
            
            // Count ratings for this product
            for (int j = 0; j < dim; j++) {
                if (nodes[j].tipo == 'U') {
                    adj_list ratings = get_adjlist(g, j + 1);
                    while (ratings != NULL) {
                        if (get_adjnode(ratings) == i + 1) {
                            total_rating += get_adjweight(ratings);
                            ps.rating_count++;
                            break;
                        }
                        ratings = get_nextadj(ratings);
                    }
                }
            }
            
            ps.average_rating = (ps.rating_count > 0) ? total_rating / ps.rating_count : 0;
            ps.popularity_score = ps.rating_count * ps.average_rating;
            stats.push_back(ps);
        }
    }
    
    return stats;
}
```

### Data Mining Applications

#### Rating Pattern Analysis
```cpp
void analyze_rating_patterns(graph g, tipo_inf* nodes, int dim) {
    cout << "=== Rating Pattern Analysis ===" << endl;
    
    // User rating behavior
    int user_types[4] = {0}; // harsh, average, generous, minimal
    
    for (int i = 0; i < dim; i++) {
        if (nodes[i].tipo == 'U') {
            float avg = media_utente(nodes[i].descrizione, g, nodes, dim);
            if (avg < 2.5) user_types[0]++; // harsh
            else if (avg < 3.5) user_types[1]++; // average
            else if (avg < 4.5) user_types[2]++; // generous
            else user_types[3]++; // very generous
        }
    }
    
    cout << "Harsh critics: " << user_types[0] << endl;
    cout << "Average raters: " << user_types[1] << endl;
    cout << "Generous raters: " << user_types[2] << endl;
    cout << "Very generous: " << user_types[3] << endl;
}
```

## Build and Execution

### Compilation
```bash
make          # Compile the project
make clean    # Clean build files
make doc      # Generate documentation
```

### Program Execution
```bash
./main
```

### Expected Output
```
=== Stampa valutazioni per utente ===
Paolo valuta 2 Gioco
Paolo valuta 5 Ciabatta
Giovanna valuta 4 Scatola
Giovanna valuta 3 Gioco
Carla valuta 5 Scatola
Pino valuta 3 Gioco

Inserisci account per calcolare media utente: Paolo
3.5

Inserisci account per suggerimenti: Pino
Inserisci prodotto valutato: Gioco
Suggerimento: Scatola

Inserisci prodotto per calcolare media: Scatola
4.5
```

## File Structure
```
prova_grafi_250305/
├── compito.cc         # Main implementation
├── grafo.cc          # Graph data structure implementation
├── grafo.h           # Graph header file
├── tipo.cc           # Node type implementation
├── tipo.h            # Node type header
├── Makefile          # Build configuration
├── Doxyfile          # Documentation configuration
├── nodi.txt          # Node data file
├── valutazioni.txt   # Rating data file
└── README.md         # This documentation
```

## Advanced Concepts for Future Extensions

### Performance Optimizations

#### Indexed Access
```cpp
class BipartiteGraph {
private:
    unordered_map<string, int> user_index;
    unordered_map<string, int> product_index;
    
public:
    void build_indices(tipo_inf* nodes, int dim) {
        for (int i = 0; i < dim; i++) {
            if (nodes[i].tipo == 'U') {
                user_index[nodes[i].descrizione] = i + 1;
            } else {
                product_index[nodes[i].descrizione] = i + 1;
            }
        }
    }
    
    int find_user_fast(const string& name) {
        return user_index.count(name) ? user_index[name] : -1;
    }
};
```

#### Caching System
```cpp
class RatingCache {
private:
    unordered_map<string, float> user_averages;
    unordered_map<string, float> product_averages;
    
public:
    float get_user_average(const string& user, bool use_cache = true) {
        if (use_cache && user_averages.count(user)) {
            return user_averages[user];
        }
        
        float avg = calculate_user_average(user);
        user_averages[user] = avg;
        return avg;
    }
};
```

### Machine Learning Integration

#### Rating Prediction
```cpp
float predict_rating(int user_id, int product_id, graph g, tipo_inf* nodes, int dim) {
    // Collaborative filtering prediction
    vector<int> similar_users = find_similar_users(user_id, g, nodes, dim);
    
    float weighted_sum = 0;
    float weight_sum = 0;
    
    for (int similar_user : similar_users) {
        float similarity = calculate_similarity(user_id, similar_user);
        float rating = get_user_rating_for_product(similar_user, product_id);
        
        if (rating > 0) {
            weighted_sum += similarity * rating;
            weight_sum += similarity;
        }
    }
    
    return (weight_sum > 0) ? weighted_sum / weight_sum : 0;
}
```

### Scalability Considerations

#### Memory Management
- **Large Datasets**: Consider using sparse matrix representations
- **Streaming Data**: Implement incremental graph updates
- **Distributed Systems**: Partition graph by user or product clusters

#### Time Complexity Analysis
- **User Average**: O(degree(user)) = O(products_rated_by_user)
- **Product Average**: O(V) where V is number of users
- **Recommendations**: O(V²) in worst case for similarity calculations
- **Graph Traversal**: O(V + E) for complete analysis

This lab demonstrates fundamental concepts in graph-based recommendation systems, providing a foundation for understanding more complex algorithms used in modern e-commerce and social media platforms.

## Conceptual Connections to Other Labs

### Related Data Structures
- **Lab 190627**: Geographic POI graphs - similar graph traversal concepts
- **Lab 180719**: Social network graphs - user relationship modeling
- **Lab 240703**: BST hotel ratings - single-criterion rating systems

### Algorithmic Patterns
- **Graph Traversal**: Similar to social network analysis in Lab 180719
- **Rating Aggregation**: Related to BST range queries in Lab 240703
- **Recommendation Logic**: Collaborative filtering principles

### Real-World Applications Bridge
- **E-commerce**: Product recommendation engines
- **Social Media**: Content and friend recommendations
- **Entertainment**: Movie, music, and content suggestions
- **Business Intelligence**: Customer behavior analysis

This bipartite graph implementation provides practical experience with recommendation systems that power modern digital platforms, making abstract graph theory concepts concrete and immediately applicable to real-world software development.
