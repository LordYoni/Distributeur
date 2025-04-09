
#include "Moteur.h"

#define SC(x) static_cast<uint8_t>(x)

Moteur::Moteur(uint8_t pin_A, uint8_t pin_B)
    : m_pin_A(pin_A), m_pin_B(pin_B), m_temps_arret(0)
{
    // Initialisation des broches
    pinMode(m_pin_A, OUTPUT);
    pinMode(m_pin_B, OUTPUT);

    // Arrêt du moteur
    digitalWrite(m_pin_A, LOW);
    digitalWrite(m_pin_B, LOW);
}

void Moteur::allumer_moteur(direction direction, uint16_t time)
{
    // Allumer le moteur dans la direction spécifiée

    switch (direction)
    {
        case direction::AVANT:
            digitalWrite(m_pin_A, HIGH);
            digitalWrite(m_pin_B, LOW);
            break;

        case direction::ARRIERE:
            digitalWrite(m_pin_A, LOW);
            digitalWrite(m_pin_B, HIGH);
            break;

        default:
            break;
    }
    
    m_temps_arret = time + millis();

}

void Moteur::arreter_moteur()
{
    digitalWrite(m_pin_A, LOW);
    digitalWrite(m_pin_B, LOW);
}

void Moteur::update()
{
    if(m_temps_arret > millis())
        arreter_moteur();
}

Moteur::~Moteur() {}