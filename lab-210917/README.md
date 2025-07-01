# Lab 210917 - Agenda/Calendar Management with Doubly Linked Lists

## Overview
This lab implements a calendar/agenda system using doubly-linked lists to manage appointments. Each appointment contains date, start time, end time, and description information. The system demonstrates practical application of list data structures for time management software.

## Data Structures

### Appointment Structure (`tipo_inf`)
```cpp
typedef struct tipo_inf {
    char data[7];      // Date in YYMMDD format (e.g., "210919")
    char orai[5];      // Start time in HHMM format (e.g., "1200")
    char oraf[5];      // End time in HHMM format (e.g., "1300")
    char descr[51];    // Description (max 50 characters)
};
```

### Doubly Linked List Node (`elem`)
```cpp
struct elem {
    tipo_inf inf;    // Appointment data
    elem* pun;       // Pointer to next appointment
    elem* prev;      // Pointer to previous appointment
};
```

### List Type
- `typedef elem* lista` - List represented as pointer to first element

## Sample Agenda Data

The `agenda.txt` file shows a typical daily schedule:

### September 19, 2021 (210919)
- **08:30-11:00**: Lezione (Lecture)
- **12:00-13:00**: Riunione con Luca (Meeting with Luca)
- **14:00-14:30**: Pranzo (Lunch)
- **14:30-15:30**: Palestra (Gym) - *Overlaps with Esami!*
- **14:30-18:30**: Esami (Exams) - *Conflict detected*
- **19:30-20:00**: Palestra (Gym again)

### Other Dates
- **September 14, 2021**: 09:30-11:00 Riunione plenaria (Plenary meeting)
- **September 21, 2021**: 09:00-11:00 Lezione (Lecture)
- **September 22, 2021**: 11:00-13:00 Lezione (Lecture)

## Implemented Functions

### Core List Operations

1. **`elem* new_elem(tipo_inf inf)`**
   - Creates new appointment element
   - Copies appointment data using `copy()` function
   - Initializes pointers to NULL

2. **`lista insert_elem(lista l, elem* e)`**
   - Inserts appointment at head of list
   - Updates bidirectional links
   - **Use case**: Adding new appointments

3. **`lista delete_elem(lista l, elem* e)`**
   - Removes specific appointment from list
   - Handles head deletion and pointer updates
   - Frees memory properly
   - **Use case**: Canceling appointments

4. **`elem* search(lista l, tipo_inf v)`**
   - Linear search for specific appointment
   - Uses `compare()` function for matching
   - **Use case**: Finding existing appointments

### Accessor Functions

5. **`tipo_inf head(lista p)`** - Returns appointment data from first element
6. **`lista tail(lista p)`** - Returns pointer to next appointment
7. **`lista prev(lista p)`** - Returns pointer to previous appointment

### Appointment Type Operations

8. **`int compare(tipo_inf a1, tipo_inf a2)`**
   - Compares two appointments for ordering/equality
   - **Possible comparison strategies**:
     - By date first, then start time
     - By start time only
     - Exact match for all fields

9. **`void copy(tipo_inf& dest, tipo_inf source)`**
   - Copies appointment data including all string fields
   - Handles date, start time, end time, and description

10. **`void print(tipo_inf inf)`**
    - Prints appointment in readable format
    - **Example**: "19/09/21 12:00-13:00: Riunione con Luca"

## Key Algorithms and Calendar Concepts

### Time Management Operations

#### Chronological Insertion
```cpp
lista insert_chronological(lista agenda, tipo_inf new_appointment) {
    // Insert maintaining date/time order
    if (agenda == NULL || is_earlier(new_appointment, head(agenda))) {
        elem* new_elem = new_elem(new_appointment);
        return insert_elem(agenda, new_elem);
    }
    
    lista current = agenda;
    while (tail(current) != NULL && 
           is_earlier(head(tail(current)), new_appointment)) {
        current = tail(current);
    }
    
    // Insert after current
    elem* new_elem = new_elem(new_appointment);
    // ... insertion logic
}
```

#### Conflict Detection
```cpp
bool has_time_conflict(tipo_inf apt1, tipo_inf apt2) {
    // Check if appointments overlap
    if (strcmp(apt1.data, apt2.data) != 0) return false; // Different days
    
    int start1 = atoi(apt1.orai), end1 = atoi(apt1.oraf);
    int start2 = atoi(apt2.orai), end2 = atoi(apt2.oraf);
    
    return !(end1 <= start2 || end2 <= start1); // No gap between appointments
}
```

#### Daily Schedule Extraction
```cpp
lista get_daily_schedule(lista agenda, char* date) {
    lista daily = NULL;
    while (agenda != NULL) {
        if (strcmp(head(agenda).data, date) == 0) {
            elem* copy = new_elem(head(agenda));
            daily = insert_elem(daily, copy);
        }
        agenda = tail(agenda);
    }
    return daily;
}
```

### Time Format Handling

#### Time Comparison
```cpp
bool is_earlier_time(char* time1, char* time2) {
    int t1 = atoi(time1), t2 = atoi(time2);
    return t1 < t2;
}

int time_difference_minutes(char* start, char* end) {
    int start_hour = atoi(start) / 100;
    int start_min = atoi(start) % 100;
    int end_hour = atoi(end) / 100;
    int end_min = atoi(end) % 100;
    
    return (end_hour * 60 + end_min) - (start_hour * 60 + start_min);
}
```

#### Date Operations
```cpp
bool is_same_date(char* date1, char* date2) {
    return strcmp(date1, date2) == 0;
}

bool is_earlier_date(char* date1, char* date2) {
    return strcmp(date1, date2) < 0; // Lexicographic comparison works for YYMMDD
}
```

## Practical Applications

### Calendar Software Features

#### Basic Operations
- **Add appointment**: `insert_elem()` or chronological insertion
- **Cancel appointment**: `search()` then `delete_elem()`
- **View schedule**: Traverse list and `print()`
- **Edit appointment**: `search()`, modify data, or delete+insert

#### Advanced Features
```cpp
// Find free time slots
lista find_free_slots(lista agenda, char* date, int min_duration) {
    // Sort by time, find gaps >= min_duration
}

// Weekly view
void print_weekly_schedule(lista agenda, char* start_date) {
    // Extract and display 7 days starting from start_date
}

// Conflict resolution
lista resolve_conflicts(lista agenda) {
    // Identify overlapping appointments and suggest alternatives
}
```

### Real-World Extensions

#### Enhanced Appointment Structure
```cpp
typedef struct {
    char data[9];           // Full date: YYYYMMDD
    char orai[6];          // Start time: HH:MM
    char oraf[6];          // End time: HH:MM
    char descr[101];       // Longer description
    char location[51];     // Meeting location
    char attendees[201];   // List of participants
    int priority;          // 1-5 priority level
    bool reminder_set;     // Reminder flag
    int reminder_minutes;  // Minutes before event
} enhanced_appointment;
```

## General Concepts for Future Reference

### Calendar Data Management

#### Ordering Strategies
1. **Chronological**: By date, then start time
2. **Priority-based**: High priority items first
3. **Duration-based**: Longest/shortest appointments first
4. **Category-based**: Group by type (meetings, classes, personal)

#### Search Patterns
- **By date range**: Find all appointments in a week/month
- **By keyword**: Search descriptions for specific terms
- **By time**: Find what's happening at a specific time
- **By duration**: Find long meetings or quick appointments

### Time Conflict Management

#### Conflict Types
1. **Direct overlap**: Same time, same date
2. **Travel time**: Insufficient time between locations
3. **Resource conflict**: Same room/equipment needed
4. **Person conflict**: Same person in multiple meetings

#### Resolution Strategies
- **Automatic rescheduling**: Find alternative time slots
- **Priority-based**: Keep higher priority, reschedule lower
- **User notification**: Alert and let user decide
- **Buffer time**: Automatically add travel/setup time

### Performance Considerations

#### Memory Usage
- **Fixed-size strings**: Predictable memory per appointment
- **List overhead**: 2 pointers per appointment
- **String storage**: Unused space in fixed arrays

#### Time Complexities
- **Insert at head**: O(1)
- **Chronological insert**: O(n)
- **Search by content**: O(n)
- **Delete with pointer**: O(1)
- **Conflict detection**: O(n²) for all pairs

### Applications
- **Personal calendars**: Desktop/mobile applications
- **Scheduling systems**: Meeting room booking, employee schedules
- **Project management**: Task scheduling with dependencies
- **Medical systems**: Appointment booking for healthcare
- **Educational systems**: Class scheduling and room allocation

This lab demonstrates how linked lists can effectively manage temporal data with complex relationships, providing a foundation for developing scheduling and time management applications.
