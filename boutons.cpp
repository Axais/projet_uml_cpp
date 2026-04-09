/**
 * @file boutons.cpp
 * @brief Implémentation de la classe Boutons.
 */
#include "boutons.h"

Boutons::Boutons(entrees* io) : io(io) {}

int Boutons::charge() {
    if (io != nullptr && io->bouton_charge == 1) {
        io->bouton_charge = 0; 
        return 1;
    }
    return 0;
}

int Boutons::stop() {
    if (io != nullptr && io->bouton_stop == 1) {
        io->bouton_stop = 0;
        return 1;
    }
    return 0;
}