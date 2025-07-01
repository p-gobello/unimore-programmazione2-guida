# Guide to setting up an SSH key for GitLab

This guide will show you how to generate a new SSH key and add it to your GitLab account.

### 1. Generate a new SSH key

Open a terminal and type the following command. Replace `MATRICOLA@studenti.unimore.it` with your institutional email address.

```bash
ssh-keygen -t ed25519 -C "MATRICOLA@studenti.unimore.it"
```

When asked "Enter a file in which to save the key", you can press Enter to accept the default location. You will also be asked to enter a passphrase, which is a password to protect your private key. Since you will only do this once (to take the exam) press Enter and do not enter anything.

### 2. Add the SSH key to the SSH agent

Run this command to add your private key to the SSH agent. This way you won't have to enter the passphrase every time.

```bash
ssh-add ~/.ssh/id_ed25519
```

### 3. Copy your public SSH key

Display your public key with this command:

```bash
cat ~/.ssh/id_ed25519.pub
```

Select and copy the entire output of this command. It starts with `ssh-ed25519` and ends with your email address.

### 4. Add the public key to GitLab

1.  Open your browser and go to [GitLab](https://gitlab.com).
2.  Log in to your account.
3.  Go to **Settings**, usually by clicking on your profile picture in the top right.
4.  In the left navigation sidebar, click on **SSH Keys**.
5.  Paste your public key (copied in the previous step) into the "Key" field.
6.  Give the key a descriptive title in the "Title" field (e.g., "Work Laptop").
7.  Click on **Add key**.

### 5. Test the connection

To verify that everything is set up correctly, run this command in the terminal:

```bash
ssh -T git@gitlab.com
```

If this is the first time you are connecting, you may see a message like this:
```
The authenticity of host 'gitlab.com (172.65.251.78)' can't be established.
ECDSA key fingerprint is SHA256:HbW3g8zUjNSksFbqTiUWPWg2Bq1x8xdGUrliXFzSnUw.
Are you sure you want to continue connecting (yes/no)?
```
Type `yes` and press Enter.

If everything went well, you should see a welcome message from GitLab, like "Welcome to GitLab, @username!".
