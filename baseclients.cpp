#include "baseclients.h"

BaseClients::BaseClients() {
    clients.push_back(Client("Jean", "Moreau", "3141"));
    clients.push_back(Client("Isabelle", "Durant", "1121"));
    clients.push_back(Client("Fleur", "Deschamps", "9101"));
}

int BaseClients::authentifier(int numero_carte) {
    for (auto& client : clients) {
        if (std::stoi(client.id_client) == numero_carte) {
            client.badge = numero_carte;
            return 1;
        }
    }
    return -1;
}

int BaseClients::reprise(int numero_carte) {
    for (auto& client : clients) {
        if (client.badge == numero_carte) {
            client.badge = 0;
            return 1;
        }
    }
    return -1;
}

void BaseClients::nouveauClient(const std::string& prenom, const std::string& nom, const std::string& id_client) {
    clients.push_back(Client(prenom, nom, id_client));
    std::cout << "Client ajoute. Nombre total : " << clients.size() << std::endl;
}

void BaseClients::supprimerClient(const std::string& id_client) {
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if (it->id_client == id_client) {
            clients.erase(it);
            std::cout << "Client " << id_client << " supprime." << std::endl;
            return;
        }
    }
    std::cout << "Client non trouve." << std::endl;
}