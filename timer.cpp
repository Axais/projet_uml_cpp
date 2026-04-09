/**
 * @file timer.cpp
 * @brief Implémentation de la classe Timer.
 */
#include "timer.h"
#include <iostream>

Timer::Timer(entrees* io) : io(io) {
    if (io != nullptr) {
        depart_timer = io->timer_sec;
    }
}

void Timer::raz() {
    if (io != nullptr) {
        depart_timer = io->timer_sec;
    }
}

int Timer::valeurs() {
    if (io == nullptr) return 0;
    int valeur_timer = io->timer_sec - depart_timer;
    std::cout << "Temps écoulé: " << valeur_timer << " secondes\n";
    return valeur_timer;
}