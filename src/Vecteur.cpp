/*
 * Vecteur.cpp - Fichier source de l'implementation de la classe Vecteur.
 *
 * @auteur Alexis Chretien (CHRA25049209)
 * @version 8 decembre 2017
 */

#include "Vecteur.h"

// Constructeur par defaut
Vecteur::Vecteur() 
    : x(0.0), y(0.0), z(0.0) {
}

// Constructeur par attributs
Vecteur::Vecteur(const double& x_ = 0.0, const double& y_ = 0.0, const double& z_ = 0.0)
    : x(x_), y(y_), z(z_) {}

// Constructeur par copie
Vecteur::Vecteur(const  Vecteur& v) 
    : x(v.x), y(v.y), z(v.z) {
}

/*
 * Retourne la magnitude du vecteur "this".
 *
 * @return  La magnitude du vecteur "this". 
 */
double Vecteur::magnitude() const {
    return sqrt(x*x + y*y + z*z);
}

/*
 * Retourne le vecteur unitaire du vecteur "this".
 *
 * @return  Le vecteur unitaire du vecteur "this".
 */
Vecteur Vecteur::vecteurUnitaire() const {
    return (*this / this->magnitude());
}

/*
 * Retourne le resultat de l'addition du vecteur "this"
 * au vecteur en argument.
 *
 * @param v  Le vecteur a additionner a "this".
 * @return   La somme de "this" et du vecteur v. 
 */
Vecteur Vecteur::operator+(const Vecteur& v) const {
    return Vecteur(x + v.x, 
                   y + v.y, 
                   z + v.z); 
}

/*
 * Retourne le resultat de la soustraction du vecteur "this"
 * au vecteur en argument.
 *
 * @param v  Le vecteur a soustraire a "this".
 * @return   La soustraction du vecteur v a "this". 
 */
Vecteur Vecteur::operator-(const Vecteur& v) const {
    return Vecteur(x - v.x, 
                   y - v.y, 
                   z - v.z); 
}

/*
 * Retourne la multiplication scalaire du vecteur "this"
 * et du nombre en argument.
 *
 * @param n   La valeur scalaire a multiplier au vecteur "this".
 * @return    La multiplication scalaire du vecteur "this" par n.
 */
Vecteur Vecteur::operator*(const double& n) const {
    return Vecteur(x*n, y*n, z*n);
}

/*
 * Retourne la division scalaire du vecteur "this" et
 * du nombre en argument.
 *
 * @param n  La valeur scalaire auquel on divise le vecteur
 *           "this".
 * @return   La division du vecteur "this" par n. 
 */
Vecteur Vecteur::operator/(const double& n) const {
    return Vecteur(x/n, y/n, z/n); 
}

/*
 * Applique l'addition vectorielle *this + v
 * a *this. 
 *
 * @param v   Le vecteur a additionner a "this" 
 * @return
 */
void Vecteur::operator+=(const Vecteur& v) {
    *this = *this + v;
}

/*
 * Verifie que le vecteur "this" et le vecteur en argument
 * representent le meme vecteur, en prenant en compte un certain
 * seuil d'incertitude,  puisque les coordonnees sont des valeurs flottantes. 
 *
 * @param  v  Le vecteur a comparer a "this".
 * @return    Vrai si "this" et v representent le meme vecteur,
 *            faux sinon.
 */
bool Vecteur::operator==(const Vecteur& v) const {
    return (((x == 0.0 && v.x == 0.0) || (fabs(x - v.x) / ((x + v.x) / 2) < SEUIL)) 
            && ((y == 0.0 && v.y == 0.0) || (fabs(y - v.y) / ((y + v.y) / 2) < SEUIL)) 
            && ((z == 0.0 && v.z == 0.0) || (fabs(z - v.z) / ((z + v.z) / 2) < SEUIL)));
}

/*
 * Verifie si le vecteur "this" et le vecteur en argument
 * representent des vecteurs differents
 *
 * @param  v  Le vecteur a comparer a "this".
 * @return    Vrai si "this" et v representent des vecteurs 
 *            differents, faux sinon.
 */
bool Vecteur::operator!=(const Vecteur& v) const {
    return !(*this == v); 
}

/*
 * Retourne l'ostream contenant la representation ascii du vecteur. 
 *
 * @return L'ostream contenant la representation ascii du vecter.
 */
std::ostream& operator<<(std::ostream& stream, const Vecteur& v) {
    return stream << "Vecteur[" << v.x << ", " << v.y << ", " << v.z << "]";
}
