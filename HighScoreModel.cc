#include "HighScoreModel.h"

using namespace std;

///
/// Constructeur de la classe HighScoreModel
///
HighScoreModel::HighScoreModel()
{}

///
/// Destructeur
///
HighScoreModel::~HighScoreModel()
{}

///
/// Accesseur : récupère la taille du vecteur
/// @return Le nombre de noms compris dans le vecteur
///
int HighScoreModel::getTaille()
{
    return _name.size();
}

///
/// Accesseur : récupère les noms du vecteur
/// @param i Entier utilisé comme indice
/// @return Le nom situé à la position i du vecteur
///
string HighScoreModel::getName(int i)
{
    return _name[i];
}

///
/// Accesseur : récupère les scores du vecteur
/// @param i Entier utilisé comme indice
/// @return Le score situé à la position i du vecteur
///
int HighScoreModel::getScore(int i)
{
    return _score[i];
}

///
/// Accesseur : récupère les niveaux du vecteur
/// @param i Entier utilisé comme indice
/// @return Le niveau situé à la position i du vecteur
///
int HighScoreModel::getNiveau(int i)
{
    return _niveau[i];
}

///
/// Action qui permet de charger le fichier des high scores
///
void HighScoreModel::chargeScore()
{
    // _name, _score, _niveau étant des vector passés en entrée/sortie qui contiendront les noms, scores et niveaux présent dans le fichier des high scores
    if (!chargerHighScore(_name, _score, _niveau))
        std::cerr << "ERROR when loading file high_score.data" << std::endl;
}
