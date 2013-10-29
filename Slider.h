#ifndef _SLIDER_H_
#define _SLIDER_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include "util.h"

static const int LONG_BARRE = 300, LONG = 20, CURSOR = 60;

class Slider : public sf::Drawable
{

private :

    int my_posX, my_posY; // position du milieu de la barre
    float my_pos_cursorX, my_pos_cursorY;

    int _val_min,_val_max,_val_local, _ecart;
    float _Xecart;

    bool enfonce;

    sf::Sprite _spr_repere;
    sf::Sprite _spr_barre;
    sf::Sprite _spr_fleche_g;
    sf::Sprite _spr_fleche_d;
    sf::String *_str_name;
    sf::String *_str_name_changed;
    std::string *_str_name_;
    sf::Font *_font;

/// Action qui affichera les sliders
    void Render(sf::RenderTarget& Target) const;

public :

    Slider(int x, int y, int val_min, int val_max, int ecart, sf::Sprite &barre, sf::Sprite &repere, sf::Sprite &fleche1, sf::Sprite & fleche2, sf::String &name,  std::string _name, sf::String &name_changed, sf::Font &font);
    ~Slider();
    bool estDedansGauche(int MouseX, int MouseY );
    bool estDedansDroit(int MouseX, int MouseY );
    bool estDedansBarre(int MouseX, int MouseY);
    void setEnfonce(bool etat);
    bool getEnfonce();
    void setPositionRepere(int MouseX);
    void setValLocal(int val);
    int getValLocal();
    int getValMin();
    int getValMax();
    void actualiseValLocal();
    void actualiseRepere();
    void setPlus();
    void setMoins();
};


#endif
