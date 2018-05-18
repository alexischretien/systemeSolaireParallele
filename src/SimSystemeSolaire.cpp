/*
 * SimSystemeSolaire.cpp - Fichier source d'une programme simulant l'evolution
 * de notre systeme solaire pour une duree de 365 jours, incluant les 8 planetes
 * du systeme solaire et le soleil. 
 *
 * Le programme produit les fichiers "simSystemeSolaireSeq.dat" et "simSystemeSolairePar.dat"
 * contenant les suites des des position successive de chaque objet celeste de notre 
 * systeme solaire, un produit via l'execution de la methode sequentielle, l'autre via
 * la methode parallele. 
 * Les donnees de ces fichiers sont dans un format pouvant etre utilise par "gnuplot" 
 * pour produire les traces des parcours des planetes.
 *
 * Les valeurs de masses et de velocites initiales ont ete obtenues via l'API web 
 * HORIZONS de la NASA. Les vecteurs positions utilise le systeme de 
 * coordonnees "Solar System Barycenter" (SSB). 
 *
 * @auteur Alexis Chretien (CHRA25049209)
 * @version 8 decembre 2017
 */

#include "Simulation.h"

const int NB_JOURS = 365;

int main() {

    ObjetCeleste soleil(1.988544e+30,   
                        Vecteur(2.970663078825469E+08, 8.925307081439127E+08,-1.864359384502308E+07),
                        Vecteur(-9.683893346951142E-03, 9.066380574701997E-03, 2.319752639818079E-04));
    ObjetCeleste mercure(3.302e+23,
                         Vecteur(5.211396252132120E+10, 5.667640140479822E+09, -4.382127783782231E+09),
                         Vecteur(-1.388936937272326E+04, 5.069636454184066E+04, 5.415360826055625E+03));
    ObjetCeleste venus(48.685e+23,
                       Vecteur(-7.655053223668182E+10, -7.526666114789380E+10, 3.371255102052093E+09),
                       Vecteur(2.439396428689432E+04, -2.503086810661203E+04, -1.751494448010337E+03));
    ObjetCeleste terre(5.97219e+24,
                       Vecteur(5.622867932650845E+10, 1.374202665457189E+11, -2.427130461850762E+07),
                       Vecteur(-2.805460916499384E+04, 1.117977585202810E+04, 3.706221570096702E-01));
    ObjetCeleste mars(6.4185e+23,
                      Vecteur(-2.467809209949438E+11, 3.345175245626475E+09, 6.096496317984799E+09),
                      Vecteur(6.545883427315248E+02,-2.214910326876376E+04, -4.803997113662941E+02));
    ObjetCeleste jupiter(1898.13e+24,
                         Vecteur(-6.585512956645839E+11, -4.757197871267882E+11, 1.670313486190084E+10),
                         Vecteur(7.498789556022850E+03, -9.971839478359007E+03, -1.263459866247003E+02));
    ObjetCeleste saturne(5.68319e+26,
                         Vecteur(-1.807399415431826E+10, -1.504325324531622E+12, 2.687494065966225E+10),
                         Vecteur(9.127116949886219E+03, -1.466288410432244E+02, -3.609134411741998E+02));
    ObjetCeleste uranus(86.8103e+24,
                        Vecteur(2.660025272768131E+12, 1.339894014913312E+12, -2.948465199859208E+10),
                        Vecteur(-3.113643999385909E+03, 5.764574717757329E+03, 6.179270805318460E+01));
    ObjetCeleste neptune(102.41e+24,
                         Vecteur(4.286473749398282E+12, -1.299771391701205E+12, -7.201980499625564E+10),
                         Vecteur(1.540602486592861E+03, 5.234091128429283E+03, -1.425884170413225E+02));
    
    std::vector<ObjetCeleste> systemeSolaire = {soleil, mercure, venus, terre, mars, jupiter, saturne, uranus, neptune};    
    Simulation simSeq(systemeSolaire);
    Simulation simPar(systemeSolaire);  

    simSeq.executerSequentielle(NB_JOURS); 
    simPar.executerParallele(NB_JOURS);

    std::ofstream fichierSeq("data/simSystemeSolaireSeq.dat", std::ofstream::trunc); 
    std::ofstream fichierPar("data/simSystemeSolairePar.dat", std::ofstream::trunc); 

    fichierSeq << "# X Y Z" << std::endl;
    fichierPar << "# X Y Z" << std::endl;

    for (int i = 0 ; i < (int)systemeSolaire.size() ; ++i) {
        std::vector<Vecteur> positionsObjSeq = simSeq.objetsCelestes[i].historiquePositions;
        std::vector<Vecteur> positionsObjPar = simPar.objetsCelestes[i].historiquePositions;

        for (int j = 0 ; j < (int)positionsObjSeq.size() ; ++j) {
            fichierSeq << positionsObjSeq[j].x << " "
                       << positionsObjSeq[j].y << " " 
                       << positionsObjSeq[j].z << std::endl;
            fichierPar << positionsObjPar[j].x << " "
                       << positionsObjPar[j].y << " "
                       << positionsObjPar[j].z << std::endl;
        }
        fichierSeq << std::endl << std::endl;
        fichierPar << std::endl << std::endl;
    }   

    return 0;
}
