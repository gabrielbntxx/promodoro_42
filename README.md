# Pomodoro Shell — Timer en ligne de commande

## 🧾 Description

Pomodoro Shell est un timer minimaliste entièrement développé en **Bash**, conçu pour améliorer la productivité directement depuis le terminal.
L’application suit la méthode Pomodoro : alternance de périodes de travail et de courtes pauses pour garder un rythme efficace.

Ce projet met l’accent sur :

* la **simplicité**,
* l’efficacité,
* une utilisation rapide depuis n’importe quel terminal Linux ou macOS.

---

## ✨ Fonctionnalités

* ⏱️ Session Pomodoro (25 minutes par défaut)
* ☕ Pause courte ou longue selon l’avancement
* 🔔 Notifications simples dans le terminal
* 📦 Aucune dépendance externe : uniquement du **Shell pur**
* ⚡ Très léger et exécutable partout

---

## 🔧 Technologies utilisées

* **Bash / Shell**
* Commandes système (sleep, echo, clear…)

---

## 📁 Structure du projet

```
pomodoro-shell/
│
├── pomodoro.sh       # Script principal
└── README.md         # Documentation
```

---

## 🚀 Utilisation

Rendre le script exécutable :

```
chmod +x pomodoro.sh
```

Lancer une session Pomodoro :

```
./pomodoro.sh
```

---

## 💡 Personnalisation

Vous pouvez modifier :

* la durée du Pomodoro,
* la longueur des pauses,
* les messages affichés.

Les valeurs sont configurables directement en haut du fichier `pomodoro.sh`.

---

## 👤 Auteur

**Gabriel Benetrix**
Étudiant à l'école 42
