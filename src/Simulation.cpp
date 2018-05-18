/*
* Simulation.cpp - Fichier source de la classe Simulation.
 *
 * @auteur Alexis Chretien (CHRA25049209)
 * @version 8 decembre 2017
 */

#include "Simulation.h"

// Constructeur par defaut
Simulation::Simulation()  {
}

// Constructeur par attribut
Simulation::Simulation(const std::vector<ObjetCeleste> &_objetsCelestes) 
    : objetsCelestes(_objetsCelestes) {
}

// Constructeur d'une simulation contenant nbObjets objets celestes
// aleatoires, incluant une etoile et (nbObjets - 1) planetes
Simulation::Simulation(const int &nbObjets) {
    initialiserObjetsCelestes(nbObjets); 
}

// Constructeur par copie
Simulation::Simulation(const Simulation &sim)
   :  objetsCelestes(sim.objetsCelestes) {
}

/*
 * Reinitialise le membre vector<objetCeleste> de la simulation "this" en 
 * y ajoutant nbObjets objets celestes aleatoires, incluant une etoile et 
 * (nbObjets - 1) planetes.
 *
 * @param nbObjets   Le nombre d'objets celestes a generer pour la simulation
 * @return
 * @require          nbObjets > 0
 */
void Simulation::initialiserObjetsCelestes(const int &nbObjets) {
    assert(nbObjets > 0);

    objetsCelestes.clear(); 
    objetsCelestes.push_back(ObjetCeleste::etoileAleatoire()); 
 
    for(int i = 1 ; i < nbObjets ; ++i) {
        objetsCelestes.push_back(ObjetCeleste::planeteAleatoire());
    }
}

/*
 * Lance l'execution de la simulation en fonction du nombre
 * de threads specifies. 
 *
 * Si le nombre de threads est invalide, utilise le nombre de threads
 * par default. Si le nombre de threads est egal a 1, lance l'execution
 * via la methode sequentielle. Sinon, lance l'execution via la
 * methode parallele en utilisant le nombre de threads specifie
 *
 * @param nbJours   Le nombre de jours que la methode appelee doit 
 *                  simuler.
 * @return          Le temps d'execution de la methode appelee, en 
 *                  secondes. 
 */

double Simulation::executer(const int& nbJours, int nbThreads) {

   int nbThreadsMax = tbb::task_scheduler_init::default_num_threads();
   double temps;

   if (nbThreads < 1 || nbThreads > nbThreadsMax) {
       nbThreads = nbThreadsMax;
   } 
   if (nbThreads == 1) {
       temps = executerSequentielle(nbJours);
   }
   else {
        tbb::task_scheduler_init init(nbThreads);
        temps = executerParallele(nbJours); 
   }
   return temps;
}
/*
 * Lance l'execution sequentielle de la simulation.
 *
 * @param   nbJours  Le nombre de jours que la methode doit simuler.
 * @return           Le temps d'execution de la methode, en secondes. 
 */
double Simulation::executerSequentielle(const int& nbJours) {
   
    long tMax; 
    tbb::tick_count tempsDebut;
    tbb::tick_count tempsFin;

    tempsDebut = tbb::tick_count::now();
    tMax = (long) nbJours * NB_SEC_JOURNEE; 
    
    for(long t = 0 ; t < tMax ; t += DELTA_T) {
        for(int i = 0 ; i < (int)objetsCelestes.size() ; ++i) {
            objetsCelestes[i].calculerAccelerationVelocite(objetsCelestes, i, DELTA_T);
            objetsCelestes[i].calculerPosition(DELTA_T); 
        }
    }
    tempsFin = tbb::tick_count::now();

    return (double) (tempsFin - tempsDebut).seconds();
}
      
/*
 * Lance l'execution parallele de la simulation.
 *
 * @param  nbJours  Le nombre de jours que la methode doit simuler.
 * @return          Le temps d'execution de la methode, en secondes. 
 */
double Simulation::executerParallele(const int& nbJours) {

    long tMax;
    tbb::tick_count tempsDebut;
    tbb::tick_count tempsFin;

    tempsDebut = tbb::tick_count::now();
    tMax = (long) nbJours * NB_SEC_JOURNEE;

    for(long t = 0 ; t < tMax ; t+= DELTA_T) {
        tbb::parallel_for( tbb::blocked_range<size_t> (0, objetsCelestes.size() ),
            [=] ( tbb::blocked_range<size_t> r) {
                for (size_t i = r.begin() ; i < r.end() ; ++i) {
                    objetsCelestes[i].calculerAccelerationVelocite(objetsCelestes, i, DELTA_T);
                }
            }
        );
        tbb::parallel_for( tbb::blocked_range<size_t> (0, objetsCelestes.size() ),
            [=] ( tbb::blocked_range<size_t> r) {
                for (size_t i = r.begin() ; i < r.end() ; ++i) {
                    objetsCelestes[i].calculerPosition(DELTA_T);
                }
            }
        );
    }
    tempsFin = tbb::tick_count::now();

    return (double) (tempsFin - tempsDebut).seconds();
}

/*
 * Verifie si la simulation "this" est dans le meme etat que la simulation
 * en argument. 
 *
 * @param  sim   La simulation a comparer a "this".  
 * @return       Vrai si les membres "objetsCelestes" contiennent le meme nombre 
 *               d'elements et si, pour chaque objetsCelestes[i], les valeurs de 
 *               masse, d'acceleration, de velocite et de position son identiques.
 *               Faux sinon. 
 */
bool Simulation::estDansMemeEtat(const Simulation& sim) const {

    if (objetsCelestes.size() != sim.objetsCelestes.size()) {
        return false;
    }
    for (int i = 0 ; i < (int)objetsCelestes.size() ; ++i) {
        if (objetsCelestes[i] != sim.objetsCelestes[i]) {
            return false;
        }
    }
    return true;
}
