#ifndef MOTEUR_H
#define MOTEUR_H

#include <Arduino.h>

enum class direction : uint8_t
{
    AVANT,
    ARRIERE
};
enum class etat_moteur : uint8_t
{
    ETEINT,
    ALLUME
};

class Moteur
{
private:
    uint8_t m_pin_A, m_pin_B;
    uint32_t m_temps_arret;
public:
    Moteur(uint8_t pin_A, uint8_t pin_B);

    ~Moteur();

    /**
     * Allume le moteur
     *
     * @param direction La direction du moteur
     * @param time Temps pendant lequel le moteur restera allumé (en ms)
     */
    void allumer_moteur(direction direction, uint16_t time);
    void arreter_moteur();

    void update();

private:
    Moteur() = delete;
};

#endif