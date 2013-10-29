#ifndef _CONTROLLER_
#define _CONTROLLER_

#include "Model.h"
#include "Vue.h"
#include <string>


class Vue;

///
/// @class Controller
/// Création d'un contrôleur; classe abtraite
///
class Controller
{
public:
    virtual void detachView(Vue *view)=0;
    virtual void attachView(Vue *view)=0;
    virtual void run(std::string &etat, bool &stop);
    virtual void run_perso(std::string &etat, bool &stop, std::string &perso);
    virtual ~Controller();
};

#endif
