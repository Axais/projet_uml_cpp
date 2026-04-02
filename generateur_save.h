#ifndef GENERATEUR_SAVE_H
#define GENERATEUR_SAVE_H

#include <iostream>
#include <vector>
#include <string>
#include "prise.h"
#include "donnees_borne.h"


class Prise;
class Voyants;

class GenerateurSave
{
    private:
        entrees* io;
        Prise& prise;
        Voyants& voyants;

        const float V_12_OUVERT  = 12.0;
        const float V_9_ATTENTE  = 9.0;
        const float V_6_CHARGE   = 6.0;

    public:

        GenerateurSave(entrees* io, Prise& prise, Voyants& voyants);
        void generer_PWM(char* type);
        float tension() const;
        void fermer_contacteur_AC();
        void ouvrir_contacteur_AC();
        void deconnecter();
        void mef();
        void charger();
        
};

#endif // GENERATEUR_SAVE_H