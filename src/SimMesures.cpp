/*
 * Mesures.cpp - Fichier source du code effectuant les mesures relatives aux
 * performances des methodes d'execution sequentielle et parallele de la
 * classe Simulation. Les donnees sont affichees sur stdout et ecrites dans
 * le fichier "data/mesures.dat"
 *
 * @auteur Alexis Chretien (CHRA25049209)
 * @version 7 decembre 2017
 */
#include <iomanip>
#include "Simulation.h"

const int NB_OBJ_MIN = 50;
const int NB_OBJ_MAX = 500;
const int PAS_NB_OBJ = 50;
const int NB_JOURS_SIM = 100; 
const int NB_THREADS[5] = {1, 4, 16, 32, 64};
const std::string ENTETE = std::string(" Legende:\n")
                         + " +--------------------------------------------------------------------------------------+\n"  
                         + " |  t(N)s    : Temps en secondes de la N-eme execution sequentielle                     |\n" 
                         + " |  t(N)p(M) : Temps en secondes de la N-eme execution parallele avec M threads         |\n" 
                         + " |  tms      : Temps moyen en secondes des trois executions sequentielles               |\n" 
                         + " |  tmp(M)   : Temps moyen en secondes des trois executions paralleles avec M threads   |\n"
                         + " |  abs(M)   : Acceleration absolue de la version parallele utilisant M threads         |\n"
                         + " +---------+----------------------------------+----------------------------------+----------------------------------+----------------------------------+---------------------------+\n"
                         + " |         |         Execution no. 1          |         Execution no. 2          |         Execution no. 3          |      Moyenne des executions      |    Acceleration Absolue   |\n"
                         + " +---------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+\n"
                         + " |nb_objets|  t1s | t1p4 | t1p16| t1p32| t1p64|  t2s | t2p4 | t2p16| t2p32| t2p64|  t3s | t3p4 | t3p16| t3p32| t3p64|  tms | tmp4 | tmp16| tmp32| tmp64| abs4 | abs16| abs32| abs64|\n"
                         + " +---------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+\n";
/*
 * Initialise le vector de simulation en argument.
 *
 * Chaque element du vector se trouvera etre une instance
 * differente de la simulation ayant toutes les memes
 * donnees initiales. 
 *
 * @param  simulations      Le vector de simulations a initialiser
 * @param  nbObjetsCelestes Le nombre d'objets celestes que doit contenir
 *                          chaque simulation.
 * @return
 */
void initialiserSimulations(const int& nbObjetsCelestes, std::vector<Simulation>& simulations){

    if (simulations.size() > 0) {
        simulations[0] = Simulation(nbObjetsCelestes);
        
        for(size_t i = 1 ; i < simulations.size() ; ++i) {
            simulations[i] = Simulation(simulations[0]);
        } 
    }
}

/*
 * Main
 */
int main() {

    std::vector<Simulation> sims(5);
    std::ofstream fichier("data/mesures.dat", std::ofstream::trunc);

    std::cout << ENTETE
              << std::fixed 
              << std::setprecision(2);

    for (int nbObj = NB_OBJ_MIN ; nbObj <= NB_OBJ_MAX ; nbObj += PAS_NB_OBJ) {
    
        double temps = 0.0;
        double tempsMoyen[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

        std::cout << std::setw(10) << nbObj << "  ";
        fflush(stdout);
        fichier << nbObj << " "; 

        // mesures et ecritures des temps des trois executions pour chaque version
        for (int j = 0 ; j < 3 ; ++j) {                
            initialiserSimulations(nbObj, sims);

            for (int k = 0 ; k < 5 ; ++k) {
                temps = sims[k].executer(NB_JOURS_SIM, NB_THREADS[k]);
                tempsMoyen[k] += (temps / 3.0); 

                std::cout << std::setw(6) << temps << " ";
                fflush(stdout);
            }
        }
        // ecritures des temps moyens
        for (int j = 0 ; j < 5 ; ++j) {
            std::cout << std::setw(6) << tempsMoyen[j] << " ";
            fichier << tempsMoyen[j] << " ";
        }
        // ecritures des accelerations absolues
        for (int j = 1 ; j < 5 ; ++j) {
            double accAbs = tempsMoyen[0] / tempsMoyen[j];
            std::cout << std::setw(6) << accAbs << " ";
            fichier << accAbs << " "; 
        }
        std::cout << std::endl;
        fichier << std::endl;
    }
    return 0;
}
