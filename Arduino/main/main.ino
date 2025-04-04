/** 
 * Programme de contrôle de distributeur de boissons avec 6 pompes.
 *
 * Objectif : 
 * Ce programme permet de contrôler 6 pompes pour un système de distribution de boissons. Les pompes
 * sont activées ou désactivées en fonction des commandes reçues via la communication série. La durée
 * d'activation des pompes dépend du volume de liquide à distribuer, qui est exprimé en pourcentage.
 *
 * Fonctionnement :
 * - Lorsqu'une commande est reçue via le port série, elle est traitée pour extraire les informations
 *   nécessaires (volume et pompe à activer).
 * - Le programme attend un caractère de nouvelle ligne ('\n') pour signaler la fin d'une commande.
 * - Une fois la commande reçue, les pompes sont activées pour la durée spécifiée par le volume à
 *   distribuer. Le volume est converti en une durée d'activation (0 à 100% du temps de remplissage
 *   maximum défini).
 * - Une fois le volume de liquide distribué, toutes les pompes sont arrêtées.
 *
 * Format des données reçues :
 * Les commandes envoyées au système doivent suivre un format spécifique. Chaque commande doit être
 * une chaîne de caractères qui contient les informations suivantes :
 * 1. Un caractère 'V' suivi d'un nombre représentant le volume de liquide à distribuer (en pourcentage).
 * 2. Un caractère 'P' suivi du numéro de la pompe (un nombre entre 1 et 6).
 * 
 * Exemple de commande :
 * - "V50P2\n" signifie : Distribuer 50% du volume à la pompe 2.
 * - "V100P1\n" signifie : Distribuer 100% du volume à la pompe 1.
 * - "V30P4\n" signifie : Distribuer 30% du volume à la pompe 4.
 * 
 * Le volume est exprimé en pourcentage, avec 100% correspondant à la durée maximale de remplissage
 * de 5 secondes ( à définir) (dureeMaxRemplissage). Le programme peut traiter plusieurs commandes successivement,
 * en s'assurant de toujours arrêter toutes les pompes après chaque activation.
 *
 *
 */

 #include <Arduino.h>

 // Déclaration des broches pour chaque pompe (chaque pompe utilise deux broches)
 const int IN1 = 4;  // Pompe 1 - Broche 1
 const int IN2 = 5;  // Pompe 1 - Broche 2
 const int IN3 = 6;  // Pompe 2 - Broche 1
 const int IN4 = 7;  // Pompe 2 - Broche 2
 const int IN5 = 8;  // Pompe 3 - Broche 1
 const int IN6 = 9;  // Pompe 3 - Broche 2
 const int IN7 = 10; // Pompe 4 - Broche 1
 const int IN8 = 11; // Pompe 4 - Broche 2
 const int IN9 = A0; // Pompe 5 - Broche 1
 const int IN10 = A1; // Pompe 5 - Broche 2
 const int IN11 = A2; // Pompe 6 - Broche 1
 const int IN12 = A3; // Pompe 6 - Broche 2
 
 // Configuration
 const int dureeMaxRemplissage = 5000; // Durée maximale pour remplir à 100% (en millisecondes)
 char commande[50]; // Tableau pour stocker la commande reçue
 int indexCommande = 0; // Index pour parcourir la commande
 
 // Structures pour gérer les états des pompes
 struct Pompe {
     int broche1;
     int broche2;
     unsigned long tempsFin;  // Temps de fin d'activation
     bool active;  // Etat de la pompe
 };
 
 Pompe pompes[6] = {
     {IN1, IN2, 0, false},
     {IN3, IN4, 0, false},
     {IN5, IN6, 0, false},
     {IN7, IN8, 0, false},
     {IN9, IN10, 0, false},
     {IN11, IN12, 0, false}
 };
 
 void setup() {
     Serial.begin(9600); // Initialisation de la communication série
 
     // Configuration de toutes les broches en mode sortie
     pinMode(IN1, OUTPUT);
     pinMode(IN2, OUTPUT);
     pinMode(IN3, OUTPUT);
     pinMode(IN4, OUTPUT);
     pinMode(IN5, OUTPUT);
     pinMode(IN6, OUTPUT);
     pinMode(IN7, OUTPUT);
     pinMode(IN8, OUTPUT);
     pinMode(IN9, OUTPUT);
     pinMode(IN10, OUTPUT);
     pinMode(IN11, OUTPUT);
     pinMode(IN12, OUTPUT);
 
     arreterToutesLesPompes(); // Assure que toutes les pompes sont arrêtées au démarrage
 }
 
 void loop() {
     // Vérifie si des données sont disponibles sur le port série
     if (Serial.available()) {
         char c = Serial.read(); // Lit un caractère depuis le port série
         if (c == '\n') { // Si le caractère est une nouvelle ligne, la commande est complète
             commande[indexCommande] = '\0'; // Termine la chaîne de caractères
             traiterCommande(commande); // Traite la commande reçue
             indexCommande = 0; // Réinitialise l'index pour la prochaine commande
         } else {
             commande[indexCommande++] = c; // Ajoute le caractère à la commande
         }
     }
 
     // Vérifie l'état de chaque pompe et arrête celles dont le temps est écoulé
     unsigned long currentMillis = millis();
     for (int i = 0; i < 6; i++) {
         if (pompes[i].active && currentMillis >= pompes[i].tempsFin) {
             // Si la pompe a dépassé son temps, l'arrêter
             digitalWrite(pompes[i].broche1, LOW);
             digitalWrite(pompes[i].broche2, LOW);
             pompes[i].active = false;
         }
     }
 }
 
 void traiterCommande(char *cmd) {
     // Arrête toutes les pompes avant de traiter une nouvelle commande
     for (int i = 0; i < 6; i++) {
         pompes[i].active = false;  // Marque toutes les pompes comme non actives
         digitalWrite(pompes[i].broche1, LOW);  // Désactive la pompe
         digitalWrite(pompes[i].broche2, LOW);  // Désactive la pompe
     }
 
     int volume = 0, pompe = 0; // Variables pour stocker le volume et le numéro de pompe
     int i = 0; // Index pour parcourir la commande
 
     // Parcourt la commande pour extraire les informations
     while (cmd[i] != '\0') {
         if (cmd[i] == 'V') { // Si le caractère est 'V', commence à lire le volume
             i++; // Passe au caractère suivant
             volume = 0;
             // Extrait le nombre correspondant au volume
             while (cmd[i] >= '0' && cmd[i] <= '9') {
                 volume = volume * 10 + (cmd[i] - '0');
                 i++;
             }
 
             if (cmd[i] == 'P') { // Si le caractère est 'P', commence à lire le numéro de pompe
                 i++; // Passe au caractère suivant
                 pompe = 0;
                 // Extrait le nombre correspondant au numéro de pompe
                 while (cmd[i] >= '0' && cmd[i] <= '9') {
                     pompe = pompe * 10 + (cmd[i] - '0');
                     i++;
                 }
 
                 // Calcule la durée d'activation en fonction du volume
                 int duree = map(volume, 0, 100, 0, dureeMaxRemplissage);
                 activerPompe(pompe - 1, duree); // Active la pompe correspondante pour la durée calculée
             }
         } else {
             i++; // Passe au caractère suivant si ce n'est pas 'V'
         }
     }
 }
 
 void activerPompe(int pompeIndex, int duree) {
     // Vérifie si le numéro de la pompe est valide
     if (pompeIndex >= 0 && pompeIndex < 6) {
         // Active la pompe
         digitalWrite(pompes[pompeIndex].broche1, HIGH);
         digitalWrite(pompes[pompeIndex].broche2, LOW);
         pompes[pompeIndex].tempsFin = millis() + duree; // Définit le temps de fin de l'activation
         pompes[pompeIndex].active = true; // Marque la pompe comme active
     }
 }
 
 void arreterToutesLesPompes() {
     // Désactive toutes les broches associées aux pompes
     for (int i = 0; i < 6; i++) {
         digitalWrite(pompes[i].broche1, LOW); // Met chaque broche à LOW pour arrêter les pompes
         digitalWrite(pompes[i].broche2, LOW); // Met chaque broche à LOW pour arrêter les pompes
         pompes[i].active = false;  // Marque toutes les pompes comme non actives
     }
 }

 
 //fait avec cahtGPT pour l'instant pour init le repo 