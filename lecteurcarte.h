/**
 * @file lecteurcarte.h
 * @brief Définition de la classe LecteurCarte pour la gestion du matériel RFID.
 */

#ifndef LECTEURCARTE_H
#define LECTEURCARTE_H

#include <lcarte.h>
#include <donnees_borne.h>
#include "baseclients.h"
#include "voyants.h" 
#include "timer.h"  

class Voyants; 
class Timer;  
class GenerateurSave; 

/**
 * @class LecteurCarte
 * @brief Interface avec le lecteur de carte de la borne.
 * * Cette classe interagit avec le matériel pour lire les cartes RFID, 
 * valider les clients auprès de la base et lancer les processus de charge.
 */
class LecteurCarte
{
  private :
    entrees* io;                    /**< Pointeur vers la mémoire partagée des entrées/sorties */
    BaseClients& baseClients;       /**< Référence vers la base de clients */
    Voyants& voyants;               /**< Référence vers le gestionnaire des voyants */
    Timer& timer;                   /**< Référence vers le timer de la borne */
    GenerateurSave& generateur;     /**< Référence vers le générateur PWM pour lancer la charge */

  public : 
    /**
     * @brief Constructeur de la classe LecteurCarte.
     * @param shared_io Pointeur vers les I/O de la borne.
     * @param bc Référence vers la base de clients.
     * @param v Référence vers les voyants.
     * @param t Référence vers le timer.
     * @param g Référence vers le générateur.
     */
    LecteurCarte(entrees* shared_io, BaseClients& bc, Voyants& v, Timer& t, GenerateurSave& g);
    
    /**
     * @brief Initialise les ports de communication avec le lecteur de carte.
     */
	void initialiser();

    /**
     * @brief Attend et lit une carte insérée, puis traite l'authentification et la charge.
     */
	void lire_carte();

    /**
     * @brief Interface permettant de lire une carte pour associer un nouveau client.
     */
    void ajouter_client(); 
};

#endif // LECTEURCARTE_H