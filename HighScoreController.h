#ifndef _HIGHSCORE_CONTROLLER_
#define _HIGHSCORE_CONTROLLER_

#include "Controller.h"
#include "HighScoreView.h"
#include "HighScoreModel.h"
#include <iostream>

///
/// @class HighScoreController
///
class HighScoreController : public Controller
{
private:
    /// Déclaration d'un pointeur sur HighScoreView
    HighScoreView *_view;
    /// Déclaration d'un pointeur sur HighScoreModel
    HighScoreModel *_model;


public:
    HighScoreController(Model *&model);
    ~HighScoreController();
    void detachView(Vue * view);
    void attachView(Vue * view);
    void  run(std::string &etat, bool &stop);

    int getTaille();
    std::string getName(int i);
    int getScore(int i);
    int getNiveau(int i);

    void chargeScore();
};

#endif

