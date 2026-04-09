/**
 * @file generateur_save.h
 * @brief Définition de la classe GenerateurSave (Générateur PWM).
 */

#ifndef GENERATEUR_SAVE_H
#define GENERATEUR_SAVE_H

#include <iostream>
#include <vector>
#include <string>
#include "prise.h"
#include "donnees_borne.h"

class Prise;
class Voyants;

/**
 * @class GenerateurSave
 * @brief Gère le signal PWM et la machine à états de la charge (MEF).
 * * Modifie le signal PWM envoyé au véhicule (+12V, +9V, PWM) et lit la 
 * tension de retour pour déduire l'état du véhicule.
 */
class GenerateurSave
{
    private:
        entrees* io;        /**< Pointeur vers la mémoire partagée */
        Prise& prise;       /**< Référence vers la prise (verrouillage/LEDs) */
        Voyants& voyants;   /**< Référence vers les voyants de la borne */

        const float V_12_OUVERT  = 12.0; /**< Tension d'état A : véhicule non connecté */
        const float V_9_ATTENTE  = 9.0;  /**< Tension d'état B : véhicule connecté, attente charge */
        const float V_6_CHARGE   = 6.0;  /**< Tension d'état C/D : véhicule en charge */

    public:
        /**
         * @brief Constructeur du générateur de signaux.
         * @param io Pointeur vers les I/O de la borne.
         * @param prise Référence vers l'objet Prise.
         * @param voyants Référence vers l'objet Voyants.
         */
        GenerateurSave(entrees* io, Prise& prise, Voyants& voyants);

        /**
         * @brief Génère un signal PWM spécifique.
         * @param type Le type de signal ("DC", "AC", ou "AC_VAR").
         */
        void generer_PWM(char* type);

        /**
         * @brief Lit la tension actuelle retournée par le véhicule.
         * @return La tension en Volts (flottant).
         */
        float tension() const;

        /**
         * @brief Ferme le contacteur de puissance AC (démarre le courant de charge).
         */
        void fermer_contacteur_AC();

        /**
         * @brief Ouvre le contacteur de puissance AC (arrête le courant de charge).
         */
        void ouvrir_contacteur_AC();

        /**
         * @brief Coupe le signal du générateur.
         */
        void deconnecter();

        /**
         * @brief Machine à États Finis (MEF) gérant les transitions selon la tension.
         */
        void mef();

        /**
         * @brief Cycle principal de recharge d'un véhicule.
         * @param numero_client Numéro du client autorisé pour cette session (pour sécuriser le stop).
         */
        void charger(int numero_client);
};

#endif // GENERATEUR_SAVE_H