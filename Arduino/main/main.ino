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
 * - Une fois la commande reçue, la ou les pompes sont activées pour la durée spécifiée par le volume à
 *   distribuer. Le volume est converti en une durée d'activation (0 à 100% du temps de remplissage
 *   maximum défini).
 * - Une fois le volume de liquide distribué, les pompes sont arrêtées.
 *
 * Format des données reçues :
 * Les commandes envoyées au système doivent suivre un format spécifique. Chaque commande doit être
 * une chaîne de caractères qui contient les informations suivantes :
 * 1. Un caractère 'V' suivi d'un nombre représentant le volume de liquide à distribuer (en pourcentage).
 * 2. Un caractère 'P' suivi du numéro de la pompe (un nombre entre 1 et 6).
 *
 * Exemple de commande :
 * - "V50P2" signifie : Distribuer 50% du volume à la pompe 2.
 * - "V100P1" signifie : Distribuer 100% du volume à la pompe 1.
 * - "V30P4" signifie : Distribuer 30% du volume à la pompe 4.
 *
 * Le volume est exprimé en pourcentage, avec 100% correspondant à la durée maximale de remplissage
 * de 5 secondes (²à définir) (dureeMaxRemplissage). Le programme peut traiter plusieurs commandes successivement,
 * en s'assurant de toujours arrêter toutes les pompes après chaque activation.
 */

#include "Moteur.h"

#define LONGUEUR_MIN_COMMANDE 4
#define NOMBRE_DE_POMPES 6

Moteur moteur1 = Moteur(6,7);

void setup()
{
    Serial.begin(9600);
    delay(1000);
    moteur1.allumer_moteur(direction::AVANT, 1000);
}

void loop()
{
    if(Serial.available() > LONGUEUR_MIN_COMMANDE)
    {
        /**
         * uint16_t car le maximum représentable en décimal sur 3 chiffres est 999 et
         * 999 > 255 donc on évite un éventuel faux positif à cause d'un overflow.
         */
        uint16_t volume = 0;
        uint8_t pompe = 0;

        if(Serial.read() == 'V')
        {
            uint8_t i = 0;

            while(isdigit(Serial.peek()) && i++ < 3)
                volume = volume * 10 + (uint8_t)Serial.read() - '0';

            if(volume <= 100 && Serial.peek() == 'P')
            {
                Serial.read();

                if(isDigit(Serial.peek()))
                {
                    pompe = (uint8_t)Serial.read() - '0';

                    if(pompe <= NOMBRE_DE_POMPES)
                    {
                        //commande pompe
                        Serial.print(F("Volume: "));
                        Serial.print(volume);
                        Serial.print(F("%\nPompe: "));
                        Serial.println(pompe);
                        Serial.println();
                    }
                }
            }
        }
    }
    moteur1.update();
}