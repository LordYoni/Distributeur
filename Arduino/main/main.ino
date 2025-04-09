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
 */
 
// Déclaration des bibliothèques nécessaires
#include "Moteur.h"
//Instanciation des moteurs

Moteur moteur1(2,3);


void setup()
{
    Serial.begin(9600);
    delay(1000);
    moteur1.allumer_moteur(direction::AVANT, 1000);
}

void loop()
{
    moteur1.update();
}