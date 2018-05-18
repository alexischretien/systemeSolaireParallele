/*
 * Vecteur.h - Fichier header de la classe Vecteur.
 *
 * @auteur Alexis Chretien (CHRA25049209)
 * @version 8 decembre 2017
 */
#ifndef VECTEUR_H
#define VECTEUR_H

#include <iostream>
#include <math.h>
#include <assert.h>

const double SEUIL = 0.0001;

class Vecteur {
    
    public:
        // attributs
        double x;
        double y;
        double z;

        // Constructeurs
        Vecteur();
        Vecteur(const double&, const double&, const double&);
        Vecteur(const Vecteur&);

        // methodes
        double magnitude() const;
        Vecteur vecteurUnitaire() const; 

        // operations
        Vecteur operator+(const Vecteur&) const;
        Vecteur operator-(const Vecteur&) const;
        Vecteur operator*(const double&) const;
        Vecteur operator/(const double&) const;
        void operator+=(const Vecteur&);
        bool operator==(const Vecteur&) const;
        bool operator!=(const Vecteur&) const;
        friend std::ostream& operator<<(std::ostream&, const Vecteur&); 
};

#endif
