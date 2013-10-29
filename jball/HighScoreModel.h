#ifndef _HIGHSCORE_MODEL_
#define _HIGHSCORE_MODEL_
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "Model.h"
#include "util.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

///
/// @class HighScoreModel
///
class HighScoreModel : public Model
{
private:
    /// Vecteur de chaîne de caractères pour récupérer les noms
    std::vector<std::string> _name;
    /// Vecteur d'entiers pour récupérer les scores
    std::vector<int> _score;
    /// Vecteur d'entiers pour récupérer le niveau
    std::vector<int> _niveau;

public:

    HighScoreModel();
    ~HighScoreModel();

    int getTaille();
    std::string getName(int i);
    int getScore(int i);
    int getNiveau(int i);

    void chargeScore();
};
#endif
