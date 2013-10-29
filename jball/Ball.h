#ifndef _BALL_
#define _BALL_

#include <vector>
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "util.h"

class Wall;
///
/// Création d'un objet appellé Ball; représente la balle
///
class Ball
{
private :
    ///Position de la balle en x
    float my_x;
    ///Position de la balle en y
    float  my_y;
    ///Diamètre de la balle
    int my_s;
    ///Direction de la balle en x
    int my_dx;
    ///Direction de la balle en y
    int my_dy;
    ///Vitesse de la balle
    int my_vit;
    ///Rectangle qui englobe la balle
    sf::Rect<int> my_rect;

public :

    Ball(int x, int y, int s, int vit);
    ~Ball();

    //Accesseur pour obtenir des données de la balle
    int getX() const;//sa position en x
    int getY() const;//sa position en y
    int getDx() const;//sa direction en x
    int getDy() const;//sa direction en y
    int getSize() const;//sa taille
    int getVit() const;//sa vitesse
    sf::Rect<int> getRect() const;//le rectangle qui englobe la balle

    //Actions pour mettre à jour des données de la balle
    void setX(int x);//sa position en x
    void setY(int y);//sa position en y
    void setVit(int vit);//sa vitesse

    //Méthodes d'une balle
    void reverseDX();//changer sa direction en x
    void reverseDY();//changer sa direction en y

    bool operator==( const Ball & b) const;//opérateur d'égalité entre deux balles

    bool collision(sf::Rect<int> a, sf::Rect<int> b);//collision entre deux rectangle
    bool collisionBalles(std::vector<Ball*> &tabBall );//collision entre la balle et le reste des autres balles
    bool collisionMur(const std::vector<std::vector< Wall* > > & matrice, bool &perdu);//collision entre la balle et la matrice de mur
};

#endif
