#include <iostream>
#include <fstream>
#include "liste.h"
#include "tipo.h"

using namespace std;

void pesca(lista& l, int v, char s){
    tipo_inf c;
    c.numero = v;
    c.seme = s;
    elem* e = new_elem(c);
    l = ord_insert_elem(l, e);
}

void stampa(lista l1, lista l2){
    elem* e1 = l1;
    elem* e2 = l2;
    while(e1 != NULL && e2 != NULL){
        print(head(e1));
        int cmp = compare(head(e1), head(e2));
        if(cmp < 0)
            cout << " e' minore di ";
        else if(cmp > 0)
            cout << " e' maggiore di ";
        else
            cout << " e' uguale a ";
        print(head(e2));
        cout << endl;
        e1 = tail(e1);
        e2 = tail(e2);
    }
}

int* tris(lista carte){
    int* t = new int[13];
    for(int i=0; i<13; i++)
        t[i] = 0;
    elem* e = carte;
    while(e != NULL){
        int count = 0;
        elem* f = carte;
        while(f != NULL){
            if(head(e).numero == head(f).numero)
                count++;
            f = tail(f);
        }
        if(count >= 3)
            t[head(e).numero-1]++;
        e = tail(e);
    }
    return t;
}

int cala(lista& carte){
    int* t = tris(carte);
    int punteggio = 0;
    for(int i=0; i<13; i++){
        if(t[i] >= 3){
            cout << "Trovato tris di " << i+1 << endl;
            punteggio += (i+1)*t[i];
            int count = 0;
            elem* e = carte;
            while(e != NULL && count < 3){
                if(head(e).numero == i+1){
                    elem* tmp = e;
                    e = tail(e);
                    carte = delete_elem(carte, tmp);
                    count++;
                }
                else
                    e = tail(e);
            }
        }
    }
    return punteggio;
}

void pesca_ordinato(lista& l, int v, char s){
    tipo_inf c;
    c.numero = v;
    c.seme = s;
    elem* e = new_elem(c);
    l = ord_insert_elem(l, e);
}

int main(){
    lista g1 = NULL;
    lista g2 = NULL;

    ifstream f1("g1.txt");
    ifstream f2("g2.txt");

    int n;
    cout << "Quante carte? ";
    cin >> n;

    for(int i=0; i<n; i++){
        int v;
        char s;
        f1 >> v >> s;
        pesca_ordinato(g1, v, s);
        f2 >> v >> s;
        pesca_ordinato(g2, v, s);
    }

    stampa(g1, g2);

    int* t1 = tris(g1);
    int* t2 = tris(g2);

    cout << "giocatore 1: ";
    for(int i=0; i<13; i++)
        cout << t1[i] << " ";
    cout << endl;

    cout << "giocatore 2: ";
    for(int i=0; i<13; i++)
        cout << t2[i] << " ";
    cout << endl;

    int p1 = 0;
    int p2 = 0;

    while(g1 != NULL && g2 != NULL){
        int v;
        char s;
        cout << "Giocatore 1, pesca una carta: ";
        cin >> v >> s;
        pesca_ordinato(g1, v, s);
        p1 += cala(g1);

        if(g1 == NULL){
            cout << "Fine gioco" << endl;
            break;
        }

        cout << "Giocatore 2, pesca una carta: ";
        cin >> v >> s;
        pesca_ordinato(g2, v, s);
        p2 += cala(g2);

        if(g2 == NULL){
            cout << "Fine gioco" << endl;
            break;
        }
    }

    if(p1 > p2)
        cout << "Vince giocatore 1 con " << p1 << " punti" << endl;
    else if(p2 > p1)
        cout << "Vince giocatore 2 con " << p2 << " punti" << endl;
    else
        cout << "Pareggio con " << p1 << " punti" << endl;


    return 0;
}
