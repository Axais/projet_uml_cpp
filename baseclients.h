/**
 * @file baseclients.h
 * @brief Définition de la classe BaseClients gérant la base de données.
 */

#ifndef BASE_CLIENTS_H
#define BASE_CLIENTS_H

#include <iostream>
#include <string>
#include <vector>
#include "client.h"

/**
 * @class BaseClients
 * @brief Gestionnaire de la liste des clients autorisés.
 * * Permet d'authentifier les utilisateurs, de gérer la reprise de charge,
 * ainsi que d'ajouter ou supprimer des clients de la base.
 */
class BaseClients {
private:
    std::vector<Client> clients; /**< Vecteur contenant la liste de tous les clients enregistrés */

public:
    /**
     * @brief Constructeur par défaut. Initialise une base avec quelques clients par défaut.
     */
    BaseClients();

    /**
     * @brief Authentifie un client à partir de son numéro de carte.
     * @param numero_carte Le numéro lu sur la carte RFID.
     * @return 1 si le client est authentifié, -1 sinon.
     */
    int authentifier(int numero_carte);

    /**
     * @brief Vérifie si la carte présentée correspond à un client en cours de charge.
     * @param numero_carte Le numéro de la carte présentée pour la reprise.
     * @return 1 si la reprise est autorisée, -1 sinon.
     */
    int reprise(int numero_carte);

    /**
     * @brief Ajoute un nouveau client à la base.
     * @param prenom Prénom du nouveau client.
     * @param nom Nom du nouveau client.
     * @param id_client Identifiant ou numéro de carte du client.
     */
    void nouveauClient(const std::string& prenom, const std::string& nom, const std::string& id_client);

    /**
     * @brief Supprime un client de la base de données.
     * @param id_client Identifiant du client à supprimer.
     */
    void supprimerClient(const std::string& id_client);
};

#endif // BASE_CLIENTS_H