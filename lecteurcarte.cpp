#include "lecteurcarte.h"
#include "generateur_save.h"
#include <iostream>
#include <unistd.h> 

LecteurCarte::LecteurCarte(entrees* shared_io, BaseClients& bc, Voyants& v, Timer& t, GenerateurSave& g)
    : io(shared_io), baseClients(bc), voyants(v), timer(t), generateur(g) 
{
}

void LecteurCarte::initialiser()
{
    initialisations_ports();
}

void LecteurCarte::lire_carte()
{
    std::cout << "En attente de l'insertion d'une carte...\n";
    attente_insertion_carte();
    
    int numero = lecture_numero_carte();
    std::cout << "Numero de carte lue: " << numero << std::endl;
    
    if (carte_inseree()) {
        if(baseClients.authentifier(numero) == 1){
            std::cout << "Authentification réussie.\n";            
            std::cout << "--> Veuillez appuyer sur le bouton CHARGE du simulateur.\n";
            
            // On attend que l'utilisateur clique sur le bouton "Charge"
            while (io->bouton_charge == 0) {
                usleep(100000); // Pause de 100ms
            }
            io->bouton_charge = 0; // On réarme le bouton après l'avoir lu

            std::cout << "--> Veuillez retirer votre carte.\n";
            attente_retrait_carte();
            generateur.charger(numero); 

        } else {
            std::cout << "Authentification échouée\n";
            attente_retrait_carte();
        }
    }
}
void LecteurCarte::ajouter_client()
{
    std::string p, n;
    std::cout << "\n=== CREATION D'UN NOUVEAU CLIENT ===\n";
    std::cout << "Prenom : "; 
    std::cin >> p;
    std::cout << "Nom : "; 
    std::cin >> n;

    std::cout << "\n--> Veuillez INSERER la nouvelle carte dans le lecteur...\n";
    attente_insertion_carte();
    
    int numero = lecture_numero_carte();
    std::cout << "Numero de carte lu : " << numero << "\n";
    
    std::cout << "--> Veuillez RETIRER la carte.\n";
    attente_retrait_carte();

    baseClients.nouveauClient(p, n, std::to_string(numero));
}