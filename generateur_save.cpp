#include "generateur_save.h"
#include "voyants.h"
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

void GenerateurSave::mef() {
    float t = tension();

    // ETAT A : Attente véhicule (12V) - On maintient juste le voyant
    if (t > 11.0 && t < 13.0 && io->gene_pwm == DC) {
        voyants.set_dispo(); 
    }
    // ETAT B : Véhicule branché (9V)
    else if (t > 8.0 && t < 10.0 && io->gene_pwm == DC) {
        std::cout << "\n[Detection] Voiture branchee (9V). Preparation..." << std::endl;
        prise.set_prise(VERT);
        prise.verrouiller_trappe();
        generer_PWM((char*)"AC"); // On envoie le signal AC 1kHz
    }
    // ETAT C & D : Charge en cours (6V)
    else if (t > 5.0 && t < 7.0 && io->gene_pwm == AC_1K) {
        std::cout << "\n[Charge] Demarrage de la charge (6V)..." << std::endl;
        fermer_contacteur_AC();
        generer_PWM((char*)"AC_VAR");
        io->led_charge = VERT; 
        io->led_dispo = OFF;
    }
}

void GenerateurSave::charger() {
    int execution = 1;
    
    // --- DEMARRAGE REEL ---
    if (io != nullptr) {
        generer_PWM((char*)"DC"); // On allume le générateur à 12V !
        prise.deverrouiller_trappe(); // On ouvre la trappe
        std::cout << "\n[Attente] Trappe ouverte." << std::endl;
    }

    while (execution) {
        // Détection du bouton STOP physique
        if (io->bouton_stop == 1) {
            std::cout << "\n[ALERTE] Bouton STOP appuye. Fin de la session.\n";
            io->bouton_stop = 0; 
            break;
        }
        
        // Fin de charge naturelle (si la voiture remonte à 9V)
        if (tension() > 8.0 && tension() < 10.0 && io->gene_pwm == AC_CL) {
            std::cout << "\n[INFO] Fin de charge detectee.\n";
            break; 
        }
        
        mef(); 
        usleep(100000); 
    }
    
    // --- NETTOYAGE ---
    std::cout << "\nArret du processus et liberation de la borne...\n";
    ouvrir_contacteur_AC();
    generer_PWM((char*)"DC"); // On repasse à 12V pour libérer la voiture
    
    if (io != nullptr) {
        io->led_charge = OFF;
        prise.set_prise(OFF);
        prise.deverrouiller_trappe();
        voyants.set_dispo(); 
    }
}