#include "OptionsController.h"

using namespace std;

///
/// Constructeur avec paramètres de OptionsController
/// @param *model Pointeur vers un Model
///
OptionsController::OptionsController(Model  *&model) : _view(0), _model(dynamic_cast<GameModel *> (model))
{}

///
/// Destructeur
///
OptionsController::~OptionsController()
{
}

///
/// Action permettant d'attacher une vue à l'OptionsController
/// @param *view Pointeur sur une Vue
///
void OptionsController::attachView(Vue *view)
{
    _view = dynamic_cast<OptionsView *>(view);
    _view->setController(this);
}

///
/// Action permettant de détacher une vue de l'OptionsController
/// @param *view Pointeur sur une vue
///
void OptionsController::detachView(Vue *view)
{
    if (_view != dynamic_cast<OptionsView *>(view))
        cerr << "trying to detach a view that is not connected to that controller" << endl;
    _view = 0;
}

///
/// Action permettant le déroulement du programme
/// @param etat Chaîne de caractère permettant de savoir dans quel View l'on se trouve
/// @param stop Booléen permettant de quitter la boucle du main
/// @param perso Chaîne de caractère pour le personnage choisi
///
void OptionsController::run_perso(std::string &etat, bool &stop, std::string &perso)
{
    while (_view != 0)
    {
        _view->draw();
        _view->manageEvent_perso(etat, stop, perso);
    }
}

///
/// Accesseur permettant de récupérer le nombre de vie(s)
/// @return la fonctione getVie() du model
///
int OptionsController::getVie()
{
    return _model->getVie();
}

///
/// Accesseur permettant de récupérer le nombre de balles
/// @return la fonction getNbBall() du model
///
int OptionsController::getNbBall()
{
    return _model->getNbBall();
}

///
/// Accesseur permettant de récupérer la vitesse des balles
/// @return la fonction getVitBall() du model
///
int OptionsController::getVitBall()
{
    return _model->getVitBall();
}

///
/// Accesseur permettant de récupérer la surface à recouvrir
/// @return getSurfaceARecouvrir du model
///
int OptionsController::getSurfaceARecouvrir()
{
    return _model->getSurfaceARecouvrir();
}

///
/// Accesseur permettant de récupérer le temps maximum par niveau
/// @return la fonction getTempsParNiveau du model
///
int OptionsController::getTempsParNiveau()
{
    return _model->getTempsParNiveau();
}

///
/// Accesseur permettant de récupérer la vitesse des barres
/// @return la fonction getVitBarre() du model
///
float OptionsController::getVitesseBarre()
{
    return _model->getVitBarre();
}

///
/// Action permettant d'ajouter une balle
///
void OptionsController::ajoutBall()
{
    _model->ajoutBall();
}

///
/// Action permettant de supprimer une balle
///
void OptionsController::suppBall()
{
    _model->suppBall();
}

///
/// Action permettant de mettre en place la surface à recouvrir
/// @param surf Entier représentant la nouvelle surface à recouvrir
///
void OptionsController::setSurface(int surf)
{
    _model->setSurfaceARecouvrir(surf);
}

///
/// Action permettant de mettre en place la vitesse des balles
/// @param vit Entier représentant la nouvelle vitesse des balles
///
void OptionsController::setVitesseBall(int vit)
{
    _model->setVitesseBall(vit);
}

///
/// Action permettant de mettre en place le nombre de vie(s)
/// @param vie Entier représentant le nouveau nombre de vie(s)
///
void OptionsController::setVie(int vie)
{
    _model->setVie(vie);
}

///
/// Action permettant de mettre en place le temps lorsqu'un niveau commence
/// @param temps Entier représentant le nouveau temps
///
void OptionsController::setTemps(int temps)
{
    _model->setTemps(temps);
}

///
/// Action permettant de mettre en place le temps maximum par niveau
/// @param temps Entier représentant le nouveau temps par niveau
///
void OptionsController::setTempsParNiveau(int temps)
{
    _model->setTempsParNiveau(temps);
}

///
/// Action qui permet de mettre à jour la vitesse des barre
/// @param vit Temps entre deux progressions de barre
///
void OptionsController::setVitesseBarre(float vit)
{
    _model->setVitesseBarre(vit);
}

///
/// Action qui permet de mettre à jour le nombre de balle
/// @param nb Entier correspondant au nouveau nombre de balle
///
void OptionsController::setNbBall(int nb)
{
    _model->setNbBall(nb);
}
