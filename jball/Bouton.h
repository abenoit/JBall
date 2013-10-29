#ifndef _BOUTON_H_
#define _BOUTON_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <sstream>

/// Constante indiquant la longueur d'un bouton
const int LONG_BUTTON = 200;
/// Constante indiquant la hauteur d'un bouton
const int HAUT_BUTTON = 40;

///
/// @class Bouton
///
class Bouton : public sf::Drawable
{
private :
    /// Centre du boutton : position en x
    int my_abs;
    /// Centre du boutton : position en y
    int my_ord;
    /// Booléen indiquant si le bouton est dans l'état enfoncé
    bool _enfonce;
    /// Sprite du bouton lorsqu'il est non coché
    sf::Sprite _spr_bouton;
    /// Sprite du bouton lorsqu'il est coché
    sf::Sprite _spr_bouton_enfonce;
    /// Texte de type sf qui de écrit sur le bouton
    sf::String *_text_bouton;
    /// Texte de type std qui contiendra le exte à écrire sur le bouton
    std::string *_text_boutonn;
    /// Police de l'écriture du texte du bouton
    sf::Font *_font_police;
    /// Action qui affichera les bouton
    void Render(sf::RenderTarget& Target) const;

public :

    Bouton(int x, int y, sf::String &text, std::string texte, sf::Sprite &S, sf::Sprite &SE, sf::Font &police);
    ~Bouton();
    bool estDedans(int MouseX, int MouseY);
    bool getEnfonce();
    void setEnfonce(bool etat);
    void changeColor(sf::Color color);
};

#endif
