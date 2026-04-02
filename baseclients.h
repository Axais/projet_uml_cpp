#ifndef BASE_CLIENTS_H
#define BASE_CLIENTS_H

#include <iostream>
#include <string>
#include <vector>
#include "client.h"

class BaseClients {
private:
    std::vector<Client> clients;

public:
    BaseClients();
    int authentifier(int numero_carte);
    int reprise(int numero_carte);
    void nouveauClient(const std::string& prenom, const std::string& nom, const std::string& id_client);
    void supprimerClient(const std::string& id_client);
};

#endif // BASE_CLIENTS_H
