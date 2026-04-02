#ifndef CLIENT_H
#define CLIENT_H    

#include <iostream>
#include <string>

class Client {
    public:
        std::string prenom;
        std::string nom;
        std::string id_client;
        int badge;

        // Constructeur
        Client(std::string p, std::string n, std::string id, int b = 0) 
            : prenom(p), nom(n), id_client(id), badge(b) {}
};

#endif // CLIENT_H