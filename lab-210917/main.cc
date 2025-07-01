#include <iostream>
#include "lista.h"
#include "tipo.h"
#include <fstream>
#include <cstring>

using namespace std;

// Funzione per caricare gli appuntamenti dal file agenda.txt
lista carica_agenda(const char* nome_file) {
    lista agenda = NULL;
    ifstream file(nome_file);
    if (!file) {
        cout << "Errore nell'apertura del file " << nome_file << endl;
        return NULL;
    }
    tipo_inf app;
    while (file >> app.data >> app.orai >> app.oraf) {
        file.ignore(); // per consumare lo spazio dopo oraf
        file.getline(app.descr, 51);
        agenda = inserimento_ordinato(agenda, app);
    }
    file.close();
    return agenda;
}

// Funzione per stampare gli appuntamenti di un dato giorno
void stampa_agenda_giorno(lista agenda, const char* giorno) {
    cout << "Appuntamenti per il giorno " << giorno << ":" << endl;
    lista p = agenda;
    while (p != NULL) {
        if (strcmp(head(p).data, giorno) == 0) {
            print(head(p));
        }
        p = tail(p);
    }
}

// Funzione per visualizzare l'agenda completa
void visualizza_agenda(lista agenda) {
    cout << "Agenda completa:" << endl;
    lista p = agenda;
    while (p != NULL) {
        print(head(p));
        p = tail(p);
    }
}

// Funzione per aggiungere un nuovo appuntamento
lista aggiungi_appuntamento(lista agenda) {
    tipo_inf nuovo_app;
    cout << "Inserisci data (AAMMGG): ";
    cin >> nuovo_app.data;
    cout << "Inserisci ora di inizio (HHMM): ";
    cin >> nuovo_app.orai;
    cout << "Inserisci ora di fine (HHMM): ";
    cin >> nuovo_app.oraf;
    cout << "Inserisci descrizione: ";
    cin.ignore();
    cin.getline(nuovo_app.descr, 51);

    if (controlla_sovrapposizioni(agenda, nuovo_app)) {
        cout << "ATTENZIONE: L'appuntamento si sovrappone con uno esistente!" << endl;
    }

    return inserimento_ordinato(agenda, nuovo_app);
}

// Funzione per cancellare un appuntamento
lista cancella_appuntamento(lista agenda) {
    tipo_inf app_da_cancellare;
    cout << "Inserisci data appuntamento da cancellare (AAMMGG): ";
    cin >> app_da_cancellare.data;
    cout << "Inserisci ora di inizio (HHMM): ";
    cin >> app_da_cancellare.orai;
    cout << "Inserisci ora di fine (HHMM): ";
    cin >> app_da_cancellare.oraf;
    cout << "Inserisci descrizione: ";
    cin.ignore();
    cin.getline(app_da_cancellare.descr, 51);

    elem* e = search(agenda, app_da_cancellare);
    if (e != NULL) {
        agenda = delete_elem(agenda, e);
        cout << "Appuntamento cancellato." << endl;
    } else {
        cout << "Appuntamento non trovato." << endl;
    }
    return agenda;
}

int main() {
    lista agenda = carica_agenda("agenda.txt");
    if(agenda == NULL){
        return 1;
    }

    char scelta;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Visualizza agenda completa" << endl;
        cout << "2. Visualizza appuntamenti di un giorno" << endl;
        cout << "3. Aggiungi appuntamento" << endl;
        cout << "4. Cancella appuntamento" << endl;
        cout << "5. Esci" << endl;
        cout << "Scelta: ";
        cin >> scelta;

        switch (scelta) {
            case '1':
                visualizza_agenda(agenda);
                break;
            case '2': {
                char giorno[7];
                cout << "Inserisci giorno (AAMMGG): ";
                cin >> giorno;
                stampa_agenda_giorno(agenda, giorno);
                break;
            }
            case '3':
                agenda = aggiungi_appuntamento(agenda);
                break;
            case '4':
                agenda = cancella_appuntamento(agenda);
                break;
            case '5':
                cout << "Uscita." << endl;
                break;
            default:
                cout << "Scelta non valida." << endl;
        }
    } while (scelta != '5');

    return 0;
}
