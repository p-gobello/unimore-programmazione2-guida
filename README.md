# Laboratorio di Programmazione 2 - Guida Completa di Analisi e Riferimento

## Attenzione
Le soluzioni sono state generate tramite AI. Sono stati utilizzati Claude-4-Sonnet e Gemini-2.5-Pro.

## Panoramica
Questa repository contiene analisi complete di 8 esercitazioni di laboratorio di programmazione incentrate su strutture dati e algoritmi fondamentali. Ogni laboratorio dimostra applicazioni pratiche di concetti di base dell'informatica attraverso scenari del mondo reale.

## Struttura della Repository
```
/
├── lab-180618/     # Albero Binario di Ricerca (BST) con le Carte
├── lab-180719/     # Implementazione di Coda e Grafo
├── lab-180911/     # Liste Doppiamente Concatenate con Indice Invertito
├── lab-190205/     # Gestione di Carte con Liste Doppiamente Concatenate
├── lab-190627/     # Grafo con Punti di Interesse + Liste
├── lab-210917/     # Gestione Calendario/Agenda
├── lab-220721/     # Sistema di Gioco di Carte Multi-giocatore
├── lab-240703/     # Gestione Alberghiera con BST
└── README.md       # Questo file di panoramica
```

## Riferimenti ai File

### Guide Complete
- [Guida Completa (Italiano)](COMPLETE_GUIDE.it.md)
- [Complete Guide (English)](COMPLETE_GUIDE.en.md)
- [Guida  GIT (Italiano)](GIT_GUIDE.it.md)
- [GIT Guide (English)](GIT_GUIDE.en.md)

### README dei Laboratori
Ogni laboratorio ha il suo file `README.md` con dettagli specifici sull'esercitazione.
- [Lab 180618](./lab-180618/README.md)
- [Lab 180719](./lab-180719/README.md)
- [Lab 180911](./lab-180911/README.md)
- [Lab 190205](./lab-190205/README.md)
- [Lab 190627](./lab-190627/README.md)
- [Lab 210917](./lab-210917/README.md)
- [Lab 220721](./lab-220721/README.md)
- [Lab 240703](./lab-240703/README.md)

## Riepilogo dei Laboratori

### Lab 180618 - Fondamenti degli Alberi Binari di Ricerca
**Focus Principale**: Implementazione di un sistema di gestione per **carte fedeltà** tramite BST.

**Strutture Dati Chiave**:
- Albero Binario di Ricerca (BST) con chiave numerica (ID carta).
- Struttura `cliente` che contiene `nome_cognome` e `punti`.

**Funzioni Essenziali**:
- `bst_insert()` - Inserimento di nuove carte fedeltà.
- `bst_search()` - Ricerca efficiente delle carte per ID.
- Query su intervalli per calcolare somme di punti.

**Obiettivi di Apprendimento**:
- Applicazione pratica dei BST per la gestione di dati reali.
- Attraversamento di alberi per reportistica ordinata e calcoli aggregati.
- Aggiornamento dei dati all'interno della struttura ad albero.

### Lab 180719 - Fondamenti di Code e Grafi
**Focus Principale**: Analisi di un social network modellato come **grafo orientato e non pesato**.

**Strutture Dati Chiave**:
- Coda per l'attraversamento Breadth-First Search (BFS).
- Grafo rappresentato con liste di adiacenza.
- Nodi di tipo `Utente` o `Tweet`.

**Funzioni Essenziali**:
- `enqueue()`/`dequeue()` - Operazioni di base della coda.
- Traversal (BFS) per trovare utenti seguiti diretti e indiretti.
- Analisi delle connessioni per identificare utenti "influenti".

**Obiettivi di Apprendimento**:
- Applicazione delle code per il BFS nei grafi.
- Modellazione di relazioni complesse (segue, like, possiede) con un grafo.
- Strategie di rappresentazione e attraversamento dei grafi.

### Lab 180911 - Liste Concatenate Avanzate e Recupero dell'Informazione
**Focus Principale**: Liste doppiamente concatenate con indicizzazione di documenti

**Strutture Dati Chiave**:
- Liste doppiamente concatenate con puntatori `prev`/`next`
- Struttura `parola` per l'indice invertito
- Sistema di mappatura documento-parola

**Funzioni Essenziali**:
- `ord_insert_elem()` - Mantiene l'ordine di inserimento
- `ord_search()` - Ricerca ottimizzata con terminazione anticipata
- Attraversamento bidirezionale della lista

**Obiettivi di Apprendimento**:
- Concetti di recupero dell'informazione
- Strutture dati a indice invertito
- Gestione di dati ordinati vs. non ordinati
- Tecniche di ottimizzazione della ricerca

### Lab 190205 - Implementazione di un Gioco di Carte Specializzato
**Focus Principale**: Gestione di carte da gioco con operazioni type-safe

**Strutture Dati Chiave**:
- Struttura `carta` con seme e valore
- Liste doppiamente concatenate per la gestione della mano

**Funzioni Essenziali**:
- Strategie di confronto delle carte (per seme, per valore)
- Validazione delle carte e rilevamento di duplicati
- Algoritmi di organizzazione della mano

**Obiettivi di Apprendimento**:
- Modellazione di dati specifici del dominio
- Sicurezza dei tipi nelle strutture dati
- Implementazione delle regole di gioco
- Strategie di validazione dei dati

### Lab 190627 - Sistemi Informativi Geografici
**Focus Principale**: Navigazione in una città modellata come **grafo non pesato** di punti di interesse (POI).

**Strutture Dati Chiave**:
- Grafo che utilizza liste di adiacenza per le connessioni tra POI.
- Lista ordinata per la gestione dei dati dei POI.
- Struttura POI con ID, nome e tipo.

**Funzioni Essenziali**:
- Filtraggio dei POI per tipo (es. solo musei).
- Ricerca di percorsi omogenei (solo tra POI dello stesso tipo) tramite DFS.
- Integrazione tra grafo e lista per la gestione dei dati.

**Obiettivi di Apprendimento**:
- Applicazioni reali dei grafi per sistemi di navigazione.
- Combinazione di diverse strutture dati per risolvere problemi complessi.
- Algoritmi di attraversamento (DFS) con vincoli.

### Lab 210917 - Gestione di Dati Temporali
**Focus Principale**: Sistema di calendario/agenda con operazioni basate sul tempo

**Strutture Dati Chiave**:
- Struttura `appuntamento` (data, ora di inizio, ora di fine, descrizione)
- Liste ordinate cronologicamente

**Funzioni Essenziali**:
- Rilevamento di conflitti temporali
- Inserimento cronologico
- Validazione di dati temporali

**Obiettivi di Apprendimento**:
- Strutture dati basate sul tempo
- Algoritmi di rilevamento dei conflitti
- Progettazione di sistemi di scheduling
- Validazione di dati temporali

### Lab 220721 - Analisi di Dati di Carte
**Focus Principale**: Gestione e analisi comparativa di più mani di carte da gioco.

**Strutture Dati Chiave**:
- Liste doppiamente concatenate per rappresentare le mani di carte.
- Struttura `carta` per seme e valore.

**Funzioni Essenziali**:
- Gestione di collezioni multiple di dati (due mani di carte).
- Ricerca di elementi comuni tra le liste.
- Conteggio e analisi statistica delle carte in ogni mano.

**Obiettivi di Apprendimento**:
- Gestione di dati multi-collezione con strutture identiche.
- Analisi comparativa tra diversi set di dati.
- Integrità e validazione dei dati all'interno di una singola collezione.

### Lab 240703 - Applicazioni Avanzate dei BST
**Focus Principale**: Sistema di gestione alberghiera con ricerca basata sulla valutazione

**Strutture Dati Chiave**:
- BST con ordinamento inverso (valutazioni più alte a sinistra)
- Informazioni sugli hotel con attributi multipli

**Funzioni Essenziali**:
- Organizzazione dell'albero basata sulla valutazione
- Query di intervallo per la ricerca di hotel
- Filtraggio basato sulla qualità

**Obiettivi di Apprendimento**:
- Strategie di ordinamento personalizzate per i BST
- Dati multi-criterio in strutture a chiave singola
- Progettazione di applicazioni aziendali
- Ottimizzazione della ricerca per domini specifici

## Concetti Fondamentali di Informatica Trattati

### Padronanza delle Strutture Dati

#### 1. **Strutture Dati Lineari**
- **Liste Concatenate**: Singole, doppiamente concatenate con varie applicazioni
- **Code**: Implementazione FIFO con operazioni efficienti
- **Applicazioni**: Scheduling di task, BFS, gestione di buffer

#### 2. **Strutture Dati ad Albero**
- **Alberi Binari di Ricerca**: Alberi auto-organizzanti e ricercabili
- **Attraversamenti di Alberi**: In-order, pre-order, post-order
- **Applicazioni**: Database, file system, parsing di espressioni

#### 3. **Strutture Dati a Grafo**
- **Liste di Adiacenza**: Rappresentazione efficiente in termini di spazio dei grafi
- **Grafi Pesati**: Applicazioni reali con costi sugli archi
- **Applicazioni**: Navigazione, social network, ottimizzazione

### Pattern di Progettazione degli Algoritmi

#### 1. **Algoritmi di Ricerca**
- **Ricerca Lineare**: Baseline O(n) per dati non ordinati
- **Ricerca Binaria**: O(log n) per strutture ordinate/alberi
- **Terminazione Anticipata**: Ottimizzazione per dati ordinati

#### 2. **Algoritmi di Inserimento**
- **Inserimento in Testa**: O(1) per liste e code
- **Inserimento Ordinato**: O(n) mantenendo la proprietà di ordinamento
- **Inserimento in Albero**: O(log n) in media per alberi bilanciati

#### 3. **Algoritmi di Cancellazione**
- **Cancellazione Semplice**: O(1) con accesso diretto ai puntatori
- **Cancellazione in Albero**: Gestione di casi complessi (foglia, un figlio, due figli)
- **Mantenimento dell'Integrità**: Conservazione delle proprietà della struttura dati

### Tecniche di Programmazione

#### 1. **Gestione della Memoria**
- Allocazione dinamica con `new`/`delete`
- Manipolazione e validazione dei puntatori
- Prevenzione dei memory leak

#### 2. **Programmazione Modulare**
- Separazione tra file header e di implementazione
- Sistemi di tipi generici (`tipo_inf`)
- Progettazione di interfacce per la riusabilità

#### 3. **Gestione degli Errori**
- Validazione dell'input
- Gestione dei casi limite
- Gestione controllata dei fallimenti

## Applicazioni nel Mondo Reale

### 1. **Sistemi di Database**
- **BST**: Strutture di indicizzazione per ricerche veloci
- **Alberi B+**: Strutture ad albero ottimizzate per il disco
- **Tabelle Hash**: Pattern di accesso a tempo costante

### 2. **Sistemi Operativi**
- **Code**: Scheduling dei processi, buffer di I/O
- **Alberi**: Organizzazione del file system
- **Grafi**: Allocazione di risorse, rilevamento di deadlock

### 3. **Applicazioni Web**
- **Grafi**: Social network, sistemi di raccomandazione
- **Alberi**: Strutture DOM, alberi decisionali
- **Liste**: Gestione di contenuti dinamici

### 4. **Sviluppo di Videogiochi**
- **Liste**: Gestione dell'inventario, statistiche dei giocatori
- **Alberi**: Alberi di stato del gioco, IA decisionale
- **Grafi**: Progettazione dei livelli, algoritmi di pathfinding

### 5. **Sistemi Informativi Geografici**
- **Grafi**: Reti stradali, pianificazione di percorsi
- **Alberi**: Indicizzazione spaziale (QuadTree, R-Tree)
- **Liste**: Gestione di POI, servizi di localizzazione

## Guida allo Studio per la Preparazione all'Esame

### Algoritmi Essenziali da Padroneggiare

#### 1. **Operazioni sugli Alberi**
```cpp
// Pattern di ricerca in un BST
while (node != NULL) {
    if (target == node->key) return node;
    node = (target < node->key) ? node->left : node->right;
}
```

#### 2. **Manipolazione delle Liste**
```cpp
// Pattern di inserimento in una lista doppiamente concatenata
new_node->next = current->next;
if (current->next != NULL) current->next->prev = new_node;
current->next = new_node;
new_node->prev = current;
```

#### 3. **Operazioni sulle Code**
```cpp
// Enqueue/dequeue efficienti
enqueue: tail->next = new_node; tail = new_node;
dequeue: temp = head; head = head->next; delete temp;
```

### Strategie di Risoluzione dei Problemi

#### 1. **Selezione della Struttura Dati**
- **Necessità di ricerca veloce?** → Usa BST o tabella hash
- **Necessità di ordinamento?** → Usa liste ordinate o BST
- **Necessità di FIFO/LIFO?** → Usa coda/stack
- **Necessità di relazioni?** → Usa grafi

#### 2. **Ottimizzazione degli Algoritmi**
- **Terminazione anticipata** negli algoritmi di ricerca
- **Analisi ammortizzata** per operazioni frequenti
- **Compromessi spazio-tempo** in base ai requisiti

#### 3. **Errori Comuni**
- **Gestione dei puntatori**: Aggiorna sempre i link bidirezionali
- **Memory leak**: Associa ogni `new` a un `delete`
- **Casi limite**: Strutture vuote, elementi singoli
- **Integrità dei dati**: Mantieni gli invarianti durante le operazioni

### Problemi di Esercitazione

#### 1. **Sfide di Implementazione**
- Implementa un BST con operazioni iterative (non ricorsive)
- Crea una coda usando due stack
- Progetta un grafo con rappresentazioni sia a lista di adiacenza che a matrice

#### 2. **Progettazione di Applicazioni**
- Progetta un file system usando alberi
- Implementa un semplice sistema di scheduling con priorità
- Crea un grafo di social network con relazioni di amicizia

#### 3. **Analisi degli Algoritmi**
- Confronta la complessità temporale/spaziale di diverse implementazioni
- Analizza le prestazioni nel caso peggiore vs. caso medio
- Progetta casi di test per le condizioni limite

## Argomenti Avanzati per Ulteriori Studi

### 1. **Alberi Auto-bilancianti**
- Alberi AVL (bilanciati in altezza)
- Alberi Rosso-Neri (bilanciati per colore)
- Alberi B (ottimizzati per il disco)

### 2. **Algoritmi su Grafi Avanzati**
- Algoritmo di Dijkstra per il percorso minimo
- Alberi di copertura minima (Prim, Kruskal)
- Ordinamento topologico

### 3. **Strutture Basate su Hash**
- Tabelle hash con risoluzione delle collisioni
- Filtri di Bloom per test di appartenenza
- Hashing consistente per sistemi distribuiti

### 4. **Strutture Dati Concorrenti**
- Implementazioni thread-safe
- Strutture dati lock-free
- Algoritmi paralleli

## Conclusione

Questa serie di laboratori fornisce una base completa su strutture dati e algoritmi attraverso applicazioni pratiche e reali. La progressione da semplici liste concatenate a complessi sistemi multi-struttura dimostra l'evoluzione delle capacità di risoluzione dei problemi essenziali per lo sviluppo del software.

Ogni laboratorio si basa sui concetti precedenti introducendo nuove sfide, creando un'esperienza di apprendimento strutturata che prepara gli studenti ad argomenti avanzati di informatica e allo sviluppo professionale di software.

L'enfasi sulle applicazioni pratiche—dai giochi di carte ai sistemi di gestione alberghiera—illustra come le strutture dati fondamentali risolvono problemi del mondo reale, rendendo i concetti astratti concreti e memorabili per la ritenzione e l'applicazione a lungo termine.

## gang