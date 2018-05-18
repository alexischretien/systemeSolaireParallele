/*
 * Simulation.h - Fichier header de la classe Simulation.
 *
 * @auteur Alexis Chretien (CHRA25049209)
 * @version 8 decembre 2017
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "ObjetCeleste.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/tick_count.h"

// Constantes
// DELTA_T = 1 heure
const int DELTA_T = 3600; 
const int NB_SEC_JOURNEE = 86400;

class Simulation {

    public:
        // attributs
        std::vector<ObjetCeleste> objetsCelestes; 

        // Constructeurs
        Simulation();
        Simulation(const std::vector<ObjetCeleste>&); 
        Simulation(const int&); 
        Simulation(const Simulation&);
       
        // methodes publiques 
        double executer(const int&, int);
        double executerSequentielle(const int&);
        double executerParallele(const int&);
        bool estDansMemeEtat(const Simulation&) const; 
    private:
        //methode privee
        void initialiserObjetsCelestes(const int&);       
};

#endif
