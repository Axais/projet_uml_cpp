/**
 * @file voyants.h
 * @brief Définition de la classe Voyants gérant les signaux lumineux.
 */

#ifndef VOYANTS_H 
#define VOYANTS_H

#include "donnees_borne.h"
#include <lcarte.h>

/**
 * @class Voyants
 * @brief Contrôle les LEDs de la borne de recharge.
 * * Permet d'allumer, d'éteindre ou de faire clignoter les différents voyants 
 * (Charge, Défaut, Disponibilité) pour indiquer l'état du système à l'utilisateur.
 */
class Voyants {
private:
    entrees* io;                /**< Pointeur vers la mémoire partagée */
    int depart_timer_voyants;   /**< Référence temporelle pour gérer les clignotements */

public:
    /**
     * @brief Constructeur de la classe Voyants.
     * @param io Pointeur vers les I/O de la borne.
     */
    Voyants(entrees* io);

    /**
     * @brief Fait clignoter la LED de charge (Vert/Off).
     */
    void blink_charge();

    /**
     * @brief Fait clignoter la LED de défaut (Rouge/Off).
     */
    void blink_defaut();

    /**
     * @brief Allume la LED de charge en vert si le bouton de charge est pressé.
     */
    void set_charge();

    /**
     * @brief Met à jour le voyant de disponibilité de la borne.
     * * S'éteint si une carte est insérée, s'allume en vert sinon.
     */
    void set_dispo();

    /**
     * @brief Vérifie l'état de disponibilité en fonction du lecteur de carte.
     * @return 1 si une carte est présente, 0 sinon.
     */
    int dispo();
};

#endif // VOYANTS_H