#include "GameController.h"
#include <iostream>

using namespace std;

///
/// Constructeur avec paramètres de la classe GameController
/// @param *model Pointeur sur un Model
///
GameController::GameController(Model  *&model) : _view(0), _model(dynamic_cast<GameModel *> (model))
{
    _pauseController = false;
}

///
/// Destructeur de GameController
///
GameController::~GameController()
{
}

///
/// Action permettant de convertir le pointeur en paramètre en un pointeur sur un GameView et attache le controller à la Vue
/// @param *view Pointeur sur une Vue
///
void GameController::attachView(Vue *view)
{
    _view = dynamic_cast<GameView *> (view);
    _view->setController(this);
}

///
/// Action testant si le paramètres est un pointeur sur le GameView et détache la Vue du controller
/// @param *view Pointeur sur une Vue
///
void GameController::detachView(Vue *view)
{
    if (_view != dynamic_cast<GameView *> (view))
        cerr << "trying to detach a view that is not connected to that controller" << endl;
    _view = 0;
}

///
/// Action qui permet d'afficher et gérer les évènements et mettre à jour le jeu tant qu'une vue est active
/// @param etat Chaîne de caractères de type std permettant de savoir dans quel view on se place
/// @param stop Booléen permettant de quitter l'application
/// @param perso Chaîne de caractère pour le personnage choisi
///
void GameController::run_perso(std::string &etat, bool &stop, std::string &perso)
{
    _model->resetTemps();
    _view->update(perso);

    while (_view != 0)
    {
        _view->draw();
        _view->manageEvent_perso(etat, stop,perso);

        if (!_pauseController)
            _model->nextStep();
        else
            _model->resetTemps();
    }
}

///
/// Action qui permet de récupérer la position d'une balle
/// @param x Position en x en (entrée/sortie)
/// @param y Position en y en (entrée/sortie)
/// @param i Indice de la balle dans le vecteur de balle
///
void GameController::getBallPos(int &x, int &y, int i)
{
    _model->getBallPos(x, y, i);
}

///
/// Action qui permet d'ajouter une balle au jeu
///
void GameController::ajoutBall()
{
    _model->ajoutBall();

}

///
/// Action qui permet de supprimer une balle du jeu
///
void GameController::suppBall()
{
    _model->suppBall();
}

///
/// Action qui permet de supprimer toutes les balles du jeu
///
void GameController::clearBall()
{
    _model->clearBall();
}

///
/// Fonction qui permet de récuperer l'état de la pause
/// @return Le booléen correspondant à l'état de la pause
///
bool GameController::getPause() const
{
    return _pauseController;
}

///
/// Action permettant de mettre le jeu en pause ou non
/// @param etat Booléen qui permet de mettre à jour le booléen pause du controller
///
void GameController::setPause(bool etat)
{
    _pauseController = etat;
}

///
/// Fonction qui retourne le nombre de vie(s) restante(s) via le model
/// @return La fonction getVie() du model
///
int GameController::getVie()
{
    return _model->getVie();
}

///
/// Fonction qui retourne le score via le model
/// @return La fonction getScore() du model
///
int GameController::getScore()
{
    return _model->getScore();
}

///
/// Fonction qui retourne le temps restant via le model
/// @return La fonction getTemps() du model
///
float GameController::getTemps()
{
    return _model->getTemps();
}

///
/// Fonction qui retourne le niveau via le model
/// @return La fonction getNiveau() du model
///
int GameController::getNiveau()
{
    return _model->getNiveau();
}

///
/// Fonction qui retourne le nombre de balle(s) en jeu via le model
/// @return La fonction getNbBall() du model
///
int GameController::getNbBall()
{
    return _model->getNbBall();
}

///
/// Fonction qui retourne la surface à recouvrir via le model
/// @return La fonction getSurfaceARecouvrir() du model
///
int GameController::getSurfaceARecouvrir()
{
    return _model->getSurfaceARecouvrir();
}

///
/// Fonction qui retourne l'état d'une case de la matrice via le model
/// @param i Entier correspondant à la position en abscisse dans la matrice
/// @param j Entier correspondant à la position en ordonnée dans la matrice
/// @return La fonction getEtat() du model
///
string GameController::getEtat(int i, int j)
{
    return _model->getEtat(i,j);
}

///
/// Fonction qui permet la progression de la barre horizontale droite
/// @param x Entier correspondant à la position en x de la souris
/// @param y Entier correspondant à la position en y de la souris
/// @param nb_d Entier passé en entrée/sortie stockant le nombre de case(s) comprise(s) entre le clic et le bord droit ou la prochaine case à l'état "plein"
/// @param fini Booléen passé en entrée/sortie permettant de savoir si la progression est terminée ou non
/// @return La fonction BarreHorizDroit du model
///
bool GameController::getHorizDroit(int x, int y, int & nb_d, bool &fini)
{
    return _model->BarreHorizDroit(x, y, nb_d, fini);

}

///
/// Fonction qui permet la progression de la barre horizontale gauche
/// @param x Entier correspondant à la position en x de la souris
/// @param y Entier correspondant à la position en y de la souris
/// @param nb_g Entier passé en entrée/sortie stockant le nombre de case(s) comprise(s) entre le clic et le bord gauche ou la prochaine case à l'état "plein"
/// @param fini Booléen passé en entrée/sortie permettant de savoir si la progression est terminée ou non
/// @return La fonction BarreHorizGauche du model
///
bool GameController::getHorizGauche(int x, int y, int &nb_g, bool &fini)
{
    return _model->BarreHorizGauche(x, y, nb_g, fini);

}

///
/// Fonction qui permet la progression de la barre verticale haut
/// @param x Entier correspondant à la position en x de la souris
/// @param y Entier correspondant à la position en y de la souris
/// @param nb_h Entier passé en entrée/sortie stockant le nombre de case(s) comprise(s) entre le clic et le bord haut ou la prochaine case à l'état "plein"
/// @param fini Booléen passé en entrée/sortie permettant de savoir si la progression est terminée ou non
/// @return La fonction BarreVertiHaut du model
///
bool GameController::getVertiHaut(int x, int y, int &nb_h, bool &fini)
{
    return _model->BarreVertiHaut(x, y, nb_h, fini);

}

///
/// Fonction qui permet la progression de la barre verticale bas
/// @param x Entier correspondant à la position en x de la souris
/// @param y Entier correspondant à la position en y de la souris
/// @param nb_b Entier passé en entrée/sortie stockant le nombre de case(s) comprise(s) entre le clic et le bord droit ou la prochaine case à l'état "plein"
/// @param fini Booléen passé en entrée/sortie permettant de savoir si la progression est terminée ou non
/// @return La fonction BarreVertiBas du model
///
bool GameController::getVertiBas(int x, int y, int &nb_b, bool &fini)
{
    return _model->BarreVertiBas(x, y, nb_b, fini);

}

///
/// Fonction qui permet de récupérer la surface recouverte par le joueur
/// @return La fonction calculSurface() du model
///
int GameController::getSurface()
{
    return _model->calculSurface();
}

bool GameController::getTouchBarre()
{
    return _model->getTouchBarre();
}

///
/// Action permettant de remplir une surface à la fin de la progression complète d'une barre horizontale
/// @param x Entier correspondant à la position en x de la souris lors du clic
/// @param y Entier correspondant à la position en y de la souris lors du clic
/// @param nb_g Entier correspondant au nombre de case(s) à l'état vide disponible sur la gauche
/// @param nb_d Entier correspondant au nombre de case(s) à l'état vide disponible sur la droite
///
void GameController::remplissageHori(int x, int y, int nb_g, int nb_d)
{
    _model->remplissageHori(x, y, nb_g, nb_d);
}

///
/// Action permettant de remplir une surface à la fin de la progression complète d'une barre verticale
/// @param x Entier correspondant à la position en x de la souris lors du clic
/// @param y Entier correspondant à la position en y de la souris lors du clic
/// @param nb_b Entier correspondant au nombre de case(s) à l'état vide disponible sur le bas
/// @param nb_h Entier correspondant au nombre de case(s) à l'état vide disponible sur le haut
///
void GameController::remplissageVerti(int x, int y, int nb_b, int nb_h)
{
    _model->remplissageVerti(x, y, nb_b, nb_h);
}

///
/// Action permettant de mettre en place un certain nombre de vie(s)
/// @param vie Nombre de vie à instaurer
///
void GameController::setVie(int vie)
{
    _model->setVie(vie);
}

///
/// Action permettant de mettre en place le temps
/// @param temps Temps à instaurer
///
void GameController::setTemps(int temps)
{
    _model->setTemps(temps);
}

///
/// Action permettant d'initialiser la matrice du jeu
///
void GameController::initGrille()
{
    _model->initGrille();
}

///
/// Action permettant de mettre en place un certain niveau
/// @param niv Niveau à instaurer
///
void GameController::setNiveau(int niv)
{
    _model->setNiveau(niv);
}

///
/// Action permettant de mettre à jour la surface à recouvrir
/// @param surf Surface à instaurer
///
void GameController::setSurfaceARecouvrir(int surf)
{
    _model->setSurfaceARecouvrir(surf);
}

///
/// Action permettant aux balles/ à la balle d'avancer à une certaine vitesse
/// @param vit Vitesse à instaurer sur le(s) balle(s)
///
void GameController::setVitesseBall(int vit)
{
    _model->setVitesseBall(vit);
}

///
/// Action permettant de mettre en place le temps par niveau : entier qui stocke le temps maximum par niveau
/// @param temps Temps à instaurer
///
void GameController::setTempsParNiveau(int temps)
{
    _model->setTempsParNiveau(temps);
}

void GameController::setTouchBarre(bool touch)
{
    _model->setTouchBarre(touch);
}

///
/// Fonction qui permet de récupérer la vitesse de(s) balle(s)
/// @return La fonction getVitBall() du model
///
int GameController::getVitBall()
{
    return _model->getVitBall();
}

///
/// Fonction qui permet de récupérer la vitesse de(s) barre(s)
/// @return La fonction getVitBarre() du model
///
float GameController::getVitBarre()
{
    return _model->getVitBarre();
}

int GameController::getTempsParNiveau()
{
    return _model->getTempsParNiveau();
}

void GameController::initAll()
{
    _model->initAll();
}
