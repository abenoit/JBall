#include "HighScoreController.h"

using namespace std;

///
/// Constructeur avec paramètres de HighScoreController
/// @param *model Pointeur sur un Model
///
HighScoreController::HighScoreController(Model  *&model) : _view(0), _model(dynamic_cast<HighScoreModel *> (model))
{}

///
/// Destructeur
///
HighScoreController::~HighScoreController()
{
}

///
/// Action permettant d'attacher une vue à ce controller
/// @param *view Pointeur sur une Vue
///
void HighScoreController::attachView(Vue *view)
{
    _view = dynamic_cast<HighScoreView *>(view);
    _view->setController(this);
}

///
/// Action permettant de détacher une vue de ce controller
/// @param *view Pointeur sur une Vue
///
void HighScoreController::detachView(Vue *view)
{
    if (_view != dynamic_cast<HighScoreView *>(view))
        cerr << "trying to detach a view that is not connected to that controller" << endl;
    _view = 0;
}

///
/// Action : affiche la fenêtre et ses composants si le view est different de 0
/// @param etat Chaîne de caractère permettant de savoir quel view afficher
/// @param stop Booléen permettant de quitter la fenêtre d'intro
///
void HighScoreController::run(std::string &etat, bool &stop)
{
    while (_view != 0)
    {
        _view->draw();
        _view->manageEvent(etat, stop);
    }
}

///
/// Accesseur : recupère la taille du vecteur
/// @return La fonction getTaille() du model
///
int HighScoreController::getTaille()
{
    return _model->getTaille();
}

///
/// Accesseur : recupère les noms
/// @param i Entier : indice dans le vecteur
/// @return getName du model
///
string HighScoreController::getName(int i)
{
    return _model->getName(i);
}

///
/// Accesseur : recupère les scores
/// @param i Entier : indice dans le vecteur
/// @return getScore du model
///
int HighScoreController::getScore(int i)
{
    return _model->getScore(i);
}
///
/// Accesseur : recupère les niveaux
/// @param i Entier : indice dans le vecteur
/// @return getNiveau du model
///
int HighScoreController::getNiveau(int i)
{
    return _model->getNiveau(i);
}

///
/// Action permettant de charger les scores
///
void HighScoreController::chargeScore()
{
    _model->chargeScore();
}
