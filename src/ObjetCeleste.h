/*
 * Planete.h - Fichier header de la classe ObjetCeleste.
 *
 * @auteur Alexis Chretien (CHRA25049209)
 * @version 8 decembre 2017
 */
#ifndef OBJETCELESTE_H
#define OBJETCELESTE_H

#include <random>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <vector>
#include "Vecteur.h"

// Constantes
// Masses en kilogrammes, distances en metres, temps en secondes
const double MASSE_SOLEIL = 1.98855e+30;
const double MASSE_TERRE  = 5.97237e+24;  
const double UNITE_ASTRONOMIQUE = 1.49597870e+11;

const double MASSE_ETOILE_MIN  = 0.5  * MASSE_SOLEIL;
const double MASSE_ETOILE_MAX  = 2    * MASSE_SOLEIL; 
const double MASSE_PLANETE_MIN = 0.05 * MASSE_TERRE;
const double MASSE_PLANETE_MAX = 400  * MASSE_TERRE; 

const double POS_PLANETE_MAX = 50 * UNITE_ASTRONOMIQUE;
const double POS_PLANETE_MIN = -1 * POS_PLANETE_MAX; 

const double CONSTANTE_GRAVITATIONNELLE = 6.6740831e-11;

class ObjetCeleste {
    
    public:
        // attributs
        double masse;
        Vecteur acceleration;
        Vecteur velocite;
        Vecteur position;
        std::vector<Vecteur> historiquePositions;

        // Constructeurs
        ObjetCeleste(); 
        ObjetCeleste(const double&, 
                     const Vecteur& = Vecteur(), 
                     const Vecteur& = Vecteur(), 
                     const Vecteur& = Vecteur());
        
        // methodes
        void calculerAccelerationVelocite(const std::vector<ObjetCeleste>&, const int&, const int&);
        void calculerPosition(const int&); 
   
        // methodes statiques
        static ObjetCeleste etoileAleatoire();
        static ObjetCeleste planeteAleatoire(); 

        // operations
        bool operator==(const ObjetCeleste&) const;
        bool operator!=(const ObjetCeleste&) const;

    private:
        static double nombreAleatoire(const double&, const double&); 
};

#endif
