#ifndef BOUTONS_H
#define BOUTONS_H

#include "donnees_borne.h"

class Boutons {
    private:
        entrees* io;
    public :
        Boutons(entrees* io);
        int charge();
        int stop();
};

#endif // BOUTONS_H