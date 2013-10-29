#ifndef _GAME_CONTROLLER_
#define _GAME_CONTROLLER_

#include "GameView.h"
#include "GameModel.h"
#include "Controller.h"
#include "Vue.h"
#include <string>

class GameView;

///
/// @class GameController
///
class GameController : public Controller
{
private:
    /// Déclaration d'un pointeur sur un GameView
    GameView *_view;
    /// Déclaration d'un pointeur sur un GameModel
    GameModel *_model;
    /// Booléen permettant de savoir si la pause est active
    bool _pauseController;

public:
    GameController(Model *& model);
    ~GameController();
    void detachView(Vue * view);
    void attachView(Vue * view);
    void run_perso(std::string &etat, bool &stop, std::string &perso);

    //Accesseur pour obtenir des données
    void getBallPos(int &x, int &y, int i);
    bool getPause() const;
    int getVie();
    int getScore();
    float getTemps();
    int getNiveau();
    int getNbBall();
    std::string getEtat(int i, int j);
    int getSurface();
    int getSurfaceARecouvrir();
    int getVitBall();
    float getVitBarre();
    int getTempsParNiveau();
    bool getTouchBarre();

    void ajoutBall();
    void suppBall();
    void clearBall();
    //Actions pour mettre à jour des données
    void setPause(bool etat);
    void setVie(int vie);
    void setTemps(int temps);
    void setNiveau(int niv);
    void setSurfaceARecouvrir(int surf);
    void setVitesseBall(int vit);
    void setTempsParNiveau(int temps);
    void setTouchBarre(bool touch);

    bool getHorizDroit(int x, int y, int &nb_d, bool &fini);
    bool getHorizGauche(int x, int y, int &nb_g, bool &fini);
    bool getVertiHaut(int x, int y, int &nb_h, bool &fini);
    bool getVertiBas(int x, int y, int &nb_b, bool &fini);

    void remplissageHori(int x, int y, int nb_g, int nb_d);
    void remplissageVerti(int x, int y, int nb_b, int nb_h);

    void initGrille();
    void initAll();
};


#endif

