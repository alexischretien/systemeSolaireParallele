/*
 * ObjetCeleste.cpp - Fichier source de l'implementation de la classe ObjetCeleste. 
 *
 * @auteur Alexis Chretien (CHRA25049209)
 * @version 8 decembre 2017
 */
#include <iostream>
#include "ObjetCeleste.h"

// Constructeur par defaut
ObjetCeleste::ObjetCeleste()
    : masse(0.0) {
}

// Constructeur par attributs
ObjetCeleste::ObjetCeleste(const double& masse_, 
                           const Vecteur& position_,
                           const Vecteur& velocite_,
                           const Vecteur& acceleration_) 
    : masse(masse_), acceleration(acceleration_), velocite(velocite_), position(position_) {

        historiquePositions.push_back(position_);
}

/*
 * Met a jour les valeurs des vecteurs d'acceleration et de velocite de l'objet
 * celeste "this" en fonction des forces gravitationnelles exercees 
 * par l'ensemble des objets celestes du systeme en argument.
 *
 * @param  objetsCelestes  L'ensemble des objets celestes du systeme, incluant "this". 
 * @param  i               L'indice de "this" dans le vecteur "objetsCelestes". 
 * @param  dt              Le nombre de secondes qui se sont ecoulees depuis la 
 *                         derniere mise a jour d'acceleration et de velocite. 
 * @return
 *
 */
void ObjetCeleste::calculerAccelerationVelocite(const std::vector<ObjetCeleste>& objetsCelestes, 
                                                 const int& i, 
                                                 const int& dt){

    Vecteur accGrav; 
    Vecteur distance;
    Vecteur vecteurUnitaireDistance;
    double  magnitudeDistance; 

    for(int j = 0 ; j < (int)objetsCelestes.size() ; ++j) {
        if (i != j) {
            distance = objetsCelestes[j].position - position; 
            magnitudeDistance = distance.magnitude();  
            vecteurUnitaireDistance = distance.vecteurUnitaire(); 
            accGrav += vecteurUnitaireDistance * objetsCelestes[j].masse / (magnitudeDistance * magnitudeDistance); 
        }
    }
    accGrav = accGrav * CONSTANTE_GRAVITATIONNELLE;

    acceleration = accGrav; 
    velocite += acceleration * dt; 
}

/*
 * Met a jour la valeur du vecteur de position de l'objet celeste "this" en fonction
 * de sa velocite actuelle. 
 * 
 * @param  dt   Le nombre de secondes qui se sont ecoulees depuis la derniere
 *              mise a jour de position. 
 * @return
 */
void ObjetCeleste::calculerPosition(const int& dt) {

    position += velocite * dt; 
    historiquePositions.push_back(position); 
}

/* 
 * Genere une etoile de masse aleatoire (masse comprise entre MASSE_ETOILE_MIN et
 * MASSE_ETOILE_MAX). 
 *
 * Les valeurs initiales des vecteurs de position, de velocite et l'acceleration
 * sont initialisees a [0, 0, 0]. 
 *
 * @return      Un objet celeste de masse compris entre MASSE_ETOILE_MIN et
 *              MASSE_ETOILE_MAX), initialement immobile, n'accelerant pas et 
 *              etant positionne aux coordonnes [0, 0, 0]. 
 */
ObjetCeleste ObjetCeleste::etoileAleatoire() {
    
    double masseAleatoire = nombreAleatoire(MASSE_ETOILE_MIN, MASSE_ETOILE_MAX);

    return ObjetCeleste(masseAleatoire); 
}

/*
 * Genere une planete de masse et de position aleatoire.
 *
 * La masse de la planete est comprise entre MASSE_PLANETE_MIN et
 * MASSE_PLANETE_MAX. Les coordonnees en x, y et z du vecteur de position
 * initial sont comprises entre POS_PLANETE_MIN et POS_PLANETE_MAX.
 *
 * Les valeurs des vecteurs de velocite et d'acceleration sont 
 * initialisees a [0, 0, 0].
 *
 * @return      Un objet celeste de masse compris entre MASSE_PLANETE_MIN
 *              et MASSE_PLANETE_MAX, initialement immobile, n'accelerant pas
 *              et ayant une position [x, y, z] telle que 
 *              POS_PANETE_MIN <= x, y, z <= POS_PLANETE_MAX.
 */
ObjetCeleste ObjetCeleste::planeteAleatoire() {
    
    double masseAleatoire = nombreAleatoire(MASSE_PLANETE_MIN, MASSE_PLANETE_MAX);
    double pos_x = nombreAleatoire(POS_PLANETE_MIN, POS_PLANETE_MAX);
    double pos_y = nombreAleatoire(POS_PLANETE_MIN, POS_PLANETE_MAX);
    double pos_z = nombreAleatoire(POS_PLANETE_MIN, POS_PLANETE_MAX); 
    Vecteur posAleatoire(pos_x, pos_y, pos_z);

    return ObjetCeleste(masseAleatoire, posAleatoire); 
}

/* 
 * Genere un nombre aleatoire 
 *
 * @param nbMin   La valeur minimal que peut prendre le nombre aleatoire.
 * @param nbMax   La valeur maximal que peut prendre le nombre aleatoire.
 * @return        Un nombre aleatoire n tel que nbMin <= n <= nbMax
 * @require       nbMin <= nbMax
 */
double ObjetCeleste::nombreAleatoire(const double& nbMin, const double& nbMax) {

    assert(nbMin <= nbMax);

    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> distribution(nbMin, nbMax); 

    return distribution(gen);
}

/*
 * Verifie si deux instances d'objets celestes representent deux
 * objets qui sont dans le meme etat
 *
 * @param objCel   L'objet celeste a comparer a "this". 
 * @return         Vrai si les deux objets celestes partagent
 *                 les memes valeurs de masse, d'acceleration
 *                 de velocite et de position, faux sinon.
 * @note           Les deux objets n'ont pas a avoir le meme
 *                 historique de positions pour que la
 *                 methode retourne vrai. Seule la valeur de
 *                 position courrante compte. 
 */
bool ObjetCeleste::operator==(const ObjetCeleste& objCel) const {

    return (((masse == 0.0 && objCel.masse == 0.0) || 
                (fabs(masse - objCel.masse) / ((masse + objCel.masse) / 2) < SEUIL)) 
              && acceleration == objCel.acceleration
              && velocite == objCel.velocite
              && position == objCel.position); 
}

/*
 * Verifie si deux instances d'objets celestes representent deux
 * objets qui sont dans des etats differents. 
 *
 * @param objCel  L'objet celeste a comparer a "this".
 * @return        Vrai si les deux objets celestes different
 *                en fait de masse, de position courrante, de 
 *                velocite ou d'acceleration, faux sinon. 
 */
bool ObjetCeleste::operator!=(const ObjetCeleste& objCel) const {

    return !(*this == objCel);
}
