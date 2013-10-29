#ifndef _INTRO_CONTROLLER_
#define _INTRO_CONTROLLER_

#include "IntroView.h"
#include "GameModel.h"
#include "Controller.h"
#include "IntroView.h"

class GameModel;
class IntroView;
class OptionsView;

///
/// @class IntroController
///
class IntroController : public Controller
{
private:
    /// Déclaration d'un pointeur sur un IntroView
    IntroView * _view;
    /// Déclaration d'un pointeur sur un GameModel
    GameModel *_model;


public:
    IntroController(Model *&model);
    ~IntroController();
    void detachView(Vue * view);
    void attachView(Vue * view);
    void  run_perso(std::string &etat, bool &stop, std::string &perso);

    void setVie(int vie);
    void setNiveau(int niv);
    void setSurfaceARecouvrir(int surf);
    void setVitesseBall(int vit);
    void setTempsParNiveau(int temps);
    void setNbBall(int nb);
    void setScore(int score);
};

#endif

