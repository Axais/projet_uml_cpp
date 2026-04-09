/**
 * @file generateur_save.cpp
 * @brief Implémentation de la classe GenerateurSave.
 * * Contient la logique principale de contrôle de charge, d'attente
 * des signaux de tension et la sécurité d'arrêt (bouton stop).
 */
#include "generateur_save.h"
#include "voyants.h"
#include "lecteurcarte.h"
#include <string>
#include <unistd.h>

GenerateurSave::GenerateurSave(entrees* io, Prise& prise, Voyants& voyants)
    : io(io), prise(prise), voyants(voyants) 
{
}

void GenerateurSave::generer_PWM(char* type) {

    std :: string dc = "DC";
    std :: string ac = "AC";
    std :: string ac_var = "AC_VAR";

    if (io == nullptr) return;
    
    if (type == dc) {
        io->gene_pwm = DC;
    } else if (type == ac) {
        io->gene_pwm = AC_1K;
    } else if (type == ac_var) {
        io->gene_pwm = AC_CL;
    }
}

float GenerateurSave::tension() const {
    return (io != nullptr) ? io->gene_u : 0.0;
}

void GenerateurSave::ouvrir_contacteur_AC() {
    if (io != nullptr) io->contacteur_AC = 0;
}

void GenerateurSave::fermer_contacteur_AC() {
    if (io != nullptr) io->contacteur_AC = 1;
}

void GenerateurSave::deconnecter() {
    if (io != nullptr) io->gene_pwm = STOP;
}

/**
 * @note Implémente la logique d'état des tensions de la norme de charge : 
 * 12V (Attente), 9V (Connecté), 6V (En charge).
 */
void GenerateurSave::mef() {
    float t = tension();

    // ETAT A : Attente véhicule (12V) - Tolérance ajoutée
    if (t > 11.0 && t < 13.0 && io->gene_pwm == DC) {
        voyants.set_dispo(); 
    }
    // ETAT B : Véhicule branché (9V) - Tolérance ajoutée
    else if (t > 8.0 && t < 10.0 && io->gene_pwm == DC) {
        std::cout << "\nVoiture branchee (9V). Preparation...\n";
        prise.set_prise(VERT);
        prise.verrouiller_trappe();
        generer_PWM((char*)"AC");
    }
    // ETAT C & D : Charge en cours (6V) - Tolérance ajoutée
    else if (t > 5.0 && t < 7.0 && io->gene_pwm == AC_1K) {
        std::cout << "\nDemarrage de la charge (6V)...\n";
        fermer_contacteur_AC();
        generer_PWM((char*)"AC_VAR");
        io->led_charge = VERT; 
        io->led_dispo = OFF;
    }
}

/**
 * @note Boucle principale de charge. Surveille le bouton stop et 
 * la tension pour détecter la fin de charge. Demande une 
 * re-validation de la carte pour débrancher.
 */
void GenerateurSave::charger(int numero_client) { // <-- Ajout du paramètre
    int execution = 1;
    
    if (io != nullptr) {
        generer_PWM((char*)"DC");
        prise.deverrouiller_trappe();
        std::cout << "\nTrappe ouverte\n";
    }

    while (execution) {
        if (io->bouton_stop == 1) {
            std::cout << "\nBouton STOP appuye\n";
            prise.verrouiller_trappe();
            io->gene_pwm = STOP;
            io->bouton_stop = 0;
            std::cout << "\n--> Veuillez vous identifier avec la MEME carte pour reprendre la recharge.\n";
            // --- DEBUT DE LA VERIFICATION ---
            bool carte_valide = false;
            while (!carte_valide) {
                attente_insertion_carte();
                int numero_lu = lecture_numero_carte();

                if (numero_lu == numero_client) {
                    std::cout << "Authentification reussie\n";
                    std::cout << "Veuillez retirer la carte\n";
                    attente_retrait_carte();
                    carte_valide = true;
                    io->gene_pwm = DC;
                } else {
                    std::cout << "Carte differente. Veuillez inserer la carte initiale.\n";
                }
                attente_retrait_carte();
            }
            // --- FIN DE LA VERIFICATION ---
            io->bouton_stop = 0; // On réarme le bouton
             // On sort de la boucle pour arrêter la charge définitivement
        }
        
        if (tension() > 8.0 && tension() < 10.0 && io->gene_pwm == AC_CL) {
            std::cout << "\nFin de charge detectee\n";
            break; 
        }
        
        mef();
        usleep(100000); 
    }
    
    std::cout << "\nArret du processus...\n";
    std::cout << "\n--> Veuillez vous identifier avec la MEME carte pour reprendre votre vehicule.\n";
    bool carte_valide = false;

    while(!carte_valide){
    attente_insertion_carte();
    int numero_lu = lecture_numero_carte();
    if (numero_lu == numero_client) {
                    std::cout << "Authentification reussie\n";
                    std::cout << "Veuillez retirer la carte\n";
                    attente_retrait_carte();

    ouvrir_contacteur_AC();
    generer_PWM((char*)"DC");
 
    if (io != nullptr) {
        io->led_charge = OFF;
        prise.set_prise(OFF);
        prise.deverrouiller_trappe();
        voyants.set_dispo(); 
    } 

    }else {
        std::cout << "Carte differente. Veuillez inserer la carte initiale.\n";
                    attente_retrait_carte();

    }
}
    
}