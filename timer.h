#ifndef TIMER_H
#define TIMER_H
#include "donnees_borne.h"

class Timer {
private:
    entrees* io;
    int depart_timer;

public:
    Timer(entrees* io);
    void raz();
    int valeurs();
};

#endif // TIMER_H