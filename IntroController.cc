#include "IntroController.h"

using namespace std;

///
/// Constructeur avec paramètres de la classe IntroController
/// @param *model Pointeur sur un Model
///
IntroController::IntroController(Model  *&model) : _view(0), _model(dynamic_cast<GameModel *> (model))
{}

///
/// Destructeur de la classe IntroController
IntroController::~IntroController()
{}

///
/// Action permettant d'attacher une Vue au controller
/// @param *view Pointeur sur la vue à attacher
///
void IntroController::attachView(Vue *view)
{
    _view = dynamic_cast<IntroView *>(view);
    _view->setController(this);
}

///
/// Action permettant de détacher une Vue au controller
/// @param *view Pointeur sur la vue à détacher
///
void IntroController::detachView(Vue *view)
{
    if (_view != dynamic_cast<IntroView *>(view))
        cerr << "trying to detach a view that is not connected to that controller" << endl;
    _view = 0;
}

///
/// Action : affiche la fenêtre et ses composants si le view est different de 0
/// @param etat Chaîne de caractère permettant de savoir quel view afficher
/// @param stop Booléen permettant de quitter la fenêtre d'intro
/// @param perso Chaîne de caractère pour le personnage choisi
///
void IntroController::run_perso(std::string &etat, bool &stop, std::string &perso)
{
    while (_view != 0)
    {
        _view->draw();
        _view->manageEvent_perso(etat, stop, perso);
    }
}

///
/// Action qui permet de mettre à jour la vie
/// @param vie Entier définissant le nouveau nombre de vie
///
void IntroController::setVie(int vie)
{
    _model->setVie(vie);
}

///
/// Action qui permet de mettre à jour le niveau
/// @param niv Entier définissant le nouveau niveau à mettre en place
///
void IntroController::setNiveau(int niv)
{
    _model->setNiveau(niv);
}

///
/// Action qui permet de mettre à jour la surface à recouvrir
/// @param surf Entier définissant la nouvelle surface à recouvrir
///
void IntroController::setSurfaceARecouvrir(int surf)
{
    _model->setSurfaceARecouvrir(surf);
}

///
/// Action qui permet de mettre à jour la vitesse des balles
/// @param vit Entier définissant la nouvelle vitesse des balles
///
void IntroController::setVitesseBall(int vit)
{
    _model->setVitesseBall(vit);
}

///
/// Action qui permet de mettre à jour le temps par niveau
/// @param temps Entier définissant le nouveau temps par niveau
///
void IntroController::setTempsParNiveau(int temps)
{
    _model->setTempsParNiveau(temps);
}

///
/// Action qui permet de mettre à jour le nombre de balle
/// @param nb Entier définissant le nouveau nombre de balle
///
void IntroController::setNbBall(int nb)
{
    _model->setNbBall(nb);
}

///
/// Action qui permet de mettre à jour le score
/// @param score Entier définissant le nouveau score
///
void IntroController::setScore(int score)
{
    _model->setScore(score);
}
