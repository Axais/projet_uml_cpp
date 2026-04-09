/**
 * @file client.h
 * @brief Définition de la classe Client.
 */

#ifndef CLIENT_H
#define CLIENT_H    

#include <iostream>
#include <string>

/**
 * @class Client
 * @brief Représente un client de la borne de recharge.
 * * Cette classe stocke les informations personnelles d'un client ainsi que 
 * l'identifiant de son badge RFID.
 */
class Client {
    public:
        std::string prenom;     /**< Prénom du client */
        std::string nom;        /**< Nom du client */
        std::string id_client;  /**< Identifiant unique du client */
        int badge;              /**< Numéro du badge associé au client (0 si non badgé) */

        /**
         * @brief Constructeur de la classe Client.
         * @param p Prénom du client.
         * @param n Nom du client.
         * @param id Identifiant unique du client sous forme de chaîne.
         * @param b Numéro du badge (par défaut 0).
         */
        Client(std::string p, std::string n, std::string id, int b = 0) 
            : prenom(p), nom(n), id_client(id), badge(b) {}
};

#endif // CLIENT_H