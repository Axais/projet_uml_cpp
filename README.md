# Borne de recharge de véhicule électrique — version C++

Reprise en conception objet du projet de borne de recharge : mêmes fonctions que la
version C, mais une classe par élément de la borne, avec les dépendances injectées
par référence à la construction. Le code est documenté au format Doxygen.

## Classes

| Classe | Rôle |
|---|---|
| `BaseClients` | collection de `Client`, authentification et reprise de charge |
| `Client` | prénom, nom, identifiant et numéro de badge |
| `LecteurCarte` | lecture du badge, déroulement d'une session ; agrège `BaseClients`, `Voyants`, `Timer` et `GenerateurSave` |
| `Voyants` | voyants disponible / charge / défaut, y compris les clignotements |
| `Timer` | temps de référence et durée écoulée depuis la dernière remise à zéro |
| `Prise` | verrouillage de la trappe et LED de la prise |
| `Boutons` | lecture des boutons charge et stop |
| `GenerateurSave` | génération du PWM, contacteur AC, mesure de tension, mise en sécurité |

Chaque classe reçoit à la construction le pointeur `entrees*` vers la mémoire
partagée qui représente les entrées / sorties physiques de la borne, obtenu dans
`borne.cpp` par `acces_memoire()`.

## Compilation

Comme la version C, le projet dépend de l'environnement de TP : `memoire_borne.h`
et `donnees_borne.h` proviennent de `/shared/TCii/include`. Il se compile sur les
machines de la salle de TP.

```bash
touch Makefile.dep
make depend
make
./borne
```

## Voir aussi

La version procédurale en C : [projetuml-borne](https://github.com/Axais/projetuml-borne).
