#ifndef WALL_H_
#define WALL_H_
#include <vector>
#include <string>
#include "GameModel.h"
#include <SFML/Graphics.hpp>

///
/// @class Wall
/// Création d'un objet appellé Wall; représente un mur
///
class Wall {
private:
    ///Constante de la hauteur d'un élément Wall
    static const int HAUT = 10;
    ///Constante de la hauteur d'un élément Wall
    static const int LARG = 10;
    ///Etat d'un élément Wall
    std::string my_etat;
    ///Rectangle qui englobe un mur
    sf::Rect<int> my_mur;

public:

    Wall(int x, int y);
    ~Wall();
    int getPosX() const;
    int getPosY() const;
    std::string getEtat() const;
    void setEtat(std::string e);
    sf::Rect<int> getRect() const ;

};
#endif
