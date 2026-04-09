/**
 * @file boutons.h
 * @brief Définition de la classe Boutons pour la gestion des interactions utilisateur.
 */

#ifndef BOUTONS_H
#define BOUTONS_H

#include "donnees_borne.h"

/**
 * @class Boutons
 * @brief Interface avec les boutons physiques de la borne.
 * * Gère la lecture de l'état des boutons "Charge" et "Stop" via la mémoire partagée.
 */
class Boutons {
    private:
        entrees* io; /**< Pointeur vers la mémoire partagée des entrées/sorties de la borne */
        
    public :
        /**
         * @brief Constructeur de la classe Boutons.
         * @param io Pointeur vers les I/O.
         */
        Boutons(entrees* io);

        /**
         * @brief Vérifie si le bouton "Charge" a été pressé.
         * * Si le bouton est pressé, son état est réarmé (remis à 0) informatiquement.
         * @return 1 si le bouton a été pressé, 0 sinon.
         */
        int charge();

        /**
         * @brief Vérifie si le bouton "Stop" a été pressé.
         * * Si le bouton est pressé, son état est réarmé (remis à 0) informatiquement.
         * @return 1 si le bouton a été pressé, 0 sinon.
         */
        int stop();
};

#endif // BOUTONS_H