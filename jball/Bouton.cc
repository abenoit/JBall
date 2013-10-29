#include "Bouton.h"
#include <iostream>

using namespace std;

///
/// Constructeur avec paramètre de la classe Bouton
/// @param x Position en x
/// @param y Position en y
/// @param text Texte du bouton de type sf
/// @param texte Texte du bouton de type std
/// @param S Sprite du bouton à l'état non enfoncé
/// @param SE Sprite du bouton à l'état enfoncé
/// @param police Police d'écriture
///
Bouton::Bouton(int x, int y, sf::String &text , std::string texte, sf::Sprite &S, sf::Sprite &SE, sf::Font &police):_spr_bouton(S), _spr_bouton_enfonce(SE), _text_bouton(&text), _text_boutonn(&texte), _font_police(&police)
{
    //my_abs et my_ord étant le centre du boutton
    my_abs = x;
    my_ord = y;

    _spr_bouton.Resize(LONG_BUTTON, HAUT_BUTTON);
    _spr_bouton.SetPosition(my_abs - (LONG_BUTTON/2), my_ord - (HAUT_BUTTON/2));

    _spr_bouton_enfonce.Resize(LONG_BUTTON, HAUT_BUTTON);
    _spr_bouton_enfonce.SetPosition(my_abs - (LONG_BUTTON/2), my_ord - (HAUT_BUTTON/2));


    _enfonce = false;

    _text_bouton->SetText(*_text_boutonn);
    _text_bouton->SetSize(25);
    _text_bouton->SetFont(*_font_police);
    _text_bouton->SetPosition(my_abs - _text_bouton->GetRect().GetWidth()/2, my_ord - _text_bouton->GetRect().GetHeight()/2 - 5);
}

///
/// Destructeur de la classe Bouton
///
Bouton::~Bouton()
{}

///
/// Surcharge pour afficher tous les éléments d'un bouton
/// @param Target Fenêtre de l'application
///
void Bouton::Render(sf::RenderTarget & Target) const
{
    if (!_enfonce)
        Target.Draw(_spr_bouton);
    else
        Target.Draw(_spr_bouton_enfonce);

    Target.Draw(*_text_bouton);
}

///
/// Permet de savoir si on se trouve sur un bouton
/// @param MouseX Position x de la souris
/// @param MouseY Position y de la souris
/// @return le résultat du test
///
bool Bouton::estDedans(int MouseX, int MouseY)
{
    return ( MouseX > (my_abs - (LONG_BUTTON/2)) && MouseX < (my_abs + (LONG_BUTTON/2)) && MouseY > (my_ord - (HAUT_BUTTON/2)) && MouseY < (my_ord + (HAUT_BUTTON/2)) );
}

///
/// Permet de savoir di un bouton est enfoncé
/// @return le résultat du test
///
bool Bouton::getEnfonce()
{
    return _enfonce;
}

///
/// Permet de mettre à jour l'état du bouton
/// @param etat nouvel état du bouton
///
void Bouton::setEnfonce(bool etat)
{
    _enfonce = etat;
}

///
/// Permet de changer la couleur du texte
/// @param color Couleur du texte du bouton
///
void Bouton::changeColor(sf::Color color)
{
    _text_bouton->SetColor(color);
}
