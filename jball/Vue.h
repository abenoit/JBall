#ifndef _VUE_
#define _VUE_

#include "Controller.h"
#include <string>
#include <cstdlib>

///
/// @class Vue
///
class Vue
{
public:
    virtual ~Vue();
    virtual void draw()=0;
    virtual void manageEvent(std::string &etat, bool &stop);
    virtual void manageEvent_perso(std::string &etat, bool &stop, std::string &perso);
};

#endif
