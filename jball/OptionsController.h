#ifndef _OPTIONS_CONTROLLER_
#define _OPTIONS_CONTROLLER_

#include "IntroView.h"
#include "GameModel.h"
#include "Controller.h"
#include "OptionsView.h"
#include <iostream>

class GameModel;
class IntroView;
class OptionsView;

///
/// @class OptionsController
///
class OptionsController : public Controller
{
private:
    /// Déclaration d'un pointeur sur un OptionsView
    OptionsView * _view;
    /// Déclaration d'un pointeur vers un GameModel (on change les données du GameModel à partir du OptionsView précédent)
    GameModel *_model;


public:
    OptionsController(Model *&model);
    ~OptionsController();
    void detachView(Vue * view);
    void attachView(Vue * view);
    void  run_perso(std::string &etat, bool &stop, std::string &perso);

    //Accesseurs
    int getVie();
    int getNbBall();
    int getVitBall();
    int getSurfaceARecouvrir();
    int getTempsParNiveau();
    float getVitesseBarre();


    void ajoutBall();
    void suppBall();

    void setSurface(int surf);
    void setVitesseBall(int vit);
    void setVie(int vie);
    void setTemps(int temps);
    void setTempsParNiveau(int temps);
    void setVitesseBarre(float vit);
    void setNbBall(int nb);


};

#endif

