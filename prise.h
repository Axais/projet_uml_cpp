#ifndef PRISE_H
#define PRISE_H

#include <vector>
#include <iostream>
#include "donnees_borne.h"

class Prise
{
    private:
        entrees* io;
        
    public:
        Prise(entrees* io);
        void set_prise(led couleur);
        void verrouiller_trappe();
        void deverrouiller_trappe();
};


#endif //PRISE_H