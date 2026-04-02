#ifndef VOYANTS_H 
#define VOYANTS_H

#include "donnees_borne.h"
#include <lcarte.h>

class Voyants {
private:
    entrees* io;
    int depart_timer_voyants;

public:
    Voyants(entrees* io);
    void blink_charge();
    void blink_defaut();
    void set_charge();
    void set_dispo();
    int dispo();
};

#endif // VOYANTS_H