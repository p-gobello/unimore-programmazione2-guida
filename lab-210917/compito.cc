#include <iostream>
#include <fstream>
#include <cstring>
#include "lista.h"
#include "tipo.h"

using namespace std;

/**
 * Punto 1: Aggiunge un appuntamento all'agenda solo se non è già presente
 * un appuntamento nella stessa data e ora di inizio
 */
void aggiungi_agenda(lista& agenda, tipo_inf a) {
    // Cerca se esiste già un appuntamento con stessa data e ora di inizio
    lista p = agenda;
    while (p != NULL) {
        tipo_inf app_esistente = head(p);
        if (strcmp(app_esistente.data, a.data) == 0 && 
            strcmp(app_esistente.orai, a.orai) == 0) {
            cout << "ERRORE: Appuntamento già presente nella stessa data e ora di inizio" << endl;
            return;
        }
        p = tail(p);
    }
    
    // Se non c'è conflitto, aggiunge l'appuntamento
    agenda = inserimento_ordinato(agenda, a);
}

/**
 * Punto 1: Stampa l'agenda completa
 */
void stampa(lista agenda) {
    cout << "=== AGENDA ===" << endl;
    lista p = agenda;
    while (p != NULL) {
        print(head(p));
        p = tail(p);
    }
    cout << "==============" << endl;
}

/**
 * Punto 2.a: Conta quanti appuntamenti precedono e seguono l'appuntamento dato
 * nello stesso giorno
 */
void quanti(lista agenda, tipo_inf a) {
    // Prima trova l'appuntamento nella lista
    elem* elemento_trovato = search(agenda, a);
    if (elemento_trovato == NULL) {
        cout << "Appuntamento non trovato nell'agenda" << endl;
        return;
    }
    
    int precedenti = 0;
    int seguenti = 0;
    
    // Conta appuntamenti precedenti nello stesso giorno
    lista p = agenda;
    while (p != NULL && p != elemento_trovato) {
        if (strcmp(head(p).data, a.data) == 0) {
            precedenti++;
        }
        p = tail(p);
    }
    
    // Conta appuntamenti seguenti nello stesso giorno
    p = tail(elemento_trovato);
    while (p != NULL) {
        if (strcmp(head(p).data, a.data) == 0) {
            seguenti++;
        }
        p = tail(p);
    }
    
    cout << precedenti << " appuntamenti prima e " << seguenti << " appuntamento dopo" << endl;
}

/**
 * Punto 3: Estrae dalla lista tutti gli appuntamenti con la descrizione specificata
 */
lista estrai(lista& agenda, char* descr) {
    lista estratti = NULL;
    lista p = agenda;
    lista precedente = NULL;
    
    while (p != NULL) {
        if (strcmp(head(p).descr, descr) == 0) {
            // Rimuovi elemento dalla lista agenda
            lista next = tail(p);
            
            if (precedente == NULL) {
                // Rimozione in testa
                agenda = next;
                if (next != NULL) {
                    next->prev = NULL;
                }
            } else {
                // Rimozione non in testa
                precedente->pun = next;
                if (next != NULL) {
                    next->prev = precedente;
                }
            }
            
            // Aggiungi elemento alla lista estratti
            p->pun = estratti;
            p->prev = NULL;
            if (estratti != NULL) {
                estratti->prev = p;
            }
            estratti = p;
            
            p = next;
        } else {
            precedente = p;
            p = tail(p);
        }
    }
    
    return estratti;
}

/**
 * Main principale secondo i requisiti del Punto 1
 */
int main() {
    lista agenda = NULL;
    
    // Legge gli appuntamenti dal file agenda.txt
    ifstream file("agenda.txt");
    if (!file) {
        cout << "Errore nell'apertura del file agenda.txt" << endl;
        return 1;
    }
    
    tipo_inf app;
    cout << "Caricamento appuntamenti da agenda.txt..." << endl;
    
    while (file >> app.data >> app.orai >> app.oraf) {
        file.ignore(); // consuma il carattere newline
        file.getline(app.descr, 51);
        
        cout << "Aggiungendo: " << app.data << " " << app.orai << " " << app.oraf << " " << app.descr << endl;
        aggiungi_agenda(agenda, app);
    }
    file.close();
    
    cout << "\nStampa agenda finale:" << endl;
    stampa(agenda);
    
    // Test Punto 2.a con l'appuntamento "210919 1400 1430 Pranzo"
    cout << "\n=== TEST PUNTO 2.A ===" << endl;
    tipo_inf test_app;
    strcpy(test_app.data, "210919");
    strcpy(test_app.orai, "1400");
    strcpy(test_app.oraf, "1430");
    strcpy(test_app.descr, "Pranzo");
    
    cout << "Test quanti() per appuntamento: ";
    print(test_app);
    quanti(agenda, test_app);
    
    // Test Punto 3 con descrizione "Lezione"
    cout << "\n=== TEST PUNTO 3 ===" << endl;
    lista agenda_backup = agenda; // Per non modificare l'originale nel test
    
    cout << "Estrazione appuntamenti con descrizione 'Lezione':" << endl;
    lista lezioni = estrai(agenda_backup, (char*)"Lezione");
    
    cout << "\nLista appuntamenti estratti (Lezioni):" << endl;
    stampa(lezioni);
    
    cout << "\nAgenda dopo estrazione:" << endl;
    stampa(agenda_backup);
    
    return 0;
} 