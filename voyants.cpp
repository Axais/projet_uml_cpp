/**
 * @file voyants.cpp
 * @brief Implémentation des méthodes de la classe Voyants.
 */
#include "voyants.h"
#include <iostream>
#include <unistd.h> // Pour usleep

Voyants::Voyants(entrees* io) : io(io) {
    if (io != nullptr) {
        depart_timer_voyants = io->timer_sec;
    }
}

/**
 * @note Le clignotement est géré via un modulo sur le timer système, 
 * avec un délai (usleep) de 100ms.
 */
void Voyants::blink_charge() {
    if (io == nullptr) return;
    if (((io->timer_sec - depart_timer_voyants) % 2) == 0) {
        io->led_charge = VERT; 
    } else {
        io->led_charge = OFF;
    }
    usleep(100000); 
}

/**
 * @note Utilise le même principe de modulo que blink_charge().
 */
void Voyants::blink_defaut() {
    if (io == nullptr) return;
    if (((io->timer_sec - depart_timer_voyants) % 2) == 0) {
        io->led_defaut = ROUGE;
    } else {
        io->led_defaut = OFF;
    }
    usleep(100000);
}

void Voyants::set_charge() {
    if (io == nullptr) return;
    
    if (io->bouton_charge == 1) {
        io->led_charge = VERT;
    } else {
        io->led_charge = OFF;
    }
}

void Voyants::set_dispo() {
    if (io == nullptr) return;
    if (carte_inseree()) {
        io->led_dispo = OFF;
    } else {
        io->led_dispo = VERT;
    }
}

int Voyants::dispo() {
    return carte_inseree();
}