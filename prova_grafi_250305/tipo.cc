/*
 * tipo.cc
 *
 * Implementation of tipo_inf structure operations
 */

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

#include "tipo.h"

/**
 * @brief Compare two tipo_inf structures
 * @param a First tipo_inf to compare
 * @param b Second tipo_inf to compare
 * @return 0 if equal, negative if a < b, positive if a > b
 */
int compare(tipo_inf a, tipo_inf b) {
    int result = strcmp(a.descrizione, b.descrizione);
    if (result == 0) {
        return a.tipo - b.tipo;
    }
    return result;
}

/**
 * @brief Copy source tipo_inf to destination
 * @param dest Destination tipo_inf (reference)
 * @param src Source tipo_inf to copy from
 */
void copy(tipo_inf& dest, tipo_inf src) {
    strcpy(dest.descrizione, src.descrizione);
    dest.tipo = src.tipo;
}

/**
 * @brief Print tipo_inf information
 * @param t tipo_inf structure to print
 */
void print(tipo_inf t) {
    cout << t.descrizione << " (" << t.tipo << ")";
}
