#include "generateur_save.h"
#include "voyants.h"
#include <cstring>
#include <unistd.h>

GenerateurSave::GenerateurSave(entrees* io, Prise& prise, Voyants& voyants)
    : io(io), prise(prise), voyants(voyants) 
{
}

void GenerateurSave::generer_PWM(char* type) {
    if (io == nullptr) return;
    
    if (strcmp(type, "DC") == 0) {
        io->gene_pwm = DC;
    } else if (strcmp(type, "AC") == 0) {
        io->gene_pwm = AC_1K;
    } else if (strcmp(type, "AC_VAR") == 0) {
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

    // ETAT A : Attente véhicule
    if (t == V_12_OUVERT) {
        voyants.set_dispo(); 
        prise.deverrouiller_trappe();
        
       
        if (io->gene_pwm != DC) { 
            generer_PWM((char*)"DC");
            std::cout << "\n[Attente] Branchez le vehicule (12V)...\n";
        }
    }
    // ETAT B : Véhicule branché
    else if (t == V_9_ATTENTE && io->gene_pwm == DC) {
        std::cout << "\n[Detection] Vehicule branche (9V).\n";
        prise.set_prise(VERT);
        prise.verrouiller_trappe();
        generer_PWM((char*)"AC");
    }
    // ETAT C & D : Charge en cours
    else if (t == V_6_CHARGE) {
        if (io->gene_pwm == AC_1K) {
            std::cout << "\n[Charge] Demarrage de la charge (6V)...\n";
            fermer_contacteur_AC();
            generer_PWM((char*)"AC_VAR");
            io->led_charge = VERT;
        } 
    }
}

void GenerateurSave::charger() {
    int execution = 1;
    
    
    generer_PWM((char*)"DC"); 

    while (execution) {
        if (io->bouton_stop == 1) {
            std::cout << "\n[ALERTE] Bouton STOP appuye.\n";
            io->bouton_stop = 0;
            break;
        }
        
        if (tension() == V_9_ATTENTE && io->gene_pwm == AC_CL) {
            std::cout << "\n[INFO] Fin de charge detectee.\n";
            break; 
        }
        
        mef();
        usleep(100000); 
    }
    
    std::cout << "\nArret du processus...\n";
    ouvrir_contacteur_AC();
    generer_PWM((char*)"DC");
    io->led_charge = VERT; 
}