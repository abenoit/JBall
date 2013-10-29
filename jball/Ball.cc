#include "Ball.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

///
/// Constructeur avec paramètres de la classe Ball
/// @param x Position en x
/// @param y Position en y
/// @param s Diamètre
/// @param vit Vitesse
///
Ball::Ball(int x, int y, int s, int vit)
{
    my_x = x;
    my_y = y;
    my_s = s;
    my_vit = vit;

    my_dx = aleaDir();
    my_dy = aleaDir();

    sf::Rect<int> tmp(my_x, my_y, (my_x+my_s) , (my_y+my_s));
    my_rect = tmp;
}

///
/// Destructeur de la classe Ball
///
Ball::~Ball()
{}

///
/// Accesseur permettant de récupérer la position en x
/// @return la position en x
///
int Ball::getX() const
{
    return my_x;
}

///
/// Accesseur permettant de récupérer la position en y
/// @return la position en y
///
int Ball::getY() const
{
    return my_y;
}

///
/// Accesseur permettant de récupérer la direction en x
/// @return la direction en x
///
int Ball::getDx() const
{
    return my_dx;
}

///
/// Accesseur permettant de récupérer la direction en y
/// @return la direction en y
///
int Ball::getDy() const
{
    return my_dy;
}

///
/// Accesseur permettant de récupérer le diamètre
/// @return le diamètre
///
int Ball::getSize() const
{
    return my_s;
}

///
/// Accesseur permettant de récupérer la vitesse
/// @return la vitesse
///
int Ball::getVit() const
{
    return my_vit;
}

///
/// Accesseur permettant de récupérer le rectangle englobant la balle
/// @return le rectangle
///
sf::Rect<int> Ball::getRect() const
{
    return my_rect;
}

///
/// Permet de mettre à jour la position en x
/// @param x nouvella position en x
///
void Ball::setX(int x)
{
    my_x = x;
    sf::Rect<int> tmp(my_x, my_y, (my_x+my_s) , (my_y+my_s));
    my_rect = tmp;
}

///
/// Permet de mettre à jour la position en y
/// @param y nouvella position en y
///
void Ball::setY(int y)
{
    my_y = y;
    sf::Rect<int> tmp(my_x, my_y, (my_x+my_s) , (my_y+my_s));
    my_rect = tmp;
}

///
/// Permet de mettre à jour la vitesse
/// @param vit nouvelle vitesse
///
void Ball::setVit(int vit)
{
    my_vit = vit;
}

///
/// Inverse la direction en x
///
void Ball::reverseDX()
{
    my_dx *= -1;
}

///
/// Inverse la direction en y
///
void Ball::reverseDY()
{
    my_dy *= -1;
}

///
/// Surcharge permettant de voir si deux balles sont confondues
/// @param b balle à comparer
/// @return le résultat du test
///
bool Ball::operator==( const Ball & b) const
{
    return (b.my_x == my_x && b.my_y == my_y);
}

///
/// Teste si deux rectangles sont en collision
/// @param a premier rectangle
/// @param b second rectangle
/// @return le résultat du test
///
bool Ball::collision(sf::Rect<int> a, sf::Rect<int> b)
{
    if (a.Bottom <= b.Top)
        return false;
    if (a.Top >= b.Bottom)
        return false;
    if (a.Right <= b.Left)
        return false;
    if (a.Left >= b.Right)
        return false;

    return true;
}

///
/// Teste si une balle est en collision avec toutes les autres
/// @param tabBall vecteur de pointeurs de balles
/// @return le résultat du test
///
bool Ball::collisionBalles(std::vector<Ball*> &tabBall)
{
    for (unsigned int i=0; i < tabBall.size(); i++)
    {
        if (this != tabBall[i])
        {
            if (collision(my_rect,tabBall[i]->getRect()))
                return true;
        }
    }
    return false;
}

///
/// Teste la collision éventuelle avec un mur
/// @param matrice vecteur de vecteur (matrice de pointeurs de Wall)
/// @param perdu booleen permettant de savoir s'il y a eu collision avec un mur en construction
/// @return resultat du test
///
bool Ball::collisionMur(const std::vector<std::vector< Wall* > > & matrice, bool &perdu)
{
    for (int i = my_y/10; i < (my_y+my_s)/10; i ++)
    {
        for (int j = my_x/10; j < (my_x+my_s)/10; j++)
        {
            if (collision(my_rect, matrice[i][j]->getRect()) && matrice[i][j]->getEtat() == "construction")
            {
                perdu = true;
                return true;
            }
            else if (collision(my_rect,matrice[i][j]->getRect()) && matrice[i][j]->getEtat() == "plein")
            {
                return true;
            }
        }
    }
    return false;;
}
