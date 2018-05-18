/*
 * Tests.cpp - Fichier source de l'executable permettant de tester les valeurs
 * obtenues par les methodes d'exections sequentielle et parallele de la
 * classe Simulation.
 *
 * @auteur Alexis Chretien (CHRA25049209)
 * @version 7 decembre 2017
 */

#include "Simulation.h"

const int NB_TESTS = 7;
const int NB_OBJ = 100;
const std::vector<int> NB_JOURS_EXEC_SEQ = {0, 10, 0, 30, 50, 1, 0 };
const std::vector<int> NB_JOURS_EXEC_PAR = {0, 0, 10, 50, 30, 0, 1 };

/*
 * afficher les informations relative a un test.
 *
 * @param  noTest         Le numero du test
 * @param  nbJoursSeq     Le nombre de jours ecoules au total dans la simulation sequentielle
 * @param  nbJoursPar     Le nombre de jours ecoules au total dans la simulation parallele
 * @param  simsMemesEtats Vrai si les objets celestes des simulations parallele et sequentielle 
 *                        ont les memes valeurs en fait de masse, de position, de velocite et 
 *                        d'acceleration courante, faux sinon. 
 * @param  testReussi     Vrai si le test a reussi (nbJoursSeq == nbJoursPar => simsIdentiques), 
 *                        (nbJoursSeq != nbJoursPar => !simsIdentiques). Faux sinon. 
 * @return
 */
void afficherResultatTest(const int& noTest, const int& nbJoursSeq, const int& nbJoursPar, 
                          const bool& simsMemesEtats, const bool& testReussi) {

    std::cout << "Test no. " << noTest << " : " << std::endl
              << "    Nombre de jours ecoules dans la simulation sequentielle : "
              << nbJoursSeq << std::endl
              << "    Nombre de jours ecoules dans la simulation parallele :    "
              << nbJoursPar << std::endl
              << (simsMemesEtats ? "    simSeq et simPar contiennent les meme donnees" :
                 "    simSeq et simPar ne contiennent pas les meme donnees") << std::endl
              << "    Test " <<  (testReussi ? "reussi" : "echoue") << std::endl;  
}

/*
 * Main
 */
int main () {

    bool simsMemesEtats = false;
    bool testReussi = false;
    bool auMoinsUnEchec = false;
    int nbJoursTotalSeq = 0;
    int nbJoursTotalPar = 0;

    Simulation simSeq(NB_OBJ); 
    Simulation simPar(simSeq);    

    std::cout << std::endl  
              << "Execution de la suite de tests pour une simulation sequentielle et "
              << "une simulation parallele d'un systeme planetaire compose de " << NB_OBJ
              << " objets celestes." << std::endl << std::endl;

    for (int i = 0 ; i < NB_TESTS ; ++i) {

        simSeq.executerSequentielle(NB_JOURS_EXEC_SEQ[i]);
        simPar.executerParallele(NB_JOURS_EXEC_PAR[i]); 

        nbJoursTotalSeq += NB_JOURS_EXEC_SEQ[i];
        nbJoursTotalPar += NB_JOURS_EXEC_PAR[i];

        simsMemesEtats = simSeq.estDansMemeEtat(simPar); 

        testReussi = (nbJoursTotalSeq == nbJoursTotalPar && simsMemesEtats == true) ||
                     (nbJoursTotalSeq != nbJoursTotalPar && simsMemesEtats == false); 

       afficherResultatTest(i + 1, nbJoursTotalSeq, nbJoursTotalPar, simsMemesEtats, testReussi); 

        if(testReussi == false) {
            auMoinsUnEchec = true; 
        } 
    }
    std::cout << std::endl << "Fin du plan de tests. " 
              << (auMoinsUnEchec ? "Au moins un test a echoue." :
                                   "Tous les tests passent.")
              << std::endl;

    return 0;
}
