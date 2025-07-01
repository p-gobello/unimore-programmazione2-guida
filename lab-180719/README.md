# Lab 180719: Social Network Analysis

## Overview

This project implements a system to analyze a simple social network, modeled after Twitter. The network is represented as a directed, unweighted graph where nodes can be either **users** or **tweets**, and edges represent relationships like **follows**, **likes**, and **ownership**.

The program reads the network structure and node information from files, performs analysis to identify key users, and determines relationship paths within the network.

## Data Model

The social network is built upon a directed graph with two types of nodes and three types of relationships.

### Node Types (`node.h`)

Nodes are stored in an array of `node` structs, where each node has a content string and a type character.

-   **User (`U`)**: Represents a user, identified by a nickname.
-   **Tweet (`T`)**: Represents a tweet, identified by its text content (up to 80 characters).

```cpp
struct node {
    char cont[81]; // Nickname or tweet text
    char tipo;     // 'U' for User, 'T' for Tweet
};
```

### Relationship Types (Edges)

Edges in the graph define the interactions between nodes:

-   **`FOLLOW` (User → User)**: A user follows another user.
-   **`LIKE` (User → Tweet)**: A user likes a tweet.
-   **`OWNER` (Tweet → User)**: A tweet is owned by a user.

## Input Files

The program loads its data from two plain text files:

-   **`graph`**: Defines the graph's structure.
    -   The first line contains the total number of nodes.
    -   Subsequent lines each contain a pair of integers representing a directed edge from a source node to a destination node.

-   **`node`**: Defines the content and type of each node.
    -   The file consists of pairs of lines. For each node, the first line is its content (e.g., "fede") and the second is its type (`U` or `T`).

## Implemented Features

The `compito.cc` file contains the main logic for the analysis, which is divided into three main parts.

### 1. Graph and Node Loading
- The program first loads the directed graph from the `graph` file.
- It then loads the node-specific data (content and type) from the `node` file into an array of `node` structs.

### 2. Verbose Graph Printing (`stampa`)
- After loading, the program prints a "verbose" representation of all relationships in the graph. Instead of printing node IDs, it shows the node content and the type of relationship.
- **Example Output**: `ale FOLLOW fede`

### 3. Network Analysis

#### 3.a. Most Influential People (`totalLike`)
- This feature identifies the "most influential" users.
- An influential user is defined as a user whose tweets have received the maximum number of likes across the entire network.
- The program calculates the total likes for each user's tweets and prints the nicknames of the user(s) with the highest count.

#### 3.b. Follower Traversal (`follow`)
- This feature, given a starting user, finds all other users that they follow, both directly and indirectly.
- It performs a **Breadth-First Search (BFS)** starting from the specified user to traverse the `FOLLOW` relationships.
- The program prompts the user to enter a user ID and then prints a list of all reachable users.

## Core Data Structures

The implementation relies on two fundamental data structures provided in `coda` and `grafi`:

-   **Graph (`grafi`)**: A graph represented using an **adjacency list**, which is efficient for sparse graphs and traversing neighbors.
-   **Queue (`coda`)**: A **FIFO (First-In, First-Out) queue** implemented with a linked list. It is essential for the BFS traversal in the `follow` function.

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
The program will run the non-interactive parts and then prompt for a user ID for the "Follow" analysis.

### Expected Output

Running the program with the provided data files (`graph`, `node`) and entering `8` at the prompt will produce the following output:

```
--- Punto 1 & 2: Stampa grafo con archi in formato verbose ---
fede LIKE Amo la Ferrari
fede LIKE Mi piace il cioccolato
Mi piace il cioccolato OWNER ale
Oggi piscina OWNER fede
Voglia di vacanze OWNER fede
ale FOLLOW ricky
ale FOLLOW fede
ale LIKE Oggi piscina
ale LIKE Amo la Ferrari
ricky FOLLOW fede
ricky LIKE Voglia di vacanze
Amo la Ferrari OWNER ricky
wilma FOLLOW ale

--- Punto 3.a: Most Influential People ---
fede
ricky

--- Punto 3.b: Follow ---
Inserire l'identificativo di un nodo utente: L'utente wilma segue:
ale
ricky
fede
```
