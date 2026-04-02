#ifndef LECTEURCARTE_H
#define LECTEURCARTE_H

#include <lcarte.h>
#include <donnees_borne.h>
#include "baseclients.h"
#include "voyants.h" 
#include "timer.h"  

class Voyants; 
class Timer;  
class GenerateurSave;

class LecteurCarte
{
  private :
    entrees* io;
    BaseClients& baseClients;
    Voyants& voyants;
    Timer& timer;
    GenerateurSave& generateur; 

  public : 
    LecteurCarte(entrees* shared_io, BaseClients& bc, Voyants& v, Timer& t, GenerateurSave& g);
    
	void initialiser();
	void lire_carte();
};

#endif // LECTEURCARTE_H