# 🥤 Distributeur de Boissons Connecté

Ce projet a pour but de créer un **distributeur de boissons connecté** et contrôlable via un **site web** hébergé sur un **Raspberry Pi 3**. Il est développé dans le cadre d’un projet étudiant à l’université.

---

## 🔧 Description du système

Le distributeur est constitué des éléments suivants :

- **6 pompes** pour distribuer différents liquides
- **1 Arduino Mini** pour contrôler les pompes
- **1 Raspberry Pi 3** qui :
  - héberge un **serveur Node.js**
  - expose une **interface web** en local (accès via une tablette 1280×800)
  - communique avec l’Arduino via une liaison **série**

---

## 🖥️ Interface utilisateur

L'interface est conçue avec **Figma**, puis développée en **HTML/CSS/JS** (version fixe, optimisée pour une tablette 1280×800).

Fonctionnalités de l’interface :

- Sélection des boissons
- Configuration des quantités
- Déclenchement de la distribution
- UX fluide adaptée à la tablette

---

## 🔌 Communication Arduino <-> Raspberry Pi 3

Le **Raspberry Pi 3** communique avec l’**Arduino Mini** via une **liaison série**.  
L’Arduino reçoit les instructions de distribution et actionne les pompes en conséquence.

---

## 🛠️ Technologies utilisées

- 🧠 **Figma** : Maquette de l’interface
- 🌐 **HTML/CSS/JS** : Front-end du site
- 🟩 **Node.js** : Serveur web local embarqué
- 🔌 **Arduino (C/C++)** : Contrôle des pompes
- 🐧 **Linux (RaspberryPiOS + yay)** : Environnement de développement
- 📱 **Tablette 1280×800** : Support d’affichage de l’interface

---

## 📌 Objectifs du projet

- 🎯 Fournir un projet fonctionnel, stable et intuitif
- 🌍 Proposer une interface web épurée et simple d’utilisation
- 🔧 Maintenir un code clair, structuré et facilement déployable
- 📦 Permettre une utilisation lors d’événements ou en démonstration

---

## 📅 Statut

🛠️ Projet actuellement **en cours de développement**.

🎉 Incroyable ce projet !!!
---

