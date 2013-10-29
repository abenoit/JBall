#include "Wall.h"
using namespace std;

///
/// Constructeur avec paramètres de la class Wall
/// @param x Position en x
/// @param y Position en y
///
Wall::Wall(int x, int y)
{
    sf::Rect<int> wall(x,y,x+LARG, y+HAUT);
    my_mur = wall;
    my_etat = "vide";
}

///
/// Destructeur de la class Wall
///
Wall::~Wall()
{}

///
/// Accesseur permettant de récupérer le rectangle qui englobe le mur
/// @return le rectangle
///
sf::Rect<int> Wall::getRect() const
{
    return my_mur;
}

///
/// Accesseur permettant de récupérer la position en x
/// @return la position en x
///
int Wall::getPosX() const
{
    return my_mur.Left;
}

///
/// Accesseur permettant de récupérer la position en y
/// @return la position en y
///
int Wall::getPosY() const
{
    return my_mur.Top;
}

///
/// Accesseur permettant de récupérer l'état du mur
/// @return l'état du mur
///
string Wall::getEtat() const
{
    return my_etat;
}

///
/// Permet de mettre à jour l'état du mur
/// @param e chaîne de caractère décrivant l'état du mur
///
void Wall::setEtat(std::string e)
{
    my_etat = e;
}
