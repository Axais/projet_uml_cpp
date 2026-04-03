#include "prise.h"

Prise::Prise(entrees* io) : io(io) {
    // Initialisation par défaut
    if (io != nullptr) {
        io->led_prise = OFF;
        io->led_trappe = OFF; 
    }
}

void Prise::set_prise(led couleur) {
    if (io != nullptr) {
        io->led_prise = couleur;
    }
}

void Prise::verrouiller_trappe() {
    if (io != nullptr) {
        io->led_trappe = OFF;
        std::cout << "Trappe VERROUILLEE\n";
    }
}

void Prise::deverrouiller_trappe() {
    if (io != nullptr) {
        io->led_trappe = VERT;
        std::cout << "Trappe DEVERROUILLEE\n";
    }
}