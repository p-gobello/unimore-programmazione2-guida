# Guida alla configurazione della chiave SSH per GitLab

Questa guida ti mostrerà come generare una nuova chiave SSH e aggiungerla al tuo account GitLab.

### 1. Genera una nuova chiave SSH

Apri un terminale e digita il seguente comando. Sostituisci `MATRICOLA@studenti.unimore.it` con il tuo indirizzo email istituzionale.

```bash
ssh-keygen -t ed25519 -C "MATRICOLA@studenti.unimore.it"
```

Quando ti viene chiesto "Enter a file in which to save the key", puoi premere Invio per accettare la posizione predefinita. Ti verrà anche chiesto di inserire una passphrase, che è una password per proteggere la tua chiave privata. Poichè lo farai solo una volta (per svolgere l'esame) premi Invio e non mettere nulla.

### 2. Aggiungi la chiave SSH all'agente SSH

Esegui questo comando per aggiungere la tua chiave privata all'agente SSH. In questo modo non dovrai inserire la passphrase ogni volta.

```bash
ssh-add ~/.ssh/id_ed25519
```

### 3. Copia la tua chiave pubblica SSH

Mostra la tua chiave pubblica con questo comando:

```bash
cat ~/.ssh/id_ed25519.pub
```

Seleziona e copia l'intero output di questo comando. Inizia con `ssh-ed25519` e finisce con il tuo indirizzo email.

### 4. Aggiungi la chiave pubblica a GitLab

1.  Apri il tuo browser e vai su [GitLab](https://gitlab.com).
2.  Accedi al tuo account.
3.  Vai su **Impostazioni** (o *Settings*), di solito cliccando sulla tua immagine del profilo in alto a destra.
4.  Nella barra laterale di navigazione a sinistra, clicca su **SSH Keys** (o *Chiavi SSH*).
5.  Incolla la tua chiave pubblica (copiata nel passaggio precedente) nel campo "Key".
6.  Dai un titolo descrittivo alla chiave nel campo "Title" (ad esempio, "Laptop Lavoro").
7.  Clicca su **Add key**.

### 5. Testa la connessione

Per verificare che tutto sia configurato correttamente, esegui questo comando nel terminale:

```bash
ssh -T git@gitlab.com
```

Se è la prima volta che ti connetti, potresti vedere un messaggio come questo:
```
The authenticity of host 'gitlab.com (172.65.251.78)' can't be established.
ECDSA key fingerprint is SHA256:HbW3g8zUjNSksFbqTiUWPWg2Bq1x8xdGUrliXFzSnUw.
Are you sure you want to continue connecting (yes/no)?
```
Digita `yes` e premi Invio.

Se tutto è andato a buon fine, dovresti vedere un messaggio di benvenuto da GitLab, come "Welcome to GitLab, @username!".