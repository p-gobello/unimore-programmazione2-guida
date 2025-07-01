# Lab 210917: Agenda Management System

## Overview

This project implements a complete agenda management system using a **doubly-linked list** to handle time-based appointments. The system reads appointment data from a file, performs ordered insertion, prevents scheduling conflicts, and provides functionalities for searching and filtering appointments based on various criteria.

The implementation successfully fulfills all requirements of the laboratory assignment, providing a robust and well-documented solution for managing temporal data.

## Data Model

The system is built around a core `tipo_inf` structure representing a single appointment, managed within a doubly-linked list.

### Appointment Data (`tipo.h`)

Appointments are defined with date, start/end times, and a textual description.

```cpp
typedef struct tipo_inf {
    char data[7];      // Date in YYMMDD format (e.g., "210919")
    char orai[5];      // Start time in HHMM format (e.g., "1200")
    char oraf[5];      // End time in HHMM format (e.g., "1300")
    char descr[51];    // Description (max 50 characters)
};
```

### Doubly-Linked List (`lista.h`)

The list structure allows for efficient traversal in both chronological and reverse-chronological order.

```cpp
struct elem {
    tipo_inf inf;    // Appointment data
    elem* pun;       // Pointer to next appointment (later in time)
    elem* prev;      // Pointer to previous appointment (earlier in time)
};
```

## Input Files

The program loads its data from a single plain text file:

-   **`agenda.txt`**: Defines appointment information.
    -   **Format**: Date, start time, and end time on the first line; description on the second line.
    -   **Example**:
        ```
        210919 1200 1300
        Riunione con Luca
        ```

## Implemented Features

The `compito.cc` file contains the main logic, divided into features as specified in the laboratory assignment.

### 1. Core Agenda Management (Punto 1)
- **`void aggiungi_agenda(lista&, tipo_inf)`**: Adds an appointment, but only if another appointment with the same date and start time does not already exist. It prints an error on conflict.
- **`void stampa(lista)`**: Prints the entire agenda to the console, ordered chronologically.
- **`main()`**: The main program loads all appointments from `agenda.txt` and uses the above functions to build and display the final, correct agenda.

### 2.a. Daily Appointment Analysis (Punto 2.a)
- **`void quanti(lista, tipo_inf)`**: Given a specific appointment, this function calculates and prints the number of other appointments scheduled on the same day that occur before it and after it.

### 2.b. Ordered Insertion (Punto 2.b)
- **`lista inserimento_ordinato(lista, tipo_inf)`**: This function ensures that appointments are always inserted into the list in chronological order (by date, then by start time). This is a core part of `aggiungi_agenda`.

### 3. Appointment Extraction (Punto 3)
- **`lista estrai(lista&, char*)`**: Creates a new list containing only appointments that match a given description. This function is highly efficient as it manipulates pointers to move nodes from the main agenda to the new list without allocating or deallocating memory.

## Core Data Structures

The implementation relies on one fundamental data structure:

-   **Ordered List (`liste`)**: A **doubly-linked list** that maintains appointment data sorted chronologically by date and start time. This structure is ideal for efficient traversal and ordered printing.

## How to Compile and Run

A `Makefile` is provided for easy compilation.

1.  **Compile the project**:
    ```sh
    make
    ```
2.  **Run the executable**:
    ```sh
    ./agenda
    ```

The program runs non-interactively, executing all defined tests and printing the results.

### Expected Output

Running the program with the provided `agenda.txt` produces the following verified results:

**Punto 1: Agenda Loading and Conflict Detection**
- The appointment `210919 1430 1530 Palestra` is correctly rejected with an error message because it conflicts with an existing appointment.
- The final agenda is printed in chronological order.

**Punto 2.a: Daily Analysis**
- For the appointment `210919 1400 1430 Pranzo`, the program prints:
  `2 appuntamenti prima e 2 appuntamento dopo`

**Punto 3: Extraction by Description**
- When extracting appointments with the description "Lezione":
    - A new list containing the 3 "Lezione" appointments is created and printed.
    - The main agenda is reprinted, now missing those 3 appointments.

## Technical Implementation

### File Loading Strategy
- **Agenda Loading**: Reads `agenda.txt` line by line, parsing date/time information and handling multi-word descriptions correctly with `getline`.
- **Error Handling**: Includes a check for the existence of `agenda.txt` to prevent runtime errors.

### Algorithm Efficiency
- **Ordered Insertion**: `O(n)` per appointment, as it may require traversing the list to find the correct position. Total loading time is `O(n^2)`.
- **Search**: `O(n)` due to the linear nature of linked list traversal.
- **Extraction**: `O(n)`, as it requires a single pass through the list.
- **Memory Management**: The `estrai` function is implemented to be memory-neutral, moving nodes without `new` or `delete` calls to prevent memory leaks.

### Data Structure Integration
- **Chronological Integrity**: The `compare` function in `tipo.cc` is central to maintaining order, first comparing by date and then by start time.
- **Conflict Management**: The core logic in `aggiungi_agenda` performs an `O(n)` search to check for duplicates before insertion, ensuring data integrity.
- **List Manipulation**: The project demonstrates robust pointer manipulation for insertion, deletion, and moving nodes between lists, which are key skills for advanced data structure management.

This implementation successfully demonstrates the use of doubly-linked lists for a practical, real-world application like an agenda system, focusing on data integrity, chronological ordering, and efficient list manipulation.
