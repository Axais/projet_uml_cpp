#include <iostream>
#include <limits>
#include "memoire_borne.h"
#include "donnees_borne.h"
#include "baseclients.h"
#include "lecteurcarte.h"
#include "prise.h"
#include "voyants.h"
#include "timer.h"
#include "generateur_save.h"

int main()
{
    int shmid;
    entrees* io = acces_memoire(&shmid);
    
    if (io == nullptr) {
        std::cerr << "Erreur memoire partagee" << std::endl;
        return -1;
    }

   
    BaseClients baseClients;
    Voyants voyants(io);
    Timer timer(io);
    Prise prise(io);
    GenerateurSave generateur(io, prise, voyants);
    
    LecteurCarte lecteurcarte(io, baseClients, voyants, timer, generateur); 
    lecteurcarte.initialiser();
    
    int choix = 0;
    while (true)
    {
        std::cout << "\n=== MENU BORNE C++ ===\n";
        std::cout << "1. Lire carte\n";
        std::cout << "2. Ajouter un client\n";
        std::cout << "0. Quitter\n";
        std::cout << "Choix : ";
        
        if (!(std::cin >> choix)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choix == 1) {
            lecteurcarte.lire_carte();
            std::cout << "[Simulation Lecture de carte...]\n";
        } else if (choix == 2) {
            std::string p, n, id;
            std::cout << "Prenom: "; std::cin >> p;
            std::cout << "Nom: "; std::cin >> n;
            std::cout << "ID: "; std::cin >> id;
            baseClients.nouveauClient(p, n, id);
        } else if (choix == 0) {
            break;
        }
    }

    liberation_ports();
    return 0;
}