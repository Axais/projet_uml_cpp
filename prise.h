/**
 * @file prise.h
 * @brief Gestion de la prise de la borne (Trappe et LEDs).
 */

#ifndef PRISE_H
#define PRISE_H

#include <vector>
#include <iostream>
#include "donnees_borne.h"

/**
 * @class Prise
 * @brief Contrôle physique de la prise du véhicule.
 * * Permet de verrouiller ou déverrouiller la trappe et d'allumer 
 * les LEDs associées à la prise matérielle.
 */
class Prise
{
    private:
        entrees* io; /**< Pointeur vers la mémoire partagée des entrées/sorties */
        
    public:
        /**
         * @brief Constructeur de la classe Prise.
         * @param io Pointeur vers les I/O.
         */
        Prise(entrees* io);

        /**
         * @brief Définit la couleur de la LED de la prise.
         * @param couleur Couleur souhaitée (VERT, ROUGE, OFF...).
         */
        void set_prise(led couleur);

        /**
         * @brief Verrouille la trappe de la prise pour sécuriser le câble.
         */
        void verrouiller_trappe();

        /**
         * @brief Déverrouille la trappe de la prise.
         */
        void deverrouiller_trappe();
};

#endif //PRISE_H