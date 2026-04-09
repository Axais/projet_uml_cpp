/**
 * @file timer.h
 * @brief Définition de la classe Timer pour la gestion du temps.
 */

#ifndef TIMER_H
#define TIMER_H
#include "donnees_borne.h"

/**
 * @class Timer
 * @brief Chronomètre de la borne de recharge.
 * * Permet de mesurer le temps écoulé depuis un instant donné, utile 
 * pour le clignotement des voyants ou la durée de la charge.
 */
class Timer {
private:
    entrees* io;        /**< Pointeur vers la mémoire partagée contenant l'horloge système */
    int depart_timer;   /**< Valeur du temps de référence enregistrée lors de la dernière mise à zéro */

public:
    /**
     * @brief Constructeur de la classe Timer.
     * @param io Pointeur vers les I/O.
     */
    Timer(entrees* io);

    /**
     * @brief Remet le chronomètre à zéro.
     * * Enregistre l'instant actuel comme nouvelle référence temporelle.
     */
    void raz();

    /**
     * @brief Calcule et affiche le temps écoulé.
     * @return Le temps écoulé en secondes depuis la dernière remise à zéro.
     */
    int valeurs();
};

#endif // TIMER_H